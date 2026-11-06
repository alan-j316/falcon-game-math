/**
 * @file BitwiseOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 28, 2026
 *
 * @brief Verify Simd256 bitwise operators(~, |, ^, &, ...)
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "SIMDTestSetup.h"

#include <array>
#include <bit>
#include <type_traits>

// TODO: Remove Preprocessor after implementing individual simd paths
#if defined(FALCON_ENABLE_AVX512) || defined(FALCON_ENABLE_AVX2) || defined(FALCON_ENABLE_AVX) ||                      \
    defined(FALCON_ENABLE_SSE4) || defined(FALCON_ENABLE_SSE2)


/**
 * @addtogroup T_SIMD256_Bit
 * @{
 */

namespace
{
    /// @brief Test fixture for Simd256 bitwise operations.
    template <typename T>
    class Simd256BitwiseOperationTests: public testing::Test
    {
    public:
        std::array<typename T::Type, 32> lhsData;
        std::array<typename T::Type, 32> rhsData;

    protected:
        void SetUp() override
        {
            constexpr auto max = std::numeric_limits<typename T::Type>::max();
            constexpr auto min = std::numeric_limits<typename T::Type>::min();
            lhsData            = { max, min, min, max, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12,
                                   max, min, min, max, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12 };
            rhsData            = { min, max, min, max, 5, 11, 3, 28, 2, 7, 5, 6, 4, 11, 4, 6,
                                   min, max, min, max, 5, 11, 3, 28, 2, 7, 5, 6, 4, 11, 4, 6 };
        }
    };
    TYPED_TEST_SUITE(Simd256BitwiseOperationTests, Simd256RegisterTypeHints);

} // namespace


