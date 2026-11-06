/**
 * @file ArithmeticOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 30, 2026
 *
 * @brief Verify @ref flcn::Point2 arithmetic operator(+, -) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Point2TestSetup.h"


/**
 * @addtogroup T_FALCON_Point2_Addition
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Point2 addition operation.
     *
     * @tparam T The scalar type (e.g., float, double) used for the point.
     */
    template <typename T>
    class Point2AdditionTests: public testing::Test
    {
    protected:
        flcn::CVec2<T> _vector;
        flcn::Point2<T> _point;
        flcn::Point2<T> _expectedPoint;

        void SetUp() override
        {
            _vector        = { T(3), T(1) };
            _point         = { T(1), T(2) };
            _expectedPoint = { T(4), T(3) };
        }
    };
    TYPED_TEST_SUITE(Point2AdditionTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref flcn::Point2 subtraction operation.
     *
     * @tparam T The scalar type (e.g., float, double) used for the point.
     */
    template <typename T>
    class Point2SubtractionTests: public testing::Test
    {
    protected:
        flcn::Point2<T> _pointA;
        flcn::Point2<T> _pointB;
        flcn::Point2<T> _expectedVector;

        void SetUp() override
        {
            _pointA         = { T(95), T(11) };
            _pointB         = { T(8), T(5) };
            _expectedVector = { T(87), T(6) };
        }
    };
    TYPED_TEST_SUITE(Point2SubtractionTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Point2 POINT_A(1, 2);
        constexpr flcn::CVec2 DIR_VEC(1, 3);
        constexpr flcn::Point2 POINT_B(4, 3);


        /// @test Verify that a Point2 + CVec2 returns a valid Point2 at compile time.
        constexpr auto SUM_POINT = POINT_A + DIR_VEC;
        static_assert(std::is_same_v<decltype(SUM_POINT), const flcn::Point2<int>>);
        static_assert(SUM_POINT.x() == 2);
        static_assert(SUM_POINT.y() == 5);

        /// @test Verify that a Point2 - Point2 returns a valid CVec2 at compile time.
        constexpr auto SUB_DIR_VEC = POINT_A - POINT_B;
        static_assert(std::is_same_v<decltype(SUB_DIR_VEC), const flcn::CVec2<int>>);
        static_assert(SUB_DIR_VEC.x() == -3);
        static_assert(SUB_DIR_VEC.y() == -1);

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Point2AdditionTests, PlusOperator_ReturnsAPointWithComponentwiseSum)
{
    const flcn::Point2 result = this->_point + this->_vector;
    EXPECT_VEC_EQ(this->_expectedPoint, result);
}


TEST(Point2AdditionTests, PlusOperator_MixedType_PromotesType)
{
    const flcn::Point2 point(3.0f, 0.0f);
    const flcn::CVec2 vector(9.0, -5.0);

    [[maybe_unused]] const flcn::Point2 result = point + vector;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


TYPED_TEST(Point2AdditionTests, PlusEqualsOperator_ReturnsSamePointWithComponentwiseSum)
{
    this->_point += this->_vector;
    EXPECT_VEC_EQ(this->_expectedPoint, this->_point);
}


TEST(Point2AdditionTests, PlusEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::Point2 point(3.0f, 0.0f);
    const flcn::CVec2 vector(9.0, -5.0);

    static_cast<void>(point += vector);

    static_assert(std::is_same_v<decltype(point)::value_type, float>);
}

/** @} */



/**
 * @addtogroup T_FALCON_Point2_Subtraction
 * @{
 */

TYPED_TEST(Point2SubtractionTests, MinusOperator_ReturnsAVectorWithComponentwiseDifference)
{
    const auto result = this->_pointA - this->_pointB;

    EXPECT_VEC_EQ(this->_expectedVector, result);
}


TEST(Point2SubtractionTests, MinusOperator_MixedType_PromotesType)
{
    const flcn::Point2 pointA(3.0f, 0.0f);
    const flcn::Point2 pointB(9.0, -5.0);

    [[maybe_unused]] const auto result = pointA - pointB;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}

/** @} */
