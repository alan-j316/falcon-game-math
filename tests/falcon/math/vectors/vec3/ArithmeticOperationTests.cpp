/**
 * @file ArithmeticOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify @ref flcn::Vec3 arithmetic operator(+, -, *, /) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"


/**
 * @addtogroup T_Falcon_Vec3_Arithmetic
 * @{
 */

namespace
{

    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec3 additions.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec3AdditionTests: public testing::Test
    {
    protected:
        flcn::Vec3<T> _vecA;
        flcn::Vec3<T> _vecB;
        flcn::Vec3<T> _expectedSum;

        void SetUp() override
        {
            _vecA        = { T(3), T(1), T(6) };
            _vecB        = { T(-8), T(5), T(-2) };
            _expectedSum = { T(-5), T(6), T(4) };
        }
    };
    TYPED_TEST_SUITE(Vec3AdditionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec3 subtraction.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec3SubtractionTests: public testing::Test
    {
    protected:
        flcn::Vec3<T> _vecA;
        flcn::Vec3<T> _vecB;
        flcn::Vec3<T> _expectedDifference;

        void SetUp() override
        {
            _vecA               = { T(95), T(11), T(-6) };
            _vecB               = { T(-8), T(5), T(-2) };
            _expectedDifference = { T(103), T(6), T(-4) };
        }
    };
    TYPED_TEST_SUITE(Vec3SubtractionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec3 scalar multiplication.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec3ScalarMultiplicationTests: public testing::Test
    {
    protected:
        flcn::Vec3<T> _vec;
        T _scalar;
        flcn::Vec3<T> _expectedFloatingVec;
        flcn::Vec3<T> _expectedIntegralVec;

        void SetUp() override
        {
            _vec                 = { T(7), T(13), T(29) };
            _scalar              = T(2.123456789123456);
            _expectedFloatingVec = { T(14.864197523864192), T(27.604938258604928), T(61.580246884580224) };
            _expectedIntegralVec = { T(14), T(26), T(58) };
        }
    };
    TYPED_TEST_SUITE(Vec3ScalarMultiplicationTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec3 scalar division.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec3ScalarDivisionTests: public testing::Test
    {
    protected:
        flcn::Vec3<T> _vec;
        T _scalar;
        flcn::Vec3<T> _expectedScaledVec;

        void SetUp() override
        {
            _vec               = { T(17), T(31), T(59) };
            _scalar            = T(13);
            _expectedScaledVec = { T(1.30769230769230769231), T(2.38461538461538461538), T(4.53846153846153846154) };
        }
    };
    TYPED_TEST_SUITE(Vec3ScalarDivisionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec3 negation.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec3NegationTests: public testing::Test
    {
    protected:
        flcn::Vec3<T> _vec;
        flcn::Vec3<T> _expectedInvertedVec;

        void SetUp() override
        {
            _vec                 = { T(-8), T(0), T(-2) };
            _expectedInvertedVec = { T(8), T(0), T(2) };
        }
    };
    TYPED_TEST_SUITE(Vec3NegationTests, SupportedSignedArithmeticTypes);


    // /// @brief Test fixture for @ref flcn::Vec3 division with NaN vectors.
    // class Vec3DivisionNaNTests: public testing::TestWithParam<flcn::Vec3<float>>
    // {};
    // INSTANTIATE_TEST_SUITE_P(Vec3InvalidDivision, Vec3DivisionNaNTests,
    //                          ::testing::Values(flcn::Vec3<float>(flcn::constants::NaN, 3.0f, 3.0f),
    //                                            flcn::Vec3<float>(3.0f, flcn::constants::NaN, 3.0f),
    //                                            flcn::Vec3<float>(3.0f, 3.0f, flcn::constants::NaN),
    //                                            flcn::Vec3<float>(flcn::constants::NaN, flcn::constants::NaN,
    //                                                             flcn::constants::NaN)));
} // namespace



/**************************************
 *           ADDITION TESTS           *
 **************************************/

/**
 * @test Verify that the binary addition operator perform a component-wise addition and
 *       returns a new vector instance.
 */
TYPED_TEST(Vec3AdditionTests, PlusOperator_ReturnsVectorSum)
{
    const flcn::Vec3 result = this->_vecA + this->_vecB;
    EXPECT_VEC_EQ(this->_expectedSum, result);
}


/**
 * @test Verify that the compound addition assignment operator perform a component-wise addition and
 *       mutates the vector in-place.
 */
TYPED_TEST(Vec3AdditionTests, PlusEqualsOperator_ReturnsSameVectorWithSum)
{
    this->_vecA += this->_vecB;
    EXPECT_VEC_EQ(this->_expectedSum, this->_vecA);
}


/**************************************
 *          SUBTRACTION TESTS         *
 **************************************/

/**
 * @test Verify that the binary subtraction operator perform a component-wise subtraction and
 *       returns a new vector instance.
 */
TYPED_TEST(Vec3SubtractionTests, MinusOperator_ReturnsMatrixDifference)
{
    const flcn::Vec3 result = this->_vecA - this->_vecB;

    EXPECT_VEC_EQ(this->_expectedDifference, result);
}


/**
 * @test Verify that the compound subtraction assignment operator perform a component-wise subtraction
 *       and mutates the vector in-place.
 */
TYPED_TEST(Vec3SubtractionTests, MinusEqualsOperator_ReturnsSameVectorWithDifference)
{
    this->_vecA -= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedDifference, this->_vecA);
}


/**************************************
 *     SCALAR MULTIPLICATION TESTS    *
 **************************************/

/** @test Verify that scalar multiplication by zero returns a zero vector. */
TEST(Vec3ScalarMultiplication, MultiplicationByZeroReturnsZeroVector)
{
    const flcn::Vec3 vec(3.0f, 1.0f, 6.0f);

    const flcn::Vec3 result = vec * 0.0f;

    EXPECT_VEC_ZERO(result);
}


/** @test Verify that scalar multiplication by one returns original vector. */
TEST(Vec3ScalarMultiplication, MultiplicationByOneReturnsOriginalVector)
{
    const flcn::Vec3 vec(3.0f, 1.0f, 6.0f);

    const flcn::Vec3 result = vec * 1;

    EXPECT_VEC_EQ(vec, result);
}


/**
 * @test Verify that the binary multiplication operator (vector * scalar) perform a component-wise (Hadamard)
 * product and returns a new vector instance.
 */
TYPED_TEST(Vec3ScalarMultiplicationTests, VectorTimesScalarReturnsScaledVector)
{
    const flcn::Vec3 result = this->_vec * this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFloatingVec, result);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntegralVec, result);
    }
}


