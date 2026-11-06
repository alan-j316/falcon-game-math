/**
 * @file GetterSetterTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 22, 2026
 *
 * @brief Verifies Simd128 getters/setters.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "SIMDTestSetup.h"

#include <array>
#include <falcon/simd/core/Simd128.h>


/**
 * @addtogroup T_SIMD128_Get_Set
 * @{
 */

// TODO: Remove Preprocessor after implementing individual simd paths
#if defined(FALCON_ENABLE_AVX512) || defined(FALCON_ENABLE_AVX2) || defined(FALCON_ENABLE_AVX) ||                      \
    defined(FALCON_ENABLE_SSE4) || defined(FALCON_ENABLE_SSE2)
namespace
{
    /**
     * @brief Test Fixture for Simd128 getter/setter operations.
     */
    template <typename T>
    class Simd128GetterSetterTests: public testing::Test
    {
    public:
        using Register = flcn::Simd128_t<typename T::Type, T::VALUE>;

        static constexpr auto max = std::numeric_limits<typename T::Type>::max();
        static constexpr auto min = std::numeric_limits<typename T::Type>::min();
        alignas(16) static constexpr std::array<typename T::Type, 16> data = { max, min, 0, 3,  5,  11, 15, 3,
                                                                               1,   2,   5, 12, 14, 3,  15, 12};

        /// Testing condition
        template <size_t... Index>
        Register setValuesAndGetRegister(std::index_sequence<Index...>)
        {
            Register reg;
            reg.set(data[Index]...);
            return reg;
        }
    };
    TYPED_TEST_SUITE(Simd128GetterSetterTests, Simd128RegisterTypeHints);
} // namespace


TYPED_TEST(Simd128GetterSetterTests, Set_FillsActiveLanesInCorrectOrder)
{
    using Type                       = typename TypeParam::Type;
    constexpr size_t Lane            = TypeParam::VALUE;
    static constexpr size_t MaxLanes = 16 / sizeof(Type);

    /// Grab the register prefilled with values using set
    auto reg = this->setValuesAndGetRegister(std::make_index_sequence<Lane>{});

    alignas(16) std::array<Type, MaxLanes> result{};
    reg.store(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(result[i], this->data[i]);
    }
}



TYPED_TEST(Simd128GetterSetterTests, Set_FillsUnoccupiedSpaceWithZeroes)
{
    using Type                       = typename TypeParam::Type;
    constexpr size_t Lane            = TypeParam::VALUE;
    static constexpr size_t MaxLanes = 16 / sizeof(Type);

    // If the register is perfectly full (e.g., 4 floats), there is no space to pad.
    // We can tell GTest to automatically skip this specific matrix combination!
    if constexpr (Lane == MaxLanes)
    {
        GTEST_SKIP() << "Register is fully occupied, skipping zero-padding test.";
    }
    else
    {
        auto reg = this->setValuesAndGetRegister(std::make_index_sequence<Lane>{});

        alignas(16) std::array<Type, MaxLanes> result{};
        reg.store(result.data());


        for (size_t i = Lane; i < MaxLanes; ++i)
        {
            EXPECT_EQ(result[i], static_cast<Type>(0));
        }
    }
}


TEST(Simd128GetterSetterTests, Set_CanTakeParametersLessThanLaneSize)
{
    using Type            = uint8_t;
    constexpr size_t Lane = 8;
    flcn::Simd128_t<Type, Lane> reg{};

    reg.set(static_cast<Type>(1), static_cast<Type>(2), static_cast<Type>(3), static_cast<Type>(4),
            static_cast<Type>(5), static_cast<Type>(6), static_cast<Type>(7));
    alignas(16) std::array<Type, Lane> result;
    reg.store(result.data());

    EXPECT_EQ(1, result[0]);
    EXPECT_EQ(2, result[1]);
    EXPECT_EQ(3, result[2]);
    EXPECT_EQ(4, result[3]);
    EXPECT_EQ(5, result[4]);
    EXPECT_EQ(6, result[5]);
    EXPECT_EQ(7, result[6]);
}



