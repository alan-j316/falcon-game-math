/**
 * @file BitwiseOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 26, 2026
 *
 * @brief Verify Simd256 bitwise left shift operators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

/**
 * @addtogroup T_SIMD256_Bit
 * @{
 */

// TODO: Remove Preprocessor after implementing individual simd paths
#if defined(FALCON_ENABLE_AVX512EX) || defined(FALCON_ENABLE_AVX512) || defined(FALCON_ENABLE_AVX2) ||                 \
    defined(FALCON_ENABLE_AVX) || defined(FALCON_ENABLE_SSE4) || defined(FALCON_ENABLE_SSE2) ||                        \
    defined(FALCON_DISABLE_SIMD)

    #include "Simd256Setup.h"

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
        TYPED_TEST(Simd256BitwiseTests, ShiftLeft_ReturnsAValidResult_WhenShiftedBy##ShiftAmount)             \
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
            flcn::Simd256<Type, Lane> reg{ data };                                                                     \
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
        TYPED_TEST(Simd256BitwiseTests, ShiftLeftEquals_ReturnsAValidResult_WhenShiftedBy##ShiftAmount)       \
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
            flcn::Simd256<Type, Lane> reg{ data };                                                                     \
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




/// @test Verify that left shift operation with a compile time count returns a valid vector(register).
    #define TEST_SIMD256_CONST_SHIFT_LEFT_WITH_DIFFERENT_SHIFT_SIZES(ShiftAmount)                                      \
        TYPED_TEST(Simd256BitwiseTests, ConstShiftLeft_ReturnsAValidResult_WhenShiftedBy##ShiftAmount)        \
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
            flcn::Simd256<Type, Lane> reg{ data };                                                                     \
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
        TYPED_TEST(Simd256BitwiseTests,                                                                       \
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
            flcn::Simd256<Type, Lane> reg{ data };                                                                     \
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


    #ifdef __clang__
        #pragma clang diagnostic pop
    #endif
    #ifdef _MSC_VER
        #pragma warning(pop)
    #endif

#endif


/** @} */
