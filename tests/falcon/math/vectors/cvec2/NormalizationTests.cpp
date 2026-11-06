/**
 * @file NormalizationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref flcn::CVec2 normalization logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CVec2TestSetup.h"



/**
 * @addtogroup T_FALCON_CVec2_Normalize
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref CVec2 normalization.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class CVec2NormalizationTests: public testing::Test
    {
        using R = flcn::Magnitude<T>;

    protected:
        flcn::CVec2<T> _vec;
        flcn::CVec2<R> _expectedUnitVec;

        void SetUp() override
        {
            _vec             = { T(14), T(27) };
            _expectedUnitVec = { static_cast<R>(0.46031716445500037), static_cast<R>(0.8877545314489294) };
        }
    };
    TYPED_TEST_SUITE(CVec2NormalizationTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref CVec2 normalization with zero vectors.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class CVec2NormalizationZeroTests: public testing::Test
    {
    protected:
        flcn::CVec2<T> _vec;

        void SetUp() override { _vec = { T(0), T(0) }; }
    };
    TYPED_TEST_SUITE(CVec2NormalizationZeroTests, SupportedArithmeticTypes);




    /**
     * @brief Test fixture for @ref CVec2 normalization with NaN vectors.
     */
    class CVec2NormalizationNaNTests: public testing::TestWithParam<flcn::CVec2<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(CVec2NormalizationNaNVectors, CVec2NormalizationNaNTests,
                             ::testing::Values(flcn::CVec2<float>(flcn::constants::NaN, 1.0f),
                                               flcn::CVec2<float>(1.0f, flcn::constants::NaN),
                                               flcn::CVec2<float>(flcn::constants::NaN, flcn::constants::NaN)));



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        // TODO: Add static tests after making sqrt constexpr
        // constexpr flcn::CVec2 Vec(14, 27);
        // constexpr auto norm = Vec.normalize();
    }
} // namespace



/**************************************
 *        NORMALIZATION TESTS         *
 **************************************/

TYPED_TEST(CVec2NormalizationTests, Normalize_NonZeroVectorReturnsUnitVector)
{
    const flcn::CVec2 normalized = this->_vec.normalize();
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


TYPED_TEST(CVec2NormalizationTests, StaticWrapper_Normalize_NonZeroVectorReturnsUnitVector)
{
    const flcn::CVec2 normalized = flcn::CVec2<TypeParam>::normalize(this->_vec);
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


TYPED_TEST(CVec2NormalizationTests, NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = this->_vec.normalize();
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}




/**************************************
 *                                    *
 *     SAFE NORMALIZATION TESTS       *
 *                                    *
 **************************************/

TYPED_TEST(CVec2NormalizationTests, SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const flcn::CVec2 normalized = this->_vec.safeNormalize();
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


TYPED_TEST(CVec2NormalizationTests, SafeNormalize_ZeroVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(flcn::CVec2<TypeParam>::zero().safeNormalize()); }


TEST(CVec2NormalizationTests, SafeNormalize_NaNVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(flcn::CVec2<float>::qnan().safeNormalize()); }


TYPED_TEST(CVec2NormalizationTests, SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = this->_vec.safeNormalize();
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


TYPED_TEST(CVec2NormalizationTests, StaticWrapper_SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const flcn::CVec2 normalized = flcn::CVec2<TypeParam>::safeNormalize(this->_vec);
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


TYPED_TEST(CVec2NormalizationTests, StaticWrapper_SafeNormalize_ZeroVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(flcn::CVec2<TypeParam>::safeNormalize(flcn::CVec2<TypeParam>::zero())); }


TEST(CVec2NormalizationTests, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(flcn::CVec2<float>::safeNormalize(flcn::CVec2<float>::qnan())); }


TYPED_TEST(CVec2NormalizationTests, StaticWrapper_SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = flcn::CVec2<TypeParam>::safeNormalize(this->_vec);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}



/**************************************
 *      TRY NORMALIZATION TESTS       *
 **************************************/

/**
 * @test Verify that normalizing a vector using @ref flcn::CVec2::tryNormalize
 *       returns a unit vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(CVec2NormalizationTests, TryNormalize_NonZeroVectorReturnsUnitVector)
{
    flcn::OperationStatus flag;
    const flcn::CVec2 normalized = this->_vec.tryNormalize(flag);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using @ref flcn::CVec2::tryNormalize
 *       returns a zero-vector and sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(CVec2NormalizationTests, TryNormalize_ZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::CVec2<TypeParam>::zero().tryNormalize(flag));
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that attempting to normalize a NaN vector using @ref flcn::CVec2::tryNormalize
 *       returns a zero-vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(CVec2NormalizationTests, TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::CVec2<float>::qnan().tryNormalize(flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that normalizing a vector using @ref flcn::CVec2::tryNormalize always
 *       return a floating-point vector.
 */
TYPED_TEST(CVec2NormalizationTests, TryNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] flcn::OperationStatus flag;
    [[maybe_unused]] const auto normalized = this->_vec.tryNormalize(flag);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**
 * @test Verify that normalizing a 2D vector using static variant of @ref flcn::CVec2::tryNormalize
 *       returns a unit vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(CVec2NormalizationTests, StaticWrapper_TryNormalize_NonZeroVectorReturnsUnitVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::CVec2 normalized = flcn::CVec2<TypeParam>::tryNormalize(this->_vec, flag);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using static variant of
 *       @ref flcn::CVec2::tryNormalize returns a zero-vector and
 *       sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(CVec2NormalizationTests, StaticWrapper_TryNormalize_ZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::CVec2<TypeParam>::zero().tryNormalize(flag));
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::CVec2::tryNormalize
 *       returns a zero-vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(CVec2NormalizationTests, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::CVec2<float>::tryNormalize(flcn::CVec2<float>::qnan(), flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that the normalizing a 2D vector using static variant of @ref flcn::CVec2::tryNormalize
 *       always return a floating-point vector.
 */
TYPED_TEST(CVec2NormalizationTests, StaticWrapper_TryNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] flcn::OperationStatus flag;
    [[maybe_unused]] const auto normalized = flcn::CVec2<TypeParam>::tryNormalize(this->_vec, flag);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**************************************
 *                                    *
 *      NAN NORMALIZATION TESTS       *
 *                                    *
 **************************************/

/**
 * @test Verify that attempting to normalize a NaN vector of @ref flcn::CVec2::safeNormalize
 *       returns a zero-vector.
 */
TEST_P(CVec2NormalizationNaNTests, SafeNormalize_NaNVectorReturnsZeroVector)
{
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(vec.safeNormalize());
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::CVec2::safeNormalize
 *       returns a zero-vector.
 */
TEST_P(CVec2NormalizationNaNTests, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(flcn::CVec2<ParamType::value_type>::safeNormalize(vec));
}


/**
 * @test Verify that attempting to normalize a NaN vector of @ref flcn::CVec2::tryNormalize
 *       returns a zero-vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(CVec2NormalizationNaNTests, TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(vec.tryNormalize(flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::CVec2::tryNormalize
 *       returns a zero-vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(CVec2NormalizationNaNTests, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(flcn::CVec2<ParamType::value_type>::tryNormalize(vec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/** @} */
