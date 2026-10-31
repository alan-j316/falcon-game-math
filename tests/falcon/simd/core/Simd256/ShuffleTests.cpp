/**
 * @file ShuffleTests.cpp
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
 * @addtogroup T_SIMD256_Shuffle
 * @{
 */

namespace
{
    using namespace simd::testing;

    // Test param to pass in a combination matrix for testing shuffle function.
    // since gtest doesn't natively support parameterized typed test(where you can pass in parameters against a type
    // vector)
    // TODO: Update values to use std::numeric_limits::max(from 100 to that)
    template <typename T, size_t Lanes, Array<T, Lanes> Data, Array<T, Lanes> Expected, uint8_t... Indices>
    struct Simd256ShuffleTestParam
    {
        using Type                            = T;
        using IndexSequence                   = std::integer_sequence<uint8_t, Indices...>;
        static constexpr size_t REGISTER_SIZE = 256;
        static constexpr size_t LaneCount     = Lanes;
        static constexpr auto data            = Data;
        static constexpr auto expected        = Expected;
        const char* TypeName                  = typeid(Type).name();

        // TODO: Fix pretty function not being used.
        friend std::ostream& operator<<(std::ostream& os, const Simd256ShuffleTestParam& param)
        { return os << "Simd256ShuffleTestParam(Type=" << param.TypeName << ", Lanes" << param.LaneCount << ")"; }

        // friend void PrintTo(const Simd256ShuffleTestParam& param, std::ostream* os)
        // { *os << "Simd256ShuffleTestParam(Type=" << param.TypeName << ", Lanes" << param.LaneCount << ")"; }
    };

