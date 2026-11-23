/**
* @file BitwiseOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 22, 2026
 *
 * @brief Verify Simd128 bitwise right shift operators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

/**
 * @addtogroup T_SIMD128_Bit
 * @{
 */

#include "Simd128Setup.h"

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

/// @test Verify that bitwise operator>> returns a valid vector(register).
    #define TEST_SIMD128_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(ShiftAmount)                                \
        TYPED_TEST(Simd128BitwiseTests, ArithmeticShiftRight_ReturnsAValidResult_WhenShiftedBy##ShiftAmount)  \
        {                                                                                                              \
            using Type            = TypeParam::Type;                                                                   \
            constexpr size_t Lane = TypeParam::VALUE;                                                                  \
                                                                                                                       \
            alignas(16) std::array<Type, Lane> data{}, expected{}, result{};                                           \
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
            flcn::Simd128_t<Type, Lane> reg{ data };                                                                   \
                                                                                                                       \
            auto regRes = reg >> ShiftAmount;                                                                          \
            regRes.storeAligned(result.data());                                                                        \
                                                                                                                       \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                EXPECT_ANY_EQ(expected[i], result[i]);                                                                 \
            }                                                                                                          \
        }

TEST_SIMD128_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(0)
TEST_SIMD128_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(1)
TEST_SIMD128_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(2)
TEST_SIMD128_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(4)
TEST_SIMD128_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(7)
TEST_SIMD128_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(8)
TEST_SIMD128_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(12)
TEST_SIMD128_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(24)
TEST_SIMD128_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(31)


/// @test Verify that bitwise operator>> returns a valid vector(register).
    #define TEST_SIMD128_SHIFT_RIGHT_EQUALS_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(ShiftAmount)                         \
        TYPED_TEST(Simd128BitwiseTests,                                                                       \
                   ArithmeticShiftRightEquals_ReturnsAValidResult_WhenShiftedBy##ShiftAmount)                          \
        {                                                                                                              \
            using Type            = TypeParam::Type;                                                                   \
            constexpr size_t Lane = TypeParam::VALUE;                                                                  \
                                                                                                                       \
            alignas(16) std::array<Type, Lane> data{}, expected{}, result{};                                           \
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
            flcn::Simd128_t<Type, Lane> reg{ data };                                                                   \
                                                                                                                       \
            reg >>= ShiftAmount;                                                                                       \
            reg.storeAligned(result.data());                                                                           \
                                                                                                                       \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                EXPECT_ANY_EQ(expected[i], result[i]);                                                                 \
            }                                                                                                          \
        }

TEST_SIMD128_SHIFT_RIGHT_EQUALS_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(0)
TEST_SIMD128_SHIFT_RIGHT_EQUALS_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(1)
TEST_SIMD128_SHIFT_RIGHT_EQUALS_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(2)
TEST_SIMD128_SHIFT_RIGHT_EQUALS_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(4)
TEST_SIMD128_SHIFT_RIGHT_EQUALS_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(7)
TEST_SIMD128_SHIFT_RIGHT_EQUALS_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(8)
TEST_SIMD128_SHIFT_RIGHT_EQUALS_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(12)
TEST_SIMD128_SHIFT_RIGHT_EQUALS_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(24)
TEST_SIMD128_SHIFT_RIGHT_EQUALS_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(31)



/// @test Verify that bitwise operator>> returns a valid vector(register).
/// @note There is no shift right logical in c++ operator, so we have to bit cast the values into their unsigned
///       variants and cast them back.
    #define TEST_SIMD128_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(ShiftAmount)                                   \
        TYPED_TEST(Simd128BitwiseTests, LogicalShiftRight_ReturnsAValidResult_WhenShiftedBy##ShiftAmount)     \
        {                                                                                                              \
            using Type            = TypeParam::Type;                                                                   \
            constexpr size_t Lane = TypeParam::VALUE;                                                                  \
                                                                                                                       \
            alignas(16) std::array<Type, Lane> data{}, expected{}, result{};                                           \
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
            flcn::Simd128_t<Type, Lane> reg{ data };                                                                   \
                                                                                                                       \
            auto resultReg = reg.shiftRightLogical(ShiftAmount);                                                       \
            resultReg.storeAligned(result.data());                                                                     \
                                                                                                                       \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                EXPECT_ANY_EQ(expected[i], result[i]);                                                                 \
            }                                                                                                          \
        }

