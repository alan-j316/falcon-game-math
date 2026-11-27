/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 04, 2026
 *
 * @brief Verify @ref flcn::Quaternion utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "include/QuaternionTestSetup.h"


/**
 * @addtogroup T_Falcon_Quaternion_Utils
 * @{
 */

namespace
{


    /**************************************
     *                                    *
     *            TEST SETUP              *
     *                                    *
     **************************************/

    template <typename T>
        requires std::floating_point<T>
    struct QuaternionUtilityParams
    {
        flcn::Quat<T> vec;
        bool expected;
    };


    /** @brief Parameterized test fixture for @ref flcn::Quaternion infinity checker. */
    class QuaternionInfCheckerTests: public testing::TestWithParam<QuaternionUtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        QuaternionInfCheckerTestSuite, QuaternionInfCheckerTests,
        ::testing::Values(
            QuaternionUtilityParams{ flcn::Quat(flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f), true },
            QuaternionUtilityParams{ flcn::Quat(1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f), true },
            QuaternionUtilityParams{ flcn::Quat(1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f), true },
            QuaternionUtilityParams{ flcn::Quat(1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f), true },
            QuaternionUtilityParams{ flcn::Quat(1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F), true },
            QuaternionUtilityParams{ flcn::Quat(flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                                     flcn::constants::INFINITY_F, flcn::constants::INFINITY_F),
                                     true },
            QuaternionUtilityParams{ flcn::Quat(1.0f, 1.0f, 1.0f, 1.0f), false }));


    /** @brief Parameterized test fixture for @ref flcn::Quaternion NaN checker. */
    class QuaternionNaNCheckerTests: public ::testing::TestWithParam<QuaternionUtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        QuaternionNaNCheckerTestSuite, QuaternionNaNCheckerTests,
        ::testing::Values(QuaternionUtilityParams{ flcn::Quat(flcn::constants::NaN, 1.0f, 1.0f, 1.0f), true },
                          QuaternionUtilityParams{ flcn::Quat(1.0f, flcn::constants::NaN, 1.0f, 1.0f), true },
                          QuaternionUtilityParams{ flcn::Quat(1.0f, 1.0f, flcn::constants::NaN, 1.0f), true },
                          QuaternionUtilityParams{ flcn::Quat(1.0f, 1.0f, flcn::constants::NaN, 1.0f), true },
                          QuaternionUtilityParams{ flcn::Quat(1.0f, 1.0f, 1.0f, flcn::constants::NaN), true },
                          QuaternionUtilityParams{ flcn::Quat(flcn::constants::NaN, flcn::constants::NaN,
                                                                   flcn::constants::NaN, flcn::constants::NaN),
                                                   true },
                          QuaternionUtilityParams{ flcn::Quat(1.0f, 1.0f, 1.0f, 1.0f), false }));


    /** @brief Test fixture for @ref flcn::Quaternion utilities, for testing against integral types. */
    template <typename T>
    class QuaternionIntegralUtilityTests: public testing::Test
    {};
    TYPED_TEST_SUITE(QuaternionIntegralUtilityTests, SupportedIntegralTypes);


    /**************************************
     *                                    *
     *           STATIC TESTS             *
     *                                    *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Quat NORMAL_QUATERNION(1.0f, 2.0f, 3.0f, 4.0f);
        constexpr flcn::Quat INF_QUATERNION(flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                                 flcn::constants::INFINITY_F, flcn::constants::INFINITY_F);
        constexpr flcn::Quat NAN_QUATERNION(flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
                                                 flcn::constants::NaN);

        /// @test Verify that quaternion hasInf return correct boolean at compile time.
        static_assert(NORMAL_QUATERNION.hasInf() == false);
        static_assert(INF_QUATERNION.hasInf() == true);
        static_assert(NAN_QUATERNION.hasInf() == false);

        /// @test Verify that quaternion hasInf(static variant) return correct boolean at compile time.
        static_assert(flcn::Quat<float>::hasInf(NORMAL_QUATERNION) == false);
        static_assert(flcn::Quat<float>::hasInf(INF_QUATERNION) == true);
        static_assert(flcn::Quat<float>::hasInf(NAN_QUATERNION) == false);

        /// @test Verify that quaternion hasNaN return correct boolean at compile time.
        static_assert(NORMAL_QUATERNION.hasNaN() == false);
        static_assert(INF_QUATERNION.hasNaN() == false);
        static_assert(NAN_QUATERNION.hasNaN() == true);

        /// @test Verify that quaternion hasNaN(static variant) return correct boolean at compile time.
        static_assert(flcn::Quat<float>::hasNaN(NORMAL_QUATERNION) == false);
        static_assert(flcn::Quat<float>::hasNaN(INF_QUATERNION) == false);
        static_assert(flcn::Quat<float>::hasNaN(NAN_QUATERNION) == true);

    } // namespace static_tests

} // namespace



/**************************************
 *      INFINITY CHECKER TESTS        *
 **************************************/

TEST_P(QuaternionInfCheckerTests, ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasInf());
}



/** @test Verify that @ref std::Quaternion::hasInf returns False for integral types. */
TYPED_TEST(QuaternionIntegralUtilityTests, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Quat(value, value, value, value).hasInf());
}


TEST_P(QuaternionInfCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsInfinity)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Quat<float>::hasInf(vec));
}


TYPED_TEST(QuaternionIntegralUtilityTests, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Quat<TypeParam>::hasInf(flcn::Quat(value, value, value, value)));
}


/**************************************
 *         NAN CHECKER TESTS          *
 **************************************/

TEST_P(QuaternionNaNCheckerTests, ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, vec.hasNaN());
}


TYPED_TEST(QuaternionIntegralUtilityTests, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Quat(value, value, value, value).hasNaN());
}


TEST_P(QuaternionNaNCheckerTests, StaticWrapper_ReturnTrueIfAnyComponentIsNaN)
{
    const auto& [vec, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Quat<float>::hasNaN(vec));
}


TYPED_TEST(QuaternionIntegralUtilityTests, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Quat<TypeParam>::hasNaN(flcn::Quat(value, value, value, value)));
}

/** @} */