/// @test Verifies unary NOT(~) returns a matrix with inverted bits.
TYPED_TEST(Simd256BitwiseOperationTests, BitwiseNot_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(32) std::array<Type, Lane> data{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = this->lhsData[i];
        // Since float and doubles don't have a NOT supported we need to bit cast it to integral types
        // and cast it back.
        if constexpr (std::is_same_v<double, Type>)
        {
            expected[i] = std::bit_cast<double>(~std::bit_cast<uint64_t>(this->lhsData[i]));
        }
        else if constexpr (std::is_same_v<float, Type>)
        {
            expected[i] = std::bit_cast<float>(~std::bit_cast<uint32_t>(this->lhsData[i]));
        }
        else
        {

            expected[i] = ~this->lhsData[i];
        }
    }

    flcn::Simd256_t<Type, Lane> reg;
    reg.loadAligned(data.data());

    auto regRes = ~reg;

    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd256BitwiseOperationTests, BitwiseAnd_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(32) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i] = this->lhsData[i];
        rhs[i] = this->rhsData[i];
        // Since float and doubles don't have a NOT supported we need to bit cast it to integral types
        // and cast it back.
        if constexpr (std::is_same_v<double, Type>)
        {
            expected[i] = std::bit_cast<double>(std::bit_cast<uint64_t>(lhs[i]) & std::bit_cast<uint64_t>(rhs[i]));
        }
        else if constexpr (std::is_same_v<float, Type>)
        {
            expected[i] = std::bit_cast<float>(std::bit_cast<uint32_t>(lhs[i]) & std::bit_cast<uint32_t>(rhs[i]));
        }
        else
        {
            expected[i] = lhs[i] & rhs[i];
        }
    }

    flcn::Simd256_t<Type, Lane> regA{}, regB{};
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    auto regRes = regA & regB;

    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd256BitwiseOperationTests, BitwiseAndEquals_PerformsANDOperationInPlace)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(32) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i] = this->lhsData[i];
        rhs[i] = this->rhsData[i];
        // Since float and doubles don't have a NOT supported we need to bit cast it to integral types
        // and cast it back.
        if constexpr (std::is_same_v<double, Type>)
        {
            expected[i] = std::bit_cast<double>(std::bit_cast<uint64_t>(lhs[i]) & std::bit_cast<uint64_t>(rhs[i]));
        }
        else if constexpr (std::is_same_v<float, Type>)
        {
            expected[i] = std::bit_cast<float>(std::bit_cast<uint32_t>(lhs[i]) & std::bit_cast<uint32_t>(rhs[i]));
        }
        else
        {
            expected[i] = lhs[i] & rhs[i];
        }
    }

    flcn::Simd256_t<Type, Lane> regA{}, regB{};
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());
    regA &= regB;

    regA.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd256BitwiseOperationTests, BitwiseOr_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(32) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i] = this->lhsData[i];
        rhs[i] = this->rhsData[i];
        // Since float and doubles don't have a NOT supported we need to bit cast it to integral types
        // and cast it back.
        if constexpr (std::is_same_v<double, Type>)
        {
            expected[i] = std::bit_cast<double>(std::bit_cast<uint64_t>(lhs[i]) | std::bit_cast<uint64_t>(rhs[i]));
        }
        else if constexpr (std::is_same_v<float, Type>)
        {
            expected[i] = std::bit_cast<float>(std::bit_cast<uint32_t>(lhs[i]) | std::bit_cast<uint32_t>(rhs[i]));
        }
        else
        {
            expected[i] = lhs[i] | rhs[i];
        }
    }

    flcn::Simd256_t<Type, Lane> regA{}, regB{};
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    auto regRes = regA | regB;

    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd256BitwiseOperationTests, BitwiseOrEquals_PerformsOROperationInPlace)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(32) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i] = this->lhsData[i];
        rhs[i] = this->rhsData[i];
        // Since float and doubles don't have a NOT supported we need to bit cast it to integral types
        // and cast it back.
        if constexpr (std::is_same_v<double, Type>)
        {
            expected[i] = std::bit_cast<double>(std::bit_cast<uint64_t>(lhs[i]) | std::bit_cast<uint64_t>(rhs[i]));
        }
        else if constexpr (std::is_same_v<float, Type>)
        {
            expected[i] = std::bit_cast<float>(std::bit_cast<uint32_t>(lhs[i]) | std::bit_cast<uint32_t>(rhs[i]));
        }
        else
        {
            expected[i] = lhs[i] | rhs[i];
        }
    }

    flcn::Simd256_t<Type, Lane> regA{}, regB{};
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());
    regA |= regB;

    regA.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd256BitwiseOperationTests, BitwiseXor_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(32) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i] = this->lhsData[i];
        rhs[i] = this->rhsData[i];
        // Since float and doubles don't have a NOT supported we need to bit cast it to integral types
        // and cast it back.
        if constexpr (std::is_same_v<double, Type>)
        {
            expected[i] = std::bit_cast<double>(std::bit_cast<uint64_t>(lhs[i]) ^ std::bit_cast<uint64_t>(rhs[i]));
        }
        else if constexpr (std::is_same_v<float, Type>)
        {
            expected[i] = std::bit_cast<float>(std::bit_cast<uint32_t>(lhs[i]) ^ std::bit_cast<uint32_t>(rhs[i]));
        }
        else
        {
            expected[i] = lhs[i] ^ rhs[i];
        }
    }

    flcn::Simd256_t<Type, Lane> regA{}, regB{};
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    auto regRes = regA ^ regB;

    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd256BitwiseOperationTests, BitwiseXorEquals_PerformsXOROperationInPlace)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(32) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i] = this->lhsData[i];
        rhs[i] = this->rhsData[i];
        // Since float and doubles don't have a NOT supported we need to bit cast it to integral types
        // and cast it back.
        if constexpr (std::is_same_v<double, Type>)
        {
            expected[i] = std::bit_cast<double>(std::bit_cast<uint64_t>(lhs[i]) ^ std::bit_cast<uint64_t>(rhs[i]));
        }
        else if constexpr (std::is_same_v<float, Type>)
        {
            expected[i] = std::bit_cast<float>(std::bit_cast<uint32_t>(lhs[i]) ^ std::bit_cast<uint32_t>(rhs[i]));
        }
        else
        {
            expected[i] = lhs[i] ^ rhs[i];
        }
    }

    flcn::Simd256_t<Type, Lane> regA{}, regB{};
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());
    regA ^= regB;

    regA.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