/**
 * @test Verify that the binary multiplication operator (scalar * vector) perform a component-wise (Hadamard)
 * product and returns a new vector instance.
 */
TYPED_TEST(Vec3ScalarMultiplicationTests, ScalarTimesAVectorReturnsScaledVector)
{
    const flcn::Vec3 result = this->_scalar * this->_vec;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFloatingVec, result);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntegralVec, result);
    }
}


/**
 * @test Verify that the compound multiplication assignment operator performs a component-wise (Hadamard) product
 *       and mutates the vector in-place.
 */
TYPED_TEST(Vec3ScalarMultiplicationTests, VectorTimesEqualScalarReturnsTheSameVectorWithScaledComponents)
{
    this->_vec *= this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFloatingVec, this->_vec);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntegralVec, this->_vec);
    }
}

//
//
// /**************************************
//  *        SCALAR DIVISION TESTS       *
//  **************************************/
//
// #ifndef ENABLE_DEBUG_TESTS
// /**
//  * @test Verify that dividing a float vector by zero returns an
//  *       infinity vector of float type.
//  */
// TEST(Vec3ScalarDivision, FloatVectorDivisionByZeroReturnsInfinityVector)
// {
//     const flcn::Vec3 vec(1.0f, 2.0f, 3.0f);
//     EXPECT_VEC_INF(vec / 0);
// }
//
//
// /**
//  * @test Verify that dividing a double vector by zero returns an
//  *       infinity vector of double type.
//  */
// TEST(Vec3ScalarDivision, DoubleVectorDivisionByZeroReturnsInfinityVector)
// {
//     const flcn::Vec3 vec(1.0, 2.0, 3.0);
//     EXPECT_VEC_INF(vec / 0);
// }
// #endif
//
// /** @test Verify that dividing a vector by one returns the original vector. */
// TYPED_TEST(Vec3ScalarDivisionTests, DivisionByOneReturnsOriginalVector)
// {
//     const flcn::Vec3 result = this->_vec / 1;
//
//     EXPECT_VEC_EQ(result, this->_vec);
// }
//
//
// /**
//  * @test Verify that the binary division operator (vector / scalar) perform a component-wise divide and
//  *       returns a vector instance.
//  */
// TYPED_TEST(Vec3ScalarDivisionTests, ScalarDivision_ReturnsVectorWithDividedComponents)
// {
//     const flcn::Vec3 result = this->_vec / this->_scalar;
//
//     EXPECT_VEC_EQ(this->_expectedScaledVec, result);
// }
//
//
// /**
//  * @test Verify that the compound division assignment operator perform a component-wise divide and
//  *       mutates the vector in-place.
//  */
// TYPED_TEST(Vec3ScalarDivisionTests, DivideEqualsOperator_ReturnsSameVectorWithDividedComponents)
// {
//     this->_vec /= this->_scalar;
//
//     EXPECT_VEC_EQ(this->_expectedScaledVec, this->_vec);
// }
//
//
//
//
// /**************************************
//  *        SAFE DIVISION TESTS         *
//  **************************************/
//
// /**
//  * @test Verify that dividing a vector using @ref flcn::Vec3::safeDiv perform a component-wise divide and
//  *       returns a new vector instance.
//  */
// TYPED_TEST(Vec3ScalarDivisionTests, SafeDiv_ReturnsVectorWithDividedComponents)
// {
//     const auto result = this->_vec.safeDiv(this->_scalar);
//
//     EXPECT_VEC_EQ(this->_expectedScaledVec, result);
// }
//
//
// /**
//  * @test Verify that dividing a vector by integral zero using @ref flcn::Vec3::safeDiv
//  *       perform a component-wise divide and returns a new vector instance.
//  */
// TYPED_TEST(Vec3ScalarDivisionTests, SafeDiv_ByIntegralZero_ReturnsZeroVector)
// {
//     const auto result = this->_vec.safeDiv(0);
//     EXPECT_VEC_ZERO(result);
// }
//
//
// /**
//  * @test Verify that dividing a vector by floating point zero using @ref flcn::Vec3::safeDiv
//  *       perform a component-wise divide and returns a new vector instance.
//  */
// TYPED_TEST(Vec3ScalarDivisionTests, SafeDiv_ByFloatZero_ReturnsZeroVector)
// {
//     const auto result = this->_vec.safeDiv(0.0f);
//     EXPECT_VEC_ZERO(result);
// }
//
//
// /**
//  * @test Verify that dividing a vector using static variant of @ref flcn::Vec3::safeDiv
//  *       perform a component-wise divide and returns a new vector instance.
//  */
// TYPED_TEST(Vec3ScalarDivisionTests, StaticWrapper_SafeDiv_ReturnsVectorWithDividedComponents)
// {
//     const auto result = flcn::Vec3<TypeParam>::safeDiv(this->_vec, this->_scalar);
//     EXPECT_VEC_EQ(this->_expectedScaledVec, result);
// }
//
//
// /**
//  * @test Verify that dividing a vector by integral zero using static variant of @ref flcn::Vec3::safeDiv
//  *       perform a component-wise divide and returns a new vector instance.
//  */
// TEST(Vec3ScalarDivision, StaticWrapper_SafeDiv_ByIntergralZero_ReturnsZeroVector)
// {
//     const flcn::Vec3 vec(1, 2, 3);
//     EXPECT_VEC_ZERO(flcn::Vec3<int>::safeDiv(vec, 0));
// }
//
//
// /**
//  * @test Verify that dividing a vector by floating point zero using static variant @ref flcn::Vec3::safeDiv
//  *       perform a component-wise divide and returns a new vector instance.
//  */
// TYPED_TEST(Vec3ScalarDivisionTests, StaticWrapper_SafeDiv_ByFloatZero_ReturnsZeroVector)
// {
//     const auto result = flcn::Vec3<TypeParam>::safeDiv(this->_vec, 0.0f);
//     EXPECT_VEC_ZERO(result);
// }
//
//
// /**
//  * @test Verify that dividing a vector by NaN using @ref flcn::Vec3::safeDiv
//  *       returns a zero vector.
//  */
// TYPED_TEST(Vec3ScalarDivisionTests, SafeDiv_ByNaN_ReturnsZeroVector)
// {
//     const auto result = this->_vec.safeDiv(flcn::constants::NaN);
//
//     EXPECT_VEC_ZERO(result);
// }
//
//
// /**
//  * @test Verify that dividing a vector by NaN using static variant of @ref flcn::Vec3::safeDiv
//  *       returns a zero vector.
//  */
// TYPED_TEST(Vec3ScalarDivisionTests, StaticWrapper_SafeDiv_ByNaN_ReturnsZeroVector)
// {
//     const auto result = flcn::Vec3<TypeParam>::safeDiv(this->_vec, flcn::constants::INFINITY_F);
//
//     EXPECT_VEC_ZERO(result);
// }
//
//
// /**************************************
//  *         TRY DIVISION TESTS         *
//  **************************************/
//
// /**
//  * @test Verify that dividing a vector using @ref flcn::Vec3::tryDiv perform a component-wise divide and
//  *       returns a new vector instance and sets the flag to @ref flcn::OperationStatus::SUCCESS.
//  */
// TYPED_TEST(Vec3ScalarDivisionTests, TryDivide_ReturnsVectorWithDividedComponentsAndSetsCorrectFlag)
// {
//     flcn::OperationStatus flag;
//     const auto result = this->_vec.tryDiv(this->_scalar, flag);
//
//     EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
//     EXPECT_VEC_EQ(this->_expectedScaledVec, result);
// }
//
//
// /**
//  * @test Verify that dividing a vector by integral zero using @ref flcn::Vec3::tryDiv returns zero vector and
//  *       sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
//  */
// TYPED_TEST(Vec3ScalarDivisionTests, TryDivideByIntegralZero_ReturnsZeroVectorAndSetsCorrectFlag)
// {
//     flcn::OperationStatus flag;
//     const auto result = this->_vec.tryDiv(0, flag);
//
//     EXPECT_VEC_ZERO(result);
//     EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
// }
//
//
// /**
//  * @test Verify that dividing a vector by floating point zero using @ref flcn::Vec3::tryDiv returns zero vector and
//  *       sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
//  */
// TYPED_TEST(Vec3ScalarDivisionTests, TryDivideByFloatZero_ReturnsZeroVectorAndSetsCorrectFlag)
// {
//     flcn::OperationStatus flag;
//     const auto result = this->_vec.tryDiv(0.0, flag);
//
//     EXPECT_VEC_ZERO(result);
//     EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
// }
//
//
// /**
//  * @test Verify that dividing a NaN vector by zero using @ref flcn::Vec3::tryDiv
//  *       @ref flcn::OperationStatus::NANOPERAND takes precedence over @ref flcn::OperationStatus::NANOPERAND.
//  */
// TEST(Vec3ScalarDivision, TryDivideNaNVectorByZero_NaNOperandStatusTakesPrecedence)
// {
//     flcn::OperationStatus flag;
//     [[maybe_unused]] const auto result = flcn::Vec3<double>::qnan().tryDiv(0, flag);
//     EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
// }
//
//
// /**
//  * @test Verify that dividing a vector by NaN using @ref flcn::Vec3::tryDiv returns a zero vector and
//  *       sets the flag to @ref flcn::OperationStatus::NANOPERAND.
//  */
// TYPED_TEST(Vec3ScalarDivisionTests, TryDivideByNaN_ReturnsZeroVectorAndSetsCorrectFlag)
// {
//     flcn::OperationStatus flag;
//     const auto result = this->_vec.tryDiv(flcn::constants::NaN, flag);
//
//     EXPECT_VEC_ZERO(result);
//     EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
// }
//
//
// /**
//  * @test Verify that dividing a vector using static variant of @ref flcn::Vec3::tryDiv
//  *       perform a component-wise divide and returns a new vector instance and
//  *       sets the flag to @ref flcn::OperationStatus::SUCCESS.
//  */
// TYPED_TEST(Vec3ScalarDivisionTests, StaticWrapper_TryDivide_ReturnsVectorWithDividedComponentsAndSetsCorrectFlag)
// {
//     flcn::OperationStatus flag;
//     const auto result = flcn::Vec3<TypeParam>::tryDiv(this->_vec, this->_scalar, flag);
//
//     EXPECT_VEC_EQ(this->_expectedScaledVec, result);
//     EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
// }
//
//
// /**
//  * @test Verify that dividing a vector by integral zero using static variant of @ref flcn::Vec3::tryDiv
//  *       returns zero vector and sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
//  */
// TYPED_TEST(Vec3ScalarDivisionTests, StaticWrapper_TryDivideByIntegralZero_ReturnsZeroVectorAndSetsCorrectFlag)
// {
//     flcn::OperationStatus flag;
//     const auto result = flcn::Vec3<TypeParam>::tryDiv(this->_vec, 0, flag);
//
//     EXPECT_VEC_ZERO(result);
//     EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
// }
//
//
// /**
//  * @test Verify that dividing a vector by floating point zero using static variant of @ref flcn::Vec3::tryDiv
//  *       returns zero vector and sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
//  */
// TYPED_TEST(Vec3ScalarDivisionTests, StaticWrapper_TryDivideByFloatZero_ReturnsZeroVectorAndSetsCorrectFlag)
// {
//     flcn::OperationStatus flag;
//     const auto result = flcn::Vec3<TypeParam>::tryDiv(this->_vec, 0.0, flag);
//
//     EXPECT_VEC_ZERO(result);
//     EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
// }
//
//
// /**
//  * @test Verify that dividing a vector by floating point zero using static variant of @ref flcn::Vec3::tryDiv
//  *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
//  */
// TEST(Vec3ScalarDivision, StaticWrapper_TryDivideNaNVector_ReturnsZeroVectorAndSetsCorrectFlag)
// {
//     flcn::OperationStatus flag;
//     const auto result = flcn::Vec3<double>::tryDiv(flcn::Vec3<double>::qnan(), 3, flag);
//
//     EXPECT_VEC_ZERO(result);
//     EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
// }
//
//
// /**
//  * @test Verify that dividing a vector by NaN using static variant of @ref flcn::Vec3::tryDiv returns zero vector
//  * and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
//  */
// TYPED_TEST(Vec3ScalarDivisionTests, StaticWrapper_TryDivideByNaN_ReturnsZeroVectorAndSetsCorrectFlag)
// {
//     flcn::OperationStatus flag;
//     const auto result = flcn::Vec3<TypeParam>::tryDiv(this->_vec, flcn::constants::NaN, flag);
//
//     EXPECT_VEC_ZERO(result);
//     EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
// }
//
//
// /**************************************
//  *                                    *
//  *         NaN DIVISION TESTS         *
//  *                                    *
//  **************************************/
//
// /**
//  * @test Verify that dividing a nan vector by a scalar using @ref flcn::Vec3::safeDiv
//  *       returns vector with NaN-components as zero.
//  */
// TEST_P(Vec3DivisionNaNTests, SafeDiv_ReturnsVectorWithNaNComponentsAsZero)
// {
//     const auto& vec = GetParam();
//     EXPECT_VEC_ZERO(vec.safeDiv(3));
// }
//
// /**
//  * @test Verify that dividing a nan vector by a scalar using static variant of @ref flcn::Vec3::safeDiv
//  *       returns zero vector.
//  */
// TEST_P(Vec3DivisionNaNTests, StaticWrapper_SafeDiv_ReturnsVectorWithNaNComponentsAsZero)
// {
//     const auto& vec = GetParam();
//     EXPECT_VEC_ZERO(flcn::Vec3<float>::safeDiv(vec, 3));
// }
//
//
// /**
//  * @test Verify that dividing a nan vector by a scalar using @ref flcn::Vec3::tryDiv
//  *       returns zero vector and sets flag to OperationStatus::NANOPERAND.
//  */
// TEST_P(Vec3DivisionNaNTests, TryDiv_ReturnsVectorWithNaNComponentsAsZero)
// {
//     const auto& vec = GetParam();
//     flcn::OperationStatus flag;
//     EXPECT_VEC_ZERO(vec.tryDiv(3, flag));
//     EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
// }
//
//
// /**
//  * @test Verify that dividing a nan vector by a scalar using static variant of @ref flcn::Vec3::tryDiv
//  *       returns zero vector and sets flag to OperationStatus::NANOPERAND.
//  */
// TEST_P(Vec3DivisionNaNTests, StaticWrapper_TryDiv_ReturnsVectorWithNaNComponentsAsZero)
// {
//     const auto& vec = GetParam();
//     flcn::OperationStatus flag;
//     EXPECT_VEC_ZERO(flcn::Vec3<float>::tryDiv(vec, 3, flag));
//     EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
// }


