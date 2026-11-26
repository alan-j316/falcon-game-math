#pragma once
/**
 * @file Simd128.h
 * @author Alan Abraham P Kochumon
 * @date Created on: August 13, 2026
 *
 * @brief Platform and Type agnostic SIMD Registers.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "falcon/simd/utils/SimdTraits.h"

#include <concepts>

/**
 * @addtogroup Falcon_SIMD_128
 * @{
 */

// TODO: Rename File to SIMD core
namespace flcn
{
    template <typename SIMDReg, typename T>
    concept IsSIMDLoadable = requires(SIMDReg reg, T* pBuffer) {
        // { reg.load(buffer) };
        // { reg.store() } -> std::same_as<T*>;
        { SIMDReg(pBuffer) };
    };


    namespace details
    {
        /// Primary Template for Simd128
        template <SimdBackend, typename, size_t>
        struct Simd128; // NOLINT

        /// Primary Template for Simd256
        template <SimdBackend, typename, size_t>
        struct Simd256; // NOLINT

        /// Primary Template for Simd256 Emulated Intrinsic Holder
        /// Each specialization will have a lower and upper 128-bit register.
        template <SimdBackend Backend, typename DataType>
        struct Emulated256; // NOLINT
    } // namespace details

    // static_assert(IsSIMDLoadable<Simd128<float>, float> == true);
} // namespace flcn


#if defined(FALCON_PLATFORM_X86)
    #include "x86/Simd128SSE.h"
    #include "x86/Simd256AVX.h"
    #include "x86/Simd256SSE.h"
// TODO: Separate Neon out
#else
    #include "scalar/Simd128Scalar.h"
#endif


namespace flcn
{
    // Simd128
#if defined(FALCON_PLATFORM_X86)
    template <typename DataType, size_t Lane>
    using Simd128 = details::Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>;
// TODO: Separate Neon OUT
#else
    template <typename DataType, size_t Lane>
    using Simd128 = details::Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>;
#endif

// Simd256
#if defined(FALCON_ENABLE_AVX) || defined(FALCON_ENABLE_AVX2) || defined(FALCON_ENABLE_AVX512F) ||                     \
    defined(FALCON_ENABLE_AVX10) || defined(FALCON_ENABLE_AVX512EX)
    template <typename DataType, size_t Lane>
    using Simd256 = details::Simd256<SimdBackend::ARCH_AVX, DataType, Lane>;
#elif defined(FALCON_PLATFORM_X86)
    template <typename DataType, size_t Lane>
    using Simd256 = details::Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>;
#else
    // TODO: Neon and scalar
#endif
} // namespace flcn

/** @} */
