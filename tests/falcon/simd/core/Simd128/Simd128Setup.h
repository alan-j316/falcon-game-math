/**
 * @file Simd128Setup.h
 * @author Alan Abraham P Kochumon
 * @date Created on: November 22, 2026
 *
 * @brief Simd128 test setup.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "SIMDTestSetup.h"
#include <array>

/// @brief Test fixture for Simd128 bitwise operations.
template <typename T>
class Simd128BitwiseTests: public testing::Test // NOLINT
{
public:
    std::array<typename T::Type, 16> lhsData;
    std::array<typename T::Type, 16> rhsData;

protected:
    void SetUp() override
    {
        constexpr auto max = std::numeric_limits<typename T::Type>::max();
        constexpr auto min = std::numeric_limits<typename T::Type>::min();
        lhsData            = { max, min, min, max, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12 };
        rhsData            = { min, max, min, max, 5, 11, 3, 28, 2, 7, 5, 6, 4, 11, 4, 6 };
    }
};
TYPED_TEST_SUITE(Simd128BitwiseTests, Simd128RegisterTypeHints);
