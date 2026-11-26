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
    FALCON_INLINE constexpr details::Reg256SSE<DataType, Lane> min(details::Reg256SSE<DataType, Lane> a,
                                                                   details::Reg256SSE<DataType, Lane> b) noexcept
    { return details::Reg256SSE<DataType, Lane>(min(a._lower, b._lower), min(a._upper, b._upper)); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr details::Reg256SSE<DataType, Lane> max(details::Reg256SSE<DataType, Lane> a,
                                                                   details::Reg256SSE<DataType, Lane> b) noexcept
    { return details::Reg256SSE<DataType, Lane>(max(a._lower, b._lower), max(a._upper, b._upper)); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr details::Reg256SSE<DataType, Lane> abs(details::Reg256SSE<DataType, Lane> reg) noexcept
    { return reg.abs(); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr details::Reg256SSE<DataType, Lane> sqrt(details::Reg256SSE<DataType, Lane> reg) noexcept
    { return reg.sqrt(); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr details::Reg256SSE<DataType, Lane> fma(details::Reg256SSE<DataType, Lane> a,
                                                                   details::Reg256SSE<DataType, Lane> b,
                                                                   details::Reg256SSE<DataType, Lane> c) noexcept
    { return a.fma(b, c); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr details::Reg256SSE<DataType, Lane> fmSub(details::Reg256SSE<DataType, Lane> a,
                                                                     details::Reg256SSE<DataType, Lane> b,
                                                                     details::Reg256SSE<DataType, Lane> c) noexcept
    { return a.fmSub(b, c); }


#define _FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType)                                                             \
    (std::floating_point<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX) ||                                \
        CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX2


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr details::Reg256AVX<DataType, Lane> min(details::Reg256AVX<DataType, Lane> a,
                                                                   details::Reg256AVX<DataType, Lane> b) noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                return details::Reg256AVX<DataType, Lane>(_mm256_min_pd(*a, *b));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return details::Reg256AVX<DataType, Lane>(_mm256_min_ps(*a, *b));
            }
            // Signed types
            else if constexpr (types::IsQWord<DataType>)
            {
                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX) // AVX512F + VL
                {
                    return details::Reg256AVX<DataType, Lane>(_mm256_min_epi64(*a, *b));
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
                return details::Reg256AVX<DataType, Lane>(_mm256_min_epi32(*a, *b));
            }
            else if constexpr (types::IsWord<DataType>)
            {
                return details::Reg256AVX<DataType, Lane>(_mm256_min_epi16(*a, *b));
            }
            else if constexpr (types::IsByte<DataType>)
            {
                return details::Reg256AVX<DataType, Lane>(_mm256_min_epi8(*a, *b));
            }
            // Unsigned types
            else if constexpr (types::IsUQWord<DataType>)
            {
                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX) // AVX512F + VL
                {
                    return details::Reg256AVX<DataType, Lane>(_mm256_min_epu64(*a, *b));
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
                return details::Reg256AVX<DataType, Lane>(_mm256_min_epu32(*a, *b));
            }
            else if constexpr (types::IsUWord<DataType>)
            {
                return details::Reg256AVX<DataType, Lane>(_mm256_min_epu16(*a, *b));
            }
            else // if constexpr (types::IsUByte<DataType>)
            {
                return details::Reg256AVX<DataType, Lane>(_mm256_min_epu8(*a, *b));
            }
        }
        else
        {
            // Emulated Register will `set` the correct values so we don't need to assign.
            return details::Reg256AVX<DataType, Lane>(flcn::min(*a, *b));
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr details::Reg256AVX<DataType, Lane> max(details::Reg256AVX<DataType, Lane> a,
                                                                   details::Reg256AVX<DataType, Lane> b) noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                return details::Reg256AVX<DataType, Lane>(_mm256_max_pd(*a, *b));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return details::Reg256AVX<DataType, Lane>(_mm256_max_ps(*a, *b));
            }
            // Signed types
            else if constexpr (types::IsQWord<DataType>)
            {
                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX) // AVX512F + VL
                {
                    return details::Reg256AVX<DataType, Lane>(_mm256_max_epi64(*a, *b));
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
                return details::Reg256AVX<DataType, Lane>(_mm256_max_epi32(*a, *b));
            }
            else if constexpr (types::IsWord<DataType>)
            {
                return details::Reg256AVX<DataType, Lane>(_mm256_max_epi16(*a, *b));
            }
            else if constexpr (types::IsByte<DataType>)
            {
                return details::Reg256AVX<DataType, Lane>(_mm256_max_epi8(*a, *b));
            }
            // Unsigned types
            else if constexpr (types::IsUQWord<DataType>)
            {
                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX) // AVX512F + VL
                {
                    return details::Reg256AVX<DataType, Lane>(_mm256_max_epu64(*a, *b));
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
                return details::Reg256AVX<DataType, Lane>(_mm256_max_epu32(*a, *b));
            }
            else if constexpr (types::IsUWord<DataType>)
            {
                return details::Reg256AVX<DataType, Lane>(_mm256_max_epu16(*a, *b));
            }
            else // if constexpr (types::IsUByte<DataType>)
            {
                return details::Reg256AVX<DataType, Lane>(_mm256_max_epu8(*a, *b));
            }
        }
        else
        {
            // Emulated Register will `set` the correct values so we don't need to assign.
            return details::Reg256AVX<DataType, Lane>(flcn::max(*a, *b));
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr details::Reg256AVX<DataType, Lane> abs(details::Reg256AVX<DataType, Lane> reg) noexcept
    { return reg.abs(); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr details::Reg256AVX<DataType, Lane> sqrt(details::Reg256AVX<DataType, Lane> reg) noexcept
    { return reg.sqrt(); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr details::Reg256AVX<DataType, Lane> fma(details::Reg256AVX<DataType, Lane> a,
                                                                   details::Reg256AVX<DataType, Lane> b,
                                                                   details::Reg256AVX<DataType, Lane> c) noexcept
    { return a.fma(b, c); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr details::Reg256AVX<DataType, Lane> fmSub(details::Reg256AVX<DataType, Lane> a,
                                                                     details::Reg256AVX<DataType, Lane> b,
                                                                     details::Reg256AVX<DataType, Lane> c) noexcept
    { return a.fmSub(b, c); }


#undef _FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC

} // namespace flcn
