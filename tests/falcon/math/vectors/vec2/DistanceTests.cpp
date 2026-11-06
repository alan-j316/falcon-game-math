/**
 * @file DistanceTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 23, 2026
 *
 * @brief Verify @ref flcn::Vec2 distance (L1, L2, L3) calculation logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "CommonSetup.h"
#include "Vec2TestSetup.h"

#include <numbers>



/**
 * @addtogroup T_FALCON_Vec2_Dist
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec2 distance functions.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec2DistanceTests: public testing::Test
    {
    protected:
        flcn::Vec2<T> _vecA, _vecB;
        T _dist;
        T _distSq, _distManhattan, _distChebyshev;


        void SetUp() override
        {
            _vecA = { T(2), T(7) };
            _vecB = { T(5), T(3) };

            _dist          = T(5);
            _distSq        = T(25);
            _distManhattan = T(7);
            _distChebyshev = T(4);
        }
    };
    TYPED_TEST_SUITE(Vec2DistanceTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref Vec2 distance functions(signed types).
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec2DistanceSignedTests: public testing::Test
    {
    protected:
        flcn::Vec2<T> _vecA, _vecB;
        T _dist;
        T _distSq, _distManhattan, _distChebyshev;


        void SetUp() override
        {
            _vecA = { T(1), T(2) };
            _vecB = { T(-2), T(3) };

            _dist          = T(3.1622776601683795);
            _distSq        = T(10);
            _distManhattan = T(4);
            _distChebyshev = T(3);
        }
    };
    TYPED_TEST_SUITE(Vec2DistanceSignedTests, SupportedSignedArithmeticTypes);

} // namespace



/**************************************
 *        EUCLIDEAN DISTANCE          *
 **************************************/

TYPED_TEST(Vec2DistanceTests, Dist_ReturnsEuclideanDistance)
{ EXPECT_MAG_EQ(this->_dist, this->_vecA.dist(this->_vecB)); }


TYPED_TEST(Vec2DistanceTests, Dist_IrrationalDistanceMaintainsPrecision)
{
    using T = TypeParam;
    const flcn::Vec2 v1{ T(0), T(0) };
    const flcn::Vec2 v2{ T(1), T(1) };

    constexpr auto expectedDistance = T(std::numbers::sqrt2);

    const auto distance = v1.dist(v2);
    EXPECT_MAG_EQ(expectedDistance, distance);
}


