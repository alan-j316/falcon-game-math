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
#include "Vec3TestSetup.h"

#include <numbers>


/**
 * @addtogroup T_FALCON_Vec3_Dist
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec3 distance functions.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec3DistanceTests: public testing::Test
    {
    protected:
        flcn::Vec3<T> _vecA, _vecB;
        flcn::Magnitude<T> _dist;
        T _distSq, _distManhattan, _distChebyshev;


        void SetUp() override
        {
            _vecA = { T(2), T(7), T(2) };
            _vecB = { T(5), T(3), T(5) };

            _dist          = flcn::Magnitude<T>(5.830951894845301);
            _distSq        = T(34);
            _distManhattan = T(10);
            _distChebyshev = T(4);
        }
    };
    TYPED_TEST_SUITE(Vec3DistanceTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec3 distance functions(signed types).
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec3DistanceSignedTests: public testing::Test
    {
    protected:
        flcn::Vec3<T> _vecA, _vecB;
        flcn::Magnitude<T> _dist;
        T _distSq, _distManhattan, _distChebyshev;


        void SetUp() override
        {
            _vecA = { T(1), T(2), T(-1) };
            _vecB = { T(-2), T(3), T(-3) };

            _dist          = flcn::Magnitude<T>(3.7416573867739413);
            _distSq        = T(14);
            _distManhattan = T(6);
            _distChebyshev = T(3);
        }
    };
    TYPED_TEST_SUITE(Vec3DistanceSignedTests, SupportedSignedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Vec3 VEC_A(1, 2, 3);
        constexpr flcn::Vec3 VEC_B(3, 8, 6);

        // TODO: Add back after creating flcn::sqrt
        //// @test Verify that @ref Vec3::dist returns the euclidean distance.
        // static_assert(VEC_A.dist(VEC_B) == 7);
        // static_assert(flcn::Vec3<int>::dist(VEC_A, VEC_B) == 7);

        /// @test Verify that @ref Vec3::distSq returns the squared distance.
        static_assert(VEC_A.distSq(VEC_B) == 49);
        /// @test Verify that @ref Vec3::distSq (static wrapper) returns the squared distance.
        static_assert(flcn::Vec3<int>::distSq(VEC_A, VEC_B) == 49);


        /// @test Verify that @ref Vec3::manhattanDist returns the manhattan distance.
        static_assert(VEC_A.manhattanDist(VEC_B) == 11);
        /// @test Verify that @ref Vec3::manhattanDist (static wrapper) returns the manhattan distance.
        static_assert(flcn::Vec3<int>::manhattanDist(VEC_A, VEC_B) == 11);

        /// @test Verify that @ref Vec3::chebyshevDist returns the chebyshev distance.
        static_assert(VEC_A.chebyshevDist(VEC_B) == 6);
        /// @test Verify that @ref Vec3::chebyshevDist (static wrapper) returns the chebyshev distance.
        static_assert(flcn::Vec3<int>::chebyshevDist(VEC_A, VEC_B) == 6);

    } // namespace static_tests
} // namespace



/**************************************
 *        EUCLIDEAN DISTANCE          *
 **************************************/

/** @test Verify that the @ref flcn::Vec3::dist function returns the Euclidean distance. */
TYPED_TEST(Vec3DistanceTests, Dist_ReturnsEuclideanDistance)
{ EXPECT_MAG_EQ(this->_dist, this->_vecA.dist(this->_vecB)); }


/** @test Verify that the @ref flcn::Vec3::dist function maintains precision for irrational numbers. */
TYPED_TEST(Vec3DistanceTests, Dist_IrrationalDistanceMaintainsPrecision)
{
    using T = TypeParam;
    const flcn::Vec3 v1{ T(0), T(0), T(0) };
    const flcn::Vec3 v2{ T(1), T(1), T(0) };

    using P                         = flcn::Magnitude<T>;
    constexpr auto expectedDistance = P(std::numbers::sqrt2);

    const auto distance = v1.dist(v2);
    EXPECT_MAG_EQ(expectedDistance, distance);
}


