#pragma once
/**
 * @file SIMDUtils.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief SIMD utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "TypeTraits.h"

#include <algorithm>
#include <bit>
#include <cstddef>
#include <type_traits>

namespace flcn::simd
{
    struct PackingParams
    {
        size_t alignedByteSize;
        size_t padding;
        size_t packedRegisterWidth;
        size_t registerCount;
    };

    /**
     * @brief Calculate the aligned Byte Size, padding, packed register width, and number of registers required to store
     *        the given bytes, with a given alignment.
     *
     * @param totalByteSize The total unaligned byte size.
     * @param maxAlignAs    The maximum possible alignment for a given CPU architecture.
     *                      **16 for SSE, 32 for AVX and AVX2, and 64 for AVX512**
     *
     * @return The aligned byte size, additional required padding, target register width,
     *         and number of registers required to pack the given bytes.
     */
    constexpr PackingParams calculatePackedSize(const size_t totalByteSize, const size_t maxAlignAs)
    {
        if (totalByteSize < 16)
        {
            return PackingParams{ 16, 16 - totalByteSize, 16, 1 };
        }

        const size_t packedSize           = std::bit_ceil(totalByteSize);
        const size_t optimalRegisterWidth = std::min(packedSize, maxAlignAs);
        const size_t numRegisters         = packedSize / optimalRegisterWidth;

        return PackingParams{ packedSize, packedSize - totalByteSize, optimalRegisterWidth, numRegisters };
    }


    // TODO: Add tests
    template <typename T>
    constexpr T getAllOnes()
    {
        if constexpr (std::is_integral_v<T>)
        {
            return static_cast<T>(-1);
        }
        else if constexpr (sizeof(T) == 4)
        {
            return std::bit_cast<T>(0xFFFFFFFF);
        }
        else if constexpr (sizeof(T) == 8)
        {
            return std::bit_cast<T>(0xFFFFFFFFFFFFFFFF);
        }
        else
        {
            return 1; // Shouldn't hit this path.
        }
    }



    /**
     * @brief Create a mask for register value blending.
     *
     * @tparam MaxLaneCount The maximum lane count of the target register/type combination.
     *                      Example: For a 128-bit lane with int32_t it will be 4 (128/32).
     *                      Must be between 2 and 32(inclusive) and be a power of 2.
     * @tparam Mask         The bool mask to be converted. The first bool translates to the lower n-bits.
     *                      Number of Mask be between 2 and @p MaxLaneCount and must be a power of 2.
     *
     * @note MaxLaneCount is Register Width(128, 256, or 512)/size of the DataType in bits.
     * @note Using the makeBlendMask32 exposed Simd classes is recommended.
     *
     * @code
     * // int32_t x 4(lane) mask.
     * const auto mask = makeBlendMask32<4, true, false, true, false>();
     * // 0b00000000111111110000000011111111 or 0x00FF00FF
     * const auto mask = makeBlendMask32<16, true, false, true, true>();
     * // 0b00000000000000000000000011110011 or 0x000000F3
     * @endcode
     *
     * @return A 32-bit integral mask usable across Simd128/256/512 const blending.
     */
    template <size_t MaxLaneCount, bool... Mask>
        requires(std::has_single_bit(sizeof...(Mask)) && sizeof...(Mask) >= 2 && sizeof...(Mask) <= MaxLaneCount) &&
        (MaxLaneCount >= 2 && MaxLaneCount <= 32 && std::has_single_bit(MaxLaneCount))
    constexpr BlendMask32_t makeBlendMask32() noexcept
    {
        constexpr bool maskArr[]{ Mask... };

        // Creates the mask with appropriate shifts.
        // We create a mask by selecting an appropriate mask (0b11..11 if true, 0b0 otherwise)
        // and shifting by width required per mask for saturating the full 32-bits.
        // Eg: For a 4 lane register mask, we with the following mask <4, true, false, true, true>.
        //     That will expand into:
        //     0b11111111 << (0 * 8) | 0b00000000 << (1 * 8) | ob11111111 << (2 * 8) << | 0b00000000 << (3 * 8)
        //     Which will return 0b00000000111111110000000011111111
        //     And <4, false, true>.
        //     0b00000000 << (0 * 8) | 0b11111111 << (1 * 8)
        //     0b00000000000000001111111100000000
        const auto getMask = [&]<size_t... Indices>(std::index_sequence<Indices...>) {
            if constexpr (MaxLaneCount == 32)
            {
                // True Mask 0b1
                return (((maskArr[Indices] ? 0x1 : 0x0) << Indices) | ...);
            }
            else if constexpr (MaxLaneCount == 16)
            {
                // True Mask 0b11
                return (((maskArr[Indices] ? 0x3 : 0x0) << (Indices * 2)) | ...);
            }
            else if constexpr (MaxLaneCount == 8)
            {
                // True Mask 0b1111
                return (((maskArr[Indices] ? 0xF : 0x0) << (Indices * 4)) | ...);
            }
            else if constexpr (MaxLaneCount == 4)
            {
                // True Mask 0b11111111
                return (((maskArr[Indices] ? 0xFF : 0x00) << (Indices * 8)) | ...);
            }
            else if constexpr (MaxLaneCount == 2)
            {
                // True Mask 0b1111111111111111
                return (((maskArr[Indices] ? 0xFFFF : 0x0000) << (Indices * 16)) | ...);
            }
            else
            {
                return 0;
            }
        };
        return getMask(std::make_index_sequence<sizeof...(Mask)>());
    }



    // TODO: Make it more generalized later(2, 4, 8, 16...) and various types.
    // TODO: Update typename to Blend128_t?
    /**
     * @brief Expand a 32-bit BlendMask into 128-bit integer by performing bit expansion.
     *        For e.g: When `10` is expanded, we get `1111 0000`.
     *
     * @param mask The 32-bit mask to expand/unfold.
     * @return A custom @ref uint128_t type with the expanded values.
     */
    constexpr u128 expandFourFold(BlendMask32_t mask)
    {
        const auto expandByFour = [&]<size_t... Index>(size_t Offset, std::index_sequence<Index...>) -> size_t {
            constexpr size_t trueMask  = 0b1111ULL;
            constexpr size_t falseMask = 0b0000ULL;
            // For performing the expansion we can mask extract each bit and expand the bit value by 4,
            // and shift it into place.
#define __FLCN_EXP4_MASKED_EXTRACT (0b1ULL << (Index + Offset))
            return ((((mask & __FLCN_EXP4_MASKED_EXTRACT) == __FLCN_EXP4_MASKED_EXTRACT ? trueMask : falseMask)
                     << (Index * 4)) |
                    ...);
#undef __FLCN_EXP4_MASKED_EXTRACT
        };

        return u128{ .upper = expandByFour(16, std::make_index_sequence<16>{}),
                          .lower = expandByFour(0, std::make_index_sequence<16>{}) };
    }

    /**
     * @brief Expand a 32-bit BlendMask into 256-bit integer by performing bit expansion.
     *        For e.g: When `10` is expanded, we get `1111 0000`.
     *
     * @param mask The 32-bit mask to expand/unfold.
     * @return A custom @ref u256 type with the expanded values.
     */
    constexpr u256 expandEightFold(BlendMask32_t mask)
    {
        const auto expandByEight = [&]<size_t... Index>(size_t Offset, std::index_sequence<Index...>) -> size_t {
            constexpr size_t trueMask  = 0xFF;
            constexpr size_t falseMask = 0x00;
// For performing the expansion we can mask extract each bit and expand the bit value by 8,
// and shift it into place.
#define __FLCN_EXP8_MASKED_EXTRACT (0b1ULL << (Index + Offset))
            return ((((mask & __FLCN_EXP8_MASKED_EXTRACT) == __FLCN_EXP8_MASKED_EXTRACT ? trueMask : falseMask)
                     << (Index * 8)) |
                    ...);
#undef __FLCN_EXP8_MASKED_EXTRACT
        };

        // Take each 8 bit(8 iterations index sequence) and offset each by 8 bits to get the next quad part.
        return u256{ .quad3 = expandByEight(24, std::make_index_sequence<8>{}),
                     .quad2 = expandByEight(16, std::make_index_sequence<8>{}),
                     .quad1 = expandByEight(8, std::make_index_sequence<8>{}),
                     .quad0 = expandByEight(0, std::make_index_sequence<8>{}) };
    }


    /**
     * @brief Expand a Blend32_t into Blend64_t by performing bit expansion.
     *        For e.g: When `10` is expanded, we get `1100`.
     *
     * @param mask The 32-bit mask to expand/unfold.
     * @return A 64-bit BlendMask type with the expanded values.
     */
    constexpr BlendMask64_t expandTwoFold(BlendMask32_t mask)
    {
        const auto expandByTwo = [&]<size_t... Index>(size_t Offset, std::index_sequence<Index...>) -> size_t {
            constexpr size_t trueMask  = 0b11ULL;
            constexpr size_t falseMask = 0b00ULL;
// For performing the expansion we can mask extract each bit and expand the bit value by 2,
// and shift it into place.
#define __FLCN_EXP2_MASKED_EXTRACT (0b1ULL << (Index + Offset))
            return ((((mask & __FLCN_EXP2_MASKED_EXTRACT) == __FLCN_EXP2_MASKED_EXTRACT ? trueMask : falseMask)
                     << (Index * 2)) |
                    ...);
#undef __FLCN_EXP2_MASKED_EXTRACT
        };

        return expandByTwo(0, std::make_index_sequence<32>{});
    }



    /**
     * @brief Pack 32-bits into the lower N-bits.
     *
     * @note The algorithm only takes into consideration the Least Significant Bit(LSB) of the group.
     *       For example: Packing a 32-bit integer to 4-bits will result in a group size of 8,
     *       i.e, only the LSB from each of the 8 bits will be considered for packing.
     *
     * @tparam N   The resultant packing bit count.
     * @param mask The mask to pack.
     * @return A 32-bit mask with values packed to the lower N-bits.
     */
    template <size_t N>
        requires(N >= 2 && N <= 16 && std::has_single_bit(N))
    constexpr BlendMask32_t packToNBits(const BlendMask32_t mask)
    {
        // Group Size = datatype size in bits / (number of bits to compress to)
        // This would imply for compressing 32-bits(uint32_t) to 4-bits we take each group of 8,
        // and extract its LSB.
        constexpr auto groupSize = (sizeof(BlendMask32_t) * 8) / N;
        // For compression, we only regard the Least Significant Bit(LSB) from each of groups
        // and then shift them into place.
        // 1111 0000 1111 1111 -> 0000 0000 0000 1011(pack to 4-bits, showing 16-bit for simplicity)
#define _FLCN_BIT_EXTRACT (mask & (0x1U << (Index * groupSize)))
        const auto compress = [&]<size_t... Index>(std::index_sequence<Index...>) {
            return ((_FLCN_BIT_EXTRACT >> ((groupSize - 1) * Index)) | ...);
        };

#undef _FLCN_BIT_EXTRACT
        return static_cast<BlendMask32_t>(compress(std::make_index_sequence<N>{}));
    }


} // namespace flcn::simd
