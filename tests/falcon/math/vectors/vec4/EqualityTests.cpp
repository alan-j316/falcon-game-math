/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verify @ref flcn::Vec4 equality operator (==, !=) and their functional counterpart's (eq, neq, allEq,
 * anyNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec4TestSetup.h"

#include <falcon/math/common/Constants.h>



/**
 * @addtogroup T_FALCON_Vec4_Equality
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
     * @brief Test fixture for @ref Vec4 equality.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec4Equality: public testing::Test
    {
    protected:
        flcn::Vec4<T> _eqVecA;
        flcn::Vec4<T> _eqVecB;
        flcn::Vec4<T> _dissimilarVec;
        flcn::Vec4<bool> _equalityMask;
        flcn::Vec4<bool> _inequalityMask;


        void SetUp() override
        {
            _eqVecA         = { T(1.1234568789), T(2.123458319), T(5.123412593891), T(123.123489172589) };
            _eqVecB         = { T(1.1234568789), T(2.123458319), T(5.123412593891), T(123.123489172589) };
            _dissimilarVec  = { T(7.1234568789), T(2.123458319), T(24.00), T(123.123489172589) };
            _equalityMask   = { false, true, false, true };
            _inequalityMask = { true, false, true, false };
        }
    };
    TYPED_TEST_SUITE(Vec4Equality, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Vec4 VEC_A(1, 2, 4, 1);
        constexpr flcn::Vec4 VEC_B(3, 2, 1, 4);
        constexpr flcn::Vec4 VEC_C(1, 2, 4, 1);

        /// @test Verify that @ref Vec4 allEq returns correct boolean for equal vectors.
        constexpr auto ALLEQ_EQ_VECS = VEC_A.allEq(VEC_B);
        static_assert(ALLEQ_EQ_VECS == false);

        /// @test Verify that @ref Vec4 allEq returns correct boolean for unequal vectors.
        constexpr auto ALL_EQ_UNEQUAL_VECS = VEC_A.allEq(VEC_C);
        static_assert(ALL_EQ_UNEQUAL_VECS == true);

        /// @test Verify that @ref Vec4 allEq (static wrapper) returns correct boolean for equal vectors.
        constexpr auto ALLEQ_EQ_VECS_STATIC = flcn::Vec4<int>::allEq(VEC_A, VEC_B);
        static_assert(ALLEQ_EQ_VECS_STATIC == false);

        /// @test Verify that @ref Vec4 allEq (static wrapper) returns correct boolean for unequal vectors.
        constexpr auto ALLEQ_UNEQUAL_VECS_STATIC = flcn::Vec4<int>::allEq(VEC_A, VEC_C);
        static_assert(ALLEQ_UNEQUAL_VECS_STATIC == true);

        /// @test Verify that @ref Vec4 equals operator returns correct boolean for equal vectors.
        constexpr auto DBLEQ_OP_EQUAL_VECS = VEC_A == VEC_B;
        static_assert(DBLEQ_OP_EQUAL_VECS == false);

        /// @test Verify that @ref Vec4 equals operator returns correct boolean for unequal vectors.
        constexpr auto DBLEQ_OP_UNEQUAL_VECS = VEC_A == VEC_C;
        static_assert(DBLEQ_OP_UNEQUAL_VECS == true);


        /// @test Verify that @ref Vec4 equality mask returns valid boolean mask
        constexpr auto EQ_VEC_MASK = VEC_A.eq(VEC_B);
        static_assert(EQ_VEC_MASK.x() == false);
        static_assert(EQ_VEC_MASK.y() == true);


        /// @test Verify that @ref Vec4 anyNeq returns correct boolean for equal vectors.
        constexpr auto ANYNEQ_EQ_VECS = VEC_A.anyNeq(VEC_B);
        static_assert(ANYNEQ_EQ_VECS == true);

        /// @test Verify that @ref Vec4 anyNeq returns correct boolean for unequal vectors.
        constexpr auto ANYNEQ_UNEQUAL_VECS = VEC_A.anyNeq(VEC_C);
        static_assert(ANYNEQ_UNEQUAL_VECS == false);

        /// @test Verify that @ref Vec4 anyNeq(static wrapper) returns correct boolean for equal vectors.
        constexpr auto ANYNEQ_EQ_VECS_STATIC = flcn::Vec4<int>::anyNeq(VEC_A, VEC_B);
        static_assert(ANYNEQ_EQ_VECS_STATIC == true);

        /// @test Verify that @ref Vec4 anyNeq(static wrapper) returns correct boolean for unequal vectors.
        constexpr auto ANYNEQ_UNEQUAL_VECS_STATIC = flcn::Vec4<int>::anyNeq(VEC_A, VEC_C);
        static_assert(ANYNEQ_UNEQUAL_VECS_STATIC == false);

        /// @test Verify that @ref Vec4 not equals operator returns correct boolean for equal vectors.
        constexpr auto ANYNEQ_OP_EQUAL_VECS = VEC_A != VEC_B;
        static_assert(ANYNEQ_OP_EQUAL_VECS == true);

        /// @test Verify that @ref Vec4 not equals operator returns correct boolean for unequal vectors.
        constexpr auto NOT_EQ_OP = VEC_A != VEC_C;
        static_assert(NOT_EQ_OP == false);

        /// @test Verify that @ref Vec4 inequality mask returns valid boolean mask.
        constexpr auto NEQ_MASK_VEC = VEC_A.neq(VEC_B);
        static_assert(NEQ_MASK_VEC.x() == true);
        static_assert(NEQ_MASK_VEC.y() == false);

    } // namespace static_tests
} // namespace



/**************************************
 *           EQUALITY TESTS           *
 **************************************/

