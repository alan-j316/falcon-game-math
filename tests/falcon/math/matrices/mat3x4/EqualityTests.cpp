/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 20, 2026
 *
 * @brief Verify flcn::Mat3x4 equality operator (==, !=) and their functional counterpart's
 *        (eq, neq, allEq, anyNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3x4TestSetup.h"

#include <falcon/math/common/Constants.h>


/**
 * @addtogroup T_FALCON_Mat3x4_Equality
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
     * @brief Test fixture for @ref flcn::Mat3x4 Equality.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat3x4EqualityTests: public testing::Test
    {
    protected:
        flcn::Mat3x4<T> _eqMatA;
        flcn::Mat3x4<T> _eqMatB;
        flcn::Mat3x4<T> _unEqualMat;


        void SetUp() override
        {
            _eqMatA     = { { T(1.1234568789), T(2.123458319), T(1.23942) },
                            { T(3.1234568789), T(4.123458319), T(5.2192381) },
                            { T(1.234891293), T(5.13289424912), T(3.29132048) },
                            { T(5.12983412), T(12.3912830), T(8.18320401) } };
            _eqMatB     = { { T(1.1234568789), T(2.123458319), T(1.23942) },
                            { T(3.1234568789), T(4.123458319), T(5.2192381) },
                            { T(1.234891293), T(5.13289424912), T(3.29132048) },
                            { T(5.12983412), T(12.3912830), T(8.18320401) } };
            _unEqualMat = {
                { T(1.1234568789), T(4.5238852912), T(5.2389421) },
                { T(3.1234568789), T(6.123458319), T(22.123904213) },
                { T(8.1238942134), T(11.01238421), T(13.51923911) },
                { T(7.9123849111), T(12.90123840), T(14.9123840324) },
            };
        }
    };
    TYPED_TEST_SUITE(Mat3x4EqualityTests, SupportedArithmeticTypes);



    struct Mat3x4ElementParam
    {
        flcn::Mat3x4<int> first, second;
        bool expected;
    };


    /// @brief Test fixture for @ref flcn::Mat3x4 Equality on a per-element basis.
    class Mat3x4PerElementEqualityTests: public testing::TestWithParam<Mat3x4ElementParam>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat3x4ElementwiseEquality, Mat3x4PerElementEqualityTests,
                             ::testing::Values(Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .expected = true },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .expected = false },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .expected = false },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 2, 1, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .expected = false },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 2, 3, 1, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .expected = false },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 2, 3, 4, 1, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .expected = false },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 2, 3, 4, 5, 1, 7, 8, 9, 10, 11, 12 },
                                                                   .expected = false },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 2, 3, 4, 5, 6, 1, 8, 9, 10, 11, 12 },
                                                                   .expected = false },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 2, 3, 4, 5, 6, 7, 1, 9, 10, 11, 12 },
                                                                   .expected = false },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 2, 3, 4, 5, 6, 7, 8, 1, 10, 11, 12 },
                                                                   .expected = false },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 11, 12 },
                                                                   .expected = false },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 12 },
                                                                   .expected = false },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 1 },
                                                                   .expected = false }));



    /// @brief Test fixture for @ref flcn::Mat3x4 Inequality on a per-element basis.
    class Mat3x4PerElementInequalityTests: public testing::TestWithParam<Mat3x4ElementParam>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat3x4ElementwiseInequality, Mat3x4PerElementInequalityTests,
                             ::testing::Values(Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .expected = false },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .expected = true },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .expected = true },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 2, 1, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .expected = true },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 2, 3, 1, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .expected = true },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 2, 3, 4, 1, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .expected = true },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 2, 3, 4, 5, 1, 7, 8, 9, 10, 11, 12 },
                                                                   .expected = true },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 2, 3, 4, 5, 6, 1, 8, 9, 10, 11, 12 },
                                                                   .expected = true },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 2, 3, 4, 5, 6, 7, 1, 9, 10, 11, 12 },
                                                                   .expected = true },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 2, 3, 4, 5, 6, 7, 8, 1, 10, 11, 12 },
                                                                   .expected = true },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 11, 12 },
                                                                   .expected = true },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 12 },
                                                                   .expected = true },
                                               Mat3x4ElementParam{ .first  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                   .second = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 1 },
                                                                   .expected = true }));



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat3x4 MAT1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
        constexpr flcn::Mat3x4 MAT2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
        constexpr flcn::Mat3x4 MAT3(4, 2, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12);
        constexpr flcn::Mat3x4 INF_MAT1(-flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                       -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                       flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                       -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                       -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                       flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
        constexpr flcn::Mat3x4 INF_MAT2(-flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                       -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                       flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                       -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                       -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                       flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);

        /** @test Verify that Mat3x4 allEq returns true for equal matrices at compile time. */
        static_assert(MAT1.allEq(MAT2) == true);

        /** @test Verify that Mat3x4 allEq returns false for unequal matrices at compile time. */
        static_assert(MAT1.allEq(MAT3) == false);

        /** @test Verify that Mat3x4 allEq returns true for equal infinite matrices at compile time. */
        static_assert(INF_MAT1.allEq(INF_MAT2) == true);



        /** @test Verify that Mat3x4 allEq (static wrapper) returns true for equal matrices at compile time. */
        static_assert(flcn::Mat3x4<int>::allEq(MAT1, MAT2) == true);

        /** @test Verify that Mat3x4 allEq (static wrapper) returns false for unequal matrices at compile time. */
        static_assert(flcn::Mat3x4<int>::allEq(MAT1, MAT3) == false);

        /** @test Verify that Mat3x4 allEq (static wrapper) returns true for equal infinite matrices at compile time. */
        static_assert(flcn::Mat3x4<float>::allEq(INF_MAT1, INF_MAT2) == true);



        /** @test Verify that Mat3x4 anyNeq returns false for equal matrices at compile time. */
        static_assert(MAT1.anyNeq(MAT2) == false);

        /** @test Verify that Mat3x4 anyNeq returns true for unequal matrices at compile time. */
        static_assert(MAT1.anyNeq(MAT3) == true);

        /** @test Verify that Mat3x4 anyNeq returns false for equal infinite matrices at compile time. */
        static_assert(INF_MAT1.anyNeq(INF_MAT2) == false);



        /** @test Verify that Mat3x4 anyNeq (static wrapper) returns false for equal matrices at compile time. */
        static_assert(flcn::Mat3x4<int>::anyNeq(MAT1, MAT2) == false);

        /** @test Verify that Mat3 anyNeq (static wrapper) returns true for unequal matrices at compile time. */
        static_assert(flcn::Mat3x4<int>::anyNeq(MAT1, MAT3) == true);

        /** @test Verify that Mat3 anyNeq (static wrapper) returns false for equal infinite matrices at compile time. */
        static_assert(flcn::Mat3x4<float>::anyNeq(INF_MAT1, INF_MAT2) == false);

    } // namespace static_tests

} // namespace


