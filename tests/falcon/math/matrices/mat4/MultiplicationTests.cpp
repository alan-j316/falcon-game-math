/**
 * @file MultiplicationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 05, 2026
 *
 * @brief Verify @ref flcn::Mat4 multiplication logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat4x4_Multiplication
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4 scalar multiplication.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat4ScalarMultiplicationTests: public testing::Test
    {
    protected:
        flcn::Mat4<T> _mat;
        T _scalar;
        flcn::Mat4<T> _expectedFloatingMat;
        flcn::Mat4<T> _expectedIntegralMat;



        void SetUp() override
        {
            _mat                 = { { T(7), T(8), T(1.23894234), T(5.28389123134) },
                                     { T(5.539), T(1.91238432), T(0.1329843), T(9.0129) },
                                     { T(5.5), T(11.25), T(1.332), T(3.8329) },
                                     { T(9.912384), T(1.2399132), T(5.383912), T(12.19381) } };
            _scalar              = T(2.123456789123456);
            _expectedFloatingMat = {
                { T(14.864197523864192), T(16.987654312987647), T(2.630840523205501), T(11.220114708178821) },
                { T(11.761827154954823), T(4.060865467717243), T(0.28238641468183), T(19.138503694690797) },
                { T(11.679012340179007), T(23.88888887763888), T(2.828444443112443), T(8.138997527031295) },
                { T(21.048519101198718), T(2.632902102463789), T(11.432504488443243), T(25.893028629781487) }
            };
            _expectedIntegralMat = { { T(14), T(16), T(2), T(10) },
                                     { T(10), T(2), T(0), T(18) },
                                     { T(10), T(22), T(2), T(6) },
                                     { T(18), T(2), T(10), T(24) }

            };
        }
    };
    TYPED_TEST_SUITE(Mat4ScalarMultiplicationTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::Mat4 vector multiplication.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat4VectorMultiplicationTests: public testing::Test
    {
    protected:
        flcn::Mat4<T> _mat;
        flcn::Vec4<T> _vec;
        flcn::Vec4<T> _expectedFloatingColVector, _expectedIntegralColVector, _expectedFloatingRowVector,
            _expectedIntegralRowVector;

        void SetUp() override
        {
            _mat = { flcn::Vec4{ T(7.12345678912345), T(13.12345678912345), T(1.32893912338), T(1.2384912349) },
                     flcn::Vec4{ T(5.12345678912345), T(4.12345678912345), T(3.3129381239321), T(3.2983192312) },
                     flcn::Vec4{ T(2.238929123125), T(11.238924194839), T(9.2389291239898), T(8.2813941329) },
                     flcn::Vec4{ T(7.32129123125), T(8.2314213412), T(2.2323329898), T(3.12343151324) } };
            _vec = { T(2.123456789123456), T(3.123456832912), T(1.2318492394128), T(4.18293482134) };
            _expectedFloatingColVector = { T(64.5117559627963), T(89.02269187729473), T(33.888435234319466),
                                           T(36.19857986352777) };
            _expectedIntegralColVector = { T(59), T(81), T(28), T(31) };
            _expectedFloatingRowVector = { T(62.93448422105393), T(41.636573058119154), T(85.88006351993967),
                                           T(57.07194293730016) };
            _expectedIntegralRowVector = { T(58), T(37), T(78), T(52) };
        }
    };
    TYPED_TEST_SUITE(Mat4VectorMultiplicationTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::Mat4 vector multiplication with floating point elements.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat4VectorFractionalMultiplicationTests: public testing::Test
    {
    protected:
        flcn::Mat4<T> _mat;
        flcn::Vec4<T> _vec, _expectedColVector, _expectedRowVector;

        void SetUp() override
        {
            _mat = { { T(0.1234568989329), T(0.1234214891234), T(0.12348923829), T(0.0893829192) },
                     { T(-0.123489823149), T(-0.123489757623), T(0.89281239432), T(0.00123849123) },
                     { T(-0.38291023892), T(0.29381938232), T(-0.0038291382), T(0.000832891234231) },
                     { T(0.58291023892), T(0.6381938232), T(-0.000291382), T(0.008391234231) } };
            _vec = flcn::Vec4{ T(0.8923764912287), T(0.78352829112384), T(0.234891238341), T(-0.9382938123) };

            _expectedColVector =
                flcn::Vec4{ T(-0.623471066313721), T(-0.516417000150393), T(0.809116633699507), T(0.073055804425393) };
            _expectedRowVector =
                flcn::Vec4{ T(0.152013362841589), T(0.001594606404517), T(-0.113165224639696), T(1.012276423171081) };
        }
    };
    TYPED_TEST_SUITE(Mat4VectorFractionalMultiplicationTests, SupportedFloatingPointTypes);



    /**
     * @brief Test fixture for @ref flcn::Mat4 matrix-matrix multiplication.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat4MatrixMultiplicationTests: public testing::Test
    {
    protected:
        flcn::Mat4<T> _matA, _matB, _expectedFloatingMat, _expectedIntegralMat;

        void SetUp() override
        {
            _matA = {
                { T(7.12345678912345), T(6.12345678912345), T(1.2389123488213), T(1.2394829342134) },
                { T(5.12345678912345), T(4.12345678912345), T(2.53283924821338), T(3.239123801234) },
                { T(1.32189342348), T(8.238192312343), T(5.12398423821223), T(0.32103489322) },
                { T(4.8934233348), T(1.9233212312343), T(4.3984231212233), T(0.5532103489322) },
            };
            _matB = {
                { T(3.12345678912345), T(5.12345678912345), T(1.213849123421), T(0.01238942934) },
                { T(8.12345678912345), T(3.12345678912345), T(2.3218934118233), T(1.238923983) },
                { T(7.23912389492341), T(4.291238423419123), T(4.18234983241234), T(0.55293891230) },
                { T(5.932123894923), T(3.338423419123), T(7.3498324123324), T(1.3234393891230) },
            };

            _expectedFloatingMat = {
                { T(50.16482483601474), T(50.27645673118712), T(23.120819357516705), T(20.863524100366096) },
                { T(83.00186446696702), T(84.13412898490563), T(35.32212201400836), T(21.616943657183004) },
                { T(81.78794580513838), T(97.5416799589801), T(43.7000110068), T(24.521194800949605) },
                { T(75.55334068335543), T(113.18568100247735), T(59.28654325421629), T(21.258026116800263) }
            };

            _expectedIntegralMat = { { 47, 46, 18, 18 }, { 77, 77, 28, 17 }, { 73, 90, 35, 19 }, { 61, 99, 50, 14 }

            };
        }
    };
    TYPED_TEST_SUITE(Mat4MatrixMultiplicationTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::Mat4 matrix-matrix multiplication with floating-point elements.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat4FractionalMultiplicationTests: public testing::Test
    {
    protected:
        flcn::Mat4<T> _matA, _matB, _expectedMat;

        void SetUp() override
        {
            _matA = { { T(0.1234568989329), T(0.1234214891234), T(0.382348912394), T(0.1234923482394) },
                      { T(-0.123489823149), T(-0.123489757623), T(0.093218349323), T(0.3928192323233) },
                      { T(0.0123489823149), T(0.53489757623), T(-0.93218349323), T(0.1210348932859) },
                      { T(-0.233298321932), T(-0.53219381923), T(0.785783564256), T(0.129348321982) } };
            _matB = { { T(0.8923764912287), T(0.78352829112384), T(0.0523812349234), T(0.00382912384813) },
                      { T(0.0123412348958), T(-0.0231423489589), T(0.3829123948324), T(0.00382312343491) },
                      { T(-0.539282348958), T(0.00033423489589), T(-0.8239123948324), T(0.00382912332432) },
                      { T(0.12343211234), T(0.2134213123321), T(-0.765243234532), T(0.23457875642343) } };

            _expectedMat = {
                { T(0.01316579096006), T(0.039361476199934), T(0.368418334848468), T(0.424821898161877) },
                { T(0.008218105279463), T(0.207165285894286), T(-0.351379100086055), T(0.039273563772687) },
                { T(-0.077687208698635), T(-0.509346883940622), T(0.56488353373203), T(-0.165692807850471) },
                { T(-0.075293619702199), T(-0.545289286689605), T(0.964764159211447), T(0.0368001527594) }
            };
        }
    };
    TYPED_TEST_SUITE(Mat4FractionalMultiplicationTests, SupportedFloatingPointTypes);


    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_test
    {
        constexpr flcn::Mat4 mat1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        constexpr flcn::Mat4 mat2(5, 6, 7, 8, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21);
        constexpr flcn::Vec4 vec4D(1, 2, 3, 4);

        /// @test Verify that matrix * scalar multiplication returns 4D matrix at compile time.
        constexpr flcn::Mat4 binaryProduct1 = mat1 * 2;
        static_assert(binaryProduct1(0, 0) == 2);
        static_assert(binaryProduct1(0, 1) == 4);
        static_assert(binaryProduct1(0, 2) == 6);
        static_assert(binaryProduct1(0, 3) == 8);
        static_assert(binaryProduct1(1, 0) == 10);
        static_assert(binaryProduct1(1, 1) == 12);
        static_assert(binaryProduct1(1, 2) == 14);
        static_assert(binaryProduct1(1, 3) == 16);
        static_assert(binaryProduct1(2, 0) == 18);
        static_assert(binaryProduct1(2, 1) == 20);
        static_assert(binaryProduct1(2, 2) == 22);
        static_assert(binaryProduct1(2, 3) == 24);
        static_assert(binaryProduct1(3, 0) == 26);
        static_assert(binaryProduct1(3, 1) == 28);
        static_assert(binaryProduct1(3, 2) == 30);
        static_assert(binaryProduct1(3, 3) == 32);


        /// @test Verify scalar * matrix multiplication returns 4D matrix at compile time.
        constexpr flcn::Mat4 binaryProduct2 = 2 * mat1;
        static_assert(binaryProduct2(0, 0) == 2);
        static_assert(binaryProduct2(0, 1) == 4);
        static_assert(binaryProduct2(0, 2) == 6);
        static_assert(binaryProduct2(0, 3) == 8);
        static_assert(binaryProduct2(1, 0) == 10);
        static_assert(binaryProduct2(1, 1) == 12);
        static_assert(binaryProduct2(1, 2) == 14);
        static_assert(binaryProduct2(1, 3) == 16);
        static_assert(binaryProduct2(2, 0) == 18);
        static_assert(binaryProduct2(2, 1) == 20);
        static_assert(binaryProduct2(2, 2) == 22);
        static_assert(binaryProduct2(2, 3) == 24);
        static_assert(binaryProduct2(3, 0) == 26);
        static_assert(binaryProduct2(3, 1) == 28);
        static_assert(binaryProduct2(3, 2) == 30);
        static_assert(binaryProduct2(3, 3) == 32);

        /// @test Verify matrix * vector multiplication returns 4D column vector at compile time.
        constexpr flcn::Vec4 colVectorProduct = mat1 * vec4D;
        static_assert(colVectorProduct[0] == 30);
        static_assert(colVectorProduct[1] == 70);
        static_assert(colVectorProduct[2] == 110);
        static_assert(colVectorProduct[3] == 150);

        /// @test Verify vector * matrix multiplication returns 4D row vector at compile time.
        constexpr flcn::Vec4 rowVectorProduct = vec4D * mat1;
        static_assert(rowVectorProduct[0] == 90);
        static_assert(rowVectorProduct[1] == 100);
        static_assert(rowVectorProduct[2] == 110);
        static_assert(rowVectorProduct[3] == 120);

        /// @test Verify that matrix * matrix multiplication returns 4D matrix at compile time.
        constexpr flcn::Mat4 matProduct = mat1 * mat2;
        static_assert(matProduct(0, 0) == 139);
        static_assert(matProduct(0, 1) == 149);
        static_assert(matProduct(0, 2) == 159);
        static_assert(matProduct(0, 3) == 169);
        static_assert(matProduct(1, 0) == 327);
        static_assert(matProduct(1, 1) == 353);
        static_assert(matProduct(1, 2) == 379);
        static_assert(matProduct(1, 3) == 405);
        static_assert(matProduct(2, 0) == 515);
        static_assert(matProduct(2, 1) == 557);
        static_assert(matProduct(2, 2) == 599);
        static_assert(matProduct(2, 3) == 641);
        static_assert(matProduct(3, 0) == 703);
        static_assert(matProduct(3, 1) == 761);
        static_assert(matProduct(3, 2) == 819);
        static_assert(matProduct(3, 3) == 877);
    } // namespace static_test
} // namespace




/**************************************
 *     SCALAR MULTIPLICATION TESTS    *
 **************************************/

