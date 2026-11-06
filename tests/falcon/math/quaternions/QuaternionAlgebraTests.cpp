/**
 * @file QuaternionAlgebraTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 03, 2026
 *
 * @brief Verify @ref flcn::Quaternion quaternion algebra(Conjugate, Inverse,...).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "include/QuaternionTestSetup.h"
#include "utils/VectorUtils.h"


/**
 * @addtogroup T_FALCON_Quaternion_Algebra
 * @{
 */

namespace
{
    using namespace testutils;

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for verifying quaternion conjugate across different scalar types.
     *
     * @tparam T The scalar type (uint32_t, float, double...) for the quaternion values.
     */
    template <typename T>
    class QuaternionConjugateTests: public testing::Test
    {
    protected:
        flcn::Quaternion<T> _quat;
        flcn::Quaternion<T> _expectedConjugate;

        void SetUp() override
        {
            _quat              = flcn::Quaternion<T>{ T(8), T(-4), T(7), T(5) };
            _expectedConjugate = flcn::Quaternion<T>{ T(-8), T(4), T(-7), T(5) };
        }
    };
    TYPED_TEST_SUITE(QuaternionConjugateTests, SupportedSignedArithmeticTypes);


    /**
     * @brief Test fixture for verifying quaternion magnitude across different scalar types.
     *
     * @tparam T The scalar type (int, float, double...) for the quaternion values.
     */
    template <typename T>
    class QuaternionMagnitudeTests: public testing::Test
    {
    protected:
        flcn::Quaternion<T> _quat;
        flcn::Magnitude<T> _expectedMagnitude;

