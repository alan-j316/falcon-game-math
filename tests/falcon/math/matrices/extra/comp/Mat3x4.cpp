/**
 * @file Mat3x4.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 25, 2026
 *
 * @brief Verify @ref flcn::Mat3x4 composition (matrix-matrix Composition) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CommonSetup.h"
#include "utils/MatrixUtils.h"

#include <falcon/math/matrices/extra/Comp.h>
#include <gtest/gtest.h>


using namespace testutils;



/**
 * @addtogroup T_FALCON_Mat3x4_Comp
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat3x4 matrix composition.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat3x4CompositionTests: public testing::Test
    {

    protected:
        flcn::Mat3x2<T> _expectedFPMat3x2, _expectedIntMat3x2;
        // 3D x 3x4 -> 3x3 matrix * 3x4 matrix result
        // 3x4 x 4D -> 3x4 matrix * 4x4 matrix result
        flcn::Mat3x4<T> _mat3x4, _expectedFPMat3Dx3x4, _expectedIntMat3Dx3x4, _expectedFPMat3x4x4D,
            _expectedIntMat3x4x4D;
        flcn::Mat3<T> _mat3, _expectedFPMat3, _expectedIntMat3;
        flcn::Mat4<T> _mat4;
        flcn::Mat4x2<T> _mat4x2;
        flcn::Mat4x3<T> _mat4x3;

        void SetUp() override
        {
            _expectedFPMat3  = { flcn::Vec3{ T(59.71294882333997123), T(40.93849965675766356), T(16.03666856715538813) },
                                 flcn::Vec3{ T(17.06563996375492565), T(11.97595332411097502), T(8.24852207871460053) },
                                 flcn::Vec3{ T(70.16686590855846362), T(46.29281811210886133),
                                           T(33.79743870785883786) } };
            _expectedIntMat3 = { flcn::Vec3{ T(58), T(40), T(14) }, flcn::Vec3{ T(16), T(11), T(7) },
                                 flcn::Vec3{ T(69), T(45), T(32) } };


            _mat3 = { flcn::Vec3{ T(5.12390421300000032), T(2.01238399999999995), T(5.01238401234000008) },
                      flcn::Vec3{ T(1.01820339999999998), T(2.01234000000000002), T(1.10234800000000011) },
                      flcn::Vec3{ T(5.01238399999999995), T(1.02384019999999998), T(0.01283400000000000) } };

            _expectedFPMat3x2 = {
                flcn::Vec3{ T(51.53148302175357287), T(31.05492997565247038), T(18.85558683533477620) },
                flcn::Vec3{ T(14.61642063652532286), T(10.45638242976778720), T(5.07640795416880053) }
            };
            _expectedIntMat3x2 = { flcn::Vec3{ T(50), T(30), T(17) }, flcn::Vec3{ T(14), T(10), T(4) } };

            _mat3x4 = { flcn::Vec3{ T(5.12390421300000032), T(2.01234000000000002), T(0.01283400000000000) },
                        flcn::Vec3{ T(1.01820339999999998), T(1.02384019999999998), T(0.25123420000000002) },
                        flcn::Vec3{ T(5.01238399999999995), T(5.01238401234000008), T(1.20830199999999999) },
                        flcn::Vec3{ T(2.01238399999999995), T(1.10234800000000011), T(3.01234499999999983) } };
            _expectedFPMat3x4x4D = {
                flcn::Vec3{ T(67.53826583649818360), T(45.22504796609911892), T(27.75047042839509359) },
                flcn::Vec3{ T(28.27462878677400582), T(22.23648098676159535), T(13.56335074930463946) },
                flcn::Vec3{ T(51.74586730346002383), T(31.51383195965590645), T(19.32819075818702714) },
                flcn::Vec3{ T(66.95907009498898788), T(56.22624476530457116), T(26.12189714725359835) }
            };
            _expectedIntMat3x4x4D = { flcn::Vec3{ T(66), T(44), T(26) }, flcn::Vec3{ T(27), T(21), T(12) },
                                      flcn::Vec3{ T(50), T(30), T(17) }, flcn::Vec3{ T(64), T(54), T(21) } };
            _expectedFPMat3Dx3x4  = {
                flcn::Vec3{ T(28.36769475021115383), T(14.37391509650059263), T(27.90143924387877306) },
                flcn::Vec3{ T(7.51893654798040423), T(4.36655449254844008), T(6.23547897998262979) },
                flcn::Vec3{ T(36.84307555021202063), T(21.41057036818867587), T(30.66489226441179383) },
                flcn::Vec3{ T(26.53270721783699315), T(9.35214824504499909), T(11.34067293712281810) }
            };
            _expectedIntMat3Dx3x4 = { flcn::Vec3{ T(27), T(14), T(27) }, flcn::Vec3{ T(6), T(4), T(6) },
                                      flcn::Vec3{ T(35), T(21), T(30) }, flcn::Vec3{ T(26), T(9), T(11) } };


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
    TYPED_TEST_SUITE(Mat3x4CompositionTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        // STATIC TEST SETUP
        constexpr flcn::Mat3x4 MAT3X4(5, 1, 5, 2, 2, 1, 5, 1, 0, 0, 1, 3);

        constexpr flcn::Mat4 MAT4(5, 1, 5, 2, 2, 1, 5, 1, 5, 3, 2, 9, 7, 3, 5, 4);
        constexpr flcn::Mat4x2 MAT4X2(5, 1, 5, 2, 2, 1, 5, 1);
        constexpr flcn::Mat4x3 MAT4X3(5, 1, 5, 2, 2, 1, 5, 1, 5, 3, 2, 9);
        constexpr flcn::Mat3 MAT3(5, 1, 5, 2, 2, 1, 5, 1, 0);


        /// @test Verify that 3x4 matrix times a 4x2 matrix yields a 3x2 matrix at compile time.
        constexpr auto EXP_MAT3X2 = MAT3X4 * MAT4X2;
        static_assert(EXP_MAT3X2[0] == flcn::Vec3{ 50, 30, 17 });
        static_assert(EXP_MAT3X2[1] == flcn::Vec3{ 14, 10, 4 });

        /// @test Verify that 3x4 matrix times a 4x3 matrix yields a 3D matrix at compile time.
        constexpr auto EXP_MAT3 = MAT3X4 * MAT4X3;
        static_assert(EXP_MAT3[0] == flcn::Vec3{ 58, 40, 14 });
        static_assert(EXP_MAT3[1] == flcn::Vec3{ 16, 11, 7 });
        static_assert(EXP_MAT3[2] == flcn::Vec3{ 69, 45, 32 });

        /// @test Verify that 2x4 matrix times a 4x4 matrix yields a 3x4 matrix at compile time.
        constexpr auto EXP_MAT3X4 = MAT3X4 * MAT4;
        static_assert(EXP_MAT3X4[0] == flcn::Vec3{ 66, 44, 26 });
        static_assert(EXP_MAT3X4[1] == flcn::Vec3{ 27, 21, 12 });
        static_assert(EXP_MAT3X4[2] == flcn::Vec3{ 50, 30, 17 });
        static_assert(EXP_MAT3X4[3] == flcn::Vec3{ 64, 54, 21 });

        /// @test Verify that 3D matrix times a 3x4 matrix yields a 3x4 matrix at compile time.
        constexpr auto EXP_MAT3X4SQ = MAT3 * MAT3X4;
        static_assert(EXP_MAT3X4SQ[0] == flcn::Vec3{ 27, 14, 27 });
        static_assert(EXP_MAT3X4SQ[1] == flcn::Vec3{ 6, 4, 6 });
        static_assert(EXP_MAT3X4SQ[2] == flcn::Vec3{ 35, 21, 30 });
        static_assert(EXP_MAT3X4SQ[3] == flcn::Vec3{ 26, 9, 11 });

    } // namespace static_tests

} // namespace



/**************************************
 *            RUNTIME TESTS           *
 **************************************/

TYPED_TEST(Mat3x4CompositionTests, Mat3x4TimesMat4x2_ReturnsAValid3x2Matrix)
{
    const auto matrixProduct = this->_mat3x4 * this->_mat4x2;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat3x2, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat3x2, matrixProduct);
    }
}


TYPED_TEST(Mat3x4CompositionTests, Mat3x4TimesMat4x3_ReturnsAValid3DMatrix)
{
    const auto matrixProduct = this->_mat3x4 * this->_mat4x3;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat3, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat3, matrixProduct);
    }
}


TYPED_TEST(Mat3x4CompositionTests, Mat3x4TimesMat4_ReturnsAValid3x4Matrix)
{
    const auto matrixProduct = this->_mat3x4 * this->_mat4;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat3x4x4D, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat3x4x4D, matrixProduct);
    }
}


TYPED_TEST(Mat3x4CompositionTests, Mat3DTimesMat3x4_ReturnsAValid3x4Matrix)
{
    const auto matrixProduct = this->_mat3 * this->_mat3x4;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat3Dx3x4, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat3Dx3x4, matrixProduct);
    }
}

/** @} */
