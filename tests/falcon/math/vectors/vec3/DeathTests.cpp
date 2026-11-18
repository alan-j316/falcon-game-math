/**
 * @file DeathTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 10, 2026
 *
 * @brief Verifies @ref flcn::Vec3 assertions in Debug Mode.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#ifdef ENABLE_DEBUG_TESTS
    #include "CommonSetup.h"

    #include <falcon/math/vectors/Vec3.h>
    #include <gtest/gtest.h>

namespace
{
    /**************************************
     *             TEST SETUP             *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec3 accessor.
     */
    class Vec3IndexingTests: public testing::TestWithParam<std::size_t>
    {};
    INSTANTIATE_TEST_SUITE_P(Vec3InvalidIndices, Vec3IndexingTests, testing::Values(4, 5, 100));



    /**
     * @brief Test fixture for @ref Vec3 scalar division.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec3ScalarDivisionTests: public testing::Test
    {
    protected:
        flcn::Vec3<T> _vec;
        T _scalar;
        flcn::Vec3<T> _expectedScaledVec;

        void SetUp() override
        {
            _vec               = { T(17), T(31), T(5) };
        }
    };
    TYPED_TEST_SUITE(Vec3ScalarDivisionTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref Vec3 normalization.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec3NormalizationTests: public testing::Test
    {
        using R = flcn::Magnitude<T>;

    protected:
        flcn::Vec3<T> _vec;

        void SetUp() override
        {
            _vec             = { T(14), T(27), T(0) };
        }
    };
    TYPED_TEST_SUITE(Vec3NormalizationTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::Vec3 projection.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class Vec3ProjectionTests: public testing::Test
    {
    protected:
        flcn::Vec3<T> _vec;
        flcn::Vec3<T> _perpendicularVec;
        flcn::Vec3<T> _ontoVec;
        flcn::Vec3<T> _expectedProjection;

        void SetUp() override
        {
            _vec                = { T(4), T(0) , T(1)};
            _perpendicularVec   = { T(0), T(11), T(1) };
            _ontoVec            = { T(2), T(0) , T(1)};
            _expectedProjection = { T(4), T(0) , T(1)};
        }
    };
    TYPED_TEST_SUITE(Vec3ProjectionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::Vec3 rejection.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class Vec3RejectionTests: public testing::Test
    {
    protected:
        flcn::Vec3<T> _vec;
        flcn::Vec3<T> _parallelVec;
        flcn::Vec3<T> _fromVec;
        flcn::Vec3<T> _expectedRejection;

        void SetUp() override
        {
            _vec               = { T(4), T(0), T(5) };
            _parallelVec       = { T(6), T(0), T(5) };
            _fromVec           = { T(0), T(2), T(5) };
            _expectedRejection = { T(4), T(0), T(5) };
        }
    };
    TYPED_TEST_SUITE(Vec3RejectionTests, SupportedArithmeticTypes);

} // namespace



TEST_P(Vec3IndexingTests, OutOfBoundAccess_TriggersAssertInDebugMode)
{
    const flcn::Vec3 vec(1, 2, 3);
    const auto index = GetParam();
    EXPECT_DEBUG_DEATH(vec[index], "");
}


TEST_P(Vec3IndexingTests, OutOfBoundMutationTriggers_AssertInDebugMode)
{
    flcn::Vec3 vec(1, 2, 3);
    const auto index = GetParam();
    EXPECT_DEBUG_DEATH(vec[index] = 2, "");
}


TYPED_TEST(Vec3ScalarDivisionTests, DivideOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec / 0), ""); }


TYPED_TEST(Vec3ScalarDivisionTests, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{
    [[maybe_unused]] flcn::Vec3 newVec = this->_vec;
    EXPECT_DEBUG_DEATH(static_cast<void>(newVec /= 0), "");
}


TYPED_TEST(Vec3NormalizationTests, ZeroMagnitudeTriggersAssertInDebugMode)
{
    const flcn::Vec3<TypeParam> zVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(zVec.normalize()), "");
}


TYPED_TEST(Vec3NormalizationTests, StaticWrapper_ZeroMagnitudeTriggersAssertInDebugMode)
{
    const flcn::Vec3<TypeParam> zVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::Vec3<TypeParam>::normalize(zVec)), "");
}


TYPED_TEST(Vec3ProjectionTests, ProjectionOntoZeroVectorTriggersAssertionInCallback)
{
    const flcn::Vec3<TypeParam> zeroVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec.project(zeroVec)), "");
}


TYPED_TEST(Vec3ProjectionTests, StaticWrapper_ProjectionOntoZeroVectorTriggersAssertionInCallback)
{
    const flcn::Vec3<TypeParam> zeroVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::Vec3<TypeParam>::project(this->_vec, zeroVec)), "");
}

TYPED_TEST(Vec3RejectionTests, FromZeroVectorTriggersAssertionInCallback)
{
    const flcn::Vec3<TypeParam> zeroVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec.reject(zeroVec)), "");
}


TYPED_TEST(Vec3RejectionTests, StaticWrapper_FromZeroVectorTriggersAssertionInCallback)
{
    const flcn::Vec3<TypeParam> zeroVec(0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::Vec3<TypeParam>::reject(this->_vec, zeroVec)), "");
}

#endif
