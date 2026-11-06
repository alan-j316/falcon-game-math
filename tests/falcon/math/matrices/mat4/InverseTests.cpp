/**
 * @file InverseTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 09, 2026
 *
 * @brief Verify @ref flcn::Mat4 inverse logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat4x4_Inverse
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4 Inverse.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */

    template <typename T>
    class Mat4InverseTests: public testing::Test
    {
    protected:
        using Mag = flcn::Magnitude<T>;
        flcn::Mat4<T> _matrix;
        flcn::Mat4<Mag> _expectedInverse;

        void SetUp() override
        {
            _matrix          = { { T(3), T(1), T(8), T(4) },
                                 { T(3), T(7), T(4), T(2) },
                                 { T(6), T(1), T(2), T(1) },
                                 { T(3), T(1), T(6), T(2) } };
            _expectedInverse = {
                { Mag(-0.037878787878788), Mag(-0.022727272727273), Mag(0.196969696969697), Mag(0.0) },
                { Mag(-0.068181818181818), Mag(0.159090909090909), Mag(-0.045454545454545), Mag(0.0) },
                { Mag(-0.204545454545455), Mag(-0.022727272727273), Mag(-0.136363636363636), Mag(0.5) },
                { Mag(0.704545454545455), Mag(0.022727272727273), Mag(0.136363636363636), Mag(-1.0) }
            };
        }
    };
    TYPED_TEST_SUITE(Mat4InverseTests, SupportedSignedArithmeticTypes);



    /** @brief Test fixture for calculating @ref flcn::Mat4 inverse with singular matrices. */
    class Mat4InverseSingularTests: public testing::TestWithParam<flcn::Mat4<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat4SingularMatrixInverse, Mat4InverseSingularTests,
        ::testing::Values(flcn::Mat4{ flcn::Vec4{ 1.0f, 2.0f, 3.0f, 4.0f }, flcn::Vec4{ 1.0f, 2.0f, 3.0f, 4.0f },
                                     flcn::Vec4{ 7.0f, 8.0f, 9.0f, 12.0f }, flcn::Vec4{ 1.0f, 85.0f, 19.0f, 12.0f } },
                          flcn::Mat4{ flcn::Vec4{ 1.0f, 1.0f, 3.0f, 4.0f }, flcn::Vec4{ 2.0f, 2.0f, 3.0f, 4.0f },
                                     flcn::Vec4{ 3.0f, 3.0f, 9.0f, 12.0f }, flcn::Vec4{ 4.0f, 4.0f, 31.6f, 2.0f } },
                          flcn::Mat4{ flcn::Vec4{ 0.0f, 0.0f, 0.0f, 0.0f }, flcn::Vec4{ 2.0f, 2.0f, 3.0f, 4.0f },
                                     flcn::Vec4{ 3.0f, 3.0f, 9.0f, 12.0f }, flcn::Vec4{ 4.0f, 4.0f, 31.6f, 2.0f } },
                          flcn::Mat4{ flcn::Vec4{ 0.0f, 1.0f, 3.0f, 4.0f }, flcn::Vec4{ 0.0f, 2.0f, 3.0f, 4.0f },
                                     flcn::Vec4{ 0.0f, 3.0f, 9.0f, 12.0f }, flcn::Vec4{ 0.0f, 4.0f, 31.6f, 2.0f } },
                          flcn::Mat4{ flcn::Vec4{ 1.0f, 2.0f, 3.0f, 4.0f }, flcn::Vec4{ 2.0f, 4.0f, 6.0f, 8.0f },
                                     flcn::Vec4{ 3.0f, 3.0f, 9.0f, 12.0f }, flcn::Vec4{ 4.0f, 4.0f, 31.6f, 2.0f } },
                          flcn::Mat4{ flcn::Vec4{ 1.0f, 2.0f, 3.0f, 4.0f }, flcn::Vec4{ 2.0f, 4.0f, 5.0f, 10.0f },
                                     flcn::Vec4{ 3.0f, 6.0f, 9.0f, 12.0f }, flcn::Vec4{ 4.0f, 8.0f, 31.6f, 2.0f } }));


    /** @brief Test fixture for @ref flcn::Mat4 inverse with NaN elements. */
    class Mat4InverseNaNTests: public testing::TestWithParam<flcn::Mat4<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat4NaNMatrixInverse, Mat4InverseNaNTests,
                             ::testing::Values(flcn::Mat4<float>{ flcn::constants::NaN, 3.0f, 3.0f, 3.0f },
                                               flcn::Mat4<float>{ 3.0f, flcn::constants::NaN, 3.0f, 3.0f },
                                               flcn::Mat4<float>{ 3.0f, 3.0f, flcn::constants::NaN, 3.0f },
                                               flcn::Mat4<float>{ 3.0f, 3.0f, 3.0f, flcn::constants::NaN },
                                               flcn::Mat4<float>{ flcn::constants::NaN, flcn::constants::NaN,
                                                                 flcn::constants::NaN, flcn::constants::NaN }));


    /**************************************
     *           STATIC TESTS             *
     **************************************/

    /** @test Verify that matrix inverse is available at compile time. */
    namespace static_tests
    {
        constexpr flcn::Mat4 mat(1.0f, -1.0f, 0.0f, -2.0f, 2.0f, -1.0f, -2.0f, -6.0f, 0.0f, -1.0f, 3.0f, 3.0f, -2.0f,
                                2.0f, -2.0f, 3.0f);

        /// @test Verify matrix inverse returns a valid matrix at compile time.
        constexpr flcn::Mat4 invMat = mat.inverse();
        static_assert(invMat(0, 0) - -9.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMat(0, 1) - 7.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMat(0, 2) - 6.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMat(0, 3) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMat(1, 0) - -6.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMat(1, 1) - 3.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMat(1, 2) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMat(1, 3) - 0.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMat(2, 0) - 0.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMat(2, 1) - -1.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMat(2, 2) - -1.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMat(2, 3) - -1.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMat(3, 0) - -2.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMat(3, 1) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMat(3, 2) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMat(3, 3) - 1.0f <= flcn::Config::FLOAT_EPSILON);

        /// @test Verify matrix inverse (static wrapper) returns a valid matrix at compile time.
        constexpr flcn::Mat4 invMatS = flcn::Mat4<float>::inverse(mat);
        static_assert(invMatS(0, 0) - -9.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMatS(0, 1) - 7.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMatS(0, 2) - 6.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMatS(0, 3) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMatS(1, 0) - -6.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMatS(1, 1) - 3.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMatS(1, 2) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMatS(1, 3) - 0.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMatS(2, 0) - 0.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMatS(2, 1) - -1.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMatS(2, 2) - -1.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMatS(2, 3) - -1.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMatS(3, 0) - -2.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMatS(3, 1) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMatS(3, 2) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(invMatS(3, 3) - 1.0f <= flcn::Config::FLOAT_EPSILON);


        /// @test Verify matrix safe inverse returns a valid matrix at compile time.
        constexpr flcn::Mat4 safeInvMat = mat.safeInverse();
        static_assert(safeInvMat(0, 0) - -9.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMat(0, 1) - 7.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMat(0, 2) - 6.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMat(0, 3) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMat(1, 0) - -6.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMat(1, 1) - 3.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMat(1, 2) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMat(1, 3) - 0.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMat(2, 0) - 0.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMat(2, 1) - -1.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMat(2, 2) - -1.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMat(2, 3) - -1.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMat(3, 0) - -2.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMat(3, 1) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMat(3, 2) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMat(3, 3) - 1.0f <= flcn::Config::FLOAT_EPSILON);


        /// @test Verify matrix safe inverse (static wrapper) returns a valid matrix at compile time.
        constexpr flcn::Mat4 safeInvMatS = flcn::Mat4<float>::safeInverseOf(mat);
        static_assert(safeInvMatS(0, 0) - -9.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMatS(0, 1) - 7.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMatS(0, 2) - 6.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMatS(0, 3) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMatS(1, 0) - -6.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMatS(1, 1) - 3.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMatS(1, 2) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMatS(1, 3) - 0.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMatS(2, 0) - 0.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMatS(2, 1) - -1.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMatS(2, 2) - -1.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMatS(2, 3) - -1.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMatS(3, 0) - -2.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMatS(3, 1) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMatS(3, 2) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(safeInvMatS(3, 3) - 1.0f <= flcn::Config::FLOAT_EPSILON);

    } // namespace static_tests
} // namespace



/**************************************
 *              INVERSE               *
 **************************************/

TYPED_TEST(Mat4InverseTests, ReturnsInverseMatrix) { EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.inverse()); }


