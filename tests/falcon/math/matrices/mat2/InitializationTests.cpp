/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref flcn::Mat2 initialization.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat2x2_Init
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2 initialization.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2InitializationTests: public testing::Test
    {
    protected:
        std::vector<T> _elements;
        std::vector<T> _diagonalElements;
        flcn::CVec2<T> _col0, _col1;
        T _diagonal0, _diagonal1;

        void SetUp() override
        {
            _elements         = { T(1), T(2), T(3), T(4) };
            _diagonalElements = { T(2), T(0), T(0), T(3) };
            _col0             = { T(1), T(3) };
            _col1             = { T(2), T(4) };
            _diagonal0        = T(2);
            _diagonal1        = T(3);
        }
    };
    TYPED_TEST_SUITE(Mat2InitializationTests, SupportedTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that the matrix can be initialized at compile time using scalar values.
        constexpr flcn::Mat2 MAT1(1, 2, 3, 4);
        static_assert(MAT1(0, 0) == 1);
        static_assert(MAT1(0, 1) == 2);
        static_assert(MAT1(1, 0) == 3);
        static_assert(MAT1(1, 1) == 4);


        /// @test Verify that the matrix can be initialized at compile time using column vectors.
        constexpr flcn::Mat2 MAT2(flcn::CVec2(1, 3), flcn::CVec2(2, 4));
        static_assert(MAT2(0, 0) == 1);
        static_assert(MAT2(0, 1) == 2);
        static_assert(MAT2(1, 0) == 3);
        static_assert(MAT2(1, 1) == 4);


        /// @test Verify that the matrix can be initialized at compile time using diagonals.
        constexpr flcn::Mat2 MAT3(3, 4);
        static_assert(MAT3(0, 0) == 3);
        static_assert(MAT3(0, 1) == 0);
        static_assert(MAT3(1, 0) == 0);
        static_assert(MAT3(1, 1) == 4);

        /// @test Verify that the matrix can be initialized at compile time using value initialization.
        constexpr flcn::Mat2<int> MAT4{};
        static_assert(MAT4(0, 0) == 0);
        static_assert(MAT4(0, 1) == 0);
        static_assert(MAT4(1, 0) == 0);
        static_assert(MAT4(1, 1) == 0);

    } // namespace static_tests

} // namespace



/**************************************
 *            RUNTIME TESTS           *
 **************************************/

TYPED_TEST(Mat2InitializationTests, EmptyCtor_ReturnsZeroMatrix)
{
    const flcn::Mat2<TypeParam> matrix{};
    EXPECT_MAT_ZERO(matrix);
}


TYPED_TEST(Mat2InitializationTests, ParameterizedCtor_InitializesMatrixWithElements)
{
    const flcn::Mat2<TypeParam> matrix(this->_elements[0], this->_elements[1], this->_elements[2], this->_elements[3]);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}


TYPED_TEST(Mat2InitializationTests, ParameterizedCtor_InitializesMatrixWithVectors)
{
    const flcn::Mat2<TypeParam> matrix(this->_col0, this->_col1);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}


TYPED_TEST(Mat2InitializationTests, ParameterizedCtor_InitializesDiagonalMatrix)
{
    const flcn::Mat2<TypeParam> matrix(this->_diagonal0, this->_diagonal1);
    EXPECT_MAT_CONTAINS(this->_diagonalElements, matrix);
}


TYPED_TEST(Mat2InitializationTests, CanBeConstructedWithBracedInitialization)
{
    const flcn::Mat2<TypeParam> matrix = { { TypeParam(1), TypeParam(3) }, { TypeParam(2), TypeParam(4) } };
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}

/** @} */
