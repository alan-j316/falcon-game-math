/**
 * @file PermuteTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 07, 2026
 *
 * @brief Verifies Simd256 shuffling operations.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "SIMDTestSetup.h"

#include <array>
#include <bit>
#include <falcon/simd/FalconSimd.h>

// TODO: Remove Preprocessor after implementing individual simd paths
#if defined(FALCON_ENABLE_AVX512) || defined(FALCON_ENABLE_AVX2) || defined(FALCON_ENABLE_AVX) ||                      \
    defined(FALCON_ENABLE_SSE4) || defined(FALCON_ENABLE_SSE2)


/**
 * @addtogroup T_SIMD256_Permute
 * @{
 */

namespace
{
    using namespace simd::testing;

    // Test param to pass in a combination matrix for testing permute function.
    // since gtest doesn't natively support parameterized typed test(where you can pass in parameters against a type
    // vector)
    // TODO: Update values to use std::numeric_limits::max(from 100 to that)
    template <typename T, size_t Lanes, Array<T, Lanes> Data, Array<T, Lanes> Expected, uint8_t... Indices>
    struct Simd256PermuteTestParam
    {
        using Type                            = T;
        using IndexSequence                   = std::integer_sequence<uint8_t, Indices...>;
        static constexpr size_t REGISTER_SIZE = 256;
        static constexpr size_t LaneCount     = Lanes;
        static constexpr auto data            = Data;
        static constexpr auto expected        = Expected;
        const char* TypeName                  = typeid(Type).name();

        // TODO: Fix pretty function not being used.
        friend std::ostream& operator<<(std::ostream& os, const Simd256PermuteTestParam& param)
        { return os << "Simd256PermuteTestParam(Type=" << param.TypeName << ", Lanes" << param.LaneCount << ")"; }
    };

