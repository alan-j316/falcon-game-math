/**
 * @file DivisionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 13, 2026
 *
 * @brief Verify @ref flcn::Mat2 division logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat2x2_Division
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2 Division.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2DivisionTests: public testing::Test
    {
    protected:
        flcn::Mat2<T> _matrix;
        T _scalar;
        flcn::Mat2<T> _expectedMatrix;

        void SetUp() override
        {
            _matrix         = { flcn::CVec2<T>{ 7, 3 }, flcn::CVec2<T>{ 1, 6 } };
            _scalar         = T(3);
            _expectedMatrix = { flcn::CVec2{ T(2.333333333333333), T(1) }, flcn::CVec2{ T(0.3333333333333333), T(2) } };
        }
    };
    TYPED_TEST_SUITE(Mat2DivisionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::Mat2 Division with NaN elements.
     */
    class Mat2DivisionNaNTests: public testing::TestWithParam<flcn::Mat2<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat2InvalidDivision, Mat2DivisionNaNTests,
                             ::testing::Values(flcn::Mat2<float>(flcn::constants::NaN, 3.0f, 3.0f, 3.0f),
                                               flcn::Mat2<float>(3.0f, flcn::constants::NaN, 3.0f, 3.0f),
                                               flcn::Mat2<float>(3.0f, 3.0f, flcn::constants::NaN, 3.0f),
                                               flcn::Mat2<float>(3.0f, 3.0f, 3.0f, flcn::constants::NaN),
                                               flcn::Mat2<float>(flcn::constants::NaN, flcn::constants::NaN,
                                                                flcn::constants::NaN, flcn::constants::NaN)));


    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat2 MAT(2, 4, 6, 8);

        /// @test Verify that Mat2 division operator returns a valid matrix at compile time.
        constexpr flcn::Mat2 DIV_OP_MAT = MAT / 2;
        static_assert(DIV_OP_MAT(0, 0) == 1);
        static_assert(DIV_OP_MAT(0, 1) == 2);
        static_assert(DIV_OP_MAT(1, 0) == 3);
        static_assert(DIV_OP_MAT(1, 1) == 4);


        /// @test Verify that Mat2 safeDiv returns a valid matrix at compile time.
        constexpr flcn::Mat2 SAFE_DIV_MAT = MAT.safeDiv(2);
        static_assert(SAFE_DIV_MAT(0, 0) == 1);
        static_assert(SAFE_DIV_MAT(0, 1) == 2);
        static_assert(SAFE_DIV_MAT(1, 0) == 3);
        static_assert(SAFE_DIV_MAT(1, 1) == 4);


        /// @test Verify that Mat2 safeDiv (static wrapper) returns a valid matrix at compile time.
        constexpr flcn::Mat2 SAFE_DIV_MAT_STATIC = flcn::Mat2<int>::safeDiv(MAT, 2);
        static_assert(SAFE_DIV_MAT_STATIC(0, 0) == 1);
        static_assert(SAFE_DIV_MAT_STATIC(0, 1) == 2);
        static_assert(SAFE_DIV_MAT_STATIC(1, 0) == 3);
        static_assert(SAFE_DIV_MAT_STATIC(1, 1) == 4);

        // Matrix Try Division
        // NOT available at compile time due to [out] parameter (OperationStatus).

    } // namespace static_tests

} // namespace




/**************************************
 *      DIVISION TESTS (RUNTIME)      *
 **************************************/

TYPED_TEST(Mat2DivisionTests, DivideOperator_ReturnsAValidMatrix)
{
    const flcn::Mat2 resultantMat = this->_matrix / this->_scalar;
    EXPECT_MAT_EQ(this->_expectedMatrix, resultantMat);
}


TYPED_TEST(Mat2DivisionTests, DivideEqualsOperator_PerformsElementWiseDivisionInPlace)
{
    flcn::Mat2 matrix = this->_matrix;
    matrix /= this->_scalar;

    EXPECT_MAT_EQ(this->_expectedMatrix, matrix);
}



