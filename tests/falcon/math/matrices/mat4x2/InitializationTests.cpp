/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref flcn::Mat4x2 initialization.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4x2TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat4x2_Init
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4x2 initialization.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat4x2InitializationTests: public testing::Test
    {
    protected:
        std::vector<T> _elements;
        flcn::Vec4<T> _col0, _col1;

        void SetUp() override
        {
            _elements = { T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8) };
            _col0     = { T(1), T(3), T(5), T(7) };
            _col1     = { T(2), T(4), T(6), T(8) };
        }
    };
    TYPED_TEST_SUITE(Mat4x2InitializationTests, SupportedTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that the matrix can be initialized at compile time using scalar values.
        constexpr flcn::Mat4x2 MAT1(1, 2, 3, 4, 5, 6, 7, 8);
        static_assert(MAT1(0, 0) == 1);
        static_assert(MAT1(0, 1) == 2);
        static_assert(MAT1(1, 0) == 3);
        static_assert(MAT1(1, 1) == 4);
        static_assert(MAT1(2, 0) == 5);
        static_assert(MAT1(2, 1) == 6);
        static_assert(MAT1(3, 0) == 7);
        static_assert(MAT1(3, 1) == 8);


        /// @test Verify that the matrix can be initialized at compile time using column vectors.
        constexpr flcn::Mat4x2 MAT2(flcn::Vec4(1, 3, 5, 7), flcn::Vec4(2, 4, 6, 8));
        static_assert(MAT2(0, 0) == 1);
        static_assert(MAT2(0, 1) == 2);
        static_assert(MAT2(1, 0) == 3);
        static_assert(MAT2(1, 1) == 4);
        static_assert(MAT2(2, 0) == 5);
        static_assert(MAT2(2, 1) == 6);
        static_assert(MAT2(3, 0) == 7);
        static_assert(MAT2(3, 1) == 8);


        /// @test Verify that the matrix can be initialized at compile time using value initialization.
        constexpr flcn::Mat4x2<int> MAT4{};
        static_assert(MAT4(0, 0) == 0);
        static_assert(MAT4(0, 1) == 0);
        static_assert(MAT4(1, 0) == 0);
        static_assert(MAT4(1, 1) == 0);
        static_assert(MAT4(2, 0) == 0);
        static_assert(MAT4(2, 1) == 0);
        static_assert(MAT4(3, 0) == 0);
        static_assert(MAT4(3, 1) == 0);

    } // namespace static_tests
} // namespace



/**************************************
 *            RUNTIME TESTS           *
 **************************************/

TYPED_TEST(Mat4x2InitializationTests, EmptyCtor_ReturnsIdentityMatrix)
{
    constexpr flcn::Mat4x2<TypeParam> matrix{};
    EXPECT_MAT_ZERO(matrix);
}


TYPED_TEST(Mat4x2InitializationTests, ParameterizedCtor_InitializesMatrixWithElements)
{
    const flcn::Mat4x2<TypeParam> matrix(this->_elements[0], this->_elements[1], this->_elements[2], this->_elements[3],
                                        this->_elements[4], this->_elements[5], this->_elements[6], this->_elements[7]);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}


TYPED_TEST(Mat4x2InitializationTests, ParameterizedCtor_InitializesMatrixWithVectors)
{
    const flcn::Mat4x2<TypeParam> matrix(this->_col0, this->_col1);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}


TYPED_TEST(Mat4x2InitializationTests, CanBeConstructedWithBracedInitialization)
{
    const flcn::Mat4x2<TypeParam> matrix = {
        { TypeParam(1), TypeParam(3), TypeParam(5), TypeParam(7) },
        { TypeParam(2), TypeParam(4), TypeParam(6), TypeParam(8) },
    };
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}

/** @} */
