/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 05, 2026
 *
 * @brief Verify @ref flcn::Quaternion equality operator (==, !=) and their functional counterpart's (vecEq,  allEq,
 * anyNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "include/QuaternionTestSetup.h"

#include <../../../../include/falcon/core/Constants.h>


/**
 * @addtogroup T_Falcon_Quaternion_Equality
 * @{
 */

namespace
{

    /**************************************
     *             TEST SETUP             *
     **************************************/

    constexpr auto NAN_F = flcn::constants::NaN;
    constexpr auto INF   = flcn::constants::INFINITY_F;

    template <typename T>
    class QuaternionEqualityTests: public testing::Test
    {
    protected:
        flcn::Quat<T> _eqQuatA, _eqQuatB, _eqVecQuatA, _eqVecQuatB;
        flcn::Quat<T> _dissimilarQuat;
        flcn::Quat<bool> _equalityMask;
        flcn::Quat<bool> _inequalityMask;


        void SetUp() override
        {
            _eqQuatA = { T(1.1234568789), T(2.123458319), T(5.123412593891), T(123.123489172589) };
            _eqQuatB = { T(1.1234568789), T(2.123458319), T(5.123412593891), T(123.123489172589) };
            // Scalar part for *VecQuat* are different
            _eqVecQuatA     = { T(1.1234568789), T(2.123458319), T(5.123412593891), T(56.213432412) };
            _eqVecQuatB     = { T(1.1234568789), T(2.123458319), T(5.123412593891), T(123.123489172589) };
            _dissimilarQuat = { T(7.1234568789), T(2.123458319), T(24.00), T(123.123489172589) };
            _equalityMask   = { false, true, false, true };
            _inequalityMask = { true, false, true, false };
        }
    };
    TYPED_TEST_SUITE(QuaternionEqualityTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        /**************************************
         *          EQUALITY TESTS            *
         **************************************/

        // Quat C and D have same vector but different vector part
        constexpr flcn::Quat QUAT_A(1, 2, 4, 12);
        constexpr flcn::Quat QUAT_B(3, 2, 1, 7);
        constexpr flcn::Quat QUAT_C(1, 2, 4, 12);
        constexpr flcn::Quat QUAT_D(1, 2, 4, 18);

        /// @test Verify that Quaternion allEq returns the correct boolean at compile time,
        ///       given two quaternions with different components.
        static_assert(QUAT_A.allEq(QUAT_B) == false);

        /// @test Verify that Quaternion allEq returns the correct boolean at compile time,
        ///       given two quaternions with same components.
        static_assert(QUAT_A.allEq(QUAT_C) == true);


        /// @test Verify that Quaternion allEq(static wrapper) returns the correct boolean at compile time,
        ///       given two quaternions with different components.
        static_assert(flcn::Quat<int>::allEq(QUAT_A, QUAT_B) == false);

        /// @test Verify that Quaternion allEq(static wrapper) returns the correct boolean at compile time,
        ///       given two quaternions with same components.
        static_assert(flcn::Quat<int>::allEq(QUAT_A, QUAT_C) == true);


        /// @test Verify that Quaternion eq returns the correct boolean mask at compile time.
        constexpr auto EQ_QUAT_MASK = QUAT_A.eq(QUAT_B);
        static_assert(EQ_QUAT_MASK.x() == false);
        static_assert(EQ_QUAT_MASK.y() == true);
        static_assert(EQ_QUAT_MASK.z() == false);
        static_assert(EQ_QUAT_MASK.w() == false);

        /// @test Verify that Quaternion eq (static wrapper) returns the correct boolean mask at compile time.
        constexpr auto EQ_QUAT_MASK_STATIC = flcn::Quat<int>::eq(QUAT_A, QUAT_B);
        static_assert(EQ_QUAT_MASK_STATIC.x() == false);
        static_assert(EQ_QUAT_MASK_STATIC.y() == true);
        static_assert(EQ_QUAT_MASK_STATIC.z() == false);
        static_assert(EQ_QUAT_MASK_STATIC.w() == false);


        /// @test Verify that Quaternion vecEq returns the correct boolean at compile time,
        ///       given two quaternions with different vector parts.
        static_assert(QUAT_A.vecEq(QUAT_B) == false);

        /// @test Verify that Quaternion vecEq returns the correct boolean at compile time,
        ///       given two quaternions with same vector parts.
        static_assert(QUAT_A.vecEq(QUAT_D) == true);


        /// @test Verify that Quaternion vecEq(static wrapper) returns the correct boolean at compile time,
        ///       given two quaternions with different vector parts.
        static_assert(flcn::Quat<int>::vecEq(QUAT_A, QUAT_B) == false);

        /// @test Verify that Quaternion vecEq(static wrapper) returns the correct boolean at compile time,
        ///       given two quaternions with same vector parts.
        static_assert(flcn::Quat<int>::vecEq(QUAT_A, QUAT_D) == true);


        /// @test Verify that Quaternion operator== returns the correct boolean at compile time,
        ///       given two quaternions with different components.
        static_assert((QUAT_A == QUAT_B) == false);

        /// @test Verify that Quaternion operator== returns the correct boolean at compile time,
        ///       given two quaternions with same components.
        static_assert((QUAT_A == QUAT_C) == true);



        /**************************************
         *         INEQUALITY TESTS           *
         **************************************/

        /// @test Verify that Quaternion anyNeq returns the correct boolean at compile time,
        ///       given two quaternions with different components.
        static_assert(QUAT_A.anyNeq(QUAT_B) == true);

        /// @test Verify that Quaternion anyNeq returns the correct boolean at compile time,
        ///       given two quaternions with same components.
        static_assert(QUAT_A.anyNeq(QUAT_C) == false);


        /// @test Verify that Quaternion anyNeq(static wrapper) returns the correct boolean at compile time,
        ///       given two quaternions with different components.
        static_assert(flcn::Quat<int>::anyNeq(QUAT_A, QUAT_B) == true);

        /// @test Verify that Quaternion anyNeq(static wrapper) returns the correct boolean at compile time,
        ///       given two quaternions with same components.
        static_assert(flcn::Quat<int>::anyNeq(QUAT_A, QUAT_C) == false);


        /// @test Verify that Quaternion neq returns the correct boolean mask at compile time.
        constexpr auto NEQ_QUAT_MASK = QUAT_A.neq(QUAT_B);
        static_assert(NEQ_QUAT_MASK.x() == true);
        static_assert(NEQ_QUAT_MASK.y() == false);
        static_assert(NEQ_QUAT_MASK.z() == true);
        static_assert(NEQ_QUAT_MASK.w() == true);

        /// @test Verify that Quaternion neq (static wrapper) returns the correct boolean mask at compile time.
        constexpr auto NEQ_QUAT_MASK_STATIC = flcn::Quat<int>::neq(QUAT_A, QUAT_B);
        static_assert(NEQ_QUAT_MASK_STATIC.x() == true);
        static_assert(NEQ_QUAT_MASK_STATIC.y() == false);
        static_assert(NEQ_QUAT_MASK_STATIC.z() == true);
        static_assert(NEQ_QUAT_MASK_STATIC.w() == true);


        /// @test Verify that Quaternion vecNeq returns the correct boolean at compile time,
        ///       given two quaternions with different vector parts.
        static_assert(QUAT_A.vecNeq(QUAT_B) == true);

        /// @test Verify that Quaternion vecNeq returns the correct boolean at compile time,
        ///       given two quaternions with same vector parts.
        static_assert(QUAT_A.vecNeq(QUAT_D) == false);


        /// @test Verify that Quaternion vecNeq(static wrapper) returns the correct boolean at compile time,
        ///       given two quaternions with different vector parts.
        static_assert(flcn::Quat<int>::vecNeq(QUAT_A, QUAT_B) == true);

        /// @test Verify that Quaternion vecNeq(static wrapper) returns the correct boolean at compile time,
        ///       given two quaternions with same vector parts.
        static_assert(flcn::Quat<int>::vecNeq(QUAT_A, QUAT_D) == false);


        /// @test Verify that Quaternion operator!= returns the correct boolean at compile time,
        ///       given two quaternions with different components.
        static_assert((QUAT_A != QUAT_B) == true);

        /// @test Verify that Quaternion operator!= returns the correct boolean at compile time,
        ///       given two quaternions with same components.
        static_assert((QUAT_A != QUAT_C) == false);


    } // namespace static_tests

} // namespace



