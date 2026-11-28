/**
 * @file Vec4.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 28, 2026
 *
 * @brief Verifies flcn::Vec4 projection and rejection.
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


namespace
{
    using namespace testutils;

    /// +---------------------------------------------------------------------------------------+
    /// |                                STATIC TESTS                                           |
    /// +---------------------------------------------------------------------------------------+
    namespace static_tests
    {
        constexpr flcn::Vec4 VEC_A4(1, 2, 3, 4);
        constexpr flcn::Vec4 VEC_B4(1, 0, 0, 0);

        /// @test Verify that vector projection(project normalized) returns a valid vector at compile time.
        constexpr auto PROJ_VEC4 = flcn::project(VEC_A4, VEC_B4);
        static_assert(PROJ_VEC4.x() == 1);
        static_assert(PROJ_VEC4.y() == 0);
        static_assert(PROJ_VEC4.z() == 0);
        static_assert(PROJ_VEC4.w() == 0);

        /// @test Verify that vector projection(project normalized-static wrapper) returns a valid vector at compile
        /// time.
        constexpr auto PROJ_NORM_VEC4 = flcn::projectNorm(VEC_A4, VEC_B4);
        static_assert(PROJ_NORM_VEC4.x() == 1);
        static_assert(PROJ_NORM_VEC4.y() == 0);
        static_assert(PROJ_NORM_VEC4.z() == 0);
        static_assert(PROJ_NORM_VEC4.w() == 0);

        /// @test Verify that vector projection(safe project normalized) returns a valid vector at compile time.
        constexpr auto SAFE_PROJ_VEC4 = flcn::safeProject(VEC_A4, VEC_B4);
        static_assert(SAFE_PROJ_VEC4.x() == 1);
        static_assert(SAFE_PROJ_VEC4.y() == 0);
        static_assert(SAFE_PROJ_VEC4.z() == 0);
        static_assert(SAFE_PROJ_VEC4.w() == 0);

        /// @test Verify that vector projection(safe project normalized-static wrapper) returns a valid vector at
        /// compile time.
        constexpr auto SAFE_PROJ_NORM_VEC4 = flcn::safeProjectNorm(VEC_A4, VEC_B4);
        static_assert(SAFE_PROJ_NORM_VEC4.x() == 1);
        static_assert(SAFE_PROJ_NORM_VEC4.y() == 0);
        static_assert(SAFE_PROJ_NORM_VEC4.z() == 0);
        static_assert(SAFE_PROJ_NORM_VEC4.w() == 0);

        /// @test Verify that vector rejection(reject-static wrapper) returns a valid vector at compile time.
        constexpr auto REJ_VEC4 = flcn::reject(VEC_A4, VEC_B4);
        static_assert(REJ_VEC4.x() == 0);
        static_assert(REJ_VEC4.y() == 2);
        static_assert(REJ_VEC4.z() == 3);
        static_assert(REJ_VEC4.w() == 4);

        /// @test Verify that vector rejection(reject normalized-static wrapper) returns a valid vector at compile
        /// time.
        constexpr auto REJ_NORM_VEC4 = flcn::rejectNorm(VEC_A4, VEC_B4);
        static_assert(REJ_NORM_VEC4.x() == 0);
        static_assert(REJ_NORM_VEC4.y() == 2);
        static_assert(REJ_NORM_VEC4.z() == 3);
        static_assert(REJ_NORM_VEC4.w() == 4);

        /// @test Verify that vector rejection(safe reject-static wrapper) returns a valid vector at compile time.
        constexpr auto SAFE_REJ_VEC4 = flcn::safeReject(VEC_A4, VEC_B4);
        static_assert(SAFE_REJ_VEC4.x() == 0);
        static_assert(SAFE_REJ_VEC4.y() == 2);
        static_assert(SAFE_REJ_VEC4.z() == 3);
        static_assert(SAFE_REJ_VEC4.w() == 4);

        /// @test Verify that vector rejection(safe reject normalized-static wrapper) returns a valid vector at
        /// compile time.
        constexpr auto SAFE_REJ_NORM_VEC4 = flcn::safeRejectNorm(VEC_A4, VEC_B4);
        static_assert(SAFE_REJ_NORM_VEC4.x() == 0);
        static_assert(SAFE_REJ_NORM_VEC4.y() == 2);
        static_assert(SAFE_REJ_NORM_VEC4.z() == 3);
        static_assert(SAFE_REJ_NORM_VEC4.w() == 4);
    } // namespace static_tests
} // namespace



TYPED_TEST(Vec4ProjectionTests, StaticWrapper_Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const flcn::Vec4 actualProjection = flcn::project(this->_vec, this->_ontoVec);
    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}

/**
 * @test Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref flcn::Vec4::projectNorm returns a non-zero vector.
 */
