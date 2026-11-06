/**
 * @file AdditionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 17, 2026
 *
 * @brief Verify @ref flcn::Mat2x3 addition logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2x3TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat2x3_Addition
 * @{
 */

namespace
{


    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2 Addition.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2x3AdditionTests: public testing::Test
    {
    protected:
        flcn::Mat2x3<T> _matA;
        flcn::Mat2x3<T> _matB;
        flcn::Mat2x3<T> _expectedSum;

        void SetUp() override
        {
            _matA        = { flcn::CVec2<T>(1, 2), flcn::CVec2<T>(3, 4), flcn::CVec2<T>(4, 6) };
            _matB        = { flcn::CVec2<T>(5, 6), flcn::CVec2<T>(7, 8), flcn::CVec2<T>(1, 3) };
            _expectedSum = { flcn::CVec2<T>(6, 8), flcn::CVec2<T>(10, 12), flcn::CVec2<T>(5, 9) };
        }
    };
    TYPED_TEST_SUITE(Mat2x3AdditionTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat2x3 MAT1(1, 2, 3, 4, 5, 6);
        constexpr flcn::Mat2x3 MAT2(5, 6, 7, 8, 10, 11);

        /** @test Verify that Mat2x3 addition returns a valid matrix at compile time. */
        constexpr flcn::Mat2x3 BINARY_SUM = MAT1 + MAT2;
        static_assert(BINARY_SUM(0, 0) == 6);
        static_assert(BINARY_SUM(0, 1) == 8);
        static_assert(BINARY_SUM(0, 2) == 10);
        static_assert(BINARY_SUM(1, 0) == 12);
        static_assert(BINARY_SUM(1, 1) == 15);
        static_assert(BINARY_SUM(1, 2) == 17);

    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat2x3AdditionTests, PlusOperator_ReturnsMatrixSum)
{
    const flcn::Mat2x3 sum = this->_matA + this->_matB;
    EXPECT_MAT_EQ(this->_expectedSum, sum);
}


TEST(Mat2x3AdditionTests, PlusOperator_MixedType_PromotesType)
{
    const flcn::Mat2x3 mat1{ flcn::CVec2{ 1.0f, 2.0f }, flcn::CVec2{ -3.0f, -4.0f }, flcn::CVec2{ 5.0f, 12.0f } };
    const flcn::Mat2x3 mat2{ flcn::CVec2{ 10.0, 2.0 }, flcn::CVec2{ 3.0, 8.0 }, flcn::CVec2{ -2.0, -12.0 } };
    [[maybe_unused]] const flcn::Mat2x3 sum = mat1 + mat2;

    static_assert(std::is_same_v<decltype(sum)::value_type, double>);
}


TYPED_TEST(Mat2x3AdditionTests, PlusEqualsOperator_ReturnsSameMatrixWithSum)
{
    this->_matA += this->_matB;
    EXPECT_MAT_EQ(this->_expectedSum, this->_matA);
}


TEST(Mat2x3AdditionTests, PlusEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::Mat2x3 mat1{ flcn::CVec2{ 1.0f, 2.0f }, flcn::CVec2{ -3.0f, -4.0f }, flcn::CVec2{ 5.0f, 12.0f } };
    const flcn::Mat2x3 mat2{ flcn::CVec2{ 10.0, 2.0 }, flcn::CVec2{ 3.0, 8.0 }, flcn::CVec2{ -2.0, -12.0 } };

    mat1 += mat2;
    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */
