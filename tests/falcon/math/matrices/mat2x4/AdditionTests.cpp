/**
 * @file AdditionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 18, 2026
 *
 * @brief Verify @ref flcn::Mat2x4 addition logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2x4TestSetup.h"

/**
 * @addtogroup T_Falcon_Mat2x4_Addition
 * @{
 */

namespace
{

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2x4 Addition.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2x4AdditionTests: public ::testing::Test
    {
    protected:
        flcn::Mat2x4<T> _matA;
        flcn::Mat2x4<T> _matB;
        flcn::Mat2x4<T> _expectedSum;

        void SetUp() override
        {
            _matA        = { flcn::Vec2<T>(1, 2), flcn::Vec2<T>(3, 4), flcn::Vec2<T>(4, 6), flcn::Vec2<T>(1, 2) };
            _matB        = { flcn::Vec2<T>(5, 6), flcn::Vec2<T>(7, 8), flcn::Vec2<T>(1, 3), flcn::Vec2<T>(3, 2) };
            _expectedSum = { flcn::Vec2<T>(6, 8), flcn::Vec2<T>(10, 12), flcn::Vec2<T>(5, 9), flcn::Vec2<T>(4, 4) };
        }
    };
    TYPED_TEST_SUITE(Mat2x4AdditionTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/
    namespace static_tests
    {
        constexpr flcn::Mat2x4 MAT1(1, 2, 3, 4, 5, 6, 7, 8);
        constexpr flcn::Mat2x4 MAT2(5, 6, 7, 8, 10, 11, 12, 13);

        /// @test Verify that Mat2 can be added at compile time.
        constexpr flcn::Mat2x4 BINARY_SUM = MAT1 + MAT2;
        static_assert(BINARY_SUM(0, 0) == 6);
        static_assert(BINARY_SUM(0, 1) == 8);
        static_assert(BINARY_SUM(0, 2) == 10);
        static_assert(BINARY_SUM(0, 3) == 12);
        static_assert(BINARY_SUM(1, 0) == 15);
        static_assert(BINARY_SUM(1, 1) == 17);
        static_assert(BINARY_SUM(1, 2) == 19);
        static_assert(BINARY_SUM(1, 3) == 21);

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat2x4AdditionTests, PlusOperator_ReturnsMatrixSum)
{
    const flcn::Mat2x4 sum = this->_matA + this->_matB;
    EXPECT_MAT_EQ(this->_expectedSum, sum);
}


TEST(Mat2x4AdditionTests, PlusOperator_MixedType_PromotesType)
{
    const flcn::Mat2x4 mat1{ flcn::Vec2{ 1.0f, 2.0f }, flcn::Vec2{ -3.0f, -4.0f }, flcn::Vec2{ 5.0f, 12.0f },
                            flcn::Vec2{ 2.0f, 8.0f } };
    const flcn::Mat2x4 mat2{ flcn::Vec2{ 10.0, 2.0 }, flcn::Vec2{ 3.0, 8.0 }, flcn::Vec2{ -2.0, -12.0 },
                            flcn::Vec2{ 13.0, 3.0 } };
    [[maybe_unused]] const flcn::Mat2x4 sum = mat1 + mat2;

    static_assert(std::is_same_v<decltype(sum)::value_type, double>);
}


TYPED_TEST(Mat2x4AdditionTests, PlusEqualsOperator_ReturnsSameMatrixWithSum)
{
    this->_matA += this->_matB;
    EXPECT_MAT_EQ(this->_expectedSum, this->_matA);
}


TEST(Mat2x4AdditionTests, PlusEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::Mat2x4 mat1{ flcn::Vec2{ 1.0f, 2.0f }, flcn::Vec2{ -3.0f, -4.0f }, flcn::Vec2{ 5.0f, 12.0f },
                      flcn::Vec2{ 3.0f, 1.0f } };
    const flcn::Mat2x4 mat2{ flcn::Vec2{ 10.0, 2.0 }, flcn::Vec2{ 3.0, 8.0 }, flcn::Vec2{ -2.0, -12.0 },
                            flcn::Vec2{ 1.0, 6.0 } };

    mat1 += mat2;
    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */
