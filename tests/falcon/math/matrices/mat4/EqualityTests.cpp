/**
 * @file EqualityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 01, 2026
 *
 * @brief Verify @ref flcn::Mat4 equality operator (==, !=) and their functional counterpart's
 *        (eq, neq, allEq, anyNeq) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4TestSetup.h"

#include <falcon/math/common/Constants.h>



/**
 * @addtogroup T_FALCON_Mat4x4_Equality
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
     * @brief Test fixture for @ref flcn::Mat4 Equality.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat4EqualityTests: public ::testing::Test
    {
    protected:
        flcn::Mat4<T> _eqMatA;
        flcn::Mat4<T> _eqMatB;
        flcn::Mat4<T> _unEqualMat;


        void SetUp() override
        {
            _eqMatA     = { { T(1.1234568789), T(2.123458319), T(3.323458319), T(5.392489234) },
                            { T(3.1234568789), T(4.123458319), T(7.123458319), T(12.3492812) },
                            { T(11.1234568789), T(3.123458319), T(5.123458319), T(0.238491234) },
                            { T(5.0), T(33.123458319), T(5.5932023), T(9.823582394) } };
            _eqMatB     = { { T(1.1234568789), T(2.123458319), T(3.323458319), T(5.392489234) },
                            { T(3.1234568789), T(4.123458319), T(7.123458319), T(12.3492812) },
                            { T(11.1234568789), T(3.123458319), T(5.123458319), T(0.238491234) },
                            { T(5.0), T(33.123458319), T(5.5932023), T(9.823582394) } };
            _unEqualMat = { { T(1.1234568789), T(4.5238852912), T(3.123458319), T(0.238491234) },
                            { T(3.1234568789), T(6.123458319), T(4.123458319), T(12.3492812) },
                            { T(3.1234568789), T(4.123458319), T(7.123458319), T(5.392489234) },
                            { T(5.0), T(33.123458319), T(5.5932023), T(9.823582394) } };
        }
    };
    TYPED_TEST_SUITE(Mat4EqualityTests, SupportedArithmeticTypes);


    struct Mat4EqualityParam
    {
        flcn::Mat4<int> first, second;
        bool expected;
    };


    /// @brief Test fixture for @ref flcn::Mat4 Equality on a per-element basis.
    class Mat4PerElementEqualityTests: public testing::TestWithParam<Mat4EqualityParam>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat4ElementwiseEquality, Mat4PerElementEqualityTests,
        ::testing::Values(Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .expected = true },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .expected = false },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .expected = false },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 1, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .expected = false },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 1, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .expected = false },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 1, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .expected = false },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 1, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .expected = false },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 6, 1, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .expected = false },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 6, 7, 1, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .expected = false },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 6, 7, 8, 1, 10, 11, 12, 13, 14, 15, 16 },
                                             .expected = false },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 11, 12, 13, 14, 15, 16 },
                                             .expected = false },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 12, 13, 14, 15, 16 },
                                             .expected = false },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 1, 13, 14, 15, 16 },
                                             .expected = false },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 14, 15, 16 },
                                             .expected = false },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 1, 15, 16 },
                                             .expected = false },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 1, 16 },
                                             .expected = false },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 1 },
                                             .expected = false }));



    /// @brief Test fixture for @ref flcn::Mat4 Inequality on a per-element basis.
    class Mat4PerElementInequalityTests: public testing::TestWithParam<Mat4EqualityParam>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat4ElementwiseInequality, Mat4PerElementInequalityTests,
        ::testing::Values(Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .expected = false },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .expected = true },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .expected = true },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 1, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .expected = true },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 1, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .expected = true },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 1, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .expected = true },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 1, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .expected = true },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 6, 1, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .expected = true },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 6, 7, 1, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .expected = true },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 6, 7, 8, 1, 10, 11, 12, 13, 14, 15, 16 },
                                             .expected = true },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 11, 12, 13, 14, 15, 16 },
                                             .expected = true },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 12, 13, 14, 15, 16 },
                                             .expected = true },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 1, 13, 14, 15, 16 },
                                             .expected = true },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 14, 15, 16 },
                                             .expected = true },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 1, 15, 16 },
                                             .expected = true },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 1, 16 },
                                             .expected = true },
                          Mat4EqualityParam{ .first    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
                                             .second   = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 1 },
                                             .expected = true }));



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat4 MAT1(1, 2, 3, 4);
        constexpr flcn::Mat4 MAT2(1, 2, 3, 4);
        constexpr flcn::Mat4 MAT3(4, 2, 2, 4);
        constexpr flcn::Mat4 INF_MAT1(-flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                     -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
        constexpr flcn::Mat4 INF_MAT2(-flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                     -flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);


        /** @test Verify that Mat4 allEq returns true for equal matrices at compile time. */
        static_assert(MAT1.allEq(MAT2) == true);

        /** @test Verify that Mat4 allEq returns false for unequal matrices at compile time. */
        static_assert(MAT1.allEq(MAT3) == false);

        /** @test Verify that Mat4 allEq returns true for equal infinite matrices at compile time. */
        static_assert(INF_MAT1.allEq(INF_MAT2) == true);



        /** @test Verify that Mat4 allEq (static wrapper) returns true for equal matrices at compile time. */
        static_assert(flcn::Mat4<int>::allEq(MAT1, MAT2) == true);

        /** @test Verify that Mat4 allEq (static wrapper) returns false for unequal matrices at compile time. */
        static_assert(flcn::Mat4<int>::allEq(MAT1, MAT3) == false);

        /** @test Verify that Mat4 allEq (static wrapper) returns true for equal infinite matrices at compile time. */
        static_assert(flcn::Mat4<float>::allEq(INF_MAT1, INF_MAT2) == true);



        /** @test Verify that Mat4 anyNeq returns false for equal matrices at compile time. */
        static_assert(MAT1.anyNeq(MAT2) == false);

        /** @test Verify that Mat4 anyNeq returns true for unequal matrices at compile time. */
        static_assert(MAT1.anyNeq(MAT3) == true);

        /** @test Verify that Mat4 anyNeq returns false for equal infinite matrices at compile time. */
        static_assert(INF_MAT1.anyNeq(INF_MAT2) == false);



        /** @test Verify that Mat4 anyNeq (static wrapper) returns false for equal matrices at compile time. */
        static_assert(flcn::Mat4<int>::anyNeq(MAT1, MAT2) == false);

        /** @test Verify that Mat4 anyNeq (static wrapper) returns true for unequal matrices at compile time. */
        static_assert(flcn::Mat4<int>::anyNeq(MAT1, MAT3) == true);

        /** @test Verify that Mat4 anyNeq (static wrapper) returns false for equal infinite matrices at compile time. */
        static_assert(flcn::Mat4<float>::anyNeq(INF_MAT1, INF_MAT2) == false);

    } // namespace static_tests

} // namespace



