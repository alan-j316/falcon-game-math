/**
 * @file RejectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 28, 2026
 *
 * @brief Verify @ref flcn::Vec4 rejection logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec4TestSetup.h"


/**
 * @addtogroup T_FALCON_Vec4_Proj
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Vec4 projection.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class Vec4RejectionTests: public testing::Test
    {
    protected:
        flcn::Vec4<T> _vec;
        flcn::Vec4<T> _parallelVec;
        flcn::Vec4<T> _fromVec;
        flcn::Vec4<T> _expectedRejection;

        void SetUp() override
        {
            _vec               = { T(1), T(2), T(3), T(4) };
            _parallelVec       = { T(2), T(4), T(6), T(8) };
            _fromVec           = { T(0), T(2), T(0), T(0) };
            _expectedRejection = { T(1), T(0), T(3), T(4) };
        }
    };
    TYPED_TEST_SUITE(Vec4RejectionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::Vec4 projection with NaN vectors.
     */
    class Vec4RejectionNaNTests: public testing::TestWithParam<flcn::Vec4<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Vec4RejectionTestSuite, Vec4RejectionNaNTests,
                             ::testing::Values(flcn::Vec4<float>(flcn::constants::NaN, 1.0f, 1.0f, 1.0f),
                                               flcn::Vec4<float>(1.0f, flcn::constants::NaN, 1.0f, 1.0f),
                                               flcn::Vec4<float>(1.0f, 1.0f, flcn::constants::NaN, 1.0f),
                                               flcn::Vec4<float>(1.0f, 1.0f, 1.0f, flcn::constants::NaN),
                                               flcn::Vec4<float>(flcn::constants::NaN, flcn::constants::NaN,
                                                                flcn::constants::NaN, flcn::constants::NaN)));



    /**************************************
     *           STATIC TESTS             *
     **************************************/
    namespace static_tests
    {
        constexpr flcn::Vec4 VEC_A(1, 2, 3, 4);
        constexpr flcn::Vec4 VEC_B(1, 0, 0, 0);

        /// @test Verify that vector rejection(reject) returns a valid vector at compile time.
        constexpr auto REJ_VEC = VEC_A.reject(VEC_B);
        static_assert(REJ_VEC.x() == 0);
        static_assert(REJ_VEC.y() == 2);
        static_assert(REJ_VEC.z() == 3);
        static_assert(REJ_VEC.w() == 4);

        /// @test Verify that vector rejection(reject-static wrapper) returns a valid vector at compile time.
        constexpr auto REJ_VEC_STATIC = flcn::Vec4<int>::reject(VEC_A, VEC_B);
        static_assert(REJ_VEC_STATIC.x() == 0);
        static_assert(REJ_VEC_STATIC.y() == 2);
        static_assert(REJ_VEC_STATIC.z() == 3);
        static_assert(REJ_VEC_STATIC.w() == 4);

        /// @test Verify that vector rejection(reject normalized) returns a valid vector at compile time.
        constexpr auto REJ_NORM_VEC = VEC_A.rejectNorm(VEC_B);
        static_assert(REJ_NORM_VEC.x() == 0);
        static_assert(REJ_NORM_VEC.y() == 2);
        static_assert(REJ_NORM_VEC.z() == 3);
        static_assert(REJ_NORM_VEC.w() == 4);

        /// @test Verify that vector rejection(reject normalized-static wrapper) returns a valid vector at compile
        /// time.
        constexpr auto REJ_NORM_VEC_STATIC = flcn::Vec4<int>::rejectNorm(VEC_A, VEC_B);
        static_assert(REJ_NORM_VEC_STATIC.x() == 0);
        static_assert(REJ_NORM_VEC_STATIC.y() == 2);
        static_assert(REJ_NORM_VEC_STATIC.z() == 3);
        static_assert(REJ_NORM_VEC_STATIC.w() == 4);


        /// @test Verify that vector rejection(safe reject) returns a valid vector at compile time.
        constexpr auto SAFE_REJ_VEC = VEC_A.safeReject(VEC_B);
        static_assert(SAFE_REJ_VEC.x() == 0);
        static_assert(SAFE_REJ_VEC.y() == 2);
        static_assert(SAFE_REJ_VEC.z() == 3);
        static_assert(SAFE_REJ_VEC.w() == 4);

        /// @test Verify that vector rejection(safe reject-static wrapper) returns a valid vector at compile time.
        constexpr auto SAFE_REJ_VEC_STATIC = flcn::Vec4<int>::safeReject(VEC_A, VEC_B);
        static_assert(SAFE_REJ_VEC_STATIC.x() == 0);
        static_assert(SAFE_REJ_VEC_STATIC.y() == 2);
        static_assert(SAFE_REJ_VEC_STATIC.z() == 3);
        static_assert(SAFE_REJ_VEC_STATIC.w() == 4);


        /// @test Verify that vector rejection(safe reject normalized) returns a valid vector at compile time.
        constexpr auto SAFE_REJ_NORM_VEC = VEC_A.safeRejectNorm(VEC_B);
        static_assert(SAFE_REJ_NORM_VEC.x() == 0);
        static_assert(SAFE_REJ_NORM_VEC.y() == 2);
        static_assert(SAFE_REJ_NORM_VEC.z() == 3);
        static_assert(SAFE_REJ_NORM_VEC.w() == 4);

        /// @test Verify that vector rejection(safe reject normalized-static wrapper) returns a valid vector at
        /// compile time.
        constexpr auto SAFE_REJ_NORM_VEC_STATIC = flcn::Vec4<int>::safeRejectNorm(VEC_A, VEC_B);
        static_assert(SAFE_REJ_NORM_VEC_STATIC.x() == 0);
        static_assert(SAFE_REJ_NORM_VEC_STATIC.y() == 2);
        static_assert(SAFE_REJ_NORM_VEC_STATIC.z() == 3);
        static_assert(SAFE_REJ_NORM_VEC_STATIC.w() == 4);

    } // namespace static_tests
} // namespace