/**************************************
 *                                    *
 *           EQUALITY TESTS           *
 *                                    *
 **************************************/

/**************************************
 *             ALL EQ                 *
 **************************************/

TYPED_TEST(QuaternionEqualityTests, AllEq_IdenticalQuaternionsReturnsTrue)
{ EXPECT_TRUE(this->_eqQuatA.allEq(this->_eqQuatB)); }


TYPED_TEST(QuaternionEqualityTests, AllEq_DifferentQuaternionsReturnsFalse)
{ EXPECT_FALSE(this->_eqQuatA.allEq(this->_dissimilarQuat)); }


TEST(QuaternionEqualityTests, AllEq_NanQuaternionsReturnsFalse)
{
    const flcn::Quat quatA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const flcn::Quat<double> quatB = { 1.0, -5.88874789, flcn::constants::INFINITY_D, NAN_F };

    EXPECT_FALSE(quatA.allEq(quatB));
}


TEST(QuaternionEqualityTests, AllEq_IdenticalInfiniteQuaternionsReturnsTrue)
{
    const flcn::Quat quatA = { INF, -INF, INF, -INF };
    const flcn::Quat quatB = { INF, -INF, INF, -INF };

    EXPECT_TRUE(quatA.allEq(quatB));
}


TEST(QuaternionEqualityTests, AllEq_DifferentInfiniteQuaternionsReturnsFalse)
{
    const flcn::Quat quatA = { INF, INF, INF, -INF };
    const flcn::Quat quatB = { INF, -INF, INF, INF };

    EXPECT_FALSE(quatA.allEq(quatB));
}


