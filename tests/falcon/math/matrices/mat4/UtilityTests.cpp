/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 01, 2026
 *
 * @brief Verify @ref flcn::Mat4 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat4x4_Utils
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    template <typename T>
        requires std::floating_point<T>
    struct Mat4UtilityParams
    {
        flcn::Mat4<T> mat;
        bool expected;
    };


    /**
     * @brief Test fixture for @ref flcn::Mat4 Infinity Checking.
     */
    class Mat4InfCheckerTests: public testing::TestWithParam<Mat4UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat4UtilsInfMatrices, Mat4InfCheckerTests,
        ::testing::Values(
            Mat4UtilityParams{ flcn::Mat4(flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                         1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                               true },
            Mat4UtilityParams{ flcn::Mat4(1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                         1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                               true },
            Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                         1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                               true },
            Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                         1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                               true },
            Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f,
                                         1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                               true },
            Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f,
                                         1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                               true },
            Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f, 1.0f,
                                         1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                               true },
            Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F, 1.0f,
                                         1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                               true },
            Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::INFINITY_F,
                                         1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                               true },
            Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                         flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                               true },
            Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                         flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                               true },
            Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                         flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f),
                               true },
            Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                         flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f),
                               true },
            Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                         flcn::constants::INFINITY_F, 1.0f, 1.0f),
                               true },
            Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                         1.0f, flcn::constants::INFINITY_F, 1.0f),
                               true },
            Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                         1.0f, 1.0f, flcn::constants::INFINITY_F),
                               true },
            Mat4UtilityParams{ flcn::Mat4(flcn::constants::INFINITY_F, flcn::constants::INFINITY_F,
                                         flcn::constants::INFINITY_F, flcn::constants::INFINITY_F),
                               true },
            Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f), false }));


    /**
     * @brief Test fixture for @ref flcn::Mat4 NaN Checking.
     */
    class Mat4NaNCheckerTests: public testing::TestWithParam<Mat4UtilityParams<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat4UtilsNaNMatrices, Mat4NaNCheckerTests,
        ::testing::Values(Mat4UtilityParams{ flcn::Mat4(flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                       1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                             true },
                          Mat4UtilityParams{ flcn::Mat4(1.0f, flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                       1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                             true },
                          Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                       1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                             true },
                          Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f,
                                                       1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                             true },
                          Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::NaN, 1.0f, 1.0f, 1.0f,
                                                       1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                             true },
                          Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::NaN, 1.0f, 1.0f,
                                                       1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                             true },
                          Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::NaN, 1.0f,
                                                       1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                             true },
                          Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::NaN,
                                                       1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                             true },
                          Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                       flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                             true },
                          Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                       flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                             true },
                          Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                       flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                                             true },
                          Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                       flcn::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f),
                                             true },
                          Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                       1.0f, flcn::constants::NaN, 1.0f, 1.0f, 1.0f),
                                             true },
                          Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                       1.0f, 1.0f, flcn::constants::NaN, 1.0f, 1.0f),
                                             true },
                          Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                       1.0f, 1.0f, 1.0f, flcn::constants::NaN, 1.0f),
                                             true },
                          Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                                       1.0f, 1.0f, 1.0f, 1.0f, flcn::constants::NaN),
                                             true },
                          Mat4UtilityParams{ flcn::Mat4(flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
                                                       flcn::constants::NaN),
                                             true },
                          Mat4UtilityParams{ flcn::Mat4(1.0f, 1.0f, 1.0f, 1.0f), false }));


    /**
     * @brief Test fixture for @ref flcn::Mat4 utilities, verifying across various integral types.
     */
    template <typename>
    class Mat4UtilsIntTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Mat4UtilsIntTests, SupportedIntegralTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat4 INF_MAT(flcn::constants::INFINITY_F, 1.0f, 1.0f, 1.0f);
        constexpr flcn::Mat4 NAN_MAT(flcn::constants::NaN, 1.0f, 1.0f, 1.0f);
        constexpr flcn::Mat4 MAT(1.0f, 1.0f, 1.0f, 1.0f);

        /** @test Verify that the Mat4 hasNaN return correct boolean at compile time. */
        static_assert(MAT.hasNaN() == false);
        static_assert(NAN_MAT.hasNaN() == true);

        /** @test Verify that the Mat4 hasNaN (static wrapper) return correct boolean at compile time. */
        static_assert(flcn::Mat4<float>::hasNaN(MAT) == false);
        static_assert(flcn::Mat4<float>::hasNaN(NAN_MAT) == true);


        /** @test Verify that the Mat4 hasInf return correct boolean at compile time. */
        static_assert(INF_MAT.hasInf() == true);
        static_assert(MAT.hasInf() == false);

        /** @test Verify that the Mat4 hasInf (static wrapper) return correct boolean at compile time. */
        static_assert(flcn::Mat4<float>::hasInf(INF_MAT) == true);
        static_assert(flcn::Mat4<float>::hasInf(MAT) == false);

    } // namespace static_tests

} // namespace



/**************************************
 *         INFINITY CHECKER           *
 **************************************/

TEST_P(Mat4InfCheckerTests, ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasInf());
}


TYPED_TEST(Mat4UtilsIntTests, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Mat4(value, value, value, value).hasInf());
}


TEST_P(Mat4InfCheckerTests, StaticWrapper_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Mat4<float>::hasInf(mat));
}


TYPED_TEST(Mat4UtilsIntTests, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Mat4<TypeParam>::hasInf(flcn::Mat4(value, value, value, value)));
}



/**************************************
 *         NAN CHECKER TESTS          *
 **************************************/

TEST_P(Mat4NaNCheckerTests, ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasNaN());
}


TYPED_TEST(Mat4UtilsIntTests, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Mat4(value, value, value, value).hasNaN());
}


TEST_P(Mat4NaNCheckerTests, StaticWrapper_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, flcn::Mat4<float>::hasNaN(mat));
}


TYPED_TEST(Mat4UtilsIntTests, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(flcn::Mat4<TypeParam>::hasNaN(flcn::Mat4(value, value, value, value)));
}

/** @} */
