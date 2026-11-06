/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 31, 2026
 *
 * @brief Verify @ref flcn::Transform4 accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Transform4TestSetup.h"


/**
 * @addtogroup T_FALCON_Transform4_Access
 * @{
 */

namespace
{
    /// @brief Test Fixture for flcn::Transform4 accessors.
    class Transform4AccessTests: public testing::Test
    {
    public:
        flcn::Transform4<float> mat{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f };
    };


    /// @brief Test Fixture for flcn::Transform4 accessors.
    class Transform4MutationTests: public testing::Test
    {
    public:
        [[maybe_unused]] flcn::Transform4<float> mat{};
    };



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Transform4<int> TRANSFORM{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
        constexpr flcn::Vec3 VEC0(1, 5, 9);
        constexpr flcn::Vec3 VEC1(2, 6, 10);
        constexpr flcn::Vec3 VEC2(3, 7, 11);
        constexpr flcn::Vec3 VEC3(4, 8, 12);

        /// @test Verify that matrix elements are accessible as (row, column) at compile time.
        static_assert(TRANSFORM(0, 0) == 1);
        static_assert(TRANSFORM(0, 1) == 2);
        static_assert(TRANSFORM(0, 2) == 3);
        static_assert(TRANSFORM(0, 3) == 4);
        static_assert(TRANSFORM(1, 0) == 5);
        static_assert(TRANSFORM(1, 1) == 6);
        static_assert(TRANSFORM(1, 2) == 7);
        static_assert(TRANSFORM(1, 3) == 8);
        static_assert(TRANSFORM(2, 0) == 9);
        static_assert(TRANSFORM(2, 1) == 10);
        static_assert(TRANSFORM(2, 2) == 11);
        static_assert(TRANSFORM(2, 3) == 12);

        /// @test Verify that matrix columns are accessible as 3D-vectors at compile time.
        static_assert(TRANSFORM[0] == VEC0);
        static_assert(TRANSFORM[1] == VEC1);
        static_assert(TRANSFORM[2] == VEC2);
        static_assert(TRANSFORM[3] == VEC3);


        /// @test Verify that getTranslation returns the last column vector as a Point3 at compile time.
        constexpr auto TRANSLATION = TRANSFORM.getTranslation();
        static_assert(std::is_same_v<decltype(TRANSLATION), const flcn::Point3<int>> == true);
        static_assert(TRANSLATION[0] == 4);
        static_assert(TRANSLATION[1] == 8);
        static_assert(TRANSLATION[2] == 12);

    } // namespace static_tests

} // namespace



/**************************************
 *            ACCESS TESTS            *
 **************************************/

TEST_F(Transform4AccessTests, AccessibleAsElements)
{

    EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
    EXPECT_FLOAT_EQ(2.0f, mat(0, 1));
    EXPECT_FLOAT_EQ(3.0f, mat(0, 2));
    EXPECT_FLOAT_EQ(4.0f, mat(0, 3));
    EXPECT_FLOAT_EQ(5.0f, mat(1, 0));
    EXPECT_FLOAT_EQ(6.0f, mat(1, 1));
    EXPECT_FLOAT_EQ(7.0f, mat(1, 2));
    EXPECT_FLOAT_EQ(8.0f, mat(1, 3));
    EXPECT_FLOAT_EQ(9.0f, mat(2, 0));
    EXPECT_FLOAT_EQ(10.0f, mat(2, 1));
    EXPECT_FLOAT_EQ(11.0f, mat(2, 2));
    EXPECT_FLOAT_EQ(12.0f, mat(2, 3));
}


TEST_F(Transform4AccessTests, AccessibleAsColumnVectors)
{
    EXPECT_VEC_EQ(flcn::Vec3(1.0f, 5.0f, 9.0f), mat[0]);
    EXPECT_VEC_EQ(flcn::Vec3(2.0f, 6.0f, 10.0f), mat[1]);
    EXPECT_VEC_EQ(flcn::Vec3(3.0f, 7.0f, 11.0f), mat[2]);
    EXPECT_VEC_EQ(flcn::Vec3(4.0f, 8.0f, 12.0f), mat[3]);
}



TEST_F(Transform4AccessTests, GetTranslation_ReturnsLastColumnAsPoint3)
{
    const auto translation = mat.getTranslation();
    EXPECT_FLOAT_EQ(4.0f, translation.x());
    EXPECT_FLOAT_EQ(8.0f, translation.y());
    EXPECT_FLOAT_EQ(12.0f, translation.z());
}


/** @} */



/**
 * @addtogroup T_FALCON_Transform4_Mutation
 * @{
 */

/**************************************
 *           MUTATION TESTS           *
 **************************************/

TEST_F(Transform4MutationTests, ElementsCanBeMutatedUsingIndex)
{
    mat(0, 0) = 1.0f;
    mat(0, 1) = 2.0f;
    mat(0, 2) = 3.0f;
    mat(0, 3) = 4.0f;
    mat(1, 0) = 5.0f;
    mat(1, 1) = 6.0f;
    mat(1, 2) = 7.0f;
    mat(1, 3) = 8.0f;
    mat(2, 0) = 9.0f;
    mat(2, 1) = 10.0f;
    mat(2, 2) = 11.0f;
    mat(2, 3) = 12.0f;


    EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
    EXPECT_FLOAT_EQ(2.0f, mat(0, 1));
    EXPECT_FLOAT_EQ(3.0f, mat(0, 2));
    EXPECT_FLOAT_EQ(4.0f, mat(0, 3));
    EXPECT_FLOAT_EQ(5.0f, mat(1, 0));
    EXPECT_FLOAT_EQ(6.0f, mat(1, 1));
    EXPECT_FLOAT_EQ(7.0f, mat(1, 2));
    EXPECT_FLOAT_EQ(8.0f, mat(1, 3));
    EXPECT_FLOAT_EQ(9.0f, mat(2, 0));
    EXPECT_FLOAT_EQ(10.0f, mat(2, 1));
    EXPECT_FLOAT_EQ(11.0f, mat(2, 2));
    EXPECT_FLOAT_EQ(12.0f, mat(2, 3));
}


TEST_F(Transform4MutationTests, ColumnsCanBeMutatedUsingIndex)
{
    const flcn::Vec3 col0 = { 1.0f, 5.0f, 9.0f };
    const flcn::Vec3 col1 = { 2.0f, 6.0f, 10.0f };
    const flcn::Vec3 col2 = { 3.0f, 7.0f, 11.0f };
    const flcn::Vec3 col3 = { 4.0f, 8.0f, 12.0f };

    mat[0] = col0;
    mat[1] = col1;
    mat[2] = col2;
    mat[3] = col3;

    EXPECT_VEC_EQ(col0, mat[0]);
    EXPECT_VEC_EQ(col1, mat[1]);
    EXPECT_VEC_EQ(col2, mat[2]);
    EXPECT_VEC_EQ(col3, mat[3]);
}


TEST_F(Transform4MutationTests, SetTranslationMutatesTheLastColumn)
{
    const flcn::Point3 translation{ 1.0f, 2.0f, 3.0f };
    mat.setTranslation(translation);

    EXPECT_FLOAT_EQ(translation.x(), mat(0, 3));
    EXPECT_FLOAT_EQ(translation.y(), mat(1, 3));
    EXPECT_FLOAT_EQ(translation.z(), mat(2, 3));
}

/** @} */
