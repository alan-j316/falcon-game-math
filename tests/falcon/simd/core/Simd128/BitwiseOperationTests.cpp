/**
 * @file BitwiseOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 01, 2026
 *
 * @brief Verify Simd128 bitwise operators(~, |, ^, &, ...)
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "SIMDTestSetup.h"

#include <array>
#include <bit>
#include <type_traits>

// TODO: Remove Preprocessor after implementing individual simd paths
#if defined(FALCON_ENABLE_AVX512EX) || defined(FALCON_ENABLE_AVX512) || defined(FALCON_ENABLE_AVX2) || defined(FALCON_ENABLE_AVX) ||                      \
    defined(FALCON_ENABLE_SSE4) || defined(FALCON_ENABLE_SSE2) || defined(FALCON_DISABLE_SIMD)

#include "Simd128Setup.h"

/**
 * @addtogroup T_SIMD128_Bit
 * @{
 */


/// @test Verifies unary NOT(~) returns a matrix with inverted bits.
TYPED_TEST(Simd128BitwiseTests, BitwiseNot_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> data{}, expected{}, result{};
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

    flcn::Simd128<Type, Lane> reg;
    reg.loadAligned(data.data());

    auto regRes = ~reg;

    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd128BitwiseTests, BitwiseAnd_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
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

    flcn::Simd128<Type, Lane> regA{}, regB{};
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    auto regRes = regA & regB;

    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd128BitwiseTests, BitwiseAndEquals_PerformsANDOperationInPlace)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
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

    flcn::Simd128<Type, Lane> regA{ lhs }, regB{ rhs };
    regA &= regB;

    regA.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd128BitwiseTests, BitwiseOr_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
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

    flcn::Simd128<Type, Lane> regA{}, regB{};
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    auto regRes = regA | regB;

    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd128BitwiseTests, BitwiseOrEquals_PerformsOROperationInPlace)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
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

    flcn::Simd128<Type, Lane> regA{ lhs }, regB{ rhs };
    regA |= regB;

    regA.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd128BitwiseTests, BitwiseXor_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
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

    flcn::Simd128<Type, Lane> regA{}, regB{};
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    auto regRes = regA ^ regB;

    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd128BitwiseTests, BitwiseXorEquals_PerformsXOROperationInPlace)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
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

    flcn::Simd128<Type, Lane> regA{ lhs }, regB{ rhs };
    regA ^= regB;

    regA.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


/// @test Verify that bitwise andnot(~a & b) returns a valid vector(register).
TYPED_TEST(Simd128BitwiseTests, BitwiseAndNot_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
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

    flcn::Simd128<Type, Lane> regA{}, regB{};
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
TYPED_TEST(Simd128BitwiseTests, HorizontalOR_ReturnsAValidScalar)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> data{};
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

    flcn::Simd128<Type, Lane> reg(data);

    auto result = reg.horizontalOr();
    EXPECT_ANY_EQ(expected, result);
}



/// @test Verifies that horizontal AND returns a scalar with bitwise AND applied.
TYPED_TEST(Simd128BitwiseTests, HorizontalAND_ReturnsAValidScalar)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> data{};
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

    flcn::Simd128<Type, Lane> reg(data);

    auto result = reg.horizontalAnd();
    EXPECT_ANY_EQ(expected, result);
}

/** @} */

#endif
