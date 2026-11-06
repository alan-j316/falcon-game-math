/**
 * @file ArithmeticOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 03, 2026
 *
 * @brief Verify @ref flcn::Quaternion arithmetic operator(+, -, *, /) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "include/QuaternionTestSetup.h"


/**
 * @addtogroup T_FALCON_Quaternion_Arithmetic
 * @{
 */

namespace
{

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for verifying quaternion addition across different scalar types.
     *
     * @tparam T The scalar type (uint32_t, float, double...) for the quaternion values.
     */
    template <typename T>
    class QuaternionAddition: public testing::Test
    {
    protected:
        flcn::Quaternion<T> _quatA;
        flcn::Quaternion<T> _quatB;
        flcn::Quaternion<T> _expectedSum;

        void SetUp() override
        {
            _quatA       = { T(3), T(1), T(6), T(2) };
            _quatB       = { T(5), T(3), T(1), T(6) };
            _expectedSum = { T(8), T(4), T(7), T(8) };
        }
    };
    TYPED_TEST_SUITE(QuaternionAddition, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for verifying quaternion subtraction across different scalar types.
     *
     * @tparam T The scalar type (uint32_t, float, double...) for the quaternion values.
     */
    template <typename T>
    class QuaternionSubtraction: public testing::Test
    {
    protected:
        flcn::Quaternion<T> _quatA;
        flcn::Quaternion<T> _quatB;
        flcn::Quaternion<T> _expectedDifference;

        void SetUp() override
        {
            _quatA              = { T(95), T(12), T(5), T(7) };
            _quatB              = { T(88), T(5), T(2), T(5) };
            _expectedDifference = { T(7), T(7), T(3), T(2) };
        }
    };
    TYPED_TEST_SUITE(QuaternionSubtraction, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for verifying quaternion multiplication with scalar across different scalar types.
     *
     * @tparam T The scalar type (uint32_t, float, double...) for the quaternion values.
     */
    template <typename T>
    class QuaternionScalarMultiplication: public testing::Test
    {
    protected:
        flcn::Quaternion<T> _quat;
        T _scalar;
        flcn::Quaternion<T> _expectedFPQuat;
        flcn::Quaternion<T> _expectedIntQuat;

        void SetUp() override
        {
            _quat            = { T(7), T(13), T(29), T(41) };
            _scalar          = T(2.123456789123456);
            _expectedFPQuat  = { T(14.864197523864192), T(27.604938258604928), T(61.580246884580224),
                                 T(87.061728354061696) };
            _expectedIntQuat = { T(14), T(26), T(58), T(82) };
        }
    };
    TYPED_TEST_SUITE(QuaternionScalarMultiplication, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for verifying quaternion multiplication with another quaternion
     *        across different scalar types.
     *
     * @tparam T The scalar type (int32_t, float, double...) for the quaternion values.
     */
    template <typename T>
    class QuaternionQuaternionMultiplication: public testing::Test
    {
    protected:
        flcn::Quaternion<T> _quatA, _quatB, _expectedFPQuat, _expectedIntQuat;

        void SetUp() override
        {
            _quatA           = { T(1.2343241213), T(2.12343214423), T(3.2134324), T(4.123423414) };
            _quatB           = { T(4.29012340), T(2.012384023), T(5.75012034), T(2.41012384023) };
            _expectedFPQuat  = flcn::Quaternion{ T(26.40819961022155127), T(20.10415512983554720),
                                               T(24.82909909011548422), T(-18.10822564795768841) };
            _expectedIntQuat = { T(22), T(19), T(20), T(-15) };
        }
    };
    TYPED_TEST_SUITE(QuaternionQuaternionMultiplication, SupportedSignedArithmeticTypes);


    /**
     * @brief Test fixture for verifying quaternion division by a scalar across different scalar types.
     *
     * @tparam T The scalar type (uint32_t, float, double...) for the quaternion values.
     */
    template <typename T>
    class QuaternionScalarDivision: public testing::Test
    {
    protected:
        flcn::Quaternion<T> _quat;
        T _scalar;
        flcn::Quaternion<T> _expectedScaledVec;

        void SetUp() override
        {
            _quat              = { T(17), T(31), T(59), T(73) };
            _scalar            = T(13);
            _expectedScaledVec = { T(1.30769230769230769231), T(2.38461538461538461538), T(4.53846153846153846154),
                                   T(5.61538461538461538462) };
        }
    };
    TYPED_TEST_SUITE(QuaternionScalarDivision, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for verifying quaternion negation across different scalar types.
     *
     * @tparam T The scalar type (uint32_t, float, double...) for the quaternion values.
     */
    template <typename T>
    class QuaternionNegation: public testing::Test
    {
    protected:
        flcn::Quaternion<T> _quat, _expectedQuat;

        void SetUp() override
        {
            _quat         = flcn::Quaternion<T>{ T(-8), T(0), T(-2), T(5) };
            _expectedQuat = flcn::Quaternion<T>{ T(8), T(0), T(2), T(-5) };
        }
    };
    TYPED_TEST_SUITE(QuaternionNegation, SupportedSignedArithmeticTypes);


    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Quaternion QUAT_A(-1, 12, 3, 4);
        constexpr flcn::Quaternion QUAT_B(5, 12, -5, 3);

        /// @test Verify that quaterion addition returns a valid quaternion at compile-time.
        constexpr auto QUAT_SUM = QUAT_A + QUAT_B;
        static_assert(QUAT_SUM.i() == 4);
        static_assert(QUAT_SUM.j() == 24);
        static_assert(QUAT_SUM.k() == -2);
        static_assert(QUAT_SUM.s() == 7);


        /// @test Verify that quaterion subtraction returns a valid quaternion at compile-time.
        constexpr auto QUAT_DIFF = QUAT_A - QUAT_B;
        static_assert(QUAT_DIFF.i() == -6);
        static_assert(QUAT_DIFF.j() == 0);
        static_assert(QUAT_DIFF.k() == 8);
        static_assert(QUAT_DIFF.s() == 1);

        /// @test Verify that quaternion multiplied with a scalar returns a valid quaternion at compile-time.
        constexpr auto QUAT_PROD_SCALAR = QUAT_A * 2;
        static_assert(QUAT_PROD_SCALAR.i() == -2);
        static_assert(QUAT_PROD_SCALAR.j() == 24);
        static_assert(QUAT_PROD_SCALAR.k() == 6);
        static_assert(QUAT_PROD_SCALAR.s() == 8);

        /// @test Verify that scalar multiplied with a quaternion returns a valid quaternion at compile-time.
        constexpr auto QUAT_SCALAR_PROD_QUAT = 2 * QUAT_A;
        static_assert(QUAT_SCALAR_PROD_QUAT.i() == -2);
        static_assert(QUAT_SCALAR_PROD_QUAT.j() == 24);
        static_assert(QUAT_SCALAR_PROD_QUAT.k() == 6);
        static_assert(QUAT_SCALAR_PROD_QUAT.s() == 8);


        /// @test Verify that quaternion negation returns a new Quaternion with negated components at compile-time.
        constexpr auto NEG_QUAT = -QUAT_A;
        static_assert(NEG_QUAT.i() == 1);
        static_assert(NEG_QUAT.j() == -12);
        static_assert(NEG_QUAT.k() == -3);
        static_assert(NEG_QUAT.s() == -4);


        /// @test Verify that quaternion-quaternion multiplication returns a valid quaternion at compile time.
        constexpr auto QUAT_QUAT_MUL = QUAT_A * QUAT_B;
        static_assert(QUAT_QUAT_MUL.i() == -79);
        static_assert(QUAT_QUAT_MUL.j() == 94);
        static_assert(QUAT_QUAT_MUL.k() == -83);
        static_assert(QUAT_QUAT_MUL.s() == -112);

    } // namespace static_tests


} // namespace



/**************************************
 *           ADDITION TESTS           *
 **************************************/

TYPED_TEST(QuaternionAddition, PlusOperator_ReturnsQuaternionSum)
{
    const flcn::Quaternion result = this->_quatA + this->_quatB;

    EXPECT_QUAT_EQ(this->_expectedSum, result);
}


TYPED_TEST(QuaternionAddition, PlusEqualsOperator_ReturnsSameQuaternionWithSum)
{
    this->_quatA += this->_quatB;

    EXPECT_QUAT_EQ(this->_expectedSum, this->_quatA);
}


TEST(QuaternionAddition, PlusOperator_MixedType_PromotesType)
{
    const flcn::Quaternion quat1(3.0f, 0.0f, -1.0f, 2.0f);
    const flcn::Quaternion quat2(9.0, -5.0, 10.0, 3.0);

    [[maybe_unused]] const flcn::Quaternion result = quat1 + quat2;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}



TEST(QuaternionAddition, PlusEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::Quaternion quat1(3.0f, 0.0f, -1.0f, 2.0f);
    [[maybe_unused]] const flcn::Quaternion quat2(9.0, -5.0, 10.0, 3.0);

    static_cast<void>(quat1 += quat2);

    static_assert(std::is_same_v<decltype(quat1)::value_type, float>);
}


TYPED_TEST(QuaternionSubtraction, MinusOperator_ReturnsQuaternionDifference)
{
    const flcn::Quaternion result = this->_quatA - this->_quatB;

    EXPECT_QUAT_EQ(this->_expectedDifference, result);
}


TYPED_TEST(QuaternionSubtraction, MinusEqualsOperator_ReturnsSameQuaternionWithDifference)
{
    this->_quatA -= this->_quatB;

    EXPECT_QUAT_EQ(this->_expectedDifference, this->_quatA);
}


TEST(QuaternionSubtraction, MinusOperator_MixedType_PromotesType)
{
    const flcn::Quaternion quat1(3.0f, 0.0f, -1.0f, 2.0f);
    const flcn::Quaternion quat2(9.0, -5.0, 10.0, 3.0);

    [[maybe_unused]] const flcn::Quaternion result = quat1 - quat2;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


TEST(QuaternionSubtraction, MinusEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::Quaternion quat1(3.0f, 0.0f, -1.0f, 2.0f);
    [[maybe_unused]] const flcn::Quaternion quat2(9.0, -5.0, 10.0, 3.0);

    static_cast<void>(quat1 -= quat2);

    static_assert(std::is_same_v<decltype(quat1)::value_type, float>);
}


TEST(QuaternionScalarMultiplication, QuaternionTimesZeroReturnsZeroQuaternion)
{
    const flcn::Quaternion quat(3.0f, 1.0f, 6.0f, 2.0f);

    const flcn::Quaternion result = quat * 0;

    EXPECT_QUAT_CONTAINS(result, 0.0f, 0.0f, 0.0f, 0.0f);
}


TEST(QuaternionScalarMultiplication, QuaternionTimesOneReturnsOriginalQuaternion)
{
    const flcn::Quaternion quat(3.0f, 1.0f, 6.0f, 2.0f);

    const flcn::Quaternion result = quat * 1;

    EXPECT_QUAT_CONTAINS(result, 3.0f, 1.0f, 6.0f, 2.0f);
}


TYPED_TEST(QuaternionScalarMultiplication, QuaternionTimesScalarReturnsScaledQuaternion)
{
    const flcn::Quaternion result = this->_quat * this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_QUAT_EQ(this->_expectedFPQuat, result);
    }
    else
    {
        EXPECT_QUAT_EQ(this->_expectedIntQuat, result);
    }
}


TYPED_TEST(QuaternionScalarMultiplication, ScalarTimesAQuaternionReturnsScaledQuaternion)
{
    const flcn::Quaternion result = this->_scalar * this->_quat;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_QUAT_EQ(this->_expectedFPQuat, result);
    }
    else
    {
        EXPECT_QUAT_EQ(this->_expectedIntQuat, result);
    }
}


TYPED_TEST(QuaternionScalarMultiplication, QuaternionTimesEqualScalarIsTheSameQuaternionScaled)
{
    this->_quat *= this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_QUAT_EQ(this->_expectedFPQuat, this->_quat);
    }
    else
    {
        EXPECT_QUAT_EQ(this->_expectedIntQuat, this->_quat);
    }
}



TEST(QuaternionScalarMultiplication, MixedTypeScalarMultiplication_PromotesType)
{
    const double scalar = 2.123456789123456;

    flcn::Quaternion quat(3.0f, 0.0f, -1.0f, 2.0f);
    [[maybe_unused]] const auto result = quat * scalar;

    static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
}


TEST(QuaternionScalarMultiplication, MixedTypeScalarMultiplicationAssignment_DoesNotPromoteType)
{
    flcn::Quaternion quat(3.0f, 0.0f, -1.0f, 2.0f);
    const double scalar = 5.0;
    quat *= scalar;

    static_assert(std::is_same_v<decltype(quat)::value_type, float>);
}


TEST(QuaternionScalarMultiplication, MixedTypeScalarMultiplicationAssignment_EnsuresMinimalPrecisionLoss)
{
    flcn::Quaternion quat(3, 0, -1, 8);
    const double scalar = 2.5;
    const flcn::Quaternion expected(7, 0, -2, 20);

    quat *= scalar;

    EXPECT_QUAT_EQ(expected, quat);
}


TYPED_TEST(QuaternionQuaternionMultiplication, TimesOperator_ReturnsAValidQuaternion)
{
    const flcn::Quaternion result = this->_quatA * this->_quatB;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_QUAT_EQ(this->_expectedFPQuat, result);
    }
    else
    {
        EXPECT_QUAT_EQ(this->_expectedIntQuat, result);
    }
}


