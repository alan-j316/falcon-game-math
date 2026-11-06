/**
 * @file TransposeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 28, 2026
 *
 * @brief Verify @ref flcn::Mat3 transpose logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat3x3_Transpose
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat3 Transpose.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat3TransposeTests: public testing::Test
    {
    protected:
        flcn::Mat3<T> _matrix, _expectedTranspose;

        void SetUp() override
        {
            _matrix            = { { T(1), T(2), T(3) }, { T(4), T(5), T(6) }, { T(7), T(8), T(9) } };
            _expectedTranspose = { { T(1), T(4), T(7) }, { T(2), T(5), T(8) }, { T(3), T(6), T(9) } };
        }
    };
    TYPED_TEST_SUITE(Mat3TransposeTests, SupportedTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat3 MAT(1, 2, 3, 4, 5, 6, 7, 8, 9);

        /** @test Verify that matrix transpose returns a valid matrix at compile time. */
        constexpr flcn::Mat3 TRANSPOSE_MAT = MAT.transpose();
        static_assert(TRANSPOSE_MAT(0, 0) == 1);
        static_assert(TRANSPOSE_MAT(0, 1) == 4);
        static_assert(TRANSPOSE_MAT(0, 2) == 7);

        static_assert(TRANSPOSE_MAT(1, 0) == 2);
        static_assert(TRANSPOSE_MAT(1, 1) == 5);
        static_assert(TRANSPOSE_MAT(1, 2) == 8);

        static_assert(TRANSPOSE_MAT(2, 0) == 3);
        static_assert(TRANSPOSE_MAT(2, 1) == 6);
        static_assert(TRANSPOSE_MAT(2, 2) == 9);


        /** @test Verify that matrix transpose (static wrapper) returns a valid matrix at compile time. */
        constexpr flcn::Mat3 TRANSPOSE_MAT_S = flcn::Mat3<int>::transpose(MAT);
        static_assert(TRANSPOSE_MAT_S(0, 0) == 1);
        static_assert(TRANSPOSE_MAT_S(0, 1) == 4);
        static_assert(TRANSPOSE_MAT_S(0, 2) == 7);

        static_assert(TRANSPOSE_MAT_S(1, 0) == 2);
        static_assert(TRANSPOSE_MAT_S(1, 1) == 5);
        static_assert(TRANSPOSE_MAT_S(1, 2) == 8);

        static_assert(TRANSPOSE_MAT_S(2, 0) == 3);
        static_assert(TRANSPOSE_MAT_S(2, 1) == 6);
        static_assert(TRANSPOSE_MAT_S(2, 2) == 9);

    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat3TransposeTests, ReturnsMatrixWithExchangedRowsAndColumnElements)
{ EXPECT_MAT_EQ(this->_expectedTranspose, this->_matrix.transpose()); }


TYPED_TEST(Mat3TransposeTests, StaticWrapper_ReturnsMatrixWithExchangedRowsAndColumnElements)
{ EXPECT_MAT_EQ(this->_expectedTranspose, flcn::Mat3<TypeParam>::transpose(this->_matrix)); }

/** @} */