TEST(Mat4ScalarMultiplicationTests, TimesOperator_ByZeroReturnsZeroMatrix)
{
    const flcn::Mat4 mat{ 3.0f,  4.0f,  5.0f,  6.0f,  7.0f,  8.0f,  9.0f,  10.0f,
                         11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f };

    const flcn::Mat4 product = mat * 0;
    EXPECT_MAT_ZERO(product);
}


TEST(Mat4ScalarMultiplicationTests, TimesOperator_ByOneReturnsOriginalMatrix)
{
    const flcn::Mat4 mat{ 3.0f,  4.0f,  5.0f,  6.0f,  7.0f,  8.0f,  9.0f,  10.0f,
                         11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f };

    const flcn::Mat4 product = mat * 1;
    EXPECT_MAT_EQ(mat, product);
}


TEST(Mat4ScalarMultiplicationTests, TimesOperator_ByNegativeScalarFlipsSigns)
{
    const flcn::Mat4 mat      = { 1.0f,  -2.0f, 3.0f,  -4.0f, 5.0f,  6.0f,  7.0f,  8.0f,
                                 -9.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f };
    const flcn::Mat4 expected = { -2.0f, 4.0f,   -6.0f,  8.0f,   -10.0f, -12.0f, -14.0f, -16.0f,
                                 18.0f, -24.0f, -26.0f, -28.0f, -30.0f, -32.0f, -34.0f, -36.0f };
    const float scalar       = -2.0f;

    const flcn::Mat4 product = mat * scalar;
    EXPECT_MAT_EQ(expected, product);
}


