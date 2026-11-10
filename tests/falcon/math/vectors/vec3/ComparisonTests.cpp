/**
 * @file ComparisonTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 10, 2026
 *
 * @brief Verify @ref flcn::Vec3 comparison operator (>, >=, <, <=) and their functional
 *        counterpart's (gt, gte, lt, lte) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"

#include <falcon/math/common/Constants.h>




/**
 * @addtogroup T_Falcon_Vec3_Comp
 * @{
 */

namespace
{

    constexpr auto NAN_F = flcn::constants::NaN;
    constexpr auto INF   = flcn::constants::INFINITY_F;

    template <typename T>
    constexpr auto False = flcn::FalseMask<flcn::Mask_t<T>>;
    template <typename T>
    constexpr auto True = flcn::TrueMask<flcn::Mask_t<T>>;

    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec3 comparisons.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec3ComparisonTests: public testing::Test
    {
    protected:
        flcn::Vec3<T> _vecA;
        flcn::Vec3<T> _vecB;
        flcn::Vec3<flcn::Mask_t<T>> _expectedGT, _expectedGTE, _expectedLT,
            _expectedLTE; // GT-> Greater Than, GTE-> Greater Than or Equal, LT -> Less than, LTE -> Less than or equal

        void SetUp() override
        {
            _vecA        = { T(1.1234568789), T(2.123458319), T(5.123412593891) };
            _vecB        = { T(5.1234568789), T(1.123458319), T(8.123412593891) };
            _expectedGT  = { False<T>, True<T>, False<T> };
            _expectedGTE = { False<T>, True<T>, False<T> };
            _expectedLT  = { True<T>, False<T>, True<T> };
            _expectedLTE = { True<T>, False<T>, True<T> };
        }
    };
    TYPED_TEST_SUITE(Vec3ComparisonTests, SupportedArithmeticTypes);
} // namespace



/**************************************
 *         GREATER THAN TESTS         *
 **************************************/

/**
 * @test Verify that the greater-than (gt) function perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec3ComparisonTests, GT_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
{
    const flcn::Vec3 mask = this->_vecA.gt(this->_vecB);
    EXPECT_VEC_EQ(this->_expectedGT, mask);
}


/**
 * @test Verify that the greater-than operator perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec3ComparisonTests, GreaterThanOperator_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
{
    const flcn::Vec3 mask = this->_vecA > this->_vecB;
    EXPECT_VEC_EQ(this->_expectedGT, mask);
}


/**
 * @test Verify that the static variant of greater-than (gt) function performs a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec3ComparisonTests, StaticWrapper_GT_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
{
    const flcn::Vec3 mask = flcn::Vec3<TypeParam>::gt(this->_vecA, this->_vecB);
    EXPECT_VEC_EQ(this->_expectedGT, mask);
}


/**
 * @test Verify that the greater-than (gt) function perform a component-wise comparison
 *       when handling infinite values.
 */
