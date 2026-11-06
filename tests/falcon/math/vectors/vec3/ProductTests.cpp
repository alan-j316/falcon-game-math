/**
 * @file ProductTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify @ref flcn::Vec3 dot and cross product logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"
#include "utils/MatrixUtils.h"

#include <falcon/math/matrices/Mat3.h>



/**
 * @addtogroup T_FALCON_Vec3_Product
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Vec3 dot product.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class Vec3DotProductTests: public testing::Test
    {
    protected:
        flcn::Vec3<T> _vecA;
        flcn::Vec3<T> _vecB;

        flcn::Vec3<T> _vecAOrthogonal;
        flcn::Vec3<T> _vecBOrthogonal;

        T _expectedDotProduct;

        T _expectedADotA;

        void SetUp() override
        {
            _vecA               = { T(2), T(3), T(4) };
            _vecB               = { T(6), T(7), T(8) };
            _vecAOrthogonal     = { T(3), T(0), T(4) };
            _vecBOrthogonal     = { T(0), T(5), T(0) };
            _expectedDotProduct = static_cast<T>(65);

            _expectedADotA = static_cast<T>(29);
        }
    };
    TYPED_TEST_SUITE(Vec3DotProductTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::Vec3 cross product.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class Vec3CrossProductTests: public testing::Test
    {
    protected:
        flcn::Vec3<T> _vecA;
        flcn::Vec3<T> _vecB;
        flcn::Vec3<T> _expectedCrossProduct;

        void SetUp() override
        {
            _vecA                 = { T(2), T(3), T(4) };
            _vecB                 = { T(5), T(6), T(7) };
            _expectedCrossProduct = { T(-3), T(6), T(-3) };
        }
    };
    TYPED_TEST_SUITE(Vec3CrossProductTests, SupportedSignedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::Vec3 tensor product.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class Vec3TensorProductTests: public testing::Test
    {
    protected:
        flcn::Vec3<T> _vecA;
        flcn::Vec3<T> _vecB;
        flcn::Mat3<T> _expectedTensorProductInt, _expectedTensorProductFP;

        void SetUp() override
        {
            _vecA = flcn::Vec3{ T(1.32194213899999991), T(2.12304122299999998), T(3.02134123399999988) };
            _vecB = flcn::Vec3{ T(1.32194213899999991), T(2.12304122299999998), T(3.02134123399999988) };
            _expectedTensorProductFP = {
                flcn::Vec3{ T(1.74753101886389506), T(2.80653765551779566), T(3.99403829352285911) },
                flcn::Vec3{ T(2.80653765551779566), T(4.50730403455733519), T(6.41443198853168894) },
                flcn::Vec3{ T(3.99403829352285911), T(6.41443198853168894), T(9.12850285226864244) }
            };
            _expectedTensorProductInt = { flcn::Vec3{ T(1), T(2), T(3) }, flcn::Vec3{ T(2), T(4), T(6) },
                                          flcn::Vec3{ T(3), T(6), T(9) } };
        }
    };
    TYPED_TEST_SUITE(Vec3TensorProductTests, SupportedSignedArithmeticTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Vec3 VEC_A(1, 2, 3);
        constexpr flcn::Vec3 VEC_B(4, 5, 6);


        /// @test Verify that dot product of two 3D vectors return a valid scale at compile time.
        constexpr auto DOT_PROD = VEC_A.dot(VEC_B);
        static_assert(DOT_PROD == 32);

        /// @test Verify that dot product of two 3D vectors using static variant of cross()
        ///       return a valid scale at compile time.
        constexpr auto DOT_PROD_STATIC = flcn::Vec3<int>::dot(VEC_A, VEC_B);
        static_assert(DOT_PROD_STATIC == 32);

        /// @test Verify that cross product of two 2D vectors return a valid 3D vector at compile time.
        constexpr auto CROSS_PROD = VEC_A.cross(VEC_B);
        static_assert(CROSS_PROD.x() == -3);
        static_assert(CROSS_PROD.y() == 6);
        static_assert(CROSS_PROD.z() == -3);

        /// @test Verify that cross product of two 3D vectors using static variant of cross()
        ///       return a valid 3D vector at compile time.
        constexpr auto CROSS_PROD_STATIC = flcn::Vec3<int>::cross(VEC_A, VEC_B);
        static_assert(CROSS_PROD_STATIC.x() == -3);
        static_assert(CROSS_PROD_STATIC.y() == 6);
        static_assert(CROSS_PROD_STATIC.z() == -3);


        /// @test Verify that tensor product of two 3D vectors return a valid 3D matrix at compile time.
        constexpr auto TENSOR_PROD = VEC_A.tensorProduct(VEC_B);
        static_assert(TENSOR_PROD[0] == flcn::Vec3{ 4, 8, 12 });
        static_assert(TENSOR_PROD[1] == flcn::Vec3{ 5, 10, 15 });
        static_assert(TENSOR_PROD[2] == flcn::Vec3{ 6, 12, 18 });

        /// @test Verify that tensor product of two 3D vectors using static variant of cross()
        ///       return a valid 3D matrix at compile time.
        constexpr auto TENSOR_PROD_STATIC = flcn::Vec3<int>::tensorProduct(VEC_A, VEC_B);
        static_assert(TENSOR_PROD_STATIC[0] == flcn::Vec3{ 4, 8, 12 });
        static_assert(TENSOR_PROD_STATIC[1] == flcn::Vec3{ 5, 10, 15 });
        static_assert(TENSOR_PROD_STATIC[2] == flcn::Vec3{ 6, 12, 18 });

    } // namespace static_tests

} // namespace



/**************************************
 *         DOT PRODUCT TESTS          *
 **************************************/

