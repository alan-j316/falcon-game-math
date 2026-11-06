/**
 * @file QuaternionAlgebraTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 06, 2026
 *
 * @brief Verify @ref flcn::Quaternion quaternion algebra assertions(Inverse,...).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "../include/QuaternionTestSetup.h"


/**
 * @addtogroup T_FALCON_Quaternion_Algebra
 * @{
 */

#ifdef ENABLE_DEBUG_TESTS

TEST(QuaternionInverseTests, ZeroQuaternionTriggersAssertInDebugMode)
{
    const auto zeroQuat = flcn::Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
    EXPECT_DEATH(static_cast<void>(zeroQuat.inverse()), "");
}

#endif

/** @} */
