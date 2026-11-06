#pragma once
/**
 * @file SIMDTestSetup.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 10, 2026
 *
 * @brief Test setups common to all @ref flcn::simd tests.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "utils/TypeUtils.h"

#include <bit>
#include <cmath>
#include <cstdint>
#include <falcon/simd/FalconSimd.h>
#include <gtest/gtest.h>
#include <limits>

using SupportedSIMDTypes =
    testing::Types<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t, double, float>;
using SupportedSIMDIntegralTypes =
    testing::Types<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t>;


template <typename T, size_t V>
struct SimdRegisterTypeMatrix
{
    using Type                    = T;
    static constexpr size_t VALUE = V;
};

template <typename T>
static constexpr T max = std::numeric_limits<T>::max();
template <typename T>
static constexpr T min = std::numeric_limits<T>::min();



using Simd128RegisterTypeHints = testing::Types<
    SimdRegisterTypeMatrix<uint8_t, 2>, SimdRegisterTypeMatrix<uint8_t, 4>, SimdRegisterTypeMatrix<uint8_t, 4>,
    SimdRegisterTypeMatrix<uint8_t, 8>, SimdRegisterTypeMatrix<uint8_t, 16>, SimdRegisterTypeMatrix<uint16_t, 2>,
    SimdRegisterTypeMatrix<uint16_t, 4>, SimdRegisterTypeMatrix<uint16_t, 8>, SimdRegisterTypeMatrix<uint32_t, 2>,
    SimdRegisterTypeMatrix<uint32_t, 4>, SimdRegisterTypeMatrix<uint64_t, 2>, SimdRegisterTypeMatrix<int8_t, 2>,
    SimdRegisterTypeMatrix<int8_t, 4>, SimdRegisterTypeMatrix<int8_t, 4>, SimdRegisterTypeMatrix<int8_t, 8>,
    SimdRegisterTypeMatrix<int8_t, 16>, SimdRegisterTypeMatrix<int16_t, 2>, SimdRegisterTypeMatrix<int16_t, 4>,
    SimdRegisterTypeMatrix<int16_t, 8>, SimdRegisterTypeMatrix<int32_t, 2>, SimdRegisterTypeMatrix<int32_t, 4>,
    SimdRegisterTypeMatrix<int64_t, 2>, SimdRegisterTypeMatrix<float, 2>, SimdRegisterTypeMatrix<float, 4>,
    SimdRegisterTypeMatrix<double, 2>>;

using Simd256RegisterTypeHints =
    testing::Types<SimdRegisterTypeMatrix<uint8_t, 32>, SimdRegisterTypeMatrix<uint16_t, 16>,
                   SimdRegisterTypeMatrix<uint32_t, 8>, SimdRegisterTypeMatrix<uint64_t, 4>,
                   SimdRegisterTypeMatrix<int8_t, 32>, SimdRegisterTypeMatrix<int16_t, 16>,
                   SimdRegisterTypeMatrix<int32_t, 8>, SimdRegisterTypeMatrix<int64_t, 4>,
                   SimdRegisterTypeMatrix<float, 8>, SimdRegisterTypeMatrix<double, 4>>;



template <typename T>
constexpr void expectAnyEq(const T& expected, const T& actual)
{
    if constexpr (std::is_floating_point_v<T>)
    {
        if (std::isnan(expected) || std::isnan(actual))
        {
            EXPECT_TRUE(std::isnan(expected) && std::isnan(actual));
        }
        else
        {

            if constexpr (std::is_same_v<T, double>)
            {
                EXPECT_DOUBLE_EQ(expected, actual);
            }
            else if constexpr (std::is_same_v<T, float>)
            {
                EXPECT_FLOAT_EQ(expected, actual);
            }
        }
    }
    else
    {
        EXPECT_EQ(expected, actual);
    }
}

/// @brief Wrapper around gtest macro for asserting equality(EXPECT) in a type agnostic manner.
#define EXPECT_ANY_EQ(expected, actual) expectAnyEq(expected, actual);


/// TODO: Add the below helpers to main library.
/// Helper that returns all 1s bitwise(1111..1111) for the given type.
template <typename T>
constexpr T getAllOnes()
{
    if constexpr (std::is_integral_v<T>)
    {
        return static_cast<T>(-1);
    }
    else if constexpr (sizeof(T) == 4)
    {
        return std::bit_cast<T>(0xFFFFFFFF);
    }
    else if constexpr (sizeof(T) == 8)
    {
        return std::bit_cast<T>(0xFFFFFFFFFFFFFFFF);
    }
    else
    {
        return 1; // Shouldn't hit this path.
    }
}


/// @brief Test whether a and b are equal bitwise.
template <typename T>
constexpr bool isEqualBitwise(T a, T b)
{
    if constexpr (std::is_same_v<T, double>)
    {
        return std::bit_cast<uint64_t>(a) == std::bit_cast<uint64_t>(b);
    }
    else if constexpr (std::is_same_v<T, float>)
    {
        return std::bit_cast<uint32_t>(a) == std::bit_cast<uint32_t>(b);
    }
    else
    {
        return a == b;
    }
}


namespace simd::testing
{
    /// A numeric primitive with all 1s(0b1111...111)
    /// @tparam T The numeric type of the primitive.
    template <typename T>
    constexpr T ONE = getAllOnes<T>();

    /// Alias for signed and unsigned types to facilitate easier testing.
    using U8   = uint8_t;
    using U16  = uint16_t;
    using U32  = uint32_t;
    using U64  = uint64_t;
    using I8   = int8_t;
    using I16  = int16_t;
    using I32  = int32_t;
    using I64  = int64_t;
    using FP32 = float;
    using FP64 = double;

    /// Alias for array for easier testing.
    template <typename T, size_t Size>
    using Array = std::array<T, Size>;
} // namespace simd::testing
