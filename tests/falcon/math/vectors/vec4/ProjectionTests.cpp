/**
 * @file ProjectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verify @ref flcn::Vec4 projection logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */




/**
 * @addtogroup T_Falcon_Vec4_Proj
 * @{
 */

#include "ProjectionTestFixture.h"
#include "Vec4TestSetup.h"


namespace
{
    /// +---------------------------------------------------------------------------------------+
    /// |                                STATIC TESTS                                           |
    /// +---------------------------------------------------------------------------------------+
    namespace static_tests
    {
        constexpr flcn::Vec4 VEC_A(1, 2, 3, 4);
        constexpr flcn::Vec4 VEC_B(1, 0, 0, 0);

        /// @test Verify that vector projection(project) returns a valid vector at compile time.
        constexpr auto PROJ_VEC = VEC_A.project(VEC_B);
        static_assert(PROJ_VEC.x() == 1);
        static_assert(PROJ_VEC.y() == 0);
        static_assert(PROJ_VEC.z() == 0);
        static_assert(PROJ_VEC.w() == 0);

        /// @test Verify that vector projection(project-static wrapper) returns a valid vector at compile time.
        constexpr auto PROJ_VEC_STATIC = VEC_A.projectNorm(VEC_B);
        static_assert(PROJ_VEC_STATIC.x() == 1);
        static_assert(PROJ_VEC_STATIC.y() == 0);
        static_assert(PROJ_VEC_STATIC.z() == 0);
        static_assert(PROJ_VEC_STATIC.w() == 0);

        /// @test Verify that vector projection(safe project) returns a valid vector at compile time.
        constexpr auto SAFE_PROJ_VEC = VEC_A.safeProject(VEC_B);
        static_assert(SAFE_PROJ_VEC.x() == 1);
        static_assert(SAFE_PROJ_VEC.y() == 0);
        static_assert(SAFE_PROJ_VEC.z() == 0);
        static_assert(SAFE_PROJ_VEC.w() == 0);

        /// @test Verify that vector projection(safe project-static wrapper) returns a valid vector at compile time.
        constexpr auto SAFE_PROJ_VEC_STATIC = VEC_A.safeProjectNorm(VEC_B);
        static_assert(SAFE_PROJ_VEC_STATIC.x() == 1);
        static_assert(SAFE_PROJ_VEC_STATIC.y() == 0);
        static_assert(SAFE_PROJ_VEC_STATIC.z() == 0);
        static_assert(SAFE_PROJ_VEC_STATIC.w() == 0);
    } // namespace static_tests
} // namespace



/**************************************
 *          PROJECTION TESTS          *
 **************************************/

