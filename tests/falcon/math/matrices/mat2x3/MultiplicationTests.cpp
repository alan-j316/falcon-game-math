/**
 * @file MultiplicationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 17, 2026
 *
 * @brief Verify @ref flcn::Mat2x3 scalar multiplication logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2x3TestSetup.h"

/**
 * @addtogroup T_FALCON_Mat2x3_Multiplication
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2 scalar multiplication.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat2x3ScalarMultiplicationTests: public ::testing::Test
    {
    protected:
        flcn::Mat2x3<T> _mat;
        T _scalar;
        flcn::Mat2x3<T> _expectedFloatingMat;
        flcn::Mat2x3<T> _expectedIntegralMat;



        void SetUp() override
        {
            _mat                 = { flcn::CVec2{ T(7), T(13) }, flcn::CVec2{ T(5), T(4) }, flcn::CVec2{ T(11), T(2) } };
            _scalar              = T(2.123456789123456);
            _expectedFloatingMat = { flcn::CVec2{ T(14.864197523864192), T(27.604938258604928) },
                                     flcn::CVec2{ T(10.61728394561728), T(8.493827156493824) },
                                     flcn::CVec2{ T(23.358024680358014), T(4.246913578246912) } };
            _expectedIntegralMat = { flcn::CVec2{ T(14), T(26) }, flcn::CVec2{ T(10), T(8) }, flcn::CVec2{ T(22), T(4) } };
        }
    };
    TYPED_TEST_SUITE(Mat2x3ScalarMultiplicationTests, SupportedArithmeticTypes);


    /**************************************
     *                                    *
     *            STATIC TESTS            *
     *                                    *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat2x3 MAT1(1, 2, 3, 4, 5, 6);

        /// @test Verify that matrix * scalar multiplication returns 2x3 matrix at compile time.
        constexpr flcn::Mat2x3 BINARY_PRODUCT_1 = MAT1 * 2;
        static_assert(BINARY_PRODUCT_1(0, 0) == 2);
        static_assert(BINARY_PRODUCT_1(0, 1) == 4);
        static_assert(BINARY_PRODUCT_1(0, 2) == 6);
        static_assert(BINARY_PRODUCT_1(1, 0) == 8);
        static_assert(BINARY_PRODUCT_1(1, 1) == 10);
        static_assert(BINARY_PRODUCT_1(1, 2) == 12);


        /// @test Verify scalar * matrix multiplication returns 2x3 matrix at compile time.
        constexpr flcn::Mat2x3 BINARY_PRODUCT_2 = 2 * MAT1;
        static_assert(BINARY_PRODUCT_2(0, 0) == 2);
        static_assert(BINARY_PRODUCT_2(0, 1) == 4);
        static_assert(BINARY_PRODUCT_2(0, 2) == 6);
        static_assert(BINARY_PRODUCT_2(1, 0) == 8);
        static_assert(BINARY_PRODUCT_2(1, 1) == 10);
        static_assert(BINARY_PRODUCT_2(1, 2) == 12);

    } // namespace static_tests

} // namespace



/**************************************
 *     SCALAR MULTIPLICATION TESTS    *
 **************************************/

TEST(Mat2x3ScalarMultiplicationTests, TimesOperator_ByZeroReturnsZeroMatrix)
{
    const flcn::Mat2x3 mat(3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);
    const flcn::Mat2x3 product = mat * 0;
    EXPECT_MAT_ZERO(product);
}


TEST(Mat2x3ScalarMultiplicationTests, TimesOperator_ByOneReturnsOriginalMatrix)
{
    const flcn::Mat2x3 mat(3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);

    const flcn::Mat2x3 product = mat * 1;

    EXPECT_MAT_EQ(mat, product);
}


TEST(Mat2x3ScalarMultiplicationTests, TimesOperator_ByNegativeScalarFlipsSigns)
{
    const flcn::Mat2x3 mat      = { 1.0f, -2.0f, -4.0f, 5.0f, 10.0f, -1.0f };
    const flcn::Mat2x3 expected = { -2.0f, 4.0f, 8.0f, -10.0f, -20.f, 2.0f };
    const float scalar         = -2.0f;

    const flcn::Mat2x3<float> product = mat * scalar;

    EXPECT_MAT_EQ(expected, product);
}


TYPED_TEST(Mat2x3ScalarMultiplicationTests, TimesOperator_ByScalarReturnsScaledMatrix)
{
    const flcn::Mat2x3 product = this->_mat * this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFloatingMat, product);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntegralMat, product);
    }
}


/**
 * @test Verify that the binary multiplication operator (scalar * matrix) perform an element-wise product
 *        and returns a new matrix instance.
 */
TYPED_TEST(Mat2x3ScalarMultiplicationTests, TimesOperator_ScalarTimesMatrixReturnsScaledMatrix)
{
    const flcn::Mat2x3 product = this->_scalar * this->_mat;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFloatingMat, product);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntegralMat, product);
    }
}


TYPED_TEST(Mat2x3ScalarMultiplicationTests, TimesOperator_MixedType_PromotesType)
{
    const double scalar = 2.123456789123456;

    [[maybe_unused]] const flcn::Mat2x3 product = this->_mat * scalar;

    static_assert(std::is_same_v<typename decltype(product)::value_type, double>);
}



TYPED_TEST(Mat2x3ScalarMultiplicationTests, TimesEqualsOperator_MatrixTimesEqualScalarIsTheSameMatrixScaled)
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


TEST(Mat2x3ScalarMultiplicationTests, TimesEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::Mat2x3 mat(3.0f, -1.0f, -12.0f, 14.0f, 12.0f, 3.2f);
    const double scalar = 5.0;
    mat *= scalar;

    static_assert(std::is_same_v<decltype(mat)::value_type, float>);
}


TEST(Mat2x3ScalarMultiplicationTests, TimesEqualsOperator_MixedType_EnsuresMinimalPrecisionLoss)
{
    flcn::Mat2x3 mat(3, -1, 10, 5, 50, 12);
    const double scalar = 2.5;
    const flcn::Mat2x3 expected(7, -2, 25, 12, 125, 30);

    mat *= scalar;

    EXPECT_MAT_EQ(expected, mat);
}

/** @} */
