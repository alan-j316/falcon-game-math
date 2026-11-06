/**
 * @file AffineTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 09, 2026
 *
 * @brief Verify @ref flcn::Mat3 affine transformation factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "../Mat3TestSetup.h"

#include <falcon/math/matrices/Mat2.h>


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
     * @brief Test fixture for @ref flcn::Mat3 Affine Transformation Factory.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat3AffineTests: public testing::Test
    {
    protected:
        flcn::Mat2<T> _linearTransform;
        flcn::CVec2<T> _translation;
        flcn::Mat3<T> _expectedMat;

        void SetUp() override
        {
            _linearTransform = { flcn::CVec2{ T(1.2341234), T(2.31419123) },
                                 flcn::CVec2{ T(15.123949182), T(0.93819231) } };
            _translation     = { T(1.2398412349), T(12.1234892134) };

            _expectedMat = { flcn::Vec3{ T(1.2341234), T(2.31419123), T(0) },
                             flcn::Vec3{ T(15.123949182), T(0.93819231), T(0) },
                             flcn::Vec3{ T(1.2398412349), T(12.1234892134), T(1) } };
        }
    };
    TYPED_TEST_SUITE(Mat3AffineTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat2 LIN_TRANSFORM{ 1, 2, 3, 4 };
        constexpr flcn::CVec2 TRANSLATION3D{ 11, 12 };

        /// @test Verify that flcn::Mat3::makeAffine returns a valid matrix at compile time.
        constexpr auto AFFINE3D = flcn::Mat3<int>::makeAffine(LIN_TRANSFORM, TRANSLATION3D);
        static_assert(AFFINE3D(0, 0) == 1);
        static_assert(AFFINE3D(0, 1) == 2);
        static_assert(AFFINE3D(0, 2) == 11);
        static_assert(AFFINE3D(1, 0) == 3);
        static_assert(AFFINE3D(1, 1) == 4);
        static_assert(AFFINE3D(1, 2) == 12);
        static_assert(AFFINE3D(2, 0) == 0);
        static_assert(AFFINE3D(2, 1) == 0);
        static_assert(AFFINE3D(2, 2) == 1);

    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat3AffineTests, ReturnsCombinedLinearTransformAndTranslation)
{ EXPECT_MAT_EQ(this->_expectedMat, flcn::Mat3<TypeParam>::makeAffine(this->_linearTransform, this->_translation)); }

/** @} */
