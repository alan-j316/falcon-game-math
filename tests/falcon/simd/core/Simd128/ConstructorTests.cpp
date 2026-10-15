/**
 * @file ConstructorTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 08, 2026
 *
 * @brief Verifies Simd128 constructors.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "SIMDTestSetup.h"

#include <array>
#include <bit>
#include <memory_resource>


// TODO: Remove Preprocessor after implementing individual simd paths
#if defined(FALCON_ENABLE_AVX512) || defined(FALCON_ENABLE_AVX2) || defined(FALCON_ENABLE_AVX) ||                      \
    defined(FALCON_ENABLE_SSE4) || defined(FALCON_ENABLE_SSE2)

/**
 * @addtogroup T_SIMD128_Ctor
 * @{
 */

namespace
{
    /**
     * @brief Test Fixture for Simd128 constructor(Buffer* and std::container based).
     */
    template <typename>
    class Simd128CtorTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Simd128CtorTests, Simd128RegisterTypeHints);

} // namespace

using namespace simd::testing;


TYPED_TEST(Simd128CtorTests, Simd128_CanBeInitializedWithAlignedVector)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    std::pmr::synchronized_pool_resource mem({ .max_blocks_per_chunk = 0, .largest_required_pool_block = 16 });
    std::pmr::vector<Type> data(Lane, &mem);

    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = static_cast<Type>(i + 11);
    }

    flcn::Simd128_t<Type, Lane> reg{ data };

    alignas(16) std::array<Type, Lane> result{};
    reg.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(data[i], result[i]);
    }
}



TYPED_TEST(Simd128CtorTests, Simd128_CanBeInitializedWithAStdArray)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> data{};

    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = static_cast<Type>(i + 11);
    }

    flcn::Simd128_t<Type, Lane> reg{ data };

    alignas(16) std::array<Type, Lane> result{};
    reg.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(data[i], result[i]);
    }
}


TYPED_TEST(Simd128CtorTests, Simd128_CanBeInitializedWithACStyleArray)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) Type data[Lane]{};

    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = static_cast<Type>(i + 11);
    }

    flcn::Simd128_t<Type, Lane> reg{ data };

    alignas(16) std::array<Type, Lane> result{};
    reg.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(data[i], result[i]);
    }
}




/**************************************
 *        VARARG CTOR TESTS           *
 **************************************/

