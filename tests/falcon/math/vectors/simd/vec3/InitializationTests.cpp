/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 10, 2026
 *
 * @brief Verify @ref flcn::simd::Vec3 initialization logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"


/**
 * @addtogroup T_Falcon_Vec3_Init
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec3 initialization.
     */
    template <typename>
    class SimdVec3InitializationTests: public testing::Test
    {};
    TYPED_TEST_SUITE(SimdVec3InitializationTests, SupportedTypes);
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

/** @test Verify that the default constructor initializes all components to zero. */
TYPED_TEST(SimdVec3InitializationTests, EmptyConstructorInitializesZeroVector)
{
    const flcn::simd::Vec3<TypeParam> vec{};
    EXPECT_VEC_ZERO(vec);
}


TYPED_TEST(SimdVec3InitializationTests, Ctor_SingleParameterInitializesVector)
{
    const auto a = static_cast<TypeParam>(3);
    const flcn::simd::Vec3<TypeParam> vec(a);
    EXPECT_VEC_CONTAINS(vec, a, a, a);
}


/** @test Verify that the parameterized constructor correctly assigns components from the provided arguments. */
TYPED_TEST(SimdVec3InitializationTests, ConstructorParametersInitializesVector)
{
    const auto a = static_cast<TypeParam>(3);
    const auto b = static_cast<TypeParam>(1);
    const auto c = static_cast<TypeParam>(6);

    const flcn::simd::Vec3<TypeParam> vec(a, b, c);
    EXPECT_VEC_CONTAINS(vec, a, b, c);
}


/**
 * @test Verify that the parameterized constructor correctly composes a 3D vector from a
 *       @ref flcn::simd::Vec3 instance and a scalar.
 */
TYPED_TEST(SimdVec3InitializationTests, 2DVectorAndScalarCanInitializeA3DVector)
{
    const auto a = static_cast<TypeParam>(3);
    const auto b = static_cast<TypeParam>(1);
    const flcn::simd::Vec2<TypeParam> vec1(a, b);
    const auto scalar = static_cast<TypeParam>(6);

    const flcn::simd::Vec3<TypeParam> vec(vec1, scalar);
    EXPECT_VEC_CONTAINS(vec, a, b, scalar);
}


/**
 * @test Verify that the parameterized constructor correctly composes a 3D vector from a
 *       @ref flcn::simd::Vec3 instance and a scalar.
 */
TYPED_TEST(SimdVec3InitializationTests, ScalarAnd2DVectorCanInitializeA3DVector)
{
    const auto scalar = static_cast<TypeParam>(3);
    const auto a      = static_cast<TypeParam>(1);
    const auto b      = static_cast<TypeParam>(6);
    const flcn::simd::Vec2<TypeParam> vec1(a, b);

    const flcn::simd::Vec3<TypeParam> vec(scalar, vec1);
    EXPECT_VEC_CONTAINS(vec, scalar, a, b);
}
