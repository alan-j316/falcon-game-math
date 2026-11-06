/**
 * @file PNormTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 22, 2026
 *
 * @brief Verify the @ref flcn::Vec4 p-Norm length logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Vec4TestSetup.h"


/**
 * @addtogroup T_FALCON_Vec4_Norm
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec4 Manhattan Norm(Distance).
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec4ManhattanNormTests: public testing::Test
    {
    protected:
        flcn::Vec4<T> _vec;
        T _norm;

        void SetUp() override
        {
            _vec  = { T(1), T(2), T(3), T(4) };
            _norm = T(10);
        }
    };
    TYPED_TEST_SUITE(Vec4ManhattanNormTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref Vec4 Chebyshev Norm(Distance).
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec4ChebyshevNormTests: public testing::Test
    {
    protected:
        flcn::Vec4<T> _vec;
        T _norm;

        void SetUp() override
        {
            _vec  = { T(1), T(2), T(3), T(4) };
            _norm = T(4);
        }
    };
    TYPED_TEST_SUITE(Vec4ChebyshevNormTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Vec4 VEC(1, -2, 3, -4);

        /// @test Verify that Vec4 Manhattan Norm returns a valid scalar.
        static_assert(VEC.manhattanNorm() == 10);
        /// @test Verify that Vec4 Manhattan Norm (static wrapper) returns a valid scalar.
        static_assert(flcn::Vec4<int>::manhattanNorm(VEC) == 10);


        /// @test Verify that Vec4 Chebyshev Norm returns a valid scalar.
        static_assert(VEC.chebyshevNorm() == 4);
        /// @test Verify that Vec4 Chebyshev Norm (static wrapper) returns a valid scalar.
        static_assert(flcn::Vec4<int>::chebyshevNorm(VEC) == 4);

    } // namespace static_tests

} // namespace



/**************************************
 *           MANHATTAN NORM           *
 **************************************/

/** @test Verify that taking the manhattan norm of a non-unit vector returns non-unit scalar. */
TYPED_TEST(Vec4ManhattanNormTests, ReturnsSumOfAbsoluteValueOfComponents)
{
    const auto magnitude = this->_vec.manhattanNorm();
    EXPECT_MAG_EQ(this->_norm, magnitude);
}


/**
 * @test Verify that taking the manhattan norm of a non-unit vector using static variant of
 *        @ref flcn::Vec4::manhattanNorm returns non-unit scalar.
 */
TYPED_TEST(Vec4ManhattanNormTests, StaticWrapper_ReturnsSumOfAbsoluteValueOfComponents)
{
    const auto magnitude = flcn::Vec4<TypeParam>::manhattanNorm(this->_vec);
    EXPECT_MAG_EQ(this->_norm, magnitude);
}



/**************************************
 *           CHEBYSHEV NORM           *
 **************************************/

/** @test Verify that taking the chebyshev norm of a non-unit vector returns non-unit scalar. */
TYPED_TEST(Vec4ChebyshevNormTests, ReturnsLongestAbsoluteComponent)
{
    const auto magnitude = this->_vec.chebyshevNorm();
    EXPECT_MAG_EQ(this->_norm, magnitude);
}


/**
 * @test Verify that taking the chebyshev norm of a non-unit vector using static variant of
 *        @ref flcn::Vec4::chebyshevNorm returns non-unit scalar.
 */
TYPED_TEST(Vec4ChebyshevNormTests, StaticWrapper_ReturnsLongestAbsoluteComponent)
{
    const auto magnitude = flcn::Vec4<TypeParam>::chebyshevNorm(this->_vec);
    EXPECT_MAG_EQ(this->_norm, magnitude);
}

/** @} */
