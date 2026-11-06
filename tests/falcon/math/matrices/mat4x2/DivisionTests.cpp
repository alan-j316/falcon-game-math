/**
 * @file DivisionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref flcn::Mat4x2 division logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4x2TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat4x2_Division
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4x2 Division.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat4x2DivisionTests: public testing::Test
    {
    protected:
        flcn::Mat4x2<T> _matrix;
        T _scalar;
        flcn::Mat4x2<T> _expectedMatrix;

        void SetUp() override
        {
            _matrix         = { flcn::Vec4{ T(7), T(3), T(0), T(21) }, flcn::Vec4{ T(1), T(6), T(6), T(12) } };
            _scalar         = T(3);
            _expectedMatrix = { flcn::Vec4{ T(2.333333333333333), T(1), T(0), T(7) },
                                flcn::Vec4{ T(0.3333333333333333), T(2), T(2), T(4) } };
        }
    };
    TYPED_TEST_SUITE(Mat4x2DivisionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::Mat4x2 Division with NaN elements.
     */
    class Mat4x2DivisionNaNTests: public testing::TestWithParam<flcn::Mat4x2<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat4x2InvalidDivision, Mat4x2DivisionNaNTests,
        ::testing::Values(flcn::Mat4x2<float>(flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
                          flcn::Mat4x2<float>(3.0f, flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
                          flcn::Mat4x2<float>(3.0f, 3.0f, flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
                          flcn::Mat4x2<float>(3.0f, 3.0f, 3.0f, flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f),
                          flcn::Mat4x2<float>(3.0f, 3.0f, 3.0f, 3.0f, flcn::constants::NaN, 3.0f, 3.0f, 3.0f),
                          flcn::Mat4x2<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, flcn::constants::NaN, 3.0f, 3.0f),
                          flcn::Mat4x2<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, flcn::constants::NaN, 3.0f),
                          flcn::Mat4x2<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, flcn::constants::NaN),
                          flcn::Mat4x2<float>(flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
                                             flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
                                             flcn::constants::NaN, flcn::constants::NaN)));




    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat4x2 MAT(2, 4, 6, 8, 10, 12, 14, 16);

        /// @test Verify that Mat4x2 division operator returns a valid matrix at compile time.
        constexpr flcn::Mat4x2 DIV_RESULT_1 = MAT / 2;
        static_assert(DIV_RESULT_1(0, 0) == 1);
        static_assert(DIV_RESULT_1(0, 1) == 2);
        static_assert(DIV_RESULT_1(1, 0) == 3);
        static_assert(DIV_RESULT_1(1, 1) == 4);
        static_assert(DIV_RESULT_1(2, 0) == 5);
        static_assert(DIV_RESULT_1(2, 1) == 6);
        static_assert(DIV_RESULT_1(3, 0) == 7);
        static_assert(DIV_RESULT_1(3, 1) == 8);

        /// @test Verify that Mat4x2 safeDiv returns a valid matrix at compile time.
        constexpr flcn::Mat4x2 DIV_RESULT_2 = MAT.safeDiv(2);
        static_assert(DIV_RESULT_2(0, 0) == 1);
        static_assert(DIV_RESULT_2(0, 1) == 2);
        static_assert(DIV_RESULT_2(1, 0) == 3);
        static_assert(DIV_RESULT_2(1, 1) == 4);
        static_assert(DIV_RESULT_2(2, 0) == 5);
        static_assert(DIV_RESULT_2(2, 1) == 6);
        static_assert(DIV_RESULT_2(3, 0) == 7);
        static_assert(DIV_RESULT_2(3, 1) == 8);

        /// @test Verify that Mat4x2 safeDiv (static wrapper) returns a valid matrix at compile time.
        constexpr flcn::Mat4x2 DIV_RESULT_3 = flcn::Mat4x2<int>::safeDiv(MAT, 2);
        static_assert(DIV_RESULT_3(0, 0) == 1);
        static_assert(DIV_RESULT_3(0, 1) == 2);
        static_assert(DIV_RESULT_3(1, 0) == 3);
        static_assert(DIV_RESULT_3(1, 1) == 4);
        static_assert(DIV_RESULT_3(2, 0) == 5);
        static_assert(DIV_RESULT_3(2, 1) == 6);
        static_assert(DIV_RESULT_3(3, 0) == 7);
        static_assert(DIV_RESULT_3(3, 1) == 8);

        // Matrix Try Division
        // NOT available at compile time due to [out] parameter (OperationStatus).

    } // namespace static_tests

} // namespace



