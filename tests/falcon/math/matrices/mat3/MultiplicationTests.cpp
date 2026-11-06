/**
 * @file MultiplicationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 25, 2026
 *
 * @brief Verify @ref flcn::Mat3 multiplication logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3TestSetup.h"

/**
 * @addtogroup T_FALCON_Mat3x3_Multiplication
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat3 scalar multiplication.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat3ScalarMultiplicationTests: public testing::Test
    {
    protected:
        flcn::Mat3<T> _mat;
        T _scalar;
        flcn::Mat3<T> _expectedFloatingMat;
        flcn::Mat3<T> _expectedIntegralMat;


        void SetUp() override
        {
            _mat                 = { flcn::Vec3{ T(7), T(13), T(3) }, flcn::Vec3{ T(5), T(4), T(7) },
                                     flcn::Vec3{ T(5.5), T(11.25), T(25.3) } };
            _scalar              = T(2.123456789123456);
            _expectedFloatingMat = { flcn::Vec3{ T(14.864197523864192), T(27.604938258604928), T(6.370370367370368) },
                                     flcn::Vec3{ T(10.61728394561728), T(8.493827156493824), T(14.864197523864192) },
                                     flcn::Vec3{ T(11.679012340179007), T(23.88888887763888), T(53.72345676482344) } };
            _expectedIntegralMat = { flcn::Vec3{ T(14), T(26), T(6) }, flcn::Vec3{ T(10), T(8), T(14) },
                                     flcn::Vec3{ T(10), T(22), T(50) } };
        }
    };

    TYPED_TEST_SUITE(Mat3ScalarMultiplicationTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::Mat3 vector multiplication.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat3VectorMultiplicationTests: public testing::Test
    {
    protected:
        flcn::Mat3<T> _mat;
        flcn::Vec3<T> _vec;
        flcn::Vec3<T> _expectedFloatingColVector, _expectedIntegralColVector, _expectedFloatingRowVector,
            _expectedIntegralRowVector;

        void SetUp() override
        {
            _mat                       = { flcn::Vec3{ T(7.12345678912345), T(13.12345678912345), T(1.32893912338) },
                                           flcn::Vec3{ T(5.12345678912345), T(4.12345678912345), T(3.3129381239321) },
                                           flcn::Vec3{ T(2.238929123125), T(11.238924194839), T(9.2389291239898) } };
            _vec                       = { T(2.123456789123456), T(3.123456832912), T(1.2318492394128) };
            _expectedFloatingColVector = { T(33.88727193442948), T(54.59119292006805), T(24.550731838459015) };
            _expectedIntegralColVector = { T(31), T(49), T(20) };
            _expectedFloatingRowVector = { T(57.753956108666344), T(27.839918694037294), T(51.239531632191486) };
            _expectedIntegralRowVector = { T(54), T(25), T(46) };
        }
    };
    TYPED_TEST_SUITE(Mat3VectorMultiplicationTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref flcn::Mat3 vector multiplication with floating point elements.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat3VectorFractionalMultiplicationTests: public testing::Test
    {
    protected:
        flcn::Mat3<T> _mat;
        flcn::Vec3<T> _vec, _expectedColVector, _expectedRowVector;

        void SetUp() override
        {
            _mat = {
                flcn::Vec3{ T(0.1234568989329), T(0.1234214891234), T(0.12348923829) },
                flcn::Vec3{ T(-0.123489823149), T(-0.123489757623), T(0.89281239432) },
                flcn::Vec3{ T(-0.38291023892), T(0.29381938232), T(-0.0038291382) },
            };
            _vec = flcn::Vec3{ T(0.8923764912287), T(0.78352829112384), T(0.234891238341) };

            _expectedColVector = flcn::Vec3{ T(-0.07652999600877063), T(0.08239631520624698), T(0.8088432317718919) };
            _expectedRowVector = flcn::Vec3{ T(0.2358808028522597), T(0.0027566750622143033), T(-0.11238372794829783) };
        }
    };
    TYPED_TEST_SUITE(Mat3VectorFractionalMultiplicationTests, SupportedFloatingPointTypes);

    /**
     * @brief Test fixture for @ref flcn::Mat3 matrix-matrix multiplication.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat3MatrixMultiplicationTests: public testing::Test
    {
    protected:
        flcn::Mat3<T> _matA, _matB, _expectedFloatingMat, _expectedIntegralMat;

        void SetUp() override
        {
            _matA = { flcn::Vec3{ T(7.12345678912345), T(6.12345678912345), T(1.2389123488213) },
                      flcn::Vec3{ T(5.12345678912345), T(4.12345678912345), T(2.53283924821338) },
                      flcn::Vec3{ T(9.32189342348), T(8.238192312343), T(5.12398423821223) } };
            _matB = { flcn::Vec3{ T(3.12345678912345), T(5.12345678912345), T(1.213849123421) },
                      flcn::Vec3{ T(8.12345678912345), T(3.12345678912345), T(2.3218934118233) },
                      flcn::Vec3{ T(7.23912389492341), T(4.291238423419123), T(4.18234983241234) } };

            _expectedFloatingMat = { flcn::Vec3{ T(59.81499110074553), T(50.25262787869462), T(23.066325405048886) },
                                     flcn::Vec3{ T(95.51443223309786), T(81.75128018451636), T(29.872810121743093) },
                                     flcn::Vec3{ T(112.54098028826937), T(96.47820080937791), T(41.267951710315614) } };

            _expectedIntegralMat = { flcn::Vec3{ T(55), T(46), T(18) }, flcn::Vec3{ T(89), T(76), T(24) },
                                     flcn::Vec3{ T(105), T(90), T(35) } };
        }
    };
    TYPED_TEST_SUITE(Mat3MatrixMultiplicationTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::Mat3 matrix-matrix multiplication with floating-point elements.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat3MatrixFractionalMultiplicationTests: public testing::Test
    {
    protected:
        flcn::Mat3<T> _matA, _matB, _expectedMat;

        void SetUp() override
        {
            _matA = { flcn::Vec3{ T(0.1234568989329), T(0.1234214891234), T(0.382348912394) },
                      flcn::Vec3{ T(-0.123489823149), T(-0.123489757623), T(0.093218349323) },
                      flcn::Vec3{ T(0.0123489823149), T(0.53489757623), T(-0.93218349323) } };
            _matB = { flcn::Vec3{ T(0.8923764912287), T(0.78352829112384), T(0.0523812349234) },
                      flcn::Vec3{ T(0.0123412348958), T(-0.0231423489589), T(0.3829123948324) },
                      flcn::Vec3{ T(-0.539282348958), T(0.00033423489589), T(-0.8239123948324) } };

            _expectedMat = { flcn::Vec3{ T(0.014059119128298), T(0.041399312244975), T(0.365409472263106) },
                             flcn::Vec3{ T(0.009110033561366), T(0.209199928556498), T(-0.354383247645329) },
                             flcn::Vec3{ T(-0.076793880652601), T(-0.50730904817435), T(0.56187467155827) } };
        }
    };
    TYPED_TEST_SUITE(Mat3MatrixFractionalMultiplicationTests, SupportedFloatingPointTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_test
    {
        constexpr flcn::Mat3 MAT1(1, 2, 3, 4, 5, 6, 7, 8, 9);
        constexpr flcn::Mat3 MAT2(5, 6, 7, 8, 10, 11, 12, 13, 14);
        constexpr flcn::Vec3 VEC(1, 2, 3);


        /// @test Verify that matrix * scalar multiplication returns 3D matrix at compile time.
        constexpr flcn::Mat3 BINARY_PRODUCT_1 = MAT1 * 2;
        static_assert(BINARY_PRODUCT_1(0, 0) == 2);
        static_assert(BINARY_PRODUCT_1(0, 1) == 4);
        static_assert(BINARY_PRODUCT_1(0, 2) == 6);
        static_assert(BINARY_PRODUCT_1(1, 0) == 8);
        static_assert(BINARY_PRODUCT_1(1, 1) == 10);
        static_assert(BINARY_PRODUCT_1(1, 2) == 12);
        static_assert(BINARY_PRODUCT_1(2, 0) == 14);
        static_assert(BINARY_PRODUCT_1(2, 1) == 16);
        static_assert(BINARY_PRODUCT_1(2, 2) == 18);


        /// @test Verify scalar * matrix multiplication returns 3D matrix at compile time.
        constexpr flcn::Mat3 BINARY_PRODUCT_2 = 2 * MAT1;
        static_assert(BINARY_PRODUCT_2(0, 0) == 2);
        static_assert(BINARY_PRODUCT_2(0, 1) == 4);
        static_assert(BINARY_PRODUCT_2(0, 2) == 6);
        static_assert(BINARY_PRODUCT_2(1, 0) == 8);
        static_assert(BINARY_PRODUCT_2(1, 1) == 10);
        static_assert(BINARY_PRODUCT_2(1, 2) == 12);
        static_assert(BINARY_PRODUCT_2(2, 0) == 14);
        static_assert(BINARY_PRODUCT_2(2, 1) == 16);
        static_assert(BINARY_PRODUCT_2(2, 2) == 18);

        /// @test Verify matrix * vector multiplication returns 3D column vector at compile time.
        constexpr flcn::Vec3 COL_VECTOR_PRODUCT = MAT1 * VEC;
        static_assert(COL_VECTOR_PRODUCT[0] == 14);
        static_assert(COL_VECTOR_PRODUCT[1] == 32);
        static_assert(COL_VECTOR_PRODUCT[2] == 50);

        /// @test Verify vector * matrix multiplication returns 3D row vector at compile time.
        constexpr flcn::Vec3 ROW_VEC_PRODUCT = VEC * MAT1;
        static_assert(ROW_VEC_PRODUCT[0] == 30);
        static_assert(ROW_VEC_PRODUCT[1] == 36);
        static_assert(ROW_VEC_PRODUCT[2] == 42);

        /// @test Verify that matrix * matrix multiplication returns 3D matrix at compile time.
        constexpr flcn::Mat3 MAT_PRODUCT = MAT1 * MAT2;
        static_assert(MAT_PRODUCT(0, 0) == 57);
        static_assert(MAT_PRODUCT(0, 1) == 65);
        static_assert(MAT_PRODUCT(0, 2) == 71);
        static_assert(MAT_PRODUCT(1, 0) == 132);
        static_assert(MAT_PRODUCT(1, 1) == 152);
        static_assert(MAT_PRODUCT(1, 2) == 167);
        static_assert(MAT_PRODUCT(2, 0) == 207);
        static_assert(MAT_PRODUCT(2, 1) == 239);
        static_assert(MAT_PRODUCT(2, 2) == 263);

    } // namespace static_test
} // namespace



/**************************************
 *     SCALAR MULTIPLICATION TESTS    *
 **************************************/

