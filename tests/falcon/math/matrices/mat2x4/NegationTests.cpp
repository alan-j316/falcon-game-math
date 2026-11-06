/**
 * @file NegationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref flcn::Mat2x4 negation logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2x4TestSetup.h"
/**
 * @addtogroup T_FALCON_Mat2x4_Negation
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2x4 Negation(-Mat).
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2x4NegationTests: public ::testing::Test
    {
    protected:
        flcn::Mat2x4<T> _matA, _expectedMat;

        void SetUp() override
        {
            _matA        = { flcn::CVec2<T>(-1, 2), flcn::CVec2<T>(5, 6), flcn::CVec2<T>(0, 15), flcn::CVec2<T>(1, 3) };
            _expectedMat = { flcn::CVec2<T>(1, -2), flcn::CVec2<T>(-5, -6), flcn::CVec2<T>(0, -15), flcn::CVec2<T>(-1, -3) };
        }
    };
    /** @brief Test fixture for @ref flcn::Mat2x4 negation, parameterized by @ref SupportedSignedArithmeticTypes. */
    TYPED_TEST_SUITE(Mat2x4NegationTests, SupportedSignedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat2x4 MAT(1, 2, 3, 4, 5, 6, 7, 8);
        constexpr flcn::Mat2x4 NEG_MAT = -MAT;

        /** @test Verify that matrix negation returns a valid matrix at compile time. */
        static_assert(NEG_MAT(0, 0) == -MAT(0, 0));
        static_assert(NEG_MAT(0, 1) == -MAT(0, 1));
        static_assert(NEG_MAT(0, 2) == -MAT(0, 2));
        static_assert(NEG_MAT(0, 3) == -MAT(0, 3));
        static_assert(NEG_MAT(1, 0) == -MAT(1, 0));
        static_assert(NEG_MAT(1, 1) == -MAT(1, 1));
        static_assert(NEG_MAT(1, 2) == -MAT(1, 2));
        static_assert(NEG_MAT(1, 3) == -MAT(1, 3));

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat2x4NegationTests, ReturnsElementWiseNegatedMatrix)
{
    const flcn::Mat2x4 negMat = -this->_matA;
    EXPECT_MAT_EQ(this->_expectedMat, negMat);
}

/** @} */
