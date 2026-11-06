/**
 * @file Mat2x3.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 4, 2026
 *
 * @brief Verifies quaternion assertions in quaternion arithmetic operations that can result in application death.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "CommonSetup.h"
#include "utils/MatrixUtils.h"
#include "utils/VectorUtils.h"

#include <falcon/math/matrices/Mat2x3.h>
#include <utility>

/**
 * @addtogroup T_FALCON_Mat2x3_Assertion
 * @{
 */

#ifdef ENABLE_DEBUG_TESTS

namespace
{

    flcn::Mat2x3 mat(1, 2, 3, 4, 5, 6);
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2x3 (Row, Column) Access.
     */
    class Mat2x3IndexingTests: public testing::TestWithParam<std::pair<std::size_t, std::size_t>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat2x3InvalidIndex, Mat2x3IndexingTests,
                             testing::Values(std::make_pair(3, 3), std::make_pair(2, 3), std::make_pair(3, 2),
                                             std::make_pair(100, 100)));



    /**
     * @brief Test fixture for @ref flcn::Mat2x3 Column Access.
     */
    class Mat2x3ColumnIndexingTests: public testing::TestWithParam<std::size_t>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat2x3InvalidColumnIndex, Mat2x3ColumnIndexingTests, testing::Values(3, 4, 100));



    /**
     * @brief Test fixture for @ref flcn::Mat2x3 Division.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2x3DivisionTests: public testing::Test
    {
    protected:
        flcn::Mat2x3<T> _matrix;
        T _scalar;
        flcn::Mat2x3<T> _expectedMatrix;

        void SetUp() override
        {
            _matrix         = { flcn::CVec2{ T(7), T(3) }, flcn::CVec2{ T(1), T(6) }, flcn::CVec2{ T(3), T(9) } };
            _scalar         = T(3);
            _expectedMatrix = { flcn::CVec2{ T(2.333333333333333), T(1) }, flcn::CVec2{ T(0.3333333333333333), T(2) },
                                flcn::CVec2{ T(1), T(3) } };
        }
    };
    TYPED_TEST_SUITE(Mat2x3DivisionTests, SupportedArithmeticTypes);


    // TODO: Add after adding nan assertion to /
    // /**
    //  * @brief Test fixture for @ref flcn::Mat2x3 Division with NaN elements.
    //  */
    // class NaNMat2x3Division: public testing::TestWithParam<flcn::Mat2x3<float>>
    // {};
    // INSTANTIATE_TEST_SUITE_P(Mat2x3InvalidDivision, NaNMat2x3Division,
    //                          ::testing::Values(flcn::Mat2x3<float>(flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //                                            flcn::Mat2x3<float>(3.0f, flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f),
    //                                            flcn::Mat2x3<float>(3.0f, 3.0f, flcn::constants::NaN, 3.0f, 3.0f, 3.0f),
    //                                            flcn::Mat2x3<float>(3.0f, 3.0f, 3.0f, flcn::constants::NaN, 3.0f, 3.0f),
    //                                            flcn::Mat2x3<float>(3.0f, 3.0f, 3.0f, 3.0f, flcn::constants::NaN, 3.0f),
    //                                            flcn::Mat2x3<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, flcn::constants::NaN),
    //                                            flcn::Mat2x3<float>(flcn::constants::NaN, flcn::constants::NaN,
    //                                                               flcn::constants::NaN, flcn::constants::NaN,
    //                                                               flcn::constants::NaN, flcn::constants::NaN)));

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TEST_P(Mat2x3ColumnIndexingTests, OutOfBoundAccessTriggers_AssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col]), "");
}

TEST_P(Mat2x3IndexingTests, OutOfBoundAccessTriggers_AssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col)), "");
}


TEST_P(Mat2x3ColumnIndexingTests, OutOfBoundMutation_TriggersAssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col] = flcn::CVec2<int>::zero()), "");
}


TEST_P(Mat2x3IndexingTests, OutOfBoundMutation_TriggersAssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col) = 5), "");
}


TYPED_TEST(Mat2x3DivisionTests, DivideOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(this->_matrix / 0), ""); }


TYPED_TEST(Mat2x3DivisionTests, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(this->_matrix /= 0, ""); }

#endif

/** @} */
