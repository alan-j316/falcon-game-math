/**
 * @file ReflectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 09, 2026
 *
 * @brief Verify @ref flcn::Mat2 reflection factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "../Mat2TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat2x2_Transforms
 * @{
 */

namespace
{

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2 Reflection Factory.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2ReflectionFactoryTests: public testing::Test
    {
    protected:
        flcn::Mat2<T> _expectedReflectionX, _expectedReflectionY, _expectedReflectionOrigin;

        void SetUp() override
        {
            _expectedReflectionX      = { flcn::CVec2{ T(1), T(0) }, flcn::CVec2{ T(0), T(-1) } };
            _expectedReflectionY      = { flcn::CVec2{ T(-1), T(0) }, flcn::CVec2{ T(0), T(1) } };
            _expectedReflectionOrigin = { flcn::CVec2{ T(-1), T(0) }, flcn::CVec2{ T(0), T(-1) } };
        }
    };
    TYPED_TEST_SUITE(Mat2ReflectionFactoryTests, SupportedSignedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that the reflection factory for x-axis return a valid matrix at compile time.
        constexpr auto REFLECTION_MAT_X = flcn::Mat2<int>::makeReflection<flcn::reflect::X>();
        static_assert(REFLECTION_MAT_X(0, 0) == 1);
        static_assert(REFLECTION_MAT_X(0, 1) == 0);
        static_assert(REFLECTION_MAT_X(1, 0) == 0);
        static_assert(REFLECTION_MAT_X(1, 1) == -1);


        /// @test Verify that the reflection factory for y-axis return a valid matrix at compile time.
        constexpr auto REFLECTION_MAT_Y = flcn::Mat2<int>::makeReflection<flcn::reflect::Y>();
        static_assert(REFLECTION_MAT_Y(0, 0) == -1);
        static_assert(REFLECTION_MAT_Y(0, 1) == 0);
        static_assert(REFLECTION_MAT_Y(1, 0) == 0);
        static_assert(REFLECTION_MAT_Y(1, 1) == 1);


        /// @test Verify that the reflection factory for origin return a valid matrix at compile time.
        constexpr auto REFLECTION_MAT_ORIGIN = flcn::Mat2<int>::makeReflection<flcn::reflect::ORIGIN>();
        static_assert(REFLECTION_MAT_ORIGIN(0, 0) == -1);
        static_assert(REFLECTION_MAT_ORIGIN(0, 1) == 0);
        static_assert(REFLECTION_MAT_ORIGIN(1, 0) == 0);
        static_assert(REFLECTION_MAT_ORIGIN(1, 1) == -1);

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat2ReflectionFactoryTests, X_ReturnsMatrixWithNegatedY)
{ EXPECT_MAT_EQ(this->_expectedReflectionX, flcn::Mat2<TypeParam>::template makeReflection<flcn::reflect::X>()); }


TYPED_TEST(Mat2ReflectionFactoryTests, Y_ReturnsMatrixWithNegatedX)
{ EXPECT_MAT_EQ(this->_expectedReflectionY, flcn::Mat2<TypeParam>::template makeReflection<flcn::reflect::Y>()); }


TYPED_TEST(Mat2ReflectionFactoryTests, Origin_ReturnsMatrixWithNegatedXY)
{
    EXPECT_MAT_EQ(this->_expectedReflectionOrigin,
                  flcn::Mat2<TypeParam>::template makeReflection<flcn::reflect::ORIGIN>());
}


/** @} */
