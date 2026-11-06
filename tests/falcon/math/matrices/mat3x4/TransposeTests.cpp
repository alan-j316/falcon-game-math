/**
 * @file TransposeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 27, 2026
 *
 * @brief Verify @ref flcn::Mat3x4 transpose logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3x4TestSetup.h"

#include <falcon/math/matrices/Mat4x3.h>


/**
 * @addtogroup T_FALCON_Mat3x4_Transpose
 * @{
 */

namespace
{
    /**************************************
     *               SETUP                *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat3x4 matrix transposition.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat3x4TransposeTests: public ::testing::Test
    {
    protected:
        flcn::Mat3x4<T> _matrix;
        flcn::Mat4x3<T> _expectedTranspose;

        void SetUp() override
        {
            _matrix = { flcn::Vec3{ T(1), T(2), T(3) }, flcn::Vec3{ T(4), T(5), T(6) }, flcn::Vec3{ T(7), T(8), T(9) },
                        flcn::Vec3{ T(10), T(11), T(12) } };
            _expectedTranspose = { flcn::Vec4{ T(1), T(4), T(7), T(10) }, flcn::Vec4{ T(2), T(5), T(8), T(11) },
                                   flcn::Vec4{ T(3), T(6), T(9), T(12) } };
        }
    };
    TYPED_TEST_SUITE(Mat3x4TransposeTests, SupportedTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    /** @test Verify that matrix transpose is available at compile time. */
    namespace static_tests
    {
        constexpr flcn::Mat3x4 MAT(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);

        // NOTE: The matrix takes elements in row, col order
        //       but when compared with Vec4, we are taking col, row order.
        //       That's why Vec4(1, 2, 3, 4) is the transpose and not Vec4(1, 5, 9, 2)

        /// @test Verify matrix transpose is returns a 4x3 matrix with swapped rows and
        ///       columns at compile time.
        constexpr auto TRANSPOSE_MAT = MAT.transpose();
        static_assert(TRANSPOSE_MAT[0] == flcn::Vec4(1, 2, 3, 4));
        static_assert(TRANSPOSE_MAT[1] == flcn::Vec4(5, 6, 7, 8));
        static_assert(TRANSPOSE_MAT[2] == flcn::Vec4(9, 10, 11, 12));

        /// @test Verify matrix transpose using static variant returns a 4x3 matrix with
        ///       swapped rows and columns at compile time.
        constexpr auto TRANSPOSE_MAT_STATIC = flcn::Mat3x4<int>::transpose(MAT);
        static_assert(TRANSPOSE_MAT_STATIC[0] == flcn::Vec4(1, 2, 3, 4));
        static_assert(TRANSPOSE_MAT_STATIC[1] == flcn::Vec4(5, 6, 7, 8));
        static_assert(TRANSPOSE_MAT_STATIC[2] == flcn::Vec4(9, 10, 11, 12));

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat3x4TransposeTests, Returns4x3MatrixWithRowAndColumnElementsExchanged)
{ EXPECT_MAT_EQ(this->_expectedTranspose, this->_matrix.transpose()); }


TYPED_TEST(Mat3x4TransposeTests, StaticWrapper_Returns4x3MatrixWithRowAndColumnElementsExchanged)
{ EXPECT_MAT_EQ(this->_expectedTranspose, flcn::Mat3x4<TypeParam>::transpose(this->_matrix)); }

/** @} */
