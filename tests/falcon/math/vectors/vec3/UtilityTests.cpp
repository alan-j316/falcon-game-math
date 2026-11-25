/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify @ref flcn::Vec3 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "Vec3TestSetup.h"



/**
 * @addtogroup T_Falcon_Vec3_Utils
 * @{
 */

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
     * @brief Test fixture for @ref flcn::Vec3 min function.
     * @tparam T The numeric type of vector components.
     */
    template <typename T>
    class Vec3MinTests: public testing::Test
    {
    public:
        flcn::Vec3<T> a, b, expectedMin;

    protected:
        void SetUp() override
        {
            a           = { T(5.3923283), T(0.5383293), T(38.280234) };
            b           = { T(3.239823), T(9.932803), T(121.2938223) };
            expectedMin = { T(3.239823), T(0.5383293), T(38.280234) };
        }
    };
    TYPED_TEST_SUITE(Vec3MinTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::Vec3 max function.
     * @tparam T The numeric type of vector components.
     */
    template <typename T>
    class Vec3MaxTests: public testing::Test
    {
    public:
        flcn::Vec3<T> a, b, expectedMax;

    protected:
        void SetUp() override
        {
            a           = { T(5.3923283), T(0.5383293), T(38.280234) };
            b           = { T(3.239823), T(9.932803), T(121.2938223) };
            expectedMax = { T(5.3923283), T(9.932803), T(121.2938223) };
        }
    };
    TYPED_TEST_SUITE(Vec3MaxTests, SupportedArithmeticTypes);



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
        constexpr flcn::Vec3 NORM_VEC(1.0f, 2.0f, 3.0f);
        constexpr flcn::Vec3 INF_VEC(flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                     flcn::constants::INFINITY_F);
        constexpr flcn::Vec3 NAN_VEC(flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN);

        /// @test Verify that Vec3::hasInf returns a valid boolean at compile time.
        static_assert(NORM_VEC.hasInf() == false);
        static_assert(INF_VEC.hasInf() == true);
        static_assert(NAN_VEC.hasInf() == false);

        /// @test Verify that Vec3::hasInf(static wrapper) returns a valid boolean at compile time.
        static_assert(flcn::Vec3<float>::hasInf(NORM_VEC) == false);
        static_assert(flcn::Vec3<float>::hasInf(INF_VEC) == true);
        static_assert(flcn::Vec3<float>::hasInf(NAN_VEC) == false);

        /// @test Verify that Vec3::hasNaN returns a valid boolean at compile time.
        static_assert(NORM_VEC.hasNaN() == false);
        static_assert(INF_VEC.hasNaN() == false);
        static_assert(NAN_VEC.hasNaN() == true);

        /// @test Verify that Vec3::hasNaN(static wrapper) returns a valid boolean at compile time.
        static_assert(flcn::Vec3<float>::hasNaN(NORM_VEC) == false);
        static_assert(flcn::Vec3<float>::hasNaN(INF_VEC) == false);
        static_assert(flcn::Vec3<float>::hasNaN(NAN_VEC) == true);

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


TYPED_TEST(Vec3MinTests, StaticWrapper_ReturnsMinimumComponentVector)
{ EXPECT_VEC_EQ(this->expectedMin, flcn::Vec3<TypeParam>::min(this->a, this->b)); }


TEST(Vec3MinTests, StaticWrapper_InfVector_ReturnsMinimumComponent)
{
    const flcn::Vec3F vecA(1.0f, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
    const flcn::Vec3F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);

    EXPECT_VEC_CONTAINS(flcn::Vec3F::min(vecA, vecB), 1.0f, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
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


TYPED_TEST(Vec3MaxTests, StaticWrapper_ReturnsMinimumComponentVector)
{ EXPECT_VEC_EQ(this->expectedMax, flcn::Vec3<TypeParam>::max(this->a, this->b)); }


TEST(Vec3MaxTests, StaticWrapper_InfVector_ReturnsMinimumComponent)
{
    const flcn::Vec3F vecA(1.0f, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
    const flcn::Vec3F vecB(flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);

    EXPECT_VEC_CONTAINS(flcn::Vec3F::max(vecA, vecB), flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                        flcn::constants::INFINITY_F);
}


/** @} */
