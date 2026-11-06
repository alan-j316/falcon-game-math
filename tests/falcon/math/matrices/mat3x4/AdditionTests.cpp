/**
 * @file AdditionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 20, 2026
 *
 * @brief Verify @ref flcn::Mat3x4 addition logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3x4TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat3x4_Addition
 * @{
 */

namespace
{

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat3x4 Addition.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat3x4AdditionTests: public ::testing::Test
    {
    protected:
        flcn::Mat3x4<T> _matA;
        flcn::Mat3x4<T> _matB;
        flcn::Mat3x4<T> _expectedSum;

        void SetUp() override
        {
            _matA = { flcn::Vec3<T>(1, 2, 3), flcn::Vec3<T>(4, 5, 6), flcn::Vec3<T>(15, 12, 13), flcn::Vec3<T>(5, 11, 12) };
            _matB = { flcn::Vec3<T>(5, 6, 1), flcn::Vec3<T>(7, 8, 5), flcn::Vec3<T>(4, 5, 6), flcn::Vec3<T>(1, 1, 0) };
            _expectedSum = { flcn::Vec3<T>(6, 8, 4), flcn::Vec3<T>(11, 13, 11), flcn::Vec3<T>(19, 17, 19),
                             flcn::Vec3<T>(6, 12, 12) };
        }
    };
    TYPED_TEST_SUITE(Mat3x4AdditionTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat3x4 MAT1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
        constexpr flcn::Mat3x4 MAT2(5, 6, 7, 8, 10, 11, 12, 13, 14, 15, 16, 17);


        /// @test Verify that Mat3 can be added at compile time.
        constexpr flcn::Mat3x4 BINARY_SUM = MAT1 + MAT2;
        static_assert(BINARY_SUM(0, 0) == 6);
        static_assert(BINARY_SUM(0, 1) == 8);
        static_assert(BINARY_SUM(0, 2) == 10);
        static_assert(BINARY_SUM(0, 3) == 12);
        static_assert(BINARY_SUM(1, 0) == 15);
        static_assert(BINARY_SUM(1, 1) == 17);
        static_assert(BINARY_SUM(1, 2) == 19);
        static_assert(BINARY_SUM(1, 3) == 21);
        static_assert(BINARY_SUM(2, 0) == 23);
        static_assert(BINARY_SUM(2, 1) == 25);
        static_assert(BINARY_SUM(2, 2) == 27);
        static_assert(BINARY_SUM(2, 3) == 29);

    } // namespace static_tests

} // namespace


/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat3x4AdditionTests, PlusOperator_ReturnsMatrixSum)
{
    const flcn::Mat3x4 sum = this->_matA + this->_matB;

    EXPECT_MAT_EQ(this->_expectedSum, sum);
}


TEST(Mat3x4AdditionTests, PlusOperator_MixedType_PromotesType)
{
    const flcn::Mat3x4 mat1{ flcn::Vec3{ 1.0f, 2.0f, 3.0f }, flcn::Vec3{ -3.0f, -4.0f, 12.0f },
                            flcn::Vec3{ 13.0f, -14.0f, 1.0f }, flcn::Vec3{ 3.0f, -4.0f, 0.0f } };
    const flcn::Mat3x4 mat2{
        flcn::Vec3{ 10.0, 2.0, 2.5 },
        flcn::Vec3{ 1.0, 12.0, 22.5 },
        flcn::Vec3{ 1.0, 9.0, 25.0 },
        flcn::Vec3{ 3.0, 8.0, 3.5 },
    };

    [[maybe_unused]] const flcn::Mat3x4 sum = mat1 + mat2;
    static_assert(std::is_same_v<decltype(sum)::value_type, double>);
}


TYPED_TEST(Mat3x4AdditionTests, PlusEqualsOperator_ReturnsSameMatrixWithSum)
{
    this->_matA += this->_matB;
    EXPECT_MAT_EQ(this->_expectedSum, this->_matA);
}


TEST(Mat3x4AdditionTests, PlusEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::Mat3x4 mat1{ flcn::Vec3{ 1.0f, 2.0f, 3.0f }, flcn::Vec3{ -3.0f, -4.0f, 12.0f }, flcn::Vec3{ 13.0f, -14.0f, 1.0f },
                      flcn::Vec3{ 3.0f, -4.0f, 0.0f } };
    const flcn::Mat3x4 mat2{
        flcn::Vec3{ 10.0, 2.0, 2.5 },
        flcn::Vec3{ 1.0, 12.0, 22.5 },
        flcn::Vec3{ 1.0, 9.0, 25.0 },
        flcn::Vec3{ 3.0, 8.0, 3.5 },
    };

    mat1 += mat2;
    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */
