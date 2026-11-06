/**
 * @file Transform4.cpp
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

#include <falcon/math/matrices/Transform4.h>
#include <utility>

/**
 * @addtogroup T_FALCON_Mat2x4_Assertion
 * @{
 */

#ifdef ENABLE_DEBUG_TESTS

namespace
{
    /// @brief Parameterized Test Fixture for @ref flcn::Transform4 element access/mutation out-of-bounds.
    class Transform4IndexingTests: public testing::TestWithParam<std::pair<std::size_t, std::size_t>>
    {
    public:
        flcn::Transform4<int> transform{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    };
    INSTANTIATE_TEST_SUITE_P(Transform4ElementAccessOutOfBoundsTests, Transform4IndexingTests,
                             testing::Values(std::make_pair(3, 3), std::make_pair(3, 4), std::make_pair(4, 3),
                                             std::make_pair(100, 100)));


    /// @brief Parameterized Test Fixture for @ref flcn::Transform4 vector access/mutation out-of-bounds.
    class Transform4VectorIndexingTests: public testing::TestWithParam<std::size_t>
    {
    public:
        flcn::Transform4<int> transform{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    };
    INSTANTIATE_TEST_SUITE_P(Transform4VectorAccessOutOfBoundsTests, Transform4VectorIndexingTests,
                             testing::Values(5, 6, 100));


    /**
     * @brief Parameterized Test fixture for @ref flcn::Transform4 singular matrix inverse.
     */
    class Transform4InverseSingularTests: public testing::TestWithParam<flcn::Transform4<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Transform4InverseTestSuite, Transform4InverseSingularTests,
        ::testing::Values(flcn::Transform4{ flcn::Vec3{ 1.0f, 2.0f, 3.0f }, flcn::Vec3{ 1.0f, 2.0f, 3.0f },
                                           flcn::Vec3{ 7.0f, 8.0f, 9.0f }, flcn::Point3{ 1.0f, 85.0f, 19.0f } },
                          flcn::Transform4{ flcn::Vec3{ 1.0f, 1.0f, 3.0f }, flcn::Vec3{ 2.0f, 2.0f, 3.0f },
                                           flcn::Vec3{ 3.0f, 3.0f, 9.0f }, flcn::Point3{ 4.0f, 4.0f, 31.6f } },
                          flcn::Transform4{ flcn::Vec3{ 0.0f, 0.0f, 0.0f }, flcn::Vec3{ 2.0f, 2.0f, 3.0f },
                                           flcn::Vec3{ 3.0f, 3.0f, 9.0f }, flcn::Point3{ 4.0f, 4.0f, 31.6f } },
                          flcn::Transform4{ flcn::Vec3{ 0.0f, 1.0f, 3.0f }, flcn::Vec3{ 0.0f, 2.0f, 3.0f },
                                           flcn::Vec3{ 0.0f, 3.0f, 9.0f }, flcn::Point3{ 0.0f, 4.0f, 31.6f } },
                          flcn::Transform4{ flcn::Vec3{ 1.0f, 2.0f, 3.0f }, flcn::Vec3{ 2.0f, 4.0f, 6.0f },
                                           flcn::Vec3{ 3.0f, 3.0f, 9.0f }, flcn::Point3{ 4.0f, 4.0f, 31.6f } },
                          flcn::Transform4{ flcn::Vec3{ 1.0f, 2.0f, 3.0f }, flcn::Vec3{ 2.0f, 4.0f, 5.0f },
                                           flcn::Vec3{ 3.0f, 6.0f, 9.0f }, flcn::Point3{ 4.0f, 8.0f, 31.6f } }));


} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

/** @test Verify that @ref flcn::Transform4 out-of-bounds column access triggers assert in debug mode. */
TEST_P(Transform4VectorIndexingTests, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(transform[col]), "");
}


/** @test Verify that @ref flcn::Transform4 out-of-bounds row, column access triggers assert in debug mode. */
TEST_P(Transform4IndexingTests, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(transform(row, col)), "");
}

/** @test Verify that @ref flcn::Transform4 out-of-bounds column mutation triggers assert in debug mode. */
TEST_P(Transform4VectorIndexingTests, OutOfBoundMutationTriggersAssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(transform[col] = flcn::Vec3<int>::zero()), "");
}


/** @test Verify that @ref flcn::Transform4 out-of-bounds row, column mutation triggers assert in debug mode. */
TEST_P(Transform4IndexingTests, OutOfBoundMutationTriggersAssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(transform(row, col) = 5), "");
}

TEST_P(Transform4InverseSingularTests, TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(matrix.inverse()), "");
}


TEST_P(Transform4InverseSingularTests, StaticWrapper_TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::Transform4<float>::inverse(matrix)), "");
}
#endif

/** @} */
