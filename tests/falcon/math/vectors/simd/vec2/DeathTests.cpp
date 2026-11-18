/**
 * @file DeathTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 10, 2026
 *
 * @brief Verifies @ref flcn::simd::Vec2 assertions in Debug Mode.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "CommonSetup.h"
#include "Vec2TestSetup.h"


#ifdef ENABLE_DEBUG_TESTS

namespace
{
    /**************************************
     *             TEST SETUP             *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec2 accessor.
     */
    class SimdVec2IndexingTests: public testing::TestWithParam<size_t>
    {};
    INSTANTIATE_TEST_SUITE_P(Vec2InvalidIndices, SimdVec2IndexingTests, testing::Values(3, 4, 100));



    /**
     * @brief Test fixture for @ref Vec2 scalar division.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class SimdVec2ScalarDivisionTests: public testing::Test
    {
    protected:
        flcn::simd::Vec2<T> _vec;
        T _scalar;
        flcn::simd::Vec2<T> _expectedScaledVec;

        void SetUp() override
        {
            _vec               = { T(17), T(31) };
            _scalar            = T(13);
            _expectedScaledVec = { T(1.30769230769230769231), T(2.38461538461538461538) };
        }
    };
    TYPED_TEST_SUITE(SimdVec2ScalarDivisionTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref Vec2 normalization.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class SimdVec2NormalizationTests: public testing::Test
    {
        //NOLINTNEXTLINE
        using R = flcn::Magnitude<T>;

    protected:
        flcn::simd::Vec2<T> _vec;
        flcn::simd::Vec2<R> _expectedUnitVec;

        void SetUp() override
        {
            _vec             = { T(14), T(27) };
            _expectedUnitVec = { static_cast<R>(0.46031716445500037), static_cast<R>(0.8877545314489294) };
        }
    };
    TYPED_TEST_SUITE(SimdVec2NormalizationTests, SupportedFloatingPointTypes);



    /**
     * @brief Test fixture for @ref flcn::simd::Vec2 projection.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class SimdVec2ProjectionTests: public testing::Test
    {
    protected:
        flcn::simd::Vec2<T> _vec;
        flcn::simd::Vec2<T> _perpendicularVec;
        flcn::simd::Vec2<T> _ontoVec;
        flcn::simd::Vec2<T> _expectedProjection;

        void SetUp() override
        {
            _vec                = { T(4), T(0) };
            _perpendicularVec   = { T(0), T(11) };
            _ontoVec            = { T(2), T(0) };
            _expectedProjection = { T(4), T(0) };
        }
    };
    TYPED_TEST_SUITE(SimdVec2ProjectionTests, SupportedFloatingPointTypes);



    /**
     * @brief Test fixture for @ref flcn::simd::Vec2 rejection.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class SimdVec2RejectionTests: public testing::Test
    {
    protected:
        flcn::simd::Vec2<T> _vec;
        flcn::simd::Vec2<T> _parallelVec;
        flcn::simd::Vec2<T> _fromVec;
        flcn::simd::Vec2<T> _expectedRejection;

        void SetUp() override
        {
            _vec               = { T(4), T(0) };
            _parallelVec       = { T(6), T(0) };
            _fromVec           = { T(0), T(2) };
            _expectedRejection = { T(4), T(0) };
        }
    };
    TYPED_TEST_SUITE(SimdVec2RejectionTests, SupportedFloatingPointTypes);

} // namespace



TEST_P(SimdVec2IndexingTests, OutOfBoundAccess_TriggersAssertInDebugMode)
{
    const flcn::simd::Vec2 vec(1, 2);
    const auto index = GetParam();
    EXPECT_DEBUG_DEATH(vec[index], "");
}


TEST_P(SimdVec2IndexingTests, OutOfBoundMutationTriggers_AssertInDebugMode)
{
    flcn::simd::Vec2 vec(1, 2);
    const auto index = GetParam();
    EXPECT_DEBUG_DEATH(vec[index] = 2, "");
}


TYPED_TEST(SimdVec2ScalarDivisionTests, DivideOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec / 0), ""); }


TYPED_TEST(SimdVec2ScalarDivisionTests, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{
    [[maybe_unused]] flcn::simd::Vec2 newVec = this->_vec;
    EXPECT_DEBUG_DEATH(static_cast<void>(newVec /= 0), "");
}


TYPED_TEST(SimdVec2NormalizationTests, ZeroMagnitudeTriggersAssertInDebugMode)
{
    const flcn::simd::Vec2<TypeParam> zVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(zVec.normalize()), "");
}


TYPED_TEST(SimdVec2NormalizationTests, StaticWrapper_ZeroMagnitudeTriggersAssertInDebugMode)
{
    const flcn::simd::Vec2<TypeParam> zVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::simd::Vec2<TypeParam>::normalize(zVec)), "");
}


TYPED_TEST(SimdVec2ProjectionTests, ProjectionOntoZeroVectorTriggersAssertionInCallback)
{
    const flcn::simd::Vec2<TypeParam> zeroVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec.project(zeroVec)), "");
}


TYPED_TEST(SimdVec2ProjectionTests, StaticWrapper_ProjectionOntoZeroVectorTriggersAssertionInCallback)
{
    const flcn::simd::Vec2<TypeParam> zeroVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::simd::Vec2<TypeParam>::project(this->_vec, zeroVec)), "");
}

TYPED_TEST(SimdVec2RejectionTests, FromZeroVectorTriggersAssertionInCallback)
{
    const flcn::simd::Vec2<TypeParam> zeroVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec.reject(zeroVec)), "");
}


TYPED_TEST(SimdVec2RejectionTests, StaticWrapper_FromZeroVectorTriggersAssertionInCallback)
{
    const flcn::simd::Vec2<TypeParam> zeroVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::simd::Vec2<TypeParam>::reject(this->_vec, zeroVec)), "");
}

#endif
