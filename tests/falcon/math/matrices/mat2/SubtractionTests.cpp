/**
 * @file SubtractionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 09, 2026
 *
 * @brief Verify @ref flcn::Mat2 subtraction logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat2x2_Subtraction
 * @{
 */

namespace
{

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2 Subtraction.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2SubtractionTests: public ::testing::Test
    {
    protected:
        flcn::Mat2<T> _matA;
        flcn::Mat2<T> _matB;
        flcn::Mat2<T> _expectedDifference;

        void SetUp() override
        {
            _matA               = { flcn::CVec2<T>(5, 6), flcn::CVec2<T>(7, 8) };
            _matB               = { flcn::CVec2<T>(1, 2), flcn::CVec2<T>(3, 4) };
            _expectedDifference = { flcn::CVec2<T>(4, 4), flcn::CVec2<T>(4, 4) };
        }
    };
    TYPED_TEST_SUITE(Mat2SubtractionTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat2 MAT1(8, 2, 12, 4);
        constexpr flcn::Mat2 MAT2(5, 6, 7, 8);
        constexpr flcn::Mat2 BINARY_DIFF = MAT1 - MAT2;

        /** @test Verify that matrix subtraction operations return a valid matrix at compile time. */
        static_assert(BINARY_DIFF(0, 0) == 3);
        static_assert(BINARY_DIFF(0, 1) == -4);
        static_assert(BINARY_DIFF(1, 0) == 5);
        static_assert(BINARY_DIFF(1, 1) == -4);

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat2SubtractionTests, MinusOperator_ReturnsMatrixDifference)
{
    const flcn::Mat2 difference = this->_matA - this->_matB;

    EXPECT_MAT_EQ(this->_expectedDifference, difference);
}


TEST(Mat2SubtractionTests, MinusOperator_MixedType_PromotesType)
{
    const flcn::Mat2 mat1(3.0f, -1.0f, 4.0f, -23.0f);
    const flcn::Mat2 mat2(9.0, 10.0, 3.0, 4.0);

    [[maybe_unused]] const flcn::Mat2 difference = mat1 - mat2;

    static_assert(std::is_same_v<decltype(difference)::value_type, double>);
}


TYPED_TEST(Mat2SubtractionTests, MinusEqualsOperator_ReturnsSameMatrixWithDifference)
{
    this->_matA -= this->_matB;
    EXPECT_MAT_EQ(this->_expectedDifference, this->_matA);
}


TEST(Mat2SubtractionTests, MinusEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::Mat2 mat1(3.0f, -1.0f, 4.0f, -23.0f);
    const flcn::Mat2 mat2(9.0, 10.0, 3.0, 4.0);

    mat1 -= mat2;
    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */
