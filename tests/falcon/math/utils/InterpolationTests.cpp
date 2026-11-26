/**
 * @file InterpolationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref flcn interpolation functions(mix, slerp).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



/**
 * @addtogroup T_Falcon_Interpolation
 * @{
 */

#include "VecUtilsSetup.h"

// namespace
// {
//     namespace static_tests
//     {
//         constexpr flcn::Vec2 NORM_VEC_A(1.0f, 2.0f);
//         constexpr flcn::Vec2 NORM_VEC_B(4.0f, 0.25f);
//         constexpr flcn::Vec2 INF_VEC(flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
//         constexpr flcn::Vec2 NAN_VEC(flcn::constants::NaN, flcn::constants::NaN);
//
//         /// @test Verify that Vec2::hasInf returns a valid boolean at compile time.
//         static_assert(NORM_VEC_A.hasInf() == false);
//         static_assert(INF_VEC.hasInf() == true);
//         static_assert(NAN_VEC.hasInf() == false);
//
//         /// @test Verify that Vec2::hasInf(static wrapper) returns a valid boolean at compile time.
//         static_assert(flcn::Vec2<float>::hasInf(NORM_VEC_A) == false);
//         static_assert(flcn::Vec2<float>::hasInf(INF_VEC) == true);
//         static_assert(flcn::Vec2<float>::hasInf(NAN_VEC) == false);
//
//         /// @test Verify that Vec2::hasNaN returns a valid boolean at compile time.
//         static_assert(NORM_VEC_A.hasNaN() == false);
//         static_assert(INF_VEC.hasNaN() == false);
//         static_assert(NAN_VEC.hasNaN() == true);
//
//         /// @test Verify that Vec2::hasNaN(static wrapper) returns a valid boolean at compile time.
//         static_assert(flcn::Vec2<float>::hasNaN(NORM_VEC_A) == false);
//         static_assert(flcn::Vec2<float>::hasNaN(INF_VEC) == false);
//         static_assert(flcn::Vec2<float>::hasNaN(NAN_VEC) == true);
//
//         /// @test Verify that Vec2::min returns a valid vector at compile time.
//         constexpr auto MIN_VEC        = NORM_VEC_A.min(NORM_VEC_B);
//         constexpr auto STATIC_MIN_VEC = flcn::Vec2F::min(NORM_VEC_A, NORM_VEC_B);
//         static_assert(MIN_VEC.x() == 1.0f);
//         static_assert(MIN_VEC.y() == 0.25f);
//         static_assert(STATIC_MIN_VEC.x() == 1.0f);
//         static_assert(STATIC_MIN_VEC.y() == 0.25f);
//
//         /// @test Verify that Vec2::max returns a valid vector at compile time.
//         constexpr auto MAX_VEC        = NORM_VEC_A.max(NORM_VEC_B);
//         constexpr auto STATIC_MAX_VEC = flcn::Vec2F::max(NORM_VEC_A, NORM_VEC_B);
//         static_assert(MAX_VEC.x() == 4.0f);
//         static_assert(MAX_VEC.y() == 2.0f);
//         static_assert(STATIC_MAX_VEC.x() == 4.0f);
//         static_assert(STATIC_MAX_VEC.y() == 2.0f);
//
//         /// @test Verify that Vec2::mix returns a valid vector at compile time.
//         constexpr auto MIX_VEC        = NORM_VEC_A.mix(NORM_VEC_B, 0.25f);
//         constexpr auto STATIC_MIX_VEC = flcn::Vec2F::mix(NORM_VEC_A, NORM_VEC_B, 0.25f);
//         static_assert(MIX_VEC.x() == 1.75f);
//         static_assert(MIX_VEC.y() == 1.5625f);
//         static_assert(STATIC_MIX_VEC.x() == 1.75f);
//         static_assert(STATIC_MIX_VEC.y() == 1.5625f);
//
//     } // namespace static_tests
// } // namespace

/// +---------------------------------------------------------------------------------------+
/// |                             SCALAR VEC<n> TESTS                                       |
/// +---------------------------------------------------------------------------------------+

TYPED_TEST(Vec2MixTests, StaticWrapper_ReturnsMinimumComponentVector)
{
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->expectedFP, flcn::mix(this->a, this->b, this->factor));
    }
    else
    {
        EXPECT_VEC_EQ(this->expectedInt, flcn::mix(this->a, this->b, this->factor));
    }
}


TEST_P(Vec2MixParameterizedTests, StaticWrapper_ReturnsInterpolatedVector)
{
    const auto& [a, b, factor, expected] = GetParam();
    EXPECT_VEC_EQ(expected, flcn::mix(a, b, factor));
}


TYPED_TEST(Vec3MixTests, StaticWrapper_ReturnsMinimumComponentVector)
{
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->expectedFP, flcn::mix(this->a, this->b, this->factor));
    }
    else
    {
        EXPECT_VEC_EQ(this->expectedInt, flcn::mix(this->a, this->b, this->factor));
    }
}


TEST_P(Vec3MixParameterizedTests, StaticWrapper_ReturnsInterpolatedVector)
{
    const auto& [a, b, factor, expected] = GetParam();
    EXPECT_VEC_EQ(expected, flcn::mix(a, b, factor));
}


TYPED_TEST(Vec4MixTests, StaticWrapper_ReturnsMinimumComponentVector)
{
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->expectedFP, flcn::mix(this->a, this->b, this->factor));
    }
    else
    {
        EXPECT_VEC_EQ(this->expectedInt, flcn::mix(this->a, this->b, this->factor));
    }
}


TEST_P(Vec4MixParameterizedTests, StaticWrapper_ReturnsInterpolatedVector)
{
    const auto& [a, b, factor, expected] = GetParam();
    EXPECT_VEC_EQ(expected, flcn::mix(a, b, factor));
}


/// +---------------------------------------------------------------------------------------+
/// |                               SIMD VEC<n> TESTS                                       |
/// +---------------------------------------------------------------------------------------+

TYPED_TEST(SimdVec2MixTests, StaticWrapper_ReturnsMinimumComponentVector)
{ EXPECT_VEC_EQ(this->expected, flcn::mix(this->a, this->b, this->factor)); }


TEST_P(SimdVec2MixParameterizedTests, StaticWrapper_ReturnsInterpolatedVector)
{
    const auto& [a, b, factor, expected] = GetParam();
    EXPECT_VEC_EQ(expected, flcn::mix(a, b, factor));
}


TYPED_TEST(SimdVec3MixTests, StaticWrapper_ReturnsMinimumComponentVector)
{ EXPECT_VEC_EQ(this->expected, flcn::mix(this->a, this->b, this->factor)); }


TEST_P(SimdVec3MixParameterizedTests, StaticWrapper_ReturnsInterpolatedVector)
{
    const auto& [a, b, factor, expected] = GetParam();
    EXPECT_VEC_EQ(expected, flcn::mix(a, b, factor));
}



/// +---------------------------------------------------------------------------------------+
/// |                                QUATERNION TESTS                                       |
/// +---------------------------------------------------------------------------------------+


/** @} */
