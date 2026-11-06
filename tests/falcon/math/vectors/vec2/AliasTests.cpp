/**
 * @file AliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify alias for @ref flcn::Vec2 returning correct data type.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"

#include <cstdint>



/**
 * @addtogroup T_FALCON_Vec2_Alias
 * @{
 */

/** @test Verify that flcn::Vec2[] are alias wrappers for integral and floating-point 2D vector. */
namespace
{
    /** @test Verify @ref flcn::Vec2B has `int8_t` value_type. */
    static_assert(std::is_same_v<flcn::Vec2B::value_type, int8_t> && "Vec2B must contain int8_t elements");
    static_assert(std::is_same_v<flcn::Vec2B, flcn::Vec2<int8_t>> && "Vec2B must be an alias of Vec2<int8_t>");


    /** @test Verify @ref flcn::Vec2UB has `uint8_t` value_type. */
    static_assert(std::is_same_v<flcn::Vec2UB::value_type, uint8_t> && "Vec2UB must contain uint8_t elements");
    static_assert(std::is_same_v<flcn::Vec2UB, flcn::Vec2<uint8_t>> && "Vec2UB must be an alias of Vec2<uint8_t>");


    /** @test Verify @ref flcn::Vec2I has `int32_t` value_type. */
    static_assert(std::is_same_v<flcn::Vec2I::value_type, int32_t> && "Vec2I must contain int32_t elements");
    static_assert(std::is_same_v<flcn::Vec2I, flcn::Vec2<int32_t>> && "Vec2I must be an alias of Vec2<int32_t>");


    /** @test Verify @ref flcn::Vec2U has `uint32_t` value_type. */
    static_assert(std::is_same_v<flcn::Vec2U::value_type, uint32_t> && "Vec2U must contain uint32_t elements");
    static_assert(std::is_same_v<flcn::Vec2U, flcn::Vec2<uint32_t>> && "Vec2U must be an alias of Vec2<uint32_t>");


    /** @test Verify @ref flcn::Vec2F has `float` value_type. */
    static_assert(std::is_same_v<flcn::Vec2F::value_type, float> &&
                  "Vec2F must contain single precision floating point elements");
    static_assert(std::is_same_v<flcn::Vec2F, flcn::Vec2<float>> && "Vec2F must be an alias of Vec2<float>");


    /** @test Verify @ref flcn::Vec2LL has `int64t` value_type. */
    static_assert(std::is_same_v<flcn::Vec2LL::value_type, int64_t> && "Vec2LL must contain int64_t elements");
    static_assert(std::is_same_v<flcn::Vec2LL, flcn::Vec2<int64_t>> && "Vec2LL must be an alias of Vec2<int64_t>");


    /** @test Verify @ref flcn::Vec2D has `double` value_type. */
    static_assert(std::is_same_v<flcn::Vec2D::value_type, double> &&
                  "Vec2D must contain double precision floating point elements");
    static_assert(std::is_same_v<flcn::Vec2D, flcn::Vec2<double>> && "Vec2D must be an alias of Vec2<double>");


    /** @test Verify @ref flcn::Vec2ULL has `uint64_t` value_type. */
    static_assert(std::is_same_v<flcn::Vec2ULL::value_type, uint64_t> && "Vec2ULL must contain uint64_t elements");
    static_assert(std::is_same_v<flcn::Vec2ULL, flcn::Vec2<uint64_t>> && "Vec2ULL must be an alias of Vec2<uint64_t>");
} // namespace

/** @} */
