/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 15, 2026
 *
 * @brief Verify @ref flcn::simd::Vec2 accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"



/**
 * @addtogroup T_Falcon_Vec2_Access
 * @{
 */


/**************************************
 *            ACCESS TESTS            *
 **************************************/

/** @test Verify that the components are accessible via named spatial aliases (x, y). */
TEST(SimdVec2AccessTests, AccessibleAsXY)
{
    static const flcn::simd::Vec2 vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
}


/** @test Verify that the components are accessible via named spatial aliases (s, t). */
TEST(SimdVec2AccessTests, AccessibleAsST)
{
    const flcn::simd::Vec2 vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
}


/** @test Verify that the components are accessible via named spatial aliases (r, g). */
TEST(SimdVec2AccessTests, AccessibleAsRG)
{
    const flcn::simd::Vec2 vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
}


/** @test Verify that the components are accessible via subscript indexing for reads. */
TEST(SimdVec2AccessTests, AccessibleAsArray)
{
    const flcn::simd::Vec2 vec(3.0f, 1.0f);
    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
}


TEST(SimdVec2AccessTests, ConstVec_AccessibleAsCompileTimeIndex)
{
    const flcn::simd::Vec2 vec(3.0f, 1.0f);
    EXPECT_FLOAT_EQ(3.0f, vec.get<0>());
    EXPECT_FLOAT_EQ(1.0f, vec.get<1>());
}


TEST(SimdVec2AccessTests, NonConstVec_AccessibleAsCompileTimeIndex)
{
    flcn::simd::Vec2 vec(3.0f, 1.0f);
    EXPECT_FLOAT_EQ(3.0f, vec.get<0>());
    EXPECT_FLOAT_EQ(1.0f, vec.get<1>());
}



/**************************************
 *           MUTATION TESTS           *
 **************************************/

/** @test Verify that the components can be mutated via named spatial aliases (x, y). */
TEST(SimdVec2MutationTests, ElementsCanBeMutatedUsingXY)
{
    flcn::simd::Vec2<float> vec{ 0.0f };

    vec.x() = 3.0f;
    vec.y() = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
}


/** @test Verify that the components can be mutated via named spatial aliases (s, t). */
TEST(SimdVec2MutationTests, ElementsCanBeMutatedUsingST)
{
    flcn::simd::Vec2<float> vec{ 0.0f };

    vec.s() = 3.0f;
    vec.t() = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
}


/** @test Verify that the components can be mutated via named spatial aliases (r, g). */
TEST(SimdVec2MutationTests, ElementsCanBeMutatedUsingRG)
{
    flcn::simd::Vec2<float> vec{ 0.0f };

    vec.r() = 3.0f;
    vec.g() = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
}


/** @test Verify that the components are accessible via subscript indexing for writing. */
TEST(SimdVec2MutationTests, ElementsCanBeMutatedUsingIndex)
{
    flcn::simd::Vec2<float> vec{ 0.0f };

    vec[0] = 3.0f;
    vec[1] = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
}

TEST(SimdVec2MutationTests, ElementsCanBeMutatedUsingCompileTimeIndexing)
{
    flcn::simd::Vec2<float> vec{ 0.0f };

    vec.set<0>(3.0f);
    vec.set<1>(1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
}

/** @} */
