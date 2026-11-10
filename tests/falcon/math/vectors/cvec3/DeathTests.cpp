/**
 * @file DeathTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 10, 2026
 *
 * @brief Verifies @ref flcn::CVec3 assertions in Debug Mode.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#ifdef ENABLE_DEBUG_TESTS
    #include "CommonSetup.h"

    #include <falcon/math/vectors/CVec3.h>
    #include <gtest/gtest.h>

namespace
{
    /**************************************
     *             TEST SETUP             *
     **************************************/

    /**
     * @brief Test fixture for @ref CVec3 accessor.
     */
    class CVec3IndexingTests: public testing::TestWithParam<std::size_t>
    {};
    INSTANTIATE_TEST_SUITE_P(CVec3InvalidIndices, CVec3IndexingTests, testing::Values(4, 5, 100));



    /**
     * @brief Test fixture for @ref CVec3 scalar division.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class CVec3ScalarDivisionTests: public testing::Test
    {
    protected:
        flcn::CVec3<T> _vec;
        T _scalar;
        flcn::CVec3<T> _expectedScaledVec;

        void SetUp() override
        {
            _vec               = { T(17), T(31), T(5) };
        }
    };
    TYPED_TEST_SUITE(CVec3ScalarDivisionTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref CVec3 normalization.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class CVec3NormalizationTests: public testing::Test
    {
        using R = flcn::Magnitude<T>;

    protected:
        flcn::CVec3<T> _vec;

        void SetUp() override
        {
            _vec             = { T(14), T(27), T(0) };
        }
    };
    TYPED_TEST_SUITE(CVec3NormalizationTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::CVec3 projection.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class CVec3ProjectionTests: public testing::Test
    {
    protected:
        flcn::CVec3<T> _vec;
        flcn::CVec3<T> _perpendicularVec;
        flcn::CVec3<T> _ontoVec;
        flcn::CVec3<T> _expectedProjection;

        void SetUp() override
        {
            _vec                = { T(4), T(0) , T(1)};
            _perpendicularVec   = { T(0), T(11), T(1) };
            _ontoVec            = { T(2), T(0) , T(1)};
            _expectedProjection = { T(4), T(0) , T(1)};
        }
    };
    TYPED_TEST_SUITE(CVec3ProjectionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::CVec3 rejection.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class CVec3RejectionTests: public testing::Test
    {
    protected:
        flcn::CVec3<T> _vec;
        flcn::CVec3<T> _parallelVec;
        flcn::CVec3<T> _fromVec;
        flcn::CVec3<T> _expectedRejection;

        void SetUp() override
        {
            _vec               = { T(4), T(0), T(5) };
            _parallelVec       = { T(6), T(0), T(5) };
            _fromVec           = { T(0), T(2), T(5) };
            _expectedRejection = { T(4), T(0), T(5) };
        }
    };
    TYPED_TEST_SUITE(CVec3RejectionTests, SupportedArithmeticTypes);

} // namespace



TEST_P(CVec3IndexingTests, OutOfBoundAccess_TriggersAssertInDebugMode)
{
    const flcn::CVec3 vec(1, 2, 3);
    const auto index = GetParam();
    EXPECT_DEBUG_DEATH(vec[index], "");
}


TEST_P(CVec3IndexingTests, OutOfBoundMutationTriggers_AssertInDebugMode)
{
    flcn::CVec3 vec(1, 2, 3);
    const auto index = GetParam();
    EXPECT_DEBUG_DEATH(vec[index] = 2, "");
}


TYPED_TEST(CVec3ScalarDivisionTests, DivideOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec / 0), ""); }


TYPED_TEST(CVec3ScalarDivisionTests, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{
    [[maybe_unused]] flcn::CVec3 newVec = this->_vec;
    EXPECT_DEBUG_DEATH(static_cast<void>(newVec /= 0), "");
}


TYPED_TEST(CVec3NormalizationTests, ZeroMagnitudeTriggersAssertInDebugMode)
{
    const flcn::CVec3<TypeParam> zVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(zVec.normalize()), "");
}


TYPED_TEST(CVec3NormalizationTests, StaticWrapper_ZeroMagnitudeTriggersAssertInDebugMode)
{
    const flcn::CVec3<TypeParam> zVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::CVec3<TypeParam>::normalize(zVec)), "");
}


TYPED_TEST(CVec3ProjectionTests, ProjectionOntoZeroVectorTriggersAssertionInCallback)
{
    const flcn::CVec3<TypeParam> zeroVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec.project(zeroVec)), "");
}


TYPED_TEST(CVec3ProjectionTests, StaticWrapper_ProjectionOntoZeroVectorTriggersAssertionInCallback)
{
    const flcn::CVec3<TypeParam> zeroVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::CVec3<TypeParam>::project(this->_vec, zeroVec)), "");
}

TYPED_TEST(CVec3RejectionTests, FromZeroVectorTriggersAssertionInCallback)
{
    const flcn::CVec3<TypeParam> zeroVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec.reject(zeroVec)), "");
}


TYPED_TEST(CVec3RejectionTests, StaticWrapper_FromZeroVectorTriggersAssertionInCallback)
{
    const flcn::CVec3<TypeParam> zeroVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::CVec3<TypeParam>::reject(this->_vec, zeroVec)), "");
}

#endif
