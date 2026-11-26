/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify @ref flcn::Vec3 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



/**
 * @addtogroup T_Falcon_Vec3_Utils
 * @{
 */

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
        flcn::Vec3<T> vec;
        bool expected;
    };


    /**
     * @brief Test fixture for @ref flcn::Vec3 Infinity Checking.
     */
    class Vec3InfCheckerTests: public testing::TestWithParam<Vec3UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Vec3UtilsInfVectors, Vec3InfCheckerTests,
        ::testing::Values(Vec3UtilityParams{ flcn::Vec3(flcn::constants::INFINITY_F, 1.0f, 1.0f), true },
                          Vec3UtilityParams{ flcn::Vec3(1.0f, flcn::constants::INFINITY_F, 1.0f), true },
                          Vec3UtilityParams{ flcn::Vec3(1.0f, 1.0f, flcn::constants::INFINITY_F), true },
                          Vec3UtilityParams{ flcn::Vec3(flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                                        flcn::constants::INFINITY_F),
                                             true },
                          Vec3UtilityParams{ flcn::Vec3(1.0f, 1.0f, 1.0f), false }));


    /**
     * @brief Test fixture for @ref flcn::Vec3 NaN Checking.
     */
    class Vec3NaNCheckerTests: public testing::TestWithParam<Vec3UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Vec3UtilsNaNVectors, Vec3NaNCheckerTests,
                             ::testing::Values(Vec3UtilityParams{ flcn::Vec3(flcn::constants::NaN, 1.0f, 1.0f), true },
                                               Vec3UtilityParams{ flcn::Vec3(1.0f, flcn::constants::NaN, 1.0f), true },
                                               Vec3UtilityParams{ flcn::Vec3(1.0f, 1.0f, flcn::constants::NaN), true },
                                               Vec3UtilityParams{ flcn::Vec3(flcn::constants::NaN, flcn::constants::NaN,
                                                                             flcn::constants::NaN),
                                                                  true },
                                               Vec3UtilityParams{ flcn::Vec3(1.0f, 1.0f, 1.0f), false }));



    /**
     * @brief Test fixture for @ref flcn::Vec3 utilities, verifying across various integral types.
     */
    template <typename>
    class Vec3UtilsIntTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Vec3UtilsIntTests, SupportedIntegralTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Vec3 NORM_VEC_A(1.0f, 2.0f, 3.0f);
        constexpr flcn::Vec3 NORM_VEC_B(4.0f, 0.25f, 5.0f);
        constexpr flcn::Vec3 INF_VEC(flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                     flcn::constants::INFINITY_F);
        constexpr flcn::Vec3 NAN_VEC(flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN);

        /// @test Verify that Vec3::hasInf returns a valid boolean at compile time.
        static_assert(NORM_VEC_A.hasInf() == false);
        static_assert(INF_VEC.hasInf() == true);
        static_assert(NAN_VEC.hasInf() == false);

        /// @test Verify that Vec3::hasInf(static wrapper) returns a valid boolean at compile time.
        static_assert(flcn::Vec3<float>::hasInf(NORM_VEC_A) == false);
        static_assert(flcn::Vec3<float>::hasInf(INF_VEC) == true);
        static_assert(flcn::Vec3<float>::hasInf(NAN_VEC) == false);

        /// @test Verify that Vec3::hasNaN returns a valid boolean at compile time.
        static_assert(NORM_VEC_A.hasNaN() == false);
        static_assert(INF_VEC.hasNaN() == false);
        static_assert(NAN_VEC.hasNaN() == true);

        /// @test Verify that Vec3::hasNaN(static wrapper) returns a valid boolean at compile time.
        static_assert(flcn::Vec3<float>::hasNaN(NORM_VEC_A) == false);
        static_assert(flcn::Vec3<float>::hasNaN(INF_VEC) == false);
        static_assert(flcn::Vec3<float>::hasNaN(NAN_VEC) == true);
        
        /// @test Verify that Vec3::min returns a valid vector at compile time.
        constexpr auto MIN_VEC        = NORM_VEC_A.min(NORM_VEC_B);
        static_assert(MIN_VEC.x() == 1.0f);
        static_assert(MIN_VEC.y() == 0.25f);
        static_assert(MIN_VEC.z() == 3.0f);

        /// @test Verify that Vec3::max returns a valid vector at compile time.
        constexpr auto MAX_VEC        = NORM_VEC_A.max(NORM_VEC_B);
        static_assert(MAX_VEC.x() == 4.0f);
        static_assert(MAX_VEC.y() == 2.0f);
        static_assert(MAX_VEC.z() == 5.0f);

        /// @test Verify that Vec3::mix returns a valid vector at compile time.
        constexpr auto MIX_VEC        = NORM_VEC_A.mix(NORM_VEC_B, 0.25f);
        static_assert(MIX_VEC.x() == 1.75f);
        static_assert(MIX_VEC.y() == 1.5625f);
        static_assert(MIX_VEC.z() == 3.5f);

    } // namespace static_tests
} // namespace



