/**
 * @file ArithmeticOperationDeathTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 4, 2026
 *
 * @brief Verifies quaternion assertions in quaternion arithmetic operations that can result in application death.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "../include/QuaternionTestSetup.h"


#ifdef ENABLE_DEBUG_TESTS

namespace
{
    /**
     * @brief Test fixture for verifying quaternion scalar division assertions.
     *
     * @tparam T The scalar type (uint32_t, float, double...) for the quaternion values.
     */
    template <typename T>
    class QuaternionScalarDivisionDeathTests: public testing::Test
    {
    protected:
        flcn::Quaternion<T> _quat;

        void SetUp() override { _quat = { T(17), T(31), T(59), T(73) }; }
    };
    TYPED_TEST_SUITE(QuaternionScalarDivisionDeathTests, SupportedArithmeticTypes);


    /** @brief Parameterized test fixture for @ref flcn::Quaternion NaN division operation. */
    class QuaternionNaNDivisionDeathTests: public testing::TestWithParam<flcn::Quaternion<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(QuaternionNaNDivisionTestSuite, QuaternionNaNDivisionDeathTests,
                             ::testing::Values(flcn::Quaternion(flcn::constants::NaN, 1.0f, 1.0f, 1.0f),
                                               flcn::Quaternion(1.0f, flcn::constants::NaN, 1.0f, 1.0f),
                                               flcn::Quaternion(1.0f, 1.0f, flcn::constants::NaN, 1.0f),
                                               flcn::Quaternion(1.0f, 1.0f, flcn::constants::NaN, 1.0f),
                                               flcn::Quaternion(1.0f, 1.0f, 1.0f, flcn::constants::NaN),
                                               flcn::Quaternion(flcn::constants::NaN, flcn::constants::NaN,
                                                               flcn::constants::NaN, flcn::constants::NaN)));

} // namespace




// Debug Mode behaviour

TYPED_TEST(QuaternionScalarDivisionDeathTests, DivideOperator_ByZeroTriggersAssertionInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(this->_quat / TypeParam(0)), ""); }


TYPED_TEST(QuaternionScalarDivisionDeathTests, DivideEqualsOperator_ByZeroTriggersAssertionInDebugMode)
{
    [[maybe_unused]] flcn::Quaternion newQuat = this->_quat;
    EXPECT_DEBUG_DEATH(static_cast<void>(newQuat /= TypeParam(0)), "");
}


TEST_P(QuaternionNaNDivisionDeathTests, DivideOperator_NaNQuaternionTriggersAssertionInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(GetParam() / 1.0f), ""); }


TEST(QuaternionNaNDivisionDeathTests, DivideOperator_DivisionByNaNTriggersAssertionInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(flcn::Quaternion(1.0f, 2.0f, 3.0f, 4.0f) / flcn::constants::NaN), ""); }


TEST_P(QuaternionNaNDivisionDeathTests, DivideEqualsOperator_NaNQuaternionTriggersInDebugMode)
{
    [[maybe_unused]] flcn::Quaternion newQuat = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(newQuat /= 1.0f), "");
}


TEST_P(QuaternionNaNDivisionDeathTests, DivideEqualsOperator_DivisionByNaNTriggersInDebugMode)
{
    [[maybe_unused]] flcn::Quaternion newQuat(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_DEBUG_DEATH(static_cast<void>(newQuat /= flcn::constants::NaN), "");
}


#else

// Release mode behaviour

TEST(QuaternionScalarDivision, FloatQuaternionDivisionByZero_ReturnsInfinityQuaternion_InReleaseMode)
{
    const flcn::Quaternion quat(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_QUAT_INF(quat / 0);
}


TEST(QuaternionScalarDivision, DoubleQuaternionDivisionByZero_ReturnsInfinityQuaternion_InReleaseMode)
{
    const flcn::Quaternion quat(1.0, 2.0, 3.0, 4.0);
    EXPECT_QUAT_INF(quat / 0);
}

#endif
