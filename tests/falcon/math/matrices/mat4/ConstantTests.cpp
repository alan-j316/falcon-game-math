/**
 * @file ConstantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 01, 2026
 *
 * @brief Verify @ref flcn::Mat4 constants (@ref flcn::Mat4::identity, @ref flcn::Mat4::zero).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat4x4_Constant
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4 Constants.
     */
    template <typename>
    class Mat4ConstantsTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Mat4ConstantsTests, SupportedArithmeticTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that Mat4::identity() returns an identity matrix at compile time.
        static_assert(flcn::Mat4<int>::identity()(0, 0) == 1);
        static_assert(flcn::Mat4<int>::identity()(0, 1) == 0);
        static_assert(flcn::Mat4<int>::identity()(0, 2) == 0);
        static_assert(flcn::Mat4<int>::identity()(0, 3) == 0);

        static_assert(flcn::Mat4<int>::identity()(1, 0) == 0);
        static_assert(flcn::Mat4<int>::identity()(1, 1) == 1);
        static_assert(flcn::Mat4<int>::identity()(1, 2) == 0);
        static_assert(flcn::Mat4<int>::identity()(1, 3) == 0);

        static_assert(flcn::Mat4<int>::identity()(2, 0) == 0);
        static_assert(flcn::Mat4<int>::identity()(2, 1) == 0);
        static_assert(flcn::Mat4<int>::identity()(2, 2) == 1);
        static_assert(flcn::Mat4<int>::identity()(2, 3) == 0);

        static_assert(flcn::Mat4<int>::identity()(3, 0) == 0);
        static_assert(flcn::Mat4<int>::identity()(3, 1) == 0);
        static_assert(flcn::Mat4<int>::identity()(3, 2) == 0);
        static_assert(flcn::Mat4<int>::identity()(3, 3) == 1);


        /// @test Verify that Mat4::zero() returns a zero matrix at compile time.
        static_assert(flcn::Mat4<int>::zero()(0, 0) == 0);
        static_assert(flcn::Mat4<int>::zero()(0, 1) == 0);
        static_assert(flcn::Mat4<int>::zero()(0, 2) == 0);
        static_assert(flcn::Mat4<int>::zero()(0, 3) == 0);

        static_assert(flcn::Mat4<int>::zero()(1, 0) == 0);
        static_assert(flcn::Mat4<int>::zero()(1, 1) == 0);
        static_assert(flcn::Mat4<int>::zero()(1, 2) == 0);
        static_assert(flcn::Mat4<int>::zero()(1, 3) == 0);

        static_assert(flcn::Mat4<int>::zero()(2, 0) == 0);
        static_assert(flcn::Mat4<int>::zero()(2, 1) == 0);
        static_assert(flcn::Mat4<int>::zero()(2, 2) == 0);
        static_assert(flcn::Mat4<int>::zero()(2, 3) == 0);

        static_assert(flcn::Mat4<int>::zero()(3, 0) == 0);
        static_assert(flcn::Mat4<int>::zero()(3, 1) == 0);
        static_assert(flcn::Mat4<int>::zero()(3, 2) == 0);
        static_assert(flcn::Mat4<int>::zero()(3, 3) == 0);

    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat4ConstantsTests, Identity_ReturnsIdentityMatrix)
{ EXPECT_MAT_IDENTITY(flcn::Mat4<TypeParam>::identity()); }


TYPED_TEST(Mat4ConstantsTests, Zero_ReturnsZeroMatrix) { EXPECT_MAT_ZERO(flcn::Mat4<TypeParam>::zero()); }

/** @} */
