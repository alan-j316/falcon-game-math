/**
 * @file ConstantsTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 03, 2026
 *
 * @brief Verify @ref flcn::Vec4 constants (@ref flcn::Vec4::ONE(), @ref flcn::Vec4::ZERO(), etc).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec4TestSetup.h"


/**
 * @addtogroup T_FALCON_Vec4_Const
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec4 constants.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec4ConstantsTests: public testing::Test
    {
    protected:
        T _one  = T(1);
        T _zero = T(0);
    };
    TYPED_TEST_SUITE(Vec4ConstantsTests, SupportedSignedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace
    {
        /// @test Verify that @ref Vec4::one() returns a one vector at compile time.
        static_assert(flcn::Vec4<int>::one().x() == 1);
        static_assert(flcn::Vec4<int>::one().y() == 1);
        static_assert(flcn::Vec4<int>::one().z() == 1);
        static_assert(flcn::Vec4<int>::one().w() == 1);

        /// @test Verify that @ref Vec4::zero() returns a zero vector at compile time.
        static_assert(flcn::Vec4<int>::zero().x() == 0);
        static_assert(flcn::Vec4<int>::zero().y() == 0);
        static_assert(flcn::Vec4<int>::zero().z() == 0);
        static_assert(flcn::Vec4<int>::zero().w() == 0);

        /// @test Verify that @ref Vec4::inf() returns a infinity vector at compile time.
        static_assert(flcn::isinf(flcn::Vec4<float>::inf().x()));
        static_assert(flcn::isinf(flcn::Vec4<float>::inf().y()));
        static_assert(flcn::isinf(flcn::Vec4<float>::inf().z()));
        static_assert(flcn::isinf(flcn::Vec4<float>::inf().w()));

        /// @test Verify that @ref Vec4::infNeg() returns a negative infinity vector at compile time.
        static_assert(flcn::isinf(flcn::Vec4<float>::infNeg().x()));
        static_assert(flcn::isinf(flcn::Vec4<float>::infNeg().y()));
        static_assert(flcn::isinf(flcn::Vec4<float>::infNeg().z()));
        static_assert(flcn::isinf(flcn::Vec4<float>::infNeg().w()));

        /// @test Verify that @ref Vec4::qnan() returns a qnan vector at compile time.
        static_assert(flcn::isnan(flcn::Vec4<float>::qnan().x()));
        static_assert(flcn::isnan(flcn::Vec4<float>::qnan().y()));
        static_assert(flcn::isnan(flcn::Vec4<float>::qnan().z()));
        static_assert(flcn::isnan(flcn::Vec4<float>::qnan().w()));

        /// @test Verify that @ref Vec4::left() returns a valid vector at compile time.
        static_assert(flcn::Vec4<int>::left().x() == -1);
        static_assert(flcn::Vec4<int>::left().y() == 0);
        static_assert(flcn::Vec4<int>::left().z() == 0);
        static_assert(flcn::Vec4<int>::left().w() == 0);

        /// @test Verify that @ref Vec4::right() returns a valid vector at compile time.
        static_assert(flcn::Vec4<int>::right().x() == 1);
        static_assert(flcn::Vec4<int>::right().y() == 0);
        static_assert(flcn::Vec4<int>::right().z() == 0);
        static_assert(flcn::Vec4<int>::right().w() == 0);

        /// @test Verify that @ref Vec4::up() returns a valid vector at compile time.
        static_assert(flcn::Vec4<int>::up().x() == 0);
        static_assert(flcn::Vec4<int>::up().y() == 1);
        static_assert(flcn::Vec4<int>::up().z() == 0);
        static_assert(flcn::Vec4<int>::up().w() == 0);

        /// @test Verify that @ref Vec4::down() returns a valid vector at compile time.
        static_assert(flcn::Vec4<int>::down().x() == 0);
        static_assert(flcn::Vec4<int>::down().y() == -1);
        static_assert(flcn::Vec4<int>::down().z() == 0);
        static_assert(flcn::Vec4<int>::down().w() == 0);


#ifdef FALCON_LEFT_HANDED
        /// @test Verify that @ref Vec4::forward() (LHS) returns a valid vector at compile time.
        static_assert(flcn::Vec4<int>::forward().x() == 0);
        static_assert(flcn::Vec4<int>::forward().y() == 0);
        static_assert(flcn::Vec4<int>::forward().z() == 1);
        static_assert(flcn::Vec4<int>::forward().w() == 0);


        /// @test Verify that @ref Vec4::backward() (LHS) returns a valid vector at compile time.
        static_assert(flcn::Vec4<int>::backward().x() == 0);
        static_assert(flcn::Vec4<int>::backward().y() == 0);
        static_assert(flcn::Vec4<int>::backward().z() == -1);
        static_assert(flcn::Vec4<int>::backward().w() == 0);
#else

        /// @test Verify that @ref Vec4::forward() (RHS) returns a valid vector at compile time.
        static_assert(flcn::Vec4<int>::forward().x() == 0);
        static_assert(flcn::Vec4<int>::forward().y() == 0);
        static_assert(flcn::Vec4<int>::forward().z() == -1);
        static_assert(flcn::Vec4<int>::forward().w() == 0);


        /// @test Verify that @ref Vec4::backward() (RHS) returns a valid vector at compile time.
        static_assert(flcn::Vec4<int>::backward().x() == 0);
        static_assert(flcn::Vec4<int>::backward().y() == 0);
        static_assert(flcn::Vec4<int>::backward().z() == 1);
        static_assert(flcn::Vec4<int>::backward().w() == 0);
#endif

    } // namespace
} // namespace


/** @test Verify that @ref flcn::Vec4::ONE() returns a 4D vector with unit components. */
TYPED_TEST(Vec4ConstantsTests, ONE_ReturnsVectorWithUnitComponents)
{
    const auto one = TypeParam(1);
    EXPECT_VEC_CONTAINS(flcn::Vec4<TypeParam>::one(), one, one, one, one);
}


