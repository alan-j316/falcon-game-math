/**
 * @file MultiplicationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref flcn::Mat4x2 scalar multiplication logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4x2TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat4x2_Multiplication
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4x2 scalar multiplication.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat4x2ScalarMultiplicationTests: public ::testing::Test
    {
    protected:
        flcn::Mat4x2<T> _mat;
        T _scalar;
        flcn::Mat4x2<T> _expectedFloatingMat;
        flcn::Mat4x2<T> _expectedIntegralMat;

        void SetUp() override
        {
            _mat                 = { flcn::Vec4{ T(7), T(13), T(11), T(22) }, flcn::Vec4{ T(5), T(4), T(2), T(12) } };
            _scalar              = T(2.123456789123456);
            _expectedFloatingMat = {
                flcn::Vec4{ T(14.864197523864192), T(27.604938258604928), T(23.358024680358014), T(46.71604936071603) },
                flcn::Vec4{ T(10.61728394561728), T(8.493827156493824), T(4.246913578246912), T(25.481481469481473) }
            };
            _expectedIntegralMat = { flcn::Vec4{ T(14), T(26), T(22), T(44) }, flcn::Vec4{ T(10), T(8), T(4), T(24) } };
        }
    };
    TYPED_TEST_SUITE(Mat4x2ScalarMultiplicationTests, SupportedArithmeticTypes);


    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_test
    {
        constexpr flcn::Mat4x2 MAT1(1, 2, 3, 4, 5, 6, 7, 8);

        /// @test Verify that matrix * scalar multiplication returns 4D matrix at compile time.
        constexpr flcn::Mat4x2 BINARY_PRODUCT_1 = MAT1 * 2;
        static_assert(BINARY_PRODUCT_1(0, 0) == 2);
        static_assert(BINARY_PRODUCT_1(0, 1) == 4);
        static_assert(BINARY_PRODUCT_1(1, 0) == 6);
        static_assert(BINARY_PRODUCT_1(1, 1) == 8);
        static_assert(BINARY_PRODUCT_1(2, 0) == 10);
        static_assert(BINARY_PRODUCT_1(2, 1) == 12);
        static_assert(BINARY_PRODUCT_1(3, 0) == 14);
        static_assert(BINARY_PRODUCT_1(3, 1) == 16);


        /// @test Verify scalar * matrix multiplication returns 4D matrix at compile time.
        constexpr flcn::Mat4x2 BINARY_PRODUCT_2 = 2 * MAT1;
        static_assert(BINARY_PRODUCT_2(0, 0) == 2);
        static_assert(BINARY_PRODUCT_2(0, 1) == 4);
        static_assert(BINARY_PRODUCT_2(1, 0) == 6);
        static_assert(BINARY_PRODUCT_2(1, 1) == 8);
        static_assert(BINARY_PRODUCT_2(2, 0) == 10);
        static_assert(BINARY_PRODUCT_2(2, 1) == 12);
        static_assert(BINARY_PRODUCT_2(3, 0) == 14);
        static_assert(BINARY_PRODUCT_2(3, 1) == 16);

    } // namespace static_test
} // namespace



/**************************************
 *     SCALAR MULTIPLICATION TESTS    *
 **************************************/

TEST(Mat4x2ScalarMultiplicationTests, TimesOperator_ByZeroReturnsZeroMatrix)
{
    const flcn::Mat4x2 mat(3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f);

    const flcn::Mat4x2 product = mat * 0;

    EXPECT_MAT_ZERO(product);
}


TEST(Mat4x2ScalarMultiplicationTests, TimesOperator_ByOneReturnsOriginalMatrix)
{
    const flcn::Mat4x2 mat(3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f);

    const flcn::Mat4x2 product = mat * 1;

    EXPECT_MAT_EQ(mat, product);
}


TEST(Mat4x2ScalarMultiplicationTests, TimesOperator_ByNegativeScalarFlipsSigns)
{
    const flcn::Mat4x2 mat      = { 1.0f, -2.0f, -4.0f, 5.0f, 10.0f, -1.0f, -1.5f, 2.25f };
    const flcn::Mat4x2 expected = { -2.0f, 4.0f, 8.0f, -10.0f, -20.f, 2.0f, 3.0f, -4.5f };
    const float scalar         = -2.0f;

    const flcn::Mat4x2<float> product = mat * scalar;

    EXPECT_MAT_EQ(expected, product);
}


TYPED_TEST(Mat4x2ScalarMultiplicationTests, TimesOperator_ByScalarReturnsScaledMatrix)
{
    const flcn::Mat4x2 product = this->_mat * this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFloatingMat, product);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntegralMat, product);
    }
}


TYPED_TEST(Mat4x2ScalarMultiplicationTests, TimesOperator_ScalarTimesMatrixReturnsScaledMatrix)
{
    const flcn::Mat4x2 product = this->_scalar * this->_mat;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFloatingMat, product);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntegralMat, product);
    }
}


TYPED_TEST(Mat4x2ScalarMultiplicationTests, TimesEqualsOperator_MatrixTimesEqualScalarIsTheSameMatrixScaled)
{
    this->_mat *= this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFloatingMat, this->_mat);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntegralMat, this->_mat);
    }
}


TYPED_TEST(Mat4x2ScalarMultiplicationTests, TimesOperator_MixedType_PromotesType)
{
    const double scalar = 2.123456789123456;

    [[maybe_unused]] const flcn::Mat4x2 product = this->_mat * scalar;

    static_assert(std::is_same_v<typename decltype(product)::value_type, double>);
}


TEST(Mat4x2ScalarMultiplicationTests, TimesEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::Mat4x2 mat(3.0f, -1.0f, -12.0f, 14.0f, 12.0f, 3.2f, 2.1f, 0.75f);
    const double scalar = 5.0;
    mat *= scalar;

    static_assert(std::is_same_v<decltype(mat)::value_type, float>);
}


TEST(Mat4x2ScalarMultiplicationTests, TimesEqualsOperator_MixedType_EnsuresMinimalPrecisionLoss)
{
    flcn::Mat4x2 mat(3, -1, 10, 5, 50, 12, 0, 5);
    const double scalar = 2.5;
    const flcn::Mat4x2 expected(7, -2, 25, 12, 125, 30, 0, 12);

    mat *= scalar;

    EXPECT_MAT_EQ(expected, mat);
}

/** @} */
