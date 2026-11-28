/**
 * @file NormalizationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 28, 2026
 *
 * @brief Verifies vector normalization(static variants).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

namespace
{


    /// +---------------------------------------------------------------------------------------+
    /// |                                 STATIC TESTS                                          |
    /// +---------------------------------------------------------------------------------------+

    namespace static_tests
    {}

} // namespace



/// +---------------------------------------------------------------------------------------+
/// |                                 VEC3(SIMD)                                            |
/// +---------------------------------------------------------------------------------------+


/// +---------------------------------------------------------------------------------------+
/// |                                 VEC3(SIMD)                                            |
/// +---------------------------------------------------------------------------------------+

/**
 * @test Verify that normalizing a vector using static variant of @ref flcn::simd::Vec3::normalize
 *       returns a unit vector.
 */
TYPED_TEST(SimdVec3NormalizationTests, StaticWrapper_Normalize_NonZeroVectorReturnsUnitVector)
{
    const flcn::simd::Vec3 normalized = flcn::simd::Vec3<TypeParam>::normalize(this->_vec);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that normalizing a 3D vector using static variant of @ref flcn::simd::Vec3::safeNormalize
 *       returns a unit vector.
 */
TYPED_TEST(SimdVec3NormalizationTests, StaticWrapper_SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const flcn::simd::Vec3 normalized = flcn::simd::Vec3<TypeParam>::safeNormalize(this->_vec);
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using static variant of
 *       @ref flcn::simd::Vec3::safeNormalize returns a zero-vector.
 */
TYPED_TEST(SimdVec3NormalizationTests, StaticWrapper_SafeNormalize_ZeroVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(flcn::simd::Vec3<TypeParam>::safeNormalize(flcn::simd::Vec3<TypeParam>::zero())); }

/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::simd::Vec3::safeNormalize
 *       returns a zero-vector.
 */
TEST(SimdVec3Normalization, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(flcn::simd::Vec3<float>::safeNormalize(flcn::simd::Vec3<float>::qnan())); }


/**
 * @test Verify that the normalizing a 3D vector using static variant of @ref flcn::simd::Vec3::safeNormalize
 *       always return a floating-point vector.
 */
TYPED_TEST(SimdVec3NormalizationTests,
           StaticWrapper_SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = flcn::simd::Vec3<TypeParam>::safeNormalize(this->_vec);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}




/**
 * @test Verify that normalizing a 3D vector using static variant of @ref flcn::simd::Vec3::tryNormalize
 *       returns a unit vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(SimdVec3NormalizationTests, StaticWrapper_TryNormalize_NonZeroVectorReturnsUnitVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::simd::Vec3 normalized = flcn::simd::Vec3<TypeParam>::tryNormalize(this->_vec, flag);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using static variant of
 *       @ref flcn::simd::Vec3::tryNormalize returns a zero-vector and
 *       sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(SimdVec3NormalizationTests, StaticWrapper_TryNormalize_ZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::simd::Vec3<TypeParam>::zero().tryNormalize(flag));
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::simd::Vec3::tryNormalize
 *       returns a zero-vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(SimdVec3Normalization, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::simd::Vec3<float>::tryNormalize(flcn::simd::Vec3<float>::qnan(), flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that the normalizing a 3D vector using static variant of @ref flcn::simd::Vec3::tryNormalize
 *       always return a floating-point vector.
 */
TYPED_TEST(SimdVec3NormalizationTests,
           StaticWrapper_TryNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] flcn::OperationStatus flag;
    [[maybe_unused]] const auto normalized = flcn::simd::Vec3<TypeParam>::tryNormalize(this->_vec, flag);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}




/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::simd::Vec3::safeNormalize
 *       returns a zero-vector.
 */
TEST_P(SimdVec3NormalizationNaNTests, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(flcn::simd::Vec3<ParamType::value_type>::safeNormalize(vec));
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::simd::Vec3::tryNormalize
 *       returns a zero-vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(SimdVec3NormalizationNaNTests, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(flcn::simd::Vec3<ParamType::value_type>::tryNormalize(vec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/// +---------------------------------------------------------------------------------------+
/// |                                 VEC4(SIMD)                                            |
/// +---------------------------------------------------------------------------------------+
