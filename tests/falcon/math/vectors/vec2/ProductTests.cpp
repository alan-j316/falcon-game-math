/**
 * @file ProductTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 23, 2026
 *
 * @brief Verify @ref flcn::Vec2 dot and cross product logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"
#include "utils/MatrixUtils.h"

#include <falcon/math/matrices/Mat2.h>


/**
 * @addtogroup T_FALCON_Vec2_Product
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Vec2 dot product.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class Vec2DotProductTests: public testing::Test
    {
    protected:
        flcn::Vec2<T> _vecA;
        flcn::Vec2<T> _vecB;

        flcn::Vec2<T> _vecAOrthogonal;
        flcn::Vec2<T> _vecBOrthogonal;

        T _expectedDotProduct;

        T _expectedADotA;

        void SetUp() override
        {
            _vecA               = { T(13), T(2) };
            _vecB               = { T(5), T(5) };
            _vecAOrthogonal     = { T(13), T(0) };
            _vecBOrthogonal     = { T(0), T(13) };
            _expectedDotProduct = static_cast<T>(75);

            _expectedADotA = static_cast<T>(173);
        }
    };
    TYPED_TEST_SUITE(Vec2DotProductTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref flcn::Vec2 cross product.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class Vec2CrossProductTests: public testing::Test
    {
    protected:
        flcn::Vec2<T> _vecA;
        flcn::Vec2<T> _vecB;
        T _expectedCrossProduct;

        void SetUp() override
        {
            _vecA                 = { T(3), T(0) };
            _vecB                 = { T(0), T(4) };
            _expectedCrossProduct = T(12);
        }
    };
    TYPED_TEST_SUITE(Vec2CrossProductTests, SupportedSignedArithmeticTypes);


    // /**
    //  * @brief Test fixture for @ref flcn::Vec2 tensor product.
    //  *
    //  * @tparam T The scalar type (e.g., float, double) used for the vectors.
    //  */
    // template <typename T>
    // class Vec2TensorProductTests: public testing::Test
    // {
    // protected:
    //     flcn::Vec2<T> _vecA;
    //     flcn::Vec2<T> _vecB;
    //     flcn::Mat2<T> _expectedTensorProductInt, _expectedTensorProductFP;
    //
    //     void SetUp() override
    //     {
    //         _vecA                     = flcn::Vec2{ T(1.23412341000000003), T(2.21341324399999984) };
    //         _vecB                     = { T(1.23412341000000003), T(2.21341324399999984) };
    //         _expectedTensorProductFP  = { flcn::Vec2{ T(1.52306059111002812), T(2.73162510042444184) },
    //                                       flcn::Vec2{ T(2.73162510042444184), T(4.89919818871460322) } };
    //         _expectedTensorProductInt = { flcn::Vec2{ T(1), T(2) }, flcn::Vec2{ T(2), T(4) } };
    //     }
    // };
    // TYPED_TEST_SUITE(Vec2TensorProductTests, SupportedSignedArithmeticTypes);

} // namespace



/**************************************
 *         DOT PRODUCT TESTS          *
 **************************************/

TYPED_TEST(Vec2DotProductTests, Dot_WithItselfReturnSquaredMagnitude)
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


TYPED_TEST(Vec2DotProductTests, Dot_OrthogonalVectorsReturnZero)
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


TYPED_TEST(Vec2DotProductTests, Dot_NonOrthogonalVectorsReturnNonZeroScalar)
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


