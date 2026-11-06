/**
 * @file Mat4x2.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 25, 2026
 *
 * @brief Verify @ref flcn::Mat4x2 vector and matrix GeometricOps logic.
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
 * @addtogroup T_FALCON_Mat4x2_Geom
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4x2 matrix geometric operations (Matrix-Vector Multiplication).
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices and vectors.
     */
    template <typename T>
    class Mat4x2GeometricOpsTests: public testing::Test
    {

    protected:
        flcn::CVec2<T> _vec2, _expectedFPCVec2, _expectedIntCVec2;
        flcn::Vec4<T> _vec4, _expectedFPVec4, _expectedIntVec4;

        flcn::Mat4x2<T> _mat4x2;


        void SetUp() override
        {

            _vec2            = flcn::CVec2{ T(1.23412341000000003), T(2.21341324399999984) };
            _expectedFPCVec2  = flcn::CVec2{ T(43.60881556301329454), T(13.13528635912819098) };
            _expectedIntCVec2 = flcn::CVec2{ T(41), T(12) };


            _vec4            = flcn::Vec4{ T(1.32194213899999991), T(2.12304122299999998), T(3.02134123399999988),
                               T(4.01283041000000029) };
            _expectedFPVec4  = { flcn::Vec4{ T(8.57723503050675617), T(10.64013783192313589), T(4.74965736129900851),
                                           T(8.62585211223543524) } };
            _expectedIntVec4 = { flcn::Vec4{ T(7), T(9), T(4), T(7) } };


            _mat4x2 = { flcn::Vec4{ T(5.12390421300000032), T(5.01238399999999995), T(2.01234000000000002),
                                   T(5.01238401234000008) },
                        flcn::Vec4{ T(1.01820339999999998), T(2.01238399999999995), T(1.02384019999999998),
                                   T(1.10234800000000011) } };
        }
    };
    TYPED_TEST_SUITE(Mat4x2GeometricOpsTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        // STATIC TEST SETUP
        constexpr flcn::CVec2 VEC2(1, 2);
        constexpr flcn::Vec4 ROW_VEC4(1, 2, 3, 4);

        constexpr flcn::Mat4x2 MAT4X2(5, 1, 5, 2, 2, 1, 5, 1);


        /// @test Verify that 4x2 matrix times a 2D column vector yields a 4D column vector at compile time.
        constexpr auto EXP_VEC4 = MAT4X2 * VEC2;
        static_assert(EXP_VEC4.x() == 7);
        static_assert(EXP_VEC4.y() == 9);
        static_assert(EXP_VEC4.z() == 4);
        static_assert(EXP_VEC4.w() == 7);

        /// @test Verify that 4D row vector times a 4x2 matrix yields a 2D row vector at compile time.
        constexpr auto EXP_ROW_VEC2 = ROW_VEC4 * MAT4X2;
        static_assert(EXP_ROW_VEC2.x() == 41);
        static_assert(EXP_ROW_VEC2.y() == 12);

    } // namespace static_tests

} // namespace



/**************************************
 *            RUNTIME TESTS           *
 **************************************/

TYPED_TEST(Mat4x2GeometricOpsTests, Mat4x2Times2DVector_ReturnsAValid4DVector)
{
    const auto expectedVector = this->_mat4x2 * this->_vec2;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFPVec4, expectedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntVec4, expectedVector);
    }
}


TYPED_TEST(Mat4x2GeometricOpsTests, 4DRowVectorTimesMat4x2_ReturnsAValid2DRowVector)
{
    const auto expectedVector = this->_vec4 * this->_mat4x2;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFPCVec2, expectedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntCVec2, expectedVector);
    }
}

/** @} */
