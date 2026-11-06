/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref flcn::CVec2 initialization logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CVec2TestSetup.h"



/**
 * @addtogroup T_FALCON_CVec2_Init
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref CVec2 initialization.
     */
    template <typename>
    class CVec2InitializationTests: public testing::Test
    {};
    TYPED_TEST_SUITE(CVec2InitializationTests, SupportedTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_wrapper
    {

        /// @test Verify that CVec2 can be initialized with a single parameters at compile time.
        constexpr flcn::CVec2 SCALAR_INIT_VEC1(1);
        static_assert(SCALAR_INIT_VEC1.x() == 1);
        static_assert(SCALAR_INIT_VEC1.y() == 1);

        /// @test Verify that CVec2 can be initialized with parameters at compile time.
        constexpr flcn::CVec2 SCALAR_INIT_VEC2(1, 2);
        static_assert(SCALAR_INIT_VEC2.x() == 1);
        static_assert(SCALAR_INIT_VEC2.y() == 2);

        /// @test Verify that CVec2 can be initialized using braced initialization at compile time.
        constexpr flcn::CVec2<int> BRACED_INIT_VEC{};
        static_assert(BRACED_INIT_VEC.x() == 0);
        static_assert(BRACED_INIT_VEC.y() == 0);

    } // namespace static_wrapper
} // namespace


/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(CVec2InitializationTests, EmptyCtor_InitializesZeroVector)
{
    const flcn::CVec2<TypeParam> vec{};
    EXPECT_VEC_ZERO(vec);
}


TYPED_TEST(CVec2InitializationTests, Ctor_ParametersInitializesVector)
{
    const TypeParam a = static_cast<TypeParam>(3);
    const TypeParam b = static_cast<TypeParam>(1);

    const flcn::CVec2<TypeParam> vec(a, b);
    EXPECT_VEC_CONTAINS(vec, a, b);
}


TYPED_TEST(CVec2InitializationTests, Ctor_SingleParameterInitializesVector)
{
    const auto a = static_cast<TypeParam>(3);
    const flcn::CVec2<TypeParam> vec(a);
    EXPECT_VEC_CONTAINS(vec, a, a);
}

/** @} */
