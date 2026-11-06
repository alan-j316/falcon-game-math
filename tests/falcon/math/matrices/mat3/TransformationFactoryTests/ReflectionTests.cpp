/**
 * @file ReflectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 09, 2026
 *
 * @brief Verify @ref flcn::Mat3 reflection factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "../Mat3TestSetup.h"

/**
 * @addtogroup T_FALCON_Mat3x3_Transforms
 * @{
 */


namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat3 Reflection across coordinate planes(xy, yz, zx).
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat3ReflectionTests: public testing::Test
    {
    protected:
        flcn::Vec3<T> _xAxis, _yAxis, _zAxis;
        flcn::Mat3<T> _expectedReflectionX, _expectedReflectionY, _expectedReflectionZ, _expectedReflectionXY,
            _expectedReflectionYZ, _expectedReflectionZX, _expectedReflectionOrigin;

        void SetUp() override
        {
            _xAxis = flcn::Vec3{ T(1), T(0), T(0) };
            _yAxis = flcn::Vec3{ T(0), T(1), T(0) };
            _zAxis = flcn::Vec3{ T(0), T(0), T(1) };

            _expectedReflectionX = { flcn::Vec3{ T(1), T(0), T(0) }, flcn::Vec3{ T(0), T(-1), T(0) },
                                     flcn::Vec3{ T(0), T(0), T(-1) } };

            _expectedReflectionY = { flcn::Vec3{ T(-1), T(0), T(0) }, flcn::Vec3{ T(0), T(1), T(0) },
                                     flcn::Vec3{ T(0), T(0), T(-1) } };

            _expectedReflectionZ = { flcn::Vec3{ T(-1), T(0), T(0) }, flcn::Vec3{ T(0), T(-1), T(0) },
                                     flcn::Vec3{ T(0), T(0), T(1) } };

            _expectedReflectionXY = { flcn::Vec3{ T(1), T(0), T(0) }, flcn::Vec3{ T(0), T(1), T(0) },
                                      flcn::Vec3{ T(0), T(0), T(-1) } };

            _expectedReflectionYZ = { flcn::Vec3{ T(-1), T(0), T(0) }, flcn::Vec3{ T(0), T(1), T(0) },
                                      flcn::Vec3{ T(0), T(0), T(1) } };

            _expectedReflectionZX = { flcn::Vec3{ T(1), T(0), T(0) }, flcn::Vec3{ T(0), T(-1), T(0) },
                                      flcn::Vec3{ T(0), T(0), T(1) } };

            _expectedReflectionOrigin = { flcn::Vec3{ T(-1), T(0), T(0) }, flcn::Vec3{ T(0), T(-1), T(0) },
                                          flcn::Vec3{ T(0), T(0), T(-1) } };
        }
    };
    TYPED_TEST_SUITE(Mat3ReflectionTests, SupportedSignedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::Mat3 Reflection across a plane.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat3ReflectionArbitraryPlaneTests: public testing::Test
    {
    protected:
        flcn::Vec3<T> _norm;
        flcn::Mat3<T> _expectedNormReflect;

        void SetUp() override
        {
            _norm = flcn::Vec3{ T(0.3244428422615251), T(0.48666426339228763), T(0.8111071056538127) };

            _expectedNormReflect = {
                flcn::Vec3{ T(0.7894736842105263), T(-0.31578947368421056), T(-0.5263157894736843) },
                flcn::Vec3{ T(-0.31578947368421056), T(0.5263157894736842), T(-0.7894736842105263) },
                flcn::Vec3{ T(-0.5263157894736843), T(-0.7894736842105263), T(-0.3157894736842106) }
            };
        }
    };
    TYPED_TEST_SUITE(Mat3ReflectionArbitraryPlaneTests, SupportedFloatingPointTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that the reflection factory for x-axis return a valid matrix at compile time.
        constexpr auto REFLECTION_MAT_X = flcn::Mat3<int>::makeReflection<flcn::reflect::X>();
        static_assert(REFLECTION_MAT_X(0, 0) == 1);
        static_assert(REFLECTION_MAT_X(0, 1) == 0);
        static_assert(REFLECTION_MAT_X(0, 2) == 0);
        static_assert(REFLECTION_MAT_X(1, 0) == 0);
        static_assert(REFLECTION_MAT_X(1, 1) == -1);
        static_assert(REFLECTION_MAT_X(1, 2) == 0);
        static_assert(REFLECTION_MAT_X(2, 0) == 0);
        static_assert(REFLECTION_MAT_X(2, 1) == 0);
        static_assert(REFLECTION_MAT_X(2, 2) == -1);


        /// @test Verify that the reflection factory for y-axis return a valid matrix at compile time.
        constexpr auto REFLECTION_MAT_Y = flcn::Mat3<int>::makeReflection<flcn::reflect::Y>();
        static_assert(REFLECTION_MAT_Y(0, 0) == -1);
        static_assert(REFLECTION_MAT_Y(0, 1) == 0);
        static_assert(REFLECTION_MAT_Y(0, 2) == 0);
        static_assert(REFLECTION_MAT_Y(1, 0) == 0);
        static_assert(REFLECTION_MAT_Y(1, 1) == 1);
        static_assert(REFLECTION_MAT_Y(1, 2) == 0);
        static_assert(REFLECTION_MAT_Y(2, 0) == 0);
        static_assert(REFLECTION_MAT_Y(2, 1) == 0);
        static_assert(REFLECTION_MAT_Y(2, 2) == -1);


        /// @test Verify that the reflection factory for origin return a valid matrix at compile time.
        constexpr auto REFLECTION_MAT_Z = flcn::Mat3<int>::makeReflection<flcn::reflect::Z>();
        static_assert(REFLECTION_MAT_Z(0, 0) == -1);
        static_assert(REFLECTION_MAT_Z(0, 1) == 0);
        static_assert(REFLECTION_MAT_Z(0, 2) == 0);
        static_assert(REFLECTION_MAT_Z(1, 0) == 0);
        static_assert(REFLECTION_MAT_Z(1, 1) == -1);
        static_assert(REFLECTION_MAT_Z(1, 2) == 0);
        static_assert(REFLECTION_MAT_Z(2, 0) == 0);
        static_assert(REFLECTION_MAT_Z(2, 1) == 0);
        static_assert(REFLECTION_MAT_Z(2, 2) == 1);


        /// @test Verify that the reflection factory for xy-plane return a valid matrix at compile time.
        constexpr auto REFLECTION_MAT_XY = flcn::Mat3<int>::makeReflection<flcn::reflect::XY>();
        static_assert(REFLECTION_MAT_XY(0, 0) == 1);
        static_assert(REFLECTION_MAT_XY(0, 1) == 0);
        static_assert(REFLECTION_MAT_XY(0, 2) == 0);
        static_assert(REFLECTION_MAT_XY(1, 0) == 0);
        static_assert(REFLECTION_MAT_XY(1, 1) == 1);
        static_assert(REFLECTION_MAT_XY(1, 2) == 0);
        static_assert(REFLECTION_MAT_XY(2, 0) == 0);
        static_assert(REFLECTION_MAT_XY(2, 1) == 0);
        static_assert(REFLECTION_MAT_XY(2, 2) == -1);


        /// @test Verify that the reflection factory for yz-plane return a valid matrix at compile time.
        constexpr auto REFLECTION_MAT_YZ = flcn::Mat3<int>::makeReflection<flcn::reflect::YZ>();
        static_assert(REFLECTION_MAT_YZ(0, 0) == -1);
        static_assert(REFLECTION_MAT_YZ(0, 1) == 0);
        static_assert(REFLECTION_MAT_YZ(0, 2) == 0);
        static_assert(REFLECTION_MAT_YZ(1, 0) == 0);
        static_assert(REFLECTION_MAT_YZ(1, 1) == 1);
        static_assert(REFLECTION_MAT_YZ(1, 2) == 0);
        static_assert(REFLECTION_MAT_YZ(2, 0) == 0);
        static_assert(REFLECTION_MAT_YZ(2, 1) == 0);
        static_assert(REFLECTION_MAT_YZ(2, 2) == 1);


        /// @test Verify that the reflection factory for zx-plane return a valid matrix at compile time.
        constexpr auto REFLECTION_MAT_ZX = flcn::Mat3<int>::makeReflection<flcn::reflect::ZX>();
        static_assert(REFLECTION_MAT_ZX(0, 0) == 1);
        static_assert(REFLECTION_MAT_ZX(0, 1) == 0);
        static_assert(REFLECTION_MAT_ZX(0, 2) == 0);
        static_assert(REFLECTION_MAT_ZX(1, 0) == 0);
        static_assert(REFLECTION_MAT_ZX(1, 1) == -1);
        static_assert(REFLECTION_MAT_ZX(1, 2) == 0);
        static_assert(REFLECTION_MAT_ZX(2, 0) == 0);
        static_assert(REFLECTION_MAT_ZX(2, 1) == 0);
        static_assert(REFLECTION_MAT_ZX(2, 2) == 1);

        /// @test Verify that the reflection factory for origin return a valid matrix at compile time.
        constexpr auto REFLECTION_MAT_ORIGIN = flcn::Mat3<int>::makeReflection<flcn::reflect::ORIGIN>();
        static_assert(REFLECTION_MAT_ORIGIN(0, 0) == -1);
        static_assert(REFLECTION_MAT_ORIGIN(0, 1) == 0);
        static_assert(REFLECTION_MAT_ORIGIN(0, 2) == 0);
        static_assert(REFLECTION_MAT_ORIGIN(1, 0) == 0);
        static_assert(REFLECTION_MAT_ORIGIN(1, 1) == -1);
        static_assert(REFLECTION_MAT_ORIGIN(1, 2) == 0);
        static_assert(REFLECTION_MAT_ORIGIN(2, 0) == 0);
        static_assert(REFLECTION_MAT_ORIGIN(2, 1) == 0);
        static_assert(REFLECTION_MAT_ORIGIN(2, 2) == -1);


        /// @test Verify that the general reflection factory for x-axis return a valid matrix at compile time.
        constexpr auto REFLECTION_MAT_X_NORM = flcn::Mat3<int>::makeReflection(flcn::Vec3(1, 0, 0));
        static_assert(REFLECTION_MAT_X_NORM(0, 0) == -1);
        static_assert(REFLECTION_MAT_X_NORM(0, 1) == 0);
        static_assert(REFLECTION_MAT_X_NORM(0, 2) == 0);
        static_assert(REFLECTION_MAT_X_NORM(1, 0) == 0);
        static_assert(REFLECTION_MAT_X_NORM(1, 1) == 1);
        static_assert(REFLECTION_MAT_X_NORM(1, 2) == 0);
        static_assert(REFLECTION_MAT_X_NORM(2, 0) == 0);
        static_assert(REFLECTION_MAT_X_NORM(2, 1) == 0);
        static_assert(REFLECTION_MAT_X_NORM(2, 2) == 1);


        /// @test Verify that the general reflection factory for y-axis return a valid matrix at compile time.
        constexpr auto REFLECTION_MAT_Y_NORM = flcn::Mat3<int>::makeReflection(flcn::Vec3(0, 1, 0));
        static_assert(REFLECTION_MAT_Y_NORM(0, 0) == 1);
        static_assert(REFLECTION_MAT_Y_NORM(0, 1) == 0);
        static_assert(REFLECTION_MAT_Y_NORM(0, 2) == 0);
        static_assert(REFLECTION_MAT_Y_NORM(1, 0) == 0);
        static_assert(REFLECTION_MAT_Y_NORM(1, 1) == -1);
        static_assert(REFLECTION_MAT_Y_NORM(1, 2) == 0);
        static_assert(REFLECTION_MAT_Y_NORM(2, 0) == 0);
        static_assert(REFLECTION_MAT_Y_NORM(2, 1) == 0);
        static_assert(REFLECTION_MAT_Y_NORM(2, 2) == 1);


        /// @test Verify that the general reflection factory for z-axis return a valid matrix at compile time.
        constexpr auto REFLECTION_MAT_Z_NORM = flcn::Mat3<int>::makeReflection(flcn::Vec3(0, 0, 1));
        static_assert(REFLECTION_MAT_Z_NORM(0, 0) == 1);
        static_assert(REFLECTION_MAT_Z_NORM(0, 1) == 0);
        static_assert(REFLECTION_MAT_Z_NORM(0, 2) == 0);
        static_assert(REFLECTION_MAT_Z_NORM(1, 0) == 0);
        static_assert(REFLECTION_MAT_Z_NORM(1, 1) == 1);
        static_assert(REFLECTION_MAT_Z_NORM(1, 2) == 0);
        static_assert(REFLECTION_MAT_Z_NORM(2, 0) == 0);
        static_assert(REFLECTION_MAT_Z_NORM(2, 1) == 0);
        static_assert(REFLECTION_MAT_Z_NORM(2, 2) == -1);


    } // namespace static_tests
} // namespace


