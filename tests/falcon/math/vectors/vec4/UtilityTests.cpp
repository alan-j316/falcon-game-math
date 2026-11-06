/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 30, 2026
 *
 * @brief Verify @ref flcn::Vec4 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec4TestSetup.h"



/**
 * @addtogroup T_FALCON_Vec4_Utils
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    template <typename T>
        requires std::floating_point<T>
    struct Vec4UtilityParams
    {
        flcn::Vec4<T> vec;
        bool expected;
    };

    /**
     * @brief Test fixture for @ref flcn::Vec4 Infinity Checking.
     */
    class Vec4InfCheckerTests: public testing::TestWithParam<Vec4UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Vec4UtilsInfVectors, Vec4InfCheckerTests,
        ::testing::Values(Vec4UtilityParams{ flcn::Vec4(flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f), true },
                          Vec4UtilityParams{ flcn::Vec4(1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f), true },
                          Vec4UtilityParams{ flcn::Vec4(1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f), true },
                          Vec4UtilityParams{ flcn::Vec4(1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f), true },
                          Vec4UtilityParams{ flcn::Vec4(1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F), true },
                          Vec4UtilityParams{ flcn::Vec4(flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                                       flcn::constants::INFINITY_F, flcn::constants::INFINITY_F),
                                             true },
                          Vec4UtilityParams{ flcn::Vec4(1.0f, 1.0f, 1.0f, 1.0f), false }));


    /**
     * @brief Test fixture for @ref flcn::Vec4 NaN Checking.
     */
    class Vec4NaNCheckerTests: public testing::TestWithParam<Vec4UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Vec4UtilsNaNVectors, Vec4NaNCheckerTests,
        ::testing::Values(Vec4UtilityParams{ flcn::Vec4(flcn::constants::NaN, 1.0f, 1.0f, 1.0f), true },
                          Vec4UtilityParams{ flcn::Vec4(1.0f, flcn::constants::NaN, 1.0f, 1.0f), true },
                          Vec4UtilityParams{ flcn::Vec4(1.0f, 1.0f, flcn::constants::NaN, 1.0f), true },
                          Vec4UtilityParams{ flcn::Vec4(1.0f, 1.0f, flcn::constants::NaN, 1.0f), true },
                          Vec4UtilityParams{ flcn::Vec4(1.0f, 1.0f, 1.0f, flcn::constants::NaN), true },
                          Vec4UtilityParams{ flcn::Vec4(flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
                                                       flcn::constants::NaN),
                                             true },
                          Vec4UtilityParams{ flcn::Vec4(1.0f, 1.0f, 1.0f, 1.0f), false }));



    /**
     * @brief Test fixture for @ref flcn::Vec4 utilities, verifying across various integral types.
     */
    template <typename>
    class Vec4UtilsIntTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Vec4UtilsIntTests, SupportedIntegralTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Vec4 NORM_VEC(1.0f, 2.0f, 3.0f, 4.0f);
        constexpr flcn::Vec4 INF_VEC(flcn::constants::INFINITY_F, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                    flcn::constants::INFINITY_F);
        constexpr flcn::Vec4 NAN_VEC(flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN);

        /// @test Verify that Vec4::hasInf returns a valid boolean at compile time.
        static_assert(NORM_VEC.hasInf() == false);
        static_assert(INF_VEC.hasInf() == true);
        static_assert(NAN_VEC.hasInf() == false);

        /// @test Verify that Vec4::hasInf(static wrapper) returns a valid boolean at compile time.
        static_assert(flcn::Vec4<float>::hasInf(NORM_VEC) == false);
        static_assert(flcn::Vec4<float>::hasInf(INF_VEC) == true);
        static_assert(flcn::Vec4<float>::hasInf(NAN_VEC) == false);

        /// @test Verify that Vec4::hasNaN returns a valid boolean at compile time.
        static_assert(NORM_VEC.hasNaN() == false);
        static_assert(INF_VEC.hasNaN() == false);
        static_assert(NAN_VEC.hasNaN() == true);

        /// @test Verify that Vec4::hasNaN(static wrapper) returns a valid boolean at compile time.
        static_assert(flcn::Vec4<float>::hasNaN(NORM_VEC) == false);
        static_assert(flcn::Vec4<float>::hasNaN(INF_VEC) == false);
        static_assert(flcn::Vec4<float>::hasNaN(NAN_VEC) == true);

    } // namespace static_tests
} // namespace



/**************************************
 *      INFINITY CHECKER TESTS        *
 **************************************/

/**
 * @test Verify that @ref std::Vec4::hasInf returns True if any of components are IEE754 infinity
 *       and False otherwise.
 */
TEST_P(Vec4InfCheckerTests, ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasInf());
}


/** @test Verify that @ref std::Vec4::hasInf returns False for integral types. */
TYPED_TEST(Vec4UtilsIntTests, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Vec4(value, value, value, value).hasInf());
}


/**
 * @test Verify that the static variant of @ref std::Vec4::hasInf returns True if any of components are IEE754
 *       infinity and False otherwise.
 */
TEST_P(Vec4InfCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Vec4<float>::hasInf(vec));
}


/** @test Verify that the static variant of @ref std::Vec4::hasInf returns False for integral types. */
TYPED_TEST(Vec4UtilsIntTests, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Vec4<TypeParam>::hasInf(flcn::Vec4(value, value, value, value)));
}



/**************************************
 *         NAN CHECKER TESTS          *
 **************************************/

/**
 * @test Verify that @ref std::Vec4::hasNaN returns True if any of components are IEE754 NaN(Not-a-Number)
 *       and False otherwise.
 */
TEST_P(Vec4NaNCheckerTests, ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasNaN());
}


/** @test Verify that @ref std::Vec4::hasNaN returns False for integral types. */
TYPED_TEST(Vec4UtilsIntTests, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Vec4(value, value, value, value).hasNaN());
}


/**
 * @test Verify that the static variant of @ref std::Vec4::hasNaN returns True if any of components are IEE754
 *       NaN(Not-a-Number) and False otherwise.
 */
TEST_P(Vec4NaNCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Vec4<float>::hasNaN(vec));
}


/** @test Verify that the static variant of @ref std::Vec4::hasNaN returns False for integral types. */
TYPED_TEST(Vec4UtilsIntTests, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Vec4<TypeParam>::hasNaN(flcn::Vec4(value, value, value, value)));
}

/** @} */
