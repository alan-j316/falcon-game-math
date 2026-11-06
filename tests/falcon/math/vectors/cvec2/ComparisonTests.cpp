/**
 * @file ComparisonTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref flcn::CVec2<bool> comparison operator (>, >=, <, <=) and
 *        their functional counterpart's (gt, gte, lt, lte) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CVec2TestSetup.h"

#include <falcon/math/common/Constants.h>



/**
 * @addtogroup T_FALCON_CVec2_Comp
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
     * @brief Test fixture for @ref CVec2 comparisons.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class CVec2ComparisonTests: public testing::Test
    {
    protected:
        flcn::CVec2<T> _vecA;
        flcn::CVec2<T> _vecB;
        flcn::CVec2<bool> _expectedGT, _expectedGTE, _expectedLT,
            _expectedLTE; // GT-> Greater Than, GTE-> Greater Than or Equal, LT -> Less than, LTE -> Less than or equal

        void SetUp() override
        {
            _vecA        = { T(1.1234568789), T(2.123458319) };
            _vecB        = { T(5.1234568789), T(1.123458319) };
            _expectedGT  = { false, true };
            _expectedGTE = { false, true };
            _expectedLT  = { true, false };
            _expectedLTE = { true, false };
        }
    };
    TYPED_TEST_SUITE(CVec2ComparisonTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::CVec2 VEC_A(1, 2);
        constexpr flcn::CVec2 VEC_B(1, 3);

        /// @test Verify that greater than operator (operator>) returns a valid mask at compile time.
        constexpr auto GT_OP_MASK_VEC = VEC_A > VEC_B;
        static_assert(GT_OP_MASK_VEC.x() == false);
        static_assert(GT_OP_MASK_VEC.y() == false);

        /// @test Verify that greater than operator (gt) returns a valid mask at compile time.
        constexpr auto GT_MASK_VEC = VEC_A.gt(VEC_B);
        static_assert(GT_MASK_VEC.x() == false);
        static_assert(GT_MASK_VEC.y() == false);

        /// @test Verify that greater than operator (gt-static wrapper) returns a valid mask at compile time.
        constexpr auto GT_MASK_VEC_STATIC = flcn::CVec2<int>::gt(VEC_A, VEC_B);
        static_assert(GT_MASK_VEC_STATIC.x() == false);
        static_assert(GT_MASK_VEC_STATIC.y() == false);


        /// @test Verify that greater or equals operator (operator>=) returns a valid mask at compile time.
        constexpr auto GTE_OP_MASK_VEC = VEC_A >= VEC_B;
        static_assert(GTE_OP_MASK_VEC.x() == true);
        static_assert(GTE_OP_MASK_VEC.y() == false);

        /// @test Verify that greater than or equals operator (gte) returns a valid mask at compile time.
        constexpr auto GTE_MASK_VEC = VEC_A.gte(VEC_B);
        static_assert(GTE_MASK_VEC.x() == true);
        static_assert(GTE_MASK_VEC.y() == false);

        /// @test Verify that greater than or equals operator (gte-static wrapper) returns a valid mask at compile time.
        constexpr auto GTE_MASK_VEC_STATIC = flcn::CVec2<int>::gte(VEC_A, VEC_B);
        static_assert(GTE_MASK_VEC_STATIC.x() == true);
        static_assert(GTE_MASK_VEC_STATIC.y() == false);


        /// @test Verify that less than operator (operator<) returns a valid mask at compile time.
        constexpr auto LT_OP_MASK_VEC = VEC_A < VEC_B;
        static_assert(LT_OP_MASK_VEC.x() == false);
        static_assert(LT_OP_MASK_VEC.y() == true);

        /// @test Verify that less than operator (lt) returns a valid mask at compile time.
        constexpr auto LT_MASK_VEC = VEC_A.lt(VEC_B);
        static_assert(LT_MASK_VEC.x() == false);
        static_assert(LT_MASK_VEC.y() == true);

        /// @test Verify that less than operator (lt-static wrapper) returns a valid mask at compile time.
        constexpr auto LT_MASK_VEC_STATIC = flcn::CVec2<int>::lt(VEC_A, VEC_B);
        static_assert(LT_MASK_VEC_STATIC.x() == false);
        static_assert(LT_MASK_VEC_STATIC.y() == true);


        constexpr auto LTE_OP_MASK_VEC = VEC_A <= VEC_B;
        /// @test Verify that less than or equals operator (operator<=) returns a valid mask at compile time.
        static_assert(LTE_OP_MASK_VEC.x() == true);
        static_assert(LTE_OP_MASK_VEC.y() == true);

        /// @test Verify that less than or equals operator (lte) returns a valid mask at compile time.
        constexpr auto LTE_MASK_VEC = VEC_A.lte(VEC_B);
        static_assert(LTE_MASK_VEC.x() == true);
        static_assert(LTE_MASK_VEC.y() == true);

        /// @test Verify that less than or equals operator (lte-static wrapper) returns a valid mask at compile time.
        constexpr auto LTE_MASK_VEC_STATIC = flcn::CVec2<int>::lte(VEC_A, VEC_B);
        static_assert(LTE_MASK_VEC_STATIC.x() == true);
        static_assert(LTE_MASK_VEC_STATIC.y() == true);

    } // namespace static_tests
} // namespace



/**************************************
 *         GREATER THAN TESTS         *
 **************************************/