/// @test Verify that bitwise andnot(~a & b) returns a valid vector(register).
TYPED_TEST(Simd256BitwiseOperationTests, BitwiseAndNot_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(32) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i] = this->lhsData[i];
        rhs[i] = this->rhsData[i];
        // Since float and doubles don't have a NOT supported we need to bit cast it to integral types
        // and cast it back.
        if constexpr (std::is_same_v<double, Type>)
        {
            expected[i] = std::bit_cast<double>(~std::bit_cast<uint64_t>(lhs[i]) & std::bit_cast<uint64_t>(rhs[i]));
        }
        else if constexpr (std::is_same_v<float, Type>)
        {
            expected[i] = std::bit_cast<float>(~std::bit_cast<uint32_t>(lhs[i]) & std::bit_cast<uint32_t>(rhs[i]));
        }
        else
        {
            expected[i] = ~lhs[i] & rhs[i];
        }
    }

    flcn::Simd256_t<Type, Lane> regA{}, regB{};
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    auto regRes = regA.andNot(regB);

    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


/// @test Verifies that horizontal OR returns a scalar with bitwise OR applied.
TYPED_TEST(Simd256BitwiseOperationTests, HorizontalOR_ReturnsAValidScalar)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(32) std::array<Type, Lane> data{};
    Type expected{};
    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = this->lhsData[i];
        // Since float and doubles don't have a NOT supported we need to bit cast it to integral types
        // and cast it back.
        if constexpr (std::is_same_v<double, Type>)
        {
            expected =
                std::bit_cast<double>(std::bit_cast<uint64_t>(this->lhsData[i]) | std::bit_cast<uint64_t>(expected));
        }
        else if constexpr (std::is_same_v<float, Type>)
        {
            expected =
                std::bit_cast<float>(std::bit_cast<uint32_t>(this->lhsData[i]) | std::bit_cast<uint32_t>(expected));
        }
        else
        {
            expected |= this->lhsData[i];
        }
    }

    flcn::Simd256_t<Type, Lane> reg(data);

    auto result = reg.horizontalOr();
    EXPECT_ANY_EQ(expected, result);
}


/// @test Verifies that horizontal AND returns a scalar with bitwise AND applied.
TYPED_TEST(Simd256BitwiseOperationTests, HorizontalAND_ReturnsAValidScalar)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(32) std::array<Type, Lane> data{};
    Type expected{};
    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = this->lhsData[i];
        // Since float and doubles don't have a NOT supported we need to bit cast it to integral types
        // and cast it back.
        if constexpr (std::is_same_v<double, Type>)
        {
            expected =
                std::bit_cast<double>(std::bit_cast<uint64_t>(this->lhsData[i]) & std::bit_cast<uint64_t>(expected));
        }
        else if constexpr (std::is_same_v<float, Type>)
        {
            expected =
                std::bit_cast<float>(std::bit_cast<uint32_t>(this->lhsData[i]) & std::bit_cast<uint32_t>(expected));
        }
        else
        {
            expected &= this->lhsData[i];
        }
    }

    flcn::Simd256_t<Type, Lane> reg(data);

    auto result = reg.horizontalAnd();
    EXPECT_ANY_EQ(expected, result);
}



/**************************************
 *        BITWISE SHIFT TESTS         *
 **************************************/

// Suppress boundary warning for bitshift overflow
    #ifdef _MSC_VER
        #pragma warning(push)
        #pragma warning(disable : 4333) // Shifting too much(compliance to this will require rewriting test cases)
        #pragma warning(disable : 4293) // shift count negative or too big, undefined behavior
    #endif
    #ifdef __clang__
        #pragma clang diagnostic push
        #pragma clang diagnostic ignored "-Wshift-count-overflow"
    #endif

