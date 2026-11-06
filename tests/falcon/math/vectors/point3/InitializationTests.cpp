/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 30, 2026
 *
 * @brief Verify @ref flcn::Point3 initialization logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Point3TestSetup.h"



/**
 * @addtogroup T_FALCON_Point3_Init
 * @{
 */

namespace
{

    /**************************************
     *               SETUP                *
     **************************************/
    /**
     * @brief Test fixture for @ref flcn::Point3 initialization(CTOR).
     *
     * @tparam T The scalar type (e.g., float, double) used for the point.
     */
    template <typename T>
    class Point3Initialization: public testing::Test
    {};
    TYPED_TEST_SUITE(Point3Initialization, SupportedArithmeticTypes);


    /**************************************
     *            STATIC TESTS            *
     **************************************/

    /** @test Verify that vector can be instantiated during compile time. */
    namespace static_tests
    {
        /// @test Verify that Point3 gets initialized with correct values at compile time.
        constexpr flcn::Point3 POINT_VAL_INIT{ 1, 2, 3 };
        static_assert(POINT_VAL_INIT.x() == 1);
        static_assert(POINT_VAL_INIT.y() == 2);
        static_assert(POINT_VAL_INIT.z() == 3);

        /// @test Verify that Point3 gets initialized with zero with braced initialization at compile time.
        constexpr flcn::Point3<int> POINT_DEF_INIT{};
        static_assert(POINT_DEF_INIT.x() == 0);
        static_assert(POINT_DEF_INIT.y() == 0);
        static_assert(POINT_DEF_INIT.z() == 0);

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Point3Initialization, BracedInitialization_InitializesComponentsToZero)
{
    const flcn::Point3<TypeParam> vec{};
    EXPECT_VEC_ZERO(vec);
}


TYPED_TEST(Point3Initialization, ParameterizedCtor_InitalizatesWithTheCorrectValues)
{
    const TypeParam a = static_cast<TypeParam>(3);
    const TypeParam b = static_cast<TypeParam>(1);
    const TypeParam c = static_cast<TypeParam>(6);

    const flcn::Point3<TypeParam> vec(a, b, c);

    EXPECT_VEC_CONTAINS(vec, a, b, c);
}

/** @} */
