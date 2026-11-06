/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref flcn::Mat4x3 initialization.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4x3TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat4x3_Init
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4x3 initialization.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat4x3InitializationTests: public testing::Test
    {
    protected:
        std::vector<T> _elements;
        flcn::Vec4<T> _col0, _col1, _col2;

        void SetUp() override
        {
            _elements = { T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8), T(9), T(10), T(11), T(12) };
            _col0     = { T(1), T(4), T(7), T(10) };
            _col1     = { T(2), T(5), T(8), T(11) };
            _col2     = { T(3), T(6), T(9), T(12) };
        }
    };
    TYPED_TEST_SUITE(Mat4x3InitializationTests, SupportedTypes);




    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that the matrix can be initialized at compile time using scalar values.
        constexpr flcn::Mat4x3 MAT1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
        static_assert(MAT1(0, 0) == 1);
        static_assert(MAT1(0, 1) == 2);
        static_assert(MAT1(0, 2) == 3);
        static_assert(MAT1(1, 0) == 4);
        static_assert(MAT1(1, 1) == 5);
        static_assert(MAT1(1, 2) == 6);
        static_assert(MAT1(2, 0) == 7);
        static_assert(MAT1(2, 1) == 8);
        static_assert(MAT1(2, 2) == 9);
        static_assert(MAT1(3, 0) == 10);
        static_assert(MAT1(3, 1) == 11);
        static_assert(MAT1(3, 2) == 12);


        /// @test Verify that the matrix can be initialized at compile time using column vectors.
        constexpr flcn::Mat4x3 MAT2(flcn::Vec4(1, 4, 7, 10), flcn::Vec4(2, 5, 8, 11), flcn::Vec4(3, 6, 9, 12));
        static_assert(MAT2(0, 0) == 1);
        static_assert(MAT2(0, 1) == 2);
        static_assert(MAT2(0, 2) == 3);
        static_assert(MAT2(1, 0) == 4);
        static_assert(MAT2(1, 1) == 5);
        static_assert(MAT2(1, 2) == 6);
        static_assert(MAT2(2, 0) == 7);
        static_assert(MAT2(2, 1) == 8);
        static_assert(MAT2(2, 2) == 9);
        static_assert(MAT2(3, 0) == 10);
        static_assert(MAT2(3, 1) == 11);
        static_assert(MAT2(3, 2) == 12);



        /// @test Verify that the matrix can be initialized at compile time using value initialization.
        constexpr flcn::Mat4x3<int> MAT3{};
        static_assert(MAT3(0, 0) == 0);
        static_assert(MAT3(0, 1) == 0);
        static_assert(MAT3(0, 2) == 0);
        static_assert(MAT3(1, 0) == 0);
        static_assert(MAT3(1, 1) == 0);
        static_assert(MAT3(1, 2) == 0);
        static_assert(MAT3(2, 0) == 0);
        static_assert(MAT3(2, 1) == 0);
        static_assert(MAT3(2, 2) == 0);
        static_assert(MAT3(3, 0) == 0);
        static_assert(MAT3(3, 1) == 0);
        static_assert(MAT3(3, 2) == 0);

    } // namespace static_tests

} // namespace



/**************************************
 *            RUNTIME TESTS           *
 **************************************/

TYPED_TEST(Mat4x3InitializationTests, EmptyCtor_ReturnsIdentityMatrix)
{
    constexpr flcn::Mat4x3<TypeParam> matrix{};

    EXPECT_MAT_ZERO(matrix);
}


TYPED_TEST(Mat4x3InitializationTests, ParameterizedCtor_InitializesMatrixWithElements)
{
    const flcn::Mat4x3<TypeParam> matrix(this->_elements[0], this->_elements[1], this->_elements[2], this->_elements[3],
                                        this->_elements[4], this->_elements[5], this->_elements[6], this->_elements[7],
                                        this->_elements[8], this->_elements[9], this->_elements[10],
                                        this->_elements[11]);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}


TYPED_TEST(Mat4x3InitializationTests, ParameterizedCtor_InitializesMatrixWithVectors)
{
    const flcn::Mat4x3<TypeParam> matrix(this->_col0, this->_col1, this->_col2);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}


TYPED_TEST(Mat4x3InitializationTests, CanBeConstructedWithBracedInitialization)
{
    const flcn::Mat4x3<TypeParam> matrix = {
        { TypeParam(1), TypeParam(4), TypeParam(7), TypeParam(10) },
        { TypeParam(2), TypeParam(5), TypeParam(8), TypeParam(11) },
        { TypeParam(3), TypeParam(6), TypeParam(9), TypeParam(12) },
    };
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}

/** @} */