/**************************************
 *      INFINITY CHECKER TESTS        *
 **************************************/

/**
 * @test Verify that @ref std::Vec3::hasInf returns True if any of components are IEE754 infinity
 *       and False otherwise.
 */
TEST_P(Vec3InfCheckerTests, ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasInf());
}



/** @test Verify that @ref std::Vec3::hasInf returns False for integral types. */
TYPED_TEST(Vec3UtilsIntTests, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Vec3(value, value, value).hasInf());
}


/**
 * @test Verify that the static variant of @ref std::Vec3::hasInf returns True if any of components are IEE754
 *       infinity and False otherwise.
 */
TEST_P(Vec3InfCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Vec3<float>::hasInf(vec));
}


/** @test Verify that the static variant of @ref std::Vec3::hasInf returns False for integral types. */
TYPED_TEST(Vec3UtilsIntTests, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Vec3<TypeParam>::hasInf(flcn::Vec3(value, value, value)));
}


/**************************************
 *         NAN CHECKER TESTS          *
 **************************************/

/**
 * @test Verify that @ref std::Vec3::hasNaN returns True if any of components are IEE754 NaN(Not-a-Number)
 *       and False otherwise.
 */
TEST_P(Vec3NaNCheckerTests, ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasNaN());
}



/** @test Verify that @ref std::Vec3::hasNaN returns False for integral types. */
TYPED_TEST(Vec3UtilsIntTests, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Vec3(value, value, value).hasNaN());
}


/**
 * @test Verify that the static variant of @ref std::Vec3::hasNaN returns True if any of components are IEE754
 *       NaN(Not-a-Number) and False otherwise.
 */
TEST_P(Vec3NaNCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Vec3<float>::hasNaN(vec));
}


/** @test Verify that the static variant of @ref std::Vec3::hasNaN returns False for integral types. */
TYPED_TEST(Vec3UtilsIntTests, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Vec3<TypeParam>::hasNaN(flcn::Vec3(value, value, value)));
}


/**************************************
 *             MIN TESTS              *
 **************************************/

TYPED_TEST(Vec3MinTests, ReturnsMinimumComponentVector) { EXPECT_VEC_EQ(this->expectedMin, this->a.min(this->b)); }


TEST(Vec3MinTests, InfVector_ReturnsMinimumComponent)
{
    const flcn::Vec3F vecA(1.0f, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
    const flcn::Vec3F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);

    EXPECT_VEC_CONTAINS(vecA.min(vecB), 1.0f, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
}


/**************************************
 *             MAX TESTS              *
 **************************************/

TYPED_TEST(Vec3MaxTests, ReturnsMinimumComponentVector) { EXPECT_VEC_EQ(this->expectedMax, this->a.max(this->b)); }


TEST(Vec3MaxTests, InfVector_ReturnsMinimumComponent)
{
    const flcn::Vec3F vecA(1.0f, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
    const flcn::Vec3F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);

    EXPECT_VEC_CONTAINS(vecA.max(vecB), flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                        flcn::constants::INFINITY_F);
}


/**************************************
 *             MIX TESTS              *
 **************************************/

TYPED_TEST(Vec3MixTests, ReturnsInterpolatedVector)
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


TEST_P(Vec3MixParameterizedTests, ReturnsInterpolatedVector)
{
    const auto& [a, b, factor, expected] = GetParam();
    EXPECT_VEC_EQ(expected, a.mix(b, factor));
}


/** @} */
