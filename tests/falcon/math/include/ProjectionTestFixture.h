#pragma once
/**
 * @file ProjectionTestFixture.h
 * @author Alan Abraham P Kochumon
 * @date Created on: November 28, 2026
 *
 * @brief Test fixtures for vector projection and rejection tests.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CommonSetup.h"

#include <falcon/math/Quat.h>
#include <falcon/math/utils/Projection.h>
#include <falcon/math/vectors/Vec2.h>
#include <falcon/math/vectors/Vec3.h>
#include <falcon/math/vectors/Vec4.h>
#include <falcon/math/vectors/simd/Vec2.h>
#include <falcon/math/vectors/simd/Vec3.h>


/// +---------------------------------------------------------------------------------------+
/// |                           VEC2, VEC3, VEC4 (SCALAR)                                   |
/// +---------------------------------------------------------------------------------------+

// ------------------------ VEC2 ------------------------

/**
 * @brief Test fixture for @ref flcn::Vec2 projection.
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
TYPED_TEST_SUITE(Vec2ProjectionTests, SupportedArithmeticTypes);


/**
 * @brief Test fixture for @ref flcn::Vec2 projection with NaN vectors.
 */
class Vec2ProjectionNaNTests: public testing::TestWithParam<flcn::Vec2<float>>
{};
INSTANTIATE_TEST_SUITE_P(Vec2ProjectionNanVectors, Vec2ProjectionNaNTests,
                         ::testing::Values(flcn::Vec2<float>(flcn::constants::NaN, 1.0f),
                                           flcn::Vec2<float>(1.0f, flcn::constants::NaN),
                                           flcn::Vec2<float>(flcn::constants::NaN, flcn::constants::NaN)));


/**
 * @brief Test fixture for @ref flcn::Vec2 rejection.
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
TYPED_TEST_SUITE(Vec2RejectionTests, SupportedArithmeticTypes);



/**
 * @brief Test fixture for @ref flcn::Vec2 rejection with NaN vectors.
 */
class Vec2RejectionNaNTests: public testing::TestWithParam<flcn::Vec2<float>>
{};
INSTANTIATE_TEST_SUITE_P(Vec2RejectionNaNVectors, Vec2RejectionNaNTests,
                         ::testing::Values(flcn::Vec2<float>(flcn::constants::NaN, 1.0f),
                                           flcn::Vec2<float>(1.0f, flcn::constants::NaN),
                                           flcn::Vec2<float>(flcn::constants::NaN, flcn::constants::NaN)));


// ------------------------ VEC3 ------------------------
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


/**
 * @brief Test fixture for @ref flcn::Vec3 rejection.
 *
 * @tparam T The scalar type (e.g., float, double) used for the vectors.
 */
template <typename T>
class Vec3RejectionTests: public testing::Test
{
protected:
    flcn::Vec3<T> _vec;
    flcn::Vec3<T> _parallelVec;
    flcn::Vec3<T> _fromVec;
    flcn::Vec3<T> _expectedRejection;

    void SetUp() override
    {
        _vec               = { T(1), T(2), T(3) };
        _parallelVec       = { T(2), T(4), T(6) };
        _fromVec           = { T(0), T(2), T(0) };
        _expectedRejection = { T(1), T(0), T(3) };
    }
};
/** @brief Test fixture for @ref flcn::Vec3 rejection, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vec3RejectionTests, SupportedArithmeticTypes);



/**
 * @brief Test fixture for @ref flcn::Vec3 rejection with NaN vectors.
 */
class Vec3RejectionNaNTests: public testing::TestWithParam<flcn::Vec3<float>>
{};
INSTANTIATE_TEST_SUITE_P(Vec3RejectionNaNVectors, Vec3RejectionNaNTests,
                         ::testing::Values(flcn::Vec3<float>(flcn::constants::NaN, 1.0f, 1.0f),
                                           flcn::Vec3<float>(1.0f, flcn::constants::NaN, 1.0f),
                                           flcn::Vec3<float>(1.0f, 1.0f, flcn::constants::NaN),
                                           flcn::Vec3<float>(flcn::constants::NaN, flcn::constants::NaN,
                                                             flcn::constants::NaN)));


// ------------------------ VEC4 ------------------------
/**
 * @brief Test fixture for @ref flcn::Vec4 projection.
 *
 * @tparam T The scalar type (e.g., float, double) used for the vectors.
 */
template <typename T>
class Vec4ProjectionTests: public testing::Test
{
protected:
    flcn::Vec4<T> _vec;
    flcn::Vec4<T> _perpendicularVec;
    flcn::Vec4<T> _ontoVec;
    flcn::Vec4<T> _expectedProjection;

    void SetUp() override
    {
        _vec                = { T(5), T(6), T(7), T(8) };
        _perpendicularVec   = { T(10), T(0), T(14), T(16) };
        _ontoVec            = { T(0), T(2), T(0), T(0) };
        _expectedProjection = { T(0), T(6), T(0), T(0) };
    }
};
TYPED_TEST_SUITE(Vec4ProjectionTests, SupportedArithmeticTypes);



