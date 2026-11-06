/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref flcn::Mat2 equality operator (==, !=) and their functional counterpart's
 *        (eq, neq, allEq, anyNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2TestSetup.h"

#include <falcon/math/common/Constants.h>


/**
 * @addtogroup T_FALCON_Mat2x2_Equality
 * @{
 */

namespace
{

    constexpr auto NAN_F = flcn::constants::NaN;
    constexpr auto INF   = flcn::constants::INFINITY_F;


    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2 Equality.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2EqualityTests: public testing::Test
    {
    protected:
        flcn::Mat2<T> _eqMatA;
        flcn::Mat2<T> _eqMatB;
        flcn::Mat2<T> _unEqualMat;


        void SetUp() override
        {
            _eqMatA        = { { T(1.1234568789), T(2.123458319) }, { T(3.1234568789), T(4.123458319) } };
            _eqMatB        = { { T(1.1234568789), T(2.123458319) }, { T(3.1234568789), T(4.123458319) } };
            _unEqualMat = { { T(1.1234568789), T(4.5238852912) }, { T(3.1234568789), T(6.123458319) } };
        }
    };
    TYPED_TEST_SUITE(Mat2EqualityTests, SupportedArithmeticTypes);


    struct Mat2ElementParam
    {
        flcn::Mat2<int> first, second;
        bool expected;
    };

    /// @brief Test fixture for @ref flcn::Mat2 Equality on a per-element basis.
    class Mat2PerElementEqualityTests: public testing::TestWithParam<Mat2ElementParam>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat2ElementwiseEquality, Mat2PerElementEqualityTests,
        ::testing::Values(Mat2ElementParam{ .first = { 1, 2, 3, 4 }, .second = { 1, 2, 3, 4 }, .expected = true },
                          Mat2ElementParam{ .first = { 1, 2, 3, 4 }, .second = { 2, 2, 3, 4 }, .expected = false },
                          Mat2ElementParam{ .first = { 1, 2, 3, 4 }, .second = { 1, 1, 3, 4 }, .expected = false },
                          Mat2ElementParam{ .first = { 1, 2, 3, 4 }, .second = { 1, 2, 1, 4 }, .expected = false },
                          Mat2ElementParam{ .first = { 1, 2, 3, 4 }, .second = { 1, 2, 3, 1 }, .expected = false }));



    /// @brief Test fixture for @ref flcn::Mat2 Inequality on a per-element basis.
    class Mat2PerElementInequalityTests: public testing::TestWithParam<Mat2ElementParam>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat2ElementwiseInequality, Mat2PerElementInequalityTests,
        ::testing::Values(Mat2ElementParam{ .first = { 1, 2, 3, 4 }, .second = { 1, 2, 3, 4 }, .expected = false },
                          Mat2ElementParam{ .first = { 1, 2, 3, 4 }, .second = { 2, 2, 3, 4 }, .expected = true },
                          Mat2ElementParam{ .first = { 1, 2, 3, 4 }, .second = { 1, 1, 3, 4 }, .expected = true },
                          Mat2ElementParam{ .first = { 1, 2, 3, 4 }, .second = { 1, 2, 1, 4 }, .expected = true },
                          Mat2ElementParam{ .first = { 1, 2, 3, 4 }, .second = { 1, 2, 3, 1 }, .expected = true }));



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat2 MAT1(1, 2, 3, 4);
        constexpr flcn::Mat2 MAT2(1, 2, 3, 4);
        constexpr flcn::Mat2 MAT3(4, 2, 2, 4);
        constexpr flcn::Mat2 INF_MAT1(-flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                     -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
        constexpr flcn::Mat2 INF_MAT2(-flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                     -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);


        /** @test Verify that Mat2 allEq returns true for equal matrices at compile time. */
        static_assert(MAT1.allEq(MAT2) == true);

        /** @test Verify that Mat2 allEq returns false for unequal matrices at compile time. */
        static_assert(MAT1.allEq(MAT3) == false);

        /** @test Verify that Mat2 allEq returns true for equal infinite matrices at compile time. */
        static_assert(INF_MAT1.allEq(INF_MAT2) == true);



        /** @test Verify that Mat2 allEq (static wrapper) returns true for equal matrices at compile time. */
        static_assert(flcn::Mat2<int>::allEq(MAT1, MAT2) == true);

        /** @test Verify that Mat2 allEq (static wrapper) returns false for unequal matrices at compile time. */
        static_assert(flcn::Mat2<int>::allEq(MAT1, MAT3) == false);

        /** @test Verify that Mat2 allEq (static wrapper) returns true for equal infinite matrices at compile time. */
        static_assert(flcn::Mat2<float>::allEq(INF_MAT1, INF_MAT2) == true);



        /** @test Verify that Mat2 anyNeq returns false for equal matrices at compile time. */
        static_assert(MAT1.anyNeq(MAT2) == false);

        /** @test Verify that Mat2 anyNeq returns true for unequal matrices at compile time. */
        static_assert(MAT1.anyNeq(MAT3) == true);

        /** @test Verify that Mat2 anyNeq returns false for equal infinite matrices at compile time. */
        static_assert(INF_MAT1.anyNeq(INF_MAT2) == false);



        /** @test Verify that Mat2 anyNeq (static wrapper) returns false for equal matrices at compile time. */
        static_assert(flcn::Mat2<int>::anyNeq(MAT1, MAT2) == false);

        /** @test Verify that Mat2 anyNeq (static wrapper) returns true for unequal matrices at compile time. */
        static_assert(flcn::Mat2<int>::anyNeq(MAT1, MAT3) == true);

        /** @test Verify that Mat2 anyNeq (static wrapper) returns false for equal infinite matrices at compile time. */
        static_assert(flcn::Mat2<float>::anyNeq(INF_MAT1, INF_MAT2) == false);

    } // namespace static_tests

} // namespace



