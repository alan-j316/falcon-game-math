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

#include <falcon/math/Quaternion.h>
#include <falcon/math/utils/Interpolation.h>
#include <falcon/math/vectors/Vec2.h>
#include <falcon/math/vectors/Vec3.h>
#include <falcon/math/vectors/Vec4.h>
#include <falcon/math/vectors/simd/Vec2.h>
#include <falcon/math/vectors/simd/Vec3.h>


/// +---------------------------------------------------------------------------------------+
/// |                           VEC2, VEC3, VEC4 (SCALAR)                                   |
/// +---------------------------------------------------------------------------------------+

// ------------------------ TEST PARAMS ------------------------

struct Vec2MixParams
{
    flcn::Vec2F a;
    flcn::Vec2F b;
    float factor;
    flcn::Vec2F expected;
};

struct Vec3MixParams
{
    flcn::Vec3F a;
    flcn::Vec3F b;
    float factor;
    flcn::Vec3F expected;
};

struct Vec4MixParams
{
    flcn::Vec4F a;
    flcn::Vec4F b;
    float factor;
    flcn::Vec4F expected;
};



// ------------------------ VEC2 ------------------------

/**
 * @brief Test fixture for @ref flcn::Vec2 mix function.
 * @tparam T The numeric type of vector components.
 */
template <typename T>
class Vec2MixTests: public testing::Test
{
public:
    flcn::Vec2<T> a, b, expectedFP, expectedInt;
    float factor = 0.5f;

protected:
    void SetUp() override
    {
        a           = { T(30.12389399999999995), T(5.03127999999999975) };
        b           = { T(4.23901000000000039), T(0.10348000000000000) };
        expectedFP  = { T(17.18145200000000017), T(2.56738000000000000) };
        expectedInt = { T(17), T(2) };
    }
};
TYPED_TEST_SUITE(Vec2MixTests, SupportedArithmeticTypes);


/**
 * @brief Test fixture for @ref flcn::Vec2 mix for testing various parameters.
 */
class Vec2MixParameterizedTests: public testing::TestWithParam<Vec2MixParams>
{};
INSTANTIATE_TEST_SUITE_P(
    Vec2MixTests, Vec2MixParameterizedTests,
    ::testing::Values(Vec2MixParams{ flcn::Vec2(30.12389f, 5.031279f), flcn::Vec2(4.23901f, 0.10348f), 0.5f,
                                     flcn::Vec2(17.18145f, 2.56738f) },
                      Vec2MixParams{ flcn::Vec2(30.12389f, 5.031279f), flcn::Vec2(4.23901f, 0.10348f), 0.25f,
                                     flcn::Vec2(23.65267f, 3.79932f) },
                      Vec2MixParams{ flcn::Vec2(30.12389f, 5.031279f), flcn::Vec2(4.23901f, 0.10348f), 1.0f,
                                     flcn::Vec2(4.23901f, 0.10348f) },
                      Vec2MixParams{ flcn::Vec2(30.12389f, 5.031279f), flcn::Vec2(4.23901f, 0.10348f), 0.0f,
                                     flcn::Vec2(30.12389f, 5.031279f) }));


// ------------------------ VEC3 ------------------------
/**
 * @brief Test fixture for @ref flcn::Vec3 mix function.
 * @tparam T The numeric type of vector components.
 */
template <typename T>
class Vec3MixTests: public testing::Test
{
public:
    flcn::Vec3<T> a, b, expectedFP, expectedInt;
    float factor = 0.5f;

protected:
    void SetUp() override
    {
        a           = { T(30.12389399999999995), T(5.03127999999999975), T(1.01238000000000006) };
        b           = { T(4.23901000000000039), T(0.10348000000000000), T(1.23893000000000009) };
        expectedFP  = { T(17.18145200000000017), T(2.56738000000000000), T(1.12565500000000007) };
        expectedInt = { T(17), T(2), T(1) };
    }
};
TYPED_TEST_SUITE(Vec3MixTests, SupportedArithmeticTypes);


/**
 * @brief Test fixture for @ref flcn::Vec3 mix for testing various parameters.
 */