/** @test Verify that projecting onto an orthogonal vector using @ref flcn::Vec4::project returns a zero vector. */
TYPED_TEST(Vec4ProjectionTests, OrthogonalVectorsReturnsZeroVector)
{
    const flcn::Vec4 actualProjection = this->_perpendicularVec.project(this->_ontoVec);
    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @test Verify that projecting onto a vector parallel to x-axis using @ref flcn::Vec4::project
 *       returns a vector containing only an x-component.
 */
TEST(Vec4Projection, Project_XAxis_ReturnVectorWithNonZeroXComponent)
{
    // Given an arbitrary vector
    const flcn::Vec4 a(10.0f, 20.0f, 30.0f, 40.0f);
    const flcn::Vec4 xAxis(1.0f, 0.0f, 0.0f, 0.0f);
    const flcn::Vec4 expectedProjection(10.0f, 0.0f, 0.0f, 0.0f);

    // When projected onto x-axis
    const flcn::Vec4 actualProjection = a.project(xAxis);

    // Then, the resultant vector only has x-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a vector parallel to y-axis using @ref flcn::Vec4::project
 *       returns a vector containing only a y-component.
 */
TEST(Vec4Projection, Project_YAxis_ReturnVectorWithNonZeroYComponent)
{
    // Given an arbitrary vector
    const flcn::Vec4 a(10.0f, 20.0f, 30.0f, 40.0f);
    const flcn::Vec4 yAxis(0.0f, 1.0f, 0.0f, 0.0f);
    const flcn::Vec4 expectedProjection(0.0f, 20.0f, 0.0f, 0.0f);

    // When projected onto y-axis
    const flcn::Vec4 actualProjection = a.project(yAxis);

    // Then, the resultant vector only has y-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a vector parallel to z-axis using @ref flcn::Vec4::project
 *       returns a vector containing only a z-component.
 */
TEST(Vec4Projection, Project_ZAxis_ReturnVectorWithNonZeroZComponent)
{
    // Given an arbitrary vector
    const flcn::Vec4 a(10.0f, 20.0f, 30.0f, 40.0f);
    const flcn::Vec4 zAxis(0.0f, 0.0f, 1.0f, 0.0f);
    const flcn::Vec4 expectedProjection(0.0f, 0.0f, 30.0f, 0.0f);

    // When projected onto z-axis
    const flcn::Vec4 actualProjection = a.project(zAxis);

    // Then, the resultant vector only has z-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a vector parallel to w-axis using @ref flcn::Vec4::project
 *       returns a vector containing only a w-component.
 */
TEST(Vec4Projection, ProjectionOntoWAxisReturnsVectorWithOnlyWComponent)
{
    // Given an arbitrary vector
    const flcn::Vec4 a(10.0f, 20.0f, 30.0f, 40.0f);
    const flcn::Vec4 wAxis(0.0f, 0.0f, 0.0f, 1.0f);
    const flcn::Vec4 expectedProjection(0.0f, 0.0f, 0.0f, 40.0f);

    // When projected onto w-axis
    const flcn::Vec4 actualProjection = a.project(wAxis);

    // Then, the resultant vector only has w-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector using @ref flcn::Vec4::project
 *       returns a non-zero vector.
 */
TYPED_TEST(Vec4ProjectionTests, Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const flcn::Vec4 actualProjection = this->_vec.project(this->_ontoVec);
    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using @ref flcn::Vec4::projectNorm
 *       returns a non-zero vector.
 */
TEST(Vec4Projection, ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, 0.0f, 0.0f, 0.0f);
    const flcn::Vec4 expectedProjection(1.0f, 0.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::Vec4 actualProjection = a.projectNorm(b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref flcn::Vec4::project returns a non-zero vector.
 */
TEST(Vec4Projection, ProjectionOntoVectorInOppositeDirectionReturnsNonZeroVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::Vec4 a(4.0f, 4.0f, 4.0f, 4.0f);
    const flcn::Vec4 negativeZAxis(0.0f, 0.0f, -1.0f, 0.0f);
    const flcn::Vec4 expectedProjection(0.0f, 0.0f, 4.0f, 0.0f);

    // When projected
    const flcn::Vec4<float> actualProjection = a.project(negativeZAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using @ref flcn::Vec4::project returns a type-promoted vector.
 */
TEST(Vec4Projection, MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const flcn::Vec4 vec(7, 13, 29, 41);
    const flcn::Vec4 onto(2.0, 4.0, 4.0, 2.0);
    const flcn::Vec4 expectedProjection(13.2, 26.4, 26.4, 13.2);

    // When projected onto another
    const flcn::Vec4 actualProjection = vec.project(onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::ValueType, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/** @test Verify that projection using @ref flcn::Vec4::project always return floating-point vector. */
TYPED_TEST(Vec4ProjectionTests, Project_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::Vec4 projection = this->_vec.project(this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::ValueType>);
}



/**************************************
 *        SAFE PROJECTION TESTS       *
 **************************************/

/**
 * @test Verify that projecting onto an orthogonal vector using @ref flcn::Vec4::safeProject
 *       returns a zero vector.
 */
TYPED_TEST(Vec4ProjectionTests, SafeProject_Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const flcn::Vec4 actualProjection = this->_vec.safeProject(this->_ontoVec);
    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using @ref flcn::Vec4::safeProjectNorm
 *       returns a non-zero vector.
 */
TEST(Vec4Projection, SafeProjectNorm_ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, 0.0f, 0.0f, 0.0f);
    const flcn::Vec4 expectedProjection(1.0f, 0.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::Vec4 actualProjection = a.safeProjectNorm(b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting a NaN vector onto a non-orthogonal unit vector using @ref
 * flcn::Vec4::safeProjectNorm returns a zero vector.
 */
TEST(Vec4Projection, SafeProjectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector and a normalized vector
    const flcn::Vec4 a(1.0f, flcn::constants::NaN, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, 0.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::Vec4 actualProjection = a.safeProjectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}

/**
 * @test Verify that projecting a NaN vector onto a non-orthogonal unit vector using @ref
 * flcn::Vec4::safeProjectNorm returns a zero vector.
 */
TEST(Vec4Projection, SafeProjectNorm_OntoNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, flcn::constants::NaN, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::Vec4 actualProjection = a.safeProjectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref flcn::Vec4::safeProject returns a non-zero vector.
 */
TEST(Vec4Projection, SafeProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::Vec4 a(4.0f, 4.0f, 4.0f, 4.0f);
    const flcn::Vec4 negativeZAxis(0.0f, 0.0f, -1.0f, 0.0f);
    const flcn::Vec4 expectedProjection(0.0f, 0.0f, 4.0f, 0.0f);

    // When projected
    const flcn::Vec4<float> actualProjection = a.safeProject(negativeZAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector of a different numeric type
 *         using @ref flcn::Vec4::safeProject returns a type-promoted vector.
 */
TEST(Vec4Projection, SafeProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const flcn::Vec4 vec(7, 13, 29, 41);
    const flcn::Vec4 onto(2.0, 4.0, 4.0, 2.0);
    const flcn::Vec4 expectedProjection(13.2, 26.4, 26.4, 13.2);

    // When projected onto another
    const flcn::Vec4 actualProjection = vec.safeProject(onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::ValueType, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a zero length vector using @ref flcn::Vec4::safeProject
 *       returns a zero vector.
 */
TYPED_TEST(Vec4ProjectionTests, SafeProject_OntoZeroReturnsZeroVector)
{
    const flcn::Vec4 zeroVec = flcn::Vec4<TypeParam>::zero();

    const flcn::Vec4 actualProjection = this->_vec.safeProject(zeroVec);

    EXPECT_VEC_ZERO(actualProjection);
}


/** @test Verify that projection using @ref flcn::Vec4::safeProject always return floating-point vector. */
TYPED_TEST(Vec4ProjectionTests, SafeProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::Vec4 projection = this->_vec.safeProject(this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::ValueType>);
}


/**
 * @test Verify that projection of NaN vector using @ref flcn::Vec4::safeProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec4ProjectionNaNTests, SafeProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::Vec4<float>::one();
    EXPECT_VEC_ZERO(nanVec.safeProject(ontoVec));
}


/**
 * @test Verify that projection onto NaN vector using @ref flcn::Vec4::safeProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec4ProjectionNaNTests, SafeProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::Vec4<float>::one();
    const auto& ontoNaNVec = GetParam();
    EXPECT_VEC_ZERO(oneVec.safeProject(ontoNaNVec));
}



/**************************************
 *         TRY PROJECTION TESTS       *
 **************************************/

/**
 * @test Verify that projecting onto an orthogonal vector using @ref flcn::Vec4::tryProject
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec4ProjectionTests, TryProject_Project_NonOrthogonalVectors_ReturnsNonZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Vec4 actualProjection = this->_vec.tryProject(this->_ontoVec, flag);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting a NaN vector onto a non-orthogonal unit vector using @ref flcn::Vec4::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec4Projection, TryProjectNorm_ProjectionOntoNormalizedVectorReturnsNonZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, 0.0f, 0.0f, 0.0f);
    const flcn::Vec4 expectedProjection(1.0f, 0.0f, 0.0f, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const flcn::Vec4 actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting a NaN vector onto a non-orthogonal unit vector using @ref flcn::Vec4::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec4Projection, TryProjectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec4 a(flcn::constants::NaN, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, 0.0f, 0.0f, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const flcn::Vec4 actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projecting a vector onto a NaN vector using @ref flcn::Vec4::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec4Projection, TryProjectNorm_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, flcn::constants::NaN, 0.0f, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const flcn::Vec4 actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref flcn::Vec4::tryProject returns a non-zero vector
 *       and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec4Projection, TryProjectNorm_OntoVectorInOppositeDirectionReturnsVectorInSameDirectionAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::Vec4 a(4.0f, 4.0f, 4.0f, 4.0f);
    const flcn::Vec4 negativeZAxis(0.0f, 0.0f, -1.0f, 0.0f);
    const flcn::Vec4 expectedProjection(0.0f, 0.0f, 4.0f, 0.0f);
    flcn::OperationStatus flag;

    // When projected
    const flcn::Vec4<float> actualProjection = a.tryProject(negativeZAxis, flag);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using @ref flcn::Vec4::tryProject returns a type-promoted vector
 *       and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec4Projection, TryProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const flcn::Vec4 vec(7, 13, 29, 41);
    const flcn::Vec4 onto(2.0, 4.0, 4.0, 2.0);
    const flcn::Vec4 expectedProjection(13.2, 26.4, 26.4, 13.2);
    flcn::OperationStatus flag;

    // When projected onto another
    const flcn::Vec4 actualProjection = vec.tryProject(onto, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::ValueType, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a zero length vector using @ref flcn::Vec4::tryProject
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec4ProjectionTests, TryProject_OntoZeroReturnsZeroVectorAndSetsCorrectFlag)
{
    const flcn::Vec4 zeroVec = flcn::Vec4<TypeParam>::zero();
    flcn::OperationStatus flag;


    const flcn::Vec4 actualProjection = this->_vec.tryProject(zeroVec, flag);

    EXPECT_VEC_ZERO(actualProjection);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/** @test Verify that projection using @ref flcn::Vec4::tryProject always return floating-point vector. */
TYPED_TEST(Vec4ProjectionTests, TryProject_AlwaysReturnFloatingPointVectorAndSetsCorrectFlag)
{
    [[maybe_unused]] flcn::OperationStatus flag;
    [[maybe_unused]] const flcn::Vec4 projection = this->_vec.tryProject(this->_ontoVec, flag);
    static_assert(std::is_floating_point_v<typename decltype(projection)::ValueType>);
}


/**
 * @test Verify that projection of NaN vector using @ref flcn::Vec4::tryProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec4ProjectionNaNTests, TryProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::Vec4<float>::one();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(nanVec.tryProject(ontoVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projection onto NaN vector using @ref flcn::Vec4::tryProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec4ProjectionNaNTests, TryProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::Vec4<float>::one();
    const auto& ontoNaNVec = GetParam();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(oneVec.tryProject(ontoNaNVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/** @} */
