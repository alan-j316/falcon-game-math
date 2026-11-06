/**
 * @file StringRepresentationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref flcn::Vec3 string representation.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"

#include <sstream>


/**
 * @addtogroup T_FALCON_Vec3_String_Repr
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Vec3 string representation.
     */
    class Vec3StringRepresentationTests: public testing::Test
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

TEST_F(Vec3StringRepresentationTests, IntegralVector_ReturnsFormattedString)
{
    const flcn::Vec3 vec(1, 2, 3);
    std::stringstream ss;

    ss << vec;

    EXPECT_EQ(ss.str(), "<1, 2, 3>\n");
}


TEST_F(Vec3StringRepresentationTests, FloatingPointVector_ReturnsFormattedString)
{
    const flcn::Vec3 vec(1.2345f, 2.0f, 3.56789f);
    std::stringstream ss;

    ss << vec;

    EXPECT_EQ(ss.str(), "<1.23450, 2.00000, 3.56789>\n");
}


TEST_F(Vec3StringRepresentationTests, DoublePrecisionFloatingPointVector_ReturnsFormattedString)
{
    const flcn::Vec3 vec(1.2345789777, 2.65831, 3.161285);
    std::stringstream ss;

    ss << vec;

    EXPECT_EQ(ss.str(), "<1.234578977700000, 2.658310000000000, 3.161285000000000>\n");
}

/** @} */