    // clang-format off
    using Simd256BlendTestTypeHints = testing::Types<
        // Unsigned types
        // Simd256ShuffleTestParam<
        //     U8, 32,
        //     Array<U8, 32>{ { max<U8>, min<U8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
        //     Array<U8, 32>{ { max<U8>, min<U8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
        //     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
        // >,
        // // Within the 128-bit lanes
        // Simd256ShuffleTestParam<
        //     U8, 32,
        //     Array<U8, 32>{ { max<U8>, min<U8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
        //     Array<U8, 32>{ { 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, min<U8>, max<U8>, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, } },
        //     15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 16
        // >,
        // Simd256ShuffleTestParam<
        //     U8, 32,
        //     Array<U8, 32>{ { max<U8>, min<U8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
        //     Array<U8, 32>{ { max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>,
        //                        max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8> } },
        //     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        // >,
        // Simd256ShuffleTestParam<
        //     U8, 32,
        //     Array<U8, 32>{ { max<U8>, min<U8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
        //     Array<U8, 32>{ { 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, min<U8>, max<U8> } },
        //     31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
        // >,
        // Simd256ShuffleTestParam<
        //     U8, 32,
        //     Array<U8, 32>{ { max<U8>, min<U8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
        //     Array<U8, 32>{ { max<U8>, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, min<U8>, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30} },
        //     0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31
        // >,
        // Simd256ShuffleTestParam<
        //     U16, 16,
        //     Array<U16, 16>{ { max<U16>, min<U16>, 13, 15, 32, 15, 71, 44, max<U16>, min<U16>, 13, 15, 32, 15, 71, 44 } },
        //     Array<U16, 16>{ { max<U16>, max<U16>, max<U16>, max<U16>, max<U16>, max<U16>, max<U16>, max<U16>,
        //                         max<U16>, max<U16>, max<U16>, max<U16>, max<U16>, max<U16>, max<U16>, max<U16> } },
        //     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        // >,
        // // Within the 128-bit lanes
        // Simd256ShuffleTestParam<
        //     U16, 16,
        //     Array<U16, 16>{ { 1, 2, 3, 4, 5, 6, 7, 8, max<U16>, min<U16>, 13, 15, 32, 15, 71, 44 } },
        //     Array<U16, 16>{ { 8, 7, 6, 5, 4, 3, 2, 1, 44, 71, 15, 32, 15, 13, min<U16>, max<U16>, } },
        //     7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12, 11, 10, 9, 8
        // >,
        // Simd256ShuffleTestParam<
        //     U16, 16,
        //     Array<U16, 16>{ { max<U16>, min<U16>, 13, 15, 32, 15, 71, 44, max<U16>, min<U16>, 13, 15, 32, 15, 71, 44 } },
        //     Array<U16, 16>{ { 44, 71, 15, 32, 15, 13, min<U16>, max<U16>, 44, 71, 15, 32, 15, 13, min<U16>, max<U16> } },
        //     15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
        // >,
        // Simd256ShuffleTestParam<
        //     U16, 16,
        //     Array<U16, 16>{ { max<U16>, min<U16>, 13, 15, 32, 15, 71, 44, max<U16>, min<U16>, 13, 15, 32, 15, 71, 44 } },
        //     Array<U16, 16>{ { max<U16>, min<U16>, 13, 15, 32, 15, 71, 44, max<U16>, min<U16>, 13, 15, 32, 15, 71, 44 } },
        //     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
        // >,
        Simd256ShuffleTestParam<
            U32, 8,
            Array<U32, 8>{ { max<U32>, min<U32>, 13, 15, 32, 15, 71, 44 } },
            Array<U32, 8>{ { max<U32>, max<U32>, max<U32>, max<U32>, max<U32>, max<U32>, max<U32>, max<U32> } },
            0, 0, 0, 0, 0, 0, 0, 0
        >,
        // Within the 128-bit lanes
        Simd256ShuffleTestParam<
            U32, 8,
            Array<U32, 8>{ { max<U32>, min<U32>, 13, 15, 32, 15, 71, 44 } },
            Array<U32, 8>{ { 15, 13, min<U32>, max<U32> , 44, 71, 15, 32 } },
            3, 2, 1, 0, 7, 6, 5, 4
        >,
        // Within the 128-bit lanes but different indices
        Simd256ShuffleTestParam<
            U32, 8,
            Array<U32, 8>{ { max<U32>, min<U32>, 13, 15, 32, 15, 71, 44 } },
            Array<U32, 8>{ { 15, 13, min<U32>, max<U32> , 15, 32, 44, 71 } },
            3, 2, 1, 0, 5, 4, 7, 6
        >,
        Simd256ShuffleTestParam<
            U32, 8,
            Array<U32, 8>{ { max<U32>, min<U32>, 13, 15, 32, 15, 71, 44 } },
            Array<U32, 8>{ { 44, 44, 44, 44, 44, 44, 44, 44 } },
            7, 7, 7, 7, 7, 7, 7, 7
        >,
        Simd256ShuffleTestParam<
            U32, 8,
            Array<U32, 8>{ { max<U32>, min<U32>, 13, 15, 32, 15, 71, 44 } },
            Array<U32, 8>{ { 44, 71, 15, 32, 15, 13, min<U32>, max<U32> } },
            7, 6, 5, 4, 3, 2, 1, 0
        >,
        Simd256ShuffleTestParam<
            U64, 4,
            Array<U64, 4>{ { max<U64>, min<U64>, 13, 15 } },
            Array<U64, 4>{ { max<U64>, max<U64>, max<U64>, max<U64> } },
            0, 0, 0, 0
        >,
        // Within the 128-bit lanes
        Simd256ShuffleTestParam<
            U64, 4,
            Array<U64, 4>{ { max<U64>, min<U64>, 13, 15 } },
            Array<U64, 4>{ { min<U64>, max<U64>, 15, 13 } },
            1, 0, 3, 2
        >,
        // Within the 128-bit lanes
        Simd256ShuffleTestParam<
            U64, 4,
            Array<U64, 4>{ { max<U64>, min<U64>, 13, 15 } },
            Array<U64, 4>{ { min<U64>, max<U64>, 13, 15 } },
            1, 0, 2, 3
        >,
        Simd256ShuffleTestParam<
            U64, 4,
            Array<U64, 4>{ { max<U64>, min<U64>, 13, 15 } },
            Array<U64, 4>{ { 15, 13, min<U64>, max<U64> } },
            3, 2, 1, 0
        >,
        Simd256ShuffleTestParam<
            U64, 4,
            Array<U64, 4>{ { max<U64>, min<U64>, 13, 15 } },
            Array<U64, 4>{ { max<U64>, min<U64>, 13, 15 } },
            0, 1, 2, 3
        >,

        // // Signed types
        // Simd256ShuffleTestParam<
        //     I8, 32,
        //     Array<I8, 32>{ { max<I8>, min<I8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
        //     Array<I8, 32>{ { max<I8>, min<I8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
        //     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
        // >,
        // // Within the 128-bit lanes
        // Simd256ShuffleTestParam<
        //     I8, 32,
        //     Array<I8, 32>{ { max<I8>, min<I8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
        //     Array<I8, 32>{ { 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, min<I8>, max<I8>, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, } },
        //     15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 16
        // >,
        // Simd256ShuffleTestParam<
        //     I8, 32,
        //     Array<I8, 32>{ { max<I8>, min<I8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
        //     Array<I8, 32>{ { max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>,
        //                        max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8> } },
        //     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        // >,
        // Simd256ShuffleTestParam<
        //     I8, 32,
        //     Array<I8, 32>{ { max<I8>, min<I8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
        //     Array<I8, 32>{ { 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, min<I8>, max<I8> } },
        //     31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
        // >,
        // Simd256ShuffleTestParam<
        //     I8, 32,
        //     Array<I8, 32>{ { max<I8>, min<I8>, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 } },
        //     Array<I8, 32>{ { max<I8>, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, min<I8>, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30 } },
        //     0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31
        // >,
        // Simd256ShuffleTestParam<
        //     I16, 16,
        //     Array<I16, 16>{ { max<I16>, min<I16>, 13, 15, 32, 15, 71, 44, max<I16>, min<I16>, 13, 15, 32, 15, 71, 44 } },
        //     Array<I16, 16>{ { max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16> } },
        //     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        // >,
        // // Within the 128-bit lanes
        // Simd256ShuffleTestParam<
        //     I16, 16,
        //     Array<I16, 16>{ { 1, 2, 3, 4, 5, 6, 7, 8, max<I16>, min<I16>, 13, 15, 32, 15, 71, 44 } },
        //     Array<I16, 16>{ { 8, 7, 6, 5, 4, 3, 2, 1, 44, 71, 15, 32, 15, 13, min<I16>, max<I16>, } },
        //     7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12, 11, 10, 9, 8
        // >,
        // Simd256ShuffleTestParam<
        //     I16, 16,
        //     Array<I16, 16>{ { max<I16>, min<I16>, 13, 15, 32, 15, 71, 44, max<I16>, min<I16>, 13, 15, 32, 15, 71, 44 } },
        //     Array<I16, 16>{ { 44, 71, 15, 32, 15, 13, min<I16>, max<I16>, 44, 71, 15, 32, 15, 13, min<I16>, max<I16> } },
        //     15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
        // >,
        // Simd256ShuffleTestParam<
        //     I16, 16,
        //     Array<I16, 16>{ { max<I16>, min<I16>, 13, 15, 32, 15, 71, 44, max<I16>, min<I16>, 13, 15, 32, 15, 71, 44 } },
        //     Array<I16, 16>{ { max<I16>, min<I16>, 13, 15, 32, 15, 71, 44, max<I16>, min<I16>, 13, 15, 32, 15, 71, 44 } },
        //     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
        // >,
        Simd256ShuffleTestParam<
            I32, 8,
            Array<I32, 8>{ { max<I32>, min<I32>, 13, 15, 32, 15, 71, 44 } },
            Array<I32, 8>{ { max<I32>, max<I32>, max<I32>, max<I32>, max<I32>, max<I32>, max<I32>, max<I32> } },
            0, 0, 0, 0, 0, 0, 0, 0
        >,
        // Within the 128-bit lanes
        Simd256ShuffleTestParam<
            I32, 8,
            Array<I32, 8>{ { max<I32>, min<I32>, 13, 15, 32, 15, 71, 44 } },
            Array<I32, 8>{ { 15, 13, min<I32>, max<I32> , 44, 71, 15, 32 } },
            3, 2, 1, 0, 7, 6, 5, 4
        >,
        // Within the 128-bit lanes but different indices
        Simd256ShuffleTestParam<
            I32, 8,
            Array<I32, 8>{ { max<I32>, min<I32>, 13, 15, 32, 15, 71, 44 } },
            Array<I32, 8>{ { 15, 13, min<I32>, max<I32> , 15, 32, 44, 71 } },
            3, 2, 1, 0, 5, 4, 7, 6
        >,
        Simd256ShuffleTestParam<
            I32, 8,
            Array<I32, 8>{ { max<I32>, min<I32>, 13, 15, 32, 15, 71, 44 } },
            Array<I32, 8>{ { 44, 44, 44, 44, 44, 44, 44, 44 } },
            7, 7, 7, 7, 7, 7, 7, 7
        >,
        Simd256ShuffleTestParam<
            I32, 8,
            Array<I32, 8>{ { max<I32>, min<I32>, 13, 15, 32, 15, 71, 44 } },
            Array<I32, 8>{ { 44, 71, 15, 32, 15, 13, min<I32>, max<I32> } },
            7, 6, 5, 4, 3, 2, 1, 0
        >,
        Simd256ShuffleTestParam<
            I64, 4,
            Array<I64, 4>{ { max<I64>, min<I64>, 13, 15 } },
            Array<I64, 4>{ { max<I64>, max<I64>, max<I64>, max<I64> } },
            0, 0, 0, 0
        >,
        // Within the 128-bit lanes
        Simd256ShuffleTestParam<
            I64, 4,
            Array<I64, 4>{ { max<I64>, min<I64>, 13, 15 } },
            Array<I64, 4>{ { min<I64>, max<I64>, 15, 13 } },
            1, 0, 3, 2
        >,
        // Within the 128-bit lanes but with different indices
        Simd256ShuffleTestParam<
            I64, 4,
            Array<I64, 4>{ { max<I64>, min<I64>, 13, 15 } },
            Array<I64, 4>{ { min<I64>, max<I64>, 13, 15 } },
            1, 0, 2, 3
        >,
        Simd256ShuffleTestParam<
            I64, 4,
            Array<I64, 4>{ { max<I64>, min<I64>, 13, 15 } },
            Array<I64, 4>{ { 15, 13, min<I64>, max<I64> } },
            3, 2, 1, 0
        >,
        Simd256ShuffleTestParam<
            I64, 4,
            Array<I64, 4>{ { max<I64>, min<I64>, 13, 15 } },
            Array<I64, 4>{ { max<I64>, min<I64>, 13, 15 } },
            0, 1, 2, 3
        >,

        // Floating point types
        Simd256ShuffleTestParam<
            FP32, 8,
            Array<FP32, 8>{ { max<FP32>, min<FP32>, 4.12349f, 3.1239f, 5.19234f, 39.12394f, 129.12934f, 0.02343f } },
            Array<FP32, 8>{ { max<FP32>, max<FP32>, max<FP32>, max<FP32>, max<FP32>, max<FP32>, max<FP32>, max<FP32> } },
            0, 0, 0, 0, 0, 0, 0, 0
        >,
        // Within the 128-bit lanes
        Simd256ShuffleTestParam<
            FP32, 8,
            Array<FP32, 8>{ { max<FP32>, min<FP32>, 4.12349f, 3.1239f, 5.19234f, 39.12394f, 129.12934f, 0.02343f } },
            Array<FP32, 8>{ { 3.1239f, 4.12349f, min<FP32>, max<FP32>, 0.02343f, 129.12934f, 39.12394f, 5.19234f } },
            3, 2, 1, 0, 7, 6, 5, 4
        >,
        // Within the 128-bit lanes with different indices
        Simd256ShuffleTestParam<
            FP32, 8,
            Array<FP32, 8>{ { max<FP32>, min<FP32>, 4.12349f, 3.1239f, 5.19234f, 39.12394f, 129.12934f, 0.02343f } },
            Array<FP32, 8>{ { 3.1239f, 4.12349f, min<FP32>, max<FP32>, 39.12394f, 0.02343f, 129.12934f, 5.19234f } },
            3, 2, 1, 0, 5, 7, 6, 4
        >,
        Simd256ShuffleTestParam<
            FP32, 8,
            Array<FP32, 8>{ { max<FP32>, min<FP32>, 4.12349f, 3.1239f, 5.19234f, 39.12394f, 129.12934f, 0.02343f } },
            Array<FP32, 8>{ { 0.02343f, 129.12934f, 39.12394f, 5.19234f, 3.1239f, 4.12349f, min<FP32>, max<FP32> } },
            7, 6, 5, 4, 3, 2, 1, 0
        >,
        Simd256ShuffleTestParam<
            FP32, 8,
            Array<FP32, 8>{ { max<FP32>, min<FP32>, 4.12349f, 3.1239f, 5.19234f, 39.12394f, 129.12934f, 0.02343f } },
            Array<FP32, 8>{ { max<FP32>, min<FP32>, 4.12349f, 3.1239f, 5.19234f, 39.12394f, 129.12934f, 0.02343f } },
            0, 1, 2, 3, 4, 5, 6, 7
        >,
        Simd256ShuffleTestParam<
            FP64, 4,
            Array<FP64, 4>{ { max<FP64>, min<FP64>, 4.12349, 3.1239 } },
            Array<FP64, 4>{ { max<FP64>, max<FP64>, max<FP64>, max<FP64> } },
            0, 0, 0, 0
        >,
        // Within the 128-bit lanes
        Simd256ShuffleTestParam<
            FP64, 4,
            Array<FP64, 4>{ { max<FP64>, min<FP64>, 4.12349, 3.1239 } },
            Array<FP64, 4>{ { min<FP64>, max<FP64>, 3.1239, 4.12349 } },
            1, 0, 3, 2
        >,
        // Within the 128-bit lanes but different indices
        Simd256ShuffleTestParam<
            FP64, 4,
            Array<FP64, 4>{ { max<FP64>, min<FP64>, 4.12349, 3.1239 } },
            Array<FP64, 4>{ { min<FP64>, max<FP64>, 4.12349, 3.1239 } },
            1, 0, 2, 3
        >,
        Simd256ShuffleTestParam<
            FP64, 4,
            Array<FP64, 4>{ { max<FP64>, min<FP64>, 4.12349, 3.1239 } },
            Array<FP64, 4>{ { 3.1239, 4.12349, min<FP64>, max<FP64> } },
            3, 2, 1, 0
        >,
        Simd256ShuffleTestParam<
            FP64, 4,
            Array<FP64, 4>{ { max<FP64>, min<FP64>, 4.12349, 3.1239 } },
            Array<FP64, 4>{ { max<FP64>, min<FP64>, 4.12349, 3.1239 } },
            0, 1, 2, 3
        >
    >;
    // clang-format on


