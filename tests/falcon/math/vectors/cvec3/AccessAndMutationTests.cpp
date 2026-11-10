/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 10, 2026
 *
 * @brief Verify @ref flcn::CVec3 accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CVec3TestSetup.h"


/**
 * @addtogroup T_Falcon_CVec3_Access
 * @{
 */

namespace
{
    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace
    {
        constexpr flcn::CVec3 vector(1, 2, 3);

        /// @test Verify that vector is accessible as <x, y, z> at compile time.
        static_assert(vector.x() == 1);
        static_assert(vector.y() == 2);
        static_assert(vector.z() == 3);

        /// @test Verify that vector is accessible as <r, g, b> at compile time.
        static_assert(vector.r() == 1);
        static_assert(vector.g() == 2);
        static_assert(vector.b() == 3);

        /// @test Verify that vector is accessible as <s, t, p> at compile time.
        static_assert(vector.s() == 1);
        static_assert(vector.t() == 2);
        static_assert(vector.p() == 3);

    } // namespace

}



/**************************************
 *            ACCESS TESTS            *
 **************************************/

/** @test Verify that the components are accessible via named spatial aliases (x, y, z). */
TEST(CVec3AccessTests, AccessibleAsXYZW)
{
    const flcn::CVec3 vec(3.0f, 1.0f, 6.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
    EXPECT_FLOAT_EQ(6.0f, vec.z());
}


/** @test Verify that the components are accessible via named spatial aliases (s, t, p). */
TEST(CVec3AccessTests, AccessibleAsSTPQ)
{
    const flcn::CVec3 vec(3.0f, 1.0f, 6.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
    EXPECT_FLOAT_EQ(6.0f, vec.p());
}


/** @test Verify that the components are accessible via named spatial aliases (r, g, b). */
TEST(CVec3AccessTests, AccessibleAsRGBA)
{
    const flcn::CVec3 vec(3.0f, 1.0f, 6.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
    EXPECT_FLOAT_EQ(6.0f, vec.b());
}


/** @test Verify that the components are accessible via subscript indexing for reads. */
TEST(CVec3AccessTests, AccessibleAsArray)
{
    const flcn::CVec3 vec(3.0f, 1.0f, 6.0f);

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);
}



/**************************************
 *           MUTATION TESTS           *
 **************************************/

/** @test Verify that the components can be mutated via named spatial aliases (x, y, z). */
TEST(CVec3MutationTests, ElementsCanBeMutatedUsingXYZW)
{
    flcn::CVec3<float> vec;

    vec.x() = 3.0f;
    vec.y() = 1.0f;
    vec.z() = 6.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
    EXPECT_FLOAT_EQ(6.0f, vec.z());
}


/** @test Verify that the components can be mutated via named spatial aliases (s, t, p). */
TEST(CVec3MutationTests, ElementsCanBeMutatedUsingSTPQ)
{
    flcn::CVec3<float> vec;

    vec.s() = 3.0f;
    vec.t() = 1.0f;
    vec.p() = 6.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
    EXPECT_FLOAT_EQ(6.0f, vec.p());
}


/** @test Verify that the components can be mutated via named spatial aliases (r, g, b). */
TEST(CVec3MutationTests, ElementsCanBeMutatedUsingRGBA)
{
    flcn::CVec3<float> vec;

    vec.r() = 3.0f;
    vec.g() = 1.0f;
    vec.b() = 6.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
    EXPECT_FLOAT_EQ(6.0f, vec.b());
}


/** @test Verify that the components are accessible via subscript indexing for writing. */
TEST(CVec3MutationTests, ElementsCanBeMutatedUsingIndex)
{
    flcn::CVec3<float> vec;

    vec[0] = 3.0f;
    vec[1] = 1.0f;
    vec[2] = 6.0f;

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);
}

/** @} */