/** @test Verify that @ref flcn::Vec4::allEq returns true for identical vectors. */
TYPED_TEST(Vec4Equality, AllEq_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA.allEq(this->_eqVecB);
    EXPECT_TRUE(equality);
}


/** @test Verify that @ref flcn::Vec4::allEq returns false if any component differ. */
TYPED_TEST(Vec4Equality, Equality_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA.allEq(this->_dissimilarVec);
    EXPECT_FALSE(equality);
}


/** @test Verify that the static variant of @ref flcn::Vec4::allEq for identical vectors. */
TYPED_TEST(Vec4Equality, StaticWrapper_AllEq_IdenticalVectorsReturnsTrue)
{
    const bool equality = flcn::Vec4<TypeParam>::allEq(this->_eqVecA, this->_eqVecB);
    EXPECT_TRUE(equality);
}


/** @test Verify that the static variant of @ref flcn::Vec4::allEq for different vectors. */
TYPED_TEST(Vec4Equality, StaticWrapper_Equality_DifferentVectorsReturnsFalse)
{
    const bool equality = flcn::Vec4<TypeParam>::allEq(this->_eqVecA, this->_dissimilarVec);
    EXPECT_FALSE(equality);
}


/** @test Verify that @ref flcn::Vec4::allEq follows IEEE 754 for NaN comparisons. */
TEST(Vec4Equality, NanEqualityReturnsFalse)
{
    const flcn::Vec4 vecA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const flcn::Vec4<double> vecB = { 1.0, -5.88874789, flcn::constants::INFINITY_D, NAN_F };

    const bool equality = vecA.allEq(vecB);
    EXPECT_FALSE(equality);
}


/** @test Verify that @ref flcn::Vec4::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec4Equality, InfinityAllEq_IdenticalVectorsReturnsTrue)
{
    const flcn::Vec4 vecA = { INF, -INF, INF, -INF };
    const flcn::Vec4 vecB = { INF, -INF, INF, -INF };

    const bool equality = vecA.allEq(vecB);
    EXPECT_TRUE(equality);
}


/** @test Verify that @ref flcn::Vec4::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec4Equality, InfinityEquality_DifferentVectorsReturnsFalse)
{
    const flcn::Vec4 vecA = { INF, INF, INF, -INF };
    const flcn::Vec4 vecB = { INF, -INF, INF, INF };

    const bool equality = vecA.allEq(vecB);
    EXPECT_FALSE(equality);
}


/** @test Verify that the equality operator returns true for identical vectors. */
TYPED_TEST(Vec4Equality, EqualityOperator_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA == this->_eqVecB;
    EXPECT_TRUE(equality);
}


