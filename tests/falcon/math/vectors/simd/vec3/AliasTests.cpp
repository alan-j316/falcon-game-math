/**
 * @file AliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 10, 2026
 *
 * @brief Verify alias for @ref flcn::simd::Vec3 returning correct data type.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"

#include <cstdint>



/**
 * @addtogroup T_Falcon_Vec3_Alias
 * @{
 */

/** @test Verify that flcn::simd::Vec3[] are alias wrappers for integral and floating-point 3D vector. */
namespace
{
    /** @test Verify @ref flcn::simd::Vec3B has `int8_t` value_type. */
    static_assert(std::is_same_v<flcn::simd::Vec3B::value_type, int8_t> && "Vec3B must contain int8_t elements");
    static_assert(std::is_same_v<flcn::simd::Vec3B, flcn::simd::Vec3<int8_t>> && "Vec3B must be an alias of Vec3<int8_t>");


    /** @test Verify @ref flcn::simd::Vec3UB has `uint8_t` value_type. */
    static_assert(std::is_same_v<flcn::simd::Vec3UB::value_type, uint8_t> && "Vec3UB must contain uint8_t elements");
    static_assert(std::is_same_v<flcn::simd::Vec3UB, flcn::simd::Vec3<uint8_t>> && "Vec3UB must be an alias of Vec3<uint8_t>");


    /** @test Verify @ref flcn::simd::Vec3I has `int32_t` value_type. */
    static_assert(std::is_same_v<flcn::simd::Vec3I::value_type, int32_t> && "Vec3I must contain int32_t elements");
    static_assert(std::is_same_v<flcn::simd::Vec3I, flcn::simd::Vec3<int32_t>> && "Vec3I must be an alias of Vec3<int32_t>");


    /** @test Verify @ref flcn::simd::Vec3U has `uint32_t` value_type. */
    static_assert(std::is_same_v<flcn::simd::Vec3U::value_type, uint32_t> && "Vec3U must contain uint32_t elements");
    static_assert(std::is_same_v<flcn::simd::Vec3U, flcn::simd::Vec3<uint32_t>> && "Vec3U must be an alias of Vec3<uint32_t>");


    /** @test Verify @ref flcn::simd::Vec3F has `float` value_type. */
    static_assert(std::is_same_v<flcn::simd::Vec3F::value_type, float> &&
                  "Vec3F must contain single precision floating point elements");
    static_assert(std::is_same_v<flcn::simd::Vec3F, flcn::simd::Vec3<float>> && "Vec3F must be an alias of Vec3<float>");


    /** @test Verify @ref flcn::simd::Vec3LL has `int64t` value_type. */
    static_assert(std::is_same_v<flcn::simd::Vec3LL::value_type, int64_t> && "Vec3LL must contain int64_t elements");
    static_assert(std::is_same_v<flcn::simd::Vec3LL, flcn::simd::Vec3<int64_t>> && "Vec3LL must be an alias of Vec3<int64_t>");


    /** @test Verify @ref flcn::simd::Vec3D has `double` value_type. */
    static_assert(std::is_same_v<flcn::simd::Vec3D::value_type, double> &&
                  "Vec3D must contain double precision floating point elements");
    static_assert(std::is_same_v<flcn::simd::Vec3D, flcn::simd::Vec3<double>> && "Vec3D must be an alias of Vec3<double>");


    /** @test Verify @ref flcn::simd::Vec3ULL has `uint64_t` value_type. */
    static_assert(std::is_same_v<flcn::simd::Vec3ULL::value_type, uint64_t> && "Vec3ULL must contain uint64_t elements");
    static_assert(std::is_same_v<flcn::simd::Vec3ULL, flcn::simd::Vec3<uint64_t>> && "Vec3ULL must be an alias of Vec3<uint64_t>");
} // namespace

/** @} */
