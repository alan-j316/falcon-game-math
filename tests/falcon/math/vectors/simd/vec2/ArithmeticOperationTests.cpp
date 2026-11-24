/**
 * @file ArithmeticOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref flcn::simd::Vec2 arithmetic operator(+, -, *, /) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"



/**
 * @addtogroup T_Falcon_Vec2_Arithmetic
 * @{
 */

namespace
{

    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec2 additions.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class SimdVec2AdditionTests: public testing::Test
    {
    protected:
        flcn::simd::Vec2<T> _vecA;
        flcn::simd::Vec2<T> _vecB;
        flcn::simd::Vec2<T> _expectedSum;

        void SetUp() override
        {
            _vecA        = { T(3), T(1) };
            _vecB        = { T(-8), T(5) };
            _expectedSum = { T(-5), T(6) };
        }
    };
    TYPED_TEST_SUITE(SimdVec2AdditionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec2 subtraction.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class SimdVec2SubtractionTests: public testing::Test
    {
    protected:
        flcn::simd::Vec2<T> _vecA;
        flcn::simd::Vec2<T> _vecB;
        flcn::simd::Vec2<T> _expectedDifference;

        void SetUp() override
        {
            _vecA               = { T(95), T(11) };
            _vecB               = { T(-8), T(5) };
            _expectedDifference = { T(103), T(6) };
        }
    };
    TYPED_TEST_SUITE(SimdVec2SubtractionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec2 scalar multiplication.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class SimdVec2ScalarMultiplicationTests: public testing::Test
    {
    protected:
        flcn::simd::Vec2<T> _vec;
        T _scalar;
        flcn::simd::Vec2<T> _expectedFloatingVec;
        flcn::simd::Vec2<T> _expectedIntegralVec;

        void SetUp() override
        {
            _vec                 = { T(7), T(13) };
            _scalar              = T(2.123456789123456);
            _expectedFloatingVec = { T(14.864197523864192), T(27.604938258604928) };
            _expectedIntegralVec = { T(14), T(26) };
        }
    };
    TYPED_TEST_SUITE(SimdVec2ScalarMultiplicationTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref flcn::simd::Vec2 vector multiplication.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class SimdVec2VectorMultiplicationTests: public testing::Test
    {
    protected:
        flcn::Vec2<T> _vecA, _vecB;
        flcn::Vec2<T> _expectedFloatingVec;
        flcn::Vec2<T> _expectedIntegralVec;

        void SetUp() override
        {
            _vecA                = { T(5.238923), T(2.394328) };
            _vecB                = { T(12.2380123), T(45.38912) };
            _expectedFloatingVec = { T(64.1140041127529), T(108.67644091135999) };
            _expectedIntegralVec = { T(60), T(90) };
        }
    };
    TYPED_TEST_SUITE(SimdVec2VectorMultiplicationTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec2 scalar division.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class SimdVec2ScalarDivisionTests: public testing::Test
    {
    protected:
        flcn::simd::Vec2<T> _vec;
        T _scalar;
        flcn::simd::Vec2<T> _expectedScaledVec;

        void SetUp() override
        {
            _vec               = { T(17), T(31) };
            _scalar            = T(13);
            _expectedScaledVec = { T(1.30769230769230769231), T(2.38461538461538461538) };
        }
    };
    TYPED_TEST_SUITE(SimdVec2ScalarDivisionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref Vec2 negation.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class SimdVec2NegationTests: public testing::Test
    {
    protected:
        flcn::simd::Vec2<T> _vec;
        flcn::simd::Vec2<T> _expectedInvertedVec;

        void SetUp() override
        {
            _vec                 = { T(-8), T(0) };
            _expectedInvertedVec = { T(8), T(0) };
        }
    };
    TYPED_TEST_SUITE(SimdVec2NegationTests, SupportedSignedArithmeticTypes);


    /// @brief Test fixture for @ref flcn::simd::Vec2 division with NaN vectors.
    class SimdVec2DivisionNaNTests: public testing::TestWithParam<flcn::simd::Vec2<float>>
    {};

    INSTANTIATE_TEST_SUITE_P(Vec2InvalidDivision, SimdVec2DivisionNaNTests,
                             ::testing::Values(flcn::simd::Vec2<float>(flcn::constants::NaN, 3.0f),
                                               flcn::simd::Vec2<float>(3.0f, flcn::constants::NaN),
                                               flcn::simd::Vec2<float>(flcn::constants::NaN, flcn::constants::NaN)));
} // namespace



/**************************************
 *           ADDITION TESTS           *
 **************************************/

TYPED_TEST(SimdVec2AdditionTests, PlusOperator_ReturnsVectorSum)
{
    const flcn::simd::Vec2 result = this->_vecA + this->_vecB;

    EXPECT_VEC_EQ(this->_expectedSum, result);
}



TYPED_TEST(SimdVec2AdditionTests, PlusEqualsOperator_ReturnsSameVectorWithSum)
{
    this->_vecA += this->_vecB;

    EXPECT_VEC_EQ(this->_expectedSum, this->_vecA);
}




/**************************************
 *          SUBTRACTION TESTS         *
 **************************************/

TYPED_TEST(SimdVec2SubtractionTests, MinusOperator_ReturnsVectorDifference)
{
    const flcn::simd::Vec2 result = this->_vecA - this->_vecB;

    EXPECT_VEC_EQ(this->_expectedDifference, result);
}


TYPED_TEST(SimdVec2SubtractionTests, MinusEqualsOperator_ReturnsSameVectorWithDifference)
{
    this->_vecA -= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedDifference, this->_vecA);
}




/**************************************
 *     SCALAR MULTIPLICATION TESTS    *
 **************************************/

TEST(SimdVec2ScalarMultiplicationTests, TimesOperator_ByZeroReturnsZeroVector)
{
    const flcn::simd::Vec2 vec(3.0f, 6.0f);

    const flcn::simd::Vec2 result = vec * 0;

    EXPECT_VEC_ZERO(result);
}


TEST(SimdVec2ScalarMultiplicationTests, TimesOperator_ByOneReturnsOriginalVector)
{
    const flcn::simd::Vec2 vec(3.0f, 6.0f);

    const flcn::simd::Vec2 result = vec * 1;

    EXPECT_VEC_EQ(vec, result);
}


TYPED_TEST(SimdVec2ScalarMultiplicationTests, TimesOperator_ByScalarReturnsScaledVector)
{
    const flcn::simd::Vec2 result = this->_vec * this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFloatingVec, result);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntegralVec, result);
    }
}


TYPED_TEST(SimdVec2ScalarMultiplicationTests, TimesOperator_ScalarByVectorReturnsScaledVector)
{
    const flcn::simd::Vec2 result = this->_scalar * this->_vec;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFloatingVec, result);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntegralVec, result);
    }
}



