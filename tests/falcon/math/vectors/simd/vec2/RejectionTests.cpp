/**
 * @file RejectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 25, 2026
 *
 * @brief Verify @ref flcn::simd::Vec2 rejection logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



/**
 * @addtogroup T_Falcon_Vec2_Rej
 * @{
 */

#include "ProjectionTestFixture.h"
#include "Vec2TestSetup.h"


/**************************************
 *          REJECTION TESTS           *
 **************************************/

/** @test Verify that rejecting from a parallel vector using @ref flcn::simd::Vec2::reject returns a zero vector. */
TYPED_TEST(SimdVec2RejectionTests, ParallelVectorsReturnsZeroVector)
{
    const flcn::simd::Vec2 actualRejection = this->_vec.reject(this->_parallelVec);
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that rejecting from a vector parallel to x-axis using @ref flcn::simd::Vec2::reject
 *       returns a vector with a zero x-component.
 */
TEST(SimdVec2RejectionTests, RejectionFromXAxisReturnsVectorWithZeroXComponent)
{
    // Given an arbitrary vector
    const flcn::simd::Vec2 a(10.0f, 20.0f);
    const flcn::simd::Vec2 xAxis(1.0f, 0.0f);
    const flcn::simd::Vec2 expectedRejection(0.0f, 20.0f);

    // When rejected from x-axis
    const flcn::simd::Vec2 actualRejection = a.reject(xAxis);

    // Then, the resultant vector has zero x-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from a vector parallel to y-axis using @ref flcn::simd::Vec2::reject
 *       returns a vector with a zero y-component.
 */
TEST(SimdVec2RejectionTests, RejectionFromYAxisReturnsVectorWithZeroYComponent)
{
    // Given an arbitrary vector
    const flcn::simd::Vec2 a(10.0f, 20.0f);
    const flcn::simd::Vec2 yAxis(0.0f, 1.0f);
    const flcn::simd::Vec2 expectedRejection(10.0f, 0.0f);

    // When rejected from y-axis
    const flcn::simd::Vec2 actualRejection = a.reject(yAxis);

    // Then, the resultant vector has zero y-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/** @test Verify that rejecting an orthogonal using @ref flcn::simd::Vec2::reject returns the original vector. */
TEST(SimdVec2RejectionTests, OrthogonalRejectionReturnsOriginalVector)
{
    // Given an arbitrary vector
    const flcn::simd::Vec2 a(0.0f, 2.0f);
    const flcn::simd::Vec2 b(1.0f, 0.0f);

    // When rejected on to an orthogonal vector
    const flcn::simd::Vec2 actualRejection = a.reject(b);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @test Verify that rejecting from a non-orthogonal vector using @ref flcn::simd::Vec2::reject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(SimdVec2RejectionTests, NonOrthogonalRejectionReturnsNonZeroVector)
{
    const flcn::simd::Vec2 actualRejection = this->_vec.reject(this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from an orthogonal unit vector using @ref flcn::simd::Vec2::rejectNorm
 *       returns a non-zero vector with perpendicular component.
 */
TEST(SimdVec2RejectionTests, RejectionFromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec2 a(1.0f, 2.0f);
    const flcn::simd::Vec2 b(1.0f, 0.0f);
    const flcn::simd::Vec2 expectedRejection(0.0f, 2.0f);

    // When rejected from another
    const flcn::simd::Vec2 actualRejection = a.rejectNorm(b);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from an orthogonal vector pointing in the opposite direction
 *       using @ref flcn::simd::Vec2::reject returns a non-zero vector with perpendicular components.
 */
TEST(SimdVec2RejectionTests, RejectionFromVectorInOppositeDirectionReturnsVectorWithPerpendicularComponents)
{
    // Given an arbitrary vector
    const flcn::simd::Vec2 a(4.0f, 4.0f);
    const flcn::simd::Vec2 negativeYAxis(0.0f, -1.0f);
    const flcn::simd::Vec2 expectedRejection(4.0f, 0.0f);

    // When rejected from a vector in opposite direction
    const flcn::simd::Vec2 actualRejection = a.reject(negativeYAxis);

    // Then, the resultant vector has components perpendicular to the `from` vector in the same direction.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}



/**************************************
 *       SAFE REJECTION TESTS         *
 **************************************/

/**
 * @test Verify that safely rejecting from a parallel vector using @ref flcn::simd::Vec2::safeReject
 *       returns a zero vector.
 */
TYPED_TEST(SimdVec2RejectionTests, SafeReject_ParallelVectorsReturnsZeroVector)
{
    const flcn::simd::Vec2 actualRejection = this->_vec.safeReject(this->_parallelVec);

    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting from orthogonal using @ref flcn::simd::Vec2::safeReject
 *       returns the original vector.
 */
TEST(SimdVec2RejectionTests, SafeReject_OrthogonalRejectionReturnsOriginalVector)
{
    // Given an arbitrary vector
    const flcn::simd::Vec2 a(0.0f, 2.0f);
    const flcn::simd::Vec2 b(1.0f, 0.0f);

    // When rejected from an orthogonal vector
    const flcn::simd::Vec2 actualRejection = a.safeReject(b);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @test Verify that safely rejecting from a non-orthogonal vector using @ref flcn::simd::Vec2::safeReject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(SimdVec2RejectionTests, SafeReject_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const flcn::simd::Vec2 actualRejection = this->_vec.safeReject(this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using @ref flcn::simd::Vec2::safeRejectNorm
 *       returns a non-zero vector with perpendicular component.
 */
TEST(SimdVec2RejectionTests, SafeRejectNorm_FromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec2 a(1.0f, 2.0f);
    const flcn::simd::Vec2 b(1.0f, 0.0f);
    const flcn::simd::Vec2 expectedRejection(0.0f, 2.0f);

    // When rejected from another
    const flcn::simd::Vec2 actualRejection = a.safeRejectNorm(b);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

/**
 * @test Verify that safely rejecting a NaN vector from a non-orthogonal unit vector using
 *       @ref flcn::simd::Vec2::safeRejectNorm returns a zero vector.
 */
TEST(SimdVec2RejectionTests, SafeRejectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector
    const flcn::simd::Vec2 a(1.0f, flcn::constants::NaN);
    const flcn::simd::Vec2 b(1.0f, 0.0f);

    // When the vector is rejected onto the normalized vector
    const flcn::simd::Vec2 actualRejection = a.safeRejectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting from a NaN vector using @ref flcn::simd::Vec2::safeRejectNorm returns a zero
 * vector.
 */
TEST(SimdVec2RejectionTests, SafeRejectNorm_FromNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector
    const flcn::simd::Vec2 a(1.0f, 2.0f);
    const flcn::simd::Vec2 b(1.0f, flcn::constants::NaN);

    // When the vector is rejected from a NaN vector
    const flcn::simd::Vec2 actualRejection = a.safeRejectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting from a zero vector using @ref flcn::simd::Vec2::safeReject
 *       returns the same vector.
 */
TYPED_TEST(SimdVec2RejectionTests, SafeReject_FromZeroVectorReturnsSameVector)
{
    const flcn::simd::Vec2 zeroVec = flcn::simd::Vec2<TypeParam>::zero();

    const flcn::simd::Vec2 actualRejection = this->_vec.safeReject(zeroVec);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
}


/**
 * @test Verify that the rejection of NaN vector using @ref flcn::simd::Vec2::safeReject
 *       returns zero vector.
 */
TEST_P(SimdVec2RejectionNaNTests, SafeReject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::simd::Vec2<float>::one();

    EXPECT_VEC_ZERO(nanVec.safeReject(ontoVec));
}


/**
 * @test Verify that rejecting onto NaN vector using @ref flcn::simd::Vec2::safeReject
 *       returns zero vector.
 */
TEST_P(SimdVec2RejectionNaNTests, SafeReject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::simd::Vec2<float>::one();
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(oneVec.safeReject(ontoNaNVec));
}



/**************************************
 *        TRY REJECTION TESTS         *
 **************************************/

/**
 * @test Verify that safely rejecting from a parallel vector using @ref flcn::simd::Vec2::tryReject
 *       returns a zero vector  and sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(SimdVec2RejectionTests, TryReject_ParallelVectorsReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    flcn::OperationStatus flag;
    const flcn::simd::Vec2 actualRejection = this->_vec.tryReject(this->_parallelVec, flag);

    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from orthogonal using @ref flcn::simd::Vec2::tryReject
 *       returns the original vector and sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(SimdVec2RejectionTests, TryReject_OrthogonalRejectionReturnsOriginalVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector
    const flcn::simd::Vec2 a(0.0f, 2.0f);
    const flcn::simd::Vec2 b(1.0f, 0.0f);
    flcn::OperationStatus flag;

    // When rejected from an orthogonal vector
    const flcn::simd::Vec2 actualRejection = a.tryReject(b, flag);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from a non-orthogonal vector using @ref flcn::simd::Vec2::tryReject
 *       returns a non-zero vector with perpendicular and component sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(SimdVec2RejectionTests, TryReject_NonOrthogonalRejectionReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    flcn::OperationStatus flag;
    const flcn::simd::Vec2 actualRejection = this->_vec.tryReject(this->_fromVec, flag);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using @ref flcn::simd::Vec2::tryRejectNorm
 *       returns a non-zero vector and with perpendicular component sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(SimdVec2RejectionTests, TryRejectNorm_FromNormalizedVectorReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec2 a(1.0f, 2.0f);
    const flcn::simd::Vec2 b(1.0f, 0.0f);
    const flcn::simd::Vec2 expectedRejection(0.0f, 2.0f);
    flcn::OperationStatus flag;


    // When rejected from another
    const flcn::simd::Vec2 actualRejection = a.tryRejectNorm(b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting NaN vector from an orthogonal unit vector using @ref
 * flcn::simd::Vec2::tryRejectNorm returns a zero vector and sets flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(SimdVec2RejectionTests, TryRejectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec2 a(1.0f, flcn::constants::NaN);
    const flcn::simd::Vec2 b(1.0f, 0.0f);
    flcn::OperationStatus flag;


    // When rejected from another
    const flcn::simd::Vec2 actualRejection = a.tryRejectNorm(b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that safely rejecting from an NaN vector using @ref flcn::simd::Vec2::tryRejectNorm
 *       returns a zero vector and sets flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(SimdVec2RejectionTests, TryRejectNorm_FromNaNVectorReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec2 a(1.0f, 2.0f);
    const flcn::simd::Vec2 b(1.0f, flcn::constants::NaN);
    flcn::OperationStatus flag;


    // When rejected from another
    const flcn::simd::Vec2 actualRejection = a.tryRejectNorm(b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that safely rejecting from a zero vector using @ref flcn::simd::Vec2::tryReject
 *       returns the same vector and sets flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(SimdVec2RejectionTests, TryReject_FromZeroVectorReturnsSameVectorAndSetsCorrectStatusFlag)
{
    const flcn::simd::Vec2 zeroVec = flcn::simd::Vec2<TypeParam>::zero();
    flcn::OperationStatus flag;

    const flcn::simd::Vec2 actualRejection = this->_vec.tryReject(zeroVec, flag);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that the rejection of NaN vector using @ref flcn::simd::Vec2::tryReject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(SimdVec2RejectionNaNTests, TryReject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::simd::Vec2<float>::one();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(nanVec.tryReject(ontoVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that the rejection onto NaN vector using @ref flcn::simd::Vec2::tryReject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(SimdVec2RejectionNaNTests, TryReject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::simd::Vec2<float>::one();
    const auto& ontoNaNVec = GetParam();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(oneVec.tryReject(ontoNaNVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/** @} */
