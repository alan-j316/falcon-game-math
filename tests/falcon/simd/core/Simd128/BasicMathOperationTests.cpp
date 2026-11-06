/**
 * @file BasicMathOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 18, 2026
 *
 * @brief Verifies basic math operations like abs, min, max.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "SIMDTestSetup.h"

/**
 * @addtogroup T_SIMD128_Math
 * @{
 */

// TODO: Remove Preprocessor after implementing individual simd paths
#if defined(FALCON_ENABLE_AVX512) || defined(FALCON_ENABLE_AVX2) || defined(FALCON_ENABLE_AVX) ||                      \
    defined(FALCON_ENABLE_SSE4) || defined(FALCON_ENABLE_SSE2)
namespace
{
    /**
     * @brief Test Fixture for Simd128 basic math operations like min, max, abs etc.
     */
    template <typename T>
    class Simd128BasicMathTests: public testing::Test
    {
    public:
        static constexpr auto max          = std::numeric_limits<typename T::Type>::max();
        static constexpr auto min          = std::numeric_limits<typename T::Type>::min();
        std::array<typename T::Type, 16> a = { max, min, max, min, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12 };
        std::array<typename T::Type, 16> b = {
            min == 0 ? 1 : min, max, max, min == 0 ? 1 : min, 2, 3, 3, 4, 2, 2, 6, 3, 7, 5, 4, 6
        };
        std::array<typename T::Type, 16> absData, absExpected;

    protected:
        void SetUp() override
        {
            if constexpr (std::is_unsigned_v<typename T::Type>)
            {
                absData     = a;
                absExpected = a;
            }
            else
            {
                absData     = { max, min, max, min, -5, 11, -15, 0, -1, 2, -5, 12, -14, 3, -15, 12 };
            }
        }
    };
    TYPED_TEST_SUITE(Simd128BasicMathTests, Simd128RegisterTypeHints);

} // namespace



TYPED_TEST(Simd128BasicMathTests, Min_ReturnsARegisterWithMinimumValuesFromEitherRegister)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = this->a[i];
        rhs[i]      = this->b[i];
        expected[i] = std::min(lhs[i], rhs[i]);
    }

    flcn::Simd128_t<Type, Lane> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    auto regRes = flcn::min(regA, regB);

    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd128BasicMathTests, Max_ReturnsARegisterWithMaximumValuesFromEitherRegister)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = this->a[i];
        rhs[i]      = this->b[i];
        expected[i] = std::max(lhs[i], rhs[i]);
    }

    flcn::Simd128_t<Type, Lane> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    auto regRes = flcn::max(regA, regB);

    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd128BasicMathTests, MemberAbsFunction_ReturnsARegisterWithAbsoluteValues)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> data{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = this->absData[i];

        if constexpr (std::is_unsigned_v<Type>)
        {
            expected[i] = data[i];
        }
        else
        {
            expected[i] = data[i] < 0 ? data[i] * -1 : data[i];
        }
    }

    flcn::Simd128_t<Type, Lane> reg;
    reg.loadAligned(data.data());

    auto regRes = reg.abs();

    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


/// @test Verify that abs return the absolute value of data types from the register.
/// @note For unsigned types, it just return a copy of the same register.
TYPED_TEST(Simd128BasicMathTests, Abs_ReturnsARegisterWithAbsoluteValues)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> data{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = this->absData[i];

        if constexpr (std::is_unsigned_v<Type>)
        {
            expected[i] = data[i];
        }
        else
        {
            expected[i] = data[i] < 0 ? data[i] * -1 : data[i];
        }
    }

    flcn::Simd128_t<Type, Lane> reg;
    reg.loadAligned(data.data());

    auto regRes = flcn::abs(reg);

    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd128BasicMathTests, MemberSqrtFunction_ReturnsARegisterWithSquareRootValues)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> data{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = this->a[i];
        // For our simd sqrt, we clamp the values for integrals to zero
        auto clampedVal = data[i];
        if constexpr (std::is_integral_v<Type>)
        {
            clampedVal = std::max(Type(0), data[i]);
        }
        expected[i] = static_cast<Type>(std::sqrt(clampedVal));
    }

    flcn::Simd128_t<Type, Lane> reg;
    reg.loadAligned(data.data());

    auto regRes = reg.sqrt();
    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}

/// @test Verify that the non member variant of sqrt function returns the sqrt of the register values.
TYPED_TEST(Simd128BasicMathTests, Sqrt_ReturnsARegisterWithSquareRootValues)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> data{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        data[i]     = this->a[i];
        // For our simd sqrt, we clamp the values for integrals to zero
        auto clampedVal = data[i];
        if constexpr (std::is_integral_v<Type>)
        {
            clampedVal = std::max(Type(0), data[i]);
        }
        expected[i] = static_cast<Type>(std::sqrt(clampedVal));
    }

    flcn::Simd128_t<Type, Lane> reg;
    reg.loadAligned(data.data());

    auto regRes = flcn::sqrt(reg);
    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}



/// @test Verify that horizontal max return the maximum element from the register.
TYPED_TEST(Simd128BasicMathTests, HorizontalMax_ReturnsTheMaxValueFromTheRegister)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> data{};
    Type max = std::numeric_limits<Type>::min();
    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = this->absData[i];
        max     = std::max(max, data[i]);
    }

    flcn::Simd128_t<Type, Lane> reg{ data };

    auto res = reg.horizontalMax();

    EXPECT_ANY_EQ(max, res);
}

/// @test Verify that horizontal min return the minimum element from the register.
TYPED_TEST(Simd128BasicMathTests, HorizontalMin_ReturnsTheMaxValueFromTheRegister)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> data{};
    Type min = std::numeric_limits<Type>::max();
    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = this->absData[i];
        min     = std::min(min, data[i]);
    }

    flcn::Simd128_t<Type, Lane> reg{ data };

    auto res = reg.horizontalMin();

    EXPECT_ANY_EQ(min, res);
}


#endif

/** @} */
