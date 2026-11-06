/**
 * @file DeterminantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 07, 2026
 *
 * @brief Verify @ref flcn::Mat4 determinant logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "Mat4TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat4x4_Det
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4 Determinants.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
template <typename T>
class Mat4DeterminantTests: public testing::Test
{
protected:
    flcn::Mat4<T> _matrix;
    T _expectedDeterminant;

    void SetUp() override
    {
        _matrix              = { { T(1), T(2), T(3), T(4) },
                                 { T(1), T(2), T(1), T(3) },
                                 { T(2), T(3), T(4), T(12) },
                                 { T(2), T(1), T(3), T(2) } };
        _expectedDeterminant = T(39);
    }
};
TYPED_TEST_SUITE(Mat4DeterminantTests, SupportedSignedArithmeticTypes);


    /**
       * @brief Test fixture for @ref flcn::Mat4 Determinants with singular matrices.
       */
class SingularMat4DeterminantTests: public testing::TestWithParam<flcn::Mat4<float>>
{};
INSTANTIATE_TEST_SUITE_P(
    Mat4DeterminantTestSuite, SingularMat4DeterminantTests,
    ::testing::Values(flcn::Mat4{ flcn::Vec4{ 1.0f, 2.0f, 3.0f, 4.0f }, flcn::Vec4{ 1.0f, 2.0f, 3.0f, 4.0f },
                                 flcn::Vec4{ 7.0f, 8.0f, 9.0f, 12.0f }, flcn::Vec4{ 1.0f, 85.0f, 19.0f, 12.0f } },
                      flcn::Mat4{ flcn::Vec4{ 1.0f, 1.0f, 3.0f, 4.0f }, flcn::Vec4{ 2.0f, 2.0f, 3.0f, 4.0f },
                                 flcn::Vec4{ 3.0f, 3.0f, 9.0f, 12.0f }, flcn::Vec4{ 4.0f, 4.0f, 31.6f, 2.0f } },
                      flcn::Mat4{ flcn::Vec4{ 0.0f, 0.0f, 0.0f, 0.0f }, flcn::Vec4{ 2.0f, 2.0f, 3.0f, 4.0f },
                                 flcn::Vec4{ 3.0f, 3.0f, 9.0f, 12.0f }, flcn::Vec4{ 4.0f, 4.0f, 31.6f, 2.0f } },
                      flcn::Mat4{ flcn::Vec4{ 0.0f, 1.0f, 3.0f, 4.0f }, flcn::Vec4{ 0.0f, 2.0f, 3.0f, 4.0f },
                                 flcn::Vec4{ 0.0f, 3.0f, 9.0f, 12.0f }, flcn::Vec4{ 0.0f, 4.0f, 31.6f, 2.0f } },
                      flcn::Mat4{ flcn::Vec4{ 1.0f, 2.0f, 3.0f, 4.0f }, flcn::Vec4{ 2.0f, 4.0f, 6.0f, 8.0f },
                                 flcn::Vec4{ 3.0f, 3.0f, 9.0f, 12.0f }, flcn::Vec4{ 4.0f, 4.0f, 31.6f, 2.0f } },
                      flcn::Mat4{ flcn::Vec4{ 1.0f, 2.0f, 3.0f, 4.0f }, flcn::Vec4{ 2.0f, 4.0f, 5.0f, 10.0f },
                                 flcn::Vec4{ 3.0f, 6.0f, 9.0f, 12.0f }, flcn::Vec4{ 4.0f, 8.0f, 31.6f, 2.0f } }));



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
    constexpr flcn::Mat4 MAT{ flcn::Vec4{ 1, 2, 3, 4 }, flcn::Vec4{ 1, 2, 1, 3 }, flcn::Vec4{ 2, 3, 4, 12 },
                             flcn::Vec4{ 2, 1, 3, 2 } };

        /// @test Verify that Mat4 determinant returns a valid value at compile time.
    static_assert(MAT.determinant() == 39);

        /// @test Verify that Mat4 determinant (static wrapper) returns a valid value at compile time.
    static_assert(flcn::Mat4<int>::determinant(MAT) == 39);

} // namespace
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat4DeterminantTests, ReturnsNonZeroScalar)
{
    EXPECT_MAG_EQ(this->_expectedDeterminant, this->_matrix.determinant());
}


TEST_P(SingularMat4DeterminantTests, SingularMatrixReturnsZero)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, matrix.determinant());
}


TYPED_TEST(Mat4DeterminantTests, StaticWrapper_ReturnsNonZeroScalar)
{
    EXPECT_MAG_EQ(this->_expectedDeterminant, flcn::Mat4<TypeParam>::determinant(this->_matrix));
}


TEST_P(SingularMat4DeterminantTests, StaticWrapper_SingularMatrixReturnsZero)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, flcn::Mat4<float>::determinant(matrix));
}

/** @} */
