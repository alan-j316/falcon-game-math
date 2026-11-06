/**
 * @file ProjectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref flcn::Vec2 projection logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"



/**
 * @addtogroup T_FALCON_Vec2_Proj
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Vec2 projection.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class Vec2ProjectionTests: public testing::Test
    {
    protected:
        flcn::Vec2<T> _vec;
        flcn::Vec2<T> _perpendicularVec;
        flcn::Vec2<T> _ontoVec;
        flcn::Vec2<T> _expectedProjection;

        void SetUp() override
        {
            _vec                = { T(4), T(0) };
            _perpendicularVec   = { T(0), T(11) };
            _ontoVec            = { T(2), T(0) };
            _expectedProjection = { T(4), T(0) };
        }
    };
    TYPED_TEST_SUITE(Vec2ProjectionTests, SupportedFloatingPointTypes);



    /**
     * @brief Test fixture for @ref flcn::Vec2 projection with NaN vectors.
     */
    class Vec2ProjectionNaNTests: public testing::TestWithParam<flcn::Vec2<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Vec2ProjectionNanVectors, Vec2ProjectionNaNTests,
                             ::testing::Values(flcn::Vec2<float>(flcn::constants::NaN, 1.0f),
                                               flcn::Vec2<float>(1.0f, flcn::constants::NaN),
                                               flcn::Vec2<float>(flcn::constants::NaN, flcn::constants::NaN)));
} // namespace



/**************************************
 *          PROJECTION TESTS          *
 **************************************/

TYPED_TEST(Vec2ProjectionTests, Project_OrthogonalVectorsReturnsZeroVector)
{
    const flcn::Vec2 actualProjection = this->_perpendicularVec.project(this->_ontoVec);
    EXPECT_VEC_ZERO(actualProjection);
}