TEST_SIMD128_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(0)
TEST_SIMD128_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(1)
TEST_SIMD128_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(2)
TEST_SIMD128_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(4)
TEST_SIMD128_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(7)
TEST_SIMD128_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(8)
TEST_SIMD128_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(12)
TEST_SIMD128_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(24)
TEST_SIMD128_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(31)


/// @test Verify that arithmetic shift right operation with a compile time count returns a valid vector(register).
    #define TEST_SIMD128_CONST_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(ShiftAmount)                          \
        TYPED_TEST(Simd128BitwiseTests,                                                                       \
                   ConstArithmeticShiftRight_ReturnsAValidResult_WhenShiftedBy##ShiftAmount)                           \
        {                                                                                                              \
            using Type            = TypeParam::Type;                                                                   \
            constexpr size_t Lane = TypeParam::VALUE;                                                                  \
                                                                                                                       \
            alignas(16) std::array<Type, Lane> data{}, expected{}, result{};                                           \
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
            flcn::Simd128_t<Type, Lane> reg{ data };                                                                   \
                                                                                                                       \
            auto regRes = reg.template shiftRightArithmetic<ShiftAmount>();                                            \
            regRes.storeAligned(result.data());                                                                        \
                                                                                                                       \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                EXPECT_ANY_EQ(expected[i], result[i]);                                                                 \
            }                                                                                                          \
        }

TEST_SIMD128_CONST_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(0)
TEST_SIMD128_CONST_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(1)
TEST_SIMD128_CONST_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(2)
TEST_SIMD128_CONST_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(4)
TEST_SIMD128_CONST_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(7)
TEST_SIMD128_CONST_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(8)
TEST_SIMD128_CONST_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(12)
TEST_SIMD128_CONST_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(24)
TEST_SIMD128_CONST_SHIFT_RIGHT_ARITHMETIC_WITH_DIFFERENT_SHIFT_SIZES(31)



/// @test Verify that bitwise operator>> returns a valid vector(register).
/// @note There is no shift right logical in c++ operator, so we have to bit cast the values into their unsigned
///       variants and cast them back.
    #define TEST_SIMD128_CONST_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(ShiftAmount)                             \
        TYPED_TEST(Simd128BitwiseTests,                                                                       \
                   ConstLogicalShiftRight_ReturnsAValidResult_WhenShiftedBy##ShiftAmount)                              \
        {                                                                                                              \
            using Type            = TypeParam::Type;                                                                   \
            constexpr size_t Lane = TypeParam::VALUE;                                                                  \
                                                                                                                       \
            alignas(16) std::array<Type, Lane> data{}, expected{}, result{};                                           \
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
            flcn::Simd128_t<Type, Lane> reg{ data };                                                                   \
                                                                                                                       \
            auto resultReg = reg.template shiftRightLogical<ShiftAmount>();                                            \
            resultReg.storeAligned(result.data());                                                                     \
                                                                                                                       \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                EXPECT_ANY_EQ(expected[i], result[i]);                                                                 \
            }                                                                                                          \
        }

TEST_SIMD128_CONST_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(0)
TEST_SIMD128_CONST_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(1)
TEST_SIMD128_CONST_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(2)
TEST_SIMD128_CONST_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(4)
TEST_SIMD128_CONST_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(7)
TEST_SIMD128_CONST_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(8)
TEST_SIMD128_CONST_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(12)
TEST_SIMD128_CONST_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(24)
TEST_SIMD128_CONST_SHIFT_RIGHT_LOGICAL_WITH_DIFFERENT_SHIFT_SIZES(31)


#ifdef __clang__
    #pragma clang diagnostic pop
#endif
#ifdef _MSC_VER
    #pragma warning(pop)
#endif

/** @} */
