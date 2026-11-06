/**
 * @file DivisionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 18, 2026
 *
 * @brief Verify @ref flcn::Mat2x4 division logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2x4TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat2x4_Division
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2x4 Division.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */

    template <typename T>
    class Mat2x4DivisionTests: public ::testing::Test
    {
    protected:
        flcn::Mat2x4<T> _matrix;
        T _scalar;
        flcn::Mat2x4<T> _expectedMatrix;

        void SetUp() override
        {
            _matrix         = { flcn::CVec2{ T(7), T(3) }, flcn::CVec2{ T(1), T(6) }, flcn::CVec2{ T(3), T(9) },
                                flcn::CVec2{ T(0), T(24) } };
            _scalar         = T(3);
            _expectedMatrix = { flcn::CVec2{ T(2.333333333333333), T(1) }, flcn::CVec2{ T(0.3333333333333333), T(2) },
                                flcn::CVec2{ T(1), T(3) }, flcn::CVec2{ T(0), T(8) } };
        }
    };
    TYPED_TEST_SUITE(Mat2x4DivisionTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref flcn::Mat2x4 Division with NaN elements.
     */
    class NaNMat2x4DivisionTests: public ::testing::TestWithParam<flcn::Mat2x4<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat2x4DivisionTestSuite, NaNMat2x4DivisionTests,
        ::testing::Values(flcn::Mat2x4<float>(flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
                          flcn::Mat2x4<float>(3.0f, flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
                          flcn::Mat2x4<float>(3.0f, 3.0f, flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
                          flcn::Mat2x4<float>(3.0f, 3.0f, 3.0f, flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f),
                          flcn::Mat2x4<float>(3.0f, 3.0f, 3.0f, 3.0f, flcn::constants::NaN, 3.0f, 3.0f, 3.0f),
                          flcn::Mat2x4<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, flcn::constants::NaN, 3.0f, 3.0f),
                          flcn::Mat2x4<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, flcn::constants::NaN, 3.0f),
                          flcn::Mat2x4<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, flcn::constants::NaN),
                          flcn::Mat2x4<float>(flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
                                             flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
                                             flcn::constants::NaN, flcn::constants::NaN)));



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat2x4 MAT(2, 4, 6, 8, 10, 12, 14, 16);

        /// @test Verify that Mat2x4 division operator returns a valid matrix at compile time.
        constexpr flcn::Mat2x4 DIV_RESULT_1 = MAT / 2;
        static_assert(DIV_RESULT_1(0, 0) == 1);
        static_assert(DIV_RESULT_1(0, 1) == 2);
        static_assert(DIV_RESULT_1(0, 2) == 3);
        static_assert(DIV_RESULT_1(0, 3) == 4);
        static_assert(DIV_RESULT_1(1, 0) == 5);
        static_assert(DIV_RESULT_1(1, 1) == 6);
        static_assert(DIV_RESULT_1(1, 2) == 7);
        static_assert(DIV_RESULT_1(1, 3) == 8);


        /// @test Verify that Mat2x4 safeDiv returns a valid matrix at compile time.
        constexpr flcn::Mat2x4 DIV_RESULT_2 = MAT.safeDiv(2);
        static_assert(DIV_RESULT_2(0, 0) == 1);
        static_assert(DIV_RESULT_2(0, 1) == 2);
        static_assert(DIV_RESULT_2(0, 2) == 3);
        static_assert(DIV_RESULT_2(0, 3) == 4);
        static_assert(DIV_RESULT_2(1, 0) == 5);
        static_assert(DIV_RESULT_2(1, 1) == 6);
        static_assert(DIV_RESULT_2(1, 2) == 7);
        static_assert(DIV_RESULT_2(1, 3) == 8);

        /// @test Verify that Mat2x4 safeDiv (static wrapper) returns a valid matrix at compile time.
        constexpr flcn::Mat2x4 DIV_RESULT_3 = flcn::Mat2x4<int>::safeDiv(MAT, 2);
        static_assert(DIV_RESULT_3(0, 0) == 1);
        static_assert(DIV_RESULT_3(0, 1) == 2);
        static_assert(DIV_RESULT_3(0, 2) == 3);
        static_assert(DIV_RESULT_3(0, 3) == 4);
        static_assert(DIV_RESULT_3(1, 0) == 5);
        static_assert(DIV_RESULT_3(1, 1) == 6);
        static_assert(DIV_RESULT_3(1, 2) == 7);
        static_assert(DIV_RESULT_3(1, 3) == 8);

        // Matrix Try Division
        // NOT available at compile time due to [out] parameter (OperationStatus).

    } // namespace static_tests
} // namespace



