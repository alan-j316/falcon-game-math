/**
 * @file StringRepresentationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref flcn::Mat4x2 string representation.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4x2TestSetup.h"

#include <sstream>



/**
 * @addtogroup T_FALCON_Mat4x2_String_Repr
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4x2 String Representation.
     */
    class Mat4x2StringRepresentationTests: public testing::Test
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

TEST_F(Mat4x2StringRepresentationTests, IntegralMatrix_ReturnsFormattedString)
{
    const flcn::Mat4x2 mat(1, 2, 3, 4, 5, 6, 7, 8);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(), "|1 2|\n|3 4|\n|5 6|\n|7 8|\n");
}


TEST_F(Mat4x2StringRepresentationTests, FloatingPointMatrix_ReturnsFormattedString)
{
    const flcn::Mat4x2 mat(1.2345f, 2.0f, 3.0f, 4.53823f, 3.323f, 2.003f, 1.5f, 3.25f);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(), "|1.23450 2.00000|\n|3.00000 4.53823|\n|3.32300 2.00300|\n|1.50000 3.25000|\n");
}


TEST_F(Mat4x2StringRepresentationTests, DoublePrecisionFloatingPointMatrix_ReturnsFormattedString)
{
    const flcn::Mat4x2 mat(1.2345789777, 2.65831, 5.39281, 2.0, 4.0, 2.0, 0.0, 5.75);
    std::stringstream ss;

    ss << mat;

    EXPECT_EQ(ss.str(),
              "|1.234578977700000 2.658310000000000|\n"
              "|5.392810000000000 2.000000000000000|\n"
              "|4.000000000000000 2.000000000000000|\n"
              "|0.000000000000000 5.750000000000000|\n");
}

/** @} */