    // clang-format off
    using Simd256BlendTestTypeHints = testing::Types<
        // Unsigned types
        // <--------- UINT8 --------->
        Simd256PermuteTestParam<
            U8, 32,
            Array<U8, 32>{ { max<U8>, min<U8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
            Array<U8, 32>{ { max<U8>, min<U8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
        >,
        // Within the 128-bit lanes
        Simd256PermuteTestParam<
            U8, 32,
            Array<U8, 32>{ { max<U8>, min<U8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
            Array<U8, 32>{ { 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, min<U8>, max<U8>, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, } },
            15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16
        >,
        // Within the 128-bit lanes with different indices.
        Simd256PermuteTestParam<
            U8, 32,
            Array<U8, 32>{ { max<U8>, min<U8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
            Array<U8, 32>{ { 12, 13, 14, 11, 10, 9, 8, 7, 6, 5, 4, 3, min<U8>, max<U8>, 2, 1, 30, 29, 28, 27, 26, 25, 24, 23, 22, 19, 18, 17, 16, 15, 21, 20 } },
            13, 14, 15, 12, 11, 10, 9, 8, 7, 6, 5, 4, 1, 0, 3, 2, 31, 30, 29, 28, 27, 26, 25, 24, 23, 20, 19, 18, 17, 16, 22, 21
        >,
        Simd256PermuteTestParam<
            U8, 32,
            Array<U8, 32>{ { max<U8>, min<U8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
            Array<U8, 32>{ { max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>,
                               max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8> } },
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        >,
        Simd256PermuteTestParam<
            U8, 32,
            Array<U8, 32>{ { max<U8>, min<U8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
            Array<U8, 32>{ { 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, min<U8>, max<U8> } },
            31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
        >,
        Simd256PermuteTestParam<
            U8, 32,
            Array<U8, 32>{ { max<U8>, min<U8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
            Array<U8, 32>{ { max<U8>, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, min<U8>, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30} },
            0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31
        >,
        Simd256PermuteTestParam<
            U8, 32,
            Array<U8, 32>{ { 75, 112, 14, 33, 53, 85, 114, 99, 5, 89, 93, 70, 93, 14, 38, 110, 102, 35, 95, 95, 28, 87, 82, 20, 63, 1, 124, 103, 39, 22, 20, 44 } },
            Array<U8, 32>{ { 124, 1, 110, 112, 87, 38, 114, 75, 28, 33, 5, 75, 14, 93, 38, 95, 20, 93, 95, 53, 70, 93, 95, 14, 5, 28, 93, 89, 38, 1, 95, 33 } },
            26, 25, 15, 1, 21, 14, 6, 0, 20, 3, 8, 0, 13, 10, 14, 19, 30, 10, 18, 4, 11, 12, 18, 2, 8, 20, 12, 9, 14, 25, 18, 3
        >,
        Simd256PermuteTestParam<
            U8, 32,
            Array<U8, 32>{ { 91, 20, 8, 65, 81, 7, 98, 63, 58, 11, 33, 119, 10, 5, 40, 57, 101, 13, 41, 10, 13, 50, 78, 106, 0, 85, 36, 88, 111, 75, 127, 29 } },
            Array<U8, 32>{ { 10, 40, 13, 10, 98, 29, 11, 5, 20, 13, 13, 101, 33, 85, 33, 13, 98, 57, 13, 20, 5, 0, 63, 20, 29, 106, 13, 63, 85, 41, 10, 81 } },
            12, 14, 20, 19, 6, 31, 9, 13, 1, 17, 17, 16, 10, 25, 10, 17, 6, 15, 17, 1, 13, 24, 7, 1, 31, 23, 17, 7, 25, 18, 12, 4
        >,

        // <--------- UINT16 --------->
        Simd256PermuteTestParam<
            U16, 16,
            Array<U16, 16>{ { max<U16>, min<U16>, 13, 15, 32, 15, 71, 44, max<U16>, min<U16>, 13, 15, 32, 15, 71, 44 } },
            Array<U16, 16>{ { max<U16>, max<U16>, max<U16>, max<U16>, max<U16>, max<U16>, max<U16>, max<U16>,
                                max<U16>, max<U16>, max<U16>, max<U16>, max<U16>, max<U16>, max<U16>, max<U16> } },
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        >,
        // Within the 128-bit lanes
        Simd256PermuteTestParam<
            U16, 16,
            Array<U16, 16>{ { 1, 2, 3, 4, 5, 6, 7, 8, max<U16>, min<U16>, 13, 15, 32, 15, 71, 44 } },
            Array<U16, 16>{ { 8, 7, 6, 5, 4, 3, 2, 1, 44, 71, 15, 32, 15, 13, min<U16>, max<U16>, } },
            7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12, 11, 10, 9, 8
        >,
        // Within the 128-bit lanes but with different indices
        Simd256PermuteTestParam<
            U16, 16,
            Array<U16, 16>{ { 1, 2, 3, 4, 5, 6, 7, 8, max<U16>, min<U16>, 13, 15, 32, 15, 71, 44 } },
            Array<U16, 16>{ { 5, 6, 8, 7, 4, 3, 2, 1, 44, 71, 15, 15, 32, min<U16>, 13, max<U16>, } },
            4, 5, 7, 6, 3, 2, 1, 0, 15, 14, 13, 11, 12, 9, 10, 8
        >,
        Simd256PermuteTestParam<
            U16, 16,
            Array<U16, 16>{ { max<U16>, min<U16>, 13, 15, 32, 15, 71, 44, max<U16>, min<U16>, 13, 15, 32, 15, 71, 44 } },
            Array<U16, 16>{ { 44, 71, 15, 32, 15, 13, min<U16>, max<U16>, 44, 71, 15, 32, 15, 13, min<U16>, max<U16> } },
            15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
        >,
        Simd256PermuteTestParam<
            U16, 16,
            Array<U16, 16>{ { max<U16>, min<U16>, 13, 15, 32, 15, 71, 44, max<U16>, min<U16>, 13, 15, 32, 15, 71, 44 } },
            Array<U16, 16>{ { max<U16>, min<U16>, 13, 15, 32, 15, 71, 44, max<U16>, min<U16>, 13, 15, 32, 15, 71, 44 } },
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
        >,
        Simd256PermuteTestParam<
            U16, 16,
            Array<U16, 16>{ { 118, 47, 19, 39, 121, 70, 105, 13, 14, 24, 34, 4, 87, 99, 57, 11 } },
            Array<U16, 16>{ { 87, 4, 39, 47, 57, 19, 34, 34, 99, 39, 4, 34, 121, 24, 13, 70 } },
            12, 11, 3, 1, 14, 2, 10, 10, 13, 3, 11, 10, 4, 9, 7, 5
        >,
        Simd256PermuteTestParam<
            U16, 16,
            Array<U16, 16>{ { 31, 103, 13, 122, 53, 10, 24, 83, 123, 113, 41, 25, 92, 1, 113, 103 } },
            Array<U16, 16>{ { 122, 31, 123, 113, 113, 103, 103, 113, 103, 24, 103, 92, 92, 1, 92, 10 } },
            3, 0, 8, 9, 14, 1, 15, 14, 15, 6, 1, 12, 12, 13, 12, 5
        >,

        // <--------- UINT32 --------->
        Simd256PermuteTestParam<
            U32, 8,
            Array<U32, 8>{ { max<U32>, min<U32>, 13, 15, 32, 15, 71, 44 } },
            Array<U32, 8>{ { max<U32>, max<U32>, max<U32>, max<U32>, max<U32>, max<U32>, max<U32>, max<U32> } },
            0, 0, 0, 0, 0, 0, 0, 0
        >,
        // Within the 128-bit lanes
        Simd256PermuteTestParam<
            U32, 8,
            Array<U32, 8>{ { max<U32>, min<U32>, 13, 15, 32, 15, 71, 44 } },
            Array<U32, 8>{ { 15, 13, min<U32>, max<U32> , 44, 71, 15, 32 } },
            3, 2, 1, 0, 7, 6, 5, 4
        >,
        // Within the 128-bit lanes but different indices
        Simd256PermuteTestParam<
            U32, 8,
            Array<U32, 8>{ { max<U32>, min<U32>, 13, 15, 32, 15, 71, 44 } },
            Array<U32, 8>{ { 13, 15, min<U32>, max<U32> , 15, 32, 44, 71 } },
            2, 3, 1, 0, 5, 4, 7, 6
        >,
        Simd256PermuteTestParam<
            U32, 8,
            Array<U32, 8>{ { max<U32>, min<U32>, 13, 15, 32, 15, 71, 44 } },
            Array<U32, 8>{ { 44, 44, 44, 44, 44, 44, 44, 44 } },
            7, 7, 7, 7, 7, 7, 7, 7
        >,
        Simd256PermuteTestParam<
            U32, 8,
            Array<U32, 8>{ { max<U32>, min<U32>, 13, 15, 32, 15, 71, 44 } },
            Array<U32, 8>{ { 44, 71, 15, 32, 15, 13, min<U32>, max<U32> } },
            7, 6, 5, 4, 3, 2, 1, 0
        >,
        Simd256PermuteTestParam<
            U32, 8,
            Array<U32, 8>{ { 6, 55, 89, 51, 31, 106, 316, 105 } },
            Array<U32, 8>{ { 55, 106, 316, 55, 55, 6, 316, 106 } },
            1, 5, 6, 1, 1, 0, 6, 5
        >,
        Simd256PermuteTestParam<
            U32, 8,
            Array<U32, 8>{ { 26, 37, 127, 56, 30, 87, 95, 100 } },
            Array<U32, 8>{ { 100, 26, 26, 95, 87, 30, 100, 56 } },
            7, 0, 0, 6, 5, 4, 7, 3
        >,

        // <--------- UINT64 --------->
        Simd256PermuteTestParam<
            U64, 4,
            Array<U64, 4>{ { max<U64>, min<U64>, 13, 15 } },
            Array<U64, 4>{ { max<U64>, max<U64>, max<U64>, max<U64> } },
            0, 0, 0, 0
        >,
        // Within the 128-bit lanes
        Simd256PermuteTestParam<
            U64, 4,
            Array<U64, 4>{ { max<U64>, min<U64>, 13, 15 } },
            Array<U64, 4>{ { min<U64>, max<U64>, 15, 13 } },
            1, 0, 3, 2
        >,
        // Within the 128-bit lanes with different indices
        Simd256PermuteTestParam<
            U64, 4,
            Array<U64, 4>{ { max<U64>, min<U64>, 13, 15 } },
            Array<U64, 4>{ { min<U64>, max<U64>, 13, 15 } },
            1, 0, 2, 3
        >,
        Simd256PermuteTestParam<
            U64, 4,
            Array<U64, 4>{ { max<U64>, min<U64>, 13, 15 } },
            Array<U64, 4>{ { 15, 13, min<U64>, max<U64> } },
            3, 2, 1, 0
        >,
        Simd256PermuteTestParam<
            U64, 4,
            Array<U64, 4>{ { max<U64>, min<U64>, 13, 15 } },
            Array<U64, 4>{ { max<U64>, min<U64>, 13, 15 } },
            0, 1, 2, 3
        >,
        Simd256PermuteTestParam<
            U64, 4,
            Array<U64, 4>{ { 114, 13, 103, 71 } },
            Array<U64, 4>{ { 114, 103, 103, 13 } },
            0, 2, 2, 1
        >,
        Simd256PermuteTestParam<
            U64, 4,
            Array<U64, 4>{ { 31, 120, 12, 88 } },
            Array<U64, 4>{ { 31, 31, 120, 88 } },
            0, 0, 1, 3
        >,


        // Signed types
        // <--------- INT8 --------->
        Simd256PermuteTestParam<
            I8, 32,
            Array<I8, 32>{ { max<I8>, min<I8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
            Array<I8, 32>{ { max<I8>, min<I8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
        >,
        // Within the 128-bit lanes
        Simd256PermuteTestParam<
            I8, 32,
            Array<I8, 32>{ { max<I8>, min<I8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
            Array<I8, 32>{ { 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, min<I8>, max<I8>, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, } },
            15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16
        >,
        // Within the 128-bit lanes with different indices.
        Simd256PermuteTestParam<
            I8, 32,
            Array<I8, 32>{ { max<I8>, min<I8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
            Array<I8, 32>{ { 12, 13, 14, 11, 10, 9, 8, 7, 6, 5, 4, 3, min<I8>, max<I8>, 2, 1, 30, 29, 28, 27, 26, 25, 24, 23, 22, 19, 18, 17, 16, 15, 21, 20 } },
            13, 14, 15, 12, 11, 10, 9, 8, 7, 6, 5, 4, 1, 0, 3, 2, 31, 30, 29, 28, 27, 26, 25, 24, 23, 20, 19, 18, 17, 16, 22, 21
        >,
        Simd256PermuteTestParam<
            I8, 32,
            Array<I8, 32>{ { max<I8>, min<I8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
            Array<I8, 32>{ { max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>,
                               max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8> } },
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        >,
        Simd256PermuteTestParam<
            I8, 32,
            Array<I8, 32>{ { max<I8>, min<I8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
            Array<I8, 32>{ { 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, min<I8>, max<I8> } },
            31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
        >,
        Simd256PermuteTestParam<
            I8, 32,
            Array<I8, 32>{ { max<I8>, min<I8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
            Array<I8, 32>{ { max<I8>, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, min<I8>, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30} },
            0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31
        >,
        Simd256PermuteTestParam<
            I8, 32,
            Array<I8, 32>{ { 75, 112, 14, 33, 53, 85, 114, 99, 5, 89, 93, 70, 93, 14, 38, 110, 102, 35, 95, 95, 28, 87, 82, 20, 63, 1, 124, 103, 39, 22, 20, 44 } },
            Array<I8, 32>{ { 124, 1, 110, 112, 87, 38, 114, 75, 28, 33, 5, 75, 14, 93, 38, 95, 20, 93, 95, 53, 70, 93, 95, 14, 5, 28, 93, 89, 38, 1, 95, 33 } },
            26, 25, 15, 1, 21, 14, 6, 0, 20, 3, 8, 0, 13, 10, 14, 19, 30, 10, 18, 4, 11, 12, 18, 2, 8, 20, 12, 9, 14, 25, 18, 3
        >,
        Simd256PermuteTestParam<
            I8, 32,
            Array<I8, 32>{ { 91, 20, 8, 65, 81, 7, 98, 63, 58, 11, 33, 119, 10, 5, 40, 57, 101, 13, 41, 10, 13, 50, 78, 106, 0, 85, 36, 88, 111, 75, 127, 29 } },
            Array<I8, 32>{ { 10, 40, 13, 10, 98, 29, 11, 5, 20, 13, 13, 101, 33, 85, 33, 13, 98, 57, 13, 20, 5, 0, 63, 20, 29, 106, 13, 63, 85, 41, 10, 81 } },
            12, 14, 20, 19, 6, 31, 9, 13, 1, 17, 17, 16, 10, 25, 10, 17, 6, 15, 17, 1, 13, 24, 7, 1, 31, 23, 17, 7, 25, 18, 12, 4
        >,

        // <--------- INT16 --------->
        Simd256PermuteTestParam<
            I16, 16,
            Array<I16, 16>{ { max<I16>, min<I16>, 13, 15, 32, 15, 71, 44, max<I16>, min<I16>, 13, 15, 32, 15, 71, 44 } },
            Array<I16, 16>{ { max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16> } },
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        >,
        // Within the 128-bit lanes
        Simd256PermuteTestParam<
            I16, 16,
            Array<I16, 16>{ { 1, 2, 3, 4, 5, 6, 7, 8, max<I16>, min<I16>, 13, 15, 32, 15, 71, 44 } },
            Array<I16, 16>{ { 8, 7, 6, 5, 4, 3, 2, 1, 44, 71, 15, 32, 15, 13, min<I16>, max<I16>, } },
            7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12, 11, 10, 9, 8
        >,
        // Within the 128-bit lanes but with different indices
        Simd256PermuteTestParam<
            I16, 16,
            Array<I16, 16>{ { 1, 2, 3, 4, 5, 6, 7, 8, max<I16>, min<I16>, 13, 15, 32, 15, 71, 44 } },
            Array<I16, 16>{ { 5, 6, 8, 7, 4, 3, 2, 1, 44, 71, 15, 15, 32, min<I16>, 13, max<I16>, } },
            4, 5, 7, 6, 3, 2, 1, 0, 15, 14, 13, 11, 12, 9, 10, 8
        >,
        Simd256PermuteTestParam<
            I16, 16,
            Array<I16, 16>{ { max<I16>, min<I16>, 13, 15, 32, 15, 71, 44, max<I16>, min<I16>, 13, 15, 32, 15, 71, 44 } },
            Array<I16, 16>{ { 44, 71, 15, 32, 15, 13, min<I16>, max<I16>, 44, 71, 15, 32, 15, 13, min<I16>, max<I16> } },
            15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
        >,
        Simd256PermuteTestParam<
            I16, 16,
            Array<I16, 16>{ { max<I16>, min<I16>, 13, 15, 32, 15, 71, 44, max<I16>, min<I16>, 13, 15, 32, 15, 71, 44 } },
            Array<I16, 16>{ { max<I16>, min<I16>, 13, 15, 32, 15, 71, 44, max<I16>, min<I16>, 13, 15, 32, 15, 71, 44 } },
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
        >,
        Simd256PermuteTestParam<
            I16, 16,
            Array<I16, 16>{ { 118, 47, 19, 39, 121, 70, 105, 13, 14, 24, 34, 4, 87, 99, 57, 11 } },
            Array<I16, 16>{ { 87, 4, 39, 47, 57, 19, 34, 34, 99, 39, 4, 34, 121, 24, 13, 70 } },
            12, 11, 3, 1, 14, 2, 10, 10, 13, 3, 11, 10, 4, 9, 7, 5
        >,
        Simd256PermuteTestParam<
            I16, 16,
            Array<I16, 16>{ { 31, 103, 13, 122, 53, 10, 24, 83, 123, 113, 41, 25, 92, 1, 113, 103 } },
            Array<I16, 16>{ { 122, 31, 123, 113, 113, 103, 103, 113, 103, 24, 103, 92, 92, 1, 92, 10 } },
            3, 0, 8, 9, 14, 1, 15, 14, 15, 6, 1, 12, 12, 13, 12, 5
        >,

        // <--------- INT32 --------->
        Simd256PermuteTestParam<
            I32, 8,
            Array<I32, 8>{ { max<I32>, min<I32>, 13, 15, 32, 15, 71, 44 } },
            Array<I32, 8>{ { max<I32>, max<I32>, max<I32>, max<I32>, max<I32>, max<I32>, max<I32>, max<I32> } },
            0, 0, 0, 0, 0, 0, 0, 0
        >,
        // Within the 128-bit lanes
        Simd256PermuteTestParam<
            I32, 8,
            Array<I32, 8>{ { max<I32>, min<I32>, 13, 15, 32, 15, 71, 44 } },
            Array<I32, 8>{ { 15, 13, min<I32>, max<I32> , 44, 71, 15, 32 } },
            3, 2, 1, 0, 7, 6, 5, 4
        >,
        // Within the 128-bit lanes but different indices
        Simd256PermuteTestParam<
            I32, 8,
            Array<I32, 8>{ { max<I32>, min<I32>, 13, 15, 32, 15, 71, 44 } },
            Array<I32, 8>{ { 13, 15, min<I32>, max<I32> , 15, 32, 44, 71 } },
            2, 3, 1, 0, 5, 4, 7, 6
        >,
        Simd256PermuteTestParam<
            I32, 8,
            Array<I32, 8>{ { max<I32>, min<I32>, 13, 15, 32, 15, 71, 44 } },
            Array<I32, 8>{ { 44, 44, 44, 44, 44, 44, 44, 44 } },
            7, 7, 7, 7, 7, 7, 7, 7
        >,
        Simd256PermuteTestParam<
            I32, 8,
            Array<I32, 8>{ { max<I32>, min<I32>, 13, 15, 32, 15, 71, 44 } },
            Array<I32, 8>{ { 44, 71, 15, 32, 15, 13, min<I32>, max<I32> } },
            7, 6, 5, 4, 3, 2, 1, 0
        >,
        Simd256PermuteTestParam<
            I32, 8,
            Array<I32, 8>{ { 6, 55, 89, 51, 31, 106, 316, 105 } },
            Array<I32, 8>{ { 55, 106, 316, 55, 55, 6, 316, 106 } },
            1, 5, 6, 1, 1, 0, 6, 5
        >,
        Simd256PermuteTestParam<
            I32, 8,
            Array<I32, 8>{ { 26, 37, 127, 56, 30, 87, 95, 100 } },
            Array<I32, 8>{ { 100, 26, 26, 95, 87, 30, 100, 56 } },
            7, 0, 0, 6, 5, 4, 7, 3
        >,

        // <--------- INT64 --------->
        Simd256PermuteTestParam<
            I64, 4,
            Array<I64, 4>{ { max<I64>, min<I64>, 13, 15 } },
            Array<I64, 4>{ { max<I64>, max<I64>, max<I64>, max<I64> } },
            0, 0, 0, 0
        >,
        // Within the 128-bit lanes
        Simd256PermuteTestParam<
            I64, 4,
            Array<I64, 4>{ { max<I64>, min<I64>, 13, 15 } },
            Array<I64, 4>{ { min<I64>, max<I64>, 15, 13 } },
            1, 0, 3, 2
        >,
        // Within the 128-bit lanes but with different indices
        Simd256PermuteTestParam<
            I64, 4,
            Array<I64, 4>{ { max<I64>, min<I64>, 13, 15 } },
            Array<I64, 4>{ { min<I64>, max<I64>, 13, 15 } },
            1, 0, 2, 3
        >,
        Simd256PermuteTestParam<
            I64, 4,
            Array<I64, 4>{ { max<I64>, min<I64>, 13, 15 } },
            Array<I64, 4>{ { 15, 13, min<I64>, max<I64> } },
            3, 2, 1, 0
        >,
        Simd256PermuteTestParam<
            I64, 4,
            Array<I64, 4>{ { max<I64>, min<I64>, 13, 15 } },
            Array<I64, 4>{ { max<I64>, min<I64>, 13, 15 } },
            0, 1, 2, 3
        >,
        Simd256PermuteTestParam<
            I64, 4,
            Array<I64, 4>{ { 114, 13, 103, 71 } },
            Array<I64, 4>{ { 114, 103, 103, 13 } },
            0, 2, 2, 1
        >,
        Simd256PermuteTestParam<
            I64, 4,
            Array<I64, 4>{ { 31, 120, 12, 88 } },
            Array<I64, 4>{ { 31, 31, 120, 88 } },
            0, 0, 1, 3
        >,


        // Floating point types
        // <--------- FP32 --------->
        Simd256PermuteTestParam<
            FP32, 8,
            Array<FP32, 8>{ { max<FP32>, min<FP32>, 4.12349f, 3.1239f, 5.19234f, 39.12394f, 129.12934f, 0.02343f } },
            Array<FP32, 8>{ { max<FP32>, max<FP32>, max<FP32>, max<FP32>, max<FP32>, max<FP32>, max<FP32>, max<FP32> } },
            0, 0, 0, 0, 0, 0, 0, 0
        >,
        // Within the 128-bit lanes
        Simd256PermuteTestParam<
            FP32, 8,
            Array<FP32, 8>{ { max<FP32>, min<FP32>, 4.12349f, 3.1239f, 5.19234f, 39.12394f, 129.12934f, 0.02343f } },
            Array<FP32, 8>{ { 3.1239f, 4.12349f, min<FP32>, max<FP32>, 0.02343f, 129.12934f, 39.12394f, 5.19234f } },
            3, 2, 1, 0, 7, 6, 5, 4
        >,
        // Within the 128-bit lanes with different indices
        Simd256PermuteTestParam<
            FP32, 8,
            Array<FP32, 8>{ { max<FP32>, min<FP32>, 4.12349f, 3.1239f, 5.19234f, 39.12394f, 129.12934f, 0.02343f } },
            Array<FP32, 8>{ { 4.12349f, 3.1239f, min<FP32>, max<FP32>, 39.12394f, 0.02343f, 129.12934f, 5.19234f } },
            2, 3, 1, 0, 5, 7, 6, 4
        >,
        Simd256PermuteTestParam<
            FP32, 8,
            Array<FP32, 8>{ { max<FP32>, min<FP32>, 4.12349f, 3.1239f, 5.19234f, 39.12394f, 129.12934f, 0.02343f } },
            Array<FP32, 8>{ { 0.02343f, 129.12934f, 39.12394f, 5.19234f, 3.1239f, 4.12349f, min<FP32>, max<FP32> } },
            7, 6, 5, 4, 3, 2, 1, 0
        >,
        Simd256PermuteTestParam<
            FP32, 8,
            Array<FP32, 8>{ { max<FP32>, min<FP32>, 4.12349f, 3.1239f, 5.19234f, 39.12394f, 129.12934f, 0.02343f } },
            Array<FP32, 8>{ { max<FP32>, min<FP32>, 4.12349f, 3.1239f, 5.19234f, 39.12394f, 129.12934f, 0.02343f } },
            0, 1, 2, 3, 4, 5, 6, 7
        >,
        Simd256PermuteTestParam<
            FP32, 8,
            Array<FP32, 8>{ { 6, 55, 89, 51, 31, 106, 316, 105 } },
            Array<FP32, 8>{ { 55, 106, 316, 55, 55, 6, 316, 106 } },
            1, 5, 6, 1, 1, 0, 6, 5
        >,
        Simd256PermuteTestParam<
            FP32, 8,
            Array<FP32, 8>{ { 26, 37, 127, 56, 30, 87, 95, 100 } },
            Array<FP32, 8>{ { 100, 26, 26, 95, 87, 30, 100, 56 } },
            7, 0, 0, 6, 5, 4, 7, 3
        >,

        // <--------- FP64 --------->
        Simd256PermuteTestParam<
            FP64, 4,
            Array<FP64, 4>{ { max<FP64>, min<FP64>, 4.12349, 3.1239 } },
            Array<FP64, 4>{ { max<FP64>, max<FP64>, max<FP64>, max<FP64> } },
            0, 0, 0, 0
        >,
        // Within the 128-bit lanes
        Simd256PermuteTestParam<
            FP64, 4,
            Array<FP64, 4>{ { max<FP64>, min<FP64>, 4.12349, 3.1239 } },
            Array<FP64, 4>{ { min<FP64>, max<FP64>, 3.1239, 4.12349 } },
            1, 0, 3, 2
        >,
        // Within the 128-bit lanes but different indices
        Simd256PermuteTestParam<
            FP64, 4,
            Array<FP64, 4>{ { max<FP64>, min<FP64>, 4.12349, 3.1239 } },
            Array<FP64, 4>{ { min<FP64>, max<FP64>, 4.12349, 3.1239 } },
            1, 0, 2, 3
        >,
        Simd256PermuteTestParam<
            FP64, 4,
            Array<FP64, 4>{ { max<FP64>, min<FP64>, 4.12349, 3.1239 } },
            Array<FP64, 4>{ { 3.1239, 4.12349, min<FP64>, max<FP64> } },
            3, 2, 1, 0
        >,
        Simd256PermuteTestParam<
            FP64, 4,
            Array<FP64, 4>{ { max<FP64>, min<FP64>, 4.12349, 3.1239 } },
            Array<FP64, 4>{ { max<FP64>, min<FP64>, 4.12349, 3.1239 } },
            0, 1, 2, 3
        >,
        Simd256PermuteTestParam<
            FP64, 4,
            Array<FP64, 4>{ { 114, 13, 103, 71 } },
            Array<FP64, 4>{ { 114, 103, 103, 13 } },
            0, 2, 2, 1
        >,
        Simd256PermuteTestParam<
            FP64, 4,
            Array<FP64, 4>{ { 31, 120, 12, 88 } },
            Array<FP64, 4>{ { 31, 31, 120, 88 } },
            0, 0, 1, 3
        >
    >;
    // clang-format on


    /// @brief Test fixture for Simd256 blending operations.
    template <typename>
    class Simd256PermuteTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Simd256PermuteTests, Simd256BlendTestTypeHints);

} // namespace


TYPED_TEST(Simd256PermuteTests, ReturnsRegisterWithCorrectValues)
{
    // Get all the parameters from the types
    using Type                            = TypeParam::Type;
    constexpr size_t Lanes                = TypeParam::LaneCount;
    alignas(32) Array<Type, Lanes> data     = TypeParam::data;
    constexpr Array<Type, Lanes> expected = TypeParam::expected;

    // Create the register and load them
    // Note: While const cast is not recommended in such a situation since the underlying buffer
    //       non-const, we can cast this as internally the load function doesn't mutate the parameters.
    // Since we can't directly access the parameter pack
    // we need to use call it using a lambda nad integer_sequence
    auto execPermute = [data]<uint8_t... I>(std::integer_sequence<uint8_t, I...>) {
        flcn::Simd256_t<Type, Lanes> reg{};
        reg.load(data.data());
        return reg.template permute<I...>();
    };

    // Perform the shuffling
    alignas(32) Array<Type, Lanes> result{};
    auto resultReg = execPermute(typename TypeParam::IndexSequence{});
    resultReg.store(result.data());

    // Compare and assert the result.
    for (size_t i = 0; i < Lanes; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}

/** @} */

#endif
