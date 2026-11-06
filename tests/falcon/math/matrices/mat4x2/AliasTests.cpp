/**
 * @file AliasTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify alias for @ref flcn::Mat4x2 returning correct data type.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4x2TestSetup.h"

#include <cstdint>



/**
 * @addtogroup T_FALCON_Mat4x2_Alias
 * @{
 */

/** @test Verify that flcn::Mat4x2[] are alias wrappers for integral and floating-point 4D matrix. */
namespace
{
    /** @test Verify @ref flcn::Mat4x2B has `int8_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat4x2B::value_type, int8_t> && "Mat4x2B must contain int8_t elements");
    static_assert(std::is_same_v<flcn::Mat4x2B, flcn::Mat4x2<int8_t>> && "Mat4x2B must be an alias of Mat4x2<int8_t>");


    /** @test Verify @ref flcn::Mat4x2UB has `uint8_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat4x2UB::value_type, uint8_t> && "Mat4x2UB must contain uint8_t elements");
    static_assert(std::is_same_v<flcn::Mat4x2UB, flcn::Mat4x2<uint8_t>> && "Mat4x2UB must be an alias of Mat4x2<uint8_t>");


    /** @test Verify @ref flcn::Mat4x2I has `int32_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat4x2I::value_type, int32_t> && "Mat4x2I must contain int32_t elements");
    static_assert(std::is_same_v<flcn::Mat4x2I, flcn::Mat4x2<int32_t>> && "Mat4x2I must be an alias of Mat4x2<int32_t>");


    /** @test Verify @ref flcn::Mat4x2U has `uint32_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat4x2U::value_type, uint32_t> && "Mat4x2U must contain uint32_t elements");
    static_assert(std::is_same_v<flcn::Mat4x2U, flcn::Mat4x2<uint32_t>> && "Mat4x2U must be an alias of Mat4x2<uint32_t>");


    /** @test Verify @ref flcn::Mat4x2F has `float` value_type. */
    static_assert(std::is_same_v<flcn::Mat4x2F::value_type, float> &&
                  "Mat4x2F must contain single precision floating point elements");
    static_assert(std::is_same_v<flcn::Mat4x2F, flcn::Mat4x2<float>> && "Mat4x2F must be an alias of Mat4x2<float>");


    /** @test Verify @ref flcn::Mat4x2LL has `int64_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat4x2LL::value_type, int64_t> && "Mat4x2LL must contain int64_t elements");
    static_assert(std::is_same_v<flcn::Mat4x2LL, flcn::Mat4x2<int64_t>> && "Mat4x2LL must be an alias of Mat4x2<int64_t>");


    /** @test Verify @ref flcn::Mat4x2D has `double` value_type. */
    static_assert(std::is_same_v<flcn::Mat4x2D::value_type, double> &&
                  "Mat4x2D must contain double precision floating point elements");
    static_assert(std::is_same_v<flcn::Mat4x2D, flcn::Mat4x2<double>> && "Mat4x2D must be an alias of Mat4x2<double>");


    /** @test Verify @ref flcn::Mat4x2ULL has `uint64_t` value_type. */
    static_assert(std::is_same_v<flcn::Mat4x2ULL::value_type, uint64_t> && "Mat4x2ULL must contain uint64_t elements");
    static_assert(std::is_same_v<flcn::Mat4x2ULL, flcn::Mat4x2<uint64_t>> && "Mat4x2ULL must be an alias of Mat4x2<uint64_t>");

} // namespace

/** @} */
