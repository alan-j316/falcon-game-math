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

#else

using SupportedTypes =
    testing::Types<int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t, bool, float, double>;
using SupportedArithmeticTypes =
    testing::Types<int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t, float, double>;
using SupportedSignedArithmeticTypes = ::testing::Types<int8_t, int16_t, int32_t, int64_t, float, double>;
using SupportedIntegralTypes = testing::Types<int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t>;
using SupportedFloatingPointTypes = testing::Types<float, double>;

#endif
