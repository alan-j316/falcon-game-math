/**
 * @file DivisionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 17, 2026
 *
 * @brief Verify @ref flcn::Mat2x3x3 division logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2x3TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat2x3_Division
 * @{
 */

namespace
{

    /**************************************
     *               SETUP                *
     **************************************/
    /**
     * @brief Test fixture for @ref flcn::Mat2x3x3 Division.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2x3DivisionTests: public testing::Test
    {
    protected:
        flcn::Mat2x3<T> _matrix;
        T _scalar;
        flcn::Mat2x3<T> _expectedMatrix;

        void SetUp() override
        {
            _matrix         = { flcn::CVec2{ T(7), T(3) }, flcn::CVec2{ T(1), T(6) }, flcn::CVec2{ T(3), T(9) } };
            _scalar         = T(3);
            _expectedMatrix = { flcn::CVec2{ T(2.333333333333333), T(1) }, flcn::CVec2{ T(0.3333333333333333), T(2) },
                                flcn::CVec2{ T(1), T(3) } };
        }
    };
    TYPED_TEST_SUITE(Mat2x3DivisionTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref flcn::Mat2x3x3 Division with NaN elements.
     */
    class Mat2x3DivisionNaNTests: public ::testing::TestWithParam<flcn::Mat2x3<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat2InvalidDivision, Mat2x3DivisionNaNTests,
                             ::testing::Values(flcn::Mat2x3<float>(flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
                                               flcn::Mat2x3<float>(3.0f, flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f),
                                               flcn::Mat2x3<float>(3.0f, 3.0f, flcn::constants::NaN, 3.0f, 3.0f, 3.0f),
                                               flcn::Mat2x3<float>(3.0f, 3.0f, 3.0f, flcn::constants::NaN, 3.0f, 3.0f),
                                               flcn::Mat2x3<float>(3.0f, 3.0f, 3.0f, 3.0f, flcn::constants::NaN, 3.0f),
                                               flcn::Mat2x3<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, flcn::constants::NaN),
                                               flcn::Mat2x3<float>(flcn::constants::NaN, flcn::constants::NaN,
                                                                  flcn::constants::NaN, flcn::constants::NaN,
                                                                  flcn::constants::NaN, flcn::constants::NaN)));

    

    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat2x3 MAT(2, 4, 6, 8, 10, 12);


        /// @test Verify that Mat2x3 division operator returns a valid matrix at compile time.
        constexpr flcn::Mat2x3 DIV_OP_MAT = MAT / 2;
        static_assert(DIV_OP_MAT(0, 0) == 1);
        static_assert(DIV_OP_MAT(0, 1) == 2);
        static_assert(DIV_OP_MAT(0, 2) == 3);
        static_assert(DIV_OP_MAT(1, 0) == 4);
        static_assert(DIV_OP_MAT(1, 1) == 5);
        static_assert(DIV_OP_MAT(1, 2) == 6);


        /// @test Verify that Mat2x3 safeDiv returns a valid matrix at compile time.
        constexpr flcn::Mat2x3 SAFE_DIV_MAT = MAT.safeDiv(2);
        static_assert(SAFE_DIV_MAT(0, 0) == 1);
        static_assert(SAFE_DIV_MAT(0, 1) == 2);
        static_assert(SAFE_DIV_MAT(0, 2) == 3);
        static_assert(SAFE_DIV_MAT(1, 0) == 4);
        static_assert(SAFE_DIV_MAT(1, 1) == 5);
        static_assert(SAFE_DIV_MAT(1, 2) == 6);


        /// @test Verify that Mat2x3 safeDiv (static wrapper) returns a valid matrix at compile time.
        constexpr flcn::Mat2x3 SAFE_DIV_MAT_STATIC = flcn::Mat2x3<int>::safeDiv(MAT, 2);
        static_assert(SAFE_DIV_MAT_STATIC(0, 0) == 1);
        static_assert(SAFE_DIV_MAT_STATIC(0, 1) == 2);
        static_assert(SAFE_DIV_MAT_STATIC(0, 2) == 3);
        static_assert(SAFE_DIV_MAT_STATIC(1, 0) == 4);
        static_assert(SAFE_DIV_MAT_STATIC(1, 1) == 5);
        static_assert(SAFE_DIV_MAT_STATIC(1, 2) == 6);

        // Matrix Try Division
        // NOT available at compile time due to [out] parameter (OperationStatus).

    } // namespace static_tests

} // namespace