TYPED_TEST(Mat4InverseTests, InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = this->_matrix.inverse();
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


TYPED_TEST(Mat4InverseTests, StaticWrapper_ReturnsInverseMatrix)
{ EXPECT_MAT_EQ(this->_expectedInverse, flcn::Mat4<TypeParam>::inverse(this->_matrix)); }


TYPED_TEST(Mat4InverseTests, StaticWrapper_InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = flcn::Mat4<TypeParam>::inverse(this->_matrix);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}



/**************************************
 *          SAFE INVERSE TESTS        *
 **************************************/

TYPED_TEST(Mat4InverseTests, SafeInverse_ReturnsInverseMatrix)
{ EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.safeInverse()); }


TYPED_TEST(Mat4InverseTests, SafeInverse_InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = this->_matrix.safeInverse();
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


TEST_P(Mat4InverseSingularTests, SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.safeInverse());
}


TEST_P(Mat4InverseSingularTests, SafeInverse_ReturnsPassedInFallbackMatrix)
{
    const auto& inverseMatrix = GetParam().safeInverse(flcn::Mat4<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
}


TEST_P(Mat4InverseNaNTests, SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.safeInverse());
}


TEST_P(Mat4InverseNaNTests, SafeInverse_ReturnsPassedInFallbackMatrix)
{
    const auto& inverseMatrix = GetParam().safeInverse(flcn::Mat4<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
}


TYPED_TEST(Mat4InverseTests, StaticWrapper_SafeInverse_ReturnsInverseMatrix)
{ EXPECT_MAT_EQ(this->_expectedInverse, flcn::Mat4<TypeParam>::safeInverseOf(this->_matrix)); }


TYPED_TEST(Mat4InverseTests, StaticWrapper_SafeInverse_InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = flcn::Mat4<TypeParam>::safeInverseOf(this->_matrix);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


TEST_P(Mat4InverseSingularTests, StaticWrapper_SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::safeInverseOf(matrix));
}


TEST_P(Mat4InverseSingularTests, StaticWrapper_SafeInverse_ReturnsPassedInFallbackMatrix)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_ZERO(ParamType::safeInverseOf(matrix, flcn::Mat4<ParamType::value_type>::zero()));
}


