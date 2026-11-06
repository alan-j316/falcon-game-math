/**
 * @file RotationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 08, 2026
 *
 * @brief Verify @ref flcn::Mat3 rotation factory logic.
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
     * @brief Test fixture for @ref flcn::Mat3 Rotation Factory (integrals).
     *
     * @tparam T The numeric type (int, long...) for matrix values.
     */
    template <typename T>
    class Mat3RotationTests: public testing::Test
    {
    protected:
        using FP_T  = T::first_type;  // FP_T -> Floating-point Type
        using COM_T = T::second_type; // COM_T -> Common Type

        FP_T _angle;
        flcn::Mat3<COM_T> _expectedMatX, _expectedMatY, _expectedMatZ;


        void SetUp() override
        {
            _angle = flcn::constants::PI<FP_T> / FP_T(2.0);
#ifdef FALCON_LEFT_HANDED
            _expectedMatX = { flcn::Vec3{ COM_T(1), COM_T(0), COM_T(0) }, flcn::Vec3{ COM_T(0), COM_T(0), COM_T(-1) },
                              flcn::Vec3 {
                                  COM_T(0),
                                  COM_T(1),
                                  COM_T(0)
                              } };
            _expectedMatY = { flcn::Vec3{ COM_T(0), COM_T(0), COM_T(1) }, flcn::Vec3{ COM_T(0), COM_T(1), COM_T(0) },
                              flcn::Vec3 {
                                  COM_T(-1),
                                  COM_T(0),
                                  COM_T(0)
                              } };
            _expectedMatZ = { flcn::Vec3{ COM_T(0), COM_T(-1), COM_T(0) }, flcn::Vec3{ COM_T(1), COM_T(0), COM_T(0) },
                              flcn::Vec3 {
                                  COM_T(0),
                                  COM_T(0),
                                  COM_T(1)
                              } };
#else
            _expectedMatX = { flcn::Vec3{ COM_T(1), COM_T(0), COM_T(0) }, flcn::Vec3{ COM_T(0), COM_T(0), COM_T(1) },
                              flcn::Vec3{ COM_T(0), COM_T(-1), COM_T(0) } };
            _expectedMatY = { flcn::Vec3{ COM_T(0), COM_T(0), COM_T(-1) }, flcn::Vec3{ COM_T(0), COM_T(1), COM_T(0) },
                              flcn::Vec3{ COM_T(1), COM_T(0), COM_T(0) } };
            _expectedMatZ = { flcn::Vec3{ COM_T(0), COM_T(1), COM_T(0) }, flcn::Vec3{ COM_T(-1), COM_T(0), COM_T(0) },
                              flcn::Vec3{ COM_T(0), COM_T(0), COM_T(1) } };

#endif
        }
    };
    TYPED_TEST_SUITE(Mat3RotationTests, SupportedSignedArithmeticFloatingTypePair);



    /**
     * @brief Test fixture for @ref flcn::Mat3 Rotation Factory(Floating Point Numbers).
     *
     * @tparam T The numeric type (float, double) for matrix values.
     */
    template <typename T>
    class Mat3RotationFloatTests: public testing::Test
    {
    protected:
        T _angle;
        flcn::CVec2<T> _center;
        flcn::Vec3<T> _axis;
        flcn::Mat3<T> _expectedMatX, _expectedMatY, _expectedMatZ, _expectedMatXYZ, _expectedMatCenter,
            _expectedAxisRotation;


        void SetUp() override
        {
            _angle  = flcn::constants::PI<T> / T(4.0);
            _center = flcn::CVec2{ T(1), T(2) };
            _axis   = flcn::Vec3{ T(0.26726124191242440), T(0.53452248382484879), T(0.80178372573727319) };

#ifdef FALCON_LEFT_HANDED
            _expectedMatX = { flcn::Vec3{ T(1.0), T(0.0), T(0.0) },
                              flcn::Vec3{ T(0.0), T(0.70710678118654757), T(-0.70710678118654757) }, flcn::Vec3 {
                                  T(0.0),
                                  T(0.70710678118654757),
                                  T(0.70710678118654757)
                              } };

            _expectedMatY = { flcn::Vec3{ T(0.70710678118654757), T(0.0), T(0.70710678118654757) },
                              flcn::Vec3{ T(0.0), T(1.0), T(0.0) }, flcn::Vec3 {
                                  T(-0.70710678118654757),
                                  T(0.0),
                                  T(0.70710678118654757)
                              } };

            _expectedMatZ = { flcn::Vec3{ T(0.70710678118654757), T(-0.70710678118654757), T(0.0) },
                              flcn::Vec3{ T(0.70710678118654757), T(0.70710678118654757), T(0.0) }, flcn::Vec3 {
                                  T(0.0),
                                  T(0.0),
                                  T(1.0)
                              } };

            _expectedMatXYZ = { flcn::Vec3{ T(0.5), T(0.5), T(-0.70710678118654757) },
                                flcn::Vec3{ T(-0.14644660940672627), T(0.85355339059327395), T(0.5) }, flcn::Vec3 {
                                    T(0.85355339059327395),
                                    T(-0.14644660940672627),
                                    T(0.5)
                                } };

            _expectedMatCenter    = { flcn::Vec3{ T(0.70710678118654757), T(-0.70710678118654757), T(0.0) },
                                      flcn::Vec3{ T(0.70710678118654757), T(0.70710678118654757), T(0.0) }, flcn::Vec3 {
                                       T(1.0),
                                       T(2.0),
                                       T(1.0)
                                   } };
            _expectedAxisRotation = {
                flcn::Vec3{ T(0.72802772538750848), T(-0.52510482111191903), T(0.44072730561210993) },
                flcn::Vec3{ T(0.60878859791576267), T(0.79079055799039111), T(-0.06345657129884830) },
                flcn::Vec3{ T(-0.31520164040634457), T(0.31450790171037896), T(0.89539527899519555) },
            };

#else

            _expectedMatX = { flcn::Vec3{ T(1.0), T(0.0), T(0.0) },
                              flcn::Vec3{ T(0.0), T(0.70710678118654757), T(0.70710678118654757) },
                              flcn::Vec3{ T(0.0), T(-0.70710678118654757), T(0.70710678118654757) } };

            _expectedMatY = { flcn::Vec3{ T(0.70710678118654757), T(0.0), T(-0.70710678118654757) },
                              flcn::Vec3{ T(0.0), T(1.0), T(0.0) },
                              flcn::Vec3{ T(0.70710678118654757), T(0.0), T(0.70710678118654757) } };

            _expectedMatZ = { flcn::Vec3{ T(0.70710678118654757), T(0.70710678118654757), T(0.0) },
                              flcn::Vec3{ T(-0.70710678118654757), T(0.70710678118654757), T(0.0) },
                              flcn::Vec3{ T(0.0), T(0.0), T(1.0) } };

            _expectedMatCenter = { flcn::Vec3{ T(0.70710678118654757), T(0.70710678118654757), T(0.0) },
                                   flcn::Vec3{ T(-0.70710678118654757), T(0.70710678118654757), T(0.0) },
                                   flcn::Vec3{ T(1.0), T(2.0), T(1.0) } };

            _expectedMatXYZ = { flcn::Vec3{ T(0.5), T(0.5), T(-0.70710678118654757) },
                                flcn::Vec3{ T(-0.14644660940672627), T(0.85355339059327395), T(0.5) },
                                flcn::Vec3{ T(0.85355339059327395), T(-0.14644660940672627), T(0.5) } };

            _expectedAxisRotation = {
                flcn::Vec3{ T(0.72802772538750848), T(0.60878859791576267), T(-0.31520164040634457) },
                flcn::Vec3{ T(-0.52510482111191903), T(0.79079055799039111), T(0.31450790171037896) },
                flcn::Vec3{ T(0.44072730561210993), T(-0.06345657129884830), T(0.89539527899519555) }
            };

#endif
        }
    };
    TYPED_TEST_SUITE(Mat3RotationFloatTests, SupportedFloatingPointTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
// TODO: Add static tests after making trig functions constexpr
#if __cplusplus >= 202603L // TODO: Add static tests after making trig functions constexpr
        // Rotation matrix for 180° or 2π radians
        constexpr auto ROTATION_MAT = flcn::Mat3<int>::rotate(flcn::constants::PI<float>);
        static_assert(ROTATION_MAT(0, 0) == 1);
        static_assert(ROTATION_MAT(0, 1) == 0);
        static_assert(ROTATION_MAT(0, 2) == 0);
        static_assert(ROTATION_MAT(1, 0) == 0);
        static_assert(ROTATION_MAT(1, 1) == -1);
        static_assert(ROTATION_MAT(1, 2) == 0);
        static_assert(ROTATION_MAT(2, 0) == 0);
        static_assert(ROTATION_MAT(2, 1) == 0);
        static_assert(ROTATION_MAT(2, 2) == -1);
#endif
    } // namespace static_tests
} // namespace