/**************************************
 *          REJECTION TESTS           *
 **************************************/

/** @test Verify that rejecting from a parallel vector using @ref flcn::Vec4::reject returns a zero vector. */
TYPED_TEST(Vec4RejectionTests, ParallelVectorsReturnsZeroVector)
{
    const flcn::Vec4 actualRejection = this->_vec.reject(this->_parallelVec);
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that rejecting from a vector parallel to x-axis using @ref flcn::Vec4::reject
 *       returns a vector with a zero x-component.
 */
TEST(Vec4RejectionTests, RejectionFromXAxisReturnsVectorWithZeroXComponent)
{
    // Given an arbitrary vector
    const flcn::Vec4 a(10.0f, 20.0f, 30.0f, 40.0f);
    const flcn::Vec4 xAxis(1.0f, 0.0f, 0.0f, 0.0f);
    const flcn::Vec4 expectedRejection(0.0f, 20.0f, 30.0f, 40.f);

    // When rejected from x-axis
    const flcn::Vec4 actualRejection = a.reject(xAxis);

    // Then, the resultant vector has zero x-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from a vector parallel to y-axis using @ref flcn::Vec4::reject
 *       returns a vector with a zero y-component.
 */
TEST(Vec4RejectionTests, RejectionFromYAxisReturnsVectorWithZeroYComponent)
{
    // Given an arbitrary vector
    const flcn::Vec4 a(10.0f, 20.0f, 30.0f, 40.0f);
    const flcn::Vec4 yAxis(0.0f, 1.0f, 0.0f, 0.0f);
    const flcn::Vec4 expectedRejection(10.0f, 0.0f, 30.0f, 40.0f);

    // When rejected from y-axis
    const flcn::Vec4 actualRejection = a.reject(yAxis);

    // Then, the resultant vector has zero y-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from a vector parallel to z-axis using @ref flcn::Vec4::reject
 *       returns a vector with a zero z-component.
 */
TEST(Vec4RejectionTests, RejectionFromZAxisReturnsVectorWithZeroZComponent)
{
    // Given an arbitrary vector
    const flcn::Vec4 a(10.0f, 20.0f, 30.0f, 40.0f);
    const flcn::Vec4 zAxis(0.0f, 0.0f, 1.0f, 0.0f);
    const flcn::Vec4 expectedRejection(10.0f, 20.0f, 0.0f, 40.0f);

    // When rejected from z-axis
    const flcn::Vec4 actualRejection = a.reject(zAxis);

    // Then, the resultant vector has zero z-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from a vector parallel to w-axis using @ref flcn::Vec4::reject
 *       returns a vector with a zero w-component.
 */
TEST(Vec4RejectionTests, RejectionFromWAxisReturnsVectorWithZeroWComponent)
{
    // Given an arbitrary vector
    const flcn::Vec4 a(10.0f, 20.0f, 30.0f, 40.0f);
    const flcn::Vec4 wAxis(0.0f, 0.0f, 0.0f, 1.0f);
    const flcn::Vec4 expectedRejection(10.0f, 20.0f, 30.0f, 0.0f);

    // When rejected from w-axis
    const flcn::Vec4 actualRejection = a.reject(wAxis);

    // Then, the resultant vector has zero w-component
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/** @test Verify that rejecting an orthogonal using @ref flcn::Vec4::reject returns the original vector. */
TEST(Vec4RejectionTests, OrthogonalRejectionReturnsOriginalVector)
{
    // Given an arbitrary vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 0.0f);
    const flcn::Vec4 b(0.0f, 0.0f, 0.0f, 1.0f);

    // When rejected on to an orthogonal vector
    const flcn::Vec4 actualRejection = a.reject(b);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @test Verify that rejecting from a non-orthogonal vector using @ref flcn::Vec4::reject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vec4RejectionTests, NonOrthogonalRejectionReturnsNonZeroVector)
{
    const flcn::Vec4 actualRejection = this->_vec.reject(this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from a non-orthogonal vector using static variant of @ref flcn::Vec4::reject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vec4RejectionTests, StaticWrapper_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const flcn::Vec4 actualRejection = flcn::Vec4<TypeParam>::reject(this->_vec, this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from an orthogonal unit vector using @ref flcn::Vec4::rejectNorm
 *       returns a non-zero vector with perpendicular component.
 */
TEST(Vec4RejectionTests, RejectionFromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, 0.0f, 0.0f, 0.0f);
    const flcn::Vec4 expectedRejection(0.0f, 2.0f, 3.0f, 4.0f);

    // When rejected from another
    const flcn::Vec4 actualRejection = a.rejectNorm(b);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from an orthogonal vector pointing in the opposite direction
 *       using @ref flcn::Vec4::reject returns a non-zero vector with perpendicular components.
 */
TEST(Vec4RejectionTests, RejectionFromVectorInOppositeDirectionReturnsVectorWithPerpendicularComponents)
{
    // Given an arbitrary vector
    const flcn::Vec4 a(4.0f, 4.0f, 4.0f, 4.0f);
    const flcn::Vec4 negativeZAxis(0.0f, 0.0f, -1.0f, 0.0f);
    const flcn::Vec4 expectedRejection(4.0f, 4.0f, 0.0f, 4.0f);

    // When rejected from a vector in opposite direction
    const flcn::Vec4 actualRejection = a.reject(negativeZAxis);

    // Then, the resultant vector has components perpendicular to the `from` vector in the same direction.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting a vector from another vector of different numeric type using @ref flcn::Vec4::reject
 *       returns a type-promoted vector.
 */
TEST(Vec4RejectionTests, MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    const flcn::Vec4 vec(7, 13, 29, 41);
    const flcn::Vec4 from(2.0, 4.0, 4.0, 2.0);
    const flcn::Vec4 expectedRejection(-6.2, -13.4, 2.6, 27.8);

    // When reject from another
    const flcn::Vec4 actualRejection = vec.reject(from);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that rejecting from an orthogonal unit vector using @ref flcn::Vec4::rejectNorm
 *       returns a non-zero vector with perpendicular component.
 */
TEST(Vec4RejectionTests, StaticWrapper_RejectionFromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, 0.0f, 0.0f, 0.0f);
    const flcn::Vec4 expectedRejection(0.0f, 2.0f, 3.0f, 4.0f);

    // When rejected from another
    const flcn::Vec4 actualRejection = flcn::Vec4<float>::rejectNorm(a, b);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/** @test Verify that rejection using @ref flcn::Vec4::reject always return floating-point vector. */
TYPED_TEST(Vec4RejectionTests, Reject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::Vec4 rejection = this->_vec.reject(this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


/**
 * @test Verify that rejection using static variant of @ref flcn::Vec4::reject
 *       always return floating-point vector.
 */
TYPED_TEST(Vec4RejectionTests, StaticWrapper_Reject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::Vec4 rejection = flcn::Vec4<TypeParam>::reject(this->_vec, this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}



/**************************************
 *       SAFE REJECTION TESTS         *
 **************************************/

/**
 * @test Verify that safely rejecting from a parallel vector using @ref flcn::Vec4::safeReject
 *       returns a zero vector.
 */
TYPED_TEST(Vec4RejectionTests, SafeReject_ParallelVectorsReturnsZeroVector)
{
    const flcn::Vec4 actualRejection = this->_vec.safeReject(this->_parallelVec);

    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting from orthogonal using @ref flcn::Vec4::safeReject
 *       returns the original vector.
 */
TEST(Vec4RejectionTests, SafeReject_OrthogonalRejectionReturnsOriginalVector)
{
    // Given an arbitrary vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 0.0f);
    const flcn::Vec4 b(0.0f, 0.0f, 0.0f, 1.0f);

    // When rejected from an orthogonal vector
    const flcn::Vec4 actualRejection = a.safeReject(b);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @test Verify that safely rejecting from a non-orthogonal vector using @ref flcn::Vec4::safeReject
 *       returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vec4RejectionTests, SafeReject_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const flcn::Vec4 actualRejection = this->_vec.safeReject(this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using @ref flcn::Vec4::safeRejectNorm
 *       returns a non-zero vector with perpendicular component.
 */
TEST(Vec4RejectionTests, SafeRejectNorm_FromNormalizedVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, 0.0f, 0.0f, 0.0f);
    const flcn::Vec4 expectedRejection(0.0f, 2.0f, 3.0f, 4.0f);

    // When rejected from another
    const flcn::Vec4 actualRejection = a.safeRejectNorm(b);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting a NaN vector from a non-orthogonal unit vector using
 *       @ref flcn::Vec4::safeRejectNorm returns a zero vector.
 */
TEST(Vec4RejectionTests, SafeRejectNorm_NaNVectorReturnsNonZeroVector)
{
    // Given a NaN vector
    const flcn::Vec4 a(1.0f, flcn::constants::NaN, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, 0.0f, 0.0f, 0.0f);

    // When the vector is rejected onto the normalized vector
    const flcn::Vec4 actualRejection = a.safeRejectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting from a NaN vector using @ref flcn::Vec4::safeRejectNorm returns a zero vector.
 */
TEST(Vec4RejectionTests, SafeRejectNorm_FromNaNVectorReturnsNonZeroVector)
{
    // Given an arbitrary vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, flcn::constants::NaN, 0.0f, 0.0f);

    // When the vector is rejected from a NaN vector
    const flcn::Vec4 actualRejection = a.safeRejectNorm(b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting a vector from another vector of different numeric
 *       type using @ref flcn::Vec4::safeReject returns a type-promoted vector.
 */
TEST(Vec4RejectionTests, SafeReject_MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    const flcn::Vec4 vec(7, 13, 29, 41);
    const flcn::Vec4 from(2.0, 4.0, 4.0, 2.0);
    const flcn::Vec4 expectedRejection(-6.2, -13.4, 2.6, 27.8);

    // When rejected from another
    const flcn::Vec4 actualRejection = vec.safeReject(from);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
}


/**
 * @test Verify that safely rejecting from a zero vector using @ref flcn::Vec4::safeReject
 *       returns the same vector.
 */
TYPED_TEST(Vec4RejectionTests, SafeReject_FromZeroVectorReturnsSameVector)
{
    const flcn::Vec4 zeroVec = flcn::Vec4<TypeParam>::zero();

    const flcn::Vec4 actualRejection = this->_vec.safeReject(zeroVec);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
}


/**
 * @test Verify that safely rejecting from a parallel vector using static variant of @ref flcn::Vec4::safeReject
 *       returns a zero vector.
 */
TYPED_TEST(Vec4RejectionTests, StaticWrapper_SafeReject_ParallelVectorsReturnsZeroVector)
{
    const flcn::Vec4 actualRejection = flcn::Vec4<TypeParam>::safeReject(this->_vec, this->_parallelVec);

    EXPECT_VEC_ZERO(actualRejection);
}


/**
 * @test Verify that safely rejecting a vector from an orthogonal vector using
 *       static variant of @ref flcn::Vec4::safeReject returns the original vector.
 */
TEST(Vec4RejectionTests, StaticWrapper_SafeReject_OrthogonalRejectionReturnsOriginalVector)
{
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 0.0f);
    const flcn::Vec4 b(0.0f, 0.0f, 0.0f, 1.0f);

    const flcn::Vec4 actualRejection = flcn::Vec4<float>::safeReject(a, b);

    EXPECT_VEC_EQ(a, actualRejection);
}


/**
 * @test Verify that safely rejecting from a non-orthogonal vector using static variant of
 *       @ref flcn::Vec4::safeReject returns a non-zero vector with perpendicular component.
 */
TYPED_TEST(Vec4RejectionTests, StaticWrapper_SafeReject_NonOrthogonalRejectionReturnsNonZeroVector)
{
    const flcn::Vec4 actualRejection = flcn::Vec4<TypeParam>::safeReject(this->_vec, this->_fromVec);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
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
    const flcn::Vec4 actualRejection = flcn::Vec4<float>::safeRejectNorm(a, b);

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
    const flcn::Vec4 actualRejection = flcn::Vec4<float>::safeRejectNorm(a, b);

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
    const flcn::Vec4 b(1.0f, flcn::constants::NaN, 0.0f, 0.0f);

    // When the vector is rejected from a NaN vector
    const flcn::Vec4 actualRejection = flcn::Vec4<float>::safeRejectNorm(a, b);

    // Then, the resultant vector is a zero vector
    EXPECT_VEC_ZERO(actualRejection);
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
    const flcn::Vec4 actualRejection = flcn::Vec4<int>::safeReject(vec, from);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
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

    const flcn::Vec4 actualRejection = flcn::Vec4<TypeParam>::safeReject(this->_vec, zeroVec);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
}


/** @test Verify that rejection using @ref flcn::Vec4::safeReject always return floating-point vector. */
TYPED_TEST(Vec4RejectionTests, SafeReject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::Vec4 rejection = this->_vec.safeReject(this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


/**
 * @test Verify that rejection using static variant of @ref flcn::Vec4::safeReject
 *       always return floating-point vector.
 */
TYPED_TEST(Vec4RejectionTests, StaticWrapper_SafeReject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] const flcn::Vec4 rejection = flcn::Vec4<TypeParam>::safeReject(this->_vec, this->_fromVec);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


/**
 * @test Verify that the rejection of NaN vector using @ref flcn::Vec4::safeReject
 *       returns zero vector.
 */
TEST_P(Vec4RejectionNaNTests, SafeReject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::Vec4<float>::one();

    EXPECT_VEC_ZERO(nanVec.safeReject(ontoVec));
}


/**
 * @test Verify that rejecting onto NaN vector using @ref flcn::Vec4::safeReject
 *       returns zero vector.
 */
TEST_P(Vec4RejectionNaNTests, SafeReject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::Vec4<float>::one();
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(oneVec.safeReject(ontoNaNVec));
}


/**
 * @test Verify that the rejection of NaN vector using static variant of @ref flcn::Vec4::safeReject
 *       returns zero vector.
 */
TEST_P(Vec4RejectionNaNTests, StaticWrapper_SafeReject_NaNVectorReturnsZeroVector)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::Vec4<float>::one();

    EXPECT_VEC_ZERO(flcn::Vec4<float>::safeReject(nanVec, ontoVec));
}


/**
 * @test Verify that rejecting onto a NaN vector using static variant of @ref flcn::Vec4::safeReject
 *       returns zero vector.
 */
TEST_P(Vec4RejectionNaNTests, StaticWrapper_SafeReject_OntoNaNVectorReturnsZeroVector)
{
    const auto& oneVec     = flcn::Vec4<float>::one();
    const auto& ontoNaNVec = GetParam();

    EXPECT_VEC_ZERO(flcn::Vec4<float>::safeReject(oneVec, ontoNaNVec));
}



/**************************************
 *        TRY REJECTION TESTS         *
 **************************************/

/**
 * @test Verify that safely rejecting from a parallel vector using @ref flcn::Vec4::tryReject
 *       returns a zero vector  and sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec4RejectionTests, TryReject_ParallelVectorsReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    flcn::OperationStatus flag;
    const flcn::Vec4 actualRejection = this->_vec.tryReject(this->_parallelVec, flag);

    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from orthogonal using @ref flcn::Vec4::tryReject
 *       returns the original vector and sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec4RejectionTests, TryReject_OrthogonalRejectionReturnsOriginalVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 0.0f);
    const flcn::Vec4 b(0.0f, 0.0f, 0.0f, 1.0f);
    flcn::OperationStatus flag;

    // When rejected from an orthogonal vector
    const flcn::Vec4 actualRejection = a.tryReject(b, flag);

    // Then, the resultant is same the original vector
    EXPECT_VEC_EQ(a, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from a non-orthogonal vector using @ref flcn::Vec4::tryReject
 *       returns a non-zero vector with perpendicular component sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec4RejectionTests, TryReject_NonOrthogonalRejectionReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    flcn::OperationStatus flag;
    const flcn::Vec4 actualRejection = this->_vec.tryReject(this->_fromVec, flag);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using @ref flcn::Vec4::tryRejectNorm
 *       returns a non-zero vector and with perpendicular component sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec4RejectionTests, TryReject_FromNormalizedVectorReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, 0.0f, 0.0f, 0.0f);
    const flcn::Vec4 expectedRejection(0.0f, 2.0f, 3.0f, 4.0f);
    flcn::OperationStatus flag;


    // When rejected from another
    const flcn::Vec4 actualRejection = a.tryRejectNorm(b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}



/**
 * @test Verify that safely rejecting NaN vector from an orthogonal unit vector using @ref flcn::Vec4::tryRejectNorm
 *       returns a zero vector and sets flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec4RejectionTests, TryRejectNorm_NaNVectorReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec4 a(1.0f, flcn::constants::NaN, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, 0.0f, 0.0f, 0.0f);
    flcn::OperationStatus flag;


    // When rejected from another
    const flcn::Vec4 actualRejection = a.tryRejectNorm(b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that safely rejecting from an NaN vector using @ref flcn::Vec4::tryRejectNorm
 *       returns a zero vector and sets flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(Vec4RejectionTests, TryRejectNorm_FromNaNVectorReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, flcn::constants::NaN, 0.0f, 0.0f);
    flcn::OperationStatus flag;


    // When rejected from another
    const flcn::Vec4 actualRejection = a.tryRejectNorm(b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_ZERO(actualRejection);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}



/**
 * @test Verify that safely rejecting a vector from another vector of different numeric
 *       type using @ref flcn::Vec4::tryReject returns a type-promoted vector
 *       sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec4RejectionTests, TryReject_MixedTypeRejectionPromotesType)
{
    // Given two arbitrary vectors
    const flcn::Vec4 vec(7, 13, 29, 41);
    const flcn::Vec4 from(2.0, 4.0, 4.0, 2.0);
    const flcn::Vec4 expectedRejection(-6.2, -13.4, 2.6, 27.8);
    flcn::OperationStatus flag;

    // When rejected from another
    const flcn::Vec4 actualRejection = vec.tryReject(from, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
    // and is the rejection
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from a zero vector using @ref flcn::Vec4::tryReject
 *       returns the same vector and sets flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(Vec4RejectionTests, TryReject_FromZeroVectorReturnsSameVectorAndSetsCorrectStatusFlag)
{
    const flcn::Vec4 zeroVec = flcn::Vec4<TypeParam>::zero();
    flcn::OperationStatus flag;

    const flcn::Vec4 actualRejection = this->_vec.tryReject(zeroVec, flag);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that safely rejecting from a parallel vector using static variant of @ref flcn::Vec4::tryReject
 *       returns a zero vector and sets flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(Vec4RejectionTests, StaticWrapper_TryReject_ParallelVectorsReturnsZeroVectorAndSetsCorrectStatusFlag)
{
    flcn::OperationStatus flag;

    const flcn::Vec4 actualRejection = flcn::Vec4<TypeParam>::tryReject(this->_vec, this->_parallelVec, flag);

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

    const flcn::Vec4 actualRejection = flcn::Vec4<float>::tryReject(a, b, flag);

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

    const flcn::Vec4 actualRejection = flcn::Vec4<TypeParam>::tryReject(this->_vec, this->_fromVec, flag);

    EXPECT_VEC_EQ(this->_expectedRejection, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that safely rejecting from an orthogonal unit vector using static variant of
 *       @ref flcn::Vec4::tryRejectNorm returns a non-zero vector and with perpendicular component sets flag to
 *       @ref flcn::OperationStatus::SUCCESS.
 */
TEST(Vec4RejectionTests, StaticWrapper_TryReject_FromNormalizedVectorReturnsNonZeroVectorAndSetsCorrectStatusFlag)
{
    // Given an arbitrary vector and a normalized vector
    const flcn::Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    const flcn::Vec4 b(1.0f, 0.0f, 0.0f, 0.0f);
    const flcn::Vec4 expectedRejection(0.0f, 2.0f, 3.0f, 4.0f);
    flcn::OperationStatus flag;

    // When rejected from another
    const flcn::Vec4 actualRejection = flcn::Vec4<float>::tryRejectNorm(a, b, flag);

    // Then, the resultant vector has components perpendicular to the `from` vector.
    EXPECT_VEC_EQ(expectedRejection, actualRejection);
    // Flag is set to SUCCESS
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
    const flcn::Vec4 actualRejection = flcn::Vec4<float>::tryRejectNorm(a, b, flag);

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
    const flcn::Vec4 b(1.0f, flcn::constants::NaN, 0.0f, 0.0f);
    flcn::OperationStatus flag;


    // When rejected from another
    const flcn::Vec4 actualRejection = flcn::Vec4<float>::tryRejectNorm(a, b, flag);

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
    const flcn::Vec4 actualRejection = flcn::Vec4<int>::tryReject(vec, from, flag);

    // Then, the resultant vector is type promoted
    static_assert(std::is_same_v<decltype(actualRejection)::value_type, double>);
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

    const flcn::Vec4 actualRejection = flcn::Vec4<TypeParam>::tryReject(this->_vec, zeroVec, flag);

    EXPECT_VEC_EQ(this->_vec, actualRejection);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/** @test Verify that rejection using @ref flcn::Vec4::tryReject always return floating-point vector. */
TYPED_TEST(Vec4RejectionTests, TryRejectAlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] flcn::OperationStatus status;
    [[maybe_unused]] const flcn::Vec4 rejection = this->_vec.tryReject(this->_fromVec, status);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}


/**
 * @test Verify that rejection using static variant of @ref flcn::Vec4::tryReject
 *       always return floating-point vector.
 */
TYPED_TEST(Vec4RejectionTests, StaticWrapper_TryReject_AlwaysReturnFloatingPointVector)
{
    [[maybe_unused]] flcn::OperationStatus status;
    [[maybe_unused]] const flcn::Vec4 rejection = flcn::Vec4<TypeParam>::tryReject(this->_vec, this->_fromVec, status);
    static_assert(std::is_floating_point_v<typename decltype(rejection)::value_type>);
}



/**
 * @test Verify that the rejection of NaN vector using @ref flcn::Vec4::tryReject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec4RejectionNaNTests, TryReject_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& nanVec  = GetParam();
    const auto& ontoVec = flcn::Vec4<float>::one();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(nanVec.tryReject(ontoVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that the rejection onto NaN vector using @ref flcn::Vec4::tryReject
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST_P(Vec4RejectionNaNTests, TryReject_OntoNaNVectorReturnsZeroVectorAndSetsCorrectFlag)
{
    const auto& oneVec     = flcn::Vec4<float>::one();
    const auto& ontoNaNVec = GetParam();
    flcn::OperationStatus flag;

    EXPECT_VEC_ZERO(oneVec.tryReject(ontoNaNVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
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

    EXPECT_VEC_ZERO(flcn::Vec4<float>::tryReject(nanVec, ontoVec, flag));
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

    EXPECT_VEC_ZERO(flcn::Vec4<float>::tryReject(oneVec, ontoNaNVec, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/** @} */
