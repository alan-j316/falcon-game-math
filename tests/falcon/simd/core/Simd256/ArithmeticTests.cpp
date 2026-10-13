/**
 * @file LoadStoreTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 26, 2026
 *
 * @brief Verify @ref flcn::Simd256 arithmetics.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "SIMDTestSetup.h"

#include <array>



/**
 * @addtogroup T_SIMD256_Arithmetic
 * @{
 */

// TODO: Remove Preprocessor after implementing individual simd paths
#if defined(FALCON_ENABLE_AVX512) || defined(FALCON_ENABLE_AVX2) || defined(FALCON_ENABLE_AVX) ||                      \
    defined(FALCON_ENABLE_SSE4) || defined(FALCON_ENABLE_SSE2)
namespace
{
    /**
     * @brief Test Fixture for Simd256 arithmetic operations.
     */
    template <typename T>
    class Simd256ArithmeticTests: public testing::Test
    {
    public:
        static constexpr auto max = std::numeric_limits<typename T::Type>::max();
        static constexpr auto min = std::numeric_limits<typename T::Type>::min();
        // Note: Min is swapped with 1 in b to prevent SegFault when dividing
        std::array<typename T::Type, 32> a = { max, min, max, min, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12,
                                               max, min, max, min, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12 };
        std::array<typename T::Type, 32> b = {
            min == 0 ? 1 : min, max, max, min == 0 ? 1 : min, 2, 3, 3, 4, 2, 2, 6, 3, 7, 5, 4, 6,
            min == 0 ? 1 : min, max, max, min == 0 ? 1 : min, 2, 3, 3, 4, 2, 2, 6, 3, 7, 5, 4, 6
        };
        std::array<typename T::Type, 32> c        = { min, max, max, min, 15, 23, 21, 12, 17, 15, 13, 3, 2, 1, 6, 12,
                                                      min, max, max, min, 15, 23, 21, 12, 17, 15, 13, 3, 2, 1, 6, 12 };
        std::array<typename T::Type, 32> haddData = { max / 2, min + 4, max / 7, min + 12, 5,  11, 15, 3,
                                                      1,       2,       5,       11,       14, 3,  15, 12,
                                                      max / 2, min + 4, max / 7, min + 12, 5,  11, 15, 3,
                                                      1,       2,       5,       11,       14, 3,  15, 12 };
    };
    TYPED_TEST_SUITE(Simd256ArithmeticTests, Simd256RegisterTypeHints);

} // namespace


TYPED_TEST(Simd256ArithmeticTests, BinaryAddOperation_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(32) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = static_cast<Type>(i * 3);
        rhs[i]      = static_cast<Type>(i * 5);
        expected[i] = static_cast<Type>((i * 3) + (i * 5));
    }

    flcn::Simd256_t<Type, Lane> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    auto regRes = regA + regB;

    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}



