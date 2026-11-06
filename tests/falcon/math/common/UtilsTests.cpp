/**
 * @file UtilsTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 28, 2026
 *
 * @brief Verify @ref flcn::utils function's logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "CommonSetup.h"
#include "utils/VectorUtils.h"

#include <falcon/math/common/Utils.h>


/**
 * @addtogroup T_FALCON_Utils
 * @{
 */

namespace
{

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::utils::diffAbs.
     */
    template <typename>
    class FALCONDiffAbsTests: public testing::Test
    {};
    TYPED_TEST_SUITE(FALCONDiffAbsTests, SupportedArithmeticTypes);



    template <typename T>
    struct CompareEqTestParams
    {
        T a, b;
        bool expected;
    };

    /**
     * @brief Test fixture for validating @ref flcn::utils::compareEq across different types.
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




    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        /** @test Verify that @ref flcn::utils::diffAbs returns the correct value at compile time. */
        static_assert(flcn::utils::diffAbs(1000, 100) == 900);
        static_assert(flcn::utils::diffAbs(100, 1000) == 900);


        /// @test Verify that @ref flcn::utils::compareEq returns the correct boolean at compile time. */
        static_assert(flcn::utils::compareEq(9.1111, 9.1112) == false);
        static_assert(flcn::utils::compareEq(9.1112, 9.1111) == false);
        static_assert(flcn::utils::compareEq(9.1112, 9.1112) == true);

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

TYPED_TEST(FALCONDiffAbsTests, ReturnsAbsoluteValueWithUnderflow_WhenAGreaterThanB)
{
    const auto a      = TypeParam(12);
    const auto b      = TypeParam(7);
    const auto result = TypeParam(5);
    testutils::EXPECT_MAG_EQ(result, flcn::utils::diffAbs(a, b));
}


TYPED_TEST(FALCONDiffAbsTests, ReturnsAbsoluteValueWithUnderflow_WhenBGreaterThanA)
{
    const auto a      = TypeParam(7);
    const auto b      = TypeParam(12);
    const auto result = TypeParam(5);
    testutils::EXPECT_MAG_EQ(result, flcn::utils::diffAbs(a, b));
}


TYPED_TEST(FALCONDiffAbsTests, ReturnsAbsoluteValueWithUnderflow_WhenAEqualsB)
{
    const auto a      = TypeParam(12);
    const auto b      = TypeParam(12);
    const auto result = TypeParam(0);
    testutils::EXPECT_MAG_EQ(result, flcn::utils::diffAbs(a, b));
}



/**************************************
 *             COMPARE EQ             *
 **************************************/

TYPED_TEST(CompareEqTests, EqualValues_ReturnTrue)
{ EXPECT_TRUE(flcn::utils::compareEq(this->_equalValueA, this->_equalValueB)); }


TYPED_TEST(CompareEqTests, UnequalValues_ReturnFalse)
{ EXPECT_FALSE(flcn::utils::compareEq(this->_equalValueA, this->_unequalValue)); }


/// @test Verify that compareEq works with relative precision when compared IEEE 754 floating point types.
TEST(CompareEqTests, MaintainsARelativePrecision)
{ EXPECT_FALSE(flcn::utils::compareEq(316.810892301231, 316.810892301222)); }

/** @} */
