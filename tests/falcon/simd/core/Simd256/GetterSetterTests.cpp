/**
 * @file GetterSetterTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 22, 2026
 *
 * @brief Verifies Simd256 getters/setters.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "SIMDTestSetup.h"

#include <array>


/**
 * @addtogroup T_SIMD256_Get_Set
 * @{
 */

// TODO: Remove Preprocessor after implementing individual simd paths
#if defined(FALCON_ENABLE_AVX512) || defined(FALCON_ENABLE_AVX2) || defined(FALCON_ENABLE_AVX) ||                      \
    defined(FALCON_ENABLE_SSE4) || defined(FALCON_ENABLE_SSE2)
namespace
{
    /**
     * @brief Test Fixture for Simd256 getter/setter operations.
     */
    template <typename T>
    class Simd256GetterSetterTests: public testing::Test
    {
    public:
        using Register = flcn::Simd256_t<typename T::Type, T::VALUE>;

        static constexpr auto max = std::numeric_limits<typename T::Type>::max();
        static constexpr auto min = std::numeric_limits<typename T::Type>::min();
        alignas(32) static constexpr std::array<typename T::Type, 32> data = { max, min, 0, 3,  5,  11, 15, 3,
                                                                               1,   2,   5, 12, 14, 3,  15, 12,
                                                                               max, min, 0, 3,  5,  11, 15, 3,
                                                                               1,   2,   5, 12, 14, 3,  15, 12 };

        /// Testing condition
        template <size_t... Index>
        Register setValuesAndGetRegister(std::index_sequence<Index...>)
        {
            Register reg;
            reg.set(data[Index]...);
            return reg;
        }
    };
    TYPED_TEST_SUITE(Simd256GetterSetterTests, Simd256RegisterTypeHints);
} // namespace


TYPED_TEST(Simd256GetterSetterTests, Set_FillsActiveLanesInCorrectOrder)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;
    const size_t MaxLanes = 32 / sizeof(Type);

    /// Grab the register prefilled with values using set
    auto reg = this->setValuesAndGetRegister(std::make_index_sequence<Lane>{});

    alignas(32) std::array<Type, MaxLanes> result{};
    reg.store(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(result[i], this->data[i]);
    }
}



TYPED_TEST(Simd256GetterSetterTests, Set_FillsUnoccupiedSpaceWithZeroes)
{
    using Type            = typename TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;
    const size_t MaxLanes = 32 / sizeof(Type);

    // If the register is perfectly full (e.g., 4 floats), there is no space to pad.
    // We can tell GTest to automatically skip this specific matrix combination!
    if constexpr (Lane == MaxLanes)
    {
        GTEST_SKIP() << "Register is fully occupied, skipping zero-padding test.";
    }
    else
    {
        auto reg = this->setValuesAndGetRegister(std::make_index_sequence<Lane>{});

        alignas(32) std::array<Type, MaxLanes> result{};
        reg.store(result.data());


        for (size_t i = Lane; i < MaxLanes; ++i)
        {
            EXPECT_EQ(result[i], static_cast<Type>(0));
        }
    }
}


TEST(Simd256GetterSetterTests, Set_CanTakeParametersLessThanLaneSize)
{
    using Type            = uint8_t;
    constexpr size_t Lane = 32;
    flcn::Simd256_t<Type, Lane> reg{};
    reg.set(static_cast<Type>(1), static_cast<Type>(2), static_cast<Type>(3), static_cast<Type>(4),
            static_cast<Type>(5), static_cast<Type>(6), static_cast<Type>(7));
    alignas(32) std::array<Type, Lane> result;
    reg.store(result.data());

    EXPECT_EQ(1, result[0]);
    EXPECT_EQ(2, result[1]);
    EXPECT_EQ(3, result[2]);
    EXPECT_EQ(4, result[3]);
    EXPECT_EQ(5, result[4]);
    EXPECT_EQ(6, result[5]);
    EXPECT_EQ(7, result[6]);
}


TYPED_TEST(Simd256GetterSetterTests, SetZero_FillsTheLanesWithZeroes)
{
    using Type            = typename TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    auto reg = flcn::Simd256_t<Type, Lane>();
    reg.setZero();

    alignas(32) std::array<Type, Lane> result{};
    reg.store(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(static_cast<Type>(0), result[i]);
    }
}