/**************************************
 *      DIVISION TESTS (RUNTIME)      *
 **************************************/

TYPED_TEST(Mat2x3DivisionTests, DivideOperator_ReturnsAValidMatrix)
{
    const flcn::Mat2x3 resultantMat = this->_matrix / this->_scalar;

    EXPECT_MAT_EQ(this->_expectedMatrix, resultantMat);
}


TYPED_TEST(Mat2x3DivisionTests, DivideEqualsOperator_PerformsElementWiseDivisionInPlace)
{
    flcn::Mat2x3 matrix = this->_matrix;
    matrix /= this->_scalar;

    EXPECT_MAT_EQ(this->_expectedMatrix, matrix);
}



/**************************************
 *         SAFE DIVISION TESTS        *
 **************************************/

TYPED_TEST(Mat2x3DivisionTests, SafeDiv_ReturnsAValidMatrix)
{
    const flcn::Mat2x3 resultantMat = this->_matrix.safeDiv(this->_scalar);
    EXPECT_MAT_EQ(this->_expectedMatrix, resultantMat);
}


TYPED_TEST(Mat2x3DivisionTests, SafeDiv_DivisionByZero_ReturnsZeroMatrixByDefault)
{
    const flcn::Mat2x3 resultantMat = this->_matrix.safeDiv(TypeParam(0));
    EXPECT_MAT_ZERO(resultantMat);
}


TYPED_TEST(Mat2x3DivisionTests, SafeDiv_DivisionByZero_ReturnsPassedInFallbackMatrix)
{
    const flcn::Mat2x3 resultantMat = this->_matrix.safeDiv(TypeParam(0), flcn::Mat2x3<TypeParam>::zero());
    EXPECT_MAT_ZERO(resultantMat);
}


TEST_P(Mat2x3DivisionNaNTests, SafeDiv_ReturnsZeroMatrixByDefault)
{
    const flcn::Mat2x3 resultantMat = GetParam().safeDiv(2.5);
    EXPECT_MAT_ZERO(resultantMat);
}


