/**
 * @file AliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verify alias for @ref flcn::Vec4 returning correct data type.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec4TestSetup.h"

#include <cstdint>



/**
 * @addtogroup T_FALCON_Vec4_Alias
 * @{
 */

/** @test Verify that flcn::Vec4[] are alias wrappers for integral and floating-point 4D vector. */
namespace
{
    /** @test Verify @ref flcn::Vec4B has `int8_t` value_type. */
    static_assert(std::is_same_v<flcn::Vec4B::value_type, int8_t> && "Vec4B must contain int8_t elements");
    static_assert(std::is_same_v<flcn::Vec4B, flcn::Vec4<int8_t>> && "Vec4B must be an alias of Vec4<int8_t>");


    /** @test Verify @ref flcn::Vec4UB has `uint8_t` value_type. */
    static_assert(std::is_same_v<flcn::Vec4UB::value_type, uint8_t> && "Vec4UB must contain uint8_t elements");
    static_assert(std::is_same_v<flcn::Vec4UB, flcn::Vec4<uint8_t>> && "Vec4UB must be an alias of Vec4<uint8_t>");


    /** @test Verify @ref flcn::Vec4I has `int32_t` value_type. */
    static_assert(std::is_same_v<flcn::Vec4I::value_type, int32_t> && "Vec4I must contain int32_t elements");
    static_assert(std::is_same_v<flcn::Vec4I, flcn::Vec4<int32_t>> && "Vec4I must be an alias of Vec4<int32_t>");


    /** @test Verify @ref flcn::Vec4U has `uint32_t` value_type. */
    static_assert(std::is_same_v<flcn::Vec4U::value_type, uint32_t> && "Vec4U must contain uint32_t elements");
    static_assert(std::is_same_v<flcn::Vec4U, flcn::Vec4<uint32_t>> && "Vec4U must be an alias of Vec4<uint32_t>");


    /** @test Verify @ref flcn::Vec4F has `float` value_type. */
    static_assert(std::is_same_v<flcn::Vec4F::value_type, float> &&
                  "Vec4F must contain single precision floating point elements");
    static_assert(std::is_same_v<flcn::Vec4F, flcn::Vec4<float>> && "Vec4F must be an alias of Vec4<float>");


    /** @test Verify @ref flcn::Vec4LL has `int64t` value_type. */
    static_assert(std::is_same_v<flcn::Vec4LL::value_type, int64_t> && "Vec4LL must contain int64_t elements");
    static_assert(std::is_same_v<flcn::Vec4LL, flcn::Vec4<int64_t>> && "Vec4LL must be an alias of Vec4<int64_t>");


    /** @test Verify @ref flcn::Vec4D has `double` value_type. */
    static_assert(std::is_same_v<flcn::Vec4D::value_type, double> &&
                  "Vec4D must contain double precision floating point elements");
    static_assert(std::is_same_v<flcn::Vec4D, flcn::Vec4<double>> && "Vec4D must be an alias of Vec4<double>");


    /** @test Verify @ref flcn::Vec4ULL has `uint64_t` value_type. */
    static_assert(std::is_same_v<flcn::Vec4ULL::value_type, uint64_t> && "Vec4ULL must contain uint64_t elements");
    static_assert(std::is_same_v<flcn::Vec4ULL, flcn::Vec4<uint64_t>> && "Vec4ULL must be an alias of Vec4<uint64_t>");
} // namespace

/** @} */