TYPED_TEST(Simd256GetterSetterTests, SetOne_FillsTheLanesWithOnes)
{
    using Type            = typename TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;
    constexpr auto one    = getAllOnes<Type>();

    auto reg = flcn::Simd256_t<Type, Lane>();
    reg.setOne();

    alignas(32) std::array<Type, Lane> result{};
    reg.store(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        // Floating point types returns -nan which doesn't equal any so we must use
        // bitwise comparison.
        if constexpr (std::is_floating_point_v<Type>)
        {
            EXPECT_TRUE(isEqualBitwise(one, result[i]));
        }
        else
        {
            EXPECT_ANY_EQ(one, result[i]);
        }
    }
}


/// @test Verify that get(index) returns the element at the given index.
TYPED_TEST(Simd256GetterSetterTests, GetAt_ReturnsTheValueAtGivenIndex)
{
    constexpr size_t Lane = TypeParam::VALUE;
    auto reg              = this->setValuesAndGetRegister(std::make_index_sequence<Lane>{});

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(this->data[i], reg.getAt(i));
    }
}


TYPED_TEST(Simd256GetterSetterTests, ExtractFirst_ReturnsTheValueAtZerothIndex)
{
    constexpr size_t Lane = TypeParam::VALUE;
    auto reg              = this->setValuesAndGetRegister(std::make_index_sequence<Lane>{});

    EXPECT_ANY_EQ(this->data[0], reg.extractFirst());
}



/// @test Verifies that store function stores a data in the appropriate index
/// @note Due to amount of combinations, we are using the typed test combined
///       with loop to test each index corresponding to matrix type, although
///       not recommended due to single assert per test, writing all the tests
///       manually will be wasteful in terms of resources.
TYPED_TEST(Simd256GetterSetterTests, SetAt_SetsTheValueAtAppropriateIndex)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    flcn::Simd256_t<Type, Lane> reg;
    reg.setZero();

    for (size_t i = 0; i < Lane; ++i)
    {
        reg.setAt(i, this->max);
        EXPECT_ANY_EQ(this->max, reg.getAt(i));
    }
}


