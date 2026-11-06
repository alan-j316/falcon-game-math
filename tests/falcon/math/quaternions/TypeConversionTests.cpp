/**
 * @file TypeConversionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 04, 2026
 *
 * @brief Verify @ref flcn::Quaternion conversion constructor logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "include/QuaternionTestSetup.h"



/**
 * @addtogroup T_FALCON_Quaternion_Type_Conv
 * @{
 */

namespace
{

    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {

        /// @test Verify that a 32-bit floating point quaternion can be converted to a 64-bt
        ///       floating point quaternion at compile time.
        constexpr flcn::Quaternion FP_QUAT(3.0f, 1.0f, 4.0f, 5.0f);
        constexpr flcn::Quaternion<double> DBL_QUAT(FP_QUAT);
        static_assert(std::is_same_v<decltype(DBL_QUAT)::value_type, double>);

        /// @test Verify that a 64-bit floating point quaternion can be converted to a 32-bt
        ///       floating point quaternion at compile time.
        [[maybe_unused]] constexpr flcn::Quaternion<float> FP_QUAT2(DBL_QUAT);
        static_assert(std::is_same_v<decltype(FP_QUAT2)::value_type, float>);
    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TEST(QuaternionConversionCtor, CanPromotesType)
{
    const flcn::Quaternion quat1(3.0f, 1.0f, 6.0f, 2.0f);

    [[maybe_unused]] const flcn::Quaternion<double> quat2(quat1);

    static_assert(std::is_same_v<decltype(quat2)::value_type, double>);
}


TEST(QuaternionConversionCtor, PerformsDeepCopy)
{
    // Given a float quaternion
    const flcn::Quaternion quat1(3.0f, 1.0f, 6.0f, 2.0f);

    // When converted to a double quaternion
    flcn::Quaternion<double> quat2(quat1);
    // And one of its value mutated
    quat2.x() = 5;

    // Then, the float quaternion remains unchanged
    EXPECT_QUAT_CONTAINS(quat1, 3.0f, 1.0f, 6.0f, 2.0f);

    // And, the new quaternion is of type double with the mutated value
    EXPECT_QUAT_CONTAINS(quat2, 5.0, 1.0, 6.0, 2.0);
}


TEST(QuaternionConversionCtor, CanDemotesType)
{
    const flcn::Quaternion quat1(3.0, 1.0, 6.0, 2.0);

    [[maybe_unused]] const flcn::Quaternion<float> quat2(quat1);

    static_assert(std::is_same_v<decltype(quat2)::value_type, float>);
}

/** @} */