TEST(Mat3ScalarMultiplicationTests, TimesOperator_ByZeroReturnsZeroMatrix)
{
    const flcn::Mat3 mat{ 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f };

    const flcn::Mat3 product = mat * 0;

    EXPECT_MAT_ZERO(product);
}


TEST(Mat3ScalarMultiplicationTests, TimesOperator_ByOneReturnsOriginalMatrix)
{
    const flcn::Mat3 mat{ 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f };

    const flcn::Mat3 product = mat * 1;

    EXPECT_MAT_EQ(mat, product);
}


TEST(Mat3ScalarMultiplicationTests, TimesOperator_ByNegativeScalarFlipsSigns)
{
    const flcn::Mat3 mat      = { 1.0f, -2.0f, 3.0f, -4.0f, 5.0f, 6.0f, 7.0f, 8.0f, -9.0f };
    const flcn::Mat3 expected = { -2.0f, 4.0f, -6.0f, 8.0f, -10.0f, -12.0f, -14.0f, -16.0f, 18.0f };
    const float scalar       = -2.0f;

    const flcn::Mat3 product = mat * scalar;

    EXPECT_MAT_EQ(expected, product);
}


TYPED_TEST(Mat3ScalarMultiplicationTests, TimesOperator_ByScalarReturnsScaledMatrix)
{
    const flcn::Mat3 product = this->_mat * this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFloatingMat, product);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntegralMat, product);
    }
}


TYPED_TEST(Mat3ScalarMultiplicationTests, TimesOperator_ScalarTimesMatrixReturnsScaledMatrix)
{
    const flcn::Mat3 product = this->_scalar * this->_mat;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFloatingMat, product);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntegralMat, product);
    }
}


TYPED_TEST(Mat3ScalarMultiplicationTests, TimesOperator_MixedType_PromotesType)
{
    const double scalar = 2.123456789123456;

    [[maybe_unused]] const flcn::Mat3 product = this->_mat * scalar;

    static_assert(std::is_same_v<typename decltype(product)::value_type, double>);
}


TYPED_TEST(Mat3ScalarMultiplicationTests, TimesEqualsOperator_MatrixTimesEqualScalarIsTheSameMatrixScaled)
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


TEST(Mat3ScalarMultiplicationTests, TimesEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::Mat3 mat       = { 1.0f, -2.0f, 3.0f, -4.0f, 5.0f, 6.0f, 7.0f, 8.0f, -9.0f };
    const double scalar = 5.0;
    
    mat *= scalar;
    static_assert(std::is_same_v<decltype(mat)::value_type, float>);
}


TEST(Mat3ScalarMultiplicationTests, TimesEqualsOperator_MixedType_EnsuresMinimalPrecisionLoss)
{
    flcn::Mat3 mat       = { 1, -2, 3, -4, 5, 6, 7, 8, -9 };
    const double scalar = 2.5;
    const flcn::Mat3 expected{ 2, -5, 7, -10, 12, 15, 17, 20, -22 };

    mat *= scalar;
    EXPECT_MAT_EQ(expected, mat);
}



/**************************************
 *    VECTOR MULTIPLICATION TESTS     *
 **************************************/

TYPED_TEST(Mat3VectorMultiplicationTests, ColumnVector_ReturnsATransformedColumnVector)
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


TYPED_TEST(Mat3VectorFractionalMultiplicationTests, ColumnFloatVector_ReturnsAColumnVectorWithPrecision)
{
    const auto transformedVector = this->_mat * this->_vec;
    EXPECT_VEC_EQ(this->_expectedColVector, transformedVector);
}


TEST(Mat3VectorMultiplicationTests, IdentityMatrixTimesColumnVector_ReturnsOriginalColumnVector)
{
    const flcn::Mat3<float> iMatrix = flcn::Mat3<float>::identity();
    const flcn::Vec3F vec{ 2.0f, 1.0f, 2.5 };

    const flcn::Vec3F transformedVector = iMatrix * vec;
    EXPECT_VEC_EQ(vec, transformedVector);
}


TEST(Mat3VectorMultiplicationTests, ColumnVector_MixedType_PromotesType)
{
    const flcn::Mat3 mat{ 1.0, 2.0, 3.0 };
    const flcn::Vec3I vec{ 2, 1, 3 };

    [[maybe_unused]] const auto transformedVector = mat * vec;
    static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
}


TYPED_TEST(Mat3VectorMultiplicationTests, RowVector_ReturnsATransformedRowVector)
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


TYPED_TEST(Mat3VectorFractionalMultiplicationTests, RowFloatVector_ReturnsARowVectorWithPrecision)
{
    const auto transformedVector = this->_vec * this->_mat;
    EXPECT_VEC_EQ(this->_expectedRowVector, transformedVector);
}


TEST(Mat3VectorMultiplicationTests, RowVectorTimesIdentityMatrix_ReturnsOriginalVector)
{
    const flcn::Mat3<float> iMatrix = flcn::Mat3<float>::identity();
    const flcn::Vec3F vec{ 2.0f, 1.0f, 3.0f };

    const flcn::Vec3F transformedVector = vec * iMatrix;

    EXPECT_VEC_EQ(vec, transformedVector);
}


TEST(Mat3VectorMultiplicationTests, RowVector_MixedType_PromotesType)
{
    const flcn::Mat3 mat{ 1.0, 2.0, 3.0 };
    const flcn::Vec3I vec{ 2, 1, 3 };

    [[maybe_unused]] const auto transformedVector = vec * mat;
    static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
}


TYPED_TEST(Mat3VectorMultiplicationTests, TimesEqualOperator_RowVector_ReturnsATransformedRowVector)
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