TYPED_TEST(Simd128GetterSetterTests, SetZero_FillsTheLanesWithZeroes)
{
    using Type            = typename TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    auto reg = flcn::Simd128_t<Type, Lane>();
    reg.setZero();

    alignas(16) std::array<Type, Lane> result{};
    reg.store(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(static_cast<Type>(0), result[i]);
    }
}


TYPED_TEST(Simd128GetterSetterTests, SetOne_FillsTheLanesWithOnes)
{
    using Type            = typename TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;
    constexpr auto one    = getAllOnes<Type>();

    auto reg = flcn::Simd128_t<Type, Lane>();
    reg.setOne();

    alignas(16) std::array<Type, Lane> result{};
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
TYPED_TEST(Simd128GetterSetterTests, GetAt_ReturnsTheValueAtGivenIndex)
{
    constexpr size_t Lane = TypeParam::VALUE;
    auto reg              = this->setValuesAndGetRegister(std::make_index_sequence<Lane>{});

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(this->data[i], reg.getAt(i));
    }
}


TYPED_TEST(Simd128GetterSetterTests, ExtractFirst_ReturnsTheValueAtZerothIndex)
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
TYPED_TEST(Simd128GetterSetterTests, SetAt_SetsTheValueAtAppropriateIndex)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    flcn::Simd128_t<Type, Lane> reg;
    reg.setZero();

    for (size_t i = 0; i < Lane; ++i)
    {
        reg.setAt(i, this->max);
        EXPECT_ANY_EQ(this->max, reg.getAt(i));
    }
}


TEST(Simd128GetterSetterTests, Integrals_Naive_ReturnsDefaultRegister)
{
    flcn::Simd128_t<int32_t, 4> reg{ 1, 2, 3, 4 };

    const auto naiveReg = reg.naive();

    alignas(16) std::array<int, 4> data{};
    _mm_store_si128(reinterpret_cast<__m128i*>(data.data()), naiveReg);

    EXPECT_ANY_EQ(1, data[0]);
    EXPECT_ANY_EQ(2, data[1]);
    EXPECT_ANY_EQ(3, data[2]);
    EXPECT_ANY_EQ(4, data[3]);
}


TEST(Simd128GetterSetterTests, Float_Naive_ReturnsDefaultRegister)
{
    flcn::Simd128_t<float, 4> reg{ 1, 2, 3, 4 };

    const auto naiveReg = reg.naive();

    alignas(16) std::array<float, 4> data{};
    _mm_store_ps(data.data(), naiveReg);

    EXPECT_ANY_EQ(1.0f, data[0]);
    EXPECT_ANY_EQ(2.0f, data[1]);
    EXPECT_ANY_EQ(3.0f, data[2]);
    EXPECT_ANY_EQ(4.0f, data[3]);
}


TEST(Simd128GetterSetterTests, Double_Naive_ReturnsDefaultRegister)
{
    flcn::Simd128_t<double, 2> reg{ 1, 2 };

    const auto naiveReg = reg.naive();

    alignas(16) std::array<double, 2> data{};
    _mm_store_pd(data.data(), naiveReg);

    EXPECT_ANY_EQ(1.0, data[0]);
    EXPECT_ANY_EQ(2.0, data[1]);
}


/// @test Verify that *reg returns the default internal register for integrals.
TEST(Simd128GetterSetterTests, UnaryTimesOperator_IntegralRegister_ReturnsDefaultRegister)
{
    flcn::Simd128_t<int32_t, 4> reg{ 1, 2, 3, 4 };

    const auto naiveReg = *reg;

    alignas(16) std::array<int, 4> data{};
    _mm_store_si128(reinterpret_cast<__m128i*>(data.data()), naiveReg);

    EXPECT_ANY_EQ(1, data[0]);
    EXPECT_ANY_EQ(2, data[1]);
    EXPECT_ANY_EQ(3, data[2]);
    EXPECT_ANY_EQ(4, data[3]);
}


