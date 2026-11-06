/**
 * @file NegationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref flcn::Mat4 negation logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat4x4_Negation
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat4 Negation(-Mat).
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat4NegationTests: public testing::Test
    {
    protected:
        flcn::Mat4<T> _matA, _expectedMat;

        void SetUp() override
        {
            _matA        = { flcn::Vec4<T>(-1, 2, 3, -4), flcn::Vec4<T>(5, 6, 7, 8), flcn::Vec4<T>(0, 15, -12, 22),
                             flcn::Vec4<T>(1, 3, 1, 6) };
            _expectedMat = { flcn::Vec4<T>(1, -2, -3, 4), flcn::Vec4<T>(-5, -6, -7, -8), flcn::Vec4<T>(0, -15, 12, -22),
                             flcn::Vec4<T>(-1, -3, -1, -6) };
        }
    };
    TYPED_TEST_SUITE(Mat4NegationTests, SupportedSignedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat4 MAT(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        constexpr flcn::Mat4 NEG_MAT = -MAT;

        /** @test Verify that matrix negation returns a valid matrix at compile time. */
        static_assert(NEG_MAT(0, 0) == -MAT(0, 0));
        static_assert(NEG_MAT(0, 1) == -MAT(0, 1));
        static_assert(NEG_MAT(0, 2) == -MAT(0, 2));
        static_assert(NEG_MAT(0, 3) == -MAT(0, 3));
        static_assert(NEG_MAT(1, 0) == -MAT(1, 0));
        static_assert(NEG_MAT(1, 1) == -MAT(1, 1));
        static_assert(NEG_MAT(1, 2) == -MAT(1, 2));
        static_assert(NEG_MAT(1, 3) == -MAT(1, 3));
        static_assert(NEG_MAT(2, 0) == -MAT(2, 0));
        static_assert(NEG_MAT(2, 1) == -MAT(2, 1));
        static_assert(NEG_MAT(2, 2) == -MAT(2, 2));
        static_assert(NEG_MAT(2, 3) == -MAT(2, 3));
        static_assert(NEG_MAT(3, 0) == -MAT(3, 0));
        static_assert(NEG_MAT(3, 1) == -MAT(3, 1));
        static_assert(NEG_MAT(3, 2) == -MAT(3, 2));
        static_assert(NEG_MAT(3, 3) == -MAT(3, 3));

    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat4NegationTests, ReturnsElementWiseNegatedMatrix)
{
    const flcn::Mat4 negMat = -this->_matA;
    EXPECT_MAT_EQ(this->_expectedMat, negMat);
}

/** @} */
