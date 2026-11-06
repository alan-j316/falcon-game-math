/**
 * @file TransposeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 25, 2026
 *
 * @brief Verify @ref flcn::Mat2x3 transpose logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2x3TestSetup.h"

#include <falcon/math/matrices/Mat3x2.h>


/**
 * @addtogroup T_FALCON_Mat2x3_Transpose
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2x3 matrix transposition.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat2x3TransposeTests: public testing::Test
    {
    protected:
        flcn::Mat2x3<T> _matrix;
        flcn::Mat3x2<T> _expectedTranspose;

        void SetUp() override
        {
            _matrix            = { flcn::CVec2{ T(1), T(4) }, flcn::CVec2{ T(2), T(5) }, flcn::CVec2{ T(3), T(6) } };
            _expectedTranspose = { flcn::Vec3{ T(1), T(2), T(3) }, flcn::Vec3{ T(4), T(5), T(6) } };
        }
    };
    TYPED_TEST_SUITE(Mat2x3TransposeTests, SupportedTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat2x3 MAT(1, 2, 3, 4, 5, 6);

        // NOTE: The matrix takes elements in row, col order
        //       but when compared with Vec3, we are taking col, row order.
        //       That's why Vec3(1, 2, 3) is the transpose and not Vec3(1, 3, 5)

        /// @test Verify matrix transpose is returns a 3x2 matrix with swapped rows and
        ///       columns at compile time.
        constexpr flcn::Mat3x2 TRANSPOSE_MAT = MAT.transpose();
        static_assert(TRANSPOSE_MAT[0] == flcn::Vec3(1, 2, 3));
        static_assert(TRANSPOSE_MAT[1] == flcn::Vec3(4, 5, 6));

        /// @test Verify matrix transpose using static variant returns a 3x2 matrix with
        ///       swapped rows and columns at compile time.
        constexpr auto TRANSPOSE_MAT_STATIC = flcn::Mat2x3<int>::transpose(MAT);
        static_assert(TRANSPOSE_MAT_STATIC[0] == flcn::Vec3(1, 2, 3));
        static_assert(TRANSPOSE_MAT_STATIC[1] == flcn::Vec3(4, 5, 6));

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat2x3TransposeTests, Returns3x2MatrixWithRowAndColumnElementsExchanged)
{ EXPECT_MAT_EQ(this->_expectedTranspose, this->_matrix.transpose()); }


TYPED_TEST(Mat2x3TransposeTests, StaticWrapper_Returns3x2MatrixWithRowAndColumnElementsExchanged)
{ EXPECT_MAT_EQ(this->_expectedTranspose, flcn::Mat2x3<TypeParam>::transpose(this->_matrix)); }

/** @} */
