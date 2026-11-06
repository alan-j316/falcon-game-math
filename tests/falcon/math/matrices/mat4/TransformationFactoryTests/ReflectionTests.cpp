/**
 * @file ReflectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 23, 2026
 *
 * @brief Verify @ref flcn::Mat4 reflection factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "../Mat4TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat4x4_Transforms
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4 reflection factory (Floating Point).
     *
     * @tparam T The floating point scalar type (e.g., float, double) used for the matrix and vectors.
     */
    template <typename T>
    class Mat4ReflectionFactoryIntTests: public testing::Test
    {
    protected:
        flcn::Vec3<T> _xAxis, _yAxis, _zAxis;
        flcn::Mat4<T> _expectedReflectionX, _expectedReflectionY, _expectedReflectionZ, _expectedReflectionXY,
            _expectedReflectionYZ, _expectedReflectionZX, _expectedReflectionOrigin;

        void SetUp() override
        {
            _xAxis = flcn::Vec3{ T(1), T(0), T(0) };
            _yAxis = flcn::Vec3{ T(0), T(1), T(0) };
            _zAxis = flcn::Vec3{ T(0), T(0), T(1) };

            _expectedReflectionX = { flcn::Vec4{ T(1), T(0), T(0), T(0) }, flcn::Vec4{ T(0), T(-1), T(0), T(0) },
                                     flcn::Vec4{ T(0), T(0), T(-1), T(0) }, flcn::Vec4{ T(0), T(0), T(0), T(1) } };

            _expectedReflectionY = { flcn::Vec4{ T(-1), T(0), T(0), T(0) }, flcn::Vec4{ T(0), T(1), T(0), T(0) },
                                     flcn::Vec4{ T(0), T(0), T(-1), T(0) }, flcn::Vec4{ T(0), T(0), T(0), T(1) } };

            _expectedReflectionZ = { flcn::Vec4{ T(-1), T(0), T(0), T(0) }, flcn::Vec4{ T(0), T(-1), T(0), T(0) },
                                     flcn::Vec4{ T(0), T(0), T(1), T(0) }, flcn::Vec4{ T(0), T(0), T(0), T(1) } };

            _expectedReflectionXY = { flcn::Vec4{ T(1), T(0), T(0), T(0) }, flcn::Vec4{ T(0), T(1), T(0), T(0) },
                                      flcn::Vec4{ T(0), T(0), T(-1), T(0) }, flcn::Vec4{ T(0), T(0), T(0), T(1) } };

            _expectedReflectionYZ = { flcn::Vec4{ T(-1), T(0), T(0), T(0) }, flcn::Vec4{ T(0), T(1), T(0), T(0) },
                                      flcn::Vec4{ T(0), T(0), T(1), T(0) }, flcn::Vec4{ T(0), T(0), T(0), T(1) } };

            _expectedReflectionZX = { flcn::Vec4{ T(1), T(0), T(0), T(0) }, flcn::Vec4{ T(0), T(-1), T(0), T(0) },
                                      flcn::Vec4{ T(0), T(0), T(1), T(0) }, flcn::Vec4{ T(0), T(0), T(0), T(1) } };

            _expectedReflectionOrigin = { flcn::Vec4{ T(-1), T(0), T(0), T(0) }, flcn::Vec4{ T(0), T(-1), T(0), T(0) },
                                          flcn::Vec4{ T(0), T(0), T(-1), T(0) }, flcn::Vec4{ T(0), T(0), T(0), T(1) } };
        }
    };
    TYPED_TEST_SUITE(Mat4ReflectionFactoryIntTests, SupportedSignedArithmeticTypes);


    /**
     * @brief Test fixture for @ref flcn::Mat4 reflection factory (Floating Point).
     *
     * @tparam T The signed scalar type (e.g., int32_t, int16_t) used for the matrix and vectors.
     */
    template <typename T>
    class Mat4ReflectionFactoryFactoryFPTests: public ::testing::Test
    {
    protected:
        flcn::Vec3<T> _norm;
        flcn::Mat4<T> _expectedNormReflect;

        void SetUp() override
        {
            _norm = flcn::Vec3{ T(0.3244428422615251), T(0.48666426339228763), T(0.8111071056538127) };

            _expectedNormReflect = {
                flcn::Vec4{ T(0.7894736842105263), T(-0.31578947368421056), T(-0.5263157894736843), T(0) },
                flcn::Vec4{ T(-0.31578947368421056), T(0.5263157894736842), T(-0.7894736842105263), T(0) },
                flcn::Vec4{ T(-0.5263157894736843), T(-0.7894736842105263), T(-0.3157894736842106), T(0) },
                flcn::Vec4{ T(0), T(0), T(0), T(1) }
            };
        }
    };
    TYPED_TEST_SUITE(Mat4ReflectionFactoryFactoryFPTests, SupportedFloatingPointTypes);



    namespace static_tests
    {
        /// @test Verify that reflection factory returns correct reflection along x-axis at compile time.
        constexpr auto REFLECTION_MAT_ACROSS_X = flcn::Mat4<int>::makeReflection<flcn::reflect::X>();
        static_assert(REFLECTION_MAT_ACROSS_X[0] == flcn::Vec4(1, 0, 0, 0));
        static_assert(REFLECTION_MAT_ACROSS_X[1] == flcn::Vec4(0, -1, 0, 0));
        static_assert(REFLECTION_MAT_ACROSS_X[2] == flcn::Vec4(0, 0, -1, 0));
        static_assert(REFLECTION_MAT_ACROSS_X[3] == flcn::Vec4(0, 0, 0, 1));


        /// @test Verify that reflection factory returns correct reflection along y-axis at compile time.
        constexpr auto REFLECTION_MAT_ACROSS_Y = flcn::Mat4<int>::makeReflection<flcn::reflect::Y>();
        static_assert(REFLECTION_MAT_ACROSS_Y[0] == flcn::Vec4(-1, 0, 0, 0));
        static_assert(REFLECTION_MAT_ACROSS_Y[1] == flcn::Vec4(0, 1, 0, 0));
        static_assert(REFLECTION_MAT_ACROSS_Y[2] == flcn::Vec4(0, 0, -1, 0));
        static_assert(REFLECTION_MAT_ACROSS_Y[3] == flcn::Vec4(0, 0, 0, 1));


        /// @test Verify that reflection factory returns correct reflection along y-axis at compile time.
        constexpr auto REFLECTION_MAT_ACROSS_Z = flcn::Mat4<int>::makeReflection<flcn::reflect::Z>();
        static_assert(REFLECTION_MAT_ACROSS_Z[0] == flcn::Vec4(-1, 0, 0, 0));
        static_assert(REFLECTION_MAT_ACROSS_Z[1] == flcn::Vec4(0, -1, 0, 0));
        static_assert(REFLECTION_MAT_ACROSS_Z[2] == flcn::Vec4(0, 0, 1, 0));
        static_assert(REFLECTION_MAT_ACROSS_Z[3] == flcn::Vec4(0, 0, 0, 1));

        /// @test Verify that reflection factory returns correct reflection along xy-plane at compile time.
        constexpr auto REFLECTION_MAT_ACROSS_XY = flcn::Mat4<int>::makeReflection<flcn::reflect::XY>();
        static_assert(REFLECTION_MAT_ACROSS_XY[0] == flcn::Vec4(1, 0, 0, 0));
        static_assert(REFLECTION_MAT_ACROSS_XY[1] == flcn::Vec4(0, 1, 0, 0));
        static_assert(REFLECTION_MAT_ACROSS_XY[2] == flcn::Vec4(0, 0, -1, 0));
        static_assert(REFLECTION_MAT_ACROSS_XY[3] == flcn::Vec4(0, 0, 0, 1));

        /// @test Verify that reflection factory returns correct reflection along yz-plane at compile time.
        constexpr auto REFLECTION_MAT_ACROSS_YZ = flcn::Mat4<int>::makeReflection<flcn::reflect::YZ>();
        static_assert(REFLECTION_MAT_ACROSS_YZ[0] == flcn::Vec4(-1, 0, 0, 0));
        static_assert(REFLECTION_MAT_ACROSS_YZ[1] == flcn::Vec4(0, 1, 0, 0));
        static_assert(REFLECTION_MAT_ACROSS_YZ[2] == flcn::Vec4(0, 0, 1, 0));
        static_assert(REFLECTION_MAT_ACROSS_YZ[3] == flcn::Vec4(0, 0, 0, 1));

        /// @test Verify that reflection factory returns correct reflection along xz-plane at compile time.
        constexpr auto REFLECTION_MAT_ACROSS_ZX = flcn::Mat4<int>::makeReflection<flcn::reflect::ZX>();
        static_assert(REFLECTION_MAT_ACROSS_ZX[0] == flcn::Vec4(1, 0, 0, 0));
        static_assert(REFLECTION_MAT_ACROSS_ZX[1] == flcn::Vec4(0, -1, 0, 0));
        static_assert(REFLECTION_MAT_ACROSS_ZX[2] == flcn::Vec4(0, 0, 1, 0));
        static_assert(REFLECTION_MAT_ACROSS_ZX[3] == flcn::Vec4(0, 0, 0, 1));

        /// @test Verify that reflection factory returns correct reflection along origin at compile time.
        constexpr auto REFLECTION_MAT_ACROSS_ORIGIN = flcn::Mat4<int>::makeReflection<flcn::reflect::ORIGIN>();
        static_assert(REFLECTION_MAT_ACROSS_ORIGIN[0] == flcn::Vec4(-1, 0, 0, 0));
        static_assert(REFLECTION_MAT_ACROSS_ORIGIN[1] == flcn::Vec4(0, -1, 0, 0));
        static_assert(REFLECTION_MAT_ACROSS_ORIGIN[2] == flcn::Vec4(0, 0, -1, 0));
        static_assert(REFLECTION_MAT_ACROSS_ORIGIN[3] == flcn::Vec4(0, 0, 0, 1));


        /// @test Verify that reflection factory for any plane returns correct reflection with x-axis normal(yz-plane)
        ///       at compile time.
        constexpr auto X_AXIS                = flcn::Vec3(1, 0, 0);
        constexpr auto REFLECTION_MAT_NORM_X = flcn::Mat4<int>::makeReflection(X_AXIS);
        static_assert(REFLECTION_MAT_NORM_X[0] == flcn::Vec4(-1, 0, 0, 0));
        static_assert(REFLECTION_MAT_NORM_X[1] == flcn::Vec4(0, 1, 0, 0));
        static_assert(REFLECTION_MAT_NORM_X[2] == flcn::Vec4(0, 0, 1, 0));
        static_assert(REFLECTION_MAT_NORM_X[3] == flcn::Vec4(0, 0, 0, 1));

        /// @test Verify that reflection factory for any plane returns correct reflection with y-axis normal(zx-plane)
        ///       at compile time.
        constexpr auto Y_AXIS                = flcn::Vec3(0, 1, 0);
        constexpr auto REFLECTION_MAT_NORM_Y = flcn::Mat4<int>::makeReflection(Y_AXIS);
        static_assert(REFLECTION_MAT_NORM_Y[0] == flcn::Vec4(1, 0, 0, 0));
        static_assert(REFLECTION_MAT_NORM_Y[1] == flcn::Vec4(0, -1, 0, 0));
        static_assert(REFLECTION_MAT_NORM_Y[2] == flcn::Vec4(0, 0, 1, 0));
        static_assert(REFLECTION_MAT_NORM_Y[3] == flcn::Vec4(0, 0, 0, 1));

        /// @test Verify that reflection factory for any plane returns correct reflection with z-axis normal(xy-plane)
        ///       at compile time.
        constexpr auto Z_AXIS                = flcn::Vec3(0, 0, 1);
        constexpr auto REFLECTION_MAT_NORM_Z = flcn::Mat4<int>::makeReflection(Z_AXIS);
        static_assert(REFLECTION_MAT_NORM_Z[0] == flcn::Vec4(1, 0, 0, 0));
        static_assert(REFLECTION_MAT_NORM_Z[1] == flcn::Vec4(0, 1, 0, 0));
        static_assert(REFLECTION_MAT_NORM_Z[2] == flcn::Vec4(0, 0, -1, 0));
        static_assert(REFLECTION_MAT_NORM_Z[3] == flcn::Vec4(0, 0, 0, 1));

    } // namespace static_tests


} // namespace



/**************************************
 *          RUNTIME TESTS             *
 **************************************/

TYPED_TEST(Mat4ReflectionFactoryIntTests, XAxis_ReturnsMatrixWithNegatedYZ)
{ EXPECT_MAT_EQ(this->_expectedReflectionX, flcn::Mat4<TypeParam>::template makeReflection<flcn::reflect::X>()); }


TYPED_TEST(Mat4ReflectionFactoryIntTests, YAxis_ReturnsMatrixWithNegatedXZ)
{ EXPECT_MAT_EQ(this->_expectedReflectionY, flcn::Mat4<TypeParam>::template makeReflection<flcn::reflect::Y>()); }


TYPED_TEST(Mat4ReflectionFactoryIntTests, ZAxis_ReturnsMatrixWithNegatedXY)
{ EXPECT_MAT_EQ(this->_expectedReflectionZ, flcn::Mat4<TypeParam>::template makeReflection<flcn::reflect::Z>()); }


TYPED_TEST(Mat4ReflectionFactoryIntTests, XYPlane_ReturnsMatrixWithNegatedZ)
{ EXPECT_MAT_EQ(this->_expectedReflectionXY, flcn::Mat4<TypeParam>::template makeReflection<flcn::reflect::XY>()); }


TYPED_TEST(Mat4ReflectionFactoryIntTests, YZPlane_ReturnsMatrixWithNegatedX)
{ EXPECT_MAT_EQ(this->_expectedReflectionYZ, flcn::Mat4<TypeParam>::template makeReflection<flcn::reflect::YZ>()); }