TEST(Vec2ProjectionTests, Project_XAxis_ReturnVectorWithNonZeroXComponent)
{
    // Given an arbitrary vector
    const flcn::Vec2 a(10.0f, 20.0f);
    const flcn::Vec2 xAxis(1.0f, 0.0f);
    const flcn::Vec2 expectedProjection(10.0f, 0.0f);

    // When projected onto x-axis
    const flcn::Vec2 actualProjection = a.project(xAxis);

    // Then, the resultant vector only has x-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


TEST(Vec2ProjectionTests, Project_YAxis_ReturnVectorWithNonZeroYComponent)
{
    // Given an arbitrary vector
    const flcn::Vec2 a(10.0f, 20.0f);
    const flcn::Vec2 yAxis(0.0f, 1.0f);
    const flcn::Vec2 expectedProjection(0.0f, 20.0f);

    // When projected onto y-axis
    const flcn::Vec2 actualProjection = a.project(yAxis);

    // Then, the resultant vector only has y-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


TYPED_TEST(Vec2ProjectionTests, Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const flcn::Vec2 actualProjection = this->_vec.project(this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


TYPED_TEST(Vec2ProjectionTests, StaticWrapper_Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const auto actualProjection = flcn::Vec2<TypeParam>::project(this->_vec, this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


TEST(Vec2ProjectionTests, ProjectNorm_NormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec2 a(1.0f, 2.0f);
    const flcn::Vec2 b(1.0f, 0.0f);
    const flcn::Vec2 expectedProjection(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::Vec2 actualProjection = a.projectNorm(b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref flcn::Vec2::project returns a non-zero vector.
 */
TEST(Vec2ProjectionTests, ProjectionOntoVectorInOppositeDirectionReturnsNonZeroVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::Vec2 a(4.0f, 4.0f);
    const flcn::Vec2 negativeYAxis(0.0f, -1.0f);
    const flcn::Vec2 expectedProjection(0.0f, 4.0f);

    // When projected
    const flcn::Vec2<float> actualProjection = a.project(negativeYAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}




/**
 * @test Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref flcn::Vec2::projectNorm returns a non-zero vector.
 */
TEST(Vec2ProjectionTests, StaticWrapper_ProjectNorm_NormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec2 a(1.0f, 2.0f);
    const flcn::Vec2 b(1.0f, 0.0f);
    const flcn::Vec2 expectedProjection(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::Vec2 actualProjection = flcn::Vec2<float>::projectNorm(a, b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}





/**************************************
 *        SAFE PROJECTION TESTS       *
 **************************************/

TYPED_TEST(Vec2ProjectionTests, SafeProject_Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const flcn::Vec2 actualProjection = this->_vec.safeProject(this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}



TEST(Vec2ProjectionTests, SafeProjectNorm_NormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec2 a(1.0f, 2.0f);
    const flcn::Vec2 b(1.0f, 0.0f);
    const flcn::Vec2 expectedProjection(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::Vec2 actualProjection = a.safeProjectNorm(b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


TEST(Vec2ProjectionTests, SafeProjectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector and a normalized vector
    const flcn::Vec2 a(1.0f, flcn::constants::NaN);
    const flcn::Vec2 b(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::Vec2 actualProjection = a.safeProjectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


TEST(Vec2ProjectionTests, SafeProjectNorm_OntoNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec2 a(1.0f, 2.0f);
    const flcn::Vec2 b(1.0f, flcn::constants::NaN);

    // When the vector is projected onto the normalized vector
    const flcn::Vec2 actualProjection = a.safeProjectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


TEST(Vec2ProjectionTests, SafeProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::Vec2 a(4.0f, 4.0f);
    const flcn::Vec2 negativeYAxis(0.0f, -1.0f);
    const flcn::Vec2 expectedProjection(0.0f, 4.0f);

    // When projected
    const flcn::Vec2<float> actualProjection = a.safeProject(negativeYAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


TYPED_TEST(Vec2ProjectionTests, SafeProject_OntoZeroReturnsZeroVector)
{
    const flcn::Vec2 zeroVec = flcn::Vec2<TypeParam>::zero();

    const flcn::Vec2 actualProjection = this->_vec.safeProject(zeroVec);

    EXPECT_VEC_ZERO(actualProjection);
}


TYPED_TEST(Vec2ProjectionTests, StaticWrapper_SafeProject_Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const flcn::Vec2 actualProjection = flcn::Vec2<TypeParam>::safeProject(this->_vec, this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


TEST(Vec2ProjectionTests, StaticWrapper_SafeProjectNorm_NormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec2 a(1.0f, 2.0f);
    const flcn::Vec2 b(1.0f, 0.0f);
    const flcn::Vec2 expectedProjection(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::Vec2 actualProjection = flcn::Vec2<float>::safeProjectNorm(a, b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


TEST(Vec2ProjectionTests, StaticWrapper_SafeProjectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector
    const flcn::Vec2 a(1.0f, flcn::constants::NaN);
    const flcn::Vec2 b(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::Vec2 actualProjection = flcn::Vec2<float>::safeProjectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


TEST(Vec2ProjectionTests, StaticWrapper_SafeProjectNorm_OntoNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector
    const flcn::Vec2 a(1.0f, 2.0f);
    const flcn::Vec2 b(1.0f, flcn::constants::NaN);

    // When the vector is from a NaN vector
    const flcn::Vec2 actualProjection = flcn::Vec2<float>::safeProjectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


TEST(Vec2ProjectionTests, StaticWrapper_SafeProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::Vec2 a(4.0f, 4.0f);
    const flcn::Vec2 negativeYAxis(0.0f, -1.0f);
    const flcn::Vec2 expectedProjection(0.0f, 4.0f);

    // When projected
    const flcn::Vec2<float> actualProjection = flcn::Vec2<float>::safeProject(a, negativeYAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


TYPED_TEST(Vec2ProjectionTests, StaticWrapper_SafeProject_OntoZeroVectorReturnsZeroVector)
{
    const flcn::Vec2 zeroVec = flcn::Vec2<TypeParam>::zero();
    const flcn::Vec2 actualProjection = flcn::Vec2<TypeParam>::safeProject(this->_vec, zeroVec);
    EXPECT_VEC_ZERO(actualProjection);
}


TEST_P(Vec2ProjectionNaNTests, SafeProject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::Vec2<float>::one();

    EXPECT_VEC_ZERO(nanVec.safeProject(ontoVec));
}


TEST_P(Vec2ProjectionNaNTests, SafeProject_OntoNaNVectorReturnsZeroVector)
{
    const auto& oneVec     = flcn::Vec2<float>::one();
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(oneVec.safeProject(ontoNaNVec));
}


TEST_P(Vec2ProjectionNaNTests, StaticWrapper_SafeProject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::Vec2<float>::one();

    EXPECT_VEC_ZERO(flcn::Vec2<float>::safeProject(nanVec, ontoVec));
}


TEST_P(Vec2ProjectionNaNTests, StaticWrapper_SafeProject_OntoNaNVectorReturnsZeroVector)
{
    const auto& oneVec     = flcn::Vec2<float>::one();
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(flcn::Vec2<float>::safeProject(oneVec, ontoNaNVec));
}



/**************************************
 *         TRY PROJECTION TESTS       *
 **************************************/

/**
 * @test Verify that projecting onto an orthogonal vector using @ref flcn::Vec2::tryProject
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec2ProjectionTests, TryProject_Project_NonOrthogonalVectors_ReturnsNonZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Vec2 actualProjection = this->_vec.tryProject(this->_ontoVec, flag);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using @ref flcn::Vec2::tryProjectNorm
 *       returns a non-zero vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec2ProjectionTests, TryProject_NormalizedVectorReturnsNonZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec2 a(1.0f, 2.0f);
    const flcn::Vec2 b(1.0f, 0.0f);
    const flcn::Vec2 expectedProjection(1.0f, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const flcn::Vec2 actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting a NaN vector onto a non-orthogonal unit vector using @ref flcn::Vec2::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec2ProjectionTests, TryProjectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec2 a(flcn::constants::NaN, 2.0f);
    const flcn::Vec2 b(1.0f, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const flcn::Vec2 actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projecting a vector onto a NaN vector using @ref flcn::Vec2::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec2ProjectionTests, TryProjectNorm_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec2 a(1.0f, 2.0f);
    const flcn::Vec2 b(1.0f, flcn::constants::NaN);
    flcn::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const flcn::Vec2 actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref flcn::Vec2::tryProject returns a non-zero vector
 *       and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec2ProjectionTests, TryProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirectionAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::Vec2 a(4.0f, 4.0f);
    const flcn::Vec2 negativeYAxis(0.0f, -1.0f);
    const flcn::Vec2 expectedProjection(0.0f, 4.0f);
    flcn::OperationStatus flag;

    // When projected
    const flcn::Vec2<float> actualProjection = a.tryProject(negativeYAxis, flag);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a zero length vector using @ref flcn::Vec2::tryProject
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec2ProjectionTests, TryProject_OntoZeroReturnsZeroVectorAndSetsCorrectFlag)
{
    const flcn::Vec2 zeroVec = flcn::Vec2<TypeParam>::zero();
    flcn::OperationStatus flag;


    const flcn::Vec2 actualProjection = this->_vec.tryProject(zeroVec, flag);

    EXPECT_VEC_ZERO(actualProjection);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector using static variant of @ref flcn::Vec2::tryProject
 *       returns a non-zero vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec2ProjectionTests, StaticWrapper_TryProject_Project_NonOrthogonalVectors_ReturnsNonZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Vec2 actualProjection = flcn::Vec2<TypeParam>::tryProject(this->_vec, this->_ontoVec, flag);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref flcn::Vec2::tryProjectNorm returns a non-zero vector and sets the flag to
 *       @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec2ProjectionTests, StaticWrapper_TryProjectNorm_NormalizedVectorReturnsNonZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec2 a(1.0f, 2.0f);
    const flcn::Vec2 b(1.0f, 0.0f);
    const flcn::Vec2 expectedProjection(1.0f, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const flcn::Vec2 actualProjection = flcn::Vec2<float>::tryProjectNorm(a, b, flag);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting a NaN vector onto a non-orthogonal unit vector using static variant of @ref
 * flcn::Vec2::tryProjectNorm returns a zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec2ProjectionTests, StaticWrapper_TryProjectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a NaN vector
    const flcn::Vec2 a(flcn::constants::NaN, 2.0f);
    const flcn::Vec2 b(1.0f, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the NaN vector
    const flcn::Vec2 actualProjection = flcn::Vec2<float>::tryProjectNorm(a, b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/**
 * @test Verify that projecting a vector onto a NaN vector using static variant of @ref flcn::Vec2::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec2ProjectionTests, StaticWrapper_TryProjectNorm_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a NaN vector
    const flcn::Vec2 a(1.0f, 2.0f);
    const flcn::Vec2 b(1.0f, flcn::constants::NaN);
    flcn::OperationStatus flag;

    // When the vector is projected onto the NaN vector
    const flcn::Vec2 actualProjection = flcn::Vec2<float>::tryProjectNorm(a, b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using static variant of @ref flcn::Vec2::tryProject returns a non-zero vector
 *       and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec2ProjectionTests,
     StaticWrapper_TryProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirectionAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::Vec2 a(4.0f, 4.0f);
    const flcn::Vec2 negativeYAxis(0.0f, -1.0f);
    const flcn::Vec2 expectedProjection(0.0f, 4.0f);
    flcn::OperationStatus flag;

    // When projected
    const flcn::Vec2<float> actualProjection = flcn::Vec2<float>::tryProject(a, negativeYAxis, flag);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a zero length vector using static variant of @ref flcn::Vec2::tryProject
 *        returns a type-promoted vector and sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec2ProjectionTests, StaticWrapper_TryProject_OntoZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const flcn::Vec2 zeroVec = flcn::Vec2<TypeParam>::zero();
    flcn::OperationStatus flag;

    const flcn::Vec2 actualProjection = flcn::Vec2<TypeParam>::tryProject(this->_vec, zeroVec, flag);

    EXPECT_VEC_ZERO(actualProjection);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}



/**
 * @test Verify that projection of NaN vector using @ref flcn::Vec2::tryProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec2ProjectionNaNTests, TryProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::Vec2<float>::one();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(nanVec.tryProject(ontoVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projection onto NaN vector using @ref flcn::Vec2::tryProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec2ProjectionNaNTests, TryProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::Vec2<float>::one();
    const auto& ontoNaNVec = GetParam();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(oneVec.tryProject(ontoNaNVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projection of NaN vector using static variant of @ref flcn::Vec2::tryProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec2ProjectionNaNTests, StaticWrapper_TryProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::Vec2<float>::one();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(flcn::Vec2<float>::tryProject(nanVec, ontoVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projection onto NaN vector using static variant of @ref flcn::Vec2::tryProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec2ProjectionNaNTests, StaticWrapper_TryProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::Vec2<float>::one();
    const auto& ontoNaNVec = GetParam();
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::Vec2<float>::tryProject(oneVec, ontoNaNVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/** @} */
