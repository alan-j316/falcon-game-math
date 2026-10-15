/**
 * @file ConstructorTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 26, 2026
 *
 * @brief Verifies Simd256 constructors.
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
 * @addtogroup T_SIMD256_Ctor
 * @{
 */

namespace
{
    /**
     * @brief Test Fixture for Simd256 constructor(Buffer* and std::container based).
     */
    template <typename>
    class Simd256CtorTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Simd256CtorTests, Simd256RegisterTypeHints);

} // namespace

using namespace simd::testing;


TYPED_TEST(Simd256CtorTests, Simd256_CanBeInitializedWithAlignedVector)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    // NOTE: Normal vector will cause memory alignment issues.
    std::pmr::synchronized_pool_resource mem({ .max_blocks_per_chunk = 0, .largest_required_pool_block = 32 });
    std::pmr::vector<Type> data(Lane, &mem);

    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = static_cast<Type>(i + 11);
    }

    flcn::Simd256_t<Type, Lane> reg{ data };

    alignas(32) std::array<Type, Lane> result{};
    reg.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(data[i], result[i]);
    }
}



TYPED_TEST(Simd256CtorTests, Simd256_CanBeInitializedWithAStdArray)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(32) std::array<Type, Lane> data{};

    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = static_cast<Type>(i + 11);
    }

    flcn::Simd256_t<Type, Lane> reg{ data };

    alignas(32) std::array<Type, Lane> result{};
    reg.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(data[i], result[i]);
    }
}


TYPED_TEST(Simd256CtorTests, Simd256_CanBeInitializedWithACStyleArray)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(32) Type data[Lane]{};

    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = static_cast<Type>(i + 11);
    }

    flcn::Simd256_t<Type, Lane> reg{ data };

    alignas(32) std::array<Type, Lane> result{};
    reg.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(data[i], result[i]);
    }
}




/**************************************
 *        VARARG CTOR TESTS           *
 **************************************/

/// @test Verifies that Simd256 can be constructed with variable arguments.
/// @note The Simd register expects integral args of datatype and since there is not direct static cast we need to use
///       a helper lambda that takes in a __VA_ARGS__ and static cast each element with parameter args.
    #define TEST_SIMD256_VARG_CTOR(TestNameSuffix, DataType, Lanes, ...)                                               \
        TEST(Simd256VarargsCtorTests, InitializesWith_##TestNameSuffix)                                                \
        {                                                                                                              \
            DataType inputData[]{ __VA_ARGS__ };                                                                       \
            constexpr size_t size = sizeof(inputData) / sizeof(DataType);                                              \
            DataType outputData[Lanes]{};                                                                              \
            auto getSimd = [](auto... args) {                                                                          \
                return flcn::Simd256_t<DataType, Lanes>{ static_cast<DataType>(args)... };                             \
            };                                                                                                         \
            flcn::Simd256_t<DataType, Lanes> reg = getSimd(__VA_ARGS__);                                               \
            reg.store(outputData);                                                                                     \
                                                                                                                       \
            for (size_t i = 0; i < size; ++i)                                                                          \
            {                                                                                                          \
                EXPECT_ANY_EQ(inputData[i], outputData[i]);                                                            \
            }                                                                                                          \
        }


// Uint8_t
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_2Arguments, U8, 32, max<U8>, min<U8>)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_3Arguments, U8, 32, max<U8>, min<U8>, 64)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_4Arguments, U8, 32, max<U8>, min<U8>, 64, 32)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_5Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_6Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_7Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_8Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_9Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_10Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_11Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 5)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_12Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_13Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_14Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_15Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_16Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_17Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_18Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_19Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_20Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_21Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21, 22)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_22Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21, 22, 23)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_23Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21, 22, 23, 24)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_24Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21, 22, 23, 24, 25)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_25Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21, 22, 23, 24, 25, 26)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_26Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_27Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_28Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_29Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_30Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_31Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33)
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes_32Arguments, U8, 32, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, max<U8>, min<U8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15, 17)
// Uint16_t
TEST_SIMD256_VARG_CTOR(Uint16_16Lanes_2Arguments, U16, 16, max<U16>, min<U16>)
TEST_SIMD256_VARG_CTOR(Uint16_16Lanes_3Arguments, U16, 16, max<U16>, min<U16>, 64)
TEST_SIMD256_VARG_CTOR(Uint16_16Lanes_4Arguments, U16, 16, max<U16>, min<U16>, 64, 32)
TEST_SIMD256_VARG_CTOR(Uint16_16Lanes_5Arguments, U16, 16, max<U16>, min<U16>, 64, 32, 16)
TEST_SIMD256_VARG_CTOR(Uint16_16Lanes_6Arguments, U16, 16, max<U16>, min<U16>, 64, 32, 16, 8)
TEST_SIMD256_VARG_CTOR(Uint16_16Lanes_7Arguments, U16, 16, max<U16>, min<U16>, 64, 32, 16, 8, 4)
TEST_SIMD256_VARG_CTOR(Uint16_16Lanes_8Arguments, U16, 16, max<U16>, min<U16>, 64, 32, 16, 8, 4, 2)
TEST_SIMD256_VARG_CTOR(Uint16_16Lanes_9Arguments, U16, 16, max<U16>, min<U16>, 64, 32, 16, 8, 4, 2, 9)
TEST_SIMD256_VARG_CTOR(Uint16_16Lanes_10Arguments, U16, 16, max<U16>, min<U16>, 64, 32, 16, 8, 4, 2, 9, 10)
TEST_SIMD256_VARG_CTOR(Uint16_16Lanes_11Arguments, U16, 16, max<U16>, min<U16>, 64, 32, 16, 8, 4, 2, 9, 10, 11)
TEST_SIMD256_VARG_CTOR(Uint16_16Lanes_12Arguments, U16, 16, max<U16>, min<U16>, 64, 32, 16, 8, 4, 2, 9, 10, 11, 12)
TEST_SIMD256_VARG_CTOR(Uint16_16Lanes_13Arguments, U16, 16, max<U16>, min<U16>, 64, 32, 16, 8, 4, 2, 9, 10, 11, 12, 13)
TEST_SIMD256_VARG_CTOR(Uint16_16Lanes_14Arguments, U16, 16, max<U16>, min<U16>, 64, 32, 16, 8, 4, 2, 9, 10, 11, 12, 13,
                       14)
