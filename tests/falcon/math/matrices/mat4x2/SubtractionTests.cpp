/**
 * @file SubtractionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref flcn::Mat4x2 subtraction logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4x2TestSetup.h"




/**
 * @addtogroup T_FALCON_Mat4x2_Subtraction
 * @{
 */

namespace
{

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4x2 Subtraction.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat4x2SubtractionTests: public testing::Test
    {
    protected:
        flcn::Mat4x2<T> _matA;
        flcn::Mat4x2<T> _matB;
        flcn::Mat4x2<T> _expectedDifference;

        void SetUp() override
        {
            _matA               = { flcn::Vec4<T>(5, 6, 5, 7), flcn::Vec4<T>(7, 8, 12, 21) };
            _matB               = { flcn::Vec4<T>(1, 2, 5, 5), flcn::Vec4<T>(3, 4, 11, 12) };
            _expectedDifference = { flcn::Vec4<T>(4, 4, 0, 2), flcn::Vec4<T>(4, 4, 1, 9) };
        }
    };
    TYPED_TEST_SUITE(Mat4x2SubtractionTests, SupportedArithmeticTypes);


    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat4x2 MAT1(8, 2, 12, 4, -5, 0, -1, 0);
        constexpr flcn::Mat4x2 MAT2(5, 6, 7, 8, -11, 5, 5, -32);
        constexpr flcn::Mat4x2 BINARY_DIFF = MAT1 - MAT2;

        /** @test Verify that matrix subtraction operations return a valid matrix at compile time. */
        static_assert(BINARY_DIFF(0, 0) == 3);
        static_assert(BINARY_DIFF(0, 1) == -4);
        static_assert(BINARY_DIFF(1, 0) == 5);
        static_assert(BINARY_DIFF(1, 1) == -4);
        static_assert(BINARY_DIFF(2, 0) == 6);
        static_assert(BINARY_DIFF(2, 1) == -5);
        static_assert(BINARY_DIFF(3, 0) == -6);
        static_assert(BINARY_DIFF(3, 1) == 32);

    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat4x2SubtractionTests, MinusOperator_ReturnsMatrixDifference)
{
    const flcn::Mat4x2 difference = this->_matA - this->_matB;

    EXPECT_MAT_EQ(this->_expectedDifference, difference);
}


TEST(Mat4x2SubtractionTests, MinusOperator_MixedType_PromotesType)
{
    const flcn::Mat4x2 mat1(3.0f, -1.0f, 4.0f, -23.0f, 5.0f, 3.0f, 1.5f, 2.0f);
    const flcn::Mat4x2 mat2(9.0, 10.0, 3.0, 4.0, 0.1, 2.5, 1.0, 2.25);

    [[maybe_unused]] const flcn::Mat4x2 difference = mat1 - mat2;

    static_assert(std::is_same_v<decltype(difference)::value_type, double>);
}


TYPED_TEST(Mat4x2SubtractionTests, MinusEqualsOperator_ReturnsSameVectorWithDifference)
{
    this->_matA -= this->_matB;

    EXPECT_MAT_EQ(this->_expectedDifference, this->_matA);
}


TEST(Mat4x2SubtractionTests, MinusEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::Mat4x2 mat1(3.0f, -1.0f, 4.0f, -23.0f, 5.0f, 3.0f, 1.5f, 2.0f);
    [[maybe_unused]] const flcn::Mat4x2 mat2(9.0, 10.0, 3.0, 4.0, 0.1, 2.5, 1.0, 2.25);

    mat1 -= mat2;

    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */
