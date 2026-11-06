/**
 * @file ProjectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref flcn::CVec2 projection logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CVec2TestSetup.h"



/**
 * @addtogroup T_FALCON_CVec2_Proj
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::CVec2 projection.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class CVec2ProjectionTests: public testing::Test
    {
    protected:
        flcn::CVec2<T> _vec;
        flcn::CVec2<T> _perpendicularVec;
        flcn::CVec2<T> _ontoVec;
        flcn::CVec2<T> _expectedProjection;

        void SetUp() override
        {
            _vec                = { T(4), T(0) };
            _perpendicularVec   = { T(0), T(11) };
            _ontoVec            = { T(2), T(0) };
            _expectedProjection = { T(4), T(0) };
        }
    };
    TYPED_TEST_SUITE(CVec2ProjectionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::CVec2 projection with NaN vectors.
     */
    class CVec2ProjectionNaNTests: public testing::TestWithParam<flcn::CVec2<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(CVec2ProjectionNanVectors, CVec2ProjectionNaNTests,
                             ::testing::Values(flcn::CVec2<float>(flcn::constants::NaN, 1.0f),
                                               flcn::CVec2<float>(1.0f, flcn::constants::NaN),
                                               flcn::CVec2<float>(flcn::constants::NaN, flcn::constants::NaN)));



    /**************************************
     *           STATIC TESTS             *
     **************************************/
    namespace static_tests
    {
        constexpr flcn::CVec2 VEC_A(1, 2);
        constexpr flcn::CVec2 VEC_B(1, 0);

        /// @test Verify that vector projection(project) returns a valid vector at compile time.
        constexpr auto PROJ_VEC = VEC_A.project(VEC_B);
        static_assert(PROJ_VEC.x() == 1);
        static_assert(PROJ_VEC.y() == 0);


        /// @test Verify that vector projection(project-static wrapper) returns a valid vector at compile time.
        constexpr auto PROJ_VEC_STATIC = flcn::CVec2<int>::project(VEC_A, VEC_B);
        static_assert(PROJ_VEC_STATIC.x() == 1);
        static_assert(PROJ_VEC_STATIC.y() == 0);


        /// @test Verify that vector projection(project normalized) returns a valid vector at compile time.
        constexpr auto PROJ_NORM_VEC = VEC_A.projectNorm(VEC_B);
        static_assert(PROJ_NORM_VEC.x() == 1);
        static_assert(PROJ_NORM_VEC.y() == 0);


        /// @test Verify that vector projection(project normalized-static wrapper) returns a valid vector at compile
        /// time.
        constexpr auto PROJ_NORM_VEC_STATIC = flcn::CVec2<int>::projectNorm(VEC_A, VEC_B);
        static_assert(PROJ_NORM_VEC_STATIC.x() == 1);
        static_assert(PROJ_NORM_VEC_STATIC.y() == 0);


        /// @test Verify that vector projection(safe project) returns a valid vector at compile time.
        constexpr auto SAFE_PROJ_VEC = VEC_A.safeProject(VEC_B);
        static_assert(SAFE_PROJ_VEC.x() == 1);
        static_assert(SAFE_PROJ_VEC.y() == 0);


        /// @test Verify that vector projection(safe project-static wrapper) returns a valid vector at compile time.
        constexpr auto SAFE_PROJ_VEC_STATIC = flcn::CVec2<int>::safeProject(VEC_A, VEC_B);
        static_assert(SAFE_PROJ_VEC_STATIC.x() == 1);
        static_assert(SAFE_PROJ_VEC_STATIC.y() == 0);


        /// @test Verify that vector projection(safe project normalized) returns a valid vector at compile time.
        constexpr auto SAFE_PROJ_NORM_VEC = VEC_A.safeProjectNorm(VEC_B);
        static_assert(SAFE_PROJ_NORM_VEC.x() == 1);
        static_assert(SAFE_PROJ_NORM_VEC.y() == 0);


        /// @test Verify that vector projection(safe project normalized-static wrapper) returns a valid vector at
        /// compile time.
        constexpr auto SAFE_PROJ_NORM_VEC_STATIC = flcn::CVec2<int>::safeProjectNorm(VEC_A, VEC_B);
        static_assert(SAFE_PROJ_NORM_VEC_STATIC.x() == 1);
        static_assert(SAFE_PROJ_NORM_VEC_STATIC.y() == 0);
    } // namespace static_tests

} // namespace