/// @test Verify that bitwise operator<< returns a valid vector(register).
    #define TEST_SIMD256_SHIFT_LEFT_WITH_DIFFERENT_SHIFT_SIZES(ShiftAmount)                                            \
        TYPED_TEST(Simd256BitwiseOperationTests, ShiftLeft_ReturnsAValidResult_WhenShiftedBy##ShiftAmount)             \
        {                                                                                                              \
            using Type            = TypeParam::Type;                                                                   \
            constexpr size_t Lane = TypeParam::VALUE;                                                                  \
                                                                                                                       \
            alignas(32) std::array<Type, Lane> data{}, expected{}, result{};                                           \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                data[i] = this->lhsData[i];                                                                            \
                if constexpr (std::is_same_v<double, Type>)                                                            \
                {                                                                                                      \
                    expected[i] =                                                                                      \
                        std::bit_cast<double>(std::bit_cast<uint64_t>(data[i]) << static_cast<uint64_t>(ShiftAmount)); \
                }                                                                                                      \
                else if constexpr (std::is_same_v<float, Type>)                                                        \
                {                                                                                                      \
                    expected[i] =                                                                                      \
                        std::bit_cast<float>(std::bit_cast<uint32_t>(data[i]) << static_cast<uint32_t>(ShiftAmount));  \
                }                                                                                                      \
                else                                                                                                   \
                {                                                                                                      \
                    expected[i] = static_cast<Type>(data[i] << ShiftAmount);                                           \
                }                                                                                                      \
            }                                                                                                          \
                                                                                                                       \
            flcn::Simd256_t<Type, Lane> reg{ data };                                                                   \
                                                                                                                       \
            auto regRes = reg << ShiftAmount;                                                                          \
            regRes.storeAligned(result.data());                                                                        \
                                                                                                                       \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                EXPECT_ANY_EQ(expected[i], result[i]);                                                                 \
            }                                                                                                          \
        }

TEST_SIMD256_SHIFT_LEFT_WITH_DIFFERENT_SHIFT_SIZES(0)
TEST_SIMD256_SHIFT_LEFT_WITH_DIFFERENT_SHIFT_SIZES(1)
TEST_SIMD256_SHIFT_LEFT_WITH_DIFFERENT_SHIFT_SIZES(2)
TEST_SIMD256_SHIFT_LEFT_WITH_DIFFERENT_SHIFT_SIZES(4)
TEST_SIMD256_SHIFT_LEFT_WITH_DIFFERENT_SHIFT_SIZES(7)
TEST_SIMD256_SHIFT_LEFT_WITH_DIFFERENT_SHIFT_SIZES(8)
TEST_SIMD256_SHIFT_LEFT_WITH_DIFFERENT_SHIFT_SIZES(12)
TEST_SIMD256_SHIFT_LEFT_WITH_DIFFERENT_SHIFT_SIZES(24)
TEST_SIMD256_SHIFT_LEFT_WITH_DIFFERENT_SHIFT_SIZES(31)



/// @test Verify that bitwise operator<<= returns a valid vector(register).
    #define TEST_SIMD256_SHIFT_LEFT_EQUALS_WITH_DIFFERENT_SHIFT_SIZES(ShiftAmount)                                     \
        TYPED_TEST(Simd256BitwiseOperationTests, ShiftLeftEquals_ReturnsAValidResult_WhenShiftedBy##ShiftAmount)       \
        {                                                                                                              \
            using Type            = TypeParam::Type;                                                                   \
            constexpr size_t Lane = TypeParam::VALUE;                                                                  \
                                                                                                                       \
            alignas(32) std::array<Type, Lane> data{}, expected{}, result{};                                           \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                data[i] = this->lhsData[i];                                                                            \
                if constexpr (std::is_same_v<double, Type>)                                                            \
                {                                                                                                      \
                    expected[i] =                                                                                      \
                        std::bit_cast<double>(std::bit_cast<uint64_t>(data[i]) << static_cast<uint64_t>(ShiftAmount)); \
                }                                                                                                      \
                else if constexpr (std::is_same_v<float, Type>)                                                        \
                {                                                                                                      \
                    expected[i] =                                                                                      \
                        std::bit_cast<float>(std::bit_cast<uint32_t>(data[i]) << static_cast<uint32_t>(ShiftAmount));  \
                }                                                                                                      \
                else                                                                                                   \
                {                                                                                                      \
                    expected[i] = static_cast<Type>(data[i] << ShiftAmount);                                           \
                }                                                                                                      \
            }                                                                                                          \
                                                                                                                       \
            flcn::Simd256_t<Type, Lane> reg{ data };                                                                   \
                                                                                                                       \
            reg <<= ShiftAmount;                                                                                       \
            reg.storeAligned(result.data());                                                                           \
                                                                                                                       \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                EXPECT_ANY_EQ(expected[i], result[i]);                                                                 \
            }                                                                                                          \
        }