TEST(Vec4ProjectionTests, StaticWrapper_ProjectNorm_NormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, 0.0f, 0.0f, 0.0f);
    const flcn::Vec4 expectedProjection(1.0f, 0.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::Vec4 actualProjection = flcn::projectNorm(a, b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}

/**
 * @test Verify that projection using static variant of @ref flcn::Vec4::project
 *       always return floating-point vector.
 */
TYPED_TEST(Vec4ProjectionTests, StaticWrapper_Project_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::Vec4 projection = flcn::project(this->_vec, this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::ValueType>);
}


TYPED_TEST(Vec4ProjectionTests, StaticWrapper_SafeProject_Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const flcn::Vec4 actualProjection = flcn::safeProject(this->_vec, this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


TEST(Vec4ProjectionTests, StaticWrapper_SafeProjectNorm_NormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, 0.0f, 0.0f, 0.0f);
    const flcn::Vec4 expectedProjection(1.0f, 0.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::Vec4 actualProjection = flcn::safeProjectNorm(a, b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


TEST(Vec4ProjectionTests, StaticWrapper_SafeProjectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector
    const flcn::Vec4 a(1.0f, flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN);
    const flcn::Vec4 b(1.0f, 0.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::Vec4 actualProjection = flcn::safeProjectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


TEST(Vec4ProjectionTests, StaticWrapper_SafeProjectNorm_OntoNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN);

    // When the vector is from a NaN vector
    const flcn::Vec4 actualProjection = flcn::safeProjectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


TEST(Vec4ProjectionTests, StaticWrapper_SafeProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::Vec4 a(4.0f, 4.0f, 4.0f, 4.0f);
    const flcn::Vec4 negativeYAxis(0.0f, -1.0f, 0.0f, 0.0f);
    const flcn::Vec4 expectedProjection(0.0f, 4.0f, 0.0f, 0.0f);

    // When projected
    const auto actualProjection = flcn::safeProject(a, negativeYAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using static variant of @ref flcn::Vec4::safeProject returns a type-promoted vector.
 */
TEST(Vec4Projection, StaticWrapper_SafeProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const flcn::Vec4 vec(7, 13, 29, 41);
    const flcn::Vec4 onto(2.0, 4.0, 4.0, 2.0);
    const flcn::Vec4 expectedProjection(13.2, 26.4, 26.4, 13.2);

    // When projected onto another
    const flcn::Vec4 actualProjection = flcn::safeProject(vec, onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::ValueType, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


TYPED_TEST(Vec4ProjectionTests, StaticWrapper_SafeProject_OntoZeroVectorReturnsZeroVector)
{
    const flcn::Vec4 zeroVec          = flcn::Vec4<TypeParam>::zero();
    const flcn::Vec4 actualProjection = flcn::safeProject(this->_vec, zeroVec);
    EXPECT_VEC_ZERO(actualProjection);
}

TYPED_TEST(Vec4ProjectionTests, StaticWrapper_SafeProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::Vec4 projection = flcn::safeProject(this->_vec, this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::ValueType>);
}

TEST_P(Vec4ProjectionNaNTests, StaticWrapper_SafeProject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::Vec4<float>::one();

    EXPECT_VEC_ZERO(flcn::safeProject(nanVec, ontoVec));
}


TEST_P(Vec4ProjectionNaNTests, StaticWrapper_SafeProject_OntoNaNVectorReturnsZeroVector)
{
    const auto& oneVec     = flcn::Vec4<float>::one();
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(flcn::safeProject(oneVec, ontoNaNVec));
}

/**
 * @test Verify that projecting onto a non-orthogonal vector using static variant of @ref flcn::Vec4::tryProject
 *       returns a non-zero vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec4ProjectionTests,
           StaticWrapper_TryProject_Project_NonOrthogonalVectors_ReturnsNonZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Vec4 actualProjection = flcn::tryProject(this->_vec, this->_ontoVec, flag);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref flcn::Vec4::tryProjectNorm returns a non-zero vector and sets the flag to
 *       @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec4ProjectionTests, StaticWrapper_TryProjectNorm_NormalizedVectorReturnsNonZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, 0.0f, 0.0f, 0.0f);
    const flcn::Vec4 expectedProjection(1.0f, 0.0f, 0.0f, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const flcn::Vec4 actualProjection = flcn::tryProjectNorm(a, b, flag);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting a NaN vector onto a non-orthogonal unit vector using static variant of @ref
 * flcn::Vec4::tryProjectNorm returns a zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec4ProjectionTests, StaticWrapper_TryProjectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a NaN vector
    const flcn::Vec4 a(flcn::constants::NaN, 2.0f, flcn::constants::NaN, flcn::constants::NaN);
    const flcn::Vec4 b(1.0f, 0.0f, 0.0f, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the NaN vector
    const flcn::Vec4 actualProjection = flcn::tryProjectNorm(a, b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/**
 * @test Verify that projecting a vector onto a NaN vector using static variant of @ref flcn::Vec4::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec4ProjectionTests, StaticWrapper_TryProjectNorm_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a NaN vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN);
    flcn::OperationStatus flag;

    // When the vector is projected onto the NaN vector
    const flcn::Vec4 actualProjection = flcn::tryProjectNorm(a, b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using static variant of @ref flcn::Vec4::tryProject returns a non-zero vector
 *       and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec4ProjectionTests,
     StaticWrapper_TryProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirectionAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::Vec4 a(4.0f, 4.0f, 4.0f, 4.0f);
    const flcn::Vec4 negativeYAxis(0.0f, -1.0f, 0.0f, 0.0f);
    const flcn::Vec4 expectedProjection(0.0f, 4.0f, 0.0f, 0.0f);
    flcn::OperationStatus flag;

    // When projected
    const auto actualProjection = flcn::tryProject(a, negativeYAxis, flag);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using static variant of @ref flcn::Vec4::tryProject returns a type-promoted vector
 *       and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec4Projection, StaticWrapper_TryProject_MixedTypeProjectionPromotesTypeAndSetsCorrectFlag)
{
    // Given two arbitrary vectors
    const flcn::Vec4 vec(7, 13, 29, 41);
    const flcn::Vec4 onto(2.0, 4.0, 4.0, 2.0);
    const flcn::Vec4 expectedProjection(13.2, 26.4, 26.4, 13.2);
    flcn::OperationStatus flag;

    // When projected onto another
    const flcn::Vec4 actualProjection = flcn::tryProject(vec, onto, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::ValueType, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a zero length vector using static variant of @ref flcn::Vec4::tryProject
 *        returns a type-promoted vector and sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec4ProjectionTests, StaticWrapper_TryProject_OntoZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const flcn::Vec4 zeroVec = flcn::Vec4<TypeParam>::zero();
    flcn::OperationStatus flag;

    const flcn::Vec4 actualProjection = flcn::tryProject(this->_vec, zeroVec, flag);

    EXPECT_VEC_ZERO(actualProjection);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}

/**
 * @test Verify that projection using static variant of @ref flcn::Vec4::tryProject
 *       always return floating-point vector.
 */
TYPED_TEST(Vec4ProjectionTests, StaticWrapper_TryProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] flcn::OperationStatus flag;
    [[maybe_unused]] const flcn::Vec4 projection = flcn::tryProject(this->_vec, this->_ontoVec, flag);
    static_assert(std::is_floating_point_v<typename decltype(projection)::ValueType>);
}


/**
 * @test Verify that projection of NaN vector using static variant of @ref flcn::Vec4::tryProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec4ProjectionNaNTests, StaticWrapper_TryProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::Vec4<float>::one();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(flcn::tryProject(nanVec, ontoVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projection onto NaN vector using static variant of @ref flcn::Vec4::tryProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec4ProjectionNaNTests, StaticWrapper_TryProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::Vec4<float>::one();
    const auto& ontoNaNVec = GetParam();
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::tryProject(oneVec, ontoNaNVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that rejecting from a non-orthogonal vector using static variant of @ref flcn::Vec4::reject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vec4RejectionTests, StaticWrapper_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const flcn::Vec4 actualRejection = flcn::reject(this->_vec, this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from an orthogonal unit vector using static variant of @ref flcn::Vec4::rejectNorm
 *       returns a non-zero vector with perpendicular component.
 */
TEST(Vec4RejectionTests, StaticWrapper_RejectionFromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, 0.0f, 0.0f, 0.0f);
    const flcn::Vec4 expectedRejection(0.0f, 2.0f, 3.0f, 4.0f);

    // When rejected from another
    const flcn::Vec4 actualRejection = flcn::rejectNorm(a, b);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that rejection using static variant of @ref flcn::Vec4::reject
 *       always return floating-point vector.
 */
TYPED_TEST(Vec4RejectionTests, StaticWrapper_Reject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::Vec4 rejection = flcn::reject(this->_vec, this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::ValueType>);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using static variant of
 *       @ref flcn::Vec4::safeRejectNorm returns a non-zero vector with perpendicular component.
 */
TEST(Vec4RejectionTests, StaticWrapper_SafeRejectNorm_FromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, 0.0f, 0.0f, 0.0f);
    const flcn::Vec4 expectedRejection(0.0f, 2.0f, 3.0f, 4.0f);

    // When rejected from another
    const flcn::Vec4 actualRejection = flcn::safeRejectNorm(a, b);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting a NaN vector from a non-orthogonal unit vector using static variant of
 *       @ref flcn::Vec4::safeRejectNorm returns a zero vector.
 */
TEST(Vec4RejectionTests, StaticWrapper_SafeRejectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector
    const flcn::Vec4 a(1.0f, flcn::constants::NaN, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, 0.0f, 0.0f, 0.0f);

    // When the vector is rejected onto the normalized vector
    const flcn::Vec4 actualRejection = flcn::safeRejectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting from a NaN vector using static variant of
 *       @ref flcn::Vec4::safeRejectNorm returns a zero vector.
 */
TEST(Vec4RejectionTests, StaticWrapper_SafeRejectNorm_FromNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, flcn::constants::NaN, 3.0f, 4.0f);

    // When the vector is rejected from a NaN vector
    const flcn::Vec4 actualRejection = flcn::safeRejectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualRejection);
}

/**
 * @test Verify that safely rejecting from a parallel vector using static variant of @ref flcn::Vec4::safeReject
 *       returns a zero vector.
 */
TYPED_TEST(Vec4RejectionTests, StaticWrapper_SafeReject_ParallelVectorsReturnsZeroVector)
{
    const flcn::Vec4 actualRejection = flcn::safeReject(this->_vec, this->_parallelVec);

    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting a vector from an orthogonal vector using
 *       static variant of @ref flcn::Vec4::safeReject returns the original vector.
 */
TEST(Vec4RejectionTests, StaticWrapper_SafeReject_OrthogonalRejectionReturnsOriginalVector)
{
    const flcn::Vec4 a(0.0f, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, 0.0f, 0.0f, 0.0f);

    const flcn::Vec4 actualRejection = flcn::safeReject(a, b);

    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @test Verify that safely rejecting from a non-orthogonal vector using static variant of
 *       @ref flcn::Vec4::safeReject returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vec4RejectionTests, StaticWrapper_SafeReject_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const flcn::Vec4 actualRejection = flcn::safeReject(this->_vec, this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting a vector from another vector of different numeric type
 *       using static variant of @ref flcn::Vec4::safeReject returns a type-promoted vector.
 */
TEST(Vec4RejectionTests, StaticWrapper_SafeReject_MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    const flcn::Vec4 vec(7, 13, 29, 41);
    const flcn::Vec4 from(2.0, 4.0, 4.0, 2.0);
    const flcn::Vec4 expectedRejection(-6.2, -13.4, 2.6, 27.8);

    // When rejected from another
    const flcn::Vec4 actualRejection = flcn::safeReject(vec, from);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::ValueType, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting from a zero length vector using static variant of @ref flcn::Vec4::safeReject
 *       returns the same vector.
 */
TYPED_TEST(Vec4RejectionTests, StaticWrapper_SafeReject_FromZeroVectorReturnsSameVector)
{
    const flcn::Vec4 zeroVec = flcn::Vec4<TypeParam>::zero();

    const flcn::Vec4 actualRejection = flcn::safeReject(this->_vec, zeroVec);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
}

/**
 * @test Verify that rejection using static variant of @ref flcn::Vec4::safeReject
 *       always return floating-point vector.
 */
TYPED_TEST(Vec4RejectionTests, StaticWrapper_SafeReject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::Vec4 rejection = flcn::safeReject(this->_vec, this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::ValueType>);
}


/**
 * @test Verify that the rejection of NaN vector using static variant of @ref flcn::Vec4::safeReject
 *       returns zero vector.
 */
TEST_P(Vec4RejectionNaNTests, StaticWrapper_SafeReject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::Vec4<float>::one();

    EXPECT_VEC_ZERO(flcn::safeReject(nanVec, ontoVec));
}


/**
 * @test Verify that rejecting onto a NaN vector using static variant of @ref flcn::Vec4::safeReject
 *       returns zero vector.
 */
TEST_P(Vec4RejectionNaNTests, StaticWrapper_SafeReject_OntoNaNVectorReturnsZeroVector)
{
    const auto& oneVec     = flcn::Vec4<float>::one();
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(flcn::safeReject(oneVec, ontoNaNVec));
}

/**
 * @test Verify that safely rejecting from a parallel vector using static variant of @ref flcn::Vec4::tryReject
 *       returns a zero vector and sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec4RejectionTests, StaticWrapper_TryReject_ParallelVectorsReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    flcn::OperationStatus flag;

    const flcn::Vec4 actualRejection = flcn::tryReject(this->_vec, this->_parallelVec, flag);

    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting a vector from an orthogonal vector using
 *       static variant of @ref flcn::Vec4::tryReject returns the original vector
 *       and sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec4RejectionTests, StaticWrapper_TryReject_OrthogonalRejectionReturnsOriginalVectorAndSetsCorrectStatusFlag)
{
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 0.0f);
    const flcn::Vec4 b(0.0f, 0.0f, 0.0f, 1.0f);
    flcn::OperationStatus flag;

    const flcn::Vec4 actualRejection = flcn::tryReject(a, b, flag);

    EXPECT_VEC_EQ(a, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from a non-orthogonal vector using static variant of
 *       @ref flcn::Vec4::tryReject returns a non-zero vector with perpendicular component
 *       and sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec4RejectionTests,
           StaticWrapper_TryReject_NonOrthogonalRejectionReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    flcn::OperationStatus flag;

    const flcn::Vec4 actualRejection = flcn::tryReject(this->_vec, this->_fromVec, flag);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using static variant of
 *       @ref flcn::Vec4::tryRejectNorm returns a non-zero vector and with perpendicular component sets flag to
 *       @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec4RejectionTests, StaticWrapper_TryRejectNorm_FromNormalizedVectorReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, 0.0f, 0.0f, 0.0f);
    const flcn::Vec4 expectedRejection(0.0f, 2.0f, 3.0f, 4.0f);
    flcn::OperationStatus flag;


    // When rejected from another
    const flcn::Vec4 actualRejection = flcn::tryRejectNorm(a, b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}

/**
 * @test Verify that safely rejecting NaN vector from an orthogonal unit vector using static variant of
 *       @ref flcn::Vec4::tryRejectNorm returns a zero vector and sets flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec4RejectionTests, StaticWrapper_TryRejectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec4 a(1.0f, flcn::constants::NaN, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, 0.0f, 0.0f, 0.0f);
    flcn::OperationStatus flag;


    // When rejected from another
    const flcn::Vec4 actualRejection = flcn::tryRejectNorm(a, b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that safely rejecting from an NaN vector using static variant of @ref flcn::Vec4::tryRejectNorm
 *       returns a zero vector and sets flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec4RejectionTests, StaticWrapper_TryRejectNorm_FromNaNVectorReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, flcn::constants::NaN, 3.0f, 4.0f);
    flcn::OperationStatus flag;


    // When rejected from another
    const flcn::Vec4 actualRejection = flcn::tryRejectNorm(a, b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that safely rejecting a vector from another vector of different numeric type
 *       using static variant of @ref flcn::Vec4::tryReject returns a type-promoted vector
 *       and sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec4RejectionTests, StaticWrapper_TryReject_MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    const flcn::Vec4 vec(7, 13, 29, 41);
    const flcn::Vec4 from(2.0, 4.0, 4.0, 2.0);
    const flcn::Vec4 expectedRejection(-6.2, -13.4, 2.6, 27.8);
    flcn::OperationStatus flag;

    // When rejected from another
    const flcn::Vec4 actualRejection = flcn::tryReject(vec, from, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::ValueType, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    // Flag is set to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from a zero length vector using static variant of @ref flcn::Vec4::tryReject
 *       returns the same vector and sets flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec4RejectionTests, StaticWrapper_TryReject_FromZeroVectorReturnsSameVectorAndSetsCorrectStatusFlag)
{
    const flcn::Vec4 zeroVec = flcn::Vec4<TypeParam>::zero();
    flcn::OperationStatus flag;

    const flcn::Vec4 actualRejection = flcn::tryReject(this->_vec, zeroVec, flag);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that rejection using static variant of @ref flcn::Vec4::tryReject
 *       always return floating-point vector.
 */
TYPED_TEST(Vec4RejectionTests, StaticWrapper_TryReject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] flcn::OperationStatus status;
    [[maybe_unused]] const flcn::Vec4 rejection = flcn::tryReject(this->_vec, this->_fromVec, status);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::ValueType>);
}


/**
 * @test Verify that the rejection of NaN vector using static variant of @ref flcn::Vec4::tryReject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec4RejectionNaNTests, StaticWrapper_TryReject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::Vec4<float>::one();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(flcn::tryReject(nanVec, ontoVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that the rejection onto NaN vector using static variant of @ref flcn::Vec4::tryReject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec4RejectionNaNTests, StaticWrapper_TryReject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::Vec4<float>::one();
    const auto& ontoNaNVec = GetParam();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(flcn::tryReject(oneVec, ontoNaNVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/** @} */