TYPED_TEST(QuaternionQuaternionMultiplication, TimesEqualsOperator_ReturnsTheSameQuaternionWithUpdatedComponents)
{
    this->_quatA *= this->_quatB;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_QUAT_EQ(this->_expectedFPQuat, this->_quatA);
    }
    else
    {
        EXPECT_QUAT_EQ(this->_expectedIntQuat, this->_quatA);
    }
}



TEST(QuaternionQuaternionMultiplication, TimesOperator_MixedType_PromotesType)
{
    flcn::Quaternion quatA(3.0f, 0.0f, -1.0f, 2.0f);
    const flcn::Quaternion quatB(1.0, 2.0, 3.0, 4.0);

    [[maybe_unused]] const auto result = quatA * quatB;

    static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
}


TEST(QuaternionQuaternionMultiplication, TimesEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::Quaternion quatA(3.0f, 0.0f, -1.0f, 2.0f);
    const flcn::Quaternion quatB(1.0, 2.0, 3.0, 4.0);
    quatA *= quatB;

    static_assert(std::is_same_v<decltype(quatA)::value_type, float>);
}


TYPED_TEST(QuaternionScalarDivision, ByOneReturnsOriginalQuaternion)
{
    const flcn::Quaternion result = this->_quat / TypeParam(1);

    EXPECT_QUAT_EQ(result, this->_quat);
}


