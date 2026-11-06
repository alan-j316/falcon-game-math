/**
 * @file MultiplicationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 10, 2026
 *
 * @brief Verify @ref flcn::Mat2 multiplication logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat2x2_Multiplication
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
    class Mat2ScalarMultiplicationTests: public testing::Test
    {
    protected:
        flcn::Mat2<T> _mat;
        T _scalar;
        flcn::Mat2<T> _expectedFloatingMat;
        flcn::Mat2<T> _expectedIntegralMat;



        void SetUp() override
        {
            _mat                 = { flcn::CVec2{ T(7), T(13) }, flcn::CVec2{ T(5), T(4) } };
            _scalar              = T(2.123456789123456);
            _expectedFloatingMat = { flcn::CVec2{ T(14.864197523864192), T(27.604938258604928) },
                                     flcn::CVec2{ T(10.61728394561728), T(8.493827156493824) } };
            _expectedIntegralMat = { flcn::CVec2{ T(14), T(26) }, flcn::CVec2{ T(10), T(8) } };
        }
    };
    TYPED_TEST_SUITE(Mat2ScalarMultiplicationTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref flcn::Mat2 vector multiplication.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat2VectorMultiplicationTests: public testing::Test
    {
    protected:
        flcn::Mat2<T> _mat;
        flcn::CVec2<T> _vec;
        flcn::CVec2<T> _expectedFloatingColVector, _expectedIntegralColVector, _expectedFloatingRowVector,
            _expectedIntegralRowVector;

        void SetUp() override
        {
            _mat                       = { flcn::CVec2{ T(7.12345678912345), T(13.12345678912345) },
                                           flcn::CVec2{ T(5.12345678912345), T(4.12345678912345) } };
            _vec                       = { T(2.123456789123456), T(3.123456832912) };
            _expectedFloatingColVector = { T(31.129248797008778), T(40.74653269883751) };
            _expectedIntegralColVector = { T(29), T(38) };
            _expectedFloatingRowVector = { T(56.116903460304776), T(23.75887838584987) };
            _expectedIntegralRowVector = { T(53), T(22) };
        }
    };
    TYPED_TEST_SUITE(Mat2VectorMultiplicationTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref flcn::Mat2 vector multiplication with floating point elements.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat2VectorFractionalMultiplicationTests: public testing::Test
    {
    protected:
        flcn::Mat2<T> _mat;
        flcn::CVec2<T> _vec, _expectedColVector, _expectedRowVector;

        void SetUp() override
        {
            _mat = { flcn::CVec2{ T(0.1234568989329), T(0.1234214891234) },
                     flcn::CVec2{ T(-0.123489823149), T(-0.123489757623) } };
            _vec = flcn::CVec2{ T(0.8923764912287), T(0.78352829112384) };

            _expectedColVector = flcn::CVec2{ T(0.013412264184596345), T(0.013380716644514457) };
            _expectedRowVector = flcn::CVec2{ T(0.20687426274853477), T(-0.20695713384580372) };
        }
    };
    TYPED_TEST_SUITE(Mat2VectorFractionalMultiplicationTests, SupportedFloatingPointTypes);


    /**
     * @brief Test fixture for @ref flcn::Mat2 matrix-matrix multiplication.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat2MatrixMultiplicationTests: public testing::Test
    {
    protected:
        flcn::Mat2<T> _matA, _matB, _expectedFloatingMat, _expectedIntegralMat;

        void SetUp() override
        {
            _matA = { flcn::CVec2{ T(7.12345678912345), T(13.12345678912345) },
                      flcn::CVec2{ T(5.12345678912345), T(4.12345678912345) } };
            _matB = { flcn::CVec2{ T(3.12345678912345), T(10.12345678912345) },
                      flcn::CVec2{ T(8.12345678912345), T(3.12345678912345) } };

            _expectedFloatingMat = { flcn::CVec2{ T(74.11690288564759), T(82.73418683126485) },
                                     flcn::CVec2{ T(73.8699893074007), T(119.48727325301795) } };
            _expectedIntegralMat = { flcn::CVec2{ T(71), T(79) }, flcn::CVec2{ T(71), T(116) } };
        }
    };
    TYPED_TEST_SUITE(Mat2MatrixMultiplicationTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref flcn::Mat2 matrix-matrix multiplication with floating-point elements.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat2MatrixFractionalMultiplicationTests: public ::testing::Test
    {
    protected:
        flcn::Mat2<T> _matA, _matB, _expectedMat;

        void SetUp() override
        {
            _matA = { flcn::CVec2{ T(0.1234568989329), T(0.1234214891234) },
                      flcn::CVec2{ T(-0.123489823149), T(-0.123489757623) } };
            _matB = { flcn::CVec2{ T(0.8923764912287), T(0.78352829112384) },
                      flcn::CVec2{ T(0.0123412348958), T(-0.0231423489589) } };

            _expectedMat = { flcn::CVec2{ T(0.013412264184596345), T(0.013380716644514457) },
                             flcn::CVec2{ T(0.004381455169424965), T(0.004381016652222751) } };
        }
    };
    TYPED_TEST_SUITE(Mat2MatrixFractionalMultiplicationTests, SupportedFloatingPointTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_test
    {
        constexpr flcn::Mat2 MAT1(1, 2, 3, 4);
        constexpr flcn::Mat2 MAT2(5, 6, 7, 8);
        constexpr flcn::CVec2 VEC(1, 2);

        /// @test Verify that matrix * scalar multiplication returns 2D matrix at compile time.
        constexpr flcn::Mat2 BINARY_PRODUCT_1 = MAT1 * 2;
        static_assert(BINARY_PRODUCT_1(0, 0) == 2);
        static_assert(BINARY_PRODUCT_1(0, 1) == 4);
        static_assert(BINARY_PRODUCT_1(1, 0) == 6);
        static_assert(BINARY_PRODUCT_1(1, 1) == 8);


        /// @test Verify scalar * matrix multiplication returns 2D matrix at compile time.
        constexpr flcn::Mat2 BINARY_PRODUCT_2 = 2 * MAT1;
        static_assert(BINARY_PRODUCT_2(0, 0) == 2);
        static_assert(BINARY_PRODUCT_2(0, 1) == 4);
        static_assert(BINARY_PRODUCT_2(1, 0) == 6);
        static_assert(BINARY_PRODUCT_2(1, 1) == 8);

        /// @test Verify matrix * vector multiplication returns 2D column vector at compile time.
        constexpr flcn::CVec2 COL_VECTOR_PRODUCT = MAT1 * VEC;
        static_assert(COL_VECTOR_PRODUCT[0] == 5);
        static_assert(COL_VECTOR_PRODUCT[1] == 11);

        /// @test Verify vector * matrix multiplication returns 2D row vector at compile time.
        constexpr flcn::CVec2 ROW_VEC_PRODUCT = VEC * MAT1;
        static_assert(ROW_VEC_PRODUCT[0] == 7);
        static_assert(ROW_VEC_PRODUCT[1] == 10);

        /// @test Verify that matrix * matrix multiplication returns 2D matrix at compile time.
        constexpr flcn::Mat2 MAT_PRODUCT = MAT1 * MAT2;
        static_assert(MAT_PRODUCT(0, 0) == 19);
        static_assert(MAT_PRODUCT(0, 1) == 22);
        static_assert(MAT_PRODUCT(1, 0) == 43);
        static_assert(MAT_PRODUCT(1, 1) == 50);

    } // namespace static_test

} // namespace



/**************************************
 *     SCALAR MULTIPLICATION TESTS    *
 **************************************/

