/**
 * @file InverseTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 14, 2026
 *
 * @brief Verify @ref flcn::Mat2 inverse logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat2x2_Inverse
 * @{
 */

namespace
{

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2 Inverse.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2InverseTests: public testing::Test
    {
    protected:
        using Mag = flcn::Magnitude<T>;
        flcn::Mat2<T> _matrix;
        flcn::Mat2<Mag> _expectedInverse;

        void SetUp() override
        {
            _matrix          = { flcn::CVec2{ T(5), T(4) }, flcn::CVec2{ T(2), T(3) } };
            _expectedInverse = { flcn::CVec2{ Mag(0.42857142857142855), Mag(-0.5714285714285714) },
                                 flcn::CVec2{ Mag(-0.2857142857142857), Mag(0.7142857142857143) } };
        }
    };
    TYPED_TEST_SUITE(Mat2InverseTests, SupportedSignedArithmeticTypes);



    /** @brief Test fixture for calculating @ref flcn::Mat2 inverse with singular matrices. */
    class Mat2InverseSingularTests: public testing::TestWithParam<flcn::Mat2<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat2SingularMatrixInverse, Mat2InverseSingularTests,
                             ::testing::Values(flcn::Mat2{ flcn::CVec2{ 1.0f, 2.0f }, flcn::CVec2{ 1.0f, 2.0f } },
                                               flcn::Mat2{ flcn::CVec2{ 2.0f, 2.0f }, flcn::CVec2{ 2.0f, 2.0f } },
                                               flcn::Mat2{ flcn::CVec2{ 3.0f, 2.0f }, flcn::CVec2{ 6.0f, 4.0f } },
                                               flcn::Mat2{ flcn::CVec2{ 0.0f, 0.0f }, flcn::CVec2{ 4.0f, 5.0f } },
                                               flcn::Mat2{ flcn::CVec2{ 0.0f, 3.0f }, flcn::CVec2{ 0.0f, 5.0f } }));



    /** @brief Test fixture for @ref flcn::Mat2 inverse with NaN elements. */
    class Mat2InverseNaNTests: public testing::TestWithParam<flcn::Mat2<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat2NaNMatrixInverse, Mat2InverseNaNTests,
                             ::testing::Values(flcn::Mat2<float>(flcn::constants::NaN, 3.0f, 3.0f, 3.0f),
                                               flcn::Mat2<float>(3.0f, flcn::constants::NaN, 3.0f, 3.0f),
                                               flcn::Mat2<float>(3.0f, 3.0f, flcn::constants::NaN, 3.0f),
                                               flcn::Mat2<float>(3.0f, 3.0f, 3.0f, flcn::constants::NaN),
                                               flcn::Mat2<float>(flcn::constants::NaN, flcn::constants::NaN,
                                                                flcn::constants::NaN, flcn::constants::NaN)));



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    /** s@test Verify that matrix inverse is available at compile time. */
    namespace static_tests
    {
        constexpr flcn::Mat2 MAT(1.0f, 2.0f, 3.0f, 4.0f);

        /// @test Verify matrix inverse returns a valid matrix at compile time.
        constexpr flcn::Mat2 INV_MAT = MAT.inverse();
        static_assert(INV_MAT(0, 0) == -2.0f);
        static_assert(INV_MAT(0, 1) == 1.0f);
        static_assert(INV_MAT(1, 0) == 1.5f);
        static_assert(INV_MAT(1, 1) == -0.5f);

        /// @test Verify matrix inverse (static wrapper) returns a valid matrix at compile time.
        constexpr flcn::Mat2 INV_MAT_STATIC = flcn::Mat2<float>::inverse(MAT);
        static_assert(INV_MAT_STATIC(0, 0) == -2.0f);
        static_assert(INV_MAT_STATIC(0, 1) == 1.0f);
        static_assert(INV_MAT_STATIC(1, 0) == 1.5f);
        static_assert(INV_MAT_STATIC(1, 1) == -0.5f);

        /// @test Verify matrix inverse returns a valid matrix at compile time.
        constexpr flcn::Mat2 SAFE_INV_MAT = MAT.safeInverse();
        static_assert(SAFE_INV_MAT(0, 0) == -2.0f);
        static_assert(SAFE_INV_MAT(0, 1) == 1.0f);
        static_assert(SAFE_INV_MAT(1, 0) == 1.5f);
        static_assert(SAFE_INV_MAT(1, 1) == -0.5f);

        /// @test Verify matrix inverse (static wrapper) returns a valid matrix at compile time.
        constexpr flcn::Mat2 SAFE_INV_MAT_STATIC = flcn::Mat2<float>::safeInverseOf(MAT);
        static_assert(SAFE_INV_MAT_STATIC(0, 0) == -2.0f);
        static_assert(SAFE_INV_MAT_STATIC(0, 1) == 1.0f);
        static_assert(SAFE_INV_MAT_STATIC(1, 0) == 1.5f);
        static_assert(SAFE_INV_MAT_STATIC(1, 1) == -0.5f);

    } // namespace static_tests

} // namespace



/**************************************
 *              INVERSE               *
 **************************************/

TYPED_TEST(Mat2InverseTests, Inverse_NonSingularMatrix_ReturnsValidInverseMatrix)
{ EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.inverse()); }


TYPED_TEST(Mat2InverseTests, Inverse_InverseMatrixTimesOriginalMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = this->_matrix.inverse();
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


TYPED_TEST(Mat2InverseTests, StaticWrapper_Inverse_NonSingularMatrix_ReturnsValidInverseMatrix)
{ EXPECT_MAT_EQ(this->_expectedInverse, flcn::Mat2<TypeParam>::inverse(this->_matrix)); }


TYPED_TEST(Mat2InverseTests, StaticWrapper_Inverse_InverseMatrixTimesOriginalMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = flcn::Mat2<TypeParam>::inverse(this->_matrix);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}



/**************************************
 *             SAFE INVERSE           *
 **************************************/

TYPED_TEST(Mat2InverseTests, SafeInverse_NonSingularMatrix_ReturnsValidInverseMatrix)
{ EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.safeInverse()); }


