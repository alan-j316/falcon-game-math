/**
 * @file SwizzlingTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 06, 2026
 *
 * @brief Verify @ref flcn::Vec3 swizzling logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"



/**
 * @addtogroup T_FALCON_Vec3_Swizzle
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
     * @brief Test fixture for @ref flcn::Vec3 swizzling.
     */
    template <typename>
    class Vec3SwizzlingTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Vec3SwizzlingTests, SupportedArithmeticTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Vec3 VECTOR(1.0f, 2.0f, 3.0f);

        /// @test Verify that vector swizzle<x,y,z> is available at compile time.
        static_assert(VECTOR.swizzle<X, Y, Z>().x() == 1.0f);
        static_assert(VECTOR.swizzle<X, Y, Z>().y() == 2.0f);
        static_assert(VECTOR.swizzle<X, Y, Z>().z() == 3.0f);

        /// @test Verify that vector swizzle<x,y,y> is available at compile time.
        static_assert(VECTOR.swizzle<X, Y, Y>().x() == 1.0f);
        static_assert(VECTOR.swizzle<X, Y, Y>().y() == 2.0f);
        static_assert(VECTOR.swizzle<X, Y, Y>().z() == 2.0f);

        /// @test Verify that vector swizzle<x,x,y> is available at compile time.
        static_assert(VECTOR.swizzle<X, X, Y>().x() == 1.0f);
        static_assert(VECTOR.swizzle<X, X, Y>().y() == 1.0f);
        static_assert(VECTOR.swizzle<X, X, Y>().z() == 2.0f);

        /// @test Verify that vector swizzle<x,x,x> is available at compile time.
        static_assert(VECTOR.swizzle<X, X, X>().x() == 1.0f);
        static_assert(VECTOR.swizzle<X, X, X>().y() == 1.0f);
        static_assert(VECTOR.swizzle<X, X, X>().z() == 1.0f);

        /// @test Verify that vector swizzle<y,y,z> is available at compile time.
        static_assert(VECTOR.swizzle<Y, Y, Z>().x() == 2.0f);
        static_assert(VECTOR.swizzle<Y, Y, Z>().y() == 2.0f);
        static_assert(VECTOR.swizzle<Y, Y, Z>().z() == 3.0f);

        /// @test Verify that vector swizzle<z,y,x> is available at compile time.
        static_assert(VECTOR.swizzle<Z, Y, X>().x() == 3.0f);
        static_assert(VECTOR.swizzle<Z, Y, X>().y() == 2.0f);
        static_assert(VECTOR.swizzle<Z, Y, X>().z() == 1.0f);

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

        /// @test Verify that vector swizzle<z> is available at compile time.
        static_assert(VECTOR.swizzle<Z>() == 3.0f);


        /// @test Verify that vector swizzle<r,g,b> is available at compile time.
        static_assert(VECTOR.swizzle<R, G, B>().r() == 1.0f);
        static_assert(VECTOR.swizzle<R, G, B>().g() == 2.0f);
        static_assert(VECTOR.swizzle<R, G, B>().b() == 3.0f);

        /// @test Verify that vector swizzle<b,g,r> is available at compile time.
        static_assert(VECTOR.swizzle<B, G, R>().r() == 3.0f);
        static_assert(VECTOR.swizzle<B, G, R>().g() == 2.0f);
        static_assert(VECTOR.swizzle<B, G, R>().b() == 1.0f);

        /// @test Verify that vector swizzle<r,g> is available at compile time.
        static_assert(VECTOR.swizzle<R, G>().r() == 1.0f);
        static_assert(VECTOR.swizzle<R, G>().g() == 2.0f);

        /// @test Verify that vector swizzle<g,r> is available at compile time.
        static_assert(VECTOR.swizzle<G, R>().r() == 2.0f);
        static_assert(VECTOR.swizzle<G, R>().g() == 1.0f);

        /// @test Verify that vector swizzle<r> is available at compile time.
        static_assert(VECTOR.swizzle<R>() == 1.0f);

        /// @test Verify that vector swizzle<g> is available at compile time.
        static_assert(VECTOR.swizzle<G>() == 2.0f);

        /// @test Verify that vector swizzle<g> is available at compile time.
        static_assert(VECTOR.swizzle<B>() == 3.0f);


        /// @test Verify that vector swizzle<s,t,p> is available at compile time.
        static_assert(VECTOR.swizzle<S, T, P>().s() == 1.0f);
        static_assert(VECTOR.swizzle<S, T, P>().t() == 2.0f);
        static_assert(VECTOR.swizzle<S, T, P>().p() == 3.0f);

        /// @test Verify that vector swizzle<p,t,s> is available at compile time.
        static_assert(VECTOR.swizzle<P, T, S>().s() == 3.0f);
        static_assert(VECTOR.swizzle<P, T, S>().t() == 2.0f);
        static_assert(VECTOR.swizzle<P, T, S>().p() == 1.0f);

        /// @test Verify that vector swizzle<s,t> is available at compile time.
        static_assert(VECTOR.swizzle<S, T>().s() == 1.0f);
        static_assert(VECTOR.swizzle<S, T>().t() == 2.0f);

        static_assert(VECTOR.swizzle<T, S>().s() == 2.0f);
        static_assert(VECTOR.swizzle<T, S>().t() == 1.0f);

        /// @test Verify that vector swizzle<t> is available at compile time.
        static_assert(VECTOR.swizzle<S>() == 1.0f);

        /// @test Verify that vector swizzle<t> is available at compile time.
        static_assert(VECTOR.swizzle<T>() == 2.0f);

        /// @test Verify that vector swizzle<p> is available at compile time.
        static_assert(VECTOR.swizzle<P>() == 3.0f);

        /// @test Verify that vector swizzle<x,y,z>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<X, Y, Z>(VECTOR).x() == 1.0f);
        static_assert(flcn::Vec3<float>::swizzle<X, Y, Z>(VECTOR).y() == 2.0f);
        static_assert(flcn::Vec3<float>::swizzle<X, Y, Z>(VECTOR).z() == 3.0f);

        /// @test Verify that vector swizzle<x,y,y>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<X, Y, Y>(VECTOR).x() == 1.0f);
        static_assert(flcn::Vec3<float>::swizzle<X, Y, Y>(VECTOR).y() == 2.0f);
        static_assert(flcn::Vec3<float>::swizzle<X, Y, Y>(VECTOR).z() == 2.0f);

        /// @test Verify that vector swizzle<x,x,y>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<X, X, Y>(VECTOR).x() == 1.0f);
        static_assert(flcn::Vec3<float>::swizzle<X, X, Y>(VECTOR).y() == 1.0f);
        static_assert(flcn::Vec3<float>::swizzle<X, X, Y>(VECTOR).z() == 2.0f);

        /// @test Verify that vector swizzle<x,x,x>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<X, X, X>(VECTOR).x() == 1.0f);
        static_assert(flcn::Vec3<float>::swizzle<X, X, X>(VECTOR).y() == 1.0f);
        static_assert(flcn::Vec3<float>::swizzle<X, X, X>(VECTOR).z() == 1.0f);

        /// @test Verify that vector swizzle<y,y,z>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<Y, Y, Z>(VECTOR).x() == 2.0f);
        static_assert(flcn::Vec3<float>::swizzle<Y, Y, Z>(VECTOR).y() == 2.0f);
        static_assert(flcn::Vec3<float>::swizzle<Y, Y, Z>(VECTOR).z() == 3.0f);

        /// @test Verify that vector swizzle<z,y,x>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<Z, Y, X>(VECTOR).x() == 3.0f);
        static_assert(flcn::Vec3<float>::swizzle<Z, Y, X>(VECTOR).y() == 2.0f);
        static_assert(flcn::Vec3<float>::swizzle<Z, Y, X>(VECTOR).z() == 1.0f);

        /// @test Verify that vector swizzle<x,y>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<X, Y>(VECTOR).x() == 1.0f);
        static_assert(flcn::Vec3<float>::swizzle<X, Y>(VECTOR).y() == 2.0f);

        /// @test Verify that vector swizzle<x,x>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<X, X>(VECTOR).x() == 1.0f);
        static_assert(flcn::Vec3<float>::swizzle<X, X>(VECTOR).y() == 1.0f);

        /// @test Verify that vector swizzle<y,y>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<Y, Y>(VECTOR).x() == 2.0f);
        static_assert(flcn::Vec3<float>::swizzle<Y, Y>(VECTOR).y() == 2.0f);

        /// @test Verify that vector swizzle<y,x>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<Y, X>(VECTOR).x() == 2.0f);
        static_assert(flcn::Vec3<float>::swizzle<Y, X>(VECTOR).y() == 1.0f);

        /// @test Verify that vector swizzle<x>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<X>(VECTOR) == 1.0f);

        /// @test Verify that vector swizzle<y>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<Y>(VECTOR) == 2.0f);

        /// @test Verify that vector swizzle<z>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<Z>(VECTOR) == 3.0f);

        /// @test Verify that vector swizzle<r,g,b>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<R, G, B>(VECTOR).r() == 1.0f);
        static_assert(flcn::Vec3<float>::swizzle<R, G, B>(VECTOR).g() == 2.0f);
        static_assert(flcn::Vec3<float>::swizzle<R, G, B>(VECTOR).b() == 3.0f);

        /// @test Verify that vector swizzle<b,g,r>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<B, G, R>(VECTOR).r() == 3.0f);
        static_assert(flcn::Vec3<float>::swizzle<B, G, R>(VECTOR).g() == 2.0f);
        static_assert(flcn::Vec3<float>::swizzle<B, G, R>(VECTOR).b() == 1.0f);

        /// @test Verify that vector swizzle<r,g>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<R, G>(VECTOR).r() == 1.0f);
        static_assert(flcn::Vec3<float>::swizzle<R, G>(VECTOR).g() == 2.0f);

        /// @test Verify that vector swizzle<g,r>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<G, R>(VECTOR).r() == 2.0f);
        static_assert(flcn::Vec3<float>::swizzle<G, R>(VECTOR).g() == 1.0f);

        /// @test Verify that vector swizzle<r>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<R>(VECTOR) == 1.0f);

        /// @test Verify that vector swizzle<g>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<G>(VECTOR) == 2.0f);

        /// @test Verify that vector swizzle<b>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<B>(VECTOR) == 3.0f);

        /// @test Verify that vector swizzle<s,t,p>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<S, T, P>(VECTOR).s() == 1.0f);
        static_assert(flcn::Vec3<float>::swizzle<S, T, P>(VECTOR).t() == 2.0f);
        static_assert(flcn::Vec3<float>::swizzle<S, T, P>(VECTOR).p() == 3.0f);

        /// @test Verify that vector swizzle<p,t,s>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<P, T, S>(VECTOR).s() == 3.0f);
        static_assert(flcn::Vec3<float>::swizzle<P, T, S>(VECTOR).t() == 2.0f);
        static_assert(flcn::Vec3<float>::swizzle<P, T, S>(VECTOR).p() == 1.0f);

        /// @test Verify that vector swizzle<s,t>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<S, T>(VECTOR).s() == 1.0f);
        static_assert(flcn::Vec3<float>::swizzle<S, T>(VECTOR).t() == 2.0f);

        /// @test Verify that vector swizzle<t,s>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<T, S>(VECTOR).s() == 2.0f);
        static_assert(flcn::Vec3<float>::swizzle<T, S>(VECTOR).t() == 1.0f);

        /// @test Verify that vector swizzle<s>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<S>(VECTOR) == 1.0f);

        /// @test Verify that vector swizzle<t>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<T>(VECTOR) == 2.0f);

        /// @test Verify that vector swizzle<p>(static wrapper) is available at compile time.
        static_assert(flcn::Vec3<float>::swizzle<P>(VECTOR) == 3.0f);

    } // namespace static_tests
} // namespace



/**************************************
 *            RUNTIME TESTS           *
 **************************************/

/** @test Verify that swizzling returns shuffled vector across different numeric. */
TYPED_TEST(Vec3SwizzlingTests, SwizzlingWorksAcrossDifferentTypes)
{
    const flcn::Vec3 vector(TypeParam(1), TypeParam(2), TypeParam(3));
    const flcn::Vec3 expectedSwizzling(TypeParam(3), TypeParam(2), TypeParam(1));

    const auto swizzledVector = vector.template swizzle<Z, Y, X>();
    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/** @test Verify that swizzling returns shuffled vector for boolean vector. */
TEST(Vec3SwizzlingTests, SwizzlingWorksForBooleanVector)
{
    const flcn::Vec3 vector(true, false, false);
    const flcn::Vec3 expectedSwizzling(false, false, true);

    const auto swizzledVector = vector.swizzle<Z, Y, X>();
    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/** @test Verify that static variant of swizzling returns shuffled vector across different numeric. */
TYPED_TEST(Vec3SwizzlingTests, StaticVariant_SwizzlingWorksAcrossDifferentTypes)
{
    const flcn::Vec3 vector(TypeParam(1), TypeParam(2), TypeParam(3));
    const flcn::Vec3 expectedSwizzling(TypeParam(3), TypeParam(2), TypeParam(1));

    const auto swizzledVector = flcn::Vec3<TypeParam>::template swizzle<Z, Y, X>(vector);
    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/** @test Verify that static variant of swizzling returns shuffled vector for boolean vector. */
TEST(Vec3SwizzlingTests, StaticVariant_SwizzlingWorksForBooleanVector)
{
    const flcn::Vec3 vector(true, false, false);
    const flcn::Vec3 expectedSwizzling(false, false, true);

    const auto swizzledVector = flcn::Vec3<bool>::swizzle<Z, Y, X>(vector);
    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}

/** @} */