/// @test Verify that *reg returns the default internal register for floats.
TEST(Simd128GetterSetterTests, UnaryTimesOperator_FloatRegister_ReturnsDefaultRegister)
{
    flcn::Simd128_t<float, 4> reg{ 1, 2, 3, 4 };

    const auto naiveReg = *reg;

    alignas(16) std::array<float, 4> data{};
    _mm_store_ps(data.data(), naiveReg);

    EXPECT_ANY_EQ(1.0f, data[0]);
    EXPECT_ANY_EQ(2.0f, data[1]);
    EXPECT_ANY_EQ(3.0f, data[2]);
    EXPECT_ANY_EQ(4.0f, data[3]);
}

/// @test Verify that *reg returns the default internal register for doubles.
TEST(Simd128GetterSetterTests, UnaryTimesOperator_DoubleRegister_ReturnsDefaultRegister)
{
    flcn::Simd128_t<double, 2> reg{ 1, 2 };

    const auto naiveReg = *reg;

    alignas(16) std::array<double, 2> data{};
    _mm_store_pd(data.data(), naiveReg);

    EXPECT_ANY_EQ(1.0, data[0]);
    EXPECT_ANY_EQ(2.0, data[1]);
}



using namespace simd::testing;

/// @test Verify that get<Index> (compile-time indexing) returns the element at the given index.
    #define TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(TestSuffix, Type, Lanes, Index)                           \
        TEST(Simd128ConstGetAtTests, ReturnsTheValue_##TestSuffix)                                                     \
        {                                                                                                              \
            constexpr auto max                                 = std::numeric_limits<Type>::max();                     \
            constexpr auto min                                 = std::numeric_limits<Type>::min();                     \
            alignas(16) constexpr std::array<Type, 16> dataArr = { max, min, 0, 3,  5,  11, 15, 3,                     \
                                                                   1,   2,   5, 12, 14, 3,  15, 12 };                  \
                                                                                                                       \
            flcn::Simd128_t<Type, Lanes> reg(dataArr.data());                                                          \
            EXPECT_ANY_EQ(dataArr[Index], reg.getAt<Index>());                                                         \
        }


// Unsigned Types
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_2Lanes_AtIndex0, U8, 2, 0)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_2Lanes_AtIndex1, U8, 2, 1)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_4Lanes_AtIndex0, U8, 4, 0)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_4Lanes_AtIndex1, U8, 4, 1)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_4Lanes_AtIndex2, U8, 4, 2)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_4Lanes_AtIndex3, U8, 4, 3)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_8Lanes_AtIndex0, U8, 8, 0)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_8Lanes_AtIndex1, U8, 8, 1)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_8Lanes_AtIndex2, U8, 8, 2)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_8Lanes_AtIndex3, U8, 8, 3)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_8Lanes_AtIndex4, U8, 8, 4)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_8Lanes_AtIndex5, U8, 8, 5)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_8Lanes_AtIndex6, U8, 8, 6)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_8Lanes_AtIndex7, U8, 8, 7)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex0, U8, 16, 0)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex1, U8, 16, 1)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex2, U8, 16, 2)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex3, U8, 16, 3)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex4, U8, 16, 4)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex5, U8, 16, 5)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex6, U8, 16, 6)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex7, U8, 16, 7)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex8, U8, 16, 8)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex9, U8, 16, 9)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex10, U8, 16, 10)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex11, U8, 16, 11)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex12, U8, 16, 12)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex13, U8, 16, 13)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex14, U8, 16, 14)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex15, U8, 16, 15)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_2Lanes_AtIndex0, U16, 2, 0)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_2Lanes_AtIndex1, U16, 2, 1)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_4Lanes_AtIndex0, U16, 4, 0)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_4Lanes_AtIndex1, U16, 4, 1)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_4Lanes_AtIndex2, U16, 4, 2)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_4Lanes_AtIndex3, U16, 4, 3)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_8Lanes_AtIndex0, U16, 8, 0)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_8Lanes_AtIndex1, U16, 8, 1)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_8Lanes_AtIndex2, U16, 8, 2)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_8Lanes_AtIndex3, U16, 8, 3)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_8Lanes_AtIndex4, U16, 8, 4)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_8Lanes_AtIndex5, U16, 8, 5)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_8Lanes_AtIndex6, U16, 8, 6)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint16_8Lanes_AtIndex7, U16, 8, 7)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint32_2Lanes_AtIndex0, U32, 2, 0)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint32_2Lanes_AtIndex1, U32, 2, 1)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint32_4Lanes_AtIndex0, U32, 4, 0)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint32_4Lanes_AtIndex1, U32, 4, 1)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint32_4Lanes_AtIndex2, U32, 4, 2)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint32_4Lanes_AtIndex3, U32, 4, 3)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint64_2Lanes_AtIndex0, U64, 2, 0)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Uint64_2Lanes_AtIndex1, U64, 2, 1)