// TEST(Simd256GetterSetterTests, Integrals_Naive_ReturnsDefaultRegister)
// {
//     flcn::Simd256_t<int32_t, 8> reg{ 1, 2, 3, 4, 5, 6, 7, 8 };
//
//     const auto naiveReg = reg.naive();
//
//     alignas(32) std::array<int, 4> dataLower{}, dataUpper{};
//     _mm_store_si128(reinterpret_cast<__m128i*>(dataLower.data()), naiveReg.lower);
//     _mm_store_si128(reinterpret_cast<__m128i*>(dataUpper.data()), naiveReg.upper);
//
//     EXPECT_ANY_EQ(1, dataLower[0]);
//     EXPECT_ANY_EQ(2, dataLower[1]);
//     EXPECT_ANY_EQ(3, dataLower[2]);
//     EXPECT_ANY_EQ(4, dataLower[3]);
//     EXPECT_ANY_EQ(5, dataUpper[0]);
//     EXPECT_ANY_EQ(6, dataUpper[1]);
//     EXPECT_ANY_EQ(7, dataUpper[2]);
//     EXPECT_ANY_EQ(8, dataUpper[3]);
// }
//
//
// TEST(Simd256GetterSetterTests, Float_Naive_ReturnsDefaultRegister)
// {
//     flcn::Simd256_t<float, 8> reg{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f };
//
//     const auto naiveReg = reg.naive();
//
//     alignas(32) std::array<float, 4> dataLower{}, dataUpper{};
//     _mm_store_ps(dataLower.data(), naiveReg.lower);
//     _mm_store_ps(dataUpper.data(), naiveReg.upper);
//
//     EXPECT_ANY_EQ(1.0f, dataLower[0]);
//     EXPECT_ANY_EQ(2.0f, dataLower[1]);
//     EXPECT_ANY_EQ(3.0f, dataLower[2]);
//     EXPECT_ANY_EQ(4.0f, dataLower[3]);
//     EXPECT_ANY_EQ(5.0f, dataUpper[0]);
//     EXPECT_ANY_EQ(6.0f, dataUpper[1]);
//     EXPECT_ANY_EQ(7.0f, dataUpper[2]);
//     EXPECT_ANY_EQ(8.0f, dataUpper[3]);
// }
//
//
// TEST(Simd256GetterSetterTests, Double_Naive_ReturnsDefaultRegister)
// {
//     flcn::Simd256_t<double, 4> reg{ 1.0, 2.0, 3.0, 4.0 };
//
//     const auto naiveReg = reg.naive();
//
//     alignas(32) std::array<double, 2> dataLower{}, dataUpper{};
//     _mm_store_pd(dataLower.data(), naiveReg.lower);
//     _mm_store_pd(dataUpper.data(), naiveReg.upper);
//
//     EXPECT_ANY_EQ(1.0, dataLower[0]);
//     EXPECT_ANY_EQ(2.0, dataLower[1]);
//     EXPECT_ANY_EQ(3.0, dataUpper[0]);
//     EXPECT_ANY_EQ(4.0, dataUpper[1]);
// }
//
//
// /// @test Verify that *reg returns the default internal register for integrals.
// TEST(Simd256GetterSetterTests, UnaryTimesOperator_IntegralRegister_ReturnsDefaultRegister)
// {
//     flcn::Simd256_t<int32_t, 8> reg{ 1, 2, 3, 4, 5, 6, 7, 8 };
//
//     const auto naiveReg = *reg;
//
//     alignas(32) std::array<int, 4> dataLower{}, dataUpper{};
//     _mm_store_si128(reinterpret_cast<__m128i*>(dataLower.data()), naiveReg.lower);
//     _mm_store_si128(reinterpret_cast<__m128i*>(dataUpper.data()), naiveReg.upper);
//
//     EXPECT_ANY_EQ(1, dataLower[0]);
//     EXPECT_ANY_EQ(2, dataLower[1]);
//     EXPECT_ANY_EQ(3, dataLower[2]);
//     EXPECT_ANY_EQ(4, dataLower[3]);
//     EXPECT_ANY_EQ(5, dataUpper[0]);
//     EXPECT_ANY_EQ(6, dataUpper[1]);
//     EXPECT_ANY_EQ(7, dataUpper[2]);
//     EXPECT_ANY_EQ(8, dataUpper[3]);
// }
//
//
// /// @test Verify that *reg returns the default internal register for floats.
// TEST(Simd256GetterSetterTests, UnaryTimesOperator_FloatRegister_ReturnsDefaultRegister)
// {
//     flcn::Simd256_t<float, 8> reg{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f };
//
//     const auto naiveReg = *reg;
//
//     alignas(32) std::array<float, 4> dataLower{}, dataUpper{};
//     _mm_store_ps(dataLower.data(), naiveReg.lower);
//     _mm_store_ps(dataUpper.data(), naiveReg.upper);
//
//     EXPECT_ANY_EQ(1.0f, dataLower[0]);
//     EXPECT_ANY_EQ(2.0f, dataLower[1]);
//     EXPECT_ANY_EQ(3.0f, dataLower[2]);
//     EXPECT_ANY_EQ(4.0f, dataLower[3]);
//     EXPECT_ANY_EQ(5.0f, dataUpper[0]);
//     EXPECT_ANY_EQ(6.0f, dataUpper[1]);
//     EXPECT_ANY_EQ(7.0f, dataUpper[2]);
//     EXPECT_ANY_EQ(8.0f, dataUpper[3]);
// }
//
//
// /// @test Verify that *reg returns the default internal register for doubles.
// TEST(Simd256GetterSetterTests, UnaryTimesOperator_DoubleRegister_ReturnsDefaultRegister)
// {
//     flcn::Simd256_t<double, 4> reg{ 1.0, 2.0, 3.0, 4.0 };
//
//     const auto naiveReg = *reg;
//
//     alignas(32) std::array<double, 2> dataLower{}, dataUpper{};
//     _mm_store_pd(dataLower.data(), naiveReg.lower);
//     _mm_store_pd(dataUpper.data(), naiveReg.upper);
//
//     EXPECT_ANY_EQ(1.0, dataLower[0]);
//     EXPECT_ANY_EQ(2.0, dataLower[1]);
//     EXPECT_ANY_EQ(3.0, dataUpper[0]);
//     EXPECT_ANY_EQ(4.0, dataUpper[1]);
// }


using namespace simd::testing;

