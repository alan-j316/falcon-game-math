/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 17, 2026
 *
 * @brief Verify @ref flcn::Mat2x3 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2x3TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat2x3_Utils
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/
    template <typename T>
        requires std::floating_point<T>
    struct Mat2x3UtilityParams
    {
        flcn::Mat2x3<T> mat;
        bool expected;
    };



    /// @brief Test fixture for @ref flcn::Mat2x3 Infinity Checking.
    class Mat2x3InfCheckerTests: public testing::TestWithParam<Mat2x3UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat2x3UtilsInfMatrices, Mat2x3InfCheckerTests,
        ::testing::Values(
            Mat2x3UtilityParams{ flcn::Mat2x3(flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
            Mat2x3UtilityParams{ flcn::Mat2x3(1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f), true },
            Mat2x3UtilityParams{ flcn::Mat2x3(1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f), true },
            Mat2x3UtilityParams{ flcn::Mat2x3(1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f), true },
            Mat2x3UtilityParams{ flcn::Mat2x3(1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f), true },
            Mat2x3UtilityParams{ flcn::Mat2x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F), true },
            Mat2x3UtilityParams{ flcn::Mat2x3(flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                             flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                             flcn::constants::INFINITY_F, flcn::constants::INFINITY_F),
                                 true },
            Mat2x3UtilityParams{ flcn::Mat2x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), false }));



    /// @brief Test fixture for @ref flcn::Mat2x3 NaN Checking.
    class Mat2x3NaNCheckerTests: public testing::TestWithParam<Mat2x3UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat2x3UtilsNaNMatrices, Mat2x3NaNCheckerTests,
        ::testing::Values(Mat2x3UtilityParams{ flcn::Mat2x3(flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
                          Mat2x3UtilityParams{ flcn::Mat2x3(1.0f, flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f), true },
                          Mat2x3UtilityParams{ flcn::Mat2x3(1.0f, 1.0f, flcn::constants::NaN, 1.0f, 1.0f, 1.0f), true },
                          Mat2x3UtilityParams{ flcn::Mat2x3(1.0f, 1.0f, 1.0f, flcn::constants::NaN, 1.0f, 1.0f), true },
                          Mat2x3UtilityParams{ flcn::Mat2x3(1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::NaN, 1.0f), true },
                          Mat2x3UtilityParams{ flcn::Mat2x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::NaN), true },
                          Mat2x3UtilityParams{ flcn::Mat2x3(flcn::constants::NaN, flcn::constants::NaN,
                                                           flcn::constants::NaN, flcn::constants::NaN,
                                                           flcn::constants::NaN, flcn::constants::NaN),
                                               true },
                          Mat2x3UtilityParams{ flcn::Mat2x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), false }));



    /// @brief Test fixture for @ref flcn::Mat2x3 utilities, verifying across various integral types.
    template <typename>
    class Mat2x3UtilsIntTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Mat2x3UtilsIntTests, SupportedIntegralTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat2x3 INF_MAT(flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
        constexpr flcn::Mat2x3 NAN_MAT(flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
        constexpr flcn::Mat2x3 MAT(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);


        /** @test Verify that the Mat2x3 hasNaN return correct boolean at compile time. */
        static_assert(MAT.hasNaN() == false);
        static_assert(NAN_MAT.hasNaN() == true);

        /** @test Verify that the Mat2x3 hasNaN (static wrapper) return correct boolean at compile time. */
        static_assert(flcn::Mat2x3<float>::hasNaN(MAT) == false);
        static_assert(flcn::Mat2x3<float>::hasNaN(NAN_MAT) == true);

        /** @test Verify that the Mat2x3 hasInf return correct boolean at compile time. */
        static_assert(INF_MAT.hasInf() == true);
        static_assert(MAT.hasInf() == false);

        /** @test Verify that the Mat2x3 hasInf (static wrapper) return correct boolean at compile time. */
        static_assert(flcn::Mat2x3<float>::hasInf(INF_MAT) == true);
        static_assert(flcn::Mat2x3<float>::hasInf(MAT) == false);

    } // namespace static_tests

} // namespace



/**************************************
 *         INFINITY CHECKER           *
 **************************************/

TEST_P(Mat2x3InfCheckerTests, HasInf_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasInf());
}


TYPED_TEST(Mat2x3UtilsIntTests, HasInf_ReturnsFalseForIntegralMatrix)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Mat2x3(value, value, value, value, value, value).hasInf());
}


TEST_P(Mat2x3InfCheckerTests, StaticWrapper_HasInf_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Mat2x3<float>::hasInf(mat));
}


TYPED_TEST(Mat2x3UtilsIntTests, StaticWrapper_HasInf_ReturnsFalseForIntegralMatrix)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Mat2x3<TypeParam>::hasInf(flcn::Mat2x3(value, value, value, value, value, value)));
}



/**************************************
 *             NAN CHECKER            *
 **************************************/

TEST_P(Mat2x3NaNCheckerTests, HasNaN_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasNaN());
}


TYPED_TEST(Mat2x3UtilsIntTests, HasNaN_ReturnsFalseForIntegralMatrix)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Mat2x3(value, value, value, value, value, value).hasNaN());
}


TEST_P(Mat2x3NaNCheckerTests, StaticWrapper_HasNaN_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Mat2x3<float>::hasNaN(mat));
}


TYPED_TEST(Mat2x3UtilsIntTests, StaticWrapper_HasNaN_ReturnsFalseForIntegralMatrix)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Mat2x3<TypeParam>::hasNaN(flcn::Mat2x3(value, value, value, value, value, value)));
}

/** @} */
