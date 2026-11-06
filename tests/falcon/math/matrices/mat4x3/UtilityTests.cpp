/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref flcn::Mat4x3 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4x3TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat4x3_Utils
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    template <typename T>
        requires std::floating_point<T>
    struct Mat4x3UtilityParams
    {
        flcn::Mat4x3<T> mat;
        bool expected;
    };


    /**
     * @brief Test fixture for @ref flcn::Mat4x3 Infinity Checking.
     */
    class Mat4x3InfCheckerTests: public testing::TestWithParam<Mat4x3UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat4x3UtilsInfMatrices, Mat4x3InfCheckerTests,
        ::testing::Values(
            Mat4x3UtilityParams{ flcn::Mat4x3(flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F,
                                             1.0f, 1.0f, 1.0f),
                                 true },
            Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                             flcn::constants::INFINITY_F, 1.0f, 1.0f),
                                 true },
            Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                             flcn::constants::INFINITY_F, 1.0f),
                                 true },
            Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                             flcn::constants::INFINITY_F),
                                 true },
            Mat4x3UtilityParams{
                flcn::Mat4x3(flcn::constants::INFINITY_F, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                            flcn::constants::INFINITY_F, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                            flcn::constants::INFINITY_F, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                            flcn::constants::INFINITY_F, flcn::constants::INFINITY_F, flcn::constants::INFINITY_F),
                true },
            Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                 false }));


    /**
     * @brief Test fixture for @ref flcn::Mat4x3 NaN Checking.
     */
    class Mat4x3NaNCheckerTests: public testing::TestWithParam<Mat4x3UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat4x3UtilsNaNMatrices, Mat4x3NaNCheckerTests,
        ::testing::Values(Mat4x3UtilityParams{ flcn::Mat4x3(flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, 1.0f, flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, 1.0f, 1.0f, flcn::constants::NaN, 1.0f, 1.0f, 1.0f,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::NaN, 1.0f, 1.0f,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::NaN, 1.0f, 1.0f,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::NaN, 1.0f,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::NaN,
                                                           1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           flcn::constants::NaN, 1.0f, 1.0f, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           flcn::constants::NaN, 1.0f, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           flcn::constants::NaN, 1.0f),
                                               true },
                          Mat4x3UtilityParams{ flcn::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                           1.0f, flcn::constants::NaN),
                                               true },
                          Mat4x3UtilityParams{
                              flcn::Mat4x3(flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
                                          flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
                                          flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
                                          flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN),
                              true },
                          Mat4x3UtilityParams{
                              flcn::Mat4x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                              false }));


    /**
     * @brief Test fixture for @ref flcn::Mat4x3 utilities, verifying across various integral types.
     */
    template <typename>
    class Mat4x3UtilsIntTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Mat4x3UtilsIntTests, SupportedIntegralTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat4x3 INF_MAT(flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                      1.0f, 1.0f);
        constexpr flcn::Mat4x3 NAN_MAT(flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                      1.0f);
        constexpr flcn::Mat4x3 MAT(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

        /** @test Verify that the Mat4x3 hasNaN return correct boolean at compile time. */
        static_assert(MAT.hasNaN() == false);
        static_assert(NAN_MAT.hasNaN() == true);

        /** @test Verify that the Mat4x3 hasNaN (static wrapper) return correct boolean at compile time. */
        static_assert(flcn::Mat4x3<float>::hasNaN(MAT) == false);
        static_assert(flcn::Mat4x3<float>::hasNaN(NAN_MAT) == true);


        /** @test Verify that the Mat4x3 hasInf return correct boolean at compile time. */
        static_assert(INF_MAT.hasInf() == true);
        static_assert(MAT.hasInf() == false);

        /** @test Verify that the Mat4x3 hasInf (static wrapper) return correct boolean at compile time. */
        static_assert(flcn::Mat4x3<float>::hasInf(INF_MAT) == true);
        static_assert(flcn::Mat4x3<float>::hasInf(MAT) == false);

    } // namespace static_tests

} // namespace



/**************************************
 *         INFINITY CHECKER           *
 **************************************/

TEST_P(Mat4x3InfCheckerTests, ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasInf());
}


TYPED_TEST(Mat4x3UtilsIntTests, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(
        flcn::Mat4x3(value, value, value, value, value, value, value, value, value, value, value, value).hasInf());
}


TEST_P(Mat4x3InfCheckerTests, StaticWrapper_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Mat4x3<float>::hasInf(mat));
}


TYPED_TEST(Mat4x3UtilsIntTests, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Mat4x3<TypeParam>::hasInf(
        flcn::Mat4x3(value, value, value, value, value, value, value, value, value, value, value, value)));
}



/**************************************
 *         NAN CHECKER TESTS          *
 **************************************/

TEST_P(Mat4x3NaNCheckerTests, ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasNaN());
}


TYPED_TEST(Mat4x3UtilsIntTests, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(
        flcn::Mat4x3(value, value, value, value, value, value, value, value, value, value, value, value).hasNaN());
}


TEST_P(Mat4x3NaNCheckerTests, StaticWrapper_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Mat4x3<float>::hasNaN(mat));
}


TYPED_TEST(Mat4x3UtilsIntTests, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Mat4x3<TypeParam>::hasNaN(
        flcn::Mat4x3(value, value, value, value, value, value, value, value, value, value, value, value)));
}

/** @} */
