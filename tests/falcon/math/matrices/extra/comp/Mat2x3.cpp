/**
 * @file Mat2x3.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 17, 2026
 *
 * @brief Verify @ref flcn::Mat2x3 composition (matrix-matrix Composition) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CommonSetup.h"
#include "utils/MatrixUtils.h"

#include <falcon/math/matrices/extra/Comp.h>
#include <gtest/gtest.h>


using namespace testutils;



/**
 * @addtogroup T_FALCON_Mat2x3_Comp
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2x3 matrix composition.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat2x3CompositionTests: public ::testing::Test
    {

    protected:
        flcn::Mat2<T> _mat2, _expectedFPMat2, _expectedIntMat2;
        flcn::Mat2x4<T> _expectedFPMat2x4, _expectedIntMat2x4;
        // 2D x 2x3 -> 2x2 matrix * 2x3 matrix result
        // 2x3 x 3D -> 2x3 matrix * 3x3 matrix result
        flcn::Mat2x3<T> _mat2x3, _expectedFPMat2Dx2x3, _expectedIntMat2Dx2x3, _expectedFPMat2x3x3D,
            _expectedIntMat2x3x3D;


        flcn::Mat3x2<T> _mat3x2;
        flcn::Mat3<T> _mat3;
        flcn::Mat3x4<T> _mat3x4;


        void SetUp() override
        {

            _expectedFPMat2  = { flcn::CVec2{ T(26.51643186788337658), T(64.24805428618311964) },
                                 flcn::CVec2{ T(39.21223418982177122), T(83.83742932933810721) } };
            _expectedIntMat2 = { flcn::CVec2{ T(24), T(63) }, flcn::CVec2{ T(38), T(83) } };


            _mat2 = { flcn::CVec2{ T(1.32194213899999991), T(3.02134123399999988) },
                      flcn::CVec2{ T(2.12304122299999998), T(4.01283041000000029) } };

            _mat2x3            = { flcn::CVec2{ T(1.32194213899999991), T(4.01283041000000029) },
                                   flcn::CVec2{ T(2.12304122299999998), T(5.10238399999999981) },
                                   flcn::CVec2{ T(3.02134123399999988), T(6.01238399999999995) } };
            _expectedFPMat2x3x3D  = { flcn::CVec2{ T(26.19000158099516895), T(60.96569200495833485) },
                                   flcn::CVec2{ T(8.94885622184232510), T(20.98134846327739567) },
                                   flcn::CVec2{ T(8.83851247021109643), T(25.41503573309023878) } };
            _expectedIntMat2x3x3D = { flcn::CVec2{ T(24), T(60) }, flcn::CVec2{ T(8), T(20) }, flcn::CVec2{ T(7), T(25) } };


            _expectedFPMat2Dx2x3  = { flcn::CVec2{ T(10.26693540020188777), T(20.09684619294363017) },
                                       flcn::CVec2{ T(13.63910922309342588), T(26.88943366722913098) },
                                       flcn::CVec2{ T(16.75857737402849068), T(33.25518020406607889) } };
            _expectedIntMat2Dx2x3 = { flcn::CVec2{ T(9), T(19) }, flcn::CVec2{ T(12), T(26) }, flcn::CVec2{ T(15), T(33) } };

            _expectedFPMat2x4  = { flcn::CVec2{ T(11.08456156345330790), T(30.90625299866951892) },
                                   flcn::CVec2{ T(4.27872517874863956), T(10.82041990645499396) },
                                   flcn::CVec2{ T(20.91827216587800464), T(52.95373054018485703) },
                                   flcn::CVec2{ T(14.10190761507471002), T(31.81133338990943926) } };
            _expectedIntMat2x4 = { flcn::CVec2{ T(9), T(30) }, flcn::CVec2{ T(3), T(9) }, flcn::CVec2{ T(18), T(51) },
                                   flcn::CVec2{ T(13), T(31) } };


            _mat3x2 = { flcn::Vec3{ T(5.12390421300000032), T(5.01238399999999995), T(3.01238040000000007) },
                        flcn::Vec3{ T(1.01820339999999998), T(5.01238042099999959), T(9.01081203400000064) } };

            _mat3 = { flcn::Vec3{ T(5.12390421300000032), T(2.01238399999999995), T(5.01238401234000008) },
                      flcn::Vec3{ T(1.01820339999999998), T(2.01234000000000002), T(1.10234800000000011) },
                      flcn::Vec3{ T(5.01238399999999995), T(1.02384019999999998), T(0.01283400000000000) } };

            _mat3x4 = { flcn::Vec3{ T(5.12390421300000032), T(2.01234000000000002), T(0.01283400000000000) },
                        flcn::Vec3{ T(1.01820339999999998), T(1.02384019999999998), T(0.25123420000000002) },
                        flcn::Vec3{ T(5.01238399999999995), T(5.01238401234000008), T(1.20830199999999999) },
                        flcn::Vec3{ T(2.01238399999999995), T(1.10234800000000011), T(3.01234499999999983) } };
        }
    };
    TYPED_TEST_SUITE(Mat2x3CompositionTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        // STATIC TEST SETUP
        constexpr flcn::Mat2 MAT2(1, 2, 3, 4);
        constexpr flcn::Mat2x3 MAT2X3(1, 2, 3, 4, 5, 6);
        constexpr flcn::Mat3 MAT3X3(5, 6, 7, 8, 9, 10, 11, 12, 13);
        constexpr flcn::Mat3x2 MAT3X2(5, 6, 7, 8, 9, 10);
        constexpr flcn::Mat3x4 MAT3X4(5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);


        /// @test Verify that 2x3 matrix times a 3x2 matrix yields a 2x2 matrix at compile time.
        constexpr auto EXP_MAT2 = MAT2X3 * MAT3X2;
        static_assert(EXP_MAT2[0] == flcn::CVec2{ 46, 109 });
        static_assert(EXP_MAT2[1] == flcn::CVec2{ 52, 124 });

        /// @test Verify that 2x3 matrix times a 3x3 matrix yields a 2x3 matrix at compile time.
        constexpr auto EXP_MAT2X3 = MAT2X3 * MAT3X3;
        static_assert(EXP_MAT2X3[0] == flcn::CVec2{ 54, 126 });
        static_assert(EXP_MAT2X3[1] == flcn::CVec2{ 60, 141 });
        static_assert(EXP_MAT2X3[2] == flcn::CVec2{ 66, 156 });

        /// @test Verify that 2x3 matrix times a 3x4 matrix yields a 2x4 matrix at compile time.
        constexpr auto EXP_MAT2X4 = MAT2X3 * MAT3X4;
        static_assert(EXP_MAT2X4[0] == flcn::CVec2{ 62, 143 });
        static_assert(EXP_MAT2X4[1] == flcn::CVec2{ 68, 158 });
        static_assert(EXP_MAT2X4[2] == flcn::CVec2{ 74, 173 });
        static_assert(EXP_MAT2X4[3] == flcn::CVec2{ 80, 188 });

        /// @test Verify that 2x2 matrix times a 2x3 matrix yields a 2x3 matrix at compile time.
        constexpr auto EXP_MAT2X3SQ = MAT2 * MAT2X3;
        static_assert(EXP_MAT2X3SQ[0] == flcn::CVec2{ 9, 19 });
        static_assert(EXP_MAT2X3SQ[1] == flcn::CVec2{ 12, 26 });
        static_assert(EXP_MAT2X3SQ[2] == flcn::CVec2{ 15, 33 });

    } // namespace static_tests

} // namespace



/**************************************
 *            RUNTIME TESTS           *
 **************************************/

TYPED_TEST(Mat2x3CompositionTests, Mat2x3TimesMat3x2_ReturnsAValid2DMatrix)
{
    const auto matrixProduct = this->_mat2x3 * this->_mat3x2;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat2, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat2, matrixProduct);
    }
}


TYPED_TEST(Mat2x3CompositionTests, Mat2x3TimesMat3_ReturnsAValid2x3Matrix)
{
    const auto matrixProduct = this->_mat2x3 * this->_mat3;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat2x3x3D, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat2x3x3D, matrixProduct);
    }
}


TYPED_TEST(Mat2x3CompositionTests, Mat2x3TimesMat3x4_ReturnsAValid2x4Matrix)
{
    const auto matrixProduct = this->_mat2x3 * this->_mat3x4;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat2x4, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat2x4, matrixProduct);
    }
}


TYPED_TEST(Mat2x3CompositionTests, Mat2x2TimesMat2x3_ReturnsAValid2x3Matrix)
{
    const auto matrixProduct = this->_mat2 * this->_mat2x3;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat2Dx2x3, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat2Dx2x3, matrixProduct);
    }
}


/** @} */