/**
 * @brief Test fixture for @ref flcn::Vec4 projection with NaN vectors.
 */
class Vec4ProjectionNaNTests: public testing::TestWithParam<flcn::Vec4<float>>
{};
INSTANTIATE_TEST_SUITE_P(Vec4ProjectionNanVectors, Vec4ProjectionNaNTests,
                         ::testing::Values(flcn::Vec4<float>(flcn::constants::NaN, 1.0f, 1.0f, 1.0f),
                                           flcn::Vec4<float>(1.0f, flcn::constants::NaN, 1.0f, 1.0f),
                                           flcn::Vec4<float>(1.0f, 1.0f, flcn::constants::NaN, 1.0f),
                                           flcn::Vec4<float>(1.0f, 1.0f, 1.0f, flcn::constants::NaN),
                                           flcn::Vec4<float>(flcn::constants::NaN, flcn::constants::NaN,
                                                             flcn::constants::NaN, flcn::constants::NaN)));


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




/// +---------------------------------------------------------------------------------------+
/// |                            VEC2, VEC3, VEC4 (SIMD)                                    |
/// +---------------------------------------------------------------------------------------+

// ------------------------ VEC2 (SIMD) ------------------------

/**
 * @brief Test fixture for @ref flcn::simd::Vec2 projection.
 *
 * @tparam T The scalar type (e.g., float, double) used for the vectors.
 */
template <typename T>
class SimdVec2ProjectionTests: public testing::Test
{
protected:
    flcn::simd::Vec2<T> _vec;
    flcn::simd::Vec2<T> _perpendicularVec;
    flcn::simd::Vec2<T> _ontoVec;
    flcn::simd::Vec2<T> _expectedProjection;

    void SetUp() override
    {
        _vec                = { T(4), T(0) };
        _perpendicularVec   = { T(0), T(11) };
        _ontoVec            = { T(2), T(0) };
        _expectedProjection = { T(4), T(0) };
    }
};
TYPED_TEST_SUITE(SimdVec2ProjectionTests, SupportedFloatingPointTypes);


/**
 * @brief Test fixture for @ref flcn::simd::Vec2 projection with NaN vectors.
 */
class SimdVec2ProjectionNaNTests: public testing::TestWithParam<flcn::simd::Vec2<float>>
{};
INSTANTIATE_TEST_SUITE_P(SimdVec2ProjectionNanVectors, SimdVec2ProjectionNaNTests,
                         ::testing::Values(flcn::simd::Vec2<float>(flcn::constants::NaN, 1.0f),
                                           flcn::simd::Vec2<float>(1.0f, flcn::constants::NaN),
                                           flcn::simd::Vec2<float>(flcn::constants::NaN, flcn::constants::NaN)));


/**
 * @brief Test fixture for @ref flcn::simd::Vec2 rejection.
 *
 * @tparam T The scalar type (e.g., float, double) used for the vectors.
 */
template <typename T>
class SimdVec2RejectionTests: public testing::Test
{
protected:
    flcn::simd::Vec2<T> _vec;
    flcn::simd::Vec2<T> _parallelVec;
    flcn::simd::Vec2<T> _fromVec;
    flcn::simd::Vec2<T> _expectedRejection;

    void SetUp() override
    {
        _vec               = { T(4), T(0) };
        _parallelVec       = { T(6), T(0) };
        _fromVec           = { T(0), T(2) };
        _expectedRejection = { T(4), T(0) };
    }
};
TYPED_TEST_SUITE(SimdVec2RejectionTests, SupportedFloatingPointTypes);


/**
 * @brief Test fixture for @ref flcn::simd::Vec2 rejection with NaN vectors.
 */
class SimdVec2RejectionNaNTests: public testing::TestWithParam<flcn::simd::Vec2<float>>
{};
INSTANTIATE_TEST_SUITE_P(SimdVec2RejectionNaNVectors, SimdVec2RejectionNaNTests,
                         ::testing::Values(flcn::simd::Vec2<float>(flcn::constants::NaN, 1.0f),
                                           flcn::simd::Vec2<float>(1.0f, flcn::constants::NaN),
                                           flcn::simd::Vec2<float>(flcn::constants::NaN, flcn::constants::NaN)));

// ------------------------ VEC3 (SIMD) ------------------------

// ------------------------ VEC4 (SIMD) ------------------------


// GTEST IGNORED AS THE HEADER IS INCLUDED IN DEATH TESTS
GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(Vec2ProjectionNaNTests);
GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(Vec3ProjectionNaNTests);
GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(Vec4ProjectionNaNTests);
GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(SimdVec2ProjectionNaNTests);
GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(SimdVec3ProjectionNaNTests);
GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(SimdVec4ProjectionNaNTests);
GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(Vec2RejectionNaNTests);
GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(Vec3RejectionNaNTests);
GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(Vec4RejectionNaNTests);
GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(SimdVec2RejectionNaNTests);
GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(SimdVec3RejectionNaNTests);
GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(SimdVec4RejectionNaNTests);