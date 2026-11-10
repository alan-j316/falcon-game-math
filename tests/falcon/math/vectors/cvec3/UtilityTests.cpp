/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify @ref flcn::CVec3 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "CVec3TestSetup.h"



/**
 * @addtogroup T_Falcon_CVec3_Utils
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    template <typename T>
        requires std::floating_point<T>
    struct CVec3UtilityParams
    {
        flcn::CVec3<T> vec;
        bool expected;
    };


    /**
     * @brief Test fixture for @ref flcn::CVec3 Infinity Checking.
     */
    class CVec3InfCheckerTests: public testing::TestWithParam<CVec3UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(CVec3UtilsInfVectors, CVec3InfCheckerTests,
                         ::testing::Values(CVec3UtilityParams{ flcn::CVec3(flcn::constants::INFINITY_F, 1.0f, 1.0f), true },
                                           CVec3UtilityParams{ flcn::CVec3(1.0f, flcn::constants::INFINITY_F, 1.0f), true },
                                           CVec3UtilityParams{ flcn::CVec3(1.0f, 1.0f, flcn::constants::INFINITY_F), true },
                                           CVec3UtilityParams{ flcn::CVec3(flcn::constants::INFINITY_F,
                                                                        flcn::constants::INFINITY_F,
                                                                        flcn::constants::INFINITY_F),
                                                              true },
                                           CVec3UtilityParams{ flcn::CVec3(1.0f, 1.0f, 1.0f), false }));


    /**
         * @brief Test fixture for @ref flcn::CVec3 NaN Checking.
         */
    class CVec3NaNCheckerTests: public testing::TestWithParam<CVec3UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(CVec3UtilsNaNVectors, CVec3NaNCheckerTests,
                             ::testing::Values(CVec3UtilityParams{ flcn::CVec3(flcn::constants::NaN, 1.0f, 1.0f), true },
                                               CVec3UtilityParams{ flcn::CVec3(1.0f, flcn::constants::NaN, 1.0f), true },
                                               CVec3UtilityParams{ flcn::CVec3(1.0f, 1.0f, flcn::constants::NaN), true },
                                               CVec3UtilityParams{
                                                   flcn::CVec3(flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN),
                                                   true },
                                               CVec3UtilityParams{ flcn::CVec3(1.0f, 1.0f, 1.0f), false }));



    /**
         * @brief Test fixture for @ref flcn::CVec3 utilities, verifying across various integral types.
         */
    template <typename>
    class CVec3UtilsIntTests: public testing::Test
    {};
    TYPED_TEST_SUITE(CVec3UtilsIntTests, SupportedIntegralTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::CVec3 NORM_VEC(1.0f, 2.0f, 3.0f);
        constexpr flcn::CVec3 INF_VEC(flcn::constants::INFINITY_F, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
        constexpr flcn::CVec3 NAN_VEC(flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN);

        /// @test Verify that CVec3::hasInf returns a valid boolean at compile time.
        static_assert(NORM_VEC.hasInf() == false);
        static_assert(INF_VEC.hasInf() == true);
        static_assert(NAN_VEC.hasInf() == false);

        /// @test Verify that CVec3::hasInf(static wrapper) returns a valid boolean at compile time.
        static_assert(flcn::CVec3<float>::hasInf(NORM_VEC) == false);
        static_assert(flcn::CVec3<float>::hasInf(INF_VEC) == true);
        static_assert(flcn::CVec3<float>::hasInf(NAN_VEC) == false);

        /// @test Verify that CVec3::hasNaN returns a valid boolean at compile time.
        static_assert(NORM_VEC.hasNaN() == false);
        static_assert(INF_VEC.hasNaN() == false);
        static_assert(NAN_VEC.hasNaN() == true);

        /// @test Verify that CVec3::hasNaN(static wrapper) returns a valid boolean at compile time.
        static_assert(flcn::CVec3<float>::hasNaN(NORM_VEC) == false);
        static_assert(flcn::CVec3<float>::hasNaN(INF_VEC) == false);
        static_assert(flcn::CVec3<float>::hasNaN(NAN_VEC) == true);

    } // namespace
} // namespace



/**************************************
 *      INFINITY CHECKER TESTS        *
 **************************************/

/**
 * @test Verify that @ref std::CVec3::hasInf returns True if any of components are IEE754 infinity
 *       and False otherwise.
 */
TEST_P(CVec3InfCheckerTests, ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasInf());
}



/** @test Verify that @ref std::CVec3::hasInf returns False for integral types. */
TYPED_TEST(CVec3UtilsIntTests, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::CVec3(value, value, value).hasInf());
}


/**
 * @test Verify that the static variant of @ref std::CVec3::hasInf returns True if any of components are IEE754
 *       infinity and False otherwise.
 */
TEST_P(CVec3InfCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, flcn::CVec3<float>::hasInf(vec));
}


/** @test Verify that the static variant of @ref std::CVec3::hasInf returns False for integral types. */
TYPED_TEST(CVec3UtilsIntTests, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::CVec3<TypeParam>::hasInf(flcn::CVec3(value, value, value)));
}


/**************************************
 *         NAN CHECKER TESTS          *
 **************************************/

/**
 * @test Verify that @ref std::CVec3::hasNaN returns True if any of components are IEE754 NaN(Not-a-Number)
 *       and False otherwise.
 */
TEST_P(CVec3NaNCheckerTests, ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasNaN());
}



/** @test Verify that @ref std::CVec3::hasNaN returns False for integral types. */
TYPED_TEST(CVec3UtilsIntTests, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::CVec3(value, value, value).hasNaN());
}


/**
 * @test Verify that the static variant of @ref std::CVec3::hasNaN returns True if any of components are IEE754
 *       NaN(Not-a-Number) and False otherwise.
 */
TEST_P(CVec3NaNCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, flcn::CVec3<float>::hasNaN(vec));
}


/** @test Verify that the static variant of @ref std::CVec3::hasNaN returns False for integral types. */
TYPED_TEST(CVec3UtilsIntTests, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::CVec3<TypeParam>::hasNaN(flcn::CVec3(value, value, value)));
}

/** @} */
