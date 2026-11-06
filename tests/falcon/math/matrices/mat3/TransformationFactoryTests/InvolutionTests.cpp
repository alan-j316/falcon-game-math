/**
 * @file InvolutionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 24, 2026
 *
 * @brief Verifies Mat3 involution transformation factory.
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
     * @brief Test fixture for @ref flcn::Mat3 involution factory (Floating Point).
     *
     * @tparam T The floating point scalar type (e.g., float, double) used for the matrix and vectors.
     */
    template <typename T>
    class Mat3InvolutionFactoryFPTests: public testing::Test
    {
    protected:
        flcn::Vec3<T> _norm;
        flcn::Mat3<T> _expectedInvolution;

        void SetUp() override
        {
            _norm = flcn::Vec3{ T(0.3244428422615251), T(0.48666426339228763), T(0.8111071056538127) };

            _expectedInvolution = {
                flcn::Vec3{ T(-0.7894736842105263), T(0.31578947368421056), T(0.5263157894736843) },
                flcn::Vec3{ T(0.31578947368421056), T(-0.5263157894736842), T(0.7894736842105263) },
                flcn::Vec3{ T(0.5263157894736843), T(0.7894736842105263), T(0.3157894736842106) },
            };
        }
    };
    TYPED_TEST_SUITE(Mat3InvolutionFactoryFPTests, SupportedFloatingPointTypes);


    /**
     * @brief Test fixture for @ref flcn::Mat3 involution factory (Integral).
     *
     * @tparam T The signed scalar type (e.g., int32_t, int16_t) used for the matrix and vectors.
     */
    template <typename T>
    class Mat3InvolutionFactoryIntTests: public ::testing::Test
    {
    protected:
        flcn::Vec3<T> _xAxis, _yAxis, _zAxis;
        flcn::Mat3<T> _expectedInvolutionX, _expectedInvolutionY, _expectedInvolutionZ;

        void SetUp() override
        {
            _xAxis = flcn::Vec3{ T(1), T(0), T(0) };
            _yAxis = flcn::Vec3{ T(0), T(1), T(0) };
            _zAxis = flcn::Vec3{ T(0), T(0), T(1) };

            _expectedInvolutionX = { flcn::Vec3{ T(1), T(0), T(0) }, flcn::Vec3{ T(0), T(-1), T(0) },
                                     flcn::Vec3{ T(0), T(0), T(-1) } };

            _expectedInvolutionY = { flcn::Vec3{ T(-1), T(0), T(0) }, flcn::Vec3{ T(0), T(1), T(0) },
                                     flcn::Vec3{ T(0), T(0), T(-1) } };

            _expectedInvolutionZ = { flcn::Vec3{ T(-1), T(0), T(0) }, flcn::Vec3{ T(0), T(-1), T(0) },
                                     flcn::Vec3{ T(0), T(0), T(1) } };
        }
    };
    TYPED_TEST_SUITE(Mat3InvolutionFactoryIntTests, SupportedSignedArithmeticTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that involution matrix transformation factory is available at compile time.
        constexpr auto INVOLUTION_MAT = flcn::Mat3<int>::makeInvolution(flcn::Vec3{ 1, 0, 0 });
        static_assert(INVOLUTION_MAT[0] == flcn::Vec3{ 1, 0, 0});
        static_assert(INVOLUTION_MAT[1] == flcn::Vec3{ 0, -1, 0 });
        static_assert(INVOLUTION_MAT[2] == flcn::Vec3{ 0, 0, -1 });

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat3InvolutionFactoryFPTests, ArbitraryDirection_ReturnsValidInvolutionMatrix)
{ EXPECT_MAT_EQ(this->_expectedInvolution, flcn::Mat3<TypeParam>::makeInvolution(this->_norm)); }


TYPED_TEST(Mat3InvolutionFactoryIntTests, XAxis_ReturnsIdentityMatrixWithNegatedYAndZ)
{ EXPECT_MAT_EQ(this->_expectedInvolutionX, flcn::Mat3<TypeParam>::makeInvolution(this->_xAxis)); }


TYPED_TEST(Mat3InvolutionFactoryIntTests, YAxis_ReturnsIdentityMatrixWithNegatedZAndX)
{ EXPECT_MAT_EQ(this->_expectedInvolutionY, flcn::Mat3<TypeParam>::makeInvolution(this->_yAxis)); }


TYPED_TEST(Mat3InvolutionFactoryIntTests, ZAxis_IdentityMatrixWithNegatedXAndY)
{ EXPECT_MAT_EQ(this->_expectedInvolutionZ, flcn::Mat3<TypeParam>::makeInvolution(this->_zAxis)); }

/** @} */
