/**
 * @file SwizzlingTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 06, 2026
 *
 * @brief Verify @ref flcn::CVec2 swizzling logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CVec2TestSetup.h"


/**
 * @addtogroup T_FALCON_CVec2_Swizzle
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    using namespace flcn::axis;
    using namespace flcn::colors;
    using namespace flcn::stp;

    /**
     * @brief Test fixture for @ref flcn::CVec2 swizzling.
     */
    template <typename>
    class CVec2SwizzlingTests: public testing::Test
    {};
    TYPED_TEST_SUITE(CVec2SwizzlingTests, SupportedArithmeticTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/
    namespace static_tests
    {
        constexpr flcn::CVec2 VECTOR(1.0f, 2.0f);


        /// @test Verify that vector swizzle<x,y> is available at compile time.
        static_assert(VECTOR.swizzle<X, Y>().x() == 1.0f);
        static_assert(VECTOR.swizzle<X, Y>().y() == 2.0f);

        /// @test Verify that vector swizzle<x,x> is available at compile time.
        static_assert(VECTOR.swizzle<X, X>().x() == 1.0f);
        static_assert(VECTOR.swizzle<X, X>().y() == 1.0f);

        /// @test Verify that vector swizzle<y,y> is available at compile time.
        static_assert(VECTOR.swizzle<Y, Y>().x() == 2.0f);
        static_assert(VECTOR.swizzle<Y, Y>().y() == 2.0f);

        /// @test Verify that vector swizzle<y,x> is available at compile time.
        static_assert(VECTOR.swizzle<Y, X>().x() == 2.0f);
        static_assert(VECTOR.swizzle<Y, X>().y() == 1.0f);

        /// @test Verify that vector swizzle<x> is available at compile time.
        static_assert(VECTOR.swizzle<X>() == 1.0f);

        /// @test Verify that vector swizzle<y> is available at compile time.
        static_assert(VECTOR.swizzle<Y>() == 2.0f);


        /// @test Verify that vector swizzle<r,g> is available at compile time.
        static_assert(VECTOR.swizzle<R, G>().r() == 1.0f);
        static_assert(VECTOR.swizzle<R, G>().g() == 2.0f);

        /// @test Verify that vector swizzle<g, r> is available at compile time.
        static_assert(VECTOR.swizzle<G, R>().r() == 2.0f);
        static_assert(VECTOR.swizzle<G, R>().g() == 1.0f);


        /// @test Verify that vector swizzle<s,t> is available at compile time.
        static_assert(VECTOR.swizzle<S, T>().s() == 1.0f);
        static_assert(VECTOR.swizzle<S, T>().t() == 2.0f);

        /// @test Verify that vector swizzle<t,s> is available at compile time.
        static_assert(VECTOR.swizzle<T, S>().s() == 2.0f);
        static_assert(VECTOR.swizzle<T, S>().t() == 1.0f);

        /// @test Verify that vector swizzle<s> is available at compile time.
        static_assert(VECTOR.swizzle<S>() == 1.0f);
        /// @test Verify that vector swizzle<t> is available at compile time.
        static_assert(VECTOR.swizzle<T>() == 2.0f);


        /// @test Verify that vector swizzle<x,y>(static wrapper) is available at compile time.
        static_assert(flcn::CVec2<float>::swizzle<X, Y>(VECTOR).x() == 1.0f);
        static_assert(flcn::CVec2<float>::swizzle<X, Y>(VECTOR).y() == 2.0f);

        /// @test Verify that vector swizzle<x,x>(static wrapper) is available at compile time.
        static_assert(flcn::CVec2<float>::swizzle<X, X>(VECTOR).x() == 1.0f);
        static_assert(flcn::CVec2<float>::swizzle<X, X>(VECTOR).y() == 1.0f);

        /// @test Verify that vector swizzle<y,y>(static wrapper) is available at compile time.
        static_assert(flcn::CVec2<float>::swizzle<Y, Y>(VECTOR).x() == 2.0f);
        static_assert(flcn::CVec2<float>::swizzle<Y, Y>(VECTOR).y() == 2.0f);

        /// @test Verify that vector swizzle<y,x>(static wrapper) is available at compile time.
        static_assert(flcn::CVec2<float>::swizzle<Y, X>(VECTOR).x() == 2.0f);
        static_assert(flcn::CVec2<float>::swizzle<Y, X>(VECTOR).y() == 1.0f);

        /// @test Verify that vector swizzle<x>(static wrapper) is available at compile time.
        static_assert(flcn::CVec2<float>::swizzle<X>(VECTOR) == 1.0f);

        /// @test Verify that vector swizzle<y>(static wrapper) is available at compile time.
        static_assert(flcn::CVec2<float>::swizzle<Y>(VECTOR) == 2.0f);


        /// @test Verify that vector swizzle<r, g>(static wrapper) is available at compile time.
        static_assert(flcn::CVec2<float>::swizzle<R, G>(VECTOR).r() == 1.0f);
        static_assert(flcn::CVec2<float>::swizzle<R, G>(VECTOR).g() == 2.0f);

        /// @test Verify that vector swizzle<g, r>(static wrapper) is available at compile time.
        static_assert(flcn::CVec2<float>::swizzle<G, R>(VECTOR).r() == 2.0f);
        static_assert(flcn::CVec2<float>::swizzle<G, R>(VECTOR).g() == 1.0f);


        /// @test Verify that vector swizzle<s, t>(static wrapper) is available at compile time.
        static_assert(flcn::CVec2<float>::swizzle<S, T>(VECTOR).s() == 1.0f);
        static_assert(flcn::CVec2<float>::swizzle<S, T>(VECTOR).t() == 2.0f);

        /// @test Verify that vector swizzle<t, s>(static wrapper) is available at compile time.
        static_assert(flcn::CVec2<float>::swizzle<T, S>(VECTOR).s() == 2.0f);
        static_assert(flcn::CVec2<float>::swizzle<T, S>(VECTOR).t() == 1.0f);


        /// @test Verify that vector swizzle<s>(static wrapper) is available at compile time.
        static_assert(flcn::CVec2<float>::swizzle<S>(VECTOR) == 1.0f);

        /// @test Verify that vector swizzle<t>(static wrapper) is available at compile time.
        static_assert(flcn::CVec2<float>::swizzle<T>(VECTOR) == 2.0f);

    } // namespace static_tests
} // namespace



/**************************************
 *            RUNTIME TESTS           *
 **************************************/

/** @test Verify that swizzling returns shuffled vector across different numeric. */
TYPED_TEST(CVec2SwizzlingTests, SwizzlingWorksAcrossDifferentTypes)
{
    const flcn::CVec2 vector(TypeParam(1), TypeParam(2));
    const flcn::CVec2 expectedSwizzling(TypeParam(2), TypeParam(1));

    const auto swizzledVector = vector.template swizzle<Y, X>();

    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/** @test Verify that swizzling returns shuffled vector for boolean vector. */
TEST(CVec2SwizzlingTest, SwizzlingWorksForBooleanVector)
{
    const flcn::CVec2 vector(true, false);
    const flcn::CVec2 expectedSwizzling(false, true);

    const auto swizzledVector = vector.swizzle<Y, X>();

    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/**
 * @test Verify that swizzling using static variant of @ref flcn::CVec2::swizzle
 *        returns shuffled vector across different numeric.
 */
TYPED_TEST(CVec2SwizzlingTests, StaticWrapper_SwizzlingWorksAcrossDifferentTypes)
{
    const flcn::CVec2 vector(TypeParam(1), TypeParam(2));
    const flcn::CVec2 expectedSwizzling(TypeParam(2), TypeParam(1));

    const auto swizzledVector = flcn::CVec2<TypeParam>::template swizzle<Y, X>(vector);

    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/**
 * @test Verify that swizzling using static variant of @ref flcn::CVec2::swizzle
 *        returns shuffled vector for boolean vector.
 */
TEST(CVec2SwizzlingTest, StaticWrapper_SwizzlingWorksForBooleanVector)
{
    const flcn::CVec2 vector(true, false);
    const flcn::CVec2 expectedSwizzling(false, true);

    const auto swizzledVector = flcn::CVec2<bool>::template swizzle<Y, X>(vector);

    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/** @} */