TEST_P(Mat4InverseNaNTests, StaticWrapper_SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::safeInverseOf(matrix));
}


TEST_P(Mat4InverseNaNTests, StaticWrapper_SafeInverse_ReturnsPassedInFallbackMatrix)
{
    const auto& inverseMatrix = ParamType::safeInverseOf(GetParam(), flcn::Mat4<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
}


/**************************************
 *          TRY INVERSE TESTS         *
 **************************************/

/**
 * @test Verify that inverting a matrix using @ref flcn::Mat4::tryInverse exchanges row and column elements and
 *        returns a new matrix and sets status flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat4InverseTests, TryInverse_ReturnsInverseMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.tryInverse(flag));
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that inverse of matrix (using @ref flcn::Mat4::tryInverse) times itself is an identity matrix and
 *        sets status flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat4InverseTests, TryInverse_InverseTimesMatrixReturnsIdentityMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto invMatrix = this->_matrix.tryInverse(flag);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that inverting a singular matrix using @ref flcn::Mat4::tryInverse
 *        returns identity matrix by default and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(Mat4InverseSingularTests, TryInverse_ReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.tryInverse(flag));
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that inverting a singular matrix using @ref flcn::Mat4::tryInverse
 *        returns passed-in fallback and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(Mat4InverseSingularTests, TryInverse_ReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& inverseMatrix = GetParam().tryInverse(flag, flcn::Mat4<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that inverting a NaN matrix using @ref flcn::Mat4::tryInverse
 *        returns identity matrix by default and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat4InverseNaNTests, TryInverse_ReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.tryInverse(flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that inverting a NaN matrix using @ref flcn::Mat4::tryInverse returns passed-in fallback
 *        and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat4InverseNaNTests, TryInverse_ReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& inverseMatrix = GetParam().tryInverse(flag, flcn::Mat4<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that inverting a matrix using static variant of @ref flcn::Mat4::tryInverse exchanges row and
 *        column elements and returns a new matrix and sets status flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat4InverseTests, StaticWrapper_TryInverse_ReturnsInverseMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    EXPECT_MAT_EQ(this->_expectedInverse, flcn::Mat4<TypeParam>::tryInverseOf(this->_matrix, flag));
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that inverse of matrix (using static variant of @ref flcn::Mat4::tryInverse) times itself is an
 *        identity matrix and sets status flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat4InverseTests, StaticWrapper_TryInverse_InverseTimesMatrixReturnsIdentityMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto invMatrix = flcn::Mat4<TypeParam>::tryInverseOf(this->_matrix, flag);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that inverting a singular matrix using static variant of @ref flcn::Mat4::tryInverseOf
 *         returns identity matrix by default and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(Mat4InverseSingularTests, StaticWrapper_TryInverse_ReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::tryInverseOf(matrix, flag));
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that inverting a singular matrix using static variant of @ref flcn::Mat4::tryInverseOf
 *         returns passed-in fallback and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(Mat4InverseSingularTests, StaticWrapper_TryInverse_ReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_ZERO(ParamType::tryInverseOf(matrix, flag, flcn::Mat4<ParamType::value_type>::zero()));
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that inverting a NaN matrix using static variant of @ref flcn::Mat4::tryInverse
 *        returns identity matrix by default and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat4InverseNaNTests, StaticWrapper_TryInverse_ReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::tryInverseOf(matrix, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}



/**
 * @test Verify that inverting a NaN matrix using static variant of @ref flcn::Mat4::tryInverse
 *        returns passed-in fallback and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat4InverseNaNTests, StaticWrapper_TryInverse_ReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& inverseMatrix = ParamType::tryInverseOf(GetParam(), flag, flcn::Mat4<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/** @} */
