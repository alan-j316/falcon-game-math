/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify @ref flcn::Vec3 equality operator (==, !=) and their functional counterpart's (eq, neq, allEq,
 * anyNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"

#include <falcon/math/common/Constants.h>

/**
 * @addtogroup T_Falcon_Vec3_Equality
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
     * @brief Test fixture for @ref Vec3 equality.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec3EqualityTests: public testing::Test
    {
    protected:
        flcn::Vec3<T> _eqVecA;
        flcn::Vec3<T> _eqVecB;
        flcn::Vec3<T> _dissimilarVec;
        flcn::Vec3<flcn::Mask_t<T>> _equalityMask;
        flcn::Vec3<flcn::Mask_t<T>> _inequalityMask;


        void SetUp() override
        {
            _eqVecA         = { T(1.1234568789), T(2.123458319), T(5.123412593891) };
            _eqVecB         = { T(1.1234568789), T(2.123458319), T(5.123412593891) };
            _dissimilarVec  = { T(7.1234568789), T(2.123458319), T(24.00) };
            _equalityMask   = { False<T>, True<T>, False<T> };
            _inequalityMask = { True<T>, False<T>, True<T> };
        }
    };
    TYPED_TEST_SUITE(Vec3EqualityTests, SupportedArithmeticTypes);

} // namespace



/**************************************
 *           EQUALITY TESTS           *
 **************************************/

/** @test Verify that @ref flcn::Vec3::allEq returns True for identical vectors. */
TYPED_TEST(Vec3EqualityTests, AllEq_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA.allEq(this->_eqVecB);
    EXPECT_TRUE(equality);
}


/** @test Verify that @ref flcn::Vec3::allEq returns False if any component differ. */
TYPED_TEST(Vec3EqualityTests, Equality_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA.allEq(this->_dissimilarVec);
    EXPECT_FALSE(equality);
}


/** @test Verify that the static variant of @ref flcn::Vec3::allEq for identical vectors. */
TYPED_TEST(Vec3EqualityTests, StaticWrapper_AllEq_IdenticalVectorsReturnsTrue)
{
    const bool equality = flcn::Vec3<TypeParam>::allEq(this->_eqVecA, this->_eqVecB);
    EXPECT_TRUE(equality);
}


/** @test Verify that the static variant of @ref flcn::Vec3::allEq for different vectors. */
TYPED_TEST(Vec3EqualityTests, StaticWrapper_Equality_DifferentVectorsReturnsFalse)
{
    const bool equality = flcn::Vec3<TypeParam>::allEq(this->_eqVecA, this->_dissimilarVec);
    EXPECT_FALSE(equality);
}


/** @test Verify that @ref flcn::Vec3::allEq follows IEEE 754 for NaN comparisons. */
TEST(Vec3EqualityTests, NanEqualityReturnsFalse)
{
    const flcn::Vec3 vecA = { NAN_F, NAN_F, NAN_F };
    const flcn::Vec3 vecB = { 1.0f, -5.88874789f, flcn::constants::INFINITY_F };

    const bool equality = vecA.allEq(vecB);
    EXPECT_FALSE(equality);
}


/** @test Verify that @ref flcn::Vec3::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec3EqualityTests, InfinityAllEq_IdenticalVectorsReturnsTrue)
{
    const flcn::Vec3 vecA = { INF, -INF, INF };
    const flcn::Vec3 vecB = { INF, -INF, INF };

    const bool equality = vecA.allEq(vecB);
    EXPECT_TRUE(equality);
}


/** @test Verify that @ref flcn::Vec3::allEq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec3EqualityTests, InfinityEquality_DifferentVectorsReturnsFalse)
{
    const flcn::Vec3 vecA = { INF, INF, INF };
    const flcn::Vec3 vecB = { INF, -INF, INF };

    const bool equality = vecA.allEq(vecB);
    EXPECT_FALSE(equality);
}


/** @test Verify that the equality operator returns True for identical vectors. */
TYPED_TEST(Vec3EqualityTests, EqualityOperator_IdenticalVectorsReturnsTrue)
{
    const bool equality = this->_eqVecA == this->_eqVecB;
    EXPECT_TRUE(equality);
}


/** @test Verify that the equality operator returns False if any component differ. */
TYPED_TEST(Vec3EqualityTests, EqualityOperator_DifferentVectorsReturnsFalse)
{
    const bool equality = this->_eqVecA == this->_dissimilarVec;
    EXPECT_FALSE(equality);
}


