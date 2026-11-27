/**
 * @file MathTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 28, 2026
 *
 * @brief Verify @ref flcn::utils function's logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "CommonSetup.h"

#include <array>
#include <falcon/core/Constants.h>
#include <falcon/core/Math.h>


/**
 * @addtogroup TFalcon_Core_Math
 * @{
 */

namespace
{
    using namespace testutils;
    inline constexpr auto INF_F = flcn::constants::INFINITY_F;
    using FpVec4                = std::vector<float>;

    /// +---------------------------------------------------------------------------------------+
    /// |                                TEST PARAMS                                            |
    /// +---------------------------------------------------------------------------------------+

    /**
     * @brief Test parameter for testing math functions binary arithmetic arguments
     *        returning another arithmetic value.
     * @tparam T Numeric type for arguments.
     */
    template <typename T>
    struct BinaryMathTestParam
    {
        T a, b;
        T expected;
    };


    /**
     * @brief Test parameter for testing math functions with list of parameters.
     * @tparam T Numeric type for elements.
     */
    template <typename T>
    struct ListMathTestParam
    {
        std::vector<T> list;
        T expected;
    };


    template <typename T>
    struct CompareEqTestParams
    {
        T a, b;
        bool expected;
    };


    /// +---------------------------------------------------------------------------------------+
    /// |                               TEST SETUP                                              |
    /// +---------------------------------------------------------------------------------------+