/**************************************
 *         SAFE DIVISION TESTS        *
 **************************************/

TYPED_TEST(Mat2DivisionTests, SafeDiv_ReturnsAValidMatrix)
{
    const flcn::Mat2 resultantMat = this->_matrix.safeDiv(this->_scalar);
    EXPECT_MAT_EQ(this->_expectedMatrix, resultantMat);
}


TYPED_TEST(Mat2DivisionTests, SafeDiv_DivisionByZero_ReturnsIdentityMatrixByDefault)
{
    const flcn::Mat2 resultantMat = this->_matrix.safeDiv(TypeParam(0));
    EXPECT_MAT_IDENTITY(resultantMat);
}


TYPED_TEST(Mat2DivisionTests, SafeDiv_DivisionByZero_ReturnsPassedInFallbackMatrix)
{
    const flcn::Mat2 resultantMat = this->_matrix.safeDiv(TypeParam(0), flcn::Mat2<TypeParam>::zero());
    EXPECT_MAT_ZERO(resultantMat);
}


TEST_P(Mat2DivisionNaNTests, SafeDiv_ReturnsIdentityMatrixByDefault)
{
    const flcn::Mat2 resultantMat = GetParam().safeDiv(2.5);
    EXPECT_MAT_IDENTITY(resultantMat);
}


