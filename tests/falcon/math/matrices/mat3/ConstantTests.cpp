/**
 * @file ConstantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 23, 2026
 *
 * @brief Verify @ref flcn::Mat3 constants (@ref flcn::Mat3::identity, @ref flcn::Mat3::zero).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat3x3_Constant
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat3 Constants.
     */
    template <typename>
    class Mat3ConstantsTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Mat3ConstantsTests, SupportedArithmeticTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that Mat3::identity() returns an identity matrix at compile time.
        static_assert(flcn::Mat3<int>::identity()(0, 0) == 1);
        static_assert(flcn::Mat3<int>::identity()(0, 1) == 0);
        static_assert(flcn::Mat3<int>::identity()(0, 2) == 0);

        static_assert(flcn::Mat3<int>::identity()(1, 0) == 0);
        static_assert(flcn::Mat3<int>::identity()(1, 1) == 1);
        static_assert(flcn::Mat3<int>::identity()(1, 2) == 0);

        static_assert(flcn::Mat3<int>::identity()(2, 0) == 0);
        static_assert(flcn::Mat3<int>::identity()(2, 1) == 0);
        static_assert(flcn::Mat3<int>::identity()(2, 2) == 1);


        /// @test Verify that Mat3::zero() returns a zero matrix at compile time.
        static_assert(flcn::Mat3<int>::zero()(0, 0) == 0);
        static_assert(flcn::Mat3<int>::zero()(0, 1) == 0);
        static_assert(flcn::Mat3<int>::zero()(0, 2) == 0);

        static_assert(flcn::Mat3<int>::zero()(1, 0) == 0);
        static_assert(flcn::Mat3<int>::zero()(1, 1) == 0);
        static_assert(flcn::Mat3<int>::zero()(1, 2) == 0);

        static_assert(flcn::Mat3<int>::zero()(2, 0) == 0);
        static_assert(flcn::Mat3<int>::zero()(2, 1) == 0);
        static_assert(flcn::Mat3<int>::zero()(2, 2) == 0);

    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat3ConstantsTests, Identity_ReturnsIdentityMatrix)
{ EXPECT_MAT_IDENTITY(flcn::Mat3<TypeParam>::identity()); }


TYPED_TEST(Mat3ConstantsTests, Zero_ReturnsZeroMatrix) { EXPECT_MAT_ZERO(flcn::Mat3<TypeParam>::zero()); }

/** @} */