TYPED_TEST(Vec2DotProductTests, StaticWrapper_Dot_NonOrthogonalVectorsReturnNonZeroScalar)
{
    const TypeParam dotProduct = flcn::Vec2<TypeParam>::dot(this->_vecA, this->_vecB);

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


TEST(Vec2DotProduct, Dot_AntiParallelVectorsReturnsNegativeScalar)
{
    // Given two opposite vectors
    const flcn::Vec2 vecA(-1.0, 0.0);
    const flcn::Vec2 vecB(1.0, 0.0);

    // When dot with each other
    const double dotProduct = vecA.dot(vecB);

    // Then, the dot product is -1
    EXPECT_DOUBLE_EQ(-1.0, dotProduct);
}


/**************************************
 *        CROSS PRODUCT TESTS         *
 **************************************/

TEST(Vec2CrossProduct, Cross_WithItself_ReturnsZeroVector)
{
    const flcn::Vec2 vec(2.0f, 1.0f);

    const float crossProduct = vec.cross(vec);

    EXPECT_FLOAT_EQ(0.0f, crossProduct);
}


TYPED_TEST(Vec2CrossProductTests, Cross_TwoNonParallelVectorsReturnsNewProduct)
{
    const TypeParam crossProduct = this->_vecA.cross(this->_vecB);

    if constexpr (std::is_same_v<TypeParam, double>)
    {
        EXPECT_DOUBLE_EQ(this->_expectedCrossProduct, crossProduct);
    }
    else if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_FLOAT_EQ(this->_expectedCrossProduct, crossProduct);
    }
    else
    {
        EXPECT_EQ(this->_expectedCrossProduct, crossProduct);
    }
}


TYPED_TEST(Vec2CrossProductTests, StaticWrapper_Cross_TwoNonParallelVectorsReturnsNewProduct)
{
    const TypeParam crossProduct = flcn::Vec2<TypeParam>::cross(this->_vecA, this->_vecB);
    if constexpr (std::is_same_v<TypeParam, double>)
    {
        EXPECT_DOUBLE_EQ(this->_expectedCrossProduct, crossProduct);
    }
    else if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_FLOAT_EQ(this->_expectedCrossProduct, crossProduct);
    }
    else
    {
        EXPECT_EQ(this->_expectedCrossProduct, crossProduct);
    }
}



// /**************************************
//  *        TENSOR PRODUCT TESTS        *
//  **************************************/
//
// TYPED_TEST(Vec2TensorProductTests, TensorProduct_BetweenTwoVectorsReturnsAValid2DMatrix)
// {
//     const auto tensorProduct = this->_vecA.tensorProduct(this->_vecB);
//     if constexpr (std::is_floating_point_v<TypeParam>)
//     {
//         EXPECT_MAT_EQ(this->_expectedTensorProductFP, tensorProduct);
//     }
//     else
//     {
//         EXPECT_MAT_EQ(this->_expectedTensorProductInt, tensorProduct);
//     }
// }
//
//
// TEST(Vec2TensorProduct, TensorProduct_MixedTypes_PromotesType)
// {
//     const flcn::Vec2 vecA(2.0f, 3.0f);
//     const flcn::Vec2 vecB(5.0, 6.0);
//
//     [[maybe_unused]] const auto crossProduct = vecA.tensorProduct(vecB);
//     static_assert(std::is_same_v<decltype(crossProduct), const flcn::Mat2<double>>);
// }
//
//
// TYPED_TEST(Vec2TensorProductTests, StaticWrapper_TensorProduct_BetweenTwoVectorsReturnsAValid2DMatrix)
// {
//     const auto tensorProduct = flcn::Vec2<TypeParam>::tensorProduct(this->_vecA, this->_vecB);
//     if constexpr (std::is_floating_point_v<TypeParam>)
//     {
//         EXPECT_MAT_EQ(this->_expectedTensorProductFP, tensorProduct);
//     }
//     else
//     {
//         EXPECT_MAT_EQ(this->_expectedTensorProductInt, tensorProduct);
//     }
// }
//
//
// TEST(Vec2TensorProduct, StaticWrapper_TensorProduct_MixedTypes_PromotesType)
// {
//     const flcn::Vec2 vecA(2.0f, 3.0f);
//     const flcn::Vec2 vecB(5.0, 6.0);
//
//     [[maybe_unused]] const auto crossProduct = flcn::Vec2<float>::tensorProduct(vecA, vecB);
//     static_assert(std::is_same_v<decltype(crossProduct), const flcn::Mat2<double>>);
// }

/** @} */
