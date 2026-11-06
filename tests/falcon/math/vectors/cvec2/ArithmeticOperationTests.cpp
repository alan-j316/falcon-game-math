/**
 * @file ArithmeticOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref flcn::CVec2 arithmetic operator(+, -, *, /) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CVec2TestSetup.h"



/**
 * @addtogroup T_FALCON_CVec2_Arithmetic
 * @{
 */

namespace
{

    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref CVec2 additions.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class CVec2AdditionTests: public testing::Test
    {
    protected:
        flcn::CVec2<T> _vecA;
        flcn::CVec2<T> _vecB;
        flcn::CVec2<T> _expectedSum;

        void SetUp() override
        {
            _vecA        = { T(3), T(1) };
            _vecB        = { T(-8), T(5) };
            _expectedSum = { T(-5), T(6) };
        }
    };
    TYPED_TEST_SUITE(CVec2AdditionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref CVec2 subtraction.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class CVec2SubtractionTests: public testing::Test
    {
    protected:
        flcn::CVec2<T> _vecA;
        flcn::CVec2<T> _vecB;
        flcn::CVec2<T> _expectedDifference;

        void SetUp() override
        {
            _vecA               = { T(95), T(11) };
            _vecB               = { T(-8), T(5) };
            _expectedDifference = { T(103), T(6) };
        }
    };
    TYPED_TEST_SUITE(CVec2SubtractionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref CVec2 scalar multiplication.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class CVec2ScalarMultiplicationTests: public testing::Test
    {
    protected:
        flcn::CVec2<T> _vec;
        T _scalar;
        flcn::CVec2<T> _expectedFloatingVec;
        flcn::CVec2<T> _expectedIntegralVec;

        void SetUp() override
        {
            _vec                 = { T(7), T(13) };
            _scalar              = T(2.123456789123456);
            _expectedFloatingVec = { T(14.864197523864192), T(27.604938258604928) };
            _expectedIntegralVec = { T(14), T(26) };
        }
    };
    TYPED_TEST_SUITE(CVec2ScalarMultiplicationTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref CVec2 scalar division.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class CVec2ScalarDivisionTests: public testing::Test
    {
    protected:
        flcn::CVec2<T> _vec;
        T _scalar;
        flcn::CVec2<T> _expectedScaledVec;

        void SetUp() override
        {
            _vec               = { T(17), T(31) };
            _scalar            = T(13);
            _expectedScaledVec = { T(1.30769230769230769231), T(2.38461538461538461538) };
        }
    };
    TYPED_TEST_SUITE(CVec2ScalarDivisionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref CVec2 negation.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class CVec2NegationTests: public testing::Test
    {
    protected:
        flcn::CVec2<T> _vec;
        flcn::CVec2<T> _expectedInvertedVec;

        void SetUp() override
        {
            _vec                 = { T(-8), T(0) };
            _expectedInvertedVec = { T(8), T(0) };
        }
    };
    TYPED_TEST_SUITE(CVec2NegationTests, SupportedSignedArithmeticTypes);


    /// @brief Test fixture for @ref flcn::CVec2 division with NaN vectors.
    class CVec2DivisionNaNTests: public testing::TestWithParam<flcn::CVec2<float>>
    {};

    INSTANTIATE_TEST_SUITE_P(CVec2InvalidDivision, CVec2DivisionNaNTests,
                             ::testing::Values(flcn::CVec2<float>(flcn::constants::NaN, 3.0f),
                                               flcn::CVec2<float>(3.0f, flcn::constants::NaN),
                                               flcn::CVec2<float>(flcn::constants::NaN, flcn::constants::NaN)));



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::CVec2 VEC_A(1, 2);
        constexpr flcn::CVec2 VEC_B(3, 5);

        /// @test Verify that vector sum returns a valid vector at compile time.
        constexpr auto VEC_SUM = VEC_A + VEC_B;
        static_assert(VEC_SUM.x() == 4);
        static_assert(VEC_SUM.y() == 7);


        /// @test Verify that vector difference returns a valid vector at compile time.
        constexpr auto VEC_DIFF = VEC_B - VEC_A;
        static_assert(VEC_DIFF.x() == 2);
        static_assert(VEC_DIFF.y() == 3);


        /// @test Verify that vector scalar product(vector * scalar) returns a valid vector at compile time.
        constexpr auto VEC_MUL_SCALAR = VEC_A * 2;
        static_assert(VEC_MUL_SCALAR.x() == 2);
        static_assert(VEC_MUL_SCALAR.y() == 4);

        /// @test Verify that vector scalar product(scalar * vector) returns a valid vector at compile time.
        constexpr auto SCALAR_MUL_VEC = VEC_A * 2;
        static_assert(SCALAR_MUL_VEC.x() == 2);
        static_assert(SCALAR_MUL_VEC.y() == 4);


        /// @test Verify that vector scalar division(operator/) returns a valid vector at compile time.
        constexpr auto DIV_VEC = VEC_B / 2;
        static_assert(DIV_VEC.x() == 1);
        static_assert(DIV_VEC.y() == 2);


        /// @test Verify that vector scalar division(safeDiv) returns a valid vector at compile time.
        constexpr auto SAFE_DIV_VEC = VEC_B.safeDiv(2);
        static_assert(SAFE_DIV_VEC.x() == 1);
        static_assert(SAFE_DIV_VEC.y() == 2);


        /// @test Verify that vector scalar division(safeDiv-static wrapper) returns a valid vector at compile time.
        constexpr auto SAFE_DIV_VEC_STATIC = flcn::CVec2<int>::safeDiv(VEC_B, 2);
        static_assert(SAFE_DIV_VEC_STATIC.x() == 1);
        static_assert(SAFE_DIV_VEC_STATIC.y() == 2);


        /// @test Verify that vector inverse returns a valid vector at compile time.
        constexpr auto INV_VEC = -VEC_A;
        static_assert(INV_VEC.x() == -1);
        static_assert(INV_VEC.y() == -2);
    } // namespace static_tests

} // namespace



/**************************************
 *           ADDITION TESTS           *
 **************************************/

TYPED_TEST(CVec2AdditionTests, PlusOperator_ReturnsVectorSum)
{
    const flcn::CVec2 result = this->_vecA + this->_vecB;

    EXPECT_VEC_EQ(this->_expectedSum, result);
}


TEST(CVec2AdditionTests, PlusOperator_MixedType_PromotesType)
{
    const flcn::CVec2 vec1(3.0f, -1.0f);
    const flcn::CVec2 vec2(9.0, 10.0);

    [[maybe_unused]] const flcn::CVec2 result = vec1 + vec2;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


TYPED_TEST(CVec2AdditionTests, PlusEqualsOperator_ReturnsSameVectorWithSum)
{
    this->_vecA += this->_vecB;

    EXPECT_VEC_EQ(this->_expectedSum, this->_vecA);
}


TEST(CVec2AdditionTests, PlusEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::CVec2 vec1(3.0f, -1.0f);
    [[maybe_unused]] const flcn::CVec2 vec2(9.0, 10.0);

    static_cast<void>(vec1 += vec2);

    static_assert(std::is_same_v<decltype(vec1)::value_type, float>);
}



/**************************************
 *          SUBTRACTION TESTS         *
 **************************************/

TYPED_TEST(CVec2SubtractionTests, MinusOperator_ReturnsVectorDifference)
{
    const flcn::CVec2 result = this->_vecA - this->_vecB;

    EXPECT_VEC_EQ(this->_expectedDifference, result);
}


TEST(CVec2SubtractionTests, MinusOperator_MixedType_PromotesType)
{
    const flcn::CVec2 vec1(3.0f, -1.0f);
    const flcn::CVec2 vec2(9.0, 10.0);

    [[maybe_unused]] const flcn::CVec2 result = vec1 - vec2;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


TYPED_TEST(CVec2SubtractionTests, MinusEqualsOperator_ReturnsSameVectorWithDifference)
{
    this->_vecA -= this->_vecB;

    EXPECT_VEC_EQ(this->_expectedDifference, this->_vecA);
}


TEST(CVec2SubtractionTests, MinusEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::CVec2 vec1(3.0f, -1.0f);
    [[maybe_unused]] const flcn::CVec2 vec2(9.0, 10.0);

    static_cast<void>(vec1 -= vec2);

    static_assert(std::is_same_v<decltype(vec1)::value_type, float>);
}



/**************************************
 *     SCALAR MULTIPLICATION TESTS    *
 **************************************/

TEST(CVec2ScalarMultiplicationTests, TimesOperator_ByZeroReturnsZeroVector)
{
    const flcn::CVec2 vec(3.0f, 6.0f);

    const flcn::CVec2 result = vec * 0;

    EXPECT_VEC_ZERO(result);
}


TEST(CVec2ScalarMultiplicationTests, TimesOperator_ByOneReturnsOriginalVector)
{
    const flcn::CVec2 vec(3.0f, 6.0f);

    const flcn::CVec2 result = vec * 1;

    EXPECT_VEC_EQ(vec, result);
}


TYPED_TEST(CVec2ScalarMultiplicationTests, TimesOperator_ByScalarReturnsScaledVector)
{
    const flcn::CVec2 result = this->_vec * this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFloatingVec, result);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntegralVec, result);
    }
}


TYPED_TEST(CVec2ScalarMultiplicationTests, TimesOperator_ScalarByVectorReturnsScaledVector)
{
    const flcn::CVec2 result = this->_scalar * this->_vec;

    if (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFloatingVec, result);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntegralVec, result);
    }
}