// Signed Types
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_2Lanes_AtIndex0, I8, 2, 0)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_2Lanes_AtIndex1, I8, 2, 1)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_4Lanes_AtIndex0, I8, 4, 0)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_4Lanes_AtIndex1, I8, 4, 1)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_4Lanes_AtIndex2, I8, 4, 2)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_4Lanes_AtIndex3, I8, 4, 3)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_8Lanes_AtIndex0, I8, 8, 0)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_8Lanes_AtIndex1, I8, 8, 1)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_8Lanes_AtIndex2, I8, 8, 2)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_8Lanes_AtIndex3, I8, 8, 3)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_8Lanes_AtIndex4, I8, 8, 4)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_8Lanes_AtIndex5, I8, 8, 5)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_8Lanes_AtIndex6, I8, 8, 6)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_8Lanes_AtIndex7, I8, 8, 7)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex0, I8, 16, 0)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex1, I8, 16, 1)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex2, I8, 16, 2)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex3, I8, 16, 3)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex4, I8, 16, 4)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex5, I8, 16, 5)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex6, I8, 16, 6)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex7, I8, 16, 7)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex8, I8, 16, 8)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex9, I8, 16, 9)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex10, I8, 16, 10)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex11, I8, 16, 11)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex12, I8, 16, 12)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex13, I8, 16, 13)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex14, I8, 16, 14)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex15, I8, 16, 15)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_2Lanes_AtIndex0, I16, 2, 0)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_2Lanes_AtIndex1, I16, 2, 1)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_4Lanes_AtIndex0, I16, 4, 0)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_4Lanes_AtIndex1, I16, 4, 1)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_4Lanes_AtIndex2, I16, 4, 2)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_4Lanes_AtIndex3, I16, 4, 3)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_8Lanes_AtIndex0, I16, 8, 0)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_8Lanes_AtIndex1, I16, 8, 1)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_8Lanes_AtIndex2, I16, 8, 2)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_8Lanes_AtIndex3, I16, 8, 3)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_8Lanes_AtIndex4, I16, 8, 4)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_8Lanes_AtIndex5, I16, 8, 5)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_8Lanes_AtIndex6, I16, 8, 6)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int16_8Lanes_AtIndex7, I16, 8, 7)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int32_2Lanes_AtIndex0, I32, 2, 0)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int32_2Lanes_AtIndex1, I32, 2, 1)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int32_4Lanes_AtIndex0, I32, 4, 0)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int32_4Lanes_AtIndex1, I32, 4, 1)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int32_4Lanes_AtIndex2, I32, 4, 2)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int32_4Lanes_AtIndex3, I32, 4, 3)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int64_2Lanes_AtIndex0, I64, 2, 0)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(Int64_2Lanes_AtIndex1, I64, 2, 1)

