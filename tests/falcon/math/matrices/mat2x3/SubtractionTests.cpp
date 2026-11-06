/**
 * @file SubtractionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 17, 2026
 *
 * @brief Verify @ref flcn::Mat2x3 subtraction logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2x3TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat2x3_Subtraction
 * @{
 */

namespace
{

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2x3 Subtraction.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2x3SubtractionTests: public ::testing::Test
    {
    protected:
        flcn::Mat2x3<T> _matA;
        flcn::Mat2x3<T> _matB;
        flcn::Mat2x3<T> _expectedDifference;

        void SetUp() override
        {
            _matA               = { flcn::CVec2<T>(5, 6), flcn::CVec2<T>(7, 8), flcn::CVec2<T>(5, 12) };
            _matB               = { flcn::CVec2<T>(1, 2), flcn::CVec2<T>(3, 4), flcn::CVec2<T>(5, 11) };
            _expectedDifference = { flcn::CVec2<T>(4, 4), flcn::CVec2<T>(4, 4), flcn::CVec2<T>(0, 1) };
        }
    };
    TYPED_TEST_SUITE(Mat2x3SubtractionTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/
    namespace static_tests
    {
        constexpr flcn::Mat2x3 MAT1(8, 2, 12, 4, -5, 0);
        constexpr flcn::Mat2x3 MAT2(5, 6, 7, 8, -11, 5);


        /** @test Verify that matrix subtraction operations return a valid matrix at compile time. */
        constexpr flcn::Mat2x3 BINARY_DIFF = MAT1 - MAT2;
        static_assert(BINARY_DIFF(0, 0) == 3);
        static_assert(BINARY_DIFF(0, 1) == -4);
        static_assert(BINARY_DIFF(0, 2) == 5);
        static_assert(BINARY_DIFF(1, 0) == -4);
        static_assert(BINARY_DIFF(1, 1) == 6);
        static_assert(BINARY_DIFF(1, 2) == -5);

    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat2x3SubtractionTests, MinusOperator_ReturnsMatrixDifference)
{
    const flcn::Mat2x3 difference = this->_matA - this->_matB;
    EXPECT_MAT_EQ(this->_expectedDifference, difference);
}


TEST(Mat2x3SubtractionTests, MinusOperator_MixedType_PromotesType)
{
    const flcn::Mat2x3 mat1(3.0f, -1.0f, 4.0f, -23.0f, 5.0f, 3.0f);
    const flcn::Mat2x3 mat2(9.0, 10.0, 3.0, 4.0, 0.1, 2.5);

    [[maybe_unused]] const flcn::Mat2x3 difference = mat1 - mat2;

    static_assert(std::is_same_v<decltype(difference)::value_type, double>);
}


TYPED_TEST(Mat2x3SubtractionTests, MinusEqualsOperator_ReturnsSameMatrixWithDifference)
{
    this->_matA -= this->_matB;
    EXPECT_MAT_EQ(this->_expectedDifference, this->_matA);
}


TEST(Mat2x3SubtractionTests, MinusEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::Mat2x3 mat1(3.0f, -1.0f, 4.0f, -23.0f, 5.0f, 3.0f);
    [[maybe_unused]] const flcn::Mat2x3 mat2(9.0, 10.0, 3.0, 4.0, 0.1, 2.5);

    mat1 -= mat2;
    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */
