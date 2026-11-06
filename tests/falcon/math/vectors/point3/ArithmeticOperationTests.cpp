/**
 * @file ArithmeticOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 30, 2026
 *
 * @brief Verify @ref flcn::Point3 arithmetic operator(+, -) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Point3TestSetup.h"


/**
 * @addtogroup T_FALCON_Point3_Addition
 * @{
 */

namespace
{

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Point3 addition operation.
     *
     * @tparam T The scalar type (e.g., float, double) used for the point.
     */
    template <typename T>
    class Point3AdditionTests: public testing::Test
    {
    protected:
        flcn::Vec3<T> _vector;
        flcn::Point3<T> _point;
        flcn::Point3<T> _expectedPoint;

        void SetUp() override
        {
            _vector        = { T(3), T(1), T(6) };
            _point         = { T(1), T(2), T(3) };
            _expectedPoint = { T(4), T(3), T(9) };
        }
    };
    TYPED_TEST_SUITE(Point3AdditionTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref flcn::Point3 subtraction operation.
     *
     * @tparam T The scalar type (e.g., float, double) used for the point.
     */
    template <typename T>
    class Point3SubtractionTests: public testing::Test
    {
    protected:
        flcn::Point3<T> _pointA;
        flcn::Point3<T> _pointB;
        flcn::Point3<T> _expectedVector;

        void SetUp() override
        {
            _pointA         = { T(95), T(11), T(6) };
            _pointB         = { T(8), T(5), T(2) };
            _expectedVector = { T(87), T(6), T(4) };
        }
    };
    TYPED_TEST_SUITE(Point3SubtractionTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Point3 POINT_A(1, 2, 3);
        constexpr flcn::Vec3 DIR_VEC(1, 3, 7);
        constexpr flcn::Point3 POINT_B(4, 3, 1);

        /// @test Verify that a Point3 + Vec3 returns a valid Point3 at compile time.
        constexpr auto SUM_POINT = POINT_A + DIR_VEC;
        static_assert(std::is_same_v<decltype(SUM_POINT), const flcn::Point3<int>>);
        static_assert(SUM_POINT.x() == 2);
        static_assert(SUM_POINT.y() == 5);
        static_assert(SUM_POINT.z() == 10);

        /// @test Verify that a Point3 - Point3 returns a valid Vec3 at compile time.
        constexpr auto SUB_DIR_VEC = POINT_A - POINT_B;
        static_assert(std::is_same_v<decltype(SUB_DIR_VEC), const flcn::Vec3<int>>);
        static_assert(SUB_DIR_VEC.x() == -3);
        static_assert(SUB_DIR_VEC.y() == -1);
        static_assert(SUB_DIR_VEC.z() == 2);

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Point3AdditionTests, PlusOperator_ReturnsAPointWithComponentwiseSum)
{
    const flcn::Point3 result = this->_point + this->_vector;
    EXPECT_VEC_EQ(this->_expectedPoint, result);
}


TEST(Point3AdditionTests, PlusOperator_MixedType_PromotesType)
{
    const flcn::Point3 point(3.0f, 0.0f, -1.0f);
    const flcn::Vec3 vector(9.0, -5.0, 10.0);

    [[maybe_unused]] const flcn::Point3 result = point + vector;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


TYPED_TEST(Point3AdditionTests, PlusEqualsOperator_ReturnsSamePointWithComponentwiseSum)
{
    this->_point += this->_vector;
    EXPECT_VEC_EQ(this->_expectedPoint, this->_point);
}


TEST(Point3AdditionTests, PlusEqualsOperator_MixedType_DoesNotPromoteType)
{
    flcn::Point3 point(3.0f, 0.0f, -1.0f);
    const flcn::Vec3 vector(9.0, -5.0, 10.0);

    static_cast<void>(point += vector);

    static_assert(std::is_same_v<decltype(point)::value_type, float>);
}

/** @} */



/**
 * @addtogroup T_FALCON_Point3_Subtraction
 * @{
 */

TYPED_TEST(Point3SubtractionTests, MinusOperator_ReturnsAVectorWithComponentwiseDifference)
{
    const auto result = this->_pointA - this->_pointB;

    EXPECT_VEC_EQ(this->_expectedVector, result);
}


TEST(Point3SubtractionTests, MinusOperator_MixedType_PromotesType)
{
    const flcn::Point3 pointA(3.0f, 0.0f, -1.0f);
    const flcn::Point3  pointB(9.0, -5.0, 10.0);

    [[maybe_unused]] const auto result = pointA - pointB;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}

/** @} */
