/**
 * @file DistanceTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 28, 2026
 *
 * @brief Verify @ref flcn::Vec3 distance (L1, L2, L3) calculation logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "CommonSetup.h"
#include "CVec2TestSetup.h"

#include <numbers>



/**
 * @addtogroup T_FALCON_CVec2_Dist
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref CVec2 distance functions.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class CVec2DistanceTests: public testing::Test
    {
    protected:
        flcn::CVec2<T> _vecA, _vecB;
        flcn::Magnitude<T> _dist;
        T _distSq, _distManhattan, _distChebyshev;


        void SetUp() override
        {
            _vecA = { T(2), T(7) };
            _vecB = { T(5), T(3) };

            _dist          = flcn::Magnitude<T>(5);
            _distSq        = T(25);
            _distManhattan = T(7);
            _distChebyshev = T(4);
        }
    };
    TYPED_TEST_SUITE(CVec2DistanceTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref CVec2 distance functions(signed types).
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class CVec2DistanceSignedTests: public testing::Test
    {
    protected:
        flcn::CVec2<T> _vecA, _vecB;
        flcn::Magnitude<T> _dist;
        T _distSq, _distManhattan, _distChebyshev;


        void SetUp() override
        {
            _vecA = { T(1), T(2) };
            _vecB = { T(-2), T(3) };

            _dist          = flcn::Magnitude<T>(3.1622776601683795);
            _distSq        = T(10);
            _distManhattan = T(4);
            _distChebyshev = T(3);
        }
    };
    TYPED_TEST_SUITE(CVec2DistanceSignedTests, SupportedSignedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::CVec2 VEC_A(2, 3);
        constexpr flcn::CVec2 VEC_B(5, 7);

        /// @test Verify that @ref CVec2::dist returns the euclidean distance.
        // TODO: Add back after creating flcn::sqrt
        // static_assert(VEC_A.dist(VEC_B) == 5);
        // static_assert(flcn::CVec2<int>::dist(VEC_A, VEC_B) == 5);


        /// @test Verify that @ref CVec2::distSq returns the squared distance.
        static_assert(VEC_A.distSq(VEC_B) == 25);
        /// @test Verify that @ref CVec2::distSq (static wrapper) returns the squared distance.
        static_assert(flcn::CVec2<int>::distSq(VEC_A, VEC_B) == 25);


        /// @test Verify that @ref CVec2::manhattanDist returns the manhattan distance.
        static_assert(VEC_A.manhattanDist(VEC_B) == 7);
        /// @test Verify that @ref CVec2::manhattanDist (static wrapper) returns the manhattan distance.
        static_assert(flcn::CVec2<int>::manhattanDist(VEC_A, VEC_B) == 7);


        /// @test Verify that @ref CVec2::chebyshevDist returns the chebyshev distance.
        static_assert(VEC_A.chebyshevDist(VEC_B) == 4);
        /// @test Verify that @ref CVec2::chebyshevDist (static wrapper) returns the chebyshev distance.
        static_assert(flcn::CVec2<int>::chebyshevDist(VEC_A, VEC_B) == 4);

    } // namespace
} // namespace



/**************************************
 *        EUCLIDEAN DISTANCE          *
 **************************************/

TYPED_TEST(CVec2DistanceTests, Dist_ReturnsEuclideanDistance)
{ EXPECT_MAG_EQ(this->_dist, this->_vecA.dist(this->_vecB)); }


TYPED_TEST(CVec2DistanceTests, Dist_IrrationalDistanceMaintainsPrecision)
{
    using T = TypeParam;
    const flcn::CVec2 v1{ T(0), T(0) };
    const flcn::CVec2 v2{ T(1), T(1) };

    using P                         = flcn::Magnitude<T>;
    constexpr auto expectedDistance = P(std::numbers::sqrt2);

    const auto distance = v1.dist(v2);
    EXPECT_MAG_EQ(expectedDistance, distance);
}