TEST_SIMD256_VARG_CTOR(Uint16_16Lanes_15Arguments, U16, 16, max<U16>, min<U16>, 64, 32, 16, 8, 4, 2, 9, 10, 11, 12, 13,
                       14, 15)
TEST_SIMD256_VARG_CTOR(Uint16_16Lanes_16Arguments, U16, 16, max<U16>, min<U16>, 64, 32, 16, 8, 4, 2, 9, 10, 11, 12, 13,
                       14, 15, 16)

// Uint32_t
TEST_SIMD256_VARG_CTOR(Uint32_8Lanes_2Arguments, U32, 8, max<U32>, min<U32>)
TEST_SIMD256_VARG_CTOR(Uint32_8Lanes_3Arguments, U32, 8, max<U32>, min<U32>, 64)
TEST_SIMD256_VARG_CTOR(Uint32_8Lanes_4Arguments, U32, 8, max<U32>, min<U32>, 64, 32)
TEST_SIMD256_VARG_CTOR(Uint32_8Lanes_5Arguments, U32, 8, max<U32>, min<U32>, 64, 32, 33)
TEST_SIMD256_VARG_CTOR(Uint32_8Lanes_6Arguments, U32, 8, max<U32>, min<U32>, 64, 32, 33, 34)
TEST_SIMD256_VARG_CTOR(Uint32_8Lanes_7Arguments, U32, 8, max<U32>, min<U32>, 64, 32, 33, 34, 35)
TEST_SIMD256_VARG_CTOR(Uint32_8Lanes_8Arguments, U32, 8, max<U32>, min<U32>, 64, 32, 33, 34, 35, 36)

// Uint64_t
TEST_SIMD256_VARG_CTOR(Uint64_4Lanes_2Arguments, U64, 4, max<U64>, min<U64>)
TEST_SIMD256_VARG_CTOR(Uint64_4Lanes_3Arguments, U64, 4, max<U64>, min<U64>, 4)
TEST_SIMD256_VARG_CTOR(Uint64_4Lanes_4Arguments, U64, 4, max<U64>, min<U64>, 4, 8)


