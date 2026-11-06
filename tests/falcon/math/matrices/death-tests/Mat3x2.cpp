/**
 * @file Mat3x2.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 08, 2026
 *
 * @brief Verifies quaternion assertions in quaternion arithmetic operations that can result in application death.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CommonSetup.h"
#include "utils/MatrixUtils.h"

#include <falcon/math/matrices/Mat3x2.h>
#include <utility>



#ifdef ENABLE_DEBUG_TESTS

/**
 * @addtogroup T_FALCON_Mat3x2_Assertion
 * @{
 */

namespace
{
    flcn::Mat3x2 mat(1, 2, 3, 4, 5, 6);


    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat3 invalid (row, column) indices.
     */
    class Mat3x2IndexingTests: public testing::TestWithParam<std::pair<std::size_t, std::size_t>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat3x2OutOfBoundsRowColumnIndices, Mat3x2IndexingTests,
                             testing::Values(std::make_pair(3, 3), std::make_pair(2, 3), std::make_pair(3, 2),
                                             std::make_pair(100, 100)));



    /**
     * @brief Test fixture for @ref flcn::Mat3 invalid column indices.
     */
    class Mat3x2ColumnIndexingTests: public testing::TestWithParam<std::size_t>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat3x2OutOfBoundsColumnIndices, Mat3x2ColumnIndexingTests, testing::Values(3, 4, 100));



    /**
     * @brief Test fixture for @ref flcn::Mat3x2 Division.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat3x2DivisionTests: public testing::Test
    {
    protected:
        flcn::Mat3x2<T> _matrix;
        T _scalar;
        flcn::Mat3x2<T> _expectedMatrix;

        void SetUp() override
        {
            _matrix         = { flcn::Vec3{ T(7), T(3), T(0) }, flcn::Vec3{ T(1), T(6), T(6) } };
            _scalar         = T(3);
            _expectedMatrix = { flcn::Vec3{ T(2.333333333333333), T(1), T(0) },
                                flcn::Vec3{ T(0.3333333333333333), T(2), T(2) } };
        }
    };
    /** Test fixture for @ref flcn::Mat3x2 division, parameterized by @ref SupportedArithmeticTypes */
    TYPED_TEST_SUITE(Mat3x2DivisionTests, SupportedArithmeticTypes);



    // TODO: Add checks for NaN Div
    /** @brief Test fixture for @ref flcn::Mat3x2 division with NaN vectors. */
    // class Mat3x2DivisionNaNTests: public testing::TestWithParam<flcn::Mat3x2<float>>
    // {};
    // INSTANTIATE_TEST_SUITE_P(Mat3x2InvalidDivision, Mat3x2DivisionNaNTests,
    //                          ::testing::Values(flcn::Mat3x2<float>(flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //                                            flcn::Mat3x2<float>(3.0f, flcn::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f),
    //                                            flcn::Mat3x2<float>(3.0f, 3.0f, flcn::constants::NaN, 3.0f, 3.0f, 3.0f),
    //                                            flcn::Mat3x2<float>(3.0f, 3.0f, 3.0f, flcn::constants::NaN, 3.0f, 3.0f),
    //                                            flcn::Mat3x2<float>(3.0f, 3.0f, 3.0f, 3.0f, flcn::constants::NaN, 3.0f),
    //                                            flcn::Mat3x2<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, flcn::constants::NaN),
    //                                            flcn::Mat3x2<float>(flcn::constants::NaN, flcn::constants::NaN,
    //                                                               flcn::constants::NaN, flcn::constants::NaN,
    //                                                               flcn::constants::NaN, flcn::constants::NaN)));


} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TEST_P(Mat3x2ColumnIndexingTests, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col]), "");
}


TEST_P(Mat3x2IndexingTests, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col)), "");
}


TEST_P(Mat3x2ColumnIndexingTests, OutOfBoundMutationTriggersAssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col] = flcn::Vec3<int>::zero()), "");
}


TEST_P(Mat3x2IndexingTests, OutOfBoundMutationTriggersAssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col) = 5), "");
}


TYPED_TEST(Mat3x2DivisionTests, DivideOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(this->_matrix / 0), ""); }


TYPED_TEST(Mat3x2DivisionTests, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(this->_matrix /= 0, ""); }

/** @} */

#endif