/**************************************
 *             ALL EQ                 *
 **************************************/

TYPED_TEST(Mat2EqualityTests, AllEq_IdenticalMatricesReturnTrue)
{
    const bool equality = this->_eqMatA.allEq(this->_eqMatB);
    EXPECT_TRUE(equality);
}


TYPED_TEST(Mat2EqualityTests, AllEq_DifferentMatricesReturnFalse)
{
    const bool equality = this->_eqMatA.allEq(this->_unEqualMat);
    EXPECT_FALSE(equality);
}


TEST(Mat2EqualityTests, AllEq_NanMatrixReturnsFalse)
{
    const flcn::Mat2 matA(NAN_F, NAN_F, NAN_F, NAN_F);
    const flcn::Mat2 matB(1.0f, -5.88874789f, 2.0f, 0.888749f);

    const bool equality = matA.allEq(matB);
    EXPECT_FALSE(equality);
}


TEST(Mat2EqualityTests, AllEq_IdenticalInfiniteMatricesReturnTrue)
{
    const flcn::Mat2 matA(INF, -INF, INF, -INF);
    const flcn::Mat2 matB(INF, -INF, INF, -INF);

    const bool equality = matA.allEq(matB);
    EXPECT_TRUE(equality);
}


TEST(Mat2EqualityTests, AllEq_DifferentInfiniteMatricesReturnFalse)
{
    const flcn::Mat2 matA(INF, -INF, INF, -INF);
    const flcn::Mat2 matB(-INF, -INF, INF, INF);

    const bool equality = matA.allEq(matB);
    EXPECT_FALSE(equality);
}


TYPED_TEST(Mat2EqualityTests, AllEq_MixedType_IdenticalMatricesReturnTrue)
{
    const flcn::Mat2 matA(1, 2);
    const flcn::Mat2 matB(1.0, 2.0);

    const bool equality = matA.allEq(matB);
    EXPECT_TRUE(equality);
}


TYPED_TEST(Mat2EqualityTests, AllEq_MixedType_DifferentMatricesReturnFalse)
{
    const flcn::Mat2 matA(5, 6);
    const flcn::Mat2 matB(1.0, 2.0);

    const bool equality = matA.allEq(matB);
    EXPECT_FALSE(equality);
}

TEST_P(Mat2PerElementEqualityTests, AllEq_VerifiesElementwiseEquality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat.allEq(secondMat));
}


TYPED_TEST(Mat2EqualityTests, StaticWrapper_AllEq_IdenticalMatricesReturnTrue)
{
    const bool equality = flcn::Mat2<TypeParam>::allEq(this->_eqMatA, this->_eqMatB);
    EXPECT_TRUE(equality);
}


TYPED_TEST(Mat2EqualityTests, StaticWrapper_AllEq_DifferentMatricesReturnFalse)
{
    const bool equality = flcn::Mat2<TypeParam>::allEq(this->_eqMatA, this->_unEqualMat);
    EXPECT_FALSE(equality);
}


TEST_P(Mat2PerElementEqualityTests, StaticWrapper_AllEq_VerifiesElementwiseEquality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Mat2<int>::allEq(firstMat, secondMat));
}



/**************************************
 *       DOUBLE-EQUALS OPERATOR       *
 **************************************/

TYPED_TEST(Mat2EqualityTests, DoubleEqualsOperator_IdenticalMatricesReturnTrue)
{
    const bool equality = this->_eqMatA == this->_eqMatB;
    EXPECT_TRUE(equality);
}


TYPED_TEST(Mat2EqualityTests, DoubleEqualsOperator_DifferentMatricesReturnFalse)
{
    const bool equality = this->_eqMatA == this->_unEqualMat;
    EXPECT_FALSE(equality);
}


TEST_P(Mat2PerElementEqualityTests, DoubleEqualsOperator_AllEq_VerifiesElementwiseEquality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat == secondMat);
}


TEST(Mat2EqualityTests, DoubleEqualsOperator_IdenticalBooleanMatricesReturnTrue)
{
    const flcn::Mat2 matA(true, false, true, false);
    const flcn::Mat2 matB(true, false, true, false);

    const bool equality = matA == matB;
    EXPECT_TRUE(equality);
}


