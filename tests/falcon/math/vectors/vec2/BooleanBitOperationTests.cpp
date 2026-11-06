/**
 * @file BooleanBitOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref flcn::Vec2 bitwise operator(&, |, !) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"


/**
 * @addtogroup T_FALCON_Vec2_Bool_Bit
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Vec2 boolean bitwise operations.
     */
    class BooleanVec2BitOperationsTests: public testing::Test
    {
    protected:
        flcn::Vec2<bool> _vecA;
        flcn::Vec2<bool> _vecB;
        flcn::Vec2<bool> _expectedConjunctionVector;
        flcn::Vec2<bool> _expectedDisjunctionVec;
        flcn::Vec2<bool> _expectedInvertedVec;

        void SetUp() override
        {
            _vecA                      = { true, false };
            _vecB                      = { true, true };
            _expectedConjunctionVector = { true, false };
            _expectedDisjunctionVec    = { true, true };
            _expectedInvertedVec       = { false, true };
        }
    };

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

/**
 * @test Verify that the bitwise AND operator perform a component-wise logical conjunction and
 *       returns the correct boolean mask.
 */
TEST_F(BooleanVec2BitOperationsTests, BitwiseAND_PerformComponentwiseConjunction)
{
    const auto mask = this->_vecA & this->_vecB;
    EXPECT_VEC_EQ(this->_expectedConjunctionVector, mask);
}


/**
 * @test Verify that the compound bitwise AND operator performs a component-wise logical conjunction in-place
 *       and updates the calling vector with the resulting mask.
 */
TEST_F(BooleanVec2BitOperationsTests, CompoundBitwiseAND_PerformInPlaceConjunction)
{
    this->_vecA &= this->_vecB;
    EXPECT_VEC_EQ(this->_expectedConjunctionVector, this->_vecA);
}


/**
 * @test Verify that the bitwise OR operator performs a component-wise logical disjunction and
 *       returns the correct boolean mask.
 */
TEST_F(BooleanVec2BitOperationsTests, BitwiseOR_PerformComponentwiseDisjunction)
{
    const auto mask = this->_vecA | this->_vecB;
    EXPECT_VEC_EQ(this->_expectedDisjunctionVec, mask);
}


/**
 * @test Verify that the compound bitwise OR operator performs a component-wise logical disjunction in-place
 *       and updates the calling vector with the resulting mask.
 */
TEST_F(BooleanVec2BitOperationsTests, CompoundBitwiseOR_PerformInPlaceDisjunction)
{
    this->_vecA |= this->_vecB;
    EXPECT_VEC_EQ(this->_expectedConjunctionVector, this->_vecA);
}


/**
 * @test Verify that the bitwise NOT operator performs a component-wise logical inversion and
 *       returns the correct boolean mask.
 */
TEST_F(BooleanVec2BitOperationsTests, BitwiseNOT_PerformComponentwiseInversion)
{
    const auto mask = !this->_vecA;
    EXPECT_VEC_EQ(this->_expectedInvertedVec, mask);
}

/** @} */