/**************************************
 *             ALL EQ                 *
 **************************************/

TYPED_TEST(Mat3x4EqualityTests, AllEq_IdenticalMatricesReturnTrue)
{
    const bool equality = this->_eqMatA.allEq(this->_eqMatB);
    EXPECT_TRUE(equality);
}


TYPED_TEST(Mat3x4EqualityTests, AllEq_DifferentMatricesReturnFalse)
{
    const bool equality = this->_eqMatA.allEq(this->_unEqualMat);
    EXPECT_FALSE(equality);
}


TEST(Mat3x4EqualityTests, AllEq_NanMatrixReturnsFalse)
{
    const flcn::Mat3x4 matA(NAN_F, NAN_F, NAN_F, NAN_F, NAN_F, 1.0f, NAN_F, NAN_F, NAN_F, NAN_F, NAN_F, 1.0f);
    const flcn::Mat3x4 matB(1.0f, -5.88874789f, 2.0f, 0.888749f, 0.5329f, 5.23193f, 1.0f, -5.88874789f, 2.0f, 0.888749f,
                           0.5329f, 5.23193f);

    const bool equality = matA.allEq(matB);
    EXPECT_FALSE(equality);
}


TEST(Mat3x4EqualityTests, AllEq_IdenticalInfiniteMatricesReturnTrue)
{
    const flcn::Mat3x4 matA(INF, -INF, INF, -INF, -INF, INF, INF, -INF, INF, -INF, -INF, INF);
    const flcn::Mat3x4 matB(INF, -INF, INF, -INF, -INF, INF, INF, -INF, INF, -INF, -INF, INF);

    const bool equality = matA.allEq(matB);
    EXPECT_TRUE(equality);
}


TEST(Mat3x4EqualityTests, AllEq_DifferentInfiniteMatricesReturnFalse)
{
    const flcn::Mat3x4 matA(INF, -INF, INF, -INF, INF, INF, INF, -INF, INF, -INF, INF, INF);
    const flcn::Mat3x4 matB(-INF, -INF, INF, INF, INF, INF, INF, -INF, INF, -INF, INF, INF);

    const bool equality = matA.allEq(matB);
    EXPECT_FALSE(equality);
}


