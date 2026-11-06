/**
 * @file Mat3x4.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 08, 2026
 *
 * @brief Verifies quaternion assertions in quaternion arithmetic operations that can result in application death.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CommonSetup.h"
#include "utils/MatrixUtils.h"

#include <falcon/math/matrices/Mat4x3.h>
#include <utility>


#ifdef ENABLE_DEBUG_TESTS

/**
 * @addtogroup T_FALCON_Mat4x3_Assertion
 * @{
 */

namespace
{
    flcn::Mat4x3 mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);

    /**
     * @brief Test fixture for @ref flcn::Mat4x3 invalid (row, column) indices.
     */
    class Mat4x3IndexingTests: public testing::TestWithParam<std::pair<std::size_t, std::size_t>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat4x3OutOfBoundsRowColumnIndices, Mat4x3IndexingTests,
                             testing::Values(std::make_pair(3, 3), std::make_pair(4, 3), std::make_pair(3, 4),
                                             std::make_pair(100, 100)));


    /**
     * @brief Test fixture for @ref flcn::Mat4x3 invalid column indices.
     */
    class Mat4x3ColumnIndexingTests: public testing::TestWithParam<std::size_t>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat4x3OutOfBoundColumnIndices, Mat4x3ColumnIndexingTests, testing::Values(3, 4, 100));


    /**
     * @brief Test fixture for @ref flcn::Mat4x3 Division.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat4x3DivisionTests: public testing::Test
    {
    protected:
        flcn::Mat4x3<T> _matrix;
        T _scalar;
        flcn::Mat4x3<T> _expectedMatrix;

        void SetUp() override
        {
            _matrix         = { flcn::Vec4{ T(7), T(3), T(0), T(21) }, flcn::Vec4{ T(1), T(6), T(6), T(12) },
                                flcn::Vec4{ T(3), T(12), T(18), T(21) } };
            _scalar         = T(3);
            _expectedMatrix = { flcn::Vec4{ T(2.333333333333333), T(1), T(0), T(7) },
                                flcn::Vec4{ T(0.3333333333333333), T(2), T(2), T(4) },
                                flcn::Vec4{ T(1), T(4), T(6), T(7) } };
        }
    };
    TYPED_TEST_SUITE(Mat4x3DivisionTests, SupportedArithmeticTypes);


    // TODO: Add tests
    // /**
    //  * @brief Test fixture for @ref flcn::Mat4 Division with NaN elements.
    //  */
    // class Mat4x3DivisionNaNTests: public testing::TestWithParam<flcn::Mat4x3<float>>
    // {};
    // INSTANTIATE_TEST_SUITE_P(
    //     Mat4InvalidDivision, Mat4x3DivisionNaNTests,
    //     ::testing::Values(
    //         flcn::Mat4x3<float>(flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //         flcn::Mat4x3<float>(3.0f,
    //         flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //         flcn::Mat4x3<float>(3.0f, 3.0f,
    //         flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //         flcn::Mat4x3<float>(3.0f, 3.0f, 3.0f,
    //         flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //         flcn::Mat4x3<float>(3.0f, 3.0f, 3.0f, 3.0f,
    //         flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //         flcn::Mat4x3<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f,
    //         flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //         flcn::Mat4x3<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f,
    //         flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //         flcn::Mat4x3<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f,
    //         flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f),
    //         flcn::Mat4x3<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f,
    //         flcn::constants::NaN, 3.0f, 3.0f, 3.0f),
    //         flcn::Mat4x3<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f,
    //         flcn::constants::NaN, 3.0f, 3.0f),
    //         flcn::Mat4x3<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f,
    //         flcn::constants::NaN, 3.0f),
    //         flcn::Mat4x3<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f,
    //         flcn::constants::NaN), flcn::Mat4x3<float>(flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
    //         flcn::constants::NaN,
    //                            flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
    //                            flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN)));
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TEST_P(Mat4x3ColumnIndexingTests, OutOfBoundAccessTriggers_AssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col]), "");
}


TEST_P(Mat4x3IndexingTests, OutOfBoundAccessTriggers_AssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col)), "");
}


TEST_P(Mat4x3ColumnIndexingTests, OutOfBoundMutation_TriggersAssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col] = flcn::Vec4<int>::zero()), "");
}


TEST_P(Mat4x3IndexingTests, OutOfBoundMutation_TriggersAssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col) = 5), "");
}


TYPED_TEST(Mat4x3DivisionTests, DivideOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(this->_matrix / 0), ""); }



TYPED_TEST(Mat4x3DivisionTests, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(this->_matrix /= 0, ""); }

/** @} */

#endif