TEST(Mat3VectorMultiplicationTests, TimesEqualOperator_RowVector_IdentityMatrix_ReturnsOriginalRowVector)
{
    const flcn::Mat3<float> iMatrix = flcn::Mat3<float>::identity();
    flcn::Vec3F vec{ 2.0f, 1.0f, 3.0f };

    vec *= iMatrix;

    EXPECT_VEC_CONTAINS(vec, 2.0f, 1.0f, 3.0f);
}


TEST(Mat3VectorMultiplicationTests, TimesEqualOperator_MixedType_DoesNotPromoteType)
{
    const flcn::Mat3<double> iMatrix = flcn::Mat3<double>::identity();
    [[maybe_unused]] flcn::Vec3I vec{ 2, 1, 5 };

    (void) (vec *= iMatrix);
    static_assert(std::is_same_v<decltype(vec)::value_type, int>);
}


TEST(Mat3VectorMultiplicationTests, TimesEqualOperator_MixedType_EnsuresMinimalPrecisionLoss)
{
    const flcn::Mat3 mat{ 2.5, 3.5, 0.5, 1.5, 12.0, 3.25, 5.0, 11.5, 5.0 };
    flcn::Vec3 vec{ 10, 20, 30 };
    const flcn::Vec3 expected{ 205, 620, 220 };

    vec *= mat;

    EXPECT_VEC_EQ(expected, vec);
}


/**************************************
 *    MATRIX MULTIPLICATION TESTS     *
 **************************************/

TYPED_TEST(Mat3MatrixMultiplicationTests, TimesOperator_ReturnsMatrixProduct)
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


TYPED_TEST(Mat3MatrixFractionalMultiplicationTests, TimesOperator_ReturnsMatrixWithPrecision)
{
    const auto transformedVector = this->_matA * this->_matB;
    EXPECT_MAT_EQ(this->_expectedMat, transformedVector);
}


TEST(Mat3MatrixMultiplicationTests, TimesOperator_IdentityMatrix_ReturnsOriginalMatrix)
{
    const flcn::Mat3<float> iMatrix = flcn::Mat3<float>::identity();
    const flcn::Mat3 mat{ 1.0f, 2.0f, 3.0f };

    const flcn::Mat3 matrixProduct = iMatrix * mat;

    EXPECT_MAT_EQ(mat, matrixProduct);
}


TEST(Mat3MatrixMultiplicationTests, TimesOperator_PromotesType)
{
    const flcn::Mat3 matA{ 1.0, 2.0, 3.0 };
    const flcn::Mat3 matB{ 2, 1, 3 };

    [[maybe_unused]] const auto transformedVector = matA * matB;
    static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
}


TYPED_TEST(Mat3MatrixMultiplicationTests, TimesEqualsOperator_PerformInPlaceMatrixMultiplication)
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


TEST(Mat3MatrixMultiplicationTests, TimesEqualsOperator_IdentityMatrix_ReturnsOriginalMatrix)
{
    const flcn::Mat3<float> iMatrix = flcn::Mat3<float>::identity();
    flcn::Mat3 mat{ 1.0f, 2.0f, 3.0f };

    mat *= iMatrix;
    EXPECT_MAT_CONTAINS(std::vector{ 1.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 3.0f }, mat);
}


TEST(Mat3MatrixMultiplicationTests, TimesEqualsOperator_MixedType_DoesNotPromoteType)
{
    const flcn::Mat3<double> iMatrix = flcn::Mat3<double>::identity();
    flcn::Mat3 mat{ 1, 2, 3 };

    mat *= iMatrix;
    static_assert(std::is_same_v<decltype(mat)::value_type, int>);
}


TEST(Mat3MatrixMultiplicationTests, TimesEqualsOperator_EnsuresMinimalPrecisionLoss)
{
    const flcn::Mat3 matA{ 2.5, 3.5, 0.5, 1.5, 2.5, -12.5, 5.45, 23.25, 85.5 };
    flcn::Mat3 matB{ 5, 10, 15, 20, 25, 30, 35, 40, 45 };
    const flcn::Mat3 expectedMatrix{ 109, 391, 1160, 251, 830, 2262, 392, 1268, 3365 };

    matB *= matA;

    EXPECT_MAT_EQ(expectedMatrix, matB);
}


/** @} */
