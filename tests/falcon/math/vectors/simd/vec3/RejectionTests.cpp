/**
 * @file RejectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref flcn::simd::Vec3 rejection logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */




/**
 * @addtogroup T_Falcon_Vec3_Rej
 * @{
 */

#include "ProjectionTestFixture.h"
#include "Vec3TestSetup.h"


/**************************************
 *          REJECTION TESTS           *
 **************************************/

/** @test Verify that rejecting from a parallel vector using @ref flcn::simd::Vec3::reject returns a zero vector. */
TYPED_TEST(SimdVec3RejectionTests, ParallelVectorsReturnsZeroVector)
{
    const flcn::simd::Vec3 actualRejection = this->_vec.reject(this->_parallelVec);
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that rejecting from a vector parallel to x-axis using @ref flcn::simd::Vec3::reject
 *       returns a vector with a zero x-component.
 */
TEST(SimdVec3Rejection, RejectionFromXAxisReturnsVectorWithZeroXComponent)
{
    // Given an arbitrary vector
    const flcn::simd::Vec3 a(10.0f, 20.0f, 30.0f);
    const flcn::simd::Vec3 xAxis(1.0f, 0.0f, 0.0f);
    const flcn::simd::Vec3 expectedRejection(0.0f, 20.0f, 30.0f);

    // When rejected from x-axis
    const flcn::simd::Vec3 actualRejection = a.reject(xAxis);

    // Then, the resultant vector has zero x-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from a vector parallel to y-axis using @ref flcn::simd::Vec3::reject
 *       returns a vector with a zero y-component.
 */
TEST(SimdVec3Rejection, RejectionFromYAxisReturnsVectorWithZeroYComponent)
{
    // Given an arbitrary vector
    const flcn::simd::Vec3 a(10.0f, 20.0f, 30.0f);
    const flcn::simd::Vec3 yAxis(0.0f, 1.0f, 0.0f);
    const flcn::simd::Vec3 expectedRejection(10.0f, 0.0f, 30.0f);

    // When rejected from y-axis
    const flcn::simd::Vec3 actualRejection = a.reject(yAxis);

    // Then, the resultant vector has zero y-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from a vector parallel to z-axis using @ref flcn::simd::Vec3::reject
 *       returns a vector with a zero z-component.
 */
TEST(SimdVec3Rejection, RejectionFromZAxisReturnsVectorWithZeroZComponent)
{
    // Given an arbitrary vector
    const flcn::simd::Vec3 a(10.0f, 20.0f, 30.0f);
    const flcn::simd::Vec3 zAxis(0.0f, 0.0f, 1.0f);
    const flcn::simd::Vec3 expectedRejection(10.0f, 20.0f, 0.0f);

    // When rejected from z-axis
    const flcn::simd::Vec3 actualRejection = a.reject(zAxis);

    // Then, the resultant vector has zero z-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/** @test Verify that rejecting an orthogonal using @ref flcn::simd::Vec3::reject returns the original vector. */
TEST(SimdVec3Rejection, OrthogonalRejectionReturnsOriginalVector)
{
    // Given an arbitrary vector
    const flcn::simd::Vec3 a(1.0f, 2.0f, 0.0f);
    const flcn::simd::Vec3 b(0.0f, 0.0f, 1.0f);

    // When rejected on to an orthogonal vector
    const flcn::simd::Vec3 actualRejection = a.reject(b);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @test Verify that rejecting from a non-orthogonal vector using @ref flcn::simd::Vec3::reject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(SimdVec3RejectionTests, NonOrthogonalRejectionReturnsNonZeroVector)
{
    const flcn::simd::Vec3 actualRejection = this->_vec.reject(this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from an orthogonal unit vector using @ref flcn::simd::Vec3::rejectNorm
 *       returns a non-zero vector with perpendicular component.
 */
TEST(SimdVec3Rejection, RejectionFromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::simd::Vec3 b(1.0f, 0.0f, 0.0f);
    const flcn::simd::Vec3 expectedRejection(0.0f, 2.0f, 3.0f);

    // When rejected from another
    const flcn::simd::Vec3 actualRejection = a.rejectNorm(b);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from an orthogonal vector pointing in the opposite direction
 *       using @ref flcn::simd::Vec3::reject returns a non-zero vector with perpendicular components.
 */
TEST(SimdVec3Rejection, RejectionFromVectorInOppositeDirectionReturnsVectorWithPerpendicularComponents)
{
    // Given an arbitrary vector
    const flcn::simd::Vec3 a(4.0f, 4.0f, 4.0f);
    const flcn::simd::Vec3 negativeZAxis(0.0f, 0.0f, -1.0f);
    const flcn::simd::Vec3 expectedRejection(4.0f, 4.0f, 0.0f);

    // When rejected from a vector in opposite direction
    const flcn::simd::Vec3 actualRejection = a.reject(negativeZAxis);

    // Then, the resultant vector has components perpendicular to the `from` vector in the same direction.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/** @test Verify that rejection using @ref flcn::simd::Vec3::reject always return floating-point vector. */
TYPED_TEST(SimdVec3RejectionTests, Reject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::simd::Vec3 rejection = this->_vec.reject(this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::ValueType>);
}



/**************************************
 *       SAFE REJECTION TESTS         *
 **************************************/

/**
 * @test Verify that safely rejecting from a parallel vector using @ref flcn::simd::Vec3::safeReject
 *       returns a zero vector.
 */
TYPED_TEST(SimdVec3RejectionTests, SafeReject_ParallelVectorsReturnsZeroVector)
{
    const flcn::simd::Vec3 actualRejection = this->_vec.safeReject(this->_parallelVec);

    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting from orthogonal using @ref flcn::simd::Vec3::safeReject
 *       returns the original vector.
 */
TEST(SimdVec3Rejection, SafeReject_OrthogonalRejectionReturnsOriginalVector)
{
    // Given an arbitrary vector
    const flcn::simd::Vec3 a(1.0f, 2.0f, 0.0f);
    const flcn::simd::Vec3 b(0.0f, 0.0f, 1.0f);

    // When rejected from an orthogonal vector
    const flcn::simd::Vec3 actualRejection = a.safeReject(b);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @test Verify that safely rejecting from a non-orthogonal vector using @ref flcn::simd::Vec3::safeReject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(SimdVec3RejectionTests, SafeReject_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const flcn::simd::Vec3 actualRejection = this->_vec.safeReject(this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using @ref flcn::simd::Vec3::safeRejectNorm
 *       returns a non-zero vector with perpendicular component.
 */
TEST(SimdVec3Rejection, SafeReject_FromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::simd::Vec3 b(1.0f, 0.0f, 0.0f);
    const flcn::simd::Vec3 expectedRejection(0.0f, 2.0f, 3.0f);

    // When rejected from another
    const flcn::simd::Vec3 actualRejection = a.safeRejectNorm(b);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting a NaN vector from a non-orthogonal unit vector using
 *       @ref flcn::simd::Vec3::safeRejectNorm returns a zero vector.
 */
TEST(SimdVec3Rejection, SafeRejectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector
    const flcn::simd::Vec3 a(1.0f, flcn::constants::NaN, 3.0f);
    const flcn::simd::Vec3 b(1.0f, 0.0f, 0.0f);

    // When the vector is rejected onto the normalized vector
    const flcn::simd::Vec3 actualRejection = a.safeRejectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting from a NaN vector using @ref flcn::simd::Vec3::safeRejectNorm returns a zero
 * vector.
 */
TEST(SimdVec3Rejection, SafeRejectNorm_FromNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector
    const flcn::simd::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::simd::Vec3 b(1.0f, flcn::constants::NaN, 0.0f);

    // When the vector is rejected from a NaN vector
    const flcn::simd::Vec3 actualRejection = a.safeRejectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting from a zero vector using @ref flcn::simd::Vec3::safeReject
 *       returns the same vector.
 */
TYPED_TEST(SimdVec3RejectionTests, SafeReject_FromZeroVectorReturnsSameVector)
{
    const flcn::simd::Vec3 zeroVec         = flcn::simd::Vec3<TypeParam>::zero();
    const flcn::simd::Vec3 actualRejection = this->_vec.safeReject(zeroVec);
    EXPECT_VEC_EQ(this->_vec, actualRejection);
}


/** @test Verify that rejection using @ref flcn::simd::Vec3::safeReject always return floating-point vector. */
TYPED_TEST(SimdVec3RejectionTests, SafeReject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::simd::Vec3 rejection = this->_vec.safeReject(this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::ValueType>);
}


/**
 * @test Verify that the rejection of NaN vector using @ref flcn::simd::Vec3::safeReject
 *       returns zero vector.
 */
TEST_P(SimdVec3RejectionNaNTests, SafeReject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::simd::Vec3<float>::one();

    EXPECT_VEC_ZERO(nanVec.safeReject(ontoVec));
}


/**
 * @test Verify that rejecting onto NaN vector using @ref flcn::simd::Vec3::safeReject
 *       returns zero vector.
 */
TEST_P(SimdVec3RejectionNaNTests, SafeReject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::simd::Vec3<float>::one();
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(oneVec.safeReject(ontoNaNVec));
}



/**************************************
 *        TRY REJECTION TESTS         *
 **************************************/

/**
 * @test Verify that safely rejecting from a parallel vector using @ref flcn::simd::Vec3::tryReject
 *       returns a zero vector  and sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(SimdVec3RejectionTests, TryReject_ParallelVectorsReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    flcn::OperationStatus flag;
    const flcn::simd::Vec3 actualRejection = this->_vec.tryReject(this->_parallelVec, flag);

    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from orthogonal using @ref flcn::simd::Vec3::tryReject
 *       returns the original vector and sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(SimdVec3Rejection, TryReject_OrthogonalRejectionReturnsOriginalVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector
    const flcn::simd::Vec3 a(1.0f, 2.0f, 0.0f);
    const flcn::simd::Vec3 b(0.0f, 0.0f, 1.0f);
    flcn::OperationStatus flag;

    // When rejected from an orthogonal vector
    const flcn::simd::Vec3 actualRejection = a.tryReject(b, flag);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from a non-orthogonal vector using @ref flcn::simd::Vec3::tryReject
 *       returns a non-zero vector with perpendicular component sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(SimdVec3RejectionTests, TryReject_NonOrthogonalRejectionReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    flcn::OperationStatus flag;
    const flcn::simd::Vec3 actualRejection = this->_vec.tryReject(this->_fromVec, flag);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using @ref flcn::simd::Vec3::tryRejectNorm
 *       returns a non-zero vector and with perpendicular component sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(SimdVec3Rejection, TryRejectNorm_FromNormalizedVectorReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::simd::Vec3 b(1.0f, 0.0f, 0.0f);
    const flcn::simd::Vec3 expectedRejection(0.0f, 2.0f, 3.0f);
    flcn::OperationStatus flag;


    // When rejected from another
    const flcn::simd::Vec3 actualRejection = a.tryRejectNorm(b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting NaN vector from an orthogonal unit vector using @ref
 * flcn::simd::Vec3::tryRejectNorm returns a zero vector and sets flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(SimdVec3Rejection, TryRejectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec3 a(1.0f, flcn::constants::NaN, 3.0f);
    const flcn::simd::Vec3 b(1.0f, 0.0f, 0.0f);
    flcn::OperationStatus flag;


    // When rejected from another
    const flcn::simd::Vec3 actualRejection = a.tryRejectNorm(b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that safely rejecting from an NaN vector using @ref flcn::simd::Vec3::tryRejectNorm
 *       returns a zero vector and sets flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(SimdVec3Rejection, TryRejectNorm_FromNaNVectorReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::simd::Vec3 b(1.0f, flcn::constants::NaN, 0.0f);
    flcn::OperationStatus flag;


    // When rejected from another
    const flcn::simd::Vec3 actualRejection = a.tryRejectNorm(b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that safely rejecting from a zero vector using @ref flcn::simd::Vec3::tryReject
 *       returns the same vector and sets flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(SimdVec3RejectionTests, TryReject_FromZeroVectorReturnsSameVectorAndSetsCorrectStatusFlag)
{
    const flcn::simd::Vec3 zeroVec = flcn::simd::Vec3<TypeParam>::zero();
    flcn::OperationStatus flag;

    const flcn::simd::Vec3 actualRejection = this->_vec.tryReject(zeroVec, flag);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/** @test Verify that rejection using @ref flcn::simd::Vec3::tryReject always return floating-point vector. */
TYPED_TEST(SimdVec3RejectionTests, TryRejectAlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] flcn::OperationStatus status;
    [[maybe_unused]] const flcn::simd::Vec3 rejection = this->_vec.tryReject(this->_fromVec, status);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::ValueType>);
}


/**
 * @test Verify that the rejection of NaN vector using @ref flcn::simd::Vec3::tryReject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(SimdVec3RejectionNaNTests, TryReject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::simd::Vec3<float>::one();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(nanVec.tryReject(ontoVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that the rejection onto NaN vector using @ref flcn::simd::Vec3::tryReject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(SimdVec3RejectionNaNTests, TryReject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::simd::Vec3<float>::one();
    const auto& ontoNaNVec = GetParam();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(oneVec.tryReject(ontoNaNVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/** @} */
