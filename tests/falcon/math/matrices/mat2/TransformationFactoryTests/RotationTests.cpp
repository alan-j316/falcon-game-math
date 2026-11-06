/**
 * @file RotationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 08, 2026
 *
 * @brief Verify @ref flcn::Mat2 rotation factory logic.
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
     * @brief Test fixture for @ref flcn::Mat2 Rotation Factory (integrals).
     *
     * @tparam T The numeric type (int, long...) for matrix values.
     */
    template <typename T>
    class Mat2RotationFactoryTests: public testing::Test
    {
    protected:
        using FP_T  = T::first_type;  // FP_T -> Floating-point Type
        using COM_T = T::second_type; // COM_T -> Common Type

        FP_T _angle;
        flcn::Mat2<COM_T> _expectedMat;


        void SetUp() override
        {
            _angle = flcn::constants::PI<FP_T> / FP_T(2.0);
#ifdef FALCON_LEFT_HANDED
            _expectedMat = { flcn::CVec2{ COM_T(0), COM_T(-1) }, flcn::CVec2 { COM_T(1), COM_T(0) } };
#else
            _expectedMat = { flcn::CVec2{ COM_T(0), COM_T(1) }, flcn::CVec2{ COM_T(-1), COM_T(0) } };
#endif
        }
    };
    TYPED_TEST_SUITE(Mat2RotationFactoryTests, SupportedSignedArithmeticFloatingTypePair);



    /**
     * @brief Test fixture for @ref flcn::Mat2 Reflection Factory(Floating Point Numbers).
     *
     * @tparam T The numeric type (float, double) for matrix values.
     */
    template <typename T>
    class Mat2RotationFactoryFPTests: public testing::Test
    {
    protected:
        T _angle;
        flcn::Mat2<T> _expectedMat;


        void SetUp() override
        {
            _angle = flcn::constants::PI<T> / T(4.0);

#ifdef FALCON_LEFT_HANDED
            _expectedMat = {
                flcn::CVec2{ T(0.70710678118654757), T(-0.70710678118654757) },
                flcn::CVec2{ T(0.70710678118654757), T(0.70710678118654757) },
            };

#else
            _expectedMat = { flcn::CVec2{ T(0.70710678118654757), T(0.70710678118654757) },
                             flcn::CVec2{ T(-0.70710678118654757), T(0.70710678118654757) } };

#endif
        }
    };
    TYPED_TEST_SUITE(Mat2RotationFactoryFPTests, SupportedFloatingPointTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
// TODO: Add static tests after implementing constexpr evaluation for trig funcs
#if __cplusplus >= 202603L
        // Rotation matrix for 180° or 2π radians
        constexpr auto ROTATION_MAT = flcn::Mat2<int>::makeRotation(flcn::constants::PI<float>);
        static_assert(ROTATION_MAT(0, 0) == 0);
        static_assert(ROTATION_MAT(0, 1) == -1);
        static_assert(ROTATION_MAT(1, 0) == 1);
        static_assert(ROTATION_MAT(1, 1) == 0);
#endif

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat2RotationFactoryTests, ReturnsValidRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMat, flcn::Mat2<typename TypeParam::first_type>::makeRotation(this->_angle)); }


TYPED_TEST(Mat2RotationFactoryFPTests, ReturnsValidRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMat, flcn::Mat2<TypeParam>::makeRotation(this->_angle)); }


/** @} */