/**************************************
 *          REFLECTION TESTS          *
 **************************************/

TYPED_TEST(Mat3ReflectionTests, X_ReturnsMatrixWithNegatedYZ)
{ EXPECT_MAT_EQ(this->_expectedReflectionX, flcn::Mat3<TypeParam>::template makeReflection<flcn::reflect::X>()); }


TYPED_TEST(Mat3ReflectionTests, Y_ReturnsMatrixWithNegatedXZ)
{ EXPECT_MAT_EQ(this->_expectedReflectionY, flcn::Mat3<TypeParam>::template makeReflection<flcn::reflect::Y>()); }


TYPED_TEST(Mat3ReflectionTests, Z_ReturnsMatrixWithNegatedXY)
{ EXPECT_MAT_EQ(this->_expectedReflectionZ, flcn::Mat3<TypeParam>::template makeReflection<flcn::reflect::Z>()); }


TYPED_TEST(Mat3ReflectionTests, XY_ReturnsMatrixWithNegatedZ)
{ EXPECT_MAT_EQ(this->_expectedReflectionXY, flcn::Mat3<TypeParam>::template makeReflection<flcn::reflect::XY>()); }


TYPED_TEST(Mat3ReflectionTests, YZ_ReturnsMatrixWithNegatedX)
{ EXPECT_MAT_EQ(this->_expectedReflectionYZ, flcn::Mat3<TypeParam>::template makeReflection<flcn::reflect::YZ>()); }


