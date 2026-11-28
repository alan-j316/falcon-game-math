/**
 * @file NormalizationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 28, 2026
 *
 * @brief Verifies vector normalization(static variants).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


/**
 *  @addtogroup T_Falcon_Normalization
 *  @{
 */

#include "CommonSetup.h"
#include "NormalizationTestFixture.h"
#include "utils/VectorUtils.h"

namespace
{
    using namespace testutils;

    /// +---------------------------------------------------------------------------------------+
    /// |                                 STATIC TESTS                                          |
    /// +---------------------------------------------------------------------------------------+

    namespace static_tests
    {
        // TODO: Add static tests after making sqrt constexpr
    }

} // namespace



/// +---------------------------------------------------------------------------------------+
/// |                                 VEC2(SCALAR)                                          |
/// +---------------------------------------------------------------------------------------+

TYPED_TEST(Vec2NormalizationTests, StaticWrapper_Normalize_NonZeroVectorReturnsUnitVector)
{
    const flcn::Vec2 normalized = flcn::normalize(this->_vec);
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


TYPED_TEST(Vec2NormalizationTests, StaticWrapper_SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const flcn::Vec2 normalized = flcn::safeNormalize(this->_vec);
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


TYPED_TEST(Vec2NormalizationTests, StaticWrapper_SafeNormalize_ZeroVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(flcn::safeNormalize(flcn::Vec2<TypeParam>::zero())); }


TEST(Vec2NormalizationTests, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(flcn::safeNormalize(flcn::Vec2<float>::qnan())); }


TYPED_TEST(Vec2NormalizationTests, StaticWrapper_SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = flcn::safeNormalize(this->_vec);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::ValueType>);
}


/**
 * @test Verify that normalizing a 2D vector using static variant of @ref flcn::Vec2::tryNormalize
 *       returns a unit vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec2NormalizationTests, StaticWrapper_TryNormalize_NonZeroVectorReturnsUnitVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Vec2 normalized = flcn::tryNormalize(this->_vec, flag);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using static variant of
 *       @ref flcn::Vec2::tryNormalize returns a zero-vector and
 *       sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec2NormalizationTests, StaticWrapper_TryNormalize_ZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::Vec2<TypeParam>::zero().tryNormalize(flag));
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::Vec2::tryNormalize
 *       returns a zero-vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec2NormalizationTests, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::tryNormalize(flcn::Vec2<float>::qnan(), flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that the normalizing a 2D vector using static variant of @ref flcn::Vec2::tryNormalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vec2NormalizationTests, StaticWrapper_TryNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] flcn::OperationStatus flag;
    [[maybe_unused]] const auto normalized = flcn::tryNormalize(this->_vec, flag);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::ValueType>);
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::Vec2::safeNormalize
 *       returns a zero-vector.
 */
TEST_P(Vec2NormalizationNaNTests, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(flcn::safeNormalize(vec));
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::Vec2::tryNormalize
 *       returns a zero-vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec2NormalizationNaNTests, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(flcn::tryNormalize(vec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/// +---------------------------------------------------------------------------------------+
/// |                                 VEC3(SCALAR)                                          |
/// +---------------------------------------------------------------------------------------+



/**
 * @test Verify that normalizing a 3D vector using static variant of @ref flcn::Vec3::safeNormalize
 *       returns a unit vector.
 */
TYPED_TEST(Vec3NormalizationTests, StaticWrapper_SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const flcn::Vec3 normalized = flcn::safeNormalize(this->_vec);
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using static variant of
 *       @ref flcn::Vec3::safeNormalize returns a zero-vector.
 */
TYPED_TEST(Vec3NormalizationTests, StaticWrapper_SafeNormalize_ZeroVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(flcn::safeNormalize(flcn::Vec3<TypeParam>::zero())); }


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::Vec3::safeNormalize
 *       returns a zero-vector.
 */
TEST(Vec3Normalization, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(flcn::safeNormalize(flcn::Vec3<float>::qnan())); }


/**
 * @test Verify that the normalizing a 3D vector using static variant of @ref flcn::Vec3::safeNormalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vec3NormalizationTests, StaticWrapper_SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = flcn::safeNormalize(this->_vec);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::ValueType>);
}


/**
 * @test Verify that normalizing a 3D vector using static variant of @ref flcn::Vec3::tryNormalize
 *       returns a unit vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec3NormalizationTests, StaticWrapper_TryNormalize_NonZeroVectorReturnsUnitVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Vec3 normalized = flcn::tryNormalize(this->_vec, flag);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using static variant of
 *       @ref flcn::Vec3::tryNormalize returns a zero-vector and
 *       sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec3NormalizationTests, StaticWrapper_TryNormalize_ZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::Vec3<TypeParam>::zero().tryNormalize(flag));
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::Vec3::tryNormalize
 *       returns a zero-vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec3Normalization, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::tryNormalize(flcn::Vec3<float>::qnan(), flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that normalizing a vector using static variant of @ref flcn::Vec3::normalize
 *       returns a unit vector.
 */
TYPED_TEST(Vec3NormalizationTests, StaticWrapper_Normalize_NonZeroVectorReturnsUnitVector)
{
    const flcn::Vec3 normalized = flcn::normalize(this->_vec);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that the normalizing a 3D vector using static variant of @ref flcn::Vec3::tryNormalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vec3NormalizationTests, StaticWrapper_TryNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] flcn::OperationStatus flag;
    [[maybe_unused]] const auto normalized = flcn::tryNormalize(this->_vec, flag);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::ValueType>);
}

/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::Vec3::safeNormalize
 *       returns a zero-vector.
 */
TEST_P(Vec3NormalizationNaNTests, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(flcn::safeNormalize(vec));
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::Vec3::tryNormalize
 *       returns a zero-vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec3NormalizationNaNTests, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(flcn::tryNormalize(vec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/// +---------------------------------------------------------------------------------------+
/// |                                 VEC4(SCALAR)                                          |
/// +---------------------------------------------------------------------------------------+

/**
 * @test Verify that normalizing a vector using static variant of @ref flcn::Vec4::normalize
 *       returns a unit vector.
 */
TYPED_TEST(Vec4NormalizationTests, StaticWrapper_Normalize_NonZeroVectorReturnsUnitVector)
{
    const flcn::Vec4 normalized = flcn::normalize(this->_vec);
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that normalizing a 4D vector using static variant of @ref flcn::Vec4::safeNormalize
 *       returns a unit vector.
 */
TYPED_TEST(Vec4NormalizationTests, StaticWrapper_SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const flcn::Vec4 normalized = flcn::safeNormalize(this->_vec);
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using static variant of
 *       @ref flcn::Vec4::safeNormalize returns a zero-vector.
 */
TYPED_TEST(Vec4NormalizationTests, StaticWrapper_SafeNormalize_ZeroVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(flcn::safeNormalize(flcn::Vec4<TypeParam>::zero())); }


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::Vec4::safeNormalize
 *       returns a zero-vector.
 */
TEST(Vec4Normalization, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(flcn::safeNormalize(flcn::Vec4<float>::qnan())); }


/**
 * @test Verify that the normalizing a 4D vector using static variant of @ref flcn::Vec4::safeNormalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vec4NormalizationTests, StaticWrapper_SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = flcn::safeNormalize(this->_vec);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::ValueType>);
}

/**
 * @test Verify that normalizing a 4D vector using static variant of @ref flcn::Vec4::tryNormalize
 *       returns a unit vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec4NormalizationTests, StaticWrapper_TryNormalize_NonZeroVectorReturnsUnitVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Vec4 normalized = flcn::tryNormalize(this->_vec, flag);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using static variant of
 *       @ref flcn::Vec4::tryNormalize returns a zero-vector and
 *       sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec4NormalizationTests, StaticWrapper_TryNormalize_ZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::Vec4<TypeParam>::zero().tryNormalize(flag));
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::Vec4::tryNormalize
 *       returns a zero-vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec4Normalization, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::tryNormalize(flcn::Vec4<float>::qnan(), flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that the normalizing a 4D vector using static variant of @ref flcn::Vec4::tryNormalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vec4NormalizationTests, StaticWrapper_TryNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] flcn::OperationStatus flag;
    [[maybe_unused]] const auto normalized = flcn::tryNormalize(this->_vec, flag);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::ValueType>);
}



/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::Vec4::safeNormalize
 *       returns a zero-vector.
 */
TEST_P(Vec4NormalizationNaNTests, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(flcn::safeNormalize(vec));
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::Vec4::tryNormalize
 *       returns a zero-vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec4NormalizationNaNTests, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(flcn::tryNormalize(vec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/// +---------------------------------------------------------------------------------------+
/// |                                 VEC2(SIMD)                                            |
/// +---------------------------------------------------------------------------------------+


TYPED_TEST(SimdVec2NormalizationTests, StaticWrapper_Normalize_NonZeroVectorReturnsUnitVector)
{
    const flcn::simd::Vec2 normalized = flcn::normalize(this->_vec);
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


TYPED_TEST(SimdVec2NormalizationTests, StaticWrapper_SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const flcn::simd::Vec2 normalized = flcn::safeNormalize(this->_vec);
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


TYPED_TEST(SimdVec2NormalizationTests, StaticWrapper_SafeNormalize_ZeroVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(flcn::safeNormalize(flcn::simd::Vec2<TypeParam>::zero())); }


TEST(SimdVec2NormalizationTests, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(flcn::safeNormalize(flcn::simd::Vec2<float>::qnan())); }


TYPED_TEST(SimdVec2NormalizationTests,
           StaticWrapper_SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = flcn::safeNormalize(this->_vec);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::ValueType>);
}



/**
 * @test Verify that normalizing a 2D vector using static variant of @ref flcn::simd::Vec2::tryNormalize
 *       returns a unit vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(SimdVec2NormalizationTests, StaticWrapper_TryNormalize_NonZeroVectorReturnsUnitVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::simd::Vec2 normalized = flcn::tryNormalize(this->_vec, flag);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using static variant of
 *       @ref flcn::simd::Vec2::tryNormalize returns a zero-vector and
 *       sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(SimdVec2NormalizationTests, StaticWrapper_TryNormalize_ZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::simd::Vec2<TypeParam>::zero().tryNormalize(flag));
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::simd::Vec2::tryNormalize
 *       returns a zero-vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(SimdVec2NormalizationTests, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::tryNormalize(flcn::simd::Vec2<float>::qnan(), flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that the normalizing a 2D vector using static variant of @ref flcn::simd::Vec2::tryNormalize
 *       always return a floating-point vector.
 */
TYPED_TEST(SimdVec2NormalizationTests,
           StaticWrapper_TryNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] flcn::OperationStatus flag;
    [[maybe_unused]] const auto normalized = flcn::tryNormalize(this->_vec, flag);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::ValueType>);
}

/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::simd::Vec2::safeNormalize
 *       returns a zero-vector.
 */
TEST_P(SimdVec2NormalizationNaNTests, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(flcn::safeNormalize(vec));
}

/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::simd::Vec2::tryNormalize
 *       returns a zero-vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(SimdVec2NormalizationNaNTests, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(flcn::tryNormalize(vec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/// +---------------------------------------------------------------------------------------+
/// |                                 VEC3(SIMD)                                            |
/// +---------------------------------------------------------------------------------------+

/**
 * @test Verify that normalizing a vector using static variant of @ref flcn::simd::Vec3::normalize
 *       returns a unit vector.
 */
TYPED_TEST(SimdVec3NormalizationTests, StaticWrapper_Normalize_NonZeroVectorReturnsUnitVector)
{
    const flcn::simd::Vec3 normalized = flcn::normalize(this->_vec);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that normalizing a 3D vector using static variant of @ref flcn::simd::Vec3::safeNormalize
 *       returns a unit vector.
 */
TYPED_TEST(SimdVec3NormalizationTests, StaticWrapper_SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const flcn::simd::Vec3 normalized = flcn::safeNormalize(this->_vec);
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using static variant of
 *       @ref flcn::simd::Vec3::safeNormalize returns a zero-vector.
 */
TYPED_TEST(SimdVec3NormalizationTests, StaticWrapper_SafeNormalize_ZeroVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(flcn::safeNormalize(flcn::simd::Vec3<TypeParam>::zero())); }

/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::simd::Vec3::safeNormalize
 *       returns a zero-vector.
 */
TEST(SimdVec3Normalization, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{ EXPECT_VEC_ZERO(flcn::safeNormalize(flcn::simd::Vec3<float>::qnan())); }


/**
 * @test Verify that the normalizing a 3D vector using static variant of @ref flcn::simd::Vec3::safeNormalize
 *       always return a floating-point vector.
 */
TYPED_TEST(SimdVec3NormalizationTests,
           StaticWrapper_SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = flcn::safeNormalize(this->_vec);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::ValueType>);
}




/**
 * @test Verify that normalizing a 3D vector using static variant of @ref flcn::simd::Vec3::tryNormalize
 *       returns a unit vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(SimdVec3NormalizationTests, StaticWrapper_TryNormalize_NonZeroVectorReturnsUnitVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::simd::Vec3 normalized = flcn::tryNormalize(this->_vec, flag);

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
    EXPECT_VEC_ZERO(flcn::tryNormalize(flcn::simd::Vec3<float>::qnan(), flag));
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
    [[maybe_unused]] const auto normalized = flcn::tryNormalize(this->_vec, flag);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::ValueType>);
}




/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::simd::Vec3::safeNormalize
 *       returns a zero-vector.
 */
TEST_P(SimdVec3NormalizationNaNTests, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
{
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(flcn::safeNormalize(vec));
}


/**
 * @test Verify that attempting to normalize a NaN vector using static variant of @ref flcn::simd::Vec3::tryNormalize
 *       returns a zero-vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(SimdVec3NormalizationNaNTests, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto& vec = GetParam();

    EXPECT_VEC_ZERO(flcn::tryNormalize(vec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/// +---------------------------------------------------------------------------------------+
/// |                                 VEC4(SIMD)                                            |
/// +---------------------------------------------------------------------------------------+


/** @} */
