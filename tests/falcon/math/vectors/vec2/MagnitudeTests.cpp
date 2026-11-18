/**
 * @file MagnitudeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref flcn::Vec2 magnitude logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"



/**
 * @addtogroup T_Falcon_Vec2_Magnitude
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec2 magnitude.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec2MagnitudeTests: public testing::Test
    {
    protected:
        flcn::Vec2<T> _vec;
        flcn::Magnitude<T> _expectedMagnitude;
        T _expectedMagnitudeSquare;

        void SetUp() override
        {
            _vec                     = { T(3), T(4) };
            _expectedMagnitude       = flcn::Magnitude<T>(5);
            _expectedMagnitudeSquare = T(25);
        }
    };
    TYPED_TEST_SUITE(Vec2MagnitudeTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref Vec2 magnitude that returns a value with decimal places.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec2UncleanMagnitudeTests: public testing::Test
    {
    protected:
        flcn::Vec2<T> _vec;
        flcn::Magnitude<T> _expectedMagnitude;

        void SetUp() override
        {
            _vec               = { T(1), T(2) };
            _expectedMagnitude = flcn::Magnitude<T>(2.2360679774997898);
        }
    };
    TYPED_TEST_SUITE(Vec2UncleanMagnitudeTests, SupportedArithmeticTypes);


    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Vec2 VEC_A(1, 2);

        // TODO: Add static test after making sqrt constexpr
        /// @test Verify that mag returns a valid value at compile time.
        // constexpr auto MAG = Vec.mag();
        /// @test Verify that mag (static wrapper) returns a valid value at compile time.
        // constexpr auto MAG_STATIC = flcn::Vec2<int>::mag(Vec);

        /// @test Verify that magSq returns a valid value at compile time.
        constexpr auto MAG_SQ = VEC_A.magSq();
        static_assert(MAG_SQ - 5.0 < 1e5);

        /// @test Verify that magSq (static wrapper) returns a valid value at compile time.
        constexpr auto MAG_SQ_STATIC = flcn::Vec2<int>::magSq(VEC_A);
        static_assert(MAG_SQ_STATIC - 5.0 < 1e5);

    } // namespace static_tests
} // namespace



/**************************************
 *           MAGNITUDE TESTS          *
 **************************************/

TEST(Vec2MagnitudeTests, ZeroVectorReturnsZero)
{
    const flcn::Vec2 vec(0.0f, 0.0f);
    EXPECT_FLOAT_EQ(0.0f, vec.mag());
}


TEST(Vec2MagnitudeTests, OneComponentVectorReturnsNonUnitScalar)
{
    const flcn::Vec2 vec(1.0f, 1.0f);
    EXPECT_NE(1.0f, vec.mag());
}


TYPED_TEST(Vec2MagnitudeTests, NonUnitVectorReturnsCorrectMagnitude)
{
    const auto magnitude = this->_vec.mag();
    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


TYPED_TEST(Vec2MagnitudeTests, Mag_AlwaysTypePromoteToFloatingPointType)
{
    [[maybe_unused]] const auto magnitude = this->_vec.mag();
    static_assert(std::is_floating_point_v<decltype(magnitude)>);
}


TYPED_TEST(Vec2MagnitudeTests, StaticWrapper_Mag_NonUnitVectorReturnsCorrectMagnitude)
{
    const auto magnitude = flcn::Vec2<TypeParam>::mag(this->_vec);
    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


TYPED_TEST(Vec2UncleanMagnitudeTests, Mag_NonUnitVectorReturnsCorrectMagnitudeWithMinimalPrecisionLoss)
{
    const auto magnitude = this->_vec.mag();
    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


TYPED_TEST(Vec2UncleanMagnitudeTests, StaticWrapper_Mag_NonUnitVectorReturnsCorrectMagnitudeWithMinimalPrecisionLoss)
{
    const auto magnitude = flcn::Vec2<TypeParam>::mag(this->_vec);
    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}



/**************************************
 *       MAGNITUDE SQUARE TESTS       *
 **************************************/

TYPED_TEST(Vec2MagnitudeTests, MagSq_ReturnsSquaredMagnitude)
{
    const auto magnitude = this->_vec.magSq();
    EXPECT_MAG_EQ(this->_expectedMagnitudeSquare, magnitude);
}


TYPED_TEST(Vec2MagnitudeTests, StaticWrapper_MagSq_ReturnsSquaredMagnitude)
{
    const auto magnitude = flcn::Vec2<TypeParam>::magSq(this->_vec);
    EXPECT_MAG_EQ(this->_expectedMagnitudeSquare, magnitude);
}


/** @} */
