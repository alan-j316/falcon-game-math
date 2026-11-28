#pragma once
/**
 * @file InterpolationTestFixture.h
 * @author Alan Abraham P Kochumon
 * @date Created on: November 26, 2026
 *
 * @brief Test fixtures for vector and quaternion interpolation tests.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "CommonSetup.h"

#include <falcon/math/Quat.h>
#include <falcon/math/utils/Normalization.h>
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
 * @brief Test fixture for @ref Vec2 normalization.
 * @tparam T The scalar type (int, float, double...) of the vector components.
 */
template <typename T>
class Vec2NormalizationTests: public testing::Test
{
    using R = flcn::Magnitude<T>;

protected:
    flcn::Vec2<T> _vec;
    flcn::Vec2<R> _expectedUnitVec;

    void SetUp() override
    {
        _vec             = { T(14), T(27) };
        _expectedUnitVec = { static_cast<R>(0.46031716445500037), static_cast<R>(0.8877545314489294) };
    }
};
TYPED_TEST_SUITE(Vec2NormalizationTests, SupportedArithmeticTypes);


/**
 * @brief Test fixture for @ref Vec2 normalization with zero vectors.
 * @tparam T The scalar type (int, float, double...) of the vector components.
 */
template <typename T>
class Vec2NormalizationZeroTests: public testing::Test
{
protected:
    flcn::Vec2<T> _vec;

    void SetUp() override { _vec = { T(0), T(0) }; }
};
TYPED_TEST_SUITE(Vec2NormalizationZeroTests, SupportedArithmeticTypes);


/**
 * @brief Test fixture for @ref Vec2 normalization with NaN vectors.
 */
class Vec2NormalizationNaNTests: public testing::TestWithParam<flcn::Vec2<float>>
{};
INSTANTIATE_TEST_SUITE_P(Vec2NormalizationNaNVectors, Vec2NormalizationNaNTests,
                         ::testing::Values(flcn::Vec2<float>(flcn::constants::NaN, 1.0f),
                                           flcn::Vec2<float>(1.0f, flcn::constants::NaN),
                                           flcn::Vec2<float>(flcn::constants::NaN, flcn::constants::NaN)));


// ------------------------ VEC3 ------------------------

/**
 * @brief Test fixture for @ref Vec3 normalization.
 * @tparam T The scalar type (int, float, double...) of the vector components.
 */
template <typename T>
class Vec3NormalizationTests: public testing::Test
{
    using R = flcn::Magnitude<T>;

protected:
    flcn::Vec3<T> _vec;
    flcn::Vec3<R> _expectedUnitVec;

    void SetUp() override
    {
        _vec             = { T(14), T(27), T(83) };
        _expectedUnitVec = { static_cast<R>(0.1583767155508236), static_cast<R>(0.30544080856230266),
                             static_cast<R>(0.9389476707655972) };
    }
};
TYPED_TEST_SUITE(Vec3NormalizationTests, SupportedArithmeticTypes);


/**
 * @brief Test fixture for @ref Vec3 normalization with zero vectors.
 * @tparam T The scalar type (int, float, double...) of the vector components.
 */
template <typename T>
class Vec3ZeroNormalizationTests: public testing::Test
{
protected:
    flcn::Vec3<T> _vec;

    void SetUp() override { _vec = { T(0), T(0), T(0) }; }
};
TYPED_TEST_SUITE(Vec3ZeroNormalization, SupportedArithmeticTypes);


/**
 * @brief Test fixture for @ref Vec3 normalization with NaN vectors.
 */
class Vec3NormalizationNaNTests: public testing::TestWithParam<flcn::Vec3<float>>
{};
INSTANTIATE_TEST_SUITE_P(Vec3NormalizationNaNVectors, Vec3NormalizationNaNTests,
                         ::testing::Values(flcn::Vec3<float>(flcn::constants::NaN, 1.0f, 1.0f),
                                           flcn::Vec3<float>(1.0f, flcn::constants::NaN, 1.0f),
                                           flcn::Vec3<float>(1.0f, 1.0f, flcn::constants::NaN),
                                           flcn::Vec3<float>(flcn::constants::NaN, flcn::constants::NaN,
                                                             flcn::constants::NaN)));


// ------------------------ VEC4 ------------------------

/**
 * @brief Test fixture for @ref Vec4 normalization.
 * @tparam T The scalar type (int, float, double...) of the vector components.
 */
template <typename T>
class Vec4NormalizationTests: public testing::Test
{
    using R = flcn::Magnitude<T>;


protected:
    flcn::Vec4<T> _vec;
    flcn::Vec4<R> _expectedUnitVec;

    void SetUp() override
    {
        _vec             = { T(14), T(27), T(83), T(52) };
        _expectedUnitVec = { R(0.13650905255670645), R(0.2632674585022196), R(0.8093036687290455),
                             R(0.5070336237820525) };
    }
};
TYPED_TEST_SUITE(Vec4NormalizationTests, SupportedArithmeticTypes);


/**
 * @brief Test fixture for @ref Vec4 normalization with zero vectors.
 * @tparam T The scalar type (int, float, double...) of the vector components.
 */
template <typename T>
class Vec4ZeroNormalizationTests: public testing::Test
{
protected:
    flcn::Vec4<T> _vec;

    void SetUp() override { _vec = { T(0), T(0), T(0), T(0) }; }
};

/**
 * @brief Test fixture for @ref flcn::Vec4 zero-vector normalization, parameterized by
 * @ref SupportedArithmeticTypes.
 */
