/**
 * @file TransposeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 27, 2026
 *
 * @brief Verify @ref flcn::Mat4x2 transpose logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4x2TestSetup.h"

#include <falcon/math/matrices/Mat2x4.h>


/**
 * @addtogroup T_FALCON_Mat4x2_Transpose
 * @{
 */

namespace
{
    /**************************************
     *               SETUP                *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4x2 matrix transposition.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat4x2TransposeTests: public testing::Test
    {
    protected:
        flcn::Mat4x2<T> _matrix;
        flcn::Mat2x4<T> _expectedTranspose;

        void SetUp() override
        {
            _matrix            = { flcn::Vec4{ T(1), T(2), T(3), T(4) }, flcn::Vec4{ T(5), T(6), T(7), T(8) } };
            _expectedTranspose = { flcn::CVec2{ T(1), T(5) }, flcn::CVec2{ T(2), T(6) }, flcn::CVec2{ T(3), T(7) },
                                   flcn::CVec2{ T(4), T(8) } };
        }
    };
    TYPED_TEST_SUITE(Mat4x2TransposeTests, SupportedTypes);




    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat4x2 MAT(1, 2, 3, 4, 5, 6, 7, 8);

        // NOTE: The matrix takes elements in row, col order
        //       but when compared with CVec2, we are taking col, row order.
        //       That's why CVec2(1, 2) is the transpose and not CVec2(1, 3)

        /// @test Verify matrix transpose is returns a 2x4 matrix with swapped rows and
        ///       columns at compile time.
        constexpr auto TRANSPOSE_MAT = MAT.transpose();
        static_assert(TRANSPOSE_MAT[0] == flcn::CVec2(1, 2));
        static_assert(TRANSPOSE_MAT[1] == flcn::CVec2(3, 4));
        static_assert(TRANSPOSE_MAT[2] == flcn::CVec2(5, 6));
        static_assert(TRANSPOSE_MAT[3] == flcn::CVec2(7, 8));

        /// @test Verify matrix transpose using static variant returns a 2x4 matrix with
        ///       swapped rows and columns at compile time.
        constexpr auto TRANSPOSE_MAT_STATIC = flcn::Mat4x2<int>::transpose(MAT);
        static_assert(TRANSPOSE_MAT_STATIC[0] == flcn::CVec2(1, 2));
        static_assert(TRANSPOSE_MAT_STATIC[1] == flcn::CVec2(3, 4));
        static_assert(TRANSPOSE_MAT_STATIC[2] == flcn::CVec2(5, 6));
        static_assert(TRANSPOSE_MAT_STATIC[3] == flcn::CVec2(7, 8));

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat4x2TransposeTests, Returns2x4MatrixWithRowAndColumnElementsExchanged)
{ EXPECT_MAT_EQ(this->_expectedTranspose, this->_matrix.transpose()); }


TYPED_TEST(Mat4x2TransposeTests, StaticWrapper_Returns2x4MatrixWithRowAndColumnElementsExchanged)
{ EXPECT_MAT_EQ(this->_expectedTranspose, flcn::Mat4x2<TypeParam>::transpose(this->_matrix)); }

/** @} */