TYPED_TEST(Mat4ReflectionFactoryIntTests, ZXPlane_ReturnsMatrixWithNegatedY)
{ EXPECT_MAT_EQ(this->_expectedReflectionZX, flcn::Mat4<TypeParam>::template makeReflection<flcn::reflect::ZX>()); }


TYPED_TEST(Mat4ReflectionFactoryIntTests, Origin_ReturnsMatrixWithNegatedXYZ)
{
    EXPECT_MAT_EQ(this->_expectedReflectionOrigin,
                  flcn::Mat4<TypeParam>::template makeReflection<flcn::reflect::ORIGIN>());
}


TYPED_TEST(Mat4ReflectionFactoryIntTests, PlaneNormalAlongXAxis_ReturnsYZReflectionMatrix)
{ EXPECT_MAT_EQ(this->_expectedReflectionYZ, flcn::Mat4<TypeParam>::makeReflection(this->_xAxis)); }


TYPED_TEST(Mat4ReflectionFactoryIntTests, PlaneNormalAlongYAxis_ReturnsZXReflectionMatrix)
{ EXPECT_MAT_EQ(this->_expectedReflectionZX, flcn::Mat4<TypeParam>::makeReflection(this->_yAxis)); }


TYPED_TEST(Mat4ReflectionFactoryIntTests, PlaneNormalAlongZAxis_ReturnsXYReflectionMatrix)
{ EXPECT_MAT_EQ(this->_expectedReflectionXY, flcn::Mat4<TypeParam>::makeReflection(this->_zAxis)); }


TYPED_TEST(Mat4ReflectionFactoryFactoryFPTests,
           AnyUnitPlaneNormal_ReturnsValidReflectionMatrixAcrossThePlanePerpendicularToTheNormal)
{ EXPECT_MAT_EQ(this->_expectedNormReflect, flcn::Mat4<TypeParam>::makeReflection(this->_norm)); }


/** @} */
