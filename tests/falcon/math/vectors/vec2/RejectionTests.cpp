/**
 * @file RejectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 25, 2026
 *
 * @brief Verify @ref flcn::Vec2 rejection logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"



/**
 * @addtogroup T_FALCON_Vec2_Rej
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Vec2 rejection.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class Vec2RejectionTests: public testing::Test
    {
    protected:
        flcn::Vec2<T> _vec;
        flcn::Vec2<T> _parallelVec;
        flcn::Vec2<T> _fromVec;
        flcn::Vec2<T> _expectedRejection;

        void SetUp() override
        {
            _vec               = { T(4), T(0) };
            _parallelVec       = { T(6), T(0) };
            _fromVec           = { T(0), T(2) };
            _expectedRejection = { T(4), T(0) };
        }
    };
    TYPED_TEST_SUITE(Vec2RejectionTests, SupportedFloatingPointTypes);



    /**
     * @brief Test fixture for @ref flcn::Vec2 rejection with NaN vectors.
     */
    class Vec2RejectionNaNTests: public testing::TestWithParam<flcn::Vec2<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Vec2RejectionNaNVectors, Vec2RejectionNaNTests,
                             ::testing::Values(flcn::Vec2<float>(flcn::constants::NaN, 1.0f),
                                               flcn::Vec2<float>(1.0f, flcn::constants::NaN),
                                               flcn::Vec2<float>(flcn::constants::NaN, flcn::constants::NaN)));
} // namespace



/**************************************
 *          REJECTION TESTS           *
 **************************************/