TYPED_TEST(CVec2ComparisonTests, GT_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
{
    const flcn::CVec2<bool> mask = this->_vecA.gt(this->_vecB);

    EXPECT_VEC_EQ(this->_expectedGT, mask);
}


TEST(CVec2ComparisonTests, GT_InfinityVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::CVec2 vec(1.2, 4.5);
    const flcn::CVec2 infVec(INF, -INF);
    const flcn::CVec2 expected(false, true);

    const flcn::CVec2<bool> mask = vec.gt(infVec);

    EXPECT_VEC_EQ(expected, mask);
}



TEST(CVec2ComparisonTests, GT_NaNVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::CVec2 vec(1.2f, 4.5f);
    const flcn::CVec2 infVec(NAN_F, NAN_F);
    const flcn::CVec2 expected(false, false);

    const flcn::CVec2<bool> mask = vec.gt(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


TEST(CVec2ComparisonTests, GT_MixedType_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    const flcn::CVec2 vecA(1.2, 7.5);
    const flcn::CVec2 vecB(5, 7);
    const flcn::CVec2 expected(false, true);

    // When compared with greater than or equal
    const flcn::CVec2<bool> mask = vecA.gt(vecB);

    // Then, the resulting elements are as expected
    EXPECT_VEC_EQ(expected, mask);
}


TYPED_TEST(CVec2ComparisonTests, GreaterThanOperator_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
{
    const flcn::CVec2<bool> mask = this->_vecA > this->_vecB;

    EXPECT_VEC_EQ(this->_expectedGT, mask);
}


TYPED_TEST(CVec2ComparisonTests, StaticWrapper_GT_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
{
    const flcn::CVec2<bool> mask = flcn::CVec2<TypeParam>::gt(this->_vecA, this->_vecB);

    EXPECT_VEC_EQ(this->_expectedGT, mask);
}



/**************************************
 *    GREATER THAN OR EQUALS TESTS    *
 **************************************/

TYPED_TEST(CVec2ComparisonTests, GTE_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
{
    const flcn::CVec2<bool> mask = this->_vecA.gte(this->_vecB);

    EXPECT_VEC_EQ(this->_expectedGTE, mask);
}


TEST(CVec2ComparisonTests, GTE_InfinityVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::CVec2 vec(1.2f, 6.8f);
    const flcn::CVec2 infVec(INF, -INF);
    const flcn::CVec2 expected(false, true);

    const flcn::CVec2<bool> mask = vec.gte(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


TEST(CVec2ComparisonTests, GTE_NanVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::CVec2 vec(1.2, 6.8);
    const flcn::CVec2 infVec(NAN_F, -5.9f);
    const flcn::CVec2 expected(false, true);

    const flcn::CVec2<bool> mask = vec.gte(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


TEST(CVec2ComparisonTests, GTE_MixedType_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    const flcn::CVec2 vecA(1.2, 7.5);
    const flcn::CVec2 vecB(5, 7);
    const flcn::CVec2 expected(false, true);

    // When compared with greater or equal than
    const flcn::CVec2<bool> mask = vecA.gte(vecB);

    // Then, the resulting elements are as expected
    EXPECT_VEC_EQ(expected, mask);
}


TYPED_TEST(CVec2ComparisonTests, GreaterThanOrEqualsOperator_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
{
    const flcn::CVec2<bool> mask = this->_vecA >= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedGTE, mask);
}


TYPED_TEST(CVec2ComparisonTests, StaticWrapper_GTE_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
{
    const flcn::CVec2<bool> mask = flcn::CVec2<TypeParam>::gte(this->_vecA, this->_vecB);

    EXPECT_VEC_EQ(this->_expectedGTE, mask);
}



/**************************************
 *          LESS THAN TESTS           *
 **************************************/


TYPED_TEST(CVec2ComparisonTests, LT_ReturnsBooleanVectorWithElementsLessThanAsTrue)
{
    const flcn::CVec2<bool> mask = this->_vecA.lt(this->_vecB);
    EXPECT_VEC_EQ(this->_expectedLT, mask);
}


TEST(CVec2ComparisonTests, LT_InfinityVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::CVec2 vec(1.2, 6.8);
    const flcn::CVec2 infVec(INF, -INF);
    const flcn::CVec2 expected(true, false);

    const flcn::CVec2<bool> mask = vec.lt(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


TEST(CVec2ComparisonTests, LT_NanVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::CVec2 vec(1.2f, 6.8f);
    const flcn::CVec2 nanVec(NAN_F, -5.9f);
    const flcn::CVec2 expected(false, false);

#if defined(_MSC_VER) && !defined(__clang__)
    // MSVC constant evaluator incorrectly returns true for NAN_F comparisons.
    // We fallback to 'const' (runtime) to verify the hardware/logic is correct.
    // Resharper disable all
    const flcn::CVec2<bool> mask = vec.lt(nanVec);
// Resharper restore all
#else
    // Clang and GCC follow IEEE 754 strictly at compile-time.
    const flcn::CVec2<bool> mask = vec.lt(nanVec);
#endif

    EXPECT_VEC_EQ(expected, mask);
}


TEST(CVec2ComparisonTests, LT_MixedType_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    const flcn::CVec2 vecA(1.2, 7.5);
    const flcn::CVec2 vecB(5, 7);
    const flcn::CVec2 expected(true, false);

    // When compared with less than or equal
    const flcn::CVec2<bool> mask = vecA.lt(vecB);

    // Then, the resulting elements are as expected
    EXPECT_VEC_EQ(expected, mask);
}


TYPED_TEST(CVec2ComparisonTests, LessThanOperator_ReturnsBooleanVectorWithElementsLessThanAsTrue)
{
    const flcn::CVec2<bool> mask = this->_vecA < this->_vecB;
    EXPECT_VEC_EQ(this->_expectedLT, mask);
}


TYPED_TEST(CVec2ComparisonTests, StaticWrapper_LT_ReturnsBooleanVectorWithElementsLessThanAsTrue)
{
    const flcn::CVec2<bool> mask = flcn::CVec2<TypeParam>::lt(this->_vecA, this->_vecB);
    EXPECT_VEC_EQ(this->_expectedLT, mask);
}



/**************************************
 *      LESS THAN OR EQUALS TESTS     *
 **************************************/

TYPED_TEST(CVec2ComparisonTests, LTE_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
{
    const flcn::CVec2<bool> mask = this->_vecA.lte(this->_vecB);
    EXPECT_VEC_EQ(this->_expectedLTE, mask);
}

TEST(CVec2ComparisonTests, LTE_InfinityVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::CVec2 vec(1.2, 6.8);
    const flcn::CVec2 infVec(INF, -INF);
    const flcn::CVec2 expected(true, false);

    const flcn::CVec2<bool> mask = vec.lte(infVec);

    EXPECT_VEC_EQ(expected, mask);
}


TEST(CVec2ComparisonTests, LTE_NanVector_ReturnsBooleanVectorWithCorrectValues)
{
    const flcn::CVec2 vec(1.2f, 6.8f);
    const flcn::CVec2 nanVec(NAN_F, -5.9f);
    const flcn::CVec2 expected(false, false);

    #if defined(_MSC_VER) && !defined(__clang__)
    // MSVC constant evaluator incorrectly returns true for NAN_F comparisons.
    // We fallback to 'const' (runtime) to verify the hardware/logic is correct.
    // Resharper disable all
    const flcn::CVec2<bool> mask = vec.lte(nanVec);
    // Resharper restore all
    #else
    // Clang and GCC follow IEEE 754 strictly at compile-time.
    const flcn::CVec2<bool> mask = vec.lte(nanVec);
    #endif

    EXPECT_VEC_EQ(expected, mask);
}


TEST(CVec2ComparisonTests, LTE_MixedType_ReturnsBooleanVectorWithCorrectValues)
{
    // Given two arbitrary vectors of different types
    const flcn::CVec2 vecA(1.2, 7.5);
    const flcn::CVec2 vecB(5, 7);
    const flcn::CVec2 expected(true, false);

    // When compared with less than or equal
    const flcn::CVec2<bool> mask = vecA.lte(vecB);

    // Then, the resulting elements are as expected
    EXPECT_VEC_EQ(expected, mask);
}


TYPED_TEST(CVec2ComparisonTests, LessThanOrEqualOperator_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
{
    const flcn::CVec2<bool> mask = this->_vecA <= this->_vecB;
    EXPECT_VEC_EQ(this->_expectedLTE, mask);
}


TYPED_TEST(CVec2ComparisonTests, StaticWrapper_LTE_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
{
    const flcn::CVec2<bool> mask = flcn::CVec2<TypeParam>::lte(this->_vecA, this->_vecB);
    EXPECT_VEC_EQ(this->_expectedLTE, mask);
}

/** @} */
