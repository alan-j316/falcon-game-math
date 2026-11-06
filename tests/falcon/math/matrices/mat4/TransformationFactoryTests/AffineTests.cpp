/**
 * @file AffineTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 08, 2026
 *
 * @brief Verify @ref flcn::Mat4 affine transformation factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "../../mat3/Mat3TestSetup.h"
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
     * @brief Test fixture for @ref flcn::Mat4 affine factory.
     *
     * @tparam T The scalar type (e.g., int, long, float, double) used for the matrix and vectors.
     */
    template <typename T>
    class Mat4AffineFactoryTests: public testing::Test
    {
    protected:
        flcn::Mat3<T> _linearTransform;
        flcn::Vec3<T> _translation;
        flcn::Mat4<T> _expectedMat;

        void SetUp() override
        {
            _linearTransform = { flcn::Vec3{ T(1.2341234), T(2.31419123), T(3.10234212) },
                                 flcn::Vec3{ T(15.123949182), T(0.93819231), T(3.10234212) },
                                 flcn::Vec3{ T(5.8329141), T(12.2319382), T(8.34232112) } };
            _translation     = { T(1.2398412349), T(12.1234892134), T(35.012342380) };

            _expectedMat = { flcn::Vec4{ T(1.2341234), T(2.31419123), T(3.10234212), T(0) },
                             flcn::Vec4{ T(15.123949182), T(0.93819231), T(3.10234212), T(0) },
                             flcn::Vec4{ T(5.8329141), T(12.2319382), T(8.34232112), T(0) },
                             flcn::Vec4{ T(1.2398412349), T(12.1234892134), T(35.012342380), T(1) } };
        }
    };
    TYPED_TEST_SUITE(Mat4AffineFactoryTests, SupportedArithmeticTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_test
    {
        /// Verify that @ref Mat4 makeAffine is available at compile time.
        constexpr flcn::Mat3 LIN_TRANSFORM{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        constexpr flcn::Vec3 TRANSLATION3D{ 11, 12, 13 };
        constexpr auto AFFINE4D = flcn::Mat4<int>::makeAffine(LIN_TRANSFORM, TRANSLATION3D);
        static_assert(AFFINE4D[0] == flcn::Vec4(1, 4, 7, 0));
        static_assert(AFFINE4D[1] == flcn::Vec4(2, 5, 8, 0));
        static_assert(AFFINE4D[2] == flcn::Vec4(3, 6, 9, 0));
        static_assert(AFFINE4D[3] == flcn::Vec4(11, 12, 13, 1));

    } // namespace static_test

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat4AffineFactoryTests, ReturnsCombinedLinearTransformAndTranslation)
{ EXPECT_MAT_EQ(this->_expectedMat, flcn::Mat4<TypeParam>::makeAffine(this->_linearTransform, this->_translation)); }

/** @} */
