/**
 * @file AliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify alias for @ref flcn::CVec2 returning correct data type.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CVec2TestSetup.h"

#include <cstdint>



/**
 * @addtogroup T_FALCON_CVec2_Alias
 * @{
 */

/** @test Verify that flcn::CVec2[] are alias wrappers for integral and floating-point 2D vector. */
namespace
{
    /** @test Verify @ref flcn::CVec2B has `int8_t` value_type. */
    static_assert(std::is_same_v<flcn::CVec2B::value_type, int8_t> && "CVec2B must contain int8_t elements");
    static_assert(std::is_same_v<flcn::CVec2B, flcn::CVec2<int8_t>> && "CVec2B must be an alias of CVec2<int8_t>");


    /** @test Verify @ref flcn::CVec2UB has `uint8_t` value_type. */
    static_assert(std::is_same_v<flcn::CVec2UB::value_type, uint8_t> && "CVec2UB must contain uint8_t elements");
    static_assert(std::is_same_v<flcn::CVec2UB, flcn::CVec2<uint8_t>> && "CVec2UB must be an alias of CVec2<uint8_t>");


    /** @test Verify @ref flcn::CVec2I has `int32_t` value_type. */
    static_assert(std::is_same_v<flcn::CVec2I::value_type, int32_t> && "CVec2I must contain int32_t elements");
    static_assert(std::is_same_v<flcn::CVec2I, flcn::CVec2<int32_t>> && "CVec2I must be an alias of CVec2<int32_t>");


    /** @test Verify @ref flcn::CVec2U has `uint32_t` value_type. */
    static_assert(std::is_same_v<flcn::CVec2U::value_type, uint32_t> && "CVec2U must contain uint32_t elements");
    static_assert(std::is_same_v<flcn::CVec2U, flcn::CVec2<uint32_t>> && "CVec2U must be an alias of CVec2<uint32_t>");


    /** @test Verify @ref flcn::CVec2F has `float` value_type. */
    static_assert(std::is_same_v<flcn::CVec2F::value_type, float> &&
                  "CVec2F must contain single precision floating point elements");
    static_assert(std::is_same_v<flcn::CVec2F, flcn::CVec2<float>> && "CVec2F must be an alias of CVec2<float>");


    /** @test Verify @ref flcn::CVec2LL has `int64t` value_type. */
    static_assert(std::is_same_v<flcn::CVec2LL::value_type, int64_t> && "CVec2LL must contain int64_t elements");
    static_assert(std::is_same_v<flcn::CVec2LL, flcn::CVec2<int64_t>> && "CVec2LL must be an alias of CVec2<int64_t>");


    /** @test Verify @ref flcn::CVec2D has `double` value_type. */
    static_assert(std::is_same_v<flcn::CVec2D::value_type, double> &&
                  "CVec2D must contain double precision floating point elements");
    static_assert(std::is_same_v<flcn::CVec2D, flcn::CVec2<double>> && "CVec2D must be an alias of CVec2<double>");


    /** @test Verify @ref flcn::CVec2ULL has `uint64_t` value_type. */
    static_assert(std::is_same_v<flcn::CVec2ULL::value_type, uint64_t> && "CVec2ULL must contain uint64_t elements");
    static_assert(std::is_same_v<flcn::CVec2ULL, flcn::CVec2<uint64_t>> && "CVec2ULL must be an alias of CVec2<uint64_t>");
} // namespace

/** @} */
