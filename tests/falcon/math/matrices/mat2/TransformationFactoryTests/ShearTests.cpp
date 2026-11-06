/**
 * @file ShearTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 29, 2026
 *
 * @brief Verify @ref flcn::Mat2 shear factory logic.
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
     *             TEST SETUP             *
     **************************************/

    /**
     * @brief Test fixture for @ref Mat2 shear transform factories.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat2ShearTests: public testing::Test
    {
    protected:
        T _shearFactor;
        flcn::Mat2<T> _shearX, _shearY;


        void SetUp() override
        {
            _shearFactor = T(22.58923191238);
            _shearX      = {
                flcn::CVec2{ T(1), T(0) },
                flcn::CVec2{ _shearFactor, T(1) },
            };
            _shearY = {
                flcn::CVec2{ T(1), _shearFactor },
                flcn::CVec2{ T(0), T(1) },
            };
        }
    };
    TYPED_TEST_SUITE(Mat2ShearTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr auto SHEAR_FACTOR = 22;

        /// @test Verify that @ref Mat2 makeShear by x-axis returns a valid shear matrix at compile time.
        constexpr auto SHEAR_X_MAT = flcn::Mat2<int>::makeShearX(SHEAR_FACTOR);
        static_assert(SHEAR_X_MAT[0] == flcn::CVec2{ 1, 0 });
        static_assert(SHEAR_X_MAT[1] == flcn::CVec2{ 22, 1 });

        /// @test Verify that @ref Mat2 makeShear by y-axis returns a valid shear matrix at compile time.
        constexpr auto SHEAR_Y_MAT = flcn::Mat2<int>::makeShearY(SHEAR_FACTOR);
        static_assert(SHEAR_Y_MAT[0] == flcn::CVec2{ 1, 22 });
        static_assert(SHEAR_Y_MAT[1] == flcn::CVec2{ 0, 1 });
    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat2ShearTests, ShearX_ReturnsAValid2DShearMatrix)
{ EXPECT_MAT_EQ(this->_shearX, flcn::Mat2<TypeParam>::makeShearX(this->_shearFactor)); }


TYPED_TEST(Mat2ShearTests, ShearY_ReturnsAValid2DShearMatrix)
{ EXPECT_MAT_EQ(this->_shearY, flcn::Mat2<TypeParam>::makeShearY(this->_shearFactor)); }

/** @} */
