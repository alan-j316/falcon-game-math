/**
 * @file ConstantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref flcn::Mat4x3 constants (@ref flcn::Mat4x3::one, @ref flcn::Mat4x3::zero).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4x3TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat4x3_Constant
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4x3 Constants.
     */
    template <typename>
    class Mat4x3ConstantsTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Mat4x3ConstantsTests, SupportedArithmeticTypes);




    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that Mat4::one() returns an one matrix at compile time.
        static_assert(flcn::Mat4x3<int>::one()(0, 0) == 1);
        static_assert(flcn::Mat4x3<int>::one()(0, 1) == 1);
        static_assert(flcn::Mat4x3<int>::one()(0, 2) == 1);

        static_assert(flcn::Mat4x3<int>::one()(1, 0) == 1);
        static_assert(flcn::Mat4x3<int>::one()(1, 1) == 1);
        static_assert(flcn::Mat4x3<int>::one()(1, 2) == 1);

        static_assert(flcn::Mat4x3<int>::one()(2, 0) == 1);
        static_assert(flcn::Mat4x3<int>::one()(2, 1) == 1);
        static_assert(flcn::Mat4x3<int>::one()(2, 2) == 1);

        static_assert(flcn::Mat4x3<int>::one()(3, 0) == 1);
        static_assert(flcn::Mat4x3<int>::one()(3, 1) == 1);
        static_assert(flcn::Mat4x3<int>::one()(3, 2) == 1);


        /// @test Verify that Mat4::zero() returns a zero matrix at compile time.
        static_assert(flcn::Mat4x3<int>::zero()(0, 0) == 0);
        static_assert(flcn::Mat4x3<int>::zero()(0, 1) == 0);
        static_assert(flcn::Mat4x3<int>::zero()(0, 2) == 0);

        static_assert(flcn::Mat4x3<int>::zero()(1, 0) == 0);
        static_assert(flcn::Mat4x3<int>::zero()(1, 1) == 0);
        static_assert(flcn::Mat4x3<int>::zero()(1, 2) == 0);

        static_assert(flcn::Mat4x3<int>::zero()(2, 0) == 0);
        static_assert(flcn::Mat4x3<int>::zero()(2, 1) == 0);
        static_assert(flcn::Mat4x3<int>::zero()(2, 2) == 0);

        static_assert(flcn::Mat4x3<int>::zero()(3, 0) == 0);
        static_assert(flcn::Mat4x3<int>::zero()(3, 1) == 0);
        static_assert(flcn::Mat4x3<int>::zero()(3, 2) == 0);

    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat4x3ConstantsTests, One_ReturnsOneMatrix) { EXPECT_MAT_ONE(flcn::Mat4x3<TypeParam>::one()); }


TYPED_TEST(Mat4x3ConstantsTests, Zero_ReturnsZeroMatrix) { EXPECT_MAT_ZERO(flcn::Mat4x3<TypeParam>::zero()); }

/** @} */
