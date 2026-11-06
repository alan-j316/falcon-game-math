/**
 * @file PNormTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 22, 2026
 *
 * @brief Verify the @ref flcn::Vec3 p-Norm length logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Vec3TestSetup.h"


/**
 * @addtogroup T_FALCON_Vec3_Norm
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
    class Vec3ManhattanNormTests: public testing::Test
    {
    protected:
        flcn::Vec3<T> _vec;
        T _norm;

        void SetUp() override
        {
            _vec  = { T(1), T(2), T(4) };
            _norm = T(7);
        }
    };
    TYPED_TEST_SUITE(Vec3ManhattanNormTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec3 Chebyshev Norm(Distance).
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec3ChebyshevNormTests: public testing::Test
    {
    protected:
        flcn::Vec3<T> _vec;
        T _norm;

        void SetUp() override
        {
            _vec  = { T(1), T(2), T(4) };
            _norm = T(4);
        }
    };
    TYPED_TEST_SUITE(Vec3ChebyshevNormTests, SupportedArithmeticTypes);




    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Vec3 vector(1, -2, 4);


        /// @test Verify that Vec3 Manhattan Norm returns a valid scalar.
        static_assert(vector.manhattanNorm() == 7);
        /// @test Verify that Vec3 Manhattan Norm (static wrapper) returns a valid scalar.
        static_assert(flcn::Vec3<int>::manhattanNorm(vector) == 7);


        /// @test Verify that Vec3 Chebyshev Norm returns a valid scalar.
        static_assert(vector.chebyshevNorm() == 4);
        /// @test Verify that Vec3 Chebyshev Norm (static wrapper) returns a valid scalar.
        static_assert(flcn::Vec3<int>::chebyshevNorm(vector) == 4);

    } // namespace static_tests
} // namespace



/**************************************
 *           MANHATTAN NORM           *
 **************************************/

/** @test Verify that taking the manhattan norm of a non-unit vector returns non-unit scalar. */
TYPED_TEST(Vec3ManhattanNormTests, ReturnsSumOfAbsoluteValueOfComponents)
{
    const auto magnitude = this->_vec.manhattanNorm();
    EXPECT_MAG_EQ(this->_norm, magnitude);
}


/**
 * @test Verify that taking the manhattan norm of a non-unit vector using static variant of
 *        @ref flcn::Vec3::manhattanNorm returns non-unit scalar.
 */
TYPED_TEST(Vec3ManhattanNormTests, StaticWrapper_ReturnsSumOfAbsoluteValueOfComponents)
{
    const auto magnitude = flcn::Vec3<TypeParam>::manhattanNorm(this->_vec);
    EXPECT_MAG_EQ(this->_norm, magnitude);
}



/**************************************
 *           CHEBYSHEV NORM           *
 **************************************/

/** @test Verify that taking the chebyshev norm of a non-unit vector returns non-unit scalar. */
TYPED_TEST(Vec3ChebyshevNormTests, ReturnsLongestAbsoluteComponent)
{
    const auto magnitude = this->_vec.chebyshevNorm();

    EXPECT_MAG_EQ(this->_norm, magnitude);
}


/**
 * @test Verify that taking the chebyshev norm of a non-unit vector using static variant of
 *        @ref flcn::Vec3::chebyshevNorm returns non-unit scalar.
 */
TYPED_TEST(Vec3ChebyshevNormTests, StaticWrapper_ReturnsLongestAbsoluteComponent)
{
    const auto magnitude = flcn::Vec3<TypeParam>::chebyshevNorm(this->_vec);

    EXPECT_MAG_EQ(this->_norm, magnitude);
}

/** @} */
