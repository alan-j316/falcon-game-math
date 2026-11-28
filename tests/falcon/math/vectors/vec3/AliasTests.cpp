/**
 * @file AliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify alias for @ref flcn::Vec3 returning correct data type.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"

#include <cstdint>



/**
 * @addtogroup T_Falcon_Vec3_Alias
 * @{
 */

/** @test Verify that flcn::Vec3[] are alias wrappers for integral and floating-point 3D vector. */
namespace
{
    /** @test Verify @ref flcn::Vec3B has `int8_t` ValueType. */
    static_assert(std::is_same_v<flcn::Vec3B::ValueType, int8_t> && "Vec3B must contain int8_t elements");
    static_assert(std::is_same_v<flcn::Vec3B, flcn::Vec3<int8_t>> && "Vec3B must be an alias of Vec3<int8_t>");


    /** @test Verify @ref flcn::Vec3UB has `uint8_t` ValueType. */
    static_assert(std::is_same_v<flcn::Vec3UB::ValueType, uint8_t> && "Vec3UB must contain uint8_t elements");
    static_assert(std::is_same_v<flcn::Vec3UB, flcn::Vec3<uint8_t>> && "Vec3UB must be an alias of Vec3<uint8_t>");


    /** @test Verify @ref flcn::Vec3I has `int32_t` ValueType. */
    static_assert(std::is_same_v<flcn::Vec3I::ValueType, int32_t> && "Vec3I must contain int32_t elements");
    static_assert(std::is_same_v<flcn::Vec3I, flcn::Vec3<int32_t>> && "Vec3I must be an alias of Vec3<int32_t>");


    /** @test Verify @ref flcn::Vec3U has `uint32_t` ValueType. */
    static_assert(std::is_same_v<flcn::Vec3U::ValueType, uint32_t> && "Vec3U must contain uint32_t elements");
    static_assert(std::is_same_v<flcn::Vec3U, flcn::Vec3<uint32_t>> && "Vec3U must be an alias of Vec3<uint32_t>");


    /** @test Verify @ref flcn::Vec3F has `float` ValueType. */
    static_assert(std::is_same_v<flcn::Vec3F::ValueType, float> &&
                  "Vec3F must contain single precision floating point elements");
    static_assert(std::is_same_v<flcn::Vec3F, flcn::Vec3<float>> && "Vec3F must be an alias of Vec3<float>");


    /** @test Verify @ref flcn::Vec3LL has `int64t` ValueType. */
    static_assert(std::is_same_v<flcn::Vec3LL::ValueType, int64_t> && "Vec3LL must contain int64_t elements");
    static_assert(std::is_same_v<flcn::Vec3LL, flcn::Vec3<int64_t>> && "Vec3LL must be an alias of Vec3<int64_t>");


    /** @test Verify @ref flcn::Vec3D has `double` ValueType. */
    static_assert(std::is_same_v<flcn::Vec3D::ValueType, double> &&
                  "Vec3D must contain double precision floating point elements");
    static_assert(std::is_same_v<flcn::Vec3D, flcn::Vec3<double>> && "Vec3D must be an alias of Vec3<double>");


    /** @test Verify @ref flcn::Vec3ULL has `uint64_t` ValueType. */
    static_assert(std::is_same_v<flcn::Vec3ULL::ValueType, uint64_t> && "Vec3ULL must contain uint64_t elements");
    static_assert(std::is_same_v<flcn::Vec3ULL, flcn::Vec3<uint64_t>> && "Vec3ULL must be an alias of Vec3<uint64_t>");
} // namespace

/** @} */
