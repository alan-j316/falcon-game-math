/**
 * @file SwizzlingTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 10, 2026
 *
 * @brief Verify @ref flcn::simd::Vec3 swizzling logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"



/**
 * @addtogroup T_Falcon_Vec3_Swizzle
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
     * @brief Test fixture for @ref flcn::simd::Vec3 swizzling.
     */
    template <typename>
    class SimdVec3SwizzlingTests: public testing::Test
    {};
    TYPED_TEST_SUITE(SimdVec3SwizzlingTests, SupportedArithmeticTypes);
} // namespace



/**************************************
 *            RUNTIME TESTS           *
 **************************************/

/** @test Verify that swizzling returns shuffled vector across different numeric. */
TYPED_TEST(SimdVec3SwizzlingTests, SwizzlingWorksAcrossDifferentTypes)
{
    const flcn::simd::Vec3 vector(TypeParam(1), TypeParam(2), TypeParam(3));
    const flcn::simd::Vec3 expectedSwizzling(TypeParam(3), TypeParam(2), TypeParam(1));

    const auto swizzledVector = vector.template swizzle<Z, Y, X>();
    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/** @test Verify that swizzling returns shuffled vector for boolean vector. */
TEST(SimdVec3SwizzlingTests, SwizzlingWorksForBooleanVector)
{
    const flcn::simd::Vec3 vector(true, false, false);
    const flcn::simd::Vec3 expectedSwizzling(false, false, true);

    const auto swizzledVector = vector.swizzle<Z, Y, X>();
    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/** @test Verify that static variant of swizzling returns shuffled vector across different numeric. */
TYPED_TEST(SimdVec3SwizzlingTests, StaticVariant_SwizzlingWorksAcrossDifferentTypes)
{
    const flcn::simd::Vec3 vector(TypeParam(1), TypeParam(2), TypeParam(3));
    const flcn::simd::Vec3 expectedSwizzling(TypeParam(3), TypeParam(2), TypeParam(1));

    const auto swizzledVector = flcn::simd::Vec3<TypeParam>::template swizzle<Z, Y, X>(vector);
    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/** @test Verify that static variant of swizzling returns shuffled vector for boolean vector. */
TEST(SimdVec3SwizzlingTests, StaticVariant_SwizzlingWorksForBooleanVector)
{
    const flcn::simd::Vec3 vector(true, false, false);
    const flcn::simd::Vec3 expectedSwizzling(false, false, true);

    const auto swizzledVector = flcn::simd::Vec3<bool>::swizzle<Z, Y, X>(vector);
    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}

/** @} */
