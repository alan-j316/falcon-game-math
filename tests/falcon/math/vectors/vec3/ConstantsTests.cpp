/**
 * @file ConstantsTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 03, 2026
 *
 * @brief Verify @ref flcn::Vec3 constants (@ref flcn::Vec3::ONE(), @ref flcn::Vec3::ZERO(), etc).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"

/**
 * @addtogroup T_Falcon_Vec3_Const
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec3 constants.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec3ConstantsTests: public testing::Test
    {
    protected:
        T _one  = T(1);
        T _zero = T(0);
    };
    TYPED_TEST_SUITE(Vec3ConstantsTests, SupportedSignedArithmeticTypes);

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

/** @test Verify that @ref flcn::Vec3::ONE() returns a 3D vector with unit components. */
TYPED_TEST(Vec3ConstantsTests, ONE_ReturnsVectorWithUnitComponents)
{
    const auto one = TypeParam(1);
    EXPECT_VEC_CONTAINS(flcn::Vec3<TypeParam>::one(), one, one, one);
}


/** @test Verify that @ref flcn::Vec3::ZERO returns a 3D vector with zero components. */
TYPED_TEST(Vec3ConstantsTests, ZERO_ReturnsVectorWithZeroComponents) { EXPECT_VEC_ZERO(flcn::Vec3<TypeParam>::zero()); }


/** @test Verify that @ref flcn::Vec3<float>::INF returns a 3D vector with infinity components. */
TEST(Vec3Constants, INF_Float_ReturnsFloatVectorWithInfinityComponents)
{
    const auto inf = flcn::Vec3<float>::inf();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC3_POS_INF(inf)
}


/** @test Verify that @ref flcn::Vec3<double>::INF returns a 3D vector with infinity components. */
TEST(Vec3Constants, INF_Double_ReturnsDoubleVectorWithInfinityComponents)
{
    const auto inf = flcn::Vec3<double>::inf();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC3_POS_INF(inf)
}


/** @test Verify that @ref flcn::Vec3<float>::INF_NEG returns a 3D vector with negative infinity components. */
TEST(Vec3Constants, INFNEG_Float_ReturnsFloatVectorWithNegativeInfinityComponents)
{
    const auto inf = flcn::Vec3<float>::infNeg();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC3_NEG_INF(inf)
}


/** @test Verify that @ref flcn::Vec3<double>::INF_NEG returns a 3D vector with negative infinity components. */
TEST(Vec3Constants, INFNEG_Double_ReturnsDoubleVectorWithNegativeInfinityComponents)
{
    const auto inf = flcn::Vec3<double>::infNeg();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC3_NEG_INF(inf)
}


/** @test Verify that @ref flcn::Vec3<float>::QNAN returns a 3D vector with NaN components. */
TEST(Vec3Constants, Float_QNAN_ReturnsFloatVectorWithNaNComponents)
{
    const auto nan = flcn::Vec3<float>::qnan();
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
}


/** @test Verify that @ref flcn::Vec3<double>::QNAN returns a 3D vector with NaN components. */
TEST(Vec3Constants, Double_QNAN_ReturnsDoubleVectorWithNaNComponents)
{
    const auto nan = flcn::Vec3<double>::qnan();
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
}


/** @test Verify that @ref flcn::Vec3::RIGHT returns a unit vector aligned with positive x-axis. */
TYPED_TEST(Vec3ConstantsTests, RIGHT_ReturnsUnitVectorWithOnlyPositiveXComponent)
{
    const auto vec = flcn::Vec3<TypeParam>::right();
    EXPECT_VEC_CONTAINS(vec, this->_one, this->_zero, this->_zero);
}


/** @test Verify that @ref flcn::Vec3::LEFT returns a unit vector aligned with negative x-axis. */
TYPED_TEST(Vec3ConstantsTests, LEFT_ReturnsUnitVectorWithOnlyNegativeXComponent)
{
    const auto vec = flcn::Vec3<TypeParam>::left();
    EXPECT_VEC_CONTAINS(vec, TypeParam(-this->_one), this->_zero, this->_zero);
}


/** @test Verify that @ref flcn::Vec3::UP returns a unit vector aligned with positive y-axis. */
TYPED_TEST(Vec3ConstantsTests, UP_ReturnsUnitVectorWithOnlyPositiveYComponent)
{
    const auto vec = flcn::Vec3<TypeParam>::up();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_one, this->_zero);
}


/** @test Verify that @ref flcn::Vec3::DOWN returns a unit vector aligned with negative y-axis. */
TYPED_TEST(Vec3ConstantsTests, DOWN_ReturnsUnitVectorWithOnlyNegativeYComponent)
{
    const auto vec = flcn::Vec3<TypeParam>::down();
    EXPECT_VEC_CONTAINS(vec, this->_zero, TypeParam(-this->_one), this->_zero);
}


#ifdef FALCON_LEFT_HANDED

/** @test Verify that @ref flcn::Vec3::FORWARD returns a unit vector aligned with positive z-axis. */
TYPED_TEST(Vec3ConstantsTests, FORWARD_ReturnsUnitVectorWithOnlyPositiveZComponent)
{
    const auto vec = flcn::Vec3<TypeParam>::forward();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, this->_one);
}


/** @test Verify that @ref flcn::Vec3::BACKWARD returns a unit vector aligned with negative z-axis. */
TYPED_TEST(Vec3ConstantsTests, BACKWARD_ReturnsUnitVectorWithOnlyNegativeZComponent)
{
    const auto vec = flcn::Vec3<TypeParam>::backward();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, TypeParam(-this->_one));
}

#else

/** @test Verify that @ref flcn::Vec3::FORWARD returns a unit vector aligned with negative z-axis. */
TYPED_TEST(Vec3ConstantsTests, FORWARD_ReturnsUnitVectorWithOnlyPositiveZComponent)
{
    const auto vec = flcn::Vec3<TypeParam>::forward();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, TypeParam(-this->_one));
}


/** @test Verify that @ref flcn::Vec3::BACKWARD returns a unit vector aligned with positive z-axis. */
TYPED_TEST(Vec3ConstantsTests, BACKWARD_ReturnsUnitVectorWithOnlyNegativeZComponent)
{
    const auto vec = flcn::Vec3<TypeParam>::backward();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, this->_one);
}

#endif

/** @} */
