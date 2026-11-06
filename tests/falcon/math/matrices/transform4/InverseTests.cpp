/**
 * @file InverseTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 31, 2026
 *
 * @brief Verify @ref flcn::Transform4 inverse logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Transform4TestSetup.h"



/**
 * @addtogroup T_FALCON_Transform4_Inverse
 * @{
 */

namespace
{

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Transform4 inverse.
     * @tparam T The scalar type (e.g., float, double) used for the transforms.
     */
    template <typename T>
    class Transform4InverseTests: public testing::Test
    {
    protected:
        using Mag = flcn::Magnitude<T>;
        flcn::Transform4<T> _transform;
        flcn::Transform4<Mag> _expectedInverse;

        void SetUp() override
        {
            _transform = { { T(3), T(1), T(8) }, { T(3), T(7), T(4) }, { T(6), T(1), T(2) }, { T(3), T(1), T(6) } };
            _expectedInverse = { { Mag(-0.037878787878788), Mag(-0.022727272727273), Mag(0.196969696969697) },
                                 { Mag(-0.068181818181818), Mag(0.159090909090909), Mag(-0.045454545454545) },
                                 { Mag(0.14772727272727273), Mag(-0.01136363636363636), Mag(-0.06818181818181818) },
                                 { Mag(-0.704545454545455), Mag(-0.022727272727273), Mag(-0.136363636363636) } };
        }
    };
    TYPED_TEST_SUITE(Transform4InverseTests, SupportedSignedArithmeticTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Transform4 TRANSFORM(1.0f, -1.0f, 0.0f, -2.0f, 2.0f, -1.0f, -2.0f, -6.0f, 0.0f, -1.0f, 3.0f,
                                            3.0f);

        /// @test Verify that inverse using inverse returns a valid Transform4 at compile time.
        constexpr flcn::Transform4 INV_TRANSFORM = TRANSFORM.inverse();
        static_assert(INV_TRANSFORM[0] == flcn::Vec3{ -5.0f, -6.0f, -2.0f });
        static_assert(INV_TRANSFORM[1] == flcn::Vec3{ 3.0f, 3.0f, 1.0f });
        static_assert(INV_TRANSFORM[2] == flcn::Vec3{ 2.0f, 2.0f, 1.0f });
        static_assert(INV_TRANSFORM[3] == flcn::Vec3{ 2.0f, 0.0f, -1.0f });

        /// @test Verify that static variant of inverse using inverse returns a valid Transform4 at compile time.
        constexpr flcn::Transform4 INV_TRANSFORM_STATIC = flcn::Transform4<float>::inverse(TRANSFORM);
        static_assert(INV_TRANSFORM_STATIC[0] == flcn::Vec3{ -5.0f, -6.0f, -2.0f });
        static_assert(INV_TRANSFORM_STATIC[1] == flcn::Vec3{ 3.0f, 3.0f, 1.0f });
        static_assert(INV_TRANSFORM_STATIC[2] == flcn::Vec3{ 2.0f, 2.0f, 1.0f });
        static_assert(INV_TRANSFORM_STATIC[3] == flcn::Vec3{ 2.0f, 0.0f, -1.0f });

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Transform4InverseTests, ReturnsInverseMatrix)
{ EXPECT_MAT_EQ(this->_expectedInverse, this->_transform.inverse()); }


TYPED_TEST(Transform4InverseTests, StaticWrapper_ReturnsInverseMatrix)
{ EXPECT_MAT_EQ(this->_expectedInverse, flcn::Transform4<TypeParam>::inverse(this->_transform)); }

/** @} */
