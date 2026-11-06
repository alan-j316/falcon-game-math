/**
 * @file StringRepresentationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 25, 2026
 *
 * @brief Verify @ref flcn::Vec2 string representation.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"

#include <sstream>


/**
 * @addtogroup T_FALCON_Vec2_String_Repr
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Vec2 string representation.
     */
    class Vec2StringRepresentationTests: public testing::Test
    {
    protected:
        /** @brief Switch to use full precision for testing. */
        void SetUp() override { flcn::Config::useFullPrecision = true; }

        /** @brief Switch back to normal log precision. */
        void TearDown() override { flcn::Config::useFullPrecision = false; }
    };
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TEST_F(Vec2StringRepresentationTests, IntegralVector_ReturnsFormattedString)
{
    const flcn::Vec2 vec(1, 2);
    std::stringstream ss;

    ss << vec;

    EXPECT_EQ(ss.str(), "<1, 2>\n");
}


TEST_F(Vec2StringRepresentationTests, FloatingPointVector_ReturnsFormattedString)
{
    const flcn::Vec2 vec(1.2345f, 2.0f);
    std::stringstream ss;

    ss << vec;

    EXPECT_EQ(ss.str(), "<1.23450, 2.00000>\n");
}


TEST_F(Vec2StringRepresentationTests, DoublePrecisionFloatingPointVector_ReturnsFormattedString)
{
    const flcn::Vec2 vec(1.2345789777, 2.65831);
    std::stringstream ss;

    ss << vec;

    EXPECT_EQ(ss.str(), "<1.234578977700000, 2.658310000000000>\n");
}

/** @} */
