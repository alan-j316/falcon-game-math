/**
 * @file AliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify alias for @ref flcn::Mat4x3 returning correct data type.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4x3TestSetup.h"

#include <cstdint>



/**
 * @addtogroup T_FALCON_Mat4x3_Alias
 * @{
 */

/** @test Verify that flcn::Mat4x3[] are alias wrappers for integral and floating-point 4D matrix. */
namespace
{
    /** @test Verify @ref flcn::Mat4x3B has `int8_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat4x3B::value_type, int8_t> && "Mat4x3B must contain int8_t elements");
    static_assert(std::is_same_v<flcn::Mat4x3B, flcn::Mat4x3<int8_t>> && "Mat4x3B must be an alias of Mat4x3<int8_t>");


    /** @test Verify @ref flcn::Mat4x3UB has `uint8_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat4x3UB::value_type, uint8_t> && "Mat4x3UB must contain uint8_t elements");
    static_assert(std::is_same_v<flcn::Mat4x3UB, flcn::Mat4x3<uint8_t>> &&
                  "Mat4x3UB must be an alias of Mat4x3<uint8_t>");


    /** @test Verify @ref flcn::Mat4x3I has `int32_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat4x3I::value_type, int32_t> && "Mat4x3I must contain int32_t elements");
    static_assert(std::is_same_v<flcn::Mat4x3I, flcn::Mat4x3<int32_t>> && "Mat4x3I must be an alias of Mat4x3<int32_t>");


    /** @test Verify @ref flcn::Mat4x3U has `uint32_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat4x3U::value_type, uint32_t> && "Mat4x3U must contain uint32_t elements");
    static_assert(std::is_same_v<flcn::Mat4x3U, flcn::Mat4x3<uint32_t>> &&
                  "Mat4x3U must be an alias of Mat4x3<uint32_t>");


    /** @test Verify @ref flcn::Mat4x3F has `float` value_type. */
    static_assert(std::is_same_v<flcn::Mat4x3F::value_type, float> &&
                  "Mat4x3F must contain single precision floating point elements");
    static_assert(std::is_same_v<flcn::Mat4x3F, flcn::Mat4x3<float>> && "Mat4x3F must be an alias of Mat4x3<float>");


    /** @test Verify @ref flcn::Mat4x3LL has `int64_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat4x3LL::value_type, int64_t> && "Mat4x3LL must contain int64_t elements");
    static_assert(std::is_same_v<flcn::Mat4x3LL, flcn::Mat4x3<int64_t>> &&
                  "Mat4x3LL must be an alias of Mat4x3<int64_t>");


    /** @test Verify @ref flcn::Mat4x3D has `double` value_type. */
    static_assert(std::is_same_v<flcn::Mat4x3D::value_type, double> &&
                  "Mat4x3D must contain double precision floating point elements");
    static_assert(std::is_same_v<flcn::Mat4x3D, flcn::Mat4x3<double>> && "Mat4x3D must be an alias of Mat4x3<double>");


    /** @test Verify @ref flcn::Mat4x3ULL has `uint64_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat4x3ULL::value_type, uint64_t> && "Mat4x3ULL must contain uint64_t elements");
    static_assert(std::is_same_v<flcn::Mat4x3ULL, flcn::Mat4x3<uint64_t>> &&
                  "Mat4x3ULL must be an alias of Mat4x3<uint64_t>");

} // namespace

/** @} */