/**************************************
 *             ALL EQ                 *
 **************************************/

TYPED_TEST(Mat4EqualityTests, AllEq_IdenticalMatricesReturnTrue)
{
    const bool equality = this->_eqMatA.allEq(this->_eqMatB);
    EXPECT_TRUE(equality);
}


TYPED_TEST(Mat4EqualityTests, AllEq_DifferentMatricesReturnFalse)
{
    const bool equality = this->_eqMatA.allEq(this->_unEqualMat);
    EXPECT_FALSE(equality);
}


TEST(Mat4EqualityTests, AllEq_NanMatrixReturnsFalse)
{
    const flcn::Mat4 matA(NAN_F, NAN_F, NAN_F, NAN_F);
    const flcn::Mat4 matB(1.0f, -5.88874789f, 0.888749f, 0.38239f);

    const bool equality = matA.allEq(matB);
    EXPECT_FALSE(equality);
}


TEST(Mat4EqualityTests, AllEq_IdenticalInfiniteMatricesReturnTrue)
{
    const flcn::Mat4 matA(INF, -INF, INF, -INF);
    const flcn::Mat4 matB(INF, -INF, INF, -INF);

    const bool equality = matA.allEq(matB);
    EXPECT_TRUE(equality);
}


TEST(Mat4EqualityTests, AllEq_DifferentInfiniteMatricesReturnFalse)
{
    const flcn::Mat4 matA(INF, -INF, INF, INF);
    const flcn::Mat4 matB(-INF, -INF, INF, -INF);

    const bool equality = matA.allEq(matB);
    EXPECT_FALSE(equality);
}


