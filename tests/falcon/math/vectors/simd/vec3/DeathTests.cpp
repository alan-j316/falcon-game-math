/**
 * @file DeathTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 10, 2026
 *
 * @brief Verifies @ref flcn::simd::Vec3 assertions in Debug Mode.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */
// TODO: Add back
// #ifdef ENABLE_DEBUG_TESTS
//     #include "CommonSetup.h"
//     #include "NormalizationTestFixture.h"
//
//     #include <falcon/math/vectors/Vec3.h>
//     #include <gtest/gtest.h>
//
// namespace
// {
//     /**************************************
//      *             TEST SETUP             *
//      **************************************/
//
//     /**
//      * @brief Test fixture for @ref Vec3 accessor.
//      */
//     class SimdVec3IndexingTests: public testing::TestWithParam<std::size_t>
//     {};
//     INSTANTIATE_TEST_SUITE_P(Vec3InvalidIndices, Vec3IndexingTests, testing::Values(4, 5, 100));
//
//
//
//     /**
//      * @brief Test fixture for @ref Vec3 scalar division.
//      * @tparam T The scalar type (int, float, double...) of the vector components.
//      */
//     template <typename T>
//     class SimdVec3ScalarDivisionTests: public testing::Test
//     {
//     protected:
//         flcn::simd::Vec3<T> _vec;
//         T _scalar;
//         flcn::simd::Vec3<T> _expectedScaledVec;
//
//         void SetUp() override
//         {
//             _vec               = { T(17), T(31), T(5) };
//         }
//     };
//     TYPED_TEST_SUITE(SimdVec3ScalarDivisionTests, SupportedArithmeticTypes);
//

//     /**
//      * @brief Test fixture for @ref flcn::simd::Vec3 projection.
//      *
//      * @tparam T The scalar type (e.g., float, double) used for the vectors.
//      */
//     template <typename T>
//     class SimdVec3ProjectionTests: public testing::Test
//     {
//     protected:
//         flcn::simd::Vec3<T> _vec;
//         flcn::simd::Vec3<T> _perpendicularVec;
//         flcn::simd::Vec3<T> _ontoVec;
//         flcn::simd::Vec3<T> _expectedProjection;
//
//         void SetUp() override
//         {
//             _vec                = { T(4), T(0) , T(1)};
//             _perpendicularVec   = { T(0), T(11), T(1) };
//             _ontoVec            = { T(2), T(0) , T(1)};
//             _expectedProjection = { T(4), T(0) , T(1)};
//         }
//     };
//     TYPED_TEST_SUITE(SimdVec3ProjectionTests, SupportedArithmeticTypes);
//
//
//
//     /**
//      * @brief Test fixture for @ref flcn::simd::Vec3 rejection.
//      *
//      * @tparam T The scalar type (e.g., float, double) used for the vectors.
//      */
//     template <typename T>
//     class SimdVec3RejectionTests: public testing::Test
//     {
//     protected:
//         flcn::simd::Vec3<T> _vec;
//         flcn::simd::Vec3<T> _parallelVec;
//         flcn::simd::Vec3<T> _fromVec;
//         flcn::simd::Vec3<T> _expectedRejection;
//
//         void SetUp() override
//         {
//             _vec               = { T(4), T(0), T(5) };
//             _parallelVec       = { T(6), T(0), T(5) };
//             _fromVec           = { T(0), T(2), T(5) };
//             _expectedRejection = { T(4), T(0), T(5) };
//         }
//     };
//     TYPED_TEST_SUITE(SimdVec3RejectionTests, SupportedArithmeticTypes);
//
// } // namespace
//
//
//
// TEST_P(SimdVec3IndexingTests, OutOfBoundAccess_TriggersAssertInDebugMode)
// {
//     const flcn::simd::Vec3 vec(1, 2, 3);
//     const auto index = GetParam();
//     EXPECT_DEBUG_DEATH(vec[index], "");
// }
//
//
// TEST_P(SimdVec3IndexingTests, OutOfBoundMutationTriggers_AssertInDebugMode)
// {
//     flcn::simd::Vec3 vec(1, 2, 3);
//     const auto index = GetParam();
//     EXPECT_DEBUG_DEATH(vec[index] = 2, "");
// }
//
//
// TYPED_TEST(SimdVec3ScalarDivisionTests, DivideOperator_ByZeroTriggersAssertInDebugMode)
// { EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec / 0), ""); }
//
//
// TYPED_TEST(SimdVec3ScalarDivisionTests, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
// {
//     [[maybe_unused]] flcn::simd::Vec3 newVec = this->_vec;
//     EXPECT_DEBUG_DEATH(static_cast<void>(newVec /= 0), "");
// }
//
//
// TYPED_TEST(SimdVec3NormalizationTests, ZeroMagnitudeTriggersAssertInDebugMode)
// {
//     const flcn::simd::Vec3<TypeParam> zVec(0, 0, 0);
//     EXPECT_DEBUG_DEATH(static_cast<void>(zVec.normalize()), "");
// }
//

//
// TYPED_TEST(SimdVec3ProjectionTests, ProjectionOntoZeroVectorTriggersAssertionInCallback)
// {
//     const flcn::simd::Vec3<TypeParam> zeroVec(0, 0, 0);
//     EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec.project(zeroVec)), "");
// }
//
//
// TYPED_TEST(SimdVec3ProjectionTests, StaticWrapper_ProjectionOntoZeroVectorTriggersAssertionInCallback)
// {
//     const flcn::simd::Vec3<TypeParam> zeroVec(0, 0, 0);
//     EXPECT_DEBUG_DEATH(static_cast<void>(flcn::simd::Vec3<TypeParam>::project(this->_vec, zeroVec)), "");
// }
//
// TYPED_TEST(SimdVec3RejectionTests, FromZeroVectorTriggersAssertionInCallback)
// {
//     const flcn::simd::Vec3<TypeParam> zeroVec(0, 0, 0);
//     EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec.reject(zeroVec)), "");
// }
//
//
// TYPED_TEST(SimdVec3RejectionTests, StaticWrapper_FromZeroVectorTriggersAssertionInCallback)
// {
//     const flcn::simd::Vec3<TypeParam> zeroVec(0, 0, 0);
//     EXPECT_DEBUG_DEATH(static_cast<void>(flcn::simd::Vec3<TypeParam>::reject(this->_vec, zeroVec)), "");
// }
//
// #endif