/// @test Verifies that Simd128 can be constructed with variable arguments.
/// @note The Simd register expects integral args of datatype and since there is not direct static cast we need to use
///       a helper lambda that takes in a __VA_ARGS__ and static cast each element with parameter args.
    #define TEST_SIMD128_VARG_CTOR(TestNameSuffix, DataType, Lanes, ...)                                               \
        TEST(Simd128VarargsCtorTests, InitializesWith_##TestNameSuffix)                                                \
        {                                                                                                              \
            DataType inputData[]{ __VA_ARGS__ };                                                                       \
            constexpr size_t size = sizeof(inputData) / sizeof(DataType);                                              \
            DataType outputData[Lanes]{};                                                                              \
            auto getSimd = [](auto... args) {                                                                          \
                return flcn::Simd128_t<DataType, Lanes>{ static_cast<DataType>(args)... };                             \
            };                                                                                                         \
            flcn::Simd128_t<DataType, Lanes> reg = getSimd(__VA_ARGS__);                                               \
            reg.store(outputData);                                                                                     \
                                                                                                                       \
            for (size_t i = 0; i < size; ++i)                                                                          \
            {                                                                                                          \
                EXPECT_ANY_EQ(inputData[i], outputData[i]);                                                            \
            }                                                                                                          \
        }


// Uint8_t
TEST_SIMD128_VARG_CTOR(Uint8_2Lanes_2Arguments, U8, 2, max<U8>, min<U8>)
TEST_SIMD128_VARG_CTOR(Uint8_4Lanes_2Arguments, U8, 4, max<U8>, min<U8>)
TEST_SIMD128_VARG_CTOR(Uint8_4Lanes_3Arguments, U8, 4, max<U8>, min<U8>, 64)
TEST_SIMD128_VARG_CTOR(Uint8_4Lanes_4Arguments, U8, 4, max<U8>, min<U8>, 64, 32)
TEST_SIMD128_VARG_CTOR(Uint8_8Lanes_2Arguments, U8, 8, max<U8>, min<U8>)
TEST_SIMD128_VARG_CTOR(Uint8_8Lanes_3Arguments, U8, 8, max<U8>, min<U8>, 64)
TEST_SIMD128_VARG_CTOR(Uint8_8Lanes_4Arguments, U8, 8, max<U8>, min<U8>, 64, 32)
TEST_SIMD128_VARG_CTOR(Uint8_8Lanes_5Arguments, U8, 8, max<U8>, min<U8>, 64, 32, 16)
TEST_SIMD128_VARG_CTOR(Uint8_8Lanes_6Arguments, U8, 8, max<U8>, min<U8>, 64, 32, 16, 8)
TEST_SIMD128_VARG_CTOR(Uint8_8Lanes_7Arguments, U8, 8, max<U8>, min<U8>, 64, 32, 16, 8, 4)
TEST_SIMD128_VARG_CTOR(Uint8_8Lanes_8Arguments, U8, 8, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_2Arguments, U8, 16, max<U8>, min<U8>)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_3Arguments, U8, 16, max<U8>, min<U8>, 64)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_4Arguments, U8, 16, max<U8>, min<U8>, 64, 32)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_5Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_6Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16, 8)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_7Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16, 8, 4)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_8Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_9Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_10Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_11Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_12Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 4)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_13Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 4, 6)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_14Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 4, 6, 8)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_15Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 4, 6, 8, 15)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes_16Arguments, U8, 16, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 4, 6, 8, 15, 17)
// Uint16_t
TEST_SIMD128_VARG_CTOR(Uint16_2Lanes_2Arguments, U16, 2, max<U16>, min<U16>)
TEST_SIMD128_VARG_CTOR(Uint16_4Lanes_2Arguments, U16, 4, max<U16>, min<U16>)
TEST_SIMD128_VARG_CTOR(Uint16_4Lanes_3Arguments, U16, 4, max<U16>, min<U16>, 64)
TEST_SIMD128_VARG_CTOR(Uint16_4Lanes_4Arguments, U16, 4, max<U16>, min<U16>, 64, 32)
TEST_SIMD128_VARG_CTOR(Uint16_8Lanes_2Arguments, U16, 8, max<U16>, min<U16>)
TEST_SIMD128_VARG_CTOR(Uint16_8Lanes_3Arguments, U16, 8, max<U16>, min<U16>, 64)
TEST_SIMD128_VARG_CTOR(Uint16_8Lanes_4Arguments, U16, 8, max<U16>, min<U16>, 64, 32)
TEST_SIMD128_VARG_CTOR(Uint16_8Lanes_5Arguments, U16, 8, max<U16>, min<U16>, 64, 32, 16)
TEST_SIMD128_VARG_CTOR(Uint16_8Lanes_6Arguments, U16, 8, max<U16>, min<U16>, 64, 32, 16, 8)
TEST_SIMD128_VARG_CTOR(Uint16_8Lanes_7Arguments, U16, 8, max<U16>, min<U16>, 64, 32, 16, 8, 4)
TEST_SIMD128_VARG_CTOR(Uint16_8Lanes_8Arguments, U16, 8, max<U16>, min<U16>, 64, 32, 16, 8, 4, 2)
// Uint32_t
TEST_SIMD128_VARG_CTOR(Uint32_2Lanes_2Arguments, U32, 2, max<U32>, min<U32>)
TEST_SIMD128_VARG_CTOR(Uint32_4Lanes_2Arguments, U32, 4, max<U32>, min<U32>)
TEST_SIMD128_VARG_CTOR(Uint32_4Lanes_3Arguments, U32, 4, max<U32>, min<U32>, 64)
TEST_SIMD128_VARG_CTOR(Uint32_4Lanes_4Arguments, U32, 4, max<U32>, min<U32>, 64, 32)
// Uint64_t
TEST_SIMD128_VARG_CTOR(Uint64_2Lanes_2Arguments, U64, 2, max<U64>, min<U64>)