/** @test Verify that the dot product of a vector with itself returns its squared magnitude. */
TYPED_TEST(Vec3DotProductTests, Dot_WithItselfReturnSquaredMagnitude)
{

    const TypeParam dotProduct = this->_vecA.dot(this->_vecA);

    if constexpr (std::is_same_v<TypeParam, double>)
    {
        EXPECT_DOUBLE_EQ(this->_expectedADotA, dotProduct);
    }
    else if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_FLOAT_EQ(this->_expectedADotA, dotProduct);
    }
    else
    {
        EXPECT_EQ(this->_expectedADotA, dotProduct);
    }
}


/** @test Verify that the dot product of a vector with an orthogonal vector returns zero. */
TYPED_TEST(Vec3DotProductTests, Dot_OrthogonalVectorsReturnZero)
{
    const TypeParam dotProduct = this->_vecAOrthogonal.dot(this->_vecBOrthogonal);

    if constexpr (std::is_same_v<TypeParam, double>)
    {
        EXPECT_DOUBLE_EQ(0.0, dotProduct);
    }
    else if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_FLOAT_EQ(0.0f, dotProduct);
    }
    else
    {
        EXPECT_EQ(0, dotProduct);
    }
}


/** @test Verify that the dot product of a vector with a non-orthogonal vector returns a non-zero scalar. */
TYPED_TEST(Vec3DotProductTests, Dot_NonOrthogonalVectorsReturnNonZeroScalar)
{
    const TypeParam dotProduct = this->_vecA.dot(this->_vecB);

    if constexpr (std::is_same_v<TypeParam, double>)
    {
        EXPECT_DOUBLE_EQ(this->_expectedDotProduct, dotProduct);
    }
    else if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_FLOAT_EQ(this->_expectedDotProduct, dotProduct);
    }
    else
    {
        EXPECT_EQ(this->_expectedDotProduct, dotProduct);
    }
}


/** @test Verify that the static variant of @ref flcn::Vec3::dot returns a non-zero scalar. */
TYPED_TEST(Vec3DotProductTests, StaticWrapper_Dot_NonOrthogonalVectorsReturnNonZeroScalar)
{
    const TypeParam dotProduct = flcn::Vec3<TypeParam>::dot(this->_vecA, this->_vecB);

    if constexpr (std::is_same_v<TypeParam, double>)
    {
        EXPECT_DOUBLE_EQ(this->_expectedDotProduct, dotProduct);
    }
    else if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_FLOAT_EQ(this->_expectedDotProduct, dotProduct);
    }
    else
    {
        EXPECT_EQ(this->_expectedDotProduct, dotProduct);
    }
}


/**
 * @test Verify that the dot product of a vector with another vector in opposite direction
 *        returns a negative scalar.
 */
TEST(Vec3DotProduct, Dot_AntiParallelVectorsReturnsNegativeScalar)
{
    // Given two opposite vectors
    const flcn::Vec3 vecA(-1.0, 0.0, 0.0);
    const flcn::Vec3 vecB(1.0, 0.0, 0.0);

    // When dot with each other
    const double dotProduct = vecA.dot(vecB);

    // Then, the dot product is -1
    EXPECT_DOUBLE_EQ(-1.0, dotProduct);
}


/**
 * @test Verify that the dot product of a vector with another vector of different type
 *        returns a type promoted vector.
 */
TEST(Vec3DotProduct, Dot_MixedType_PromotesType)
{
    // Given two vectors of different type
    const flcn::Vec3 vecA(7, 13, 29);
    const flcn::Vec3 vecB(1.123456789, 2.123456789, 3.123456789);

    // When dot with each other
    const auto dotProduct = vecA.dot(vecB);

    // Then, the dot product is type promoted
    static_assert(std::is_same_v<decltype(dotProduct), const double>);

    // Then, the dot product is non-zero
    EXPECT_DOUBLE_EQ(126.049382661, dotProduct);
}


