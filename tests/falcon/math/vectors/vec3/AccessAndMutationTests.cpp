/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 10, 2026
 *
 * @brief Verify @ref flcn::Vec3 accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"


/**
 * @addtogroup T_Falcon_Vec3_Access
 * @{
 */

/**************************************
 *            ACCESS TESTS            *
 **************************************/

/** @test Verify that the components are accessible via named spatial aliases (x, y, z). */
TEST(Vec3AccessTests, AccessibleAsXYZW)
{
    const flcn::Vec3 vec(3.0f, 1.0f, 6.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
    EXPECT_FLOAT_EQ(6.0f, vec.z());
}


/** @test Verify that the components are accessible via named spatial aliases (s, t, p). */
TEST(Vec3AccessTests, AccessibleAsSTPQ)
{
    const flcn::Vec3 vec(3.0f, 1.0f, 6.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
    EXPECT_FLOAT_EQ(6.0f, vec.p());
}


/** @test Verify that the components are accessible via named spatial aliases (r, g, b). */
TEST(Vec3AccessTests, AccessibleAsRGBA)
{
    const flcn::Vec3 vec(3.0f, 1.0f, 6.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
    EXPECT_FLOAT_EQ(6.0f, vec.b());
}


/** @test Verify that the components are accessible via subscript indexing for reads. */
TEST(Vec3AccessTests, AccessibleAsArray)
{
    const flcn::Vec3 vec(3.0f, 1.0f, 6.0f);

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);
}


TEST(Vec3AccessTests, ConstVec_AccessibleAsCompileTimeIndex)
{
    const flcn::Vec3 vec(3.0f, 1.0f, 6.0f);
    EXPECT_FLOAT_EQ(3.0f, vec.get<0>());
    EXPECT_FLOAT_EQ(1.0f, vec.get<1>());
    EXPECT_FLOAT_EQ(6.0f, vec.get<2>());
}


TEST(Vec3AccessTests, NonConstVec_AccessibleAsCompileTimeIndex)
{
    flcn::Vec3 vec(3.0f, 1.0f, 6.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.get<0>());
    EXPECT_FLOAT_EQ(1.0f, vec.get<1>());
    EXPECT_FLOAT_EQ(6.0f, vec.get<2>());
}



/**************************************
 *           MUTATION TESTS           *
 **************************************/

/** @test Verify that the components can be mutated via named spatial aliases (x, y, z). */
TEST(Vec3MutationTests, ElementsCanBeMutatedUsingXYZW)
{
    flcn::Vec3<float> vec;

    vec.x() = 3.0f;
    vec.y() = 1.0f;
    vec.z() = 6.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
    EXPECT_FLOAT_EQ(6.0f, vec.z());
}


/** @test Verify that the components can be mutated via named spatial aliases (s, t, p). */
TEST(Vec3MutationTests, ElementsCanBeMutatedUsingSTPQ)
{
    flcn::Vec3<float> vec;

    vec.s() = 3.0f;
    vec.t() = 1.0f;
    vec.p() = 6.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
    EXPECT_FLOAT_EQ(6.0f, vec.p());
}


/** @test Verify that the components can be mutated via named spatial aliases (r, g, b). */
TEST(Vec3MutationTests, ElementsCanBeMutatedUsingRGBA)
{
    flcn::Vec3<float> vec;

    vec.r() = 3.0f;
    vec.g() = 1.0f;
    vec.b() = 6.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
    EXPECT_FLOAT_EQ(6.0f, vec.b());
}


/** @test Verify that the components are accessible via subscript indexing for writing. */
TEST(Vec3MutationTests, ElementsCanBeMutatedUsingIndex)
{
    flcn::Vec3<float> vec;

    vec[0] = 3.0f;
    vec[1] = 1.0f;
    vec[2] = 6.0f;

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);
}


TEST(Vec3MutationTests, ElementsCanBeMutatedUsingCompileTimeIndexing)
{
    flcn::Vec3<float> vec{ 0.0f };

    vec.set<0>(3.0f);
    vec.set<1>(1.0f);
    vec.set<2>(6.0f);

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);
}

/** @} */
