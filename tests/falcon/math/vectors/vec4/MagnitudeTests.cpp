/**
 * @file MagnitudeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verify @ref flcn::Vec4 magnitude logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec4TestSetup.h"



/**
 * @addtogroup T_FALCON_Vec3_Magnitude
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec3 magnitude.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec4MagnitudeTests: public testing::Test
    {
    protected:
        flcn::Vec4<T> _vec;
        flcn::Magnitude<T> _expectedMagnitude;
        T _expectedMagnitudeSquare;

        void SetUp() override
        {
            _vec                     = { T(1), T(2), T(2), T(4) };
            _expectedMagnitude       = flcn::Magnitude<T>(5);
            _expectedMagnitudeSquare = T(25);
        }
    };
    TYPED_TEST_SUITE(Vec4MagnitudeTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec3 magnitude that returns a value with decimal places.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec4UncleanMagnitude: public testing::Test
    {
    protected:
        flcn::Vec4<T> _vec;
        flcn::Magnitude<T> _expectedMagnitude;

        void SetUp() override
        {
            _vec               = { T(1), T(2), T(3), T(4) };
            _expectedMagnitude = flcn::Magnitude<T>(5.477225575051661);
        }
    };
    TYPED_TEST_SUITE(Vec4UncleanMagnitude, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Vec4 VEC_A(1, 2, 3, 4);

        // TODO: Add static test after making sqrt constexpr
        /// @test Verify that mag returns a valid value at compile time.

        // constexpr auto MAG = Vec.mag();
        // static_assert(MAG - 5.477225575051661 <= 1e-5);

        /// @test Verify that mag (static wrapper) returns a valid value at compile time.
        // constexpr auto MAG_STATIC = flcn::Vec4<int>::mag(Vec);
        // static_assert(MAG_STATIC - 5.477225575051661 <= 1e-5);

        /// @test Verify that magSq returns a valid value at compile time.
        constexpr auto MAG_SQ = VEC_A.magSq();
        static_assert(MAG_SQ - 30.0 < 1e5);

        /// @test Verify that magSq (static wrapper) returns a valid value at compile time.
        constexpr auto MAG_SQ_STATIC = flcn::Vec4<int>::magSq(VEC_A);
        static_assert(MAG_SQ_STATIC - 30.0 < 1e5);

    } // namespace static_tests
} // namespace



/**************************************
 *          MAGNITUDE TESTS           *
 **************************************/

/** @test Verify that taking the magnitude of a zero vector returns exactly zero. */
TEST(Vec4Magnitude, ZeroVectorReturnsZero)
{
    const flcn::Vec4 vec(0.0f, 0.0f, 0.0f, 0.0f);
    EXPECT_FLOAT_EQ(0.0f, vec.mag());
}


/** @test Verify that taking the magnitude of a one vector returns non-unit scalar. */
TEST(Vec4Magnitude, OneComponentVectorReturnsNonUnitScalar)
{
    const flcn::Vec4 vec(1.0f, 1.0f, 1.0f, 1.0f);
    EXPECT_NE(1.0f, vec.mag());
}


/** @test Verify that taking the magnitude of a non-unit vector returns non-unit scalar. */
TYPED_TEST(Vec4MagnitudeTests, NonUnitVectorReturnsCorrectMagnitude)
{
    const auto magnitude = this->_vec.mag();

    static_assert(std::is_floating_point_v<decltype(magnitude)>);
    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/** @test Verify that taking the magnitude always returns a floating-point scalar. */
TYPED_TEST(Vec4MagnitudeTests, MagnitudeIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto magnitude = this->_vec.mag();
    static_assert(std::is_floating_point_v<decltype(magnitude)>);
}


/**
 * @test Verify that taking the magnitude of a non-unit vector using static variant of @ref flcn::Vec4::mag
 *       returns non-unit scalar.
 */
TYPED_TEST(Vec4MagnitudeTests, StaticWrapper_NonUnitVectorReturnsCorrectMagnitude)
{
    const auto magnitude = flcn::Vec4<TypeParam>::mag(this->_vec);
    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/** @test Verify that the magnitude calculations for non-unit vectors ensure minimal precision loss. */
TYPED_TEST(Vec4UncleanMagnitude, NonUnitVectorReturnsCorrectMagnitudeWithMinimalPrecisionLoss)
{
    const auto magnitude = this->_vec.mag();
    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/**
 * @test Verify that the magnitude calculations for non-unit vectors using static variant of @ref flcn::Vec4::mag
 *       ensure minimal precision loss.
 */
TYPED_TEST(Vec4UncleanMagnitude, StaticWrapper_NonUnitVectorReturnsCorrectMagnitudeWithMinimalPrecisionLoss)
{
    const auto magnitude = flcn::Vec4<TypeParam>::mag(this->_vec);
    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/**************************************
 *       MAGNITUDE SQUARE TESTS       *
 **************************************/

/** @test Verify that taking the magnitude of a non-unit vector returns non-unit scalar. */
TYPED_TEST(Vec4MagnitudeTests, MagSq_ReturnsSquaredMagnitude)
{
    const auto magnitude = this->_vec.magSq();
    EXPECT_MAG_EQ(this->_expectedMagnitudeSquare, magnitude);
}


/**
 * @test Verify that taking the magnitude square of a non-unit vector using static variant of
 *        @ref flcn::Vec4::mag returns non-unit scalar.
 */
TYPED_TEST(Vec4MagnitudeTests, StaticWrapper_MagSq_ReturnsSquaredMagnitude)
{
    const auto magnitude = flcn::Vec4<TypeParam>::magSq(this->_vec);
    EXPECT_MAG_EQ(this->_expectedMagnitudeSquare, magnitude);
}

/** @} */
