/**
 * @file DeathTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 28, 2026
 *
 * @brief Falcon Math Utility Death tests.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#ifdef ENABLE_DEBUG_TESTS
    #include "CommonSetup.h"
    #include "NormalizationTestFixture.h"
    #include "ProjectionTestFixture.h"

    #include <falcon/math/vectors/Vec2.h>
    #include <gtest/gtest.h>



/// +---------------------------------------------------------------------------------------+
/// |                             NORMALIZATION TESTS                                       |
/// +---------------------------------------------------------------------------------------+

TYPED_TEST(Vec2NormalizationTests, StaticWrapper_ZeroMagnitudeTriggersAssertInDebugMode)
{
    const flcn::Vec2<TypeParam> zVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::normalize(zVec)), "");
}


TYPED_TEST(Vec3NormalizationTests, StaticWrapper_ZeroMagnitudeTriggersAssertInDebugMode)
{
    const flcn::Vec3<TypeParam> zVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::normalize(zVec)), "");
}


TYPED_TEST(Vec4NormalizationTests, StaticWrapper_ZeroMagnitudeTriggersAssertInDebugMode)
{
    const flcn::Vec4<TypeParam> zVec(0, 0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::normalize(zVec)), "");
}


TYPED_TEST(SimdVec2NormalizationTests, StaticWrapper_ZeroMagnitudeTriggersAssertInDebugMode)
{
    const flcn::simd::Vec2<TypeParam> zVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::normalize(zVec)), "");
}


TYPED_TEST(SimdVec3NormalizationTests, StaticWrapper_ZeroMagnitudeTriggersAssertInDebugMode)
{
    const flcn::simd::Vec3<TypeParam> zVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::normalize(zVec)), "");
}



/// +---------------------------------------------------------------------------------------+
/// |                               PROJECTION TESTS                                        |
/// +---------------------------------------------------------------------------------------+

TYPED_TEST(Vec2ProjectionTests, StaticWrapper_ProjectionOntoZeroVectorTriggersAssertionInCallback)
{
    const flcn::Vec2<TypeParam> zeroVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::project(this->_vec, zeroVec)), "");
}


TYPED_TEST(Vec2RejectionTests, StaticWrapper_FromZeroVectorTriggersAssertionInCallback)
{
    const flcn::Vec2<TypeParam> zeroVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::reject(this->_vec, zeroVec)), "");
}


TYPED_TEST(Vec3ProjectionTests, StaticWrapper_ProjectionOntoZeroVectorTriggersAssertionInCallback)
{
    const flcn::Vec3<TypeParam> zeroVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::project(this->_vec, zeroVec)), "");
}


TYPED_TEST(Vec3RejectionTests, StaticWrapper_FromZeroVectorTriggersAssertionInCallback)
{
    const flcn::Vec3<TypeParam> zeroVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::reject(this->_vec, zeroVec)), "");
}


TYPED_TEST(Vec4ProjectionTests, StaticWrapper_ProjectionOntoZeroVectorTriggersAssertionInCallback)
{
    const flcn::Vec4<TypeParam> zeroVec(0, 0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::project(this->_vec, zeroVec)), "");
}


TYPED_TEST(Vec4RejectionTests, StaticWrapper_FromZeroVectorTriggersAssertionInCallback)
{
    const flcn::Vec4<TypeParam> zeroVec(0, 0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::reject(this->_vec, zeroVec)), "");
}


TYPED_TEST(SimdVec2ProjectionTests, StaticWrapper_ProjectionOntoZeroVectorTriggersAssertionInCallback)
{
    const flcn::simd::Vec2<TypeParam> zeroVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::project(this->_vec, zeroVec)), "");
}


TYPED_TEST(SimdVec2RejectionTests, StaticWrapper_FromZeroVectorTriggersAssertionInCallback)
{
    const flcn::simd::Vec2<TypeParam> zeroVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::reject(this->_vec, zeroVec)), "");
}


/// +---------------------------------------------------------------------------------------+
/// |                                REJECTION TESTS                                        |
/// +---------------------------------------------------------------------------------------+

#endif
