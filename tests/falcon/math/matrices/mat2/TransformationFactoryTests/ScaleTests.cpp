/**
 * @file ScaleTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 09, 2026
 *
 * @brief Verify @ref flcn::Mat2 scale factory logic.
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
     * @brief Test fixture for @ref flcn::Mat2 Uniform Scale Factory.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2UniformScaleFactoryTests: public testing::Test
    {
    protected:
        flcn::Mat2<T> _expectedMat;
        T _scale;

        void SetUp() override
        {
            _expectedMat = { flcn::CVec2{ T(5.3821839321), T(0) }, flcn::CVec2{ T(0), T(5.3821839321) } };
            _scale       = T(5.3821839321);
        }
    };
    TYPED_TEST_SUITE(Mat2UniformScaleFactoryTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::Mat2 Non-uniform Scale Factory.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2NonUniformScaleFactoryTests: public ::testing::Test
    {
    protected:
        flcn::Mat2<T> _expectedMat;
        T _scaleX, _scaleY;

        void SetUp() override
        {
            _expectedMat = { flcn::CVec2{ T(5.3821839321), T(0) }, flcn::CVec2{ T(0), T(8.1234921348) } };
            _scaleX      = T(5.3821839321);
            _scaleY      = T(8.1234921348);
        }
    };
    TYPED_TEST_SUITE(Mat2NonUniformScaleFactoryTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that Mat2 uniform scale factory returns a valid matrix at compile time.
        constexpr auto U_SCALE_MAT = flcn::Mat2<int>::makeScale(2);
        static_assert(U_SCALE_MAT(0, 0) == 2);
        static_assert(U_SCALE_MAT(0, 1) == 0);
        static_assert(U_SCALE_MAT(1, 0) == 0);
        static_assert(U_SCALE_MAT(1, 1) == 2);


        /// @test Verify that Mat2 non-uniform scale factory returns a valid matrix at compile time.
        constexpr auto SCALE_MAT = flcn::Mat2<int>::makeScale(2, 3);
        static_assert(SCALE_MAT(0, 0) == 2);
        static_assert(SCALE_MAT(0, 1) == 0);
        static_assert(SCALE_MAT(1, 0) == 0);
        static_assert(SCALE_MAT(1, 1) == 3);

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat2UniformScaleFactoryTests, ReturnsValidScaleMatrix)
{ EXPECT_MAT_EQ(this->_expectedMat, flcn::Mat2<TypeParam>::makeScale(this->_scale)); }


TYPED_TEST(Mat2NonUniformScaleFactoryTests, ReturnsValidScaleMatrix)
{ EXPECT_MAT_EQ(this->_expectedMat, flcn::Mat2<TypeParam>::makeScale(this->_scaleX, this->_scaleY)); }


/** @} */
