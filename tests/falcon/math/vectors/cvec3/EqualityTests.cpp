/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify @ref flcn::CVec3 equality operator (==, !=) and their functional counterpart's (eq, neq, allEq,
 * anyNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CVec3TestSetup.h"

#include <falcon/math/common/Constants.h>

/**
 * @addtogroup T_Falcon_CVec3_Equality
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
     * @brief Test fixture for @ref CVec3 equality.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class CVec3EqualityTests: public testing::Test
    {
    protected:
        flcn::CVec3<T> _eqVecA;
        flcn::CVec3<T> _eqVecB;
        flcn::CVec3<T> _dissimilarVec;
        flcn::CVec3<bool> _equalityMask;
        flcn::CVec3<bool> _inequalityMask;


        void SetUp() override
        {
            _eqVecA         = { T(1.1234568789), T(2.123458319), T(5.123412593891) };
            _eqVecB         = { T(1.1234568789), T(2.123458319), T(5.123412593891) };
            _dissimilarVec  = { T(7.1234568789), T(2.123458319), T(24.00) };
            _equalityMask   = { false, true, false };
            _inequalityMask = { true, false, true };
        }
    };
    TYPED_TEST_SUITE(CVec3EqualityTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::CVec3 VEC_A(1, 2, 4);
        constexpr flcn::CVec3 VEC_B(3, 2, 1);
        constexpr flcn::CVec3 VEC_C(1, 2, 4);


        /// @test Verify that @ref CVec3 allEq returns correct boolean for equal vectors.
        constexpr auto ALLEQ_EQ_VECS = VEC_A.allEq(VEC_B);
        static_assert(ALLEQ_EQ_VECS == false);

        /// @test Verify that @ref CVec3 allEq returns correct boolean for unequal vectors.
        constexpr auto ALL_EQ_UNEQUAL_VECS = VEC_A.allEq(VEC_C);
        static_assert(ALL_EQ_UNEQUAL_VECS == true);

        /// @test Verify that @ref CVec3 allEq (static wrapper) returns correct boolean for equal vectors.
        constexpr auto ALLEQ_EQ_VECS_STATIC = flcn::CVec3<int>::allEq(VEC_A, VEC_B);
        static_assert(ALLEQ_EQ_VECS_STATIC == false);

        /// @test Verify that @ref CVec3 allEq (static wrapper) returns correct boolean for unequal vectors.
        constexpr auto ALLEQ_UNEQUAL_VECS_STATIC = flcn::CVec3<int>::allEq(VEC_A, VEC_C);
        static_assert(ALLEQ_UNEQUAL_VECS_STATIC == true);

        /// @test Verify that @ref CVec3 equals operator returns correct boolean for equal vectors.
        constexpr auto DBLEQ_OP_EQUAL_VECS = VEC_A == VEC_B;
        static_assert(DBLEQ_OP_EQUAL_VECS == false);

        /// @test Verify that @ref CVec3 equals operator returns correct boolean for unequal vectors.
        constexpr auto DBLEQ_OP_UNEQUAL_VECS = VEC_A == VEC_C;
        static_assert(DBLEQ_OP_UNEQUAL_VECS == true);


        /// @test Verify that @ref CVec3 equality mask returns valid boolean mask
        constexpr auto EQ_VEC_MASK = VEC_A.eq(VEC_B);
        static_assert(EQ_VEC_MASK.x() == false);
        static_assert(EQ_VEC_MASK.y() == true);


        /// @test Verify that @ref CVec3 anyNeq returns correct boolean for equal vectors.
        constexpr auto ANYNEQ_EQ_VECS = VEC_A.anyNeq(VEC_B);
        static_assert(ANYNEQ_EQ_VECS == true);

        /// @test Verify that @ref CVec3 anyNeq returns correct boolean for unequal vectors.
        constexpr auto ANYNEQ_UNEQUAL_VECS = VEC_A.anyNeq(VEC_C);
        static_assert(ANYNEQ_UNEQUAL_VECS == false);

        /// @test Verify that @ref CVec3 anyNeq(static wrapper) returns correct boolean for equal vectors.
        constexpr auto ANYNEQ_EQ_VECS_STATIC = flcn::CVec3<int>::anyNeq(VEC_A, VEC_B);
        static_assert(ANYNEQ_EQ_VECS_STATIC == true);

        /// @test Verify that @ref CVec3 anyNeq(static wrapper) returns correct boolean for unequal vectors.
        constexpr auto ANYNEQ_UNEQUAL_VECS_STATIC = flcn::CVec3<int>::anyNeq(VEC_A, VEC_C);
        static_assert(ANYNEQ_UNEQUAL_VECS_STATIC == false);

        /// @test Verify that @ref CVec3 not equals operator returns correct boolean for equal vectors.
        constexpr auto ANYNEQ_OP_EQUAL_VECS = VEC_A != VEC_B;
        static_assert(ANYNEQ_OP_EQUAL_VECS == true);

        /// @test Verify that @ref CVec3 not equals operator returns correct boolean for unequal vectors.
        constexpr auto NOT_EQ_OP = VEC_A != VEC_C;
        static_assert(NOT_EQ_OP == false);

        /// @test Verify that @ref CVec3 inequality mask returns valid boolean mask.
        constexpr auto NEQ_MASK_VEC = VEC_A.neq(VEC_B);
        static_assert(NEQ_MASK_VEC.x() == true);
        static_assert(NEQ_MASK_VEC.y() == false);

    } // namespace static_tests
} // namespace



/**************************************
 *           EQUALITY TESTS           *
 **************************************/