TYPED_TEST(Mat3x4EqualityTests, AllEq_MixedType_IdenticalMatricesReturnTrue)
{
    const flcn::Mat3x4 matA(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
    const flcn::Mat3x4 matB(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0);

    const bool equality = matA.allEq(matB);
    EXPECT_TRUE(equality);
}


TYPED_TEST(Mat3x4EqualityTests, AllEq_MixedType_DifferentMatricesReturnFalse)
{
    const flcn::Mat3x4 matA(5, 6, 7, 8, 9, 10, 5, 6, 7, 8, 9, 10);
    const flcn::Mat3x4 matB(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    const bool equality = matA.allEq(matB);
    EXPECT_FALSE(equality);
}

TEST_P(Mat3x4PerElementEqualityTests, AllEq_VerifiesElementwiseEquality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat.allEq(secondMat));
}


TYPED_TEST(Mat3x4EqualityTests, StaticWrapper_AllEq_IdenticalMatricesReturnTrue)
{
    const bool equality = flcn::Mat3x4<TypeParam>::allEq(this->_eqMatA, this->_eqMatB);
    EXPECT_TRUE(equality);
}


TYPED_TEST(Mat3x4EqualityTests, StaticWrapper_AllEq_DifferentMatricesReturnFalse)
{
    const bool equality = flcn::Mat3x4<TypeParam>::allEq(this->_eqMatA, this->_unEqualMat);
    EXPECT_FALSE(equality);
}


TEST_P(Mat3x4PerElementEqualityTests, StaticWrapper_AllEq_VerifiesElementwiseEquality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Mat3x4<int>::allEq(firstMat, secondMat));
}



/**************************************
 *       DOUBLE-EQUALS OPERATOR       *
 **************************************/

TYPED_TEST(Mat3x4EqualityTests, DoubleEqualsOperator_IdenticalMatricesReturnTrue)
{
    const bool equality = this->_eqMatA == this->_eqMatB;
    EXPECT_TRUE(equality);
}


TYPED_TEST(Mat3x4EqualityTests, DoubleEqualsOperator_DifferentMatricesReturnFalse)
{
    const bool equality = this->_eqMatA == this->_unEqualMat;
    EXPECT_FALSE(equality);
}


TEST_P(Mat3x4PerElementEqualityTests, DoubleEqualsOperator_AllEq_VerifiesElementwiseEquality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat == secondMat);
}


TEST(Mat3x4EqualityTests, DoubleEqualsOperator_IdenticalBooleanMatricesReturnTrue)
{
    const flcn::Mat3x4 matA(true, false, true, false, false, true, true, false, true, false, false, true);
    const flcn::Mat3x4 matB(true, false, true, false, false, true, true, false, true, false, false, true);

    const bool equality = matA == matB;
    EXPECT_TRUE(equality);
}


TEST(Mat3x4EqualityTests, DoubleEqualsOperator_DifferentBooleanMatricesReturnFalse)
{
    const flcn::Mat3x4 matA(true, false, false, true, false, false, true, false, true, false, false, true);
    const flcn::Mat3x4 matB(true, true, false, true, true, true, false, true, false, false, true, false);

    const bool equality = matA == matB;
    EXPECT_FALSE(equality);
}


TEST_P(Mat3x4PerElementEqualityTests, DoubleEqualsOperator_VerifiesElementwiseEquality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat == secondMat);
}



/**************************************
 *             ANY NEQ                *
 **************************************/

TYPED_TEST(Mat3x4EqualityTests, AnyNeq_IdenticalMatricesReturnFalse)
{
    const bool inequality = this->_eqMatA.anyNeq(this->_eqMatB);
    EXPECT_FALSE(inequality);
}


TYPED_TEST(Mat3x4EqualityTests, AnyNeq_DifferentMatricesReturnTrue)
{
    const bool inequality = this->_eqMatA.anyNeq(this->_unEqualMat);
    EXPECT_TRUE(inequality);
}


TEST(Mat3x4EqualityTests, AnyNeq_NanMatrixReturnsTrue)
{
    const flcn::Mat3x4 matA(NAN_F, NAN_F, NAN_F, NAN_F, NAN_F, 1.0f, NAN_F, NAN_F, NAN_F, NAN_F, NAN_F, 1.0f);
    const flcn::Mat3x4 matB(1.0f, -5.88874789f, 2.0f, 0.888749f, 0.5329f, 5.23193f, 1.0f, -5.88874789f, 2.0f, 0.888749f,
                           0.5329f, 5.23193f);

    const bool inequality = matA.anyNeq(matB);
    EXPECT_TRUE(inequality);
}