TEST_P(Mat2x3DivisionNaNTests, SafeDiv_ReturnsPassedInFallbackMatrix)
{
    const flcn::Mat2x3 resultantMat = GetParam().safeDiv(2.5, flcn::Mat2x3<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(resultantMat);
}


TYPED_TEST(Mat2x3DivisionTests, StaticWrapper_SafeDiv_ReturnsAValidMatrix)
{
    const flcn::Mat2x3 resultantMat = flcn::Mat2x3<TypeParam>::safeDiv(this->_matrix, this->_scalar);
    EXPECT_MAT_EQ(this->_expectedMatrix, resultantMat);
}


TYPED_TEST(Mat2x3DivisionTests, StaticWrapper_SafeDiv_DivisionByZeroReturnsZeroMatrixByDefault)
{
    const flcn::Mat2x3 resultantMat = flcn::Mat2x3<TypeParam>::safeDiv(this->_matrix, TypeParam(0));
    EXPECT_MAT_ZERO(resultantMat);
}


TYPED_TEST(Mat2x3DivisionTests, StaticWrapper_SafeDiv_DivisionByZeroReturnsPassedInFallbackMatrix)
{
    const flcn::Mat2x3 resultantMat =
        flcn::Mat2x3<TypeParam>::safeDiv(this->_matrix, TypeParam(0), flcn::Mat2x3<TypeParam>::zero());
    EXPECT_MAT_ZERO(resultantMat);
}


TEST_P(Mat2x3DivisionNaNTests, StaticWrapper_SafeDiv_ReturnsZeroMatrixByDefault)
{
    using T                          = ParamType::value_type;
    const flcn::Mat2x3 resultantMat = flcn::Mat2x3<T>::safeDiv(GetParam(), 2.5);
    EXPECT_MAT_ZERO(resultantMat);
}


TEST_P(Mat2x3DivisionNaNTests, StaticWrapper_SafeDiv_ReturnsPassedInFallbackMatrix)
{
    using T                          = ParamType::value_type;
    const flcn::Mat2x3 resultantMat = flcn::Mat2x3<T>::safeDiv(GetParam(), 2.5, flcn::Mat2x3<T>::zero());
    EXPECT_MAT_ZERO(resultantMat);
}



/**************************************
 *         TRY DIVISION TESTS         *
 **************************************/

/**
 * @test Verify that dividing a matrix using @ref flcn::Mat2x3::tryDiv perform an element-wise divide
 *        returns a new matrix instance and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat2x3DivisionTests, TryDiv_ReturnsAValidMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat2x3 resultantMat = this->_matrix.tryDiv(this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, resultantMat);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that dividing a matrix by zero using @ref flcn::Mat2x3::tryDiv
 *        returns zero matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2x3DivisionTests, TryDiv_DivisionByZeroReturnsZeroMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat2x3 resultantMat = this->_matrix.tryDiv(TypeParam(0), flag);

    EXPECT_MAT_ZERO(resultantMat);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a matrix by zero using @ref flcn::Mat2x3::tryDiv returns passed-in fallback
 *        and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2x3DivisionTests, TryDiv_DivisionByZeroReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat2x3 resultantMat = this->_matrix.tryDiv(TypeParam(0), flag, flcn::Mat2x3<TypeParam>::zero());

    EXPECT_MAT_ZERO(resultantMat);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a NaN matrix using @ref flcn::Mat2x3::tryDiv returns zero matrix
 *        by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2x3DivisionNaNTests, TryDiv_ReturnsZeroMatrixByDefault)
{
    flcn::OperationStatus flag;
    const flcn::Mat2x3 resultantMat = GetParam().tryDiv(2.5, flag);
    EXPECT_MAT_ZERO(resultantMat);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix using @ref flcn::Mat2x3::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2x3DivisionNaNTests, TryDiv_ReturnsPassedInFallbackMatrix)
{
    flcn::OperationStatus flag;
    const flcn::Mat2x3 resultantMat = GetParam().tryDiv(2.5, flag, flcn::Mat2x3<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(resultantMat);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix by zero using @ref flcn::Mat2x3::tryDiv
 *        returns set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2x3DivisionNaNTests, TryDiv_NaNOperandTakesPrecedenceOverZeroDivision)
{
    flcn::OperationStatus flag;
    [[maybe_unused]] const flcn::Mat2x3 resultantMat =
        GetParam().tryDiv(0, flag, flcn::Mat2x3<ParamType::value_type>::zero());
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a matrix using the static variant of @ref flcn::Mat2x3::tryDiv
 *        perform an element-wise divide, returns a new matrix instance
 *        and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat2x3DivisionTests, StaticWrapper_TryDiv_ReturnsAValidMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat2x3 resultantMat = flcn::Mat2x3<TypeParam>::tryDiv(this->_matrix, this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, resultantMat);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that dividing a matrix by zero using the static variant of @ref flcn::Mat2x3::tryDiv
 *        returns zero matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2x3DivisionTests, StaticWrapper_TryDiv_DivisionByZeroReturnsZeroMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat2x3 resultantMat = flcn::Mat2x3<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag);
    EXPECT_MAT_ZERO(resultantMat);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a matrix by zero using the static variant of @ref flcn::Mat2x3::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2x3DivisionTests, StaticWrapper_TryDiv_DivisionByZeroReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat2x3 resultantMat =
        flcn::Mat2x3<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag, flcn::Mat2x3<TypeParam>::zero());
    EXPECT_MAT_ZERO(resultantMat);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a NaN matrix using the static variant of @ref flcn::Mat2x3::tryDiv
 *        returns zero matrix by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2x3DivisionNaNTests, StaticWrapper_TryDiv_ReturnsZeroMatrixByDefault)
{
    flcn::OperationStatus flag;
    using T                          = ParamType::value_type;
    const flcn::Mat2x3 resultantMat = flcn::Mat2x3<T>::tryDiv(GetParam(), 2.5, flag);
    EXPECT_MAT_ZERO(resultantMat);

    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix by zero using the static variant of @ref flcn::Mat2x3::tryDiv
 *        set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2x3DivisionNaNTests, StaticWrapper_TryDiv_NaNOperandTakesPrecedenceOverZeroDivision)
{
    flcn::OperationStatus flag;
    using T                                           = ParamType::value_type;
    [[maybe_unused]] const flcn::Mat2x3 resultantMat = flcn::Mat2x3<T>::tryDiv(GetParam(), T(0), flag);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix using the static variant of @ref flcn::Mat2x3::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2x3DivisionNaNTests, StaticWrapper_TryDiv_ReturnsPassedInFallback)
{
    flcn::OperationStatus flag;
    using T = ParamType::value_type;
    const flcn::Mat2x3 resultantMat =
        flcn::Mat2x3<T>::tryDiv(GetParam(), 2.5, flag, flcn::Mat2x3<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(resultantMat);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}
/** @} */
