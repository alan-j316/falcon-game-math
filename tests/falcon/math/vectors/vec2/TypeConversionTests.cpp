/**
 * @file TypeConversionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref flcn::Vec2 conversion constructor logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"



/**
 * @addtogroup T_Falcon_Vec2_Type_Conv
 * @{
 */

namespace
{
    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Vec2 VEC(3.0f, 1.0f);

        /// @test Verify that vector conversion constructor can promote type at compile time. */
        constexpr flcn::Vec2<double> PROMOTED_VEC(VEC);
        static_assert(std::is_same_v<decltype(PROMOTED_VEC)::ValueType, double>);

        /// @test Verify that vector conversion constructor can demote type at compile time. */
        [[maybe_unused]] constexpr flcn::Vec2<float> DEMOTED_VEC(PROMOTED_VEC);
        static_assert(std::is_same_v<decltype(DEMOTED_VEC)::ValueType, float>);

    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TEST(Vec2TypeConversionTests, ConversionCtor_PromotesType)
{
    const flcn::Vec2 vec1(3.0f, 1.0f);

    [[maybe_unused]] const flcn::Vec2<double> vec2(vec1);

    static_assert(std::is_same_v<decltype(vec2)::ValueType, double>);
}


TEST(Vec2TypeConversionTests, ConversionCtor_ReturnsNewInstance)
{
    // Given a float vector
    const flcn::Vec2 vec1(3.0f, 1.0f);

    // When converted to a double vector
    flcn::Vec2<double> vec2(vec1);
    // And one of its value mutated
    vec2.x() = 5;

    // Then, the float vector remains unchanged
    EXPECT_VEC_CONTAINS(vec1, 3.0f, 1.0f);

    // And, the new vector is of type double with the mutated value
    EXPECT_VEC_CONTAINS(vec2, 5.0, 1.0);
}


TEST(Vec2TypeConversionTests, ConversionCtor_DemotesType)
{
    const flcn::Vec2 vec1(3.0, 1.0);

    [[maybe_unused]] const flcn::Vec2<float> vec2(vec1);

    static_assert(std::is_same_v<decltype(vec2)::ValueType, float>);
}

/** @} */
