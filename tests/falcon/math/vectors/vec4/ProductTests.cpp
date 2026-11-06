/**
 * @file ProductTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verify @ref flcn::Vec4 dot product logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec4TestSetup.h"
#include "utils/MatrixUtils.h"

#include <falcon/math/matrices/Mat4.h>



/**
 * @addtogroup T_FALCON_Vec4_Product
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Vec4 dot product.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class Vec4DotProductTests: public testing::Test
    {
    protected:
        flcn::Vec4<T> _vecA;
        flcn::Vec4<T> _vecB;

        flcn::Vec4<T> _vecAOrthogonal;
        flcn::Vec4<T> _vecBOrthogonal;

        T _expectedDotProduct;

        T _expectedADotA;

        void SetUp() override
        {
            _vecA               = { T(2), T(3), T(4), T(5) };
            _vecB               = { T(6), T(7), T(8), T(9) };
            _vecAOrthogonal     = { T(3), T(0), T(4), T(0) };
            _vecBOrthogonal     = { T(0), T(5), T(0), T(6) };
            _expectedDotProduct = static_cast<T>(110);

            _expectedADotA = static_cast<T>(54);
        }
    };
    TYPED_TEST_SUITE(Vec4DotProductTests, SupportedArithmeticTypes);


    
    /**
     * @brief Test fixture for @ref flcn::Vec4 tensor product.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class Vec4TensorProductTests: public testing::Test
    {
    protected:
        flcn::Vec4<T> _vecA;
        flcn::Vec4<T> _vecB;
        flcn::Mat4<T> _expectedTensorProductInt, _expectedTensorProductFP;

        void SetUp() override
        {
            _vecA = flcn::Vec4{ T(1.32194213899999991), T(2.12304122299999998), T(3.02134123399999988),
                               T(4.01283041000000029) };
            _vecB = flcn::Vec4{ T(1.32194213899999991), T(2.12304122299999998), T(3.02134123399999988),
                               T(4.01283041000000029) };
            _expectedTensorProductInt = { flcn::Vec4{ T(1), T(2), T(3), T(4) }, flcn::Vec4{ T(2), T(4), T(6), T(8) },
                                          flcn::Vec4{ T(3), T(6), T(9), T(12) }, flcn::Vec4{ T(4), T(8), T(12), T(16) } };
            _expectedTensorProductFP  = { flcn::Vec4{ T(1.74753101886389506), T(2.80653765551779566),
                                                    T(3.99403829352285911), T(5.30472961563964684) },
                                          flcn::Vec4{ T(2.80653765551779566), T(4.50730403455733519),
                                                    T(6.41443198853168894), T(8.51940438133799205) },
                                          flcn::Vec4{ T(3.99403829352285911), T(6.41443198853168894),
                                                    T(9.12850285226864244), T(12.12412998278212584) },
                                          flcn::Vec4{ T(5.30472961563964684), T(8.51940438133799205),
                                                    T(12.12412998278212584), T(16.10280789942077107) } };
        }
    };
    TYPED_TEST_SUITE(Vec4TensorProductTests, SupportedSignedArithmeticTypes);

    

    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Vec4 VEC_A(1, 2, 3, 4);
        constexpr flcn::Vec4 VEC_B(5, 6, 7, 8);

        /// @test Verify that dot product of two 4D vectors return a valid scalar at compile time.
        constexpr auto DOT_PROD = VEC_A.dot(VEC_B);
        static_assert(DOT_PROD == 70);

        /// @test Verify that dot product of two 4D vectors using static variant of dot()
        ///       return a valid scalar at compile time.
        constexpr auto DOT_PROD_STATIC = flcn::Vec4<int>::dot(VEC_A, VEC_B);
        static_assert(DOT_PROD_STATIC == 70);


        /// @test Verify that tensor product of two 4D vectors return a valid 4D matrix at compile time.
        constexpr auto TENSOR_PROD = VEC_A.tensorProduct(VEC_B);
        static_assert(TENSOR_PROD[0] == flcn::Vec4{ 5, 10, 15, 20 });
        static_assert(TENSOR_PROD[1] == flcn::Vec4{ 6, 12, 18, 24 });
        static_assert(TENSOR_PROD[2] == flcn::Vec4{ 7, 14, 21, 28 });
        static_assert(TENSOR_PROD[3] == flcn::Vec4{ 8, 16, 24, 32 });

        /// @test Verify that tensor product of two 4D vectors using static variant of cross()
        ///       return a valid 4D matrix at compile time.
        constexpr auto TENSOR_PROD_STATIC = flcn::Vec4<int>::tensorProduct(VEC_A, VEC_B);
        static_assert(TENSOR_PROD_STATIC[0] == flcn::Vec4{ 5, 10, 15, 20 });
        static_assert(TENSOR_PROD_STATIC[1] == flcn::Vec4{ 6, 12, 18, 24 });
        static_assert(TENSOR_PROD_STATIC[2] == flcn::Vec4{ 7, 14, 21, 28 });
        static_assert(TENSOR_PROD_STATIC[3] == flcn::Vec4{ 8, 16, 24, 32 });

    } // namespace static_tests

} // namespace



/**************************************
 *            DOT PRODUCT             *
 **************************************/

