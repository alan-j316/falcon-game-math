/**
 * @file SwizzlingTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 06, 2026
 *
 * @brief Verify @ref flcn::Vec2 swizzling logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"


/**
 * @addtogroup T_FALCON_Vec2_Swizzle
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
     * @brief Test fixture for @ref flcn::Vec2 swizzling.
     */
    template <typename>
    class Vec2SwizzlingTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Vec2SwizzlingTests, SupportedArithmeticTypes);
} // namespace



/**************************************
 *            RUNTIME TESTS           *
 **************************************/

/** @test Verify that swizzling returns shuffled vector across different numeric. */
TYPED_TEST(Vec2SwizzlingTests, SwizzlingWorksAcrossDifferentTypes)
{
    const flcn::Vec2 vector(TypeParam(1), TypeParam(2));
    const flcn::Vec2 expectedSwizzling(TypeParam(2), TypeParam(1));

    const auto swizzledVector = vector.template swizzle<Y, X>();

    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/** @test Verify that swizzling returns shuffled vector for boolean vector. */
TEST(Vec2SwizzlingTest, SwizzlingWorksForBooleanVector)
{
    const flcn::Vec2 vector(true, false);
    const flcn::Vec2 expectedSwizzling(false, true);

    const auto swizzledVector = vector.swizzle<Y, X>();

    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/**
 * @test Verify that swizzling using static variant of @ref flcn::Vec2::swizzle
 *        returns shuffled vector across different numeric.
 */
TYPED_TEST(Vec2SwizzlingTests, StaticWrapper_SwizzlingWorksAcrossDifferentTypes)
{
    const flcn::Vec2 vector(TypeParam(1), TypeParam(2));
    const flcn::Vec2 expectedSwizzling(TypeParam(2), TypeParam(1));

    const auto swizzledVector = flcn::Vec2<TypeParam>::template swizzle<Y, X>(vector);

    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/**
 * @test Verify that swizzling using static variant of @ref flcn::Vec2::swizzle
 *        returns shuffled vector for boolean vector.
 */
TEST(Vec2SwizzlingTest, StaticWrapper_SwizzlingWorksForBooleanVector)
{
    const flcn::Vec2 vector(true, false);
    const flcn::Vec2 expectedSwizzling(false, true);

    const auto swizzledVector = flcn::Vec2<bool>::template swizzle<Y, X>(vector);

    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/** @} */
