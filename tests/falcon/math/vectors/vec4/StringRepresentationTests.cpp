/**
 * @file StringRepresentationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 16, 2026
 *
 * @brief Verify @ref flcn::Vec4 string representation.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec4TestSetup.h"

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
    class Vec4StringRepresentationTests: public testing::Test
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

TEST_F(Vec4StringRepresentationTests, IntegralVector_ReturnsFormattedString)
{
    const flcn::Vec4 vec(1, 2, 3, 4);
    std::stringstream ss;

    ss << vec;

    EXPECT_EQ(ss.str(), "<1, 2, 3, 4>\n");
}


TEST_F(Vec4StringRepresentationTests, FloatingPointVector_ReturnsFormattedString)
{
    const flcn::Vec4 vec(1.2345f, 2.0f, 3.56789f, 4.2f);
    std::stringstream ss;

    ss << vec;

    EXPECT_EQ(ss.str(), "<1.23450, 2.00000, 3.56789, 4.20000>\n");
}


TEST_F(Vec4StringRepresentationTests, DoublePrecisionFloatingPointVector_ReturnsFormattedString)
{
    const flcn::Vec4 vec(1.2345789777, 2.65831, 3.161285, 4.0);
    std::stringstream ss;

    ss << vec;

    EXPECT_EQ(ss.str(), "<1.234578977700000, 2.658310000000000, 3.161285000000000, 4.000000000000000>\n");
}

/** @} */
