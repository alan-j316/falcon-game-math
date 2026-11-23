/**
 * @file Bitwise.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 23, 2026
 *
 * @brief Verifies bitwise operators and functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "falcon/core/Bitwise.h"

#include "CommonSetup.h"


/**
 *  @addtogroup TFalcon_Bitwise
 *  @{
 */

namespace
{
    /// @brief Test fixture for flcn::bitEq.
    /// @tparam T The numeric type of primitives to compare.
    template <typename T>
    class BitEqTests: public testing::Test
    {
    public:
        T eqA, eqB, unEqA;

    protected:
        void SetUp() override
        {
            eqA   = static_cast<T>(55.12394);
            eqB   = static_cast<T>(55.12394);
            unEqA = static_cast<T>(123.0213);
        }
    };

    TYPED_TEST_SUITE(BitEqTests, SupportedArithmeticTypes);


    /// +---------------------------------------------------------------------------------------+
    /// |                                 STATIC TESTS                                          |
    /// +---------------------------------------------------------------------------------------+

    namespace static_tests
    {
        /// @test Verify that flcn::bitEq return valid result at compile time.
        static_assert(flcn::bitEq(4, 4) == true);
        static_assert(flcn::bitEq(4, 8) == false);
        static_assert(flcn::bitEq(4, -4) == false);

        static_assert(flcn::bitEq(4.125, 4.125) == true);
        static_assert(flcn::bitEq(4.125, 8.125) == false);
        static_assert(flcn::bitEq(4.125, -4.125) == false);

        static_assert(flcn::bitEq(4.125f, 4.125f) == true);
        static_assert(flcn::bitEq(4.125f, 8.125f) == false);
        static_assert(flcn::bitEq(4.125f, -4.125f) == false);
    } // namespace static_tests
} // namespace


TYPED_TEST(BitEqTests, EqualValues_ReturnTrue) { EXPECT_TRUE(flcn::bitEq(this->eqA, this->eqB)); }

TYPED_TEST(BitEqTests, UnequalValues_ReturnFalse) { EXPECT_FALSE(flcn::bitEq(this->eqA, this->unEqA)); }

/** @} */