/** @test Verify that the @ref flcn::Vec3::dist function returns zero for the same vector. */
TYPED_TEST(Vec3DistanceTests, Dist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = flcn::Magnitude<TypeParam>(0);
    const auto distance = this->_vecA.dist(this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @test Verify that the @ref flcn::Vec3::dist function handles negative coordinates. */
TYPED_TEST(Vec3DistanceSignedTests, Dist_HandlesNegativeNumbers)
{
    const auto distance = this->_vecA.dist(this->_vecB);
    EXPECT_MAG_EQ(this->_dist, distance);
}


/** @test Verify that the @ref flcn::Vec3::dist function always return a floating-point value. */
TYPED_TEST(Vec3DistanceTests, Dist_AlwaysReturnFloatingPointValue)
{
    [[maybe_unused]] const auto distance = this->_vecA.dist(this->_vecB);
    static_assert(std::is_floating_point_v<decltype(distance)>);
}


/** @test Verify that the static variant of  @ref flcn::Vec3::dist function returns the Euclidean distance. */
TYPED_TEST(Vec3DistanceTests, StaticWrapper_Dist_ReturnsEuclideanDistance)
{ EXPECT_MAG_EQ(this->_dist, flcn::Vec3<TypeParam>::dist(this->_vecA, this->_vecB)); }


/**
 * @test Verify that the static variant of @ref flcn::Vec3::dist function maintains precision
 *        for irrational numbers.
 */
TYPED_TEST(Vec3DistanceTests, StaticWrapper_Dist_IrrationalDistanceMaintainsPrecision)
{
    using T = TypeParam;
    const flcn::Vec3 v1{ T(0), T(0), T(0) };
    const flcn::Vec3 v2{ T(1), T(1), T(0) };

    using P                         = flcn::Magnitude<T>;
    constexpr auto expectedDistance = P(std::numbers::sqrt2);

    const auto distance = flcn::Vec3<T>::dist(v1, v2);

    EXPECT_MAG_EQ(expectedDistance, distance);
}


/** @test Verify that the @ref flcn::Vec3::dist function returns zero for the same vector. */
TYPED_TEST(Vec3DistanceTests, StaticWrapper_Dist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = flcn::Magnitude<TypeParam>(0);
    const auto distance = flcn::Vec3<TypeParam>::dist(this->_vecA, this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @test Verify that the static variant of @ref flcn::Vec3::dist function handles negative coordinates. */
TYPED_TEST(Vec3DistanceSignedTests, StaticWrapper_Dist_HandlesNegativeNumbers)
{
    const auto distance = flcn::Vec3<TypeParam>::dist(this->_vecA, this->_vecB);
    EXPECT_MAG_EQ(this->_dist, distance);
}


/** @test Verify that the static variant of @ref flcn::Vec3::dist function always return a floating-point value. */
TYPED_TEST(Vec3DistanceTests, StaticWrapper_Dist_AlwaysReturnFloatingPointValue)
{
    [[maybe_unused]] const auto distance = this->_vecA.dist(this->_vecB);
    static_assert(std::is_floating_point_v<decltype(distance)>);
}



/**************************************
 *    EUCLIDEAN DISTANCE (SQUARED)    *
 **************************************/

/** @test Verify that the @ref flcn::Vec3::distSq function returns the Euclidean distance (squared). */
TYPED_TEST(Vec3DistanceTests, DistSq_ReturnsSquaredEuclideanDistance)
{ EXPECT_MAG_EQ(this->_distSq, this->_vecA.distSq(this->_vecB)); }


/** @test Verify that the @ref flcn::Vec3::distSq function returns zero for the same vector. */
TYPED_TEST(Vec3DistanceTests, DistSq_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = this->_vecA.distSq(this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @test Verify that the @ref flcn::Vec3::distSq function handles negative coordinates. */
TYPED_TEST(Vec3DistanceSignedTests, DistSq_HandlesNegativeNumbers)
{
    const auto distance = this->_vecA.distSq(this->_vecB);
    EXPECT_MAG_EQ(this->_distSq, distance);
}


/**
 * @test Verify that the static variant of  @ref flcn::Vec3::distSq function
 *        returns the Euclidean distance (squared).
 */
TYPED_TEST(Vec3DistanceTests, StaticWrapper_DistSq_ReturnsSquaredEuclideanDistance)
{ EXPECT_MAG_EQ(this->_distSq, flcn::Vec3<TypeParam>::distSq(this->_vecA, this->_vecB)); }


/** @test Verify that the @ref flcn::Vec3::distSq function returns zero for the same vector. */
TYPED_TEST(Vec3DistanceTests, StaticWrapper_DistSq_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = flcn::Vec3<TypeParam>::distSq(this->_vecA, this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @test Verify that the static variant of @ref flcn::Vec3::distSq function handles negative coordinates. */
TYPED_TEST(Vec3DistanceSignedTests, StaticWrapper_DistSq_HandlesNegativeNumbers)
{
    const auto distance = flcn::Vec3<TypeParam>::distSq(this->_vecA, this->_vecB);
    EXPECT_MAG_EQ(this->_distSq, distance);
}


/**************************************
 *        MANHATTAN DISTANCE          *
 **************************************/

/** @test Verify that the @ref flcn::Vec3::manhattanDist function returns the Manhattan. */
TYPED_TEST(Vec3DistanceTests, ManhattanDist_ReturnsManhattanDistance)
{ EXPECT_MAG_EQ(this->_distManhattan, this->_vecA.manhattanDist(this->_vecB)); }


/** @test Verify that the @ref flcn::Vec3::manhattanDist function returns zero for the same vector. */
TYPED_TEST(Vec3DistanceTests, ManhattanDist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = this->_vecA.manhattanDist(this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @test Verify that the @ref flcn::Vec3::manhattanDist function handles negative coordinates. */
TYPED_TEST(Vec3DistanceSignedTests, ManhattanDist_HandlesNegativeNumbers)
{
    const auto distance = this->_vecA.manhattanDist(this->_vecB);
    EXPECT_MAG_EQ(this->_distManhattan, distance);
}


/**
 * @test Verify that the static variant of  @ref flcn::Vec3::manhattanDist function
 *        returns the Manhattan distance.
 */
TYPED_TEST(Vec3DistanceTests, StaticWrapper_ManhattanDist_ReturnsManhattanDistance)
{ EXPECT_MAG_EQ(this->_distManhattan, flcn::Vec3<TypeParam>::manhattanDist(this->_vecA, this->_vecB)); }


/** @test Verify that the @ref flcn::Vec3::manhattanDist function returns zero for the same vector. */
TYPED_TEST(Vec3DistanceTests, StaticWrapper_ManhattanDist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = flcn::Vec3<TypeParam>::manhattanDist(this->_vecA, this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @test Verify that the static variant of @ref flcn::Vec3::manhattanDist function handles negative coordinates. */
TYPED_TEST(Vec3DistanceSignedTests, StaticWrapper_ManhattanDist_HandlesNegativeNumbers)
{
    const auto distance = flcn::Vec3<TypeParam>::manhattanDist(this->_vecA, this->_vecB);
    EXPECT_MAG_EQ(this->_distManhattan, distance);
}


/**************************************
 *        CHEBYSHEV DISTANCE          *
 **************************************/


/** @test Verify that the @ref flcn::Vec3::chebyshevDist function returns the Chebyshev distance. */
TYPED_TEST(Vec3DistanceTests, ChebyshevDist_ReturnsChebyshevDistance)
{ EXPECT_MAG_EQ(this->_distChebyshev, this->_vecA.chebyshevDist(this->_vecB)); }


/** @test Verify that the @ref flcn::Vec3::chebyshevDist function returns zero for the same vector. */
TYPED_TEST(Vec3DistanceTests, ChebyshevDist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = this->_vecA.chebyshevDist(this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @test Verify that the @ref flcn::Vec3::chebyshevDist function handles negative coordinates. */
TYPED_TEST(Vec3DistanceSignedTests, ChebyshevDist_HandlesNegativeNumbers)
{
    const auto distance = this->_vecA.chebyshevDist(this->_vecB);
    EXPECT_MAG_EQ(this->_distChebyshev, distance);
}


/**
 * @test Verify that the static variant of  @ref flcn::Vec3::chebyshevDist function
 *        returns the Chebyshev distance.
 */
TYPED_TEST(Vec3DistanceTests, StaticWrapper_ChebyshevDist_ReturnsChebyshevDistance)
{ EXPECT_MAG_EQ(this->_distChebyshev, flcn::Vec3<TypeParam>::chebyshevDist(this->_vecA, this->_vecB)); }


/** @test Verify that the @ref flcn::Vec3::chebyshevDist function returns zero for the same vector. */
TYPED_TEST(Vec3DistanceTests, StaticWrapper_ChebyshevDist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = flcn::Vec3<TypeParam>::chebyshevDist(this->_vecA, this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @test Verify that the static variant of @ref flcn::Vec3::chebyshevDist function handles negative coordinates. */
TYPED_TEST(Vec3DistanceSignedTests, StaticWrapper_ChebyshevDist_HandlesNegativeNumbers)
{
    const auto distance = flcn::Vec3<TypeParam>::chebyshevDist(this->_vecA, this->_vecB);
    EXPECT_MAG_EQ(this->_distChebyshev, distance);
}

/** @} */
