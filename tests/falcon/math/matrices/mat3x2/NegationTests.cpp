/**
 * @file NegationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref flcn::Mat3x2 negation logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3x2TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat3x2_Negation
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat3x2 Negation(-Mat).
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat3x2NegationTests: public testing::Test
    {
    protected:
        flcn::Mat3x2<T> _matA, _expectedMat;

        void SetUp() override
        {
            _matA        = { flcn::Vec3<T>(-1, 2, 3), flcn::Vec3<T>(5, 6, 7) };
            _expectedMat = { flcn::Vec3<T>(1, -2, -3), flcn::Vec3<T>(-5, -6, -7) };
        }
    };
    TYPED_TEST_SUITE(Mat3x2NegationTests, SupportedSignedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat3x2 MAT(1, 2, 3, 4, 5, 6);
        constexpr flcn::Mat3x2 NEG_MAT = -MAT;
        /** @test Verify that matrix negation returns a valid matrix at compile time. */
        static_assert(NEG_MAT(0, 0) == -MAT(0, 0));
        static_assert(NEG_MAT(0, 1) == -MAT(0, 1));
        static_assert(NEG_MAT(1, 0) == -MAT(1, 0));
        static_assert(NEG_MAT(1, 1) == -MAT(1, 1));
        static_assert(NEG_MAT(2, 0) == -MAT(2, 0));
        static_assert(NEG_MAT(2, 1) == -MAT(2, 1));

    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat3x2NegationTests, ReturnsElementWiseNegatedMatrix)
{
    const flcn::Mat3x2 negMat = -this->_matA;
    EXPECT_MAT_EQ(this->_expectedMat, negMat);
}

/** @} */
