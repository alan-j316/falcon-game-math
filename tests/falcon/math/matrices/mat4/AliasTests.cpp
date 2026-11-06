/**
 * @file AliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 07, 2026
 *
 * @brief Verify alias for @ref flcn::Mat4 returning correct data type.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4TestSetup.h"

#include <cstdint>



/**
 * @addtogroup T_FALCON_Mat4x4_Alias
 * @{
 */

/** @test Verify that flcn::Mat4[] are alias wrappers for integral and floating-point 4D matrix. */
namespace
{
    /** @test Verify @ref flcn::Mat4B has `int8_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat4B::value_type, int8_t> && "Mat4B must contain int8_t elements");
    static_assert(std::is_same_v<flcn::Mat4B, flcn::Mat4<int8_t>> && "Mat4B must be an alias of Mat4<int8_t>");


    /** @test Verify @ref flcn::Mat4UB has `uint8_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat4UB::value_type, uint8_t> && "Mat4UB must contain uint8_t elements");
    static_assert(std::is_same_v<flcn::Mat4UB, flcn::Mat4<uint8_t>> && "Mat4UB must be an alias of Mat4<uint8_t>");


    /** @test Verify @ref flcn::Mat4I has `int32_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat4I::value_type, int32_t> && "Mat4I must contain int32_t elements");
    static_assert(std::is_same_v<flcn::Mat4I, flcn::Mat4<int32_t>> && "Mat4I must be an alias of Mat4<int32_t>");


    /** @test Verify @ref flcn::Mat4U has `uint32_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat4U::value_type, uint32_t> && "Mat4U must contain uint32_t elements");
    static_assert(std::is_same_v<flcn::Mat4U, flcn::Mat4<uint32_t>> && "Mat4U must be an alias of Mat4<uint32_t>");


    /** @test Verify @ref flcn::Mat4F has `float` value_type. */
    static_assert(std::is_same_v<flcn::Mat4F::value_type, float> &&
                  "Mat4F must contain single precision floating point elements");
    static_assert(std::is_same_v<flcn::Mat4F, flcn::Mat4<float>> && "Mat4F must be an alias of Mat4<float>");


    /** @test Verify @ref flcn::Mat4LL has `int64_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat4LL::value_type, int64_t> && "Mat4LL must contain int64_t elements");
    static_assert(std::is_same_v<flcn::Mat4LL, flcn::Mat4<int64_t>> && "Mat4LL must be an alias of Mat4<int64_t>");


    /** @test Verify @ref flcn::Mat4D has `double` value_type. */
    static_assert(std::is_same_v<flcn::Mat4D::value_type, double> &&
                  "Mat4D must contain double precision floating point elements");
    static_assert(std::is_same_v<flcn::Mat4D, flcn::Mat4<double>> && "Mat4D must be an alias of Mat4<double>");


    /** @test Verify @ref flcn::Mat4ULL has `uint64_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat4ULL::value_type, uint64_t> && "Mat4ULL must contain uint64_t elements");
    static_assert(std::is_same_v<flcn::Mat4ULL, flcn::Mat4<uint64_t>> && "Mat4ULL must be an alias of Mat4<uint64_t>");

} // namespace

/** @} */
