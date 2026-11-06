/**
 * @file DivisionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 07, 2026
 *
 * @brief Verify @ref flcn::Mat4 division logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat4x4_Division
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4 Division.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat4DivisionTests: public testing::Test
    {
    protected:
        flcn::Mat4<T> _matrix;
        T _scalar;
        flcn::Mat4<T> _expectedMatrix;


        void SetUp() override
        {
            _matrix         = { { T(17), T(13), T(15), T(12) },
                                { T(11), T(16), T(35), T(101) },
                                { T(27), T(44), T(56), T(23) },
                                { T(5), T(6), T(11), T(31) } };
            _scalar         = T(7);
            _expectedMatrix = {
                { T(2.428571428571428), T(1.857142857142857), T(2.142857142857143), T(1.714285714285714) },
                { T(1.571428571428571), T(2.285714285714286), T(5.0), T(14.428571428571429) },
                { T(3.857142857142857), T(6.285714285714286), T(8.0), T(3.285714285714286) },
                { T(0.714285714285714), T(0.857142857142857), T(1.571428571428571), T(4.428571428571429) },
            };
        }
    };
    TYPED_TEST_SUITE(Mat4DivisionTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref flcn::Mat4 Division with NaN elements.
     */
    class Mat4DivisionNaNTests: public testing::TestWithParam<flcn::Mat4<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat4InvalidDivision, Mat4DivisionNaNTests,
                             ::testing::Values(flcn::Mat4<float>{ flcn::constants::NaN, 3.0f, 3.0f, 3.0f },
                                               flcn::Mat4<float>{ 3.0f, flcn::constants::NaN, 3.0f, 3.0f },
                                               flcn::Mat4<float>{ 3.0f, 3.0f, flcn::constants::NaN, 3.0f },
                                               flcn::Mat4<float>{ 3.0f, 3.0f, 3.0f, flcn::constants::NaN },
                                               flcn::Mat4<float>{ flcn::constants::NaN, flcn::constants::NaN,
                                                                 flcn::constants::NaN, flcn::constants::NaN }));



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat4 MAT(2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32);

        /// @test Verify that Mat4 division operator returns a valid matrix at compile time.
        constexpr flcn::Mat4 DIV_RESULT_1 = MAT / 2;
        static_assert(DIV_RESULT_1(0, 0) == 1);
        static_assert(DIV_RESULT_1(0, 1) == 2);
        static_assert(DIV_RESULT_1(0, 2) == 3);
        static_assert(DIV_RESULT_1(0, 3) == 4);
        static_assert(DIV_RESULT_1(1, 0) == 5);
        static_assert(DIV_RESULT_1(1, 1) == 6);
        static_assert(DIV_RESULT_1(1, 2) == 7);
        static_assert(DIV_RESULT_1(1, 3) == 8);
        static_assert(DIV_RESULT_1(2, 0) == 9);
        static_assert(DIV_RESULT_1(2, 1) == 10);
        static_assert(DIV_RESULT_1(2, 2) == 11);
        static_assert(DIV_RESULT_1(2, 3) == 12);
        static_assert(DIV_RESULT_1(3, 0) == 13);
        static_assert(DIV_RESULT_1(3, 1) == 14);
        static_assert(DIV_RESULT_1(3, 2) == 15);
        static_assert(DIV_RESULT_1(3, 3) == 16);


        /// @test Verify that Mat4 safeDiv returns a valid matrix at compile time.
        constexpr flcn::Mat4 DIV_RESULT_2 = MAT.safeDiv(2);
        static_assert(DIV_RESULT_2(0, 0) == 1);
        static_assert(DIV_RESULT_2(0, 1) == 2);
        static_assert(DIV_RESULT_2(0, 2) == 3);
        static_assert(DIV_RESULT_2(0, 3) == 4);
        static_assert(DIV_RESULT_2(1, 0) == 5);
        static_assert(DIV_RESULT_2(1, 1) == 6);
        static_assert(DIV_RESULT_2(1, 2) == 7);
        static_assert(DIV_RESULT_2(1, 3) == 8);
        static_assert(DIV_RESULT_2(2, 0) == 9);
        static_assert(DIV_RESULT_2(2, 1) == 10);
        static_assert(DIV_RESULT_2(2, 2) == 11);
        static_assert(DIV_RESULT_2(2, 3) == 12);
        static_assert(DIV_RESULT_2(3, 0) == 13);
        static_assert(DIV_RESULT_2(3, 1) == 14);
        static_assert(DIV_RESULT_2(3, 2) == 15);
        static_assert(DIV_RESULT_2(3, 3) == 16);


        /// @test Verify that Mat4 safeDiv (static wrapper) returns a valid matrix at compile time.
        constexpr flcn::Mat4 DIV_RESULT_3 = flcn::Mat4<int>::safeDiv(MAT, 2);
        static_assert(DIV_RESULT_3(0, 0) == 1);
        static_assert(DIV_RESULT_3(0, 1) == 2);
        static_assert(DIV_RESULT_3(0, 2) == 3);
        static_assert(DIV_RESULT_3(0, 3) == 4);
        static_assert(DIV_RESULT_3(1, 0) == 5);
        static_assert(DIV_RESULT_3(1, 1) == 6);
        static_assert(DIV_RESULT_3(1, 2) == 7);
        static_assert(DIV_RESULT_3(1, 3) == 8);
        static_assert(DIV_RESULT_3(2, 0) == 9);
        static_assert(DIV_RESULT_3(2, 1) == 10);
        static_assert(DIV_RESULT_3(2, 2) == 11);
        static_assert(DIV_RESULT_3(2, 3) == 12);
        static_assert(DIV_RESULT_3(3, 0) == 13);
        static_assert(DIV_RESULT_3(3, 1) == 14);
        static_assert(DIV_RESULT_3(3, 2) == 15);
        static_assert(DIV_RESULT_3(3, 3) == 16);


        // Matrix Try Division
        // NOT available at compile time due to [out] parameter (OperationStatus).

    } // namespace static_tests
} // namespace



