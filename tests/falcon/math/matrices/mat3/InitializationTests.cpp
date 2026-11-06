/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 22, 2026
 *
 * @brief Verify @ref flcn::Mat3 initialization.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat3x3_Init
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat3 initialization.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat3InitializationTests: public testing::Test
    {
    protected:
        std::vector<T> _elements;
        std::vector<T> _diagonalElements;
        flcn::Vec3<T> _col0, _col1, _col2;
        T _diagonal0, _diagonal1, _diagonal2;

        void SetUp() override
        {
            _elements         = { T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8), T(9) };
            _diagonalElements = { T(2), T(0), T(0), T(0), T(3), T(0), T(0), T(0), T(5) };
            _col0             = { T(1), T(4), T(7) };
            _col1             = { T(2), T(5), T(8) };
            _col2             = { T(3), T(6), T(9) };
            _diagonal0        = T(2);
            _diagonal1        = T(3);
            _diagonal2        = T(5);
        }
    };
    TYPED_TEST_SUITE(Mat3InitializationTests, SupportedTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that the matrix can be initialized at compile time using scalar values.
        constexpr flcn::Mat3 MAT1(1, 2, 3, 4, 5, 6, 7, 8, 9);
        static_assert(MAT1(0, 0) == 1);
        static_assert(MAT1(0, 1) == 2);
        static_assert(MAT1(0, 2) == 3);
        static_assert(MAT1(1, 0) == 4);
        static_assert(MAT1(1, 1) == 5);
        static_assert(MAT1(1, 2) == 6);
        static_assert(MAT1(2, 0) == 7);
        static_assert(MAT1(2, 1) == 8);
        static_assert(MAT1(2, 2) == 9);


        /// @test Verify that the matrix can be initialized at compile time using column vectors.
        constexpr flcn::Mat3 MAT2(flcn::Vec3(1, 4, 7), flcn::Vec3(2, 5, 8), flcn::Vec3(3, 6, 9));
        static_assert(MAT2(0, 0) == 1);
        static_assert(MAT2(0, 1) == 2);
        static_assert(MAT2(0, 2) == 3);
        static_assert(MAT2(1, 0) == 4);
        static_assert(MAT2(1, 1) == 5);
        static_assert(MAT2(1, 2) == 6);
        static_assert(MAT2(2, 0) == 7);
        static_assert(MAT2(2, 1) == 8);
        static_assert(MAT2(2, 2) == 9);


        /// @test Verify that the matrix can be initialized at compile time using diagonals.
        constexpr flcn::Mat3 MAT3(3, 4, 5);
        static_assert(MAT3(0, 0) == 3);
        static_assert(MAT3(0, 1) == 0);
        static_assert(MAT3(0, 2) == 0);
        static_assert(MAT3(1, 0) == 0);
        static_assert(MAT3(1, 1) == 4);
        static_assert(MAT3(1, 2) == 0);
        static_assert(MAT3(2, 0) == 0);
        static_assert(MAT3(2, 1) == 0);
        static_assert(MAT3(2, 2) == 5);


        /// @test Verify that the matrix can be initialized at compile time using value initialization.
        constexpr flcn::Mat3<int> MAT4{};
        static_assert(MAT4(0, 0) == 0);
        static_assert(MAT4(0, 1) == 0);
        static_assert(MAT4(0, 2) == 0);
        static_assert(MAT4(1, 0) == 0);
        static_assert(MAT4(1, 1) == 0);
        static_assert(MAT4(1, 2) == 0);
        static_assert(MAT4(2, 0) == 0);
        static_assert(MAT4(2, 1) == 0);
        static_assert(MAT4(2, 2) == 0);

    } // namespace static_tests
} // namespace



/**************************************
 *            RUNTIME TESTS           *
 **************************************/

TYPED_TEST(Mat3InitializationTests, EmptyCtor_ReturnsIdentityMatrix)
{
    const flcn::Mat3<TypeParam> matrix{};

    EXPECT_MAT_ZERO(matrix);
}


TYPED_TEST(Mat3InitializationTests, ParameterizedCtor_InitializesMatrixWithElements)
{
    const flcn::Mat3<TypeParam> matrix(this->_elements[0], this->_elements[1], this->_elements[2], this->_elements[3],
                                      this->_elements[4], this->_elements[5], this->_elements[6], this->_elements[7],
                                      this->_elements[8]);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}


TYPED_TEST(Mat3InitializationTests, ParameterizedCtor_InitializesMatrixWithVectors)
{
    const flcn::Mat3<TypeParam> matrix(this->_col0, this->_col1, this->_col2);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}


TYPED_TEST(Mat3InitializationTests, ParameterizedCtor_InitializesDiagonalMatrix)
{
    const flcn::Mat3<TypeParam> matrix(this->_diagonal0, this->_diagonal1, this->_diagonal2);
    EXPECT_MAT_CONTAINS(this->_diagonalElements, matrix);
}


TYPED_TEST(Mat3InitializationTests, CanBeConstructedWithBracedInitialization)
{
    const flcn::Mat3<TypeParam> matrix = { { TypeParam(1), TypeParam(4), TypeParam(7) },
                                          { TypeParam(2), TypeParam(5), TypeParam(8) },
                                          { TypeParam(3), TypeParam(6), TypeParam(9) } };
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}

/** @} */
