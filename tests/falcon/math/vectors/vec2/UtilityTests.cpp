/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref flcn::Vec2 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"


/**
 * @addtogroup T_FALCON_Vec2_Utils
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    template <typename T>
        requires std::floating_point<T>
    struct Vec2UtilityParams
    {
        flcn::Vec2<T> vec;
        bool expected;
    };


    /**
     * @brief Test fixture for @ref flcn::Vec2 Infinity Checking.
     */
    class Vec2InfCheckerTests: public testing::TestWithParam<Vec2UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Vec2UtilsInfVectors, Vec2InfCheckerTests,
        ::testing::Values(Vec2UtilityParams{ flcn::Vec2(flcn::constants::INFINITY_F, 1.0f), true },
                          Vec2UtilityParams{ flcn::Vec2(1.0f, flcn::constants::INFINITY_F), true },
                          Vec2UtilityParams{ flcn::Vec2(flcn::constants::INFINITY_F, flcn::constants::INFINITY_F), true },
                          Vec2UtilityParams{ flcn::Vec2(1.0f, 1.0f), false }));


    /**
     * @brief Test fixture for @ref flcn::Vec2 NaN Checking.
     */
    class Vec2NaNCheckerTests: public testing::TestWithParam<Vec2UtilityParams<float>> {};

    INSTANTIATE_TEST_SUITE_P(Vec2UtilsNaNVectors, Vec2NaNCheckerTests,
                             ::testing::Values(Vec2UtilityParams{ flcn::Vec2(flcn::constants::NaN, 1.0f), true },
                                 Vec2UtilityParams{ flcn::Vec2(1.0f, flcn::constants::NaN), true },
                                 Vec2UtilityParams{ flcn::Vec2(flcn::constants::NaN, flcn::constants::NaN),
                                 true },
                                 Vec2UtilityParams{ flcn::Vec2(1.0f, 1.0f), false }));


    /**
     * @brief Test fixture for @ref flcn::Vec2 utilities, verifying across various integral types.
     */
    template <typename>
    class Vec2UtilsIntTests: public testing::Test {};

    TYPED_TEST_SUITE(Vec2UtilsIntTests, SupportedIntegralTypes);

} // namespace


/**************************************
 *      INFINITY CHECKER TESTS        *
 **************************************/

/**
 * @test Verify that @ref std::Vec2::hasInf returns True if any of components are IEE754 infinity
 *       and False otherwise.
 */
TEST_P(Vec2InfCheckerTests, ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasInf());
}


/** @test Verify that @ref std::Vec2::hasInf returns False for integral types. */
TYPED_TEST(Vec2UtilsIntTests, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Vec2(value, value).hasInf());
}


/**
 * @test Verify that the static variant of @ref std::Vec2::hasInf returns True if any of components are IEE754
 *       infinity and False otherwise.
 */
TEST_P(Vec2InfCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Vec2<float>::hasInf(vec));
}


/** @test Verify that the static variant of @ref std::Vec2::hasInf returns False for integral types. */
TYPED_TEST(Vec2UtilsIntTests, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Vec2<TypeParam>::hasInf(flcn::Vec2(value, value)));
}


/**************************************
 *         NAN CHECKER TESTS          *
 **************************************/

/**
 * @test Verify that @ref std::Vec2::hasNaN returns True if any of components are IEE754 NaN(Not-a-Number)
 *       and False otherwise.
 */
TEST_P(Vec2NaNCheckerTests, ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasNaN());
}


/** @test Verify that @ref std::Vec2::hasNaN returns False for integral types. */
TYPED_TEST(Vec2UtilsIntTests, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Vec2(value, value).hasNaN());
}


/**
 * @test Verify that the static variant of @ref std::Vec2::hasNaN returns True if any of components are IEE754
 *       NaN(Not-a-Number) and False otherwise.
 */
TEST_P(Vec2NaNCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Vec2<float>::hasNaN(vec));
}


/** @test Verify that the static variant of @ref std::Vec2::hasNaN returns False for integral types. */
TYPED_TEST(Vec2UtilsIntTests, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Vec2<TypeParam>::hasNaN(flcn::Vec2(value, value)));
}

/** @} */