class Vec3MixParameterizedTests: public testing::TestWithParam<Vec3MixParams>
{};
INSTANTIATE_TEST_SUITE_P(Vec3MixTests, Vec3MixParameterizedTests,
                         ::testing::Values(Vec3MixParams{ flcn::Vec3(30.12389f, 5.031279f, 1.01238f),
                                                          flcn::Vec3(4.23901f, 0.10348f, 1.23893f), 0.5f,
                                                          flcn::Vec3(17.18145f, 2.56738f, 1.125655f) },
                                           Vec3MixParams{ flcn::Vec3(30.12389f, 5.031279f, 1.01238f),
                                                          flcn::Vec3(4.23901f, 0.10348f, 1.23893f), 0.25f,
                                                          flcn::Vec3(23.65267f, 3.79932f, 1.069017f) },
                                           Vec3MixParams{ flcn::Vec3(30.12389f, 5.031279f, 1.01238f),
                                                          flcn::Vec3(4.23901f, 0.10348f, 1.23893f), 1.0f,
                                                          flcn::Vec3(4.23901f, 0.10348f, 1.23893f) },
                                           Vec3MixParams{ flcn::Vec3(30.12389f, 5.031279f, 1.01238f),
                                                          flcn::Vec3(4.23901f, 0.10348f, 1.23893f), 0.0f,
                                                          flcn::Vec3(30.12389f, 5.031279f, 1.01238f) }));




// ------------------------ VEC4 ------------------------

/**
 * @brief Test fixture for @ref flcn::Vec4 mix function.
 * @tparam T The numeric type of vector components.
 */
template <typename T>
class Vec4MixTests: public testing::Test
{
public:
    flcn::Vec4<T> a, b, expectedFP, expectedInt;
    float factor = 0.5f;

protected:
    void SetUp() override
    {
        a = { T(30.12389399999999995), T(5.03127999999999975), T(1.01238000000000006), T(1.90300000000000002) };
        b = { T(4.23901000000000039), T(0.10348000000000000), T(1.23893000000000009), T(5.03892000000000007) };
        expectedFP  = { T(17.18145200000000017), T(2.56738000000000000), T(1.12565500000000007),
                        T(3.47095999999999982) };
        expectedInt = { T(17), T(2), T(1), T(3) };
    }
};
TYPED_TEST_SUITE(Vec4MixTests, SupportedArithmeticTypes);

/**
 * @brief Test fixture for @ref flcn::Vec4 mix for testing various parameters.
 */
class Vec4MixParameterizedTests: public testing::TestWithParam<Vec4MixParams>
{};
INSTANTIATE_TEST_SUITE_P(Vec4MixTests, Vec4MixParameterizedTests,
                         ::testing::Values(Vec4MixParams{ flcn::Vec4(30.12389f, 5.031279f, 1.01238f, 1.903000f),
                                                          flcn::Vec4(4.23901f, 0.10348f, 1.23893f, 5.038920f), 0.5f,
                                                          flcn::Vec4(17.18145f, 2.56738f, 1.125655f, 3.470959f) },
                                           Vec4MixParams{ flcn::Vec4(30.12389f, 5.031279f, 1.01238f, 1.903000f),
                                                          flcn::Vec4(4.23901f, 0.10348f, 1.23893f, 5.038920f), 0.25f,
                                                          flcn::Vec4(23.65267f, 3.79932f, 1.069017f, 2.68698f) },
                                           Vec4MixParams{ flcn::Vec4(30.12389f, 5.031279f, 1.01238f, 1.903000f),
                                                          flcn::Vec4(4.23901f, 0.10348f, 1.23893f, 5.038920f), 1.0f,
                                                          flcn::Vec4(4.23901f, 0.10348f, 1.23893f, 5.038920f) },
                                           Vec4MixParams{ flcn::Vec4(30.12389f, 5.031279f, 1.01238f, 1.903000f),
                                                          flcn::Vec4(4.23901f, 0.10348f, 1.23893f, 5.038920f), 0.0f,
                                                          flcn::Vec4(30.12389f, 5.031279f, 1.01238f, 1.903000f) }));



/// +---------------------------------------------------------------------------------------+
/// |                             VEC2, VEC3, VEC4(SIMD)                                    |
/// +---------------------------------------------------------------------------------------+

// ------------------------ TEST PARAMS ------------------------

struct SimdVec2MixParams
{
    flcn::simd::Vec2F a;
    flcn::simd::Vec2F b;
    float factor;
    flcn::simd::Vec2F expected;
};

struct SimdVec3MixParams
{
    flcn::simd::Vec3F a;
    flcn::simd::Vec3F b;
    float factor;
    flcn::simd::Vec3F expected;
};


// ------------------------ VEC2(SIMD) ------------------------
/**
 * @brief Test fixture for @ref flcn::simd::Vec2 mix function.
 * @tparam T The numeric type of vector components.
 */
