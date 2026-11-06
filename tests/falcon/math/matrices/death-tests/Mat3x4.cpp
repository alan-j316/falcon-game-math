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

#include <falcon/math/matrices/Mat3x4.h>
#include <utility>



#ifdef ENABLE_DEBUG_TESTS

/**
 * @addtogroup T_FALCON_Mat3x4_Assertion
 * @{
 */

namespace
{
    flcn::Mat3x4 mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);


    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat3x4 invalid (row, column) indices.
     */
    class Mat3x4IndexingTests: public testing::TestWithParam<std::pair<std::size_t, std::size_t>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat3x4OutOfBoundsRowColumnIndices, Mat3x4IndexingTests,
                             testing::Values(std::make_pair(3, 3), std::make_pair(3, 4), std::make_pair(4, 3),
                                             std::make_pair(100, 100)));



    /**
     * @brief Test fixture for @ref flcn::Mat3x4 invalid column indices.
     */
    class Mat3x4ColumnIndexingTests: public testing::TestWithParam<std::size_t>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat3x4OutOfBoundsColumnIndices, Mat3x4ColumnIndexingTests, testing::Values(4, 5, 100));



    /**
     * @brief Test fixture for @ref flcn::Mat3x4 Division.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat3x4DivisionTests: public testing::Test
    {
    protected:
        flcn::Mat3x4<T> _matrix;
        T _scalar;
        flcn::Mat3x4<T> _expectedMatrix;

        void SetUp() override
        {
            _matrix = { flcn::Vec3{ T(7), T(3), T(0) }, flcn::Vec3{ T(1), T(6), T(6) }, flcn::Vec3{ T(0), T(6), T(9) },
                        flcn::Vec3{ T(27), T(24), T(30) } };
            _scalar = T(3);
            _expectedMatrix = { flcn::Vec3{ T(2.333333333333333), T(1), T(0) },
                                flcn::Vec3{ T(0.3333333333333333), T(2), T(2) }, flcn::Vec3{ T(0), T(2), T(3) },
                                flcn::Vec3{ T(9), T(8), T(10) } };
        }
    };
    TYPED_TEST_SUITE(Mat3x4DivisionTests, SupportedArithmeticTypes);


    // TODO: Add after adding assertions
    // /**
    //  * @brief Test fixture for @ref flcn::Mat3x4 Division with NaN elements.
    //  */
    // class NaNMat3x4Division: public testing::TestWithParam<flcn::Mat3x4<float>>
    // {};
    // INSTANTIATE_TEST_SUITE_P(
    //     Mat3x4DivisionTestSuite, NaNMat3x4Division,
    //     ::testing::Values(
    //         flcn::Mat3x4<float>(flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //         flcn::Mat3x4<float>(3.0f,
    //         flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //         flcn::Mat3x4<float>(3.0f, 3.0f,
    //         flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //         flcn::Mat3x4<float>(3.0f, 3.0f, 3.0f,
    //         flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //         flcn::Mat3x4<float>(3.0f, 3.0f, 3.0f, 3.0f,
    //         flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //         flcn::Mat3x4<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f,
    //         flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //         flcn::Mat3x4<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f,
    //         flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //         flcn::Mat3x4<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f,
    //         flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f),
    //         flcn::Mat3x4<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f,
    //         flcn::constants::NaN, 3.0f, 3.0f, 3.0f),
    //         flcn::Mat3x4<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f,
    //         flcn::constants::NaN, 3.0f, 3.0f),
    //         flcn::Mat3x4<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f,
    //         flcn::constants::NaN, 3.0f),
    //         flcn::Mat3x4<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f,
    //         flcn::constants::NaN), flcn::Mat3x4<float>(flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
    //         flcn::constants::NaN,
    //                            flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
    //                            flcn::constants::NaN, flcn::constants::NaN, flcn::constants::NaN,
    //                            flcn::constants::NaN)));


} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TEST_P(Mat3x4ColumnIndexingTests, OutOfBoundAccess_TriggersAssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col]), "");
}


TEST_P(Mat3x4IndexingTests, OutOfBoundAccess_TriggersAssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col)), "");
}


TEST_P(Mat3x4ColumnIndexingTests, OutOfBoundMutation_TriggersAssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col] = flcn::Vec3<int>::zero()), "");
}


TEST_P(Mat3x4IndexingTests, OutOfBoundMutation_TriggersAssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col) = 5), "");
}


TYPED_TEST(Mat3x4DivisionTests, DivideOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(this->_matrix / 0), ""); }


TYPED_TEST(Mat3x4DivisionTests, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(this->_matrix /= 0, ""); }

/** @} */

#endif
