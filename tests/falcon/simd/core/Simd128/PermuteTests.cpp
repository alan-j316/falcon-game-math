/**
 * @file PermuteTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 07, 2026
 *
 * @brief Verifies Simd128 shuffling operations.
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
 * @addtogroup T_SIMD128_Permute
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
    struct Simd128PermuteTestParam
    {
        using Type                            = T;
        using IndexSequence                   = std::integer_sequence<uint8_t, Indices...>;
        static constexpr size_t REGISTER_SIZE = 128;
        static constexpr size_t LaneCount     = Lanes;
        static constexpr auto data            = Data;
        static constexpr auto expected        = Expected;
        const char* TypeName                  = typeid(Type).name();

        // TODO: Fix pretty function not being used.
        friend std::ostream& operator<<(std::ostream& os, const Simd128PermuteTestParam& param)
        { return os << "Simd128PermuteTestParam(Type=" << param.TypeName << ", Lanes" << param.LaneCount << ")"; }

        // friend void PrintTo(const Simd128PermuteTestParam& param, std::ostream* os)
        // { *os << "Simd128PermuteTestParam(Type=" << param.TypeName << ", Lanes" << param.LaneCount << ")"; }
    };


    using Simd128BlendTestTypeHints = testing::Types<
        // Unsigned types
        Simd128PermuteTestParam<U8, 2, Array<U8, 2>{ { max<U8>, min<U8> } }, Array<U8, 2>{ { max<U8>, max<U8> } }, 0,
                                0>,
        Simd128PermuteTestParam<U8, 2, Array<U8, 2>{ { max<U8>, min<U8> } }, Array<U8, 2>{ { min<U8>, max<U8> } }, 1,
                                0>,
        Simd128PermuteTestParam<U8, 2, Array<U8, 2>{ { max<U8>, min<U8> } }, Array<U8, 2>{ { max<U8>, min<U8> } }, 0,
                                1>,
        Simd128PermuteTestParam<U8, 4, Array<U8, 4>{ { max<U8>, min<U8>, 13, 15 } },
                                Array<U8, 4>{ { max<U8>, max<U8>, max<U8>, max<U8> } }, 0, 0, 0, 0>,
        Simd128PermuteTestParam<U8, 4, Array<U8, 4>{ { max<U8>, min<U8>, 13, 15 } },
                                Array<U8, 4>{ { 15, 13, min<U8>, max<U8> } }, 3, 2, 1, 0>,
        Simd128PermuteTestParam<U8, 4, Array<U8, 4>{ { max<U8>, min<U8>, 13, 15 } },
                                Array<U8, 4>{ { max<U8>, min<U8>, 13, 15 } }, 0, 1, 2, 3>,
        Simd128PermuteTestParam<U8, 8, Array<U8, 8>{ { max<U8>, min<U8>, 13, 15, 32, 15, 71, 44 } },
                                Array<U8, 8>{
                                    { max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8> } },
                                0, 0, 0, 0, 0, 0, 0, 0>,
        Simd128PermuteTestParam<U8, 8, Array<U8, 8>{ { max<U8>, min<U8>, 13, 15, 32, 15, 71, 44 } },
                                Array<U8, 8>{ { 44, 71, 15, 32, 15, 13, min<U8>, max<U8> } }, 7, 6, 5, 4, 3, 2, 1, 0>,
        Simd128PermuteTestParam<U8, 8, Array<U8, 8>{ { max<U8>, min<U8>, 13, 15, 32, 15, 71, 44 } },
                                Array<U8, 8>{ { max<U8>, min<U8>, 13, 15, 32, 15, 71, 44 } }, 0, 1, 2, 3, 4, 5, 6, 7>,
        Simd128PermuteTestParam<
            U8, 16,
            Array<U8, 16>{ { max<U8>, min<U8>, 13, 15, 32, 15, 71, 44, max<U8>, min<U8>, 13, 15, 32, 15, 71, 44 } },
            Array<U8, 16>{ { max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8>,
                             max<U8>, max<U8>, max<U8>, max<U8>, max<U8>, max<U8> } },
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0>,
        Simd128PermuteTestParam<
            U8, 16,
            Array<U8, 16>{ { max<U8>, min<U8>, 13, 15, 32, 15, 71, 44, max<U8>, min<U8>, 13, 15, 32, 15, 71, 44 } },
            Array<U8, 16>{ { 44, 71, 15, 32, 15, 13, min<U8>, max<U8>, 44, 71, 15, 32, 15, 13, min<U8>, max<U8> } }, 15,
            14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0>,
        Simd128PermuteTestParam<
            U8, 16,
            Array<U8, 16>{ { max<U8>, min<U8>, 13, 15, 32, 15, 71, 44, max<U8>, min<U8>, 13, 15, 32, 15, 71, 44 } },
            Array<U8, 16>{ { max<U8>, min<U8>, 13, 15, 32, 15, 71, 44, max<U8>, min<U8>, 13, 15, 32, 15, 71, 44 } }, 0,
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15>,

        Simd128PermuteTestParam<U16, 2, Array<U16, 2>{ { max<U16>, min<U16> } },
                                Array<U16, 2>{ { max<U16>, max<U16> } }, 0, 0>,
        Simd128PermuteTestParam<U16, 2, Array<U16, 2>{ { max<U16>, min<U16> } },
                                Array<U16, 2>{ { min<U16>, max<U16> } }, 1, 0>,
        Simd128PermuteTestParam<U16, 2, Array<U16, 2>{ { max<U16>, min<U16> } },
                                Array<U16, 2>{ { max<U16>, min<U16> } }, 0, 1>,

        Simd128PermuteTestParam<U16, 4, Array<U16, 4>{ { max<U16>, min<U16>, 13, 15 } },
                                Array<U16, 4>{ { max<U16>, max<U16>, max<U16>, max<U16> } }, 0, 0, 0, 0>,
        Simd128PermuteTestParam<U16, 4, Array<U16, 4>{ { max<U16>, min<U16>, 13, 15 } },
                                Array<U16, 4>{ { 15, 13, min<U16>, max<U16> } }, 3, 2, 1, 0>,
        Simd128PermuteTestParam<U16, 4, Array<U16, 4>{ { max<U16>, min<U16>, 13, 15 } },
                                Array<U16, 4>{ { max<U16>, min<U16>, 13, 15 } }, 0, 1, 2, 3>,

        Simd128PermuteTestParam<U16, 8, Array<U16, 8>{ { max<U16>, min<U16>, 13, 15, 32, 15, 71, 44 } },
                                Array<U16, 8>{ { max<U16>, max<U16>, max<U16>, max<U16>, max<U16>, max<U16>, max<U16>,
                                                 max<U16> } },
                                0, 0, 0, 0, 0, 0, 0, 0>,
        Simd128PermuteTestParam<U16, 8, Array<U16, 8>{ { max<U16>, min<U16>, 13, 15, 32, 15, 71, 44 } },
                                Array<U16, 8>{ { 44, 44, 44, 44, 44, 44, 44, 44 } }, 7, 7, 7, 7, 7, 7, 7, 7>,

        Simd128PermuteTestParam<U16, 8, Array<U16, 8>{ { max<U16>, min<U16>, 13, 15, 32, 15, 71, 44 } },
                                Array<U16, 8>{ { 44, 71, 15, 32, 15, 13, min<U16>, max<U16> } }, 7, 6, 5, 4, 3, 2, 1,
                                0>,

        Simd128PermuteTestParam<U16, 8, Array<U16, 8>{ { max<U16>, min<U16>, 13, 15, 32, 15, 71, 44 } },
                                Array<U16, 8>{ { max<U16>, min<U16>, 13, 15, 32, 15, 71, 44 } }, 0, 1, 2, 3, 4, 5, 6,
                                7>,
        Simd128PermuteTestParam<U32, 2, Array<U32, 2>{ { max<U32>, min<U32> } },
                                Array<U32, 2>{ { max<U32>, max<U32> } }, 0, 0>,
        Simd128PermuteTestParam<U32, 2, Array<U32, 2>{ { max<U32>, min<U32> } },
                                Array<U32, 2>{ { min<U32>, max<U32> } }, 1, 0>,
        Simd128PermuteTestParam<U32, 2, Array<U32, 2>{ { max<U32>, min<U32> } },
                                Array<U32, 2>{ { max<U32>, min<U32> } }, 0, 1>,
        Simd128PermuteTestParam<U32, 4, Array<U32, 4>{ { max<U32>, min<U32>, 13, 15 } },
                                Array<U32, 4>{ { max<U32>, max<U32>, max<U32>, max<U32> } }, 0, 0, 0, 0>,
        Simd128PermuteTestParam<U32, 4, Array<U32, 4>{ { max<U32>, min<U32>, 13, 15 } },
                                Array<U32, 4>{ { 15, 13, min<U32>, max<U32> } }, 3, 2, 1, 0>,
        Simd128PermuteTestParam<U32, 4, Array<U32, 4>{ { max<U32>, min<U32>, 13, 15 } },
                                Array<U32, 4>{ { max<U32>, min<U32>, 13, 15 } }, 0, 1, 2, 3>,

        Simd128PermuteTestParam<U64, 2, Array<U64, 2>{ { max<U64>, min<U64> } },
                                Array<U64, 2>{ { max<U64>, max<U64> } }, 0, 0>,
        Simd128PermuteTestParam<U64, 2, Array<U64, 2>{ { max<U64>, min<U64> } },
                                Array<U64, 2>{ { min<U64>, max<U64> } }, 1, 0>,
        Simd128PermuteTestParam<U64, 2, Array<U64, 2>{ { max<U64>, min<U64> } },
                                Array<U64, 2>{ { max<U64>, min<U64> } }, 0, 1>,

        // Signed types
        Simd128PermuteTestParam<I8, 2, Array<I8, 2>{ { max<I8>, min<I8> } }, Array<I8, 2>{ { max<I8>, max<I8> } }, 0,
                                0>,
        Simd128PermuteTestParam<I8, 2, Array<I8, 2>{ { max<I8>, min<I8> } }, Array<I8, 2>{ { min<I8>, max<I8> } }, 1,
                                0>,
        Simd128PermuteTestParam<I8, 2, Array<I8, 2>{ { max<I8>, min<I8> } }, Array<I8, 2>{ { max<I8>, min<I8> } }, 0,
                                1>,
        Simd128PermuteTestParam<I8, 4, Array<I8, 4>{ { max<I8>, min<I8>, 13, 15 } },
                                Array<I8, 4>{ { max<I8>, max<I8>, max<I8>, max<I8> } }, 0, 0, 0, 0>,
        Simd128PermuteTestParam<I8, 4, Array<I8, 4>{ { max<I8>, min<I8>, 13, 15 } },
                                Array<I8, 4>{ { 15, 13, min<I8>, max<I8> } }, 3, 2, 1, 0>,
        Simd128PermuteTestParam<I8, 4, Array<I8, 4>{ { max<I8>, min<I8>, 13, 15 } },
                                Array<I8, 4>{ { max<I8>, min<I8>, 13, 15 } }, 0, 1, 2, 3>,
        Simd128PermuteTestParam<I8, 8, Array<I8, 8>{ { max<I8>, min<I8>, 13, 15, 32, 15, 71, 44 } },
                                Array<I8, 8>{
                                    { max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8> } },
                                0, 0, 0, 0, 0, 0, 0, 0>,
        Simd128PermuteTestParam<I8, 8, Array<I8, 8>{ { max<I8>, min<I8>, 13, 15, 32, 15, 71, 44 } },
                                Array<I8, 8>{ { 44, 71, 15, 32, 15, 13, min<I8>, max<I8> } }, 7, 6, 5, 4, 3, 2, 1, 0>,
        Simd128PermuteTestParam<I8, 8, Array<I8, 8>{ { max<I8>, min<I8>, 13, 15, 32, 15, 71, 44 } },
                                Array<I8, 8>{ { max<I8>, min<I8>, 13, 15, 32, 15, 71, 44 } }, 0, 1, 2, 3, 4, 5, 6, 7>,
        Simd128PermuteTestParam<
            I8, 16,
            Array<I8, 16>{ { max<I8>, min<I8>, 13, 15, 32, 15, 71, 44, max<I8>, min<I8>, 13, 15, 32, 15, 71, 44 } },
            Array<I8, 16>{ { max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8>,
                             max<I8>, max<I8>, max<I8>, max<I8>, max<I8>, max<I8> } },
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0>,
        Simd128PermuteTestParam<
            I8, 16,
            Array<I8, 16>{ { max<I8>, min<I8>, 13, 15, 32, 15, 71, 44, max<I8>, min<I8>, 13, 15, 32, 15, 71, 44 } },
            Array<I8, 16>{ { 44, 71, 15, 32, 15, 13, min<I8>, max<I8>, 44, 71, 15, 32, 15, 13, min<I8>, max<I8> } }, 15,
            14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0>,
        Simd128PermuteTestParam<
            I8, 16,
            Array<I8, 16>{ { max<I8>, min<I8>, 13, 15, 32, 15, 71, 44, max<I8>, min<I8>, 13, 15, 32, 15, 71, 44 } },
            Array<I8, 16>{ { max<I8>, min<I8>, 13, 15, 32, 15, 71, 44, max<I8>, min<I8>, 13, 15, 32, 15, 71, 44 } }, 0,
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15>,

        Simd128PermuteTestParam<I16, 2, Array<I16, 2>{ { max<I16>, min<I16> } },
                                Array<I16, 2>{ { max<I16>, max<I16> } }, 0, 0>,
        Simd128PermuteTestParam<I16, 2, Array<I16, 2>{ { max<I16>, min<I16> } },
                                Array<I16, 2>{ { min<I16>, max<I16> } }, 1, 0>,
        Simd128PermuteTestParam<I16, 2, Array<I16, 2>{ { max<I16>, min<I16> } },
                                Array<I16, 2>{ { max<I16>, min<I16> } }, 0, 1>,
        Simd128PermuteTestParam<I16, 4, Array<I16, 4>{ { max<I16>, min<I16>, 13, 15 } },
                                Array<I16, 4>{ { max<I16>, max<I16>, max<I16>, max<I16> } }, 0, 0, 0, 0>,
        Simd128PermuteTestParam<I16, 4, Array<I16, 4>{ { max<I16>, min<I16>, 13, 15 } },
                                Array<I16, 4>{ { 15, 13, min<I16>, max<I16> } }, 3, 2, 1, 0>,
        Simd128PermuteTestParam<I16, 4, Array<I16, 4>{ { max<I16>, min<I16>, 13, 15 } },
                                Array<I16, 4>{ { max<I16>, min<I16>, 13, 15 } }, 0, 1, 2, 3>,
        Simd128PermuteTestParam<I16, 8, Array<I16, 8>{ { max<I16>, min<I16>, 13, 15, 32, 15, 71, 44 } },
                                Array<I16, 8>{ { max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16>, max<I16>,
                                                 max<I16> } },
                                0, 0, 0, 0, 0, 0, 0, 0>,
        Simd128PermuteTestParam<I16, 8, Array<I16, 8>{ { max<I16>, min<I16>, 13, 15, 32, 15, 71, 44 } },
                                Array<I16, 8>{ { 44, 71, 15, 32, 15, 13, min<I16>, max<I16> } }, 7, 6, 5, 4, 3, 2, 1,
                                0>,
        Simd128PermuteTestParam<I16, 8, Array<I16, 8>{ { max<I16>, min<I16>, 13, 15, 32, 15, 71, 44 } },
                                Array<I16, 8>{ { max<I16>, min<I16>, 13, 15, 32, 15, 71, 44 } }, 0, 1, 2, 3, 4, 5, 6,
                                7>,
        Simd128PermuteTestParam<I16, 8, Array<I16, 8>{ { max<I16>, min<I16>, 13, 15, 32, 15, 71, 44 } },
                                Array<I16, 8>{ { 44, 44, 44, 44, 44, 44, 44, 44 } }, 7, 7, 7, 7, 7, 7, 7, 7>,

        Simd128PermuteTestParam<I32, 2, Array<I32, 2>{ { max<I32>, min<I32> } },
                                Array<I32, 2>{ { max<I32>, max<I32> } }, 0, 0>,
        Simd128PermuteTestParam<I32, 2, Array<I32, 2>{ { max<I32>, min<I32> } },
                                Array<I32, 2>{ { min<I32>, max<I32> } }, 1, 0>,
        Simd128PermuteTestParam<I32, 2, Array<I32, 2>{ { max<I32>, min<I32> } },
                                Array<I32, 2>{ { max<I32>, min<I32> } }, 0, 1>,
        Simd128PermuteTestParam<I32, 4, Array<I32, 4>{ { max<I32>, min<I32>, 13, 15 } },
                                Array<I32, 4>{ { max<I32>, max<I32>, max<I32>, max<I32> } }, 0, 0, 0, 0>,
        Simd128PermuteTestParam<I32, 4, Array<I32, 4>{ { max<I32>, min<I32>, 13, 15 } },
                                Array<I32, 4>{ { 15, 13, min<I32>, max<I32> } }, 3, 2, 1, 0>,
        Simd128PermuteTestParam<I32, 4, Array<I32, 4>{ { max<I32>, min<I32>, 13, 15 } },
                                Array<I32, 4>{ { max<I32>, min<I32>, 13, 15 } }, 0, 1, 2, 3>,

        Simd128PermuteTestParam<I64, 2, Array<I64, 2>{ { max<I64>, min<I64> } },
                                Array<I64, 2>{ { max<I64>, max<I64> } }, 0, 0>,
        Simd128PermuteTestParam<I64, 2, Array<I64, 2>{ { max<I64>, min<I64> } },
                                Array<I64, 2>{ { min<I64>, max<I64> } }, 1, 0>,
        Simd128PermuteTestParam<I64, 2, Array<I64, 2>{ { max<I64>, min<I64> } },
                                Array<I64, 2>{ { max<I64>, min<I64> } }, 0, 1>,

        // Floating point types
        Simd128PermuteTestParam<FP32, 2, Array<FP32, 2>{ { max<FP32>, min<FP32> } },
                                Array<FP32, 2>{ { max<FP32>, max<FP32> } }, 0, 0>,
        Simd128PermuteTestParam<FP32, 2, Array<FP32, 2>{ { max<FP32>, min<FP32> } },
                                Array<FP32, 2>{ { min<FP32>, max<FP32> } }, 1, 0>,
        Simd128PermuteTestParam<FP32, 2, Array<FP32, 2>{ { max<FP32>, min<FP32> } },
                                Array<FP32, 2>{ { max<FP32>, min<FP32> } }, 0, 1>,

        Simd128PermuteTestParam<FP32, 4, Array<FP32, 4>{ { max<FP32>, min<FP32>, 4.12349f, 3.1239f } },
                                Array<FP32, 4>{ { max<FP32>, max<FP32>, max<FP32>, max<FP32> } }, 0, 0, 0, 0>,
        Simd128PermuteTestParam<FP32, 4, Array<FP32, 4>{ { max<FP32>, min<FP32>, 4.12349f, 3.1239f } },
                                Array<FP32, 4>{ { 3.1239f, 4.12349f, min<FP32>, max<FP32> } }, 3, 2, 1, 0>,
        Simd128PermuteTestParam<FP32, 4, Array<FP32, 4>{ { max<FP32>, min<FP32>, 4.12349f, 3.1239f } },
                                Array<FP32, 4>{ { max<FP32>, min<FP32>, 4.12349f, 3.1239f } }, 0, 1, 2, 3>,

        Simd128PermuteTestParam<FP64, 2, Array<FP64, 2>{ { max<FP64>, min<FP64> } },
                                Array<FP64, 2>{ { max<FP64>, max<FP64> } }, 0, 0>,
        Simd128PermuteTestParam<FP64, 2, Array<FP64, 2>{ { max<FP64>, min<FP64> } },
                                Array<FP64, 2>{ { min<FP64>, max<FP64> } }, 1, 0>,
        Simd128PermuteTestParam<FP64, 2, Array<FP64, 2>{ { max<FP64>, min<FP64> } },
                                Array<FP64, 2>{ { max<FP64>, min<FP64> } }, 0, 1>>;

    /// @brief Test fixture for Simd128 blending operations.
    template <typename>
    class Simd128PermuteTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Simd128PermuteTests, Simd128BlendTestTypeHints);

} // namespace


TYPED_TEST(Simd128PermuteTests, ReturnsRegisterWithCorrectValues)
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
    auto execPermute = [data]<uint8_t... I>(std::integer_sequence<uint8_t, I...>) {
        flcn::Simd128_t<Type, Lanes> reg{};
        reg.load(const_cast<Type*>(data.data()));
        return reg.template permute<I...>();
    };

    // Perform the shuffling
    alignas(16) Array<Type, Lanes> result{};
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
