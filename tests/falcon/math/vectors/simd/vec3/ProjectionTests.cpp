/**
 * @file ProjectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref flcn::simd::Vec3 projection logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



/**
 * @addtogroup T_Falcon_Vec3_Proj
 * @{
 */

#include "ProjectionTestFixture.h"
#include "Vec3TestSetup.h"



/**************************************
 *          PROJECTION TESTS          *
 **************************************/

/** @test Verify that projecting onto an orthogonal vector using @ref flcn::simd::Vec3::project returns a zero vector.
 */
TYPED_TEST(SimdVec3ProjectionTests, OrthogonalVectorsReturnsZeroVector)
{
    const flcn::simd::Vec3 actualProjection = this->_perpendicularVec.project(this->_ontoVec);

    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @test Verify that projecting onto a vector parallel to x-axis using @ref flcn::simd::Vec3::project
 *       returns a vector containing only an x-component.
 */
TEST(SimdVec3ProjectionTests, Project_XAxis_ReturnVectorWithNonZeroXComponent)
{
    // Given an arbitrary vector
    const flcn::simd::Vec3 a(10.0f, 20.0f, 30.0f);
    const flcn::simd::Vec3 xAxis(1.0f, 0.0f, 0.0f);
    const flcn::simd::Vec3 expectedProjection(10.0f, 0.0f, 0.0f);

    // When projected onto x-axis
    const flcn::simd::Vec3 actualProjection = a.project(xAxis);

    // Then, the resultant vector only has x-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a vector parallel to y-axis using @ref flcn::simd::Vec3::project
 *       returns a vector containing only a y-component.
 */
TEST(SimdVec3ProjectionTests, Project_YAxis_ReturnVectorWithNonZeroYComponent)
{
    // Given an arbitrary vector
    const flcn::simd::Vec3 a(10.0f, 20.0f, 30.0f);
    const flcn::simd::Vec3 yAxis(0.0f, 1.0f, 0.0f);
    const flcn::simd::Vec3 expectedProjection(0.0f, 20.0f, 0.0f);

    // When projected onto y-axis
    const flcn::simd::Vec3 actualProjection = a.project(yAxis);

    // Then, the resultant vector only has y-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a vector parallel to z-axis using @ref flcn::simd::Vec3::project
 *       returns a vector containing only a z-component.
 */
TEST(SimdVec3ProjectionTests, Project_ZAxis_ReturnVectorWithNonZeroZComponent)
{
    // Given an arbitrary vector
    const flcn::simd::Vec3 a(10.0f, 20.0f, 30.0f);
    const flcn::simd::Vec3 zAxis(0.0f, 0.0f, 1.0f);
    const flcn::simd::Vec3 expectedProjection(0.0f, 0.0f, 30.0f);

    // When projected onto z-axis
    const flcn::simd::Vec3 actualProjection = a.project(zAxis);

    // Then, the resultant vector only has z-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector using @ref flcn::simd::Vec3::project
 *       returns a non-zero vector.
 */
TYPED_TEST(SimdVec3ProjectionTests, Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const flcn::simd::Vec3 actualProjection = this->_vec.project(this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using @ref flcn::simd::Vec3::projectNorm
 *       returns a non-zero vector.
 */
TEST(SimdVec3ProjectionTests, ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::simd::Vec3 b(1.0f, 0.0f, 0.0f);
    const flcn::simd::Vec3 expectedProjection(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::simd::Vec3 actualProjection = a.projectNorm(b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref flcn::simd::Vec3::project returns a non-zero vector.
 */
TEST(SimdVec3ProjectionTests, ProjectionOntoVectorInOppositeDirectionReturnsNonZeroVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::simd::Vec3 a(4.0f, 4.0f, 4.0f);
    const flcn::simd::Vec3 negativeZAxis(0.0f, 0.0f, -1.0f);
    const flcn::simd::Vec3 expectedProjection(0.0f, 0.0f, 4.0f);

    // When projected
    const flcn::simd::Vec3<float> actualProjection = a.project(negativeZAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/** @test Verify that projection using @ref flcn::simd::Vec3::project always return floating-point vector. */
TYPED_TEST(SimdVec3ProjectionTests, Project_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::simd::Vec3 projection = this->_vec.project(this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::ValueType>);
}




/**************************************
 *        SAFE PROJECTION TESTS       *
 **************************************/

/**
 * @test Verify that projecting onto an orthogonal vector using @ref flcn::simd::Vec3::safeProject
 *       returns a zero vector.
 */
TYPED_TEST(SimdVec3ProjectionTests, SafeProject_Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const flcn::simd::Vec3 actualProjection = this->_vec.safeProject(this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using @ref flcn::simd::Vec3::safeProjectNorm
 *       returns a non-zero vector.
 */
TEST(SimdVec3ProjectionTests, SafeProjectNorm_ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::simd::Vec3 b(1.0f, 0.0f, 0.0f);
    const flcn::simd::Vec3 expectedProjection(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::simd::Vec3 actualProjection = a.safeProject(b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting a NaN vector onto a non-orthogonal unit vector using @ref
 * flcn::simd::Vec3::safeProjectNorm returns a zero vector.
 */
TEST(SimdVec3ProjectionTests, SafeProjectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector and a normalized vector
    const flcn::simd::Vec3 a(1.0f, 2.0f, flcn::constants::NaN);
    const flcn::simd::Vec3 b(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::simd::Vec3 actualProjection = a.safeProjectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @test Verify that projecting a NaN vector onto a non-orthogonal unit vector using @ref
 * flcn::simd::Vec3::safeProjectNorm returns a zero vector.
 */
TEST(SimdVec3ProjectionTests, SafeProjectNorm_OntoNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::simd::Vec3 b(1.0f, 1.0f, flcn::constants::NaN);

    // When the vector is projected onto the normalized vector
    const flcn::simd::Vec3 actualProjection = a.safeProjectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref flcn::simd::Vec3::safeProject returns a non-zero vector.
 */
TEST(SimdVec3ProjectionTests, SafeProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::simd::Vec3 a(4.0f, 4.0f, 4.0f);
    const flcn::simd::Vec3 negativeZAxis(0.0f, 0.0f, -1.0f);
    const flcn::simd::Vec3 expectedProjection(0.0f, 0.0f, 4.0f);

    // When projected
    const flcn::simd::Vec3<float> actualProjection = a.safeProject(negativeZAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a zero length vector using @ref flcn::simd::Vec3::safeProject
 *       returns a zero vector.
 */
TYPED_TEST(SimdVec3ProjectionTests, SafeProject_OntoZeroReturnsZeroVector)
{
    const flcn::simd::Vec3 zeroVec = flcn::simd::Vec3<TypeParam>::zero();
    const flcn::simd::Vec3 actualProjection = this->_vec.safeProject(zeroVec);
    EXPECT_VEC_ZERO(actualProjection);
}


/** @test Verify that projection using @ref flcn::simd::Vec3::safeProject always return floating-point vector. */
TYPED_TEST(SimdVec3ProjectionTests, SafeProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::simd::Vec3 projection = this->_vec.safeProject(this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::ValueType>);
}


/**
 * @test Verify that projection of NaN vector using @ref flcn::simd::Vec3::safeProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(SimdVec3ProjectionNaNTests, SafeProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::simd::Vec3<float>::one();

    EXPECT_VEC_ZERO(nanVec.safeProject(ontoVec));
}


/**
 * @test Verify that projection onto NaN vector using @ref flcn::simd::Vec3::safeProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(SimdVec3ProjectionNaNTests, SafeProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::simd::Vec3<float>::one();
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(oneVec.safeProject(ontoNaNVec));
}



/**************************************
 *         TRY PROJECTION TESTS       *
 **************************************/

/**
 * @test Verify that projecting onto an orthogonal vector using @ref flcn::simd::Vec3::tryProject
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(SimdVec3ProjectionTests, TryProject_Project_NonOrthogonalVectors_ReturnsNonZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::simd::Vec3 actualProjection = this->_vec.tryProject(this->_ontoVec, flag);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}
/**
 * @test Verify that projecting onto a non-orthogonal unit vector using @ref flcn::simd::Vec3::tryProject
 *       returns a non-zero vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(SimdVec3ProjectionTests, TryProjectNorm_ProjectionOntoNormalizedVectorReturnsNonZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::simd::Vec3 b(1.0f, 0.0f, 0.0f);
    const flcn::simd::Vec3 expectedProjection(1.0f, 0.0f, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const flcn::simd::Vec3 actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting a NaN vector onto a non-orthogonal unit vector using @ref
 flcn::simd::Vec3::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(SimdVec3ProjectionTests, TryProjectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec3 a(flcn::constants::NaN, 2.0f, 3.0f);
    const flcn::simd::Vec3 b(1.0f, 0.0f, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const flcn::simd::Vec3 actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/**
 * @test Verify that projecting a vector onto a NaN vector using @ref flcn::simd::Vec3::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(SimdVec3ProjectionTests, TryProjectNorm_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::simd::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::simd::Vec3 b(1.0f, flcn::constants::NaN, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const flcn::simd::Vec3 actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref flcn::simd::Vec3::tryProject returns a non-zero vector
 *       and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(SimdVec3ProjectionTests, TryProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirectionAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::simd::Vec3 a(4.0f, 4.0f, 4.0f);
    const flcn::simd::Vec3 negativeZAxis(0.0f, 0.0f, -1.0f);
    const flcn::simd::Vec3 expectedProjection(0.0f, 0.0f, 4.0f);
    flcn::OperationStatus flag;

    // When projected
    const flcn::simd::Vec3<float> actualProjection = a.tryProject(negativeZAxis, flag);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a zero length vector using @ref flcn::simd::Vec3::tryProject
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(SimdVec3ProjectionTests, TryProject_OntoZeroReturnsZeroVectorAndSetsCorrectFlag)
{
    const flcn::simd::Vec3 zeroVec = flcn::simd::Vec3<TypeParam>::zero();
    flcn::OperationStatus flag;

    const flcn::simd::Vec3 actualProjection = this->_vec.tryProject(zeroVec, flag);

    EXPECT_VEC_ZERO(actualProjection);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/** @test Verify that projection using @ref flcn::simd::Vec3::tryProject always return floating-point vector. */
TYPED_TEST(SimdVec3ProjectionTests, TryProject_AlwaysReturnFloatingPointVectorAndSetsCorrectFlag)
{
    [[maybe_unused]] flcn::OperationStatus flag;
    [[maybe_unused]] const flcn::simd::Vec3 projection = this->_vec.tryProject(this->_ontoVec, flag);
    static_assert(std::is_floating_point_v<typename decltype(projection)::ValueType>);
}


/**
 * @test Verify that projection of NaN vector using @ref flcn::simd::Vec3::tryProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(SimdVec3ProjectionNaNTests, TryProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::simd::Vec3<float>::one();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(nanVec.tryProject(ontoVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projection onto NaN vector using @ref flcn::simd::Vec3::tryProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(SimdVec3ProjectionNaNTests, TryProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::simd::Vec3<float>::one();
    const auto& ontoNaNVec = GetParam();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(oneVec.tryProject(ontoNaNVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/** @} */