/** @test Verify that rejecting from a parallel vector using @ref flcn::Vec2::reject returns a zero vector. */
TYPED_TEST(Vec2RejectionTests, ParallelVectorsReturnsZeroVector)
{
    const flcn::Vec2 actualRejection = this->_vec.reject(this->_parallelVec);
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that rejecting from a vector parallel to x-axis using @ref flcn::Vec2::reject
 *       returns a vector with a zero x-component.
 */
TEST(Vec2RejectionTests, RejectionFromXAxisReturnsVectorWithZeroXComponent)
{
    // Given an arbitrary vector
    const flcn::Vec2 a(10.0f, 20.0f);
    const flcn::Vec2 xAxis(1.0f, 0.0f);
    const flcn::Vec2 expectedRejection(0.0f, 20.0f);

    // When rejected from x-axis
    const flcn::Vec2 actualRejection = a.reject(xAxis);

    // Then, the resultant vector has zero x-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from a vector parallel to y-axis using @ref flcn::Vec2::reject
 *       returns a vector with a zero y-component.
 */
TEST(Vec2RejectionTests, RejectionFromYAxisReturnsVectorWithZeroYComponent)
{
    // Given an arbitrary vector
    const flcn::Vec2 a(10.0f, 20.0f);
    const flcn::Vec2 yAxis(0.0f, 1.0f);
    const flcn::Vec2 expectedRejection(10.0f, 0.0f);

    // When rejected from y-axis
    const flcn::Vec2 actualRejection = a.reject(yAxis);

    // Then, the resultant vector has zero y-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/** @test Verify that rejecting an orthogonal using @ref flcn::Vec2::reject returns the original vector. */
TEST(Vec2RejectionTests, OrthogonalRejectionReturnsOriginalVector)
{
    // Given an arbitrary vector
    const flcn::Vec2 a(0.0f, 2.0f);
    const flcn::Vec2 b(1.0f, 0.0f);

    // When rejected on to an orthogonal vector
    const flcn::Vec2 actualRejection = a.reject(b);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @test Verify that rejecting from a non-orthogonal vector using @ref flcn::Vec2::reject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vec2RejectionTests, NonOrthogonalRejectionReturnsNonZeroVector)
{
    const flcn::Vec2 actualRejection = this->_vec.reject(this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from a non-orthogonal vector using static variant of @ref flcn::Vec2::reject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vec2RejectionTests, StaticWrapper_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const flcn::Vec2 actualRejection = flcn::Vec2<TypeParam>::reject(this->_vec, this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from an orthogonal unit vector using @ref flcn::Vec2::rejectNorm
 *       returns a non-zero vector with perpendicular component.
 */
TEST(Vec2RejectionTests, RejectionFromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec2 a(1.0f, 2.0f);
    const flcn::Vec2 b(1.0f, 0.0f);
    const flcn::Vec2 expectedRejection(0.0f, 2.0f);

    // When rejected from another
    const flcn::Vec2 actualRejection = a.rejectNorm(b);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from an orthogonal vector pointing in the opposite direction
 *       using @ref flcn::Vec2::reject returns a non-zero vector with perpendicular components.
 */
TEST(Vec2RejectionTests, RejectionFromVectorInOppositeDirectionReturnsVectorWithPerpendicularComponents)
{
    // Given an arbitrary vector
    const flcn::Vec2 a(4.0f, 4.0f);
    const flcn::Vec2 negativeYAxis(0.0f, -1.0f);
    const flcn::Vec2 expectedRejection(4.0f, 0.0f);

    // When rejected from a vector in opposite direction
    const flcn::Vec2 actualRejection = a.reject(negativeYAxis);

    // Then, the resultant vector has components perpendicular to the `from` vector in the same direction.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}



/**
 * @test Verify that rejecting from an orthogonal unit vector using static variant of @ref flcn::Vec2::rejectNorm
 *       returns a non-zero vector with perpendicular component.
 */
TEST(Vec2RejectionTests, StaticWrapper_RejectionFromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec2 a(1.0f, 2.0f);
    const flcn::Vec2 b(1.0f, 0.0f);
    const flcn::Vec2 expectedRejection(0.0f, 2.0f);

    // When rejected from another
    const flcn::Vec2 actualRejection = flcn::Vec2<float>::rejectNorm(a, b);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}



/**************************************
 *       SAFE REJECTION TESTS         *
 **************************************/

/**
 * @test Verify that safely rejecting from a parallel vector using @ref flcn::Vec2::safeReject
 *       returns a zero vector.
 */
TYPED_TEST(Vec2RejectionTests, SafeReject_ParallelVectorsReturnsZeroVector)
{
    const flcn::Vec2 actualRejection = this->_vec.safeReject(this->_parallelVec);

    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting from orthogonal using @ref flcn::Vec2::safeReject
 *       returns the original vector.
 */
TEST(Vec2RejectionTests, SafeReject_OrthogonalRejectionReturnsOriginalVector)
{
    // Given an arbitrary vector
    const flcn::Vec2 a(0.0f, 2.0f);
    const flcn::Vec2 b(1.0f, 0.0f);

    // When rejected from an orthogonal vector
    const flcn::Vec2 actualRejection = a.safeReject(b);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @test Verify that safely rejecting from a non-orthogonal vector using @ref flcn::Vec2::safeReject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vec2RejectionTests, SafeReject_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const flcn::Vec2 actualRejection = this->_vec.safeReject(this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using @ref flcn::Vec2::safeRejectNorm
 *       returns a non-zero vector with perpendicular component.
 */
TEST(Vec2RejectionTests, SafeRejectNorm_FromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec2 a(1.0f, 2.0f);
    const flcn::Vec2 b(1.0f, 0.0f);
    const flcn::Vec2 expectedRejection(0.0f, 2.0f);

    // When rejected from another
    const flcn::Vec2 actualRejection = a.safeRejectNorm(b);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}

/**
 * @test Verify that safely rejecting a NaN vector from a non-orthogonal unit vector using
 *       @ref flcn::Vec2::safeRejectNorm returns a zero vector.
 */
TEST(Vec2RejectionTests, SafeRejectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector
    const flcn::Vec2 a(1.0f, flcn::constants::NaN);
    const flcn::Vec2 b(1.0f, 0.0f);

    // When the vector is rejected onto the normalized vector
    const flcn::Vec2 actualRejection = a.safeRejectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting from a NaN vector using @ref flcn::Vec2::safeRejectNorm returns a zero vector.
 */
TEST(Vec2RejectionTests, SafeRejectNorm_FromNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector
    const flcn::Vec2 a(1.0f, 2.0f);
    const flcn::Vec2 b(1.0f, flcn::constants::NaN);

    // When the vector is rejected from a NaN vector
    const flcn::Vec2 actualRejection = a.safeRejectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using static variant of
 *       @ref flcn::Vec2::safeRejectNorm returns a non-zero vector with perpendicular component.
 */
TEST(Vec2RejectionTests, StaticWrapper_SafeRejectNorm_FromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec2 a(1.0f, 2.0f);
    const flcn::Vec2 b(1.0f, 0.0f);
    const flcn::Vec2 expectedRejection(0.0f, 2.0f);

    // When rejected from another
    const flcn::Vec2 actualRejection = flcn::Vec2<float>::safeRejectNorm(a, b);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting a NaN vector from a non-orthogonal unit vector using static variant of
 *       @ref flcn::Vec2::safeRejectNorm returns a zero vector.
 */
TEST(Vec2RejectionTests, StaticWrapper_SafeRejectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector
    const flcn::Vec2 a(1.0f, flcn::constants::NaN);
    const flcn::Vec2 b(1.0f, 0.0f);

    // When the vector is rejected onto the normalized vector
    const flcn::Vec2 actualRejection = flcn::Vec2<float>::safeRejectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting from a NaN vector using static variant of
 *       @ref flcn::Vec2::safeRejectNorm returns a zero vector.
 */
TEST(Vec2RejectionTests, StaticWrapper_SafeRejectNorm_FromNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector
    const flcn::Vec2 a(1.0f, 2.0f);
    const flcn::Vec2 b(1.0f, flcn::constants::NaN);

    // When the vector is rejected from a NaN vector
    const flcn::Vec2 actualRejection = flcn::Vec2<float>::safeRejectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting from a zero vector using @ref flcn::Vec2::safeReject
 *       returns the same vector.
 */
TYPED_TEST(Vec2RejectionTests, SafeReject_FromZeroVectorReturnsSameVector)
{
    const flcn::Vec2 zeroVec = flcn::Vec2<TypeParam>::zero();

    const flcn::Vec2 actualRejection = this->_vec.safeReject(zeroVec);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
}


/**
 * @test Verify that safely rejecting from a parallel vector using static variant of @ref flcn::Vec2::safeReject
 *       returns a zero vector.
 */
TYPED_TEST(Vec2RejectionTests, StaticWrapper_SafeReject_ParallelVectorsReturnsZeroVector)
{
    const flcn::Vec2 actualRejection = flcn::Vec2<TypeParam>::safeReject(this->_vec, this->_parallelVec);

    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting a vector from an orthogonal vector using
 *       static variant of @ref flcn::Vec2::safeReject returns the original vector.
 */
TEST(Vec2RejectionTests, StaticWrapper_SafeReject_OrthogonalRejectionReturnsOriginalVector)
{
    const flcn::Vec2 a(0.0f, 2.0f);
    const flcn::Vec2 b(1.0f, 0.0f);

    const flcn::Vec2 actualRejection = flcn::Vec2<float>::safeReject(a, b);

    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @test Verify that safely rejecting from a non-orthogonal vector using static variant of
 *       @ref flcn::Vec2::safeReject returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vec2RejectionTests, StaticWrapper_SafeReject_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const flcn::Vec2 actualRejection = flcn::Vec2<TypeParam>::safeReject(this->_vec, this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}



/**
 * @test Verify that safely rejecting from a zero length vector using static variant of @ref flcn::Vec2::safeReject
 *       returns the same vector.
 */
TYPED_TEST(Vec2RejectionTests, StaticWrapper_SafeReject_FromZeroVectorReturnsSameVector)
{
    const flcn::Vec2 zeroVec = flcn::Vec2<TypeParam>::zero();

    const flcn::Vec2 actualRejection = flcn::Vec2<TypeParam>::safeReject(this->_vec, zeroVec);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
}


/**
 * @test Verify that the rejection of NaN vector using @ref flcn::Vec2::safeReject
 *       returns zero vector.
 */
TEST_P(Vec2RejectionNaNTests, SafeReject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::Vec2<float>::one();

    EXPECT_VEC_ZERO(nanVec.safeReject(ontoVec));
}


/**
 * @test Verify that rejecting onto NaN vector using @ref flcn::Vec2::safeReject
 *       returns zero vector.
 */
TEST_P(Vec2RejectionNaNTests, SafeReject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::Vec2<float>::one();
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(oneVec.safeReject(ontoNaNVec));
}


/**
 * @test Verify that the rejection of NaN vector using static variant of @ref flcn::Vec2::safeReject
 *       returns zero vector.
 */
TEST_P(Vec2RejectionNaNTests, StaticWrapper_SafeReject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::Vec2<float>::one();

    EXPECT_VEC_ZERO(flcn::Vec2<float>::safeReject(nanVec, ontoVec));
}


/**
 * @test Verify that rejecting onto a NaN vector using static variant of @ref flcn::Vec2::safeReject
 *       returns zero vector.
 */
TEST_P(Vec2RejectionNaNTests, StaticWrapper_SafeReject_OntoNaNVectorReturnsZeroVector)
{
    const auto& oneVec     = flcn::Vec2<float>::one();
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(flcn::Vec2<float>::safeReject(oneVec, ontoNaNVec));
}



/**************************************
 *        TRY REJECTION TESTS         *
 **************************************/

/**
 * @test Verify that safely rejecting from a parallel vector using @ref flcn::Vec2::tryReject
 *       returns a zero vector  and sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec2RejectionTests, TryReject_ParallelVectorsReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    flcn::OperationStatus flag;
    const flcn::Vec2 actualRejection = this->_vec.tryReject(this->_parallelVec, flag);

    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from orthogonal using @ref flcn::Vec2::tryReject
 *       returns the original vector and sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec2RejectionTests, TryReject_OrthogonalRejectionReturnsOriginalVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector
    const flcn::Vec2 a(0.0f, 2.0f);
    const flcn::Vec2 b(1.0f, 0.0f);
    flcn::OperationStatus flag;

    // When rejected from an orthogonal vector
    const flcn::Vec2 actualRejection = a.tryReject(b, flag);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from a non-orthogonal vector using @ref flcn::Vec2::tryReject
 *       returns a non-zero vector with perpendicular and component sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec2RejectionTests, TryReject_NonOrthogonalRejectionReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    flcn::OperationStatus flag;
    const flcn::Vec2 actualRejection = this->_vec.tryReject(this->_fromVec, flag);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using @ref flcn::Vec2::tryRejectNorm
 *       returns a non-zero vector and with perpendicular component sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec2RejectionTests, TryRejectNorm_FromNormalizedVectorReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec2 a(1.0f, 2.0f);
    const flcn::Vec2 b(1.0f, 0.0f);
    const flcn::Vec2 expectedRejection(0.0f, 2.0f);
    flcn::OperationStatus flag;


    // When rejected from another
    const flcn::Vec2 actualRejection = a.tryRejectNorm(b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting NaN vector from an orthogonal unit vector using @ref flcn::Vec2::tryRejectNorm
 *       returns a zero vector and sets flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec2RejectionTests, TryRejectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec2 a(1.0f, flcn::constants::NaN);
    const flcn::Vec2 b(1.0f, 0.0f);
    flcn::OperationStatus flag;


    // When rejected from another
    const flcn::Vec2 actualRejection = a.tryRejectNorm(b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that safely rejecting from an NaN vector using @ref flcn::Vec2::tryRejectNorm
 *       returns a zero vector and sets flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec2RejectionTests, TryRejectNorm_FromNaNVectorReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec2 a(1.0f, 2.0f);
    const flcn::Vec2 b(1.0f, flcn::constants::NaN);
    flcn::OperationStatus flag;


    // When rejected from another
    const flcn::Vec2 actualRejection = a.tryRejectNorm(b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}



/**
 * @test Verify that safely rejecting from a zero vector using @ref flcn::Vec2::tryReject
 *       returns the same vector and sets flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec2RejectionTests, TryReject_FromZeroVectorReturnsSameVectorAndSetsCorrectStatusFlag)
{
    const flcn::Vec2 zeroVec = flcn::Vec2<TypeParam>::zero();
    flcn::OperationStatus flag;

    const flcn::Vec2 actualRejection = this->_vec.tryReject(zeroVec, flag);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that safely rejecting from a parallel vector using static variant of @ref flcn::Vec2::tryReject
 *       returns a zero vector and sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec2RejectionTests, StaticWrapper_TryReject_ParallelVectorsReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    flcn::OperationStatus flag;

    const flcn::Vec2 actualRejection = flcn::Vec2<TypeParam>::tryReject(this->_vec, this->_parallelVec, flag);

    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting a vector from an orthogonal vector using
 *       static variant of @ref flcn::Vec2::tryReject returns the original vector
 *       and sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec2RejectionTests, StaticWrapper_TryReject_OrthogonalRejectionReturnsOriginalVectorAndSetsCorrectStatusFlag)
{
    const flcn::Vec2 a(0.0f, 2.0f);
    const flcn::Vec2 b(1.0f, 0.0f);
    flcn::OperationStatus flag;

    const flcn::Vec2 actualRejection = flcn::Vec2<float>::tryReject(a, b, flag);

    EXPECT_VEC_EQ(a, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from a non-orthogonal vector using static variant of
 *       @ref flcn::Vec2::tryReject returns a non-zero vector with perpendicular component
 *       and sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec2RejectionTests,
           StaticWrapper_TryReject_NonOrthogonalRejectionReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    flcn::OperationStatus flag;

    const flcn::Vec2 actualRejection = flcn::Vec2<TypeParam>::tryReject(this->_vec, this->_fromVec, flag);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using static variant of
 *       @ref flcn::Vec2::tryRejectNorm returns a non-zero vector and with perpendicular component sets flag to
 *       @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec2RejectionTests, StaticWrapper_TryRejectNorm_FromNormalizedVectorReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec2 a(1.0f, 2.0f);
    const flcn::Vec2 b(1.0f, 0.0f);
    const flcn::Vec2 expectedRejection(0.0f, 2.0f);
    flcn::OperationStatus flag;


    // When rejected from another
    const flcn::Vec2 actualRejection = flcn::Vec2<float>::tryRejectNorm(a, b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}

/**
 * @test Verify that safely rejecting NaN vector from an orthogonal unit vector using static variant of
 *       @ref flcn::Vec2::tryRejectNorm returns a zero vector and sets flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec2RejectionTests, StaticWrapper_TryRejectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec2 a(1.0f, flcn::constants::NaN);
    const flcn::Vec2 b(1.0f, 0.0f);
    flcn::OperationStatus flag;


    // When rejected from another
    const flcn::Vec2 actualRejection = flcn::Vec2<float>::tryRejectNorm(a, b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that safely rejecting from an NaN vector using static variant of @ref flcn::Vec2::tryRejectNorm
 *       returns a zero vector and sets flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec2RejectionTests, StaticWrapper_TryRejectNorm_FromNaNVectorReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec2 a(1.0f, 2.0f);
    const flcn::Vec2 b(1.0f, flcn::constants::NaN);
    flcn::OperationStatus flag;


    // When rejected from another
    const flcn::Vec2 actualRejection = flcn::Vec2<float>::tryRejectNorm(a, b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that safely rejecting from a zero length vector using static variant of @ref flcn::Vec2::tryReject
 *       returns the same vector and sets flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec2RejectionTests, StaticWrapper_TryReject_FromZeroVectorReturnsSameVectorAndSetsCorrectStatusFlag)
{
    const flcn::Vec2 zeroVec = flcn::Vec2<TypeParam>::zero();
    flcn::OperationStatus flag;

    const flcn::Vec2 actualRejection = flcn::Vec2<TypeParam>::tryReject(this->_vec, zeroVec, flag);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that the rejection of NaN vector using @ref flcn::Vec2::tryReject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec2RejectionNaNTests, TryReject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::Vec2<float>::one();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(nanVec.tryReject(ontoVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that the rejection onto NaN vector using @ref flcn::Vec2::tryReject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec2RejectionNaNTests, TryReject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::Vec2<float>::one();
    const auto& ontoNaNVec = GetParam();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(oneVec.tryReject(ontoNaNVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that the rejection of NaN vector using static variant of @ref flcn::Vec2::tryReject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec2RejectionNaNTests, StaticWrapper_TryReject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::Vec2<float>::one();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(flcn::Vec2<float>::tryReject(nanVec, ontoVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that the rejection onto NaN vector using static variant of @ref flcn::Vec2::tryReject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec2RejectionNaNTests, StaticWrapper_TryReject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::Vec2<float>::one();
    const auto& ontoNaNVec = GetParam();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(flcn::Vec2<float>::tryReject(oneVec, ontoNaNVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/** @} */
