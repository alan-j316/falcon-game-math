/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 17, 2026
 *
 * @brief Verify @ref flcn::Mat2x3 initialization.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2x3TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat2x3_Init
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2x3 initialization.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2x3InitializationTests: public testing::Test
    {
    protected:
        std::vector<T> _elements;
        flcn::CVec2<T> _col0, _col1, _col2;

        void SetUp() override
        {
            _elements = { T(1), T(2), T(3), T(4), T(5), T(6) };
            _col0     = { T(1), T(4) };
            _col1     = { T(2), T(5) };
            _col2     = { T(3), T(6) };
        }
    };
    TYPED_TEST_SUITE(Mat2x3InitializationTests, SupportedTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that the matrix can be initialized at compile time using scalar values.
        constexpr flcn::Mat2x3 MAT1(1, 2, 3, 4, 5, 6);
        static_assert(MAT1(0, 0) == 1);
        static_assert(MAT1(0, 1) == 2);
        static_assert(MAT1(0, 2) == 3);
        static_assert(MAT1(1, 0) == 4);
        static_assert(MAT1(1, 1) == 5);
        static_assert(MAT1(1, 2) == 6);


        /// @test Verify that the matrix can be initialized at compile time using column vectors.
        constexpr flcn::Mat2x3 MAT2(flcn::CVec2(1, 4), flcn::CVec2(2, 5), flcn::CVec2(3, 6));
        static_assert(MAT2(0, 0) == 1);
        static_assert(MAT2(0, 1) == 2);
        static_assert(MAT2(0, 2) == 3);
        static_assert(MAT2(1, 0) == 4);
        static_assert(MAT2(1, 1) == 5);
        static_assert(MAT2(1, 2) == 6);


        /// @test Verify that the matrix can be initialized at compile time using value initialization.
        constexpr flcn::Mat2x3<int> MAT4{};
        static_assert(MAT4(0, 0) == 0);
        static_assert(MAT4(0, 1) == 0);
        static_assert(MAT4(0, 2) == 0);
        static_assert(MAT4(1, 0) == 0);
        static_assert(MAT4(1, 1) == 0);
        static_assert(MAT4(1, 2) == 0);

    } // namespace static_tests

} // namespace



/**************************************
 *            RUNTIME TESTS           *
 **************************************/

TYPED_TEST(Mat2x3InitializationTests, EmptyCtor_ReturnsIdentityMatrix)
{
    constexpr flcn::Mat2x3<TypeParam> matrix{};
    EXPECT_MAT_ZERO(matrix);
}


TYPED_TEST(Mat2x3InitializationTests, ParameterizedCtor_InitializesMatrixWithElements)
{
    const flcn::Mat2x3<TypeParam> matrix(this->_elements[0], this->_elements[1], this->_elements[2], this->_elements[3],
                                        this->_elements[4], this->_elements[5]);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}


TYPED_TEST(Mat2x3InitializationTests, ParameterizedCtor_InitializesMatrixWithVectors)
{
    const flcn::Mat2x3<TypeParam> matrix(this->_col0, this->_col1, this->_col2);
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}


TYPED_TEST(Mat2x3InitializationTests, CanBeConstructedWithBracedInitialization)
{
    const flcn::Mat2x3<TypeParam> matrix = {
        { TypeParam(1), TypeParam(4) },
        { TypeParam(2), TypeParam(5) },
        { TypeParam(3), TypeParam(6) },
    };
    EXPECT_MAT_CONTAINS(this->_elements, matrix);
}

/** @} */
