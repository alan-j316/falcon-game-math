/**
 * @file ComparisonTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify @ref flcn::Vec3<bool> comparison operator (>, >=, <, <=) and their functional counterpart's (gt,
 * gte, lt, lte) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"

#include <falcon/math/common/Constants.h>




/**
 * @addtogroup T_FALCON_Vec3_Comp
 * @{
 */

namespace
{

    constexpr auto NAN_F = flcn::constants::NaN;
    constexpr auto INF   = flcn::constants::INFINITY_F;


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
        flcn::Vec3<bool> _expectedGT, _expectedGTE, _expectedLT,
            _expectedLTE; // GT-> Greater Than, GTE-> Greater Than or Equal, LT -> Less than, LTE -> Less than or equal

        void SetUp() override
        {
            _vecA        = { T(1.1234568789), T(2.123458319), T(5.123412593891) };
            _vecB        = { T(5.1234568789), T(1.123458319), T(8.123412593891) };
            _expectedGT  = { false, true, false };
            _expectedGTE = { false, true, false };
            _expectedLT  = { true, false, true };
            _expectedLTE = { true, false, true };
        }
    };
    TYPED_TEST_SUITE(Vec3ComparisonTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Vec3 VEC_A(1, 2, 5);
        constexpr flcn::Vec3 VEC_B(1, 3, 4);
        /// @test Verify that greater than operator (operator>) returns a valid mask at compile time.
        constexpr auto GT_OP_MASK_VEC = VEC_A > VEC_B;
        static_assert(GT_OP_MASK_VEC.x() == false);
        static_assert(GT_OP_MASK_VEC.y() == false);
        static_assert(GT_OP_MASK_VEC.z() == true);

        /// @test Verify that greater than operator (gt) returns a valid mask at compile time.
        constexpr auto GT_MASK_VEC = VEC_A.gt(VEC_B);
        static_assert(GT_MASK_VEC.x() == false);
        static_assert(GT_MASK_VEC.y() == false);
        static_assert(GT_MASK_VEC.z() == true);

        /// @test Verify that greater than operator (gt-static wrapper) returns a valid mask at compile time.
        constexpr auto GT_MASK_VEC_STATIC = flcn::Vec3<int>::gt(VEC_A, VEC_B);
        static_assert(GT_MASK_VEC_STATIC.x() == false);
        static_assert(GT_MASK_VEC_STATIC.y() == false);
        static_assert(GT_MASK_VEC_STATIC.z() == true);


        /// @test Verify that greater or equals operator (operator>=) returns a valid mask at compile time.
        constexpr auto GTE_OP_MASK_VEC = VEC_A >= VEC_B;
        static_assert(GTE_OP_MASK_VEC.x() == true);
        static_assert(GTE_OP_MASK_VEC.y() == false);
        static_assert(GTE_OP_MASK_VEC.z() == true);

        /// @test Verify that greater than or equals operator (gte) returns a valid mask at compile time.
        constexpr auto GTE_MASK_VEC = VEC_A.gte(VEC_B);
        static_assert(GTE_MASK_VEC.x() == true);
        static_assert(GTE_MASK_VEC.y() == false);
        static_assert(GTE_MASK_VEC.z() == true);

        /// @test Verify that greater than or equals operator (gte-static wrapper) returns a valid mask at compile time.
        constexpr auto GTE_MASK_VEC_STATIC = flcn::Vec3<int>::gte(VEC_A, VEC_B);
        static_assert(GTE_MASK_VEC_STATIC.x() == true);
        static_assert(GTE_MASK_VEC_STATIC.y() == false);
        static_assert(GTE_MASK_VEC_STATIC.z() == true);


        /// @test Verify that less than operator (operator<) returns a valid mask at compile time.
        constexpr auto LT_OP_MASK_VEC = VEC_A < VEC_B;
        static_assert(LT_OP_MASK_VEC.x() == false);
        static_assert(LT_OP_MASK_VEC.y() == true);
        static_assert(LT_OP_MASK_VEC.z() == false);

        /// @test Verify that less than operator (lt) returns a valid mask at compile time.
        constexpr auto LT_MASK_VEC = VEC_A.lt(VEC_B);
        static_assert(LT_MASK_VEC.x() == false);
        static_assert(LT_MASK_VEC.y() == true);
        static_assert(LT_MASK_VEC.z() == false);

        /// @test Verify that less than operator (lt-static wrapper) returns a valid mask at compile time.
        constexpr auto LT_MASK_VEC_STATIC = flcn::Vec3<int>::lt(VEC_A, VEC_B);
        static_assert(LT_MASK_VEC_STATIC.x() == false);
        static_assert(LT_MASK_VEC_STATIC.y() == true);
        static_assert(LT_MASK_VEC_STATIC.z() == false);


        constexpr auto LTE_OP_MASK_VEC = VEC_A <= VEC_B;
        /// @test Verify that less than or equals operator (operator<=) returns a valid mask at compile time.
        static_assert(LTE_OP_MASK_VEC.x() == true);
        static_assert(LTE_OP_MASK_VEC.y() == true);
        static_assert(LTE_OP_MASK_VEC.z() == false);

        /// @test Verify that less than or equals operator (lte) returns a valid mask at compile time.
        constexpr auto LTE_MASK_VEC = VEC_A.lte(VEC_B);
        static_assert(LTE_MASK_VEC.x() == true);
        static_assert(LTE_MASK_VEC.y() == true);
        static_assert(LTE_MASK_VEC.z() == false);

        /// @test Verify that less than or equals operator (lte-static wrapper) returns a valid mask at compile time.
        constexpr auto LTE_MASK_VEC_STATIC = flcn::Vec3<int>::lte(VEC_A, VEC_B);
        static_assert(LTE_MASK_VEC_STATIC.x() == true);
        static_assert(LTE_MASK_VEC_STATIC.y() == true);
        static_assert(LTE_MASK_VEC_STATIC.z() == false);

    } // namespace static_tests
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
    const flcn::Vec3<bool> mask = this->_vecA.gt(this->_vecB);

    EXPECT_VEC_EQ(this->_expectedGT, mask);
}


