/**
 * @file Mat2x3.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 17, 2026
 *
 * @brief Verify @ref flcn::Mat2x3 vector and matrix GeometricOps logic.
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
 * @addtogroup T_FALCON_Mat2x3_Geom
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2x3 matrix geometric operations (Matrix-Vector Multiplication).
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices and vectors.
     */
    template <typename T>
    class Mat2x3GeometricOpsTests: public ::testing::Test
    {

    protected:
        flcn::CVec2<T> _vec2, _expectedFPCVec2, _expectedIntCVec2;
        flcn::Vec3<T> _vec3, _expectedFPVec3, _expectedIntVec3;

        flcn::Mat2x3<T> _mat2x3;


        void SetUp() override
        {
            _vec2            = flcn::CVec2{ T(1.23412341000000003), T(2.21341324399999984) };
            _expectedFPCVec2  = flcn::CVec2{ T(24.07931514680494445), T(55.89300074421511511) };
            _expectedIntCVec2 = flcn::CVec2{ T(22), T(55) };


            _vec3            = flcn::Vec3{ T(5.12390421300000032), T(1.01820339999999998), T(5.01238399999999995) };
            _expectedFPVec3  = flcn::Vec3{ T(10.51349171582532449), T(13.91377919527302609), T(17.03659832009138242) };
            _expectedIntVec3 = flcn::Vec3{ T(9), T(12), T(15) };

            _mat2x3            = { flcn::CVec2{ T(1.32194213899999991), T(4.01283041000000029) },
                                   flcn::CVec2{ T(2.12304122299999998), T(5.10238399999999981) },
                                   flcn::CVec2{ T(3.02134123399999988), T(6.01238399999999995) } };
        }
    };
    TYPED_TEST_SUITE(Mat2x3GeometricOpsTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        // STATIC TEST SETUP
        constexpr flcn::CVec2 ROW_VEC2(1, 2);
        constexpr flcn::Vec3 VEC3(5, 6, 7);

        constexpr flcn::Mat2x3 MAT2X3(1, 2, 3, 4, 5, 6);


        /// @test Verify that 2x3 matrix times a 3D column vector yields a 2D column vector at compile time.
        constexpr auto EXP_VEC2 = MAT2X3 * VEC3;
        static_assert(EXP_VEC2.x() == 38);
        static_assert(EXP_VEC2.y() == 92);

        /// @test Verify that 2D row vector times a 2x3 matrix yields a 3D row vector at compile time.
        constexpr auto EXP_ROW_VEC3 = ROW_VEC2 * MAT2X3;
        static_assert(EXP_ROW_VEC3.x() == 9);
        static_assert(EXP_ROW_VEC3.y() == 12);
        static_assert(EXP_ROW_VEC3.z() == 15);

    } // namespace static_tests

} // namespace



/**************************************
 *            RUNTIME TESTS           *
 **************************************/

TYPED_TEST(Mat2x3GeometricOpsTests, Mat2x3Times3DVector_ReturnsAValid2DVector)
{
    const auto expectedVector = this->_mat2x3 * this->_vec3;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFPCVec2, expectedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntCVec2, expectedVector);
    }
}


TYPED_TEST(Mat2x3GeometricOpsTests, 2DRowVectorTimeMat2x3_ReturnsAValid3DRowVector)
{
    const auto expectedVector = this->_vec2 * this->_mat2x3;
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