TEST(Vec3Comparison, GT_InfinityVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::Vec3 vec(1.2f, 4.5f, 6.8f);
    const flcn::Vec3 infVec(INF, INF, -INF);
    const flcn::Vec3 expected(False<float>, False<float>, True<float>);

    const flcn::Vec3 mask = vec.gt(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @test Verify that the greater-than (gt) function perform a component-wise comparison
 *       when handling NaN values.
 */
TEST(Vec3Comparison, GT_NaNVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::Vec3 vec(1.2f, 4.5f, 6.8f);
    const flcn::Vec3 infVec(NAN_F, NAN_F, -5.9f);
    const flcn::Vec3 expected(False<float>, False<float>, True<float>);

    const flcn::Vec3 mask = vec.gt(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**************************************
 *    GREATER THAN OR EQUALS TESTS    *
 **************************************/

/**
 * @test Verify that the greater-than-or-equal (gte) function perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec3ComparisonTests, GTE_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
{
    const flcn::Vec3 mask = this->_vecA.gte(this->_vecB);

    EXPECT_VEC_EQ(this->_expectedGTE, mask);
}


/**
 * @test Verify that the greater-than-or-equal operator performs a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec3ComparisonTests, GreaterThanOrEqualsOperator_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
{
    const flcn::Vec3 mask = this->_vecA >= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedGTE, mask);
}


/**
 * @test Verify that the static variant of greater-than-or-equal (gte) function perform a component-wise
 *       comparison and returns the correct boolean mask.
 */
TYPED_TEST(Vec3ComparisonTests, StaticWrapper_GTE_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
{
    const flcn::Vec3 mask = flcn::Vec3<TypeParam>::gte(this->_vecA, this->_vecB);

    EXPECT_VEC_EQ(this->_expectedGTE, mask);
}


/**
 * @test Verify that the greater-than-or-equal (gte) function perform a component-wise comparison
 *       when handling infinite values.
 */
TEST(Vec3Comparison, GTE_InfinityVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::Vec3 vec(1.2f, 4.5f, 6.8f);
    const flcn::Vec3 infVec(INF, INF, -INF);
    const flcn::Vec3 expected(False<float>, False<float>, True<float>);

    const flcn::Vec3 mask = vec.gte(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @test Verify that the greater-than-or-equal (gte) function perform a component-wise comparison
 *       when handling NaN values.
 */
TEST(Vec3Comparison, GTE_NanVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::Vec3 vec(1.2f, 4.5f, 6.8f);
    const flcn::Vec3 infVec(NAN_F, NAN_F, -5.9f);
    const flcn::Vec3 expected(False<float>, False<float>, True<float>);

    const flcn::Vec3 mask = vec.gte(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**************************************
 *          LESS THAN TESTS           *
 **************************************/

/**
 * @test Verify that the less-than (lt) function perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec3ComparisonTests, LT_ReturnsBooleanVectorWithElementsLessThanAsTrue)
{
    const flcn::Vec3 mask = this->_vecA.lt(this->_vecB);

    EXPECT_VEC_EQ(this->_expectedLT, mask);
}


/**
 * @test Verify that the less-than operator perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec3ComparisonTests, LessThanOperator_ReturnsBooleanVectorWithElementsLessThanAsTrue)
{
    const flcn::Vec3 mask = this->_vecA < this->_vecB;

    EXPECT_VEC_EQ(this->_expectedLT, mask);
}


/**
 * @test Verify that the static variant of less-than (lt) function perform a component-wise comparison and
 *		 returns the correct boolean mask.
 */
TYPED_TEST(Vec3ComparisonTests, StaticWrapper_LT_ReturnsBooleanVectorWithElementsLessThanAsTrue)
{
    const flcn::Vec3 mask = flcn::Vec3<TypeParam>::lt(this->_vecA, this->_vecB);

    EXPECT_VEC_EQ(this->_expectedLT, mask);
}


/**
 * @test Verify that the less-than (lt) function perform a component-wise comparison
 *       when handling infinite values.
 */
TEST(Vec3Comparison, LT_InfinityVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::Vec3 vec(1.2f, 4.5f, 6.8f);
    const flcn::Vec3 infVec(INF, INF, -INF);
    const flcn::Vec3 expected(True<float>, True<float>, False<float>);

    const flcn::Vec3 mask = vec.lt(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @test Verify that the less-than (lt) function perform a component-wise comparison
 *       when handling NaN values.
 */
TEST(Vec3Comparison, LT_NanVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::Vec3 vec(1.2f, 4.5f, 6.8f);
    const flcn::Vec3 nanVec(NAN_F, NAN_F, -5.9f);
    const flcn::Vec3 expected(False<float>, False<float>, False<float>);

#if defined(_MSC_VER) && !defined(__clang__)
    // MSVC constant evaluator incorrectly returns True<float> for NAN_F comparisons.
    // We fallback to 'const' (runtime) to verify the hardware/logic is correct.
    // Resharper disable all
    const flcn::Vec3 mask = vec.lt(nanVec);
    // Resharper restore all
#else
    // Clang and GCC follow IEEE 754 strictly at compile-time.
    const flcn::Vec3 mask = vec.lt(nanVec);
#endif

    EXPECT_VEC_EQ(expected, mask);
}


/**************************************
 *      LESS THAN OR EQUALS TESTS     *
 **************************************/

/**
 * @test Verify that the less-than-or-equal (lte) function perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec3ComparisonTests, LTE_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
{
    const flcn::Vec3 mask = this->_vecA.lte(this->_vecB);

    EXPECT_VEC_EQ(this->_expectedLTE, mask);
}


/**
 * @test Verify that the less-than-or-equal operator perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec3ComparisonTests, LessThanOrEqualOperator_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
{
    const flcn::Vec3 mask = this->_vecA <= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedLTE, mask);
}


/**
 * @test Verify that the static variant of less-than-or-equal (lte) function perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec3ComparisonTests, StaticWrapper_LTE_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
{
    const flcn::Vec3 mask = flcn::Vec3<TypeParam>::lte(this->_vecA, this->_vecB);

    EXPECT_VEC_EQ(this->_expectedLTE, mask);
}


/**
 * @test Verify that the less-than-or-equal (lte) function perform a component-wise comparison
 *       when handling infinite values.
 */
TEST(Vec3Comparison, LTE_InfinityVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::Vec3 vec(1.2f, 4.5f, 6.8f);
    const flcn::Vec3 infVec(INF, INF, -INF);
    const flcn::Vec3 expected(True<float>, True<float>, False<float>);

    const flcn::Vec3 mask = vec.lte(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @test Verify that the less-than-or-equal (lte) function perform a component-wise comparison
 *       when handling NaN values.
 */
TEST(Vec3Comparison, LTE_NanVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::Vec3 vec(1.2f, 4.5f, 6.8f);
    const flcn::Vec3 nanVec(NAN_F, NAN_F, -5.9f);
    const flcn::Vec3 expected(False<float>, False<float>, False<float>);

#if defined(_MSC_VER) && !defined(__clang__)
    // MSVC constant evaluator incorrectly returns True<float> for NAN_F comparisons.
    // We fallback to 'const' (runtime) to verify the hardware/logic is correct.
    // Resharper disable all
    const flcn::Vec3 mask = vec.lte(nanVec);
    // Resharper restore all
#else
    // Clang and GCC follow IEEE 754 strictly at compile-time.
    const flcn::Vec3 mask = vec.lte(nanVec);
#endif

    EXPECT_VEC_EQ(expected, mask);
}

/** @} */
