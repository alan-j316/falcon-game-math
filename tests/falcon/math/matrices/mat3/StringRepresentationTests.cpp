/**
 * @file StringRepresentationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 01, 2026
 *
 * @brief Verify @ref flcn::Mat3 string representation.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3TestSetup.h"

#include <sstream>


/**
 * @addtogroup T_FALCON_Mat3x3_String_Repr
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat3 String Representation.
     */
    class Mat3StringRepresentationTests: public ::testing::Test
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

TEST_F(Mat3StringRepresentationTests, IntegralMatrix_ReturnsFormattedString)
{
    const flcn::Mat3 mat(1, 2, 3, 4, 5, 6, 7, 8, 9);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(), "|1 2 3|\n|4 5 6|\n|7 8 9|\n");
}


TEST_F(Mat3StringRepresentationTests, FloatingPointMatrix_ReturnsFormattedString)
{
    const flcn::Mat3 mat(1.2345f, 2.0f, 4.53823f, 3.323f, 3.5832f, 5.8392f, 9.9238f, -12.0532f, 3.2312f);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(), "|1.23450 2.00000 4.53823|\n|3.32300 3.58320 5.83920|\n|9.92380 -12.05320 3.23120|\n");
}


TEST_F(Mat3StringRepresentationTests, DoublePrecisionFloatingPointMatrix_ReturnsFormattedString)
{
    const flcn::Mat3 mat(1.2345789777, 2.65831, 2.0, 4.0, 3.2345789777, 1.2345789777, 12.0, -6.2345789777, 0.2345789777);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(),
              "|1.234578977700000 2.658310000000000 2.000000000000000|\n|4.000000000000000 3.234578977700000 "
              "1.234578977700000|\n|12.000000000000000 -6.234578977700000 0.234578977700000|\n");
}

/** @} */