/** @test Verify that @ref flcn::CVec3::allEq returns true for identical vectors. */
TYPED_TEST(CVec3EqualityTests, AllEq_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA.allEq(this->_eqVecB);
    EXPECT_TRUE(equality);
}


/** @test Verify that @ref flcn::CVec3::allEq returns false if any component differ. */
TYPED_TEST(CVec3EqualityTests, Equality_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA.allEq(this->_dissimilarVec);
    EXPECT_FALSE(equality);
}


/** @test Verify that the static variant of @ref flcn::CVec3::allEq for identical vectors. */
TYPED_TEST(CVec3EqualityTests, StaticWrapper_AllEq_IdenticalVectorsReturnsTrue)
{
    const bool equality = flcn::CVec3<TypeParam>::allEq(this->_eqVecA, this->_eqVecB);
    EXPECT_TRUE(equality);
}


/** @test Verify that the static variant of @ref flcn::CVec3::allEq for different vectors. */
TYPED_TEST(CVec3EqualityTests, StaticWrapper_Equality_DifferentVectorsReturnsFalse)
{
    const bool equality = flcn::CVec3<TypeParam>::allEq(this->_eqVecA, this->_dissimilarVec);
    EXPECT_FALSE(equality);
}


/** @test Verify that @ref flcn::CVec3::allEq follows IEEE 754 for NaN comparisons. */
TEST(CVec3EqualityTests, NanEqualityReturnsFalse)
{
    const flcn::CVec3 vecA = { NAN_F, NAN_F, NAN_F };
    const flcn::CVec3 vecB = { 1.0, -5.88874789, flcn::constants::INFINITY_D };

    const bool equality = vecA.allEq(vecB);
    EXPECT_FALSE(equality);
}


/** @test Verify that @ref flcn::CVec3::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(CVec3EqualityTests, InfinityAllEq_IdenticalVectorsReturnsTrue)
{
    const flcn::CVec3 vecA = { INF, -INF, INF };
    const flcn::CVec3 vecB = { INF, -INF, INF };

    const bool equality = vecA.allEq(vecB);
    EXPECT_TRUE(equality);
}


/** @test Verify that @ref flcn::CVec3::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(CVec3EqualityTests, InfinityEquality_DifferentVectorsReturnsFalse)
{
    const flcn::CVec3 vecA = { INF, INF, INF };
    const flcn::CVec3 vecB = { INF, -INF, INF };

    const bool equality = vecA.allEq(vecB);
    EXPECT_FALSE(equality);
}


/** @test Verify that the equality operator returns true for identical vectors. */
TYPED_TEST(CVec3EqualityTests, EqualityOperator_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA == this->_eqVecB;
    EXPECT_TRUE(equality);
}