// Floating Point Types
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(FP32_2Lanes_AtIndex0, FP32, 2, 0)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(FP32_2Lanes_AtIndex1, FP32, 2, 1)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(FP32_4Lanes_AtIndex0, FP32, 4, 0)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(FP32_4Lanes_AtIndex1, FP32, 4, 1)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(FP32_4Lanes_AtIndex2, FP32, 4, 2)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(FP32_4Lanes_AtIndex3, FP32, 4, 3)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(FP64_2Lanes_AtIndex0, FP64, 2, 0)
TEST_SIMD128_CONST_GET_AT_RETURNS_VALUE_AT_INDEX(FP64_2Lanes_AtIndex1, FP64, 2, 1)


/// @test Verify that get<Index> (compile-time indexing) returns the element at the given index.
    #define TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(TestSuffix, Type, Lanes, Index)                           \
        TEST(Simd128ConstSetAtTests, SetsTheValue_##TestSuffix)                                                        \
        {                                                                                                              \
            constexpr auto max                                 = std::numeric_limits<Type>::max();                     \
            constexpr auto min                                 = std::numeric_limits<Type>::min();                     \
            alignas(16) constexpr std::array<Type, 16> dataArr = { max, min, 0, 3,  5,  11, 15, 3,                     \
                                                                   1,   2,   5, 12, 14, 3,  15, 12 };                  \
                                                                                                                       \
            flcn::Simd128_t<Type, Lanes> reg{};                                                                        \
            reg.setAt<Index>(dataArr[Index]);                                                                          \
            EXPECT_ANY_EQ(dataArr[Index], reg.getAt<Index>());                                                         \
        }

// Unsigned Types
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_2Lanes_AtIndex0, U8, 2, 0)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_2Lanes_AtIndex1, U8, 2, 1)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_4Lanes_AtIndex0, U8, 4, 0)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_4Lanes_AtIndex1, U8, 4, 1)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_4Lanes_AtIndex2, U8, 4, 2)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_4Lanes_AtIndex3, U8, 4, 3)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_8Lanes_AtIndex0, U8, 8, 0)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_8Lanes_AtIndex1, U8, 8, 1)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_8Lanes_AtIndex2, U8, 8, 2)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_8Lanes_AtIndex3, U8, 8, 3)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_8Lanes_AtIndex4, U8, 8, 4)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_8Lanes_AtIndex5, U8, 8, 5)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_8Lanes_AtIndex6, U8, 8, 6)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_8Lanes_AtIndex7, U8, 8, 7)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex0, U8, 16, 0)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex1, U8, 16, 1)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex2, U8, 16, 2)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex3, U8, 16, 3)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex4, U8, 16, 4)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex5, U8, 16, 5)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex6, U8, 16, 6)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex7, U8, 16, 7)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex8, U8, 16, 8)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex9, U8, 16, 9)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex10, U8, 16, 10)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex11, U8, 16, 11)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex12, U8, 16, 12)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex13, U8, 16, 13)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex14, U8, 16, 14)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint8_16Lanes_AtIndex15, U8, 16, 15)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_2Lanes_AtIndex0, U16, 2, 0)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_2Lanes_AtIndex1, U16, 2, 1)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_4Lanes_AtIndex0, U16, 4, 0)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_4Lanes_AtIndex1, U16, 4, 1)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_4Lanes_AtIndex2, U16, 4, 2)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_4Lanes_AtIndex3, U16, 4, 3)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_8Lanes_AtIndex0, U16, 8, 0)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_8Lanes_AtIndex1, U16, 8, 1)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_8Lanes_AtIndex2, U16, 8, 2)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_8Lanes_AtIndex3, U16, 8, 3)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_8Lanes_AtIndex4, U16, 8, 4)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_8Lanes_AtIndex5, U16, 8, 5)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_8Lanes_AtIndex6, U16, 8, 6)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint16_8Lanes_AtIndex7, U16, 8, 7)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint32_2Lanes_AtIndex0, U32, 2, 0)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint32_2Lanes_AtIndex1, U32, 2, 1)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint32_4Lanes_AtIndex0, U32, 4, 0)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint32_4Lanes_AtIndex1, U32, 4, 1)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint32_4Lanes_AtIndex2, U32, 4, 2)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint32_4Lanes_AtIndex3, U32, 4, 3)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint64_2Lanes_AtIndex0, U64, 2, 0)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Uint64_2Lanes_AtIndex1, U64, 2, 1)