/** @test Verify that @ref flcn::Vec4::allEq works for different vector types with identical components. */
TYPED_TEST(Vec4Equality, MixedType_AllEq_IdenticalVectorsReturnsTrue)
{
    const flcn::Vec4 vecA(1, 2, 3, 4);
    const flcn::Vec4 vecB(1.0, 2.0, 3.0, 4.0);

    const bool equality = vecA.allEq(vecB);
    EXPECT_TRUE(equality);
}


/** @test Verify that @ref flcn::Vec4::allEq works for different vector types with different components. */
TYPED_TEST(Vec4Equality, MixedType_Equality_DifferentVectorsReturnsFalse)
{
    const flcn::Vec4 vecA(5, 6, 7, 8);
    const flcn::Vec4 vecB(1.0, 2.0, 3.0, 4.0);

    const bool equality = vecA.allEq(vecB);
    EXPECT_FALSE(equality);
}


/** @test Verify that the equality operator returns false if any component differ. */
TYPED_TEST(Vec4Equality, EqualityOperator_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA == this->_dissimilarVec;
    EXPECT_FALSE(equality);
}


/** @test Verify that the equality operator works for bool vector with identical components. */
TEST(Vec4Equality, EqualityOperator_IdenticalBooleanVectorsReturnsTrue)
{
    const flcn::Vec4 vecA(true, false, true, false);
    const flcn::Vec4 vecB(true, false, true, false);

    const bool equality = vecA == vecB;
    EXPECT_TRUE(equality);
}


/** @test Verify that the equality operator works for bool vector with different components. */
TEST(Vec4Equality, EqualityOperator_DifferentBooleanVectorsReturnsFalse)
{
    const flcn::Vec4 vecA(true, false, true, false);
    const flcn::Vec4 vecB(true, true, true, false);

    const bool equality = vecA == vecB;
    EXPECT_FALSE(equality);
}


/** @test Verify that @ref flcn::Vec4::eq returns @ref flcn::Vec4<bool> mask for identical vectors. */
TYPED_TEST(Vec4Equality, EqualityReturnsCorrectBooleanMask)
{
    const flcn::Vec4<bool> mask = this->_eqVecA.eq(this->_dissimilarVec);
    EXPECT_VEC_EQ(this->_equalityMask, mask);
}

