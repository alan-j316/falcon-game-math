/**
 * @file Mat3x2.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 25, 2026
 *
 * @brief Verify @ref flcn::Mat3x2 vector and matrix GeometricOps logic.
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
 * @addtogroup T_FALCON_Mat3x2_Geom
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat3x2 matrix geometric operations (Matrix-Vector Multiplication).
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices and vectors.
     */
    template <typename T>
    class Mat3x2GeometricOpsTests: public testing::Test
    {

    protected:
        flcn::CVec2<T> _vec2, _expectedFPCVec2, _expectedIntCVec2;
        flcn::Vec3<T> _vec3, _expectedFPVec3, _expectedIntVec3;

        flcn::Mat3x2<T> _mat3x2;


        void SetUp() override
        {
            _vec2            = flcn::CVec2{ T(1.23412341000000003), T(2.21341324399999984) };
            _expectedFPCVec2  = flcn::CVec2{ T(23.57800617829743928), T(29.49140573069764315) };
            _expectedIntCVec2 = flcn::CVec2{ T(22), T(28) };

            _vec3            = flcn::Vec3{ T(1.32194213899999991), T(2.12304122299999998), T(3.02134123399999988) };
            _expectedFPVec3  = flcn::Vec3{ T(6.33060730095153090), T(12.61075992189763717), T(19.60486191482313600) };
            _expectedIntVec3 = flcn::Vec3{ T(5), T(11), T(17) };


            _mat3x2 = { flcn::Vec3{ T(1.32194213899999991), T(3.02134123399999988), T(5.10238399999999981) },
                        flcn::Vec3{ T(2.12304122299999998), T(4.01283041000000029), T(6.01238399999999995) } };
        }
    };
    TYPED_TEST_SUITE(Mat3x2GeometricOpsTests, SupportedArithmeticTypes);


    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        // STATIC TEST SETUP
        constexpr flcn::CVec2 VEC2(1, 2);
        constexpr flcn::Vec3 ROW_VEC3(1, 2, 3);

        constexpr flcn::Mat3x2 MAT3X2(1, 2, 3, 4, 5, 6);


        /// @test Verify that 3x2 matrix times a 2D column vector yields a 3D column vector at compile time.
        constexpr auto EXP_VEC3 = MAT3X2 * VEC2;
        static_assert(EXP_VEC3.x() == 5);
        static_assert(EXP_VEC3.y() == 11);
        static_assert(EXP_VEC3.z() == 17);

        /// @test Verify that 3D row vector times a 3x2 matrix yields a 2D row vector at compile time.
        constexpr auto EXP_ROW_VEC2 = ROW_VEC3 * MAT3X2;
        static_assert(EXP_ROW_VEC2.x() == 22);
        static_assert(EXP_ROW_VEC2.y() == 28);


    } // namespace static_tests

} // namespace



/**************************************
 *            RUNTIME TESTS           *
 **************************************/

TYPED_TEST(Mat3x2GeometricOpsTests, Mat3x2Times2DVector_ReturnsAValid3DVector)
{
    const auto expectedVector = this->_mat3x2 * this->_vec2;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFPVec3, expectedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntVec3, expectedVector);
    }
}


TYPED_TEST(Mat3x2GeometricOpsTests, 3DRowVectorTimesMat3x2_ReturnsAValid2DRowVector)
{
    const auto expectedVector = this->_vec3 * this->_mat3x2;
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
