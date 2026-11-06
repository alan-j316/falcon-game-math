/**
 * @file ShearTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 29, 2026
 *
 * @brief Verify @ref flcn::Mat3 shear factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "../Mat3TestSetup.h"

#include <numbers>


/**
 * @addtogroup T_FALCON_Mat3x3_Transforms
 * @{
 */

namespace
{
    /**************************************
     *             TEST SETUP             *
     **************************************/

    /**
     * @brief Test fixture for @ref Mat3 shear transform factories.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat3ShearTests: public testing::Test
    {
    protected:
        T _shearFactor1, _shearFactor2;
        flcn::Mat3<T> _shearX2D, _shearY2D, _shearX3D, _shearY3D, _shearZ3D;


        void SetUp() override
        {
            _shearFactor1 = T(22.58923191238);
            _shearFactor2 = T(3.16);

            _shearX2D = { flcn::Vec3{ T(1), T(0), T(0) }, flcn::Vec3{ _shearFactor1, T(1), T(0) },
                          flcn::Vec3{ T(0), T(0), T(1) } };
            _shearY2D = {
                flcn::Vec3{ T(1), _shearFactor1, T(0) },
                flcn::Vec3{ T(0), T(1), T(0) },
                flcn::Vec3{ T(0), T(0), T(1) },
            };

            _shearX3D = {
                flcn::Vec3{ T(1), _shearFactor1, _shearFactor2 },
                flcn::Vec3{ T(0), T(1), T(0) },
                flcn::Vec3{ T(0), T(0), T(1) },
            };

            _shearY3D = {
                flcn::Vec3{ T(1), T(0), T(0) },
                flcn::Vec3{ _shearFactor1, T(1), _shearFactor2 },
                flcn::Vec3{ T(0), T(0), T(1) },
            };

            _shearZ3D = {
                flcn::Vec3{ T(1), T(0), T(0) },
                flcn::Vec3{ T(0), T(1), T(0) },
                flcn::Vec3{ _shearFactor1, _shearFactor2, T(1) },
            };
        }
    };
    TYPED_TEST_SUITE(Mat3ShearTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref Mat3 shear transform factory skewing along any arbitrary unit vector.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat3ShearCustomTests: public testing::Test
    {
    protected:
        T _shearAngle;
        T _shearFactor;
        flcn::Vec3<T> _shearDirection, _shearPlaneNormal;
        flcn::Mat3<T> _shear;

        void SetUp() override
        {
            _shearAngle       = T(std::numbers::pi / 4);
            _shearFactor      = T(1);
            _shearDirection   = flcn::Vec3{ T(0.2672612419124244), T(0.5345224838248488), T(0.8017837257372732) };
            _shearPlaneNormal = flcn::Vec3{ T(0.48471791416315496), T(0.5728484440110013), T(0.6609789738588476) };
            _shear = flcn::Mat3<T>{ flcn::Vec3{ T(1.1295463117164446), T(0.15310018657398008), T(0.1766540614315155) },
                                   flcn::Vec3{ T(0.2590926234328894), T(1.3062003731479601), T(0.353308122863031) },
                                   flcn::Vec3{ T(0.3886389351493341), T(0.45930055972194034), T(1.5299621842945466) } };
        }
    };
    TYPED_TEST_SUITE(Mat3ShearCustomTests, SupportedFloatingPointTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/
    namespace static_tests
    {
        constexpr auto SHEAR_FACTOR1 = 22;
        constexpr auto SHEAR_FACTOR2 = 316;

        /// @test Verify that @ref Mat3 makeShearX2D by x-axis returns a valid 3D shear matrix at compile time.
        constexpr auto SHEAR2D_X_MAT = flcn::Mat3<int>::makeShearX2D(SHEAR_FACTOR1);
        static_assert(SHEAR2D_X_MAT[0] == flcn::Vec3{ 1, 0, 0 });
        static_assert(SHEAR2D_X_MAT[1] == flcn::Vec3{ SHEAR_FACTOR1, 1, 0 });
        static_assert(SHEAR2D_X_MAT[2] == flcn::Vec3{ 0, 0, 1 });

        /// @test Verify that @ref Mat3 makeShearY2D by y-axis returns a valid 3D shear matrix at compile time.
        constexpr auto SHEAR2D_Y_MAT = flcn::Mat3<int>::makeShearY2D(SHEAR_FACTOR1);
        static_assert(SHEAR2D_Y_MAT[0] == flcn::Vec3{ 1, SHEAR_FACTOR1, 0 });
        static_assert(SHEAR2D_Y_MAT[1] == flcn::Vec3{ 0, 1, 0 });
        static_assert(SHEAR2D_Y_MAT[2] == flcn::Vec3{ 0, 0, 1 });


        /// @test Verify that @ref Mat3 makeShearX3D by x-axis returns a valid 3D shear matrix at compile time.
        constexpr auto SHEAR3D_X_MAT = flcn::Mat3<int>::makeShearX3D(SHEAR_FACTOR1, SHEAR_FACTOR2);
        static_assert(SHEAR3D_X_MAT[0] == flcn::Vec3{ 1, SHEAR_FACTOR1, SHEAR_FACTOR2 });
        static_assert(SHEAR3D_X_MAT[1] == flcn::Vec3{ 0, 1, 0 });
        static_assert(SHEAR3D_X_MAT[2] == flcn::Vec3{ 0, 0, 1 });

        /// @test Verify that @ref Mat3 makeShearY3D by y-axis returns a valid 3D shear matrix at compile time.
        constexpr auto SHEAR3D_Y_MAT = flcn::Mat3<int>::makeShearY3D(SHEAR_FACTOR1, SHEAR_FACTOR2);
        static_assert(SHEAR3D_Y_MAT[0] == flcn::Vec3{ 1, 0, 0 });
        static_assert(SHEAR3D_Y_MAT[1] == flcn::Vec3{ SHEAR_FACTOR1, 1, SHEAR_FACTOR2 });
        static_assert(SHEAR3D_Y_MAT[2] == flcn::Vec3{ 0, 0, 1 });

        /// @test Verify that @ref Mat3 makeShearZ3D by z-axis returns a valid 3D shear matrix at compile time.
        constexpr auto SHEAR3D_Z_MAT = flcn::Mat3<int>::makeShearZ3D(SHEAR_FACTOR1, SHEAR_FACTOR2);
        static_assert(SHEAR3D_Z_MAT[0] == flcn::Vec3{ 1, 0, 0 });
        static_assert(SHEAR3D_Z_MAT[1] == flcn::Vec3{ 0, 1, 0 });
        static_assert(SHEAR3D_Z_MAT[2] == flcn::Vec3{ SHEAR_FACTOR1, SHEAR_FACTOR2, 1 });

        /// TODO: Add shear by angle static tests after making tan compile time.


        /// @test Verify that @ref Mat3 makeShear returns a valid 3D shear matrix at compile time.
        constexpr auto SHEAR3D_MAT =
            flcn::Mat3<float>::makeShear(1.0f, flcn::Vec3{ 1.0f, 0.0f, 0.0f }, flcn::Vec3{ 0.0f, 0.0f, 1.0f });
        static_assert(SHEAR3D_MAT[0] == flcn::Vec3{ 1, 0, 0 });
        static_assert(SHEAR3D_MAT[1] == flcn::Vec3{ 0, 1, 0 });
        static_assert(SHEAR3D_MAT[2] == flcn::Vec3{ 1, 0, 1 });
    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat3ShearTests, ShearX2D_ReturnsAValid3DAffineShearMatrix)
{ EXPECT_MAT_EQ(this->_shearX2D, flcn::Mat3<TypeParam>::makeShearX2D(this->_shearFactor1)); }


TYPED_TEST(Mat3ShearTests, ShearY2D_ReturnsAValid3DAffineShearMatrix)
{ EXPECT_MAT_EQ(this->_shearY2D, flcn::Mat3<TypeParam>::makeShearY2D(this->_shearFactor1)); }


TYPED_TEST(Mat3ShearTests, ShearX3D_ReturnsAValid3DShearMatrix)
{ EXPECT_MAT_EQ(this->_shearX3D, flcn::Mat3<TypeParam>::makeShearX3D(this->_shearFactor1, this->_shearFactor2)); }


TYPED_TEST(Mat3ShearTests, ShearY3D_ReturnsAValid3DShearMatrix)
{ EXPECT_MAT_EQ(this->_shearY3D, flcn::Mat3<TypeParam>::makeShearY3D(this->_shearFactor1, this->_shearFactor2)); }


TYPED_TEST(Mat3ShearTests, ShearZ3D_ReturnsAValid3DShearMatrix)
{ EXPECT_MAT_EQ(this->_shearZ3D, flcn::Mat3<TypeParam>::makeShearZ3D(this->_shearFactor1, this->_shearFactor2)); }


TYPED_TEST(Mat3ShearCustomTests, ShearByAngle_ReturnsAValid3DShearMatrix)
{
    EXPECT_MAT_EQ(
        this->_shear,
        flcn::Mat3<TypeParam>::makeShearByAngle(this->_shearAngle, this->_shearPlaneNormal, this->_shearDirection));
}


TYPED_TEST(Mat3ShearCustomTests, Shear_ReturnsAValid3DShearMatrix)
{
    EXPECT_MAT_EQ(this->_shear,
                  flcn::Mat3<TypeParam>::makeShear(this->_shearFactor, this->_shearPlaneNormal, this->_shearDirection));
}


/** @} */
