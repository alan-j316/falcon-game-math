/**
 * @file ConstantsTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref flcn::Vec2 constants (@ref flcn::Vec2::ONE, @ref flcn::Vec2::ZERO, etc).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"



/**
 * @addtogroup T_FALCON_Vec2_Const
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec2 constants.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec2ConstantsTests: public testing::Test
    {
    protected:
        T _one  = T(1);
        T _zero = T(0);
    };
    TYPED_TEST_SUITE(Vec2ConstantsTests, SupportedSignedArithmeticTypes);
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Vec2ConstantsTests, ONE_ReturnsVectorWithUnitComponents)
{
    const auto one = TypeParam(1);
    EXPECT_VEC_CONTAINS(flcn::Vec2<TypeParam>::one(), one, one);
}


TYPED_TEST(Vec2ConstantsTests, ZERO_ReturnsVectorWithZeroComponents) { EXPECT_VEC_ZERO(flcn::Vec2<TypeParam>::zero()); }


TEST(Vec2ConstantsTests, INF_Float_ReturnsFloatVectorWithInfiniteComponents)
{
    const auto inf = flcn::Vec2<float>::inf();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC2_POS_INF(inf)
}


TEST(Vec2ConstantsTests, INF_Double_ReturnsDoubleVectorWithInfinityComponents)
{
    const auto inf = flcn::Vec2<double>::inf();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC2_POS_INF(inf)
}


TEST(Vec2ConstantsTests, INFNEG_Float_ReturnsFloatVectorWithNegativeInfinityComponents)
{
    const auto inf = flcn::Vec2<float>::infNeg();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC2_NEG_INF(inf)
}


TEST(Vec2ConstantsTests, INFNEG_Double_ReturnsDoubleVectorWithNegativeInfinityComponents)
{
    const auto inf = flcn::Vec2<double>::infNeg();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC2_NEG_INF(inf)
}


TEST(Vec2ConstantsTests, Float_QNAN_ReturnsFloatVectorWithNaNComponents)
{
    const auto nan = flcn::Vec2<float>::qnan();
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
}


TEST(Vec2ConstantsTests, Double_QNAN_ReturnsDoubleVectorWithNaNComponents)
{
    const auto nan = flcn::Vec2<double>::qnan();
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
}


TYPED_TEST(Vec2ConstantsTests, RIGHT_ReturnsUnitVectorWithOnlyPositiveXComponent)
{
    const auto x = flcn::Vec2<TypeParam>::right();
    EXPECT_VEC_CONTAINS(x, this->_one, this->_zero);
}


TYPED_TEST(Vec2ConstantsTests, LEFT_ReturnsUnitVectorWithOnlyNegativeXComponent)
{
    const auto x = flcn::Vec2<TypeParam>::left();
    EXPECT_VEC_CONTAINS(x, TypeParam(-this->_one), this->_zero);
}


TYPED_TEST(Vec2ConstantsTests, UP_ReturnsUnitVectorWithOnlyPositiveYComponent)
{
    const auto x = flcn::Vec2<TypeParam>::up();
    EXPECT_VEC_CONTAINS(x, this->_zero, this->_one);
}


TYPED_TEST(Vec2ConstantsTests, DOWN_ReturnsUnitVectorWithOnlyNegativeYComponent)
{
    const auto x = flcn::Vec2<TypeParam>::down();
    EXPECT_VEC_CONTAINS(x, this->_zero, TypeParam(-this->_one));
}

/** @} */
