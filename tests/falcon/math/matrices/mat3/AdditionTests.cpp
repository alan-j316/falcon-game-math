/**
 * @file AdditionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 24, 2026
 *
 * @brief Verify @ref flcn::Mat3 addition logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat3x3_Addition
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat3 Addition.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat3AdditionTests: public ::testing::Test
    {
    protected:
        flcn::Mat3<T> _matA;
        flcn::Mat3<T> _matB;
        flcn::Mat3<T> _expectedSum;

        void SetUp() override
        {
            _matA        = { flcn::Vec3<T>{ 1, 2, 3 }, flcn::Vec3<T>{ 4, 5, 6 }, flcn::Vec3<T>{ 7, 8, 9 } };
            _matB        = { flcn::Vec3<T>{ 10, 11, 12 }, flcn::Vec3<T>{ 13, 14, 15 }, flcn::Vec3<T>{ 16, 17, 18 } };
            _expectedSum = { flcn::Vec3<T>{ 11, 13, 15 }, flcn::Vec3<T>{ 17, 19, 21 }, flcn::Vec3<T>{ 23, 25, 27 } };
        }
    };
    TYPED_TEST_SUITE(Mat3AdditionTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat3 MAT1(1, 2, 3, 4, 5, 6, 7, 8, 9);
        constexpr flcn::Mat3 MAT2(5, 6, 7, 8, 9, 10, 11, 12, 13);

        /// @test Verify that Mat3 can be added at compile time.
        constexpr flcn::Mat3 BINARY_SUM = MAT1 + MAT2;
        static_assert(BINARY_SUM(0, 0) == 6);
        static_assert(BINARY_SUM(0, 1) == 8);
        static_assert(BINARY_SUM(0, 2) == 10);
        static_assert(BINARY_SUM(1, 0) == 12);
        static_assert(BINARY_SUM(1, 1) == 14);
        static_assert(BINARY_SUM(1, 2) == 16);
        static_assert(BINARY_SUM(2, 0) == 18);
        static_assert(BINARY_SUM(2, 1) == 20);
        static_assert(BINARY_SUM(2, 2) == 22);

    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat3AdditionTests, PlusOperator_ReturnsMatrixSum)
{
    const flcn::Mat3 sum = this->_matA + this->_matB;
    EXPECT_MAT_EQ(this->_expectedSum, sum);
}


TEST(Mat3AdditionTests, PlusOperator_MixedType_PromotesType)
{
    const flcn::Mat3 mat1{ flcn::Vec3{ 1.0f, 2.0f, 3.0f }, flcn::Vec3{ -3.0f, -4.0f, 10.0f },
                          flcn::Vec3{ 4.5f, 3.25f, 3.16f } };
    const flcn::Mat3 mat2{ flcn::Vec3{ 10.0, 2.0, -1.0 }, flcn::Vec3{ 3.0, -8.0, 12.0 }, flcn::Vec3{ 3.25, 5.1, 0.0 } };

    [[maybe_unused]] const flcn::Mat3 sum = mat1 + mat2;
    static_assert(std::is_same_v<decltype(sum)::value_type, double>);
}


TYPED_TEST(Mat3AdditionTests, PlusEqualsOperator_ReturnsSameMatrixWithSum)
{
    this->_matA += this->_matB;
    EXPECT_MAT_EQ(this->_expectedSum, this->_matA);
}


TEST(Mat3AdditionTests, PlusEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::Mat3 mat1{ flcn::Vec3{ 1.0f, 2.0f, 3.0f }, flcn::Vec3{ -3.0f, -4.0f, 10.0f }, flcn::Vec3{ 4.5f, 3.25f, 3.16f } };
    constexpr flcn::Mat3 mat2{ flcn::Vec3{ 10.0, 2.0, -1.0 }, flcn::Vec3{ 3.0, -8.0, 12.0 }, flcn::Vec3{ 3.25, 5.1, 0.0 } };

    mat1 += mat2;
    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */
