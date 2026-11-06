/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verify @ref flcn::Vec4 initialization logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec4TestSetup.h"


/**
 * @addtogroup T_FALCON_Vec4_Init
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec4 initialization.
     */
    template <typename>
    class Vec4InitializationTests: public testing::Test
    {};
    /** @brief Test fixture for @ref flcn::Vec4 initialization, parameterized by @ref SupportedTypes */
    TYPED_TEST_SUITE(Vec4InitializationTests, SupportedTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_wrapper
    {

        /// @test Verify that Vec4 can be initialized with parameters at compile time.
        constexpr flcn::Vec4 SCALAR_INIT_VEC(1, 2, 3, 4);
        static_assert(SCALAR_INIT_VEC.x() == 1);
        static_assert(SCALAR_INIT_VEC.y() == 2);
        static_assert(SCALAR_INIT_VEC.z() == 3);
        static_assert(SCALAR_INIT_VEC.w() == 4);

        /// @test Verify that Vec4 can be initialized with a 2 CVec2 at compile time.
        constexpr flcn::Vec4<int> VEC2_INIT_VEC({ 1, 2 }, { 3, 4 });
        static_assert(VEC2_INIT_VEC.x() == 1);
        static_assert(VEC2_INIT_VEC.y() == 2);
        static_assert(VEC2_INIT_VEC.z() == 3);
        static_assert(VEC2_INIT_VEC.w() == 4);

        /// @test Verify that Vec4 can be initialized with a scalar and Vec3 at compile time.
        constexpr flcn::Vec4 VEC3_SCALAR_INIT_VEC(1, { 2, 3, 4 });
        static_assert(VEC3_SCALAR_INIT_VEC.x() == 1);
        static_assert(VEC3_SCALAR_INIT_VEC.y() == 2);
        static_assert(VEC3_SCALAR_INIT_VEC.z() == 3);
        static_assert(VEC3_SCALAR_INIT_VEC.w() == 4);

        /// @test Verify that Vec4 can be initialized with a Vec3 and scalar at compile time.
        constexpr flcn::Vec4 SCALAR_VEC3_INIT_VEC({ 1, 2, 3 }, 4);
        static_assert(SCALAR_VEC3_INIT_VEC.x() == 1);
        static_assert(SCALAR_VEC3_INIT_VEC.y() == 2);
        static_assert(SCALAR_VEC3_INIT_VEC.z() == 3);
        static_assert(SCALAR_VEC3_INIT_VEC.w() == 4);

        /// @test Verify that Vec4 can be initialized using braced initialization at compile time.
        constexpr flcn::Vec4<int> BRACED_INIT_VEC{};
        static_assert(BRACED_INIT_VEC.x() == 0);
        static_assert(BRACED_INIT_VEC.y() == 0);
        static_assert(BRACED_INIT_VEC.z() == 0);
        static_assert(BRACED_INIT_VEC.z() == 0);

    } // namespace static_wrapper
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

/** @test Verify that the default constructor initializes all components to zero. */
TYPED_TEST(Vec4InitializationTests, EmptyConstructorInitializesZeroVector)
{
    const flcn::Vec4<TypeParam> vec{};
    EXPECT_VEC_ZERO(vec);
}


/** @test Verify that the parameterized constructor correctly assigns components from the provided arguments. */
TYPED_TEST(Vec4InitializationTests, ConstructorInitializesVectorsWithCorrectValue)
{
    const TypeParam a = static_cast<TypeParam>(3);
    const TypeParam b = static_cast<TypeParam>(1);
    const TypeParam c = static_cast<TypeParam>(6);
    const TypeParam d = static_cast<TypeParam>(4);

    const flcn::Vec4<TypeParam> vec(a, b, c, d);
    EXPECT_VEC_CONTAINS(vec, a, b, c, d);
}


/**
 * @test Verify that the parameterized constructor correctly composes a 4D vector from
 *       two @ref flcn::CVec2 instances.
 */
TYPED_TEST(Vec4InitializationTests, Two2DVectorsCanInitializeA4DVector)
{
    const TypeParam a = static_cast<TypeParam>(3);
    const TypeParam b = static_cast<TypeParam>(1);
    const TypeParam c = static_cast<TypeParam>(6);
    const TypeParam d = static_cast<TypeParam>(4);
    const flcn::CVec2<TypeParam> vec1(a, b);
    const flcn::CVec2<TypeParam> vec2(c, d);

    const flcn::Vec4<TypeParam> vec(vec1, vec2);
    EXPECT_VEC_CONTAINS(vec, a, b, c, d);
}


/**
 * @test Verify that the parameterized constructor correctly composes a 4D vector from a
 *       @ref flcn::Vec3 instance and a scalar.
 */
TYPED_TEST(Vec4InitializationTests, 3DVectorAndScalarCanInitializeA4DVector)
{
    const TypeParam a = static_cast<TypeParam>(3);
    const TypeParam b = static_cast<TypeParam>(1);
    const TypeParam c = static_cast<TypeParam>(6);
    const flcn::Vec3 vec1(a, b, c);
    const TypeParam scalar = static_cast<TypeParam>(4);

    const flcn::Vec4 vec(vec1, scalar);
    EXPECT_VEC_CONTAINS(vec, a, b, c, scalar);
}


/**
 * @test Verify that the parameterized constructor correctly composes a 4D vector from a scalar and
 *        a @ref flcn::Vec3 instance.
 */
TYPED_TEST(Vec4InitializationTests, ScalarAnd3DVectorCanInitializeA4DVector)
{
    const TypeParam a = static_cast<TypeParam>(3);
    const TypeParam b = static_cast<TypeParam>(1);
    const TypeParam c = static_cast<TypeParam>(6);
    const flcn::Vec3 vec1(a, b, c);
    const TypeParam scalar = static_cast<TypeParam>(4);

    const flcn::Vec4 vec(scalar, vec1);
    EXPECT_VEC_CONTAINS(vec, scalar, a, b, c);
}


/** @} */
