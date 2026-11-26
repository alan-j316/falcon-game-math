#pragma once
/**
 * @file BoundsTestFixture.h
 * @author Alan Abraham P Kochumon
 * @date Created on: November 26, 2026
 *
 * @brief Test fixtures for math structure bounds (min, max, clamp) tests.
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

// ------------------------ VEC2 ------------------------
/**
 * @brief Test fixture for @ref flcn::Vec2 min function.
 * @tparam T The numeric type of vector components.
 */
template <typename T>
class Vec2MinTests: public testing::Test
{
public:
    flcn::Vec2<T> a, b, expectedMin;

protected:
    void SetUp() override
    {
        a           = { T(5.3923283), T(0.5383293) };
        b           = { T(3.239823), T(9.932803) };
        expectedMin = { T(3.239823), T(0.5383293) };
    }
};
TYPED_TEST_SUITE(Vec2MinTests, SupportedArithmeticTypes);


/**
 * @brief Test fixture for @ref flcn::Vec2 max function.
 * @tparam T The numeric type of vector components.
 */
template <typename T>
class Vec2MaxTests: public testing::Test
{
public:
    flcn::Vec2<T> a, b, expectedMax;

protected:
    void SetUp() override
    {
        a           = { T(5.3923283), T(0.5383293) };
        b           = { T(3.239823), T(9.932803) };
        expectedMax = { T(5.3923283), T(9.932803) };
    }
};
TYPED_TEST_SUITE(Vec2MaxTests, SupportedArithmeticTypes);


// ------------------------ VEC3 ------------------------
/**
 * @brief Test fixture for @ref flcn::Vec3 min function.
 * @tparam T The numeric type of vector components.
 */
template <typename T>
class Vec3MinTests: public testing::Test
{
public:
    flcn::Vec3<T> a, b, expectedMin;

protected:
    void SetUp() override
    {
        a           = { T(5.3923283), T(0.5383293), T(38.280234) };
        b           = { T(3.239823), T(9.932803), T(121.2938223) };
        expectedMin = { T(3.239823), T(0.5383293), T(38.280234) };
    }
};
TYPED_TEST_SUITE(Vec3MinTests, SupportedArithmeticTypes);


/**
 * @brief Test fixture for @ref flcn::Vec3 max function.
 * @tparam T The numeric type of vector components.
 */
template <typename T>
class Vec3MaxTests: public testing::Test
{
public:
    flcn::Vec3<T> a, b, expectedMax;

protected:
    void SetUp() override
    {
        a           = { T(5.3923283), T(0.5383293), T(38.280234) };
        b           = { T(3.239823), T(9.932803), T(121.2938223) };
        expectedMax = { T(5.3923283), T(9.932803), T(121.2938223) };
    }
};
TYPED_TEST_SUITE(Vec3MaxTests, SupportedArithmeticTypes);


// ------------------------ VEC4 ------------------------
/**
 * @brief Test fixture for @ref flcn::Vec4 min function.
 * @tparam T The numeric type of vector components.
 */
template <typename T>
class Vec4MinTests: public testing::Test
{
public:
    flcn::Vec4<T> a, b, expectedMin;

protected:
    void SetUp() override
    {
        a           = { T(5.3923283), T(0.5383293), T(38.280234), T(15.93283) };
        b           = { T(3.239823), T(9.932803), T(121.2938223), T(102.39823) };
        expectedMin = { T(3.239823), T(0.5383293), T(38.280234), T(15.93283) };
    }
};
TYPED_TEST_SUITE(Vec4MinTests, SupportedArithmeticTypes);


/**
 * @brief Test fixture for @ref flcn::Vec4 max function.
 * @tparam T The numeric type of vector components.
 */
template <typename T>
class Vec4MaxTests: public testing::Test
{
public:
    flcn::Vec4<T> a, b, expectedMax;

protected:
    void SetUp() override
    {
        a           = { T(5.3923283), T(0.5383293), T(38.280234), T(15.93283) };
        b           = { T(3.239823), T(9.932803), T(121.2938223), T(102.39823) };
        expectedMax = { T(5.3923283), T(9.932803), T(121.2938223), T(102.39823) };
    }
};
TYPED_TEST_SUITE(Vec4MaxTests, SupportedArithmeticTypes);



/// +---------------------------------------------------------------------------------------+
/// |                            VEC2, VEC3, VEC4 (SIMD)                                    |
/// +---------------------------------------------------------------------------------------+

// ------------------------ VEC2 (SIMD) ------------------------
/**
 * @brief Test fixture for @ref flcn::simd::Vec2 min function.
 * @tparam T The numeric type of vector components.
 */
template <typename T>
class SimdVec2MinTests: public testing::Test
{
public:
    flcn::simd::Vec2<T> a, b, expectedMin;

protected:
    void SetUp() override
    {
        a           = { T(5.3923283), T(0.5383293) };
        b           = { T(3.239823), T(9.932803) };
        expectedMin = { T(3.239823), T(0.5383293) };
    }
};
TYPED_TEST_SUITE(SimdVec2MinTests, SupportedArithmeticTypes);


/**
 * @brief Test fixture for @ref flcn::simd::Vec2 max function.
 * @tparam T The numeric type of vector components.
 */
template <typename T>
class SimdVec2MaxTests: public testing::Test
{
public:
    flcn::simd::Vec2<T> a, b, expectedMax;

protected:
    void SetUp() override
    {
        a           = { T(5.3923283), T(0.5383293) };
        b           = { T(3.239823), T(9.932803) };
        expectedMax = { T(5.3923283), T(9.932803) };
    }
};
TYPED_TEST_SUITE(SimdVec2MaxTests, SupportedArithmeticTypes);



// ------------------------ VEC3 (SIMD) ------------------------
/**
 * @brief Test fixture for @ref flcn::simd::Vec3 min function.
 * @tparam T The numeric type of vector components.
 */
template <typename T>
class SimdVec3MinTests: public testing::Test
{
public:
    flcn::simd::Vec3<T> a, b, expectedMin;

protected:
    void SetUp() override
    {
        a           = { T(5.3923283), T(0.5383293), T(38.280234) };
        b           = { T(3.239823), T(9.932803), T(121.2938223) };
        expectedMin = { T(3.239823), T(0.5383293), T(38.280234) };
    }
};
TYPED_TEST_SUITE(SimdVec3MinTests, SupportedArithmeticTypes);


/**
 * @brief Test fixture for @ref flcn::simd::Vec3 max function.
 * @tparam T The numeric type of vector components.
 */
template <typename T>
class SimdVec3MaxTests: public testing::Test
{
public:
    flcn::simd::Vec3<T> a, b, expectedMax;

protected:
    void SetUp() override
    {
        a           = { T(5.3923283), T(0.5383293), T(38.280234) };
        b           = { T(3.239823), T(9.932803), T(121.2938223) };
        expectedMax = { T(5.3923283), T(9.932803), T(121.2938223) };
    }
};
TYPED_TEST_SUITE(SimdVec3MaxTests, SupportedArithmeticTypes);

// ------------------------ VEC4 (SIMD) ------------------------