TEST(Mat2ScalarMultiplicationTests, TimesOperator_ByZeroReturnsZeroMatrix)
{
    const flcn::Mat2 mat(3.0f, 4.0f, 5.0f, 6.0f);
    const flcn::Mat2 product = mat * 0;
    EXPECT_MAT_ZERO(product);
}


TEST(Mat2ScalarMultiplicationTests, TimesOperator_ByOneReturnsOriginalMatrix)
{
    const flcn::Mat2 mat(3.0f, 4.0f, 5.0f, 6.0f);
    const flcn::Mat2 product = mat * 1;
    EXPECT_MAT_EQ(mat, product);
}


TEST(Mat2ScalarMultiplicationTests, TimesOperator_ByNegativeScalarFlipsSigns)
{
    const flcn::Mat2 mat      = { 1.0f, -2.0f, -4.0f, 5.0f };
    const flcn::Mat2 expected = { -2.0f, 4.0f, 8.0f, -10.0f };
    const float scalar       = -2.0f;

    const flcn::Mat2<float> product = mat * scalar;

    EXPECT_MAT_EQ(expected, product);
}


TYPED_TEST(Mat2ScalarMultiplicationTests, TimesOperator_ByScalarReturnsScaledMatrix)
{
    const flcn::Mat2 product = this->_mat * this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFloatingMat, product);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntegralMat, product);
    }
}


