/**
 * @file PNormTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 22, 2026
 *
 * @brief Verify the @ref flcn::CVec2 p-Norm length logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "CVec2TestSetup.h"



/**
 * @addtogroup T_FALCON_CVec2_Norm
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref CVec2 Manhattan Norm(Distance).
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class CVec2ManhattanNormTests: public testing::Test
    {
    protected:
        flcn::CVec2<T> _vec;
        T _norm;

        void SetUp() override
        {
            _vec  = { T(1), T(2) };
            _norm = T(3);
        }
    };
    TYPED_TEST_SUITE(CVec2ManhattanNormTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref CVec2 Chebyshev Norm(Distance).
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class CVec2ChebyshevNormTests: public testing::Test
    {
    protected:
        flcn::CVec2<T> _vec;
        T _norm;

        void SetUp() override
        {
            _vec  = { T(1), T(2) };
            _norm = T(2);
        }
    };
    TYPED_TEST_SUITE(CVec2ChebyshevNormTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::CVec2 VEC(1, -2);

        /// @test Verify that CVec2 Manhattan Norm returns a valid scalar.
        static_assert(VEC.manhattanNorm() == 3);
        /// @test Verify that CVec2 Manhattan Norm (static wrapper) returns a valid scalar.
        static_assert(flcn::CVec2<int>::manhattanNorm(VEC) == 3);


        /// @test Verify that CVec2 Chebyshev Norm returns a valid scalar.
        static_assert(VEC.chebyshevNorm() == 2);
        /// @test Verify that CVec2 Chebyshev Norm (static wrapper) returns a valid scalar.
        static_assert(flcn::CVec2<int>::chebyshevNorm(VEC) == 2);

    } // namespace static_tests
} // namespace



/**************************************
 *           MANHATTAN NORM           *
 **************************************/

/** @test Verify that taking the manhattan norm of a non-unit vector returns non-unit scalar. */
TYPED_TEST(CVec2ManhattanNormTests, ReturnsSumOfAbsoluteValueOfComponents)
{
    const auto magnitude = this->_vec.manhattanNorm();
    EXPECT_MAG_EQ(this->_norm, magnitude);
}


/**
 * @test Verify that taking the manhattan norm of a non-unit vector using static variant of
 *        @ref flcn::CVec2::manhattanNorm returns non-unit scalar.
 */
TYPED_TEST(CVec2ManhattanNormTests, StaticWrapper_ReturnsSumOfAbsoluteValueOfComponents)
{
    const auto magnitude = flcn::CVec2<TypeParam>::manhattanNorm(this->_vec);
    EXPECT_MAG_EQ(this->_norm, magnitude);
}



/**************************************
 *           CHEBYSHEV NORM           *
 **************************************/

/** @test Verify that taking the chebyshev norm of a non-unit vector returns non-unit scalar. */
TYPED_TEST(CVec2ChebyshevNormTests, ReturnsLongestAbsoluteComponent)
{
    const auto magnitude = this->_vec.chebyshevNorm();
    EXPECT_MAG_EQ(this->_norm, magnitude);
}


/**
 * @test Verify that taking the chebyshev norm of a non-unit vector using static variant of
 *        @ref flcn::CVec2::chebyshevNorm returns non-unit scalar.
 */
TYPED_TEST(CVec2ChebyshevNormTests, StaticWrapper_ReturnsLongestAbsoluteComponent)
{
    const auto magnitude = flcn::CVec2<TypeParam>::chebyshevNorm(this->_vec);
    EXPECT_MAG_EQ(this->_norm, magnitude);
}

/** @} */
