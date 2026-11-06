/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 17, 2026
 *
 * @brief Verify @ref flcn::Mat2x3 accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2x3TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat2x3_Access
 * @{
 */

namespace
{
    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat2x3 MAT(1, 2, 3, 4, 5, 6);
        constexpr flcn::CVec2 VEC0(1, 4);
        constexpr flcn::CVec2 VEC1(2, 5);
        constexpr flcn::CVec2 VEC2(3, 6);

        /// @test Verify that matrix elements are accessible as (row, column) during compile time.
        static_assert(MAT(0, 0) == 1);
        static_assert(MAT(0, 1) == 2);
        static_assert(MAT(0, 2) == 3);
        static_assert(MAT(1, 0) == 4);
        static_assert(MAT(1, 1) == 5);
        static_assert(MAT(1, 2) == 6);

        /// @test Verify that matrix columns are accessible as 2D-vectors during compile time.
        static_assert(MAT[0].x() == VEC0[0]);
        static_assert(MAT[0].y() == VEC0[1]);
        static_assert(MAT[1].x() == VEC1[0]);
        static_assert(MAT[1].y() == VEC1[1]);
        static_assert(MAT[2].x() == VEC2[0]);
        static_assert(MAT[2].y() == VEC2[1]);

    } // namespace static_tests
} // namespace



/**************************************
 *            ACCESS TESTS            *
 **************************************/

TEST(Mat2x3AccessTests, AccessibleAsElements)
{
    constexpr flcn::Mat2x3 mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);

    EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
    EXPECT_FLOAT_EQ(2.0f, mat(0, 1));
    EXPECT_FLOAT_EQ(3.0f, mat(0, 2));
    EXPECT_FLOAT_EQ(4.0f, mat(1, 0));
    EXPECT_FLOAT_EQ(5.0f, mat(1, 1));
    EXPECT_FLOAT_EQ(6.0f, mat(1, 2));
}


TEST(Mat2x3AccessTests, AccessibleAsColumnVectors)
{
    constexpr flcn::Mat2x3 mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);

    EXPECT_VEC_EQ(flcn::CVec2(1.0f, 4.0f), mat[0]);
    EXPECT_VEC_EQ(flcn::CVec2(2.0f, 5.0f), mat[1]);
    EXPECT_VEC_EQ(flcn::CVec2(3.0f, 6.0f), mat[2]);
}



/**************************************
 *           MUTATION TESTS           *
 **************************************/

TEST(Mat2x3MutationTests, ElementsCanBeMutatedUsingIndex)
{
    flcn::Mat2x3<float> mat;

    mat(0, 0) = 1.0f;
    mat(0, 1) = 2.0f;
    mat(0, 2) = 3.0f;
    mat(1, 0) = 4.0f;
    mat(1, 1) = 5.0f;
    mat(1, 2) = 6.0f;

    EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
    EXPECT_FLOAT_EQ(2.0f, mat(0, 1));
    EXPECT_FLOAT_EQ(3.0f, mat(0, 2));
    EXPECT_FLOAT_EQ(4.0f, mat(1, 0));
    EXPECT_FLOAT_EQ(5.0f, mat(1, 1));
    EXPECT_FLOAT_EQ(6.0f, mat(1, 2));
}


TEST(Mat2x3MutationTests, ColumnsCanBeMutatedUsingIndex)
{
    const flcn::CVec2 col0 = { 1.0f, 4.0f };
    const flcn::CVec2 col1 = { 2.0f, 5.0f };
    const flcn::CVec2 col2 = { 3.0f, 6.0f };
    flcn::Mat2x3<float> mat;

    mat[0] = col0;
    mat[1] = col1;
    mat[2] = col2;

    EXPECT_VEC_EQ(col0, mat[0]);
    EXPECT_VEC_EQ(col1, mat[1]);
    EXPECT_VEC_EQ(col2, mat[2]);
}

/** @} */
