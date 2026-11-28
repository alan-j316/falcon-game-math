/**
 * @file NormalizationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref flcn::simd::Vec3 normalization logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"



/**
 * @addtogroup T_Falcon_Vec3_Normalize
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec3 normalization.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class SimdVec3NormalizationTests: public testing::Test
    {
        using R = flcn::Magnitude<T>;

    protected:
        flcn::simd::Vec3<T> _vec;
        flcn::simd::Vec3<R> _expectedUnitVec;

        void SetUp() override
        {
            _vec             = { T(14), T(27), T(83) };
            _expectedUnitVec = { static_cast<R>(0.1583767155508236), static_cast<R>(0.30544080856230266),
                                 static_cast<R>(0.9389476707655972) };
        }
    };
    TYPED_TEST_SUITE(SimdVec3NormalizationTests, SupportedFloatingPointTypes);



    /**
     * @brief Test fixture for @ref Vec3 normalization with zero vectors.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class SimdVec3ZeroNormalizationTests: public testing::Test
    {
    protected:
        flcn::simd::Vec3<T> _vec;

        void SetUp() override { _vec = { T(0), T(0), T(0) }; }
    };
    TYPED_TEST_SUITE(SimdVec3ZeroNormalization, SupportedFloatingPointTypes);



    /**
     * @brief Test fixture for @ref Vec3 normalization with NaN vectors.
     */
    class SimdVec3NormalizationNaNTests: public testing::TestWithParam<flcn::simd::Vec3<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(SimdVec3NormalizationNaNVectors, SimdVec3NormalizationNaNTests,
                             ::testing::Values(flcn::simd::Vec3<float>(flcn::constants::NaN, 1.0f, 1.0f),
                                               flcn::simd::Vec3<float>(1.0f, flcn::constants::NaN, 1.0f),
                                               flcn::simd::Vec3<float>(1.0f, 1.0f, flcn::constants::NaN),
                                               flcn::simd::Vec3<float>(flcn::constants::NaN, flcn::constants::NaN,
                                                                flcn::constants::NaN)));

} // namespace



/**************************************
 *        NORMALIZATION TESTS         *
 **************************************/

/** @test Verify that normalizing a vector using @ref flcn::simd::Vec3::normalize returns a unit vector. */
TYPED_TEST(SimdVec3NormalizationTests, Normalize_NonZeroVectorReturnsUnitVector)
{
    const flcn::simd::Vec3 normalized = this->_vec.normalize();

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that normalizing a vector using @ref flcn::simd::Vec3::normalize
 *       always return a floating-point vector.
 */
TYPED_TEST(SimdVec3NormalizationTests, NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = this->_vec.normalize();
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}



/**************************************
 *     SAFE NORMALIZATION TESTS       *
 **************************************/

/** @test Verify that normalizing a vector using @ref flcn::simd::Vec3::safeNormalize returns a unit vector. */
TYPED_TEST(SimdVec3NormalizationTests, SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const flcn::simd::Vec3 normalized = this->_vec.safeNormalize();
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using @ref flcn::simd::Vec3::safeNormalize
 *       returns a zero-vector.
 */
TYPED_TEST(SimdVec3NormalizationTests, SafeNormalize_ZeroVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(flcn::simd::Vec3<TypeParam>::zero().safeNormalize()); }


/**
 * @test Verify that attempting to normalize a NaN vector using @ref flcn::simd::Vec3::safeNormalize
 *       returns a zero-vector.
 */
TEST(SimdVec3Normalization, SafeNormalize_NaNVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(flcn::simd::Vec3<float>::qnan().safeNormalize()); }


/**
 * @test Verify that normalizing a vector using @ref flcn::simd::Vec3::safeNormalize always
 *       return a floating-point vector.
 */
TYPED_TEST(SimdVec3NormalizationTests, SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = this->_vec.safeNormalize();
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}



/**************************************
 *      TRY NORMALIZATION TESTS       *
 **************************************/

/**
 * @test Verify that normalizing a vector using @ref flcn::simd::Vec3::tryNormalize
 *       returns a unit vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(SimdVec3NormalizationTests, TryNormalize_NonZeroVectorReturnsUnitVector)
{
    flcn::OperationStatus flag;
    const flcn::simd::Vec3 normalized = this->_vec.tryNormalize(flag);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using @ref flcn::simd::Vec3::tryNormalize
 *       returns a zero-vector and sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(SimdVec3NormalizationTests, TryNormalize_ZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::simd::Vec3<TypeParam>::zero().tryNormalize(flag));
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that attempting to normalize a NaN vector using @ref flcn::simd::Vec3::tryNormalize
 *       returns a zero-vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(SimdVec3Normalization, TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::simd::Vec3<float>::qnan().tryNormalize(flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that normalizing a vector using @ref flcn::simd::Vec3::tryNormalize always
 *       return a floating-point vector.
 */
TYPED_TEST(SimdVec3NormalizationTests, TryNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] flcn::OperationStatus flag;
    [[maybe_unused]] const auto normalized = this->_vec.tryNormalize(flag);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}



/**************************************
 *      NAN NORMALIZATION TESTS       *
 **************************************/

/**
 * @test Verify that attempting to normalize a NaN vector of @ref flcn::simd::Vec3::safeNormalize
 *       returns a zero-vector.
 */
TEST_P(SimdVec3NormalizationNaNTests, SafeNormalize_NaNVectorReturnsZeroVector)
{
    const auto& vec = GetParam();
    EXPECT_VEC_ZERO(vec.safeNormalize());
}


/**
 * @test Verify that attempting to normalize a NaN vector of @ref flcn::simd::Vec3::tryNormalize
 *       returns a zero-vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(SimdVec3NormalizationNaNTests, TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(vec.tryNormalize(flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/** @} */