/// @test Verify that get<Index> (compile-time indexing) returns the element at the given index.
    #define TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(TestSuffix, Type, Lanes, Index)                           \
        TEST(Simd256ConstGetAtTests, ReturnsTheValue_##TestSuffix)                                                     \
        {                                                                                                              \
            constexpr auto max                                 = std::numeric_limits<Type>::max();                     \
            constexpr auto min                                 = std::numeric_limits<Type>::min();                     \
            alignas(32) constexpr std::array<Type, 32> dataArr = { max, min, 0, 3,  5,  11,  15,  3, 1,  2, 5,         \
                                                                   12,  14,  3, 15, 12, max, min, 0, 3,  5, 11,        \
                                                                   15,  3,   1, 2,  5,  12,  14,  3, 15, 12 };         \
                                                                                                                       \
            flcn::Simd256_t<Type, Lanes> reg(dataArr.data());                                                          \
            EXPECT_ANY_EQ(dataArr[Index], reg.getAt<Index>());                                                         \
        }


// Unsigned Types
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex0, U8, 32, 0)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex1, U8, 32, 1)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex2, U8, 32, 2)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex3, U8, 32, 3)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex4, U8, 32, 4)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex5, U8, 32, 5)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex6, U8, 32, 6)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex7, U8, 32, 7)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex8, U8, 32, 8)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex9, U8, 32, 9)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex10, U8, 32, 10)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex11, U8, 32, 11)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex12, U8, 32, 12)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex13, U8, 32, 13)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex14, U8, 32, 14)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex15, U8, 32, 15)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex16, U8, 32, 16)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex17, U8, 32, 17)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex18, U8, 32, 18)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex19, U8, 32, 19)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex20, U8, 32, 20)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex21, U8, 32, 21)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex22, U8, 32, 22)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex23, U8, 32, 23)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex24, U8, 32, 24)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex25, U8, 32, 25)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex26, U8, 32, 26)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex27, U8, 32, 27)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex28, U8, 32, 28)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex29, U8, 32, 29)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex30, U8, 32, 30)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex31, U8, 32, 31)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex0, U16, 16, 0)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex1, U16, 16, 1)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex2, U16, 16, 2)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex3, U16, 16, 3)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex4, U16, 16, 4)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex5, U16, 16, 5)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex6, U16, 16, 6)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex7, U16, 16, 7)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex8, U16, 16, 8)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex9, U16, 16, 9)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex10, U16, 16, 10)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex11, U16, 16, 11)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex12, U16, 16, 12)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex13, U16, 16, 13)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex14, U16, 16, 14)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex15, U16, 16, 15)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint32_8Lanes_AtIndex0, U32, 8, 0)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint32_8Lanes_AtIndex1, U32, 8, 1)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint32_8Lanes_AtIndex2, U32, 8, 2)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint32_8Lanes_AtIndex3, U32, 8, 3)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint32_8Lanes_AtIndex4, U32, 8, 4)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint32_8Lanes_AtIndex5, U32, 8, 5)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint32_8Lanes_AtIndex6, U32, 8, 6)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint32_8Lanes_AtIndex7, U32, 8, 7)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint64_4Lanes_AtIndex0, U64, 4, 0)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint64_4Lanes_AtIndex1, U64, 4, 1)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint64_4Lanes_AtIndex2, U64, 4, 2)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint64_4Lanes_AtIndex3, U64, 4, 3)


// Signed Types
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex0, I8, 32, 0)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex1, I8, 32, 1)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex2, I8, 32, 2)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex3, I8, 32, 3)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex4, I8, 32, 4)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex5, I8, 32, 5)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex6, I8, 32, 6)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex7, I8, 32, 7)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex8, I8, 32, 8)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex9, I8, 32, 9)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex10, I8, 32, 10)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex11, I8, 32, 11)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex12, I8, 32, 12)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex13, I8, 32, 13)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex14, I8, 32, 14)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex15, I8, 32, 15)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex16, I8, 32, 16)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex17, I8, 32, 17)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex18, I8, 32, 18)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex19, I8, 32, 19)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex20, I8, 32, 20)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex21, I8, 32, 21)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex22, I8, 32, 22)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex23, I8, 32, 23)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex24, I8, 32, 24)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex25, I8, 32, 25)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex26, I8, 32, 26)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex27, I8, 32, 27)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex28, I8, 32, 28)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex29, I8, 32, 29)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex30, I8, 32, 30)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex31, I8, 32, 31)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex0, I16, 16, 0)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex1, I16, 16, 1)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex2, I16, 16, 2)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex3, I16, 16, 3)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex4, I16, 16, 4)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex5, I16, 16, 5)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex6, I16, 16, 6)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex7, I16, 16, 7)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex8, I16, 16, 8)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex9, I16, 16, 9)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex10, I16, 16, 10)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex11, I16, 16, 11)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex12, I16, 16, 12)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex13, I16, 16, 13)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex14, I16, 16, 14)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex15, I16, 16, 15)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int32_8Lanes_AtIndex0, I32, 8, 0)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int32_8Lanes_AtIndex1, I32, 8, 1)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int32_8Lanes_AtIndex2, I32, 8, 2)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int32_8Lanes_AtIndex3, I32, 8, 3)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int32_8Lanes_AtIndex4, I32, 8, 4)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int32_8Lanes_AtIndex5, I32, 8, 5)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int32_8Lanes_AtIndex6, I32, 8, 6)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int32_8Lanes_AtIndex7, I32, 8, 7)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int64_4Lanes_AtIndex0, I64, 4, 0)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int64_4Lanes_AtIndex1, I64, 4, 1)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int64_4Lanes_AtIndex2, I64, 4, 2)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int64_4Lanes_AtIndex3, I64, 4, 3)