TEST_SIMD256_SHIFT_LEFT_EQUALS_WITH_DIFFERENT_SHIFT_SIZES(0)
TEST_SIMD256_SHIFT_LEFT_EQUALS_WITH_DIFFERENT_SHIFT_SIZES(1)
TEST_SIMD256_SHIFT_LEFT_EQUALS_WITH_DIFFERENT_SHIFT_SIZES(2)
TEST_SIMD256_SHIFT_LEFT_EQUALS_WITH_DIFFERENT_SHIFT_SIZES(4)
TEST_SIMD256_SHIFT_LEFT_EQUALS_WITH_DIFFERENT_SHIFT_SIZES(7)
TEST_SIMD256_SHIFT_LEFT_EQUALS_WITH_DIFFERENT_SHIFT_SIZES(8)
TEST_SIMD256_SHIFT_LEFT_EQUALS_WITH_DIFFERENT_SHIFT_SIZES(12)
TEST_SIMD256_SHIFT_LEFT_EQUALS_WITH_DIFFERENT_SHIFT_SIZES(24)
TEST_SIMD256_SHIFT_LEFT_EQUALS_WITH_DIFFERENT_SHIFT_SIZES(31)


/// @test Verify that bitwise operator>> returns a valid vector(register).
    #define TEST_SIMD256_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(ShiftAmount)                                \
        TYPED_TEST(Simd256BitwiseOperationTests, ArithmeticShiftRight_ReturnsAValidResult_WhenShiftedBy##ShiftAmount)  \
        {                                                                                                              \
            using Type            = TypeParam::Type;                                                                   \
            constexpr size_t Lane = TypeParam::VALUE;                                                                  \
                                                                                                                       \
            alignas(32) std::array<Type, Lane> data{}, expected{}, result{};                                           \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                data[i] = this->lhsData[i];                                                                            \
                if constexpr (std::is_same_v<double, Type>)                                                            \
                {                                                                                                      \
                    expected[i] =                                                                                      \
                        std::bit_cast<double>(std::bit_cast<int64_t>(data[i]) >> static_cast<int64_t>(ShiftAmount));   \
                }                                                                                                      \
                else if constexpr (std::is_same_v<float, Type>)                                                        \
                {                                                                                                      \
                    expected[i] =                                                                                      \
                        std::bit_cast<float>(std::bit_cast<int32_t>(data[i]) >> static_cast<int32_t>(ShiftAmount));    \
                }                                                                                                      \
                else                                                                                                   \
                {                                                                                                      \
                    expected[i] = data[i] >> ShiftAmount;                                                              \
                }                                                                                                      \
            }                                                                                                          \
                                                                                                                       \
            flcn::Simd256_t<Type, Lane> reg{ data };                                                                   \
                                                                                                                       \
            auto regRes = reg >> ShiftAmount;                                                                          \
            regRes.storeAligned(result.data());                                                                        \
                                                                                                                       \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                EXPECT_ANY_EQ(expected[i], result[i]);                                                                 \
            }                                                                                                          \
        }



TEST_SIMD256_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(0)
TEST_SIMD256_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(1)
TEST_SIMD256_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(2)
TEST_SIMD256_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(4)
TEST_SIMD256_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(7)
TEST_SIMD256_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(8)
TEST_SIMD256_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(12)
TEST_SIMD256_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(24)
TEST_SIMD256_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(31)




