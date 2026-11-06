/**
 * @file RotationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 08, 2026
 *
 * @brief Verify @ref flcn::Mat4 rotation factory logic.
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
     * @brief Test fixture for @ref flcn::Mat4 Rotation Factory (integrals).
     *
     * @tparam T The numeric type (int, long...) for matrix values.
     */
    template <typename T>
    class Mat4RotationTests: public testing::Test
    {
    protected:
        using FP_T  = T::first_type;  // FP_T -> Floating-point Type
        using COM_T = T::second_type; // COM_T -> Common Type

        FP_T _angle;
        flcn::Mat4<COM_T> _expectedMatX, _expectedMatY, _expectedMatZ, _expectedMatXYZ;


        void SetUp() override
        {
            _angle = flcn::constants::PI<FP_T> / FP_T(2.0);

#ifdef FALCON_LEFT_HANDED
            _expectedMatX   = { flcn::Vec4{ COM_T(1), COM_T(0), COM_T(0), COM_T(0) },
                                flcn::Vec4{ COM_T(0), COM_T(0), COM_T(-1), COM_T(0) },
                                flcn::Vec4{ COM_T(0), COM_T(1), COM_T(0), COM_T(0) }, flcn::Vec4 {
                                  COM_T(0),
                                  COM_T(0),
                                  COM_T(0),
                                  COM_T(1)
                              } };
            _expectedMatY   = { flcn::Vec4{ COM_T(0), COM_T(0), COM_T(1), COM_T(0) },
                                flcn::Vec4{ COM_T(0), COM_T(1), COM_T(0), COM_T(0) },
                                flcn::Vec4{ COM_T(-1), COM_T(0), COM_T(0), COM_T(0) }, flcn::Vec4 {
                                  COM_T(0),
                                  COM_T(0),
                                  COM_T(0),
                                  COM_T(1)
                              } };
            _expectedMatZ   = { flcn::Vec4{ COM_T(0), COM_T(-1), COM_T(0), COM_T(0) },
                                flcn::Vec4{ COM_T(1), COM_T(0), COM_T(0), COM_T(0) },
                                flcn::Vec4{ COM_T(0), COM_T(0), COM_T(1), COM_T(0) }, flcn::Vec4 {
                                  COM_T(0),
                                  COM_T(0),
                                  COM_T(0),
                                  COM_T(1)
                              } };
            _expectedMatXYZ = { flcn::Vec4{ COM_T(0), COM_T(0), COM_T(1), COM_T(0) },
                                flcn::Vec4{ COM_T(0), COM_T(-1), COM_T(0), COM_T(0) },
                                flcn::Vec4{ COM_T(1), COM_T(0), COM_T(0), COM_T(0) }, flcn::Vec4 {
                                    COM_T(0),
                                    COM_T(0),
                                    COM_T(0),
                                    COM_T(1)
                                } };
#else
            _expectedMatX   = { flcn::Vec4{ COM_T(1), COM_T(0), COM_T(0), COM_T(0) },
                                flcn::Vec4{ COM_T(0), COM_T(0), COM_T(1), COM_T(0) },
                                flcn::Vec4{ COM_T(0), COM_T(-1), COM_T(0), COM_T(0) },
                                flcn::Vec4{ COM_T(0), COM_T(0), COM_T(0), COM_T(1) } };
            _expectedMatY   = { flcn::Vec4{ COM_T(0), COM_T(0), COM_T(-1), COM_T(0) },
                                flcn::Vec4{ COM_T(0), COM_T(1), COM_T(0), COM_T(0) },
                                flcn::Vec4{ COM_T(1), COM_T(0), COM_T(0), COM_T(0) },
                                flcn::Vec4{ COM_T(0), COM_T(0), COM_T(0), COM_T(1) } };
            _expectedMatZ   = { flcn::Vec4{ COM_T(0), COM_T(1), COM_T(0), COM_T(0) },
                                flcn::Vec4{ COM_T(-1), COM_T(0), COM_T(0), COM_T(0) },
                                flcn::Vec4{ COM_T(0), COM_T(0), COM_T(1), COM_T(0) },
                                flcn::Vec4{ COM_T(0), COM_T(0), COM_T(0), COM_T(1) } };
            _expectedMatXYZ = { flcn::Vec4{ COM_T(0), COM_T(0), COM_T(-1), COM_T(0) },
                                flcn::Vec4{ COM_T(0), COM_T(1), COM_T(0), COM_T(0) },
                                flcn::Vec4{ COM_T(1), COM_T(0), COM_T(0), COM_T(0) },
                                flcn::Vec4{ COM_T(0), COM_T(0), COM_T(0), COM_T(1) } };

#endif
        }
    };
    /**
     * @brief Test fixture for @ref flcn::Mat4 rotation factory, parameterized
     *        @ref SupportedSignedArithmeticFloatingTypePair
     */
    TYPED_TEST_SUITE(Mat4RotationTests, SupportedSignedArithmeticFloatingTypePair);



    /**
     * @brief Test fixture for @ref flcn::Mat4 Rotation Factory(Floating Point Numbers).
     *
     * @tparam T The numeric type (float, double) for matrix values.
     */
    template <typename T>
    class Mat4FloatRotationTests: public testing::Test
    {
    protected:
        T _angle;
        flcn::Vec3<T> _axis, _center;
        flcn::Mat4<T> _expectedMatX, _expectedMatY, _expectedMatZ, _expectedMatXYZ, _expectedAxisRotation;
        flcn::Mat4<T> _expectedMatXCenter, _expectedMatYCenter, _expectedMatZCenter, _expectedMatXYZCenter,
            _expectedAxisRotationCenter;


        void SetUp() override
        {
            _angle  = flcn::constants::PI<T> / T(4.0);
            _center = flcn::Vec3{ T(1), T(2), T(3) };
            _axis   = flcn::Vec3{ T(0.26726124191242440), T(0.53452248382484879), T(0.80178372573727319) };

#ifdef FALCON_LEFT_HANDED
            _expectedMatX = { flcn::Vec4{ T(1.0), T(0.0), T(0.0), T(0.0) },
                              flcn::Vec4{ T(0.0), T(0.70710678118654757), T(-0.70710678118654757), T(0.0) },
                              flcn::Vec4{ T(0.0), T(0.70710678118654757), T(0.70710678118654757), T(0.0) }, flcn::Vec4 {
                                  T(0.0),
                                  T(0.0),
                                  T(0.0),
                                  T(1.0)
                              } };

            _expectedMatY = { flcn::Vec4{ T(0.70710678118654757), T(0.0), T(0.70710678118654757), T(0.0) },
                              flcn::Vec4{ T(0.0), T(1.0), T(0.0), T(0.0) },
                              flcn::Vec4{ T(-0.70710678118654757), T(0.0), T(0.70710678118654757), T(0.0) }, flcn::Vec4 {
                                  T(0.0),
                                  T(0.0),
                                  T(0.0),
                                  T(1.0)
                              } };

            _expectedMatZ = { flcn::Vec4{ T(0.70710678118654757), T(-0.70710678118654757), T(0.0), T(0.0) },
                              flcn::Vec4{ T(0.70710678118654757), T(0.70710678118654757), T(0.0), T(0.0) },
                              flcn::Vec4{ T(0.0), T(0.0), T(1.0), T(0.0) }, flcn::Vec4 {
                                  T(0.0),
                                  T(0.0),
                                  T(0.0),
                                  T(1.0)
                              } };

            _expectedMatXYZ = { flcn::Vec4{ T(0.5), T(0.5), T(-0.70710678118654757), T(0.0) },
                                flcn::Vec4{ T(-0.14644660940672627), T(0.85355339059327395), T(0.5), T(0.0) },
                                flcn::Vec4{ T(0.85355339059327395), T(-0.14644660940672627), T(0.5), T(0.0) },
                                flcn::Vec4 {
                                    T(0.0),
                                    T(0.0),
                                    T(0.0),
                                    T(1.0)
                                } };

            _expectedAxisRotation = {
                flcn::Vec4{ T(0.72802772538750848), T(0.60878859791576267), T(-0.31520164040634457), T(0.0) },
                flcn::Vec4{ T(-0.52510482111191903), T(0.79079055799039111), T(0.31450790171037896), T(0.0) },
                flcn::Vec4{ T(0.44072730561210993), T(-0.06345657129884830), T(0.89539527899519555), T(0.0) },
                flcn::Vec4 {
                    T(0.0),
                    T(0.0),
                    T(0.0),
                    T(1.0)
                }
            };

            _expectedMatXCenter = { flcn::Vec4{ T(1.0), T(0.0), T(0.0), T(0.0) },
                                    flcn::Vec4{ T(0.0), T(0.70710678118654757), T(-0.70710678118654757), T(0.0) },
                                    flcn::Vec4{ T(0.0), T(0.70710678118654757), T(0.70710678118654757), T(0.0) },
                                    flcn::Vec4 {
                                        T(1.0),
                                        T(2.0),
                                        T(3.0),
                                        T(1.0)
                                    } };

            _expectedMatYCenter = { flcn::Vec4{ T(0.70710678118654757), T(0.0), T(0.70710678118654757), T(0.0) },
                                    flcn::Vec4{ T(0.0), T(1.0), T(0.0), T(0.0) },
                                    flcn::Vec4{ T(-0.70710678118654757), T(0.0), T(0.70710678118654757), T(0.0) },
                                    flcn::Vec4 {
                                        T(1.0),
                                        T(2.0),
                                        T(3.0),
                                        T(1.0)
                                    } };

            _expectedMatZCenter = { flcn::Vec4{ T(0.70710678118654757), T(-0.70710678118654757), T(0.0), T(0.0) },
                                    flcn::Vec4{ T(0.70710678118654757), T(0.70710678118654757), T(0.0), T(0.0) },
                                    flcn::Vec4{ T(0.0), T(0.0), T(1.0), T(0.0) }, flcn::Vec4 {
                                        T(1.0),
                                        T(2.0),
                                        T(3.0),
                                        T(1.0)
                                    } };

            _expectedMatXYZCenter = { flcn::Vec4{ T(0.5), T(0.5), T(-0.70710678118654757), T(0.0) },
                                      flcn::Vec4{ T(-0.14644660940672627), T(0.85355339059327395), T(0.5), T(0.0) },
                                      flcn::Vec4{ T(0.85355339059327395), T(-0.14644660940672627), T(0.5), T(0.0) },
                                      flcn::Vec4 {
                                          T(1.0),
                                          T(2.0),
                                          T(3.0),
                                          T(1.0)
                                      } };
            _expectedAxisRotation = {
                flcn::Vec4{ T(0.72802772538750848), T(-0.52510482111191903), T(0.44072730561210993), T(0.0) },
                flcn::Vec4{ T(0.60878859791576267), T(0.79079055799039111), T(-0.06345657129884830), T(0.0) },
                flcn::Vec4{ T(-0.31520164040634457), T(0.31450790171037896), T(0.89539527899519555), T(0.0) },
                flcn::Vec4 {
                    T(0.0),
                    T(0.0),
                    T(0.0),
                    T(1.0)
                }
            };

            _expectedAxisRotationCenter = {
                flcn::Vec4{ T(0.72802772538750848), T(-0.52510482111191903), T(0.44072730561210993), T(0.0) },
                flcn::Vec4{ T(0.60878859791576267), T(0.79079055799039111), T(-0.06345657129884830), T(0.0) },
                flcn::Vec4{ T(-0.31520164040634457), T(0.31450790171037896), T(0.89539527899519555), T(0.0) },
                flcn::Vec4 {
                    T(1.0),
                    T(2.0),
                    T(3.0),
                    T(1.0)
                }
            };

#else

            _expectedMatX = { flcn::Vec4{ T(1.0), T(0.0), T(0.0), T(0.0) },
                              flcn::Vec4{ T(0.0), T(0.70710678118654757), T(0.70710678118654757), T(0.0) },
                              flcn::Vec4{ T(0.0), T(-0.70710678118654757), T(0.70710678118654757), T(0.0) },
                              flcn::Vec4{ T(0.0), T(0.0), T(0.0), T(1.0) } };

            _expectedMatY = { flcn::Vec4{ T(0.70710678118654757), T(0.0), T(-0.70710678118654757), T(0.0) },
                              flcn::Vec4{ T(0.0), T(1.0), T(0.0), T(0.0) },
                              flcn::Vec4{ T(0.70710678118654757), T(0.0), T(0.70710678118654757), T(0.0) },
                              flcn::Vec4{ T(0.0), T(0.0), T(0.0), T(1.0) } };

            _expectedMatZ = { flcn::Vec4{ T(0.70710678118654757), T(0.70710678118654757), T(0.0), T(0.0) },
                              flcn::Vec4{ T(-0.70710678118654757), T(0.70710678118654757), T(0.0), T(0.0) },
                              flcn::Vec4{ T(0.0), T(0.0), T(1.0), T(0.0) },
                              flcn::Vec4{ T(0.0), T(0.0), T(0.0), T(1.0) } };

            _expectedMatXYZ = { flcn::Vec4{ T(0.5), T(0.5), T(-0.70710678118654757), T(0.0) },
                                flcn::Vec4{ T(-0.14644660940672627), T(0.85355339059327395), T(0.5), T(0.0) },
                                flcn::Vec4{ T(0.85355339059327395), T(-0.14644660940672627), T(0.5), T(0.0) },
                                flcn::Vec4{ T(0.0), T(0.0), T(0.0), T(1.0) } };

            _expectedAxisRotation = {
                flcn::Vec4{ T(0.72802772538750848), T(0.60878859791576267), T(-0.31520164040634457), T(0.0) },
                flcn::Vec4{ T(-0.52510482111191903), T(0.79079055799039111), T(0.31450790171037896), T(0.0) },
                flcn::Vec4{ T(0.44072730561210993), T(-0.06345657129884830), T(0.89539527899519555), T(0.0) },
                flcn::Vec4{ T(0.0), T(0.0), T(0.0), T(1.0) }
            };

            _expectedMatXCenter = { flcn::Vec4{ T(1.0), T(0.0), T(0.0), T(0.0) },
                                    flcn::Vec4{ T(0.0), T(0.70710678118654757), T(0.70710678118654757), T(0.0) },
                                    flcn::Vec4{ T(0.0), T(-0.70710678118654757), T(0.70710678118654757), T(0.0) },
                                    flcn::Vec4{ T(1.0), T(2.0), T(3.0), T(1.0) } };

            _expectedMatYCenter = { flcn::Vec4{ T(0.70710678118654757), T(0.0), T(-0.70710678118654757), T(0.0) },
                                    flcn::Vec4{ T(0.0), T(1.0), T(0.0), T(0.0) },
                                    flcn::Vec4{ T(0.70710678118654757), T(0.0), T(0.70710678118654757), T(0.0) },
                                    flcn::Vec4{ T(1.0), T(2.0), T(3.0), T(1.0) } };

            _expectedMatZCenter = { flcn::Vec4{ T(0.70710678118654757), T(0.70710678118654757), T(0.0), T(0.0) },
                                    flcn::Vec4{ T(-0.70710678118654757), T(0.70710678118654757), T(0.0), T(0.0) },
                                    flcn::Vec4{ T(0.0), T(0.0), T(1.0), T(0.0) },
                                    flcn::Vec4{ T(1.0), T(2.0), T(3.0), T(1.0) } };

            _expectedMatXYZCenter = { flcn::Vec4{ T(0.5), T(0.5), T(-0.70710678118654757), T(0.0) },
                                      flcn::Vec4{ T(-0.14644660940672627), T(0.85355339059327395), T(0.5), T(0.0) },
                                      flcn::Vec4{ T(0.85355339059327395), T(-0.14644660940672627), T(0.5), T(0.0) },
                                      flcn::Vec4{ T(1.0), T(2.0), T(3.0), T(1.0) } };

            _expectedAxisRotationCenter = {
                flcn::Vec4{ T(0.72802772538750848), T(0.60878859791576267), T(-0.31520164040634457), T(0.0) },
                flcn::Vec4{ T(-0.52510482111191903), T(0.79079055799039111), T(0.31450790171037896), T(0.0) },
                flcn::Vec4{ T(0.44072730561210993), T(-0.06345657129884830), T(0.89539527899519555), T(0.0) },
                flcn::Vec4{ T(1.0), T(2.0), T(3.0), T(1.0) }
            };

#endif
        }
    };
    TYPED_TEST_SUITE(Mat4FloatRotationTests, SupportedFloatingPointTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        // TODO: Add static tests after making trig functions constexpr
    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

/** @test Verify that rotation transformation factory for x returns a rotation matrix. */
TYPED_TEST(Mat4RotationTests, X_ReturnsAValidRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatX, flcn::Mat4<typename TypeParam::first_type>::makeRotationX(this->_angle)); }