// Floating Point Types
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(FP32_8Lanes_AtIndex0, FP32, 8, 0)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(FP32_8Lanes_AtIndex1, FP32, 8, 1)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(FP32_8Lanes_AtIndex2, FP32, 8, 2)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(FP32_8Lanes_AtIndex3, FP32, 8, 3)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(FP32_8Lanes_AtIndex4, FP32, 8, 4)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(FP32_8Lanes_AtIndex5, FP32, 8, 5)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(FP32_8Lanes_AtIndex6, FP32, 8, 6)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(FP32_8Lanes_AtIndex7, FP32, 8, 7)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(FP64_4Lanes_AtIndex0, FP64, 4, 0)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(FP64_4Lanes_AtIndex1, FP64, 4, 1)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(FP64_4Lanes_AtIndex2, FP64, 4, 2)
TEST_SIMD256_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(FP64_4Lanes_AtIndex3, FP64, 4, 3)



/// @test Verify that get<Index> (compile-time indexing) returns the element at the given index.
    #define TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(TestSuffix, Type, Lanes, Index)                           \
        TEST(Simd256ConstSetAtTests, SetsTheValue_##TestSuffix)                                                        \
        {                                                                                                              \
            constexpr auto max                                 = std::numeric_limits<Type>::max();                     \
            constexpr auto min                                 = std::numeric_limits<Type>::min();                     \
            alignas(32) constexpr std::array<Type, 32> dataArr = { max, min, 0, 3,  5,  11,  15,  3, 1,  2, 5,         \
                                                                   12,  14,  3, 15, 12, max, min, 0, 3,  5, 11,        \
                                                                   15,  3,   1, 2,  5,  12,  14,  3, 15, 12 };         \
                                                                                                                       \
            flcn::Simd256_t<Type, Lanes> reg{};                                                                        \
            reg.setAt<Index>(dataArr[Index]);                                                                          \
            EXPECT_ANY_EQ(dataArr[Index], reg.getAt<Index>());                                                         \
        }


// Unsigned Types
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex0, U8, 32, 0)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex1, U8, 32, 1)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex2, U8, 32, 2)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex3, U8, 32, 3)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex4, U8, 32, 4)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex5, U8, 32, 5)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex6, U8, 32, 6)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex7, U8, 32, 7)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex8, U8, 32, 8)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex9, U8, 32, 9)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex10, U8, 32, 10)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex11, U8, 32, 11)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex12, U8, 32, 12)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex13, U8, 32, 13)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex14, U8, 32, 14)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex15, U8, 32, 15)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex16, U8, 32, 16)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex17, U8, 32, 17)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex18, U8, 32, 18)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex19, U8, 32, 19)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex20, U8, 32, 20)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex21, U8, 32, 21)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex22, U8, 32, 22)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex23, U8, 32, 23)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex24, U8, 32, 24)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex25, U8, 32, 25)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex26, U8, 32, 26)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex27, U8, 32, 27)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex28, U8, 32, 28)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex29, U8, 32, 29)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex30, U8, 32, 30)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_32Lanes_AtIndex31, U8, 32, 31)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex0, U16, 16, 0)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex1, U16, 16, 1)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex2, U16, 16, 2)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex3, U16, 16, 3)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex4, U16, 16, 4)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex5, U16, 16, 5)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex6, U16, 16, 6)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex7, U16, 16, 7)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex8, U16, 16, 8)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex9, U16, 16, 9)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex10, U16, 16, 10)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex11, U16, 16, 11)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex12, U16, 16, 12)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex13, U16, 16, 13)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex14, U16, 16, 14)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_16Lanes_AtIndex15, U16, 16, 15)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint32_8Lanes_AtIndex0, U32, 8, 0)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint32_8Lanes_AtIndex1, U32, 8, 1)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint32_8Lanes_AtIndex2, U32, 8, 2)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint32_8Lanes_AtIndex3, U32, 8, 3)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint32_8Lanes_AtIndex4, U32, 8, 4)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint32_8Lanes_AtIndex5, U32, 8, 5)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint32_8Lanes_AtIndex6, U32, 8, 6)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint32_8Lanes_AtIndex7, U32, 8, 7)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint64_4Lanes_AtIndex0, U64, 4, 0)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint64_4Lanes_AtIndex1, U64, 4, 1)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint64_4Lanes_AtIndex2, U64, 4, 2)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint64_4Lanes_AtIndex3, U64, 4, 3)