TYPED_TEST(CVec2ScalarMultiplicationTests, TimesOperator_MixedType_PromotesType)
{
    const double scalar = 2.123456789123456;

    [[maybe_unused]] const flcn::CVec2 result = this->_vec * scalar;

    static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
}


TYPED_TEST(CVec2ScalarMultiplicationTests, TimesEqualsOperator_ByScalarReturnsTheSameVectorWithScaledComponents)
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


TEST(CVec2ScalarMultiplicationTests, TimesEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::CVec2 vec(3.0f, -1.0f);
    const double scalar = 5.0;
    vec *= scalar;

    static_assert(std::is_same_v<decltype(vec)::value_type, float>);
}


TEST(CVec2ScalarMultiplicationTests, TimesEqualsOperator_MixedType_EnsuresMinimalPrecisionLoss)
{
    flcn::CVec2 vec(3, -1);
    const double scalar = 2.5;
    const flcn::CVec2 expected(7, -2);

    vec *= scalar;

    EXPECT_VEC_EQ(expected, vec);
}



/**************************************
 *           DIVIDE OPERATOR          *
 **************************************/

TYPED_TEST(CVec2ScalarDivisionTests, DivideOperator_ByOneReturnsOriginalVector)
{
    const flcn::CVec2 result = this->_vec / 1;

    EXPECT_VEC_EQ(result, this->_vec);
}


