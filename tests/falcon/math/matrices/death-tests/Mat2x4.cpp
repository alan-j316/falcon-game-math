/**
 * @file Mat2x4.cpp
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

#include <falcon/math/matrices/Mat2x4.h>
#include <utility>

/**
 * @addtogroup T_FALCON_Mat2x4_Assertion
 * @{
 */

#ifdef ENABLE_DEBUG_TESTS

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    flcn::Mat2x4 mat(1, 2, 3, 4, 5, 6, 7, 8);

    /**
     * @brief Test fixture for @ref flcn::Mat2x4 (Row, Column) Access.
     */
    class Mat2x4IndexingTests: public testing::TestWithParam<std::pair<std::size_t, std::size_t>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat2x4InvalidIndex, Mat2x4IndexingTests,
                             testing::Values(std::make_pair(4, 4), std::make_pair(2, 3), std::make_pair(3, 2),
                                             std::make_pair(100, 100)));



    /**
     * @brief Test fixture for @ref flcn::Mat2x4 Column Access.
     */
    class Mat2x4ColumnIndexingTests: public testing::TestWithParam<std::size_t>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat2x4InvalidColumnIndex, Mat2x4ColumnIndexingTests, testing::Values(4, 5, 100));



        /**
     * @brief Test fixture for @ref flcn::Mat2x4 Division.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */

    template <typename T>
    class Mat2x4DivisionTests: public ::testing::Test
    {
    protected:
        flcn::Mat2x4<T> _matrix;
        T _scalar;
        flcn::Mat2x4<T> _expectedMatrix;

        void SetUp() override
        {
            _matrix         = { flcn::CVec2{ T(7), T(3) }, flcn::CVec2{ T(1), T(6) }, flcn::CVec2{ T(3), T(9) },
                                flcn::CVec2{ T(0), T(24) } };
            _scalar         = T(3);
            _expectedMatrix = { flcn::CVec2{ T(2.333333333333333), T(1) }, flcn::CVec2{ T(0.3333333333333333), T(2) },
                                flcn::CVec2{ T(1), T(3) }, flcn::CVec2{ T(0), T(8) } };
        }
    };
    TYPED_TEST_SUITE(Mat2x4DivisionTests, SupportedArithmeticTypes);


    // /**
    //  * @brief Test fixture for @ref flcn::Mat2x4 Division with NaN elements.
    //  */
    // class NaNMat2x4Division: public ::testing::TestWithParam<flcn::Mat2x4<float>>
    // {};
    // INSTANTIATE_TEST_SUITE_P(
    //     Mat2x4DivisionTestSuite, NaNMat2x4Division,
    //     ::testing::Values(flcn::Mat2x4<float>(flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //                       flcn::Mat2x4<float>(3.0f, flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //                       flcn::Mat2x4<float>(3.0f, 3.0f, flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //                       flcn::Mat2x4<float>(3.0f, 3.0f, 3.0f, flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f),
    //                       flcn::Mat2x4<float>(3.0f, 3.0f, 3.0f, 3.0f, flcn::constants::NaN, 3.0f, 3.0f, 3.0f),
    //                       flcn::Mat2x4<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, flcn::constants::NaN, 3.0f, 3.0f),
    //                       flcn::Mat2x4<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, flcn::constants::NaN, 3.0f),
    //                       flcn::Mat2x4<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, flcn::constants::NaN),
    //                       flcn::Mat2x4<float>(flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
    //                                          flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
    //                                          flcn::constants::NaN, flcn::constants::NaN)));

    // TODO: Add after adding nan assertion to /

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TEST_P(Mat2x4ColumnIndexingTests, OutOfBoundAccessTriggers_AssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col]), "");
}

TEST_P(Mat2x4IndexingTests, OutOfBoundAccessTriggers_AssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col)), "");
}


TEST_P(Mat2x4ColumnIndexingTests, OutOfBoundMutation_TriggersAssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col] = flcn::CVec2<int>::zero()), "");
}


TEST_P(Mat2x4IndexingTests, OutOfBoundMutation_TriggersAssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col) = 5), "");
}


TYPED_TEST(Mat2x4DivisionTests, DivideOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(this->_matrix / 0), ""); }


TYPED_TEST(Mat2x4DivisionTests, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(this->_matrix /= 0, ""); }

#endif

/** @} */
