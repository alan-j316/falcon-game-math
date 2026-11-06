/**
 * @file TraceTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 07, 2026
 *
 * @brief Verify @ref flcn::Mat4 trace operation logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4TestSetup.h"


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
     * @brief Test fixture for @ref flcn::Mat4 Trace (Sum along diagonals).
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat4TraceTests: public testing::Test
    {
    protected:
        flcn::Mat4<T> _mat;
        T _expectedSum;

        void SetUp() override
        {
            _mat = {
                { T(5.1234523151234), T(1.2521412341253), T(5.481578329483), T(5.123891234) },
                { T(8.1234983217498234), T(3.12348219341342), T(1.2138348294893), T(7.9123048192) },
                { T(1.3482939843), T(12.38424812934), T(7.248381294829), T(1.2839812348) },
                { T(3.5382939843), T(1.38324812934), T(1.1232194829), T(5.139832212348) },
            };
            _expectedSum = T(20.63514801571382);
        }
    };
    TYPED_TEST_SUITE(Mat4TraceTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Mat4 MAT(3, 2, 5, 7, 5, 12, 8, 11, 12, 13, 14, 15, 16, 17, 18, 19);

        /// @test Verify that the Mat4 trace returns valid scalar at compile time.
        static_assert(MAT.trace() == 48);

        /// @test Verify that the Mat4 trace (static wrapper) returns valid scalar at compile time.
        static_assert(flcn::Mat4<int>::trace(MAT) == 48);

    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat4TraceTests, ReturnsSumOfDiagonalElements) { EXPECT_MAG_EQ(this->_expectedSum, this->_mat.trace()); }


TYPED_TEST(Mat4TraceTests, StaticWrapper_ReturnsSumOfDiagonalElements)
{ EXPECT_MAG_EQ(this->_expectedSum, flcn::Mat4<TypeParam>::trace(this->_mat)); }

/** @} */
