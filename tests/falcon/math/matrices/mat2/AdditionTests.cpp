/**
 * @file AdditionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 09, 2026
 *
 * @brief Verify @ref flcn::Mat2 addition logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2TestSetup.h"

/**
 * @addtogroup T_FALCON_Mat2x2_Addition
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
    class Mat2AdditionTests: public ::testing::Test
    {
    protected:
        flcn::Mat2<T> _matA;
        flcn::Mat2<T> _matB;
        flcn::Mat2<T> _expectedSum;

        void SetUp() override
        {
            _matA        = { flcn::CVec2<T>(1, 2), flcn::CVec2<T>(3, 4) };
            _matB        = { flcn::CVec2<T>(5, 6), flcn::CVec2<T>(7, 8) };
            _expectedSum = { flcn::CVec2<T>(6, 8), flcn::CVec2<T>(10, 12) };
        }
    };
    TYPED_TEST_SUITE(Mat2AdditionTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat2 MAT1(1, 2, 3, 4);
        constexpr flcn::Mat2 MAT2(5, 6, 7, 8);

        /// @test Verify that Mat2 can be added at compile time.
        constexpr flcn::Mat2 BINARY_SUM = MAT1 + MAT2;
        static_assert(BINARY_SUM(0, 0) == 6);
        static_assert(BINARY_SUM(0, 1) == 8);
        static_assert(BINARY_SUM(1, 0) == 10);
        static_assert(BINARY_SUM(1, 1) == 12);

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat2AdditionTests, PlusOperator_ReturnsMatrixSum)
{
    const flcn::Mat2 sum = this->_matA + this->_matB;
    EXPECT_MAT_EQ(this->_expectedSum, sum);
}


TEST(Mat2AdditionTests, PlusOperator_MixedType_PromotesType)
{
    const flcn::Mat2 mat1{ flcn::CVec2{ 1.0f, 2.0f }, flcn::CVec2{ -3.0f, -4.0f } };
    const flcn::Mat2 mat2{ flcn::CVec2{ 10.0, 2.0 }, flcn::CVec2{ 3.0, 8.0 } };
    [[maybe_unused]] const flcn::Mat2 sum = mat1 + mat2;

    static_assert(std::is_same_v<decltype(sum)::value_type, double>);
}


TYPED_TEST(Mat2AdditionTests, PlusEqualsOperator_ReturnsSameMatrixWithSum)
{
    this->_matA += this->_matB;
    EXPECT_MAT_EQ(this->_expectedSum, this->_matA);
}


TEST(Mat2AdditionTests, PlusEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::Mat2 mat1{ flcn::CVec2{ 1.0f, 2.0f }, flcn::CVec2{ -3.0f, -4.0f } };
    const flcn::Mat2 mat2{ flcn::CVec2{ 10.0, 2.0 }, flcn::CVec2{ 3.0, 8.0 } };

    mat1 += mat2;
    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */
