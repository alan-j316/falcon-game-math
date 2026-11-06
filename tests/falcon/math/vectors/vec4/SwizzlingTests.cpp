/**
 * @file SwizzlingTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 06, 2026
 *
 * @brief Verify @ref flcn::Vec4 swizzling logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec4TestSetup.h"



/**
 * @addtogroup T_FALCON_Vec4_Swizzle
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
     * @brief Test fixture for @ref flcn::Vec4 swizzling.
     */
    template <typename>
    class Vec4SwizzlingTests: public ::testing::Test
    {};
    TYPED_TEST_SUITE(Vec4SwizzlingTests, SupportedArithmeticTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Vec4 VECTOR(1.0f, 2.0f, 3.0f, 4.0f);

        /// @test Verify that vector swizzle<x,y,z,w> is available at compile time.
        static_assert(VECTOR.swizzle<X, Y, Z, W>().x() == 1.0f);
        static_assert(VECTOR.swizzle<X, Y, Z, W>().y() == 2.0f);
        static_assert(VECTOR.swizzle<X, Y, Z, W>().z() == 3.0f);
        static_assert(VECTOR.swizzle<X, Y, Z, W>().w() == 4.0f);

        /// @test Verify that vector swizzle<x,y,y,y> is available at compile time.
        static_assert(VECTOR.swizzle<X, X, Y, Y>().x() == 1.0f);
        static_assert(VECTOR.swizzle<X, X, Y, Y>().y() == 1.0f);
        static_assert(VECTOR.swizzle<X, X, Y, Y>().z() == 2.0f);
        static_assert(VECTOR.swizzle<X, X, Y, Y>().w() == 2.0f);

        /// @test Verify that vector swizzle<x,x,x,y> is available at compile time.
        static_assert(VECTOR.swizzle<X, X, X, Y>().x() == 1.0f);
        static_assert(VECTOR.swizzle<X, X, X, Y>().y() == 1.0f);
        static_assert(VECTOR.swizzle<X, X, X, Y>().z() == 1.0f);
        static_assert(VECTOR.swizzle<X, X, X, Y>().w() == 2.0f);

        /// @test Verify that vector swizzle<x,x,x,x> is available at compile time.
        static_assert(VECTOR.swizzle<X, X, X, X>().x() == 1.0f);
        static_assert(VECTOR.swizzle<X, X, X, X>().y() == 1.0f);
        static_assert(VECTOR.swizzle<X, X, X, X>().z() == 1.0f);
        static_assert(VECTOR.swizzle<X, X, X, X>().w() == 1.0f);

        /// @test Verify that vector swizzle<y,y,z,z> is available at compile time.
        static_assert(VECTOR.swizzle<Y, Y, Z, Z>().x() == 2.0f);
        static_assert(VECTOR.swizzle<Y, Y, Z, Z>().y() == 2.0f);
        static_assert(VECTOR.swizzle<Y, Y, Z, Z>().z() == 3.0f);
        static_assert(VECTOR.swizzle<Y, Y, Z, Z>().w() == 3.0f);

        /// @test Verify that vector swizzle<w,z,y,x> is available at compile time.
        static_assert(VECTOR.swizzle<W, Z, Y, X>().x() == 4.0f);
        static_assert(VECTOR.swizzle<W, Z, Y, X>().y() == 3.0f);
        static_assert(VECTOR.swizzle<W, Z, Y, X>().z() == 2.0f);
        static_assert(VECTOR.swizzle<W, Z, Y, X>().w() == 1.0f);

        /// @test Verify that vector swizzle<z,w,y,x> is available at compile time.
        static_assert(VECTOR.swizzle<Z, W, Y, X>().x() == 3.0f);
        static_assert(VECTOR.swizzle<Z, W, Y, X>().y() == 4.0f);
        static_assert(VECTOR.swizzle<Z, W, Y, X>().z() == 2.0f);
        static_assert(VECTOR.swizzle<Z, W, Y, X>().w() == 1.0f);

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

        /// @test Verify that vector swizzle<w,z,y> is available at compile time.
        static_assert(VECTOR.swizzle<W, Z, Y>().x() == 4.0f);
        static_assert(VECTOR.swizzle<W, Z, Y>().y() == 3.0f);
        static_assert(VECTOR.swizzle<W, Z, Y>().z() == 2.0f);

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

        /// @test Verify that vector swizzle<w,z> is available at compile time.
        static_assert(VECTOR.swizzle<W, Z>().x() == 4.0f);
        static_assert(VECTOR.swizzle<W, Z>().y() == 3.0f);

        /// @test Verify that vector swizzle<y,x> is available at compile time.
        static_assert(VECTOR.swizzle<Y, X>().x() == 2.0f);
        static_assert(VECTOR.swizzle<Y, X>().y() == 1.0f);

        /// @test Verify that vector swizzle<x> is available at compile time.
        static_assert(VECTOR.swizzle<X>() == 1.0f);

        /// @test Verify that vector swizzle<y> is available at compile time.
        static_assert(VECTOR.swizzle<Y>() == 2.0f);

        /// @test Verify that vector swizzle<z> is available at compile time.
        static_assert(VECTOR.swizzle<Z>() == 3.0f);

        /// @test Verify that vector swizzle<w> is available at compile time.
        static_assert(VECTOR.swizzle<W>() == 4.0f);

        /// @test Verify that vector swizzle<r,g,b,a> is available at compile time.
        static_assert(VECTOR.swizzle<R, G, B, A>().r() == 1.0f);
        static_assert(VECTOR.swizzle<R, G, B, A>().g() == 2.0f);
        static_assert(VECTOR.swizzle<R, G, B, A>().b() == 3.0f);
        static_assert(VECTOR.swizzle<R, G, B, A>().a() == 4.0f);

        /// @test Verify that vector swizzle<a,b,g,r> is available at compile time.
        static_assert(VECTOR.swizzle<A, B, G, R>().r() == 4.0f);
        static_assert(VECTOR.swizzle<A, B, G, R>().g() == 3.0f);
        static_assert(VECTOR.swizzle<A, B, G, R>().b() == 2.0f);
        static_assert(VECTOR.swizzle<A, B, G, R>().a() == 1.0f);

        /// @test Verify that vector swizzle<r,g,b> is available at compile time.
        static_assert(VECTOR.swizzle<R, G, B>().r() == 1.0f);
        static_assert(VECTOR.swizzle<R, G, B>().g() == 2.0f);
        static_assert(VECTOR.swizzle<R, G, B>().b() == 3.0f);

        /// @test Verify that vector swizzle<a,b,g> is available at compile time.
        static_assert(VECTOR.swizzle<A, B, G>().r() == 4.0f);
        static_assert(VECTOR.swizzle<A, B, G>().g() == 3.0f);
        static_assert(VECTOR.swizzle<A, B, G>().b() == 2.0f);

        /// @test Verify that vector swizzle<r,g> is available at compile time.
        static_assert(VECTOR.swizzle<R, G>().r() == 1.0f);
        static_assert(VECTOR.swizzle<R, G>().g() == 2.0f);

        /// @test Verify that vector swizzle<b,a> is available at compile time.
        static_assert(VECTOR.swizzle<B, A>().r() == 3.0f);
        static_assert(VECTOR.swizzle<B, A>().g() == 4.0f);

        /// @test Verify that vector swizzle<a,b> is available at compile time.
        static_assert(VECTOR.swizzle<A, B>().r() == 4.0f);
        static_assert(VECTOR.swizzle<A, B>().g() == 3.0f);
        /// @test Verify that vector swizzle<g,r> is available at compile time.
        static_assert(VECTOR.swizzle<G, R>().r() == 2.0f);
        static_assert(VECTOR.swizzle<G, R>().g() == 1.0f);

        /// @test Verify that vector swizzle<r> is available at compile time.
        static_assert(VECTOR.swizzle<R>() == 1.0f);

        /// @test Verify that vector swizzle<g> is available at compile time.
        static_assert(VECTOR.swizzle<G>() == 2.0f);

        /// @test Verify that vector swizzle<b> is available at compile time.
        static_assert(VECTOR.swizzle<B>() == 3.0f);

        /// @test Verify that vector swizzle<a> is available at compile time.
        static_assert(VECTOR.swizzle<A>() == 4.0f);

        /// @test Verify that vector swizzle<s,t,p,q> is available at compile time.
        static_assert(VECTOR.swizzle<S, T, P, Q>().s() == 1.0f);
        static_assert(VECTOR.swizzle<S, T, P, Q>().t() == 2.0f);
        static_assert(VECTOR.swizzle<S, T, P, Q>().p() == 3.0f);
        static_assert(VECTOR.swizzle<S, T, P, Q>().q() == 4.0f);

        /// @test Verify that vector swizzle<q,p,t,s> is available at compile time.
        static_assert(VECTOR.swizzle<Q, P, T, S>().s() == 4.0f);
        static_assert(VECTOR.swizzle<Q, P, T, S>().t() == 3.0f);
        static_assert(VECTOR.swizzle<Q, P, T, S>().p() == 2.0f);
        static_assert(VECTOR.swizzle<Q, P, T, S>().q() == 1.0f);

        /// @test Verify that vector swizzle<s,t,p> is available at compile time.
        static_assert(VECTOR.swizzle<S, T, P>().s() == 1.0f);
        static_assert(VECTOR.swizzle<S, T, P>().t() == 2.0f);
        static_assert(VECTOR.swizzle<S, T, P>().p() == 3.0f);

        /// @test Verify that vector swizzle<q,p,t> is available at compile time.
        static_assert(VECTOR.swizzle<Q, P, T>().s() == 4.0f);
        static_assert(VECTOR.swizzle<Q, P, T>().t() == 3.0f);
        static_assert(VECTOR.swizzle<Q, P, T>().p() == 2.0f);

        /// @test Verify that vector swizzle<s,t> is available at compile time.
        static_assert(VECTOR.swizzle<S, T>().s() == 1.0f);
        static_assert(VECTOR.swizzle<S, T>().t() == 2.0f);

        /// @test Verify that vector swizzle<p,q> is available at compile time.
        static_assert(VECTOR.swizzle<P, Q>().s() == 3.0f);
        static_assert(VECTOR.swizzle<P, Q>().t() == 4.0f);

        /// @test Verify that vector swizzle<q,p> is available at compile time.
        static_assert(VECTOR.swizzle<Q, P>().s() == 4.0f);
        static_assert(VECTOR.swizzle<Q, P>().t() == 3.0f);

        /// @test Verify that vector swizzle<t,s> is available at compile time.
        static_assert(VECTOR.swizzle<T, S>().s() == 2.0f);
        static_assert(VECTOR.swizzle<T, S>().t() == 1.0f);

        /// @test Verify that vector swizzle<s> is available at compile time.
        static_assert(VECTOR.swizzle<S>() == 1.0f);

        /// @test Verify that vector swizzle<t> is available at compile time.
        static_assert(VECTOR.swizzle<T>() == 2.0f);

        /// @test Verify that vector swizzle<p> is available at compile time.
        static_assert(VECTOR.swizzle<P>() == 3.0f);

        /// @test Verify that vector swizzle<q> is available at compile time.
        static_assert(VECTOR.swizzle<Q>() == 4.0f);


        /// @test Verify that vector swizzle<x,y,z,w> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<X, Y, Z, W>(VECTOR).x() == 1.0f);
        static_assert(flcn::Vec4<float>::swizzle<X, Y, Z, W>(VECTOR).y() == 2.0f);
        static_assert(flcn::Vec4<float>::swizzle<X, Y, Z, W>(VECTOR).z() == 3.0f);
        static_assert(flcn::Vec4<float>::swizzle<X, Y, Z, W>(VECTOR).w() == 4.0f);

        /// @test Verify that vector swizzle<x,x,y,y> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<X, X, Y, Y>(VECTOR).x() == 1.0f);
        static_assert(flcn::Vec4<float>::swizzle<X, X, Y, Y>(VECTOR).y() == 1.0f);
        static_assert(flcn::Vec4<float>::swizzle<X, X, Y, Y>(VECTOR).z() == 2.0f);
        static_assert(flcn::Vec4<float>::swizzle<X, X, Y, Y>(VECTOR).w() == 2.0f);

        /// @test Verify that vector swizzle<x,x,x,y> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<X, X, X, Y>(VECTOR).x() == 1.0f);
        static_assert(flcn::Vec4<float>::swizzle<X, X, X, Y>(VECTOR).y() == 1.0f);
        static_assert(flcn::Vec4<float>::swizzle<X, X, X, Y>(VECTOR).z() == 1.0f);
        static_assert(flcn::Vec4<float>::swizzle<X, X, X, Y>(VECTOR).w() == 2.0f);

        /// @test Verify that vector swizzle<x,x,x,x> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<X, X, X, X>(VECTOR).x() == 1.0f);
        static_assert(flcn::Vec4<float>::swizzle<X, X, X, X>(VECTOR).y() == 1.0f);
        static_assert(flcn::Vec4<float>::swizzle<X, X, X, X>(VECTOR).z() == 1.0f);
        static_assert(flcn::Vec4<float>::swizzle<X, X, X, X>(VECTOR).w() == 1.0f);

        /// @test Verify that vector swizzle<y,y,z,z> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<Y, Y, Z, Z>(VECTOR).x() == 2.0f);
        static_assert(flcn::Vec4<float>::swizzle<Y, Y, Z, Z>(VECTOR).y() == 2.0f);
        static_assert(flcn::Vec4<float>::swizzle<Y, Y, Z, Z>(VECTOR).z() == 3.0f);
        static_assert(flcn::Vec4<float>::swizzle<Y, Y, Z, Z>(VECTOR).w() == 3.0f);

        /// @test Verify that vector swizzle<w,z,y,x> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<W, Z, Y, X>(VECTOR).x() == 4.0f);
        static_assert(flcn::Vec4<float>::swizzle<W, Z, Y, X>(VECTOR).y() == 3.0f);
        static_assert(flcn::Vec4<float>::swizzle<W, Z, Y, X>(VECTOR).z() == 2.0f);
        static_assert(flcn::Vec4<float>::swizzle<W, Z, Y, X>(VECTOR).w() == 1.0f);

        /// @test Verify that vector swizzle<z,w,y,x> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<Z, W, Y, X>(VECTOR).x() == 3.0f);
        static_assert(flcn::Vec4<float>::swizzle<Z, W, Y, X>(VECTOR).y() == 4.0f);
        static_assert(flcn::Vec4<float>::swizzle<Z, W, Y, X>(VECTOR).z() == 2.0f);
        static_assert(flcn::Vec4<float>::swizzle<Z, W, Y, X>(VECTOR).w() == 1.0f);

        /// @test Verify that vector swizzle<x,y,z> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<X, Y, Z>(VECTOR).x() == 1.0f);
        static_assert(flcn::Vec4<float>::swizzle<X, Y, Z>(VECTOR).y() == 2.0f);
        static_assert(flcn::Vec4<float>::swizzle<X, Y, Z>(VECTOR).z() == 3.0f);

        /// @test Verify that vector swizzle<x,y,y> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<X, Y, Y>(VECTOR).x() == 1.0f);
        static_assert(flcn::Vec4<float>::swizzle<X, Y, Y>(VECTOR).y() == 2.0f);
        static_assert(flcn::Vec4<float>::swizzle<X, Y, Y>(VECTOR).z() == 2.0f);

        /// @test Verify that vector swizzle<x,x,y> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<X, X, Y>(VECTOR).x() == 1.0f);
        static_assert(flcn::Vec4<float>::swizzle<X, X, Y>(VECTOR).y() == 1.0f);
        static_assert(flcn::Vec4<float>::swizzle<X, X, Y>(VECTOR).z() == 2.0f);

        /// @test Verify that vector swizzle<x,x,x> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<X, X, X>(VECTOR).x() == 1.0f);
        static_assert(flcn::Vec4<float>::swizzle<X, X, X>(VECTOR).y() == 1.0f);
        static_assert(flcn::Vec4<float>::swizzle<X, X, X>(VECTOR).z() == 1.0f);

        /// @test Verify that vector swizzle<y,y,z> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<Y, Y, Z>(VECTOR).x() == 2.0f);
        static_assert(flcn::Vec4<float>::swizzle<Y, Y, Z>(VECTOR).y() == 2.0f);
        static_assert(flcn::Vec4<float>::swizzle<Y, Y, Z>(VECTOR).z() == 3.0f);

        /// @test Verify that vector swizzle<w,z,y> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<W, Z, Y>(VECTOR).x() == 4.0f);
        static_assert(flcn::Vec4<float>::swizzle<W, Z, Y>(VECTOR).y() == 3.0f);
        static_assert(flcn::Vec4<float>::swizzle<W, Z, Y>(VECTOR).z() == 2.0f);

        /// @test Verify that vector swizzle<z,y,x> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<Z, Y, X>(VECTOR).x() == 3.0f);
        static_assert(flcn::Vec4<float>::swizzle<Z, Y, X>(VECTOR).y() == 2.0f);
        static_assert(flcn::Vec4<float>::swizzle<Z, Y, X>(VECTOR).z() == 1.0f);

        /// @test Verify that vector swizzle<x,y> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<X, Y>(VECTOR).x() == 1.0f);
        static_assert(flcn::Vec4<float>::swizzle<X, Y>(VECTOR).y() == 2.0f);

        /// @test Verify that vector swizzle<x,x> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<X, X>(VECTOR).x() == 1.0f);
        static_assert(flcn::Vec4<float>::swizzle<X, X>(VECTOR).y() == 1.0f);

        /// @test Verify that vector swizzle<y,y> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<Y, Y>(VECTOR).x() == 2.0f);
        static_assert(flcn::Vec4<float>::swizzle<Y, Y>(VECTOR).y() == 2.0f);

        /// @test Verify that vector swizzle<w,z> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<W, Z>(VECTOR).x() == 4.0f);
        static_assert(flcn::Vec4<float>::swizzle<W, Z>(VECTOR).y() == 3.0f);

        /// @test Verify that vector swizzle<y,x> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<Y, X>(VECTOR).x() == 2.0f);
        static_assert(flcn::Vec4<float>::swizzle<Y, X>(VECTOR).y() == 1.0f);

        /// @test Verify that vector swizzle<x> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<X>(VECTOR) == 1.0f);

        /// @test Verify that vector swizzle<y> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<Y>(VECTOR) == 2.0f);

        /// @test Verify that vector swizzle<z> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<Z>(VECTOR) == 3.0f);

        /// @test Verify that vector swizzle<w> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<W>(VECTOR) == 4.0f);

        /// @test Verify that vector swizzle<r,g,b,a> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<R, G, B, A>(VECTOR).r() == 1.0f);
        static_assert(flcn::Vec4<float>::swizzle<R, G, B, A>(VECTOR).g() == 2.0f);
        static_assert(flcn::Vec4<float>::swizzle<R, G, B, A>(VECTOR).b() == 3.0f);
        static_assert(flcn::Vec4<float>::swizzle<R, G, B, A>(VECTOR).a() == 4.0f);

        /// @test Verify that vector swizzle<a,b,g,r> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<A, B, G, R>(VECTOR).r() == 4.0f);
        static_assert(flcn::Vec4<float>::swizzle<A, B, G, R>(VECTOR).g() == 3.0f);
        static_assert(flcn::Vec4<float>::swizzle<A, B, G, R>(VECTOR).b() == 2.0f);
        static_assert(flcn::Vec4<float>::swizzle<A, B, G, R>(VECTOR).a() == 1.0f);

        /// @test Verify that vector swizzle<r,g,b> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<R, G, B>(VECTOR).r() == 1.0f);
        static_assert(flcn::Vec4<float>::swizzle<R, G, B>(VECTOR).g() == 2.0f);
        static_assert(flcn::Vec4<float>::swizzle<R, G, B>(VECTOR).b() == 3.0f);

        /// @test Verify that vector swizzle<a,b,g> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<A, B, G>(VECTOR).r() == 4.0f);
        static_assert(flcn::Vec4<float>::swizzle<A, B, G>(VECTOR).g() == 3.0f);
        static_assert(flcn::Vec4<float>::swizzle<A, B, G>(VECTOR).b() == 2.0f);

        /// @test Verify that vector swizzle<r,g> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<R, G>(VECTOR).r() == 1.0f);
        static_assert(flcn::Vec4<float>::swizzle<R, G>(VECTOR).g() == 2.0f);

        /// @test Verify that vector swizzle<b,a> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<B, A>(VECTOR).r() == 3.0f);
        static_assert(flcn::Vec4<float>::swizzle<B, A>(VECTOR).g() == 4.0f);

        /// @test Verify that vector swizzle<a,b> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<A, B>(VECTOR).r() == 4.0f);
        static_assert(flcn::Vec4<float>::swizzle<A, B>(VECTOR).g() == 3.0f);

        /// @test Verify that vector swizzle<g,r> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<G, R>(VECTOR).r() == 2.0f);
        static_assert(flcn::Vec4<float>::swizzle<G, R>(VECTOR).g() == 1.0f);

        /// @test Verify that vector swizzle<r> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<R>(VECTOR) == 1.0f);

        /// @test Verify that vector swizzle<g> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<G>(VECTOR) == 2.0f);

        /// @test Verify that vector swizzle<b> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<B>(VECTOR) == 3.0f);

        /// @test Verify that vector swizzle<a> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<A>(VECTOR) == 4.0f);

        /// @test Verify that vector swizzle<s,t,p,q> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<S, T, P, Q>(VECTOR).s() == 1.0f);
        static_assert(flcn::Vec4<float>::swizzle<S, T, P, Q>(VECTOR).t() == 2.0f);
        static_assert(flcn::Vec4<float>::swizzle<S, T, P, Q>(VECTOR).p() == 3.0f);
        static_assert(flcn::Vec4<float>::swizzle<S, T, P, Q>(VECTOR).q() == 4.0f);

        /// @test Verify that vector swizzle<q,p,t,s> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<Q, P, T, S>(VECTOR).s() == 4.0f);
        static_assert(flcn::Vec4<float>::swizzle<Q, P, T, S>(VECTOR).t() == 3.0f);
        static_assert(flcn::Vec4<float>::swizzle<Q, P, T, S>(VECTOR).p() == 2.0f);
        static_assert(flcn::Vec4<float>::swizzle<Q, P, T, S>(VECTOR).q() == 1.0f);

        /// @test Verify that vector swizzle<s,t,p> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<S, T, P>(VECTOR).s() == 1.0f);
        static_assert(flcn::Vec4<float>::swizzle<S, T, P>(VECTOR).t() == 2.0f);
        static_assert(flcn::Vec4<float>::swizzle<S, T, P>(VECTOR).p() == 3.0f);

        /// @test Verify that vector swizzle<q,p,t> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<Q, P, T>(VECTOR).s() == 4.0f);
        static_assert(flcn::Vec4<float>::swizzle<Q, P, T>(VECTOR).t() == 3.0f);
        static_assert(flcn::Vec4<float>::swizzle<Q, P, T>(VECTOR).p() == 2.0f);

        /// @test Verify that vector swizzle<s,t> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<S, T>(VECTOR).s() == 1.0f);
        static_assert(flcn::Vec4<float>::swizzle<S, T>(VECTOR).t() == 2.0f);

        /// @test Verify that vector swizzle<p,q> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<P, Q>(VECTOR).s() == 3.0f);
        static_assert(flcn::Vec4<float>::swizzle<P, Q>(VECTOR).t() == 4.0f);

        /// @test Verify that vector swizzle<q,q> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<Q, P>(VECTOR).s() == 4.0f);
        static_assert(flcn::Vec4<float>::swizzle<Q, P>(VECTOR).t() == 3.0f);

        /// @test Verify that vector swizzle<t,s> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<T, S>(VECTOR).s() == 2.0f);
        static_assert(flcn::Vec4<float>::swizzle<T, S>(VECTOR).t() == 1.0f);

        /// @test Verify that vector swizzle<s> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<S>(VECTOR) == 1.0f);

        /// @test Verify that vector swizzle<t> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<T>(VECTOR) == 2.0f);

        /// @test Verify that vector swizzle<p> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<P>(VECTOR) == 3.0f);

        /// @test Verify that vector swizzle<q> (static wrapper) is available at compile time.
        static_assert(flcn::Vec4<float>::swizzle<Q>(VECTOR) == 4.0f);
    } // namespace static_tests
} // namespace