    /**
     * @brief Test fixture for @ref flcn::diffAbs.
     */
    template <typename>
    class FalconDiffAbsTests: public testing::Test
    {};
    TYPED_TEST_SUITE(FalconDiffAbsTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for validating @ref flcn::compareEq across different types.
     */
    template <typename T>
    class CompareEqTests: public testing::Test
    {
    protected:
        T _equalValueA, _equalValueB, _unequalValue;

        void SetUp() override
        {
            _equalValueA  = T(1.01238402134);
            _equalValueB  = T(1.01238402134);
            _unequalValue = T(5.2139032);
        }
    };
    TYPED_TEST_SUITE(CompareEqTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref flcn::abs(signed numbers).
     *
     * @tparam T The scalar type(int, float, double...) of the values.
     */
    template <typename T>
    class AbsTestUnsigned: public testing::Test
    {
    protected:
        T _value, _expectedAbsValue;

        void SetUp() override
        {
            _value            = T(-5.2891283123432);
            _expectedAbsValue = T(5.2891283123432);
        }
    };
    TYPED_TEST_SUITE(AbsTestUnsigned, SupportedSignedArithmeticTypes);


    /**
     * @brief Test fixture for @ref flcn::abs(unsigned numbers).
     *
     * @tparam T The scalar type(int, float, double...) of the values.
     */
    template <typename T>
    class AbsTest: public testing::Test
    {
    protected:
        T _value, _expectedAbsValue;

        void SetUp() override
        {
            _value            = T(5.2891283123432);
            _expectedAbsValue = T(5.2891283123432);
        }
    };
    TYPED_TEST_SUITE(AbsTest, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref flcn::min.
     * @tparam T The scalar type(int, float, double...) of the values.
     */
    template <typename T>
    class MinTypedTests: public testing::Test
    {
    public:
        std::vector<T> elements{};
        T expected;

    protected:
        void SetUp() override
        {
            elements = { T(99), T(0), T(5), T(3) };
            expected = T(0);
        }
    };
    TYPED_TEST_SUITE(MinTypedTests, SupportedArithmeticTypes);


    /// @brief Parameterized test fixture for flcn::min(binary parameters)
    class MinBinaryParamTests: public testing::TestWithParam<BinaryMathTestParam<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        MinBinaryParamTests, MinBinaryParamTests,
        testing::Values(BinaryMathTestParam{ 1.0f, 2.0f, 1.0f }, BinaryMathTestParam{ 1.0f, -2.0f, -2.0f },
                        BinaryMathTestParam{ -1.0f, -2.0f, -2.0f }, BinaryMathTestParam{ INF_F, -2.0f, -2.0f },
                        BinaryMathTestParam{ -INF_F, -2.0f, -INF_F }, BinaryMathTestParam{ -INF_F, INF_F, -INF_F },
                        BinaryMathTestParam{ 5000.0f, INF_F, 5000.0f }));

    /// @brief Parameterized test fixture for flcn::min(binary parameters)
    class MinListParamTests: public testing::TestWithParam<ListMathTestParam<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(MinListParamTests, MinListParamTests,
                             testing::Values(ListMathTestParam{ FpVec4{ 1.0f, 2.0f, 3.0f, 4.0f }, 1.0f },
                                             ListMathTestParam{ FpVec4{ 1.0f, -2.0f, -1.5f, 0.5f }, -2.0f },
                                             ListMathTestParam{ FpVec4{ -1.0f, -2.0f, -3.5f, -99.0f }, -99.0f },
                                             ListMathTestParam{ FpVec4{ INF_F, -2.0f, INF_F, 49.0f }, -2.0f },
                                             ListMathTestParam{ FpVec4{ -INF_F, -2.0f, INF_F, 2.0f }, -INF_F },
                                             ListMathTestParam{ FpVec4{ -INF_F, INF_F, 0.0f, 999999.0f }, -INF_F },
                                             ListMathTestParam{ FpVec4{ 5000.0f, INF_F, 50.0f, 316.0f }, 50.0f }));



    /**
     * @brief Test fixture for @ref flcn::min.
     * @tparam T The scalar type(int, float, double...) of the values.
     */
    template <typename T>
    class MaxTypedTests: public testing::Test
    {
    public:
        std::vector<T> elements{};
        T expected;

    protected:
        void SetUp() override
        {
            elements = { T(99), T(0), T(5), T(3) };
            expected = T(99);
        }
    };
    TYPED_TEST_SUITE(MaxTypedTests, SupportedArithmeticTypes);


    /// @brief Parameterized test fixture for flcn::max(binary parameters)
    class MaxBinaryParamTests: public testing::TestWithParam<BinaryMathTestParam<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        MaxBinaryParamTests, MaxBinaryParamTests,
        testing::Values(BinaryMathTestParam{ 1.0f, 2.0f, 2.0f }, BinaryMathTestParam{ 1.0f, -2.0f, 1.0f },
                        BinaryMathTestParam{ -1.0f, -2.0f, -1.0f }, BinaryMathTestParam{ INF_F, -2.0f, INF_F },
                        BinaryMathTestParam{ -INF_F, -2.0f, -2.0f }, BinaryMathTestParam{ -INF_F, INF_F, INF_F },
                        BinaryMathTestParam{ 5000.0f, INF_F, INF_F }));

    /// @brief Parameterized test fixture for flcn::max(binary parameters)
    class MaxListParamTests: public testing::TestWithParam<ListMathTestParam<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(MaxListParamTests, MaxListParamTests,
                             testing::Values(ListMathTestParam{ FpVec4{ 1.0f, 2.0f, 3.0f, 4.0f }, 4.0f },
                                             ListMathTestParam{ FpVec4{ 1.0f, -2.0f, -1.5f, 0.5f }, 1.0f },
                                             ListMathTestParam{ FpVec4{ -1.0f, -2.0f, -3.5f, -99.0f }, -1.0f },
                                             ListMathTestParam{ FpVec4{ INF_F, -2.0f, INF_F, 49.0f }, INF_F },
                                             ListMathTestParam{ FpVec4{ -INF_F, -2.0f, INF_F, 2.0f }, INF_F },
                                             ListMathTestParam{ FpVec4{ -INF_F, INF_F, 0.0f, 999999.0f }, INF_F },
                                             ListMathTestParam{ FpVec4{ 5000.0f, INF_F, 50.0f, 316.0f }, INF_F }));



    /// +---------------------------------------------------------------------------------------+
    /// |                                 STATIC TESTS                                          |
    /// +---------------------------------------------------------------------------------------+

    namespace static_tests
    {
        /** @test Verify that @ref flcn::diffAbs returns the correct value at compile time. */
        static_assert(flcn::diffAbs(1000, 100) == 900);
        static_assert(flcn::diffAbs(100, 1000) == 900);


        /// @test Verify that @ref flcn::compareEq returns the correct boolean at compile time. */
        static_assert(flcn::compareEq(9.1111, 9.1112) == false);
        static_assert(flcn::compareEq(9.1112, 9.1111) == false);
        static_assert(flcn::compareEq(9.1112, 9.1112) == true);

        /** @test Verify that @ref flcn::abs return absolute value at compile time. */
        static_assert(flcn::abs(-3.53) == 3.53);
        static_assert(flcn::abs(static_cast<unsigned int>(12)) == 12);
        static_assert(flcn::abs(static_cast<char>(-3.5312893)) == 3);
        static_assert(flcn::abs(-0.0000000000053) == 0.0000000000053);
        static_assert(flcn::abs(-3) == 3);
        static_assert(flcn::abs(flcn::constants::NaN_D) != flcn::constants::NaN_D);


        /** @test Verify that @ref flcn::isNaN is correct boolean at compile time. */
        static_assert(flcn::isNaN(-3.53) == false);
        static_assert(flcn::isNaN(3.53) == false);
        static_assert(flcn::isNaN(0) == false);
        static_assert(flcn::isNaN(flcn::constants::NaN) == true);
        static_assert(flcn::isNaN(flcn::constants::NaN_D) == true);


        /** @test Verify that @ref flcn::isInf returns correct boolean at compile time. */
        static_assert(flcn::isInf(-3.53) == false);
        static_assert(flcn::isInf(3.53) == false);
        static_assert(flcn::isInf(0) == false);
        static_assert(flcn::isInf(INF_F) == true);
        static_assert(flcn::isInf(-INF_F) == true);

        /** @test Verify that @ref flcn::min return the smallest value at compile time. */
        static_assert(flcn::min(0, 1) == 0);
        static_assert(flcn::min(-1, 1) == -1);
        static_assert(flcn::min(-1, -5) == -5);
        static_assert(flcn::min(5.0f, 5.5f) == 5.0f);
        static_assert(flcn::min(5.0f, 5.01f) == 5.0f);
        static_assert(flcn::min(4.99f, 5.01f) == 4.99f);
        static_assert(flcn::min(4.99f, -5.01f) == -5.01f);
        static_assert(flcn::min(-INF_F, -5.01f) == -INF_F);
        static_assert(flcn::min(-INF_F, INF_F) == -INF_F);
        static_assert(flcn::min(-2.0f, INF_F) == -2.0f);

        /** @test Verify that @ref flcn::min(init list) return the smallest value at compile time. */
        static_assert(flcn::min({ 1, 2, 3 }) == 1);
        static_assert(flcn::min({ -1, -2, -3 }) == -3);
        static_assert(flcn::min({ 1, -2, 3 }) == -2);
        static_assert(flcn::min({ 1.0f, 2.0f, 3.0f }) == 1.0f);
        static_assert(flcn::min({ 1.0f, -2.0f, 3.0f }) == -2.0f);
        static_assert(flcn::min({ 1.0f, -2.0f, -INF_F }) == -INF_F);
        static_assert(flcn::min({ 1.0f, -2.0f, INF_F }) == -2.0f);
        static_assert(flcn::min({ 1.0f, INF_F, -INF_F }) == -INF_F);

        /** @test Verify that @ref flcn::max return the largest value at compile time. */
        static_assert(flcn::max(0, 1) == 1);
        static_assert(flcn::max(-1, 1) == 1);
        static_assert(flcn::max(-1, -5) == -1);
        static_assert(flcn::max(5.0f, 5.5f) == 5.5f);
        static_assert(flcn::max(5.0f, 5.01f) == 5.01f);
        static_assert(flcn::max(4.99f, 5.01f) == 5.01f);
        static_assert(flcn::max(4.99f, -5.01f) == 4.99f);
        static_assert(flcn::max(-INF_F, -5.01f) == -5.01f);
        static_assert(flcn::max(-INF_F, INF_F) == INF_F);
        static_assert(flcn::max(-2.0f, INF_F) == INF_F);

        /** @test Verify that @ref flcn::max(init list) return the largest value at compile time. */
        static_assert(flcn::max({ 1, 2, 3 }) == 3);
        static_assert(flcn::max({ -1, -2, -3 }) == -1);
        static_assert(flcn::max({ 1, -2, 3 }) == 3);
        static_assert(flcn::max({ 1.0f, 2.0f, 3.0f }) == 3.0f);
        static_assert(flcn::max({ 1.0f, -2.0f, 3.0f }) == 3.0f);
        static_assert(flcn::max({ 1.0f, -2.0f, -INF_F }) == 1.0f);
        static_assert(flcn::max({ 1.0f, -2.0f, INF_F }) == INF_F);
        static_assert(flcn::max({ 1.0f, INF_F, -INF_F }) == INF_F);


        /// TODO: Add sqrt tests
        //     static_assert(flcn::utils::sqrt(4) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        //     static_assert(flcn::utils::sqrt(2.0) - 1.41421356237 <= flcn::Config::DOUBLE_EPSILON);
        //     static_assert(flcn::utils::sqrt(4) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        //     static_assert(flcn::utils::sqrt(4) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        //     static_assert(flcn::utils::sqrt(4) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        //     static_assert(flcn::utils::sqrt(4) - 2.0f <= flcn::Config::FLOAT_EPSILON);
        //     static_assert(flcn::utils::sqrt(4) - 2.0f <= flcn::Config::FLOAT_EPSILON);
    } // namespace static_tests


} // namespace



/// +---------------------------------------------------------------------------------------+
/// |                                DIFF_ABS TESTS                                         |
/// +---------------------------------------------------------------------------------------+

TYPED_TEST(FalconDiffAbsTests, ReturnsAbsoluteValueWithUnderflow_WhenAGreaterThanB)
{
    const auto a      = TypeParam(12);
    const auto b      = TypeParam(7);
    const auto result = TypeParam(5);
    testutils::EXPECT_MAG_EQ(result, flcn::diffAbs(a, b));
}


TYPED_TEST(FalconDiffAbsTests, ReturnsAbsoluteValueWithUnderflow_WhenBGreaterThanA)
{
    const auto a      = TypeParam(7);
    const auto b      = TypeParam(12);
    const auto result = TypeParam(5);
    testutils::EXPECT_MAG_EQ(result, flcn::diffAbs(a, b));
}


TYPED_TEST(FalconDiffAbsTests, ReturnsAbsoluteValueWithUnderflow_WhenAEqualsB)
{
    const auto a      = TypeParam(12);
    const auto b      = TypeParam(12);
    const auto result = TypeParam(0);
    testutils::EXPECT_MAG_EQ(result, flcn::diffAbs(a, b));
}



/// +---------------------------------------------------------------------------------------+
/// |                               COMPARE_EQ TESTS                                        |
/// +---------------------------------------------------------------------------------------+

TYPED_TEST(CompareEqTests, EqualValues_ReturnTrue)
{ EXPECT_TRUE(flcn::compareEq(this->_equalValueA, this->_equalValueB)); }


TYPED_TEST(CompareEqTests, UnequalValues_ReturnFalse)
{ EXPECT_FALSE(flcn::compareEq(this->_equalValueA, this->_unequalValue)); }


/// @test Verify that compareEq works with relative precision when compared IEEE 754 floating point types.
TEST(CompareEqTests, MaintainsARelativePrecision) { EXPECT_FALSE(flcn::compareEq(316.810892301231, 316.810892301222)); }



/// +---------------------------------------------------------------------------------------+
/// |                                  ABS TESTS                                            |
/// +---------------------------------------------------------------------------------------+

TYPED_TEST(AbsTestUnsigned, UnsignedNumbers_ReturnsAbsoluteValue)
{ testutils::EXPECT_MAG_EQ(this->_expectedAbsValue, flcn::abs(this->_value)); }


TYPED_TEST(AbsTest, SignedNumbers_ReturnsAbsoluteValue)
{ testutils::EXPECT_MAG_EQ(this->_expectedAbsValue, flcn::abs(this->_value)); }



/// +---------------------------------------------------------------------------------------+
/// |                                 ISNAN TESTS                                           |
/// +---------------------------------------------------------------------------------------+

/** @test Verify that check for IEEE 754 NaN using @ref flcn::isnan returns true for a standard quiet NaN. */
TEST(IsNaNTests, NaNReturnsTrue) { EXPECT_TRUE(flcn::isNaN(flcn::constants::NaN)); }


/** @test Verify that check for IEEE 754 NaN using @ref flcn::isnan returns false for a non-NaN. */
TEST(IsNaNTests, NumberReturnsFalse) { EXPECT_FALSE(flcn::isNaN(3.16f)); }



/// +---------------------------------------------------------------------------------------+
/// |                                 IS_INF TESTS                                          |
/// +---------------------------------------------------------------------------------------+

/** @test Verify that check for IEEE 754 infinity using @ref flcn::isinf returns true for a positive infinity. */
TEST(IsInfTests, PositiveInfinityReturnsTrue) { EXPECT_TRUE(flcn::isInf(INF_F)); }


/** @test Verify that check for IEEE 754 infinity using @ref flcn::isinf returns true for a negative infinity. */
TEST(IsInfTests, NegativeInfinityReturnsTrue) { EXPECT_TRUE(flcn::isInf(-INF_F)); }


/** @test Verify that check for IEEE 754 infinity using @ref flcn::isinf returns true for a non-infinity value. */
TEST(IsInfTests, NonInfiniteNumberReturnsFalse) { EXPECT_FALSE(flcn::isInf(3.16f)); }



/// +---------------------------------------------------------------------------------------+
/// |                                  MIN TESTS                                            |
/// +---------------------------------------------------------------------------------------+

TYPED_TEST(MinTypedTests, BinaryValues_ReturnsTheMinimumOfTwo)
{ EXPECT_MAG_EQ(this->expected, flcn::min(this->elements[0], this->elements[1])); }


TYPED_TEST(MinTypedTests, ListValues_ReturnsTheMinimumFromTheList)
{
    EXPECT_EQ(4, this->elements.size()) << "Test Parameter error: List must be of size of 4.";
    EXPECT_MAG_EQ(this->expected,
                  flcn::min({ this->elements[0], this->elements[1], this->elements[2], this->elements[3] }));
}


TEST_P(MinBinaryParamTests, ReturnsTheMinimumValue)
{
    const auto [first, second, expected] = GetParam();
    EXPECT_MAG_EQ(expected, flcn::min(first, second));
}


TEST_P(MinListParamTests, ReturnsTheMinimumValue)
{
    const auto& [list, expected] = GetParam();
    EXPECT_EQ(4, list.size()) << "Test Parameter error: List must be of size of 4.";
    EXPECT_MAG_EQ(expected, flcn::min({ list[0], list[1], list[2], list[3] }));
}



/// +---------------------------------------------------------------------------------------+
/// |                                  MAX TESTS                                            |
/// +---------------------------------------------------------------------------------------+

TYPED_TEST(MaxTypedTests, BinaryValues_ReturnsTheMinimumOfTwo)
{ EXPECT_MAG_EQ(this->expected, flcn::max(this->elements[0], this->elements[1])); }


TYPED_TEST(MaxTypedTests, ListValues_ReturnsTheMinimumFromTheList)
{
    EXPECT_EQ(4, this->elements.size()) << "Test Parameter error: List must be of size of 4.";
    EXPECT_MAG_EQ(this->expected,
                  flcn::max({ this->elements[0], this->elements[1], this->elements[2], this->elements[3] }));
}


TEST_P(MaxBinaryParamTests, ReturnsTheMinimumValue)
{
    const auto [first, second, expected] = GetParam();
    EXPECT_MAG_EQ(expected, flcn::max(first, second));
}


TEST_P(MaxListParamTests, ReturnsTheMinimumValue)
{
    const auto& [list, expected] = GetParam();
    EXPECT_EQ(4, list.size()) << "Test Parameter error: List must be of size of 4.";
    EXPECT_MAG_EQ(expected, flcn::max({ list[0], list[1], list[2], list[3] }));
}


/** @} */
