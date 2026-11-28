/**
 * @file SimdVec3.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 28, 2026
 *
 * @brief Verifies flcn::simd::Vec3 projection and rejection.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


/**
 *  @addtogroup T_Falcon_Projection
 *  @{
 */

#include "CommonSetup.h"
#include "ProjectionTestFixture.h"
#include "utils/VectorUtils.h"

using namespace testutils;


/**
 * @test Verify that projecting onto a non-orthogonal vector using static variant of @ref flcn::simd::Vec3::project
 *       returns a non-zero vector.
 */
TYPED_TEST(SimdVec3ProjectionTests, StaticWrapper_Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const flcn::simd::Vec3 actualProjection = flcn::project(this->_vec, this->_ontoVec);
    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref flcn::simd::Vec3::projectNorm returns a non-zero vector.
 */
TEST(SimdVec3ProjectionTests, StaticWrapper_ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::simd::Vec3 b(1.0f, 0.0f, 0.0f);
    const flcn::simd::Vec3 expectedProjection(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::simd::Vec3 actualProjection = flcn::projectNorm(a, b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projection using static variant of @ref flcn::simd::Vec3::project
 *       always return floating-point vector.
 */
TYPED_TEST(SimdVec3ProjectionTests, StaticWrapper_Project_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::simd::Vec3 projection = flcn::project(this->_vec, this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::ValueType>);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector using static variant of @ref
 flcn::simd::Vec3::safeProject
 *       returns a non-zero vector.
 */
TYPED_TEST(SimdVec3ProjectionTests, StaticWrapper_SafeProject_Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const flcn::simd::Vec3 actualProjection = flcn::safeProject(this->_vec, this->_ontoVec);
    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref flcn::simd::Vec3::safeProjectNorm returns a non-zero vector.
 */
TEST(SimdVec3ProjectionTests, StaticWrapper_SafeProjectNorm_ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::simd::Vec3 b(1.0f, 0.0f, 0.0f);
    const flcn::simd::Vec3 expectedProjection(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::simd::Vec3 actualProjection = flcn::safeProjectNorm(a, b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}



/**
 * @test Verify that projecting a NaN vector onto a non-orthogonal unit vector using static variant of
 *       @ref flcn::simd::Vec3::safeProjectNorm returns a zero vector.
 */
TEST(SimdVec3ProjectionTests, StaticWrapper_SafeProjectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector and a normalized vector
    const flcn::simd::Vec3 a(1.0f, 2.0f, flcn::constants::NaN);
    const flcn::simd::Vec3 b(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::simd::Vec3 actualProjection = flcn::safeProjectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @test Verify that projecting a NaN vector onto a non-orthogonal unit vector using static variant of
 *       @ref flcn::simd::Vec3::safeProjectNorm returns a zero vector.
 */
TEST(SimdVec3ProjectionTests, StaticWrapper_SafeProjectNorm_OntoNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::simd::Vec3 b(1.0f, 1.0f, flcn::constants::NaN);

    // When the vector is projected onto the normalized vector
    const flcn::simd::Vec3 actualProjection = flcn::safeProjectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}

/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using static variant of @ref flcn::simd::Vec3::safeProject returns a non-zero vector.
 */
TEST(SimdVec3ProjectionTests, StaticWrapper_SafeProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::simd::Vec3 a(4.0f, 4.0f, 4.0f);
    const flcn::simd::Vec3 negativeZAxis(0.0f, 0.0f, -1.0f);
    const flcn::simd::Vec3 expectedProjection(0.0f, 0.0f, 4.0f);

    // When projected
    const auto actualProjection = flcn::safeProject(a, negativeZAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a zero length vector using static variant of @ref flcn::simd::Vec3::safeProject
 *       returns a type-promoted vector.
 */
TYPED_TEST(SimdVec3ProjectionTests, StaticWrapper_SafeProject_OntoZeroVectorReturnsZeroVector)
{
    const flcn::simd::Vec3 zeroVec = flcn::simd::Vec3<TypeParam>::zero();

    const flcn::simd::Vec3 actualProjection = flcn::safeProject(this->_vec, zeroVec);

    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @test Verify that projection using static variant of @ref flcn::simd::Vec3::safeProject
 *       always return floating-point vector.
 */
TYPED_TEST(SimdVec3ProjectionTests, StaticWrapper_SafeProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::simd::Vec3 projection = flcn::safeProject(this->_vec, this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::ValueType>);
}


/**
 * @test Verify that projection of NaN vector using static variant of @ref flcn::simd::Vec3::safeProject
 *       returns zero vector.
 */
TEST_P(SimdVec3ProjectionNaNTests, StaticWrapper_SafeProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::simd::Vec3<float>::one();

    EXPECT_VEC_ZERO(flcn::safeProject(nanVec, ontoVec));
}


/**
 * @test Verify that projection onto NaN vector using static variant of @ref flcn::simd::Vec3::safeProject
 *       returns zero vector.
 */
TEST_P(SimdVec3ProjectionNaNTests, StaticWrapper_SafeProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::simd::Vec3<float>::one();
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(flcn::safeProject(oneVec, ontoNaNVec));
}



/**
 * @test Verify that projecting onto a non-orthogonal vector using static variant of @ref
 flcn::simd::Vec3::tryProject
 *       returns a non-zero vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(SimdVec3ProjectionTests,
           StaticWrapper_TryProject_Project_NonOrthogonalVectors_ReturnsNonZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::simd::Vec3 actualProjection = flcn::tryProject(this->_vec, this->_ontoVec, flag);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref flcn::simd::Vec3::tryProject returns a non-zero vector and sets the flag to
 *       @ref flcn::OperationStatus::SUCCESS.
 */
TEST(SimdVec3ProjectionTests,
     StaticWrapper_TryProject_ProjectionOntoNormalizedVectorReturnsNonZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::simd::Vec3 b(1.0f, 0.0f, 0.0f);
    const flcn::simd::Vec3 expectedProjection(1.0f, 0.0f, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const flcn::simd::Vec3 actualProjection = flcn::tryProject(a, b, flag);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}



/**
 * @test Verify that projecting a NaN vector onto a non-orthogonal unit vector using static variant of @ref
 * flcn::simd::Vec3::tryProjectNorm returns a zero vector and sets the flag to @ref
 flcn::OperationStatus::NANOPERAND.
 */
TEST(SimdVec3ProjectionTests, StaticWrapper_TryProjectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a NaN vector
    const flcn::simd::Vec3 a(flcn::constants::NaN, 2.0f, 3.0f);
    const flcn::simd::Vec3 b(1.0f, 0.0f, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the NaN vector
    const flcn::simd::Vec3 actualProjection = flcn::tryProjectNorm(a, b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/**
 * @test Verify that projecting a vector onto a NaN vector using static variant of @ref
 flcn::simd::Vec3::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(SimdVec3ProjectionTests, StaticWrapper_TryProjectNorm_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a NaN vector
    const flcn::simd::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::simd::Vec3 b(1.0f, flcn::constants::NaN, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the NaN vector
    const flcn::simd::Vec3 actualProjection = flcn::tryProjectNorm(a, b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}



/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using static variant of @ref flcn::simd::Vec3::tryProject returns a non-zero vector
 *       and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(SimdVec3ProjectionTests,
     StaticWrapper_TryProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirectionAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::simd::Vec3 a(4.0f, 4.0f, 4.0f);
    const flcn::simd::Vec3 negativeZAxis(0.0f, 0.0f, -1.0f);
    const flcn::simd::Vec3 expectedProjection(0.0f, 0.0f, 4.0f);
    flcn::OperationStatus flag;

    // When projected
    const auto actualProjection = flcn::tryProject(a, negativeZAxis, flag);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a zero length vector using static variant of @ref flcn::simd::Vec3::tryProject
 *       returns a type-promoted vector and sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(SimdVec3ProjectionTests, StaticWrapper_TryProject_OntoZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const flcn::simd::Vec3 zeroVec = flcn::simd::Vec3<TypeParam>::zero();
    flcn::OperationStatus flag;

    const flcn::simd::Vec3 actualProjection = flcn::tryProject(this->_vec, zeroVec, flag);

    EXPECT_VEC_ZERO(actualProjection);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that projection using static variant of @ref flcn::simd::Vec3::tryProject
 *       always return floating-point vector.
 */
TYPED_TEST(SimdVec3ProjectionTests, StaticWrapper_TryProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] flcn::OperationStatus flag;
    [[maybe_unused]] const flcn::simd::Vec3 projection = flcn::tryProject(this->_vec, this->_ontoVec, flag);
    static_assert(std::is_floating_point_v<typename decltype(projection)::ValueType>);
}


/**
 * @test Verify that projection of NaN vector using static variant of @ref flcn::simd::Vec3::tryProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(SimdVec3ProjectionNaNTests, StaticWrapper_TryProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::simd::Vec3<float>::one();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(flcn::tryProject(nanVec, ontoVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projection onto NaN vector using static variant of @ref flcn::simd::Vec3::tryProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(SimdVec3ProjectionNaNTests, StaticWrapper_TryProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::simd::Vec3<float>::one();
    const auto& ontoNaNVec = GetParam();
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::tryProject(oneVec, ontoNaNVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/** @} */
