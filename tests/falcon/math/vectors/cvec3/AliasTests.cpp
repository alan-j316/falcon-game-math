/**
 * @file AliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify alias for @ref flcn::CVec3 returning correct data type.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CVec3TestSetup.h"

#include <cstdint>



/**
 * @addtogroup T_Falcon_CVec3_Alias
 * @{
 */

/** @test Verify that flcn::CVec3[] are alias wrappers for integral and floating-point 3D vector. */
namespace
{
    /** @test Verify @ref flcn::CVec3B has `int8_t` value_type. */
    static_assert(std::is_same_v<flcn::CVec3B::value_type, int8_t> && "CVec3B must contain int8_t elements");
    static_assert(std::is_same_v<flcn::CVec3B, flcn::CVec3<int8_t>> && "CVec3B must be an alias of CVec3<int8_t>");


    /** @test Verify @ref flcn::CVec3UB has `uint8_t` value_type. */
    static_assert(std::is_same_v<flcn::CVec3UB::value_type, uint8_t> && "CVec3UB must contain uint8_t elements");
    static_assert(std::is_same_v<flcn::CVec3UB, flcn::CVec3<uint8_t>> && "CVec3UB must be an alias of CVec3<uint8_t>");


    /** @test Verify @ref flcn::CVec3I has `int32_t` value_type. */
    static_assert(std::is_same_v<flcn::CVec3I::value_type, int32_t> && "CVec3I must contain int32_t elements");
    static_assert(std::is_same_v<flcn::CVec3I, flcn::CVec3<int32_t>> && "CVec3I must be an alias of CVec3<int32_t>");


    /** @test Verify @ref flcn::CVec3U has `uint32_t` value_type. */
    static_assert(std::is_same_v<flcn::CVec3U::value_type, uint32_t> && "CVec3U must contain uint32_t elements");
    static_assert(std::is_same_v<flcn::CVec3U, flcn::CVec3<uint32_t>> && "CVec3U must be an alias of CVec3<uint32_t>");


    /** @test Verify @ref flcn::CVec3F has `float` value_type. */
    static_assert(std::is_same_v<flcn::CVec3F::value_type, float> &&
                  "CVec3F must contain single precision floating point elements");
    static_assert(std::is_same_v<flcn::CVec3F, flcn::CVec3<float>> && "CVec3F must be an alias of CVec3<float>");


    /** @test Verify @ref flcn::CVec3LL has `int64t` value_type. */
    static_assert(std::is_same_v<flcn::CVec3LL::value_type, int64_t> && "CVec3LL must contain int64_t elements");
    static_assert(std::is_same_v<flcn::CVec3LL, flcn::CVec3<int64_t>> && "CVec3LL must be an alias of CVec3<int64_t>");


    /** @test Verify @ref flcn::CVec3D has `double` value_type. */
    static_assert(std::is_same_v<flcn::CVec3D::value_type, double> &&
                  "CVec3D must contain double precision floating point elements");
    static_assert(std::is_same_v<flcn::CVec3D, flcn::CVec3<double>> && "CVec3D must be an alias of CVec3<double>");


    /** @test Verify @ref flcn::CVec3ULL has `uint64_t` value_type. */
    static_assert(std::is_same_v<flcn::CVec3ULL::value_type, uint64_t> && "CVec3ULL must contain uint64_t elements");
    static_assert(std::is_same_v<flcn::CVec3ULL, flcn::CVec3<uint64_t>> && "CVec3ULL must be an alias of CVec3<uint64_t>");
} // namespace

/** @} */