/**************************************
 *              NEGATION              *
 **************************************/

/**
 * @test Verify that  @ref flcn::Vec3 unary minus operator inverts each component and
 * returns a new vector.
 */
TYPED_TEST(Vec3NegationTests, InvertsTheSignOfEachComponents)
{
    const flcn::Vec3 inverted = -this->_vec;
    EXPECT_VEC_EQ(this->_expectedInvertedVec, inverted);
}


/** @test Verify that @ref flcn::Vec3 unary minus operator inverts each component of an infinity vector. */
TEST(Vec3Negation, InvertsSignOfInfinity)
{
    const flcn::Vec3 infVec = {
        flcn::constants::INFINITY_F,
        -flcn::constants::INFINITY_F,
        flcn::constants::INFINITY_F,
    };
    const flcn::Vec3 expected = {
        -flcn::constants::INFINITY_F,
        flcn::constants::INFINITY_F,
        -flcn::constants::INFINITY_F,
    };

    const flcn::Vec3<float> inverted = -infVec;

    EXPECT_VEC_EQ(expected, inverted);
}


/** @test Verify that @ref flcn::Vec3 unary minus follows IEEE 754 rules for NaN. */
TEST(Vec3Negation, NoOpOnNaNVectors)
{
    const flcn::Vec3 nanVec = {
        flcn::constants::NaN,
        flcn::constants::NaN,
        flcn::constants::NaN,
    };

    const flcn::Vec3<float> inverted = -nanVec;

    EXPECT_TRUE(std::isnan(inverted.x()));
    EXPECT_TRUE(std::isnan(inverted.y()));
    EXPECT_TRUE(std::isnan(inverted.z()));
}

/** @} */
