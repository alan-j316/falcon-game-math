/**
 * @file SubtractionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 24, 2026
 *
 * @brief Verify @ref flcn::Mat3 subtraction logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat3x3_Subtraction
 * @{
 */

namespace
{

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat3 Subtraction.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat3SubtractionTests: public testing::Test
    {
    protected:
        flcn::Mat3<T> _matA;
        flcn::Mat3<T> _matB;
        flcn::Mat3<T> _expectedDifference;

        void SetUp() override
        {
            _matA               = { flcn::Vec3<T>{ 5, 6, 9 }, flcn::Vec3<T>{ 13, 8, 5 }, flcn::Vec3<T>{ 5, 4, 10 } };
            _matB               = { flcn::Vec3<T>{ 3, 1, 6 }, flcn::Vec3<T>{ 8, 1, 5 }, flcn::Vec3<T>{ 2, 3, 1 } };
            _expectedDifference = { flcn::Vec3<T>{ 2, 5, 3 }, flcn::Vec3<T>{ 5, 7, 0 }, flcn::Vec3<T>{ 3, 1, 9 } };
        }
    };
    TYPED_TEST_SUITE(Mat3SubtractionTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat3 MAT1{ 8, 2, 12, 4, 15, -11, 23, -55, 12 };
        constexpr flcn::Mat3 MAT2{ 80, -5, 15, 3, 1, -13, 0, 55, 38 };


        /** @test Verify that matrix subtraction operations return a valid matrix at compile time. */
        constexpr flcn::Mat3 BINARY_DIFF = MAT1 - MAT2;
        static_assert(BINARY_DIFF(0, 0) == -72);
        static_assert(BINARY_DIFF(0, 1) == 7);
        static_assert(BINARY_DIFF(0, 2) == -3);
        static_assert(BINARY_DIFF(1, 0) == 1);
        static_assert(BINARY_DIFF(1, 1) == 14);
        static_assert(BINARY_DIFF(1, 2) == 2);
        static_assert(BINARY_DIFF(2, 0) == 23);
        static_assert(BINARY_DIFF(2, 1) == -110);
        static_assert(BINARY_DIFF(2, 2) == -26);

    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat3SubtractionTests, MinusOperator_ReturnsMatrixDifference)
{
    const flcn::Mat3 difference = this->_matA - this->_matB;
    EXPECT_MAT_EQ(this->_expectedDifference, difference);
}


TEST(Mat3SubtractionTests, MinusOperator_MixedType_PromotesType)
{
    const flcn::Mat3 mat1(3.0f, -1.0f, 4.0f, -23.0f, 4.0f, 5.0f, 3.0f, 3.0f, 12.0f);
    const flcn::Mat3 mat2(9.0, 10.0, 3.0, 4.0, -1.0, 0.0, 5.0, 12.0, -22.0);

    [[maybe_unused]] const flcn::Mat3 difference = mat1 - mat2;
    static_assert(std::is_same_v<decltype(difference)::value_type, double>);
}


TYPED_TEST(Mat3SubtractionTests, MinusEqualsOperator_ReturnsSameMatrixWithDifference)
{
    this->_matA -= this->_matB;
    EXPECT_MAT_EQ(this->_expectedDifference, this->_matA);
}


TEST(Mat3SubtractionTests, MinusEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::Mat3 mat1(3.0f, -1.0f, 4.0f, -23.0f, 4.0f, 5.0f, 3.0f, 3.0f, 12.0f);
    const flcn::Mat3 mat2(9.0, 10.0, 3.0, 4.0, -1.0, 0.0, 5.0, 12.0, -22.0);

    mat1 -= mat2;
    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */
