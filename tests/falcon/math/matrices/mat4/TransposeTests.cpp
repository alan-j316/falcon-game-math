/**
 * @file TransposeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 07, 2026
 *
 * @brief Verify @ref flcn::Mat4 transpose logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat4x4_Transpose
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4 Transpose.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat4TransposeTests: public ::testing::Test
    {
    protected:
        flcn::Mat4<T> _matrix, _expectedTranspose;

        void SetUp() override
        {
            _matrix            = { { T(1), T(2), T(3), T(4) },
                                   { T(5), T(6), T(7), T(8) },
                                   { T(9), T(10), T(11), T(12) },
                                   { T(13), T(14), T(15), T(16) } };
            _expectedTranspose = { { T(1), T(5), T(9), T(13) },
                                   { T(2), T(6), T(10), T(14) },
                                   { T(3), T(7), T(11), T(15) },
                                   { T(4), T(8), T(12), T(16) } };
        }
    };
    TYPED_TEST_SUITE(Mat4TransposeTests, SupportedTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat4 MAT(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);


        /** @test Verify that matrix transpose returns a valid matrix at compile time. */
        constexpr flcn::Mat4 TRANSPOSE_MAT = MAT.transpose();
        static_assert(TRANSPOSE_MAT(0, 0) == 1);
        static_assert(TRANSPOSE_MAT(0, 1) == 5);
        static_assert(TRANSPOSE_MAT(0, 2) == 9);
        static_assert(TRANSPOSE_MAT(0, 3) == 13);

        static_assert(TRANSPOSE_MAT(1, 0) == 2);
        static_assert(TRANSPOSE_MAT(1, 1) == 6);
        static_assert(TRANSPOSE_MAT(1, 2) == 10);
        static_assert(TRANSPOSE_MAT(1, 3) == 14);

        static_assert(TRANSPOSE_MAT(2, 0) == 3);
        static_assert(TRANSPOSE_MAT(2, 1) == 7);
        static_assert(TRANSPOSE_MAT(2, 2) == 11);
        static_assert(TRANSPOSE_MAT(2, 3) == 15);

        static_assert(TRANSPOSE_MAT(3, 0) == 4);
        static_assert(TRANSPOSE_MAT(3, 1) == 8);
        static_assert(TRANSPOSE_MAT(3, 2) == 12);
        static_assert(TRANSPOSE_MAT(3, 3) == 16);


        /** @test Verify that matrix transpose (static wrapper) returns a valid matrix at compile time. */
        constexpr flcn::Mat4 TRANSPOSE_MAT_S = flcn::Mat4<int>::transpose(MAT);
        static_assert(TRANSPOSE_MAT_S(0, 0) == 1);
        static_assert(TRANSPOSE_MAT_S(0, 1) == 5);
        static_assert(TRANSPOSE_MAT_S(0, 2) == 9);
        static_assert(TRANSPOSE_MAT_S(0, 3) == 13);

        static_assert(TRANSPOSE_MAT_S(1, 0) == 2);
        static_assert(TRANSPOSE_MAT_S(1, 1) == 6);
        static_assert(TRANSPOSE_MAT_S(1, 2) == 10);
        static_assert(TRANSPOSE_MAT_S(1, 3) == 14);

        static_assert(TRANSPOSE_MAT_S(2, 0) == 3);
        static_assert(TRANSPOSE_MAT_S(2, 1) == 7);
        static_assert(TRANSPOSE_MAT_S(2, 2) == 11);
        static_assert(TRANSPOSE_MAT_S(2, 3) == 15);

        static_assert(TRANSPOSE_MAT_S(3, 0) == 4);
        static_assert(TRANSPOSE_MAT_S(3, 1) == 8);
        static_assert(TRANSPOSE_MAT_S(3, 2) == 12);
        static_assert(TRANSPOSE_MAT_S(3, 3) == 16);

    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat4TransposeTests, ReturnsMatrixWithExchangedRowsAndColumnElements)
{ EXPECT_MAT_EQ(this->_expectedTranspose, this->_matrix.transpose()); }


TYPED_TEST(Mat4TransposeTests, StaticWrapper_ReturnsMatrixWithExchangedRowsAndColumnElements)
{ EXPECT_MAT_EQ(this->_expectedTranspose, flcn::Mat4<TypeParam>::transpose(this->_matrix)); }

/** @} */
