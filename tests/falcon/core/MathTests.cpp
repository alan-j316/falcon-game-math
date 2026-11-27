/**
 * @file MathTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 28, 2026
 *
 * @brief Verify @ref flcn::utils function's logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "CommonSetup.h"

#include <falcon/core/Constants.h>
#include <falcon/core/Math.h>


/**
 * @addtogroup TFalcon_Core_Math
 * @{
 */

namespace
{
    using namespace testutils;

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::diffAbs.
     */
    template <typename>
    class FalconDiffAbsTests: public testing::Test
    {};
    TYPED_TEST_SUITE(FalconDiffAbsTests, SupportedArithmeticTypes);



    template <typename T>
    struct CompareEqTestParams
    {
        T a, b;
        bool expected;
    };

    /**
     * @brief Test fixture for validating @ref flcn::compareEq across different types.
     */
    template <typename T>
    class CompareEqTests: public testing::Test
    {
    protected:
        T _equalValueA, _equalValueB, _unequalValue;

        void SetUp() override
        {
            _equalValueA  = T(1.01238402134);
            _equalValueB  = T(1.01238402134);
            _unequalValue = T(5.2139032);
        }
    };
    TYPED_TEST_SUITE(CompareEqTests, SupportedArithmeticTypes);

    /**
     * @brief Test fixture for @ref flcn::abs(signed numbers).
     *
     * @tparam T The scalar type(int, float, double...) of the values.
     */
    template <typename T>
    class AbsTestUnsigned: public testing::Test
    {
    protected:
        T _value, _expectedAbsValue;

        void SetUp() override
        {
            _value            = T(-5.2891283123432);
            _expectedAbsValue = T(5.2891283123432);
        }
    };
    TYPED_TEST_SUITE(AbsTestUnsigned, SupportedSignedArithmeticTypes);


    /**
     * @brief Test fixture for @ref flcn::abs(unsigned numbers).
     *
     * @tparam T The scalar type(int, float, double...) of the values.
     */
    template <typename T>
    class AbsTest: public testing::Test
    {
    protected:
        T _value, _expectedAbsValue;

        void SetUp() override
        {
            _value            = T(5.2891283123432);
            _expectedAbsValue = T(5.2891283123432);
        }
    };
    TYPED_TEST_SUITE(AbsTest, SupportedArithmeticTypes);


    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        /** @test Verify that @ref flcn::diffAbs returns the correct value at compile time. */
        static_assert(flcn::diffAbs(1000, 100) == 900);
        static_assert(flcn::diffAbs(100, 1000) == 900);


        /// @test Verify that @ref flcn::compareEq returns the correct boolean at compile time. */
        static_assert(flcn::compareEq(9.1111, 9.1112) == false);
        static_assert(flcn::compareEq(9.1112, 9.1111) == false);
        static_assert(flcn::compareEq(9.1112, 9.1112) == true);

        /** @test Verify that @ref flcn::abs return absolute value at compile time. */
        static_assert(flcn::abs(-3.53) == 3.53);
        static_assert(flcn::abs(static_cast<unsigned int>(12)) == 12);
        static_assert(flcn::abs(static_cast<char>(-3.5312893)) == 3);
        static_assert(flcn::abs(-0.0000000000053) == 0.0000000000053);
        static_assert(flcn::abs(-3) == 3);
        static_assert(flcn::abs(flcn::constants::NaN_D) != flcn::constants::NaN_D);


        /** @test Verify that @ref flcn::isnan is correct boolean at compile time. */
        static_assert(flcn::isNaN(-3.53) == false);
        static_assert(flcn::isNaN(flcn::constants::NaN) == true);
        static_assert(flcn::isNaN(flcn::constants::NaN_D) == true);


        /** @test Verify that @ref flcn::isinf returns correct boolean at compile time. */
        static_assert(flcn::isInf(-3.53) == false);
        static_assert(flcn::isInf(3.53) == false);
        static_assert(flcn::isInf(flcn::constants::INFINITY_F) == true);
        static_assert(flcn::isInf(-flcn::constants::INFINITY_F) == true);

