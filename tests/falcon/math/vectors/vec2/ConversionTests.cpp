/**
 * @file ConversionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 26, 2026
 *
 * @brief Verifies @ref Vec2 to CVec2 conversion logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"


/**
 * @addtogroup T_FALCON_Vec2_Conv
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec2 to CVec2 conversion.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec2ToCVec2ConversionTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Vec2ToCVec2ConversionTests, SupportedSignedArithmeticTypes);
} // namespace


TYPED_TEST(Vec2ToCVec2ConversionTests, ToVec2_ReturnsAValidVec2)
{
    const TypeParam a = TypeParam(7);
    const TypeParam b = TypeParam(12);
    const flcn::Vec2 vec(a, b);
    const auto cVec = vec.toCVec2();

    static_assert(std::is_same_v<decltype(cVec), const flcn::CVec2<TypeParam>>);

    EXPECT_MAG_EQ(vec.x(), cVec.x());
    EXPECT_MAG_EQ(vec.y(), cVec.y());
}


TYPED_TEST(Vec2ToCVec2ConversionTests, StaticWrapper_ToVec2_ReturnsAValidVec2)
{
    const TypeParam a = TypeParam(7);
    const TypeParam b = TypeParam(12);
    const flcn::Vec2 vec(a, b);
    const auto cVec = vec.toCVec2();

    static_assert(std::is_same_v<decltype(cVec), const flcn::CVec2<TypeParam>>);

    EXPECT_MAG_EQ(vec.x(), cVec.x());
    EXPECT_MAG_EQ(vec.y(), cVec.y());
}

/** @} */