TYPED_TEST(SimdVec2ScalarMultiplicationTests, TimesEqualsOperator_ByScalarReturnsTheSameVectorWithScaledComponents)
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


/**************************************
 *     VECTOR MULTIPLICATION TESTS    *
 **************************************/

TYPED_TEST(SimdVec2VectorMultiplicationTests, TimesOperator_ReturnVectorComponentwiseProduct)
{
    const flcn::Vec2 result = this->_vecA * this->_vecB;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFloatingVec, result);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntegralVec, result);
    }
}


TYPED_TEST(SimdVec2VectorMultiplicationTests, TimesEqualsOperator_PerformComponentwiseProductInPlace)
{
    this->_vecA *= this->_vecB;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFloatingVec, this->_vecA);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntegralVec, this->_vecA);
    }
}


/**************************************
 *           DIVIDE OPERATOR          *
 **************************************/

TYPED_TEST(SimdVec2ScalarDivisionTests, DivideOperator_ByOneReturnsOriginalVector)
{
    const flcn::simd::Vec2 result = this->_vec / 1;

    EXPECT_VEC_EQ(result, this->_vec);
}


TYPED_TEST(SimdVec2ScalarDivisionTests, DivideOperator_ReturnsVectorWithDividedComponents)
{
    const flcn::simd::Vec2 result = this->_vec / this->_scalar;

    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


TYPED_TEST(SimdVec2ScalarDivisionTests, DivideEqualsOperator_ReturnsSameVectorWithDividedComponents)
{
    this->_vec /= this->_scalar;

    EXPECT_VEC_EQ(this->_expectedScaledVec, this->_vec);
}




#ifndef ENABLE_DEBUG_TESTS
/**
 * @test Verify that dividing a float vector by zero returns an
 *        infinity vector of float type.
 */
TEST(SimdVec2ScalarDivisionTests, FloatVectorDivisionByZeroReturnsInfinityVector)
{
    const flcn::simd::Vec2 vec(1.0f, 3.0f);
    EXPECT_VEC_INF(vec / 0);
}


/**
 * @test Verify that dividing a double vector by zero returns an
 *        infinity vector of double type.
 */
TEST(SimdVec2ScalarDivisionTests, DoubleVectorDivisionByZeroReturnsInfinityVector)
{
    const flcn::simd::Vec2 vec(1.0, 3.0);
    EXPECT_VEC_INF(vec / 0);
}
#endif



/**************************************
 *        SAFE DIVISION TESTS         *
 **************************************/

TYPED_TEST(SimdVec2ScalarDivisionTests, SafeDiv_ReturnsVectorWithDividedComponents)
{
    const auto result = this->_vec.safeDiv(this->_scalar);

    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


TYPED_TEST(SimdVec2ScalarDivisionTests, SafeDiv_ByIntegralZero_ReturnsZeroVector)
{
    const auto result = this->_vec.safeDiv(0);
    EXPECT_VEC_ZERO(result);
}


TYPED_TEST(SimdVec2ScalarDivisionTests, SafeDiv_ByFloatZero_ReturnsZeroVector)
{
    const auto result = this->_vec.safeDiv(0.0f);
    EXPECT_VEC_ZERO(result);
}


TYPED_TEST(SimdVec2ScalarDivisionTests, StaticWrapper_SafeDiv_ReturnsVectorWithDividedComponents)
{
    const auto result = flcn::simd::Vec2<TypeParam>::safeDiv(this->_vec, this->_scalar);
    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


TEST(SimdVec2ScalarDivision, StaticWrapper_SafeDiv_ByIntergralZero_ReturnsZeroVector)
{
    const flcn::simd::Vec2 vec(1, 3);
    EXPECT_VEC_ZERO(flcn::simd::Vec2<int>::safeDiv(vec, 0));
}


TYPED_TEST(SimdVec2ScalarDivisionTests, StaticWrapper_SafeDiv_ByFloatZero_ReturnsZeroVector)
{
    const auto result = flcn::simd::Vec2<TypeParam>::safeDiv(this->_vec, 0.0f);
    EXPECT_VEC_ZERO(result);
}


TYPED_TEST(SimdVec2ScalarDivisionTests, SafeDiv_ByNaN_ReturnsZeroVector)
{
    if constexpr (std::is_integral_v<TypeParam>)
    {
        GTEST_SKIP() << "NaN tests only applicable for floating-point types.";
    }
    else
    {
        const auto result = this->_vec.safeDiv(flcn::constants::NaN);
        EXPECT_VEC_ZERO(result);
    }
}



TYPED_TEST(SimdVec2ScalarDivisionTests, StaticWrapper_SafeDiv_ByNaN_ReturnsZeroVector)
{
    if constexpr (std::is_integral_v<TypeParam>)
    {
        GTEST_SKIP() << "NaN tests only applicable for floating-point types.";
    }
    else
    {
        const auto result = flcn::simd::Vec2<TypeParam>::safeDiv(this->_vec, flcn::constants::INFINITY_F);
        EXPECT_VEC_ZERO(result);
    }
}



/**************************************
 *         TRY DIVISION TESTS         *
 **************************************/

/**
 * @test Verify that dividing a vector using @ref flcn::simd::Vec2::tryDiv perform a component-wise divide and
 *       returns a new vector instance and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(SimdVec2ScalarDivisionTests, TryDivide_ReturnsVectorWithDividedComponentsAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto result = this->_vec.tryDiv(this->_scalar, flag);

    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


/**
 * @test Verify that dividing a vector by integral zero using @ref flcn::simd::Vec2::tryDiv returns zero vector and
 *       sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(SimdVec2ScalarDivisionTests, TryDivideByIntegralZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto result = this->_vec.tryDiv(0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a vector by floating point zero using @ref flcn::simd::Vec2::tryDiv returns zero vector
 * and sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(SimdVec2ScalarDivisionTests, TryDivideByFloatZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto result = this->_vec.tryDiv(0.0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a NaN vector by zero using @ref flcn::simd::Vec2::tryDiv
 *       @ref flcn::OperationStatus::NANOPERAND takes precedence over @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(SimdVec2ScalarDivision, TryDivideNaNVectorByZero_NaNOperandStatusTakesPrecedence)
{
    flcn::OperationStatus flag;
    [[maybe_unused]] const auto result = flcn::simd::Vec2<double>::qnan().tryDiv(0, flag);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a vector by NaN using @ref flcn::simd::Vec2::tryDiv returns a zero vector and
 *       sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TYPED_TEST(SimdVec2ScalarDivisionTests, TryDivideByNaN_ReturnsZeroVectorAndSetsCorrectFlag)
{
    if constexpr (std::is_integral_v<TypeParam>)
    {
        GTEST_SKIP() << "NaN tests only applies to floating-point types.";
    }
    else
    {
        flcn::OperationStatus flag;
        const auto result = this->_vec.tryDiv(flcn::constants::NaN, flag);
        EXPECT_VEC_ZERO(result);
        EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
    }
}


/**
 * @test Verify that dividing a vector using static variant of @ref flcn::simd::Vec2::tryDiv
 *       perform a component-wise divide and returns a new vector instance and
 *       sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(SimdVec2ScalarDivisionTests, StaticWrapper_TryDivide_ReturnsVectorWithDividedComponentsAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto result = flcn::simd::Vec2<TypeParam>::tryDiv(this->_vec, this->_scalar, flag);

    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that dividing a vector by integral zero using static variant of @ref flcn::simd::Vec2::tryDiv
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(SimdVec2ScalarDivisionTests, StaticWrapper_TryDivideByIntegralZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto result = flcn::simd::Vec2<TypeParam>::tryDiv(this->_vec, 0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a vector by floating point zero using static variant of @ref flcn::simd::Vec2::tryDiv
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(SimdVec2ScalarDivisionTests, StaticWrapper_TryDivideByFloatZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto result = flcn::simd::Vec2<TypeParam>::tryDiv(this->_vec, 0.0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a vector by floating point zero using static variant of @ref flcn::simd::Vec2::tryDiv
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(SimdVec2ScalarDivision, StaticWrapper_TryDivideNaNVector_ReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto result = flcn::simd::Vec2<double>::tryDiv(flcn::simd::Vec2<double>::qnan(), 3, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a vector by NaN using static variant of @ref flcn::simd::Vec2::tryDiv returns zero vector
 *       and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TYPED_TEST(SimdVec2ScalarDivisionTests, StaticWrapper_TryDivideByNaN_ReturnsZeroVectorAndSetsCorrectFlag)
{
    if constexpr (std::is_integral_v<TypeParam>)
    {
        GTEST_SKIP() << "NaN tests only applies to floating-point types.";
    }
    else
    {
        flcn::OperationStatus flag;
        const auto result = flcn::simd::Vec2<TypeParam>::tryDiv(this->_vec, flcn::constants::NaN, flag);

        EXPECT_VEC_ZERO(result);
        EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
    }
}



/**************************************
 *         NaN DIVISION TESTS         *
 **************************************/

/**
 * @test Verify that dividing a nan vector by a scalar using @ref flcn::simd::Vec2::safeDiv
 *       returns vector with NaN-components as zero.
 */
TEST_P(SimdVec2DivisionNaNTests, SafeDiv_ReturnsVectorWithNaNComponentsAsZero)
{
    const auto& vec = GetParam();
    EXPECT_VEC_ZERO(vec.safeDiv(3));
}

/**
 * @test Verify that dividing a nan vector by a scalar using static variant of @ref flcn::simd::Vec2::safeDiv
 *       returns zero vector.
 */
TEST_P(SimdVec2DivisionNaNTests, StaticWrapper_SafeDiv_ReturnsVectorWithNaNComponentsAsZero)
{
    const auto& vec = GetParam();
    EXPECT_VEC_ZERO(flcn::simd::Vec2<float>::safeDiv(vec, 3));
}


/**
 * @test Verify that dividing a nan vector by a scalar using @ref flcn::simd::Vec2::tryDiv
 *       returns zero vector and sets flag to OperationStatus::NANOPERAND.
 */
TEST_P(SimdVec2DivisionNaNTests, TryDiv_ReturnsVectorWithNaNComponentsAsZero)
{
    const auto& vec = GetParam();
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(vec.tryDiv(3, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a nan vector by a scalar using static variant of @ref flcn::simd::Vec2::tryDiv
 *       returns zero vector and sets flag to OperationStatus::NANOPERAND.
 */
TEST_P(SimdVec2DivisionNaNTests, StaticWrapper_TryDiv_ReturnsVectorWithNaNComponentsAsZero)
{
    const auto& vec = GetParam();
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::simd::Vec2<float>::tryDiv(vec, 3, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}



/**************************************
 *              NEGATION              *
 **************************************/

TYPED_TEST(SimdVec2NegationTests, InvertsTheSignOfEachComponents)
{
    const flcn::simd::Vec2 inverted = -this->_vec;
    EXPECT_VEC_EQ(this->_expectedInvertedVec, inverted);
}


/** @test Verify that @ref flcn::simd::Vec2 unary minus operator inverts each component of an infinity vector. */
TEST(SimdVec2NegationTests, InvertsSignOfInfinity)
{
    const flcn::simd::Vec2 infVec = {
        flcn::constants::INFINITY_F,
        -flcn::constants::INFINITY_F,
    };
    const flcn::simd::Vec2 expected = {
        -flcn::constants::INFINITY_F,
        flcn::constants::INFINITY_F,
    };

    const flcn::simd::Vec2<float> inverted = -infVec;

    EXPECT_VEC_EQ(expected, inverted);
}


/** @test Verify that @ref flcn::simd::Vec2 unary minus follows IEEE 754 rules for NaN. */
TEST(SimdVec2NegationTests, NoOpOnNaNVectors)
{
    const flcn::simd::Vec2 nanVec = {
        flcn::constants::NaN,
        flcn::constants::NaN,
    };

    const flcn::simd::Vec2<float> inverted = -nanVec;

    EXPECT_TRUE(std::isnan(inverted.x()));
    EXPECT_TRUE(std::isnan(inverted.y()));
}

/** @} */