TYPED_TEST(Mat4ScalarMultiplicationTests, TimesOperator_ByScalarReturnsScaledMatrix)
{
    const flcn::Mat4 product = this->_mat * this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFloatingMat, product);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntegralMat, product);
    }
}


TYPED_TEST(Mat4ScalarMultiplicationTests, TimesOperator_ScalarTimesMatrixReturnsScaledMatrix)
{
    const flcn::Mat4 product = this->_scalar * this->_mat;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFloatingMat, product);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntegralMat, product);
    }
}


TYPED_TEST(Mat4ScalarMultiplicationTests, TimesEqualsOperator_MatrixTimesEqualScalarIsTheSameMatrixScaled)
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


TYPED_TEST(Mat4ScalarMultiplicationTests, TimesOperator_MixedType_PromotesType)
{
    const double scalar = 2.123456789123456;

    [[maybe_unused]] const flcn::Mat4 product = this->_mat * scalar;

    static_assert(std::is_same_v<typename decltype(product)::value_type, double>);
}



TEST(Mat4ScalarMultiplicationTests, TimesEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::Mat4 mat       = { 1.0f,  -2.0f, 3.0f,  -4.0f, 5.0f,  6.0f,  7.0f,  8.0f,
                            -9.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f };
    const double scalar = 5.0;
    mat *= scalar;

    static_assert(std::is_same_v<decltype(mat)::value_type, float>);
}



