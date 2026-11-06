/**
 * @file StringRepresentationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 07, 2026
 *
 * @brief Verify @ref flcn::Mat4 string representation.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4TestSetup.h"

#include <sstream>


/**
 * @addtogroup T_FALCON_Mat4x4_String_Repr
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4 String Representation.
     */
    class Mat4StringRepresentationTests: public testing::Test
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

TEST_F(Mat4StringRepresentationTests, IntegralMatrix_ReturnsFormattedString)
{
    constexpr flcn::Mat4 mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(), "|1 2 3 4|\n|5 6 7 8|\n|9 10 11 12|\n|13 14 15 16|\n");
}


TEST_F(Mat4StringRepresentationTests, FloatingPointMatrix_ReturnsFormattedString)
{
    constexpr flcn::Mat4 mat(1.2345f, 2.0f, 4.53823f, 3.323f, 3.5832f, 5.8392f, 9.9238f, -12.0532f, 3.2312f, 12.0f,
                            13.5f, 14.4f, 23.5f, 44.44f, 3.160f, 9.32f);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(),
              "|1.23450 2.00000 4.53823 3.32300|\n|3.58320 5.83920 9.92380 -12.05320|\n|3.23120 12.00000 13.50000 "
              "14.40000|\n|23.50000 44.44000 3.16000 9.32000|\n");
}


TEST_F(Mat4StringRepresentationTests, DoublePrecisionFloatingPointMatrix_ReturnsFormattedString)
{
    constexpr flcn::Mat4 mat(1.2345789777, 2.65831, 2.0, 4.0, 3.2345789777, 1.2345789777, 12.0, -6.2345789777,
                            0.2345789777, 5.9123849123, 12.123948213, 5.1912384, 2.19234812, 1.129348923, 1.213921,
                            5.382911932);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(),
              "|1.234578977700000 2.658310000000000 2.000000000000000 4.000000000000000|\n|3.234578977700000 "
              "1.234578977700000 12.000000000000000 -6.234578977700000|\n|0.234578977700000 5.912384912300000 "
              "12.123948213000000 5.191238400000000|\n|2.192348120000000 1.129348923000000 1.213921000000000 "
              "5.382911932000000|\n");
}

/** @} */