        void SetUp() override
        {
            _quat              = { T(1), T(2), T(3), T(4) };
            _expectedMagnitude = flcn::Magnitude<T>(5.477225575051661);
        }
    };
    TYPED_TEST_SUITE(QuaternionMagnitudeTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for verifying quaternion inverse across different scalar types.
     *
     * @tparam T The scalar type (int, float, double...) for the quaternion values.
     */
    template <typename T>
    class QuaternionInverseTests: public testing::Test
    {
    protected:
        using M = flcn::Magnitude<T>;
        flcn::Quaternion<T> _quat;
        flcn::Quaternion<M> _expectedInverse;

        void SetUp() override
        {
            _quat            = { T(3), T(1), T(6), T(4) };
            _expectedInverse = flcn::Quaternion<M>{ M(-0.04838709677419355), M(-0.01612903225806452),
                                                   M(-0.09677419354838709), M(0.06451612903225806) };
        }
    };
    TYPED_TEST_SUITE(QuaternionInverseTests, SupportedSignedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Quaternion QUAT_A(-1, 12, 3, 4);
        // constexpr flcn::Quaternion QUAT_B(5, 12, -5, 3);

        /// @test Verify that quaterion conjugate returns a valid quaternion at compile-time.
        constexpr auto QUAT_CONJUGATE = QUAT_A.conjugate();
        static_assert(QUAT_CONJUGATE.i() == 1);
        static_assert(QUAT_CONJUGATE.j() == -12);
        static_assert(QUAT_CONJUGATE.k() == -3);
        static_assert(QUAT_CONJUGATE.s() == 4);

        /// @test Verify that quaterion conjugate(static wrapper) returns a valid quaternion at compile-time.
        constexpr auto QUAT_CONJUGATE_STATIC = flcn::Quaternion<int>::conjugate(QUAT_A);
        static_assert(QUAT_CONJUGATE_STATIC.i() == 1);
        static_assert(QUAT_CONJUGATE_STATIC.j() == -12);
        static_assert(QUAT_CONJUGATE_STATIC.k() == -3);
        static_assert(QUAT_CONJUGATE_STATIC.s() == 4);

        // TODO: Add quaternion magnitude test after adding flcn::sqrt(constexpr)


        /// @test Verify that quaterion inverse(static wrapper) returns a valid quaternion at compile-time.
        constexpr auto QUAT_INVERSE = QUAT_A.inverse();
        static_assert(QUAT_INVERSE.i() - 0.005882 < flcn::Config::FLOAT_EPSILON);
        static_assert(QUAT_INVERSE.j() - -0.07058 < flcn::Config::FLOAT_EPSILON);
        static_assert(QUAT_INVERSE.k() - -0.01764 < flcn::Config::FLOAT_EPSILON);
        static_assert(QUAT_INVERSE.s() - 0.023529 < flcn::Config::FLOAT_EPSILON);


        /// @test Verify that quaterion inverse(static wrapper) returns a valid quaternion at compile-time.
        constexpr auto QUAT_INVERSE_STATIC = flcn::Quaternion<int>::inverse(QUAT_A);
        static_assert(QUAT_INVERSE_STATIC.i() - 0.005882 < flcn::Config::FLOAT_EPSILON);
        static_assert(QUAT_INVERSE_STATIC.j() - -0.07058 < flcn::Config::FLOAT_EPSILON);
        static_assert(QUAT_INVERSE_STATIC.k() - -0.01764 < flcn::Config::FLOAT_EPSILON);
        static_assert(QUAT_INVERSE_STATIC.s() - 0.023529 < flcn::Config::FLOAT_EPSILON);

    } // namespace static_tests

} // namespace



/**************************************
 *           CONJUGATE TESTS          *
 **************************************/

TYPED_TEST(QuaternionConjugateTests, ReturnsAQuaternionWithInvertedVectorPart)
{ EXPECT_QUAT_EQ(this->_expectedConjugate, this->_quat.conjugate()); }


TYPED_TEST(QuaternionConjugateTests, StaticWrapper_ReturnsAQuaternionWithInvertedVectorPart)
{ EXPECT_QUAT_EQ(this->_expectedConjugate, flcn::Quaternion<TypeParam>::conjugate(this->_quat)); }



/**************************************
 *          MAGNITUDE TESTS           *
 **************************************/

TYPED_TEST(QuaternionMagnitudeTests, NonUnitVectorReturnsCorrectMagnitude)
{
    const auto magnitude = this->_quat.mag();

    static_assert(std::is_floating_point_v<decltype(magnitude)>);
    testutils::EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


TYPED_TEST(QuaternionMagnitudeTests, MagnitudeIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto magnitude = this->_quat.mag();
    static_assert(std::is_floating_point_v<decltype(magnitude)>);
}


TYPED_TEST(QuaternionMagnitudeTests, StaticWrapper_NonUnitVectorReturnsCorrectMagnitude)
{
    const auto magnitude = flcn::Quaternion<TypeParam>::mag(this->_quat);

    static_assert(std::is_floating_point_v<decltype(magnitude)>);
    testutils::EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


TYPED_TEST(QuaternionMagnitudeTests, StaticWrapper_MagnitudeIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto magnitude = flcn::Quaternion<TypeParam>::mag(this->_quat);
    static_assert(std::is_floating_point_v<decltype(magnitude)>);
}



/**************************************
 *           INVERSE TESTS           *
 **************************************/

TYPED_TEST(QuaternionInverseTests, ReturnsValidQuaternion)
{ EXPECT_QUAT_EQ(this->_expectedInverse, this->_quat.inverse()); }


TYPED_TEST(QuaternionInverseTests, AlwaysReturnFloatingPointQuaternion)
{ static_assert(std::is_floating_point_v<typename decltype(this->_quat.inverse())::value_type> == true); }


TYPED_TEST(QuaternionInverseTests, StaticWrapper_ReturnsValidQuaternion)
{ EXPECT_QUAT_EQ(this->_expectedInverse, flcn::Quaternion<TypeParam>::inverse(this->_quat)); }


TYPED_TEST(QuaternionInverseTests, StaticWrapper_AlwaysReturnFloatingPointQuaternion)
{
    static_assert(
        std::is_floating_point_v<typename decltype(flcn::Quaternion<TypeParam>::inverse(this->_quat))::value_type> ==
        true);
}

/** @} */