/**************************************
 *      DIVISION TESTS (RUNTIME)      *
 **************************************/

TYPED_TEST(Mat4x2DivisionTests, DivideOperator_ReturnsAValidMatrix)
{
    const flcn::Mat4x2 inverseScaledMat = this->_matrix / this->_scalar;
    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


TYPED_TEST(Mat4x2DivisionTests, DivideEqualsOperator_PerformsElementWiseDivisionInPlace)
{
    flcn::Mat4x2 matrix = this->_matrix;

    matrix /= this->_scalar;
    EXPECT_MAT_EQ(this->_expectedMatrix, matrix);
}


/**************************************
 *         SAFE DIVISION TESTS        *
 **************************************/

TYPED_TEST(Mat4x2DivisionTests, SafeDiv_ReturnsAValidMatrix)
{
    const flcn::Mat4x2 inverseScaledMat = this->_matrix.safeDiv(this->_scalar);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


TYPED_TEST(Mat4x2DivisionTests, SafeDiv_DivisionByZeroReturnsIdentityMatrixByDefault)
{
    const flcn::Mat4x2 inverseScaledMat = this->_matrix.safeDiv(TypeParam(0));
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TYPED_TEST(Mat4x2DivisionTests, SafeDiv_DivisionByZeroReturnsPassedInFallbackMatrix)
{
    const flcn::Mat4x2 inverseScaledMat = this->_matrix.safeDiv(TypeParam(0), flcn::Mat4x2<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TEST_P(Mat4x2DivisionNaNTests, SafeDiv_ReturnsIdentityMatrixByDefault)
{
    const flcn::Mat4x2 inverseScaledMat = GetParam().safeDiv(2.5);
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TEST_P(Mat4x2DivisionNaNTests, SafeDiv_ReturnsPassedInFallbackMatrix)
{
    const flcn::Mat4x2 inverseScaledMat = GetParam().safeDiv(2.5, flcn::Mat4x2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TYPED_TEST(Mat4x2DivisionTests, SafeDiv_StaticWrapper_ReturnsAValidMatrix)
{
    const flcn::Mat4x2 inverseScaledMat = flcn::Mat4x2<TypeParam>::safeDiv(this->_matrix, this->_scalar);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


TYPED_TEST(Mat4x2DivisionTests, StaticWrapper_SafeDiv_DivisionByZeroReturnsIdentityMatrixByDefault)
{
    const flcn::Mat4x2 inverseScaledMat = flcn::Mat4x2<TypeParam>::safeDiv(this->_matrix, TypeParam(0));
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TYPED_TEST(Mat4x2DivisionTests, StaticWrapper_SafeDiv_DivisionByZeroReturnsPassedInFallbackMatrix)
{
    const flcn::Mat4x2 inverseScaledMat =
        flcn::Mat4x2<TypeParam>::safeDiv(this->_matrix, TypeParam(0), flcn::Mat4x2<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TEST_P(Mat4x2DivisionNaNTests, StaticWrapper_SafeDiv_ReturnsIdentityMatrixByDefault)
{
    using T                            = ParamType::value_type;
    const flcn::Mat4x2 inverseScaledMat = flcn::Mat4x2<T>::safeDiv(GetParam(), 2.5);
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TEST_P(Mat4x2DivisionNaNTests, StaticWrapper_SafeDiv_ReturnsPassedInFallbackMatrix)
{
    using T                            = ParamType::value_type;
    const flcn::Mat4x2 inverseScaledMat = flcn::Mat4x2<T>::safeDiv(GetParam(), 2.5, flcn::Mat4x2<T>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}



/**************************************
 *         TRY DIVISION TESTS         *
 **************************************/

/**
 * @test Verify that dividing a matrix using @ref flcn::Mat4x2::tryDiv perform an element-wise divide
 *        returns a new matrix instance and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat4x2DivisionTests, TryDiv_ReturnsAValidMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat4x2 inverseScaledMat = this->_matrix.tryDiv(this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that dividing a matrix by zero using @ref flcn::Mat4x2::tryDiv
 *        returns zero matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat4x2DivisionTests, TryDiv_DivisionByZeroReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat4x2 inverseScaledMat = this->_matrix.tryDiv(TypeParam(0), flag);

    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a matrix by zero using @ref flcn::Mat4x2::tryDiv returns passed-in fallback
 *        and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat4x2DivisionTests, TryDiv_DivisionByZeroReturnsPassedInFallbackAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat4x2 inverseScaledMat = this->_matrix.tryDiv(TypeParam(0), flag, flcn::Mat4x2<TypeParam>::zero());

    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a NaN matrix using @ref flcn::Mat4x2::tryDiv returns zero matrix
 *        by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat4x2DivisionNaNTests, TryDiv_ReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat4x2 inverseScaledMat = GetParam().tryDiv(2.5, flag);
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix using @ref flcn::Mat4x2::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat4x2DivisionNaNTests, TryDiv_ReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat4x2 inverseScaledMat = GetParam().tryDiv(2.5, flag, flcn::Mat4x2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix by zero using @ref flcn::Mat4x2::tryDiv
 *        returns set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat4x2DivisionNaNTests, TryDiv_NaNOperandTakesPrecedenceOverZeroDivisionAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    [[maybe_unused]] const flcn::Mat4x2 inverseScaledMat =
        GetParam().tryDiv(0, flag, flcn::Mat4x2<ParamType::value_type>::zero());
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a matrix using the static variant of @ref flcn::Mat4x2::tryDiv
 *        perform an element-wise divide, returns a new matrix instance
 *        and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat4x2DivisionTests, StaticWrapper_TryDiv_ReturnsAValidMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat4x2 inverseScaledMat = flcn::Mat4x2<TypeParam>::tryDiv(this->_matrix, this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that dividing a matrix by zero using the static variant of @ref flcn::Mat4x2::tryDiv
 *        returns zero matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat4x2DivisionTests, StaticWrapper_TryDiv_DivisionByZeroReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat4x2 inverseScaledMat = flcn::Mat4x2<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag);
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a matrix by zero using the static variant of @ref flcn::Mat4x2::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat4x2DivisionTests, StaticWrapper_TryDiv_DivisionByZeroReturnsPassedInFallbackAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat4x2 inverseScaledMat =
        flcn::Mat4x2<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag, flcn::Mat4x2<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a NaN matrix using the static variant of @ref flcn::Mat4x2::tryDiv
 *        returns zero matrix by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat4x2DivisionNaNTests, StaticWrapper_TryDiv_ReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    using T                            = ParamType::value_type;
    const flcn::Mat4x2 inverseScaledMat = flcn::Mat4x2<T>::tryDiv(GetParam(), 2.5, flag);
    EXPECT_MAT_ZERO(inverseScaledMat);

    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix by zero using the static variant of @ref flcn::Mat4x2::tryDiv
 *        set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat4x2DivisionNaNTests, StaticWrapper_TryDiv_NaNOperandTakesPrecedenceOverZeroDivisionAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    using T                                             = ParamType::value_type;
    [[maybe_unused]] const flcn::Mat4x2 inverseScaledMat = flcn::Mat4x2<T>::tryDiv(GetParam(), T(0), flag);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix using the static variant of @ref flcn::Mat4x2::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat4x2DivisionNaNTests, StaticWrapper_TryDiv_ReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    using T = ParamType::value_type;
    const flcn::Mat4x2 inverseScaledMat =
        flcn::Mat4x2<T>::tryDiv(GetParam(), 2.5, flag, flcn::Mat4x2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/** @} */
