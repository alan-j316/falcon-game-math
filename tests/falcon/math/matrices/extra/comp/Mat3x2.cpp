/**
 * @file Mat3x2.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 25, 2026
 *
 * @brief Verify @ref flcn::Mat3x2 composition (matrix-matrix Composition) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CommonSetup.h"
#include "utils/MatrixUtils.h"

#include <falcon/math/matrices/extra/Comp.h>
#include <gtest/gtest.h>


using namespace testutils;



/**
 * @addtogroup T_FALCON_Mat3x2_Comp
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat3x2 matrix composition.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat3x2CompositionTests: public testing::Test
    {

    protected:
        flcn::Mat2<T> _mat2;
        flcn::Mat2x3<T> _mat2x3;
        flcn::Mat3<T> _mat3, _expectedFPMat3, _expectedIntMat3;
        // 3D x 3x2 -> 3x3 matrix * 3x2 matrix result
        // 3x2 x 2D -> 3x2 matrix * 2x2 matrix result
        flcn::Mat3x2<T> _mat3x2, _expectedFPMat3Dx3x2, _expectedIntMat3Dx3x2, _expectedFPMat3x2x2D,
            _expectedIntMat3x2x2D;

        flcn::Mat2x4<T> _mat2x4;
        flcn::Mat3x4<T> _expectedFPMat3x4, _expectedIntMat3x4;

        void SetUp() override
        {
            _mat2 = { flcn::CVec2{ T(1.32194213899999991), T(3.02134123399999988) },
                      flcn::CVec2{ T(2.12304122299999998), T(4.01283041000000029) } };

            _mat3x2 = { flcn::Vec3{ T(1.32194213899999991), T(3.02134123399999988), T(5.10238399999999981) },
                        flcn::Vec3{ T(2.12304122299999998), T(4.01283041000000029), T(6.01238399999999995) } };

            _expectedFPMat3x2x2D = {
                flcn::Vec3{ T(8.16196300739558467), T(16.11816827630498494), T(24.91052011280122969) },
                flcn::Vec3{ T(11.32594203685578726), T(22.51723988795246001), T(34.95924891937306711) }
            };
            _expectedIntMat3x2x2D = { flcn::Vec3{ T(7), T(15), T(23) }, flcn::Vec3{ T(10), T(22), T(34) } };

            _expectedFPMat3Dx3x2 = {
                flcn::Vec3{ T(35.42495273583932658), T(13.96424688331373609), T(10.02213510563557541) },
                flcn::Vec3{ T(45.10051479744376479), T(18.50327377280183327), T(15.14219639676264073) }
            };
            _expectedIntMat3Dx3x2 = { flcn::Vec3{ T(33), T(13), T(8) }, flcn::Vec3{ T(44), T(18), T(14) } };

            _mat2x3 = { flcn::CVec2{ T(1.32194213899999991), T(4.01283041000000029) },
                        flcn::CVec2{ T(2.12304122299999998), T(5.10238399999999981) },
                        flcn::CVec2{ T(3.02134123399999988), T(6.01238399999999995) } };


            _mat3 = { flcn::Vec3{ T(5.12390421300000032), T(2.01238399999999995), T(5.01238401234000008) },
                      flcn::Vec3{ T(1.01820339999999998), T(2.01234000000000002), T(1.10234800000000011) },
                      flcn::Vec3{ T(5.01238399999999995), T(1.02384019999999998), T(0.01283400000000000) } };

            _expectedFPMat3  = { flcn::Vec3{ T(10.26693540020188777), T(20.09684619294363017), T(30.87173377075681557) },
                                 flcn::Vec3{ T(13.63910922309342588), T(26.88943366722913098), T(41.51006349103163018) },
                                 flcn::Vec3{ T(16.75857737402849068), T(33.25518020406607889),
                                           T(51.56480453435784739) } };
            _expectedIntMat3 = { flcn::Vec3{ T(9), T(19), T(29) }, flcn::Vec3{ T(12), T(26), T(40) },
                                 flcn::Vec3{ T(15), T(33), T(51) } };

            _mat2x4 = { flcn::CVec2{ T(5.12390421300000032), T(2.01234000000000002) },
                        flcn::CVec2{ T(1.01820339999999998), T(1.02384019999999998) },
                        flcn::CVec2{ T(5.01238399999999995), T(5.01238401234000008) },
                        flcn::CVec2{ T(2.01238399999999995), T(1.10234800000000011) } };

            _expectedFPMat3x4 = {
                flcn::Vec3{ T(11.04578567005615142), T(23.55624222506261845), T(38.24308769250379214) },
                flcn::Vec3{ T(3.51966093089763676), T(7.18483700655947821), T(11.35098517394239970) },
                flcn::Vec3{ T(17.26757951015333603), T(35.25796945115762071), T(55.71148536110482041) },
                flcn::Vec3{ T(5.00058545554098011), T(10.50363433464453600), T(16.89569540108799828) }
            };
            _expectedIntMat3x4 = { flcn::Vec3{ T(9), T(23), T(37) }, flcn::Vec3{ T(3), T(7), T(11) },
                                   flcn::Vec3{ T(15), T(35), T(55) }, flcn::Vec3{ T(4), T(10), T(16) } };
        }
    };
    TYPED_TEST_SUITE(Mat3x2CompositionTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        // STATIC TEST SETUP
        constexpr flcn::Mat2 MAT2(1, 2, 3, 4);
        constexpr flcn::Mat2x3 MAT2X3(1, 2, 3, 4, 5, 6);
        constexpr flcn::Mat2x4 MAT2X4(5, 1, 5, 2, 2, 1, 5, 1);

        constexpr flcn::Mat3 MAT3(5, 1, 5, 2, 2, 1, 5, 1, 0);
        constexpr flcn::Mat3x2 MAT3X2(1, 2, 3, 4, 5, 6);


        /// @test Verify that 3x2 matrix times a 2D matrix yields a 3x2 matrix at compile time.
        constexpr auto EXP_MAT2 = MAT3X2 * MAT2;
        static_assert(EXP_MAT2[0] == flcn::Vec3{ 7, 15, 23 });
        static_assert(EXP_MAT2[1] == flcn::Vec3{ 10, 22, 34 });

        /// @test Verify that 3x2 matrix times a 2x3 matrix yields a 3x3 matrix at compile time.
        constexpr auto EXP_MAT3 = MAT3X2 * MAT2X3;
        static_assert(EXP_MAT3[0] == flcn::Vec3{ 9, 19, 29 });
        static_assert(EXP_MAT3[1] == flcn::Vec3{ 12, 26, 40 });
        static_assert(EXP_MAT3[2] == flcn::Vec3{ 15, 33, 51 });

        /// @test Verify that 3x2 matrix times a 2x4 matrix yields a 3x4 matrix at compile time.
        constexpr auto EXP_MAT3X4 = MAT3X2 * MAT2X4;
        static_assert(EXP_MAT3X4[0] == flcn::Vec3{ 9, 23, 37 });
        static_assert(EXP_MAT3X4[1] == flcn::Vec3{ 3, 7, 11 });
        static_assert(EXP_MAT3X4[2] == flcn::Vec3{ 15, 35, 55 });
        static_assert(EXP_MAT3X4[3] == flcn::Vec3{ 4, 10, 16 });

        /// @test Verify that 3x3 matrix times a 3x2 matrix yields a 3x2 matrix at compile time.
        constexpr auto EXP_MAT3X2 = MAT3 * MAT3X2;
        static_assert(EXP_MAT3X2[0] == flcn::Vec3{ 33, 13, 8 });
        static_assert(EXP_MAT3X2[1] == flcn::Vec3{ 44, 18, 14 });

    } // namespace static_tests

} // namespace



/**************************************
 *            RUNTIME TESTS           *
 **************************************/

TYPED_TEST(Mat3x2CompositionTests, Mat3x2TimesMat2_ReturnsAValid3x2Matrix)
{
    const auto matrixProduct = this->_mat3x2 * this->_mat2;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat3x2x2D, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat3x2x2D, matrixProduct);
    }
}


TYPED_TEST(Mat3x2CompositionTests, Mat3x2TimesMat2x3_ReturnsAValid3DMatrix)
{
    const auto matrixProduct = this->_mat3x2 * this->_mat2x3;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat3, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat3, matrixProduct);
    }
}


TYPED_TEST(Mat3x2CompositionTests, Mat3x2TimesMat2x4_ReturnsAValid3x4Matrix)
{
    const auto matrixProduct = this->_mat3x2 * this->_mat2x4;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat3x4, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat3x4, matrixProduct);
    }
}


TYPED_TEST(Mat3x2CompositionTests, Mat3TimesMat3x2_ReturnsAValid3x2Matrix)
{
    const auto matrixProduct = this->_mat3 * this->_mat3x2;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat3Dx3x2, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat3Dx3x2, matrixProduct);
    }
}

/** @} */
