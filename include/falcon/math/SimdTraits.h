#pragma once


#include <cstddef>
// TODO: To be migrated
namespace math
{

    // Dimension defines the dimension of the vector or matrix using SimdTrait,
    // Eg, for Vec4 it is 4
    template <typename T, std::size_t Dimension>
    struct SimdTraits
    {
        static constexpr std::size_t alignment = sizeof(T);
    };

#ifndef FORCE_NO_SIMD
    #include <emmintrin.h>
    #include <immintrin.h>
    #if defined(__AVX__) || defined(__AVX2__)
        #include <xmmintrin.h>

        #define AVX_SUPPORTED
        #define SIMD_SUPPORTED
    #elif defined(__SSE__) || defined(__SSE4_1__) || defined(_M_X64)
        #define SSE_SUPPORTED
        #define SIMD_SUPPORTED
    #endif

    #ifdef SIMD_SUPPORTED
    template <>
    struct SimdTraits<float, 4>
    {
        static constexpr std::size_t alignment = 16; // 16 bit aligned
        using reg_type                         = __m128;
    };

    template <>
    struct SimdTraits<int, 4>
    {
        static constexpr std::size_t alignment = 16; // 16 bit aligned
        using reg_type                         = __m128i;
    };

    template <>
    struct SimdTraits<double, 4>
    {
        #ifdef AVX_SUPPORTED
        static constexpr std::size_t alignment = 32; // 32 bit aligned
        using reg_type                         = __m256d;
        #else
        static constexpr std::size_t alignment = 16; // 16 bit aligned
        using reg_type                         = __m128d;
        #endif
    };

    template <>
    struct SimdTraits<std::size_t, 4>
    {
        #ifdef AVX_SUPPORTED
        static constexpr std::size_t alignment = 32; // 32 bit aligned
        using reg_type                         = __m256i;
        #else
        static constexpr std::size_t alignment = 16; // 16 bit aligned
        using reg_type                         = __m128i;
        #endif
    };
    #endif
#endif
} // namespace math
