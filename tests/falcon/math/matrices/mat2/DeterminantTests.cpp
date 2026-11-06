/**
 * @file DeterminantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 13, 2026
 *
 * @brief Verify @ref flcn::Mat2 determinant logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "Mat2TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat2x2_Det
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2 Determinants.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2DeterminantTests: public testing::Test
    {
    protected:
        flcn::Mat2<T> _matrix;
        T _expectedDeterminant;

        void SetUp() override
        {
            _matrix              = { flcn::CVec2<T>{ 4, 1 }, flcn::CVec2<T>{ 2, 5 } };
            _expectedDeterminant = 18;
        }
    };
    TYPED_TEST_SUITE(Mat2DeterminantTests, SupportedSignedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::Mat2 Determinants with singular matrices.
     */
    class Mat2DeterminantSingularTests: public ::testing::TestWithParam<flcn::Mat2<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat2InvalidDeterminantTests, Mat2DeterminantSingularTests,
                             ::testing::Values(flcn::Mat2{ flcn::CVec2{ 1.0f, 2.0f }, flcn::CVec2{ 1.0f, 2.0f } },
                                               flcn::Mat2{ flcn::CVec2{ 2.0f, 2.0f }, flcn::CVec2{ 2.0f, 2.0f } },
                                               flcn::Mat2{ flcn::CVec2{ 3.0f, 2.0f }, flcn::CVec2{ 6.0f, 4.0f } },
                                               flcn::Mat2{ flcn::CVec2{ 0.0f, 0.0f }, flcn::CVec2{ 4.0f, 5.0f } },
                                               flcn::Mat2{ flcn::CVec2{ 0.0f, 3.0f }, flcn::CVec2{ 0.0f, 5.0f } }));



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat2 MAT{ flcn::CVec2{ 4, 2 }, flcn::CVec2{ 3, 4 } };

        /// @test Verify that Mat2 determinant returns a valid value at compile time.
        static_assert(MAT.determinant() == 10);

        /// @test Verify that Mat2 determinant (static wrapper) returns a valid value at compile time.
        static_assert(flcn::Mat2<int>::determinant(MAT) == 10);

    } // namespace

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat2DeterminantTests, NonSingularMatrix_ReturnsNonZeroScalar)
{ EXPECT_MAG_EQ(this->_expectedDeterminant, this->_matrix.determinant()); }


TYPED_TEST(Mat2DeterminantTests, StaticWrapper_NonSingularMatrix_ReturnsNonZeroScalar)
{ EXPECT_MAG_EQ(this->_expectedDeterminant, flcn::Mat2<TypeParam>::determinant(this->_matrix)); }


TEST_P(Mat2DeterminantSingularTests, SingularMatrix_ReturnsZeroMatrix)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, matrix.determinant());
}


TEST_P(Mat2DeterminantSingularTests, StaticWrapper_SingularMatrix_ReturnsZeroMatrix)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, flcn::Mat2<float>::determinant(matrix));
}

/** @} */
