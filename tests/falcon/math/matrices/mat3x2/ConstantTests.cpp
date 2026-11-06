/**
 * @file ConstantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 20, 2026
 *
 * @brief Verify @ref flcn::Mat3x2 constants (@ref flcn::Mat3x2::one, @ref flcn::Mat3x2::zero).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3x2TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat3x2_Constant
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat3x2 Constants.
     */
    template <typename>
    class Mat3x2ConstantsTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Mat3x2ConstantsTests, SupportedArithmeticTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that Mat3::one() returns an one matrix at compile time.
        static_assert(flcn::Mat3x2<int>::one()(0, 0) == 1);
        static_assert(flcn::Mat3x2<int>::one()(0, 1) == 1);

        static_assert(flcn::Mat3x2<int>::one()(1, 0) == 1);
        static_assert(flcn::Mat3x2<int>::one()(1, 1) == 1);

        static_assert(flcn::Mat3x2<int>::one()(2, 0) == 1);
        static_assert(flcn::Mat3x2<int>::one()(2, 1) == 1);


        /// @test Verify that Mat3::zero() returns a zero matrix at compile time.
        static_assert(flcn::Mat3x2<int>::zero()(0, 0) == 0);
        static_assert(flcn::Mat3x2<int>::zero()(0, 1) == 0);

        static_assert(flcn::Mat3x2<int>::zero()(1, 0) == 0);
        static_assert(flcn::Mat3x2<int>::zero()(1, 1) == 0);

        static_assert(flcn::Mat3x2<int>::zero()(2, 0) == 0);
        static_assert(flcn::Mat3x2<int>::zero()(2, 1) == 0);

    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat3x2ConstantsTests, One_ReturnsOneMatrix) { EXPECT_MAT_ONE(flcn::Mat3x2<TypeParam>::one()); }


TYPED_TEST(Mat3x2ConstantsTests, Zero_ReturnsZeroMatrix) { EXPECT_MAT_ZERO(flcn::Mat3x2<TypeParam>::zero()); }

/** @} */