/** @test Verify that the dot product of a vector with itself returns its squared magnitude. */
TYPED_TEST(Vec4DotProductTests, Dot_WithItselfReturnSquaredMagnitude)
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
TYPED_TEST(Vec4DotProductTests, Dot_OrthogonalVectorsReturnZero)
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
TYPED_TEST(Vec4DotProductTests, Dot_NonOrthogonalVectorsReturnNonZeroScalar)
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


/** @test Verify that the static variant of @ref flcn::Vec4::dot returns a non-zero scalar. */
TYPED_TEST(Vec4DotProductTests, StaticWrapper_Dot_NonOrthogonalVectorsReturnNonZeroScalar)
{
    const TypeParam dotProduct = flcn::Vec4<TypeParam>::dot(this->_vecA, this->_vecB);

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
TEST(Vec4DotProductTests, Dot_AntiParallelVectorsReturnsNegativeScalar)
{
    // Given two opposite vectors
    const flcn::Vec4 vecA(-1.0, 0.0, 0.0, 0.0);
    const flcn::Vec4 vecB(1.0, 0.0, 0.0, 0.0);

    // When dot with each other
    const double dotProduct = vecA.dot(vecB);

    // Then, the dot product is -1
    EXPECT_DOUBLE_EQ(-1.0, dotProduct);
}


/**
 * @test Verify that the dot product of a vector with another vector of different type
 *        returns a type promoted vector.
 */
TEST(Vec4DotProductTests, Dot_MixedType_PromotesType)
{
    // Given two vectors of different type
    const flcn::Vec4 vecA(7, 13, 29, 41);
    const flcn::Vec4 vecB(1.123456789, 2.123456789, 3.123456789, 4.123456789);

    // When dot with each other
    const auto dotProduct = vecA.dot(vecB);

    // Then, the dot product is type promoted
    static_assert(std::is_same_v<decltype(dotProduct), const double>);

    // Then, the dot product is non-zero
    EXPECT_DOUBLE_EQ(295.11111101, dotProduct);
}



/**************************************
 *        TENSOR PRODUCT TESTS        *
 **************************************/

TYPED_TEST(Vec4TensorProductTests, TensorProduct_BetweenTwoVectorsReturnsAValid2DMatrix)
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


TEST(Vec4TensorProductTests, TensorProduct_MixedTypes_PromotesType)
{
    const flcn::Vec4 vecA(2.0f, 3.0f, 4.0f, 5.0f);
    const flcn::Vec4 vecB(5.0, 6.0, 1.0, 2.0);

    [[maybe_unused]] const auto crossProduct = vecA.tensorProduct(vecB);
    static_assert(std::is_same_v<decltype(crossProduct), const flcn::Mat4<double>>);
}


TYPED_TEST(Vec4TensorProductTests, StaticWrapper_TensorProduct_BetweenTwoVectorsReturnsAValid2DMatrix)
{
    const auto tensorProduct = flcn::Vec4<TypeParam>::tensorProduct(this->_vecA, this->_vecB);
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedTensorProductFP, tensorProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedTensorProductInt, tensorProduct);
    }
}


TEST(Vec4TensorProductTests, StaticWrapper_TensorProduct_MixedTypes_PromotesType)
{
    const flcn::Vec4 vecA(2.0f, 3.0f, 4.0f, 5.0f);
    const flcn::Vec4 vecB(5.0, 6.0, 1.0, 2.0);

    [[maybe_unused]] const auto crossProduct = flcn::Vec4<float>::tensorProduct(vecA, vecB);
    static_assert(std::is_same_v<decltype(crossProduct), const flcn::Mat4<double>>);
}

/** @} */