/** @test Verify that the equality operator works for bool vector with identical components. */
TEST(Vec3EqualityTests, EqualityOperator_IdenticalBooleanVectorsReturnsTrue)
{
    const flcn::Vec3 vecA(True<float>, False<float>, True<float>);
    const flcn::Vec3 vecB(True<float>, False<float>, True<float>);

    const bool equality = vecA == vecB;
    EXPECT_TRUE(equality);
}


/** @test Verify that the equality operator works for bool vector with different components. */
TEST(Vec3EqualityTests, EqualityOperator_DifferentBooleanVectorsReturnsFalse)
{
    const flcn::Vec3 vecA(True<float>, False<float>, True<float>);
    const flcn::Vec3 vecB(True<float>, True<float>, True<float>);

    const bool equality = vecA == vecB;
    EXPECT_FALSE(equality);
}


/** @test Verify that @ref flcn::Vec3::eq returns @ref flcn::Vec3 mask for identical vectors. */
TYPED_TEST(Vec3EqualityTests, EqualityReturnsCorrectBooleanMask)
{
    const flcn::Vec3 mask = this->_eqVecA.eq(this->_dissimilarVec);
    EXPECT_VEC_EQ(this->_equalityMask, mask);
}


/** @test Verify that @ref flcn::Vec3::eq follows IEEE 754 for NaN comparisons. */
TEST(Vec3EqualityTests, NanEqualityReturnsFalseBooleanMask)
{
    const flcn::Vec3 vecA         = { NAN_F, NAN_F, NAN_F };
    const flcn::Vec3 vecB         = { 1.0f, -5.88874789f, flcn::constants::INFINITY_F };
    const flcn::Vec3 expectedMask = { False<float>, False<float>, False<float> };

    const flcn::Vec3 mask = vecA.eq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @test Verify that @ref flcn::Vec3::eq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec3EqualityTests, InfinityEqualityReturnsCorrectBooleanMask)
{
    const flcn::Vec3 vecA         = { INF, -INF, INF };
    const flcn::Vec3 vecB         = { flcn::constants::INFINITY_F, flcn::constants::INFINITY_F, 10.0f };
    const flcn::Vec3 expectedMask = { True<float>, False<float>, False<float> };

    const flcn::Vec3 mask = vecA.eq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


/**
 * @test Verify that the static variant of @ref flcn::Vec3::eq returns @ref flcn::Vec3<bool> mask
 *       for different vectors.
 */
TYPED_TEST(Vec3EqualityTests, StaticWrapper_EqualityReturnsCorrectBooleanMask)
{
    const flcn::Vec3 mask = flcn::Vec3<TypeParam>::eq(this->_eqVecA, this->_dissimilarVec);
    EXPECT_VEC_EQ(this->_equalityMask, mask);
}



/**************************************
 *          INEQUALITY TESTS          *
 **************************************/

/** @test Verify that @ref flcn::Vec3::anyNeq returns False for identical vectors. */
TYPED_TEST(Vec3EqualityTests, Inequality_IdenticalVectorsReturnsFalse)
{
    const bool inequality = this->_eqVecA.anyNeq(this->_eqVecB);
    EXPECT_FALSE(inequality);
}


/** @test Verify that @ref flcn::Vec3::anyNeq returns True if any component differ. */
TYPED_TEST(Vec3EqualityTests, Inequality_DifferentVectorsReturnsTrue)
{
    const bool inequality = this->_eqVecA.anyNeq(this->_dissimilarVec);
    EXPECT_TRUE(inequality);
}


/** @test Verify that the static variant of @ref flcn::Vec3::anyNeq for identical vectors. */
TYPED_TEST(Vec3EqualityTests, StaticWrapper_Inequality_IdenticalVectorsReturnsFalse)
{
    const bool inequality = flcn::Vec3<TypeParam>::anyNeq(this->_eqVecA, this->_eqVecB);
    EXPECT_FALSE(inequality);
}


/** @test Verify that the static variant of @ref flcn::Vec3::anyNeq for different vectors. */
TYPED_TEST(Vec3EqualityTests, StaticWrapper_Inequality_DifferentVectorsReturnsTrue)
{
    const bool inequality = flcn::Vec3<TypeParam>::anyNeq(this->_eqVecA, this->_dissimilarVec);
    EXPECT_TRUE(inequality);
}


/** @test Verify that @ref flcn::Vec3::anyNeq follows IEEE 754 for NaN comparisons. */
TEST(Vec3EqualityTests, NanInequalityReturnsTrue)
{
    const flcn::Vec3 vecA = { NAN_F, NAN_F, NAN_F };
    const flcn::Vec3 vecB = {
        1.0f,
        -5.88874789f,
        flcn::constants::INFINITY_F,
    };

    const bool inequality = vecA.anyNeq(vecB);
    EXPECT_TRUE(inequality);
}


/** @test Verify that @ref flcn::Vec3::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec3EqualityTests, InfinityInequality_IdenticalVectorsReturnsFalse)
{
    const flcn::Vec3 vecA = { INF, -INF, INF };
    const flcn::Vec3 vecB = { INF, -INF, INF };

    const bool inequality = vecA.anyNeq(vecB);
    EXPECT_FALSE(inequality);
}


/** @test Verify that @ref flcn::Vec3::anyNeq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec3EqualityTests, InfinityInequality_DifferentVectorsReturnsTrue)
{
    const flcn::Vec3 vecA = { INF, INF, INF };
    const flcn::Vec3 vecB = { INF, -INF, INF };

    const bool inequality = vecA.anyNeq(vecB);
    EXPECT_TRUE(inequality);
}


/** @test Verify that the operator returns False for identical vectors. */
TYPED_TEST(Vec3EqualityTests, NotEqualsOperator_IdenticalVectorsReturnsFalse)
{
    const bool inequality = this->_eqVecA != this->_eqVecB;
    EXPECT_FALSE(inequality);
}


/** @test Verify that the inequality operator returns True for different vectors. */
TYPED_TEST(Vec3EqualityTests, NotEqualsOperator_DifferentVectorsReturnsTrue)
{
    const bool inequality = this->_eqVecA != this->_dissimilarVec;
    EXPECT_TRUE(inequality);
}


/** @test Verify that the inequality operator works for @ref flcn::Vec3<bool> with identical components. */
TEST(Vec3EqualityTests, InequalityOperator_IdenticalBooleanVectorsReturnsFalse)
{
    const flcn::Vec3 vecA(True<float>, False<float>, True<float>);
    const flcn::Vec3 vecB(True<float>, False<float>, True<float>);

    const bool inequality = vecA != vecB;
    EXPECT_FALSE(inequality);
}


/** @test Verify that the inequality operator works for @ref flcn::Vec3<bool> with different components. */
TEST(Vec3EqualityTests, InequalityOperator_DifferentBooleanVectorsReturnsTrue)
{
    const flcn::Vec3 vecA(True<float>, False<float>, True<float>);
    const flcn::Vec3 vecB(True<float>, True<float>, True<float>);

    const bool inequality = vecA != vecB;
    EXPECT_TRUE(inequality);
}


/** @test Verify that @ref flcn::Vec3::neq returns @ref flcn::Vec3<bool> mask for identical vectors. */
TYPED_TEST(Vec3EqualityTests, InequalityReturnsCorrectBooleanMask)
{
    const flcn::Vec3 mask = this->_eqVecA.neq(this->_dissimilarVec);
    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}


/** @test Verify that @ref flcn::Vec3::neq follows IEEE 754 for NaN comparisons. */
TEST(Vec3EqualityTests, NanInequalityReturnsTrueBooleanMask)
{
    const flcn::Vec3 vecA         = { NAN_F, NAN_F, NAN_F };
    const flcn::Vec3 vecB         = { 1.0f, -5.88874789f, flcn::constants::INFINITY_F };
    const flcn::Vec3 expectedMask = { True<float>, True<float>, True<float> };

    const flcn::Vec3 mask = vecA.neq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


/** @test Verify that @ref flcn::Vec3::neq follows IEEE 754 for INFINITY comparisons. */
TEST(Vec3EqualityTests, InfinityInequalityReturnsCorrectBooleanMask)
{
    const flcn::Vec3 vecA         = { INF, -INF, INF };
    const flcn::Vec3 vecB         = { flcn::constants::INFINITY_F, flcn::constants::INFINITY_F, 10.f };
    const flcn::Vec3 expectedMask = { False<float>, True<float>, True<float> };

    const flcn::Vec3 mask = vecA.neq(vecB);
    EXPECT_VEC_EQ(expectedMask, mask);
}


/**
 * @test Verify that the static variant of @ref flcn::Vec3::neq returns @ref flcn::Vec3<bool> mask
 *       for different vectors.
 */
TYPED_TEST(Vec3EqualityTests, StaticWrapper_InequalityReturnsCorrectBooleanMask)
{
    const flcn::Vec3 mask = flcn::Vec3<TypeParam>::neq(this->_eqVecA, this->_dissimilarVec);
    EXPECT_VEC_EQ(this->_inequalityMask, mask);
}

/** @} */
