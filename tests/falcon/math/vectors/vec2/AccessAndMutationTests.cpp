/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 15, 2026
 *
 * @brief Verify @ref flcn::Vec2 accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"



/**
 * @addtogroup T_FALCON_Vec2_Access
 * @{
 */


/**************************************
 *            ACCESS TESTS            *
 **************************************/

/** @test Verify that the components are accessible via named spatial aliases (x, y). */
TEST(Vec2AccessTests, AccessibleAsXY)
{
    static const flcn::Vec2 vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
}


/** @test Verify that the components are accessible via named spatial aliases (s, t). */
TEST(Vec2AccessTests, AccessibleAsST)
{
    const flcn::Vec2 vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
}


/** @test Verify that the components are accessible via named spatial aliases (r, g). */
TEST(Vec2AccessTests, AccessibleAsRG)
{
    const flcn::Vec2 vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
}


/** @test Verify that the components are accessible via subscript indexing for reads. */
TEST(Vec2AccessTests, AccessibleAsArray)
{
    const flcn::Vec2 vec(3.0f, 1.0f);
    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
}


TEST(Vec2AccessTests, ConstVec_AccessibleAsCompileTimeIndex)
{
    const flcn::Vec2 vec(3.0f, 1.0f);
    EXPECT_FLOAT_EQ(3.0f, vec.get<0>());
    EXPECT_FLOAT_EQ(1.0f, vec.get<1>());
}


TEST(Vec2AccessTests, NonConstVec_AccessibleAsCompileTimeIndex)
{
    flcn::Vec2 vec(3.0f, 1.0f);
    EXPECT_FLOAT_EQ(3.0f, vec.get<0>());
    EXPECT_FLOAT_EQ(1.0f, vec.get<1>());
}



/**************************************
 *           MUTATION TESTS           *
 **************************************/

/** @test Verify that the components can be mutated via named spatial aliases (x, y). */
TEST(Vec2MutationTests, ElementsCanBeMutatedUsingXY)
{
    flcn::Vec2<float> vec;

    vec.x() = 3.0f;
    vec.y() = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
}


/** @test Verify that the components can be mutated via named spatial aliases (s, t). */
TEST(Vec2MutationTests, ElementsCanBeMutatedUsingST)
{
    flcn::Vec2<float> vec;

    vec.s() = 3.0f;
    vec.t() = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
}


/** @test Verify that the components can be mutated via named spatial aliases (r, g). */
TEST(Vec2MutationTests, ElementsCanBeMutatedUsingRG)
{
    flcn::Vec2<float> vec;

    vec.r() = 3.0f;
    vec.g() = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
}


/** @test Verify that the components are accessible via subscript indexing for writing. */
TEST(Vec2MutationTests, ElementsCanBeMutatedUsingIndex)
{
    flcn::Vec2<float> vec;

    vec[0] = 3.0f;
    vec[1] = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
}

TEST(Vec2MutationTests, ElementsCanBeMutatedUsingCompileTimeIndexing)
{
    flcn::Vec2<float> vec;

    vec.set<0>(3.0f);
    vec.set<1>(1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
}

/** @} */
