/**
 * @file PNormTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 12, 2026
 *
 * @brief Verify the @ref flcn::simd::Vec3 p-Norm length logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Vec3TestSetup.h"


/**
 * @addtogroup T_Falcon_Vec3_Norm
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec3 Manhattan Norm(Distance).
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class SimdVec3ManhattanNormTests: public testing::Test
    {
    protected:
        flcn::simd::Vec3<T> _vec;
        T _norm;

        void SetUp() override
        {
            _vec  = { T(1), T(2), T(4) };
            _norm = T(7);
        }
    };
    TYPED_TEST_SUITE(SimdVec3ManhattanNormTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec3 Chebyshev Norm(Distance).
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class SimdVec3ChebyshevNormTests: public testing::Test
    {
    protected:
        flcn::simd::Vec3<T> _vec;
        T _norm;

        void SetUp() override
        {
            _vec  = { T(1), T(2), T(4) };
            _norm = T(4);
        }
    };
    TYPED_TEST_SUITE(SimdVec3ChebyshevNormTests, SupportedArithmeticTypes);

} // namespace



/**************************************
 *           MANHATTAN NORM           *
 **************************************/

/** @test Verify that taking the manhattan norm of a non-unit vector returns non-unit scalar. */
TYPED_TEST(SimdVec3ManhattanNormTests, ReturnsSumOfAbsoluteValueOfComponents)
{
    const auto magnitude = this->_vec.manhattanNorm();
    EXPECT_MAG_EQ(this->_norm, magnitude);
}


/**
 * @test Verify that taking the manhattan norm of a non-unit vector using static variant of
 *        @ref flcn::simd::Vec3::manhattanNorm returns non-unit scalar.
 */
TYPED_TEST(SimdVec3ManhattanNormTests, StaticWrapper_ReturnsSumOfAbsoluteValueOfComponents)
{
    const auto magnitude = flcn::simd::Vec3<TypeParam>::manhattanNorm(this->_vec);
    EXPECT_MAG_EQ(this->_norm, magnitude);
}



/**************************************
 *           CHEBYSHEV NORM           *
 **************************************/

/** @test Verify that taking the chebyshev norm of a non-unit vector returns non-unit scalar. */
TYPED_TEST(SimdVec3ChebyshevNormTests, ReturnsLongestAbsoluteComponent)
{
    const auto magnitude = this->_vec.chebyshevNorm();

    EXPECT_MAG_EQ(this->_norm, magnitude);
}


/**
 * @test Verify that taking the chebyshev norm of a non-unit vector using static variant of
 *        @ref flcn::simd::Vec3::chebyshevNorm returns non-unit scalar.
 */
TYPED_TEST(SimdVec3ChebyshevNormTests, StaticWrapper_ReturnsLongestAbsoluteComponent)
{
    const auto magnitude = flcn::simd::Vec3<TypeParam>::chebyshevNorm(this->_vec);

    EXPECT_MAG_EQ(this->_norm, magnitude);
}

/** @} */
