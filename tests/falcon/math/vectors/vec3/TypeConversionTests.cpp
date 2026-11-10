/**
 * @file TypeConversionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 10, 2026
 *
 * @brief Verify @ref flcn::Vec3 conversion constructor logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"



/**
 * @addtogroup T_Falcon_Vec3_Type_Conv
 * @{
 */

/**************************************
 *           RUNTIME TESTS            *
 **************************************/

/**
 * @test Verify that the conversion constructor correctly promotes components from float to double.
 */
TEST(Vec3TypeConversionTests, ConversionCtor_PromotesType)
{
    const flcn::Vec3 vec1(3.0f, 1.0f, 6.0f);
    [[maybe_unused]] const flcn::Vec3<double> vec2(vec1);
    static_assert(std::is_same_v<decltype(vec2)::value_type, double>);
}


/** @test Verify that the conversion constructor ensures deep-copy value semantics. */
TEST(Vec3TypeConversionTests, ConversionCtor_ReturnsNewInstance)
{
    // Given a float vector
    const flcn::Vec3 vec1(3.0f, 1.0f, 6.0f);

    // When converted to a double vector
    flcn::Vec3<double> vec2(vec1);
    // And one of its value mutated
    vec2.x() = 5;

    // Then, the float vector remains unchanged
    EXPECT_VEC_CONTAINS(vec1, 3.0f, 1.0f, 6.0f);

    // And, the new vector is of type double with the mutated value
    EXPECT_VEC_CONTAINS(vec2, 5.0, 1.0, 6.0);
}


/**
 * @test Verify that the conversion constructor correctly demotes components from double to float.
 */
TEST(Vec3TypeConversionTests, ConversionCtor_DemotesType)
{
    const flcn::Vec3 vec1(3.0, 1.0, 6.0);
    [[maybe_unused]] const flcn::Vec3<float> vec2(vec1);
    static_assert(std::is_same_v<decltype(vec2)::value_type, float>);
}

/** @} */