/// @test Verify that bitwise operator>> returns a valid vector(register).
    #define TEST_SIMD256_SHIFT_RIGHT_EQUALS_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(ShiftAmount)                         \
        TYPED_TEST(Simd256BitwiseOperationTests,                                                                       \
                   ArithmeticShiftRightEquals_ReturnsAValidResult_WhenShiftedBy##ShiftAmount)                          \
        {                                                                                                              \
            using Type            = TypeParam::Type;                                                                   \
            constexpr size_t Lane = TypeParam::VALUE;                                                                  \
                                                                                                                       \
            alignas(32) std::array<Type, Lane> data{}, expected{}, result{};                                           \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                data[i] = this->lhsData[i];                                                                            \
                if constexpr (std::is_same_v<double, Type>)                                                            \
                {                                                                                                      \
                    expected[i] =                                                                                      \
                        std::bit_cast<double>(std::bit_cast<int64_t>(data[i]) >> static_cast<int64_t>(ShiftAmount));   \
                }                                                                                                      \
                else if constexpr (std::is_same_v<float, Type>)                                                        \
                {                                                                                                      \
                    expected[i] =                                                                                      \
                        std::bit_cast<float>(std::bit_cast<int32_t>(data[i]) >> static_cast<int32_t>(ShiftAmount));    \
                }                                                                                                      \
                else                                                                                                   \
                {                                                                                                      \
                    expected[i] = data[i] >> ShiftAmount;                                                              \
                }                                                                                                      \
            }                                                                                                          \
                                                                                                                       \
            flcn::Simd256_t<Type, Lane> reg{ data };                                                                   \
                                                                                                                       \
            reg >>= ShiftAmount;                                                                                       \
            reg.storeAligned(result.data());                                                                           \
                                                                                                                       \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                EXPECT_ANY_EQ(expected[i], result[i]);                                                                 \
            }                                                                                                          \
        }


TEST_SIMD256_SHIFT_RIGHT_EQUALS_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(0)
TEST_SIMD256_SHIFT_RIGHT_EQUALS_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(1)
TEST_SIMD256_SHIFT_RIGHT_EQUALS_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(2)
TEST_SIMD256_SHIFT_RIGHT_EQUALS_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(4)
TEST_SIMD256_SHIFT_RIGHT_EQUALS_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(7)
TEST_SIMD256_SHIFT_RIGHT_EQUALS_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(8)
TEST_SIMD256_SHIFT_RIGHT_EQUALS_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(12)
TEST_SIMD256_SHIFT_RIGHT_EQUALS_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(24)
TEST_SIMD256_SHIFT_RIGHT_EQUALS_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(31)



/// @test Verify that bitwise operator>> returns a valid vector(register).
/// @note There is no shift right logical in c++ operator, so we have to bit cast the values into their unsigned
///       variants and cast them back.
    #define TEST_SIMD256_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(ShiftAmount)                                   \
        TYPED_TEST(Simd256BitwiseOperationTests, LogicalShiftRight_ReturnsAValidResult_WhenShiftedBy##ShiftAmount)     \
        {                                                                                                              \
            using Type            = TypeParam::Type;                                                                   \
            constexpr size_t Lane = TypeParam::VALUE;                                                                  \
                                                                                                                       \
            alignas(32) std::array<Type, Lane> data{}, expected{}, result{};                                           \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                data[i] = this->lhsData[i];                                                                            \
                if constexpr (std::is_same_v<double, Type>)                                                            \
                {                                                                                                      \
                    expected[i] =                                                                                      \
                        std::bit_cast<double>(std::bit_cast<uint64_t>(data[i]) >> static_cast<uint64_t>(ShiftAmount)); \
                }                                                                                                      \
                else if constexpr (std::is_same_v<float, Type>)                                                        \
                {                                                                                                      \
                    expected[i] =                                                                                      \
                        std::bit_cast<float>(std::bit_cast<uint32_t>(data[i]) >> static_cast<uint32_t>(ShiftAmount));  \
                }                                                                                                      \
                else                                                                                                   \
                {                                                                                                      \
                    using UnsignedType = std::make_unsigned_t<Type>;                                                   \
                    expected[i]        = static_cast<Type>(static_cast<UnsignedType>(data[i]) >> ShiftAmount);         \
                }                                                                                                      \
            }                                                                                                          \
                                                                                                                       \
            flcn::Simd256_t<Type, Lane> reg{ data };                                                                   \
                                                                                                                       \
            auto resultReg = reg.shiftRightLogical(ShiftAmount);                                                       \
            resultReg.storeAligned(result.data());                                                                     \
                                                                                                                       \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                EXPECT_ANY_EQ(expected[i], result[i]);                                                                 \
            }                                                                                                          \
        }


TEST_SIMD256_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(0)
TEST_SIMD256_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(1)
TEST_SIMD256_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(2)
TEST_SIMD256_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(4)
TEST_SIMD256_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(7)
TEST_SIMD256_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(8)
TEST_SIMD256_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(12)
TEST_SIMD256_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(24)
TEST_SIMD256_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(31)


