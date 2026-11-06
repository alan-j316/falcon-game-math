/**
 * @file StringRepresentationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 20, 2026
 *
 * @brief Verify @ref flcn::Mat3x4 string representation.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3x4TestSetup.h"

#include <sstream>



/**
 * @addtogroup T_FALCON_Mat3x4_String_Repr
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat3x4 String Representation.
     */
    class Mat3x4StringRepresentationTests: public ::testing::Test
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

TEST_F(Mat3x4StringRepresentationTests, IntegralMatrix_ReturnsFormattedString)
{
    const flcn::Mat3x4 mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(), "|1 2 3 4|\n|5 6 7 8|\n|9 10 11 12|\n");
}


TEST_F(Mat3x4StringRepresentationTests, FloatingPointMatrix_ReturnsFormattedString)
{
    const flcn::Mat3x4 mat(1.2345f, 2.0f, 4.53823f, 3.323f, 3.5832f, 5.8392f, 9.9238f, -12.0532f, 3.2312f, 12.0f, 13.5f,
                          14.4f);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(),
              "|1.23450 2.00000 4.53823 3.32300|\n"
              "|3.58320 5.83920 9.92380 -12.05320|\n"
              "|3.23120 12.00000 13.50000 14.40000|\n");
}


TEST_F(Mat3x4StringRepresentationTests, DoublePrecisionFloatingPointMatrix_ReturnsFormattedString)
{
    const flcn::Mat3x4 mat(1.2345789777, 2.65831, 2.0, 4.0, 3.2345789777, 1.2345789777, 12.0, -6.2345789777,
                          0.2345789777, 5.9123849123, 12.123948213, 5.1912384);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(),
              "|1.234578977700000 2.658310000000000 2.000000000000000 4.000000000000000|\n"
              "|3.234578977700000 1.234578977700000 12.000000000000000 -6.234578977700000|\n"
              "|0.234578977700000 5.912384912300000 12.123948213000000 5.191238400000000|\n");
}

/** @} */