/** @test Verify that @ref flcn::Vec4::ZERO returns a 4D vector with zero components. */
TYPED_TEST(Vec4ConstantsTests, ZERO_ReturnsVectorWithZeroComponents) { EXPECT_VEC_ZERO(flcn::Vec4<TypeParam>::zero()); }


/** @test Verify that @ref flcn::Vec4<float>::INF returns a 4D vector with infinity components. */
TEST(Vec4Constants, INF_Float_ReturnsFloatVectorWithInfinityComponents)
{
    const auto inf = flcn::Vec4<float>::inf();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC4_POS_INF(inf)
}


/** @test Verify that @ref flcn::Vec4<double>::INF returns a 4D vector with infinity components. */
TEST(Vec4Constants, INF_Double_ReturnsDoubleVectorWithInfinityComponents)
{
    const auto inf = flcn::Vec4<double>::inf();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC4_POS_INF(inf)
}


/** @test Verify that @ref flcn::Vec4<float>::INF_NEG returns a 4D vector with negative infinity components. */
TEST(Vec4Constants, INFNEG_Float_ReturnsFloatVectorWithNegativeInfinityComponents)
{
    const auto inf = flcn::Vec4<float>::infNeg();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC4_NEG_INF(inf)
}


/** @test Verify that @ref flcn::Vec4<double>::INF_NEG returns a 4D vector with negative infinity components. */
TEST(Vec4Constants, INFNEG_Double_ReturnsDoubleVectorWithNegativeInfinityComponents)
{
    const auto inf = flcn::Vec4<double>::infNeg();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC4_NEG_INF(inf)
}


/** @test Verify that @ref flcn::Vec4<float>::QNAN returns a 4D vector with NaN components. */
TEST(Vec4Constants, Float_QNAN_ReturnsFloatVectorWithNaNComponents)
{
    const auto nan = flcn::Vec4<float>::qnan();
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
}


/** @test Verify that @ref flcn::Vec4<double>::QNAN returns a 4D vector with NaN components. */
TEST(Vec4Constants, Double_QNAN_ReturnsDoubleVectorWithNaNComponents)
{
    const auto nan = flcn::Vec4<double>::qnan();
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
}


/** @test Verify that @ref flcn::Vec4::RIGHT returns a unit vector aligned with positive x-axis. */
TYPED_TEST(Vec4ConstantsTests, RIGHT_ReturnsUnitVectorWithOnlyPositiveXComponent)
{
    const auto vec = flcn::Vec4<TypeParam>::right();
    EXPECT_VEC_CONTAINS(vec, this->_one, this->_zero, this->_zero, this->_zero);
}


/** @test Verify that @ref flcn::Vec4::LEFT returns a unit vector aligned with negative x-axis. */
TYPED_TEST(Vec4ConstantsTests, LEFT_ReturnsUnitVectorWithOnlyNegativeXComponent)
{
    const auto vec = flcn::Vec4<TypeParam>::left();
    EXPECT_VEC_CONTAINS(vec, TypeParam(-this->_one), this->_zero, this->_zero, this->_zero);
}


/** @test Verify that @ref flcn::Vec4::UP returns a unit vector aligned with positive y-axis. */
TYPED_TEST(Vec4ConstantsTests, UP_ReturnsUnitVectorWithOnlyPositiveYComponent)
{
    const auto vec = flcn::Vec4<TypeParam>::up();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_one, this->_zero, this->_zero);
}


/** @test Verify that @ref flcn::Vec4::DOWN returns a unit vector aligned with negative y-axis. */
TYPED_TEST(Vec4ConstantsTests, DOWN_ReturnsUnitVectorWithOnlyNegativeYComponent)
{
    const auto vec = flcn::Vec4<TypeParam>::down();
    EXPECT_VEC_CONTAINS(vec, this->_zero, TypeParam(-this->_one), this->_zero, this->_zero);
}


#ifdef FALCON_LEFT_HANDED

/** @test Verify that @ref flcn::Vec4::FORWARD returns a unit vector aligned with positive z-axis. */
TYPED_TEST(Vec4ConstantsTests, FORWARD_ReturnsUnitVectorWithOnlyPositiveZComponent)
{
    const auto vec = flcn::Vec4<TypeParam>::forward();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, this->_one, this->_zero);
}


/** @test Verify that @ref flcn::Vec4::BACKWARD returns a unit vector aligned with negative z-axis. */
TYPED_TEST(Vec4ConstantsTests, BACKWARD_ReturnsUnitVectorWithOnlyNegativeZComponent)
{
    const auto vec = flcn::Vec4<TypeParam>::backward();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, TypeParam(-this->_one), this->_zero);
}

#else

/** @test Verify that @ref flcn::Vec4::FORWARD returns a unit vector aligned with negative z-axis. */
TYPED_TEST(Vec4ConstantsTests, FORWARD_ReturnsUnitVectorWithOnlyPositiveZComponent)
{
    const auto vec = flcn::Vec4<TypeParam>::forward();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, TypeParam(-this->_one), this->_zero);
}


/** @test Verify that @ref flcn::Vec4::BACKWARD returns a unit vector aligned with positive z-axis. */
TYPED_TEST(Vec4ConstantsTests, BACKWARD_ReturnsUnitVectorWithOnlyNegativeZComponent)
{
    const auto vec = flcn::Vec4<TypeParam>::backward();
    EXPECT_VEC_CONTAINS(vec, this->_zero, this->_zero, this->_one, this->_zero);
}

#endif

/** @} */
