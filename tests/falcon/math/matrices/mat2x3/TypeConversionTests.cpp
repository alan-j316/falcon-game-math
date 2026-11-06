/**
 * @file TypeConversionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 18, 2026
 *
 * @brief Verify @ref flcn::Mat2x3 conversion constructor logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2x3TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat2x3_Type_Conv
 * @{
 */

namespace
{
    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat2x3 MAT(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);

        // Verify that the matrix can be type promoted at compile time.
        constexpr flcn::Mat2x3<double> MAT_D(MAT);
        static_assert(std::is_same_v<decltype(MAT_D)::value_type, double>);

        // Verify that the matrix can be type demoted at compile time.
        constexpr flcn::Mat2x3<int> MATI(MAT);
        static_assert(std::is_same_v<decltype(MATI)::value_type, int>);

    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TEST(Mat2x3ConversionConstructorTests, ConversionCtor_CanPromoteType)
{
    const flcn::Mat2x3 mat1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);

    [[maybe_unused]] const flcn::Mat2x3<double> mat2(mat1);
    static_assert(std::is_same_v<decltype(mat2)::value_type, double>);
}


TEST(Mat2x3ConversionConstructorTests, ConversionCtor_ReturnsNewInstance)
{
    // Given a float matrix
    const flcn::Mat2x3 mat1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);

    // When converted to a double matrix
    flcn::Mat2x3<double> mat2(mat1);
    // And one of its value mutated
    mat2(0, 0) = 5;

    // Then, the float matrix remains unchanged
    EXPECT_MAT_CONTAINS(std::vector{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f }, mat1);

    // And, the new matrix is of type double with the mutated value
    EXPECT_MAT_CONTAINS(std::vector{ 5.0, 2.0, 3.0, 4.0, 5.0, 6.0 }, mat2);
}


TEST(Mat2x3ConversionConstructorTests, ConversionCtor_DemotesType)
{
    const flcn::Mat2x3 mat1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    [[maybe_unused]] const flcn::Mat2x3<float> mat2(mat1);
    static_assert(std::is_same_v<decltype(mat2)::value_type, float>);
}

/** @} */