/**************************************
 *        CROSS PRODUCT TESTS         *
 **************************************/

/**
 * @test Verify that the cross product of vector aligned with x-axis and a vector aligned with y-axis
 *        returns a vector aligned with the z-axis.
 */
TEST(Vec3CrossProduct, BetweenAxisAlignedXAndYVectorsReturnsZ)
{
    const flcn::Vec3 xAxis(1.0f, 0.0f, 0.0f);
    const flcn::Vec3 yAxis(0.0f, 1.0f, 0.0f);
    const flcn::Vec3 expectedCrossProduct(0.0f, 0.0f, 1.0f);

    const flcn::Vec3 crossProduct = xAxis.cross(yAxis);

    EXPECT_VEC_EQ(expectedCrossProduct, crossProduct);
}


/**
 * @test Verify that the cross product of vector aligned with y-axis and a vector aligned with x-axis
 *        returns a vector aligned with the negative z-axis.
 */
TEST(Vec3CrossProduct, BetweenAxisAlignedYAndZVectorsReturnsNegativeZ)
{
    const flcn::Vec3 yAxis(0.0f, 1.0f, 0.0f);
    const flcn::Vec3 xAxis(1.0f, 0.0f, 0.0f);
    const flcn::Vec3 expectedCrossProduct(0.0f, 0.0f, -1.0f);

    const flcn::Vec3 crossProduct = yAxis.cross(xAxis);

    EXPECT_VEC_EQ(expectedCrossProduct, crossProduct);
}


/**
 * @test Verify that the cross product of vector aligned with z-axis and a vector aligned with y-axis
 *        returns a vector aligned with the negative x-axis.
 */
TEST(Vec3CrossProduct, BetweenAxisAlignedZAndYVectorsReturnsNegativeX)
{
    // Arrange
    const flcn::Vec3 zAxis(0.0f, 0.0f, 1.0f);
    const flcn::Vec3 yAxis(0.0f, 1.0f, 0.0f);
    const flcn::Vec3 expectedCrossProduct(-1.0f, 0.0f, 0.0f);

    // Act
    const flcn::Vec3 crossProduct = zAxis.cross(yAxis);

    // Assert
    EXPECT_VEC_EQ(expectedCrossProduct, crossProduct);
}


/** @test Verify that the cross product of vector with self is a zero-vector. */
TEST(Vec3CrossProduct, Cross_WithItself_ReturnsZeroVector)
{
    const flcn::Vec3 vec(0.0f, 0.0f, 1.0f);

    const flcn::Vec3 crossProduct = vec.cross(vec);

    EXPECT_VEC_ZERO(crossProduct);
}


/** @test Verify that the cross product of vector with a non-parallel vector returns a new vector. */
TYPED_TEST(Vec3CrossProductTests, Cross_TwoNonParallelVectorsReturnsNewProduct)
{
    const flcn::Vec3 crossProduct = this->_vecA.cross(this->_vecB);

    EXPECT_VEC_EQ(this->_expectedCrossProduct, crossProduct);
}


/**
 * @test Verify that the cross product of vector with a non-parallel vector
 *        returns a new vector perpendicular to both.
 */
TYPED_TEST(Vec3CrossProductTests, BetweenTwoNonParallelVectorsReturnAVectorPerpendicularToBoth)
{
    const flcn::Vec3 crossProduct = this->_vecA.cross(this->_vecB);

    // Orientation Check: Dot must be zero
    if constexpr (std::is_same_v<TypeParam, double>)
    {
        EXPECT_DOUBLE_EQ(0.0, this->_vecA.dot(crossProduct));
        EXPECT_DOUBLE_EQ(0.0, this->_vecB.dot(crossProduct));
    }
    else if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_FLOAT_EQ(0.0f, this->_vecA.dot(crossProduct));
        EXPECT_FLOAT_EQ(0.0f, this->_vecB.dot(crossProduct));
    }
    else
    {
        EXPECT_EQ(0, this->_vecA.dot(crossProduct));
        EXPECT_EQ(0, this->_vecB.dot(crossProduct));
    }
}


/**
 * @test Verify that the cross product of vector with a non-parallel vector using static variant of
 *        @ref flcn::Vec3::cross returns a new vector.
 */
TYPED_TEST(Vec3CrossProductTests, StaticWrapper_Cross_TwoNonParallelVectorsReturnsNewProduct)
{
    const flcn::Vec3 crossProduct = flcn::Vec3<TypeParam>::cross(this->_vecA, this->_vecB);

    EXPECT_VEC_EQ(this->_expectedCrossProduct, crossProduct);
}


/**
 * @test Verify that the cross product of vector with a non-parallel vector using static variant of
 *        @ref flcn::Vec3::cross returns a new vector perpendicular to both.
 */
