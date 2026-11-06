/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 18, 2026
 *
 * @brief Verify @ref flcn::Mat2x4 initialization.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2x4TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat2x4_Init
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2x4 initialization.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2x4InitializationTests: public testing::Test
    {
    protected:
        std::vector<T> _elements;
        flcn::CVec2<T> _col0, _col1, _col2, _col3;

        void SetUp() override
        {
            _elements = { T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8) };
            _col0     = { T(1), T(5) };
            _col1     = { T(2), T(6) };
            _col2     = { T(3), T(7) };
            _col3     = { T(4), T(8) };
        }
    };
    TYPED_TEST_SUITE(Mat2x4InitializationTests, SupportedTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that the matrix can be initialized at compile time using scalar values.
        constexpr flcn::Mat2x4 MAT1(1, 2, 3, 4, 5, 6, 7, 8);
        static_assert(MAT1(0, 0) == 1);
        static_assert(MAT1(0, 1) == 2);
        static_assert(MAT1(0, 2) == 3);
        static_assert(MAT1(0, 3) == 4);
        static_assert(MAT1(1, 0) == 5);
        static_assert(MAT1(1, 1) == 6);
        static_assert(MAT1(1, 2) == 7);
        static_assert(MAT1(1, 3) == 8);


        /// @test Verify that the matrix can be initialized at compile time using column vectors.
        constexpr flcn::Mat2x4 MAT2(flcn::CVec2(1, 5), flcn::CVec2(2, 6), flcn::CVec2(3, 7), flcn::CVec2(4, 8));
        static_assert(MAT2(0, 0) == 1);
        static_assert(MAT2(0, 1) == 2);
        static_assert(MAT2(0, 2) == 3);
        static_assert(MAT2(0, 3) == 4);
        static_assert(MAT2(1, 0) == 5);
        static_assert(MAT2(1, 1) == 6);
        static_assert(MAT2(1, 2) == 7);
        static_assert(MAT2(1, 3) == 8);



        /// @test Verify that the matrix can be initialized at compile time using value initialization.
        constexpr flcn::Mat2x4<int> MAT4{};
        static_assert(MAT4(0, 0) == 0);
        static_assert(MAT4(0, 1) == 0);
        static_assert(MAT4(0, 2) == 0);
        static_assert(MAT4(0, 3) == 0);
        static_assert(MAT4(1, 0) == 0);
        static_assert(MAT4(1, 1) == 0);
        static_assert(MAT4(1, 2) == 0);
        static_assert(MAT4(1, 3) == 0);

    } // namespace static_tests
} // namespace




/**************************************
 *            RUNTIME TESTS           *
 **************************************/

TYPED_TEST(Mat2x4InitializationTests, EmptyCtor_ReturnsIdentityMatrix)
{
    constexpr flcn::Mat2x4<TypeParam> matrix{};

    EXPECT_MAT_ZERO(matrix);
}


TYPED_TEST(Mat2x4InitializationTests, ParameterizedCtor_InitializesMatrixWithElements)
{
    const flcn::Mat2x4<TypeParam> matrix(this->_elements[0], this->_elements[1], this->_elements[2], this->_elements[3],
                                        this->_elements[4], this->_elements[5], this->_elements[6], this->_elements[7]);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}


TYPED_TEST(Mat2x4InitializationTests, ParameterizedCtor_InitializesMatrixWithVectors)
{
    const flcn::Mat2x4<TypeParam> matrix(this->_col0, this->_col1, this->_col2, this->_col3);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}



TYPED_TEST(Mat2x4InitializationTests, CanBeConstructedWithBracedInitialization)
{
    const flcn::Mat2x4<TypeParam> matrix = {
        { TypeParam(1), TypeParam(5) },
        { TypeParam(2), TypeParam(6) },
        { TypeParam(3), TypeParam(7) },
        { TypeParam(4), TypeParam(8) },
    };
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}

/** @} */
