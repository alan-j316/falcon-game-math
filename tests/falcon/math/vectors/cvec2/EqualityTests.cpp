/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref flcn::CVec2 equality operator (==, !=) and their functional counterpart's
 *        (eq, neq, allEq, anyNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CVec2TestSetup.h"

#include <falcon/math/common/Constants.h>




/**
 * @addtogroup T_FALCON_CVec2_Equality
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
     * @brief Test fixture for @ref CVec2 equality.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class CVec2EqualityTests: public testing::Test
    {
    protected:
        flcn::CVec2<T> _eqVecA;
        flcn::CVec2<T> _eqVecB;
        flcn::CVec2<T> _dissimilarVec;
        flcn::CVec2<bool> _equalityMask;
        flcn::CVec2<bool> _inequalityMask;


        void SetUp() override
        {
            _eqVecA         = { T(1.1234568789), T(2.123458319) };
            _eqVecB         = { T(1.1234568789), T(2.123458319) };
            _dissimilarVec  = { T(7.1234568789), T(2.123458319) };
            _equalityMask   = { false, true };
            _inequalityMask = { true, false };
        }
    };
    TYPED_TEST_SUITE(CVec2EqualityTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::CVec2 VEC_A(1, 2);
        constexpr flcn::CVec2 VEC_B(3, 2);
        constexpr flcn::CVec2 VEC_C(1, 2);


        /// @test Verify that @ref CVec2 allEq returns correct boolean for equal vectors.
        constexpr auto ALLEQ_EQ_VECS = VEC_A.allEq(VEC_B);
        static_assert(ALLEQ_EQ_VECS == false);

        /// @test Verify that @ref CVec2 allEq returns correct boolean for unequal vectors.
        constexpr auto ALL_EQ_UNEQUAL_VECS = VEC_A.allEq(VEC_C);
        static_assert(ALL_EQ_UNEQUAL_VECS == true);

        /// @test Verify that @ref CVec2 allEq (static wrapper) returns correct boolean for equal vectors.
        constexpr auto ALLEQ_EQ_VECS_STATIC = flcn::CVec2<int>::allEq(VEC_A, VEC_B);
        static_assert(ALLEQ_EQ_VECS_STATIC == false);

        /// @test Verify that @ref CVec2 allEq (static wrapper) returns correct boolean for unequal vectors.
        constexpr auto ALLEQ_UNEQUAL_VECS_STATIC = flcn::CVec2<int>::allEq(VEC_A, VEC_C);
        static_assert(ALLEQ_UNEQUAL_VECS_STATIC == true);

        /// @test Verify that @ref CVec2 equals operator returns correct boolean for equal vectors.
        constexpr auto DBLEQ_OP_EQUAL_VECS = VEC_A == VEC_B;
        static_assert(DBLEQ_OP_EQUAL_VECS == false);

        /// @test Verify that @ref CVec2 equals operator returns correct boolean for unequal vectors.
        constexpr auto DBLEQ_OP_UNEQUAL_VECS = VEC_A == VEC_C;
        static_assert(DBLEQ_OP_UNEQUAL_VECS == true);


        /// @test Verify that @ref CVec2 equality mask returns valid boolean mask
        constexpr auto EQ_VEC_MASK = VEC_A.eq(VEC_B);
        static_assert(EQ_VEC_MASK.x() == false);
        static_assert(EQ_VEC_MASK.y() == true);


        /// @test Verify that @ref CVec2 anyNeq returns correct boolean for equal vectors.
        constexpr auto ANYNEQ_EQ_VECS = VEC_A.anyNeq(VEC_B);
        static_assert(ANYNEQ_EQ_VECS == true);

        /// @test Verify that @ref CVec2 anyNeq returns correct boolean for unequal vectors.
        constexpr auto ANYNEQ_UNEQUAL_VECS = VEC_A.anyNeq(VEC_C);
        static_assert(ANYNEQ_UNEQUAL_VECS == false);

        /// @test Verify that @ref CVec2 anyNeq(static wrapper) returns correct boolean for equal vectors.
        constexpr auto ANYNEQ_EQ_VECS_STATIC = flcn::CVec2<int>::anyNeq(VEC_A, VEC_B);
        static_assert(ANYNEQ_EQ_VECS_STATIC == true);

        /// @test Verify that @ref CVec2 anyNeq(static wrapper) returns correct boolean for unequal vectors.
        constexpr auto ANYNEQ_UNEQUAL_VECS_STATIC = flcn::CVec2<int>::anyNeq(VEC_A, VEC_C);
        static_assert(ANYNEQ_UNEQUAL_VECS_STATIC == false);

        /// @test Verify that @ref CVec2 not equals operator returns correct boolean for equal vectors.
        constexpr auto ANYNEQ_OP_EQUAL_VECS = VEC_A != VEC_B;
        static_assert(ANYNEQ_OP_EQUAL_VECS == true);

        /// @test Verify that @ref CVec2 not equals operator returns correct boolean for unequal vectors.
        constexpr auto NOT_EQ_OP = VEC_A != VEC_C;
        static_assert(NOT_EQ_OP == false);

        /// @test Verify that @ref CVec2 inequality mask returns valid boolean mask.
        constexpr auto NEQ_MASK_VEC = VEC_A.neq(VEC_B);
        static_assert(NEQ_MASK_VEC.x() == true);
        static_assert(NEQ_MASK_VEC.y() == false);

    } // namespace static_tests
} // namespace



/**************************************
 *           EQUALITY TESTS           *
 **************************************/

TYPED_TEST(CVec2EqualityTests, AllEq_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA.allEq(this->_eqVecB);
    EXPECT_TRUE(equality);
}


TYPED_TEST(CVec2EqualityTests, AllEq_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA.allEq(this->_dissimilarVec);
    EXPECT_FALSE(equality);
}


TYPED_TEST(CVec2EqualityTests, StaticWrapper_AllEq_IdenticalVectorsReturnsTrue)
{
    const bool equality = flcn::CVec2<TypeParam>::allEq(this->_eqVecA, this->_eqVecB);

    EXPECT_TRUE(equality);
}


TYPED_TEST(CVec2EqualityTests, StaticWrapper_AllEq_DifferentVectorsReturnsFalse)
{
    const bool equality = flcn::CVec2<TypeParam>::allEq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_FALSE(equality);
}


TEST(CVec2EqualityTests, AllEq_NanVectorsReturnsFalse)
{
    const flcn::CVec2 vecA = { NAN_F, NAN_F };
    const flcn::CVec2 vecB = { 1.0, -5.88874789 };

    const bool equality = vecA.allEq(vecB);
    EXPECT_FALSE(equality) << "NaN vector shouldn't equal anything!";
}


TEST(CVec2EqualityTests, AllEq_IdenticalInfinitVectors_VectorsReturnsTrue)
{
    const flcn::CVec2 vecA = { INF, -INF };
    const flcn::CVec2 vecB = { INF, -INF };

    const bool equality = vecA.allEq(vecB);
    EXPECT_TRUE(equality);
}


TEST(CVec2EqualityTests, AllEq_DifferentInfinitVectors_VectorsReturnsFalse)
{
    const flcn::CVec2 vecA = { INF, INF };
    const flcn::CVec2 vecB = { INF, -INF };

    const bool equality = vecA.allEq(vecB);
    EXPECT_FALSE(equality);
}


TYPED_TEST(CVec2EqualityTests, DoubleEqualsOperator_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA == this->_eqVecB;

    EXPECT_TRUE(equality);
}


TYPED_TEST(CVec2EqualityTests, MixedType_AllEq_IdenticalVectorsReturnsTrue)
{
    const flcn::CVec2 vecA(1, 2);
    const flcn::CVec2 vecB(1.0, 2.0);

    const bool equality = vecA.allEq(vecB);

    EXPECT_TRUE(equality);
}


TYPED_TEST(CVec2EqualityTests, MixedType_AllEq_DifferentVectorsReturnsFalse)
{
    const flcn::CVec2 vecA(5, 6);
    const flcn::CVec2 vecB(1.0, 2.0);

    const bool equality = vecA.allEq(vecB);
    EXPECT_FALSE(equality);
}


TYPED_TEST(CVec2EqualityTests, DoubleEqualsOperator_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA == this->_dissimilarVec;
    EXPECT_FALSE(equality);
}


TEST(CVec2EqualityTests, DoubleEqualsOperator_IdenticalBooleanVectorsReturnsTrue)
{
    const flcn::CVec2 vecA(true, false);
    const flcn::CVec2 vecB(true, false);

    const bool equality = vecA == vecB;
    EXPECT_TRUE(equality);
}


TEST(CVec2EqualityTests, DoubleEqualsOperator_DifferentBooleanVectorsReturnsFalse)
{
    const flcn::CVec2 vecA(true, false);
    const flcn::CVec2 vecB(true, true);

    const bool equality = vecA == vecB;
    EXPECT_FALSE(equality);
}


TYPED_TEST(CVec2EqualityTests, Eq_ReturnsCorrectBooleanMask)
{
    const flcn::CVec2<bool> mask = this->_eqVecA.eq(this->_dissimilarVec);
    EXPECT_VEC_EQ(this->_equalityMask, mask);
}


TEST(CVec2EqualityTests, Eq_MixedType_ReturnsCorrectBooleanMask)
{
    const flcn::CVec2 vecA         = { 1, 2 };
    const flcn::CVec2 vecB         = { 1.0, 4.0 };
    const flcn::CVec2 expectedMask = { true, false };

    const flcn::CVec2<bool> mask = vecA.eq(vecB);

    EXPECT_VEC_EQ(expectedMask, mask);
}


TEST(CVec2EqualityTests, Eq_NanVectorsReturnsFalseBooleanMask)
{
    const flcn::CVec2 vecA         = { NAN_F, NAN_F };
    const flcn::CVec2 vecB         = { 1.0, -5.88874789 };
    const flcn::CVec2 expectedMask = { false, false };

    const flcn::CVec2 mask = vecA.eq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


TEST(CVec2EqualityTests, Eq_InfiniteVectorsReturnsCorrectBooleanMask)
{
    const flcn::CVec2 vecA         = { INF, -INF };
    const flcn::CVec2<double> vecB = { flcn::constants::INFINITY_D, flcn::constants::INFINITY_D };
    const flcn::CVec2 expectedMask = { true, false };

    const flcn::CVec2 mask = vecA.eq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


TYPED_TEST(CVec2EqualityTests, StaticWrapper_Eq_ReturnsCorrectBooleanMask)
{
    const flcn::CVec2<bool> mask = flcn::CVec2<TypeParam>::eq(this->_eqVecA, this->_dissimilarVec);
    EXPECT_VEC_EQ(this->_equalityMask, mask);
}



/**************************************
 *          INEQUALITY TESTS          *
 **************************************/

TYPED_TEST(CVec2EqualityTests, AnyNeq_IdenticalVectorsReturnsFalse)
{
    const bool inequality = this->_eqVecA.anyNeq(this->_eqVecB);
    EXPECT_FALSE(inequality);
}


TYPED_TEST(CVec2EqualityTests, AnyNeq_DifferentVectorsReturnsTrue)
{
    const bool inequality = this->_eqVecA.anyNeq(this->_dissimilarVec);
    EXPECT_TRUE(inequality);
}


TYPED_TEST(CVec2EqualityTests, StaticWrapper_AnyNeq_IdenticalVectorsReturnsFalse)
{
    const bool inequality = flcn::CVec2<TypeParam>::anyNeq(this->_eqVecA, this->_eqVecB);
    EXPECT_FALSE(inequality);
}


TYPED_TEST(CVec2EqualityTests, StaticWrapper_AnyNeq_DifferentVectorsReturnsTrue)
{
    const bool inequality = flcn::CVec2<TypeParam>::anyNeq(this->_eqVecA, this->_dissimilarVec);
    EXPECT_TRUE(inequality);
}


TEST(CVec2EqualityTests, AnyNeq_NaNVectorsReturnsTrue)
{
    const flcn::CVec2 vecA = { NAN_F, NAN_F };
    const flcn::CVec2 vecB = { 1.0, -5.88874789 };

    const bool inequality = vecA.anyNeq(vecB);
    EXPECT_TRUE(inequality);
}


TEST(CVec2EqualityTests, AnyNeq_IdenticalInfinitVectors_ReturnsFalse)
{
    const flcn::CVec2 vecA = { INF, -INF };
    const flcn::CVec2 vecB = { INF, -INF };

    const bool inequality = vecA.anyNeq(vecB);
    EXPECT_FALSE(inequality);
}


TEST(CVec2EqualityTests, AnyNeq_DifferentInfinitVectors_ReturnsTrue)
{
    const flcn::CVec2 vecA = { INF, INF };
    const flcn::CVec2 vecB = { INF, -INF };

    const bool inequality = vecA.anyNeq(vecB);
    EXPECT_TRUE(inequality);
}


TYPED_TEST(CVec2EqualityTests, AnyNeq_MixedType_IdenticalVectorsReturnsFalse)
{
    const flcn::CVec2 vecA(1, 2);
    const flcn::CVec2 vecB(1.0, 2.0);

    const bool inequality = vecA.anyNeq(vecB);
    EXPECT_FALSE(inequality);
}


TYPED_TEST(CVec2EqualityTests, AnyNeq_MixedType_DifferentVectorsReturnsTrue)
{
    const flcn::CVec2 vecA(5, 6);
    const flcn::CVec2 vecB(1.0, 2.0);

    const bool inequality = vecA.anyNeq(vecB);
    EXPECT_TRUE(inequality);
}


TYPED_TEST(CVec2EqualityTests, NotEqualsOperator_IdenticalVectorsReturnsFalse)
{
    const bool inequality = this->_eqVecA != this->_eqVecB;
    EXPECT_FALSE(inequality);
}


TYPED_TEST(CVec2EqualityTests, NotEqualsOperator_DifferentVectorsReturnsTrue)
{
    const bool inequality = this->_eqVecA != this->_dissimilarVec;
    EXPECT_TRUE(inequality);
}


TEST(CVec2EqualityTests, InequalityOperator_IdenticalBooleanVectorsReturnsFalse)
{
    const flcn::CVec2 vecA(true, false);
    const flcn::CVec2 vecB(true, false);

    const bool inequality = vecA != vecB;
    EXPECT_FALSE(inequality);
}


TEST(CVec2EqualityTests, InequalityOperator_DifferentBooleanVectorsReturnsTrue)
{
    const flcn::CVec2 vecA(true, false);
    const flcn::CVec2 vecB(true, true);

    const bool inequality = vecA != vecB;
    EXPECT_TRUE(inequality);
}


TYPED_TEST(CVec2EqualityTests, Neq_ReturnsCorrectBooleanMask)
{
    const flcn::CVec2<bool> mask = this->_eqVecA.neq(this->_dissimilarVec);
    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}


TEST(CVec2EqualityTests, Neq_MixedType_ReturnsCorrectBooleanMask)
{
    const flcn::CVec2 vecA         = { 1, 2 };
    const flcn::CVec2 vecB         = { 1.0, 4.0 };
    const flcn::CVec2 expectedMask = { false, true };

    const flcn::CVec2<bool> mask = vecA.neq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


TEST(CVec2EqualityTests, Neq_NaNVectorsReturnsTrueBooleanMask)
{
    const flcn::CVec2 vecA         = { NAN_F, NAN_F };
    const flcn::CVec2 vecB         = { 1.0, -5.88874789 };
    const flcn::CVec2 expectedMask = { true, true };

    const flcn::CVec2 mask = vecA.neq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


TEST(CVec2EqualityTests, Neq_InfinityVectorsReturnsCorrectBooleanMask)
{
    const flcn::CVec2 vecA         = { INF, -INF };
    const flcn::CVec2 vecB         = { flcn::constants::INFINITY_D, flcn::constants::INFINITY_D };
    const flcn::CVec2 expectedMask = { false, true };

    const flcn::CVec2 mask = vecA.neq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}



TYPED_TEST(CVec2EqualityTests, StaticWrapper_Neq_ReturnsCorrectBooleanMask)
{
    const flcn::CVec2<bool> mask = flcn::CVec2<TypeParam>::neq(this->_eqVecA, this->_dissimilarVec);
    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}

/** @} */