TYPED_TEST(Mat4EqualityTests, AllEq_MixedType_IdenticalMatricesReturnTrue)
{
    const flcn::Mat4 matA(1, 2, 3, 4);
    const flcn::Mat4 matB(1.0, 2.0, 3.0, 4.0);

    const bool equality = matA.allEq(matB);
    EXPECT_TRUE(equality);
}


TYPED_TEST(Mat4EqualityTests, AllEq_MixedType_DifferentMatricesReturnFalse)
{
    const flcn::Mat4 matA(5, 6, 7, 1);
    const flcn::Mat4 matB(1.0, 2.0, 3.0, 1.0);

    const bool equality = matA.allEq(matB);
    EXPECT_FALSE(equality);
}

TEST_P(Mat4PerElementEqualityTests, AllEq_VerifiesElementwiseEquality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat.allEq(secondMat));
}


TYPED_TEST(Mat4EqualityTests, StaticWrapper_AllEq_IdenticalMatricesReturnTrue)
{
    const bool equality = flcn::Mat4<TypeParam>::allEq(this->_eqMatA, this->_eqMatB);
    EXPECT_TRUE(equality);
}


TYPED_TEST(Mat4EqualityTests, StaticWrapper_AllEq_DifferentMatricesReturnFalse)
{
    const bool equality = flcn::Mat4<TypeParam>::allEq(this->_eqMatA, this->_unEqualMat);
    EXPECT_FALSE(equality);
}


TEST_P(Mat4PerElementEqualityTests, StaticWrapper_AllEq_VerifiesElementwiseEquality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Mat4<int>::allEq(firstMat, secondMat));
}



/**************************************
 *       DOUBLE-EQUALS OPERATOR       *
 **************************************/

TYPED_TEST(Mat4EqualityTests, DoubleEqualsOperator_IdenticalMatricesReturnTrue)
{
    const bool equality = this->_eqMatA == this->_eqMatB;
    EXPECT_TRUE(equality);
}


TYPED_TEST(Mat4EqualityTests, DoubleEqualsOperator_DifferentMatricesReturnFalse)
{
    const bool equality = this->_eqMatA == this->_unEqualMat;
    EXPECT_FALSE(equality);
}


TEST_P(Mat4PerElementEqualityTests, DoubleEqualsOperator_AllEq_VerifiesElementwiseEquality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat == secondMat);
}


TEST(Mat4EqualityTests, DoubleEqualsOperator_IdenticalBooleanMatricesReturnTrue)
{
    const flcn::Mat4 matA(true, false, true, false);
    const flcn::Mat4 matB(true, false, true, false);

    const bool equality = matA == matB;
    EXPECT_TRUE(equality);
}


TEST(Mat4EqualityTests, DoubleEqualsOperator_DifferentBooleanMatricesReturnFalse)
{
    const flcn::Mat4 matA(true, false, false, true);
    const flcn::Mat4 matB(true, true, false, false);

    const bool equality = matA == matB;
    EXPECT_FALSE(equality);
}


TEST_P(Mat4PerElementEqualityTests, DoubleEqualsOperator_VerifiesElementwiseEquality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat == secondMat);
}



/**************************************
 *             ANY NEQ                *
 **************************************/

TYPED_TEST(Mat4EqualityTests, AnyNeq_IdenticalMatricesReturnFalse)
{
    const bool inequality = this->_eqMatA.anyNeq(this->_eqMatB);
    EXPECT_FALSE(inequality);
}


TYPED_TEST(Mat4EqualityTests, AnyNeq_DifferentMatricesReturnTrue)
{
    const bool inequality = this->_eqMatA.anyNeq(this->_unEqualMat);
    EXPECT_TRUE(inequality);
}


