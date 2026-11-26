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

namespace
{
    namespace static_tests
    {
        constexpr flcn::Vec2 VEC_A2(1.0f, 2.0f);
        constexpr flcn::Vec2 VEC_B2(4.0f, 0.25f);
        constexpr flcn::Vec3 VEC_A3(1.0f, 2.0f, 3.0f);
        constexpr flcn::Vec3 VEC_B3(4.0f, 0.25f, 5.0f);
        constexpr flcn::Vec4 VEC_A4(1.0f, 2.0f, 3.0f, 4.0f);
        constexpr flcn::Vec4 VEC_B4(4.0f, 0.25f, 5.0f, -5.0f);

        /// @test Verify that flcn::mix returns a valid 2D-vector at compile time.
        constexpr auto STATIC_MIX_VEC2 = flcn::mix(VEC_A2, VEC_B2, 0.25f);
        static_assert(STATIC_MIX_VEC2.x() == 1.75f);
        static_assert(STATIC_MIX_VEC2.y() == 1.5625f);

        /// @test Verify that flcn::mix returns a valid 3D-vector at compile time.
        constexpr auto STATIC_MIX_VEC3 = flcn::mix(VEC_A3, VEC_B3, 0.25f);
        static_assert(STATIC_MIX_VEC3.x() == 1.75f);
        static_assert(STATIC_MIX_VEC3.y() == 1.5625f);
        static_assert(STATIC_MIX_VEC3.z() == 3.5f);

        /// @test Verify that flcn::mix returns a valid 4D-vector at compile time.
        constexpr auto STATIC_MIX_VEC4 = flcn::mix(VEC_A4, VEC_B4, 0.25f);
        static_assert(STATIC_MIX_VEC4.x() == 1.75f);
        static_assert(STATIC_MIX_VEC4.y() == 1.5625f);
        static_assert(STATIC_MIX_VEC4.z() == 3.5f);
        static_assert(STATIC_MIX_VEC4.w() == 1.75f);

    } // namespace static_tests
} // namespace


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
