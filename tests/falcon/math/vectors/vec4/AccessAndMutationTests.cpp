/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verify @ref flcn::Vec4 accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec4TestSetup.h"



/**
 * @addtogroup T_FALCON_Vec4_Access
 * @{
 */

namespace
{
    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Vec4 VEC(1, 2, 3, 4);

        /// @test Verify that vector is accessible as <x, y, z, w> at compile time.
        static_assert(VEC.x() == 1);
        static_assert(VEC.y() == 2);
        static_assert(VEC.z() == 3);
        static_assert(VEC.w() == 4);

        /// @test Verify that vector is accessible as <r, g, b, a> at compile time.
        static_assert(VEC.r() == 1);
        static_assert(VEC.g() == 2);
        static_assert(VEC.b() == 3);
        static_assert(VEC.a() == 4);

        /// @test Verify that vector is accessible as <s, t, p, q> at compile time.
        static_assert(VEC.s() == 1);
        static_assert(VEC.t() == 2);
        static_assert(VEC.p() == 3);
        static_assert(VEC.q() == 4);
    } // namespace static_tests
} // namespace



/**************************************
 *            ACCESS TESTS            *
 **************************************/

/** @test Verify that the components are accessible via named spatial aliases (x, y, z, w). */
TEST(Vec4AccessTests, AccessibleAsXYZW)
{
    const flcn::Vec4 vec(3.0f, 1.0f, 6.0f, 2.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
    EXPECT_FLOAT_EQ(6.0f, vec.z());
    EXPECT_FLOAT_EQ(2.0f, vec.w());
}


/** @test Verify that the components are accessible via named spatial aliases (s, t, p, q). */
TEST(Vec4AccessTests, AccessibleAsSTPQ)
{
    const flcn::Vec4 vec(3.0f, 1.0f, 6.0f, 2.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
    EXPECT_FLOAT_EQ(6.0f, vec.p());
    EXPECT_FLOAT_EQ(2.0f, vec.q());
}


/** @test Verify that the components are accessible via named spatial aliases (r, g, b, a). */
TEST(Vec4AccessTests, AccessibleAsRGBA)
{
    const flcn::Vec4 vec(3.0f, 1.0f, 6.0f, 2.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
    EXPECT_FLOAT_EQ(6.0f, vec.b());
    EXPECT_FLOAT_EQ(2.0f, vec.a());
}


/** @test Verify that the components are accessible via subscript indexing for reads. */
TEST(Vec4AccessTests, AccessibleAsArray)
{
    const flcn::Vec4 vec(3.0f, 1.0f, 6.0f, 2.0f);

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);
    EXPECT_FLOAT_EQ(2.0f, vec[3]);
}




/**************************************
 *           MUTATION TESTS           *
 **************************************/

/** @test Verify that the components can be mutated via named spatial aliases (x, y, z, w). */
TEST(Vec4MutationTests, ElementsCanBeMutatedUsingXYZW)
{
    flcn::Vec4<float> vec;

    vec.x() = 3.0f;
    vec.y() = 1.0f;
    vec.z() = 6.0f;
    vec.w() = 2.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
    EXPECT_FLOAT_EQ(6.0f, vec.z());
    EXPECT_FLOAT_EQ(2.0f, vec.w());
}


/** @test Verify that the components can be mutated via named spatial aliases (s, t, p, q). */
TEST(Vec4MutationTests, ElementsCanBeMutatedUsingSTPQ)
{
    flcn::Vec4<float> vec;

    vec.s() = 3.0f;
    vec.t() = 1.0f;
    vec.p() = 6.0f;
    vec.q() = 2.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
    EXPECT_FLOAT_EQ(6.0f, vec.p());
    EXPECT_FLOAT_EQ(2.0f, vec.q());
}


/** @test Verify that the components can be mutated via named spatial aliases (r, g, b, a). */
TEST(Vec4MutationTests, ElementsCanBeMutatedUsingRGBA)
{
    flcn::Vec4<float> vec;

    vec.r() = 3.0f;
    vec.g() = 1.0f;
    vec.b() = 6.0f;
    vec.a() = 2.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
    EXPECT_FLOAT_EQ(6.0f, vec.b());
    EXPECT_FLOAT_EQ(2.0f, vec.a());
}


/** @test Verify that the components are accessible via subscript indexing for writing. */
TEST(Vec4MutationTests, ElementsCanBeMutatedUsingIndex)
{
    flcn::Vec4<float> vec;

    vec[0] = 3.0f;
    vec[1] = 1.0f;
    vec[2] = 6.0f;
    vec[3] = 2.0f;

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);
    EXPECT_FLOAT_EQ(2.0f, vec[3]);
}

/** @} */