TYPED_TEST(QuaternionEqualityTests, AllEq_MixedType_IdenticalQuaternionsReturnsTrue)
{
    const flcn::Quat quatA(1, 2, 3, 4);
    const flcn::Quat quatB(1.0, 2.0, 3.0, 4.0);

    EXPECT_TRUE(quatA.allEq(quatB));
}


TYPED_TEST(QuaternionEqualityTests, StaticWrapper_AllEq_IdenticalQuaternionsReturnsTrue)
{ EXPECT_TRUE(flcn::Quat<TypeParam>::allEq(this->_eqQuatA, this->_eqQuatB)); }


TYPED_TEST(QuaternionEqualityTests, StaticWrapper_AllEq_DifferentQuaternionsReturnsFalse)
{ EXPECT_FALSE(flcn::Quat<TypeParam>::allEq(this->_eqQuatA, this->_dissimilarQuat)); }


TEST(QuaternionEqualityTests, StaticWrapper_AllEq_NanQuaternionsReturnsFalse)
{
    const flcn::Quat quatA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const flcn::Quat<double> quatB = { 1.0, -5.88874789, flcn::constants::INFINITY_D, NAN_F };

    EXPECT_FALSE(flcn::Quat<float>::allEq(quatA, quatB));
}


TEST(QuaternionEqualityTests, StaticWrapper_AllEq_IdenticalInfiniteQuaternionsReturnsTrue)
{
    const flcn::Quat quatA = { INF, -INF, INF, -INF };
    const flcn::Quat quatB = { INF, -INF, INF, -INF };

    EXPECT_TRUE(flcn::Quat<float>::allEq(quatA, quatB));
}


TEST(QuaternionEqualityTests, StaticWrapper_AllEq_DifferentInfiniteQuaternionsReturnsFalse)
{
    const flcn::Quat quatA = { INF, INF, INF, -INF };
    const flcn::Quat quatB = { INF, -INF, INF, INF };

    EXPECT_FALSE(flcn::Quat<float>::allEq(quatA, quatB));
}


TYPED_TEST(QuaternionEqualityTests, StaticWrapper_AllEq_MixedType_IdenticalQuaternionsReturnsTrue)
{
    const flcn::Quat quatA(1, 2, 3, 4);
    const flcn::Quat quatB(1.0, 2.0, 3.0, 4.0);

    EXPECT_TRUE(flcn::Quat<int>::allEq(quatA, quatB));
}



/**************************************
 *          EQUALITY MASK             *
 **************************************/

TYPED_TEST(QuaternionEqualityTests, Eq_ReturnsCorrectBooleanMask)
{
    const flcn::Quat<bool> mask = this->_eqQuatA.eq(this->_dissimilarQuat);
    EXPECT_QUAT_EQ(this->_equalityMask, mask);
}