TYPED_TEST(Mat2ScalarMultiplicationTests, TimesOperator_ScalarTimesMatrixReturnsScaledMatrix)
{
    const flcn::Mat2 product = this->_scalar * this->_mat;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFloatingMat, product);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntegralMat, product);
    }
}


TYPED_TEST(Mat2ScalarMultiplicationTests, TimesOperator_MixedType_PromotesType)
{
    const double scalar = 2.123456789123456;

    [[maybe_unused]] const flcn::Mat2 product = this->_mat * scalar;

    static_assert(std::is_same_v<typename decltype(product)::value_type, double>);
}


TYPED_TEST(Mat2ScalarMultiplicationTests, TimesEqualsOperator_MatrixTimesEqualScalarIsTheSameMatrixScaled)
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


TEST(Mat2ScalarMultiplicationTests, TimesEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::Mat2 mat(3.0f, -1.0f, -12.0f, 14.0f);
    const double scalar = 5.0;

    mat *= scalar;
    static_assert(std::is_same_v<decltype(mat)::value_type, float>);
}


TEST(Mat2ScalarMultiplicationTests, TimesEqualsOperator_MixedType_EnsuresMinimalPrecisionLoss)
{
    flcn::Mat2 mat(3, -1, 10, 5);
    const double scalar = 2.5;
    const flcn::Mat2 expected(7, -2, 25, 12);

    mat *= scalar;
    EXPECT_MAT_EQ(expected, mat);
}



/**************************************
 *    VECTOR MULTIPLICATION TESTS     *
 **************************************/

TYPED_TEST(Mat2VectorMultiplicationTests, ColumnVector_ReturnsATransformedColumnVector)
{
    const auto transformedVector = this->_mat * this->_vec;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFloatingColVector, transformedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntegralColVector, transformedVector);
    }
}


TYPED_TEST(Mat2VectorFractionalMultiplicationTests, ColumnFloatVector_ReturnsAColumnVectorWithPrecision)
{
    const auto transformedVector = this->_mat * this->_vec;
    EXPECT_VEC_EQ(this->_expectedColVector, transformedVector);
}


TEST(Mat2VectorMultiplicationTests, IdentityMatrixTimesColumnVector_ReturnsOriginalColumnVector)
{
    const flcn::Mat2<float> iMatrix = flcn::Mat2<float>::identity();
    const flcn::CVec2F vec(2.0f, 1.0f);

    const flcn::CVec2F transformedVector = iMatrix * vec;

    EXPECT_VEC_EQ(vec, transformedVector);
}


TEST(Mat2VectorMultiplicationTests, ColumnVector_MixedType_PromotesType)
{
    const flcn::Mat2 mat(1.0, 2.0);
    const flcn::CVec2I vec(2, 1);

    [[maybe_unused]] const auto transformedVector = mat * vec;
    static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
}


TYPED_TEST(Mat2VectorMultiplicationTests, RowVector_ReturnsATransformedRowVector)
{
    const auto transformedVector = this->_vec * this->_mat;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFloatingRowVector, transformedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntegralRowVector, transformedVector);
    }
}


TYPED_TEST(Mat2VectorFractionalMultiplicationTests, RowFloatVector_ReturnsARowVectorWithPrecision)
{
    const auto transformedVector = this->_vec * this->_mat;
    EXPECT_VEC_EQ(this->_expectedRowVector, transformedVector);
}


TEST(Mat2VectorMultiplicationTests, RowVectorTimesIdentityMatrixReturnsOriginalVector)
{
    const flcn::Mat2<float> iMatrix = flcn::Mat2<float>::identity();
    const flcn::CVec2F vec(2.0f, 1.0f);

    const flcn::CVec2F transformedVector = vec * iMatrix;

    EXPECT_VEC_EQ(vec, transformedVector);
}


TEST(Mat2VectorMultiplicationTests, RowVector_MixedType_PromotesType)
{
    const flcn::Mat2 mat(1.0, 2.0);
    const flcn::CVec2I vec(2, 1);

    [[maybe_unused]] const auto transformedVector = vec * mat;
    static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
}


