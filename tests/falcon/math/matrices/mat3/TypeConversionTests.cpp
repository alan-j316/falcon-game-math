/**
 * @file TypeConversionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref flcn::Mat3 conversion constructor logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat3x3_Type_Conv
 * @{
 */

namespace
{
    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat3 MAT(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);


        /// @test Verify that the matrix can be type promoted at compile time.
        constexpr flcn::Mat3<double> MAT_D(MAT);
        static_assert(std::is_same_v<decltype(MAT_D)::value_type, double>);

        /// @test Verify that the matrix can be type demoted at compile time.
        constexpr flcn::Mat3<int> MATI(MAT);
        static_assert(std::is_same_v<decltype(MATI)::value_type, int>);
    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TEST(Mat3TypeConversionTests, ConversionCtor_PromotesType)
{
    const flcn::Mat3 mat1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    [[maybe_unused]] const flcn::Mat3<double> mat2(mat1);
    static_assert(std::is_same_v<decltype(mat2)::value_type, double>);
}


TEST(Mat3TypeConversionTests, ConversionCtor_ReturnsNewInstance)
{
    // Given a float matrix
    const flcn::Mat3 mat1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

    // When converted to a double matrix
    flcn::Mat3<double> mat2(mat1);
    // And one of its value mutated
    mat2(0, 0) = 5;

    // Then, the float matrix remains unchanged
    EXPECT_MAT_CONTAINS(std::vector{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f }, mat1);

    // And, the new matrix is of type double with the mutated value
    EXPECT_MAT_CONTAINS(std::vector{ 5.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 }, mat2);
}


TEST(Mat3TypeConversionTests, ConversionCtor_DemotesType)
{
    const flcn::Mat3 mat1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
    [[maybe_unused]] const flcn::Mat3<float> mat2(mat1);
    static_assert(std::is_same_v<decltype(mat2)::value_type, float>);
}

/** @} */
