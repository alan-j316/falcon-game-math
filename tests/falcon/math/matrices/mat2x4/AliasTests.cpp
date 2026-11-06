/**
 * @file AliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify alias for @ref flcn::Mat2x4 returning correct data type.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2x4TestSetup.h"

#include <cstdint>



/**
 * @addtogroup T_FALCON_Mat2x4_Alias
 * @{
 */

/** @test Verify that flcn::Mat2x4[] are alias wrappers for integral and floating-point 4D matrix. */
namespace
{
    /** @test Verify @ref flcn::Mat2x4B has `int8_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat2x4B::value_type, int8_t> && "Mat2x4B must contain int8_t elements");
    static_assert(std::is_same_v<flcn::Mat2x4B, flcn::Mat2x4<int8_t>> && "Mat2x4B must be an alias of Mat2x4<int8_t>");


    /** @test Verify @ref flcn::Mat2x4UB has `uint8_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat2x4UB::value_type, uint8_t> && "Mat2x4UB must contain uint8_t elements");
    static_assert(std::is_same_v<flcn::Mat2x4UB, flcn::Mat2x4<uint8_t>> && "Mat2x4UB must be an alias of Mat2x4<uint8_t>");


    /** @test Verify @ref flcn::Mat2x4I has `int32_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat2x4I::value_type, int32_t> && "Mat2x4I must contain int32_t elements");
    static_assert(std::is_same_v<flcn::Mat2x4I, flcn::Mat2x4<int32_t>> && "Mat2x4I must be an alias of Mat2x4<int32_t>");


    /** @test Verify @ref flcn::Mat2x4U has `uint32_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat2x4U::value_type, uint32_t> && "Mat2x4U must contain uint32_t elements");
    static_assert(std::is_same_v<flcn::Mat2x4U, flcn::Mat2x4<uint32_t>> && "Mat2x4U must be an alias of Mat2x4<uint32_t>");


    /** @test Verify @ref flcn::Mat2x4F has `float` value_type. */
    static_assert(std::is_same_v<flcn::Mat2x4F::value_type, float> &&
                  "Mat2x4F must contain single precision floating point elements");
    static_assert(std::is_same_v<flcn::Mat2x4F, flcn::Mat2x4<float>> && "Mat2x4F must be an alias of Mat2x4<float>");


    /** @test Verify @ref flcn::Mat2x4LL has `int64_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat2x4LL::value_type, int64_t> && "Mat2x4LL must contain int64_t elements");
    static_assert(std::is_same_v<flcn::Mat2x4LL, flcn::Mat2x4<int64_t>> && "Mat2x4LL must be an alias of Mat2x4<int64_t>");


    /** @test Verify @ref flcn::Mat2x4D has `double` value_type. */
    static_assert(std::is_same_v<flcn::Mat2x4D::value_type, double> &&
                  "Mat2x4D must contain double precision floating point elements");
    static_assert(std::is_same_v<flcn::Mat2x4D, flcn::Mat2x4<double>> && "Mat2x4D must be an alias of Mat2x4<double>");


    /** @test Verify @ref flcn::Mat2x4ULL has `uint64_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat2x4ULL::value_type, uint64_t> && "Mat2x4ULL must contain uint64_t elements");
    static_assert(std::is_same_v<flcn::Mat2x4ULL, flcn::Mat2x4<uint64_t>> && "Mat2x4ULL must be an alias of Mat2x4<uint64_t>");

} // namespace

/** @} */