TEST(Mat4EqualityTests, AnyNeq_NanMatrixReturnsTrue)
{
    const flcn::Mat4 matA(NAN_F, NAN_F, NAN_F, NAN_F);
    const flcn::Mat4 matB(1.0f, INF, -INF, NAN_F);

    const bool inequality = matA.anyNeq(matB);
    EXPECT_TRUE(inequality);
}


TEST(Mat4EqualityTests, AnyNeq_IdenticalInfiniteMatricesReturnFalse)
{
    const flcn::Mat4 matA(INF, -INF, INF, -INF);
    const flcn::Mat4 matB(INF, -INF, INF, -INF);

    const bool inequality = matA.anyNeq(matB);
    EXPECT_FALSE(inequality);
}


TEST(Mat4EqualityTests, AnyNeq_DifferentInfiniteMatricesReturnTrue)
{
    const flcn::Mat4 matA(INF, -INF, INF, -INF);
    const flcn::Mat4 matB(INF, -INF, INF, INF);


    const bool inequality = matA.anyNeq(matB);
    EXPECT_TRUE(inequality);
}


TYPED_TEST(Mat4EqualityTests, AnyNeq_MixedType_IdenticalMatricesReturnFalse)
{
    const flcn::Mat4 matA(1, 2, 3, 4);
    const flcn::Mat4 matB(1.0, 2.0, 3.0, 4.0);

    const bool inequality = matA.anyNeq(matB);
    EXPECT_FALSE(inequality);
}


TYPED_TEST(Mat4EqualityTests, AnyNeq_MixedType_DifferentMatricesReturnTrue)
{
    const flcn::Mat4 matA(5, 6, 7, 8);
    const flcn::Mat4 matB(1.0, 2.0, 3.0, 4.0);

    const bool inequality = matA.anyNeq(matB);
    EXPECT_TRUE(inequality);
}


TEST_P(Mat4PerElementInequalityTests, AnyNeq_VerifiesElementwiseInequality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat.anyNeq(secondMat));
}


TYPED_TEST(Mat4EqualityTests, StaticWrapper_AnyNeq_IdenticalMatricesReturnFalse)
{
    const bool inequality = flcn::Mat4<TypeParam>::anyNeq(this->_eqMatA, this->_eqMatB);
    EXPECT_FALSE(inequality);
}


TYPED_TEST(Mat4EqualityTests, StaticWrapper_AnyNeq_DifferentMatricesReturnTrue)
{
    const bool inequality = flcn::Mat4<TypeParam>::anyNeq(this->_eqMatA, this->_unEqualMat);
    EXPECT_TRUE(inequality);
}


TEST_P(Mat4PerElementInequalityTests, StaticWrapper_AnyNeq_VerifiesElementwiseInequality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Mat4<int>::anyNeq(firstMat, secondMat));
}



/**************************************
 *            NOT EQUALS              *
 **************************************/

TYPED_TEST(Mat4EqualityTests, NotEqualsOperator_IdenticalMatricesReturnFalse)
{
    const bool inequality = this->_eqMatA != this->_eqMatB;
    EXPECT_FALSE(inequality);
}


TYPED_TEST(Mat4EqualityTests, NotEqualsOperator_DifferentMatricesReturnTrue)
{
    const bool inequality = this->_eqMatA != this->_unEqualMat;
    EXPECT_TRUE(inequality);
}


TEST(Mat4EqualityTests, NotEqualsOperator_IdenticalBooleanMatricesReturnFalse)
{
    const flcn::Mat4 matA(true, false, true, false);
    const flcn::Mat4 matB(true, false, true, false);

    const bool inequality = matA != matB;
    EXPECT_FALSE(inequality);
}


TEST(Mat4EqualityTests, NotEqualsOperator_DifferentBooleanMatricesReturnTrue)
{
    const flcn::Mat4 matA(true, false, true, false);
    const flcn::Mat4 matB(true, true, false, false);

    const bool inequality = matA != matB;
    EXPECT_TRUE(inequality);
}


TEST_P(Mat4PerElementInequalityTests, NotEqualsOperator_VerifiesElementwiseInequality)
{
    const auto& [firstMat, secondMat, expected] = GetParam();
    EXPECT_EQ(expected, firstMat != secondMat);
}

/** @} */