TYPED_TEST(Vec2DistanceTests, Dist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = this->_vecA.dist(this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


TYPED_TEST(Vec2DistanceSignedTests, Dist_HandlesNegativeNumbers)
{
    const auto distance = this->_vecA.dist(this->_vecB);
    EXPECT_MAG_EQ(this->_dist, distance);
}


TYPED_TEST(Vec2DistanceTests, StaticWrapper_Dist_ReturnsEuclideanDistance)
{ EXPECT_MAG_EQ(this->_dist, flcn::Vec2<TypeParam>::dist(this->_vecA, this->_vecB)); }



TYPED_TEST(Vec2DistanceTests, StaticWrapper_Dist_IrrationalDistanceMaintainsPrecision)
{
    using T = TypeParam;
    const flcn::Vec2 v1{ T(0), T(0) };
    const flcn::Vec2 v2{ T(1), T(1) };
    constexpr auto expectedDistance = T(std::numbers::sqrt2);

    const auto distance = flcn::Vec2<T>::dist(v1, v2);

    EXPECT_MAG_EQ(expectedDistance, distance);
}


TYPED_TEST(Vec2DistanceTests, StaticWrapper_Dist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = flcn::Vec2<TypeParam>::dist(this->_vecA, this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


TYPED_TEST(Vec2DistanceSignedTests, StaticWrapper_Dist_HandlesNegativeNumbers)
{
    const auto distance = flcn::Vec2<TypeParam>::dist(this->_vecA, this->_vecB);
    EXPECT_MAG_EQ(this->_dist, distance);
}


/**************************************
 *    EUCLIDEAN DISTANCE (SQUARED)    *
 **************************************/

TYPED_TEST(Vec2DistanceTests, DistSq_ReturnsSquaredEuclideanDistance)
{ EXPECT_MAG_EQ(this->_distSq, this->_vecA.distSq(this->_vecB)); }


TYPED_TEST(Vec2DistanceTests, DistSq_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = this->_vecA.distSq(this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


TYPED_TEST(Vec2DistanceSignedTests, DistSq_HandlesNegativeNumbers)
{
    const auto distance = this->_vecA.distSq(this->_vecB);
    EXPECT_MAG_EQ(this->_distSq, distance);
}


TYPED_TEST(Vec2DistanceTests, StaticWrapper_DistSq_ReturnsSquaredEuclideanDistance)
{ EXPECT_MAG_EQ(this->_distSq, flcn::Vec2<TypeParam>::distSq(this->_vecA, this->_vecB)); }


TYPED_TEST(Vec2DistanceTests, StaticWrapper_DistSq_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = flcn::Vec2<TypeParam>::distSq(this->_vecA, this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


TYPED_TEST(Vec2DistanceSignedTests, StaticWrapper_DistSq_HandlesNegativeNumbers)
{
    const auto distance = flcn::Vec2<TypeParam>::distSq(this->_vecA, this->_vecB);
    EXPECT_MAG_EQ(this->_distSq, distance);
}



/**************************************
 *        MANHATTAN DISTANCE          *
 **************************************/

TYPED_TEST(Vec2DistanceTests, ManhattanDist_ReturnsManhattanDistance)
{ EXPECT_MAG_EQ(this->_distManhattan, this->_vecA.manhattanDist(this->_vecB)); }


TYPED_TEST(Vec2DistanceTests, ManhattanDist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = this->_vecA.manhattanDist(this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


TYPED_TEST(Vec2DistanceSignedTests, ManhattanDist_HandlesNegativeNumbers)
{
    const auto distance = this->_vecA.manhattanDist(this->_vecB);
    EXPECT_MAG_EQ(this->_distManhattan, distance);
}


TYPED_TEST(Vec2DistanceTests, StaticWrapper_ManhattanDist_ReturnsManhattanDistance)
{ EXPECT_MAG_EQ(this->_distManhattan, flcn::Vec2<TypeParam>::manhattanDist(this->_vecA, this->_vecB)); }


TYPED_TEST(Vec2DistanceTests, StaticWrapper_ManhattanDist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = flcn::Vec2<TypeParam>::manhattanDist(this->_vecA, this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


TYPED_TEST(Vec2DistanceSignedTests, StaticWrapper_ManhattanDist_HandlesNegativeNumbers)
{
    const auto distance = flcn::Vec2<TypeParam>::manhattanDist(this->_vecA, this->_vecB);
    EXPECT_MAG_EQ(this->_distManhattan, distance);
}


/**************************************
 *        CHEBYSHEV DISTANCE          *
 **************************************/

TYPED_TEST(Vec2DistanceTests, ChebyshevDist_ReturnsChebyshevDistance)
{ EXPECT_MAG_EQ(this->_distChebyshev, this->_vecA.chebyshevDist(this->_vecB)); }



TYPED_TEST(Vec2DistanceTests, ChebyshevDist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = this->_vecA.chebyshevDist(this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


TYPED_TEST(Vec2DistanceSignedTests, ChebyshevDist_HandlesNegativeNumbers)
{
    const auto distance = this->_vecA.chebyshevDist(this->_vecB);
    EXPECT_MAG_EQ(this->_distChebyshev, distance);
}


TYPED_TEST(Vec2DistanceTests, StaticWrapper_ChebyshevDist_ReturnsChebyshevDistance)
{ EXPECT_MAG_EQ(this->_distChebyshev, flcn::Vec2<TypeParam>::chebyshevDist(this->_vecA, this->_vecB)); }


TYPED_TEST(Vec2DistanceTests, StaticWrapper_ChebyshevDist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = flcn::Vec2<TypeParam>::chebyshevDist(this->_vecA, this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


TYPED_TEST(Vec2DistanceSignedTests, StaticWrapper_ChebyshevDist_HandlesNegativeNumbers)
{
    const auto distance = flcn::Vec2<TypeParam>::chebyshevDist(this->_vecA, this->_vecB);
    EXPECT_MAG_EQ(this->_distChebyshev, distance);
}

/** @} */
