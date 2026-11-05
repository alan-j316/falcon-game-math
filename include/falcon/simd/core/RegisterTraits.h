#pragma once
/**
 * @file RegisterTraits.h
 * @author Alan Abraham P Kochumon
 * @date Created on: August 17, 2026
 *
 * @brief Wrappers for SIMD register instrinsics exposed by C++.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "falcon/simd/utils/SimdTraits.h"

#if defined(FALCON_PLATFORM_X86)
    #include <emmintrin.h>
    #include <immintrin.h>
#elif defined(FALCON_PLATFORM_ARM)
/// TODO: Add header includes
#else
/// TODO: Add header includes
#endif

/**
 * @addtogroup Falcon_Reg
 * @{
 */

/**
 * @brief Defines a SSE(1/2/3/4) Register(128-bit) for a given data type.
 *        @note Use @ref SSERegister_t<type> for a shorter syntax.
 */
namespace flcn
{
    /// Forward Declaration
    template <SimdBackend Backend, typename T, size_t Lane>
    struct Simd256;


    namespace simd::internal
    {
        /**
         * @brief Defines the internal register type of a 256-bit register, given ISA and the data-type.
         *        @note Use @ref AVXRegister_t<type> for a shorter syntax.
         */
        template <SimdBackend, typename, size_t>
        struct Simd256Register;

#if defined(FALCON_PLATFORM_X86)
        // TODO: Update to have a backend type parameter
        template <typename>
        struct Simd128Register
        {
            using Type = __m128i;
        };

        template <>
        struct Simd128Register<float>
        {
            using Type = __m128;
        };

        template <>
        struct Simd128Register<double>
        {
            using Type = __m128d;
        };

        template <typename T>
        using Simd128Register_t = Simd128Register<T>::Type;



        //+=+=+=+=+=+=+=+=+=+=
        //  x86 Architecture
        //+=+=+=+=+=+=+=+=+=+=

        template <SimdBackend Backend, typename T, size_t Lane>
            requires(isX86ISA(Backend))
        struct Simd256Register<Backend, T, Lane>
        {
            using Type = Simd256<SimdBackend::ARCH_SSE2, T, Lane>;
        };

        /// AVX2 Integral Specialization
        template <SimdBackend Backend, typename T, size_t Lane>
            requires(Backend >= SimdBackend::ARCH_AVX2)
        struct Simd256Register<Backend, T, Lane>
        {
            using Type = __m256i;
        };

        /// AVX Floating Point Specialization
        template <SimdBackend Backend, size_t Lane>
            requires(Backend >= SimdBackend::ARCH_AVX)
        struct Simd256Register<Backend, float, Lane>
        {
            using Type = __m256;
        };

        /// AVX Double(FP64) Specialization
        template <SimdBackend Backend, size_t Lane>
            requires(Backend >= SimdBackend::ARCH_AVX)
        struct Simd256Register<Backend, double, Lane>
        {
            using Type = __m256d;
        };

        /// Simd256Register type alias
        template <SimdBackend Backend, typename T, size_t Lane>
        using Simd256Register_t = Simd256Register<Backend, T, Lane>::Type;


        /**
         * @brief Defines an AVX512 Register(512-bit) for a given data type.
         *        @note Use @ref AVX512Register_t<type> for a shorter syntax.
         */
        template <typename>
        struct AVX512Register
        {
            using Type = __m256i;
        };

        template <>
        struct AVX512Register<float>
        {
            using Type = __m256;
        };

        template <>
        struct AVX512Register<double>
        {
            using Type = __m256d;
        };

        template <typename T>
        using AVX512Register_t = AVX512Register<T>::Type;


#elif defined(FALCON_PLATFORM_ARM)
        // TODO: Add Neon Intrinsics here
#endif
    } // namespace simd::internal

} // namespace flcn


/** @} */
