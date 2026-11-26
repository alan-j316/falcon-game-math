/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref flcn::simd::Vec2 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */




/**
 * @addtogroup T_Falcon_Vec2_Utils
 * @{
 */

#include "InterpolationTestFixture.h"
#include "Vec2TestSetup.h"

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    template <typename T>
        requires std::floating_point<T>
    struct Vec2UtilityParams
    {
        flcn::simd::Vec2<T> vec;
        bool expected;
    };


    /**
     * @brief Test fixture for @ref flcn::simd::Vec2 Infinity Checking.
     */
    class SimdVec2InfCheckerTests: public testing::TestWithParam<Vec2UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        SimdVec2UtilsInfVectors, SimdVec2InfCheckerTests,
        ::testing::Values(Vec2UtilityParams{ flcn::simd::Vec2(flcn::constants::INFINITY_F, 1.0f), true },
                          Vec2UtilityParams{ flcn::simd::Vec2(1.0f, flcn::constants::INFINITY_F), true },
                          Vec2UtilityParams{ flcn::simd::Vec2(flcn::constants::INFINITY_F, flcn::constants::INFINITY_F),
                                             true },
                          Vec2UtilityParams{ flcn::simd::Vec2(1.0f, 1.0f), false }));


    /**
     * @brief Test fixture for @ref flcn::simd::Vec2 NaN Checking.
     */
    class SimdVec2NaNCheckerTests: public testing::TestWithParam<Vec2UtilityParams<float>>
    {};

    INSTANTIATE_TEST_SUITE_P(SimdSimdVec2UtilsNaNVectors, SimdVec2NaNCheckerTests,
                             ::testing::Values(Vec2UtilityParams{ flcn::simd::Vec2(flcn::constants::NaN, 1.0f), true },
                                               Vec2UtilityParams{ flcn::simd::Vec2(1.0f, flcn::constants::NaN), true },
                                               Vec2UtilityParams{
                                                   flcn::simd::Vec2(flcn::constants::NaN, flcn::constants::NaN), true },
                                               Vec2UtilityParams{ flcn::simd::Vec2(1.0f, 1.0f), false }));


    /**
     * @brief Test fixture for @ref flcn::simd::Vec2 utilities, verifying across various integral types.
     */
    template <typename>
    class SimdVec2UtilsIntTests: public testing::Test
    {};

    TYPED_TEST_SUITE(SimdVec2UtilsIntTests, SupportedIntegralTypes);

} // namespace


/**************************************
 *      INFINITY CHECKER TESTS        *
 **************************************/

/**
 * @test Verify that @ref std::Vec2::hasInf returns True if any of components are IEE754 infinity
 *       and False otherwise.
 */
TEST_P(SimdVec2InfCheckerTests, ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasInf());
}


/** @test Verify that @ref std::Vec2::hasInf returns False for integral types. */
TYPED_TEST(SimdVec2UtilsIntTests, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::simd::Vec2(value, value).hasInf());
}


/**
 * @test Verify that the static variant of @ref std::Vec2::hasInf returns True if any of components are IEE754
 *       infinity and False otherwise.
 */
TEST_P(SimdVec2InfCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, flcn::simd::Vec2<float>::hasInf(vec));
}


/** @test Verify that the static variant of @ref std::Vec2::hasInf returns False for integral types. */
TYPED_TEST(SimdVec2UtilsIntTests, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::simd::Vec2<TypeParam>::hasInf(flcn::simd::Vec2(value, value)));
}


/**************************************
 *         NAN CHECKER TESTS          *
 **************************************/

/**
 * @test Verify that @ref std::Vec2::hasNaN returns True if any of components are IEE754 NaN(Not-a-Number)
 *       and False otherwise.
 */
TEST_P(SimdVec2NaNCheckerTests, ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasNaN());
}


/** @test Verify that @ref std::Vec2::hasNaN returns False for integral types. */
TYPED_TEST(SimdVec2UtilsIntTests, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::simd::Vec2(value, value).hasNaN());
}


/**
 * @test Verify that the static variant of @ref std::Vec2::hasNaN returns True if any of components are IEE754
 *       NaN(Not-a-Number) and False otherwise.
 */
TEST_P(SimdVec2NaNCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, flcn::simd::Vec2<float>::hasNaN(vec));
}


/** @test Verify that the static variant of @ref std::Vec2::hasNaN returns False for integral types. */
TYPED_TEST(SimdVec2UtilsIntTests, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::simd::Vec2<TypeParam>::hasNaN(flcn::simd::Vec2(value, value)));
}


/**************************************
 *             MIN TESTS              *
 **************************************/

TYPED_TEST(SimdVec2MinTests, ReturnsMinimumComponentVector) { EXPECT_VEC_EQ(this->expectedMin, this->a.min(this->b)); }


TEST(SimdVec2MinTests, InfVector_ReturnsMinimumComponent)
{
    const flcn::simd::Vec2F vecA(1.0f, flcn::constants::INFINITY_F);
    const flcn::simd::Vec2F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F);

    EXPECT_VEC_CONTAINS(vecA.min(vecB), 1.0f, -flcn::constants::INFINITY_F);
}


/**************************************
 *             MAX TESTS              *
 **************************************/

TYPED_TEST(SimdVec2MaxTests, ReturnsMinimumComponentVector) { EXPECT_VEC_EQ(this->expectedMax, this->a.max(this->b)); }


TEST(SimdVec2MaxTests, InfVector_ReturnsMinimumComponent)
{
    const flcn::simd::Vec2F vecA(1.0f, flcn::constants::INFINITY_F);
    const flcn::simd::Vec2F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F);

    EXPECT_VEC_CONTAINS(vecA.max(vecB), flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
}


/**************************************
 *             MIX TESTS              *
 **************************************/

TYPED_TEST(SimdVec2MixTests, ReturnsInterpolatedVector)
{ EXPECT_VEC_EQ(this->expected, this->a.mix(this->b, this->factor)); }


TEST_P(SimdVec2MixParameterizedTests, ReturnsInterpolatedVector)
{
    const auto& [a, b, factor, expected] = GetParam();
    EXPECT_VEC_EQ(expected, a.mix(b, factor));
}


/** @} */