/**
 * @test Verify that rotation transformation factory for x returns a rotation matrix for non-integral rotation values.
 */
TYPED_TEST(Mat4FloatRotationTests, X_ReturnsAValidRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatX, flcn::Mat4<TypeParam>::makeRotationX(this->_angle)); }


/**
 * @test Verify that rotation transformation factory for x around arbitrary center includes translation to that point.
 */
TYPED_TEST(Mat4FloatRotationTests, X_NonOriginCenter_ReturnsAValidRotationMatrixWithTranslation)
{ EXPECT_MAT_EQ(this->_expectedMatXCenter, flcn::Mat4<TypeParam>::makeRotationX(this->_angle, this->_center)); }


/** @test Verify that rotation transformation factory for y returns a rotation matrix. */
TYPED_TEST(Mat4RotationTests, Y_ReturnsAValidRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatY, flcn::Mat4<typename TypeParam::first_type>::makeRotationY(this->_angle)); }


/**
 * @test Verify that rotation transformation factory for y returns a rotation matrix for non-integral rotation values.
 */
TYPED_TEST(Mat4FloatRotationTests, Y_ReturnsAValidRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatY, flcn::Mat4<TypeParam>::makeRotationY(this->_angle)); }


/**
 * @test Verify that rotation transformation factory for y around arbitrary center includes translation to that point.
 */
