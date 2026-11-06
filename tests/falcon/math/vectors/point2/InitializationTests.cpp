/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 30, 2026
 *
 * @brief Verify @ref flcn::Point2 initialization logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Point2TestSetup.h"


/**
 * @addtogroup T_FALCON_Point2_Init
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/
    /**
     * @brief Test fixture for @ref flcn::Point2 initialization(CTOR).
     */
    template <typename>
    class Point2InitializationTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Point2InitializationTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    /** @test Verify that vector can be instantiated during compile time. */
    namespace static_tests
    {
        /// @test Verify that Point2 gets initialized with correct values at compile time.
        constexpr flcn::Point2 POINT_VAL_INIT{ 1, 2 };
        static_assert(POINT_VAL_INIT.x() == 1);
        static_assert(POINT_VAL_INIT.y() == 2);

        /// @test Verify that Point2 gets initialized with zero with braced initialization at compile time.
        constexpr flcn::Point2<int> POINT_DEF_INIT{};
        static_assert(POINT_DEF_INIT.x() == 0);
        static_assert(POINT_DEF_INIT.y() == 0);

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Point2InitializationTests, BracedInitialization_InitializesComponentsToZero)
{
    const flcn::Point2<TypeParam> vec{};
    EXPECT_VEC_ZERO(vec);
}


TYPED_TEST(Point2InitializationTests, ParameterizedCtor_InitalizatesWithTheCorrectValues)
{
    const TypeParam a = static_cast<TypeParam>(3);
    const TypeParam b = static_cast<TypeParam>(1);

    const flcn::Point2<TypeParam> vec(a, b);

    EXPECT_VEC_CONTAINS(vec, a, b);
}

/** @} */
