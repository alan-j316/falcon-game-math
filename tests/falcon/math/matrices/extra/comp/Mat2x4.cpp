/**
 * @file Mat2x4.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 24, 2026
 *
 * @brief Verify @ref flcn::Mat2x4 composition (matrix-matrix Composition) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CommonSetup.h"
#include "utils/MatrixUtils.h"

#include <falcon/math/matrices/extra/Comp.h>
#include <gtest/gtest.h>


using namespace testutils;



/**
 * @addtogroup T_FALCON_Mat2x4_Comp
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2x4 matrix composition.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat2x4CompositionTests: public testing::Test
    {

    protected:
        flcn::Mat2<T> _mat2, _expectedFPMat2, _expectedIntMat2;
        flcn::Mat2x3<T> _expectedFPMat2x3, _expectedIntMat2x3;
        // 2D x 2x4 -> 2x2 matrix * 2x4 matrix result
        // 2x4 x 4D -> 2x4 matrix * 4x4 matrix result
        flcn::Mat2x4<T> _mat2x4, _expectedFPMat2Dx2x4, _expectedIntMat2Dx2x4, _expectedFPMat2x4x4D,
            _expectedIntMat2x4x4D;

        flcn::Mat4<T> _mat4;
        flcn::Mat4x2<T> _mat4x2;
        flcn::Mat4x3<T> _mat4x3;

        void SetUp() override
        {
            _expectedFPMat2  = { flcn::CVec2{ T(51.53148302175357287), T(31.05492997565247038) },
                                 flcn::CVec2{ T(14.61642063652532286), T(10.45638242976778720) } };
            _expectedIntMat2 = { flcn::CVec2{ T(50), T(30) }, flcn::CVec2{ T(14), T(10) } };

            _expectedFPMat2x3  = { flcn::CVec2{ T(59.71294882333997123), T(40.93849965675766356) },
                                   flcn::CVec2{ T(17.06563996375492565), T(11.97595332411097502) },
                                   flcn::CVec2{ T(70.16686590855846362), T(46.29281811210886133) } };
            _expectedIntMat2x3 = { flcn::CVec2{ T(58), T(40) }, flcn::CVec2{ T(16), T(11) }, flcn::CVec2{ T(69), T(45) } };


            _mat2 = { flcn::CVec2{ T(1.32194213899999991), T(3.02134123399999988) },
                      flcn::CVec2{ T(2.12304122299999998), T(4.01283041000000029) } };

            _mat2x4               = { flcn::CVec2{ T(5.12390421300000032), T(2.01234000000000002) },
                                      flcn::CVec2{ T(1.01820339999999998), T(1.02384019999999998) },
                                      flcn::CVec2{ T(5.01238399999999995), T(5.01238401234000008) },
                                      flcn::CVec2{ T(2.01238399999999995), T(1.10234800000000011) } };
            _expectedFPMat2x4x4D  = { flcn::CVec2{ T(67.53826583649818360), T(45.22504796609911892) },
                                      flcn::CVec2{ T(28.27462878677400582), T(22.23648098676159535) },
                                      flcn::CVec2{ T(51.74586730346002383), T(31.51383195965590645) },
                                      flcn::CVec2{ T(66.95907009498898788), T(56.22624476530457116) } };
            _expectedIntMat2x4x4D = { flcn::CVec2{ T(66), T(44) }, flcn::CVec2{ T(27), T(21) }, flcn::CVec2{ T(50), T(30) },
                                      flcn::CVec2{ T(64), T(54) } };

            _expectedFPMat2Dx2x4  = { flcn::CVec2{ T(11.04578567005615142), T(23.55624222506261845) },
                                      flcn::CVec2{ T(3.51966093089763676), T(7.18483700655947821) },
                                      flcn::CVec2{ T(17.26757951015333603), T(35.25796945115762071) },
                                      flcn::CVec2{ T(5.00058545554098011), T(10.50363433464453600) } };
            _expectedIntMat2Dx2x4 = { flcn::CVec2{ T(9), T(23) }, flcn::CVec2{ T(3), T(7) }, flcn::CVec2{ T(15), T(35) },
                                      flcn::CVec2{ T(4), T(10) } };

            _mat4 = { flcn::Vec4{ T(5.12390421300000032), T(2.01234000000000002), T(5.01238399999999995),
                                 T(7.01203481000000028) },
                      flcn::Vec4{ T(1.01820339999999998), T(1.02384019999999998), T(3.12343210000000004),
                                 T(3.16000000000000014) },
                      flcn::Vec4{ T(5.01238399999999995), T(5.01238401234000008), T(2.12389900000000020),
                                 T(5.12500000000000000) },
                      flcn::Vec4{ T(2.01238399999999995), T(1.10234800000000011), T(9.10234799999999922),
                                 T(4.91999999999999993) } };

            _mat4x2 = { flcn::Vec4{ T(5.12390421300000032), T(5.01238399999999995), T(2.01234000000000002),
                                   T(5.01238401234000008) },
                        flcn::Vec4{ T(1.01820339999999998), T(2.01238399999999995), T(1.02384019999999998),
                                   T(1.10234800000000011) } };

            _mat4x3 = { flcn::Vec4{ T(5.12390421300000032), T(2.01238399999999995), T(5.01238401234000008),
                                   T(3.12343210000000004) },
                        flcn::Vec4{ T(1.01820339999999998), T(2.01234000000000002), T(1.10234800000000011),
                                   T(2.12389900000000020) },
                        flcn::Vec4{ T(5.01238399999999995), T(1.02384019999999998), T(5.01238399999999995),
                                   T(9.10234799999999922) } };
        }
    };
    TYPED_TEST_SUITE(Mat2x4CompositionTests, SupportedArithmeticTypes);


    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        // STATIC TEST SETUP
        constexpr flcn::Mat2 MAT2(1, 2, 3, 4);
        constexpr flcn::Mat2x4 MAT2X4(5, 6, 7, 8, 9, 10, 11, 12);

        constexpr flcn::Mat4 MAT4(5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20);
        constexpr flcn::Mat4x2 MAT4X2(5, 6, 7, 8, 9, 10, 11, 12);
        constexpr flcn::Mat4x3 MAT4X3(5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);


        /// @test Verify that 2x4 matrix times a 4x2 matrix yields a 2x2 matrix at compile time.
        constexpr auto EXP_MAT2 = MAT2X4 * MAT4X2;
        static_assert(EXP_MAT2[0] == flcn::CVec2{ 218, 346 });
        static_assert(EXP_MAT2[1] == flcn::CVec2{ 244, 388 });

        /// @test Verify that 2x4 matrix times a 4x3 matrix yields a 2x3 matrix at compile time.
        constexpr auto EXP_MAT2X3 = MAT2X4 * MAT4X3;
        static_assert(EXP_MAT2X3[0] == flcn::CVec2{ 262, 414 });
        static_assert(EXP_MAT2X3[1] == flcn::CVec2{ 288, 456 });
        static_assert(EXP_MAT2X3[2] == flcn::CVec2{ 314, 498 });


        /// @test Verify that 2x4 matrix times a 4x4 matrix yields a 2x4 matrix at compile time.
        constexpr auto EXP_MAT2X4 = MAT2X4 * MAT4;
        static_assert(EXP_MAT2X4[0] == flcn::CVec2{ 306, 482 });
        static_assert(EXP_MAT2X4[1] == flcn::CVec2{ 332, 524 });
        static_assert(EXP_MAT2X4[2] == flcn::CVec2{ 358, 566 });
        static_assert(EXP_MAT2X4[3] == flcn::CVec2{ 384, 608 });

        /// @test Verify that 2x2 matrix times a 2x4 matrix yields a 2x4 matrix at compile time.
        constexpr auto EXP_MAT2X4SQ = MAT2 * MAT2X4;
        static_assert(EXP_MAT2X4SQ[0] == flcn::CVec2{ 23, 51 });
        static_assert(EXP_MAT2X4SQ[1] == flcn::CVec2{ 26, 58 });
        static_assert(EXP_MAT2X4SQ[2] == flcn::CVec2{ 29, 65 });
        static_assert(EXP_MAT2X4SQ[3] == flcn::CVec2{ 32, 72 });

    } // namespace static_tests

} // namespace



/**************************************
 *                                    *
 *            RUNTIME TESTS           *
 *                                    *
 **************************************/

TYPED_TEST(Mat2x4CompositionTests, Mat2x4TimesMat4x2_ReturnsAValid2DMatrix)
{
    const auto matrixProduct = this->_mat2x4 * this->_mat4x2;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat2, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat2, matrixProduct);
    }
}


TYPED_TEST(Mat2x4CompositionTests, Mat2x4TimesMat4_ReturnsAValid2x4Matrix)
{
    const auto matrixProduct = this->_mat2x4 * this->_mat4;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat2x4x4D, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat2x4x4D, matrixProduct);
    }
}


TYPED_TEST(Mat2x4CompositionTests, Mat2x4TimesMat4x3_ReturnsAValid2x3Matrix)
{
    const auto matrixProduct = this->_mat2x4 * this->_mat4x3;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat2x3, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat2x3, matrixProduct);
    }
}


TYPED_TEST(Mat2x4CompositionTests, Mat2TimesMat2x4_ReturnsAValid2x4Matrix)
{
    const auto matrixProduct = this->_mat2 * this->_mat2x4;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat2Dx2x4, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat2Dx2x4, matrixProduct);
    }
}



/** @} */