TEST_SIMD256_VARG_CTOR(Int8_32Lanes_2Arguments, I8, 32, max<I8>, min<I8>)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_3Arguments, I8, 32, max<I8>, min<I8>, 64)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_4Arguments, I8, 32, max<I8>, min<I8>, 64, 32)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_5Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_6Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_7Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_8Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_9Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_10Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_11Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 5)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_12Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_13Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_14Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_15Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_16Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_17Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_18Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_19Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_20Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_21Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21, 22)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_22Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21, 22, 23)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_23Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21, 22, 23, 24)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_24Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21, 22, 23, 24, 25)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_25Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21, 22, 23, 24, 25, 26)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_26Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_27Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_28Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_29Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_30Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_31Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33)
TEST_SIMD256_VARG_CTOR(Int8_32Lanes_32Arguments, I8, 32, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15,
                       17, max<I8>, min<I8>, 64, 32, 16, 8, 4, 2, 1, 2, 5, 4, 6, 8, 15, 17)
// Int16_t
TEST_SIMD256_VARG_CTOR(Int16_16Lanes_2Arguments, I16, 16, max<I16>, min<I16>)
TEST_SIMD256_VARG_CTOR(Int16_16Lanes_3Arguments, I16, 16, max<I16>, min<I16>, 64)
TEST_SIMD256_VARG_CTOR(Int16_16Lanes_4Arguments, I16, 16, max<I16>, min<I16>, 64, 32)
TEST_SIMD256_VARG_CTOR(Int16_16Lanes_5Arguments, I16, 16, max<I16>, min<I16>, 64, 32, 16)
TEST_SIMD256_VARG_CTOR(Int16_16Lanes_6Arguments, I16, 16, max<I16>, min<I16>, 64, 32, 16, 8)
TEST_SIMD256_VARG_CTOR(Int16_16Lanes_7Arguments, I16, 16, max<I16>, min<I16>, 64, 32, 16, 8, 4)
TEST_SIMD256_VARG_CTOR(Int16_16Lanes_8Arguments, I16, 16, max<I16>, min<I16>, 64, 32, 16, 8, 4, 2)
TEST_SIMD256_VARG_CTOR(Int16_16Lanes_9Arguments, I16, 16, max<I16>, min<I16>, 64, 32, 16, 8, 4, 2, 9)
TEST_SIMD256_VARG_CTOR(Int16_16Lanes_10Arguments, I16, 16, max<I16>, min<I16>, 64, 32, 16, 8, 4, 2, 9, 10)
TEST_SIMD256_VARG_CTOR(Int16_16Lanes_11Arguments, I16, 16, max<I16>, min<I16>, 64, 32, 16, 8, 4, 2, 9, 10, 11)
TEST_SIMD256_VARG_CTOR(Int16_16Lanes_12Arguments, I16, 16, max<I16>, min<I16>, 64, 32, 16, 8, 4, 2, 9, 10, 11, 12)
TEST_SIMD256_VARG_CTOR(Int16_16Lanes_13Arguments, I16, 16, max<I16>, min<I16>, 64, 32, 16, 8, 4, 2, 9, 10, 11, 12, 13)
TEST_SIMD256_VARG_CTOR(Int16_16Lanes_14Arguments, I16, 16, max<I16>, min<I16>, 64, 32, 16, 8, 4, 2, 9, 10, 11, 12, 13,
                       14)
TEST_SIMD256_VARG_CTOR(Int16_16Lanes_15Arguments, I16, 16, max<I16>, min<I16>, 64, 32, 16, 8, 4, 2, 9, 10, 11, 12, 13,
                       14, 15)
TEST_SIMD256_VARG_CTOR(Int16_16Lanes_16Arguments, I16, 16, max<I16>, min<I16>, 64, 32, 16, 8, 4, 2, 9, 10, 11, 12, 13,
                       14, 15, 16)

// Int32_t
TEST_SIMD256_VARG_CTOR(Int32_8Lanes_2Arguments, I32, 8, max<I32>, min<I32>)
TEST_SIMD256_VARG_CTOR(Int32_8Lanes_3Arguments, I32, 8, max<I32>, min<I32>, 64)
TEST_SIMD256_VARG_CTOR(Int32_8Lanes_4Arguments, I32, 8, max<I32>, min<I32>, 64, 32)
TEST_SIMD256_VARG_CTOR(Int32_8Lanes_5Arguments, I32, 8, max<I32>, min<I32>, 64, 32, 33)
TEST_SIMD256_VARG_CTOR(Int32_8Lanes_6Arguments, I32, 8, max<I32>, min<I32>, 64, 32, 33, 34)
TEST_SIMD256_VARG_CTOR(Int32_8Lanes_7Arguments, I32, 8, max<I32>, min<I32>, 64, 32, 33, 34, 35)
TEST_SIMD256_VARG_CTOR(Int32_8Lanes_8Arguments, I32, 8, max<I32>, min<I32>, 64, 32, 33, 34, 35, 36)

