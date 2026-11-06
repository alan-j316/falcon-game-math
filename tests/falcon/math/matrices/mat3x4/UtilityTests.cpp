/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 20, 2026
 *
 * @brief Verify @ref flcn::Mat3x4 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3x4TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat3x4_Utils
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    template <typename T>
        requires std::floating_point<T>
    struct Mat3x4UtilityParams
    {
        flcn::Mat3x4<T> mat;
        bool expected;
    };


    /**
     * @brief Test fixture for @ref flcn::Mat3x4 Infinity Checking.
     */
    class Mat3x4InfCheckerTests: public testing::TestWithParam<Mat3x4UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat3x4UtilsInfMatrices, Mat3x4InfCheckerTests,
        ::testing::Values(
            Mat3x4UtilityParams{ flcn::Mat3x4(flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                             flcn::constants::INFINITY_F, 1.0f, 1.0f),
                                 true },
            Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                             flcn::constants::INFINITY_F, 1.0f),
                                 true },
            Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                             flcn::constants::INFINITY_F),
                                 true },
            Mat3x4UtilityParams{
                flcn::Mat3x4(flcn::constants::INFINITY_F, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                            flcn::constants::INFINITY_F, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                            flcn::constants::INFINITY_F, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                            flcn::constants::INFINITY_F, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F),
                true },
            Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                 false }));



    /**
     * @brief Test fixture for @ref flcn::Mat3x4 NaN Checking.
     */
    class Mat3x4NaNCheckerTests: public testing::TestWithParam<Mat3x4UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat3x4UtilsNaNMatrices, Mat3x4NaNCheckerTests,
        ::testing::Values(Mat3x4UtilityParams{ flcn::Mat3x4(flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, 1.0f, flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, 1.0f, 1.0f, flcn::constants::NaN, 1.0f, 1.0f, 1.0f,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::NaN, 1.0f, 1.0f,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::NaN, 1.0f,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::NaN, 1.0f,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::NaN, 1.0f,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::NaN,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           flcn::constants::NaN, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           flcn::constants::NaN, 1.0f, 1.0f),
                                               true },
                          Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           flcn::constants::NaN, 1.0f),
                                               true },
                          Mat3x4UtilityParams{ flcn::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           1.0f, flcn::constants::NaN),
                                               true },
                          Mat3x4UtilityParams{
                              flcn::Mat3x4(flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
                                          flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
                                          flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
                                          flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN),
                              true },
                          Mat3x4UtilityParams{
                              flcn::Mat3x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                              false }));



    /**
     * @brief Test fixture for @ref flcn::Mat3x4 utilities, verifying across various integral types.
     */
    template <typename>
    class Mat3x4UtilsIntTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Mat3x4UtilsIntTests, SupportedIntegralTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat3x4 INF_MAT(flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                      flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                      -flcn::constants::INFINITY_F, -flcn::constants::INFINITY_F);
        constexpr flcn::Mat3x4 NAN_MAT(flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                      1.0f);
        constexpr flcn::Mat3x4 MAT(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);



        /** @test Verify that the Mat3x4 hasNaN return correct boolean at compile time. */
        static_assert(MAT.hasNaN() == false);
        static_assert(NAN_MAT.hasNaN() == true);

        /** @test Verify that the Mat3x4 hasNaN (static wrapper) return correct boolean at compile time. */
        static_assert(flcn::Mat3x4<float>::hasNaN(MAT) == false);
        static_assert(flcn::Mat3x4<float>::hasNaN(NAN_MAT) == true);


        /** @test Verify that the Mat3x4 hasInf return correct boolean at compile time. */
        static_assert(INF_MAT.hasInf() == true);
        static_assert(MAT.hasInf() == false);


        /** @test Verify that the Mat3x4 hasInf (static wrapper) return correct boolean at compile time. */
        static_assert(flcn::Mat3x4<float>::hasInf(INF_MAT) == true);
        static_assert(flcn::Mat3x4<float>::hasInf(MAT) == false);

    } // namespace static_tests

} // namespace



/**************************************
 *      INFINITY CHECKER TESTS        *
 **************************************/

TEST_P(Mat3x4InfCheckerTests, ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasInf());
}


TYPED_TEST(Mat3x4UtilsIntTests, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(
        flcn::Mat3x4(value, value, value, value, value, value, value, value, value, value, value, value).hasInf());
}


TEST_P(Mat3x4InfCheckerTests, StaticWrapper_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Mat3x4<float>::hasInf(mat));
}


TYPED_TEST(Mat3x4UtilsIntTests, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Mat3x4<TypeParam>::hasInf(
        flcn::Mat3x4(value, value, value, value, value, value, value, value, value, value, value, value)));
}



/**************************************
 *         NAN CHECKER TESTS          *
 **************************************/

TEST_P(Mat3x4NaNCheckerTests, ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasNaN());
}


TYPED_TEST(Mat3x4UtilsIntTests, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(
        flcn::Mat3x4(value, value, value, value, value, value, value, value, value, value, value, value).hasNaN());
}


TEST_P(Mat3x4NaNCheckerTests, StaticWrapper_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Mat3x4<float>::hasNaN(mat));
}


TYPED_TEST(Mat3x4UtilsIntTests, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Mat3x4<TypeParam>::hasNaN(
        flcn::Mat3x4(value, value, value, value, value, value, value, value, value, value, value, value)));
}

/** @} */