// Signed Types
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex0, I8, 32, 0)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex1, I8, 32, 1)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex2, I8, 32, 2)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex3, I8, 32, 3)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex4, I8, 32, 4)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex5, I8, 32, 5)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex6, I8, 32, 6)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex7, I8, 32, 7)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex8, I8, 32, 8)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex9, I8, 32, 9)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex10, I8, 32, 10)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex11, I8, 32, 11)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex12, I8, 32, 12)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex13, I8, 32, 13)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex14, I8, 32, 14)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex15, I8, 32, 15)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex16, I8, 32, 16)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex17, I8, 32, 17)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex18, I8, 32, 18)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex19, I8, 32, 19)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex20, I8, 32, 20)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex21, I8, 32, 21)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex22, I8, 32, 22)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex23, I8, 32, 23)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex24, I8, 32, 24)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex25, I8, 32, 25)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex26, I8, 32, 26)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex27, I8, 32, 27)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex28, I8, 32, 28)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex29, I8, 32, 29)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex30, I8, 32, 30)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_32Lanes_AtIndex31, I8, 32, 31)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex0, I16, 16, 0)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex1, I16, 16, 1)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex2, I16, 16, 2)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex3, I16, 16, 3)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex4, I16, 16, 4)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex5, I16, 16, 5)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex6, I16, 16, 6)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex7, I16, 16, 7)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex8, I16, 16, 8)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex9, I16, 16, 9)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex10, I16, 16, 10)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex11, I16, 16, 11)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex12, I16, 16, 12)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex13, I16, 16, 13)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex14, I16, 16, 14)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_16Lanes_AtIndex15, I16, 16, 15)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int32_8Lanes_AtIndex0, I32, 8, 0)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int32_8Lanes_AtIndex1, I32, 8, 1)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int32_8Lanes_AtIndex2, I32, 8, 2)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int32_8Lanes_AtIndex3, I32, 8, 3)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int32_8Lanes_AtIndex4, I32, 8, 4)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int32_8Lanes_AtIndex5, I32, 8, 5)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int32_8Lanes_AtIndex6, I32, 8, 6)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int32_8Lanes_AtIndex7, I32, 8, 7)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int64_4Lanes_AtIndex0, I64, 4, 0)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int64_4Lanes_AtIndex1, I64, 4, 1)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int64_4Lanes_AtIndex2, I64, 4, 2)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int64_4Lanes_AtIndex3, I64, 4, 3)

// Floating Point Types
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(FP32_8Lanes_AtIndex0, FP32, 8, 0)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(FP32_8Lanes_AtIndex1, FP32, 8, 1)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(FP32_8Lanes_AtIndex2, FP32, 8, 2)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(FP32_8Lanes_AtIndex3, FP32, 8, 3)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(FP32_8Lanes_AtIndex4, FP32, 8, 4)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(FP32_8Lanes_AtIndex5, FP32, 8, 5)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(FP32_8Lanes_AtIndex6, FP32, 8, 6)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(FP32_8Lanes_AtIndex7, FP32, 8, 7)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(FP64_4Lanes_AtIndex0, FP64, 4, 0)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(FP64_4Lanes_AtIndex1, FP64, 4, 1)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(FP64_4Lanes_AtIndex2, FP64, 4, 2)
TEST_SIMD256_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(FP64_4Lanes_AtIndex3, FP64, 4, 3)

#endif

/** @} */
