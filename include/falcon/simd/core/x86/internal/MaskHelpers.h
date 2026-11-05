#pragma once
/**
 * @file MaskHelpers.h
 * @author Alan Abraham P Kochumon
 * @date Created on: November 04, 2026
 *
 * @brief Helper utilities for SIMD mask creation and shuffling.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <array>
#include <cstddef>
#include <cstdint>


namespace flcn::simd::internal
{
    /**
     * Generate a suitable shuffle mask set for 16x16 register(mm256).
     * @tparam Lane  The number of lanes in the register.
     * @tparam Index The shuffle indices.
     * @return Selection indices for original and permuted array.
     *         First -  Selection index for in-lane shuffling
     *         Second - Selection index for permuted register.
     *         Return 0x80 for element if the current index is out-of-lane.
     */
    template <size_t Lane, uint8_t... Index>
        requires(sizeof...(Index) == 16)
    consteval std::pair<std::array<uint8_t, 32>, std::array<uint8_t, 32>> mm256Epi16PermMask() noexcept
    {
        // To perform a shuffle with _mm256_shuffle_epi8 we need to create 2 masks.
        // One for in-place shuffle and one for cross-lane shuffle.
        // In-place shuffles the register elements as is without crossing the 128-bit boundary.
        // Cross-lane shuffles elements after upper and lower lanes are exchanged.
        // [3, 2 | 1, 0] -After Exchange-> [1, 0 | 3, 2]
        //
        // We put 0x80* in any of the indices where the lanes are crossed.
        // [   1,    6,    7,    5 |    4,    2,    0,    3]
        // [0x80,    6,    7,    5 | 0x80,    2,    0,    3] // In-Place
        // [   1, 0x80, 0x80, 0x80 |    4, 0x80, 0x80, 0x80] // Cross-Lane
        //
        // _mm256_shuffle_epi8 expects shuffling 8-bits so a total of 32 indices are required.
        // We can convert from 16 indices to 32 by using 2n and (2n + 1) as a single index.
        // Example: 15 -> 30(2n) and 31(2n + 1)
        //
        // One other transform we need to do is ensure that each of 16 or 32 index is clamped to only half the size
        // since the 128-bit registers are independently permuted.
        // [3, 2, 1, 0 | 3, 2, 1, 0] for a 8 element register.
        //
        // *_mm256_shuffle_epi8 does 128-bit same lane shuffle, but it will convert any bytes with 0x80 mask into 0.

        constexpr uint8_t indices[]{ Index... };

        // In Lane Index  - Shuffling indices of elements in the same lane.
        // Permuted Index - Shuffling indices of elements that has cross lanes.
        std::array<uint8_t, 32> inLaneIdx{}, permutedIdx{};

        constexpr auto HalfLane = Lane >> 1; // Lane / 2

        for (size_t i = 0; i < sizeof...(Index); ++i)
        {
            // Lane is crossed if the we are iterating the lower half and the index is greater than or
            // equal to the middle index or if a index less than middle index is found in the upper portion.
            // Example: [1, 7, 5, 4| 2, 3, 6, 0]
            //          Here, 1 crossed the lane since it's greater than 4 (4-7 is the upper lane index).
            //          6 crossed because its greater than 3(0-3 is the lower lane)
            const bool inSameLane =
                (i >= HalfLane && indices[i] >= HalfLane) || (i < HalfLane && indices[i] < HalfLane);
            // If the indices are in the same lane, we can just pass it as it is but switch the permuted to 0x80.
            if (inSameLane)
            {
                // NOTE: We can only shuffle within the 16 positions so the the positions are split into
                //       [16-0 | 16-0] so we need to % by Lane or 16 to index the values in that range.
                // We mod by the Lane since we need to take the 16 indices and transforming it into 32
                // by using adjacency math (2n and 2n + 1).
                //
                // We need to update 2 indices as we want to shuffle a epi16 register with 8-bit shuffle.
                // so 2n and 2n+1 gives the adjacent registers.
                // NOTE: Mode by Lane is used since we are having mask index of size 32.
                inLaneIdx[i * 2]     = (indices[i] * 2) % Lane;
                inLaneIdx[i * 2 + 1] = (indices[i] * 2 + 1) % Lane;

                permutedIdx[i * 2]     = 0x80;
                permutedIdx[i * 2 + 1] = 0x80;
            }
            else
            {
                permutedIdx[i * 2]     = (indices[i] * 2) % Lane;
                permutedIdx[i * 2 + 1] = (indices[i] * 2 + 1) % Lane;

                inLaneIdx[i * 2]     = 0x80;
                inLaneIdx[i * 2 + 1] = 0x80;
            }
        }
        return { inLaneIdx, permutedIdx };
    }


    /**
     * Generate a suitable shuffle mask set for 8x32register(mm256).
     * @tparam Lane  The number of lanes in the register.
     * @tparam Index The shuffle indices. Must be 32.
     * @return Selection indices for original and permuted array.
     *         First -  Selection index for in-lane shuffling
     *         Second - Selection index for permuted register.
     *         Return 0x80 for element if the current index is out-of-lane.
     */
    template <size_t Lane, uint8_t... Index>
        requires(sizeof...(Index) == 32)
    consteval std::pair<std::array<uint8_t, 32>, std::array<uint8_t, 32>> mm256Epi8PermMask() noexcept
    {
        // To perform a shuffle with _mm256_shuffle_epi8 we need to create 2 masks.
        // One for in-place shuffle and one for cross-lane shuffle.
        // In-place shuffles the register elements as is without crossing the 128-bit boundary.
        // Cross-lane shuffles elements after upper and lower lanes are exchanged.
        // [3, 2 | 1, 0] -After Exchange-> [1, 0 | 3, 2]
        //
        // We put 0x80* in any of the indices where the lanes are crossed.
        // [   1,    6,    7,    5 |    4,    2,    0,    3]
        // [0x80,    6,    7,    5 | 0x80,    2,    0,    3] // In-Place
        // [   1, 0x80, 0x80, 0x80 |    4, 0x80, 0x80, 0x80] // Cross-Lane
        //
        // Then need to ensure that each of the 32 indices are clamped to only half the size
        // since the 128-bit registers are independently permuted.
        // [3, 2, 1, 0 | 3, 2, 1, 0] for a 8 element register.
        //
        // *_mm256_shuffle_epi8 does 128-bit same lane shuffle, but it will convert any bytes with 0x80 mask into 0.

        constexpr uint8_t indices[]{ Index... };

        // In Lane Index  - Shuffling indices of elements in the same lane.
        // Permuted Index - Shuffling indices of elements that has crossed lanes.
        std::array<uint8_t, 32> inLaneIdx{}, permutedIdx{};

        constexpr auto HalfLane = Lane >> 1; // Lane / 2

        for (size_t i = 0; i < sizeof...(Index); ++i)
        {
            // Lane is crossed if the we are iterating the lower half and the index is greater than or
            // equal to the middle index or if a index less than middle index is found in the upper portion.
            // Example: [1, 7, 5, 4| 2, 3, 6, 0]
            //          Here, 1 crossed the lane since it's greater than 4 (4-7 is the upper lane index).
            //          6 crossed because its greater than 3(0-3 is the lower lane)
            const bool inSameLane =
                (i >= HalfLane && indices[i] >= HalfLane) || (i < HalfLane && indices[i] < HalfLane);
            // If the indices are in the same lane, we can just pass it as it is but switch the permuted to 0x80.
            if (inSameLane)
            {
                // NOTE: We can only shuffle within the 16 positions so the the positions are split into
                //       [16-0 | 16-0] so we need to % by Half the lanes or 16 to index the values in that range.
                inLaneIdx[i] = indices[i] % HalfLane;

                permutedIdx[i] = 0x80;
            }
            else
            {
                permutedIdx[i] = indices[i] % HalfLane;

                inLaneIdx[i] = 0x80;
            }
        }
        return { inLaneIdx, permutedIdx };
    }


    /**
     * @brief Create an integer blend mask for a set of permute indices for blending based on whether the indices
     *        cross the half-lane.
     * @tparam Lane  The lane count.
     *
     * @param indices The permute indices.
     * @return A packed integer bitmask with 1 indicating that the index is in-lane and 0 indicating a boundary cross.
     */
    template <size_t Lane, size_t Size>
    consteval uint32_t createInLaneBlendMask(const uint8_t (&indices)[Size]) noexcept
    {
        // [2, 0 | 3, 1]
        //  1  0   0  1
        // Mask = 0b000..01001
        constexpr auto halfLane = Lane / 2;
        uint32_t mask           = 0;
        for (size_t i = 0; i < Size; ++i)
        {
            const bool inSameLane =
                (i < halfLane && indices[i] < halfLane) || (i >= halfLane && indices[i] >= halfLane);
            mask |= static_cast<uint32_t>(inSameLane) << i;
        }
        return mask;
    }

} // namespace flcn::simd::internal
