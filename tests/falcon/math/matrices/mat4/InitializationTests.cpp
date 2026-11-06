/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 01, 2026
 *
 * @brief Verify @ref flcn::Mat4 initialization.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat4x4_Init
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4 initialization.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat4InitializationTests: public testing::Test
    {
    protected:
        std::vector<T> _elements;
        std::vector<T> _diagonalElements;
        flcn::Vec4<T> _col0, _col1, _col2, _col3;
        T _diagonal0, _diagonal1, _diagonal2, _diagonal3;

        void SetUp() override
        {
            _elements         = { T(1), T(2),  T(3),  T(4),  T(5),  T(6),  T(7),  T(8),
                                  T(9), T(10), T(11), T(12), T(13), T(14), T(15), T(16) };
            _diagonalElements = { T(2), T(0), T(0), T(0), T(0), T(3), T(0), T(0),
                                  T(0), T(0), T(5), T(0), T(0), T(0), T(0), T(11) };
            _col0             = { T(1), T(5), T(9), T(13) };
            _col1             = { T(2), T(6), T(10), T(14) };
            _col2             = { T(3), T(7), T(11), T(15) };
            _col3             = { T(4), T(8), T(12), T(16) };
            _diagonal0        = T(2);
            _diagonal1        = T(3);
            _diagonal2        = T(5);
            _diagonal3        = T(11);
        }
    };
    TYPED_TEST_SUITE(Mat4InitializationTests, SupportedTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that the matrix can be initialized at compile time using scalar values.
        constexpr flcn::Mat4 MAT1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        static_assert(MAT1(0, 0) == 1);
        static_assert(MAT1(0, 1) == 2);
        static_assert(MAT1(0, 2) == 3);
        static_assert(MAT1(0, 3) == 4);
        static_assert(MAT1(1, 0) == 5);
        static_assert(MAT1(1, 1) == 6);
        static_assert(MAT1(1, 2) == 7);
        static_assert(MAT1(1, 3) == 8);
        static_assert(MAT1(2, 0) == 9);
        static_assert(MAT1(2, 1) == 10);
        static_assert(MAT1(2, 2) == 11);
        static_assert(MAT1(2, 3) == 12);
        static_assert(MAT1(3, 0) == 13);
        static_assert(MAT1(3, 1) == 14);
        static_assert(MAT1(3, 2) == 15);
        static_assert(MAT1(3, 3) == 16);


        /// @test Verify that the matrix can be initialized at compile time using column vectors.
        constexpr flcn::Mat4 MAT2(flcn::Vec4(1, 5, 9, 13), flcn::Vec4(2, 6, 10, 14), flcn::Vec4(3, 7, 11, 15),
                                 flcn::Vec4(4, 8, 12, 16));
        static_assert(MAT2(0, 0) == 1);
        static_assert(MAT2(0, 1) == 2);
        static_assert(MAT2(0, 2) == 3);
        static_assert(MAT2(0, 3) == 4);
        static_assert(MAT2(1, 0) == 5);
        static_assert(MAT2(1, 1) == 6);
        static_assert(MAT2(1, 2) == 7);
        static_assert(MAT2(1, 3) == 8);
        static_assert(MAT2(2, 0) == 9);
        static_assert(MAT2(2, 1) == 10);
        static_assert(MAT2(2, 2) == 11);
        static_assert(MAT2(2, 3) == 12);
        static_assert(MAT2(3, 0) == 13);
        static_assert(MAT2(3, 1) == 14);
        static_assert(MAT2(3, 2) == 15);
        static_assert(MAT2(3, 3) == 16);


        /// @test Verify that the matrix can be initialized at compile time using diagonals.
        constexpr flcn::Mat4 MAT3(3, 4, 5, 6);
        static_assert(MAT3(0, 0) == 3);
        static_assert(MAT3(0, 1) == 0);
        static_assert(MAT3(0, 2) == 0);
        static_assert(MAT3(0, 3) == 0);
        static_assert(MAT3(1, 0) == 0);
        static_assert(MAT3(1, 1) == 4);
        static_assert(MAT3(1, 2) == 0);
        static_assert(MAT3(1, 3) == 0);
        static_assert(MAT3(2, 0) == 0);
        static_assert(MAT3(2, 1) == 0);
        static_assert(MAT3(2, 2) == 5);
        static_assert(MAT3(2, 3) == 0);
        static_assert(MAT3(3, 0) == 0);
        static_assert(MAT3(3, 1) == 0);
        static_assert(MAT3(3, 2) == 0);
        static_assert(MAT3(3, 3) == 6);


        /// @test Verify that the matrix can be initialized at compile time using value initialization.
        constexpr flcn::Mat4<int> MAT4{};
        static_assert(MAT4(0, 0) == 0);
        static_assert(MAT4(0, 1) == 0);
        static_assert(MAT4(0, 2) == 0);
        static_assert(MAT4(0, 3) == 0);
        static_assert(MAT4(1, 0) == 0);
        static_assert(MAT4(1, 1) == 0);
        static_assert(MAT4(1, 2) == 0);
        static_assert(MAT4(1, 3) == 0);
        static_assert(MAT4(2, 0) == 0);
        static_assert(MAT4(2, 1) == 0);
        static_assert(MAT4(2, 2) == 0);
        static_assert(MAT4(2, 3) == 0);
        static_assert(MAT4(3, 0) == 0);
        static_assert(MAT4(3, 1) == 0);
        static_assert(MAT4(3, 2) == 0);
        static_assert(MAT4(3, 3) == 0);

    } // namespace static_tests
} // namespace



/**************************************
 *            RUNTIME TESTS           *
 **************************************/

TYPED_TEST(Mat4InitializationTests, EmptyCtor_ReturnsIdentityMatrix)
{
    constexpr flcn::Mat4<TypeParam> matrix{};

    EXPECT_MAT_ZERO(matrix);
}


TYPED_TEST(Mat4InitializationTests, ParameterizedCtor_InitializesMatrixWithElements)
{
    const flcn::Mat4<TypeParam> matrix(this->_elements[0], this->_elements[1], this->_elements[2], this->_elements[3],
                                      this->_elements[4], this->_elements[5], this->_elements[6], this->_elements[7],
                                      this->_elements[8], this->_elements[9], this->_elements[10], this->_elements[11],
                                      this->_elements[12], this->_elements[13], this->_elements[14],
                                      this->_elements[15]);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}


TYPED_TEST(Mat4InitializationTests, ParameterizedCtor_InitializesMatrixWithVectors)
{
    const flcn::Mat4<TypeParam> matrix(this->_col0, this->_col1, this->_col2, this->_col3);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}


TYPED_TEST(Mat4InitializationTests, ParameterizedCtor_InitializesDiagonalMatrix)
{
    const flcn::Mat4<TypeParam> matrix(this->_diagonal0, this->_diagonal1, this->_diagonal2, this->_diagonal3);
    EXPECT_MAT_CONTAINS(this->_diagonalElements, matrix);
}


TYPED_TEST(Mat4InitializationTests, CanBeConstructedWithBracedInitialization)
{
    const flcn::Mat4<TypeParam> matrix = { { TypeParam(1), TypeParam(5), TypeParam(9), TypeParam(13) },
                                          { TypeParam(2), TypeParam(6), TypeParam(10), TypeParam(14) },
                                          { TypeParam(3), TypeParam(7), TypeParam(11), TypeParam(15) },
                                          { TypeParam(4), TypeParam(8), TypeParam(12), TypeParam(16) } };
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}

/** @} */
