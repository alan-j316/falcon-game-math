/**
 * @file Mat4x3.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 25, 2026
 *
 * @brief Verify @ref flcn::Mat4x3 vector and matrix GeometricOps logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CommonSetup.h"
#include "utils/MatrixUtils.h"
#include "utils/VectorUtils.h"

#include <falcon/math/matrices/extra/Geom.h>
#include <gtest/gtest.h>


using namespace testutils;



/**
 * @addtogroup T_FALCON_Mat4x3_Geom
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4x3 matrix geometric operations (Matrix-Vector Multiplication).
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices and vectors.
     */
    template <typename T>
    class Mat4x3GeometricOpsTests: public testing::Test
    {

    protected:
        flcn::Vec3<T> _vec3, _expectedFPVec3, _expectedIntVec3;
        flcn::Vec4<T> _vec4, _expectedFPVec4, _expectedIntVec4;

        flcn::Mat4x3<T> _mat4x3;


        void SetUp() override
        {
            _vec3            = flcn::Vec3{ T(1.32194213899999991), T(2.12304122299999998), T(3.02134123399999988) };
            _expectedFPVec3  = flcn::Vec3{ T(38.72380489544533333), T(17.47170271681091691), T(60.47003789345847480) };
            _expectedIntVec3 = flcn::Vec3{ T(36), T(16), T(58) };

            _vec4            = flcn::Vec4{ T(1.32194213899999991), T(2.12304122299999998), T(3.02134123399999988),
                               T(4.01283041000000029) };
            _expectedFPVec4  = flcn::Vec4{ T(24.07931514680494445), T(10.02590659742800305), T(24.11053434869560164),
                                         T(36.13942098040116946) };
            _expectedIntVec4 = flcn::Vec4{ T(22), T(9), T(22), T(34) };


            _mat4x3 = { flcn::Vec4{ T(5.12390421300000032), T(2.01238399999999995), T(5.01238401234000008),
                                   T(3.12343210000000004) },
                        flcn::Vec4{ T(1.01820339999999998), T(2.01234000000000002), T(1.10234800000000011),
                                   T(2.12389900000000020) },
                        flcn::Vec4{ T(5.01238399999999995), T(1.02384019999999998), T(5.01238399999999995),
                                   T(9.10234799999999922) } };
        }
    };
    TYPED_TEST_SUITE(Mat4x3GeometricOpsTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        // STATIC TEST SETUP
        constexpr flcn::Vec3 VEC3(1, 2, 3);
        constexpr flcn::Vec4 ROW_VEC4(1, 2, 3, 4);

        constexpr flcn::Mat4x3 MAT4X3(5, 1, 5, 2, 2, 1, 5, 1, 5, 3, 2, 9);


        /// @test Verify that 4x3 matrix times a 3D column vector yields a 4D column vector at compile time.
        constexpr auto EXP_VEC4 = MAT4X3 * VEC3;
        static_assert(EXP_VEC4.x() == 22);
        static_assert(EXP_VEC4.y() == 9);
        static_assert(EXP_VEC4.z() == 22);
        static_assert(EXP_VEC4.w() == 34);

        /// @test Verify that 4D row vector times a 4x3 matrix yields a 3D row vector at compile time.
        constexpr auto EXP_ROW_VEC3 = ROW_VEC4 * MAT4X3;
        static_assert(EXP_ROW_VEC3.x() == 36);
        static_assert(EXP_ROW_VEC3.y() == 16);
        static_assert(EXP_ROW_VEC3.z() == 58);

    } // namespace static_tests

} // namespace



/**************************************
 *            RUNTIME TESTS           *
 **************************************/

TYPED_TEST(Mat4x3GeometricOpsTests, Mat4x3Times2DVector_ReturnsAValid4DVector)
{
    const auto expectedVector = this->_mat4x3 * this->_vec3;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFPVec4, expectedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntVec4, expectedVector);
    }
}


TYPED_TEST(Mat4x3GeometricOpsTests, 4DRowVectorTimesMat4x3_ReturnsAValid2DRowVector)
{
    const auto expectedVector = this->_vec4 * this->_mat4x3;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFPVec3, expectedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntVec3, expectedVector);
    }
}

/** @} */
