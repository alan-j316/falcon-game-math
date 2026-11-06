/**
 * @file TraceTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 17, 2026
 *
 * @brief Verify @ref flcn::Mat2 trace operation logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2TestSetup.h"



/**
 * @addtogroup T_FALCON_Mat2x2_Trace
 * @{
 */

namespace
{

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2 Trace (Sum along diagonals).
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2TraceTests: public ::testing::Test
    {
    protected:
        flcn::Mat2<T> _mat;
        T _expectedSum;

        void SetUp() override
        {
            _mat         = { flcn::CVec2{ T(5.1234523151234), T(1.2521412341253) },
                             flcn::CVec2{ T(8.1234983217498234), T(3.12348219341342) } };
            _expectedSum = T(8.24693450853682);
        }
    };
    TYPED_TEST_SUITE(Mat2TraceTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat2 MAT(3, 2, 5, 7);

        /// @test Verify that the Mat2 trace returns valid scalar at compile time.
        static_assert(MAT.trace() == 10);

        /// @test Verify that the Mat2 trace (static wrapper) returns valid scalar at compile time.
        static_assert(flcn::Mat2<int>::trace(MAT) == 10);
    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat2TraceTests, ReturnsSumOfDiagonalElements) { EXPECT_MAG_EQ(this->_expectedSum, this->_mat.trace()); }


TYPED_TEST(Mat2TraceTests, StaticWrapper_ReturnsSumOfDiagonalElements)
{ EXPECT_MAG_EQ(this->_expectedSum, flcn::Mat2<TypeParam>::trace(this->_mat)); }

/** @} */
