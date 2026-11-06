/**
 * @file ShearTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 30, 2026
 *
 * @brief Verify @ref flcn::Mat4 shear factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <numbers>

#include "../Mat4TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat4x4_Transforms
 * @{
 */

namespace
{
    /**************************************
     *             TEST SETUP             *
     **************************************/

    /**
     * @brief Test fixture for @ref Mat4 shear transform factories.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat4ShearTests: public testing::Test
    {
    protected:
        T _shearFactor1, _shearFactor2;
        flcn::Mat4<T> _shearX, _shearY, _shearZ;


        void SetUp() override
        {
            _shearFactor1 = T(22.58923191238);
            _shearFactor2 = T(3.16);
            _shearX = { flcn::Vec4{ T(1), _shearFactor1, _shearFactor2, T(0) }, flcn::Vec4{ T(0), T(1), T(0), T(0) },
                        flcn::Vec4{ T(0), T(0), T(1), T(0) }, flcn::Vec4{ T(0), T(0), T(0), T(1) } };
            _shearY = { flcn::Vec4{ T(1), T(0), T(0), T(0) }, flcn::Vec4{ _shearFactor1, T(1), _shearFactor2, T(0) },
                        flcn::Vec4{ T(0), T(0), T(1), T(0) }, flcn::Vec4{ T(0), T(0), T(0), T(1) } };
            _shearZ = { flcn::Vec4{ T(1), T(0), T(0), T(0) }, flcn::Vec4{ T(0), T(1), T(0), T(0) },
                        flcn::Vec4{ _shearFactor1, _shearFactor2, T(1), T(0) }, flcn::Vec4{ T(0), T(0), T(0), T(1) } };
        }
    };
    TYPED_TEST_SUITE(Mat4ShearTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Mat4 shear transform factory skewing along any arbitrary unit vector.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat4ShearCustomTests: public testing::Test
    {
    protected:
        T _shearAngle;
        T _shearFactor;
        flcn::Vec3<T> _shearDirection, _shearPlaneNormal;
        flcn::Mat4<T> _shear;

        void SetUp() override
        {
            _shearAngle       = T(std::numbers::pi / 4);
            _shearFactor      = T(1);
            _shearDirection   = flcn::Vec3{ T(0.2672612419124244), T(0.5345224838248488), T(0.8017837257372732) };
            _shearPlaneNormal = flcn::Vec3{ T(0.48471791416315496), T(0.5728484440110013), T(0.6609789738588476) };
            _shear =
                flcn::Mat4<T>{ flcn::Vec4{ T(1.1295463117164446), T(0.15310018657398008), T(0.1766540614315155), T(0) },
                              flcn::Vec4{ T(0.2590926234328894), T(1.3062003731479601), T(0.353308122863031), T(0) },
                              flcn::Vec4{ T(0.3886389351493341), T(0.45930055972194034), T(1.5299621842945466), T(0) },
                              flcn::Vec4{ T(0), T(0), T(0), T(1) } };
        }
    };
    TYPED_TEST_SUITE(Mat4ShearCustomTests, SupportedFloatingPointTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr auto SHEAR_FACTOR1 = 22;
        constexpr auto SHEAR_FACTOR2 = 316;


        /// @test Verify that @ref Mat4 makeShearX by x-axis returns a valid 4D shear matrix at compile time.
        constexpr auto SHEAR4D_X_MAT = flcn::Mat4<int>::makeShearX(SHEAR_FACTOR1, SHEAR_FACTOR2);
        static_assert(SHEAR4D_X_MAT[0] == flcn::Vec4{ 1, SHEAR_FACTOR1, SHEAR_FACTOR2, 0 });
        static_assert(SHEAR4D_X_MAT[1] == flcn::Vec4{ 0, 1, 0, 0 });
        static_assert(SHEAR4D_X_MAT[2] == flcn::Vec4{ 0, 0, 1, 0 });
        static_assert(SHEAR4D_X_MAT[3] == flcn::Vec4{ 0, 0, 0, 1 });


        /// @test Verify that @ref Mat4 makeShearY by y-axis returns a valid 4D shear matrix at compile time.
        constexpr auto SHEAR4D_Y_MAT = flcn::Mat4<int>::makeShearY(SHEAR_FACTOR1, SHEAR_FACTOR2);
        static_assert(SHEAR4D_Y_MAT[0] == flcn::Vec4{ 1, 0, 0, 0 });
        static_assert(SHEAR4D_Y_MAT[1] == flcn::Vec4{ SHEAR_FACTOR1, 1, SHEAR_FACTOR2, 0 });
        static_assert(SHEAR4D_Y_MAT[2] == flcn::Vec4{ 0, 0, 1, 0 });
        static_assert(SHEAR4D_Y_MAT[3] == flcn::Vec4{ 0, 0, 0, 1 });


        /// @test Verify that @ref Mat4 makeShearZ by z-axis returns a valid 4D shear matrix at compile time.
        constexpr auto SHEAR4D_Z_MAT = flcn::Mat4<int>::makeShearZ(SHEAR_FACTOR1, SHEAR_FACTOR2);
        static_assert(SHEAR4D_Z_MAT[0] == flcn::Vec4{ 1, 0, 0, 0 });
        static_assert(SHEAR4D_Z_MAT[1] == flcn::Vec4{ 0, 1, 0, 0 });
        static_assert(SHEAR4D_Z_MAT[2] == flcn::Vec4{ SHEAR_FACTOR1, SHEAR_FACTOR2, 1, 0 });
        static_assert(SHEAR4D_Y_MAT[3] == flcn::Vec4{ 0, 0, 0, 1 });


        /// TODO: Add shear by angle static tests after making tan compile time.


        /// @test Verify that @ref Mat4 makeShear returns a valid 4D shear matrix at compile time.
        constexpr auto SHEAR4D_MAT =
            flcn::Mat4<float>::makeShear(1.0f, flcn::Vec3{ 1.0f, 0.0f, 0.0f }, flcn::Vec3{ 0.0f, 0.0f, 1.0f });
        static_assert(SHEAR4D_MAT[0] == flcn::Vec4{ 1, 0, 0, 0 });
        static_assert(SHEAR4D_MAT[1] == flcn::Vec4{ 0, 1, 0, 0 });
        static_assert(SHEAR4D_MAT[2] == flcn::Vec4{ 1, 0, 1, 0 });
        static_assert(SHEAR4D_MAT[3] == flcn::Vec4{ 0, 0, 0, 1 });
    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat4ShearTests, ShearX4D_ReturnsAValid4DShearMatrix)
{ EXPECT_MAT_EQ(this->_shearX, flcn::Mat4<TypeParam>::makeShearX(this->_shearFactor1, this->_shearFactor2)); }


TYPED_TEST(Mat4ShearTests, ShearY4D_ReturnsAValid4DShearMatrix)
{ EXPECT_MAT_EQ(this->_shearY, flcn::Mat4<TypeParam>::makeShearY(this->_shearFactor1, this->_shearFactor2)); }


TYPED_TEST(Mat4ShearTests, ShearZ4D_ReturnsAValid4DShearMatrix)
{ EXPECT_MAT_EQ(this->_shearZ, flcn::Mat4<TypeParam>::makeShearZ(this->_shearFactor1, this->_shearFactor2)); }


TYPED_TEST(Mat4ShearCustomTests, ShearByAngle_ReturnsAValid4DShearMatrix)
{
    EXPECT_MAT_EQ(
        this->_shear,
        flcn::Mat4<TypeParam>::makeShearByAngle(this->_shearAngle, this->_shearPlaneNormal, this->_shearDirection));
}

TYPED_TEST(Mat4ShearCustomTests, Shear_ReturnsAValid4DShearMatrix)
{
    EXPECT_MAT_EQ(this->_shear,
                  flcn::Mat4<TypeParam>::makeShear(this->_shearFactor, this->_shearPlaneNormal, this->_shearDirection));
}

/** @} */
