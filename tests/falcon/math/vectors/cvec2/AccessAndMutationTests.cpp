/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref flcn::CVec2 accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "CVec2TestSetup.h"




/**
 * @addtogroup T_FALCON_CVec2_Access
 * @{
 */

namespace
{
    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace
    {
        constexpr flcn::CVec2 vector(1, 2);

        /// @test Verify that vector is accessible as <x, y> at compile time.
        static_assert(vector.x() == 1);
        static_assert(vector.y() == 2);

        /// @test Verify that vector is accessible as <r, g> at compile time.
        static_assert(vector.r() == 1);
        static_assert(vector.g() == 2);

        /// @test Verify that vector is accessible as <s, t> at compile time.
        static_assert(vector.s() == 1);
        static_assert(vector.t() == 2);
    } // namespace

} // namespace


/**************************************
 *            ACCESS TESTS            *
 **************************************/

/** @test Verify that the components are accessible via named spatial aliases (x, y). */
TEST(CVec2AccessTests, AccessibleAsXY)
{
    static const flcn::CVec2 vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
}


/** @test Verify that the components are accessible via named spatial aliases (s, t). */
TEST(CVec2AccessTests, AccessibleAsST)
{
    const flcn::CVec2 vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
}


/** @test Verify that the components are accessible via named spatial aliases (r, g). */
TEST(CVec2AccessTests, AccessibleAsRG)
{
    const flcn::CVec2 vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
}


/** @test Verify that the components are accessible via subscript indexing for reads. */
TEST(CVec2AccessTests, AccessibleAsArray)
{
    const flcn::CVec2 vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
}



/**************************************
 *           MUTATION TESTS           *
 **************************************/

/** @test Verify that the components can be mutated via named spatial aliases (x, y). */
TEST(CVec2MutationTests, ElementsCanBeMutatedUsingXY)
{
    flcn::CVec2<float> vec;

    vec.x() = 3.0f;
    vec.y() = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
}


/** @test Verify that the components can be mutated via named spatial aliases (s, t). */
TEST(CVec2MutationTests, ElementsCanBeMutatedUsingST)
{
    flcn::CVec2<float> vec;

    vec.s() = 3.0f;
    vec.t() = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
}


/** @test Verify that the components can be mutated via named spatial aliases (r, g). */
TEST(CVec2MutationTests, ElementsCanBeMutatedUsingRG)
{
    flcn::CVec2<float> vec;

    vec.r() = 3.0f;
    vec.g() = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
}


/** @test Verify that the components are accessible via subscript indexing for writing. */
TEST(CVec2MutationTests, ElementsCanBeMutatedUsingIndex)
{
    flcn::CVec2<float> vec;

    vec[0] = 3.0f;
    vec[1] = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
}



/** @} */