TEST(Mat2EqualityTests, DoubleEqualsOperator_DifferentBooleanMatricesReturnFalse)
{
    const flcn::Mat2 matA(true, false, false, true);
    const flcn::Mat2 matB(true, true, false, true);

    const bool equality = matA == matB;

    EXPECT_FALSE(equality);
}


TEST_P(Mat2PerElementEqualityTests, DoubleEqualsOperator_VerifiesElementwiseEquality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat == secondMat);
}



/**************************************
 *             ANY NEQ                *
 **************************************/

TYPED_TEST(Mat2EqualityTests, AnyNeq_IdenticalMatricesReturnFalse)
{
    const bool inequality = this->_eqMatA.anyNeq(this->_eqMatB);
    EXPECT_FALSE(inequality);
}


TYPED_TEST(Mat2EqualityTests, AnyNeq_DifferentMatricesReturnTrue)
{
    const bool inequality = this->_eqMatA.anyNeq(this->_unEqualMat);
    EXPECT_TRUE(inequality);
}


TEST(Mat2EqualityTests, AnyNeq_NanMatrixReturnsTrue)
{
    const flcn::Mat2 matA(NAN_F, NAN_F, NAN_F, NAN_F);
    const flcn::Mat2 matB(1.0f, -5.88874789f, INF, -INF);

    const bool inequality = matA.anyNeq(matB);

    EXPECT_TRUE(inequality);
}


TEST(Mat2EqualityTests, AnyNeq_IdenticalInfiniteMatricesReturnFalse)
{
    const flcn::Mat2 matA(INF, -INF, INF, -INF);
    const flcn::Mat2 matB(INF, -INF, INF, -INF);

    const bool inequality = matA.anyNeq(matB);
    EXPECT_FALSE(inequality);
}


TEST(Mat2EqualityTests, AnyNeq_DifferentInfiniteMatricesReturnTrue)
{
    const flcn::Mat2 matA(-INF, INF, INF, -INF);
    const flcn::Mat2 matB(INF, INF, -INF, -INF);

    const bool inequality = matA.anyNeq(matB);
    EXPECT_TRUE(inequality);
}


TYPED_TEST(Mat2EqualityTests, AnyNeq_MixedType_IdenticalMatricesReturnFalse)
{
    const flcn::Mat2 matA(1, 2, 3, 4);
    const flcn::Mat2 matB(1.0, 2.0, 3.0, 4.0);

    const bool inequality = matA.anyNeq(matB);
    EXPECT_FALSE(inequality);
}


TYPED_TEST(Mat2EqualityTests, AnyNeq_MixedType_DifferentMatricesReturnTrue)
{
    const flcn::Mat2 matA(5, 6, 7, 8);
    const flcn::Mat2 matB(1.0, 2.0, 7.0, 8.0);

    const bool inequality = matA.anyNeq(matB);
    EXPECT_TRUE(inequality);
}


TEST_P(Mat2PerElementInequalityTests, AnyNeq_VerifiesElementwiseInequality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat.anyNeq(secondMat));
}


TYPED_TEST(Mat2EqualityTests, StaticWrapper_AnyNeq_IdenticalMatricesReturnFalse)
{
    const bool inequality = flcn::Mat2<TypeParam>::anyNeq(this->_eqMatA, this->_eqMatB);
    EXPECT_FALSE(inequality);
}


TYPED_TEST(Mat2EqualityTests, StaticWrapper_AnyNeq_DifferentMatricesReturnTrue)
{
    const bool inequality = flcn::Mat2<TypeParam>::anyNeq(this->_eqMatA, this->_unEqualMat);
    EXPECT_TRUE(inequality);
}


TEST_P(Mat2PerElementInequalityTests, StaticWrapper_AnyNeq_VerifiesElementwiseInequality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Mat2<int>::anyNeq(firstMat, secondMat));
}



/**************************************
 *            NOT EQUALS              *
 **************************************/

TYPED_TEST(Mat2EqualityTests, NotEqualsOperator_IdenticalMatricesReturnFalse)
{
    const bool inequality = this->_eqMatA != this->_eqMatB;
    EXPECT_FALSE(inequality);
}


TYPED_TEST(Mat2EqualityTests, NotEqualsOperator_DifferentMatricesReturnTrue)
{
    const bool inequality = this->_eqMatA != this->_unEqualMat;

    EXPECT_TRUE(inequality);
}


TEST(Mat2EqualityTests, NotEqualsOperator_IdenticalBooleanMatricesReturnFalse)
{
    const flcn::Mat2 matA(true, false);
    const flcn::Mat2 matB(true, false);

    const bool inequality = matA != matB;

    EXPECT_FALSE(inequality);
}


TEST(Mat2EqualityTests, NotEqualsOperator_DifferentBooleanMatricesReturnTrue)
{
    const flcn::Mat2 matA(true, false, true, false);
    const flcn::Mat2 matB(true, true, false, true);

    const bool inequality = matA != matB;

    EXPECT_TRUE(inequality);
}


TEST_P(Mat2PerElementInequalityTests, NotEqualsOperator_VerifiesElementwiseInequality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat != secondMat);
}

/** @} */