/**************************************
 *          PROJECTION TESTS          *
 **************************************/

TYPED_TEST(CVec2ProjectionTests, Project_OrthogonalVectorsReturnsZeroVector)
{
    const flcn::CVec2 actualProjection = this->_perpendicularVec.project(this->_ontoVec);
    EXPECT_VEC_ZERO(actualProjection);
}


TEST(CVec2ProjectionTests, Project_XAxis_ReturnVectorWithNonZeroXComponent)
{
    // Given an arbitrary vector
    const flcn::CVec2 a(10.0f, 20.0f);
    const flcn::CVec2 xAxis(1.0f, 0.0f);
    const flcn::CVec2 expectedProjection(10.0f, 0.0f);

    // When projected onto x-axis
    const flcn::CVec2 actualProjection = a.project(xAxis);

    // Then, the resultant vector only has x-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


TEST(CVec2ProjectionTests, Project_YAxis_ReturnVectorWithNonZeroYComponent)
{
    // Given an arbitrary vector
    const flcn::CVec2 a(10.0f, 20.0f);
    const flcn::CVec2 yAxis(0.0f, 1.0f);
    const flcn::CVec2 expectedProjection(0.0f, 20.0f);

    // When projected onto y-axis
    const flcn::CVec2 actualProjection = a.project(yAxis);

    // Then, the resultant vector only has y-component as non-zero
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


TYPED_TEST(CVec2ProjectionTests, Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const flcn::CVec2 actualProjection = this->_vec.project(this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


TYPED_TEST(CVec2ProjectionTests, StaticWrapper_Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const flcn::CVec2 actualProjection = flcn::CVec2<TypeParam>::project(this->_vec, this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


TEST(CVec2ProjectionTests, ProjectNorm_NormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::CVec2 a(1.0f, 2.0f);
    const flcn::CVec2 b(1.0f, 0.0f);
    const flcn::CVec2 expectedProjection(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::CVec2 actualProjection = a.projectNorm(b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref flcn::CVec2::project returns a non-zero vector.
 */
TEST(CVec2ProjectionTests, ProjectionOntoVectorInOppositeDirectionReturnsNonZeroVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::CVec2 a(4.0f, 4.0f);
    const flcn::CVec2 negativeYAxis(0.0f, -1.0f);
    const flcn::CVec2 expectedProjection(0.0f, 4.0f);

    // When projected
    const flcn::CVec2<float> actualProjection = a.project(negativeYAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using @ref flcn::CVec2::project returns a type-promoted vector.
 */
TEST(CVec2ProjectionTests, MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const flcn::CVec2 vec(7, 13);
    const flcn::CVec2 onto(2.0, 4.0);
    const flcn::CVec2 expectedProjection(6.6, 13.2);

    // When projected onto another
    const flcn::CVec2 actualProjection = vec.project(onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref flcn::CVec2::projectNorm returns a non-zero vector.
 */
TEST(CVec2ProjectionTests, StaticWrapper_ProjectNorm_NormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::CVec2 a(1.0f, 2.0f);
    const flcn::CVec2 b(1.0f, 0.0f);
    const flcn::CVec2 expectedProjection(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::CVec2 actualProjection = flcn::CVec2<float>::projectNorm(a, b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


/** @test Verify that projection using @ref flcn::CVec2::project always return floating-point vector. */
TYPED_TEST(CVec2ProjectionTests, Project_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::CVec2 projection = this->_vec.project(this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @test Verify that projection using static variant of @ref flcn::CVec2::project
 *       always return floating-point vector.
 */
TYPED_TEST(CVec2ProjectionTests, StaticWrapper_Project_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::CVec2 projection = flcn::CVec2<TypeParam>::project(this->_vec, this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}





/**************************************
 *        SAFE PROJECTION TESTS       *
 **************************************/

TYPED_TEST(CVec2ProjectionTests, SafeProject_Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const flcn::CVec2 actualProjection = this->_vec.safeProject(this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}



TEST(CVec2ProjectionTests, SafeProjectNorm_NormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::CVec2 a(1.0f, 2.0f);
    const flcn::CVec2 b(1.0f, 0.0f);
    const flcn::CVec2 expectedProjection(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::CVec2 actualProjection = a.safeProjectNorm(b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


TEST(CVec2ProjectionTests, SafeProjectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector and a normalized vector
    const flcn::CVec2 a(1.0f, flcn::constants::NaN);
    const flcn::CVec2 b(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::CVec2 actualProjection = a.safeProjectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


TEST(CVec2ProjectionTests, SafeProjectNorm_OntoNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::CVec2 a(1.0f, 2.0f);
    const flcn::CVec2 b(1.0f, flcn::constants::NaN);

    // When the vector is projected onto the normalized vector
    const flcn::CVec2 actualProjection = a.safeProjectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


TEST(CVec2ProjectionTests, SafeProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::CVec2 a(4.0f, 4.0f);
    const flcn::CVec2 negativeYAxis(0.0f, -1.0f);
    const flcn::CVec2 expectedProjection(0.0f, 4.0f);

    // When projected
    const flcn::CVec2<float> actualProjection = a.safeProject(negativeYAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}



TEST(CVec2ProjectionTests, SafeProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const flcn::CVec2 vec(7, 13);
    const flcn::CVec2 onto(2.0, 4.0);
    const flcn::CVec2 expectedProjection(6.6, 13.2);

    // When projected onto another
    const flcn::CVec2 actualProjection = vec.safeProject(onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}



TYPED_TEST(CVec2ProjectionTests, SafeProject_OntoZeroReturnsZeroVector)
{
    const flcn::CVec2 zeroVec = flcn::CVec2<TypeParam>::zero();

    const flcn::CVec2 actualProjection = this->_vec.safeProject(zeroVec);

    EXPECT_VEC_ZERO(actualProjection);
}


TYPED_TEST(CVec2ProjectionTests, StaticWrapper_SafeProject_Project_NonOrthogonalVectors_ReturnsNonZeroVector)
{
    const flcn::CVec2 actualProjection = flcn::CVec2<TypeParam>::safeProject(this->_vec, this->_ontoVec);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
}


TEST(CVec2ProjectionTests, StaticWrapper_SafeProjectNorm_NormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::CVec2 a(1.0f, 2.0f);
    const flcn::CVec2 b(1.0f, 0.0f);
    const flcn::CVec2 expectedProjection(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::CVec2 actualProjection = flcn::CVec2<float>::safeProjectNorm(a, b);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


TEST(CVec2ProjectionTests, StaticWrapper_SafeProjectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector
    const flcn::CVec2 a(1.0f, flcn::constants::NaN);
    const flcn::CVec2 b(1.0f, 0.0f);

    // When the vector is projected onto the normalized vector
    const flcn::CVec2 actualProjection = flcn::CVec2<float>::safeProjectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


TEST(CVec2ProjectionTests, StaticWrapper_SafeProjectNorm_OntoNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector
    const flcn::CVec2 a(1.0f, 2.0f);
    const flcn::CVec2 b(1.0f, flcn::constants::NaN);

    // When the vector is from a NaN vector
    const flcn::CVec2 actualProjection = flcn::CVec2<float>::safeProjectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualProjection);
}


TEST(CVec2ProjectionTests, StaticWrapper_SafeProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirection)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::CVec2 a(4.0f, 4.0f);
    const flcn::CVec2 negativeYAxis(0.0f, -1.0f);
    const flcn::CVec2 expectedProjection(0.0f, 4.0f);

    // When projected
    const flcn::CVec2<float> actualProjection = flcn::CVec2<float>::safeProject(a, negativeYAxis);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}



TEST(CVec2ProjectionTests, StaticWrapper_SafeProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const flcn::CVec2 vec(7, 13);
    const flcn::CVec2 onto(2.0, 4.0);
    const flcn::CVec2 expectedProjection(6.6, 13.2);

    // When projected onto another
    const flcn::CVec2 actualProjection = flcn::CVec2<int>::safeProject(vec, onto);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
}


TYPED_TEST(CVec2ProjectionTests, StaticWrapper_SafeProject_OntoZeroVectorReturnsZeroVector)
{
    const flcn::CVec2 zeroVec = flcn::CVec2<TypeParam>::zero();
    const flcn::CVec2 actualProjection = flcn::CVec2<TypeParam>::safeProject(this->_vec, zeroVec);
    EXPECT_VEC_ZERO(actualProjection);
}


TYPED_TEST(CVec2ProjectionTests, SafeProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::CVec2 projection = this->_vec.safeProject(this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


TYPED_TEST(CVec2ProjectionTests, StaticWrapper_SafeProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::CVec2 projection = flcn::CVec2<TypeParam>::safeProject(this->_vec, this->_ontoVec);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


TEST_P(CVec2ProjectionNaNTests, SafeProject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::CVec2<float>::one();

    EXPECT_VEC_ZERO(nanVec.safeProject(ontoVec));
}


TEST_P(CVec2ProjectionNaNTests, SafeProject_OntoNaNVectorReturnsZeroVector)
{
    const auto& oneVec     = flcn::CVec2<float>::one();
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(oneVec.safeProject(ontoNaNVec));
}


TEST_P(CVec2ProjectionNaNTests, StaticWrapper_SafeProject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::CVec2<float>::one();

    EXPECT_VEC_ZERO(flcn::CVec2<float>::safeProject(nanVec, ontoVec));
}


TEST_P(CVec2ProjectionNaNTests, StaticWrapper_SafeProject_OntoNaNVectorReturnsZeroVector)
{
    const auto& oneVec     = flcn::CVec2<float>::one();
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(flcn::CVec2<float>::safeProject(oneVec, ontoNaNVec));
}



/**************************************
 *         TRY PROJECTION TESTS       *
 **************************************/

/**
 * @test Verify that projecting onto an orthogonal vector using @ref flcn::CVec2::tryProject
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(CVec2ProjectionTests, TryProject_Project_NonOrthogonalVectors_ReturnsNonZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::CVec2 actualProjection = this->_vec.tryProject(this->_ontoVec, flag);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using @ref flcn::CVec2::tryProjectNorm
 *       returns a non-zero vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(CVec2ProjectionTests, TryProject_NormalizedVectorReturnsNonZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::CVec2 a(1.0f, 2.0f);
    const flcn::CVec2 b(1.0f, 0.0f);
    const flcn::CVec2 expectedProjection(1.0f, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const flcn::CVec2 actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting a NaN vector onto a non-orthogonal unit vector using @ref flcn::CVec2::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(CVec2ProjectionTests, TryProjectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::CVec2 a(flcn::constants::NaN, 2.0f);
    const flcn::CVec2 b(1.0f, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const flcn::CVec2 actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projecting a vector onto a NaN vector using @ref flcn::CVec2::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(CVec2ProjectionTests, TryProjectNorm_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::CVec2 a(1.0f, 2.0f);
    const flcn::CVec2 b(1.0f, flcn::constants::NaN);
    flcn::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const flcn::CVec2 actualProjection = a.tryProjectNorm(b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using @ref flcn::CVec2::tryProject returns a non-zero vector
 *       and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(CVec2ProjectionTests, TryProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirectionAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::CVec2 a(4.0f, 4.0f);
    const flcn::CVec2 negativeYAxis(0.0f, -1.0f);
    const flcn::CVec2 expectedProjection(0.0f, 4.0f);
    flcn::OperationStatus flag;

    // When projected
    const flcn::CVec2<float> actualProjection = a.tryProject(negativeYAxis, flag);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using @ref flcn::CVec2::tryProject returns a type-promoted vector
 *       and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(CVec2ProjectionTests, TryProject_MixedTypeProjectionPromotesType)
{
    // Given two arbitrary vectors
    const flcn::CVec2 vec(7, 13);
    const flcn::CVec2 onto(2.0, 4.0);
    const flcn::CVec2 expectedProjection(6.6, 13.2);
    flcn::OperationStatus flag;

    // When projected onto another
    const flcn::CVec2 actualProjection = vec.tryProject(onto, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a zero length vector using @ref flcn::CVec2::tryProject
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(CVec2ProjectionTests, TryProject_OntoZeroReturnsZeroVectorAndSetsCorrectFlag)
{
    const flcn::CVec2 zeroVec = flcn::CVec2<TypeParam>::zero();
    flcn::OperationStatus flag;


    const flcn::CVec2 actualProjection = this->_vec.tryProject(zeroVec, flag);

    EXPECT_VEC_ZERO(actualProjection);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector using static variant of @ref flcn::CVec2::tryProject
 *       returns a non-zero vector and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(CVec2ProjectionTests, StaticWrapper_TryProject_Project_NonOrthogonalVectors_ReturnsNonZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const flcn::CVec2 actualProjection = flcn::CVec2<TypeParam>::tryProject(this->_vec, this->_ontoVec, flag);

    EXPECT_VEC_EQ(this->_expectedProjection, actualProjection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal unit vector using static variant of
 *       @ref flcn::CVec2::tryProjectNorm returns a non-zero vector and sets the flag to
 *       @ref flcn::OperationStatus::SUCCESS.
 */
TEST(CVec2ProjectionTests, StaticWrapper_TryProjectNorm_NormalizedVectorReturnsNonZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::CVec2 a(1.0f, 2.0f);
    const flcn::CVec2 b(1.0f, 0.0f);
    const flcn::CVec2 expectedProjection(1.0f, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the normalized vector
    const flcn::CVec2 actualProjection = flcn::CVec2<float>::tryProjectNorm(a, b, flag);

    // Then, the resultant vector has components that is parallel to the projected vector
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting a NaN vector onto a non-orthogonal unit vector using static variant of @ref
 * flcn::CVec2::tryProjectNorm returns a zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(CVec2ProjectionTests, StaticWrapper_TryProjectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a NaN vector
    const flcn::CVec2 a(flcn::constants::NaN, 2.0f);
    const flcn::CVec2 b(1.0f, 0.0f);
    flcn::OperationStatus flag;

    // When the vector is projected onto the NaN vector
    const flcn::CVec2 actualProjection = flcn::CVec2<float>::tryProjectNorm(a, b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/**
 * @test Verify that projecting a vector onto a NaN vector using static variant of @ref flcn::CVec2::tryProjectNorm
 *       returns a zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(CVec2ProjectionTests, StaticWrapper_TryProjectNorm_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a NaN vector
    const flcn::CVec2 a(1.0f, 2.0f);
    const flcn::CVec2 b(1.0f, flcn::constants::NaN);
    flcn::OperationStatus flag;

    // When the vector is projected onto the NaN vector
    const flcn::CVec2 actualProjection = flcn::CVec2<float>::tryProjectNorm(a, b, flag);

    // Then, the resultant vector is a zero vector.
    EXPECT_VEC_ZERO(actualProjection);
    // And sets the flag to NANOPERAND
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector pointing in the opposite direction
 *       using static variant of @ref flcn::CVec2::tryProject returns a non-zero vector
 *       and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(CVec2ProjectionTests,
     StaticWrapper_TryProject_OntoVectorInOppositeDirectionReturnsVectorInSameDirectionAndSetsCorrectFlag)
{
    // Given an arbitrary vector and a vector in the opposite Direction
    const flcn::CVec2 a(4.0f, 4.0f);
    const flcn::CVec2 negativeYAxis(0.0f, -1.0f);
    const flcn::CVec2 expectedProjection(0.0f, 4.0f);
    flcn::OperationStatus flag;

    // When projected
    const flcn::CVec2<float> actualProjection = flcn::CVec2<float>::tryProject(a, negativeYAxis, flag);

    // Then, the resultant vector is non-zero and in the same direction
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a non-orthogonal vector of a different numeric type
 *       using static variant of @ref flcn::CVec2::tryProject returns a type-promoted vector
 *       and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(CVec2ProjectionTests, StaticWrapper_TryProject_MixedTypeProjectionPromotesTypeAndSetsCorrectFlag)
{
    // Given two arbitrary vectors
    const flcn::CVec2 vec(7, 13);
    const flcn::CVec2 onto(2.0, 4.0);
    const flcn::CVec2 expectedProjection(6.6, 13.2);
    flcn::OperationStatus flag;

    // When projected onto another
    const flcn::CVec2 actualProjection = flcn::CVec2<int>::tryProject(vec, onto, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualProjection)::value_type, double>);
    // and is the projection
    EXPECT_VEC_EQ(expectedProjection, actualProjection);
    // And sets the flag to SUCCESS
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that projecting onto a zero length vector using static variant of @ref flcn::CVec2::tryProject
 *        returns a type-promoted vector and sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(CVec2ProjectionTests, StaticWrapper_TryProject_OntoZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const flcn::CVec2 zeroVec = flcn::CVec2<TypeParam>::zero();
    flcn::OperationStatus flag;

    const flcn::CVec2 actualProjection = flcn::CVec2<TypeParam>::tryProject(this->_vec, zeroVec, flag);

    EXPECT_VEC_ZERO(actualProjection);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/** @test Verify that projection using @ref flcn::CVec2::tryProject always return floating-point vector. */
TYPED_TEST(CVec2ProjectionTests, TryProject_AlwaysReturnFloatingPointVectorAndSetsCorrectFlag)
{
    [[maybe_unused]] flcn::OperationStatus flag;
    [[maybe_unused]] const flcn::CVec2 projection = this->_vec.tryProject(this->_ontoVec, flag);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @test Verify that projection using static variant of @ref flcn::CVec2::tryProject
 *       always return floating-point vector.
 */
TYPED_TEST(CVec2ProjectionTests, StaticWrapper_TryProject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] flcn::OperationStatus flag;
    [[maybe_unused]] const flcn::CVec2 projection = flcn::CVec2<TypeParam>::tryProject(this->_vec, this->_ontoVec, flag);
    static_assert(std::is_floating_point_v<typename decltype(projection)::value_type>);
}


/**
 * @test Verify that projection of NaN vector using @ref flcn::CVec2::tryProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(CVec2ProjectionNaNTests, TryProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::CVec2<float>::one();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(nanVec.tryProject(ontoVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projection onto NaN vector using @ref flcn::CVec2::tryProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(CVec2ProjectionNaNTests, TryProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::CVec2<float>::one();
    const auto& ontoNaNVec = GetParam();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(oneVec.tryProject(ontoNaNVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projection of NaN vector using static variant of @ref flcn::CVec2::tryProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(CVec2ProjectionNaNTests, StaticWrapper_TryProject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::CVec2<float>::one();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(flcn::CVec2<float>::tryProject(nanVec, ontoVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that projection onto NaN vector using static variant of @ref flcn::CVec2::tryProject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(CVec2ProjectionNaNTests, StaticWrapper_TryProject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::CVec2<float>::one();
    const auto& ontoNaNVec = GetParam();
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::CVec2<float>::tryProject(oneVec, ontoNaNVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}

/** @} */