/** @test Verify that @ref flcn::Vec4::eq returns @ref flcn::Vec4<bool> mask for different vectors. */
TEST(Vec4Equality, MixedType_EqualityReturnsCorrectBooleanMask)
{
    const flcn::Vec4 vecA         = { 1, 2, 3, 4 };
    const flcn::Vec4 vecB         = { 1.0, 4.0, 0.0, 4.0 };
    const flcn::Vec4 expectedMask = { true, false, false, true };

    const flcn::Vec4<bool> mask = vecA.eq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @test Verify that @ref flcn::Vec4::eq follows IEEE 754 for NaN comparisons. */
TEST(Vec4Equality, NanEqualityReturnsFalseBooleanMask)
{
    const flcn::Vec4 vecA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const flcn::Vec4 vecB         = { 1.0, -5.88874789, flcn::constants::INFINITY_D, flcn::constants::NaN_D };
    const flcn::Vec4 expectedMask = { false, false, false, false };

    const flcn::Vec4 mask = vecA.eq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @test Verify that @ref flcn::Vec4::eq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec4Equality, InfinityEqualityReturnsCorrectBooleanMask)
{
    const flcn::Vec4 vecA         = { INF, -INF, INF, -INF };
    const flcn::Vec4<double> vecB = { flcn::constants::INFINITY_D, flcn::constants::INFINITY_D, 10e11, 10e11 };
    const flcn::Vec4 expectedMask = { true, false, false, false };

    const flcn::Vec4 mask = vecA.eq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


/**
 * @test Verify that the static variant of @ref flcn::Vec4::eq returns @ref flcn::Vec4<bool> mask
 *       for different vectors.
 */
TYPED_TEST(Vec4Equality, StaticWrapper_EqualityReturnsCorrectBooleanMask)
{
    const flcn::Vec4<bool> mask = flcn::Vec4<TypeParam>::eq(this->_eqVecA, this->_dissimilarVec);
    EXPECT_VEC_EQ(this->_equalityMask, mask);
}



/**************************************
 *          INEQUALITY TESTS          *
 **************************************/

/** @test Verify that @ref flcn::Vec4::anyNeq returns false for identical vectors. */
TYPED_TEST(Vec4Equality, Inequality_IdenticalVectorsReturnsFalse)
{
    const bool inequality = this->_eqVecA.anyNeq(this->_eqVecB);
    EXPECT_FALSE(inequality);
}


/** @test Verify that @ref flcn::Vec4::anyNeq returns true if any component differ. */
TYPED_TEST(Vec4Equality, Inequality_DifferentVectorsReturnsTrue)
{
    const bool inequality = this->_eqVecA.anyNeq(this->_dissimilarVec);
    EXPECT_TRUE(inequality);
}


/** @test Verify that the static variant of @ref flcn::Vec4::anyNeq for identical vectors. */
TYPED_TEST(Vec4Equality, StaticWrapper_Inequality_IdenticalVectorsReturnsFalse)
{
    const bool inequality = flcn::Vec4<TypeParam>::anyNeq(this->_eqVecA, this->_eqVecB);
    EXPECT_FALSE(inequality);
}


/** @test Verify that the static variant of @ref flcn::Vec4::anyNeq for different vectors. */
TYPED_TEST(Vec4Equality, StaticWrapper_Inequality_DifferentVectorsReturnsTrue)
{
    const bool inequality = flcn::Vec4<TypeParam>::anyNeq(this->_eqVecA, this->_dissimilarVec);
    EXPECT_TRUE(inequality);
}


/** @test Verify that @ref flcn::Vec4::anyNeq follows IEEE 754 for NaN comparisons. */
TEST(Vec4Equality, NanInequalityReturnsTrue)
{
    const flcn::Vec4 vecA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const flcn::Vec4<double> vecB = { 1.0, -5.88874789, flcn::constants::INFINITY_D, NAN_F };

    const bool inequality = vecA.anyNeq(vecB);
    EXPECT_TRUE(inequality);
}


/** @test Verify that @ref flcn::Vec4::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec4Equality, InfinityInequality_IdenticalVectorsReturnsFalse)
{
    const flcn::Vec4 vecA = { INF, -INF, INF, -INF };
    const flcn::Vec4 vecB = { INF, -INF, INF, -INF };

    const bool inequality = vecA.anyNeq(vecB);
    EXPECT_FALSE(inequality);
}


/** @test Verify that @ref flcn::Vec4::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec4Equality, InfinityInequality_DifferentVectorsReturnsTrue)
{
    const flcn::Vec4 vecA = { INF, INF, INF, -INF };
    const flcn::Vec4 vecB = { INF, -INF, INF, INF };

    const bool inequality = vecA.anyNeq(vecB);
    EXPECT_TRUE(inequality);
}


/** @test Verify that @ref flcn::Vec4::anyNeq works for different vector types with identical components. */
TYPED_TEST(Vec4Equality, MixedType_Inequality_IdenticalVectorsReturnsFalse)
{
    const flcn::Vec4 vecA(1, 2, 3, 4);
    const flcn::Vec4 vecB(1.0, 2.0, 3.0, 4.0);

    const bool inequality = vecA.anyNeq(vecB);
    EXPECT_FALSE(inequality);
}


/** @test Verify that @ref flcn::Vec4::anyNeq works for different vector types with different components. */
TYPED_TEST(Vec4Equality, MixedType_Inequality_DifferentVectorsReturnsTrue)
{
    const flcn::Vec4 vecA(5, 6, 7, 8);
    const flcn::Vec4 vecB(1.0, 2.0, 3.0, 4.0);

    const bool inequality = vecA.anyNeq(vecB);
    EXPECT_TRUE(inequality);
}


/** @test Verify that the operator returns false for identical vectors. */
TYPED_TEST(Vec4Equality, NotEqualsOperator_IdenticalVectorsReturnsFalse)
{
    const bool inequality = this->_eqVecA != this->_eqVecB;
    EXPECT_FALSE(inequality);
}


/** @test Verify that the inequality operator returns true for different vectors. */
TYPED_TEST(Vec4Equality, NotEqualsOperator_DifferentVectorsReturnsTrue)
{
    const bool inequality = this->_eqVecA != this->_dissimilarVec;
    EXPECT_TRUE(inequality);
}


/** @test Verify that the inequality operator works for @ref flcn::Vec4<bool> with identical components. */
TEST(Vec4Equality, InequalityOperator_IdenticalBooleanVectorsReturnsFalse)
{
    const flcn::Vec4 vecA(true, false, true, false);
    const flcn::Vec4 vecB(true, false, true, false);

    const bool inequality = vecA != vecB;
    EXPECT_FALSE(inequality);
}


/** @test Verify that the inequality operator works for @ref flcn::Vec4<bool> with different components. */
TEST(Vec4Equality, InequalityOperator_DifferentBooleanVectorsReturnsTrue)
{
    const flcn::Vec4 vecA(true, false, true, false);
    const flcn::Vec4 vecB(true, true, true, false);

    const bool inequality = vecA != vecB;
    EXPECT_TRUE(inequality);
}


/** @test Verify that @ref flcn::Vec4::neq returns @ref flcn::Vec4<bool> mask for identical vectors. */
TYPED_TEST(Vec4Equality, InequalityReturnsCorrectBooleanMask)
{
    const flcn::Vec4<bool> mask = this->_eqVecA.neq(this->_dissimilarVec);
    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}


/** @test Verify that @ref flcn::Vec4::neq returns @ref flcn::Vec4<bool> mask for different vectors. */
TEST(Vec4Equality, MixedType_InequalityReturnsCorrectBooleanMask)
{
    const flcn::Vec4 vecA         = { 1, 2, 3, 4 };
    const flcn::Vec4 vecB         = { 1.0, 4.0, 0.0, 4.0 };
    const flcn::Vec4 expectedMask = { false, true, true, false };

    const flcn::Vec4<bool> mask = vecA.neq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @test Verify that @ref flcn::Vec4::neq follows IEEE 754 for NaN comparisons. */
TEST(Vec4Equality, NanInequalityReturnsTrueBooleanMask)
{
    const flcn::Vec4 vecA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const flcn::Vec4<double> vecB = { 1.0, -5.88874789, flcn::constants::INFINITY_D, NAN_F };
    const flcn::Vec4 expectedMask = { true, true, true, true };

    const flcn::Vec4 mask = vecA.neq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @test Verify that @ref flcn::Vec4::neq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec4Equality, InfinityInequalityReturnsCorrectBooleanMask)
{
    const flcn::Vec4 vecA         = { INF, -INF, INF, -INF };
    const flcn::Vec4 vecB         = { flcn::constants::INFINITY_D, flcn::constants::INFINITY_D, 10e11, 10e11 };
    const flcn::Vec4 expectedMask = { false, true, true, true };

    const flcn::Vec4 mask = vecA.neq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


/**
 * @test Verify that the static variant of @ref flcn::Vec4::neq returns @ref flcn::Vec4<bool> mask
 *        for different vectors.
 */
TYPED_TEST(Vec4Equality, StaticWrapper_InequalityReturnsCorrectBooleanMask)
{
    const flcn::Vec4<bool> mask = flcn::Vec4<TypeParam>::neq(this->_eqVecA, this->_dissimilarVec);
    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}

/** @} */