template <typename T>
class SimdVec2MixTests: public testing::Test
{
public:
    flcn::simd::Vec2<T> a, b, expected;
    float factor = 0.5f;

protected:
    void SetUp() override
    {
        a           = { T(30.12389399999999995), T(5.03127999999999975) };
        b           = { T(4.23901000000000039), T(0.10348000000000000) };
        expected  = { T(17.18145200000000017), T(2.56738000000000000) };
    }
};
TYPED_TEST_SUITE(SimdVec2MixTests, SupportedFloatingPointTypes);


/**
 * @brief Test fixture for @ref flcn::simd::Vec2 mix for testing various parameters.
 */
class SimdVec2MixParameterizedTests: public testing::TestWithParam<SimdVec2MixParams>
{};
INSTANTIATE_TEST_SUITE_P(
    SimdVec2MixTests, SimdVec2MixParameterizedTests,
    ::testing::Values(SimdVec2MixParams{ flcn::simd::Vec2(30.12389f, 5.031279f), flcn::simd::Vec2(4.23901f, 0.10348f),
                                         0.5f, flcn::simd::Vec2(17.18145f, 2.56738f) },
                      SimdVec2MixParams{ flcn::simd::Vec2(30.12389f, 5.031279f), flcn::simd::Vec2(4.23901f, 0.10348f),
                                         0.25f, flcn::simd::Vec2(23.65267f, 3.79932f) },
                      SimdVec2MixParams{ flcn::simd::Vec2(30.12389f, 5.031279f), flcn::simd::Vec2(4.23901f, 0.10348f),
                                         1.0f, flcn::simd::Vec2(4.23901f, 0.10348f) },
                      SimdVec2MixParams{ flcn::simd::Vec2(30.12389f, 5.031279f), flcn::simd::Vec2(4.23901f, 0.10348f),
                                         0.0f, flcn::simd::Vec2(30.12389f, 5.031279f) }));


// ------------------------ VEC3(SIMD) ------------------------

/**
 * @brief Test fixture for @ref flcn::simd::Vec3 mix function.
 * @tparam T The numeric type of vector components.
 */
template <typename T>
class SimdVec3MixTests: public testing::Test
{
public:
    flcn::simd::Vec3<T> a, b, expected;
    T factor = T(0.5f); // Only floating point mix types.

protected:
    void SetUp() override
    {
        a        = { T(30.12389399999999995), T(5.03127999999999975), T(1.01238000000000006) };
        b        = { T(4.23901000000000039), T(0.10348000000000000), T(1.23893000000000009) };
        expected = { T(17.18145200000000017), T(2.56738000000000000), T(1.12565500000000007) };
    }
};
TYPED_TEST_SUITE(SimdVec3MixTests, SupportedFloatingPointTypes);


/**
 * @brief Test fixture for @ref flcn::Vec3 mix for testing various parameters.
 */
class SimdVec3MixParameterizedTests: public testing::TestWithParam<SimdVec3MixParams>
{};
INSTANTIATE_TEST_SUITE_P(SimdVec3MixTests, SimdVec3MixParameterizedTests,
                         ::testing::Values(SimdVec3MixParams{ flcn::simd::Vec3(30.12389f, 5.031279f, 1.01238f),
                                                              flcn::simd::Vec3(4.23901f, 0.10348f, 1.23893f), 0.5f,
                                                              flcn::simd::Vec3(17.18145f, 2.56738f, 1.125655f) },
                                           SimdVec3MixParams{ flcn::simd::Vec3(30.12389f, 5.031279f, 1.01238f),
                                                              flcn::simd::Vec3(4.23901f, 0.10348f, 1.23893f), 0.25f,
                                                              flcn::simd::Vec3(23.65267f, 3.79932f, 1.069017f) },
                                           SimdVec3MixParams{ flcn::simd::Vec3(30.12389f, 5.031279f, 1.01238f),
                                                              flcn::simd::Vec3(4.23901f, 0.10348f, 1.23893f), 1.0f,
                                                              flcn::simd::Vec3(4.23901f, 0.10348f, 1.23893f) },
                                           SimdVec3MixParams{ flcn::simd::Vec3(30.12389f, 5.031279f, 1.01238f),
                                                              flcn::simd::Vec3(4.23901f, 0.10348f, 1.23893f), 0.0f,
                                                              flcn::simd::Vec3(30.12389f, 5.031279f, 1.01238f) }));

// ------------------------ VEC4(SIMD) ------------------------



/// +---------------------------------------------------------------------------------------+
/// |                                 QUATERNIONS                                           |
/// +---------------------------------------------------------------------------------------+
