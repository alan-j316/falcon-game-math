/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 01, 2026
 *
 * @brief Verify @ref flcn::Quaternion accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "include/QuaternionTestSetup.h"
#include "utils/VectorUtils.h"



/**
 * @addtogroup T_FALCON_Quaternion_Access_Mutate
 * @{
 */

namespace
{

    /**************************************
     *                                    *
     *            STATIC TESTS            *
     *                                    *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Quaternion QUATERNION(1, 2, 3, 4);

        /// @test Verify that quaternions can be accessed as <x, y, z, w> at compile time.
        static_assert(QUATERNION.x() == 1);
        static_assert(QUATERNION.y() == 2);
        static_assert(QUATERNION.z() == 3);
        static_assert(QUATERNION.w() == 4);


        /// @test Verify that quaternions can be accessed as <i, j, k, s> at compile time.
        static_assert(QUATERNION.i() == 1);
        static_assert(QUATERNION.j() == 2);
        static_assert(QUATERNION.k() == 3);
        static_assert(QUATERNION.s() == 4);

        /// @test Verify that quaternion's getVectorPart returns a valid 3D vector at compile time.
        static_assert(QUATERNION.getVectorPart() == flcn::Vec3{ 1, 2, 3 });

        /// @test Verify that quaternion's getScalarPart returns the fourth component of the vector at compile time.
        static_assert(QUATERNION.getScalarPart() == 4);

    } // namespace static_tests

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

TEST(QuaternionAccess, ComponentsAreAccessibleAsXYZW)
{
    const flcn::Quaternion quat{ 1.0f, 2.0f, 3.0f, 4.0f };

    EXPECT_FLOAT_EQ(1.0f, quat.x());
    EXPECT_FLOAT_EQ(2.0f, quat.y());
    EXPECT_FLOAT_EQ(3.0f, quat.z());
    EXPECT_FLOAT_EQ(4.0f, quat.w());
}


TEST(QuaternionAccess, ComponentsAreAccessibleAsIJKS)
{
    const flcn::Quaternion quat{ 1.0f, 2.0f, 3.0f, 4.0f };

    EXPECT_FLOAT_EQ(1.0f, quat.i());
    EXPECT_FLOAT_EQ(2.0f, quat.j());
    EXPECT_FLOAT_EQ(3.0f, quat.k());
    EXPECT_FLOAT_EQ(4.0f, quat.s());
}


TEST(QuaternionAccess, GetVectorPart_ReturnsAValid3DVector)
{
    const flcn::Quaternion quat{ 1.0f, 2.0f, 3.0f, 4.0f };
    const auto vectorPart = quat.getVectorPart();
    EXPECT_FLOAT_EQ(1.0f, vectorPart.x());
    EXPECT_FLOAT_EQ(2.0f, vectorPart.y());
    EXPECT_FLOAT_EQ(3.0f, vectorPart.z());
}


TEST(QuaternionAccess, GetScalarPart_ReturnsAScalarComponent)
{
    const flcn::Quaternion quat{ 1.0f, 2.0f, 3.0f, 4.0f };
    EXPECT_FLOAT_EQ(4.0f, quat.getScalarPart());
}


TEST(QuaternionMutation, ComponentsCanBeMutatedUsingXYZW)
{
    flcn::Quaternion<float> quat{};

    quat.x() = 1.0f;
    quat.y() = 2.0f;
    quat.z() = 3.0f;
    quat.w() = 4.0f;

    EXPECT_FLOAT_EQ(1.0f, quat.x());
    EXPECT_FLOAT_EQ(2.0f, quat.y());
    EXPECT_FLOAT_EQ(3.0f, quat.z());
    EXPECT_FLOAT_EQ(4.0f, quat.w());
}


TEST(QuaternionMutation, ComponentsCanBeMutatedUsingIJKS)
{
    flcn::Quaternion<float> quat;

    quat.i() = 1.0f;
    quat.j() = 2.0f;
    quat.k() = 3.0f;
    quat.s() = 4.0f;

    EXPECT_FLOAT_EQ(1.0f, quat.i());
    EXPECT_FLOAT_EQ(2.0f, quat.j());
    EXPECT_FLOAT_EQ(3.0f, quat.k());
    EXPECT_FLOAT_EQ(4.0f, quat.s());
}

/** @} */