TYPED_TEST(Mat2VectorMultiplicationTests, TimesEqualOperator_RowVector_ReturnsATransformedRowVector)
{
    auto transformedVector = this->_vec;
    transformedVector *= this->_mat;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFloatingRowVector, transformedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntegralRowVector, transformedVector);
    }
}


TEST(Mat2VectorMultiplicationTests, TimesEqualOperator_RowVector_IdentityMatrix_ReturnsOriginalRowVector)
{
    const auto iMatrix = flcn::Mat2<float>::identity();
    flcn::CVec2F vec(2.0f, 1.0f);

    vec *= iMatrix;
    EXPECT_VEC_CONTAINS(vec, 2.0f, 1.0f);
}


TEST(Mat2VectorMultiplicationTests, TimesEqualOperator_MixedType_DoesNotPromoteType)
{
    const flcn::Mat2<double> iMatrix = flcn::Mat2<double>::identity();
    [[maybe_unused]] flcn::CVec2I vec(2, 1);

    (void) (vec *= iMatrix);
    static_assert(std::is_same_v<decltype(vec)::value_type, int>);
}


TEST(Mat2VectorMultiplicationTests, TimesEqualOperator_MixedType_EnsuresMinimalPrecisionLoss)
{
    const flcn::Mat2 mat(2.5, 3.5, 0.5, 1.5);
    flcn::CVec2 vec(10, 20);
    const flcn::CVec2 expected(35, 65);

    vec *= mat;

    EXPECT_VEC_EQ(expected, vec);
}



/**************************************
 *    MATRIX MULTIPLICATION TESTS     *
 **************************************/

TYPED_TEST(Mat2MatrixMultiplicationTests, TimesOperator_ReturnsMatrixProduct)
{
    const auto transformedVector = this->_matA * this->_matB;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFloatingMat, transformedVector);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntegralMat, transformedVector);
    }
}


TYPED_TEST(Mat2MatrixFractionalMultiplicationTests, TimesOperator_ReturnsMatrixWithPrecision)
{
    const auto transformedVector = this->_matA * this->_matB;
    EXPECT_MAT_EQ(this->_expectedMat, transformedVector);
}


TEST(Mat2MatrixMultiplicationTests, TimesOperator_IdentityMatrix_ReturnsOriginalMatrix)
{
    const flcn::Mat2<float> iMatrix = flcn::Mat2<float>::identity();
    const flcn::Mat2 mat(1.0f, 2.0f, 3.0f, 4.0f);

    const flcn::Mat2 matrixProduct = iMatrix * mat;

    EXPECT_MAT_EQ(mat, matrixProduct);
}


TEST(Mat2MatrixMultiplicationTests, TimesOperator_PromotesType)
{
    const flcn::Mat2 matA(1.0, 2.0);
    const flcn::Mat2 matB(2, 1);

    [[maybe_unused]] const auto transformedVector = matA * matB;
    static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
}


TYPED_TEST(Mat2MatrixMultiplicationTests, TimesEqualsOperator_PerformInPlaceMatrixMultiplication)
{
    auto transformedVector = this->_matA;
    transformedVector *= this->_matB;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFloatingMat, transformedVector);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntegralMat, transformedVector);
    }
}


TEST(Mat2MatrixMultiplicationTests, TimesEqualsOperator_IdentityMatrix_ReturnsOriginalMatrix)
{
    const flcn::Mat2<float> iMatrix = flcn::Mat2<float>::identity();
    flcn::Mat2 mat(1.0f, 2.0f, 3.0f, 4.0f);

    mat *= iMatrix;
    EXPECT_MAT_CONTAINS(std::vector{ 1.0f, 2.0f, 3.0f, 4.0f }, mat);
}


TEST(Mat2MatrixMultiplicationTests, TimesEqualsOperator_MixedType_DoesNotPromoteType)
{
    const flcn::Mat2<double> iMatrix = flcn::Mat2<double>::identity();
    flcn::Mat2 mat(1, 2, 3, 4);

    mat *= iMatrix;
    static_assert(std::is_same_v<decltype(mat)::value_type, int>);
}


TEST(Mat2MatrixMultiplicationTests, TimesEqualsOperator_EnsuresMinimalPrecisionLoss)
{
    const flcn::Mat2 matA(2.5, 3.5, 0.5, 1.5);
    flcn::Mat2 matB(5, 10, 15, 20);
    const flcn::Mat2 expectedMatrix(17, 32, 47, 82);

    matB *= matA;

    EXPECT_MAT_EQ(expectedMatrix, matB);
}


/** @} */
