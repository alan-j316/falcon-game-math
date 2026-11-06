/**
 * @file Mat4x2.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 25, 2026
 *
 * @brief Verify @ref flcn::Mat4x2 composition (matrix-matrix Composition) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CommonSetup.h"
#include "utils/MatrixUtils.h"

#include <falcon/math/matrices/extra/Comp.h>
#include <gtest/gtest.h>


using namespace testutils;



/**
 * @addtogroup T_FALCON_Mat4x2_Comp
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4x2 matrix composition.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat4x2CompositionTests: public testing::Test
    {

    protected:
        flcn::Mat2<T> _mat2;
        flcn::Mat2x3<T> _mat2x3;
        flcn::Mat2x4<T> _mat2x4;

        flcn::Mat3x2<T> _mat3x2;

        flcn::Mat4<T> _mat4, _expectedFPMat4, _expectedIntMat4;
        // 4D x 4x2 -> 4x4 matrix * 4x2 matrix result
        // 4x2 x 2D -> 4x2 matrix * 2x2 matrix result
        flcn::Mat4x2<T> _mat4x2, _expectedFPMat4Dx4x2, _expectedIntMat4Dx4x2, _expectedFPMat4x2x2D,
            _expectedIntMat4x2x2D;
        flcn::Mat4x3<T> _expectedFPMat4x3, _expectedIntMat4x3;


        void SetUp() override
        {
            _mat2 = { flcn::CVec2{ T(1.32194213899999991), T(3.02134123399999988) },
                      flcn::CVec2{ T(2.12304122299999998), T(4.01283041000000029) } };

            _mat2x3 = { flcn::CVec2{ T(1.32194213899999991), T(4.01283041000000029) },
                        flcn::CVec2{ T(2.12304122299999998), T(5.10238399999999981) },
                        flcn::CVec2{ T(3.02134123399999988), T(6.01238399999999995) } };

            _mat2x4 = { flcn::CVec2{ T(5.12390421300000032), T(2.01234000000000002) },
                        flcn::CVec2{ T(1.01820339999999998), T(1.02384019999999998) },
                        flcn::CVec2{ T(5.01238399999999995), T(5.01238401234000008) },
                        flcn::CVec2{ T(2.01238399999999995), T(1.10234800000000011) } };


            _mat3x2 = { flcn::Vec3{ T(1.32194213899999991), T(3.02134123399999988), T(5.10238399999999981) },
                        flcn::Vec3{ T(2.12304122299999998), T(4.01283041000000029), T(6.01238399999999995) } };

            _mat4x2 = { flcn::Vec4{ T(5.12390421300000032), T(5.01238399999999995), T(2.01234000000000002),
                                   T(5.01238401234000008) },
                        flcn::Vec4{ T(1.01820339999999998), T(2.01238399999999995), T(1.02384019999999998),
                                   T(1.10234800000000011) } };

            _expectedFPMat4x2x2D = { flcn::Vec4{ T(9.84984481238332776), T(12.70618038429122976), T(5.75356765728206643),
                                                T(9.95665110937957465) },
                                     flcn::Vec4{ T(14.96413743398776930), T(18.71685356930307265),
                                                T(8.38077786423230364), T(15.06503346050664049) } };
            _expectedIntMat4x2x2D = { flcn::Vec4{ T(8), T(11), T(5), T(8) }, flcn::Vec4{ T(14), T(18), T(8), T(14) } };

            _expectedFPMat4Dx4x2  = { flcn::Vec4{ T(51.53148302175357287), T(31.05492997565247038),
                                                T(91.23728708151516287), T(86.74229998537445852) },
                                      flcn::Vec4{ T(14.61642063652532286), T(10.45638242976778720),
                                                T(23.59765950407579993), T(24.16954430946035259) } };
            _expectedIntMat4Dx4x2 = { flcn::Vec4{ T(50), T(30), T(89), T(80) },
                                      flcn::Vec4{ T(14), T(10), T(22), T(22) } };

            _expectedFPMat4x3  = { flcn::Vec4{ T(10.85938246244972660), T(14.70143733824681576), T(6.76869413353574245),
                                             T(11.04961721956482279) },
                                   flcn::Vec4{ T(16.07352460380797510), T(20.90945378096163054), T(9.49630662972862005),
                                             T(16.26610068133595988) },
                                   flcn::Vec4{ T(21.60289290870881729), T(27.24334782329785298), T(12.23568625586436021),
                                             T(21.77186197475720775) } };
            _expectedIntMat4x3 = { flcn::Vec4{ T(9), T(13), T(6), T(9) }, flcn::Vec4{ T(15), T(20), T(9), T(15) },
                                   flcn::Vec4{ T(21), T(27), T(12), T(21) } };


            _mat4            = { flcn::Vec4{ T(5.12390421300000032), T(2.01234000000000002), T(5.01238399999999995),
                                 T(7.01203481000000028) },
                                 flcn::Vec4{ T(1.01820339999999998), T(1.02384019999999998), T(3.12343210000000004),
                                 T(3.16000000000000014) },
                                 flcn::Vec4{ T(5.01238399999999995), T(5.01238401234000008), T(2.12389900000000020),
                                 T(5.12500000000000000) },
                                 flcn::Vec4{ T(2.01238399999999995), T(1.10234800000000011), T(9.10234799999999922),
                                 T(4.91999999999999993) } };
            _expectedFPMat4  = { flcn::Vec4{ T(28.30336581395515338), T(29.73257631333379436), T(12.37135199205641989),
                                           T(27.90127453232277333) },
                                 flcn::Vec4{ T(6.25965426364760447), T(7.16398606794239967), T(3.09722018509204000),
                                           T(6.23225464025983023) },
                                 flcn::Vec4{ T(30.78660193824402214), T(35.21083475174481237), T(15.21850106823098869),
                                           T(30.64938491654379504) },
                                 flcn::Vec4{ T(11.43367733735699332), T(12.30518884108800037), T(5.17822901534960067),
                                           T(11.30201250139281832) } };
            _expectedIntMat4 = { flcn::Vec4{ T(27), T(29), T(12), T(27) }, flcn::Vec4{ T(6), T(7), T(3), T(6) },
                                 flcn::Vec4{ T(30), T(35), T(15), T(30) }, flcn::Vec4{ T(11), T(12), T(5), T(11) } };
        }
    };
    TYPED_TEST_SUITE(Mat4x2CompositionTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        // STATIC TEST SETUP
        constexpr flcn::Mat2 MAT2(1, 2, 3, 4);
        constexpr flcn::Mat2x3 MAT2X3(1, 2, 3, 4, 5, 6);
        constexpr flcn::Mat2x4 MAT2X4(5, 1, 5, 2, 2, 1, 5, 1);

        constexpr flcn::Mat4 MAT4(5, 1, 5, 2, 2, 1, 5, 1, 5, 3, 2, 9, 7, 3, 5, 4);
        constexpr flcn::Mat4x2 MAT4X2(5, 1, 5, 2, 2, 1, 5, 1);


        /// @test Verify that 4x2 matrix times a 2D matrix yields a 4x2 matrix at compile time.
        constexpr auto EXP_MAT4X2 = MAT4X2 * MAT2;
        static_assert(EXP_MAT4X2[0] == flcn::Vec4{ 8, 11, 5, 8 });
        static_assert(EXP_MAT4X2[1] == flcn::Vec4{ 14, 18, 8, 14 });

        /// @test Verify that 4x2 matrix times a 2x3 matrix yields a 4x3 matrix at compile time.
        constexpr auto EXP_MAT4X3 = MAT4X2 * MAT2X3;
        static_assert(EXP_MAT4X3[0] == flcn::Vec4{ 9, 13, 6, 9 });
        static_assert(EXP_MAT4X3[1] == flcn::Vec4{ 15, 20, 9, 15 });
        static_assert(EXP_MAT4X3[2] == flcn::Vec4{ 21, 27, 12, 21 });

        /// @test Verify that 4x2 matrix times a 2x4 matrix yields a 4D matrix at compile time.
        constexpr auto EXP_MAT4 = MAT4X2 * MAT2X4;
        static_assert(EXP_MAT4[0] == flcn::Vec4{ 27, 29, 12, 27 });
        static_assert(EXP_MAT4[1] == flcn::Vec4{ 6, 7, 3, 6 });
        static_assert(EXP_MAT4[2] == flcn::Vec4{ 30, 35, 15, 30 });
        static_assert(EXP_MAT4[3] == flcn::Vec4{ 11, 12, 5, 11 });

        /// @test Verify that 4D matrix times a 4x2 matrix yields a 4x2 matrix at compile time.
        constexpr auto EXP_MAT4X2SQ = MAT4 * MAT4X2;
        static_assert(EXP_MAT4X2SQ[0] == flcn::Vec4{ 50, 30, 89, 80 });
        static_assert(EXP_MAT4X2SQ[1] == flcn::Vec4{ 14, 10, 22, 22 });

    } // namespace static_tests

} // namespace



/**************************************
 *            RUNTIME TESTS           *
 **************************************/

TYPED_TEST(Mat4x2CompositionTests, Mat4x2TimesMat2_ReturnsAValid4x2Matrix)
{
    const auto matrixProduct = this->_mat4x2 * this->_mat2;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat4x2x2D, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat4x2x2D, matrixProduct);
    }
}


TYPED_TEST(Mat4x2CompositionTests, Mat4x2TimesMat2x3_ReturnsAValid4x3Matrix)
{
    const auto matrixProduct = this->_mat4x2 * this->_mat2x3;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat4x3, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat4x3, matrixProduct);
    }
}


TYPED_TEST(Mat4x2CompositionTests, Mat4x2TimesMat2x4_ReturnsAValid4DMatrix)
{
    const auto matrixProduct = this->_mat4x2 * this->_mat2x4;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat4, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat4, matrixProduct);
    }
}


TYPED_TEST(Mat4x2CompositionTests, Mat4TimesMat4x2_ReturnsAValid4x2Matrix)
{
    const auto matrixProduct = this->_mat4 * this->_mat4x2;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat4Dx4x2, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat4Dx4x2, matrixProduct);
    }
}

/** @} */