TEST(Mat3x4EqualityTests, AnyNeq_IdenticalInfiniteMatricesReturnFalse)
{
    const flcn::Mat3x4 matA(INF, -INF, INF, -INF, -INF, INF, INF, -INF, INF, -INF, -INF, INF);
    const flcn::Mat3x4 matB(INF, -INF, INF, -INF, -INF, INF, INF, -INF, INF, -INF, -INF, INF);

    const bool inequality = matA.anyNeq(matB);
    EXPECT_FALSE(inequality);
}


TEST(Mat3x4EqualityTests, AnyNeq_DifferentInfiniteMatricesReturnTrue)
{
    const flcn::Mat3x4 matA(INF, -INF, INF, -INF, INF, INF, INF, -INF, INF, -INF, INF, INF);
    const flcn::Mat3x4 matB(-INF, -INF, INF, INF, INF, INF, INF, -INF, INF, -INF, INF, INF);

    const bool inequality = matA.anyNeq(matB);
    EXPECT_TRUE(inequality);
}


TYPED_TEST(Mat3x4EqualityTests, AnyNeq_MixedType_IdenticalMatricesReturnFalse)
{
    const flcn::Mat3x4 matA(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
    const flcn::Mat3x4 matB(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0);

    const bool inequality = matA.anyNeq(matB);
    EXPECT_FALSE(inequality);
}


TYPED_TEST(Mat3x4EqualityTests, AnyNeq_MixedType_DifferentMatricesReturnTrue)
{
    const flcn::Mat3x4 matA(5, 6, 7, 8, 9, 10, 5, 6, 7, 8, 9, 10);
    const flcn::Mat3x4 matB(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    const bool inequality = matA.anyNeq(matB);
    EXPECT_TRUE(inequality);
}


TEST_P(Mat3x4PerElementInequalityTests, AnyNeq_VerifiesElementwiseInequality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat.anyNeq(secondMat));
}


TYPED_TEST(Mat3x4EqualityTests, StaticWrapper_AnyNeq_IdenticalMatricesReturnFalse)
{
    const bool inequality = flcn::Mat3x4<TypeParam>::anyNeq(this->_eqMatA, this->_eqMatB);
    EXPECT_FALSE(inequality);
}


TYPED_TEST(Mat3x4EqualityTests, StaticWrapper_AnyNeq_DifferentMatricesReturnTrue)
{
    const bool inequality = flcn::Mat3x4<TypeParam>::anyNeq(this->_eqMatA, this->_unEqualMat);
    EXPECT_TRUE(inequality);
}


TEST_P(Mat3x4PerElementInequalityTests, StaticWrapper_AnyNeq_VerifiesElementwiseInequality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Mat3x4<int>::anyNeq(firstMat, secondMat));
}



/**************************************
 *            NOT EQUALS              *
 **************************************/

TYPED_TEST(Mat3x4EqualityTests, NotEqualsOperator_IdenticalMatricesReturnFalse)
{
    const bool inequality = this->_eqMatA != this->_eqMatB;
    EXPECT_FALSE(inequality);
}


TYPED_TEST(Mat3x4EqualityTests, NotEqualsOperator_DifferentMatricesReturnTrue)
{
    const bool inequality = this->_eqMatA != this->_unEqualMat;
    EXPECT_TRUE(inequality);
}


TEST(Mat3x4EqualityTests, NotEqualsOperator_IdenticalBooleanMatricesReturnFalse)
{
    const flcn::Mat3x4 matA(true, false, true, false, false, true, true, false, true, false, false, true);
    const flcn::Mat3x4 matB(true, false, true, false, false, true, true, false, true, false, false, true);

    const bool inequality = matA != matB;
    EXPECT_FALSE(inequality);
}


TEST(Mat3x4EqualityTests, NotEqualsOperator_DifferentBooleanMatricesReturnTrue)
{
    const flcn::Mat3x4 matA(true, false, false, true, false, false, true, false, true, false, false, true);
    const flcn::Mat3x4 matB(true, true, false, true, true, true, false, true, false, false, true, false);

    const bool inequality = matA != matB;
    EXPECT_TRUE(inequality);
}


TEST_P(Mat3x4PerElementInequalityTests, NotEqualsOperator_VerifiesElementwiseInequality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat != secondMat);
}


/** @} */