TYPED_TEST(CVec2ScalarDivisionTests, DivideOperator_ReturnsVectorWithDividedComponents)
{
    const flcn::CVec2 result = this->_vec / this->_scalar;

    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


TEST(CVec2ScalarDivisionTests, MixedType_ScalarDivision_PromotesType)
{
    const flcn::CVec2 vec(15.0, -5.0);
    const double scalar = 5.0;

    [[maybe_unused]] const flcn::CVec2 result = vec / scalar;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


TYPED_TEST(CVec2ScalarDivisionTests, DivideEqualsOperator_ReturnsSameVectorWithDividedComponents)
{
    this->_vec /= this->_scalar;

    EXPECT_VEC_EQ(this->_expectedScaledVec, this->_vec);
}


TEST(CVec2ScalarDivisionTests, MixedType_ScalarDivisionAssignment_DoesNotPromoteType)
{
    flcn::CVec2 vec(15.0f, -5.0f);
    const double scalar = 5.0;

    vec /= scalar;

    static_assert(std::is_same_v<decltype(vec)::value_type, float>);
}


TEST(CVec2ScalarDivisionTests, TimesEqualsOperator_MixedType_EnsuresMinimalPrecisionLoss)
{
    flcn::CVec2 vec(10, -30);
    const double scalar = 2.5;
    const flcn::CVec2 expected(4, -12);

    vec /= scalar;

    EXPECT_VEC_EQ(expected, vec);
}


#ifndef ENABLE_DEBUG_TESTS
/**
 * @test Verify that dividing a float vector by zero returns an
 *        infinity vector of float type.
 */
TEST(CVec2ScalarDivisionTests, FloatVectorDivisionByZeroReturnsInfinityVector)
{
    const flcn::CVec2 vec(1.0f, 3.0f);
    EXPECT_VEC_INF(vec / 0);
}


/**
 * @test Verify that dividing a double vector by zero returns an
 *        infinity vector of double type.
 */
TEST(CVec2ScalarDivisionTests, DoubleVectorDivisionByZeroReturnsInfinityVector)
{
    const flcn::CVec2 vec(1.0, 3.0);
    EXPECT_VEC_INF(vec / 0);
}
#endif



/**************************************
 *        SAFE DIVISION TESTS         *
 **************************************/

TYPED_TEST(CVec2ScalarDivisionTests, SafeDiv_ReturnsVectorWithDividedComponents)
{
    const auto result = this->_vec.safeDiv(this->_scalar);

    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


TYPED_TEST(CVec2ScalarDivisionTests, SafeDiv_ByIntegralZero_ReturnsZeroVector)
{
    const auto result = this->_vec.safeDiv(0);
    EXPECT_VEC_ZERO(result);
}


TYPED_TEST(CVec2ScalarDivisionTests, SafeDiv_ByFloatZero_ReturnsZeroVector)
{
    const auto result = this->_vec.safeDiv(0.0f);
    EXPECT_VEC_ZERO(result);
}


TYPED_TEST(CVec2ScalarDivisionTests, StaticWrapper_SafeDiv_ReturnsVectorWithDividedComponents)
{
    const auto result = flcn::CVec2<TypeParam>::safeDiv(this->_vec, this->_scalar);
    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


TEST(CVec2ScalarDivision, StaticWrapper_SafeDiv_ByIntergralZero_ReturnsZeroVector)
{
    const flcn::CVec2 vec(1, 3);
    EXPECT_VEC_ZERO(flcn::CVec2<int>::safeDiv(vec, 0));
}


TYPED_TEST(CVec2ScalarDivisionTests, StaticWrapper_SafeDiv_ByFloatZero_ReturnsZeroVector)
{
    const auto result = flcn::CVec2<TypeParam>::safeDiv(this->_vec, 0.0f);
    EXPECT_VEC_ZERO(result);
}


TYPED_TEST(CVec2ScalarDivisionTests, SafeDiv_ByNaN_ReturnsZeroVector)
{
    const auto result = this->_vec.safeDiv(flcn::constants::NaN);

    EXPECT_VEC_ZERO(result);
}



TYPED_TEST(CVec2ScalarDivisionTests, StaticWrapper_SafeDiv_ByNaN_ReturnsZeroVector)
{
    const auto result = flcn::CVec2<TypeParam>::safeDiv(this->_vec, flcn::constants::INFINITY_F);

    EXPECT_VEC_ZERO(result);
}



/**************************************
 *         TRY DIVISION TESTS         *
 **************************************/

/**
 * @test Verify that dividing a vector using @ref flcn::CVec2::tryDiv perform a component-wise divide and
 *       returns a new vector instance and sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(CVec2ScalarDivisionTests, TryDivide_ReturnsVectorWithDividedComponentsAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto result = this->_vec.tryDiv(this->_scalar, flag);

    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
}


/**
 * @test Verify that dividing a vector by integral zero using @ref flcn::CVec2::tryDiv returns zero vector and
 *       sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(CVec2ScalarDivisionTests, TryDivideByIntegralZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto result = this->_vec.tryDiv(0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a vector by floating point zero using @ref flcn::CVec2::tryDiv returns zero vector and
 *       sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(CVec2ScalarDivisionTests, TryDivideByFloatZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto result = this->_vec.tryDiv(0.0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a NaN vector by zero using @ref flcn::CVec2::tryDiv
 *       @ref flcn::OperationStatus::NANOPERAND takes precedence over @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(CVec2ScalarDivision, TryDivideNaNVectorByZero_NaNOperandStatusTakesPrecedence)
{
    flcn::OperationStatus flag;
    [[maybe_unused]] const auto result = flcn::CVec2<double>::qnan().tryDiv(0, flag);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a vector by NaN using @ref flcn::CVec2::tryDiv returns a zero vector and
 *       sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TYPED_TEST(CVec2ScalarDivisionTests, TryDivideByNaN_ReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto result = this->_vec.tryDiv(flcn::constants::NaN, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a vector using static variant of @ref flcn::CVec2::tryDiv
 *       perform a component-wise divide and returns a new vector instance and
 *       sets the flag to @ref flcn::OperationStatus::SUCCESS.
 */
TYPED_TEST(CVec2ScalarDivisionTests, StaticWrapper_TryDivide_ReturnsVectorWithDividedComponentsAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto result = flcn::CVec2<TypeParam>::tryDiv(this->_vec, this->_scalar, flag);

    EXPECT_VEC_EQ(this->_expectedScaledVec, result);
    EXPECT_EQ(flcn::OperationStatus::SUCCESS, flag);
}


/**
 * @test Verify that dividing a vector by integral zero using static variant of @ref flcn::CVec2::tryDiv
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(CVec2ScalarDivisionTests, StaticWrapper_TryDivideByIntegralZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto result = flcn::CVec2<TypeParam>::tryDiv(this->_vec, 0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a vector by floating point zero using static variant of @ref flcn::CVec2::tryDiv
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::DIVISIONBYZERO.
 */
TYPED_TEST(CVec2ScalarDivisionTests, StaticWrapper_TryDivideByFloatZero_ReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto result = flcn::CVec2<TypeParam>::tryDiv(this->_vec, 0.0, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(flcn::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @test Verify that dividing a vector by floating point zero using static variant of @ref flcn::CVec2::tryDiv
 *       returns zero vector and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TEST(CVec2ScalarDivision, StaticWrapper_TryDivideNaNVector_ReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto result = flcn::CVec2<double>::tryDiv(flcn::CVec2<double>::qnan(), 3, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a vector by NaN using static variant of @ref flcn::CVec2::tryDiv returns zero vector
 * and sets the flag to @ref flcn::OperationStatus::NANOPERAND.
 */
TYPED_TEST(CVec2ScalarDivisionTests, StaticWrapper_TryDivideByNaN_ReturnsZeroVectorAndSetsCorrectFlag)
{
    flcn::OperationStatus flag;
    const auto result = flcn::CVec2<TypeParam>::tryDiv(this->_vec, flcn::constants::NaN, flag);

    EXPECT_VEC_ZERO(result);
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}



/**************************************
 *         NaN DIVISION TESTS         *
 **************************************/

/**
 * @test Verify that dividing a nan vector by a scalar using @ref flcn::CVec2::safeDiv
 *       returns vector with NaN-components as zero.
 */
TEST_P(CVec2DivisionNaNTests, SafeDiv_ReturnsVectorWithNaNComponentsAsZero)
{
    const auto& vec = GetParam();
    EXPECT_VEC_ZERO(vec.safeDiv(3));
}

/**
 * @test Verify that dividing a nan vector by a scalar using static variant of @ref flcn::CVec2::safeDiv
 *       returns zero vector.
 */
TEST_P(CVec2DivisionNaNTests, StaticWrapper_SafeDiv_ReturnsVectorWithNaNComponentsAsZero)
{
    const auto& vec = GetParam();
    EXPECT_VEC_ZERO(flcn::CVec2<float>::safeDiv(vec, 3));
}


/**
 * @test Verify that dividing a nan vector by a scalar using @ref flcn::CVec2::tryDiv
 *       returns zero vector and sets flag to OperationStatus::NANOPERAND.
 */
TEST_P(CVec2DivisionNaNTests, TryDiv_ReturnsVectorWithNaNComponentsAsZero)
{
    const auto& vec = GetParam();
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(vec.tryDiv(3, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}


/**
 * @test Verify that dividing a nan vector by a scalar using static variant of @ref flcn::CVec2::tryDiv
 *       returns zero vector and sets flag to OperationStatus::NANOPERAND.
 */
TEST_P(CVec2DivisionNaNTests, StaticWrapper_TryDiv_ReturnsVectorWithNaNComponentsAsZero)
{
    const auto& vec = GetParam();
    flcn::OperationStatus flag;
    EXPECT_VEC_ZERO(flcn::CVec2<float>::tryDiv(vec, 3, flag));
    EXPECT_EQ(flcn::OperationStatus::NANOPERAND, flag);
}



/**************************************
 *              NEGATION              *
 **************************************/

TYPED_TEST(CVec2NegationTests, InvertsTheSignOfEachComponents)
{
    const flcn::CVec2 inverted = -this->_vec;
    EXPECT_VEC_EQ(this->_expectedInvertedVec, inverted);
}


/** @test Verify that @ref flcn::CVec2 unary minus operator inverts each component of an infinity vector. */
TEST(CVec2NegationTests, InvertsSignOfInfinity)
{
    const flcn::CVec2 infVec = {
        flcn::constants::INFINITY_F,
        -flcn::constants::INFINITY_F,
    };
    const flcn::CVec2 expected = {
        -flcn::constants::INFINITY_F,
        flcn::constants::INFINITY_F,
    };

    const flcn::CVec2<float> inverted = -infVec;

    EXPECT_VEC_EQ(expected, inverted);
}


/** @test Verify that @ref flcn::CVec2 unary minus follows IEEE 754 rules for NaN. */
TEST(CVec2NegationTests, NoOpOnNaNVectors)
{
    const flcn::CVec2 nanVec = {
        flcn::constants::NaN,
        flcn::constants::NaN,
    };

    const flcn::CVec2<float> inverted = -nanVec;

    EXPECT_TRUE(std::isnan(inverted.x()));
    EXPECT_TRUE(std::isnan(inverted.y()));
}

/** @} */