/**************************************
 *      DIVISION TESTS (RUNTIME)      *
 **************************************/

TYPED_TEST(Mat4DivisionTests, DivideOperator_ReturnsAValidMatrix)
{
    const flcn::Mat4 inverseScaledMat = this->_matrix / this->_scalar;

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


TYPED_TEST(Mat4DivisionTests, DivideEqualsOperator_PerformsElementWiseDivisionInPlace)
{
    flcn::Mat4 matrix = this->_matrix;
    matrix /= this->_scalar;

    EXPECT_MAT_EQ(this->_expectedMatrix, matrix);
}


/**************************************
 *         SAFE DIVISION TESTS        *
 **************************************/

TYPED_TEST(Mat4DivisionTests, SafeDiv_ReturnsAValidMatrix)
{
    const flcn::Mat4 inverseScaledMat = this->_matrix.safeDiv(this->_scalar);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


TYPED_TEST(Mat4DivisionTests, SafeDiv_DivisionByZeroReturnsIdentityMatrixByDefault)
{
    const flcn::Mat4 inverseScaledMat = this->_matrix.safeDiv(TypeParam(0));
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


TYPED_TEST(Mat4DivisionTests, SafeDiv_DivisionByZeroReturnsPassedInFallback)
{
    const flcn::Mat4 inverseScaledMat = this->_matrix.safeDiv(TypeParam(0), flcn::Mat4<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TEST_P(Mat4DivisionNaNTests, SafeDiv_ReturnsIdentityMatrixByDefault)
{
    const flcn::Mat4 inverseScaledMat = GetParam().safeDiv(2.5);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


TEST_P(Mat4DivisionNaNTests, SafeDiv_ReturnsPassedInFallback)
{
    const flcn::Mat4 inverseScaledMat = GetParam().safeDiv(2.5, flcn::Mat4<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TYPED_TEST(Mat4DivisionTests, StaticWrapper_SafeDiv_ReturnsAValidMatrix)
{
    const flcn::Mat4 inverseScaledMat = flcn::Mat4<TypeParam>::safeDiv(this->_matrix, this->_scalar);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


TYPED_TEST(Mat4DivisionTests, StaticWrapper_SafeDiv_DivisionByZeroReturnsIdentityMatrixByDefault)
{
    const flcn::Mat4 inverseScaledMat = flcn::Mat4<TypeParam>::safeDiv(this->_matrix, TypeParam(0));
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


TYPED_TEST(Mat4DivisionTests, StaticWrapper_SafeDiv_DivisionByZeroReturnsPassedInFallback)
{
    const flcn::Mat4 inverseScaledMat =
        flcn::Mat4<TypeParam>::safeDiv(this->_matrix, TypeParam(0), flcn::Mat4<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}


TEST_P(Mat4DivisionNaNTests, StaticWrapper_SafeDiv_ReturnsIdentityMatrixByDefault)
{
    using T                          = ParamType::value_type;
    const flcn::Mat4 inverseScaledMat = flcn::Mat4<T>::safeDiv(GetParam(), 2.5);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
}


TEST_P(Mat4DivisionNaNTests, StaticWrapper_SafeDiv_ReturnsPassedInFallback)
{
    using T                          = ParamType::value_type;
    const flcn::Mat4 inverseScaledMat = flcn::Mat4<T>::safeDiv(GetParam(), 2.5, flcn::Mat4<T>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
}



/**************************************
 *         TRY DIVISION TESTS         *
 **************************************/

/**
 * @test Verify that dividing a matrix using @ref flcn::Mat4::tryDiv perform an element-wise divide
 *        returns a new matrix instance and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat4DivisionTests, TryDiv_ReturnsAValidMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat4 inverseScaledMat = this->_matrix.tryDiv(this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that dividing a matrix by zero using @ref flcn::Mat4::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat4DivisionTests, TryDiv_DivisionByZeroReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat4 inverseScaledMat = this->_matrix.tryDiv(TypeParam(0), flag);

    EXPECT_MAT_IDENTITY(inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a matrix by zero using @ref flcn::Mat4::tryDiv returns passed-in fallback
 *        and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat4DivisionTests, TryDiv_DivisionByZeroReturnsPassedInFallbackAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat4 inverseScaledMat = this->_matrix.tryDiv(TypeParam(0), flag, flcn::Mat4<TypeParam>::zero());

    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a NaN matrix using @ref flcn::Mat4::tryDiv returns identity matrix
 *        by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat4DivisionNaNTests, TryDiv_ReturnsIdentityMatrixByDefault)
{
    flcn::OperationStatus flag;
    const flcn::Mat4 inverseScaledMat = GetParam().tryDiv(2.5, flag);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix using @ref flcn::Mat4::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat4DivisionNaNTests, TryDiv_ReturnsPassedInFallback)
{
    flcn::OperationStatus flag;
    const flcn::Mat4 inverseScaledMat = GetParam().tryDiv(2.5, flag, flcn::Mat4<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix by zero using @ref flcn::Mat4::tryDiv
 *        returns set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat4DivisionNaNTests, TryDiv_NaNOperandTakesPrecedenceOverZeroDivision)
{
    flcn::OperationStatus flag;
    [[maybe_unused]] const flcn::Mat4 inverseScaledMat =
        GetParam().tryDiv(0, flag, flcn::Mat4<ParamType::value_type>::zero());
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a matrix using the static variant of @ref flcn::Mat4::tryDiv
 *        perform an element-wise divide, returns a new matrix instance
 *        and set flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat4DivisionTests, StaticWrapper_TryDiv_ReturnsAValidMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat4 inverseScaledMat = flcn::Mat4<TypeParam>::tryDiv(this->_matrix, this->_scalar, flag);

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that dividing a matrix by zero using the static variant of @ref flcn::Mat4::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat4DivisionTests, StaticWrapper_TryDiv_DivisionByZeroReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat4 inverseScaledMat = flcn::Mat4<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag);
    EXPECT_MAT_IDENTITY(inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a matrix by zero using the static variant of @ref flcn::Mat4::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Mat4DivisionTests, StaticWrapper_TryDiv_DivisionByZeroReturnsPassedInFallbackAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Mat4 inverseScaledMat =
        flcn::Mat4<TypeParam>::tryDiv(this->_matrix, TypeParam(0), flag, flcn::Mat4<TypeParam>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a NaN matrix using the static variant of @ref flcn::Mat4::tryDiv
 *        returns identity matrix by default and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat4DivisionNaNTests, StaticWrapper_TryDiv_ReturnsIdentityMatrixByDefault)
{
    flcn::OperationStatus flag;
    using T                          = ParamType::value_type;
    const flcn::Mat4 inverseScaledMat = flcn::Mat4<T>::tryDiv(GetParam(), 2.5, flag);
    EXPECT_MAT_IDENTITY(inverseScaledMat);

    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix by zero using the static variant of @ref flcn::Mat4::tryDiv
 *        set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat4DivisionNaNTests, StaticWrapper_TryDiv_NaNOperandTakesPrecedenceOverZeroDivision)
{
    flcn::OperationStatus flag;
    using T                                           = ParamType::value_type;
    [[maybe_unused]] const flcn::Mat4 inverseScaledMat = flcn::Mat4<T>::tryDiv(GetParam(), static_cast<T>(0), flag);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a NaN matrix using the static variant of @ref flcn::Mat4::tryDiv
 *        returns passed-in fallback and set flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat4DivisionNaNTests, StaticWrapper_TryDiv_ReturnsPassedInFallback)
{
    flcn::OperationStatus flag;
    using T = ParamType::value_type;
    const flcn::Mat4 inverseScaledMat =
        flcn::Mat4<T>::tryDiv(GetParam(), 2.5, flag, flcn::Mat4<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseScaledMat);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/** @} */
