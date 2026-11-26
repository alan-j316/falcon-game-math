/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 30, 2026
 *
 * @brief Verify @ref flcn::Vec4 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


/**
 * @addtogroup T_Falcon_Vec4_Utils
 * @{
 */

#include "Vec4TestSetup.h"

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
                          Vec4UtilityParams{ flcn::Vec4(flcn::constants::NaN, flcn::constants::NaN,
                                                        flcn::constants::NaN, flcn::constants::NaN),
                                             true },
                          Vec4UtilityParams{ flcn::Vec4(1.0f, 1.0f, 1.0f, 1.0f), false }));



    /**
     * @brief Test fixture for @ref flcn::Vec4 utilities, verifying across various integral types.
     */
    template <typename>
    class Vec4UtilsIntTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Vec4UtilsIntTests, SupportedIntegralTypes);


    /**
     * @brief Test fixture for @ref flcn::Vec4 min function.
     * @tparam T The numeric type of vector components.
     */
    template <typename T>
    class Vec4MinTests: public testing::Test
    {
    public:
        flcn::Vec4<T> a, b, expectedMin;

    protected:
        void SetUp() override
        {
            a           = { T(5.3923283), T(0.5383293), T(38.280234), T(15.93283) };
            b           = { T(3.239823), T(9.932803), T(121.2938223), T(102.39823) };
            expectedMin = { T(3.239823), T(0.5383293), T(38.280234), T(15.93283) };
        }
    };
    TYPED_TEST_SUITE(Vec4MinTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref flcn::Vec4 max function.
     * @tparam T The numeric type of vector components.
     */
    template <typename T>
    class Vec4MaxTests: public testing::Test
    {
    public:
        flcn::Vec4<T> a, b, expectedMax;

    protected:
        void SetUp() override
        {
            a           = { T(5.3923283), T(0.5383293), T(38.280234), T(15.93283) };
            b           = { T(3.239823), T(9.932803), T(121.2938223), T(102.39823) };
            expectedMax = { T(5.3923283), T(9.932803), T(121.2938223), T(102.39823) };
        }
    };
    TYPED_TEST_SUITE(Vec4MaxTests, SupportedArithmeticTypes);


    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Vec4 NORM_VEC_A(1.0f, 2.0f, 3.0f, 4.0f);
        constexpr flcn::Vec4 NORM_VEC_B(4.0f, 0.25f, 5.0f, -5.0f);
        constexpr flcn::Vec4 INF_VEC(flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                     flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
        constexpr flcn::Vec4 NAN_VEC(flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
                                     flcn::constants::NaN);

        /// @test Verify that Vec4::hasInf returns a valid boolean at compile time.
        static_assert(NORM_VEC_A.hasInf() == false);
        static_assert(INF_VEC.hasInf() == true);
        static_assert(NAN_VEC.hasInf() == false);

        /// @test Verify that Vec4::hasInf(static wrapper) returns a valid boolean at compile time.
        static_assert(flcn::Vec4<float>::hasInf(NORM_VEC_A) == false);
        static_assert(flcn::Vec4<float>::hasInf(INF_VEC) == true);
        static_assert(flcn::Vec4<float>::hasInf(NAN_VEC) == false);

        /// @test Verify that Vec4::hasNaN returns a valid boolean at compile time.
        static_assert(NORM_VEC_A.hasNaN() == false);
        static_assert(INF_VEC.hasNaN() == false);
        static_assert(NAN_VEC.hasNaN() == true);

        /// @test Verify that Vec4::hasNaN(static wrapper) returns a valid boolean at compile time.
        static_assert(flcn::Vec4<float>::hasNaN(NORM_VEC_A) == false);
        static_assert(flcn::Vec4<float>::hasNaN(INF_VEC) == false);
        static_assert(flcn::Vec4<float>::hasNaN(NAN_VEC) == true);


        /// @test Verify that Vec4::min returns a valid vector at compile time.
        constexpr auto MIN_VEC        = NORM_VEC_A.min(NORM_VEC_B);
        constexpr auto STATIC_MIN_VEC = flcn::Vec4F::min(NORM_VEC_A, NORM_VEC_B);
        static_assert(MIN_VEC.x() == 1.0f);
        static_assert(MIN_VEC.y() == 0.25f);
        static_assert(MIN_VEC.z() == 3.0f);
        static_assert(MIN_VEC.w() == -5.0f);
        static_assert(STATIC_MIN_VEC.x() == 1.0f);
        static_assert(STATIC_MIN_VEC.y() == 0.25f);
        static_assert(STATIC_MIN_VEC.z() == 3.0f);
        static_assert(STATIC_MIN_VEC.w() == -5.0f);

        /// @test Verify that Vec4::max returns a valid vector at compile time.
        constexpr auto MAX_VEC        = NORM_VEC_A.max(NORM_VEC_B);
        constexpr auto STATIC_MAX_VEC = flcn::Vec4F::max(NORM_VEC_A, NORM_VEC_B);
        static_assert(MAX_VEC.x() == 4.0f);
        static_assert(MAX_VEC.y() == 2.0f);
        static_assert(MAX_VEC.z() == 5.0f);
        static_assert(MAX_VEC.w() == 4.0f);
        static_assert(STATIC_MAX_VEC.x() == 4.0f);
        static_assert(STATIC_MAX_VEC.y() == 2.0f);
        static_assert(STATIC_MAX_VEC.z() == 5.0f);
        static_assert(STATIC_MAX_VEC.w() == 4.0f);

        /// @test Verify that Vec4::mix returns a valid vector at compile time.
        constexpr auto MIX_VEC        = NORM_VEC_A.mix(NORM_VEC_B, 0.25f);
        static_assert(MIX_VEC.x() == 1.75f);
        static_assert(MIX_VEC.y() == 1.5625f);
        static_assert(MIX_VEC.z() == 3.5f);
        static_assert(MIX_VEC.w() == 1.75f);

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



/**************************************
 *             MIN TESTS              *
 **************************************/

TYPED_TEST(Vec4MinTests, ReturnsMinimumComponentVector) { EXPECT_VEC_EQ(this->expectedMin, this->a.min(this->b)); }


TEST(Vec4MinTests, InfVector_ReturnsMinimumComponent)
{
    const flcn::Vec4F vecA(1.0f, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
    const flcn::Vec4F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                           -4.0f);

    EXPECT_VEC_CONTAINS(vecA.min(vecB), 1.0f, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F, -4.0f);
}


TYPED_TEST(Vec4MinTests, StaticWrapper_ReturnsMinimumComponentVector)
{ EXPECT_VEC_EQ(this->expectedMin, flcn::Vec4<TypeParam>::min(this->a, this->b)); }


TEST(Vec4MinTests, StaticWrapper_InfVector_ReturnsMinimumComponent)
{
    const flcn::Vec4F vecA(1.0f, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
    const flcn::Vec4F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                           -4.0f);

    EXPECT_VEC_CONTAINS(flcn::Vec4F::min(vecA, vecB), 1.0f, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                        -4.0f);
}


/**************************************
 *             MAX TESTS              *
 **************************************/

TYPED_TEST(Vec4MaxTests, ReturnsMinimumComponentVector) { EXPECT_VEC_EQ(this->expectedMax, this->a.max(this->b)); }


TEST(Vec4MaxTests, InfVector_ReturnsMinimumComponent)
{
    const flcn::Vec4F vecA(1.0f, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
    const flcn::Vec4F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                           -4.0f);

    EXPECT_VEC_CONTAINS(vecA.max(vecB), flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                        flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
}


TYPED_TEST(Vec4MaxTests, StaticWrapper_ReturnsMinimumComponentVector)
{ EXPECT_VEC_EQ(this->expectedMax, flcn::Vec4<TypeParam>::max(this->a, this->b)); }


TEST(Vec4MaxTests, StaticWrapper_InfVector_ReturnsMinimumComponent)
{
    const flcn::Vec4F vecA(1.0f, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
    const flcn::Vec4F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                           -4.0f);

    EXPECT_VEC_CONTAINS(flcn::Vec4F::max(vecA, vecB), flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                        flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
}



/**************************************
 *             MIX TESTS              *
 **************************************/

TYPED_TEST(Vec4MixTests, ReturnsInterpolatedVector)
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


TEST_P(Vec4MixParameterizedTests, ReturnsInterpolatedVector)
{
    const auto& [a, b, factor, expected] = GetParam();
    EXPECT_VEC_EQ(expected, a.mix(b, factor));
}

/** @} */
