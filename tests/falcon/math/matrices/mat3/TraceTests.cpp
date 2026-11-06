/**
 * @file TraceTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 05, 2026
 *
 * @brief Verify @ref flcn::Mat3 trace operation logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3TestSetup.h"


/**
 * @addtogroup T_FALCON_Mat3x3_Trace
 * @{
 */

namespace
{

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat3 Trace (Sum along diagonals).
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat3TraceTests: public testing::Test
    {
    protected:
        flcn::Mat3<T> _mat;
        T _expectedSum;

        void SetUp() override
        {
            _mat         = { { T(5.1234523151234), T(1.2521412341253), T(5.481578329483) },
                             { T(8.1234983217498234), T(3.12348219341342), T(1.2138348294893) },
                             { T(1.3482939843), T(12.38424812934), T(7.248381294829) } };
            _expectedSum = T(15.49531580336582);
        }
    };
    TYPED_TEST_SUITE(Mat3TraceTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat3 MAT(3, 2, 5, 7, 5, 12, 8, 11, 12);

        /// @test Verify that the Mat3 trace returns valid scalar at compile time.
        static_assert(MAT.trace() == 20);

        /// @test Verify that the Mat3 trace (static wrapper) returns valid scalar at compile time.
        static_assert(flcn::Mat3<int>::trace(MAT) == 20);

    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat3TraceTests, ReturnsSumOfDiagonalElements) { EXPECT_MAG_EQ(this->_expectedSum, this->_mat.trace()); }


TYPED_TEST(Mat3TraceTests, StaticWrapper_ReturnsSumOfDiagonalElements)
{ EXPECT_MAG_EQ(this->_expectedSum, flcn::Mat3<TypeParam>::trace(this->_mat)); }

/** @} */