    /// @brief Test fixture for Simd256 blending operations.
    template <typename>
    class Simd256ShuffleTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Simd256ShuffleTests, Simd256BlendTestTypeHints);

} // namespace


TYPED_TEST(Simd256ShuffleTests, ReturnsRegisterWithCorrectValues)
{
    // Get all the parameters from the types
    using Type                            = TypeParam::Type;
    constexpr size_t Lanes                = TypeParam::LaneCount;
    constexpr Array<Type, Lanes> data     = TypeParam::data;
    constexpr Array<Type, Lanes> expected = TypeParam::expected;

    // Create the register and load them
    // Note: While const cast is not recommended in such a situation since the underlying buffer
    //       non-const, we can cast this as internally the load function doesn't mutate the parameters.
    // Since we can't directly access the parameter pack
    // we need to use call it using a lambda nad integer_sequence
    auto execShuffle = [data]<uint8_t... I>(std::integer_sequence<uint8_t, I...>) {
        flcn::Simd256_t<Type, Lanes> reg{};
        reg.load(const_cast<Type*>(data.data()));
        return reg.template shuffle<I...>();
    };

    // Perform the shuffling
    Array<Type, Lanes> result{};
    auto resultReg = execShuffle(typename TypeParam::IndexSequence{});
    resultReg.store(result.data());

    // Compare and assert the result.
    for (size_t i = 0; i < Lanes; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}

/** @} */

#endif
