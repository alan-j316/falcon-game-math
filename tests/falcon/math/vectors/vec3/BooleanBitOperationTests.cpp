/**
 * @file BooleanBitOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify @ref flcn::Vec3 bitwise operator(&, |, !) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"



/**
 * @addtogroup T_FALCON_Vec3_Bool_Bit
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Vec3 boolean bitwise operations.
     */
    class BooleanVec3BitOperationsTests: public testing::Test
    {
    protected:
        flcn::Vec3<bool> _vecA;
        flcn::Vec3<bool> _vecB;
        flcn::Vec3<bool> _expectedConjunctionVector;
        flcn::Vec3<bool> _expectedDisjunctionVec;
        flcn::Vec3<bool> _expectedInvertedVec;

        void SetUp() override
        {
            _vecA                      = { true, false, true };
            _vecB                      = { true, true, false };
            _expectedConjunctionVector = { true, false, false };
            _expectedDisjunctionVec    = { true, true, true };
            _expectedInvertedVec       = { false, true, false };
        }
    };



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Vec3 VEC_A(true, false, true);
        constexpr flcn::Vec3 VEC_B(false, false, true);

        /// @test Verify that vector AND returns a valid vector at compile time.
        constexpr auto AND_VEC = VEC_A & VEC_B;
        static_assert(AND_VEC.x() == false);
        static_assert(AND_VEC.y() == false);
        static_assert(AND_VEC.z() == true);


        /// @test Verify that vector OR returns a valid vector at compile time.
        constexpr auto OR_VEC = VEC_A | VEC_B;
        static_assert(OR_VEC.x() == true);
        static_assert(OR_VEC.y() == false);
        static_assert(OR_VEC.z() == true);


        /// @test Verify that vector NOT returns a valid vector at compile time.
        constexpr auto NOT_VEC = !VEC_A;
        static_assert(NOT_VEC.x() == false);
        static_assert(NOT_VEC.y() == true);
        static_assert(NOT_VEC.z() == false);
    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

/**
 * @test Verify that the bitwise AND operator perform a component-wise logical conjunction and
 *       returns the correct boolean mask.
 */
TEST_F(BooleanVec3BitOperationsTests, BitwiseAND_PerformComponentwiseConjunction)
{
    const auto mask = this->_vecA & this->_vecB;

    EXPECT_VEC_EQ(this->_expectedConjunctionVector, mask);
}

/**
 * @test Verify that the compound bitwise AND operator performs a component-wise logical conjunction in-place
 *       and updates the calling vector with the resulting mask.
 */
TEST_F(BooleanVec3BitOperationsTests, CompoundBitwiseAND_PerformInPlaceConjunction)
{
    this->_vecA &= this->_vecB;
    EXPECT_VEC_EQ(this->_expectedConjunctionVector, this->_vecA);
}


/**
 * @test Verify that the bitwise OR operator performs a component-wise logical disjunction and
 *       returns the correct boolean mask.
 */
TEST_F(BooleanVec3BitOperationsTests, BitwiseOR_PerformComponentwiseDisjunction)
{
    const auto mask = this->_vecA | this->_vecB;
    EXPECT_VEC_EQ(this->_expectedDisjunctionVec, mask);
}


/**
 * @test Verify that the compound bitwise OR operator performs a component-wise logical disjunction in-place
 *       and updates the calling vector with the resulting mask.
 */
TEST_F(BooleanVec3BitOperationsTests, CompoundBitwiseOR_PerformInPlaceDisjunction)
{
    this->_vecA |= this->_vecB;
    EXPECT_VEC_EQ(this->_expectedConjunctionVector, this->_vecA);
}


/**
 * @test Verify that the bitwise NOT operator performs a component-wise logical inversion and
 *       returns the correct boolean mask.
 */
TEST_F(BooleanVec3BitOperationsTests, BitwiseNOT_PerformComponentwiseInversion)
{
    const auto mask = !this->_vecA;
    EXPECT_VEC_EQ(this->_expectedInvertedVec, mask);
}

/** @} */
