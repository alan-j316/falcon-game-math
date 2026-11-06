/**
 * @file AliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 14, 2026
 *
 * @brief @test Verify alias for @ref flcn::Mat2 returning correct data type.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2TestSetup.h"

#include <cstdint>



/**
 * @addtogroup T_FALCON_Mat2x2_Alias
 * @{
 */

namespace
{
    /** @test Verify @ref flcn::Mat2B has `int8_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat2B::value_type, int8_t> && "Mat2B must contain int8_t elements");
    static_assert(std::is_same_v<flcn::Mat2B, flcn::Mat2<int8_t>> && "Mat2B must be an alias of Mat2<int8_t>");


    /** @test Verify @ref flcn::Mat2UB has `uint8_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat2UB::value_type, uint8_t> && "Mat2UB must contain uint8_t elements");
    static_assert(std::is_same_v<flcn::Mat2UB, flcn::Mat2<uint8_t>> && "Mat2UB must be an alias of Mat2<uint8_t>");


    /** @test Verify @ref flcn::Mat2I has `int32_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat2I::value_type, int32_t> && "Mat2I must contain int32_t elements");
    static_assert(std::is_same_v<flcn::Mat2I, flcn::Mat2<int32_t>> && "Mat2I must be an alias of Mat2<int32_t>");


    /** @test Verify @ref flcn::Mat2U has `uint32_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat2U::value_type, uint32_t> && "Mat2U must contain uint32_t elements");
    static_assert(std::is_same_v<flcn::Mat2U, flcn::Mat2<uint32_t>> && "Mat2U must be an alias of Mat2<uint32_t>");


    /** @test Verify @ref flcn::Mat2F has `float` value_type. */
    static_assert(std::is_same_v<flcn::Mat2F::value_type, float> &&
                  "Mat2F must contain single precision floating point elements");
    static_assert(std::is_same_v<flcn::Mat2F, flcn::Mat2<float>> && "Mat2F must be an alias of Mat2<float>");


    /** @test Verify @ref flcn::Mat2LL has `int64_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat2LL::value_type, int64_t> && "Mat2LL must contain int64_t elements");
    static_assert(std::is_same_v<flcn::Mat2LL, flcn::Mat2<int64_t>> && "Mat2LL must be an alias of Mat2<int64_t>");


    /** @test Verify @ref flcn::Mat2D has `double` value_type. */
    static_assert(std::is_same_v<flcn::Mat2D::value_type, double> &&
                  "Mat2D must contain double precision floating point elements");
    static_assert(std::is_same_v<flcn::Mat2D, flcn::Mat2<double>> && "Mat2D must be an alias of Mat2<double>");


    /** @test Verify @ref flcn::Mat2ULL has `uint64_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat2ULL::value_type, uint64_t> && "Mat2ULL must contain uint64_t elements");
    static_assert(std::is_same_v<flcn::Mat2ULL, flcn::Mat2<uint64_t>> && "Mat2ULL must be an alias of Mat2<uint64_t>");

} // namespace

/** @} */