// Int8_t
TEST_SIMD128_VARG_CTOR(Int8_2Lanes_2Arguments, I8, 2, max<I8>, min<I8>)
TEST_SIMD128_VARG_CTOR(Int8_4Lanes_2Arguments, I8, 4, max<I8>, min<I8>)
TEST_SIMD128_VARG_CTOR(Int8_4Lanes_3Arguments, I8, 4, max<I8>, min<I8>, 64)
TEST_SIMD128_VARG_CTOR(Int8_4Lanes_4Arguments, I8, 4, max<I8>, min<I8>, 64, 32)
TEST_SIMD128_VARG_CTOR(Int8_8Lanes_2Arguments, I8, 8, max<I8>, min<I8>)
TEST_SIMD128_VARG_CTOR(Int8_8Lanes_3Arguments, I8, 8, max<I8>, min<I8>, 64)
TEST_SIMD128_VARG_CTOR(Int8_8Lanes_4Arguments, I8, 8, max<I8>, min<I8>, 64, 32)
TEST_SIMD128_VARG_CTOR(Int8_8Lanes_5Arguments, I8, 8, max<I8>, min<I8>, 64, 32, 16)
TEST_SIMD128_VARG_CTOR(Int8_8Lanes_6Arguments, I8, 8, max<I8>, min<I8>, 64, 32, 16, 8)
TEST_SIMD128_VARG_CTOR(Int8_8Lanes_7Arguments, I8, 8, max<I8>, min<I8>, 64, 32, 16, 8, 4)
TEST_SIMD128_VARG_CTOR(Int8_8Lanes_8Arguments, I8, 8, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_2Arguments, I8, 16, max<I8>, min<I8>)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_3Arguments, I8, 16, max<I8>, min<I8>, 64)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_4Arguments, I8, 16, max<I8>, min<I8>, 64, 32)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_5Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_6Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16, 8)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_7Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16, 8, 4)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_8Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_9Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_10Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_11Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_12Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 4)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_13Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 4, 6)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_14Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 4, 6, 8)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_15Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 4, 6, 8, 15)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes_16Arguments, I8, 16, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 4, 6, 8, 15, 17)
// Int16_t
TEST_SIMD128_VARG_CTOR(Int16_2Lanes_2Arguments, I16, 2, max<I16>, min<I16>)
TEST_SIMD128_VARG_CTOR(Int16_4Lanes_2Arguments, I16, 4, max<I16>, min<I16>)
TEST_SIMD128_VARG_CTOR(Int16_4Lanes_3Arguments, I16, 4, max<I16>, min<I16>, 64)
TEST_SIMD128_VARG_CTOR(Int16_4Lanes_4Arguments, I16, 4, max<I16>, min<I16>, 64, 32)
TEST_SIMD128_VARG_CTOR(Int16_8Lanes_2Arguments, I16, 8, max<I16>, min<I16>)
TEST_SIMD128_VARG_CTOR(Int16_8Lanes_3Arguments, I16, 8, max<I16>, min<I16>, 64)
TEST_SIMD128_VARG_CTOR(Int16_8Lanes_4Arguments, I16, 8, max<I16>, min<I16>, 64, 32)
TEST_SIMD128_VARG_CTOR(Int16_8Lanes_5Arguments, I16, 8, max<I16>, min<I16>, 64, 32, 16)
TEST_SIMD128_VARG_CTOR(Int16_8Lanes_6Arguments, I16, 8, max<I16>, min<I16>, 64, 32, 16, 8)
TEST_SIMD128_VARG_CTOR(Int16_8Lanes_7Arguments, I16, 8, max<I16>, min<I16>, 64, 32, 16, 8, 4)
TEST_SIMD128_VARG_CTOR(Int16_8Lanes_8Arguments, I16, 8, max<I16>, min<I16>, 64, 32, 16, 8, 4, 2)
// Int32_t
TEST_SIMD128_VARG_CTOR(Int32_2Lanes_2Arguments, I32, 2, max<I32>, min<I32>)
TEST_SIMD128_VARG_CTOR(Int32_4Lanes_2Arguments, I32, 4, max<I32>, min<I32>)
TEST_SIMD128_VARG_CTOR(Int32_4Lanes_3Arguments, I32, 4, max<I32>, min<I32>, 64)
TEST_SIMD128_VARG_CTOR(Int32_4Lanes_4Arguments, I32, 4, max<I32>, min<I32>, 64, 32)
// Int64_t
TEST_SIMD128_VARG_CTOR(Int64_2Lanes_2Arguments, I64, 2, max<I64>, min<I64>)