TYPED_TEST(Vec3CrossProductTests, StaticWrapper_BetweenTwoNonParallelVectorsReturnAVectorPerpendicularToBoth)
{
    const flcn::Vec3 crossProduct = flcn::Vec3<TypeParam>::cross(this->_vecA, this->_vecB);

    // Orientation Check: Dot must be zero
    if constexpr (std::is_same_v<TypeParam, double>)
    {
        EXPECT_DOUBLE_EQ(0.0, this->_vecA.dot(crossProduct));
        EXPECT_DOUBLE_EQ(0.0, this->_vecB.dot(crossProduct));
    }
    else if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_FLOAT_EQ(0.0f, this->_vecA.dot(crossProduct));
        EXPECT_FLOAT_EQ(0.0f, this->_vecB.dot(crossProduct));
    }
    else
    {
        EXPECT_EQ(0, this->_vecA.dot(crossProduct));
        EXPECT_EQ(0, this->_vecB.dot(crossProduct));
    }
}


/**
 * @test Verify that the cross product between non-parallel vectors is anti-commutative.
 *        Anti-Commutativity: \f$ \mathbf{a}\times\mathbf{b} = -(\mathbf{b}\times\mathbf{a}) \f$
 */
TYPED_TEST(Vec3CrossProductTests, IsAntiCommutative)
{
    flcn::Vec3 crossProduct1 = flcn::Vec3<TypeParam>::cross(this->_vecA, this->_vecB);
    flcn::Vec3 crossProduct2 = flcn::Vec3<TypeParam>::cross(this->_vecB, this->_vecA);

    EXPECT_VEC_EQ(crossProduct1, -1.0f * crossProduct2);
}


/**
 * @test Verify that the cross product between parallel vectors is commutative.
 *        Commutativity: \f$ \mathbf{a}\times\mathbf{b} = \mathbf{b}\times\mathbf{a} \f$,
 *        **given a and b are scalar multiples of each other**.
 */
TYPED_TEST(Vec3CrossProductTests, BetweenParallelVectorIsCommutatives)
{
    const flcn::Vec3 vecB    = TypeParam(2) * this->_vecA;
    flcn::Vec3 crossProduct1 = flcn::Vec3<TypeParam>::cross(this->_vecA, vecB);
    flcn::Vec3 crossProduct2 = flcn::Vec3<TypeParam>::cross(vecB, this->_vecA);

    EXPECT_VEC_EQ(crossProduct1, crossProduct2);
}


/** @test Verify that the cross product between two differently typed vectors promote type. */
TEST(Vec3CrossProduct, TensorProduct_MixedTypes_PromotesType)
{
    const flcn::Vec3 vecA(2.0f, 3.0f, 4.0f);
    const flcn::Vec3 vecB(5.0, 6.0, 7.0);

    [[maybe_unused]] const flcn::Vec3 crossProduct = vecA.cross(vecB);

    static_assert(std::is_same_v<typename decltype(crossProduct)::value_type, double>);
}



/**************************************
 *        TENSOR PRODUCT TESTS        *
 **************************************/

TYPED_TEST(Vec3TensorProductTests, TensorProduct_BetweenTwoVectorsReturnsAValid2DMatrix)
{
    const auto tensorProduct = this->_vecA.tensorProduct(this->_vecB);
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedTensorProductFP, tensorProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedTensorProductInt, tensorProduct);
    }
}


TEST(Vec3TensorProduct, TensorProduct_MixedTypes_PromotesType)
{
    const flcn::Vec3 vecA(2.0f, 3.0f, 4.0f);
    const flcn::Vec3 vecB(5.0, 6.0, 7.0);

    [[maybe_unused]] const auto crossProduct = vecA.tensorProduct(vecB);
    static_assert(std::is_same_v<decltype(crossProduct), const flcn::Mat3<double>>);
}


TYPED_TEST(Vec3TensorProductTests, StaticWrapper_TensorProduct_BetweenTwoVectorsReturnsAValid2DMatrix)
{
    const auto tensorProduct = flcn::Vec3<TypeParam>::tensorProduct(this->_vecA, this->_vecB);
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedTensorProductFP, tensorProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedTensorProductInt, tensorProduct);
    }
}


TEST(Vec3TensorProduct, StaticWrapper_TensorProduct_MixedTypes_PromotesType)
{
    const flcn::Vec3 vecA(2.0f, 3.0f, 4.0f);
    const flcn::Vec3 vecB(5.0, 6.0, 7.0);

    [[maybe_unused]] const auto crossProduct = flcn::Vec3<float>::tensorProduct(vecA, vecB);
    static_assert(std::is_same_v<decltype(crossProduct), const flcn::Mat3<double>>);
}

/** @} */
