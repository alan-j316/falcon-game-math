/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref flcn::Vec2 equality operator (==, !=) and their functional counterpart's
 *        (eq, neq, allEq, anyNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"

#include <falcon/math/common/Constants.h>




/**
 * @addtogroup T_FALCON_Vec2_Equality
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
     * @brief Test fixture for @ref Vec2 equality.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec2EqualityTests: public testing::Test
    {
    protected:
        flcn::Vec2<T> _eqVecA;
        flcn::Vec2<T> _eqVecB;
        flcn::Vec2<T> _dissimilarVec;
        flcn::Vec2<flcn::Mask_t<T>> _equalityMask;
        flcn::Vec2<flcn::Mask_t<T>> _inequalityMask;


        void SetUp() override
        {
            _eqVecA         = { T(1.1234568789), T(2.123458319) };
            _eqVecB         = { T(1.1234568789), T(2.123458319) };
            _dissimilarVec  = { T(7.1234568789), T(2.123458319) };
            _equalityMask   = { False<T>, True<T> };
            _inequalityMask = { True<T>, False<T> };
        }
    };
    TYPED_TEST_SUITE(Vec2EqualityTests, SupportedArithmeticTypes);

} // namespace



/**************************************
 *           EQUALITY TESTS           *
 **************************************/

TYPED_TEST(Vec2EqualityTests, AllEq_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA.allEq(this->_eqVecB);
    EXPECT_TRUE(equality);
}


TYPED_TEST(Vec2EqualityTests, AllEq_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA.allEq(this->_dissimilarVec);
    EXPECT_FALSE(equality);
}


TYPED_TEST(Vec2EqualityTests, StaticWrapper_AllEq_IdenticalVectorsReturnsTrue)
{
    const bool equality = flcn::Vec2<TypeParam>::allEq(this->_eqVecA, this->_eqVecB);

    EXPECT_TRUE(equality);
}


TYPED_TEST(Vec2EqualityTests, StaticWrapper_AllEq_DifferentVectorsReturnsFalse)
{
    const bool equality = flcn::Vec2<TypeParam>::allEq(this->_eqVecA, this->_dissimilarVec);

    EXPECT_FALSE(equality);
}


TEST(Vec2EqualityTests, AllEq_NanVectorsReturnsFalse)
{
    const flcn::Vec2 vecA = { NAN_F, NAN_F };
    const flcn::Vec2 vecB = { 1.0f, -5.88874789f };

    const bool equality = vecA.allEq(vecB);
    EXPECT_FALSE(equality) << "NaN vector shouldn't equal anything!";
}


TEST(Vec2EqualityTests, AllEq_IdenticalInfinitVectors_VectorsReturnsTrue)
{
    const flcn::Vec2 vecA = { INF, -INF };
    const flcn::Vec2 vecB = { INF, -INF };

    const bool equality = vecA.allEq(vecB);
    EXPECT_TRUE(equality);
}


TEST(Vec2EqualityTests, AllEq_DifferentInfinitVectors_VectorsReturnsFalse)
{
    const flcn::Vec2 vecA = { INF, INF };
    const flcn::Vec2 vecB = { INF, -INF };

    const bool equality = vecA.allEq(vecB);
    EXPECT_FALSE(equality);
}


TYPED_TEST(Vec2EqualityTests, DoubleEqualsOperator_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA == this->_eqVecB;

    EXPECT_TRUE(equality);
}


TYPED_TEST(Vec2EqualityTests, DoubleEqualsOperator_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA == this->_dissimilarVec;
    EXPECT_FALSE(equality);
}


TEST(Vec2EqualityTests, DoubleEqualsOperator_IdenticalBooleanVectorsReturnsTrue)
{
    const flcn::Vec2 vecA(True<float>, False<float>);
    const flcn::Vec2 vecB(True<float>, False<float>);

    const bool equality = vecA == vecB;
    EXPECT_TRUE(equality);
}


TEST(Vec2EqualityTests, DoubleEqualsOperator_DifferentBooleanVectorsReturnsFalse)
{
    const flcn::Vec2 vecA(True<float>, False<float>);
    const flcn::Vec2 vecB(True<float>, True<float>);

    const bool equality = vecA == vecB;
    EXPECT_FALSE(equality);
}


TYPED_TEST(Vec2EqualityTests, Eq_ReturnsCorrectBooleanMask)
{
    const auto mask = this->_eqVecA.eq(this->_dissimilarVec);
    EXPECT_VEC_EQ(this->_equalityMask, mask);
}


TEST(Vec2EqualityTests, Eq_NanVectorsReturnsFalseBooleanMask)
{
    const flcn::Vec2 vecA         = { NAN_F, NAN_F };
    const flcn::Vec2 vecB         = { 1.0f, -5.88874789f };
    const flcn::Vec2 expectedMask = { False<float>, False<float> };

    const flcn::Vec2 mask = vecA.eq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


TEST(Vec2EqualityTests, Eq_InfiniteVectorsReturnsCorrectBooleanMask)
{
    const flcn::Vec2 vecA         = { INF, -INF };
    const flcn::Vec2 vecB = { INF, INF };
    const flcn::Vec2 expectedMask = { True<float>, False<float> };

    const flcn::Vec2 mask = vecA.eq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


TYPED_TEST(Vec2EqualityTests, StaticWrapper_Eq_ReturnsCorrectBooleanMask)
{
    const auto mask = flcn::Vec2<TypeParam>::eq(this->_eqVecA, this->_dissimilarVec);
    EXPECT_VEC_EQ(this->_equalityMask, mask);
}



/**************************************
 *          INEQUALITY TESTS          *
 **************************************/

TYPED_TEST(Vec2EqualityTests, AnyNeq_IdenticalVectorsReturnsFalse)
{
    const bool inequality = this->_eqVecA.anyNeq(this->_eqVecB);
    EXPECT_FALSE(inequality);
}


TYPED_TEST(Vec2EqualityTests, AnyNeq_DifferentVectorsReturnsTrue)
{
    const bool inequality = this->_eqVecA.anyNeq(this->_dissimilarVec);
    EXPECT_TRUE(inequality);
}


TYPED_TEST(Vec2EqualityTests, StaticWrapper_AnyNeq_IdenticalVectorsReturnsFalse)
{
    const bool inequality = flcn::Vec2<TypeParam>::anyNeq(this->_eqVecA, this->_eqVecB);
    EXPECT_FALSE(inequality);
}


TYPED_TEST(Vec2EqualityTests, StaticWrapper_AnyNeq_DifferentVectorsReturnsTrue)
{
    const bool inequality = flcn::Vec2<TypeParam>::anyNeq(this->_eqVecA, this->_dissimilarVec);
    EXPECT_TRUE(inequality);
}


TEST(Vec2EqualityTests, AnyNeq_NaNVectorsReturnsTrue)
{
    const flcn::Vec2 vecA = { NAN_F, NAN_F };
    const flcn::Vec2 vecB = { 1.0f, -5.88874789f };

    const bool inequality = vecA.anyNeq(vecB);
    EXPECT_TRUE(inequality);
}


TEST(Vec2EqualityTests, AnyNeq_IdenticalInfinitVectors_ReturnsFalse)
{
    const flcn::Vec2 vecA = { INF, -INF };
    const flcn::Vec2 vecB = { INF, -INF };

    const bool inequality = vecA.anyNeq(vecB);
    EXPECT_FALSE(inequality);
}


TEST(Vec2EqualityTests, AnyNeq_DifferentInfinitVectors_ReturnsTrue)
{
    const flcn::Vec2 vecA = { INF, INF };
    const flcn::Vec2 vecB = { INF, -INF };

    const bool inequality = vecA.anyNeq(vecB);
    EXPECT_TRUE(inequality);
}


TYPED_TEST(Vec2EqualityTests, NotEqualsOperator_IdenticalVectorsReturnsFalse)
{
    const bool inequality = this->_eqVecA != this->_eqVecB;
    EXPECT_FALSE(inequality);
}


TYPED_TEST(Vec2EqualityTests, NotEqualsOperator_DifferentVectorsReturnsTrue)
{
    const bool inequality = this->_eqVecA != this->_dissimilarVec;
    EXPECT_TRUE(inequality);
}


TEST(Vec2EqualityTests, InequalityOperator_IdenticalBooleanVectorsReturnsFalse)
{
    const flcn::Vec2 vecA(True<float>, False<float>);
    const flcn::Vec2 vecB(True<float>, False<float>);

    const bool inequality = vecA != vecB;
    EXPECT_FALSE(inequality);
}


TEST(Vec2EqualityTests, InequalityOperator_DifferentBooleanVectorsReturnsTrue)
{
    const flcn::Vec2 vecA(True<float>, False<float>);
    const flcn::Vec2 vecB(True<float>, True<float>);

    const bool inequality = vecA != vecB;
    EXPECT_TRUE(inequality);
}


TYPED_TEST(Vec2EqualityTests, Neq_ReturnsCorrectBooleanMask)
{
    const auto mask = this->_eqVecA.neq(this->_dissimilarVec);
    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}


TEST(Vec2EqualityTests, Neq_NaNVectorsReturnsTrueBooleanMask)
{
    const flcn::Vec2 vecA         = { NAN_F, NAN_F };
    const flcn::Vec2 vecB         = { 1.0f, -5.88874789f };
    const flcn::Vec2 expectedMask = { True<float>, True<float> };

    const flcn::Vec2 mask = vecA.neq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


TEST(Vec2EqualityTests, Neq_InfinityVectorsReturnsCorrectBooleanMask)
{
    const flcn::Vec2 vecA         = { INF, -INF };
    const flcn::Vec2 vecB         = { INF, INF };
    const flcn::Vec2 expectedMask = { False<float>, True<float> };

    const flcn::Vec2 mask = vecA.neq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}



TYPED_TEST(Vec2EqualityTests, StaticWrapper_Neq_ReturnsCorrectBooleanMask)
{
    const auto mask = flcn::Vec2<TypeParam>::neq(this->_eqVecA, this->_dissimilarVec);
    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}

/** @} */