// Int64_t
TEST_SIMD256_VARG_CTOR(Int64_4Lanes_2Arguments, I64, 4, max<I64>, min<I64>)
TEST_SIMD256_VARG_CTOR(Int64_4Lanes_3Arguments, I64, 4, max<I64>, min<I64>, 4)
TEST_SIMD256_VARG_CTOR(Int64_4Lanes_4Arguments, I64, 4, max<I64>, min<I64>, 4, 8)

// FP32
TEST_SIMD256_VARG_CTOR(FP32_8Lanes_2Arguments, FP32, 8, max<FP32>, min<FP32>)
TEST_SIMD256_VARG_CTOR(FP32_8Lanes_3Arguments, FP32, 8, max<FP32>, min<FP32>, 64.1234f)
TEST_SIMD256_VARG_CTOR(FP32_8Lanes_4Arguments, FP32, 8, max<FP32>, min<FP32>, 64.1234f, 32.9899f)
TEST_SIMD256_VARG_CTOR(FP32_8Lanes_5Arguments, FP32, 8, max<FP32>, min<FP32>, 64.1234f, 32.9899f, 4.31f)
TEST_SIMD256_VARG_CTOR(FP32_8Lanes_6Arguments, FP32, 8, max<FP32>, min<FP32>, 64.1234f, 32.9899f, 4.31f, 12.51f)
TEST_SIMD256_VARG_CTOR(FP32_8Lanes_7Arguments, FP32, 8, max<FP32>, min<FP32>, 64.1234f, 32.9899f, 4.31f, 12.51f, 2.12f)
TEST_SIMD256_VARG_CTOR(FP32_8Lanes_8Arguments, FP32, 8, max<FP32>, min<FP32>, 64.1234f, 32.9899f, 4.31f, 12.51f, 2.12f,
                       5.1f)
// FP64
TEST_SIMD256_VARG_CTOR(FP64_4Lanes_2Arguments, FP64, 4, max<FP64>, min<FP64>)
TEST_SIMD256_VARG_CTOR(FP64_4Lanes_3Arguments, FP64, 4, max<FP64>, min<FP64>, 3.123424)
TEST_SIMD256_VARG_CTOR(FP64_4Lanes_4Arguments, FP64, 4, max<FP64>, min<FP64>, 3.123424, 9.91283)




/// @test Verifies that Simd256 when constructed with single argument broadcasts it across the lanes.
/// @note The Simd register expects integral args of datatype and since there is not direct static cast we need to use
///       a helper lambda that takes in a __VA_ARGS__ and static cast each element with parameter args.
    #define TEST_SIMD256_SINGLE_ARG_CTOR(TestNameSuffix, DataType, Lanes, Data)                                        \
        TEST(Simd256SingleArgCtorTests, InitializesWith_##TestNameSuffix)                                              \
        {                                                                                                              \
            DataType outputData[Lanes]{};                                                                              \
            flcn::Simd256_t<DataType, Lanes> reg{ Data };                                                              \
            reg.store(outputData);                                                                                     \
                                                                                                                       \
            for (size_t i = 0; i < Lanes; ++i)                                                                         \
            {                                                                                                          \
                EXPECT_ANY_EQ(Data, outputData[i]);                                                                    \
            }                                                                                                          \
        }

// Unsigned Types
TEST_SIMD256_VARG_CTOR(Uint8_32Lanes, U8, 32, max<U8>)
TEST_SIMD256_VARG_CTOR(Uint16_16Lanes, U16, 16, max<U16>)
TEST_SIMD256_VARG_CTOR(Uint32_8Lanes, U32, 8, max<U32>)
TEST_SIMD256_VARG_CTOR(Uint64_4Lanes, U64, 4, max<U64>)

// Signed Types
TEST_SIMD256_VARG_CTOR(Int8_32Lanes, I8, 32, max<I8>)
TEST_SIMD256_VARG_CTOR(Int16_16Lanes, I16, 16, max<I16>)
TEST_SIMD256_VARG_CTOR(Int32_8Lanes, I32, 8, max<I32>)
TEST_SIMD256_VARG_CTOR(Int64_4Lanes, I64, 4, max<I64>)

TEST_SIMD256_VARG_CTOR(FP32_8Lanes, FP32, 8, max<FP32>)
TEST_SIMD256_VARG_CTOR(FP64_4Lanes, FP64, 4, max<FP64>)

#endif
/** @} */
