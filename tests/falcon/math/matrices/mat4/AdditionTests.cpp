/**
 * @file AdditionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 04, 2026
 *
 * @brief Verify @ref flcn::Mat4 addition logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat4x4_Addition
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4 Addition.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat4AdditionTests: public testing::Test
    {
    protected:
        flcn::Mat4<T> _matA;
        flcn::Mat4<T> _matB;
        flcn::Mat4<T> _expectedSum;

        void SetUp() override
        {
            _matA        = { { T(1), T(2), T(3), T(4) },
                             { T(5), T(6), T(7), T(8) },
                             { T(9), T(10), T(11), T(12) },
                             { T(13), T(14), T(15), T(16) } };
            _matB        = { { T(10), T(20), T(30), T(40) },
                             { T(50), T(60), T(70), T(80) },
                             { T(90), T(100), T(110), T(100) },
                             { T(12), T(13), T(14), T(14) } };
            _expectedSum = {
                { T(11), T(22), T(33), T(44) },
                { T(55), T(66), T(77), T(88) },
                { T(99), T(110), T(121), T(112) },
                { T(25), T(27), T(29), T(30) },
            };
        }
    };
    TYPED_TEST_SUITE(Mat4AdditionTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat4 MATA(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        constexpr flcn::Mat4 MATB(5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20);

        /// @test Verify that Mat4 can be added at compile time.
        constexpr flcn::Mat4 BINARY_SUM = MATA + MATB;
        static_assert(BINARY_SUM(0, 0) == 6);
        static_assert(BINARY_SUM(0, 1) == 8);
        static_assert(BINARY_SUM(0, 2) == 10);
        static_assert(BINARY_SUM(0, 3) == 12);
        static_assert(BINARY_SUM(1, 0) == 14);
        static_assert(BINARY_SUM(1, 1) == 16);
        static_assert(BINARY_SUM(1, 2) == 18);
        static_assert(BINARY_SUM(1, 3) == 20);
        static_assert(BINARY_SUM(2, 0) == 22);
        static_assert(BINARY_SUM(2, 1) == 24);
        static_assert(BINARY_SUM(2, 2) == 26);
        static_assert(BINARY_SUM(2, 3) == 28);
        static_assert(BINARY_SUM(3, 0) == 30);
        static_assert(BINARY_SUM(3, 1) == 32);
        static_assert(BINARY_SUM(3, 2) == 34);
        static_assert(BINARY_SUM(3, 3) == 36);

    } // namespace static_tests
} // namespace


/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat4AdditionTests, PlusOperator_ReturnsMatrixSum)
{
    const flcn::Mat4 sum = this->_matA + this->_matB;

    EXPECT_MAT_EQ(this->_expectedSum, sum);
}


TEST(Mat4AdditionTests, PlusOperator_MixedType_PromotesType)
{
    constexpr flcn::Mat4 mat1{ flcn::Vec4{ 1.0f, 2.0f, 3.0f, 7.5f }, flcn::Vec4{ -3.0f, -4.0f, 10.0f, -11.0f },
                              flcn::Vec4{ 4.5f, 3.25f, 3.16f, -22.0f }, flcn::Vec4{ 15.0f, 32.0f, 101.0f, 12.5f } };
    constexpr flcn::Mat4 mat2{ flcn::Vec4{ 11.0, 10.0, 2.0, -1.0 }, flcn::Vec4{ 3.0, -8.0, 12.0, 11.0 },
                              flcn::Vec4{ 3.25, 5.1, 0.0, 0.25 }, flcn::Vec4{ 12.0, 13.0, 14.0, 15.0 } };

    [[maybe_unused]] constexpr flcn::Mat4 sum = mat1 + mat2;
    static_assert(std::is_same_v<decltype(sum)::value_type, double>);
}


TYPED_TEST(Mat4AdditionTests, PlusEqualsOperator_ReturnsSameMatrixWithSum)
{
    this->_matA += this->_matB;
    EXPECT_MAT_EQ(this->_expectedSum, this->_matA);
}


TEST(Mat4AdditionTests, PlusEqualsOperator_MixedType_DoesNotPromoteType)
{
    [[maybe_unused]] flcn::Mat4 mat1{ flcn::Vec4{ 1.0f, 2.0f, 3.0f, 7.5f }, flcn::Vec4{ -3.0f, -4.0f, 10.0f, -11.0f },
                                     flcn::Vec4{ 4.5f, 3.25f, 3.16f, -22.0f },
                                     flcn::Vec4{ 15.0f, 32.0f, 101.0f, 12.5f } };
    [[maybe_unused]] constexpr flcn::Mat4 mat2{ flcn::Vec4{ 11.0, 10.0, 2.0, -1.0 }, flcn::Vec4{ 3.0, -8.0, 12.0, 11.0 },
                                               flcn::Vec4{ 3.25, 5.1, 0.0, 0.25 }, flcn::Vec4{ 12.0, 13.0, 14.0, 15.0 } };

    (void) (mat1 += mat2);
    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */
