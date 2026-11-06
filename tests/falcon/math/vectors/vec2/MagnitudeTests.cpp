/**
 * @file MagnitudeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 23, 2026
 *
 * @brief Verify @ref flcn::Vec2 magnitude logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"



/**
 * @addtogroup T_FALCON_Vec2_Magnitude
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
        T _expectedMagnitude;
        T _expectedMagnitudeSquare;

        void SetUp() override
        {
            _vec                     = { T(3), T(4) };
            _expectedMagnitude       = T(5);
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
        T _expectedMagnitude;

        void SetUp() override
        {
            _vec               = { T(1), T(2) };
            _expectedMagnitude = T(2.2360679774997898);
        }
    };
    TYPED_TEST_SUITE(Vec2UncleanMagnitudeTests, SupportedArithmeticTypes);

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
