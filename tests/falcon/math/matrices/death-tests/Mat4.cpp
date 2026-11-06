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

#include <falcon/math/matrices/Mat4.h>
#include <utility>



#ifdef ENABLE_DEBUG_TESTS

/**
 * @addtogroup T_FALCON_Mat4x4_Assertion
 * @{
 */

namespace
{
    flcn::Mat4 mat(1, 2, 3, 4);

    /**
     * @brief Test fixture for @ref flcn::Mat4 invalid (row, column) indices.
     */
    class Mat4IndexingTests: public testing::TestWithParam<std::pair<std::size_t, std::size_t>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat4OutOfBoundsRowColumnIndices, Mat4IndexingTests,
                             testing::Values(std::make_pair(5, 5), std::make_pair(4, 5), std::make_pair(5, 4),
                                             std::make_pair(100, 100)));


    /**
     * @brief Test fixture for @ref flcn::Mat4 invalid column indices.
     */
    class Mat4ColumnIndexingTests: public testing::TestWithParam<std::size_t>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat4OutOfBoundsColumnIndices, Mat4ColumnIndexingTests, testing::Values(5, 6, 100));



    /**
     * @brief Test fixture for @ref flcn::Mat4 Division.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat4DivisionTests: public testing::Test
    {
    protected:
        flcn::Mat4<T> _matrix;
        T _scalar;
        flcn::Mat4<T> _expectedMatrix;


        void SetUp() override
        {
            _matrix         = { { T(17), T(13), T(15), T(12) },
                                { T(11), T(16), T(35), T(101) },
                                { T(27), T(44), T(56), T(23) },
                                { T(5), T(6), T(11), T(31) } };
            _scalar         = T(7);
            _expectedMatrix = {
                { T(2.428571428571428), T(1.857142857142857), T(2.142857142857143), T(1.714285714285714) },
                { T(1.571428571428571), T(2.285714285714286), T(5.0), T(14.428571428571429) },
                { T(3.857142857142857), T(6.285714285714286), T(8.0), T(3.285714285714286) },
                { T(0.714285714285714), T(0.857142857142857), T(1.571428571428571), T(4.428571428571429) },
            };
        }
    };
    TYPED_TEST_SUITE(Mat4DivisionTests, SupportedArithmeticTypes);


    // TODO: Add tests
    /**
     * @brief Test fixture for @ref flcn::Mat4 Division with NaN elements.
     */
    // class NaNMat4DivisionTests: public testing::TestWithParam<flcn::Mat4<float>>
    // {};
    // INSTANTIATE_TEST_SUITE_P(Mat4InvalidDivision, NaNMat4DivisionTests,
    //                          ::testing::Values(flcn::Mat4<float>{ flcn::constants::NaN, 3.0f, 3.0f, 3.0f },
    //                                            flcn::Mat4<float>{ 3.0f, flcn::constants::NaN, 3.0f, 3.0f },
    //                                            flcn::Mat4<float>{ 3.0f, 3.0f, flcn::constants::NaN, 3.0f },
    //                                            flcn::Mat4<float>{ 3.0f, 3.0f, 3.0f, flcn::constants::NaN },
    //                                            flcn::Mat4<float>{ flcn::constants::NaN, flcn::constants::NaN,
    //                                                              flcn::constants::NaN, flcn::constants::NaN }));

    /** @brief Test fixture for calculating @ref flcn::Mat4 inverse with singular matrices. */
    class Mat4InverseSingularTests: public testing::TestWithParam<flcn::Mat4<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat4SingularMatrixInverse, Mat4InverseSingularTests,
        ::testing::Values(flcn::Mat4{ flcn::Vec4{ 1.0f, 2.0f, 3.0f, 4.0f }, flcn::Vec4{ 1.0f, 2.0f, 3.0f, 4.0f },
                                     flcn::Vec4{ 7.0f, 8.0f, 9.0f, 12.0f }, flcn::Vec4{ 1.0f, 85.0f, 19.0f, 12.0f } },
                          flcn::Mat4{ flcn::Vec4{ 1.0f, 1.0f, 3.0f, 4.0f }, flcn::Vec4{ 2.0f, 2.0f, 3.0f, 4.0f },
                                     flcn::Vec4{ 3.0f, 3.0f, 9.0f, 12.0f }, flcn::Vec4{ 4.0f, 4.0f, 31.6f, 2.0f } },
                          flcn::Mat4{ flcn::Vec4{ 0.0f, 0.0f, 0.0f, 0.0f }, flcn::Vec4{ 2.0f, 2.0f, 3.0f, 4.0f },
                                     flcn::Vec4{ 3.0f, 3.0f, 9.0f, 12.0f }, flcn::Vec4{ 4.0f, 4.0f, 31.6f, 2.0f } },
                          flcn::Mat4{ flcn::Vec4{ 0.0f, 1.0f, 3.0f, 4.0f }, flcn::Vec4{ 0.0f, 2.0f, 3.0f, 4.0f },
                                     flcn::Vec4{ 0.0f, 3.0f, 9.0f, 12.0f }, flcn::Vec4{ 0.0f, 4.0f, 31.6f, 2.0f } },
                          flcn::Mat4{ flcn::Vec4{ 1.0f, 2.0f, 3.0f, 4.0f }, flcn::Vec4{ 2.0f, 4.0f, 6.0f, 8.0f },
                                     flcn::Vec4{ 3.0f, 3.0f, 9.0f, 12.0f }, flcn::Vec4{ 4.0f, 4.0f, 31.6f, 2.0f } },
                          flcn::Mat4{ flcn::Vec4{ 1.0f, 2.0f, 3.0f, 4.0f }, flcn::Vec4{ 2.0f, 4.0f, 5.0f, 10.0f },
                                     flcn::Vec4{ 3.0f, 6.0f, 9.0f, 12.0f }, flcn::Vec4{ 4.0f, 8.0f, 31.6f, 2.0f } }));


    // TODO: Add
    // /** @brief Test fixture for @ref flcn::Mat4 inverse with NaN elements. */
    // class Mat4InverseNaNTests: public testing::TestWithParam<flcn::Mat4<float>>
    // {};
    // INSTANTIATE_TEST_SUITE_P(Mat4NaNMatrixInverse, Mat4InverseNaNTests,
    //                          ::testing::Values(flcn::Mat4<float>{ flcn::constants::NaN, 3.0f, 3.0f, 3.0f },
    //                                            flcn::Mat4<float>{ 3.0f, flcn::constants::NaN, 3.0f, 3.0f },
    //                                            flcn::Mat4<float>{ 3.0f, 3.0f, flcn::constants::NaN, 3.0f },
    //                                            flcn::Mat4<float>{ 3.0f, 3.0f, 3.0f, flcn::constants::NaN },
    //                                            flcn::Mat4<float>{ flcn::constants::NaN, flcn::constants::NaN,
    //                                                              flcn::constants::NaN, flcn::constants::NaN }));

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TEST_P(Mat4ColumnIndexingTests, OutOfBoundAccessTriggers_AssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col]), "");
}


TEST_P(Mat4IndexingTests, OutOfBoundAccessTriggers_AssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col)), "");
}


TEST_P(Mat4ColumnIndexingTests, OutOfBoundMutation_TriggersAssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col] = flcn::Vec4<int>::zero()), "");
}


TEST_P(Mat4IndexingTests, OutOfBoundMutationTriggers_AssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col) = 5), "");
}



TYPED_TEST(Mat4DivisionTests, DivideOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(this->_matrix / 0), ""); }


TYPED_TEST(Mat4DivisionTests, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(this->_matrix /= 0), ""); }



TEST_P(Mat4InverseSingularTests, TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    // Static cast is placed to suppress the no-discard warning
    EXPECT_DEBUG_DEATH(static_cast<void>(matrix.inverse()), "");
}


TEST_P(Mat4InverseSingularTests, StaticWrapper_TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    // Static cast is placed to suppress the no-discard warning
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::Mat4<float>::inverse(matrix)), "");
}

/** @} */

#endif
