/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 01, 2026
 *
 * @brief Verify @ref flcn::Quaternion initialization logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "include/QuaternionTestSetup.h"

/**
 * @addtogroup T_FALCON_Quaternion_Init
 * @{
 */

namespace
{


    /**************************************
     *                                    *
     *            TEST SETUP              *
     *                                    *
     **************************************/

    /**
     * @brief Test Fixture for @ref flcn::Quaternion initialization.
     *
     * @tparam T The scalar type (uint8_t, float, uint32_t...) used for the values.
     */
    template <typename T>
    class QuaternionInitialization: public testing::Test
    {
    protected:
        flcn::Vec3<T> _complexPart;
        T _realPart;
        flcn::Quaternion<T> _expectedQuaternion;

        void SetUp() override
        {
            _complexPart        = { T(1), T(2), T(3) };
            _realPart           = T(4);
            _expectedQuaternion = { T(1), T(2), T(3), T(4) };
        }
    };
    TYPED_TEST_SUITE(QuaternionInitialization, SupportedTypes);



    /**************************************
     *                                    *
     *            STATIC TESTS            *
     *                                    *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Vec3 VECTOR(1, 2, 3);
        constexpr auto SCALAR{ 5 };

        /// @test Verify that quaternions can be initialized with braced initializer has zero out components
        ///       at compile time.
        constexpr flcn::Quaternion<int> ZERO_QUATERNION{};
        static_assert(ZERO_QUATERNION.x() == 0);
        static_assert(ZERO_QUATERNION.y() == 0);
        static_assert(ZERO_QUATERNION.z() == 0);
        static_assert(ZERO_QUATERNION.w() == 0);


        /// @test Verify that quaternions can be initialized with individuals values at compile time.
        constexpr flcn::Quaternion QUATERNION_VALUE_INIT(1, 2, 3, 4);
        static_assert(QUATERNION_VALUE_INIT.x() == 1);
        static_assert(QUATERNION_VALUE_INIT.y() == 2);
        static_assert(QUATERNION_VALUE_INIT.z() == 3);
        static_assert(QUATERNION_VALUE_INIT.w() == 4);

        /// @test Verify that quaternions can be initialized with <vector, scalar> at compile time.
        constexpr flcn::Quaternion QUATERNION_VEC_SCALAR(VECTOR, SCALAR);
        static_assert(QUATERNION_VEC_SCALAR.x() == 1);
        static_assert(QUATERNION_VEC_SCALAR.y() == 2);
        static_assert(QUATERNION_VEC_SCALAR.z() == 3);
        static_assert(QUATERNION_VEC_SCALAR.w() == 5);

        /// @test Verify that quaternions can be initialized with <scalar, vector> at compile time.
        constexpr flcn::Quaternion QUATERNION_SCALAR_VECTOR(SCALAR, VECTOR);
        static_assert(QUATERNION_SCALAR_VECTOR.x() == 1);
        static_assert(QUATERNION_SCALAR_VECTOR.y() == 2);
        static_assert(QUATERNION_SCALAR_VECTOR.z() == 3);
        static_assert(QUATERNION_SCALAR_VECTOR.w() == 5);


    } // namespace static_tests

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

TYPED_TEST(QuaternionInitialization, BracedInitializer_InitializesAllComponentsToZero)
{
    const flcn::Quaternion<TypeParam> quat{};
    const auto zero = TypeParam(0);
    EXPECT_QUAT_CONTAINS(quat, zero, zero, zero, zero);
}


TYPED_TEST(QuaternionInitialization, ParameterizedCtor_InitializesQuaternionWithIndividalComponents)
{
    const auto a = static_cast<TypeParam>(3);
    const auto b = static_cast<TypeParam>(1);
    const auto c = static_cast<TypeParam>(6);
    const auto d = static_cast<TypeParam>(4);

    const flcn::Quaternion<TypeParam> quat(a, b, c, d);

    EXPECT_QUAT_CONTAINS(quat, a, b, c, d);
}


/**
 * @test Verify that Quaternion(vector, scalar) initializes a quaternion of <vector, scalar> component order.
 */
TYPED_TEST(QuaternionInitialization, VectorScalarParameterCtor_InitializesQuaternionWithValidComponentOrder)
{ EXPECT_QUAT_EQ(this->_expectedQuaternion, flcn::Quaternion<TypeParam>(this->_complexPart, this->_realPart)); }


/**
 * @test Verify that Quaternion(scalar, vector) initializes a quaternion of <vector, scalar> component order.
 */
TYPED_TEST(QuaternionInitialization, ScalarVectorParameterCtor_InitializesQuaternionWithValidComponentOrder)
{ EXPECT_QUAT_EQ(this->_expectedQuaternion, flcn::Quaternion<TypeParam>(this->_complexPart, this->_realPart)); }



/** @} */
