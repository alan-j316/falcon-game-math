/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref flcn::Mat4x2 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4x2TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat4x2_Utils
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    template <typename T>
        requires std::floating_point<T>
    struct Mat4x2UtilityParams
    {
        flcn::Mat4x2<T> mat;
        bool expected;
    };


    /**
     * @brief Test fixture for @ref flcn::Mat4x2 Infinity Checking.
     */
    class Mat4x2InfCheckerTests: public testing::TestWithParam<Mat4x2UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat4UtilsInfMatrices, Mat4x2InfCheckerTests,
        ::testing::Values(
            Mat4x2UtilityParams{ flcn::Mat4x2(flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                 true },
            Mat4x2UtilityParams{ flcn::Mat4x2(1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                 true },
            Mat4x2UtilityParams{ flcn::Mat4x2(1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                 true },
            Mat4x2UtilityParams{ flcn::Mat4x2(1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f),
                                 true },
            Mat4x2UtilityParams{ flcn::Mat4x2(1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f),
                                 true },
            Mat4x2UtilityParams{ flcn::Mat4x2(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f),
                                 true },
            Mat4x2UtilityParams{ flcn::Mat4x2(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f),
                                 true },
            Mat4x2UtilityParams{ flcn::Mat4x2(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F),
                                 true },
            Mat4x2UtilityParams{ flcn::Mat4x2(flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                             flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                             flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                             flcn::constants::INFINITY_F, flcn::constants::INFINITY_F),
                                 true },
            Mat4x2UtilityParams{ flcn::Mat4x2(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), false }));



    /**
     * @brief Test fixture for @ref flcn::Mat4x2 NaN Checking.
     */
    class Mat4x2NaNCheckerTests: public testing::TestWithParam<Mat4x2UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat4UtilsNaNMatrices, Mat4x2NaNCheckerTests,
        ::testing::Values(
            Mat4x2UtilityParams{ flcn::Mat4x2(flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
            Mat4x2UtilityParams{ flcn::Mat4x2(1.0f, flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
            Mat4x2UtilityParams{ flcn::Mat4x2(1.0f, 1.0f, flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
            Mat4x2UtilityParams{ flcn::Mat4x2(1.0f, 1.0f, 1.0f, flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f), true },
            Mat4x2UtilityParams{ flcn::Mat4x2(1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::NaN, 1.0f, 1.0f, 1.0f), true },
            Mat4x2UtilityParams{ flcn::Mat4x2(1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::NaN, 1.0f, 1.0f, 1.0f), true },
            Mat4x2UtilityParams{ flcn::Mat4x2(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::NaN, 1.0f, 1.0f), true },
            Mat4x2UtilityParams{ flcn::Mat4x2(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::NaN, 1.0f), true },
            Mat4x2UtilityParams{ flcn::Mat4x2(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::NaN), true },
            Mat4x2UtilityParams{ flcn::Mat4x2(flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
                                             flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
                                             flcn::constants::NaN, flcn::constants::NaN),
                                 true },
            Mat4x2UtilityParams{ flcn::Mat4x2(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), false }));



    /**
     * @brief Test fixture for @ref flcn::Mat4x2 utilities, verifying across various integral types.
     */
    template <typename>
    class Mat4x2IntegralUtilityTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Mat4x2IntegralUtilityTests, SupportedIntegralTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat4x2 INF_MAT(flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
        constexpr flcn::Mat4x2 NAN_MAT(flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
        constexpr flcn::Mat4x2 MAT(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);


        /** @test Verify that the Mat4x2 hasNaN return correct boolean at compile time. */
        static_assert(MAT.hasNaN() == false);
        static_assert(NAN_MAT.hasNaN() == true);

        /** @test Verify that the Mat4x2 hasNaN (static wrapper) return correct boolean at compile time. */
        static_assert(flcn::Mat4x2<float>::hasNaN(MAT) == false);
        static_assert(flcn::Mat4x2<float>::hasNaN(NAN_MAT) == true);


        /** @test Verify that the Mat4x2 hasInf return correct boolean at compile time. */
        static_assert(INF_MAT.hasInf() == true);
        static_assert(MAT.hasInf() == false);

        /** @test Verify that the Mat4x2 hasInf (static wrapper) return correct boolean at compile time. */
        static_assert(flcn::Mat4x2<float>::hasInf(INF_MAT) == true);
        static_assert(flcn::Mat4x2<float>::hasInf(MAT) == false);

    } // namespace static_tests

} // namespace



/**************************************
 *         INFINITY CHECKER           *
 **************************************/

TEST_P(Mat4x2InfCheckerTests, ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasInf());
}


TYPED_TEST(Mat4x2IntegralUtilityTests, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Mat4x2(value, value, value, value, value, value, value, value).hasInf());
}


TEST_P(Mat4x2InfCheckerTests, StaticWrapper_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Mat4x2<float>::hasInf(mat));
}


TYPED_TEST(Mat4x2IntegralUtilityTests, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Mat4x2<TypeParam>::hasInf(flcn::Mat4x2(value, value, value, value, value, value, value, value)));
}



/**************************************
 *         NAN CHECKER TESTS          *
 **************************************/

TEST_P(Mat4x2NaNCheckerTests, ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasNaN());
}


TYPED_TEST(Mat4x2IntegralUtilityTests, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Mat4x2(value, value, value, value, value, value, value, value).hasNaN());
}


TEST_P(Mat4x2NaNCheckerTests, StaticWrapper_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Mat4x2<float>::hasNaN(mat));
}


TYPED_TEST(Mat4x2IntegralUtilityTests, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Mat4x2<TypeParam>::hasNaN(flcn::Mat4x2(value, value, value, value, value, value, value, value)));
}

/** @} */
