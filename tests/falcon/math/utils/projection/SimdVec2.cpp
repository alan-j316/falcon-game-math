/**
 * @file SimdVec2.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 28, 2026
 *
 * @brief Verifies flcn::simd::Vec2 projection and rejection.
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


TYPED_TEST(SimdVec2ProjectionTests, StaticWrapper_Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const auto actualProjection = flcn::project(this->_vec, this->_ontoVec);
    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref flcn::simd::Vec2::projectNorm returns a non-zero vector.
 */
TEST(SimdVec2ProjectionTests, StaticWrapper_ProjectNorm_NormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec2 a(1.0f, 2.0f);
    const flcn::simd::Vec2 b(1.0f, 0.0f);
    const flcn::simd::Vec2 expectedProjection(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::simd::Vec2 actualProjection = flcn::projectNorm(a, b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


TYPED_TEST(SimdVec2ProjectionTests, StaticWrapper_SafeProject_Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const flcn::simd::Vec2 actualProjection = flcn::safeProject(this->_vec, this->_ontoVec);
    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


TEST(SimdVec2ProjectionTests, StaticWrapper_SafeProjectNorm_NormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec2 a(1.0f, 2.0f);
    const flcn::simd::Vec2 b(1.0f, 0.0f);
    const flcn::simd::Vec2 expectedProjection(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::simd::Vec2 actualProjection = flcn::safeProjectNorm(a, b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


TEST(SimdVec2ProjectionTests, StaticWrapper_SafeProjectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector
    const flcn::simd::Vec2 a(1.0f, flcn::constants::NaN);
    const flcn::simd::Vec2 b(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::simd::Vec2 actualProjection = flcn::safeProjectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


TEST(SimdVec2ProjectionTests, StaticWrapper_SafeProjectNorm_OntoNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector
    const flcn::simd::Vec2 a(1.0f, 2.0f);
    const flcn::simd::Vec2 b(1.0f, flcn::constants::NaN);

    // When the vector is from a NaN vector
    const flcn::simd::Vec2 actualProjection = flcn::safeProjectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


TEST(SimdVec2ProjectionTests, StaticWrapper_SafeProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::simd::Vec2 a(4.0f, 4.0f);
    const flcn::simd::Vec2 negativeYAxis(0.0f, -1.0f);
    const flcn::simd::Vec2 expectedProjection(0.0f, 4.0f);

    // When projected
    const auto actualProjection = flcn::safeProject(a, negativeYAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


TYPED_TEST(SimdVec2ProjectionTests, StaticWrapper_SafeProject_OntoZeroVectorReturnsZeroVector)
{
    const flcn::simd::Vec2 zeroVec          = flcn::simd::Vec2<TypeParam>::zero();
    const flcn::simd::Vec2 actualProjection = flcn::safeProject(this->_vec, zeroVec);
    EXPECT_VEC_ZERO(actualProjection);
}

TEST_P(SimdVec2ProjectionNaNTests, StaticWrapper_SafeProject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::simd::Vec2<float>::one();

    EXPECT_VEC_ZERO(flcn::safeProject(nanVec, ontoVec));
}


TEST_P(SimdVec2ProjectionNaNTests, StaticWrapper_SafeProject_OntoNaNVectorReturnsZeroVector)
{
    const auto& oneVec     = flcn::simd::Vec2<float>::one();
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(flcn::safeProject(oneVec, ontoNaNVec));
}


/**
 * @test Verify that projecting onto a non-orthogonal vector using static variant of @ref flcn::simd::Vec2::tryProject
 *       returns a non-zero vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(SimdVec2ProjectionTests,
           StaticWrapper_TryProject_Project_NonOrthogonalVectors_ReturnsNonZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::simd::Vec2 actualProjection = flcn::tryProject(this->_vec, this->_ontoVec, flag);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref flcn::simd::Vec2::tryProjectNorm returns a non-zero vector and sets the flag to
 *       @ref flcn::OperationStatus::SUCCESS.
 */
TEST(SimdVec2ProjectionTests, StaticWrapper_TryProjectNorm_NormalizedVectorReturnsNonZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec2 a(1.0f, 2.0f);
    const flcn::simd::Vec2 b(1.0f, 0.0f);
    const flcn::simd::Vec2 expectedProjection(1.0f, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const flcn::simd::Vec2 actualProjection = flcn::tryProjectNorm(a, b, flag);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting a NaN vector onto a non-orthogonal unit vector using static variant of @ref
 * flcn::simd::Vec2::tryProjectNorm returns a zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(SimdVec2ProjectionTests, StaticWrapper_TryProjectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a NaN vector
    const flcn::simd::Vec2 a(flcn::constants::NaN, 2.0f);
    const flcn::simd::Vec2 b(1.0f, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the NaN vector
    const flcn::simd::Vec2 actualProjection = flcn::tryProjectNorm(a, b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/**
 * @test Verify that projecting a vector onto a NaN vector using static variant of @ref flcn::simd::Vec2::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(SimdVec2ProjectionTests, StaticWrapper_TryProjectNorm_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a NaN vector
    const flcn::simd::Vec2 a(1.0f, 2.0f);
    const flcn::simd::Vec2 b(1.0f, flcn::constants::NaN);
    flcn::OperationStatus flag;

    // When the vector is projected onto the NaN vector
    const flcn::simd::Vec2 actualProjection = flcn::tryProjectNorm(a, b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using static variant of @ref flcn::simd::Vec2::tryProject returns a non-zero vector
 *       and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(SimdVec2ProjectionTests,
     StaticWrapper_TryProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirectionAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::simd::Vec2 a(4.0f, 4.0f);
    const flcn::simd::Vec2 negativeYAxis(0.0f, -1.0f);
    const flcn::simd::Vec2 expectedProjection(0.0f, 4.0f);
    flcn::OperationStatus flag;

    // When projected
    const auto actualProjection = flcn::tryProject(a, negativeYAxis, flag);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a zero length vector using static variant of @ref flcn::simd::Vec2::tryProject
 *        returns a type-promoted vector and sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(SimdVec2ProjectionTests, StaticWrapper_TryProject_OntoZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const flcn::simd::Vec2 zeroVec = flcn::simd::Vec2<TypeParam>::zero();
    flcn::OperationStatus flag;

    const flcn::simd::Vec2 actualProjection = flcn::tryProject(this->_vec, zeroVec, flag);

    EXPECT_VEC_ZERO(actualProjection);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}

/**
 * @test Verify that projection of NaN vector using static variant of @ref flcn::simd::Vec2::tryProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(SimdVec2ProjectionNaNTests, StaticWrapper_TryProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::simd::Vec2<float>::one();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(flcn::tryProject(nanVec, ontoVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projection onto NaN vector using static variant of @ref flcn::simd::Vec2::tryProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(SimdVec2ProjectionNaNTests, StaticWrapper_TryProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::simd::Vec2<float>::one();
    const auto& ontoNaNVec = GetParam();
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::tryProject(oneVec, ontoNaNVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/**
 * @test Verify that rejecting from a non-orthogonal vector using static variant of @ref flcn::simd::Vec2::reject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(SimdVec2RejectionTests, StaticWrapper_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const flcn::simd::Vec2 actualRejection = flcn::reject(this->_vec, this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}

/**
 * @test Verify that rejecting from an orthogonal unit vector using static variant of @ref flcn::simd::Vec2::rejectNorm
 *       returns a non-zero vector with perpendicular component.
 */
TEST(SimdVec2RejectionTests, StaticWrapper_RejectionFromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec2 a(1.0f, 2.0f);
    const flcn::simd::Vec2 b(1.0f, 0.0f);
    const flcn::simd::Vec2 expectedRejection(0.0f, 2.0f);

    // When rejected from another
    const flcn::simd::Vec2 actualRejection = flcn::rejectNorm(a, b);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using static variant of
 *       @ref flcn::simd::Vec2::safeRejectNorm returns a non-zero vector with perpendicular component.
 */
TEST(SimdVec2RejectionTests, StaticWrapper_SafeRejectNorm_FromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec2 a(1.0f, 2.0f);
    const flcn::simd::Vec2 b(1.0f, 0.0f);
    const flcn::simd::Vec2 expectedRejection(0.0f, 2.0f);

    // When rejected from another
    const flcn::simd::Vec2 actualRejection = flcn::safeRejectNorm(a, b);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting a NaN vector from a non-orthogonal unit vector using static variant of
 *       @ref flcn::simd::Vec2::safeRejectNorm returns a zero vector.
 */
TEST(SimdVec2RejectionTests, StaticWrapper_SafeRejectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector
    const flcn::simd::Vec2 a(1.0f, flcn::constants::NaN);
    const flcn::simd::Vec2 b(1.0f, 0.0f);

    // When the vector is rejected onto the normalized vector
    const flcn::simd::Vec2 actualRejection = flcn::safeRejectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting from a NaN vector using static variant of
 *       @ref flcn::simd::Vec2::safeRejectNorm returns a zero vector.
 */
TEST(SimdVec2RejectionTests, StaticWrapper_SafeRejectNorm_FromNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector
    const flcn::simd::Vec2 a(1.0f, 2.0f);
    const flcn::simd::Vec2 b(1.0f, flcn::constants::NaN);

    // When the vector is rejected from a NaN vector
    const flcn::simd::Vec2 actualRejection = flcn::safeRejectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualRejection);
}



/**
 * @test Verify that safely rejecting from a parallel vector using static variant of @ref flcn::simd::Vec2::safeReject
 *       returns a zero vector.
 */
TYPED_TEST(SimdVec2RejectionTests, StaticWrapper_SafeReject_ParallelVectorsReturnsZeroVector)
{
    const flcn::simd::Vec2 actualRejection = flcn::safeReject(this->_vec, this->_parallelVec);

    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting a vector from an orthogonal vector using
 *       static variant of @ref flcn::simd::Vec2::safeReject returns the original vector.
 */
TEST(SimdVec2RejectionTests, StaticWrapper_SafeReject_OrthogonalRejectionReturnsOriginalVector)
{
    const flcn::simd::Vec2 a(0.0f, 2.0f);
    const flcn::simd::Vec2 b(1.0f, 0.0f);

    const flcn::simd::Vec2 actualRejection = flcn::safeReject(a, b);

    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @test Verify that safely rejecting from a non-orthogonal vector using static variant of
 *       @ref flcn::simd::Vec2::safeReject returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(SimdVec2RejectionTests, StaticWrapper_SafeReject_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const flcn::simd::Vec2 actualRejection = flcn::safeReject(this->_vec, this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}



/**
 * @test Verify that safely rejecting from a zero length vector using static variant of @ref
 * flcn::simd::Vec2::safeReject returns the same vector.
 */
TYPED_TEST(SimdVec2RejectionTests, StaticWrapper_SafeReject_FromZeroVectorReturnsSameVector)
{
    const flcn::simd::Vec2 zeroVec = flcn::simd::Vec2<TypeParam>::zero();

    const flcn::simd::Vec2 actualRejection = flcn::safeReject(this->_vec, zeroVec);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
}


/**
 * @test Verify that the rejection of NaN vector using static variant of @ref flcn::simd::Vec2::safeReject
 *       returns zero vector.
 */
TEST_P(SimdVec2RejectionNaNTests, StaticWrapper_SafeReject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::simd::Vec2<float>::one();

    EXPECT_VEC_ZERO(flcn::safeReject(nanVec, ontoVec));
}


/**
 * @test Verify that rejecting onto a NaN vector using static variant of @ref flcn::simd::Vec2::safeReject
 *       returns zero vector.
 */
TEST_P(SimdVec2RejectionNaNTests, StaticWrapper_SafeReject_OntoNaNVectorReturnsZeroVector)
{
    const auto& oneVec     = flcn::simd::Vec2<float>::one();
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(flcn::safeReject(oneVec, ontoNaNVec));
}


/**
 * @test Verify that safely rejecting from a parallel vector using static variant of @ref flcn::simd::Vec2::tryReject
 *       returns a zero vector and sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(SimdVec2RejectionTests, StaticWrapper_TryReject_ParallelVectorsReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    flcn::OperationStatus flag;

    const flcn::simd::Vec2 actualRejection = flcn::tryReject(this->_vec, this->_parallelVec, flag);

    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting a vector from an orthogonal vector using
 *       static variant of @ref flcn::simd::Vec2::tryReject returns the original vector
 *       and sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(SimdVec2RejectionTests, StaticWrapper_TryReject_OrthogonalRejectionReturnsOriginalVectorAndSetsCorrectStatusFlag)
{
    const flcn::simd::Vec2 a(0.0f, 2.0f);
    const flcn::simd::Vec2 b(1.0f, 0.0f);
    flcn::OperationStatus flag;

    const flcn::simd::Vec2 actualRejection = flcn::tryReject(a, b, flag);

    EXPECT_VEC_EQ(a, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from a non-orthogonal vector using static variant of
 *       @ref flcn::simd::Vec2::tryReject returns a non-zero vector with perpendicular component
 *       and sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(SimdVec2RejectionTests,
           StaticWrapper_TryReject_NonOrthogonalRejectionReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    flcn::OperationStatus flag;

    const flcn::simd::Vec2 actualRejection = flcn::tryReject(this->_vec, this->_fromVec, flag);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using static variant of
 *       @ref flcn::simd::Vec2::tryRejectNorm returns a non-zero vector and with perpendicular component sets flag to
 *       @ref flcn::OperationStatus::SUCCESS.
 */
TEST(SimdVec2RejectionTests,
     StaticWrapper_TryRejectNorm_FromNormalizedVectorReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec2 a(1.0f, 2.0f);
    const flcn::simd::Vec2 b(1.0f, 0.0f);
    const flcn::simd::Vec2 expectedRejection(0.0f, 2.0f);
    flcn::OperationStatus flag;


    // When rejected from another
    const flcn::simd::Vec2 actualRejection = flcn::tryRejectNorm(a, b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}

/**
 * @test Verify that safely rejecting NaN vector from an orthogonal unit vector using static variant of
 *       @ref flcn::simd::Vec2::tryRejectNorm returns a zero vector and sets flag to @ref
 * flcn::OperationStatus::NANOPERAND.
 */
TEST(SimdVec2RejectionTests, StaticWrapper_TryRejectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec2 a(1.0f, flcn::constants::NaN);
    const flcn::simd::Vec2 b(1.0f, 0.0f);
    flcn::OperationStatus flag;


    // When rejected from another
    const flcn::simd::Vec2 actualRejection = flcn::tryRejectNorm(a, b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that safely rejecting from an NaN vector using static variant of @ref flcn::simd::Vec2::tryRejectNorm
 *       returns a zero vector and sets flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(SimdVec2RejectionTests, StaticWrapper_TryRejectNorm_FromNaNVectorReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec2 a(1.0f, 2.0f);
    const flcn::simd::Vec2 b(1.0f, flcn::constants::NaN);
    flcn::OperationStatus flag;


    // When rejected from another
    const flcn::simd::Vec2 actualRejection = flcn::tryRejectNorm(a, b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that safely rejecting from a zero length vector using static variant of @ref flcn::simd::Vec2::tryReject
 *       returns the same vector and sets flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(SimdVec2RejectionTests, StaticWrapper_TryReject_FromZeroVectorReturnsSameVectorAndSetsCorrectStatusFlag)
{
    const flcn::simd::Vec2 zeroVec = flcn::simd::Vec2<TypeParam>::zero();
    flcn::OperationStatus flag;

    const flcn::simd::Vec2 actualRejection = flcn::tryReject(this->_vec, zeroVec, flag);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}

/**
 * @test Verify that the rejection of NaN vector using static variant of @ref flcn::simd::Vec2::tryReject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(SimdVec2RejectionNaNTests, StaticWrapper_TryReject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::simd::Vec2<float>::one();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(flcn::tryReject(nanVec, ontoVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that the rejection onto NaN vector using static variant of @ref flcn::simd::Vec2::tryReject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(SimdVec2RejectionNaNTests, StaticWrapper_TryReject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::simd::Vec2<float>::one();
    const auto& ontoNaNVec = GetParam();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(flcn::tryReject(oneVec, ontoNaNVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/** @} */
