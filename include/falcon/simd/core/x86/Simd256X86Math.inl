#pragma once
/**
 * @file Simd256X86Math.inl
 * @author Alan Abraham P Kochumon
 * @date Created on: September 29, 2026
 *
 * @brief Implementation of function declared in Simd256X86Math.h.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Simd128X86Math.h"

namespace flcn
{
    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr _REG_256_SSE<DataType, Lane> min(_REG_256_SSE<DataType, Lane> a,
                                                             _REG_256_SSE<DataType, Lane> b) noexcept
    { return _REG_256_SSE<DataType, Lane>(min(a._lower, b._lower), min(a._upper, b._upper)); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr _REG_256_SSE<DataType, Lane> max(_REG_256_SSE<DataType, Lane> a,
                                                             _REG_256_SSE<DataType, Lane> b) noexcept
    { return _REG_256_SSE<DataType, Lane>(max(a._lower, b._lower), max(a._upper, b._upper)); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr _REG_256_SSE<DataType, Lane> abs(_REG_256_SSE<DataType, Lane> reg) noexcept
    { return reg.abs(); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr _REG_256_SSE<DataType, Lane> sqrt(_REG_256_SSE<DataType, Lane> reg) noexcept
    { return reg.sqrt(); }


#define _FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType)                                                             \
    (std::floating_point<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX) ||                                \
        CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX2


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr _REG_256_AVX<DataType, Lane> min(_REG_256_AVX<DataType, Lane> a,
                                                             _REG_256_AVX<DataType, Lane> b) noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                return _REG_256_AVX<DataType, Lane>(_mm256_min_pd(*a, *b));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return _REG_256_AVX<DataType, Lane>(_mm256_min_ps(*a, *b));
            }
            // Signed types
            else if constexpr (types::IsQWord<DataType>)
            {
                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX) // AVX512F + VL
                {
                    return _REG_256_AVX<DataType, Lane>(_mm256_min_epi64(*a, *b));
                }
                else
                {
                    // A > B ? B : A
                    const auto mask = a > b;
                    return a.blend(b, mask);
                }
            }
            else if constexpr (types::IsDWord<DataType>)
            {
                return _REG_256_AVX<DataType, Lane>(_mm256_min_epi32(*a, *b));
            }
            else if constexpr (types::IsWord<DataType>)
            {
                return _REG_256_AVX<DataType, Lane>(_mm256_min_epi16(*a, *b));
            }
            else if constexpr (types::IsByte<DataType>)
            {
                return _REG_256_AVX<DataType, Lane>(_mm256_min_epi8(*a, *b));
            }
            // Unsigned types
            else if constexpr (types::IsUQWord<DataType>)
            {
                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX) // AVX512F + VL
                {
                    return _REG_256_AVX<DataType, Lane>(_mm256_min_epu64(*a, *b));
                }
                else
                {
                    // A > B ? B : A
                    const auto mask = a > b;
                    return a.blend(b, mask);
                }
            }
            else if constexpr (types::IsUDWord<DataType>)
            {
                return _REG_256_AVX<DataType, Lane>(_mm256_min_epu32(*a, *b));
            }
            else if constexpr (types::IsUWord<DataType>)
            {
                return _REG_256_AVX<DataType, Lane>(_mm256_min_epu16(*a, *b));
            }
            else // if constexpr (types::IsUByte<DataType>)
            {
                return _REG_256_AVX<DataType, Lane>(_mm256_min_epu8(*a, *b));
            }
        }
        else
        {
            // Emulated Register will `set` the correct values so we don't need to assign.
            return flcn::min(*a, *b);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr _REG_256_AVX<DataType, Lane> max(_REG_256_AVX<DataType, Lane> a,
                                                             _REG_256_AVX<DataType, Lane> b) noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                return _REG_256_AVX<DataType, Lane>(_mm256_max_pd(*a, *b));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return _REG_256_AVX<DataType, Lane>(_mm256_max_ps(*a, *b));
            }
            // Signed types
            else if constexpr (types::IsQWord<DataType>)
            {
                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX) // AVX512F + VL
                {
                    return _REG_256_AVX<DataType, Lane>(_mm256_max_epi64(*a, *b));
                }
                else
                {
                    // A > B ? A : B
                    const auto mask = a > b;
                    return b.blend(a, mask);
                }
            }
            else if constexpr (types::IsDWord<DataType>)
            {
                return _REG_256_AVX<DataType, Lane>(_mm256_max_epi32(*a, *b));
            }
            else if constexpr (types::IsWord<DataType>)
            {
                return _REG_256_AVX<DataType, Lane>(_mm256_max_epi16(*a, *b));
            }
            else if constexpr (types::IsByte<DataType>)
            {
                return _REG_256_AVX<DataType, Lane>(_mm256_max_epi8(*a, *b));
            }
            // Unsigned types
            else if constexpr (types::IsUQWord<DataType>)
            {
                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX) // AVX512F + VL
                {
                    return _REG_256_AVX<DataType, Lane>(_mm256_max_epu64(*a, *b));
                }
                else
                {
                    // A > B ? A : B
                    const auto mask = a > b;
                    return b.blend(a, mask);
                }
            }
            else if constexpr (types::IsUDWord<DataType>)
            {
                return _REG_256_AVX<DataType, Lane>(_mm256_max_epu32(*a, *b));
            }
            else if constexpr (types::IsUWord<DataType>)
            {
                return _REG_256_AVX<DataType, Lane>(_mm256_max_epu16(*a, *b));
            }
            else // if constexpr (types::IsUByte<DataType>)
            {
                return _REG_256_AVX<DataType, Lane>(_mm256_max_epu8(*a, *b));
            }
        }
        else
        {
            // Emulated Register will `set` the correct values so we don't need to assign.
            return flcn::max(*a, *b);
        }
    }


#undef _FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC
} // namespace flcn