/// @test Verify that left shift operation with a compile time count returns a valid vector(register).
    #define TEST_SIMD256_CONST_SHIFT_LEFT_WITH_DIFFERENT_SHIFT_SIZES(ShiftAmount)                                      \
        TYPED_TEST(Simd256BitwiseOperationTests, ConstShiftLeft_ReturnsAValidResult_WhenShiftedBy##ShiftAmount)        \
        {                                                                                                              \
            using Type            = TypeParam::Type;                                                                   \
            constexpr size_t Lane = TypeParam::VALUE;                                                                  \
                                                                                                                       \
            alignas(32) std::array<Type, Lane> data{}, expected{}, result{};                                           \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                data[i] = this->lhsData[i];                                                                            \
                if constexpr (std::is_same_v<double, Type>)                                                            \
                {                                                                                                      \
                    expected[i] =                                                                                      \
                        std::bit_cast<double>(std::bit_cast<uint64_t>(data[i]) << static_cast<uint64_t>(ShiftAmount)); \
                }                                                                                                      \
                else if constexpr (std::is_same_v<float, Type>)                                                        \
                {                                                                                                      \
                    expected[i] =                                                                                      \
                        std::bit_cast<float>(std::bit_cast<uint32_t>(data[i]) << static_cast<uint32_t>(ShiftAmount));  \
                }                                                                                                      \
                else                                                                                                   \
                {                                                                                                      \
                    expected[i] = static_cast<Type>(data[i] << ShiftAmount);                                           \
                }                                                                                                      \
            }                                                                                                          \
                                                                                                                       \
            flcn::Simd256_t<Type, Lane> reg{ data };                                                                   \
                                                                                                                       \
            auto regRes = reg.template shiftLeft<ShiftAmount>();                                                       \
            regRes.storeAligned(result.data());                                                                        \
                                                                                                                       \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                EXPECT_ANY_EQ(expected[i], result[i]);                                                                 \
            }                                                                                                          \
        }

TEST_SIMD256_CONST_SHIFT_LEFT_WITH_DIFFERENT_SHIFT_SIZES(0)
TEST_SIMD256_CONST_SHIFT_LEFT_WITH_DIFFERENT_SHIFT_SIZES(1)
TEST_SIMD256_CONST_SHIFT_LEFT_WITH_DIFFERENT_SHIFT_SIZES(2)
TEST_SIMD256_CONST_SHIFT_LEFT_WITH_DIFFERENT_SHIFT_SIZES(4)
TEST_SIMD256_CONST_SHIFT_LEFT_WITH_DIFFERENT_SHIFT_SIZES(7)
TEST_SIMD256_CONST_SHIFT_LEFT_WITH_DIFFERENT_SHIFT_SIZES(8)
TEST_SIMD256_CONST_SHIFT_LEFT_WITH_DIFFERENT_SHIFT_SIZES(12)
TEST_SIMD256_CONST_SHIFT_LEFT_WITH_DIFFERENT_SHIFT_SIZES(24)
TEST_SIMD256_CONST_SHIFT_LEFT_WITH_DIFFERENT_SHIFT_SIZES(31)


