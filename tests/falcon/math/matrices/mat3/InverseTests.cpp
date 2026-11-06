/**
 * @file InverseTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 28, 2026
 *
 * @brief Verify @ref flcn::Mat3 inverse logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat3x3_Inverse
 * @{
 */

namespace
{

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat3 Inverse.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat3InverseTests: public testing::Test
    {
    protected:
        using Mag = flcn::Magnitude<T>;
        flcn::Mat3<T> _matrix;
        flcn::Mat3<Mag> _expectedInverse;

        void SetUp() override
        {
            _matrix          = { { T(3), T(1), T(8) }, { T(3), T(9), T(3) }, { T(5), T(6), T(1) } };
            _expectedInverse = { { Mag(0.038961038961039), Mag(-0.203463203463203), Mag(0.298701298701299) },
                                 { Mag(-0.051948051948052), Mag(0.16017316017316), Mag(-0.064935064935065) },
                                 { Mag(0.116883116883117), Mag(0.056277056277056), Mag(-0.103896103896104) } };
        }
    };
    TYPED_TEST_SUITE(Mat3InverseTests, SupportedSignedArithmeticTypes);



    /** @brief Test fixture for calculating @ref flcn::Mat3 inverse with singular matrices. */
    class Mat3InverseSingularTests: public testing::TestWithParam<flcn::Mat3<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat3SingularMatrixInverse, Mat3InverseSingularTests,
        ::testing::Values(
            flcn::Mat3{ flcn::Vec3{ 1.0f, 2.0f, 3.0f }, flcn::Vec3{ 1.0f, 2.0f, 3.0f }, flcn::Vec3{ 7.0f, 8.0f, 9.0f } },
            flcn::Mat3{ flcn::Vec3{ 1.0f, 1.0f, 5.0f }, flcn::Vec3{ 2.0f, 2.0f, 3.0f }, flcn::Vec3{ 3.0f, 3.0f, 9.0f } },
            flcn::Mat3{ flcn::Vec3{ 0.0f, 0.0f, 0.0f }, flcn::Vec3{ 1.0f, 2.0f, 3.0f }, flcn::Vec3{ 1.0f, 8.0f, 9.0f } },
            flcn::Mat3{ flcn::Vec3{ 0.0f, 5.0f, 1.0f }, flcn::Vec3{ 0.0f, 2.0f, 3.0f }, flcn::Vec3{ 0.0f, 8.0f, 9.0f } },
            flcn::Mat3{ flcn::Vec3{ 1.0f, 2.0f, 3.0f }, flcn::Vec3{ 2.0f, 4.0f, 6.0f }, flcn::Vec3{ 7.0f, 8.0f, 9.0f } },
            flcn::Mat3{ flcn::Vec3{ 1.0f, 2.0f, 1.0f }, flcn::Vec3{ 2.0f, 4.0f, 3.0f }, flcn::Vec3{ 3.0f, 6.0f, 9.0f } }));



    /** @brief Test fixture for @ref flcn::Mat3 inverse with NaN elements. */
    class Mat3InverseNaNTests: public testing::TestWithParam<flcn::Mat3<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat3NaNMatrixInverse, Mat3InverseNaNTests,
                             ::testing::Values(flcn::Mat3<float>(flcn::constants::NaN, 3.0f, 3.0f),
                                               flcn::Mat3<float>(3.0f, flcn::constants::NaN, 3.0f),
                                               flcn::Mat3<float>(3.0f, 3.0f, flcn::constants::NaN),
                                               flcn::Mat3<float>(flcn::constants::NaN, flcn::constants::NaN,
                                                                flcn::constants::NaN)));



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    /** @test Verify that matrix inverse is available at compile time. */
    namespace static_tests
    {
        constexpr flcn::Mat3 MAT(1.0f, 2.0f, 3.0f, 0.0f, 1.0f, 4.0f, 5.0f, 6.0f, 0.0f);


        /// @test Verify matrix inverse returns a valid matrix at compile time.
        constexpr flcn::Mat3 INV_MAT = MAT.inverse();
        static_assert(INV_MAT(0, 0) - -24.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(INV_MAT(0, 1) - 18.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(INV_MAT(0, 2) - 5.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(INV_MAT(1, 0) - 20.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(INV_MAT(1, 1) - -15.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(INV_MAT(1, 2) - -4.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(INV_MAT(2, 0) - -5.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(INV_MAT(2, 1) - 4.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(INV_MAT(2, 2) - 1.0f <= flcn::Config::FLOAT_EPSILON);

        /// @test Verify matrix inverse (static wrapper) returns a valid matrix at compile time.
        constexpr flcn::Mat3 INV_MAT_S = flcn::Mat3<float>::inverse(MAT);
        static_assert(INV_MAT_S(0, 0) - -24.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(INV_MAT_S(0, 1) - 18.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(INV_MAT_S(0, 2) - 5.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(INV_MAT_S(1, 0) - 20.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(INV_MAT_S(1, 1) - -15.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(INV_MAT_S(1, 2) - -4.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(INV_MAT_S(2, 0) - -5.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(INV_MAT_S(2, 1) - 4.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(INV_MAT_S(2, 2) - 1.0f <= flcn::Config::FLOAT_EPSILON);


        /// @test Verify matrix safe inverse returns a valid matrix at compile time.
        constexpr flcn::Mat3 SAFE_INV_MAT = MAT.safeInverse();
        static_assert(SAFE_INV_MAT(0, 0) - -24.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(SAFE_INV_MAT(0, 1) - 18.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(SAFE_INV_MAT(0, 2) - 5.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(SAFE_INV_MAT(1, 0) - 20.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(SAFE_INV_MAT(1, 1) - -15.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(SAFE_INV_MAT(1, 2) - -4.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(SAFE_INV_MAT(2, 0) - -5.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(SAFE_INV_MAT(2, 1) - 4.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(SAFE_INV_MAT(2, 2) - 1.0f <= flcn::Config::FLOAT_EPSILON);

        /// @test Verify matrix safe inverse (static wrapper) returns a valid matrix at compile time.
        constexpr flcn::Mat3 SAFE_INV_MAT_S = flcn::Mat3<float>::safeInverseOf(MAT);
        static_assert(SAFE_INV_MAT_S(0, 0) - -24.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(SAFE_INV_MAT_S(0, 1) - 18.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(SAFE_INV_MAT_S(0, 2) - 5.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(SAFE_INV_MAT_S(1, 0) - 20.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(SAFE_INV_MAT_S(1, 1) - -15.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(SAFE_INV_MAT_S(1, 2) - -4.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(SAFE_INV_MAT_S(2, 0) - -5.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(SAFE_INV_MAT_S(2, 1) - 4.0f <= flcn::Config::FLOAT_EPSILON);
        static_assert(SAFE_INV_MAT_S(2, 2) - 1.0f <= flcn::Config::FLOAT_EPSILON);
    } // namespace static_tests
} // namespace



/**************************************
 *              INVERSE               *
 **************************************/

TYPED_TEST(Mat3InverseTests, ReturnsInverseMatrix) { EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.inverse()); }


TYPED_TEST(Mat3InverseTests, InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = this->_matrix.inverse();
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


TYPED_TEST(Mat3InverseTests, StaticWrapper_ReturnsInverseMatrix)
{ EXPECT_MAT_EQ(this->_expectedInverse, flcn::Mat3<TypeParam>::inverse(this->_matrix)); }


TYPED_TEST(Mat3InverseTests, StaticWrapper_InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = flcn::Mat3<TypeParam>::inverse(this->_matrix);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


/**************************************
 *            SAFE INVERSE            *
 **************************************/

TYPED_TEST(Mat3InverseTests, SafeInverse_ReturnsInverseMatrix)
{ EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.safeInverse()); }


TYPED_TEST(Mat3InverseTests, SafeInverse_InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = this->_matrix.safeInverse();
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


TEST_P(Mat3InverseSingularTests, SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.safeInverse());
}


TEST_P(Mat3InverseSingularTests, SafeInverse_ReturnsPassedInFallbackMatrix)
{
    const auto& inverseMatrix = GetParam().safeInverse(flcn::Mat3<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
}


TEST_P(Mat3InverseNaNTests, SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.safeInverse());
}


TEST_P(Mat3InverseNaNTests, SafeInverse_ReturnsPassedInFallbackMatrix)
{
    const auto& inverseMatrix = GetParam().safeInverse(flcn::Mat3<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
}


TYPED_TEST(Mat3InverseTests, StaticWrapper_SafeInverse_ReturnsInverseMatrix)
{ EXPECT_MAT_EQ(this->_expectedInverse, flcn::Mat3<TypeParam>::safeInverseOf(this->_matrix)); }


TYPED_TEST(Mat3InverseTests, StaticWrapper_SafeInverse_InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = flcn::Mat3<TypeParam>::safeInverseOf(this->_matrix);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}



TEST_P(Mat3InverseSingularTests, StaticWrapper_SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::safeInverseOf(matrix));
}


TEST_P(Mat3InverseSingularTests, StaticWrapper_SafeInverse_ReturnsPassedInFallbackMatrix)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_ZERO(ParamType::safeInverseOf(matrix, flcn::Mat3<ParamType::value_type>::zero()));
}


TEST_P(Mat3InverseNaNTests, StaticWrapper_SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::safeInverseOf(matrix));
}


TEST_P(Mat3InverseNaNTests, StaticWrapper_SafeInverse_ReturnsPassedInFallbackMatrix)
{
    const auto& inverseMatrix = ParamType::safeInverseOf(GetParam(), flcn::Mat3<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
}



/**************************************
 *            TRY INVERSE             *
 **************************************/

/**
 * @test Verify that inverting a matrix using @ref flcn::Mat3::tryInverse returns a new matrix
 *        that when multiplied with the original matrix returns an identity matrix and sets status flag to
 *        @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat3InverseTests, TryInverse_ReturnsInverseMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.tryInverse(flag));
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that inverse of matrix (using @ref flcn::Mat3::tryInverse) times itself is an identity matrix and
 *        sets status flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat3InverseTests, TryInverse_InverseTimesMatrixReturnsIdentityMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto invMatrix = this->_matrix.tryInverse(flag);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that inverting a singular matrix using @ref flcn::Mat3::tryInverse
 *        returns identity matrix by default and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(Mat3InverseSingularTests, TryInverse_ReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.tryInverse(flag));
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that inverting a singular matrix using @ref flcn::Mat3::tryInverse
 *        returns passed-in fallback and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(Mat3InverseSingularTests, TryInverse_ReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& inverseMatrix = GetParam().tryInverse(flag, flcn::Mat3<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that inverting a NaN matrix using @ref flcn::Mat3::tryInverse
 *        returns identity matrix by default and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat3InverseNaNTests, TryInverse_ReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.tryInverse(flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that inverting a NaN matrix using @ref flcn::Mat3::tryInverse returns passed-in fallback
 *        and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat3InverseNaNTests, TryInverse_ReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& inverseMatrix = GetParam().tryInverse(flag, flcn::Mat3<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that inverting a matrix using static variant of @ref flcn::Mat3::tryInverse returns a new matrix
 *        that when multiplied with the original matrix returns an identity matrix and sets status flag to
 *        @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat3InverseTests, StaticWrapper_TryInverse_ReturnsInverseMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    EXPECT_MAT_EQ(this->_expectedInverse, flcn::Mat3<TypeParam>::tryInverseOf(this->_matrix, flag));
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that inverse of matrix (using static variant of @ref flcn::Mat3::tryInverse) times itself is an
 *        identity matrix and sets status flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat3InverseTests, StaticWrapper_TryInverse_InverseTimesMatrixReturnsIdentityMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto invMatrix = flcn::Mat3<TypeParam>::tryInverseOf(this->_matrix, flag);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that inverting a singular matrix using static variant of @ref flcn::Mat3::tryInverseOf
 *         returns identity matrix by default and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(Mat3InverseSingularTests, StaticWrapper_TryInverse_ReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::tryInverseOf(matrix, flag));
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that inverting a singular matrix using static variant of @ref flcn::Mat3::tryInverseOf
 *         returns passed-in fallback and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(Mat3InverseSingularTests, StaticWrapper_TryInverse_ReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_ZERO(ParamType::tryInverseOf(matrix, flag, flcn::Mat3<ParamType::value_type>::zero()));
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that inverting a NaN matrix using static variant of @ref flcn::Mat3::tryInverse
 *        returns identity matrix by default and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat3InverseNaNTests, StaticWrapper_TryInverse_ReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::tryInverseOf(matrix, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that inverting a NaN matrix using static variant of @ref flcn::Mat3::tryInverse
 *        returns passed-in fallback and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat3InverseNaNTests, StaticWrapper_TryInverse_ReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& inverseMatrix = ParamType::tryInverseOf(GetParam(), flag, flcn::Mat3<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/** @} */
