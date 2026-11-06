/**
 * @file StringRepresentationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 18, 2026
 *
 * @brief Verify @ref flcn::Mat2x4 string representation.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2x4TestSetup.h"

#include <sstream>


/**
 * @addtogroup T_FALCON_Mat2x4_String_Repr
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2x4 String Representation.
     */
    class Mat2x4StringRepresentationTests: public testing::Test
    {
    protected:
        /** @brief Switch to use full precision for testing. */
        void SetUp() override { flcn::Config::useFullPrecision = true; }

        /** @brief Switch back to normal log precision. */
        void TearDown() override { flcn::Config::useFullPrecision = false; }
    };
} // namespace



TEST_F(Mat2x4StringRepresentationTests, IntegralMatrix_ReturnsFormattedString)
{
    const flcn::Mat2x4 mat(1, 2, 3, 4, 5, 6, 7, 8);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(), "|1 2 3 4|\n|5 6 7 8|\n");
}


TEST_F(Mat2x4StringRepresentationTests, FloatingPointMatrix_ReturnsFormattedString)
{
    const flcn::Mat2x4 mat(1.2345f, 2.0f, 3.0f, 4.53823f, 3.323f, 12.003f, 0.0f, -1.234f);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(), "|1.23450 2.00000 3.00000 4.53823|\n|3.32300 12.00300 0.00000 -1.23400|\n");
}


TEST_F(Mat2x4StringRepresentationTests, DoublePrecisionFloatingPointMatrix_ReturnsFormattedString)
{
    const flcn::Mat2x4 mat(1.2345789777, 2.65831, 5.39281, 2.0, 4.0, 12.0, 0.0, -1.234);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(),
              "|1.234578977700000 2.658310000000000 5.392810000000000 2.000000000000000|\n|4.000000000000000 "
              "12.000000000000000 0.000000000000000 -1.234000000000000|\n");
}

/** @} */