TYPED_TEST(Mat2InverseTests, SafeInverse_InverseMatrixTimesOriginalMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = this->_matrix.safeInverse();
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


TEST_P(Mat2InverseSingularTests, SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.safeInverse());
}


TEST_P(Mat2InverseSingularTests, SafeInverse_ReturnsPassedInFallbackMatrix)
{
    const auto& inverseMatrix = GetParam().safeInverse(flcn::Mat2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
}


TEST_P(Mat2InverseNaNTests, SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.safeInverse());
}


TEST_P(Mat2InverseNaNTests, SafeInverse_ReturnsPassedInFallbackMatrix)
{
    const auto& inverseMatrix = GetParam().safeInverse(flcn::Mat2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
}


TYPED_TEST(Mat2InverseTests, StaticWrapper_SafeInverse_ReturnsInverseMatrix)
{ EXPECT_MAT_EQ(this->_expectedInverse, flcn::Mat2<TypeParam>::safeInverseOf(this->_matrix)); }


TYPED_TEST(Mat2InverseTests, StaticWrapper_SafeInverse_InverseMatrixTimesOriginalMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = flcn::Mat2<TypeParam>::safeInverseOf(this->_matrix);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


TEST_P(Mat2InverseSingularTests, StaticWrapper_SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::safeInverseOf(matrix));
}


TEST_P(Mat2InverseSingularTests, StaticWrapper_SafeInverse_ReturnsPassedInFallbackMatrix)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_ZERO(ParamType::safeInverseOf(matrix, flcn::Mat2<ParamType::value_type>::zero()));
}


TEST_P(Mat2InverseNaNTests, StaticWrapper_SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::safeInverseOf(matrix));
}


TEST_P(Mat2InverseNaNTests, StaticWrapper_SafeInverse_ReturnsPassedInFallbackMatrix)
{
    const auto& inverseMatrix = ParamType::safeInverseOf(GetParam(), flcn::Mat2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
}



/**************************************
 *            TRY INVERSE             *
 **************************************/

/**
 * @test Verify that inverting a matrix using @ref flcn::Mat2::tryInverse returns a new matrix
 *        that when multiplied with the original matrix returns an identity matrix and sets status flag to
 *        @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat2InverseTests, TryInverse_ReturnsInverseMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.tryInverse(flag));
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that inverse of matrix (using @ref flcn::Mat2::tryInverse) times itself is an identity matrix and
 *        sets status flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat2InverseTests, TryInverse_InverseMatrixTimesOriginalMatrixReturnsIdentityMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto invMatrix = this->_matrix.tryInverse(flag);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that inverting a singular matrix using @ref flcn::Mat2::tryInverse
 *        returns identity matrix by default and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(Mat2InverseSingularTests, TryInverse_ReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.tryInverse(flag));
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that inverting a singular matrix using @ref flcn::Mat2::tryInverse
 *        returns passed-in fallback and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(Mat2InverseSingularTests, TryInverse_ReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& inverseMatrix = GetParam().tryInverse(flag, flcn::Mat2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that inverting a NaN matrix using @ref flcn::Mat2::tryInverse
 *        returns identity matrix by default and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2InverseNaNTests, TryInverse_ReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.tryInverse(flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that inverting a NaN matrix using @ref flcn::Mat2::tryInverse returns passed-in fallback
 *        and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2InverseNaNTests, TryInverse_ReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& inverseMatrix = GetParam().tryInverse(flag, flcn::Mat2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that inverting a matrix using static variant of @ref flcn::Mat2::tryInverse returns a new matrix
 *        that when multiplied with the original matrix returns an identity matrix and sets status flag to
 *        @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat2InverseTests, StaticWrapper_TryInverse_ReturnsInverseMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    EXPECT_MAT_EQ(this->_expectedInverse, flcn::Mat2<TypeParam>::tryInverseOf(this->_matrix, flag));
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that inverse of matrix (using static variant of @ref flcn::Mat2::tryInverse) times itself is an
 *        identity matrix and sets status flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat2InverseTests,
           StaticWrapper_TryInverse_InverseMatrixTimesOriginalMatrixReturnsIdentityMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto invMatrix = flcn::Mat2<TypeParam>::tryInverseOf(this->_matrix, flag);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that inverting a singular matrix using static variant of @ref flcn::Mat2::tryInverseOf
 *        returns identity matrix by default and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(Mat2InverseSingularTests, StaticWrapper_TryInverse_ReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::tryInverseOf(matrix, flag));
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that inverting a singular matrix using static variant of @ref flcn::Mat2::tryInverseOf
 *        returns passed-in fallback and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(Mat2InverseSingularTests, StaticWrapper_TryInverse_ReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_ZERO(ParamType::tryInverseOf(matrix, flag, flcn::Mat2<ParamType::value_type>::zero()));
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that inverting a NaN matrix using static variant of @ref flcn::Mat2::tryInverse
 *        returns identity matrix by default and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2InverseNaNTests, StaticWrapper_TryInverse_ReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::tryInverseOf(matrix, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that inverting a NaN matrix using static variant of @ref flcn::Mat2::tryInverse
 *        returns passed-in fallback and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2InverseNaNTests, StaticWrapper_TryInverse_ReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& inverseMatrix = ParamType::tryInverseOf(GetParam(), flag, flcn::Mat2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/** @} */
