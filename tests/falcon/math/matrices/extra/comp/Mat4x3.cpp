/**
 * @file Mat4x3.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 25, 2026
 *
 * @brief Verify @ref flcn::Mat4x3 composition (matrix-matrix Composition) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CommonSetup.h"
#include "utils/MatrixUtils.h"

#include <falcon/math/matrices/extra/Comp.h>
#include <gtest/gtest.h>


using namespace testutils;



/**
 * @addtogroup T_FALCON_Mat4x3_Comp
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4x3 matrix composition.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat4x3CompositionTests: public testing::Test
    {

    protected:
        flcn::Mat3<T> _mat3;
        flcn::Mat3x2<T> _mat3x2;
        flcn::Mat3x4<T> _mat3x4;

        flcn::Mat4<T> _mat4, _expectedFPMat4, _expectedIntMat4;
        flcn::Mat4x2<T> _expectedFPMat4x2, _expectedIntMat4x2;
        // 4D x 4x3 -> 4x4 matrix * 4x2 matrix result
        // 4x3 x 3D -> 4x3 matrix * 3x3 matrix result
        flcn::Mat4x3<T> _mat4x3, _expectedFPMat4Dx4x3, _expectedIntMat4Dx4x3, _expectedFPMat4x3x3D,
            _expectedIntMat4x3x3D;


        void SetUp() override
        {
            _mat4x3 =       {
                flcn::Vec4 { T(5.12390421300000032), T(2.01238399999999995), T(5.01238401234000008), T(3.12343210000000004)},
                flcn::Vec4 { T(1.01820339999999998), T(2.01234000000000002), T(1.10234800000000011), T(2.12389900000000020)},
                flcn::Vec4 { T(5.01238399999999995), T(1.02384019999999998), T(5.01238399999999995), T(9.10234799999999922)}
            };


            _mat3 = { flcn::Vec3{ T(5.12390421300000032), T(2.01238399999999995), T(5.01238401234000008) },
                      flcn::Vec3{ T(1.01820339999999998), T(2.01234000000000002), T(1.10234800000000011) },
                      flcn::Vec3{ T(5.01238399999999995), T(1.02384019999999998), T(0.01283400000000000) } };

            _mat3x2 = { flcn::Vec3{ T(1.32194213899999991), T(3.02134123399999988), T(5.10238399999999981) },
                        flcn::Vec3{ T(2.12304122299999998), T(4.01283041000000029), T(6.01238399999999995) } };

            _mat3x4 = { flcn::Vec3{ T(5.12390421300000032), T(2.01234000000000002), T(0.01283400000000000) },
                        flcn::Vec3{ T(1.01820339999999998), T(1.02384019999999998), T(0.25123420000000002) },
                        flcn::Vec3{ T(5.01238399999999995), T(5.01238401234000008), T(1.20830199999999999) },
                        flcn::Vec3{ T(2.01238399999999995), T(1.10234800000000011), T(3.01234499999999983) } };

            _expectedFPMat4x2  = { flcn::Vec4{ T(35.42495273583932658), T(13.96424688331373609), T(35.53175903283557346),
                                             T(56.98969493447862078) },
                                   flcn::Vec4{ T(45.10051479744376479), T(18.50327377280183327), T(45.20141082396263954),
                                             T(69.88083307814204659) } };
            _expectedIntMat4x2 = { flcn::Vec4{ T(33), T(13), T(33), T(54) }, flcn::Vec4{ T(44), T(18), T(44), T(68) } };

            _mat4 =         {
                flcn::Vec4 { T(5.12390421300000032), T(2.01234000000000002), T(5.01238399999999995), T(7.01203481000000028)},
                flcn::Vec4 { T(1.01820339999999998), T(1.02384019999999998), T(3.12343210000000004), T(3.16000000000000014)},
                flcn::Vec4 { T(5.01238399999999995), T(5.01238401234000008), T(2.12389900000000020), T(5.12500000000000000)},
                flcn::Vec4 { T(2.01238399999999995), T(1.10234800000000011), T(9.10234799999999922), T(4.91999999999999993)}
            };
            _expectedFPMat4  = { flcn::Vec4{ T(28.36769475021115383), T(14.37391509650059263), T(27.96560346857877377),
                                           T(20.39499334410143661) },
                                 flcn::Vec4{ T(7.51893654798040423), T(4.36655449254844008), T(7.49153692459262999),
                                           T(7.64164347873053984) },
                                 flcn::Vec4{ T(36.84307555021202063), T(21.41057036818867587), T(36.70585852851179709),
                                           T(37.30002376764731764) },
                                 flcn::Vec4{ T(26.53270721783699315), T(9.35214824504499909), T(26.40104238187281993),
                                           T(36.04623308403839843) } };
            _expectedIntMat4 = { flcn::Vec4{ T(27), T(14), T(27), T(19) }, flcn::Vec4{ T(6), T(4), T(6), T(5) },
                                 flcn::Vec4{ T(35), T(21), T(35), T(34) }, flcn::Vec4{ T(26), T(9), T(26), T(35) } };


            _expectedFPMat4x3x3D  = { flcn::Vec4{ T(53.42740404021357392), T(19.49274392400478106),
                                                T(53.02531646094359274), T(65.90273085138041154) },
                                      flcn::Vec4{ T(12.79153959853892530), T(7.22715670329520066),
                                                T(12.84731689542222988), T(17.48825121065313937) },
                                      flcn::Vec4{ T(26.78978200372647223), T(12.16029591665079934),
                                                T(26.31695055835441721), T(17.94719379429820094) } };
            _expectedIntMat4x3x3D = { flcn::Vec4{ T(52), T(19), T(52), T(64) }, flcn::Vec4{ T(12), T(7), T(12), T(16) },
                                      flcn::Vec4{ T(26), T(12), T(26), T(17) } };

            _expectedFPMat4Dx4x3  = {
                flcn::Vec4 { T(59.71294882333997123), T(40.93849965675766356), T(71.04488359789590390), T(83.34388213990415295)},
                flcn::Vec4 { T(17.06563996375492565), T(11.97595332411097502), T(33.06277741272359805), T(29.59778866446035650)},
                flcn::Vec4 { T(70.16686590855846362), T(46.29281811210886133), T(121.82042518772639994), T(108.85436628108703871)}
            };
            _expectedIntMat4Dx4x3 = {
                flcn::Vec4 { T(58), T(40), T(68), T(78)},
                flcn::Vec4 { T(16), T(11), T(31), T(26)},
                flcn::Vec4 { T(69), T(45), T(119), T(99)}
            };
        }
    };
    TYPED_TEST_SUITE(Mat4x3CompositionTests, SupportedArithmeticTypes);


    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        // STATIC TEST SETUP
        constexpr flcn::Mat4x3 MAT4X3(5, 1, 5, 2, 2, 1, 5, 1, 5, 3, 2, 9);
        constexpr flcn::Mat3x2 MAT3X2(1, 2, 3, 4, 5, 6);
        constexpr flcn::Mat3 MAT3(5, 1, 5, 2, 2, 1, 5, 1, 0);
        constexpr flcn::Mat3x4 MAT3X4(5, 1, 5, 2, 2, 1, 5, 1, 0, 0, 1, 3);
        constexpr flcn::Mat4 MAT4(5, 1, 5, 2, 2, 1, 5, 1, 5, 3, 2, 9, 7, 3, 5, 4);


        /// @test Verify that 4x3 matrix times a 3x2 matrix yields a 4x2 matrix at compile time.
        constexpr auto EXP_MAT4X2 = MAT4X3 * MAT3X2;
        static_assert(EXP_MAT4X2[0] == flcn::Vec4{ 33, 13, 33, 54 });
        static_assert(EXP_MAT4X2[1] == flcn::Vec4{ 44, 18, 44, 68 });

        /// @test Verify that 4x3 matrix times a 3x3 matrix yields a 4x3 matrix at compile time.
        constexpr auto EXP_MAT4X3 = MAT4X3 * MAT3;
        static_assert(EXP_MAT4X3[0] == flcn::Vec4{ 52, 19, 52, 64 });
        static_assert(EXP_MAT4X3[1] == flcn::Vec4{ 12, 7, 12, 16 });
        static_assert(EXP_MAT4X3[2] == flcn::Vec4{ 26, 12, 26, 17 });

        /// @test Verify that 4x3 matrix times a 3x4 matrix yields a 4D matrix at compile time.
        constexpr auto EXP_MAT4 = MAT4X3 * MAT3X4;
        static_assert(EXP_MAT4[0] == flcn::Vec4{ 27, 14, 27, 19 });
        static_assert(EXP_MAT4[1] == flcn::Vec4{ 6, 4, 6, 5 });
        static_assert(EXP_MAT4[2] == flcn::Vec4{ 35, 21, 35, 34 });
        static_assert(EXP_MAT4[3] == flcn::Vec4{ 26, 9, 26, 35 });

        /// @test Verify that 4x3 matrix times a 3x4 matrix yields a 4D matrix at compile time.
        constexpr auto EXP_MAT4SQ = MAT4 * MAT4X3;
        static_assert(EXP_MAT4SQ[0] == flcn::Vec4{ 58, 40, 68, 78 });
        static_assert(EXP_MAT4SQ[1] == flcn::Vec4{ 16, 11, 31, 26 });
        static_assert(EXP_MAT4SQ[2] == flcn::Vec4{ 69, 45, 119, 99 });

    } // namespace static_tests

} // namespace



/**************************************
 *            RUNTIME TESTS           *
 **************************************/

TYPED_TEST(Mat4x3CompositionTests, Mat4x3TimesMat3x2_ReturnsAValid4x2Matrix)
{
    const auto matrixProduct = this->_mat4x3 * this->_mat3x2;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat4x2, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat4x2, matrixProduct);
    }
}


TYPED_TEST(Mat4x3CompositionTests, Mat4x3TimesMat3_ReturnsAValid4x3Matrix)
{
    const auto matrixProduct = this->_mat4x3 * this->_mat3;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat4x3x3D, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat4x3x3D, matrixProduct);
    }
}


TYPED_TEST(Mat4x3CompositionTests, Mat4x3TimesMat3x4_ReturnsAValid4DMatrix)
{
    const auto matrixProduct = this->_mat4x3 * this->_mat3x4;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat4, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat4, matrixProduct);
    }
}


TYPED_TEST(Mat4x3CompositionTests, Mat4x4TimesMat4x3_ReturnsAValid4x3Matrix)
{
    const auto matrixProduct = this->_mat4 * this->_mat4x3;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat4Dx4x3, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat4Dx4x3, matrixProduct);
    }
}

/** @} */
