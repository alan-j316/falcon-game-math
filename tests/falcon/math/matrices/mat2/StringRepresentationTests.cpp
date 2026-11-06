/**
 * @file StringRepresentationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 14, 2026
 *
 * @brief Verify @ref flcn::Mat2 string representation.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2TestSetup.h"

#include <sstream>



/**
 * @addtogroup T_FALCON_Mat2x2_String_Repr
 * @{
 */

namespace

{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2 String Representation.
     */
    class Mat2StringRepresentationTests: public ::testing::Test
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

TEST_F(Mat2StringRepresentationTests, IntegralMatrix_ReturnsFormattedString)
{
    const flcn::Mat2 mat(1, 2, 3, 4);
    std::stringstream ss;

    ss << mat;
    EXPECT_EQ(ss.str(), "|1 2|\n|3 4|\n");
}


TEST_F(Mat2StringRepresentationTests, FloatingPointMatrix_ReturnsFormattedString)
{
    const flcn::Mat2 mat(1.2345f, 2.0f, 4.53823f, 3.323f);
    std::stringstream ss;

    ss << mat;
    EXPECT_EQ(ss.str(), "|1.23450 2.00000|\n|4.53823 3.32300|\n");
}


TEST_F(Mat2StringRepresentationTests, DoublePrecisionFloatingPointMatrix_ReturnsFormattedString)
{
    const flcn::Mat2 mat(1.2345789777, 2.65831, 2.0, 4.0);
    std::stringstream ss;

    ss << mat;
    EXPECT_EQ(ss.str(), "|1.234578977700000 2.658310000000000|\n|2.000000000000000 4.000000000000000|\n");
}

/** @} */
