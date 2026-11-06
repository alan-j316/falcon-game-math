/**
 * @file DeathTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 10, 2026
 *
 * @brief Verifies @ref flcn::CVec2 assertions in Debug Mode.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#ifdef ENABLE_DEBUG_TESTS
    #include "CommonSetup.h"

    #include <falcon/math/vectors/CVec2.h>
    #include <gtest/gtest.h>

namespace
{
    /**************************************
     *             TEST SETUP             *
     **************************************/

    /**
     * @brief Test fixture for @ref CVec2 accessor.
     */
    class CVec2IndexingTests: public testing::TestWithParam<std::size_t>
    {};
    INSTANTIATE_TEST_SUITE_P(CVec2InvalidIndices, CVec2IndexingTests, testing::Values(3, 4, 100));



    /**
     * @brief Test fixture for @ref CVec2 scalar division.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class CVec2ScalarDivisionTests: public testing::Test
    {
    protected:
        flcn::CVec2<T> _vec;
        T _scalar;
        flcn::CVec2<T> _expectedScaledVec;

        void SetUp() override
        {
            _vec               = { T(17), T(31) };
            _scalar            = T(13);
            _expectedScaledVec = { T(1.30769230769230769231), T(2.38461538461538461538) };
        }
    };
    TYPED_TEST_SUITE(CVec2ScalarDivisionTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref CVec2 normalization.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class CVec2NormalizationTests: public testing::Test
    {
        using R = flcn::Magnitude<T>;

    protected:
        flcn::CVec2<T> _vec;
        flcn::CVec2<R> _expectedUnitVec;

        void SetUp() override
        {
            _vec             = { T(14), T(27) };
            _expectedUnitVec = { static_cast<R>(0.46031716445500037), static_cast<R>(0.8877545314489294) };
        }
    };
    TYPED_TEST_SUITE(CVec2NormalizationTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::CVec2 projection.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class CVec2ProjectionTests: public testing::Test
    {
    protected:
        flcn::CVec2<T> _vec;
        flcn::CVec2<T> _perpendicularVec;
        flcn::CVec2<T> _ontoVec;
        flcn::CVec2<T> _expectedProjection;

        void SetUp() override
        {
            _vec                = { T(4), T(0) };
            _perpendicularVec   = { T(0), T(11) };
            _ontoVec            = { T(2), T(0) };
            _expectedProjection = { T(4), T(0) };
        }
    };
    TYPED_TEST_SUITE(CVec2ProjectionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::CVec2 rejection.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class CVec2RejectionTests: public testing::Test
    {
    protected:
        flcn::CVec2<T> _vec;
        flcn::CVec2<T> _parallelVec;
        flcn::CVec2<T> _fromVec;
        flcn::CVec2<T> _expectedRejection;

        void SetUp() override
        {
            _vec               = { T(4), T(0) };
            _parallelVec       = { T(6), T(0) };
            _fromVec           = { T(0), T(2) };
            _expectedRejection = { T(4), T(0) };
        }
    };
    TYPED_TEST_SUITE(CVec2RejectionTests, SupportedArithmeticTypes);

} // namespace



TEST_P(CVec2IndexingTests, OutOfBoundAccess_TriggersAssertInDebugMode)
{
    const flcn::CVec2 vec(1, 2);
    const auto index = GetParam();
    EXPECT_DEBUG_DEATH(vec[index], "");
}


TEST_P(CVec2IndexingTests, OutOfBoundMutationTriggers_AssertInDebugMode)
{
    flcn::CVec2 vec(1, 2);
    const auto index = GetParam();
    EXPECT_DEBUG_DEATH(vec[index] = 2, "");
}


TYPED_TEST(CVec2ScalarDivisionTests, DivideOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec / 0), ""); }


TYPED_TEST(CVec2ScalarDivisionTests, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{
    [[maybe_unused]] flcn::CVec2 newVec = this->_vec;
    EXPECT_DEBUG_DEATH(static_cast<void>(newVec /= 0), "");
}


TYPED_TEST(CVec2NormalizationTests, ZeroMagnitudeTriggersAssertInDebugMode)
{
    const flcn::CVec2<TypeParam> zVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(zVec.normalize()), "");
}


TYPED_TEST(CVec2NormalizationTests, StaticWrapper_ZeroMagnitudeTriggersAssertInDebugMode)
{
    const flcn::CVec2<TypeParam> zVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::CVec2<TypeParam>::normalize(zVec)), "");
}


TYPED_TEST(CVec2ProjectionTests, ProjectionOntoZeroVectorTriggersAssertionInCallback)
{
    const flcn::CVec2<TypeParam> zeroVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec.project(zeroVec)), "");
}


TYPED_TEST(CVec2ProjectionTests, StaticWrapper_ProjectionOntoZeroVectorTriggersAssertionInCallback)
{
    const flcn::CVec2<TypeParam> zeroVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::CVec2<TypeParam>::project(this->_vec, zeroVec)), "");
}

TYPED_TEST(CVec2RejectionTests, FromZeroVectorTriggersAssertionInCallback)
{
    const flcn::CVec2<TypeParam> zeroVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec.reject(zeroVec)), "");
}


TYPED_TEST(CVec2RejectionTests, StaticWrapper_FromZeroVectorTriggersAssertionInCallback)
{
    const flcn::CVec2<TypeParam> zeroVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::CVec2<TypeParam>::reject(this->_vec, zeroVec)), "");
}

#endif
