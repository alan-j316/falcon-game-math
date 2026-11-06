/**
 * @file Mat2x4.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 24, 2026
 *
 * @brief Verify @ref flcn::Mat2x4 vector and matrix GeometricOps logic.
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
 * @addtogroup T_FALCON_Mat2x4_Geom
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2x4 matrix geometric operations (Matrix-Vector Multiplication).
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices and vectors.
     */
    template <typename T>
    class Mat2x4GeometricOpsTests: public testing::Test
    {

    protected:
        flcn::CVec2<T> _vec2, _expectedFPCVec2, _expectedIntCVec2;
        flcn::Vec4<T> _vec4, _expectedFPVec4, _expectedIntVec4;

        flcn::Mat2x4<T> _mat2x4;


        void SetUp() override
        {

            _vec2            = flcn::CVec2{ T(1.23412341000000003), T(2.21341324399999984) };
            _expectedFPCVec2  = flcn::CVec2{ T(32.15467085860238683), T(24.40151006828770974) };
            _expectedIntCVec2 = flcn::CVec2{ T(30), T(23) };

            _vec4            = flcn::Vec4{ T(1.32194213899999991), T(2.12304122299999998), T(3.02134123399999988),
                               T(4.01283041000000029) };
            _expectedFPVec4  = flcn::Vec4{ T(10.77767014729188588), T(3.52277011050120237), T(17.28037759123665751),
                                         T(4.92348186700635182) };
            _expectedIntVec4 = flcn::Vec4{ T(9), T(3), T(15), T(4) };


            _mat2x4            = { flcn::CVec2{ T(5.12390421300000032), T(2.01234000000000002) },
                                   flcn::CVec2{ T(1.01820339999999998), T(1.02384019999999998) },
                                   flcn::CVec2{ T(5.01238399999999995), T(5.01238401234000008) },
                                   flcn::CVec2{ T(2.01238399999999995), T(1.10234800000000011) } };
        }
    };
    TYPED_TEST_SUITE(Mat2x4GeometricOpsTests, SupportedArithmeticTypes);


    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        // STATIC TEST SETUP
        constexpr flcn::CVec2 ROW_VEC2(1, 2);
        constexpr flcn::Vec4 VEC4(1, 2, 3, 4);

        constexpr flcn::Mat2x4 MAT2X4(5, 6, 7, 8, 9, 10, 11, 12);


        /// @test Verify that 2x4 matrix times a 4D column vector yields a 2D column vector at compile time.
        constexpr auto EXP_VEC2 = MAT2X4 * VEC4;
        static_assert(EXP_VEC2.x() == 70);
        static_assert(EXP_VEC2.y() == 110);

        /// @test Verify that 2D row vector times a 2x4 matrix yields a 4D row vector at compile time.
        constexpr auto EXP_ROW_VEC4 = ROW_VEC2 * MAT2X4;
        static_assert(EXP_ROW_VEC4.x() == 23);
        static_assert(EXP_ROW_VEC4.y() == 26);
        static_assert(EXP_ROW_VEC4.z() == 29);
        static_assert(EXP_ROW_VEC4.w() == 32);

    } // namespace static_tests

} // namespace



/**************************************
 *            RUNTIME TESTS           *
 **************************************/

TYPED_TEST(Mat2x4GeometricOpsTests, Mat2x4Times4DVector_ReturnsAValid2DVector)
{
    const auto expectedVector = this->_mat2x4 * this->_vec4;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFPCVec2, expectedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntCVec2, expectedVector);
    }
}


TYPED_TEST(Mat2x4GeometricOpsTests, 2DRowVectorTimesMat2x4_ReturnsAValid4DRowVector)
{
    const auto expectedVector = this->_vec2 * this->_mat2x4;
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
