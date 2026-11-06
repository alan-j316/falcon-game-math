/**
 * @file SubtractionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 18, 2026
 *
 * @brief Verify @ref flcn::Mat3x4 subtraction logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3x4TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat3x4_Subtraction
 * @{
 */

namespace
{

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat3x4 Subtraction.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat3x4SubtractionTests: public ::testing::Test
    {
    protected:
        flcn::Mat3x4<T> _matA;
        flcn::Mat3x4<T> _matB;
        flcn::Mat3x4<T> _expectedDifference;

        void SetUp() override
        {
            _matA = { flcn::Vec3<T>(5, 6, 5), flcn::Vec3<T>(7, 8, 12), flcn::Vec3<T>(17, 81, 22),
                      flcn::Vec3<T>(22, 32, 11) };
            _matB = { flcn::Vec3<T>(1, 2, 5), flcn::Vec3<T>(3, 4, 11), flcn::Vec3<T>(0, 1, 19), flcn::Vec3<T>(21, 14, 11) };
            _expectedDifference = { flcn::Vec3<T>(4, 4, 0), flcn::Vec3<T>(4, 4, 1), flcn::Vec3<T>(17, 80, 3),
                                    flcn::Vec3<T>(1, 18, 0) };
        }
    };
    TYPED_TEST_SUITE(Mat3x4SubtractionTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat3x4 MAT1(8, 2, 12, 4, -5, 0, -12, 5, 11, 23, 11, 5);
        constexpr flcn::Mat3x4 MAT2(5, 6, 7, 8, -11, 5, -12, -5, 0, 2, -1, -3);


        /** @test Verify that matrix subtraction operations return a valid matrix at compile time. */
        constexpr flcn::Mat3x4 BINARY_DIFF = MAT1 - MAT2;
        static_assert(BINARY_DIFF(0, 0) == 3);
        static_assert(BINARY_DIFF(0, 1) == -4);
        static_assert(BINARY_DIFF(0, 2) == 5);
        static_assert(BINARY_DIFF(0, 3) == -4);
        static_assert(BINARY_DIFF(1, 0) == 6);
        static_assert(BINARY_DIFF(1, 1) == -5);
        static_assert(BINARY_DIFF(1, 2) == 0);
        static_assert(BINARY_DIFF(1, 3) == 10);
        static_assert(BINARY_DIFF(2, 0) == 11);
        static_assert(BINARY_DIFF(2, 1) == 21);
        static_assert(BINARY_DIFF(2, 2) == 12);
        static_assert(BINARY_DIFF(2, 3) == 8);

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/
TYPED_TEST(Mat3x4SubtractionTests, MinusOperator_ReturnsMatrixDifference)
{
    const flcn::Mat3x4 difference = this->_matA - this->_matB;

    EXPECT_MAT_EQ(this->_expectedDifference, difference);
}


TEST(Mat3x4SubtractionTests, MinusOperator_MixedType_PromotesType)
{
    const flcn::Mat3x4 mat1(3.0f, -1.0f, 4.0f, -23.0f, 5.0f, 3.0f, 1.2f, 2.25f, 3.0f, 15.0f, 22.0f, 1.0f);
    const flcn::Mat3x4 mat2(9.0, 10.0, 3.0, 4.0, 0.1, 2.5, 0.5, 1.25, 22.0, 3.15, 15.0, 11.0);

    [[maybe_unused]] const flcn::Mat3x4 difference = mat1 - mat2;

    static_assert(std::is_same_v<decltype(difference)::value_type, double>);
}


TYPED_TEST(Mat3x4SubtractionTests, MinusEqualsOperator_ReturnsSameVectorWithDifference)
{
    this->_matA -= this->_matB;

    EXPECT_MAT_EQ(this->_expectedDifference, this->_matA);
}


TEST(Mat3x4SubtractionTests, MinusEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::Mat3x4 mat1(3.0f, -1.0f, 4.0f, -23.0f, 5.0f, 3.0f, 1.2f, 2.25f, 3.0f, 15.0f, 22.0f, 1.0f);
    [[maybe_unused]] const flcn::Mat3x4 mat2(9.0, 10.0, 3.0, 4.0, 0.1, 2.5, 0.5, 1.25, 22.0, 3.15, 15.0, 11.0);

    mat1 -= mat2;

    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */
