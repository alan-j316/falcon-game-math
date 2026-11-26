/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref flcn::Vec2 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



/**
 * @addtogroup T_Falcon_Vec2_Utils
 * @{
 */

#include "Vec2TestSetup.h"
#include "InterpolationTestFixture.h"

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
    INSTANTIATE_TEST_SUITE_P(Vec2UtilsInfVectors, Vec2InfCheckerTests,
                             ::testing::Values(Vec2UtilityParams{ flcn::Vec2(flcn::constants::INFINITY_F, 1.0f), true },
                                               Vec2UtilityParams{ flcn::Vec2(1.0f, flcn::constants::INFINITY_F), true },
                                               Vec2UtilityParams{
                                                   flcn::Vec2(flcn::constants::INFINITY_F, flcn::constants::INFINITY_F),
                                                   true },
                                               Vec2UtilityParams{ flcn::Vec2(1.0f, 1.0f), false }));



    /**
     * @brief Test fixture for @ref flcn::Vec2 NaN Checking.
     */
    class Vec2NaNCheckerTests: public testing::TestWithParam<Vec2UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Vec2UtilsNaNVectors, Vec2NaNCheckerTests,
                             ::testing::Values(Vec2UtilityParams{ flcn::Vec2(flcn::constants::NaN, 1.0f), true },
                                               Vec2UtilityParams{ flcn::Vec2(1.0f, flcn::constants::NaN), true },
                                               Vec2UtilityParams{
                                                   flcn::Vec2(flcn::constants::NaN, flcn::constants::NaN), true },
                                               Vec2UtilityParams{ flcn::Vec2(1.0f, 1.0f), false }));



    /**
     * @brief Test fixture for @ref flcn::Vec2 utilities, verifying across various integral types.
     */
    template <typename>
    class Vec2UtilsIntTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Vec2UtilsIntTests, SupportedIntegralTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Vec2 NORM_VEC_A(1.0f, 2.0f);
        constexpr flcn::Vec2 NORM_VEC_B(4.0f, 0.25f);
        constexpr flcn::Vec2 INF_VEC(flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
        constexpr flcn::Vec2 NAN_VEC(flcn::constants::NaN, flcn::constants::NaN);

        /// @test Verify that Vec2::hasInf returns a valid boolean at compile time.
        static_assert(NORM_VEC_A.hasInf() == false);
        static_assert(INF_VEC.hasInf() == true);
        static_assert(NAN_VEC.hasInf() == false);

        /// @test Verify that Vec2::hasInf(static wrapper) returns a valid boolean at compile time.
        static_assert(flcn::Vec2<float>::hasInf(NORM_VEC_A) == false);
        static_assert(flcn::Vec2<float>::hasInf(INF_VEC) == true);
        static_assert(flcn::Vec2<float>::hasInf(NAN_VEC) == false);

        /// @test Verify that Vec2::hasNaN returns a valid boolean at compile time.
        static_assert(NORM_VEC_A.hasNaN() == false);
        static_assert(INF_VEC.hasNaN() == false);
        static_assert(NAN_VEC.hasNaN() == true);

        /// @test Verify that Vec2::hasNaN(static wrapper) returns a valid boolean at compile time.
        static_assert(flcn::Vec2<float>::hasNaN(NORM_VEC_A) == false);
        static_assert(flcn::Vec2<float>::hasNaN(INF_VEC) == false);
        static_assert(flcn::Vec2<float>::hasNaN(NAN_VEC) == true);

        /// @test Verify that Vec2::min returns a valid vector at compile time.
        constexpr auto MIN_VEC        = NORM_VEC_A.min(NORM_VEC_B);
        static_assert(MIN_VEC.x() == 1.0f);
        static_assert(MIN_VEC.y() == 0.25f);

        /// @test Verify that Vec2::max returns a valid vector at compile time.
        constexpr auto MAX_VEC        = NORM_VEC_A.max(NORM_VEC_B);
        static_assert(MAX_VEC.x() == 4.0f);
        static_assert(MAX_VEC.y() == 2.0f);

        /// @test Verify that Vec2::mix returns a valid vector at compile time.
        constexpr auto MIX_VEC        = NORM_VEC_A.mix(NORM_VEC_B, 0.25f);
        static_assert(MIX_VEC.x() == 1.75f);
        static_assert(MIX_VEC.y() == 1.5625f);

    } // namespace static_tests
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



/**************************************
 *             MIN TESTS              *
 **************************************/

TYPED_TEST(Vec2MinTests, ReturnsMinimumComponentVector) { EXPECT_VEC_EQ(this->expectedMin, this->a.min(this->b)); }


TEST(Vec2MinTests, InfVector_ReturnsMinimumComponent)
{
    const flcn::Vec2F vecA(1.0f, flcn::constants::INFINITY_F);
    const flcn::Vec2F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F);

    EXPECT_VEC_CONTAINS(vecA.min(vecB), 1.0f, -flcn::constants::INFINITY_F);
}



/**************************************
 *             MAX TESTS              *
 **************************************/

TYPED_TEST(Vec2MaxTests, ReturnsMinimumComponentVector) { EXPECT_VEC_EQ(this->expectedMax, this->a.max(this->b)); }


TEST(Vec2MaxTests, InfVector_ReturnsMinimumComponent)
{
    const flcn::Vec2F vecA(1.0f, flcn::constants::INFINITY_F);
    const flcn::Vec2F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F);

    EXPECT_VEC_CONTAINS(vecA.max(vecB), flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
}



/**************************************
 *             MIX TESTS              *
 **************************************/

TYPED_TEST(Vec2MixTests, ReturnsInterpolatedVector)
{
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->expectedFP, this->a.mix(this->b, this->factor));
    }
    else
    {
        EXPECT_VEC_EQ(this->expectedInt, this->a.mix(this->b, this->factor));
    }
}


TEST_P(Vec2MixParameterizedTests, ReturnsInterpolatedVector)
{
    const auto& [a, b, factor, expected] = GetParam();
    EXPECT_VEC_EQ(expected, a.mix(b, factor));
}


/** @} */