// FP32
TEST_SIMD128_VARG_CTOR(FP32_2Lanes_2Arguments, FP32, 2, max<FP32>, min<FP32>)
TEST_SIMD128_VARG_CTOR(FP32_4Lanes_2Arguments, FP32, 4, max<FP32>, min<FP32>)
TEST_SIMD128_VARG_CTOR(FP32_4Lanes_3Arguments, FP32, 4, max<FP32>, min<FP32>, 64.1234f)
TEST_SIMD128_VARG_CTOR(FP32_4Lanes_4Arguments, FP32, 4, max<FP32>, min<FP32>, 64.1234f, 32.9899f)
// FP64
TEST_SIMD128_VARG_CTOR(FP64_2Lanes_2Arguments, FP64, 2, max<FP64>, min<FP64>)




/// @test Verifies that Simd128 when constructed with single argument broadcasts it across the lanes.
/// @note The Simd register expects integral args of datatype and since there is not direct static cast we need to use
///       a helper lambda that takes in a __VA_ARGS__ and static cast each element with parameter args.
    #define TEST_SIMD128_SINGLE_ARG_CTOR(TestNameSuffix, DataType, Lanes, Data)                                        \
        TEST(Simd128SingleArgCtorTests, InitializesWith_##TestNameSuffix)                                              \
        {                                                                                                              \
            DataType outputData[Lanes]{};                                                                              \
            flcn::Simd128_t<DataType, Lanes> reg{ Data };                                                              \
            reg.store(outputData);                                                                                     \
                                                                                                                       \
            for (size_t i = 0; i < Lanes; ++i)                                                                         \
            {                                                                                                          \
                EXPECT_ANY_EQ(Data, outputData[i]);                                                                    \
            }                                                                                                          \
        }

// Unsigned Types
TEST_SIMD128_VARG_CTOR(Uint8_2Lanes, U8, 2, max<U8>)
TEST_SIMD128_VARG_CTOR(Uint8_4Lanes, U8, 4, max<U8>)
TEST_SIMD128_VARG_CTOR(Uint8_8Lanes, U8, 8, max<U8>)
TEST_SIMD128_VARG_CTOR(Uint8_16Lanes, U8, 16, max<U8>)
TEST_SIMD128_VARG_CTOR(Uint16_2Lanes, U16, 2, max<U16>)
TEST_SIMD128_VARG_CTOR(Uint16_4Lanes, U16, 4, max<U16>)
TEST_SIMD128_VARG_CTOR(Uint16_8Lanes, U16, 8, max<U16>)
TEST_SIMD128_VARG_CTOR(Uint32_2Lanes, U32, 2, max<U32>)
TEST_SIMD128_VARG_CTOR(Uint32_4Lanes, U32, 4, max<U32>)
TEST_SIMD128_VARG_CTOR(Uint64_2Lanes, U64, 2, max<U64>)

// Signed Types
TEST_SIMD128_VARG_CTOR(Int8_2Lanes, I8, 2, max<I8>)
TEST_SIMD128_VARG_CTOR(Int8_4Lanes, I8, 4, max<I8>)
TEST_SIMD128_VARG_CTOR(Int8_8Lanes, I8, 8, max<I8>)
TEST_SIMD128_VARG_CTOR(Int8_16Lanes, I8, 16, max<I8>)
TEST_SIMD128_VARG_CTOR(Int16_2Lanes, I16, 2, max<I16>)
TEST_SIMD128_VARG_CTOR(Int16_4Lanes, I16, 4, max<I16>)
TEST_SIMD128_VARG_CTOR(Int16_8Lanes, I16, 8, max<I16>)
TEST_SIMD128_VARG_CTOR(Int32_2Lanes, I32, 2, max<I32>)
TEST_SIMD128_VARG_CTOR(Int32_4Lanes, I32, 4, max<I32>)
TEST_SIMD128_VARG_CTOR(Int64_2Lanes, I64, 2, max<I64>)

TEST_SIMD128_VARG_CTOR(FP32_2Lanes, FP32, 2, max<FP32>)
TEST_SIMD128_VARG_CTOR(FP32_4Lanes, FP32, 4, max<FP32>)
TEST_SIMD128_VARG_CTOR(FP64_2Lanes, FP64, 2, max<FP64>)

#endif
/** @} */
