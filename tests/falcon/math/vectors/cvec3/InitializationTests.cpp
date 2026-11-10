/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verify @ref flcn::CVec3 initialization logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CVec3TestSetup.h"


/**
 * @addtogroup T_Falcon_CVec3_Init
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref CVec3 initialization.
     */
    template <typename>
    class CVec3InitializationTests: public testing::Test
    {};
    TYPED_TEST_SUITE(CVec3InitializationTests, SupportedTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_wrapper
    {
        /// @test Verify that CVec3 can be initialized with parameters at compile time.
        constexpr flcn::CVec3 SCALAR_INIT_VEC(1, 2, 3);
        static_assert(SCALAR_INIT_VEC.x() == 1);
        static_assert(SCALAR_INIT_VEC.y() == 2);
        static_assert(SCALAR_INIT_VEC.z() == 3);

        /// @test Verify that CVec3 can be initialized with a CVec2 and scalar at compile time.
        constexpr flcn::CVec3 VEC2_SCALAR_INIT_VEC({ 1, 2 }, 3);
        static_assert(VEC2_SCALAR_INIT_VEC.x() == 1);
        static_assert(VEC2_SCALAR_INIT_VEC.y() == 2);
        static_assert(VEC2_SCALAR_INIT_VEC.z() == 3);

        /// @test Verify that CVec3 can be initialized with a scalar and CVec2 at compile time.
        constexpr flcn::CVec3 SCALAR_VEC2_INIT_VEC(1, { 2, 3 });
        static_assert(SCALAR_VEC2_INIT_VEC.x() == 1);
        static_assert(SCALAR_VEC2_INIT_VEC.y() == 2);
        static_assert(SCALAR_VEC2_INIT_VEC.z() == 3);

        /// @test Verify that CVec3 can be initialized using braced initialization at compile time.
        constexpr flcn::CVec3<int> BRACED_INIT_VEC{};
        static_assert(BRACED_INIT_VEC.x() == 0);
        static_assert(BRACED_INIT_VEC.y() == 0);
        static_assert(BRACED_INIT_VEC.z() == 0);
    } // namespace static_wrapper
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

/** @test Verify that the default constructor initializes all components to zero. */
TYPED_TEST(CVec3InitializationTests, EmptyConstructorInitializesZeroVector)
{
    const flcn::CVec3<TypeParam> vec{};
    EXPECT_VEC_ZERO(vec);
}


/** @test Verify that the parameterized constructor correctly assigns components from the provided arguments. */
TYPED_TEST(CVec3InitializationTests, ConstructorParametersInitializesVector)
{
    const TypeParam a = static_cast<TypeParam>(3);
    const TypeParam b = static_cast<TypeParam>(1);
    const TypeParam c = static_cast<TypeParam>(6);

    const flcn::CVec3<TypeParam> vec(a, b, c);
    EXPECT_VEC_CONTAINS(vec, a, b, c);
}


/**
 * @test Verify that the parameterized constructor correctly composes a 3D vector from a
 *       @ref flcn::CVec3 instance and a scalar.
 */
TYPED_TEST(CVec3InitializationTests, 2DVectorAndScalarCanInitializeA3DVector)
{
    const TypeParam a = static_cast<TypeParam>(3);
    const TypeParam b = static_cast<TypeParam>(1);
    const flcn::CVec2<TypeParam> vec1(a, b);
    const TypeParam scalar = static_cast<TypeParam>(6);

    const flcn::CVec3<TypeParam> vec(vec1, scalar);
    EXPECT_VEC_CONTAINS(vec, a, b, scalar);
}


/**
 * @test Verify that the parameterized constructor correctly composes a 3D vector from a
 *       @ref flcn::CVec3 instance and a scalar.
 */
TYPED_TEST(CVec3InitializationTests, ScalarAnd2DVectorCanInitializeA3DVector)
{
    const TypeParam scalar = static_cast<TypeParam>(3);
    const TypeParam a      = static_cast<TypeParam>(1);
    const TypeParam b      = static_cast<TypeParam>(6);
    const flcn::CVec2<TypeParam> vec1(a, b);

    const flcn::CVec3<TypeParam> vec(scalar, vec1);
    EXPECT_VEC_CONTAINS(vec, scalar, a, b);
}
