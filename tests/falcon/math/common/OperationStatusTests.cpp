/**
 * @file OperationStatusTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 30, 2026
 *
 * @brief Verify @ref flcn::OperationStatus code to message mapping.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <falcon/math/common/OperationStatus.h>
#include <gtest/gtest.h>


namespace
{

    /**************************************
     *            TEST SETUP              *
     **************************************/

    struct OperationStatusMappingParams
    {
        flcn::OperationStatus status;
        const char* expectedMessage;
    };

    /// @brief Test fixture for @ref flcn::OperationStatus to verify corresponding string mapping.
    class OperationStatusMappingTests: public testing::TestWithParam<OperationStatusMappingParams>
    {};

} // namespace


/**
 * @addtogroup T_Op_Status
 * @{
 */

TEST_P(OperationStatusMappingTests, GetStatusMessage_ReturnsCorrectMessage)
{
    const auto& [status, expectedMessage] = GetParam();
    const auto message                    = flcn::getStatusMessage(status);
    EXPECT_EQ(expectedMessage, message);
}


INSTANTIATE_TEST_SUITE_P(
    OperationStatusMappingTestSuite, OperationStatusMappingTests,
    ::testing::Values(OperationStatusMappingParams{ flcn::OperationStatus::SUCCESS, "Operation success!" },
                      OperationStatusMappingParams{ flcn::OperationStatus::DIVISIONBYZERO, "Failure: Division by Zero" },
                      OperationStatusMappingParams{ flcn::OperationStatus::NANOPERAND,
                                                    "Failure: NaN operand encountered" },
                      OperationStatusMappingParams{ static_cast<flcn::OperationStatus>(7), "Failure: Unknown error" }));

/** @} */
