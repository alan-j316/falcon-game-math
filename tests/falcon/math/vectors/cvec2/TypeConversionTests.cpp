/**
 * @file TypeConversionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref flcn::CVec2 conversion constructor logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CVec2TestSetup.h"



/**
 * @addtogroup T_FALCON_CVec2_Type_Conv
 * @{
 */

namespace
{
    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::CVec2 VEC(3.0f, 1.0f);

        /// @test Verify that vector conversion constructor can promote type at compile time. */
        constexpr flcn::CVec2<double> PROMOTED_VEC(VEC);
        static_assert(std::is_same_v<decltype(PROMOTED_VEC)::value_type, double>);

        /// @test Verify that vector conversion constructor can demote type at compile time. */
        [[maybe_unused]] constexpr flcn::CVec2<float> DEMOTED_VEC(PROMOTED_VEC);
        static_assert(std::is_same_v<decltype(DEMOTED_VEC)::value_type, float>);

    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TEST(CVec2TypeConversionTests, ConversionCtor_PromotesType)
{
    const flcn::CVec2 vec1(3.0f, 1.0f);

    [[maybe_unused]] const flcn::CVec2<double> vec2(vec1);

    static_assert(std::is_same_v<decltype(vec2)::value_type, double>);
}


TEST(CVec2TypeConversionTests, ConversionCtor_ReturnsNewInstance)
{
    // Given a float vector
    const flcn::CVec2 vec1(3.0f, 1.0f);

    // When converted to a double vector
    flcn::CVec2<double> vec2(vec1);
    // And one of its value mutated
    vec2.x() = 5;

    // Then, the float vector remains unchanged
    EXPECT_VEC_CONTAINS(vec1, 3.0f, 1.0f);

    // And, the new vector is of type double with the mutated value
    EXPECT_VEC_CONTAINS(vec2, 5.0, 1.0);
}


TEST(CVec2TypeConversionTests, ConversionCtor_DemotesType)
{
    const flcn::CVec2 vec1(3.0, 1.0);

    [[maybe_unused]] const flcn::CVec2<float> vec2(vec1);

    static_assert(std::is_same_v<decltype(vec2)::value_type, float>);
}

/** @} */