TEST(Mat4ScalarMultiplicationTests, TimesEqualsOperator_MixedType_EnsuresMinimalPrecisionLoss)
{
    flcn::Mat4 mat       = { 1, -2, 3, -4, 5, 6, 7, 8, -9, 10, 12, 13, 14, 16, 18, 20 };
    const double scalar = 2.5;
    const flcn::Mat4 expected{ 2, -5, 7, -10, 12, 15, 17, 20, -22, 25, 30, 32, 35, 40, 45, 50 };

    mat *= scalar;

    EXPECT_MAT_EQ(expected, mat);
}



/**************************************
 *    VECTOR MULTIPLICATION TESTS     *
 **************************************/

TYPED_TEST(Mat4VectorMultiplicationTests, ColumnVector_ReturnsATransformedColumnVector)
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


TYPED_TEST(Mat4VectorFractionalMultiplicationTests, ColumnVector_ReturnsATransformedColumnVectorWithPrecision)
{
    const auto transformedVector = this->_mat * this->_vec;
    EXPECT_VEC_EQ(this->_expectedColVector, transformedVector);
}


TEST(Mat4VectorMultiplicationTests, IdentityMatrixTimesColumnVector_ReturnsOriginalColumnVector)
{
    const flcn::Mat4<float> iMatrix = flcn::Mat4<float>::identity();
    const flcn::Vec4F vec{ 2.0f, 1.0f, 2.5f, 12.5f };

    const flcn::Vec4F transformedVector = iMatrix * vec;

    EXPECT_VEC_EQ(vec, transformedVector);
}


