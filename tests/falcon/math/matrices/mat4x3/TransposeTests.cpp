/**
 * @file TransposeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 27, 2026
 *
 * @brief Verify @ref flcn::Mat4x3 transpose logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4x3TestSetup.h"

#include <falcon/math/matrices/Mat3x4.h>


/**
 * @addtogroup T_FALCON_Mat4x3_Transpose
 * @{
 */

namespace
{
    /**************************************
     *               SETUP                *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4x3 matrix transposition.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat4x3TransposeTests: public ::testing::Test
    {
    protected:
        flcn::Mat4x3<T> _matrix;
        flcn::Mat3x4<T> _expectedTranspose;

        void SetUp() override
        {
            _matrix            = { flcn::Vec4{ T(1), T(4), T(7), T(10) }, flcn::Vec4{ T(2), T(5), T(8), T(11) },
                                   flcn::Vec4{ T(3), T(6), T(9), T(12) } };
            _expectedTranspose = { flcn::Vec3{ T(1), T(2), T(3) }, flcn::Vec3{ T(4), T(5), T(6) },
                                   flcn::Vec3{ T(7), T(8), T(9) }, flcn::Vec3{ T(10), T(11), T(12) } };
        }
    };
    TYPED_TEST_SUITE(Mat4x3TransposeTests, SupportedTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat4x3 MAT(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);

        // NOTE: The matrix takes elements in row, col order
        //       but when compared with Vec3, we are taking col, row order.
        //       That's why Vec3(1, 2, 3) is the transpose and not Vec4(1, 4, 7)

        /// @test Verify matrix transpose is returns a 3x4 matrix with swapped rows and
        ///       columns at compile time.
        constexpr auto TRANSPOSE_MAT = MAT.transpose();
        static_assert(TRANSPOSE_MAT[0] == flcn::Vec3(1, 2, 3));
        static_assert(TRANSPOSE_MAT[1] == flcn::Vec3(4, 5, 6));
        static_assert(TRANSPOSE_MAT[2] == flcn::Vec3(7, 8, 9));
        static_assert(TRANSPOSE_MAT[3] == flcn::Vec3(10, 11, 12));

        /// @test Verify matrix transpose using static variant returns a 3x4 matrix with
        ///       swapped rows and columns at compile time.
        constexpr auto TRANSPOSE_MAT_STATIC = flcn::Mat4x3<int>::transpose(MAT);
        static_assert(TRANSPOSE_MAT_STATIC[0] == flcn::Vec3(1, 2, 3));
        static_assert(TRANSPOSE_MAT_STATIC[1] == flcn::Vec3(4, 5, 6));
        static_assert(TRANSPOSE_MAT_STATIC[2] == flcn::Vec3(7, 8, 9));
        static_assert(TRANSPOSE_MAT_STATIC[3] == flcn::Vec3(10, 11, 12));

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat4x3TransposeTests, Returns3x4MatrixWithRowAndColumnElementsExchanged)
{ EXPECT_MAT_EQ(this->_expectedTranspose, this->_matrix.transpose()); }


TYPED_TEST(Mat4x3TransposeTests, StaticWrapper_Returns3x4MatrixWithRowAndColumnElementsExchanged)
{ EXPECT_MAT_EQ(this->_expectedTranspose, flcn::Mat4x3<TypeParam>::transpose(this->_matrix)); }

/** @} */
