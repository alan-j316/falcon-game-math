#pragma once
/**
 * @file Simd128X86Math.inl
 * @author Alan Abraham P Kochumon
 * @date Created on: September 18, 2026
 *
 * @brief Implementation of function declared in Simd128X86Math.h.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


namespace flcn
{
    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr _REG_128_SSE<DataType, Lane> min(_REG_128_SSE<DataType, Lane> a,
                                                             _REG_128_SSE<DataType, Lane> b) noexcept
    {
        // min function is not available for all data types and for some,
        // it was introduced with SSE4.1
        // As a workaround we use a > b ? b : a
        // with blend to get the correct min values.
        using Reg = _REG_128_SSE<DataType, Lane>;
        if constexpr (types::IsFP64<DataType>)
        {
            return Reg(_mm_min_pd(*a, *b));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            return Reg(_mm_min_ps(*a, *b));
        }
        // Types natively supported by SSE or SSE2(EPI16 and EPU8)
        // This allows us to remove redundant if CURRENT_SIMD_BACKEND conditionals in majority of the code.
        else if constexpr (types::IsWord<DataType>)
        {
            return Reg(_mm_min_epi16(*a, *b));
        }
        else if constexpr (types::IsUByte<DataType>)
        {
            return Reg(_mm_min_epu8(*a, *b));
        }
        else if constexpr (types::IsQWord<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
        {
            return Reg(_mm_min_epi64(*a, *b)); // AVX512F + VL
        }
        else if constexpr (types::IsUQWord<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
        {
            return Reg(_mm_min_epu64(*a, *b)); // AVX512F + VL
        }
        else if constexpr (types::IsDWord<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
        {
            return Reg(_mm_min_epi32(*a, *b));
        }
        else if constexpr (types::IsByte<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
        {
            return Reg(_mm_min_epi8(*a, *b));
        } // Unsigned types
        else if constexpr (types::IsUDWord<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
        {
            return Reg(_mm_min_epu32(*a, *b));
        }
        else if constexpr (types::IsUWord<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
        {
            return Reg(_mm_min_epu16(*a, *b));
        }
        else // if constexpr(CURRENT_SIMD_BACKEND <= SimdBackend::ARCH_SSE2)
        {
            auto mask = a > b;
            return a.blend(b, mask);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr _REG_128_SSE<DataType, Lane> max(_REG_128_SSE<DataType, Lane> a,
                                                             _REG_128_SSE<DataType, Lane> b) noexcept
    {
        // min function is not available for all data types and for some,
        // it was introduced with SSE4.1
        // As a workaround we use a > b ? a : b
        // with blend to get the correct min values.
        using Reg = _REG_128_SSE<DataType, Lane>;
        if constexpr (types::IsFP64<DataType>)
        {
            return Reg(_mm_max_pd(*a, *b));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            return Reg(_mm_max_ps(*a, *b));
        }
        // Types natively supported by SSE or SSE2(EPI16 and EPU8)
        // This allows us to remove redundant if CURRENT_SIMD_BACKEND conditionals in majority of the code.
        else if constexpr (types::IsWord<DataType>)
        {
            return Reg(_mm_max_epi16(*a, *b));
        }
        else if constexpr (types::IsUByte<DataType>)
        {
            return Reg(_mm_max_epu8(*a, *b));
        }
        else if constexpr (types::IsQWord<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
        {
            return Reg(_mm_max_epi64(*a, *b)); // AVX512F + VL
        }
        else if constexpr (types::IsUQWord<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
        {
            return Reg(_mm_max_epu64(*a, *b)); // AVX512F + VL
        }
        else if constexpr (types::IsDWord<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
        {
            return Reg(_mm_max_epi32(*a, *b));
        }
        else if constexpr (types::IsByte<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
        {
            return Reg(_mm_max_epi8(*a, *b));
        } // Unsigned types
        else if constexpr (types::IsUDWord<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
        {
            return Reg(_mm_max_epu32(*a, *b));
        }
        else if constexpr (types::IsUWord<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
        {
            return Reg(_mm_max_epu16(*a, *b));
        }
        else // if constexpr(CURRENT_SIMD_BACKEND <= SimdBackend::ARCH_SSE2)
        {
            // a > b ? a : b
            auto mask = a > b;
            return b.blend(a, mask);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr _REG_128_SSE<DataType, Lane> abs(_REG_128_SSE<DataType, Lane> reg) noexcept
    { return reg.abs(); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr _REG_128_SSE<DataType, Lane> sqrt(_REG_128_SSE<DataType, Lane> reg) noexcept
    { return reg.sqrt(); }
} // namespace flcn