/**************************************
 *           RUNTIME TESTS            *
 **************************************/

/** @test Verify that rotation transformation factory for x returns a rotation matrix. */
TYPED_TEST(Mat3RotationTests, X_ReturnsAValidRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatX, flcn::Mat3<typename TypeParam::first_type>::makeRotationX(this->_angle)); }


/** @test Verify that rotation transformation factory for x returns a rotation matrix for non-integral values. */
TYPED_TEST(Mat3RotationFloatTests, X_ReturnsAValidRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatX, flcn::Mat3<TypeParam>::makeRotationX(this->_angle)); }


/** @test Verify that rotation transformation factory for y returns a rotation matrix. */
TYPED_TEST(Mat3RotationTests, Y_ReturnsAValidRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatY, flcn::Mat3<typename TypeParam::first_type>::makeRotationY(this->_angle)); }


/** @test Verify that rotation transformation factory for y returns a rotation matrix for non-integral values. */
TYPED_TEST(Mat3RotationFloatTests, Y_ReturnsAValidRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatY, flcn::Mat3<TypeParam>::makeRotationY(this->_angle)); }


/** @test Verify that rotation transformation factory for z returns a rotation matrix. */
TYPED_TEST(Mat3RotationTests, Z_ReturnsAValidRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatZ, flcn::Mat3<typename TypeParam::first_type>::makeRotationZ(this->_angle)); }


/** @test Verify that rotation transformation factory for z returns a rotation matrix for non-integral values. */
TYPED_TEST(Mat3RotationFloatTests, Z_ReturnsAValidRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatZ, flcn::Mat3<TypeParam>::makeRotationZ(this->_angle)); }


/** @test Verify that rotation transformation factory for 2D returns a rotation matrix with translation. */
TYPED_TEST(Mat3RotationFloatTests, Z_NonOriginCenter_ReturnsAValidRotationMatrixWithTranslation)
{ EXPECT_MAT_EQ(this->_expectedMatCenter, flcn::Mat3<TypeParam>::makeRotation(this->_angle, this->_center)); }

/**
 * @test Verify that rotation transformation factory for an axis returns a rotation matrix.
 */
TYPED_TEST(Mat3RotationFloatTests, AxisAligned_ReturnsAValidRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedAxisRotation, flcn::Mat3<TypeParam>::makeRotation(this->_angle, this->_axis)); }


/** @} */
