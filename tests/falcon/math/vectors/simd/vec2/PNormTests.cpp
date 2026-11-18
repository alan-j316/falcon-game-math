/**
 * @file PNormTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 24, 2026
 *
 * @brief Verify the @ref flcn::simd::Vec2 p-Norm length logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Vec2TestSetup.h"



/**
 * @addtogroup T_Falcon_Vec2_Norm
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec2 Manhattan Norm(Distance).
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class SimdVec2ManhattanNormTests: public testing::Test
    {
    protected:
        flcn::simd::Vec2<T> _vec;
        T _norm;

        void SetUp() override
        {
            _vec  = { T(1), T(2) };
            _norm = T(3);
        }
    };
    TYPED_TEST_SUITE(SimdVec2ManhattanNormTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec2 Chebyshev Norm(Distance).
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class SimdVec2ChebyshevNormTests: public testing::Test
    {
    protected:
        flcn::simd::Vec2<T> _vec;
        T _norm;

        void SetUp() override
        {
            _vec  = { T(1), T(2) };
            _norm = T(2);
        }
    };
    TYPED_TEST_SUITE(SimdVec2ChebyshevNormTests, SupportedArithmeticTypes);
} // namespace



/**************************************
 *           MANHATTAN NORM           *
 **************************************/

/** @test Verify that taking the manhattan norm of a non-unit vector returns non-unit scalar. */
TYPED_TEST(SimdVec2ManhattanNormTests, ReturnsSumOfAbsoluteValueOfComponents)
{
    const auto magnitude = this->_vec.manhattanNorm();
    EXPECT_MAG_EQ(this->_norm, magnitude);
}


/**
 * @test Verify that taking the manhattan norm of a non-unit vector using static variant of
 *        @ref flcn::simd::Vec2::manhattanNorm returns non-unit scalar.
 */
TYPED_TEST(SimdVec2ManhattanNormTests, StaticWrapper_ReturnsSumOfAbsoluteValueOfComponents)
{
    const auto magnitude = flcn::simd::Vec2<TypeParam>::manhattanNorm(this->_vec);
    EXPECT_MAG_EQ(this->_norm, magnitude);
}



/**************************************
 *           CHEBYSHEV NORM           *
 **************************************/

/** @test Verify that taking the chebyshev norm of a non-unit vector returns non-unit scalar. */
TYPED_TEST(SimdVec2ChebyshevNormTests, ReturnsLongestAbsoluteComponent)
{
    const auto magnitude = this->_vec.chebyshevNorm();
    EXPECT_MAG_EQ(this->_norm, magnitude);
}


/**
 * @test Verify that taking the chebyshev norm of a non-unit vector using static variant of
 *        @ref flcn::simd::Vec2::chebyshevNorm returns non-unit scalar.
 */
TYPED_TEST(SimdVec2ChebyshevNormTests, StaticWrapper_ReturnsLongestAbsoluteComponent)
{
    const auto magnitude = flcn::simd::Vec2<TypeParam>::chebyshevNorm(this->_vec);
    EXPECT_MAG_EQ(this->_norm, magnitude);
}

/** @} */
