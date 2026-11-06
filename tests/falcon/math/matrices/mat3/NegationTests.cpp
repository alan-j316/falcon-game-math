/**
 * @file NegationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref flcn::Mat3 negation logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat3x3_Negation
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat3 Negation(-Mat).
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat3NegationTests: public testing::Test
    {
    protected:
        flcn::Mat3<T> _matA, _expectedMat;

        void SetUp() override
        {
            _matA        = { flcn::Vec3<T>(-1, 2, 3), flcn::Vec3<T>(5, 6, 7), flcn::Vec3<T>(0, 15, -12) };
            _expectedMat = { flcn::Vec3<T>(1, -2, -3), flcn::Vec3<T>(-5, -6, -7), flcn::Vec3<T>(0, -15, 12) };
        }
    };
    TYPED_TEST_SUITE(Mat3NegationTests, SupportedSignedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat3 MAT(1, 2, 3, 4, 5, 6, 7, 8, 9);
        constexpr flcn::Mat3 NEG_MAT = -MAT;

        /** @test Verify that matrix negation returns a valid matrix at compile time. */
        static_assert(NEG_MAT(0, 0) == -MAT(0, 0));
        static_assert(NEG_MAT(0, 1) == -MAT(0, 1));
        static_assert(NEG_MAT(0, 2) == -MAT(0, 2));
        static_assert(NEG_MAT(1, 0) == -MAT(1, 0));
        static_assert(NEG_MAT(1, 1) == -MAT(1, 1));
        static_assert(NEG_MAT(1, 2) == -MAT(1, 2));
        static_assert(NEG_MAT(2, 0) == -MAT(2, 0));
        static_assert(NEG_MAT(2, 1) == -MAT(2, 1));
        static_assert(NEG_MAT(2, 2) == -MAT(2, 2));

    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat3NegationTests, ReturnsElementWiseNegatedMatrix)
{
    const flcn::Mat3 negMat = -this->_matA;
    EXPECT_MAT_EQ(this->_expectedMat, negMat);
}

/** @} */
