/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify @ref flcn::simd::Vec3 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



/**
 * @addtogroup T_Falcon_Vec3_Utils
 * @{
 */

#include "InterpolationTestFixture.h"
#include "Vec3TestSetup.h"


namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    template <typename T>
        requires std::floating_point<T>
    struct Vec3UtilityParams
    {
        flcn::simd::Vec3<T> vec;
        bool expected;
    };


    /**
     * @brief Test fixture for @ref flcn::simd::Vec3 Infinity Checking.
     */
    class SimdVec3InfCheckerTests: public testing::TestWithParam<Vec3UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        SimdVec3UtilsInfVectors, SimdVec3InfCheckerTests,
        ::testing::Values(Vec3UtilityParams{ flcn::simd::Vec3(flcn::constants::INFINITY_F, 1.0f, 1.0f), true },
                          Vec3UtilityParams{ flcn::simd::Vec3(1.0f, flcn::constants::INFINITY_F, 1.0f), true },
                          Vec3UtilityParams{ flcn::simd::Vec3(1.0f, 1.0f, flcn::constants::INFINITY_F), true },
                          Vec3UtilityParams{ flcn::simd::Vec3(flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                                              flcn::constants::INFINITY_F),
                                             true },
                          Vec3UtilityParams{ flcn::simd::Vec3(1.0f, 1.0f, 1.0f), false }));


    /**
     * @brief Test fixture for @ref flcn::simd::Vec3 NaN Checking.
     */
    class SimdVec3NaNCheckerTests: public testing::TestWithParam<Vec3UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        SimdVec3UtilsNaNVectors, SimdVec3NaNCheckerTests,
        ::testing::Values(Vec3UtilityParams{ flcn::simd::Vec3(flcn::constants::NaN, 1.0f, 1.0f), true },
                          Vec3UtilityParams{ flcn::simd::Vec3(1.0f, flcn::constants::NaN, 1.0f), true },
                          Vec3UtilityParams{ flcn::simd::Vec3(1.0f, 1.0f, flcn::constants::NaN), true },
                          Vec3UtilityParams{
                              flcn::simd::Vec3(flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN),
                              true },
                          Vec3UtilityParams{ flcn::simd::Vec3(1.0f, 1.0f, 1.0f), false }));


    /**
     * @brief Test fixture for @ref flcn::simd::Vec3 utilities, verifying across various integral types.
     */
    template <typename>
    class SimdVec3UtilsIntTests: public testing::Test
    {};
    TYPED_TEST_SUITE(SimdVec3UtilsIntTests, SupportedIntegralTypes);
} // namespace



/**************************************
 *      INFINITY CHECKER TESTS        *
 **************************************/

/**
 * @test Verify that @ref std::Vec3::hasInf returns True if any of components are IEE754 infinity
 *       and False otherwise.
 */
TEST_P(SimdVec3InfCheckerTests, ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasInf());
}



/** @test Verify that @ref std::Vec3::hasInf returns False for integral types. */
TYPED_TEST(SimdVec3UtilsIntTests, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::simd::Vec3(value, value, value).hasInf());
}


/**
 * @test Verify that the static variant of @ref std::Vec3::hasInf returns True if any of components are IEE754
 *       infinity and False otherwise.
 */
TEST_P(SimdVec3InfCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, flcn::simd::Vec3<float>::hasInf(vec));
}


/** @test Verify that the static variant of @ref std::Vec3::hasInf returns False for integral types. */
TYPED_TEST(SimdVec3UtilsIntTests, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::simd::Vec3<TypeParam>::hasInf(flcn::simd::Vec3(value, value, value)));
}


/**************************************
 *         NAN CHECKER TESTS          *
 **************************************/

/**
 * @test Verify that @ref std::Vec3::hasNaN returns True if any of components are IEE754 NaN(Not-a-Number)
 *       and False otherwise.
 */
TEST_P(SimdVec3NaNCheckerTests, ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasNaN());
}



/** @test Verify that @ref std::Vec3::hasNaN returns False for integral types. */
TYPED_TEST(SimdVec3UtilsIntTests, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::simd::Vec3(value, value, value).hasNaN());
}


/**
 * @test Verify that the static variant of @ref std::Vec3::hasNaN returns True if any of components are IEE754
 *       NaN(Not-a-Number) and False otherwise.
 */
TEST_P(SimdVec3NaNCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, flcn::simd::Vec3<float>::hasNaN(vec));
}


/** @test Verify that the static variant of @ref std::Vec3::hasNaN returns False for integral types. */
TYPED_TEST(SimdVec3UtilsIntTests, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::simd::Vec3<TypeParam>::hasNaN(flcn::simd::Vec3(value, value, value)));
}

/**************************************
 *             MIN TESTS              *
 **************************************/

TYPED_TEST(SimdVec3MinTests, ReturnsMinimumComponentVector) { EXPECT_VEC_EQ(this->expectedMin, this->a.min(this->b)); }


TEST(SimdVec3MinTests, InfVector_ReturnsMinimumComponent)
{
    const flcn::Vec3F vecA(1.0f, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
    const flcn::Vec3F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);

    EXPECT_VEC_CONTAINS(vecA.min(vecB), 1.0f, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
}


/**************************************
 *             MAX TESTS              *
 **************************************/

TYPED_TEST(SimdVec3MaxTests, ReturnsMinimumComponentVector) { EXPECT_VEC_EQ(this->expectedMax, this->a.max(this->b)); }


TEST(SimdVec3MaxTests, InfVector_ReturnsMinimumComponent)
{
    const flcn::Vec3F vecA(1.0f, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
    const flcn::Vec3F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);

    EXPECT_VEC_CONTAINS(vecA.max(vecB), flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                        flcn::constants::INFINITY_F);
}


/**************************************
 *             MIX TESTS              *
 **************************************/

TYPED_TEST(SimdVec3MixTests, ReturnsInterpolatedVector)
{
    EXPECT_VEC_EQ(this->expected, this->a.mix(this->b, this->factor));
}


TEST_P(SimdVec3MixParameterizedTests, ReturnsInterpolatedVector)
{
    const auto& [a, b, factor, expected] = GetParam();
    EXPECT_VEC_EQ(expected, a.mix(b, factor));
}

/** @} */
