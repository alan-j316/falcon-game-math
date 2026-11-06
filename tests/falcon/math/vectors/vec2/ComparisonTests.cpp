/**
 * @file ComparisonTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref auto comparison operator (>, >=, <, <=) and
 *        their functional counterpart's (gt, gte, lt, lte) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"

#include <falcon/math/common/Constants.h>



/**
 * @addtogroup T_FALCON_Vec2_Comp
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
     * @brief Test fixture for @ref Vec2 comparisons.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec2ComparisonTests: public testing::Test
    {
    protected:
        flcn::Vec2<T> _vecA;
        flcn::Vec2<T> _vecB;
        flcn::Vec2<flcn::Mask_t<T>> _expectedGT, _expectedGTE, _expectedLT,
            _expectedLTE; // GT-> Greater Than, GTE-> Greater Than or Equal, LT -> Less than, LTE -> Less than or equal

        void SetUp() override
        {
            _vecA        = { T(1.1234568789), T(2.123458319) };
            _vecB        = { T(5.1234568789), T(1.123458319) };
            _expectedGT  = { False<T>, True<T> };
            _expectedGTE = { False<T>, True<T> };
            _expectedLT  = { True<T>, False<T> };
            _expectedLTE = { True<T>, False<T> };
        }
    };
    TYPED_TEST_SUITE(Vec2ComparisonTests, SupportedArithmeticTypes);

} // namespace



/**************************************
 *         GREATER THAN TESTS         *
 **************************************/

