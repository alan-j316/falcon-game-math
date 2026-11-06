/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 14, 2026
 *
 * @brief Verify @ref flcn::Mat2 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat2x2_Utils
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    template <typename T>
        requires std::floating_point<T>
    struct Mat2UtilityParams
    {
        flcn::Mat2<T> mat;
        bool expected;
    };


    /**
     * @brief Test fixture for @ref flcn::Mat2 Infinity Checking.
     */
    class Mat2InfCheckerTests: public testing::TestWithParam<Mat2UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat2UtilsInfMatrices, Mat2InfCheckerTests,
        ::testing::Values(Mat2UtilityParams{ flcn::Mat2(flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f), true },
                          Mat2UtilityParams{ flcn::Mat2(1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f), true },
                          Mat2UtilityParams{ flcn::Mat2(1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f), true },
                          Mat2UtilityParams{ flcn::Mat2(1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F), true },
                          Mat2UtilityParams{ flcn::Mat2(flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                                       flcn::constants::INFINITY_F, flcn::constants::INFINITY_F),
                                             true },
                          Mat2UtilityParams{ flcn::Mat2(1.0f, 1.0f, 1.0f, 1.0f), false }));

    /**
     * @brief Test fixture for @ref flcn::Mat2 NaN Checking.
     */
    class Mat2NaNCheckerTests: public testing::TestWithParam<Mat2UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat2UtilsNaNMatrices, Mat2NaNCheckerTests,
        ::testing::Values(Mat2UtilityParams{ flcn::Mat2(flcn::constants::NaN, 1.0f), true },
                          Mat2UtilityParams{ flcn::Mat2(1.0f, flcn::constants::NaN, 1.0f, 1.0f), true },
                          Mat2UtilityParams{ flcn::Mat2(1.0f, 1.0f, flcn::constants::NaN, 1.0f), true },
                          Mat2UtilityParams{ flcn::Mat2(1.0f, 1.0f, 1.0f, flcn::constants::NaN), true },
                          Mat2UtilityParams{ flcn::Mat2(flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
                                                       flcn::constants::NaN),
                                             true },
                          Mat2UtilityParams{ flcn::Mat2(1.0f, 1.0f, 1.0f, 1.0f), false }));



    /**
     * @brief Test fixture for @ref flcn::Mat2 utilities, verifying across various integral types.
     */
    template <typename>
    class Mat2UtilsIntTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Mat2UtilsIntTests, SupportedIntegralTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat2 INF_MAT(flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f);
        constexpr flcn::Mat2 NAN_MAT(flcn::constants::NaN, 1.0f, 1.0f, 1.0f);
        constexpr flcn::Mat2 MAT(1.0f, 1.0f, 1.0f, 1.0f);


        /** s@test Verify that the Mat2 hasNaN return correct boolean at compile time. */
        static_assert(MAT.hasNaN() == false);
        static_assert(NAN_MAT.hasNaN() == true);

        /** @test Verify that the Mat2 hasNaN (static wrapper) return correct boolean at compile time. */
        static_assert(flcn::Mat2<float>::hasNaN(MAT) == false);
        static_assert(flcn::Mat2<float>::hasNaN(NAN_MAT) == true);


        /** @test Verify that the Mat2 hasInf return correct boolean at compile time. */
        static_assert(INF_MAT.hasInf() == true);
        static_assert(MAT.hasInf() == false);


        /** @test Verify that the Mat2 hasInf (static wrapper) return correct boolean at compile time. */
        static_assert(flcn::Mat2<float>::hasInf(INF_MAT) == true);
        static_assert(flcn::Mat2<float>::hasInf(MAT) == false);

    } // namespace static_tests

} // namespace



/**************************************
 *         INFINITY CHECKER           *
 **************************************/

TEST_P(Mat2InfCheckerTests, HasInf_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasInf());
}


TYPED_TEST(Mat2UtilsIntTests, HasInf_ReturnsFalseForIntegralMatrix)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Mat2(value, value).hasInf());
}


TEST_P(Mat2InfCheckerTests, StaticWrapper_HasInf_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Mat2<float>::hasInf(mat));
}


TYPED_TEST(Mat2UtilsIntTests, StaticWrapper_HasInf_ReturnsFalseForIntegralMatrix)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Mat2<TypeParam>::hasInf(flcn::Mat2(value, value)));
}



/**************************************
 *             NAN CHECKER            *
 **************************************/

TEST_P(Mat2NaNCheckerTests, HasNaN_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasNaN());
}


TYPED_TEST(Mat2UtilsIntTests, HasNaN_ReturnsFalseForIntegralMatrix)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Mat2(value, value).hasNaN());
}


TEST_P(Mat2NaNCheckerTests, StaticWrapper_HasNaN_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Mat2<float>::hasNaN(mat));
}


TYPED_TEST(Mat2UtilsIntTests, StaticWrapper_HasNaN_ReturnsFalseForIntegralMatrix)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Mat2<TypeParam>::hasNaN(flcn::Mat2(value, value)));
}

/** @} */
