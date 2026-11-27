#pragma once
/**
 * @file CommonSetup.h
 * @author Alan Abraham P Kochumon
 * @date Created on: April 20, 2026
 *
 * @brief Define all common test setup including types, headers includes, etc.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <concepts>
#include <falcon/core/traits/MathTraits.h>
#include <gtest/gtest.h>
#include <limits>
#include <type_traits>
#include <utility>
#include <vector>


#ifdef NONCOMPREHENSIVE
using SupportedTypes                 = ::testing::Types<int32_t, int64_t, uint8_t, bool, float, double>;
using SupportedArithmeticTypes       = ::testing::Types<int32_t, int64_t, uint8_t, float, double>;
using SupportedSignedArithmeticTypes = ::testing::Types<int32_t, int64_t, float, double>;
using SupportedIntegralTypes         = ::testing::Types<int32_t, int64_t, uint8_t>;
using SupportedFloatingPointTypes    = ::testing::Types<float, double>;
using SupportedArithmeticFloatingTypePair =
    ::testing::Types<std::pair<float, int32_t>, std::pair<float, int64_t>, std::pair<float, uint8_t>,
                     std::pair<float, double>, std::pair<double, int32_t>, std::pair<double, int64_t>,
                     std::pair<double, uint8_t>, std::pair<double, float>>;
using SupportedSignedArithmeticFloatingTypePair =
    ::testing::Types<std::pair<float, int32_t>, std::pair<float, int64_t>, std::pair<float, float>,
                     std::pair<double, int8_t>, std::pair<double, float>>;
#else

using SupportedTypes =
    testing::Types<int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t, bool, float, double>;
using SupportedArithmeticTypes =
    testing::Types<int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t, float, double>;
using SupportedSignedArithmeticTypes = testing::Types<int8_t, int16_t, int32_t, int64_t, float, double>;
using SupportedIntegralTypes = testing::Types<int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t>;
using SupportedFloatingPointTypes         = ::testing::Types<float, double>;
using SupportedArithmeticFloatingTypePair = ::testing::Types<
    std::pair<float, int8_t>, std::pair<float, int16_t>, std::pair<float, int32_t>, std::pair<float, int64_t>,
    std::pair<float, uint8_t>, std::pair<float, uint16_t>, std::pair<float, uint32_t>, std::pair<float, uint64_t>,
    std::pair<float, double>, std::pair<float, float>, std::pair<double, int8_t>, std::pair<double, int16_t>,
    std::pair<double, int32_t>, std::pair<double, int64_t>, std::pair<double, uint8_t>, std::pair<double, uint16_t>,
    std::pair<double, uint32_t>, std::pair<double, uint64_t>, std::pair<double, double>, std::pair<double, float>>;
using SupportedSignedArithmeticFloatingTypePair =
    ::testing::Types<std::pair<float, int8_t>, std::pair<float, int16_t>, std::pair<float, int32_t>,
                     std::pair<float, int64_t>, std::pair<float, float>, std::pair<double, int8_t>,
                     std::pair<double, int16_t>, std::pair<double, int32_t>, std::pair<double, int64_t>,
                     std::pair<double, double>, std::pair<double, float>>;
#endif


// TODO: Move to separate test utils file
namespace testutils
{
    /**
     * @brief Validates that two scalar values are equal within a defined numerical tolerance.
     *
     * @tparam T Numeric type of the values being compared.
     *
     * @param[in] expected The ground-truth reference value.
     * @param[in] actual   The value being evaluated.
     *
     * @note Uses GoogleTest macros. Triggers a non-fatal failure if the absolute difference
     *       between expected and actual exceeds the library's standard epsilon.
     */
    template <flcn::StrictArithmetic T>
    void EXPECT_MAG_EQ(T expected, T actual) // NOLINT
    {
        if constexpr (std::is_same_v<T, float>)
        {
            EXPECT_FLOAT_EQ(expected, actual);
        }
        else if constexpr (std::is_floating_point_v<T>)
        {
            EXPECT_DOUBLE_EQ(expected, actual);
        }
        else
        {
            EXPECT_EQ(expected, actual);
        }
    }

} // namespace testutils
