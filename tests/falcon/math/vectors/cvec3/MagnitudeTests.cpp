/**
 * @file MagnitudeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref flcn::CVec3 magnitude logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CVec3TestSetup.h"



/**
 * @addtogroup T_Falcon_CVec3_Magnitude
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref CVec3 magnitude.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class CVec3MagnitudeTests: public testing::Test
    {
    protected:
        flcn::CVec3<T> _vec;
        flcn::Magnitude<T> _expectedMagnitude;
        T _expectedMagnitudeSquare;

        void SetUp() override
        {
            _vec                     = { T(9), T(6), T(2) };
            _expectedMagnitude       = flcn::Magnitude<T>(11);
            _expectedMagnitudeSquare = T(121);
        }
    };
    TYPED_TEST_SUITE(CVec3MagnitudeTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref CVec3 magnitude that returns a value with decimal places.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class CVec3UncleanMagnitudeTests: public testing::Test
    {
    protected:
        flcn::CVec3<T> _vec;
        flcn::Magnitude<T> _expectedMagnitude;

        void SetUp() override
        {
            _vec               = { T(1), T(2), T(3) };
            _expectedMagnitude = flcn::Magnitude<T>(3.7416573867739413);
        }
    };
    TYPED_TEST_SUITE(CVec3UncleanMagnitudeTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::CVec3 VEC_A(1, 2, 3);

        // TODO: Add static test after making sqrt constexpr
        /// @test Verify that mag returns a valid value at compile time.
        // constexpr auto MAG = Vec.mag();
        /// @test Verify that mag (static wrapper) returns a valid value at compile time.
        // constexpr auto MAG_STATIC = flcn::CVec3<int>::mag(Vec);

        /// @test Verify that magSq returns a valid value at compile time.
        constexpr auto MAG_SQ = VEC_A.magSq();
        static_assert(MAG_SQ - 14.0 < 1e5);

        /// @test Verify that magSq (static wrapper) returns a valid value at compile time.
        constexpr auto MAG_SQ_STATIC = flcn::CVec3<int>::magSq(VEC_A);
        static_assert(MAG_SQ_STATIC - 14.0 < 1e5);

    } // namespace static_tests

} // namespace



/**************************************
 *          MAGNITUDE TESTS           *
 **************************************/

/** @test Verify that taking the magnitude of a zero vector returns exactly zero. */
TEST(CVec3Magnitude, ZeroVectorReturnsZero)
{
    const flcn::CVec3 vec(0.0f, 0.0f, 0.0f);
    EXPECT_FLOAT_EQ(0.0f, vec.mag());
}


/** @test Verify that taking the magnitude of a one vector returns non-unit scalar. */
TEST(CVec3Magnitude, OneComponentVectorReturnsNonUnitScalar)
{
    const flcn::CVec3 vec(1.0f, 1.0f, 1.0f);
    EXPECT_NE(1.0f, vec.mag());
}


/** @test Verify that taking the magnitude of a non-unit vector returns non-unit scalar. */
TYPED_TEST(CVec3MagnitudeTests, NonUnitVectorReturnsCorrectMagnitude)
{
    const auto magnitude = this->_vec.mag();
    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/** @test Verify that taking the magnitude always returns a floating-point scalar. */
TYPED_TEST(CVec3MagnitudeTests, MagnitudeIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto magnitude = this->_vec.mag();
    static_assert(std::is_floating_point_v<decltype(magnitude)>);
}


/**
 * @test Verify that taking the magnitude of a non-unit vector using static variant of @ref flcn::CVec3::mag
 *       returns non-unit scalar.
 */
TYPED_TEST(CVec3MagnitudeTests, StaticWrapper_NonUnitVectorReturnsCorrectMagnitude)
{
    const auto magnitude = flcn::CVec3<TypeParam>::mag(this->_vec);
    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/** @test Verify that the magnitude calculations for non-unit vectors ensure minimal precision loss. */
TYPED_TEST(CVec3UncleanMagnitudeTests, NonUnitVectorReturnsCorrectMagnitudeWithMinimalPrecisionLoss)
{
    const auto magnitude = this->_vec.mag();
    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/**
 * @test Verify that the magnitude calculations for non-unit vectors using static variant of @ref flcn::CVec3::mag
 *       ensure minimal precision loss.
 */
TYPED_TEST(CVec3UncleanMagnitudeTests, StaticWrapper_NonUnitVectorReturnsCorrectMagnitudeWithMinimalPrecisionLoss)
{
    const auto magnitude = flcn::CVec3<TypeParam>::mag(this->_vec);
    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


/**************************************
 *       MAGNITUDE SQUARE TESTS       *
 **************************************/

/** @test Verify that taking the magnitude of a non-unit vector returns non-unit scalar. */
TYPED_TEST(CVec3MagnitudeTests, MagSq_ReturnsSquaredMagnitude)
{
    const auto magnitude = this->_vec.magSq();
    EXPECT_MAG_EQ(this->_expectedMagnitudeSquare, magnitude);
}


/**
 * @test Verify that taking the magnitude square of a non-unit vector using static variant of
 *        @ref flcn::CVec3::mag returns non-unit scalar.
 */
TYPED_TEST(CVec3MagnitudeTests, StaticWrapper_MagSq_ReturnsSquaredMagnitude)
{
    const auto magnitude = flcn::CVec3<TypeParam>::magSq(this->_vec);
    EXPECT_MAG_EQ(this->_expectedMagnitudeSquare, magnitude);
}

/** @} */
