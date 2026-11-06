/**
 * @file NegationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref flcn::Mat2 negation logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat2x2_Negation
 * @{
 */

namespace
{

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2 Negation(-Mat).
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2NegationTests: public testing::Test
    {
    protected:
        flcn::Mat2<T> _mat, _expectedMat;

        void SetUp() override
        {
            _mat         = { flcn::CVec2<T>(-1, 2), flcn::CVec2<T>(5, 6) };
            _expectedMat = { flcn::CVec2<T>(1, -2), flcn::CVec2<T>(-5, -6) };
        }
    };
    TYPED_TEST_SUITE(Mat2NegationTests, SupportedSignedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat2 MAT(1, 2, 3, 4);
        constexpr flcn::Mat2 NEG_MAT = -MAT;

        /** @test Verify that matrix negation returns a valid matrix at compile time. */
        static_assert(NEG_MAT(0, 0) == -MAT(0, 0));
        static_assert(NEG_MAT(0, 1) == -MAT(0, 1));
        static_assert(NEG_MAT(1, 0) == -MAT(1, 0));
        static_assert(NEG_MAT(1, 1) == -MAT(1, 1));

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat2NegationTests, ReturnsElementWiseNegatedMatrix)
{
    const flcn::Mat2 negMat = -this->_mat;
    EXPECT_MAT_EQ(this->_expectedMat, negMat);
}

/** @} */