TEST(QuaternionEqualityTests, Eq_MixedType_ReturnsCorrectBooleanMask)
{
    const flcn::Quat quatA        = { 1, 2, 3, 4 };
    const flcn::Quat quatB        = { 1.0, 4.0, 0.0, 4.0 };
    const flcn::Quat expectedMask = { true, false, false, true };

    const flcn::Quat<bool> mask = quatA.eq(quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}


TEST(QuaternionEqualityTests, Eq_NaNQuaternionsReturnsFalseBooleanMask)
{
    const flcn::Quat quatA        = { NAN_F, NAN_F, NAN_F, NAN_F };
    const flcn::Quat quatB        = { 1.0, -5.88874789, flcn::constants::INFINITY_D, flcn::constants::NaN_D };
    const flcn::Quat expectedMask = { false, false, false, false };

    const flcn::Quat mask = quatA.eq(quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}


TEST(QuaternionEqualityTests, Eq_InfiniteQuaternionsReturnsCorrectBooleanMask)
{
    const flcn::Quat quatA         = { INF, -INF, INF, -INF };
    const flcn::Quat<double> quatB = { flcn::constants::INFINITY_D, flcn::constants::INFINITY_D, 10e11, 10e11 };
    const flcn::Quat expectedMask  = { true, false, false, false };

    const flcn::Quat mask = quatA.eq(quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}


TYPED_TEST(QuaternionEqualityTests, StaticWrapper_Eq_ReturnsCorrectBooleanMask)
{
    const flcn::Quat<bool> mask = flcn::Quat<TypeParam>::eq(this->_eqQuatA, this->_dissimilarQuat);
    EXPECT_QUAT_EQ(this->_equalityMask, mask);
}


TEST(QuaternionEqualityTests, StaticWrapper_Eq_MixedType_ReturnsCorrectBooleanMask)
{
    const flcn::Quat quatA        = { 1, 2, 3, 4 };
    const flcn::Quat quatB        = { 1.0, 4.0, 0.0, 4.0 };
    const flcn::Quat expectedMask = { true, false, false, true };

    const flcn::Quat<bool> mask = flcn::Quat<int>::eq(quatA, quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}


TEST(QuaternionEqualityTests, StaticWrapper_Eq_NaNQuaternionsReturnsFalseBooleanMask)
{
    const flcn::Quat quatA        = { NAN_F, NAN_F, NAN_F, NAN_F };
    const flcn::Quat quatB        = { 1.0, -5.88874789, flcn::constants::INFINITY_D, flcn::constants::NaN_D };
    const flcn::Quat expectedMask = { false, false, false, false };

    const flcn::Quat<bool> mask = flcn::Quat<float>::eq(quatA, quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}


TEST(QuaternionEqualityTests, StaticWrapper_Eq_InfiniteQuaternionsReturnsCorrectBooleanMask)
{
    const flcn::Quat quatA         = { INF, -INF, INF, -INF };
    const flcn::Quat<double> quatB = { flcn::constants::INFINITY_D, flcn::constants::INFINITY_D, 10e11, 10e11 };
    const flcn::Quat expectedMask  = { true, false, false, false };

    const flcn::Quat<bool> mask = flcn::Quat<float>::eq(quatA, quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}



/**************************************
 *             VEC EQ                 *
 **************************************/

TYPED_TEST(QuaternionEqualityTests, VeqEq_QuaternionsWithIdenticalVectorPartReturnsTrue)
{ EXPECT_TRUE(this->_eqVecQuatA.vecEq(this->_eqVecQuatB)); }


TYPED_TEST(QuaternionEqualityTests, VeqEq_QuaternionsWithDifferentVectorPartReturnsFalse)
{ EXPECT_FALSE(this->_eqVecQuatA.vecEq(this->_dissimilarQuat)); }


TEST(QuaternionEqualityTests, VeqEq_NanQuaternionsReturnsFalse)
{
    const flcn::Quat quatA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const flcn::Quat<double> quatB = { 1.0, -5.88874789, flcn::constants::INFINITY_D, NAN_F };

    EXPECT_FALSE(quatA.vecEq(quatB));
}


TEST(QuaternionEqualityTests, VeqEq_IdenticalInfiniteQuaternionsReturnsTrue)
{
    const flcn::Quat quatA = { INF, -INF, INF, 4.0f };
    const flcn::Quat quatB = { INF, -INF, INF, 8.0f };

    EXPECT_TRUE(quatA.vecEq(quatB));
}


TEST(QuaternionEqualityTests, VeqEq_DifferentInfiniteQuaternionsReturnsFalse)
{
    const flcn::Quat quatA = { INF, INF, INF, -INF };
    const flcn::Quat quatB = { INF, -INF, INF, -INF };

    EXPECT_FALSE(quatA.vecEq(quatB));
}


TYPED_TEST(QuaternionEqualityTests, VeqEq_MixedType_QuaternionsWithIdenticalVectorPartReturnsTrue)
{
    const flcn::Quat quatA(1, 2, 3, 4);
    const flcn::Quat quatB(1.0, 2.0, 3.0, 4.0);

    EXPECT_TRUE(quatA.allEq(quatB));
}

TYPED_TEST(QuaternionEqualityTests, StaticWrapper_VeqEq_QuaternionsWithIdenticalVectorPartReturnsTrue)
{ EXPECT_TRUE(flcn::Quat<TypeParam>::vecEq(this->_eqVecQuatA, this->_eqVecQuatB)); }


TYPED_TEST(QuaternionEqualityTests, StaticWrapper_VeqEq_QuaternionsWithDifferentVectorPartReturnsFalse)
{ EXPECT_FALSE(flcn::Quat<TypeParam>::vecEq(this->_eqVecQuatA, this->_dissimilarQuat)); }


TEST(QuaternionEqualityTests, StaticWrapper_VeqEq_NanQuaternionsReturnsFalse)
{
    const flcn::Quat quatA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const flcn::Quat<double> quatB = { 1.0, -5.88874789, flcn::constants::INFINITY_D, NAN_F };

    EXPECT_FALSE(flcn::Quat<float>::vecEq(quatA, quatB));
}


TEST(QuaternionEqualityTests, StaticWrapper_VeqEq_IdenticalInfiniteQuaternionsReturnsTrue)
{
    const flcn::Quat quatA = { INF, -INF, INF, 4.0f };
    const flcn::Quat quatB = { INF, -INF, INF, 8.0f };

    EXPECT_TRUE(flcn::Quat<float>::vecEq(quatA, quatB));
}


TEST(QuaternionEqualityTests, StaticWrapper_VeqEq_DifferentInfiniteQuaternionsReturnsFalse)
{
    const flcn::Quat quatA = { INF, INF, INF, -INF };
    const flcn::Quat quatB = { INF, -INF, INF, -INF };

    EXPECT_FALSE(flcn::Quat<float>::vecEq(quatA, quatB));
}


TYPED_TEST(QuaternionEqualityTests, StaticWrapper_VeqEq_MixedType_QuaternionsWithIdenticalVectorPartReturnsTrue)
{
    const flcn::Quat quatA(1, 2, 3, 4);
    const flcn::Quat quatB(1.0, 2.0, 3.0, 4.0);

    EXPECT_TRUE(flcn::Quat<int>::vecEq(quatA, quatB));
}



/**************************************
 *         EQUALITY OPERATOR          *
 **************************************/

TYPED_TEST(QuaternionEqualityTests, EqualityOperator_IdenticalQuaternionsReturnsTrue)
{ EXPECT_TRUE(this->_eqQuatA == this->_eqQuatB); }


TYPED_TEST(QuaternionEqualityTests, EqualityOperator_DifferentQuaternionsReturnsFalse)
{ EXPECT_FALSE(this->_eqQuatA == this->_dissimilarQuat); }


TEST(QuaternionEqualityTests, EqualityOperator_NanQuaternionsReturnsFalse)
{
    const flcn::Quat quatA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const flcn::Quat<double> quatB = { 1.0, -5.88874789, flcn::constants::INFINITY_D, NAN_F };

    EXPECT_FALSE(quatA == quatB);
}


TEST(QuaternionEqualityTests, EqualityOperator_IdenticalInfiniteQuaternionsReturnsTrue)
{
    const flcn::Quat quatA = { INF, -INF, INF, -INF };
    const flcn::Quat quatB = { INF, -INF, INF, -INF };

    EXPECT_TRUE(quatA == quatB);
}


TEST(QuaternionEqualityTests, EqualityOperator_DifferentInfiniteQuaternionsReturnsFalse)
{
    const flcn::Quat quatA = { INF, INF, INF, -INF };
    const flcn::Quat quatB = { INF, -INF, INF, INF };

    EXPECT_FALSE(quatA == quatB);
}


TYPED_TEST(QuaternionEqualityTests, EqualityOperator_MixedType_IdenticalQuaternionsReturnsTrue)
{
    const flcn::Quat quatA(1, 2, 3, 4);
    const flcn::Quat quatB(1.0, 2.0, 3.0, 4.0);

    EXPECT_TRUE(quatA == quatB);
}




/**************************************
 *                                    *
 *          INEQUALITY TESTS          *
 *                                    *
 **************************************/

/**************************************
 *             ANY NEQ                *
 **************************************/

TYPED_TEST(QuaternionEqualityTests, AnyNeq_IdenticalQuaternionsReturnsFalse)
{ EXPECT_FALSE(this->_eqQuatA.anyNeq(this->_eqQuatB)); }


TYPED_TEST(QuaternionEqualityTests, AnyNeq__DifferentQuaternionsReturnsTrue)
{ EXPECT_TRUE(this->_eqQuatA.anyNeq(this->_dissimilarQuat)); }


TEST(QuaternionEqualityTests, AnyNeq_NanQuaternionsReturnsTrue)
{
    const flcn::Quat quatA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const flcn::Quat<double> quatB = { 1.0, -5.88874789, flcn::constants::INFINITY_D, NAN_F };

    EXPECT_TRUE(quatA.anyNeq(quatB));
}


TEST(QuaternionEqualityTests, AnyNeq_IdenticalInfiniteQuaternionsReturnsFalse)
{
    const flcn::Quat quatA = { INF, -INF, INF, -INF };
    const flcn::Quat quatB = { INF, -INF, INF, -INF };

    EXPECT_FALSE(quatA.anyNeq(quatB));
}


TEST(QuaternionEqualityTests, AnyNeq_DifferentInfiniteQuaternionsReturnsTrue)
{
    const flcn::Quat quatA = { INF, INF, INF, -INF };
    const flcn::Quat quatB = { INF, -INF, INF, INF };

    EXPECT_TRUE(quatA.anyNeq(quatB));
}


TYPED_TEST(QuaternionEqualityTests, AnyNeq_MixedType_IdenticalQuaternionsReturnsFalse)
{
    const flcn::Quat quatA(1, 2, 3, 4);
    const flcn::Quat quatB(1.0, 2.0, 3.0, 4.0);

    EXPECT_FALSE(quatA.anyNeq(quatB));
}


TYPED_TEST(QuaternionEqualityTests, StaticWrapper_AnyNeq_IdenticalQuaternionsReturnsFalse)
{ EXPECT_FALSE(flcn::Quat<TypeParam>::anyNeq(this->_eqQuatA, this->_eqQuatB)); }


TYPED_TEST(QuaternionEqualityTests, StaticWrapper_AnyNeq_DifferentQuaternionsReturnsTrue)
{ EXPECT_TRUE(flcn::Quat<TypeParam>::anyNeq(this->_eqQuatA, this->_dissimilarQuat)); }


TEST(QuaternionEqualityTests, StaticWrapper_AnyNeq_NanQuaternionsReturnsTrue)
{
    const flcn::Quat quatA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const flcn::Quat<double> quatB = { 1.0, -5.88874789, flcn::constants::INFINITY_D, NAN_F };

    EXPECT_TRUE(flcn::Quat<float>::anyNeq(quatA, quatB));
}


TEST(QuaternionEqualityTests, StaticWrapper_AnyNeq_IdenticalInfiniteQuaternionsReturnsFalse)
{
    const flcn::Quat quatA = { INF, -INF, INF, -INF };
    const flcn::Quat quatB = { INF, -INF, INF, -INF };

    EXPECT_FALSE(flcn::Quat<float>::anyNeq(quatA, quatB));
}


TEST(QuaternionEqualityTests, StaticWrapper_AnyNeq_DifferentInfiniteQuaternionsReturnsTrue)
{
    const flcn::Quat quatA = { INF, INF, INF, -INF };
    const flcn::Quat quatB = { INF, -INF, INF, INF };

    EXPECT_TRUE(flcn::Quat<float>::anyNeq(quatA, quatB));
}


TYPED_TEST(QuaternionEqualityTests, StaticWrapper_AnyNeq_MixedType_IdenticalQuaternionsReturnsFalse)
{
    const flcn::Quat quatA(1, 2, 3, 4);
    const flcn::Quat quatB(1.0, 2.0, 3.0, 4.0);

    EXPECT_FALSE(flcn::Quat<int>::anyNeq(quatA, quatB));
}


/**************************************
 *         INEQUALITY MASK            *
 **************************************/

TYPED_TEST(QuaternionEqualityTests, Neq_ReturnsCorrectBooleanMask)
{
    const flcn::Quat<bool> mask = this->_eqQuatA.neq(this->_dissimilarQuat);
    EXPECT_QUAT_EQ(this->_inequalityMask, mask);
}


TEST(QuaternionEqualityTests, Neq_MixedType_ReturnsCorrectBooleanMask)
{
    const flcn::Quat quatA        = { 1, 2, 3, 4 };
    const flcn::Quat quatB        = { 1.0, 4.0, 0.0, 4.0 };
    const flcn::Quat expectedMask = { false, true, true, false };

    const flcn::Quat<bool> mask = quatA.neq(quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}


TEST(QuaternionEqualityTests, Neq_NaNQuaternionsReturnsFalseBooleanMask)
{
    const flcn::Quat quatA        = { NAN_F, NAN_F, NAN_F, NAN_F };
    const flcn::Quat quatB        = { 1.0, -5.88874789, flcn::constants::INFINITY_D, flcn::constants::NaN_D };
    const flcn::Quat expectedMask = { true, true, true, true };

    const flcn::Quat mask = quatA.neq(quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}


TEST(QuaternionEqualityTests, Neq_InfiniteQuaternionsReturnsCorrectBooleanMask)
{
    const flcn::Quat quatA         = { INF, -INF, INF, -INF };
    const flcn::Quat<double> quatB = { flcn::constants::INFINITY_D, flcn::constants::INFINITY_D, 10e11, 10e11 };
    const flcn::Quat expectedMask  = { false, true, true, true };

    const flcn::Quat mask = quatA.neq(quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}


TYPED_TEST(QuaternionEqualityTests, StaticWrapper_Neq_ReturnsCorrectBooleanMask)
{
    const flcn::Quat<bool> mask = flcn::Quat<TypeParam>::neq(this->_eqQuatA, this->_dissimilarQuat);
    EXPECT_QUAT_EQ(this->_inequalityMask, mask);
}


TEST(QuaternionEqualityTests, StaticWrapper_Neq_MixedType_ReturnsCorrectBooleanMask)
{
    const flcn::Quat quatA        = { 1, 2, 3, 4 };
    const flcn::Quat quatB        = { 1.0, 4.0, 0.0, 4.0 };
    const flcn::Quat expectedMask = { false, true, true, false };

    const flcn::Quat<bool> mask = flcn::Quat<int>::neq(quatA, quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}


TEST(QuaternionEqualityTests, StaticWrapper_Neq_NaNQuaternionsReturnsFalseBooleanMask)
{
    const flcn::Quat quatA        = { NAN_F, NAN_F, NAN_F, NAN_F };
    const flcn::Quat quatB        = { 1.0, -5.88874789, flcn::constants::INFINITY_D, flcn::constants::NaN_D };
    const flcn::Quat expectedMask = { true, true, true, true };

    const flcn::Quat<bool> mask = flcn::Quat<float>::neq(quatA, quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}


TEST(QuaternionEqualityTests, StaticWrapper_Neq_InfiniteQuaternionsReturnsCorrectBooleanMask)
{
    const flcn::Quat quatA         = { INF, -INF, INF, -INF };
    const flcn::Quat<double> quatB = { flcn::constants::INFINITY_D, flcn::constants::INFINITY_D, 10e11, 10e11 };
    const flcn::Quat expectedMask  = { false, true, true, true };

    const flcn::Quat<bool> mask = flcn::Quat<float>::neq(quatA, quatB);

    EXPECT_QUAT_EQ(expectedMask, mask);
}



/**************************************
 *             VEC NEQ                *
 **************************************/

TYPED_TEST(QuaternionEqualityTests, VeqNeq_QuaternionsWithIdenticalVectorPartReturnsFalse)
{ EXPECT_FALSE(this->_eqVecQuatA.vecNeq(this->_eqVecQuatB)); }


TYPED_TEST(QuaternionEqualityTests, VeqNeq_QuaternionsWithDifferentVectorPartReturnsTrue)
{ EXPECT_TRUE(this->_eqVecQuatA.vecNeq(this->_dissimilarQuat)); }


TEST(QuaternionEqualityTests, VeqNeq_NanQuaternionsReturnsTrue)
{
    const flcn::Quat quatA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const flcn::Quat<double> quatB = { 1.0, -5.88874789, flcn::constants::INFINITY_D, NAN_F };

    EXPECT_TRUE(quatA.vecNeq(quatB));
}


TEST(QuaternionEqualityTests, VeqNeq_IdenticalInfiniteQuaternionsReturnsFalse)
{
    const flcn::Quat quatA = { INF, -INF, INF, 4.0f };
    const flcn::Quat quatB = { INF, -INF, INF, 8.0f };

    EXPECT_FALSE(quatA.vecNeq(quatB));
}


TEST(QuaternionEqualityTests, VeqNeq_DifferentInfiniteQuaternionsReturnsTrue)
{
    const flcn::Quat quatA = { INF, INF, INF, -INF };
    const flcn::Quat quatB = { INF, -INF, INF, -INF };

    EXPECT_TRUE(quatA.vecNeq(quatB));
}


TYPED_TEST(QuaternionEqualityTests, VeqNeq_MixedType_QuaternionsWithIdenticalVectorPartReturnsFalse)
{
    const flcn::Quat quatA(1, 2, 3, 4);
    const flcn::Quat quatB(1.0, 2.0, 3.0, 4.0);

    EXPECT_FALSE(quatA.vecNeq(quatB));
}


TYPED_TEST(QuaternionEqualityTests, StaticWrapper_VeqNeq_QuaternionsWithIdenticalVectorPartReturnsFalse)
{ EXPECT_FALSE(flcn::Quat<TypeParam>::vecNeq(this->_eqVecQuatA, this->_eqVecQuatB)); }


TYPED_TEST(QuaternionEqualityTests, StaticWrapper_VeqNeq_QuaternionsWithDifferentVectorPartReturnsTrue)
{ EXPECT_TRUE(flcn::Quat<TypeParam>::vecNeq(this->_eqVecQuatA, this->_dissimilarQuat)); }


TEST(QuaternionEqualityTests, StaticWrapper_VeqNeq_NanQuaternionsReturnsTrue)
{
    const flcn::Quat quatA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const flcn::Quat<double> quatB = { 1.0, -5.88874789, flcn::constants::INFINITY_D, NAN_F };

    EXPECT_TRUE(flcn::Quat<float>::vecNeq(quatA, quatB));
}


TEST(QuaternionEqualityTests, StaticWrapper_VeqNeq_IdenticalInfiniteQuaternionsReturnsFalse)
{
    const flcn::Quat quatA = { INF, -INF, INF, 4.0f };
    const flcn::Quat quatB = { INF, -INF, INF, 8.0f };

    EXPECT_FALSE(flcn::Quat<float>::vecNeq(quatA, quatB));
}


TEST(QuaternionEqualityTests, StaticWrapper_VeqNeq_DifferentInfiniteQuaternionsReturnsTrue)
{
    const flcn::Quat quatA = { INF, INF, INF, -INF };
    const flcn::Quat quatB = { INF, -INF, INF, -INF };

    EXPECT_TRUE(flcn::Quat<float>::vecNeq(quatA, quatB));
}


TYPED_TEST(QuaternionEqualityTests, StaticWrapper_VeqNeq_MixedType_QuaternionsWithIdenticalVectorPartReturnsFalse)
{
    const flcn::Quat quatA(1, 2, 3, 4);
    const flcn::Quat quatB(1.0, 2.0, 3.0, 4.0);

    EXPECT_FALSE(flcn::Quat<int>::vecNeq(quatA, quatB));
}



/**************************************
 *        INEQUALITY OPERATOR         *
 **************************************/

TYPED_TEST(QuaternionEqualityTests, InequalityOperator_IdenticalQuaternionsReturnsFalse)
{ EXPECT_FALSE(this->_eqQuatA != this->_eqQuatB); }


TYPED_TEST(QuaternionEqualityTests, InequalityOperator_DifferentQuaternionsReturnsTrue)
{ EXPECT_TRUE(this->_eqQuatA != this->_dissimilarQuat); }


TEST(QuaternionEqualityTests, InequalityOperator_NanQuaternionsReturnsTrue)
{
    const flcn::Quat quatA         = { NAN_F, NAN_F, NAN_F, NAN_F };
    const flcn::Quat<double> quatB = { 1.0, -5.88874789, flcn::constants::INFINITY_D, NAN_F };

    EXPECT_TRUE(quatA != quatB);
}


TEST(QuaternionEqualityTests, InequalityOperator_IdenticalInfiniteQuaternionsReturnsFalse)
{
    const flcn::Quat quatA = { INF, -INF, INF, -INF };
    const flcn::Quat quatB = { INF, -INF, INF, -INF };

    EXPECT_FALSE(quatA != quatB);
}


TEST(QuaternionEqualityTests, InequalityOperator_DifferentInfiniteQuaternionsReturnsTrue)
{
    const flcn::Quat quatA = { INF, INF, INF, -INF };
    const flcn::Quat quatB = { INF, -INF, INF, INF };

    EXPECT_TRUE(quatA != quatB);
}


TYPED_TEST(QuaternionEqualityTests, InequalityOperator_MixedType_IdenticalQuaternionsReturnsFalse)
{
    const flcn::Quat quatA(1, 2, 3, 4);
    const flcn::Quat quatB(1.0, 2.0, 3.0, 4.0);

    EXPECT_FALSE(quatA != quatB);
}

/** @} */
