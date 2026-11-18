/**
 * @file ConversionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 25, 2026
 *
 * @brief Verifies @ref Vec2 to Vec2 conversion logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"

#include <falcon/math/vectors/simd/Vec2.h>
#include <falcon/math/vectors/Vec2.h>


/**
 * @addtogroup T_Falcon_Vec2_Conv
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec2 to Vec2 conversion.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec2ToVec2ConversionTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Vec2ToVec2ConversionTests, SupportedSignedArithmeticTypes);
} // namespace


TYPED_TEST(Vec2ToVec2ConversionTests, ToVec2_ReturnsAValidVec2)
{
    const auto a = TypeParam(7);
    const auto b = TypeParam(12);
    flcn::Vec2 cVec(a, b);
    const auto vec = cVec.toVec2();

    static_assert(std::is_same_v<decltype(vec), const flcn::simd::Vec2<TypeParam>>);

    EXPECT_MAG_EQ(vec.x(), cVec.x());
    EXPECT_MAG_EQ(vec.y(), cVec.y());
}


TYPED_TEST(Vec2ToVec2ConversionTests, StaticWrapper_ToVec2_ReturnsAValidVec2)
{
    const auto a = TypeParam(7);
    const auto b = TypeParam(12);
    flcn::Vec2 cVec(a, b);
    const auto vec = flcn::Vec2<TypeParam>::toVec2(cVec);

    static_assert(std::is_same_v<decltype(vec), const flcn::simd::Vec2<TypeParam>>);

    EXPECT_MAG_EQ(vec.x(), cVec.x());
    EXPECT_MAG_EQ(vec.y(), cVec.y());
}

/** @} */
