/**
 * @file TransposeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 25, 2026
 *
 * @brief Verify @ref flcn::Mat2x4 transpose logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2x4TestSetup.h"

#include <falcon/math/matrices/Mat4x2.h>


/**
 * @addtogroup T_FALCON_Mat2x4_Transpose
 * @{
 */

namespace
{
    /**************************************
     *               SETUP                *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2x4 matrix transposition.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat2x4TransposeTests: public testing::Test
    {
    protected:
        flcn::Mat2x4<T> _matrix;
        flcn::Mat4x2<T> _expectedTranspose;

        void SetUp() override
        {
            _matrix            = { flcn::CVec2{ T(1), T(5) }, flcn::CVec2{ T(2), T(6) }, flcn::CVec2{ T(3), T(7) },
                                   flcn::CVec2{ T(4), T(8) } };
            _expectedTranspose = { flcn::Vec4{ T(1), T(2), T(3), T(4) }, flcn::Vec4{ T(5), T(6), T(7), T(8) } };
        }
    };
    TYPED_TEST_SUITE(Mat2x4TransposeTests, SupportedTypes);




    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat2x4 MAT(1, 2, 3, 4, 5, 6, 7, 8);

        // NOTE: The matrix takes elements in row, col order
        //       but when compared with Vec4, we are taking col, row order.
        //       That's why Vec4(1, 2, 3, 4) is the transpose and not Vec4(1, 5, 2, 6)

        /// @test Verify matrix transpose is returns a 4x2 matrix with swapped rows and
        ///       columns at compile time.
        constexpr auto TRANSPOSE_MAT = MAT.transpose();
        static_assert(TRANSPOSE_MAT[0] == flcn::Vec4(1, 2, 3, 4));
        static_assert(TRANSPOSE_MAT[1] == flcn::Vec4(5, 6, 7, 8));

        /// @test Verify matrix transpose using static variant returns a 4x2 matrix with
        ///       swapped rows and columns at compile time.
        constexpr auto TRANSPOSE_MAT_STATIC = flcn::Mat2x4<int>::transpose(MAT);
        static_assert(TRANSPOSE_MAT_STATIC[0] == flcn::Vec4(1, 2, 3, 4));
        static_assert(TRANSPOSE_MAT_STATIC[1] == flcn::Vec4(5, 6, 7, 8));

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat2x4TransposeTests, Returns4x2MatrixWithRowAndColumnElementsExchanged)
{ EXPECT_MAT_EQ(this->_expectedTranspose, this->_matrix.transpose()); }


TYPED_TEST(Mat2x4TransposeTests, StaticWrapper_Returns4x2MatrixWithRowAndColumnElementsExchanged)
{ EXPECT_MAT_EQ(this->_expectedTranspose, flcn::Mat2x4<TypeParam>::transpose(this->_matrix)); }

/** @} */
