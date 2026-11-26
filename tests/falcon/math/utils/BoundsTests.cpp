/**
 * @file BoundsTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 26, 2026
 *
 * @brief Verifies falcon bounds functions like min, max, clamp.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


/**
 *  @addtogroup T_Falcon_Bounds
 *  @{
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

        /// @test Verify that flcn::min returns a valid 2D-vector at compile time.
        constexpr auto MIN_VEC2 = flcn::min(VEC_A2, VEC_B2);
        static_assert(MIN_VEC2.x() == 1.0f);
        static_assert(MIN_VEC2.y() == 0.25f);

        /// @test Verify that flcn::max returns a valid 2D-vector at compile time.
        constexpr auto MAX_VEC2 = flcn::max(VEC_A2, VEC_B2);
        static_assert(MAX_VEC2.x() == 4.0f);
        static_assert(MAX_VEC2.y() == 2.0f);


        /// @test Verify that flcn::min returns a valid 3D-vector at compile time.
        constexpr auto MIN_VEC3 = flcn::min(VEC_A3, VEC_B3);
        static_assert(MIN_VEC3.x() == 1.0f);
        static_assert(MIN_VEC3.y() == 0.25f);
        static_assert(MIN_VEC3.z() == 3.0f);

        /// @test Verify that flcn::max returns a valid 3D-vector at compile time.
        constexpr auto MAX_VEC3 = flcn::max(VEC_A3, VEC_B3);
        static_assert(MAX_VEC3.x() == 4.0f);
        static_assert(MAX_VEC3.y() == 2.0f);
        static_assert(MAX_VEC3.z() == 5.0f);


        /// @test Verify that flcn::min returns a valid 4D-vector at compile time.
        constexpr auto MIN_VEC4 = flcn::min(VEC_A4, VEC_B4);
        static_assert(MIN_VEC4.x() == 1.0f);
        static_assert(MIN_VEC4.y() == 0.25f);
        static_assert(MIN_VEC4.z() == 3.0f);
        static_assert(MIN_VEC4.w() == -5.0f);

        /// @test Verify that flcn::max returns a valid 4D-vector at compile time.
        constexpr auto MAX_VEC4 = flcn::max(VEC_A4, VEC_B4);
        static_assert(MAX_VEC4.x() == 4.0f);
        static_assert(MAX_VEC4.y() == 2.0f);
        static_assert(MAX_VEC4.z() == 5.0f);
        static_assert(MAX_VEC4.w() == 4.0f);

    } // namespace static_tests
} // namespace


/// +---------------------------------------------------------------------------------------+
/// |                             SCALAR VEC<n> TESTS                                       |
/// +---------------------------------------------------------------------------------------+

// ------------------------ VEC2 ------------------------

TYPED_TEST(Vec2MinTests, StaticWrapper_ReturnsMinimumComponentVector)
{ EXPECT_VEC_EQ(this->expectedMin, flcn::min(this->a, this->b)); }


TEST(Vec2MinTests, StaticWrapper_InfVector_ReturnsMinimumComponent)
{
    const flcn::Vec2F vecA(1.0f, flcn::constants::INFINITY_F);
    const flcn::Vec2F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F);

    EXPECT_VEC_CONTAINS(flcn::min(vecA, vecB), 1.0f, -flcn::constants::INFINITY_F);
}


TYPED_TEST(Vec2MaxTests, StaticWrapper_ReturnsMinimumComponentVector)
{ EXPECT_VEC_EQ(this->expectedMax, flcn::max(this->a, this->b)); }


TEST(Vec2MaxTests, StaticWrapper_InfVector_ReturnsMinimumComponent)
{
    const flcn::Vec2F vecA(1.0f, flcn::constants::INFINITY_F);
    const flcn::Vec2F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F);

    EXPECT_VEC_CONTAINS(flcn::max(vecA, vecB), flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
}


// ------------------------ VEC3 ------------------------

TYPED_TEST(Vec3MinTests, StaticWrapper_ReturnsMinimumComponentVector)
{ EXPECT_VEC_EQ(this->expectedMin, flcn::min(this->a, this->b)); }


TEST(Vec3MinTests, StaticWrapper_InfVector_ReturnsMinimumComponent)
{
    const flcn::Vec3F vecA(1.0f, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
    const flcn::Vec3F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);

    EXPECT_VEC_CONTAINS(flcn::min(vecA, vecB), 1.0f, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
}


TYPED_TEST(Vec3MaxTests, StaticWrapper_ReturnsMinimumComponentVector)
{ EXPECT_VEC_EQ(this->expectedMax, flcn::max(this->a, this->b)); }


TEST(Vec3MaxTests, StaticWrapper_InfVector_ReturnsMinimumComponent)
{
    const flcn::Vec3F vecA(1.0f, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
    const flcn::Vec3F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);

    EXPECT_VEC_CONTAINS(flcn::max(vecA, vecB), flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                        flcn::constants::INFINITY_F);
}


// ------------------------ VEC4 ------------------------

TYPED_TEST(Vec4MinTests, StaticWrapper_ReturnsMinimumComponentVector)
{ EXPECT_VEC_EQ(this->expectedMin, flcn::min(this->a, this->b)); }


TEST(Vec4MinTests, StaticWrapper_InfVector_ReturnsMinimumComponent)
{
    const flcn::Vec4F vecA(1.0f, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
    const flcn::Vec4F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                           -4.0f);

    EXPECT_VEC_CONTAINS(flcn::min(vecA, vecB), 1.0f, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                        -4.0f);
}


TYPED_TEST(Vec4MaxTests, StaticWrapper_ReturnsMinimumComponentVector)
{ EXPECT_VEC_EQ(this->expectedMax, flcn::max(this->a, this->b)); }


TEST(Vec4MaxTests, StaticWrapper_InfVector_ReturnsMinimumComponent)
{
    const flcn::Vec4F vecA(1.0f, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
    const flcn::Vec4F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                           -4.0f);

    EXPECT_VEC_CONTAINS(flcn::max(vecA, vecB), flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                        flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
}



/// +---------------------------------------------------------------------------------------+
/// |                              SIMD VEC<n> TESTS                                        |
/// +---------------------------------------------------------------------------------------+


// ------------------------ VEC2 ------------------------

TYPED_TEST(SimdVec2MinTests, StaticWrapper_ReturnsMinimumComponentVector)
{ EXPECT_VEC_EQ(this->expectedMin, flcn::min(this->a, this->b)); }


TEST(SimdVec2MinTests, StaticWrapper_InfVector_ReturnsMinimumComponent)
{
    const flcn::simd::Vec2F vecA(1.0f, flcn::constants::INFINITY_F);
    const flcn::simd::Vec2F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F);

    EXPECT_VEC_CONTAINS(flcn::min(vecA, vecB), 1.0f, -flcn::constants::INFINITY_F);
}


TYPED_TEST(SimdVec2MaxTests, StaticWrapper_ReturnsMinimumComponentVector)
{ EXPECT_VEC_EQ(this->expectedMax, flcn::max(this->a, this->b)); }


TEST(SimdVec2MaxTests, StaticWrapper_InfVector_ReturnsMinimumComponent)
{
    const flcn::simd::Vec2F vecA(1.0f, flcn::constants::INFINITY_F);
    const flcn::simd::Vec2F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F);

    EXPECT_VEC_CONTAINS(flcn::max(vecA, vecB), flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
}


// ------------------------ VEC3 ------------------------

TYPED_TEST(SimdVec3MinTests, StaticWrapper_ReturnsMinimumComponentVector)
{ EXPECT_VEC_EQ(this->expectedMin, flcn::min(this->a, this->b)); }


TEST(SimdVec3MinTests, StaticWrapper_InfVector_ReturnsMinimumComponent)
{
    const flcn::simd::Vec3F vecA(1.0f, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
    const flcn::simd::Vec3F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);

    EXPECT_VEC_CONTAINS(flcn::min(vecA, vecB), 1.0f, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
}


TYPED_TEST(SimdVec3MaxTests, StaticWrapper_ReturnsMinimumComponentVector)
{ EXPECT_VEC_EQ(this->expectedMax, flcn::max(this->a, this->b)); }


TEST(SimdVec3MaxTests, StaticWrapper_InfVector_ReturnsMinimumComponent)
{
    const flcn::simd::Vec3F vecA(1.0f, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
    const flcn::simd::Vec3F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);

    EXPECT_VEC_CONTAINS(flcn::max(vecA, vecB), flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                        flcn::constants::INFINITY_F);
}



/** @} */