TEST_P(Mat2DivisionNaNTests, SafeDiv_ReturnsPassedInFallbackMatrix)
{
    const flcn::Mat2 resultantMat = GetParam().safeDiv(2.5, flcn::Mat2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(resultantMat);
}


TYPED_TEST(Mat2DivisionTests, StaticWrapper_SafeDiv_ReturnsAValidMatrix)
{
    const flcn::Mat2 resultantMat = flcn::Mat2<TypeParam>::safeDiv(this->_matrix, this->_scalar);
    EXPECT_MAT_EQ(this->_expectedMatrix, resultantMat);
}


TYPED_TEST(Mat2DivisionTests, StaticWrapper_SafeDiv_DivisionByZeroReturnsIdentityMatrixByDefault)
{
    const flcn::Mat2 resultantMat = flcn::Mat2<TypeParam>::safeDiv(this->_matrix, TypeParam(0));
    EXPECT_MAT_IDENTITY(resultantMat);
}


TYPED_TEST(Mat2DivisionTests, StaticWrapper_SafeDiv_DivisionByZeroReturnsPassedInFallbackMatrix)
{
    const flcn::Mat2 resultantMat =
        flcn::Mat2<TypeParam>::safeDiv(this->_matrix, TypeParam(0), flcn::Mat2<TypeParam>::zero());
    EXPECT_MAT_ZERO(resultantMat);
}


TEST_P(Mat2DivisionNaNTests, StaticWrapper_SafeDiv_ReturnsIdentityMatrixByDefault)
{
    using T                          = ParamType::value_type;
    const flcn::Mat2 resultantMat = flcn::Mat2<T>::safeDiv(GetParam(), 2.5);
    EXPECT_MAT_IDENTITY(resultantMat);
}


TEST_P(Mat2DivisionNaNTests, StaticWrapper_SafeDiv_ReturnsPassedInFallbackMatrix)
{
    using T                          = ParamType::value_type;
    const flcn::Mat2 resultantMat = flcn::Mat2<T>::safeDiv(GetParam(), 2.5, flcn::Mat2<T>::zero());
    EXPECT_MAT_ZERO(resultantMat);
}



/**************************************
 *         TRY DIVISION TESTS         *
 **************************************/

/**
 * @test Verify that dividing a matrix using @ref flcn::Mat2::tryDiv perform an element-wise divide
 *        returns a new matrix instance and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat2DivisionTests, TryDiv_ReturnsAValidMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat2 resultantMat = this->_matrix.tryDiv(this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, resultantMat);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that dividing a matrix by zero using @ref flcn::Mat2::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2DivisionTests, TryDiv_DivisionByZeroReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat2 resultantMat = this->_matrix.tryDiv(TypeParam(0), flag);

    EXPECT_MAT_IDENTITY(resultantMat);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a matrix by zero using @ref flcn::Mat2::tryDiv returns passed-in fallback
 *        and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2DivisionTests, TryDiv_DivisionByZeroReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat2 resultantMat = this->_matrix.tryDiv(TypeParam(0), flag, flcn::Mat2<TypeParam>::zero());

    EXPECT_MAT_ZERO(resultantMat);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a NaN matrix using @ref flcn::Mat2::tryDiv returns identity matrix
 *        by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2DivisionNaNTests, TryDiv_ReturnsIdentityMatrixByDefault)
{
    flcn::OperationStatus flag;
    const flcn::Mat2 resultantMat = GetParam().tryDiv(2.5, flag);
    EXPECT_MAT_IDENTITY(resultantMat);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix using @ref flcn::Mat2::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2DivisionNaNTests, TryDiv_ReturnsPassedInFallbackMatrix)
{
    flcn::OperationStatus flag;
    const flcn::Mat2 resultantMat = GetParam().tryDiv(2.5, flag, flcn::Mat2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(resultantMat);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix by zero using @ref flcn::Mat2::tryDiv
 *        returns set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2DivisionNaNTests, TryDiv_NaNOperandTakesPrecedenceOverZeroDivision)
{
    flcn::OperationStatus flag;
    [[maybe_unused]] const flcn::Mat2 resultantMat =
        GetParam().tryDiv(0, flag, flcn::Mat2<ParamType::value_type>::zero());
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a matrix using the static variant of @ref flcn::Mat2::tryDiv
 *        perform an element-wise divide, returns a new matrix instance
 *        and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat2DivisionTests, StaticWrapper_TryDiv_ReturnsAValidMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat2 resultantMat = flcn::Mat2<TypeParam>::tryDiv(this->_matrix, this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, resultantMat);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that dividing a matrix by zero using the static variant of @ref flcn::Mat2::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2DivisionTests, StaticWrapper_TryDiv_DivisionByZeroReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat2 resultantMat = flcn::Mat2<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag);
    EXPECT_MAT_IDENTITY(resultantMat);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a matrix by zero using the static variant of @ref flcn::Mat2::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2DivisionTests, StaticWrapper_TryDiv_DivisionByZeroReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat2 resultantMat =
        flcn::Mat2<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag, flcn::Mat2<TypeParam>::zero());
    EXPECT_MAT_ZERO(resultantMat);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a NaN matrix using the static variant of @ref flcn::Mat2::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2DivisionNaNTests, StaticWrapper_TryDiv_ReturnsIdentityMatrixByDefault)
{
    flcn::OperationStatus flag;
    using T                          = ParamType::value_type;
    const flcn::Mat2 resultantMat = flcn::Mat2<T>::tryDiv(GetParam(), 2.5, flag);
    EXPECT_MAT_IDENTITY(resultantMat);

    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix by zero using the static variant of @ref flcn::Mat2::tryDiv
 *        set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2DivisionNaNTests, StaticWrapper_TryDiv_NaNOperandTakesPrecedenceOverZeroDivision)
{
    flcn::OperationStatus flag;
    using T                                           = ParamType::value_type;
    [[maybe_unused]] const flcn::Mat2 resultantMat = flcn::Mat2<T>::tryDiv(GetParam(), T(0), flag);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix using the static variant of @ref flcn::Mat2::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2DivisionNaNTests, StaticWrapper_TryDiv_ReturnsPassedInFallback)
{
    flcn::OperationStatus flag;
    using T = ParamType::value_type;
    const flcn::Mat2 resultantMat =
        flcn::Mat2<T>::tryDiv(GetParam(), 2.5, flag, flcn::Mat2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(resultantMat);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/** @} */