TYPED_TEST(Mat4FloatRotationTests, Y_NonOriginCenter_ReturnsAValidRotationMatrixWithTranslation)
{ EXPECT_MAT_EQ(this->_expectedMatYCenter, flcn::Mat4<TypeParam>::makeRotationY(this->_angle, this->_center)); }


/** @test Verify that rotation transformation factory for y returns a rotation matrix. */
TYPED_TEST(Mat4RotationTests, Z_ReturnsAValidRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatZ, flcn::Mat4<typename TypeParam::first_type>::makeRotationZ(this->_angle)); }


/**
 * @test Verify that rotation transformation factory for z returns a rotation matrix for non-integral rotation values.
 */
TYPED_TEST(Mat4FloatRotationTests, Z_ReturnsAValidRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatZ, flcn::Mat4<TypeParam>::makeRotationZ(this->_angle)); }


/**
 * @test Verify that rotation transformation factory for z around arbitrary center includes translation to that point.
 */
TYPED_TEST(Mat4FloatRotationTests, Z_NonOriginCenter_ReturnsAValidRotationMatrixWithTranslation)
{ EXPECT_MAT_EQ(this->_expectedMatZCenter, flcn::Mat4<TypeParam>::makeRotationZ(this->_angle, this->_center)); }


/**
 * @test Verify that rotation transformation factory for an axis returns a rotation matrix.
 */
TYPED_TEST(Mat4FloatRotationTests, AxisAligned_ReturnsAValidRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedAxisRotation, flcn::Mat4<TypeParam>::makeRotation(this->_angle, this->_axis)); }


/**
 * @test Verify that rotation transformation factory for an axis and around an arbitrary center
 *        returns a rotation matrix.
 */
TYPED_TEST(Mat4FloatRotationTests, AxisAligned_NonOriginCenter_ReturnsAValidRotationMatrixWithTranslation)
{
    EXPECT_MAT_EQ(this->_expectedAxisRotationCenter,
                  flcn::Mat4<TypeParam>::makeRotation(this->_angle, this->_axis, this->_center));
}


/** @} */
