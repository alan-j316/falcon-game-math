/**
 * @file AliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify alias for @ref flcn::Mat3x2 returning correct data type.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3x2TestSetup.h"

#include <cstdint>



/**
 * @addtogroup T_FALCON_Mat3x2_Alias
 * @{
 */

/** @test Verify that flcn::Mat3x2[] are alias wrappers for integral and floating-point 4D matrix. */
namespace
{
    /** @test Verify @ref flcn::Mat3x2B has `int8_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat3x2B::value_type, int8_t> && "Mat3x2B must contain int8_t elements");
    static_assert(std::is_same_v<flcn::Mat3x2B, flcn::Mat3x2<int8_t>> && "Mat3x2B must be an alias of Mat3x2<int8_t>");


    /** @test Verify @ref flcn::Mat3x2UB has `uint8_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat3x2UB::value_type, uint8_t> && "Mat3x2UB must contain uint8_t elements");
    static_assert(std::is_same_v<flcn::Mat3x2UB, flcn::Mat3x2<uint8_t>> && "Mat3x2UB must be an alias of Mat3x2<uint8_t>");


    /** @test Verify @ref flcn::Mat3x2I has `int32_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat3x2I::value_type, int32_t> && "Mat3x2I must contain int32_t elements");
    static_assert(std::is_same_v<flcn::Mat3x2I, flcn::Mat3x2<int32_t>> && "Mat3x2I must be an alias of Mat3x2<int32_t>");


    /** @test Verify @ref flcn::Mat3x2U has `uint32_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat3x2U::value_type, uint32_t> && "Mat3x2U must contain uint32_t elements");
    static_assert(std::is_same_v<flcn::Mat3x2U, flcn::Mat3x2<uint32_t>> && "Mat3x2U must be an alias of Mat3x2<uint32_t>");


    /** @test Verify @ref flcn::Mat3x2F has `float` value_type. */
    static_assert(std::is_same_v<flcn::Mat3x2F::value_type, float> &&
                  "Mat3x2F must contain single precision floating point elements");
    static_assert(std::is_same_v<flcn::Mat3x2F, flcn::Mat3x2<float>> && "Mat3x2F must be an alias of Mat3x2<float>");


    /** @test Verify @ref flcn::Mat3x2LL has `int64_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat3x2LL::value_type, int64_t> && "Mat3x2LL must contain int64_t elements");
    static_assert(std::is_same_v<flcn::Mat3x2LL, flcn::Mat3x2<int64_t>> && "Mat3x2LL must be an alias of Mat3x2<int64_t>");


    /** @test Verify @ref flcn::Mat3x2D has `double` value_type. */
    static_assert(std::is_same_v<flcn::Mat3x2D::value_type, double> &&
                  "Mat3x2D must contain double precision floating point elements");
    static_assert(std::is_same_v<flcn::Mat3x2D, flcn::Mat3x2<double>> && "Mat3x2D must be an alias of Mat3x2<double>");


    /** @test Verify @ref flcn::Mat3x2ULL has `uint64_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat3x2ULL::value_type, uint64_t> && "Mat3x2ULL must contain uint64_t elements");
    static_assert(std::is_same_v<flcn::Mat3x2ULL, flcn::Mat3x2<uint64_t>> && "Mat3x2ULL must be an alias of Mat3x2<uint64_t>");

} // namespace

/** @} */