TEST(Simd256ArithmeticTests, BinaryAddOperation_WorksWithMixedNumbers)
{

    alignas(32) std::array<float, 8> lhs{ 1, 5, -2, 0, -5, 27, 45, 19 }, rhs{ -1, 5, -5, -1, 5, -5, -1, 12 },
        expected{ 0, 10, -7, -1, 0, 22, 44, 31 }, result{};

    flcn::Simd256_t<float, 8> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    const auto regRes = regA + regB;
    regRes.storeAligned(result.data());


    for (size_t i = 0; i < 8; ++i)
    {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd256ArithmeticTests, CompoundAddOperation_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(32) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = static_cast<Type>(i * 3);
        rhs[i]      = static_cast<Type>(i * 5);
        expected[i] = static_cast<Type>((i * 3) + (i * 5));
    }

    flcn::Simd256_t<Type, Lane> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    regA += regB;
    regA.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TEST(Simd256ArithmeticTests, CompoundAddOperation_WorksWithMixedNumbers)
{

    alignas(32) std::array<float, 8> lhs{ 1, 5, -2, 0, -5, 27, 45, 19 }, rhs{ -1, 5, -5, -1, 5, -5, -1, 12 },
        expected{ 0, 10, -7, -1, 0, 22, 44, 31 }, result{};

    flcn::Simd256_t<float, 8> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    regA += regB;
    regA.storeAligned(result.data());


    for (size_t i = 0; i < 8; ++i)
    {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd256ArithmeticTests, BinarySubtractOperation_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(32) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = static_cast<Type>(i * 5);
        rhs[i]      = static_cast<Type>(i * 3);
        expected[i] = static_cast<Type>((i * 5) - (i * 3));
    }

    flcn::Simd256_t<Type, Lane> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    auto regRes = regA - regB;

    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TEST(Simd256ArithmeticTests, BinarySubtractOperation_WorksWithMixedNumbers)
{

    alignas(32) std::array<float, 8> lhs{ 1, 5, -2, 0, 11, -12, 13, -14 }, rhs{ -1, 5, -5, -1, 1, 5, -2, 0 },
        expected{ 2, 0, 3, 1, 10, -17, 15, -14 }, result{};

    flcn::Simd256_t<float, 8> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    const auto regRes = regA - regB;
    regRes.storeAligned(result.data());


    for (size_t i = 0; i < 8; ++i)
    {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd256ArithmeticTests, CompoundSubtractOperation_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(32) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = static_cast<Type>(i * 5);
        rhs[i]      = static_cast<Type>(i * 3);
        expected[i] = static_cast<Type>((i * 5) - (i * 3));
    }

    flcn::Simd256_t<Type, Lane> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    regA -= regB;
    regA.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TEST(Simd256ArithmeticTests, CompoundSubtractOperation_WorksWithMixedNumbers)
{

    alignas(32) std::array<float, 8> lhs{ 1, 5, -2, 0, 11, -12, 13, -14 }, rhs{ -1, 5, -5, -1, 1, 5, -2, 0 },
        expected{ 2, 0, 3, 1, 10, -17, 15, -14 }, result{};

    flcn::Simd256_t<float, 8> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    regA -= regB;
    regA.storeAligned(result.data());

    for (size_t i = 0; i < 8; ++i)
    {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}


/// @test Verify that unary minus return a new register with negated values(0-reg).
TYPED_TEST(Simd256ArithmeticTests, UnaryMinusOperator_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    Type min = std::numeric_limits<Type>::min();
    Type max = std::numeric_limits<Type>::max();
    alignas(32) std::array<Type, Lane> data{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {

        if (i % 2 == 0)
        {
            data[i] = static_cast<Type>(max - i * 2);
        }
        else
        {
            data[i] = static_cast<Type>(min + i * 2);
        }
    // Disable msvc from generating unsigned negation warnings
    #ifdef _MSC_VER
        #pragma warning(push)
        #pragma warning(disable : 4146)
    #endif
        expected[i] = static_cast<Type>(-data[i]);
    #ifdef _MSC_VER
        #pragma warning(pop)
    #endif
    }
    flcn::Simd256_t<Type, Lane> reg{ data };
    auto regRes = -reg;
    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd256ArithmeticTests, BinaryMultiplication_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(32) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = this->a[i];
        rhs[i]      = this->b[i];
        expected[i] = static_cast<Type>(rhs[i] * lhs[i]);
    }

    flcn::Simd256_t<Type, Lane> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    auto regRes = regA * regB;
    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TEST(Simd256ArithmeticTests, BinaryMultiplicationOperation_WorksWithMixedNumbers)
{
    alignas(32) std::array<float, 8> lhs{ 1, 5, -2, 0, -5, 4, 1, 10 }, rhs{ -1, 5, -5, -1, 6, 5, 13, 12 }, result{};
    const std::array<float, 8> expected{ -1, 25, 10, 0, -30, 20, 13, 120 };

    flcn::Simd256_t<float, 8> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    const auto regRes = regA * regB;
    regRes.storeAligned(result.data());


    for (size_t i = 0; i < 8; ++i)
    {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd256ArithmeticTests, CompoundMultiplication_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(32) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = this->a[i];
        rhs[i]      = this->b[i];
        expected[i] = static_cast<Type>(rhs[i] * lhs[i]);
    }

    flcn::Simd256_t<Type, Lane> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    regA *= regB;
    regA.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TEST(Simd256ArithmeticTests, CompoundMultiplicationOperation_WorksWithMixedNumbers)
{
    alignas(32) std::array<float, 8> lhs{ 1, 5, -2, 0, -5, 4, 1, 10 }, rhs{ -1, 5, -5, -1, 6, 5, 13, 12 }, result{};
    const std::array<float, 8> expected{ -1, 25, 10, 0, -30, 20, 13, 120 };

    flcn::Simd256_t<float, 8> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    regA *= regB;
    regA.storeAligned(result.data());

    for (size_t i = 0; i < 8; ++i)
    {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd256ArithmeticTests, DivReg_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(32) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = this->a[i];
        rhs[i]      = this->b[i];
        expected[i] = static_cast<Type>(lhs[i] / rhs[i]);
    }

    flcn::Simd256_t<Type, Lane> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    auto regRes = regA.divReg(regB);
    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


/// @test Verify that division using divReg function returns the correct value for the largest and smallest numbers.
TYPED_TEST(Simd256ArithmeticTests, DivReg_MaintainsPrecisionForAtUpperAndLowerLimits)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    constexpr auto largestNumber  = std::numeric_limits<Type>::max();
    constexpr auto smallestNumber = std::numeric_limits<Type>::min();

    alignas(32) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = this->a[i];
        rhs[i]      = this->b[i];
        expected[i] = static_cast<Type>(lhs[i] / rhs[i]);
    }
    lhs[0]      = largestNumber;
    lhs[1]      = smallestNumber;
    expected[0] = static_cast<Type>(lhs[0] / rhs[0]);
    expected[1] = static_cast<Type>(lhs[1] / rhs[1]);


    flcn::Simd256_t<Type, Lane> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    auto regRes = regA.divReg(regB);
    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TEST(Simd256ArithmeticTests, DivReg_WorksWithMixedNumbers)
{
    alignas(32) std::array<float, 8> lhs{ 25, -51, 13, 0, 12, 15, 44, 17 }, rhs{ -5, 25, 3, 16, 2, 3, 11, 2 }, result{};
    const std::array<float, 8> expected{ -5, -2.04f, 4.333333f, 0, 6, 5, 4, 8.5 };

    flcn::Simd256_t<float, 8> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    const auto regRes = regA.divReg(regB);
    regRes.storeAligned(result.data());


    for (size_t i = 0; i < 8; ++i)
    {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd256ArithmeticTests, BinaryDivideOperator_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;
    const Type divisor    = Type(5);

    alignas(32) std::array<Type, Lane> lhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = this->a[i];
        expected[i] = static_cast<Type>(lhs[i] / divisor);
    }

    flcn::Simd256_t<Type, Lane> regA;
    regA.loadAligned(lhs.data());

    auto regRes = regA / divisor;
    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


/// @test Verify that division using operator/ returns the correct value for the largest and smallest numbers.
TYPED_TEST(Simd256ArithmeticTests, BinaryDivideOperator_MaintainsPrecisionForAtUpperAndLowerLimits)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;
    const Type divisor    = Type(5);

    constexpr auto largestNumber  = std::numeric_limits<Type>::max();
    constexpr auto smallestNumber = std::numeric_limits<Type>::min();

    // We are swapping for the largest and smallest for the first two indices
    // since we have at least 2 lanes(256 / 64(max data type size)) we can safely inject those values
    alignas(32) std::array<Type, Lane> lhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = this->a[i];
        expected[i] = static_cast<Type>(lhs[i] / divisor);
    }
    lhs[0]      = largestNumber;
    lhs[1]      = smallestNumber;
    expected[0] = static_cast<Type>(lhs[0] / divisor);
    expected[1] = static_cast<Type>(lhs[1] / divisor);


    flcn::Simd256_t<Type, Lane> regA;
    regA.loadAligned(lhs.data());

    auto regRes = regA / divisor;
    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TEST(Simd256ArithmeticTests, BinaryDivideOperator_WorksWithMixedNumbers)
{
    alignas(32) std::array<float, 8> lhs{ 25, -51, 13, 0, 12, 15, 44, 17 }, result{};
    const std::array<float, 8> expected{ -6.25, 12.75, -3.25, -0.0, -3.0, -3.75, -11.0, -4.25 };

    flcn::Simd256_t<float, 8> regA;
    regA.loadAligned(lhs.data());

    const auto regRes = regA / -4;
    regRes.storeAligned(result.data());


    for (size_t i = 0; i < 8; ++i)
    {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd256ArithmeticTests, CompoundDivideOperator_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;
    const Type divisor    = Type(5);

    alignas(32) std::array<Type, Lane> lhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = this->a[i];
        expected[i] = static_cast<Type>(lhs[i] / divisor);
    }

    flcn::Simd256_t<Type, Lane> regA;
    regA.loadAligned(lhs.data());

    regA /= divisor;
    regA.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


/// @test Verify that division using operator/ returns the correct value for the largest and smallest numbers.
TYPED_TEST(Simd256ArithmeticTests, CompoundDivideOperator_MaintainsPrecisionForAtUpperAndLowerLimits)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;
    const Type divisor    = Type(5);

    constexpr auto largestNumber  = std::numeric_limits<Type>::max();
    constexpr auto smallestNumber = std::numeric_limits<Type>::min();

    // We are swapping for the largest and smallest for the first two indices
    // since we have at least 2 lanes(256 / 64(max data type size)) we can safely inject those values
    alignas(32) std::array<Type, Lane> lhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = this->a[i];
        expected[i] = static_cast<Type>(lhs[i] / divisor);
    }
    lhs[0]      = largestNumber;
    lhs[1]      = smallestNumber;
    expected[0] = static_cast<Type>(lhs[0] / divisor);
    expected[1] = static_cast<Type>(lhs[1] / divisor);


    flcn::Simd256_t<Type, Lane> regA;
    regA.loadAligned(lhs.data());

    regA /= divisor;
    regA.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TEST(Simd256ArithmeticTests, CompoundDivideOperator_WorksWithMixedNumbers)
{
    alignas(32) std::array<float, 8> lhs{ 25, -51, 13, 0, 12, 15, 44, 17 }, result{};
    const std::array<float, 8> expected{ -6.25, 12.75, -3.25, -0.0, -3.0, -3.75, -11.0, -4.25 };

    flcn::Simd256_t<float, 8> regA;
    regA.loadAligned(lhs.data());

    regA /= -4;
    regA.storeAligned(result.data());

    for (size_t i = 0; i < 8; ++i)
    {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}



/// @test Verify that fma operation returns a valid result (a * b + c).
TYPED_TEST(Simd256ArithmeticTests, FMA_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    // We are swapping for the largest and smallest for the first two indices
    // since we have at least 2 lanes(256 / 64(max data type size)) we can safely inject those values
    alignas(32) std::array<Type, Lane> a{}, b{}, c{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        a[i]        = this->a[i];
        b[i]        = this->b[i];
        c[i]        = this->c[i];
        expected[i] = static_cast<Type>(a[i] * b[i] + c[i]);
    }


    flcn::Simd256_t<Type, Lane> regA{ a }, regB{ b }, regC{ c };

    const auto resReg = regA.fma(regB, regC);
    resReg.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


// TYPED_TEST(Simd256ArithmeticTests, HorizontalAdd_ReturnsAValidResult)
// {
//     using Type            = TypeParam::Type;
//     constexpr size_t Lane = TypeParam::VALUE;
//
//     // We are swapping for the largest and smallest for the first two indices
//     // since we have at least 2 lanes(256 / 64(max data type size)) we can safely inject those values
//     alignas(32) std::array<Type, Lane> a{};
//     Type sum = 0;
//     for (size_t i = 0; i < Lane; ++i)
//     {
//         a[i] = this->haddData[i];
//         sum += a[i];
//     }
//     sum = static_cast<Type>(sum);
//
//     flcn::Simd256_t<Type, Lane> regA{ a };
//     const auto result = regA.horizontalAdd();
//     EXPECT_ANY_EQ(sum, result);
// }
//
//
// TYPED_TEST(Simd256ArithmeticTests, HorizontalSub_ReturnsAValidResult)
// {
//     using Type            = TypeParam::Type;
//     constexpr size_t Lane = TypeParam::VALUE;
//
//     alignas(32) std::array<Type, Lane> a{};
//     Type difference = 0;
//     for (size_t i = 0; i < Lane; ++i)
//     {
//         a[i] = this->haddData[i];
//         if (i == 0)
//         {
//             difference = a[i];
//         }
//         else
//         {
//             difference -= a[i];
//         }
//     }
//     difference = static_cast<Type>(difference);
//
//     flcn::Simd256_t<Type, Lane> regA{ a };
//     const auto result = regA.horizontalSub();
//     EXPECT_ANY_EQ(difference, result);
// }


#endif

/** @} */