TYPED_TEST(QuaternionScalarDivision, DivideOperator_ReturnsAValidQuaternion)
{
    const flcn::Quaternion result = this->_quat / this->_scalar;

    EXPECT_QUAT_EQ(this->_expectedScaledVec, result);
}


TYPED_TEST(QuaternionScalarDivision, DivideEqualsOperator_ReturnsSameQuaternionInverseScaled)
{
    this->_quat /= this->_scalar;

    EXPECT_QUAT_EQ(this->_expectedScaledVec, this->_quat);
}


TEST(QuaternionScalarDivision, DivideOperator_MixedType_PromotesType)
{
    const flcn::Quaternion quat(15.0, 0.0, -5.0, 10.0);
    const double scalar = 5.0;

    [[maybe_unused]] const auto result = quat / scalar;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


TEST(QuaternionScalarDivision, DivideEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::Quaternion quat(15.0f, 0.0f, -5.0f, 10.0f);
    const double scalar = 5.0;

    quat /= scalar;

    static_assert(std::is_same_v<decltype(quat)::value_type, float>);
}


TEST(QuaternionScalarDivision, DivideEqualsOperator_MixedType_ReturnsResultWithMinimalPrecisionLoss)
{
    flcn::Quaternion quat(10, 25, -30, 2);
    const double scalar = 2.5;
    const flcn::Quaternion expected(4, 10, -12, 0);

    quat /= scalar;

    EXPECT_QUAT_EQ(expected, quat);
}


TYPED_TEST(QuaternionNegation, InvertsTheSignOfEachComponents)
{
    const flcn::Quaternion inverted = -this->_quat;
    EXPECT_QUAT_EQ(this->_expectedQuat, inverted);
}


TEST(QuaternionNegation, InvertsSignOfInfinity)
{
    const flcn::Quaternion infQuat = {
        flcn::constants::INFINITY_F,
        -flcn::constants::INFINITY_F,
        flcn::constants::INFINITY_F,
        -flcn::constants::INFINITY_F,
    };
    const flcn::Quaternion expected = {
        -flcn::constants::INFINITY_F,
        flcn::constants::INFINITY_F,
        -flcn::constants::INFINITY_F,
        flcn::constants::INFINITY_F,
    };

    const flcn::Quaternion<float> inverted = -infQuat;

    EXPECT_QUAT_EQ(expected, inverted);
}


TEST(QuaternionNegation, NoOpOnNaNQuaternions)
{
    const flcn::Quaternion nanQuat = {
        flcn::constants::NaN,
        flcn::constants::NaN,
        flcn::constants::NaN,
        flcn::constants::NaN,
    };

    const flcn::Quaternion<float> inverted = -nanQuat;

    EXPECT_TRUE(std::isnan(inverted.x()));
    EXPECT_TRUE(std::isnan(inverted.y()));
    EXPECT_TRUE(std::isnan(inverted.z()));
    EXPECT_TRUE(std::isnan(inverted.w()));
}

/** @} */
