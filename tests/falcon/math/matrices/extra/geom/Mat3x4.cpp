/**
 * @file Mat3x4.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 25, 2026
 *
 * @brief Verify @ref flcn::Mat3x4 vector and matrix GeometricOps logic.
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
 * @addtogroup T_FALCON_Mat3x4_Geom
 * @{
 */

namespace
{

    /**************************************
     *               SETUP                *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat3x4 matrix geometric operations (Matrix-Vector Multiplication).
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices and vectors.
     */
    template <typename T>
    class Mat3x4GeometricOpsTests: public testing::Test
    {

    protected:
        flcn::Vec3<T> _vec3, _expectedFPVec3, _expectedIntVec3;
        flcn::Vec4<T> _vec4, _expectedFPVec4, _expectedIntVec4;

        flcn::Mat3x4<T> _mat3x4;

        void SetUp() override
        {

            _vec3            = flcn::Vec3{ T(1.32194213899999991), T(2.12304122299999998), T(3.02134123399999988) };
            _expectedFPVec3  = { flcn::Vec3{ T(32.15467085860238683), T(24.40151006828770974),
                                           T(16.28906864577547253) } };
            _expectedIntVec3 = { flcn::Vec3{ T(30), T(23), T(15) } };

            _vec4            = { flcn::Vec4{ T(1.32194213899999991), T(2.12304122299999998), T(3.02134123399999988),
                                 T(4.01283041000000029) } };
            _expectedFPVec4  = flcn::Vec4{ T(11.08456156345330790), T(4.27872517874863956), T(20.91827216587800464),
                                         T(14.10190761507471002) };
            _expectedIntVec4 = flcn::Vec4{ T(9), T(3), T(18), T(13) };

            _mat3x4           = { flcn::Vec3{ T(5.12390421300000032), T(2.01234000000000002), T(0.01283400000000000) },
                                  flcn::Vec3{ T(1.01820339999999998), T(1.02384019999999998), T(0.25123420000000002) },
                                  flcn::Vec3{ T(5.01238399999999995), T(5.01238401234000008), T(1.20830199999999999) },
                                  flcn::Vec3{ T(2.01238399999999995), T(1.10234800000000011), T(3.01234499999999983) } };
        }
    };
    TYPED_TEST_SUITE(Mat3x4GeometricOpsTests, SupportedArithmeticTypes);


    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        // STATIC TEST SETUP
        constexpr flcn::Vec3 ROW_VEC3(1, 2, 3);
        constexpr flcn::Vec4 VEC4(1, 2, 3, 4);

        constexpr flcn::Mat3x4 MAT3X4(5, 1, 5, 2, 2, 1, 5, 1, 0, 0, 1, 3);


        /// @test Verify that 3x4 matrix times a 4D column vector yields a 3D column vector at compile time.
        constexpr auto EXP_VEC3 = MAT3X4 * VEC4;
        static_assert(EXP_VEC3.x() == 30);
        static_assert(EXP_VEC3.y() == 23);
        static_assert(EXP_VEC3.z() == 15);

        /// @test Verify that 3D row vector times a 3x4 matrix yields a 4D row vector at compile time.
        constexpr auto EXP_ROW_VEC4 = ROW_VEC3 * MAT3X4;
        static_assert(EXP_ROW_VEC4.x() == 9);
        static_assert(EXP_ROW_VEC4.y() == 3);
        static_assert(EXP_ROW_VEC4.z() == 18);
        static_assert(EXP_ROW_VEC4.w() == 13);

    } // namespace static_tests

} // namespace



/**************************************
 *            RUNTIME TESTS           *
 **************************************/

TYPED_TEST(Mat3x4GeometricOpsTests, Mat3x4Times4DVector_ReturnsAValid3DVector)
{
    const auto expectedVector = this->_mat3x4 * this->_vec4;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFPVec3, expectedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntVec3, expectedVector);
    }
}


TYPED_TEST(Mat3x4GeometricOpsTests, 3DRowVectorTimesMat3x4_ReturnsAValid4DRowVector)
{
    const auto expectedVector = this->_vec3 * this->_mat3x4;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFPVec4, expectedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntVec4, expectedVector);
    }
}

/** @} */