TYPED_TEST(CVec2DistanceTests, Dist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = flcn::Magnitude<TypeParam>(0);
    const auto distance = this->_vecA.dist(this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


TYPED_TEST(CVec2DistanceSignedTests, Dist_HandlesNegativeNumbers)
{
    const auto distance = this->_vecA.dist(this->_vecB);
    EXPECT_MAG_EQ(this->_dist, distance);
}


TYPED_TEST(CVec2DistanceTests, Dist_AlwaysReturnFloatingPointValue)
{
    [[maybe_unused]] const auto distance = this->_vecA.dist(this->_vecB);
    static_assert(std::is_floating_point_v<decltype(distance)>);
}


TYPED_TEST(CVec2DistanceTests, StaticWrapper_Dist_ReturnsEuclideanDistance)
{ EXPECT_MAG_EQ(this->_dist, flcn::CVec2<TypeParam>::dist(this->_vecA, this->_vecB)); }



TYPED_TEST(CVec2DistanceTests, StaticWrapper_Dist_IrrationalDistanceMaintainsPrecision)
{
    using T = TypeParam;
    const flcn::CVec2 v1{ T(0), T(0) };
    const flcn::CVec2 v2{ T(1), T(1) };

    using P                         = flcn::Magnitude<T>;
    constexpr auto expectedDistance = P(std::numbers::sqrt2);

    const auto distance = flcn::CVec2<T>::dist(v1, v2);

    EXPECT_MAG_EQ(expectedDistance, distance);
}


TYPED_TEST(CVec2DistanceTests, StaticWrapper_Dist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = flcn::Magnitude<TypeParam>(0);
    const auto distance = flcn::CVec2<TypeParam>::dist(this->_vecA, this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


TYPED_TEST(CVec2DistanceSignedTests, StaticWrapper_Dist_HandlesNegativeNumbers)
{
    const auto distance = flcn::CVec2<TypeParam>::dist(this->_vecA, this->_vecB);
    EXPECT_MAG_EQ(this->_dist, distance);
}


TYPED_TEST(CVec2DistanceTests, StaticWrapper_Dist_AlwaysReturnFloatingPointValue)
{
    [[maybe_unused]] const auto distance = this->_vecA.dist(this->_vecB);
    static_assert(std::is_floating_point_v<decltype(distance)>);
}



/**************************************
 *                                    *
 *    EUCLIDEAN DISTANCE (SQUARED)    *
 *                                    *
 **************************************/

TYPED_TEST(CVec2DistanceTests, DistSq_ReturnsSquaredEuclideanDistance)
{ EXPECT_MAG_EQ(this->_distSq, this->_vecA.distSq(this->_vecB)); }


TYPED_TEST(CVec2DistanceTests, DistSq_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = this->_vecA.distSq(this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


TYPED_TEST(CVec2DistanceSignedTests, DistSq_HandlesNegativeNumbers)
{
    const auto distance = this->_vecA.distSq(this->_vecB);
    EXPECT_MAG_EQ(this->_distSq, distance);
}


TYPED_TEST(CVec2DistanceTests, StaticWrapper_DistSq_ReturnsSquaredEuclideanDistance)
{ EXPECT_MAG_EQ(this->_distSq, flcn::CVec2<TypeParam>::distSq(this->_vecA, this->_vecB)); }


TYPED_TEST(CVec2DistanceTests, StaticWrapper_DistSq_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = flcn::CVec2<TypeParam>::distSq(this->_vecA, this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


TYPED_TEST(CVec2DistanceSignedTests, StaticWrapper_DistSq_HandlesNegativeNumbers)
{
    const auto distance = flcn::CVec2<TypeParam>::distSq(this->_vecA, this->_vecB);
    EXPECT_MAG_EQ(this->_distSq, distance);
}



/**************************************
 *        MANHATTAN DISTANCE          *
 **************************************/

TYPED_TEST(CVec2DistanceTests, ManhattanDist_ReturnsManhattanDistance)
{ EXPECT_MAG_EQ(this->_distManhattan, this->_vecA.manhattanDist(this->_vecB)); }


TYPED_TEST(CVec2DistanceTests, ManhattanDist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = this->_vecA.manhattanDist(this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


TYPED_TEST(CVec2DistanceSignedTests, ManhattanDist_HandlesNegativeNumbers)
{
    const auto distance = this->_vecA.manhattanDist(this->_vecB);
    EXPECT_MAG_EQ(this->_distManhattan, distance);
}


TYPED_TEST(CVec2DistanceTests, StaticWrapper_ManhattanDist_ReturnsManhattanDistance)
{ EXPECT_MAG_EQ(this->_distManhattan, flcn::CVec2<TypeParam>::manhattanDist(this->_vecA, this->_vecB)); }


TYPED_TEST(CVec2DistanceTests, StaticWrapper_ManhattanDist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = flcn::CVec2<TypeParam>::manhattanDist(this->_vecA, this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


TYPED_TEST(CVec2DistanceSignedTests, StaticWrapper_ManhattanDist_HandlesNegativeNumbers)
{
    const auto distance = flcn::CVec2<TypeParam>::manhattanDist(this->_vecA, this->_vecB);
    EXPECT_MAG_EQ(this->_distManhattan, distance);
}


/**************************************
 *        CHEBYSHEV DISTANCE          *
 **************************************/

TYPED_TEST(CVec2DistanceTests, ChebyshevDist_ReturnsChebyshevDistance)
{ EXPECT_MAG_EQ(this->_distChebyshev, this->_vecA.chebyshevDist(this->_vecB)); }



TYPED_TEST(CVec2DistanceTests, ChebyshevDist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = this->_vecA.chebyshevDist(this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


TYPED_TEST(CVec2DistanceSignedTests, ChebyshevDist_HandlesNegativeNumbers)
{
    const auto distance = this->_vecA.chebyshevDist(this->_vecB);
    EXPECT_MAG_EQ(this->_distChebyshev, distance);
}


TYPED_TEST(CVec2DistanceTests, StaticWrapper_ChebyshevDist_ReturnsChebyshevDistance)
{ EXPECT_MAG_EQ(this->_distChebyshev, flcn::CVec2<TypeParam>::chebyshevDist(this->_vecA, this->_vecB)); }


TYPED_TEST(CVec2DistanceTests, StaticWrapper_ChebyshevDist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = flcn::CVec2<TypeParam>::chebyshevDist(this->_vecA, this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


TYPED_TEST(CVec2DistanceSignedTests, StaticWrapper_ChebyshevDist_HandlesNegativeNumbers)
{
    const auto distance = flcn::CVec2<TypeParam>::chebyshevDist(this->_vecA, this->_vecB);
    EXPECT_MAG_EQ(this->_distChebyshev, distance);
}

/** @} */