/// @test Verify that arithmetic shift right operation with a compile time count returns a valid vector(register).
    #define TEST_SIMD256_CONST_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(ShiftAmount)                          \
        TYPED_TEST(Simd256BitwiseOperationTests,                                                                       \
                   ConstArithmeticShiftRight_ReturnsAValidResult_WhenShiftedBy##ShiftAmount)                           \
        {                                                                                                              \
            using Type            = TypeParam::Type;                                                                   \
            constexpr size_t Lane = TypeParam::VALUE;                                                                  \
                                                                                                                       \
            alignas(32) std::array<Type, Lane> data{}, expected{}, result{};                                           \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                data[i] = this->lhsData[i];                                                                            \
                if constexpr (std::is_same_v<double, Type>)                                                            \
                {                                                                                                      \
                    expected[i] =                                                                                      \
                        std::bit_cast<double>(std::bit_cast<int64_t>(data[i]) >> static_cast<int64_t>(ShiftAmount));   \
                }                                                                                                      \
                else if constexpr (std::is_same_v<float, Type>)                                                        \
                {                                                                                                      \
                    expected[i] =                                                                                      \
                        std::bit_cast<float>(std::bit_cast<int32_t>(data[i]) >> static_cast<int32_t>(ShiftAmount));    \
                }                                                                                                      \
                else                                                                                                   \
                {                                                                                                      \
                    expected[i] = data[i] >> ShiftAmount;                                                              \
                }                                                                                                      \
            }                                                                                                          \
                                                                                                                       \
            flcn::Simd256_t<Type, Lane> reg{ data };                                                                   \
                                                                                                                       \
            auto regRes = reg.template shiftRightArithmetic<ShiftAmount>();                                            \
            regRes.storeAligned(result.data());                                                                        \
                                                                                                                       \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                EXPECT_ANY_EQ(expected[i], result[i]);                                                                 \
            }                                                                                                          \
        }



TEST_SIMD256_CONST_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(0)
TEST_SIMD256_CONST_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(1)
TEST_SIMD256_CONST_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(2)
TEST_SIMD256_CONST_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(4)
TEST_SIMD256_CONST_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(7)
TEST_SIMD256_CONST_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(8)
TEST_SIMD256_CONST_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(12)
TEST_SIMD256_CONST_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(24)
TEST_SIMD256_CONST_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(31)


/// @test Verify that bitwise operator>> returns a valid vector(register).
/// @note There is no shift right logical in c++ operator, so we have to bit cast the values into their unsigned
///       variants and cast them back.
    #define TEST_SIMD256_CONST_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(ShiftAmount)                             \
        TYPED_TEST(Simd256BitwiseOperationTests,                                                                       \
                   ConstLogicalShiftRight_ReturnsAValidResult_WhenShiftedBy##ShiftAmount)                              \
        {                                                                                                              \
            using Type            = TypeParam::Type;                                                                   \
            constexpr size_t Lane = TypeParam::VALUE;                                                                  \
                                                                                                                       \
            alignas(32) std::array<Type, Lane> data{}, expected{}, result{};                                           \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                data[i] = this->lhsData[i];                                                                            \
                if constexpr (std::is_same_v<double, Type>)                                                            \
                {                                                                                                      \
                    expected[i] =                                                                                      \
                        std::bit_cast<double>(std::bit_cast<uint64_t>(data[i]) >> static_cast<uint64_t>(ShiftAmount)); \
                }                                                                                                      \
                else if constexpr (std::is_same_v<float, Type>)                                                        \
                {                                                                                                      \
                    expected[i] =                                                                                      \
                        std::bit_cast<float>(std::bit_cast<uint32_t>(data[i]) >> static_cast<uint32_t>(ShiftAmount));  \
                }                                                                                                      \
                else                                                                                                   \
                {                                                                                                      \
                    using UnsignedType = std::make_unsigned_t<Type>;                                                   \
                    expected[i]        = static_cast<Type>(static_cast<UnsignedType>(data[i]) >> ShiftAmount);         \
                }                                                                                                      \
            }                                                                                                          \
                                                                                                                       \
            flcn::Simd256_t<Type, Lane> reg{ data };                                                                   \
                                                                                                                       \
            auto resultReg = reg.template shiftRightLogical<ShiftAmount>();                                            \
            resultReg.storeAligned(result.data());                                                                     \
                                                                                                                       \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                EXPECT_ANY_EQ(expected[i], result[i]);                                                                 \
            }                                                                                                          \
        }


TEST_SIMD256_CONST_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(0)
TEST_SIMD256_CONST_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(1)
TEST_SIMD256_CONST_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(2)
TEST_SIMD256_CONST_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(4)
TEST_SIMD256_CONST_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(7)
TEST_SIMD256_CONST_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(8)
TEST_SIMD256_CONST_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(12)
TEST_SIMD256_CONST_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(24)
TEST_SIMD256_CONST_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(31)

    #ifdef __clang__
        #pragma clang diagnostic pop
    #endif
    #ifdef _MSC_VER
        #pragma warning(pop)
    #endif

/** @} */

#endif