/** @test Verify that @ref flcn::CVec3::allEq works for different vector types with identical components. */
TYPED_TEST(CVec3EqualityTests, MixedType_AllEq_IdenticalVectorsReturnsTrue)
{
    const flcn::CVec3 vecA(1, 2, 3);
    const flcn::CVec3 vecB(1.0, 2.0, 3.0);

    const bool equality = vecA.allEq(vecB);
    EXPECT_TRUE(equality);
}


/** @test Verify that @ref flcn::CVec3::allEq works for different vector types with different components. */
TYPED_TEST(CVec3EqualityTests, MixedType_Equality_DifferentVectorsReturnsFalse)
{
    const flcn::CVec3 vecA(5, 6, 7);
    const flcn::CVec3 vecB(1.0, 2.0, 3.0);

    const bool equality = vecA.allEq(vecB);
    EXPECT_FALSE(equality);
}


/** @test Verify that the equality operator returns false if any component differ. */
TYPED_TEST(CVec3EqualityTests, EqualityOperator_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA == this->_dissimilarVec;
    EXPECT_FALSE(equality);
}


/** @test Verify that the equality operator works for bool vector with identical components. */
TEST(CVec3EqualityTests, EqualityOperator_IdenticalBooleanVectorsReturnsTrue)
{
    const flcn::CVec3 vecA(true, false, true);
    const flcn::CVec3 vecB(true, false, true);

    const bool equality = vecA == vecB;
    EXPECT_TRUE(equality);
}


/** @test Verify that the equality operator works for bool vector with different components. */
TEST(CVec3EqualityTests, EqualityOperator_DifferentBooleanVectorsReturnsFalse)
{
    const flcn::CVec3 vecA(true, false, true);
    const flcn::CVec3 vecB(true, true, true);

    const bool equality = vecA == vecB;
    EXPECT_FALSE(equality);
}


/** @test Verify that @ref flcn::CVec3::eq returns @ref flcn::CVec3<bool> mask for identical vectors. */
TYPED_TEST(CVec3EqualityTests, EqualityReturnsCorrectBooleanMask)
{
    const flcn::CVec3<bool> mask = this->_eqVecA.eq(this->_dissimilarVec);
    EXPECT_VEC_EQ(this->_equalityMask, mask);
}