// Signed Types
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_2Lanes_AtIndex0, I8, 2, 0)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_2Lanes_AtIndex1, I8, 2, 1)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_4Lanes_AtIndex0, I8, 4, 0)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_4Lanes_AtIndex1, I8, 4, 1)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_4Lanes_AtIndex2, I8, 4, 2)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_4Lanes_AtIndex3, I8, 4, 3)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_8Lanes_AtIndex0, I8, 8, 0)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_8Lanes_AtIndex1, I8, 8, 1)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_8Lanes_AtIndex2, I8, 8, 2)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_8Lanes_AtIndex3, I8, 8, 3)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_8Lanes_AtIndex4, I8, 8, 4)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_8Lanes_AtIndex5, I8, 8, 5)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_8Lanes_AtIndex6, I8, 8, 6)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_8Lanes_AtIndex7, I8, 8, 7)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex0, I8, 16, 0)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex1, I8, 16, 1)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex2, I8, 16, 2)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex3, I8, 16, 3)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex4, I8, 16, 4)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex5, I8, 16, 5)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex6, I8, 16, 6)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex7, I8, 16, 7)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex8, I8, 16, 8)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex9, I8, 16, 9)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex10, I8, 16, 10)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex11, I8, 16, 11)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex12, I8, 16, 12)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex13, I8, 16, 13)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex14, I8, 16, 14)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int8_16Lanes_AtIndex15, I8, 16, 15)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_2Lanes_AtIndex0, I16, 2, 0)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_2Lanes_AtIndex1, I16, 2, 1)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_4Lanes_AtIndex0, I16, 4, 0)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_4Lanes_AtIndex1, I16, 4, 1)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_4Lanes_AtIndex2, I16, 4, 2)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_4Lanes_AtIndex3, I16, 4, 3)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_8Lanes_AtIndex0, I16, 8, 0)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_8Lanes_AtIndex1, I16, 8, 1)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_8Lanes_AtIndex2, I16, 8, 2)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_8Lanes_AtIndex3, I16, 8, 3)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_8Lanes_AtIndex4, I16, 8, 4)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_8Lanes_AtIndex5, I16, 8, 5)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_8Lanes_AtIndex6, I16, 8, 6)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int16_8Lanes_AtIndex7, I16, 8, 7)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int32_2Lanes_AtIndex0, I32, 2, 0)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int32_2Lanes_AtIndex1, I32, 2, 1)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int32_4Lanes_AtIndex0, I32, 4, 0)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int32_4Lanes_AtIndex1, I32, 4, 1)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int32_4Lanes_AtIndex2, I32, 4, 2)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int32_4Lanes_AtIndex3, I32, 4, 3)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int64_2Lanes_AtIndex0, I64, 2, 0)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(Int64_2Lanes_AtIndex1, I64, 2, 1)

// Floating Point Types
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(FP32_2Lanes_AtIndex0, FP32, 2, 0)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(FP32_2Lanes_AtIndex1, FP32, 2, 1)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(FP32_4Lanes_AtIndex0, FP32, 4, 0)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(FP32_4Lanes_AtIndex1, FP32, 4, 1)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(FP32_4Lanes_AtIndex2, FP32, 4, 2)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(FP32_4Lanes_AtIndex3, FP32, 4, 3)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(FP64_2Lanes_AtIndex0, FP64, 2, 0)
TEST_SIMD128_CONST_SET_AT_RETURNS_VALUE_AT_INDEX(FP64_2Lanes_AtIndex1, FP64, 2, 1)

#endif

/** @} */