TEST(Mat4VectorMultiplicationTests, ColumnVector_MixedType_PromotesType)
{
    const flcn::Mat4 mat{ 1.0, 2.0, 3.0, 4.0 };
    const flcn::Vec4I vec{ 2, 1, 3, 4 };

    [[maybe_unused]] const auto transformedVector = mat * vec;
    static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
}


TYPED_TEST(Mat4VectorMultiplicationTests, RowVector_ReturnsATransformedRowVector)
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


TYPED_TEST(Mat4VectorFractionalMultiplicationTests, RowFloatVector_ReturnsARowVectorWithPrecision)
{
    const auto transformedVector = this->_vec * this->_mat;
    EXPECT_VEC_EQ(this->_expectedRowVector, transformedVector);
}


TEST(Mat4VectorMultiplicationTests, RowVectorTimesIdentityMatrix_ReturnsOriginalVector)
{
    const flcn::Mat4<float> iMatrix = flcn::Mat4<float>::identity();
    const flcn::Vec4F vec{ 2.0f, 1.0f, 2.5f, 12.5f };

    const flcn::Vec4F transformedVector = vec * iMatrix;

    EXPECT_VEC_EQ(vec, transformedVector);
}



TEST(Mat4VectorMultiplicationTests, RowVector_MixedType_PromotesType)
{
    const flcn::Mat4 mat{ 1.0, 2.0, 3.0, 4.0 };
    const flcn::Vec4I vec{ 2, 1, 3, 4 };

    [[maybe_unused]] const auto transformedVector = vec * mat;
    static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
}


TYPED_TEST(Mat4VectorMultiplicationTests, TimesEqualOperator_RowVector_ReturnsATransformedRowVector)
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


TEST(Mat4VectorMultiplicationTests, TimesEqualOperator_RowVector_IdentityMatrix_ReturnsOriginalRowVector)
{
    const flcn::Mat4<float> iMatrix = flcn::Mat4<float>::identity();
    flcn::Vec4F vec{ 2.0f, 1.0f, 3.0f, 12.0f };

    vec *= iMatrix;

    EXPECT_VEC_CONTAINS(vec, 2.0f, 1.0f, 3.0f, 12.0f);
}


TEST(Mat4VectorMultiplicationTests, TimesEqualOperator_MixedType_DoesNotPromoteType)
{
    const flcn::Mat4<double> iMatrix = flcn::Mat4<double>::identity();
    [[maybe_unused]] flcn::Vec4I vec{ 2, 1, 5, 4 };

    (void) (vec *= iMatrix);
    static_assert(std::is_same_v<decltype(vec)::value_type, int>);
}


TEST(Mat4VectorMultiplicationTests, TimesEqualOperator_MixedType_EnsuresMinimalPrecisionLoss)
{
    const flcn::Mat4 mat{ 2.5, 3.5, 0.5, 1.5, 12.0, 3.25, 5.0, 11.5, 5.0, 20.0, 12.0, 12.25, 15.0, 16.0, 13.75, 15.5 };
    flcn::Vec4 vec{ 10, 20, 30, 40 };
    const flcn::Vec4 expected{ 1015, 1340, 1015, 1232 };

    vec *= mat;

    EXPECT_VEC_EQ(expected, vec);
}