TYPED_TEST_SUITE(Vec4ZeroNormalizationTests, SupportedArithmeticTypes);


/** @brief Test fixture for @ref flcn::Vec4 normalization with NaN vectors. */
class Vec4NormalizationNaNTests: public testing::TestWithParam<flcn::Vec4<float>>
{};

INSTANTIATE_TEST_SUITE_P(Vec4NormalizationNaNVectors, Vec4NormalizationNaNTests,
                         ::testing::Values(flcn::Vec4<float>(flcn::constants::NaN, 1.0f, 1.0f, 1.0f),
                                           flcn::Vec4<float>(1.0f, flcn::constants::NaN, 1.0f, 1.0f),
                                           flcn::Vec4<float>(1.0f, 1.0f, flcn::constants::NaN, 1.0f),
                                           flcn::Vec4<float>(1.0f, 1.0f, 1.0f, flcn::constants::NaN),
                                           flcn::Vec4<float>(flcn::constants::NaN, flcn::constants::NaN,
                                                             flcn::constants::NaN, flcn::constants::NaN)));



/// +---------------------------------------------------------------------------------------+
/// |                             VEC2, VEC3, VEC4(SIMD)                                    |
/// +---------------------------------------------------------------------------------------+

// ------------------------ VEC2(SIMD) ------------------------

/**
 * @brief Test fixture for @ref Vec2 normalization.
 * @tparam T The scalar type (int, float, double...) of the vector components.
 */
template <typename T>
class SimdVec2NormalizationTests: public testing::Test
{
    using R = flcn::Magnitude<T>;

protected:
    flcn::simd::Vec2<T> _vec;
    flcn::simd::Vec2<R> _expectedUnitVec;

    void SetUp() override
    {
        _vec             = { T(14), T(27) };
        _expectedUnitVec = { static_cast<R>(0.46031716445500037), static_cast<R>(0.8877545314489294) };
    }
};
TYPED_TEST_SUITE(SimdVec2NormalizationTests, SupportedFloatingPointTypes);


/**
 * @brief Test fixture for @ref Vec2 normalization with zero vectors.
 * @tparam T The scalar type (int, float, double...) of the vector components.
 */
template <typename T>
class SimdVec2NormalizationZeroTests: public testing::Test
{
protected:
    flcn::simd::Vec2<T> _vec;

    void SetUp() override { _vec = { T(0), T(0) }; }
};
TYPED_TEST_SUITE(SimdVec2NormalizationZeroTests, SupportedFloatingPointTypes);


/**
 * @brief Test fixture for @ref Vec2 normalization with NaN vectors.
 */
class SimdVec2NormalizationNaNTests: public testing::TestWithParam<flcn::simd::Vec2<float>>
{};
INSTANTIATE_TEST_SUITE_P(SimdVec2NormalizationNaNVectors, SimdVec2NormalizationNaNTests,
                         ::testing::Values(flcn::simd::Vec2<float>(flcn::constants::NaN, 1.0f),
                                           flcn::simd::Vec2<float>(1.0f, flcn::constants::NaN),
                                           flcn::simd::Vec2<float>(flcn::constants::NaN, flcn::constants::NaN)));



// ------------------------ VEC3(SIMD) ------------------------

/**
 * @brief Test fixture for @ref Vec3 normalization.
 * @tparam T The scalar type (int, float, double...) of the vector components.
 */
template <typename T>
class SimdVec3NormalizationTests: public testing::Test
{
    using R = flcn::Magnitude<T>;

protected:
    flcn::simd::Vec3<T> _vec;
    flcn::simd::Vec3<R> _expectedUnitVec;

    void SetUp() override
    {
        _vec             = { T(14), T(27), T(83) };
        _expectedUnitVec = { static_cast<R>(0.1583767155508236), static_cast<R>(0.30544080856230266),
                             static_cast<R>(0.9389476707655972) };
    }
};
TYPED_TEST_SUITE(SimdVec3NormalizationTests, SupportedFloatingPointTypes);


/**
 * @brief Test fixture for @ref Vec3 normalization with zero vectors.
 * @tparam T The scalar type (int, float, double...) of the vector components.
 */
template <typename T>
class SimdVec3ZeroNormalizationTests: public testing::Test
{
protected:
    flcn::simd::Vec3<T> _vec;

    void SetUp() override { _vec = { T(0), T(0), T(0) }; }
};
TYPED_TEST_SUITE(SimdVec3ZeroNormalization, SupportedFloatingPointTypes);


/**
 * @brief Test fixture for @ref Vec3 normalization with NaN vectors.
 */
class SimdVec3NormalizationNaNTests: public testing::TestWithParam<flcn::simd::Vec3<float>>
{};
INSTANTIATE_TEST_SUITE_P(SimdVec3NormalizationNaNVectors, SimdVec3NormalizationNaNTests,
                         ::testing::Values(flcn::simd::Vec3<float>(flcn::constants::NaN, 1.0f, 1.0f),
                                           flcn::simd::Vec3<float>(1.0f, flcn::constants::NaN, 1.0f),
                                           flcn::simd::Vec3<float>(1.0f, 1.0f, flcn::constants::NaN),
                                           flcn::simd::Vec3<float>(flcn::constants::NaN, flcn::constants::NaN,
                                                                   flcn::constants::NaN)));



// ------------------------ VEC4(SIMD) ------------------------



/// +---------------------------------------------------------------------------------------+
/// |                                 QUATERNIONS                                           |
/// +---------------------------------------------------------------------------------------+