/** @test Verify that @ref flcn::CVec3::eq returns @ref flcn::CVec3<bool> mask for different vectors. */
TEST(CVec3EqualityTests, MixedType_EqualityReturnsCorrectBooleanMask)
{
    const flcn::CVec3 vecA         = { 1, 2, 3 };
    const flcn::CVec3 vecB         = { 1.0, 4.0, 0.0 };
    const flcn::CVec3 expectedMask = { true, false, false };

    const flcn::CVec3<bool> mask = vecA.eq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @test Verify that @ref flcn::CVec3::eq follows IEEE 754 for NaN comparisons. */
TEST(CVec3EqualityTests, NanEqualityReturnsFalseBooleanMask)
{
    const flcn::CVec3 vecA         = { NAN_F, NAN_F, NAN_F };
    const flcn::CVec3 vecB         = { 1.0, -5.88874789, flcn::constants::INFINITY_D };
    const flcn::CVec3 expectedMask = { false, false, false };

    const flcn::CVec3 mask = vecA.eq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @test Verify that @ref flcn::CVec3::eq follows IEEE 754 for INFINITY comparisons. */
TEST(CVec3EqualityTests, InfinityEqualityReturnsCorrectBooleanMask)
{
    const flcn::CVec3 vecA         = { INF, -INF, INF };
    const flcn::CVec3<double> vecB = { flcn::constants::INFINITY_D, flcn::constants::INFINITY_D, 10e11 };
    const flcn::CVec3 expectedMask = { true, false, false };

    const flcn::CVec3 mask = vecA.eq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


/**
 * @test Verify that the static variant of @ref flcn::CVec3::eq returns @ref flcn::CVec3<bool> mask
 *       for different vectors.
 */
TYPED_TEST(CVec3EqualityTests, StaticWrapper_EqualityReturnsCorrectBooleanMask)
{
    const flcn::CVec3<bool> mask = flcn::CVec3<TypeParam>::eq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_VEC_EQ(this->_equalityMask, mask);
}



/**************************************
 *          INEQUALITY TESTS          *
 **************************************/

/** @test Verify that @ref flcn::CVec3::anyNeq returns false for identical vectors. */
TYPED_TEST(CVec3EqualityTests, Inequality_IdenticalVectorsReturnsFalse)
{
    const bool inequality = this->_eqVecA.anyNeq(this->_eqVecB);
    EXPECT_FALSE(inequality);
}


/** @test Verify that @ref flcn::CVec3::anyNeq returns true if any component differ. */
TYPED_TEST(CVec3EqualityTests, Inequality_DifferentVectorsReturnsTrue)
{
    const bool inequality = this->_eqVecA.anyNeq(this->_dissimilarVec);
    EXPECT_TRUE(inequality);
}


/** @test Verify that the static variant of @ref flcn::CVec3::anyNeq for identical vectors. */
TYPED_TEST(CVec3EqualityTests, StaticWrapper_Inequality_IdenticalVectorsReturnsFalse)
{
    const bool inequality = flcn::CVec3<TypeParam>::anyNeq(this->_eqVecA, this->_eqVecB);
    EXPECT_FALSE(inequality);
}


/** @test Verify that the static variant of @ref flcn::CVec3::anyNeq for different vectors. */
TYPED_TEST(CVec3EqualityTests, StaticWrapper_Inequality_DifferentVectorsReturnsTrue)
{
    const bool inequality = flcn::CVec3<TypeParam>::anyNeq(this->_eqVecA, this->_dissimilarVec);
    EXPECT_TRUE(inequality);
}


/** @test Verify that @ref flcn::CVec3::anyNeq follows IEEE 754 for NaN comparisons. */
TEST(CVec3EqualityTests, NanInequalityReturnsTrue)
{
    const flcn::CVec3 vecA         = { NAN_F, NAN_F, NAN_F };
    const flcn::CVec3<double> vecB = {
        1.0,
        -5.88874789,
        flcn::constants::INFINITY_D,
    };

    const bool inequality = vecA.anyNeq(vecB);
    EXPECT_TRUE(inequality);
}


/** @test Verify that @ref flcn::CVec3::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(CVec3EqualityTests, InfinityInequality_IdenticalVectorsReturnsFalse)
{
    const flcn::CVec3 vecA = { INF, -INF, INF };
    const flcn::CVec3 vecB = { INF, -INF, INF };

    const bool inequality = vecA.anyNeq(vecB);
    EXPECT_FALSE(inequality);
}


/** @test Verify that @ref flcn::CVec3::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(CVec3EqualityTests, InfinityInequality_DifferentVectorsReturnsTrue)
{
    const flcn::CVec3 vecA = { INF, INF, INF };
    const flcn::CVec3 vecB = { INF, -INF, INF };

    const bool inequality = vecA.anyNeq(vecB);
    EXPECT_TRUE(inequality);
}


/** @test Verify that @ref flcn::CVec3::anyNeq works for different vector types with identical components. */
TYPED_TEST(CVec3EqualityTests, MixedType_Inequality_IdenticalVectorsReturnsFalse)
{
    const flcn::CVec3 vecA(1, 2, 3);
    const flcn::CVec3 vecB(1.0, 2.0, 3.0);

    const bool inequality = vecA.anyNeq(vecB);
    EXPECT_FALSE(inequality);
}


/** @test Verify that @ref flcn::CVec3::anyNeq works for different vector types with different components. */
TYPED_TEST(CVec3EqualityTests, MixedType_Inequality_DifferentVectorsReturnsTrue)
{
    const flcn::CVec3 vecA(5, 6, 7);
    const flcn::CVec3 vecB(1.0, 2.0, 3.0);

    const bool inequality = vecA.anyNeq(vecB);
    EXPECT_TRUE(inequality);
}


/** @test Verify that the operator returns false for identical vectors. */
TYPED_TEST(CVec3EqualityTests, NotEqualsOperator_IdenticalVectorsReturnsFalse)
{
    const bool inequality = this->_eqVecA != this->_eqVecB;
    EXPECT_FALSE(inequality);
}


/** @test Verify that the inequality operator returns true for different vectors. */
TYPED_TEST(CVec3EqualityTests, NotEqualsOperator_DifferentVectorsReturnsTrue)
{
    const bool inequality = this->_eqVecA != this->_dissimilarVec;
    EXPECT_TRUE(inequality);
}


/** @test Verify that the inequality operator works for @ref flcn::CVec3<bool> with identical components. */
TEST(CVec3EqualityTests, InequalityOperator_IdenticalBooleanVectorsReturnsFalse)
{
    const flcn::CVec3 vecA(true, false, true);
    const flcn::CVec3 vecB(true, false, true);

    const bool inequality = vecA != vecB;
    EXPECT_FALSE(inequality);
}


/** @test Verify that the inequality operator works for @ref flcn::CVec3<bool> with different components. */
TEST(CVec3EqualityTests, InequalityOperator_DifferentBooleanVectorsReturnsTrue)
{
    const flcn::CVec3 vecA(true, false, true);
    const flcn::CVec3 vecB(true, true, true);

    const bool inequality = vecA != vecB;
    EXPECT_TRUE(inequality);
}


/** @test Verify that @ref flcn::CVec3::neq returns @ref flcn::CVec3<bool> mask for identical vectors. */
TYPED_TEST(CVec3EqualityTests, InequalityReturnsCorrectBooleanMask)
{
    const flcn::CVec3<bool> mask = this->_eqVecA.neq(this->_dissimilarVec);
    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}


/** @test Verify that @ref flcn::CVec3::neq returns @ref flcn::CVec3<bool> mask for different vectors. */
TEST(CVec3EqualityTests, MixedType_InequalityReturnsCorrectBooleanMask)
{
    const flcn::CVec3 vecA         = { 1, 2, 3 };
    const flcn::CVec3 vecB         = { 1.0, 4.0, 0.0 };
    const flcn::CVec3 expectedMask = { false, true, true };

    const flcn::CVec3<bool> mask = vecA.neq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @test Verify that @ref flcn::CVec3::neq follows IEEE 754 for NaN comparisons. */
TEST(CVec3EqualityTests, NanInequalityReturnsTrueBooleanMask)
{
    const flcn::CVec3 vecA         = { NAN_F, NAN_F, NAN_F };
    const flcn::CVec3<double> vecB = { 1.0, -5.88874789, flcn::constants::INFINITY_D };
    const flcn::CVec3 expectedMask = { true, true, true };

    const flcn::CVec3 mask = vecA.neq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @test Verify that @ref flcn::CVec3::neq follows IEEE 754 for INFINITY comparisons. */
TEST(CVec3EqualityTests, InfinityInequalityReturnsCorrectBooleanMask)
{
    const flcn::CVec3 vecA         = { INF, -INF, INF };
    const flcn::CVec3 vecB         = { flcn::constants::INFINITY_D, flcn::constants::INFINITY_D, 10e11 };
    const flcn::CVec3 expectedMask = { false, true, true };

    const flcn::CVec3 mask = vecA.neq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


/**
 * @test Verify that the static variant of @ref flcn::CVec3::neq returns @ref flcn::CVec3<bool> mask
 *       for different vectors.
 */
TYPED_TEST(CVec3EqualityTests, StaticWrapper_InequalityReturnsCorrectBooleanMask)
{
    const flcn::CVec3<bool> mask = flcn::CVec3<TypeParam>::neq(this->_eqVecA, this->_dissimilarVec);
    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}

/** @} */
