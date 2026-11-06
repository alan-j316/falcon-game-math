/**
 * @file ProjectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref flcn::Vec3 projection logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"


/**
 * @addtogroup T_FALCON_Vec3_Proj
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Vec3 projection.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class Vec3ProjectionTests: public ::testing::Test
    {
    protected:
        flcn::Vec3<T> _vec;
        flcn::Vec3<T> _perpendicularVec;
        flcn::Vec3<T> _ontoVec;
        flcn::Vec3<T> _expectedProjection;

        void SetUp() override
        {
            _vec                = { T(4), T(9), T(0) };
            _perpendicularVec   = { T(0), T(0), T(11) };
            _ontoVec            = { T(0), T(2), T(0) };
            _expectedProjection = { T(0), T(9), T(0) };
        }
    };
    TYPED_TEST_SUITE(Vec3ProjectionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::Vec3 projection with NaN vectors.
     */
    class Vec3ProjectionNaNTests: public testing::TestWithParam<flcn::Vec3<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Vec3ProjectionNanVectors, Vec3ProjectionNaNTests,
                             ::testing::Values(flcn::Vec3<float>(flcn::constants::NaN, 1.0f, 1.0f),
                                               flcn::Vec3<float>(1.0f, flcn::constants::NaN, 1.0f),
                                               flcn::Vec3<float>(1.0f, 1.0f, flcn::constants::NaN),
                                               flcn::Vec3<float>(flcn::constants::NaN, flcn::constants::NaN,
                                                                flcn::constants::NaN)));




    /**************************************
     *           STATIC TESTS             *
     **************************************/
    namespace static_tests
    {
        constexpr flcn::Vec3 VEC_A(1, 2, 3);
        constexpr flcn::Vec3 VEC_B(1, 0, 0);

        /// @test Verify that vector projection(project) returns a valid vector at compile time.
        constexpr auto PROJ_VEC = VEC_A.project(VEC_B);
        static_assert(PROJ_VEC.x() == 1);
        static_assert(PROJ_VEC.y() == 0);
        static_assert(PROJ_VEC.z() == 0);

        /// @test Verify that vector projection(project-static wrapper) returns a valid vector at compile time.
        constexpr auto PROJ_VEC_STATIC = flcn::Vec3<int>::project(VEC_A, VEC_B);
        static_assert(PROJ_VEC_STATIC.x() == 1);
        static_assert(PROJ_VEC_STATIC.y() == 0);
        static_assert(PROJ_VEC_STATIC.z() == 0);

        /// @test Verify that vector projection(project normalized) returns a valid vector at compile time.
        constexpr auto PROJ_NORM_VEC = VEC_A.projectNorm(VEC_B);
        static_assert(PROJ_NORM_VEC.x() == 1);
        static_assert(PROJ_NORM_VEC.y() == 0);
        static_assert(PROJ_NORM_VEC.z() == 0);

        /// @test Verify that vector projection(project normalized-static wrapper) returns a valid vector at compile
        /// time.
        constexpr auto PROJ_NORM_VEC_STATIC = flcn::Vec3<int>::projectNorm(VEC_A, VEC_B);
        static_assert(PROJ_NORM_VEC_STATIC.x() == 1);
        static_assert(PROJ_NORM_VEC_STATIC.y() == 0);
        static_assert(PROJ_NORM_VEC_STATIC.z() == 0);

        /// @test Verify that vector projection(safe project) returns a valid vector at compile time.
        constexpr auto SAFE_PROJ_VEC = VEC_A.safeProject(VEC_B);
        static_assert(SAFE_PROJ_VEC.x() == 1);
        static_assert(SAFE_PROJ_VEC.y() == 0);
        static_assert(SAFE_PROJ_VEC.z() == 0);

        /// @test Verify that vector projection(safe project-static wrapper) returns a valid vector at compile time.
        constexpr auto SAFE_PROJ_VEC_STATIC = flcn::Vec3<int>::safeProject(VEC_A, VEC_B);
        static_assert(SAFE_PROJ_VEC_STATIC.x() == 1);
        static_assert(SAFE_PROJ_VEC_STATIC.y() == 0);
        static_assert(SAFE_PROJ_VEC_STATIC.z() == 0);

        /// @test Verify that vector projection(safe project normalized) returns a valid vector at compile time.
        constexpr auto SAFE_PROJ_NORM_VEC = VEC_A.safeProjectNorm(VEC_B);
        static_assert(SAFE_PROJ_NORM_VEC.x() == 1);
        static_assert(SAFE_PROJ_NORM_VEC.y() == 0);
        static_assert(SAFE_PROJ_NORM_VEC.z() == 0);

        /// @test Verify that vector projection(safe project normalized-static wrapper) returns a valid vector at
        /// compile time.
        constexpr auto SAFE_PROJ_NORM_VEC_STATIC = flcn::Vec3<int>::safeProjectNorm(VEC_A, VEC_B);
        static_assert(SAFE_PROJ_NORM_VEC_STATIC.x() == 1);
        static_assert(SAFE_PROJ_NORM_VEC_STATIC.y() == 0);
        static_assert(SAFE_PROJ_NORM_VEC_STATIC.z() == 0);
    } // namespace static_tests

} // namespace