/**
 * @test Verify that the greater-than operator perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec3ComparisonTests, GreaterThanOperator_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
{
    const flcn::Vec3<bool> mask = this->_vecA > this->_vecB;

    EXPECT_VEC_EQ(this->_expectedGT, mask);
}


/**
 * @test Verify that the static variant of greater-than (gt) function performs a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec3ComparisonTests, StaticWrapper_GT_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
{
    const flcn::Vec3<bool> mask = flcn::Vec3<TypeParam>::gt(this->_vecA, this->_vecB);

    EXPECT_VEC_EQ(this->_expectedGT, mask);
}


/**
 * @test Verify that the greater-than (gt) function perform a component-wise comparison
 *       when handling infinite values.
 */
TEST(Vec3Comparison, GT_InfinityVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::Vec3 vec(1.2, 4.5, 6.8);
    const flcn::Vec3 infVec(INF, INF, -INF);
    const flcn::Vec3 expected(false, false, true);

    const flcn::Vec3<bool> mask = vec.gt(infVec);

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
    const flcn::Vec3 expected(false, false, true);

    const flcn::Vec3<bool> mask = vec.gt(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @test Verify that the greater-than (gt) function perform a component-wise comparison
 *       when handling vectors of different types.
 */
TEST(Vec3Comparison, MixedType_GT_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    const flcn::Vec3 vecA(1.2, 4.5, 7.5);
    const flcn::Vec3 vecB(5, 6, 7);
    const flcn::Vec3 expected(false, false, true);

    // When compared with greater than or equal
    const flcn::Vec3<bool> mask = vecA.gt(vecB);

    // Then, the resulting elements are as expected
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
    const flcn::Vec3<bool> mask = this->_vecA.gte(this->_vecB);

    EXPECT_VEC_EQ(this->_expectedGTE, mask);
}


/**
 * @test Verify that the greater-than-or-equal operator performs a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec3ComparisonTests, GreaterThanOrEqualsOperator_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
{
    const flcn::Vec3<bool> mask = this->_vecA >= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedGTE, mask);
}


/**
 * @test Verify that the static variant of greater-than-or-equal (gte) function perform a component-wise
 *       comparison and returns the correct boolean mask.
 */
TYPED_TEST(Vec3ComparisonTests, StaticWrapper_GTE_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
{
    const flcn::Vec3<bool> mask = flcn::Vec3<TypeParam>::gte(this->_vecA, this->_vecB);

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
    const flcn::Vec3 expected(false, false, true);

    const flcn::Vec3<bool> mask = vec.gte(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @test Verify that the greater-than-or-equal (gte) function perform a component-wise comparison
 *       when handling NaN values.
 */
TEST(Vec3Comparison, GTE_NanVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::Vec3 vec(1.2, 4.5, 6.8);
    const flcn::Vec3 infVec(NAN_F, NAN_F, -5.9f);
    const flcn::Vec3 expected(false, false, true);

    const flcn::Vec3<bool> mask = vec.gte(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @test Verify that the greater-than-or-equal (gte) function performs a component-wise comparison
 *       when handling vectors of different types.
 */
TEST(Vec3Comparison, GTE_MixedType_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    const flcn::Vec3 vecA(1.2, 4.5, 7.5);
    const flcn::Vec3 vecB(5, 6, 7);
    const flcn::Vec3 expected(false, false, true);

    // When compared with greater or equal than
    const flcn::Vec3<bool> mask = vecA.gte(vecB);

    // Then, the resulting elements are as expected
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
    const flcn::Vec3<bool> mask = this->_vecA.lt(this->_vecB);

    EXPECT_VEC_EQ(this->_expectedLT, mask);
}


/**
 * @test Verify that the less-than operator perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec3ComparisonTests, LessThanOperator_ReturnsBooleanVectorWithElementsLessThanAsTrue)
{
    const flcn::Vec3<bool> mask = this->_vecA < this->_vecB;

    EXPECT_VEC_EQ(this->_expectedLT, mask);
}


/**
 * @test Verify that the static variant of less-than (lt) function perform a component-wise comparison and
 *		 returns the correct boolean mask.
 */
TYPED_TEST(Vec3ComparisonTests, StaticWrapper_LT_ReturnsBooleanVectorWithElementsLessThanAsTrue)
{
    const flcn::Vec3<bool> mask = flcn::Vec3<TypeParam>::lt(this->_vecA, this->_vecB);

    EXPECT_VEC_EQ(this->_expectedLT, mask);
}


/**
 * @test Verify that the less-than (lt) function perform a component-wise comparison
 *       when handling infinite values.
 */
TEST(Vec3Comparison, LT_InfinityVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::Vec3 vec(1.2, 4.5, 6.8);
    const flcn::Vec3 infVec(INF, INF, -INF);
    const flcn::Vec3 expected(true, true, false);

    const flcn::Vec3<bool> mask = vec.lt(infVec);

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
    const flcn::Vec3 expected(false, false, false);

#if defined(_MSC_VER) && !defined(__clang__)
    // MSVC constant evaluator incorrectly returns true for NAN_F comparisons.
    // We fallback to 'const' (runtime) to verify the hardware/logic is correct.
    // Resharper disable all
    const flcn::Vec3<bool> mask = vec.lt(nanVec);
    // Resharper restore all
#else
    // Clang and GCC follow IEEE 754 strictly at compile-time.
    const flcn::Vec3<bool> mask = vec.lt(nanVec);
#endif

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @test Verify that the less-than (lt) function perform a component-wise comparison
 *       when handling vectors of different types.
 */
TEST(Vec3Comparison, LT_MixedType_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    const flcn::Vec3 vecA(1.2, 4.5, 7.5);
    const flcn::Vec3 vecB(5, 6, 7);
    const flcn::Vec3 expected(true, true, false);

    // When compared with less than or equal
    const flcn::Vec3<bool> mask = vecA.lt(vecB);

    // Then, the resulting elements are as expected
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
    const flcn::Vec3<bool> mask = this->_vecA.lte(this->_vecB);

    EXPECT_VEC_EQ(this->_expectedLTE, mask);
}


/**
 * @test Verify that the less-than-or-equal operator perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec3ComparisonTests, LessThanOrEqualOperator_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
{
    const flcn::Vec3<bool> mask = this->_vecA <= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedLTE, mask);
}


/**
 * @test Verify that the static variant of less-than-or-equal (lte) function perform a component-wise comparison and
 *       returns the correct boolean mask.
 */
TYPED_TEST(Vec3ComparisonTests, StaticWrapper_LTE_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
{
    const flcn::Vec3<bool> mask = flcn::Vec3<TypeParam>::lte(this->_vecA, this->_vecB);

    EXPECT_VEC_EQ(this->_expectedLTE, mask);
}


/**
 * @test Verify that the less-than-or-equal (lte) function perform a component-wise comparison
 *       when handling infinite values.
 */
TEST(Vec3Comparison, LTE_InfinityVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::Vec3 vec(1.2, 4.5, 6.8);
    const flcn::Vec3 infVec(INF, INF, -INF);
    const flcn::Vec3 expected(true, true, false);

    const flcn::Vec3<bool> mask = vec.lte(infVec);

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
    const flcn::Vec3 expected(false, false, false);

#if defined(_MSC_VER) && !defined(__clang__)
    // MSVC constant evaluator incorrectly returns true for NAN_F comparisons.
    // We fallback to 'const' (runtime) to verify the hardware/logic is correct.
    // Resharper disable all
    const flcn::Vec3<bool> mask = vec.lte(nanVec);
    // Resharper restore all
#else
    // Clang and GCC follow IEEE 754 strictly at compile-time.
    const flcn::Vec3<bool> mask = vec.lte(nanVec);
#endif

    EXPECT_VEC_EQ(expected, mask);
}


/**
 * @test Verify that the less-than-or-equal (lte) function perform a component-wise comparison
 *       when handling vectors of different types.
 */
TEST(Vec3Comparison, LTE_MixedType_LTE_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    const flcn::Vec3 vecA(1.2, 4.5, 7.5);
    const flcn::Vec3 vecB(5, 6, 7);
    const flcn::Vec3 expected(true, true, false);

    // When compared with less than or equal
    const flcn::Vec3<bool> mask = vecA.lte(vecB);

    // Then, the resulting elements are as expected
    EXPECT_VEC_EQ(expected, mask);
}

/** @} */