/**************************************
 *      DIVISION TESTS (RUNTIME)      *
 **************************************/

TYPED_TEST(Mat2x4DivisionTests, DivideOperator_ReturnsAValidMatrix)
{
    const flcn::Mat2x4 inverseScaledMat = this->_matrix / this->_scalar;
    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}



TYPED_TEST(Mat2x4DivisionTests, DivideEqualsOperator_PerformsElementWiseDivisionInPlace)
{
    flcn::Mat2x4 matrix = this->_matrix;
    matrix /= this->_scalar;

    EXPECT_MAT_EQ(this->_expectedMatrix, matrix);
}



/**************************************
 *         SAFE DIVISION TESTS        *
 **************************************/

TYPED_TEST(Mat2x4DivisionTests, SafeDiv_ReturnsAValidMatrix)
{
    const flcn::Mat2x4 inverseScaledMat = this->_matrix.safeDiv(this->_scalar);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


TYPED_TEST(Mat2x4DivisionTests, SafeDiv_DivisionByZero_ReturnsZeroMatrixByDefault)
{
    const flcn::Mat2x4 inverseScaledMat = this->_matrix.safeDiv(TypeParam(0));
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TYPED_TEST(Mat2x4DivisionTests, SafeDiv_DivisionByZero_ReturnsPassedInFallback)
{
    const flcn::Mat2x4 inverseScaledMat = this->_matrix.safeDiv(TypeParam(0), flcn::Mat2x4<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TEST_P(NaNMat2x4DivisionTests, SafeDiv_ReturnsZeroMatrixByDefault)
{
    const flcn::Mat2x4 inverseScaledMat = GetParam().safeDiv(2.5);
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TEST_P(NaNMat2x4DivisionTests, SafeDiv_ReturnsPassedInFallback)
{
    const flcn::Mat2x4 inverseScaledMat = GetParam().safeDiv(2.5, flcn::Mat2x4<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TYPED_TEST(Mat2x4DivisionTests, StaticWrapper_SafeDiv_ReturnsAValidMatrix)
{
    const flcn::Mat2x4 inverseScaledMat = flcn::Mat2x4<TypeParam>::safeDiv(this->_matrix, this->_scalar);
    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


TYPED_TEST(Mat2x4DivisionTests, StaticWrapper_SafeDiv_DivisionByZero_ReturnsZeroMatrixByDefault)
{
    const flcn::Mat2x4 inverseScaledMat = flcn::Mat2x4<TypeParam>::safeDiv(this->_matrix, TypeParam(0));
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TYPED_TEST(Mat2x4DivisionTests, StaticWrapper_SafeDiv_DivisionByZeroReturnsPassedInFallback)
{
    const flcn::Mat2x4 inverseScaledMat =
        flcn::Mat2x4<TypeParam>::safeDiv(this->_matrix, TypeParam(0), flcn::Mat2x4<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TEST_P(NaNMat2x4DivisionTests, StaticWrapper_SafeDiv_ReturnsZeroMatrixByDefault)
{
    using T                            = ParamType::value_type;
    const flcn::Mat2x4 inverseScaledMat = flcn::Mat2x4<T>::safeDiv(GetParam(), 2.5);
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TEST_P(NaNMat2x4DivisionTests, StaticWrapper_SafeDiv_ReturnsPassedInFallback)
{
    using T                            = ParamType::value_type;
    const flcn::Mat2x4 inverseScaledMat = flcn::Mat2x4<T>::safeDiv(GetParam(), 2.5, flcn::Mat2x4<T>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}



/**************************************
 *         TRY DIVISION TESTS         *
 **************************************/

/**
 * @test Verify that dividing a matrix using @ref flcn::Mat2x4::tryDiv perform an element-wise divide
 *        returns a new matrix instance and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat2x4DivisionTests, TryDiv_ReturnsAValidMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat2x4 inverseScaledMat = this->_matrix.tryDiv(this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that dividing a matrix by zero using @ref flcn::Mat2x4::tryDiv
 *        returns zero matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2x4DivisionTests, TryDiv_DivisionByZero_ReturnsZeroMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat2x4 inverseScaledMat = this->_matrix.tryDiv(TypeParam(0), flag);

    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a matrix by zero using @ref flcn::Mat2x4::tryDiv returns passed-in fallback
 *        and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2x4DivisionTests, TryDiv_DivisionByZeroReturnsPassedInFallbackAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat2x4 inverseScaledMat = this->_matrix.tryDiv(TypeParam(0), flag, flcn::Mat2x4<TypeParam>::zero());

    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a NaN matrix using @ref flcn::Mat2x4::tryDiv returns zero matrix
 *        by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMat2x4DivisionTests, TryDiv_ReturnsZeroMatrixByDefault)
{
    flcn::OperationStatus flag;
    const flcn::Mat2x4 inverseScaledMat = GetParam().tryDiv(2.5, flag);
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix using @ref flcn::Mat2x4::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMat2x4DivisionTests, TryDiv_ReturnsPassedInFallback)
{
    flcn::OperationStatus flag;
    const flcn::Mat2x4 inverseScaledMat = GetParam().tryDiv(2.5, flag, flcn::Mat2x4<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix by zero using @ref flcn::Mat2x4::tryDiv
 *        returns set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMat2x4DivisionTests, TryDiv_NaNOperandTakesPrecedenceOverZeroDivision)
{
    flcn::OperationStatus flag;
    [[maybe_unused]] const flcn::Mat2x4 inverseScaledMat =
        GetParam().tryDiv(0, flag, flcn::Mat2x4<ParamType::value_type>::zero());
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a matrix using the static variant of @ref flcn::Mat2x4::tryDiv
 *        perform an element-wise divide, returns a new matrix instance
 *        and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat2x4DivisionTests, StaticWrapper_TryDiv_ReturnsAValidMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat2x4 inverseScaledMat = flcn::Mat2x4<TypeParam>::tryDiv(this->_matrix, this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that dividing a matrix by zero using the static variant of @ref flcn::Mat2x4::tryDiv
 *        returns zero matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2x4DivisionTests, StaticWrapper_TryDiv_DivisionByZero_ReturnsZeroMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat2x4 inverseScaledMat = flcn::Mat2x4<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag);
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a matrix by zero using the static variant of @ref flcn::Mat2x4::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat2x4DivisionTests, StaticWrapper_TryDiv_DivisionByZeroReturnsPassedInFallbackAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat2x4 inverseScaledMat =
        flcn::Mat2x4<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag, flcn::Mat2x4<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a NaN matrix using the static variant of @ref flcn::Mat2x4::tryDiv
 *        returns zero matrix by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMat2x4DivisionTests, StaticWrapper_TryDiv_ReturnsZeroMatrixByDefault)
{
    flcn::OperationStatus flag;
    using T                            = ParamType::value_type;
    const flcn::Mat2x4 inverseScaledMat = flcn::Mat2x4<T>::tryDiv(GetParam(), 2.5, flag);
    EXPECT_MAT_ZERO(inverseScaledMat);

    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix by zero using the static variant of @ref flcn::Mat2x4::tryDiv
 *        set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMat2x4DivisionTests, StaticWrapper_TryDiv_NaNOperandTakesPrecedenceOverZeroDivision)
{
    flcn::OperationStatus flag;
    using T                                             = ParamType::value_type;
    [[maybe_unused]] const flcn::Mat2x4 inverseScaledMat = flcn::Mat2x4<T>::tryDiv(GetParam(), T(0), flag);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix using the static variant of @ref flcn::Mat2x4::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMat2x4DivisionTests, StaticWrapper_TryDiv_ReturnsPassedInFallback)
{
    flcn::OperationStatus flag;
    using T = ParamType::value_type;
    const flcn::Mat2x4 inverseScaledMat =
        flcn::Mat2x4<T>::tryDiv(GetParam(), 2.5, flag, flcn::Mat2x4<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/** @} */