/**************************************
 *            RUNTIME TESTS           *
 **************************************/

/** @test Verify that swizzling returns shuffled vector across different numeric. */
TYPED_TEST(Vec4SwizzlingTests, SwizzlingWorksAcrossDifferentTypes)
{
    const flcn::Vec4 vector(TypeParam(1), TypeParam(2), TypeParam(3), TypeParam(4));
    const flcn::Vec4 expectedSwizzling(TypeParam(4), TypeParam(3), TypeParam(2), TypeParam(1));
    const auto swizzledVector = vector.template swizzle<W, Z, Y, X>();
    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/** @test Verify that swizzling returns shuffled vector for boolean vector. */
TEST(Vec4SwizzlingTest, SwizzlingWorksForBooleanVector)
{
    const flcn::Vec4 vector(true, true, false, false);
    const flcn::Vec4 expectedSwizzling(false, false, true, true);
    const auto swizzledVector = vector.swizzle<W, Z, Y, X>();
    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/** @test Verify that the static variant of swizzling returns shuffled vector across different numeric. */
TYPED_TEST(Vec4SwizzlingTests, StaticVariant_SwizzlingWorksAcrossDifferentTypes)
{
    const flcn::Vec4 vector(TypeParam(1), TypeParam(2), TypeParam(3), TypeParam(4));
    const flcn::Vec4 expectedSwizzling(TypeParam(4), TypeParam(3), TypeParam(2), TypeParam(1));
    const auto swizzledVector = flcn::Vec4<TypeParam>::template swizzle<W, Z, Y, X>(vector);
    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/** @test Verify that the static variant of swizzling returns shuffled vector for boolean vector. */
TEST(Vec4SwizzlingTest, StaticVariant_SwizzlingWorksForBooleanVector)
{
    const flcn::Vec4 vector(true, true, false, false);
    const flcn::Vec4 expectedSwizzling(false, false, true, true);
    const auto swizzledVector = flcn::Vec4<bool>::swizzle<W, Z, Y, X>(vector);
    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/** @} */
