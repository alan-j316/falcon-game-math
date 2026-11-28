/**
 * @file ConstantsTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 06, 2026
 *
 * @brief Verify @ref flcn::Quaternion constants (@ref flcn::Quaternion::one(), @ref flcn::Quaternion::zero(),
 *        @ref flcn::Quaternion::identity()).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "QuatTestSetup.h"



/**
 * @addtogroup T_Falcon_Quaternion_Const
 * @{
 */

namespace
{
    /**************************************
     *             TEST SETUP             *
     **************************************/

    /**
     * @brief Test fixture for testing @ref flcn::Quaternions across different types.
     *
     * @tparam T The scalar type of values to check against.
     */
    template <typename T>
    class QuaternionConstants: public testing::Test
    {
    protected:
        T _one  = T(1);
        T _zero = T(0);
    };
    TYPED_TEST_SUITE(QuaternionConstants, SupportedSignedArithmeticTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that @ref Quaternion::one() returns a quaternion with unit components at compile time.
        static_assert(flcn::Quat<int>::one().x() == 1);
        static_assert(flcn::Quat<int>::one().y() == 1);
        static_assert(flcn::Quat<int>::one().z() == 1);
        static_assert(flcn::Quat<int>::one().w() == 1);

        /// @test Verify that @ref Quaternion::zero() returns a quaternion with unit components at compile time.
        static_assert(flcn::Quat<int>::zero().x() == 0);
        static_assert(flcn::Quat<int>::zero().y() == 0);
        static_assert(flcn::Quat<int>::zero().z() == 0);
        static_assert(flcn::Quat<int>::zero().w() == 0);


        /// @test Verify that @ref Quaternion::identity() returns a quaternion with unit scalar and
        ///       zero vector part at compile time.
        static_assert(flcn::Quat<int>::zero().x() == 0);
        static_assert(flcn::Quat<int>::zero().y() == 0);
        static_assert(flcn::Quat<int>::zero().z() == 0);
        static_assert(flcn::Quat<int>::zero().w() == 0);

    } // namespace static_tests

} // namespace



TYPED_TEST(QuaternionConstants, One_ReturnsAQuaternionWithUnitComponents)
{
    const auto one = TypeParam(1);
    EXPECT_QUAT_CONTAINS(flcn::Quat<TypeParam>::one(), one, one, one, one);
}


TYPED_TEST(QuaternionConstants, Zero_ReturnsAQuaternionWithZeroComponents)
{
    const auto zero = TypeParam(0);
    EXPECT_QUAT_CONTAINS(flcn::Quat<TypeParam>::zero(), zero, zero, zero, zero);
}


TYPED_TEST(QuaternionConstants, Identity_ReturnsAQuaternionWithUnitScalarAndZeroVectorPart)
{
    const auto zero = TypeParam(0);
    const auto one  = TypeParam(1);
    // NOTE: Quaternion is of the form [v w] = [i j k w]
    EXPECT_QUAT_CONTAINS(flcn::Quat<TypeParam>::identity(), zero, zero, zero, one);
}



/** @} */