/**************************************
 *          PROJECTION TESTS          *
 **************************************/

/** @test Verify that projecting onto an orthogonal vector using @ref flcn::Vec3::project returns a zero vector. */
TYPED_TEST(Vec3ProjectionTests, OrthogonalVectorsReturnsZeroVector)
{
    const flcn::Vec3 actualProjection = this->_perpendicularVec.project(this->_ontoVec);

    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @test Verify that projecting onto a vector parallel to x-axis using @ref flcn::Vec3::project
 *       returns a vector containing only an x-component.
 */
TEST(Vec3ProjectionTests, Project_XAxis_ReturnVectorWithNonZeroXComponent)
{
    // Given an arbitrary vector
    const flcn::Vec3 a(10.0f, 20.0f, 30.0f);
    const flcn::Vec3 xAxis(1.0f, 0.0f, 0.0f);
    const flcn::Vec3 expectedProjection(10.0f, 0.0f, 0.0f);

    // When projected onto x-axis
    const flcn::Vec3 actualProjection = a.project(xAxis);

    // Then, the resultant vector only has x-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a vector parallel to y-axis using @ref flcn::Vec3::project
 *       returns a vector containing only a y-component.
 */
TEST(Vec3ProjectionTests, Project_YAxis_ReturnVectorWithNonZeroYComponent)
{
    // Given an arbitrary vector
    const flcn::Vec3 a(10.0f, 20.0f, 30.0f);
    const flcn::Vec3 yAxis(0.0f, 1.0f, 0.0f);
    const flcn::Vec3 expectedProjection(0.0f, 20.0f, 0.0f);

    // When projected onto y-axis
    const flcn::Vec3 actualProjection = a.project(yAxis);

    // Then, the resultant vector only has y-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a vector parallel to z-axis using @ref flcn::Vec3::project
 *       returns a vector containing only a z-component.
 */
TEST(Vec3ProjectionTests, Project_ZAxis_ReturnVectorWithNonZeroZComponent)
{
    // Given an arbitrary vector
    const flcn::Vec3 a(10.0f, 20.0f, 30.0f);
    const flcn::Vec3 zAxis(0.0f, 0.0f, 1.0f);
    const flcn::Vec3 expectedProjection(0.0f, 0.0f, 30.0f);

    // When projected onto z-axis
    const flcn::Vec3 actualProjection = a.project(zAxis);

    // Then, the resultant vector only has z-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector using @ref flcn::Vec3::project
 *       returns a non-zero vector.
 */
TYPED_TEST(Vec3ProjectionTests, Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const flcn::Vec3 actualProjection = this->_vec.project(this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector using static variant of @ref flcn::Vec3::project
 *       returns a non-zero vector.
 */
TYPED_TEST(Vec3ProjectionTests, StaticWrapper_Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const flcn::Vec3 actualProjection = flcn::Vec3<TypeParam>::project(this->_vec, this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using @ref flcn::Vec3::projectNorm
 *       returns a non-zero vector.
 */
TEST(Vec3ProjectionTests, ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::Vec3 b(1.0f, 0.0f, 0.0f);
    const flcn::Vec3 expectedProjection(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::Vec3 actualProjection = a.projectNorm(b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref flcn::Vec3::project returns a non-zero vector.
 */
TEST(Vec3ProjectionTests, ProjectionOntoVectorInOppositeDirectionReturnsNonZeroVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::Vec3 a(4.0f, 4.0f, 4.0f);
    const flcn::Vec3 negativeZAxis(0.0f, 0.0f, -1.0f);
    const flcn::Vec3 expectedProjection(0.0f, 0.0f, 4.0f);

    // When projected
    const flcn::Vec3<float> actualProjection = a.project(negativeZAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using @ref flcn::Vec3::project returns a type-promoted vector.
 */
TEST(Vec3ProjectionTests, MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const flcn::Vec3 vec(7, 13, 29);
    const flcn::Vec3 onto(2.0, 4.0, 4.0);
    const flcn::Vec3 expectedProjection(10.111111111111111, 20.222222222222222, 20.222222222222222);

    // When projected onto another
    const flcn::Vec3 actualProjection = vec.project(onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref flcn::Vec3::projectNorm returns a non-zero vector.
 */
TEST(Vec3ProjectionTests, StaticWrapper_ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::Vec3 b(1.0f, 0.0f, 0.0f);
    const flcn::Vec3 expectedProjection(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::Vec3 actualProjection = flcn::Vec3<float>::projectNorm(a, b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/** @test Verify that projection using @ref flcn::Vec3::project always return floating-point vector. */
TYPED_TEST(Vec3ProjectionTests, Project_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::Vec3 projection = this->_vec.project(this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @test Verify that projection using static variant of @ref flcn::Vec3::project
 *       always return floating-point vector.
 */
TYPED_TEST(Vec3ProjectionTests, StaticWrapper_Project_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::Vec3 projection = flcn::Vec3<TypeParam>::project(this->_vec, this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}



/**************************************
 *        SAFE PROJECTION TESTS       *
 **************************************/

/**
 * @test Verify that projecting onto an orthogonal vector using @ref flcn::Vec3::safeProject
 *       returns a zero vector.
 */
TYPED_TEST(Vec3ProjectionTests, SafeProject_Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const flcn::Vec3 actualProjection = this->_vec.safeProject(this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using @ref flcn::Vec3::safeProjectNorm
 *       returns a non-zero vector.
 */
TEST(Vec3ProjectionTests, SafeProjectNorm_ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::Vec3 b(1.0f, 0.0f, 0.0f);
    const flcn::Vec3 expectedProjection(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::Vec3 actualProjection = a.safeProject(b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting a NaN vector onto a non-orthogonal unit vector using @ref
 * flcn::Vec3::safeProjectNorm returns a zero vector.
 */
TEST(Vec3ProjectionTests, SafeProjectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector and a normalized vector
    const flcn::Vec3 a(1.0f, 2.0f, flcn::constants::NaN);
    const flcn::Vec3 b(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::Vec3 actualProjection = a.safeProjectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @test Verify that projecting a NaN vector onto a non-orthogonal unit vector using @ref
 * flcn::Vec3::safeProjectNorm returns a zero vector.
 */
TEST(Vec3ProjectionTests, SafeProjectNorm_OntoNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::Vec3 b(1.0f, 1.0f, flcn::constants::NaN);

    // When the vector is projected onto the normalized vector
    const flcn::Vec3 actualProjection = a.safeProjectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref flcn::Vec3::safeProject returns a non-zero vector.
 */
TEST(Vec3ProjectionTests, SafeProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::Vec3 a(4.0f, 4.0f, 4.0f);
    const flcn::Vec3 negativeZAxis(0.0f, 0.0f, -1.0f);
    const flcn::Vec3 expectedProjection(0.0f, 0.0f, 4.0f);

    // When projected
    const flcn::Vec3<float> actualProjection = a.safeProject(negativeZAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using @ref flcn::Vec3::safeProject returns a type-promoted vector.
 */
TEST(Vec3ProjectionTests, SafeProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const flcn::Vec3 vec(7, 13, 29);
    const flcn::Vec3 onto(2.0, 4.0, 4.0);
    const flcn::Vec3 expectedProjection(10.111111111111111, 20.222222222222222, 20.222222222222222);

    // When projected onto another
    const flcn::Vec3 actualProjection = vec.safeProject(onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a zero length vector using @ref flcn::Vec3::safeProject
 *       returns a zero vector.
 */
TYPED_TEST(Vec3ProjectionTests, SafeProject_OntoZeroReturnsZeroVector)
{
    const flcn::Vec3 zeroVec = flcn::Vec3<TypeParam>::zero();

    const flcn::Vec3 actualProjection = this->_vec.safeProject(zeroVec);

    EXPECT_VEC_ZERO(actualProjection);
}

/**
 * @test Verify that projecting onto a non-orthogonal vector using static variant of @ref flcn::Vec3::safeProject
 *       returns a non-zero vector.
 */
TYPED_TEST(Vec3ProjectionTests, StaticWrapper_SafeProject_Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const flcn::Vec3 actualProjection = flcn::Vec3<TypeParam>::safeProject(this->_vec, this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref flcn::Vec3::safeProjectNorm returns a non-zero vector.
 */
TEST(Vec3ProjectionTests, StaticWrapper_SafeProjectNorm_ProjectionOntoNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::Vec3 b(1.0f, 0.0f, 0.0f);
    const flcn::Vec3 expectedProjection(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::Vec3 actualProjection = flcn::Vec3<float>::safeProjectNorm(a, b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}



/**
 * @test Verify that projecting a NaN vector onto a non-orthogonal unit vector using static variant of
 *       @ref flcn::Vec3::safeProjectNorm returns a zero vector.
 */
TEST(Vec3ProjectionTests, StaticWrapper_SafeProjectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector and a normalized vector
    const flcn::Vec3 a(1.0f, 2.0f, flcn::constants::NaN);
    const flcn::Vec3 b(1.0f, 0.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::Vec3 actualProjection = flcn::Vec3<float>::safeProjectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


/**
 * @test Verify that projecting a NaN vector onto a non-orthogonal unit vector using static variant of
 *       @ref flcn::Vec3::safeProjectNorm returns a zero vector.
 */
TEST(Vec3ProjectionTests, StaticWrapper_SafeProjectNorm_OntoNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::Vec3 b(1.0f, 1.0f, flcn::constants::NaN);

    // When the vector is projected onto the normalized vector
    const flcn::Vec3 actualProjection = flcn::Vec3<float>::safeProjectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}

/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using static variant of @ref flcn::Vec3::safeProject returns a non-zero vector.
 */
TEST(Vec3ProjectionTests, StaticWrapper_SafeProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::Vec3 a(4.0f, 4.0f, 4.0f);
    const flcn::Vec3 negativeZAxis(0.0f, 0.0f, -1.0f);
    const flcn::Vec3 expectedProjection(0.0f, 0.0f, 4.0f);

    // When projected
    const flcn::Vec3<float> actualProjection = flcn::Vec3<float>::safeProject(a, negativeZAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using static variant of @ref flcn::Vec3::safeProject returns a type-promoted vector.
 */
TEST(Vec3ProjectionTests, StaticWrapper_SafeProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const flcn::Vec3 vec(7, 13, 29);
    const flcn::Vec3 onto(2.0, 4.0, 4.0);
    const flcn::Vec3 expectedProjection(10.111111111111111, 20.222222222222222, 20.222222222222222);

    // When projected onto another
    const flcn::Vec3 actualProjection = flcn::Vec3<int>::safeProject(vec, onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a zero length vector using static variant of @ref flcn::Vec3::safeProject
 *       returns a type-promoted vector.
 */
TYPED_TEST(Vec3ProjectionTests, StaticWrapper_SafeProject_OntoZeroVectorReturnsZeroVector)
{
    const flcn::Vec3 zeroVec = flcn::Vec3<TypeParam>::zero();

    const flcn::Vec3 actualProjection = flcn::Vec3<TypeParam>::safeProject(this->_vec, zeroVec);

    EXPECT_VEC_ZERO(actualProjection);
}


/** @test Verify that projection using @ref flcn::Vec3::safeProject always return floating-point vector. */
TYPED_TEST(Vec3ProjectionTests, SafeProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::Vec3 projection = this->_vec.safeProject(this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @test Verify that projection using static variant of @ref flcn::Vec3::safeProject
 *       always return floating-point vector.
 */
TYPED_TEST(Vec3ProjectionTests, StaticWrapper_SafeProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::Vec3 projection = flcn::Vec3<TypeParam>::safeProject(this->_vec, this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @test Verify that projection of NaN vector using @ref flcn::Vec3::safeProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec3ProjectionNaNTests, SafeProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::Vec3<float>::one();

    EXPECT_VEC_ZERO(nanVec.safeProject(ontoVec));
}


/**
 * @test Verify that projection onto NaN vector using @ref flcn::Vec3::safeProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec3ProjectionNaNTests, SafeProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::Vec3<float>::one();
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(oneVec.safeProject(ontoNaNVec));
}


/**
 * @test Verify that projection of NaN vector using static variant of @ref flcn::Vec3::safeProject
 *       returns zero vector.
 */
TEST_P(Vec3ProjectionNaNTests, StaticWrapper_SafeProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::Vec3<float>::one();

    EXPECT_VEC_ZERO(flcn::Vec3<float>::safeProject(nanVec, ontoVec));
}


/**
 * @test Verify that projection onto NaN vector using static variant of @ref flcn::Vec3::safeProject
 *       returns zero vector.
 */
TEST_P(Vec3ProjectionNaNTests, StaticWrapper_SafeProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::Vec3<float>::one();
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(flcn::Vec3<float>::safeProject(oneVec, ontoNaNVec));
}


/**************************************
 *         TRY PROJECTION TESTS       *
 **************************************/

/**
 * @test Verify that projecting onto an orthogonal vector using @ref flcn::Vec3::tryProject
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec3ProjectionTests, TryProject_Project_NonOrthogonalVectors_ReturnsNonZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Vec3 actualProjection = this->_vec.tryProject(this->_ontoVec, flag);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}
/**
 * @test Verify that projecting onto a non-orthogonal unit vector using @ref flcn::Vec3::tryProject
 *       returns a non-zero vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec3ProjectionTests, TryProjectNorm_ProjectionOntoNormalizedVectorReturnsNonZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::Vec3 b(1.0f, 0.0f, 0.0f);
    const flcn::Vec3 expectedProjection(1.0f, 0.0f, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const flcn::Vec3 actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting a NaN vector onto a non-orthogonal unit vector using @ref flcn::Vec3::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec3ProjectionTests, TryProjectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec3 a(flcn::constants::NaN, 2.0f, 3.0f);
    const flcn::Vec3 b(1.0f, 0.0f, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const flcn::Vec3 actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/**
 * @test Verify that projecting a vector onto a NaN vector using @ref flcn::Vec3::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec3ProjectionTests, TryProjectNorm_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::Vec3 b(1.0f, flcn::constants::NaN, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const flcn::Vec3 actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref flcn::Vec3::tryProject returns a non-zero vector
 *       and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec3ProjectionTests, TryProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirectionAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::Vec3 a(4.0f, 4.0f, 4.0f);
    const flcn::Vec3 negativeZAxis(0.0f, 0.0f, -1.0f);
    const flcn::Vec3 expectedProjection(0.0f, 0.0f, 4.0f);
    flcn::OperationStatus flag;

    // When projected
    const flcn::Vec3<float> actualProjection = a.tryProject(negativeZAxis, flag);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using @ref flcn::Vec3::tryProject returns a type-promoted vector
 *       and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec3ProjectionTests, TryProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const flcn::Vec3 vec(7, 13, 29);
    const flcn::Vec3 onto(2.0, 4.0, 4.0);
    const flcn::Vec3 expectedProjection(10.111111111111111, 20.222222222222222, 20.222222222222222);
    flcn::OperationStatus flag;

    // When projected onto another
    const flcn::Vec3 actualProjection = vec.tryProject(onto, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a zero length vector using @ref flcn::Vec3::tryProject
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec3ProjectionTests, TryProject_OntoZeroReturnsZeroVectorAndSetsCorrectFlag)
{
    const flcn::Vec3 zeroVec = flcn::Vec3<TypeParam>::zero();
    flcn::OperationStatus flag;


    const flcn::Vec3 actualProjection = this->_vec.tryProject(zeroVec, flag);

    EXPECT_VEC_ZERO(actualProjection);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector using static variant of @ref flcn::Vec3::tryProject
 *       returns a non-zero vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec3ProjectionTests,
           StaticWrapper_TryProject_Project_NonOrthogonalVectors_ReturnsNonZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::Vec3 actualProjection = flcn::Vec3<TypeParam>::tryProject(this->_vec, this->_ontoVec, flag);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref flcn::Vec3::tryProject returns a non-zero vector and sets the flag to
 *       @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec3ProjectionTests, StaticWrapper_TryProject_ProjectionOntoNormalizedVectorReturnsNonZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::Vec3 b(1.0f, 0.0f, 0.0f);
    const flcn::Vec3 expectedProjection(1.0f, 0.0f, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const flcn::Vec3 actualProjection = flcn::Vec3<float>::tryProject(a, b, flag);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}



/**
 * @test Verify that projecting a NaN vector onto a non-orthogonal unit vector using static variant of @ref
 * flcn::Vec3::tryProjectNorm returns a zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec3ProjectionTests, StaticWrapper_TryProjectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a NaN vector
    const flcn::Vec3 a(flcn::constants::NaN, 2.0f, 3.0f);
    const flcn::Vec3 b(1.0f, 0.0f, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the NaN vector
    const flcn::Vec3 actualProjection = flcn::Vec3<float>::tryProjectNorm(a, b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/**
 * @test Verify that projecting a vector onto a NaN vector using static variant of @ref flcn::Vec3::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec3ProjectionTests, StaticWrapper_TryProjectNorm_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a NaN vector
    const flcn::Vec3 a(1.0f, 2.0f, 3.0f);
    const flcn::Vec3 b(1.0f, flcn::constants::NaN, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the NaN vector
    const flcn::Vec3 actualProjection = flcn::Vec3<float>::tryProjectNorm(a, b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}



/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using static variant of @ref flcn::Vec3::tryProject returns a non-zero vector
 *       and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec3ProjectionTests,
     StaticWrapper_TryProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirectionAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::Vec3 a(4.0f, 4.0f, 4.0f);
    const flcn::Vec3 negativeZAxis(0.0f, 0.0f, -1.0f);
    const flcn::Vec3 expectedProjection(0.0f, 0.0f, 4.0f);
    flcn::OperationStatus flag;

    // When projected
    const flcn::Vec3<float> actualProjection = flcn::Vec3<float>::tryProject(a, negativeZAxis, flag);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using static variant of @ref flcn::Vec3::tryProject returns a type-promoted vector
 *       and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec3ProjectionTests, StaticWrapper_TryProject_MixedTypeProjectionPromotesTypeAndSetsCorrectFlag)
{
    // Given two arbitrary vectors
    const flcn::Vec3 vec(7, 13, 29);
    const flcn::Vec3 onto(2.0, 4.0, 4.0);
    const flcn::Vec3 expectedProjection(10.111111111111111, 20.222222222222222, 20.222222222222222);
    flcn::OperationStatus flag;

    // When projected onto another
    const flcn::Vec3 actualProjection = flcn::Vec3<int>::tryProject(vec, onto, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a zero length vector using static variant of @ref flcn::Vec3::tryProject
 *       returns a type-promoted vector and sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec3ProjectionTests, StaticWrapper_TryProject_OntoZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const flcn::Vec3 zeroVec = flcn::Vec3<TypeParam>::zero();
    flcn::OperationStatus flag;

    const flcn::Vec3 actualProjection = flcn::Vec3<TypeParam>::tryProject(this->_vec, zeroVec, flag);

    EXPECT_VEC_ZERO(actualProjection);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/** @test Verify that projection using @ref flcn::Vec3::tryProject always return floating-point vector. */
TYPED_TEST(Vec3ProjectionTests, TryProject_AlwaysReturnFloatingPointVectorAndSetsCorrectFlag)
{
    [[maybe_unused]] flcn::OperationStatus flag;
    [[maybe_unused]] const flcn::Vec3 projection = this->_vec.tryProject(this->_ontoVec, flag);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @test Verify that projection using static variant of @ref flcn::Vec3::tryProject
 *       always return floating-point vector.
 */
TYPED_TEST(Vec3ProjectionTests, StaticWrapper_TryProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] flcn::OperationStatus flag;
    [[maybe_unused]] const flcn::Vec3 projection = flcn::Vec3<TypeParam>::tryProject(this->_vec, this->_ontoVec, flag);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @test Verify that projection of NaN vector using @ref flcn::Vec3::tryProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec3ProjectionNaNTests, TryProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::Vec3<float>::one();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(nanVec.tryProject(ontoVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projection onto NaN vector using @ref flcn::Vec3::tryProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec3ProjectionNaNTests, TryProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::Vec3<float>::one();
    const auto& ontoNaNVec = GetParam();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(oneVec.tryProject(ontoNaNVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projection of NaN vector using static variant of @ref flcn::Vec3::tryProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec3ProjectionNaNTests, StaticWrapper_TryProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::Vec3<float>::one();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(flcn::Vec3<float>::tryProject(nanVec, ontoVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projection onto NaN vector using static variant of @ref flcn::Vec3::tryProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec3ProjectionNaNTests, StaticWrapper_TryProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::Vec3<float>::one();
    const auto& ontoNaNVec = GetParam();
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::Vec3<float>::tryProject(oneVec, ontoNaNVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/** @} */
