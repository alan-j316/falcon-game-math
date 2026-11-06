/**
 * @file Mat2.cpp
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

#include <falcon/math/matrices/Mat2.h>
#include <utility>


#ifdef ENABLE_DEBUG_TESTS

/**
 * @addtogroup T_FALCON_Mat2x2_Assertion
 * @{
 */

namespace
{
    flcn::Mat2 mat(1, 2);

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Mat2 invalid (row, column) indices.
     */
    class Mat2IndexingTests: public testing::TestWithParam<std::pair<std::size_t, std::size_t>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat2OutOfBoundsRowColumnIndices, Mat2IndexingTests,
                             testing::Values(std::make_pair(3, 3), std::make_pair(2, 3), std::make_pair(3, 2),
                                             std::make_pair(100, 100)));


    /**
     * @brief Test fixture for @ref flcn::Mat2 invalid column indexing.
     */
    class Mat2ColumnIndexingTests: public testing::TestWithParam<std::size_t>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat2OutOfBoundsColumnIndices, Mat2ColumnIndexingTests, testing::Values(3, 4, 100));



    /**
     * @brief Test fixture for @ref flcn::Mat2 Division.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2DivisionTests: public testing::Test
    {
    protected:
        flcn::Mat2<T> _matrix;
        T _scalar;
        flcn::Mat2<T> _expectedMatrix;

        void SetUp() override
        {
            _matrix         = { flcn::CVec2<T>{ 7, 3 }, flcn::CVec2<T>{ 1, 6 } };
            _scalar         = T(3);
            _expectedMatrix = { flcn::CVec2{ T(2.333333333333333), T(1) }, flcn::CVec2{ T(0.3333333333333333), T(2) } };
        }
    };
    TYPED_TEST_SUITE(Mat2DivisionTests, SupportedArithmeticTypes);




    /** @brief Test fixture for calculating @ref flcn::Mat2 inverse with singular matrices. */
    class Mat2InverseSingularTests: public testing::TestWithParam<flcn::Mat2<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat2SingularMatrixInverse, Mat2InverseSingularTests,
                             ::testing::Values(flcn::Mat2{ flcn::CVec2{ 1.0f, 2.0f }, flcn::CVec2{ 1.0f, 2.0f } },
                                               flcn::Mat2{ flcn::CVec2{ 2.0f, 2.0f }, flcn::CVec2{ 2.0f, 2.0f } },
                                               flcn::Mat2{ flcn::CVec2{ 3.0f, 2.0f }, flcn::CVec2{ 6.0f, 4.0f } },
                                               flcn::Mat2{ flcn::CVec2{ 0.0f, 0.0f }, flcn::CVec2{ 4.0f, 5.0f } },
                                               flcn::Mat2{ flcn::CVec2{ 0.0f, 3.0f }, flcn::CVec2{ 0.0f, 5.0f } }));



    /** @brief Test fixture for @ref flcn::Mat2 inverse with NaN elements. */
    class Mat2InverseNaNTests: public testing::TestWithParam<flcn::Mat2<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat2NaNMatrixInverse, Mat2InverseNaNTests,
                             ::testing::Values(flcn::Mat2<float>(flcn::constants::NaN, 3.0f, 3.0f, 3.0f),
                                               flcn::Mat2<float>(3.0f, flcn::constants::NaN, 3.0f, 3.0f),
                                               flcn::Mat2<float>(3.0f, 3.0f, flcn::constants::NaN, 3.0f),
                                               flcn::Mat2<float>(3.0f, 3.0f, 3.0f, flcn::constants::NaN),
                                               flcn::Mat2<float>(flcn::constants::NaN, flcn::constants::NaN,
                                                                flcn::constants::NaN, flcn::constants::NaN)));
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TEST_P(Mat2ColumnIndexingTests, OutOfBoundAccess_TriggersAssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col]), "");
}

TEST_P(Mat2IndexingTests, OutOfBoundAccess_TriggersAssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col)), "");
}



TEST_P(Mat2ColumnIndexingTests, OutOfBoundMutation_TriggersAssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col] = flcn::CVec2<int>::zero()), "");
}

TEST_P(Mat2IndexingTests, OutOfBoundMutationTriggersAssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col) = 5), "");
}



TYPED_TEST(Mat2DivisionTests, DivideOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(this->_matrix / 0), ""); }

TYPED_TEST(Mat2DivisionTests, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(this->_matrix /= 0, ""); }



TEST_P(Mat2InverseSingularTests, Inverse_TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    // Static cast is placed to suppress the no-discard warning
    EXPECT_DEBUG_DEATH(static_cast<void>(matrix.inverse()), "");
}

TEST_P(Mat2InverseSingularTests, StaticWrapper_Inverse_TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    // Static cast is placed to suppress the no-discard warning
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::Mat2<float>::inverse(matrix)), "");
}

TEST_P(Mat2InverseNaNTests, Inverse_TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    // Static cast is placed to suppress the no-discard warning
    EXPECT_DEBUG_DEATH(static_cast<void>(matrix.inverse()), "");
}

TEST_P(Mat2InverseNaNTests, StaticWrapper_Inverse_TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    // Static cast is placed to suppress the no-discard warning
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::Mat2<float>::inverse(matrix)), "");
}

/** @} */

#endif