TYPED_TEST(Mat3ReflectionTests, ZX_ReturnsMatrixWithNegatedY)
{ EXPECT_MAT_EQ(this->_expectedReflectionZX, flcn::Mat3<TypeParam>::template makeReflection<flcn::reflect::ZX>()); }


TYPED_TEST(Mat3ReflectionTests, Origin_ReturnsMatrixWithNegatedXYZ)
{
    EXPECT_MAT_EQ(this->_expectedReflectionOrigin,
                  flcn::Mat3<TypeParam>::template makeReflection<flcn::reflect::ORIGIN>());
}


/**
 * @test Verify that reflection transformation factory(makeReflection(normal)) along x-axis
 *        returns a reflection matrix across yz-plane.
 */
TYPED_TEST(Mat3ReflectionTests, PlaneNormalReflection_X_ReturnsYZReflectionMatrix)
{ EXPECT_MAT_EQ(this->_expectedReflectionYZ, flcn::Mat3<TypeParam>::makeReflection(this->_xAxis)); }


/**
 * @test Verify that reflection transformation factory(makeReflection(normal)) for y-axis
 *        returns a reflection matrix across zx-plane.
 */
TYPED_TEST(Mat3ReflectionTests, PlaneNormalReflection_Y_ReturnsZXReflectionMatrix)
{ EXPECT_MAT_EQ(this->_expectedReflectionZX, flcn::Mat3<TypeParam>::makeReflection(this->_yAxis)); }


/**
 * @test Verify that reflection transformation factory(makeReflection(normal)) for z-axis
 *        returns a reflection matrix across xy-plane.
 */
TYPED_TEST(Mat3ReflectionTests, PlaneNormalReflection_Z_ReturnsXYReflectionMatrix)
{ EXPECT_MAT_EQ(this->_expectedReflectionXY, flcn::Mat3<TypeParam>::makeReflection(this->_zAxis)); }



/**
 * @test Verify that reflection transformation factory(makeReflection(normal)) for a plane normal
 *        returns a reflection matrix.
 */
TYPED_TEST(Mat3ReflectionArbitraryPlaneTests, ReturnsCorrectReflectionMatrix)
{ EXPECT_MAT_EQ(this->_expectedNormReflect, flcn::Mat3<TypeParam>::makeReflection(this->_norm)); }

/** @} */
