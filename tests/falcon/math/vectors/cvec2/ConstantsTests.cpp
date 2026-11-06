/**
 * @file ConstantsTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref flcn::CVec2 constants (@ref flcn::CVec2::ONE, @ref flcn::CVec2::ZERO, etc).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CVec2TestSetup.h"



/**
 * @addtogroup T_FALCON_CVec2_Const
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref CVec2 constants.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class CVec2ConstantsTests: public testing::Test
    {
    protected:
        T _one  = T(1);
        T _zero = T(0);
    };
    TYPED_TEST_SUITE(CVec2ConstantsTests, SupportedSignedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that @ref CVec2::one() returns a one vector at compile time.
        static_assert(flcn::CVec2<int>::one().x() == 1);
        static_assert(flcn::CVec2<int>::one().y() == 1);

        /// @test Verify that @ref CVec2::zero() returns a zero vector at compile time.
        static_assert(flcn::CVec2<int>::zero().x() == 0);
        static_assert(flcn::CVec2<int>::zero().y() == 0);

        /// @test Verify that @ref CVec2::inf() returns a infinity vector at compile time.
        static_assert(flcn::isinf(flcn::CVec2<float>::inf().x()));
        static_assert(flcn::isinf(flcn::CVec2<float>::inf().y()));

        /// @test Verify that @ref CVec2::infNeg() returns a negative infinity vector at compile time.
        static_assert(flcn::isinf(flcn::CVec2<float>::infNeg().x()));
        static_assert(flcn::isinf(flcn::CVec2<float>::infNeg().y()));

        /// @test Verify that @ref CVec2::qnan() returns a qnan vector at compile time.
        static_assert(flcn::isnan(flcn::CVec2<float>::qnan().x()));
        static_assert(flcn::isnan(flcn::CVec2<float>::qnan().y()));

        /// @test Verify that @ref CVec2::left() returns a valid vector at compile time.
        static_assert(flcn::CVec2<int>::left().x() == -1);
        static_assert(flcn::CVec2<int>::left().y() == 0);

        /// @test Verify that @ref CVec2::right() returns a valid vector at compile time.
        static_assert(flcn::CVec2<int>::right().x() == 1);
        static_assert(flcn::CVec2<int>::right().y() == 0);

        /// @test Verify that @ref CVec2::up() returns a valid vector at compile time.
        static_assert(flcn::CVec2<int>::up().x() == 0);
        static_assert(flcn::CVec2<int>::up().y() == 1);

        /// @test Verify that @ref CVec2::down() returns a valid vector at compile time.
        static_assert(flcn::CVec2<int>::down().x() == 0);
        static_assert(flcn::CVec2<int>::down().y() == -1);

    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(CVec2ConstantsTests, ONE_ReturnsVectorWithUnitComponents)
{
    const auto one = TypeParam(1);
    EXPECT_VEC_CONTAINS(flcn::CVec2<TypeParam>::one(), one, one);
}


TYPED_TEST(CVec2ConstantsTests, ZERO_ReturnsVectorWithZeroComponents) { EXPECT_VEC_ZERO(flcn::CVec2<TypeParam>::zero()); }


TEST(CVec2ConstantsTests, INF_Float_ReturnsFloatVectorWithInfiniteComponents)
{
    const auto inf = flcn::CVec2<float>::inf();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC2_POS_INF(inf)
}


TEST(CVec2ConstantsTests, INF_Double_ReturnsDoubleVectorWithInfinityComponents)
{
    const auto inf = flcn::CVec2<double>::inf();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC2_POS_INF(inf)
}


TEST(CVec2ConstantsTests, INFNEG_Float_ReturnsFloatVectorWithNegativeInfinityComponents)
{
    const auto inf = flcn::CVec2<float>::infNeg();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, float>);
    EXPECT_VEC2_NEG_INF(inf)
}


TEST(CVec2ConstantsTests, INFNEG_Double_ReturnsDoubleVectorWithNegativeInfinityComponents)
{
    const auto inf = flcn::CVec2<double>::infNeg();
    static_assert(std::is_same_v<typename decltype(inf)::value_type, double>);
    EXPECT_VEC2_NEG_INF(inf)
}


TEST(CVec2ConstantsTests, Float_QNAN_ReturnsFloatVectorWithNaNComponents)
{
    const auto nan = flcn::CVec2<float>::qnan();
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
}


TEST(CVec2ConstantsTests, Double_QNAN_ReturnsDoubleVectorWithNaNComponents)
{
    const auto nan = flcn::CVec2<double>::qnan();
    EXPECT_TRUE(std::isnan(nan.x()));
    EXPECT_TRUE(std::isnan(nan.y()));
}


TYPED_TEST(CVec2ConstantsTests, RIGHT_ReturnsUnitVectorWithOnlyPositiveXComponent)
{
    const auto x = flcn::CVec2<TypeParam>::right();
    EXPECT_VEC_CONTAINS(x, this->_one, this->_zero);
}


TYPED_TEST(CVec2ConstantsTests, LEFT_ReturnsUnitVectorWithOnlyNegativeXComponent)
{
    const auto x = flcn::CVec2<TypeParam>::left();
    EXPECT_VEC_CONTAINS(x, TypeParam(-this->_one), this->_zero);
}


TYPED_TEST(CVec2ConstantsTests, UP_ReturnsUnitVectorWithOnlyPositiveYComponent)
{
    const auto x = flcn::CVec2<TypeParam>::up();
    EXPECT_VEC_CONTAINS(x, this->_zero, this->_one);
}


TYPED_TEST(CVec2ConstantsTests, DOWN_ReturnsUnitVectorWithOnlyNegativeYComponent)
{
    const auto x = flcn::CVec2<TypeParam>::down();
    EXPECT_VEC_CONTAINS(x, this->_zero, TypeParam(-this->_one));
}

/** @} */