/**************************************
 *    MATRIX MULTIPLICATION TESTS     *
 **************************************/

TYPED_TEST(Mat4MatrixMultiplicationTests, TimesOperator_ReturnsMatrixProduct)
{
    const auto transformedVector = this->_matA * this->_matB;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        /// LOWERED EPSILON DUE TO NUMERICAL IMPRECISION WITH LARGE NUMS
        EXPECT_MAT_EQ(this->_expectedFloatingMat, transformedVector, std::is_same_v<TypeParam, float> ? 1e-4 : 1e-12);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntegralMat, transformedVector);
    }
}


TYPED_TEST(Mat4FractionalMultiplicationTests, TimesOperator_ReturnsMatrixWithPrecision)
{
    const auto transformedVector = this->_matA * this->_matB;
    EXPECT_MAT_EQ(this->_expectedMat, transformedVector);
}


TEST(Mat4MultiplicationTests, TimesOperator_IdentityMatrix_ReturnsOriginalMatrix)
{
    const flcn::Mat4<float> iMatrix = flcn::Mat4<float>::identity();
    const flcn::Mat4 mat{ 1.0f, 2.0f, 3.0f, 4.0f };

    const flcn::Mat4 matrixProduct = iMatrix * mat;

    EXPECT_MAT_EQ(mat, matrixProduct);
}



TEST(Mat4MultiplicationTests, TimesOperator_PromotesType)
{
    const flcn::Mat4 matA{ 1.0, 2.0, 3.0, 4.0 };
    const flcn::Mat4 matB{ 2, 1, 3, 4 };

    [[maybe_unused]] const auto transformedVector = matA * matB;
    static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
}


TYPED_TEST(Mat4MatrixMultiplicationTests, TimesEqualsOperator_PerformInPlaceMatrixMultiplication)
{
    auto transformedVector = this->_matA;
    transformedVector *= this->_matB;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        ///  NOTE: PRECISION LOWERED IN COMPARISION DUE TO FP ERRORS
        EXPECT_MAT_EQ(this->_expectedFloatingMat, transformedVector, std::is_same_v<TypeParam, float> ? 1e-4 : 1e-12);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntegralMat, transformedVector);
    }
}


TEST(Mat4MultiplicationTests, TimesEqualsOperator_IdentityMatrix_ReturnsOriginalMatrix)
{
    const flcn::Mat4<float> iMatrix = flcn::Mat4<float>::identity();
    flcn::Mat4 mat{ 1.0f, 2.0f, 3.0f, 4.0f };

    mat *= iMatrix;
    EXPECT_MAT_CONTAINS(
        std::vector{ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 4.0f },
        mat);
}


TEST(Mat4MultiplicationTests, TimesEqualsOperator_MixedType_DoesNotPromoteType)
{
    const flcn::Mat4<double> iMatrix = flcn::Mat4<double>::identity();
    flcn::Mat4 mat{ 1, 2, 3, 4 };

    mat *= iMatrix;
    static_assert(std::is_same_v<decltype(mat)::value_type, int>);
}


TEST(Mat4MultiplicationTests, TimesEqualsOperator_EnsuresMinimalPrecisionLoss)
{
    flcn::Mat4 matA{ 2.5, 3.5, 0.5, 1.5, 2.5, -12.5, 5.45, 23.25, 85.5, 12.5, 0.5, 1.75, 15.5, 13.5, 14.5, 16.5 };
    const flcn::Mat4 matB{ 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80 };
    const flcn::Mat4 expectedMatrix{
        220, 260, 300, 340, 1456, 1550, 1643, 1737, 876, 1377, 1878, 2380, 2140, 2440, 2740, 3040,
    };

    matA *= matB;

    EXPECT_MAT_EQ(expectedMatrix, matA);
}

/** @} */