TYPED_TEST(Vec2ComparisonTests, GT_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
{
    const auto mask = this->_vecA.gt(this->_vecB);
    EXPECT_VEC_EQ(this->_expectedGT, mask);
}


TEST(Vec2ComparisonTests, GT_InfinityVector_ReturnsBooleanVectorWithCorrectValues)
{

    const flcn::Vec2 vec(1.2f, 4.5f);
    const flcn::Vec2 infVec(INF, -INF);
    const flcn::Vec2 expected(False<float>, True<float>);
    const auto mask = vec.gt(infVec);
    EXPECT_VEC_EQ(expected, mask);
}



TEST(Vec2ComparisonTests, GT_NaNVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::Vec2 vec(1.2f, 4.5f);
    const flcn::Vec2 infVec(NAN_F, NAN_F);
    const flcn::Vec2 expected(False<float>, False<float>);
    const auto mask = vec.gt(infVec);
    EXPECT_VEC_EQ(expected, mask);
}



TYPED_TEST(Vec2ComparisonTests, GreaterThanOperator_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
{
    const auto mask = this->_vecA > this->_vecB;
    EXPECT_VEC_EQ(this->_expectedGT, mask);
}


TYPED_TEST(Vec2ComparisonTests, StaticWrapper_GT_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
{
    const auto mask = flcn::Vec2<TypeParam>::gt(this->_vecA, this->_vecB);
    EXPECT_VEC_EQ(this->_expectedGT, mask);
}



/**************************************
 *    GREATER THAN OR EQUALS TESTS    *
 **************************************/

TYPED_TEST(Vec2ComparisonTests, GTE_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
{
    const auto mask = this->_vecA.gte(this->_vecB);
    EXPECT_VEC_EQ(this->_expectedGTE, mask);
}


TEST(Vec2ComparisonTests, GTE_InfinityVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::Vec2 vec(1.2f, 6.8f);
    const flcn::Vec2 infVec(INF, -INF);
    const flcn::Vec2 expected(False<float>, True<float>);

    const auto mask = vec.gte(infVec);
    EXPECT_VEC_EQ(expected, mask);
}


TEST(Vec2ComparisonTests, GTE_NanVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::Vec2 vec(1.2f, 6.8f);
    const flcn::Vec2 infVec(NAN_F, -5.9f);
    const flcn::Vec2 expected(False<float>, True<float>);

    const auto mask = vec.gte(infVec);
    EXPECT_VEC_EQ(expected, mask);
}


TYPED_TEST(Vec2ComparisonTests, GreaterThanOrEqualsOperator_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
{
    const auto mask = this->_vecA >= this->_vecB;
    EXPECT_VEC_EQ(this->_expectedGTE, mask);
}


TYPED_TEST(Vec2ComparisonTests, StaticWrapper_GTE_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
{
    const auto mask = flcn::Vec2<TypeParam>::gte(this->_vecA, this->_vecB);
    EXPECT_VEC_EQ(this->_expectedGTE, mask);
}



/**************************************
 *          LESS THAN TESTS           *
 **************************************/


TYPED_TEST(Vec2ComparisonTests, LT_ReturnsBooleanVectorWithElementsLessThanAsTrue)
{
    const auto mask = this->_vecA.lt(this->_vecB);
    EXPECT_VEC_EQ(this->_expectedLT, mask);
}


TEST(Vec2ComparisonTests, LT_InfinityVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::Vec2 vec(1.2f, 6.8f);
    const flcn::Vec2 infVec(INF, -INF);
    const flcn::Vec2 expected(True<float>, False<float>);

    const auto mask = vec.lt(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


TEST(Vec2ComparisonTests, LT_NanVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::Vec2 vec(1.2f, 6.8f);
    const flcn::Vec2 nanVec(NAN_F, -5.9f);
    const flcn::Vec2 expected(False<float>, False<float>);

#if defined(_MSC_VER) && !defined(__clang__)
    // MSVC constant evaluator incorrectly returns True<float> for NAN_F comparisons.
    // We fallback to 'const' (runtime) to verify the hardware/logic is correct.
    // Resharper disable all
    const auto mask = vec.lt(nanVec);
// Resharper restore all
#else
    // Clang and GCC follow IEEE 754 strictly at compile-time.
    const auto mask = vec.lt(nanVec);
#endif

    EXPECT_VEC_EQ(expected, mask);
}


TYPED_TEST(Vec2ComparisonTests, LessThanOperator_ReturnsBooleanVectorWithElementsLessThanAsTrue)
{
    const auto mask = this->_vecA < this->_vecB;
    EXPECT_VEC_EQ(this->_expectedLT, mask);
}


TYPED_TEST(Vec2ComparisonTests, StaticWrapper_LT_ReturnsBooleanVectorWithElementsLessThanAsTrue)
{
    const auto mask = flcn::Vec2<TypeParam>::lt(this->_vecA, this->_vecB);
    EXPECT_VEC_EQ(this->_expectedLT, mask);
}



/**************************************
 *      LESS THAN OR EQUALS TESTS     *
 **************************************/

TYPED_TEST(Vec2ComparisonTests, LTE_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
{
    const auto mask = this->_vecA.lte(this->_vecB);
    EXPECT_VEC_EQ(this->_expectedLTE, mask);
}

TEST(Vec2ComparisonTests, LTE_InfinityVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::Vec2 vec(1.2f, 6.8f);
    const flcn::Vec2 infVec(INF, -INF);
    const flcn::Vec2 expected(True<float>, False<float>);

    const auto mask = vec.lte(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


TEST(Vec2ComparisonTests, LTE_NanVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::Vec2 vec(1.2f, 6.8f);
    const flcn::Vec2 nanVec(NAN_F, -5.9f);
    const flcn::Vec2 expected(False<float>, False<float>);

    #if defined(_MSC_VER) && !defined(__clang__)
    // MSVC constant evaluator incorrectly returns True<float> for NAN_F comparisons.
    // We fallback to 'const' (runtime) to verify the hardware/logic is correct.
    // Resharper disable all
    const auto mask = vec.lte(nanVec);
    // Resharper restore all
    #else
    // Clang and GCC follow IEEE 754 strictly at compile-time.
    const auto mask = vec.lte(nanVec);
    #endif

    EXPECT_VEC_EQ(expected, mask);
}


TYPED_TEST(Vec2ComparisonTests, LessThanOrEqualOperator_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
{
    const auto mask = this->_vecA <= this->_vecB;
    EXPECT_VEC_EQ(this->_expectedLTE, mask);
}


TYPED_TEST(Vec2ComparisonTests, StaticWrapper_LTE_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
{
    const auto mask = flcn::Vec2<TypeParam>::lte(this->_vecA, this->_vecB);
    EXPECT_VEC_EQ(this->_expectedLTE, mask);
}

/** @} */