        /// TODO: Add sqrt tests
        //     static_assert(flcn::utils::sqrt(4) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        //     static_assert(flcn::utils::sqrt(2.0) - 1.41421356237 <= flcn::Config::DOUBLE_EPSILON);
        //     static_assert(flcn::utils::sqrt(4) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        //     static_assert(flcn::utils::sqrt(4) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        //     static_assert(flcn::utils::sqrt(4) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        //     static_assert(flcn::utils::sqrt(4) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        //     static_assert(flcn::utils::sqrt(4) - 2.0f <= flcn::Config::FLOAT_EPSILON);
    } // namespace static_tests


} // namespace




/**************************************
 *              DIFF ABS              *
 **************************************/

TYPED_TEST(FalconDiffAbsTests, ReturnsAbsoluteValueWithUnderflow_WhenAGreaterThanB)
{
    const auto a      = TypeParam(12);
    const auto b      = TypeParam(7);
    const auto result = TypeParam(5);
    testutils::EXPECT_MAG_EQ(result, flcn::diffAbs(a, b));
}


TYPED_TEST(FalconDiffAbsTests, ReturnsAbsoluteValueWithUnderflow_WhenBGreaterThanA)
{
    const auto a      = TypeParam(7);
    const auto b      = TypeParam(12);
    const auto result = TypeParam(5);
    testutils::EXPECT_MAG_EQ(result, flcn::diffAbs(a, b));
}


TYPED_TEST(FalconDiffAbsTests, ReturnsAbsoluteValueWithUnderflow_WhenAEqualsB)
{
    const auto a      = TypeParam(12);
    const auto b      = TypeParam(12);
    const auto result = TypeParam(0);
    testutils::EXPECT_MAG_EQ(result, flcn::diffAbs(a, b));
}



/**************************************
 *             COMPARE EQ             *
 **************************************/

TYPED_TEST(CompareEqTests, EqualValues_ReturnTrue)
{ EXPECT_TRUE(flcn::compareEq(this->_equalValueA, this->_equalValueB)); }


TYPED_TEST(CompareEqTests, UnequalValues_ReturnFalse)
{ EXPECT_FALSE(flcn::compareEq(this->_equalValueA, this->_unequalValue)); }


/// @test Verify that compareEq works with relative precision when compared IEEE 754 floating point types.
TEST(CompareEqTests, MaintainsARelativePrecision)
{ EXPECT_FALSE(flcn::compareEq(316.810892301231, 316.810892301222)); }



/**************************************
 *              ABS TEST              *
 **************************************/

TYPED_TEST(AbsTestUnsigned, UnsignedNumbers_ReturnsAbsoluteValue)
{ testutils::EXPECT_MAG_EQ(this->_expectedAbsValue, flcn::abs(this->_value)); }


TYPED_TEST(AbsTest, SignedNumbers_ReturnsAbsoluteValue)
{ testutils::EXPECT_MAG_EQ(this->_expectedAbsValue, flcn::abs(this->_value)); }



/**************************************
 *            ISNAN TESTS             *
 **************************************/

/** @test Verify thatcheck for IEEE 754 NaN using @ref flcn::isnan returns true for a standard quiet NaN. */
TEST(IsNaNTests, NaNReturnsTrue) { EXPECT_TRUE(flcn::isNaN(flcn::constants::NaN)); }


/** @test Verify thatcheck for IEEE 754 NaN using @ref flcn::isnan returns false for a non-NaN. */
TEST(IsNaNTests, NumberReturnsFalse) { EXPECT_FALSE(flcn::isNaN(3.16f)); }



/**************************************
 *            IS INF TESTS            *
 **************************************/

/** @test Verify thatcheck for IEEE 754 infinity using @ref flcn::isinf returns true for a positive infinity. */
TEST(IsInfTests, PositiveInfinityReturnsTrue) { EXPECT_TRUE(flcn::isInf(flcn::constants::INFINITY_F)); }


/** @test Verify thatcheck for IEEE 754 infinity using @ref flcn::isinf returns true for a negative infinity. */
TEST(IsInfTests, NegativeInfinityReturnsTrue) { EXPECT_TRUE(flcn::isInf(-flcn::constants::INFINITY_F)); }


/** @test Verify thatcheck for IEEE 754 infinity using @ref flcn::isinf returns true for a non-infinity value. */
TEST(IsInfTests, NonInfiniteNumberReturnsFalse) { EXPECT_FALSE(flcn::isInf(3.16f)); }


/** @} */
