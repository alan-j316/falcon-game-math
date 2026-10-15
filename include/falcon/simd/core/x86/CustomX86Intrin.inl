#pragma once
/**
 * @file CustomX86Intrin.h
 * @author Alan Abraham P Kochumon
 * @date Created on: October 14, 2026
 *
 * @brief Custom implementation of non-native intrinsics for x86 architecture.
 *
 * @note Including this file standalone can cause compilation errors since it depends on
 *       definition of `CURRENT_SIMD_BACKEND`.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "falcon/core/Preprocessors.h"

#include <immintrin.h>

namespace flcn::intrin
{
    ///+=+=+=+=+=+=+=+=+=+=+=
    /// MM128(XMM) Registers
    ///+=+=+=+=+=+=+=+=+=+=+=

    /// @brief Perform a logical right shift on the 128-bit register composed of Byte values.
    FALCON_INLINE constexpr __m128i _mm_srl_epi8_custom(const __m128i reg, const uint32_t count) noexcept
    {
        // Since there is no direct shift operation for 8-bit integers
        // we need to shift using epi16 and apply a mask to the overflow
        // ([1001 1001] [1001 1001]) >> 3 = [0010 0110] [0010 0110]
        // We first mask out the bit that will be zero when shifted
        // [1111 1111] << 3 -> [1111 1000] Create the mask
        // [1001 1001] & [1111 1000] = [1001 1000] And apply it
        const auto countReg = _mm_cvtsi32_si128(count); // Load the shift value into the lower 32-bit lanes
        const auto mask     = 0xff << count;
        const auto maskReg  = _mm_set1_epi8(static_cast<int8_t>(mask));
        const auto andReg   = _mm_and_si128(reg, maskReg);
        // Now we shift the entire register to the left by shiftCount
        // since the overflown values are already zero-ed out shifting this will
        // create the correct put.
        // [1001 1000] [1001 1000] >> 3
        // [0010 1100] [0010 1100]
        return _mm_srl_epi16(andReg, countReg);
    }


    /// @brief Perform a arithmetic right shift on the 128-bit register composed of Quad Word (64-bit integral) values.
    FALCON_INLINE constexpr __m128i _mm_sra_epi64_custom(const __m128i reg, const __m128i count) noexcept
    {
        if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX) // AVX512F + VL
        {
            return _mm_sra_epi64(reg, count);
        }
        else
        {
            // Hacker Delight Ch.2 (2-7)
            // ((x + 0x8000..00) u>> n) - (0x8000.000 u>> n)
            // For signed shift we need to first remove the sign bit or add it (if its a positive number)
            // and then we shift both the sum and the sign by the shifted amount.
            // Finally subtracting the sign will remove the sign if it was a unsigned number(or positive signed
            // number) or if it was a negative number, it will cause an signed overflow since we are subtracting a
            // smaller number from a larger number(sign will be larger), which will fill all the shifted spaces with 1.
            // -7(1101) >> 2 = -1(1111)                          | 5(0101) >> 2 = 1(0001)                        |
            // 1101 + 1000 = 0101 (Overflow)                     | 0101 + 1000  = 1101                           |
            // 0101 >> 2   = 0001                                | 1101 >> 2    = 0011                           |
            // 1000 >> 2   = 0010                                | 1000 >> 2    = 0010                           |
            // 0001 - 0010 = 1111 (Borrowed bit signed overflow) | 0011 - 0010  = 0001                           |
            const auto signReg        = _mm_set1_epi64x(0x8000000000000000ULL);
            const auto sumReg         = _mm_add_epi64(reg, signReg);
            const auto shiftedSumReg  = _mm_srl_epi64(sumReg, count);
            const auto shiftedSignReg = _mm_srl_epi64(signReg, count);
            return _mm_sub_epi64(shiftedSumReg, shiftedSignReg);
        }
    }


    /// @brief Perform a logical left shift on the 128-bit register composed of Byte values by a constant known
    ///        at compile time.
    /// @tparam Count The shift amount.
    template <uint32_t Count>
    FALCON_INLINE constexpr __m128i _mm_slli_epi8_custom(const __m128i reg) noexcept
    {
        // 8-bit integrals have no right or left shift operations so, we need to mask out the overflow bits
        // and then do a shift using the epi16 intrinsic.
        // Since this is a left shift operations values to to the right will need to be masked.
        constexpr auto mask = 0xFF >> Count;                             // 0b0011 1111(Assume Count = 2)
        const auto maskReg  = _mm_set1_epi8(static_cast<uint8_t>(mask)); // [0b00111111, 0b00111111, ..]
        const auto andReg   = _mm_and_si128(reg, maskReg);               // [00xxxxxx, 00xxxxxx, 00xxxxxx,..]
        return _mm_slli_epi16(andReg, Count);
    }


    /// @brief Perform a arithmetic right shift on the 128-bit register composed of Quad Word (64-bit integral) values
    ///        by a constant known at compile time.
    /// @tparam Count The shift amount.
    template <uint32_t Count>
    FALCON_INLINE constexpr __m128i _mm_srai_epi64_custom(const __m128i reg) noexcept
    {
        // Until AVX512F + VL there is no dedicated srai function so, we need to use xor to convert the signed
        // values to unsigned and then shifted and the sign bits.
        if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
        {
            return _mm_srai_epi64(reg, Count);
        }
        else
        {
            // Hacker Delight Ch.2 (2-7) (See a detailed example in operator>> definition)
            // t = -(x u>> 63) // This is -1(0b111..111) for negative numbers and 0 for positive numbers.
            // res = ((x xor t) u>> Count) xor t
            const auto signShifted   = _mm_srli_epi64(reg, 63); // x u>> 63
            const auto t             = _mm_sub_epi64(_mm_setzero_si128(), signShifted);
            const auto signIsolated  = _mm_xor_si128(reg, t);               // x xor t
            const auto unsignedShift = _mm_srli_epi64(signIsolated, Count); // (x xor t) u>> Count
            return _mm_xor_si128(unsignedShift, t);
        }
    }


    /// @brief Perform a logical left right on the 128-bit register composed of Byte values by a constant known
    ///        at compile time.
    /// @tparam Count The shift amount.
    template <uint32_t Count>
    FALCON_INLINE constexpr __m128i _mm_srli_epi8_custom(const __m128i reg) noexcept
    {
        // Since we don't have 8-bit integral logical right shift intrinsic we need to use masks to mask out all the
        // bits that are not overflown, and then use epi16 shifts.
        // See _mm_srl_epi8_custom for a detailed example.
        constexpr auto mask = 0xff << Count; // 0b11111100 (Assume Count = 2)
        const auto maskReg  = _mm_set1_epi8(static_cast<uint8_t>(mask));
        // This essentially pseudo-shifts by zeroing out the bit in that would have zeroed out if
        // performed the shift.
        const auto andReg = _mm_and_si128(reg, maskReg);
        // The final shift, shifts the binary values to their shifted place.
        return _mm_srli_epi16(andReg, Count);
    }

    /// @brief Perform a arithmetic left right on the 128-bit register composed of Byte values by a constant known
    ///        at compile time.
    /// @tparam Count The shift amount.
    template <uint32_t Count>
    FALCON_INLINE constexpr __m128i _mm_srai_epi8_custom(const __m128i reg) noexcept
    {
        // For arithmetic shifts we can use the XOR trick from Hackers Delight explained in operator>> or
        // _mm_srai_epi64_custom implementation.
        const auto shiftedSign = _mm_srli_epi8_custom<7>(reg);                   // Extract the sign bit to the LSB
        const auto t           = _mm_sub_epi8(_mm_setzero_si128(), shiftedSign); // t = -(x u>> 7)
        const auto unsignedReg = _mm_xor_si128(reg, t);                          // x xor t => Remove the sign bit
        const auto shiftedReg  = _mm_srli_epi8_custom<Count>(unsignedReg);       // x xor t u>> Count.
        // Add back the sign bit and return
        return _mm_xor_si128(shiftedReg, t); // ((x xor t) u>> Count) xor t
    }


    /// @brief Unpack the lower lanes of the integral register into the next power of 2 (16->32).
    ///        with sign saturation.
    /// @note This has no effect on the 64-bit integrals.
    template <typename DataType>
    FALCON_INLINE constexpr __m128i _mm_unpacklo_saturated_custom(const __m128i reg) noexcept
    {
        // NOTE: Floats are not handled.
        // For unpacking signed numbers, we need to unpack a number with itself and
        // expands its sign bits through arithmetic right shift.
        // For expanding 1011 we can do
        // Unpack 1011 1011 a>> 4 bits
        // Res    1111 1011
        // Signed integrals
        if constexpr (types::IsDWord<DataType>)
        {
            /// Since there is no srai for epi64 we can create a sign bit mask
            /// with srai
            /// 1000 1011 = 1111 1111
            /// and unpack the sign bits with the register
            /// 1111 1011
            const auto signBits = _mm_srai_epi32(reg, 31);
            return _mm_unpacklo_epi32(reg, signBits);
        }
        else if constexpr (types::IsWord<DataType>)
        {
            const auto unpacked = _mm_unpacklo_epi16(reg, reg);
            return _mm_srai_epi32(unpacked, 16);
        }
        else if constexpr (types::IsByte<DataType>)
        {
            const auto unpacked = _mm_unpacklo_epi8(reg, reg);
            return _mm_srai_epi16(unpacked, 8);
        }
        // Unsigned integrals
        else if constexpr (types::IsUDWord<DataType>)
        {
            return _mm_unpacklo_epi32(reg, _mm_setzero_si128());
        }
        else if constexpr (types::IsUWord<DataType>)
        {
            return _mm_unpacklo_epi16(reg, _mm_setzero_si128());
        }
        else if constexpr (types::IsUByte<DataType>)
        {
            return _mm_unpacklo_epi8(reg, _mm_setzero_si128());
        }
        else
        {
            // 64-bit integrals are not unpacked further
            return reg;
        }
    }


    /// @brief Unpack the upper lanes of the integral register into the next power of 2 (16->32)
    ///        with sign saturation.
    /// @note This has no effect on the 64-bit integrals.
    template <typename DataType>
    FALCON_INLINE constexpr __m128i _mm_unpackhi_saturated_custom(const __m128i reg) noexcept
    {
        // NOTE: Floats are not handled.
        // For unpacking signed numbers, we need to unpack a number with itself and
        // expands its sign bits through arithmetic right shift.
        // For expanding 1011 we can do
        // Unpack 1011 1011 a>> 4 bits
        // Res    1111 1011
        // Signed integrals
        if constexpr (types::IsDWord<DataType>)
        {
            /// Since there is no srai for epi64 we can create a sign bit mask
            /// with srai
            /// 1000 1011 = 1111 1111
            /// and unpack the sign bits with the register
            /// 1111 1011
            const auto signBits = _mm_srai_epi32(reg, 31);
            return _mm_unpackhi_epi32(reg, signBits);
        }
        else if constexpr (types::IsWord<DataType>)
        {
            const auto unpacked = _mm_unpackhi_epi16(reg, reg);
            return _mm_srai_epi32(unpacked, 16);
        }
        else if constexpr (types::IsByte<DataType>)
        {
            const auto unpacked = _mm_unpackhi_epi8(reg, reg);
            return _mm_srai_epi16(unpacked, 8);
        }
        // Unsigned integrals
        else if constexpr (types::IsUDWord<DataType>)
        {
            return _mm_unpackhi_epi32(reg, _mm_setzero_si128());
        }
        else if constexpr (types::IsUWord<DataType>)
        {
            return _mm_unpackhi_epi16(reg, _mm_setzero_si128());
        }
        else if constexpr (types::IsUByte<DataType>)
        {
            return _mm_unpackhi_epi8(reg, _mm_setzero_si128());
        }
        else
        {
            // 64-bit integrals are not unpacked further
            return reg;
        }
    }



    //==================================================================================================================
    ///+=+=+=+=+=+=+=+=+=+=+=
    /// MM256(YMM) Registers
    ///+=+=+=+=+=+=+=+=+=+=+=

    /// @brief Perform a logical left shift on the 256-bit register composed of Quad Word values.
    FALCON_INLINE __m256i _mm256_sll_epi64_custom(const __m256i reg, const __m128i count) noexcept
    {
        if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX2)
        {
            return _mm256_sll_epi64(reg, count);
        }
        else
        {
            // AVX doesn't have integral shifts so we have to extract them
            // and perform 2 128-bit shifts, insert, and cast back.
            const auto loReg = _mm256_castsi256_si128(reg);
            const auto hiReg = _mm256_extracti128_si256(reg, 1);

            const auto loShifted = _mm256_castsi128_si256(_mm_sll_epi64(loReg, count));
            const auto hiShifted = _mm_sll_epi64(hiReg, count);
            return _mm256_inserti128_si256(loShifted, hiShifted, 1);
        }
    }


    /// @brief Perform a logical left shift on the 256-bit register composed of Double Word values.
    FALCON_INLINE __m256i _mm256_sll_epi32_custom(const __m256i reg, const __m128i count) noexcept
    {
        if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX2)
        {
            return _mm256_sll_epi32(reg, count);
        }
        else
        {
            // AVX doesn't have integral shifts so we have to extract them
            // and perform 2 128-bit shifts, insert, and cast back.
            const auto loReg = _mm256_castsi256_si128(reg);
            const auto hiReg = _mm256_extracti128_si256(reg, 1);

            const auto loShifted = _mm256_castsi128_si256(_mm_sll_epi32(loReg, count));
            const auto hiShifted = _mm_sll_epi32(hiReg, count);
            return _mm256_inserti128_si256(loShifted, hiShifted, 1);
        }
    }


    /// @brief Perform a logical left shift on the 256-bit register composed of Byte values.
    FALCON_INLINE __m256i _mm256_sll_epi8_custom(const __m256i reg, const uint32_t count) noexcept
    {
        // There is no native shifts for epi8
        // so we need to mask the bits that will be zeroed out
        // and shift using epi16
        // Example using 8-bit register and 4-bit shifts
        // [1011 1101] << 2 => [1100 0100]
        // Mask = 0b1111 >> 2 = 0b0011
        // Mask Reg = 0011 0011
        // And Reg  = 1011 1101 & 0011 0011
        //          = 0011 0001
        // 0011 0001 8<< 2 1100 0100
        const auto mask     = 0xff >> count;
        const auto maskReg  = _mm256_set1_epi8(mask);
        const auto countReg = _mm_cvtsi32_si128(count);
        const auto andReg   = _mm256_and_si256(reg, maskReg);
        return _mm256_sll_epi16(andReg, countReg);
    }


    /// @brief Perform a logical left shift on the 256-bit register composed of Quad Word values
    ///        with a compile time constant.
    /// @tparam Count The shift amount.
    template<uint32_t Count>
    FALCON_INLINE __m256i _mm256_slli_epi64_custom(const __m256i reg) noexcept
    {
        if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX2)
        {
            return _mm256_slli_epi64(reg, Count);
        }
        else
        {
            // AVX doesn't have integral shifts so we have to extract them
            // and perform 2 128-bit shifts, insert, and cast back.
            const auto loReg = _mm256_castsi256_si128(reg);
            const auto hiReg = _mm256_extracti128_si256(reg, 1);

            const auto loShifted = _mm256_castsi128_si256(_mm_slli_epi64(loReg, Count));
            const auto hiShifted = _mm_slli_epi64(hiReg, Count);
            return _mm256_inserti128_si256(loShifted, hiShifted, 1);
        }
    }


    /// @brief Perform a logical left shift on the 256-bit register composed of Double Word values
    ///        with a compile time constant.
    /// @tparam Count The shift amount.
    template<uint32_t Count>
    FALCON_INLINE __m256i _mm256_slli_epi32_custom(const __m256i reg) noexcept
    {
        if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX2)
        {
            return _mm256_slli_epi32(reg, Count);
        }
        else
        {
            // AVX doesn't have integral shifts so we have to extract them
            // and perform 2 128-bit shifts, insert, and cast back.
            const auto loReg = _mm256_castsi256_si128(reg);
            const auto hiReg = _mm256_extracti128_si256(reg, 1);

            const auto loShifted = _mm256_castsi128_si256(_mm_slli_epi32(loReg, Count));
            const auto hiShifted = _mm_slli_epi32(hiReg, Count);
            return _mm256_inserti128_si256(loShifted, hiShifted, 1);
        }
    }


    /// @brief Perform a logical left shift on the 256-bit register composed of Byte values
    ///        with a compile time constant.
    /// @tparam Count The shift amount.
    template <uint32_t Count>
    FALCON_INLINE __m256i _mm256_slli_epi8_custom(const __m256i reg) noexcept
    {
        // There is no native shifts for epi8
        // so we need to mask the bits that will be zeroed out
        // and shift using epi16
        constexpr auto mask = static_cast<uint8_t>(0xff >> Count);
        const auto maskReg  = _mm256_set1_epi8(mask);
        const auto andReg   = _mm256_and_si256(reg, maskReg);
        return _mm256_slli_epi16(andReg, Count);
    }


    /// @brief Perform a logical right shift on the 256-bit register composed of Quad Word values.
    FALCON_INLINE __m256i _mm256_srl_epi64_custom(const __m256i reg, const __m128i count) noexcept
    {
        if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX2)
        {
            return _mm256_srl_epi64(reg, count);
        }
        else
        {
            // AVX doesn't have integral shifts so we have to extract them
            // and perform 2 128-bit shifts, insert, and cast back.
            const auto loReg = _mm256_castsi256_si128(reg);
            const auto hiReg = _mm256_extracti128_si256(reg, 1);

            const auto loShifted = _mm256_castsi128_si256(_mm_srl_epi64(loReg, count));
            const auto hiShifted = _mm_srl_epi64(hiReg, count);
            return _mm256_inserti128_si256(loShifted, hiShifted, 1);
        }
    }


    /// @brief Perform a logical right shift on the 256-bit register composed of Double Word values.
    FALCON_INLINE __m256i _mm256_srl_epi32_custom(const __m256i reg, const __m128i count) noexcept
    {
        if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX2)
        {
            return _mm256_srl_epi32(reg, count);
        }
        else
        {
            // AVX doesn't have integral shifts so we have to extract them
            // and perform 2 128-bit shifts, insert, and cast back.
            const auto loReg = _mm256_castsi256_si128(reg);
            const auto hiReg = _mm256_extracti128_si256(reg, 1);

            const auto loShifted = _mm256_castsi128_si256(_mm_srl_epi32(loReg, count));
            const auto hiShifted = _mm_srl_epi32(hiReg, count);
            return _mm256_inserti128_si256(loShifted, hiShifted, 1);
        }
    }


    /// @brief Perform a logical right shift on the 256-bit register composed of Quad Word values
    ///        with a compile time constant.
    /// @tparam Count The shift amount.
    template<uint32_t Count>
    FALCON_INLINE __m256i _mm256_srli_epi64_custom(const __m256i reg) noexcept
    {
        if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX2)
        {
            return _mm256_srli_epi64(reg, Count);
        }
        else
        {
            // AVX doesn't have integral shifts so we have to extract them
            // and perform 2 128-bit shifts, insert, and cast back.
            const auto loReg = _mm256_castsi256_si128(reg);
            const auto hiReg = _mm256_extracti128_si256(reg, 1);

            const auto loShifted = _mm256_castsi128_si256(_mm_srli_epi64(loReg, Count));
            const auto hiShifted = _mm_srli_epi64(hiReg, Count);
            return _mm256_inserti128_si256(loShifted, hiShifted, 1);
        }
    }


    /// @brief Perform a logical right shift on the 256-bit register composed of Double Word values
    ///        with a compile time constant.
    /// @tparam Count The shift amount.
    template<uint32_t Count>
    FALCON_INLINE __m256i _mm256_srli_epi32_custom(const __m256i reg) noexcept
    {
        if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX2)
        {
            return _mm256_srli_epi32(reg, Count);
        }
        else
        {
            // AVX doesn't have integral shifts so we have to extract them
            // and perform 2 128-bit shifts, insert, and cast back.
            const auto loReg = _mm256_castsi256_si128(reg);
            const auto hiReg = _mm256_extracti128_si256(reg, 1);

            const auto loShifted = _mm256_castsi128_si256(_mm_srli_epi32(loReg, Count));
            const auto hiShifted = _mm_srli_epi32(hiReg, Count);
            return _mm256_inserti128_si256(loShifted, hiShifted, 1);
        }
    }


    /// @brief Perform a logical right shift on the 256-bit register composed of Byte values.
    FALCON_INLINE __m256i _mm256_srl_epi8_custom(const __m256i reg, const uint32_t count) noexcept
    {
        // There is no native shifts for epi8
        // so we need to mask the bits that will be zeroed out
        // and shift using epi16
        // Example using 8-bit register and 4-bit shifts
        // [1011 1101] >> 2 => [0010 1111]
        // Mask = 0b1111 << 2 = 0b1100
        // Mask Reg = 1100 1100
        // And Reg  = 1011 1101 & 1100 1100
        //          = 1000 1100
        // 1000 1100 8>> 2 0010 1111
        const auto mask     = 0xff << count;
        const auto maskReg  = _mm256_set1_epi8(mask);
        const auto countReg = _mm_cvtsi32_si128(count);
        const auto andReg   = _mm256_and_si256(reg, maskReg);
        return _mm256_srl_epi16(andReg, countReg);
    }


    /// @brief Perform a logical right shift on the 256-bit register composed of Byte values
    ///        with a compile time constant.
    /// @tparam Count The shift amount.
    template <uint32_t Count>
    FALCON_INLINE __m256i _mm256_srli_epi8_custom(const __m256i reg) noexcept
    {
        // There is no native shifts for epi8
        // so we need to mask the bits that will be zeroed out
        // and shift using epi16
        constexpr auto mask = static_cast<uint8_t>(0xff << Count);
        const auto maskReg  = _mm256_set1_epi8(mask);
        const auto andReg   = _mm256_and_si256(reg, maskReg);
        return _mm256_srli_epi16(andReg, Count);
    }

    /// @brief Perform an arithmetic right shift on the 256-bit register composed of Quad Word values.
    FALCON_INLINE __m256i _mm256_sra_epi64_custom(const __m256i reg, const __m128i count) noexcept
    {
        if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
        {
            return _mm256_sra_epi64(reg, count);
        }
        else
        {
            // AVX doesn't have integral shifts so we have to extract them
            // and perform 2 128-bit shifts, insert, and cast back.
            const auto loReg     = _mm256_castsi256_si128(reg);
            const auto hiReg     = _mm256_extracti128_si256(reg, 1);
            const auto loShifted = _mm256_castsi128_si256(_mm_sra_epi64_custom(loReg, count));
            const auto hiShifted = _mm_sra_epi64_custom(hiReg, count);
            return _mm256_inserti128_si256(loShifted, hiShifted, 1);
        }
    }


    /// @brief Perform an arithmetic right shift on the 256-bit register composed of Double Word values.
    FALCON_INLINE __m256i _mm256_sra_epi32_custom(const __m256i reg, const __m128i count) noexcept
    {
        if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX2)
        {
            return _mm256_sra_epi32(reg, count);
        }
        else
        {
            // AVX doesn't have integral shifts so we have to extract them
            // and perform 2 128-bit shifts, insert, and cast back.
            const auto loReg = _mm256_castsi256_si128(reg);
            const auto hiReg = _mm256_extracti128_si256(reg, 1);

            const auto loShifted = _mm256_castsi128_si256(_mm_sra_epi32(loReg, count));
            const auto hiShifted = _mm_sra_epi32(hiReg, count);
            return _mm256_inserti128_si256(loShifted, hiShifted, 1);
        }
    }



    /// @brief Perform an arithmetic right shift on the 256-bit register composed of Quad Word values
    ///        with a compile time constant.
    /// @tparam Count The shift amount.
    template<uint32_t Count>
    FALCON_INLINE __m256i _mm256_srai_epi64_custom(const __m256i reg) noexcept
    {
        if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
        {
            return _mm256_srai_epi64(reg, Count);
        }
        else
        {
            // Hacker Delight Ch.2 (2-7)
            // ((x + 0x8000..00) u>> n) - (0x8000.000 u>> n)
            // For signed shift we need to first remove the sign bit or add it (if its a positive number)
            // and then we shift both the sum and the sign by the shifted amount.
            // Finally subtracting the sign will remove the sign if it was a unsigned number(or positive signed
            // number) or if it was a negative number, it will cause an signed overflow since we are subtracting a
            // smaller number from a larger number(sign will be larger), which will fill all the shifted spaces with 1.
            // -7(1101) >> 2 = -1(1111)                          | 5(0101) >> 2 = 1(0001)                        |
            // 1101 + 1000 = 0101 (Overflow)                     | 0101 + 1000  = 1101                           |
            // 0101 >> 2   = 0001                                | 1101 >> 2    = 0011                           |
            // 1000 >> 2   = 0010                                | 1000 >> 2    = 0010                           |
            // 0001 - 0010 = 1111 (Borrowed bit signed overflow) | 0011 - 0010  = 0001                           |
            const auto signReg        = _mm256_set1_epi64x(0x8000000000000000ULL);
            const auto sumReg         = _mm256_add_epi64(reg, signReg);
            const auto shiftedSumReg  = _mm256_srli_epi64(sumReg, Count);
            const auto shiftedSignReg = _mm256_srli_epi64(signReg, Count);
            return _mm256_sub_epi64(shiftedSumReg, shiftedSignReg);
            // TODO: Update sra(256) with the same logic
        }
    }


    /// @brief Perform an arithmetic right shift on the 256-bit register composed of Double Word values
    ///        with a compile time constant.
    /// @tparam Count The shift amount.
    template<uint32_t Count>
    FALCON_INLINE __m256i _mm256_srai_epi32_custom(const __m256i reg) noexcept
    {

        const auto loReg = _mm256_castsi256_si128(reg);
        const auto hiReg = _mm256_extracti128_si256(reg, 1);

        const auto loShifted = _mm256_castsi128_si256(_mm_srai_epi32(loReg, Count));
        const auto hiShifted = _mm_srai_epi32(hiReg, Count);
        return _mm256_inserti128_si256(loShifted, hiShifted, 1);
        // if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX2)
        // {
        //     return _mm256_srli_epi32(reg, Count);
        // }
        // else
        // {
        //     // AVX doesn't have integral shifts so we have to extract them
        //     // and perform 2 128-bit shifts, insert, and cast back.
        //     const auto loReg = _mm256_castsi256_si128(reg);
        //     const auto hiReg = _mm256_extracti128_si256(reg, 1);
        //
        //     const auto loShifted = _mm256_castsi128_si256(_mm_srli_epi32(loReg, Count));
        //     const auto hiShifted = _mm_srli_epi32(hiReg, Count);
        //     return _mm256_inserti128_si256(loShifted, hiShifted, 1);
        // }
    }

} // namespace flcn::intrin
