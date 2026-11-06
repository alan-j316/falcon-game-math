/**
 * @file DeathTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 10, 2026
 *
 * @brief Verifies @ref flcn::Vec4 assertions in Debug Mode.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#ifdef ENABLE_DEBUG_TESTS
    #include "CommonSetup.h"

    #include <falcon/math/vectors/Vec4.h>
    #include <gtest/gtest.h>

namespace
{
    /**************************************
     *             TEST SETUP             *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec4 accessor.
     */
    class Vec4IndexingTests: public testing::TestWithParam<std::size_t>
    {};
    INSTANTIATE_TEST_SUITE_P(Vec4InvalidIndices, Vec4IndexingTests, testing::Values(5, 6, 100));



    /**
     * @brief Test fixture for @ref Vec4 scalar division.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec4ScalarDivisionTests: public testing::Test
    {
    protected:
        flcn::Vec4<T> _vec;
        T _scalar;
        flcn::Vec4<T> _expectedScaledVec;

        void SetUp() override { _vec = { T(17), T(31), T(5), T(10) }; }
    };
    TYPED_TEST_SUITE(Vec4ScalarDivisionTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref Vec4 normalization.
     * @tparam T The scalar type (int, float, double...) of the vector components.
     */
    template <typename T>
    class Vec4NormalizationTests: public testing::Test
    {
        using R = flcn::Magnitude<T>;

    protected:
        flcn::Vec4<T> _vec;

        void SetUp() override { _vec = { T(14), T(27), T(0), T(0) }; }
    };
    TYPED_TEST_SUITE(Vec4NormalizationTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::Vec4 projection.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class Vec4ProjectionTests: public testing::Test
    {
    protected:
        flcn::Vec4<T> _vec;
        flcn::Vec4<T> _perpendicularVec;
        flcn::Vec4<T> _ontoVec;
        flcn::Vec4<T> _expectedProjection;

        void SetUp() override
        {
            _vec                = { T(4), T(0), T(1), T(0) };
            _perpendicularVec   = { T(0), T(11), T(1), T(0) };
            _ontoVec            = { T(2), T(0), T(1), T(0) };
            _expectedProjection = { T(4), T(0), T(1), T(0) };
        }
    };
    TYPED_TEST_SUITE(Vec4ProjectionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref flcn::Vec4 rejection.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class Vec4RejectionTests: public testing::Test
    {
    protected:
        flcn::Vec4<T> _vec;
        flcn::Vec4<T> _parallelVec;
        flcn::Vec4<T> _fromVec;
        flcn::Vec4<T> _expectedRejection;

        void SetUp() override
        {
            _vec               = { T(4), T(0), T(5), T(0) };
            _parallelVec       = { T(6), T(0), T(5), T(0) };
            _fromVec           = { T(0), T(2), T(5), T(0) };
            _expectedRejection = { T(4), T(0), T(5), T(0) };
        }
    };
    TYPED_TEST_SUITE(Vec4RejectionTests, SupportedArithmeticTypes);

} // namespace



TEST_P(Vec4IndexingTests, OutOfBoundAccess_TriggersAssertInDebugMode)
{
    const flcn::Vec4 vec(1, 2, 3,4);
    const auto index = GetParam();
    EXPECT_DEBUG_DEATH(vec[index], "");
}


TEST_P(Vec4IndexingTests, OutOfBoundMutationTriggers_AssertInDebugMode)
{
    flcn::Vec4 vec(1, 2, 3,4);
    const auto index = GetParam();
    EXPECT_DEBUG_DEATH(vec[index] = 2, "");
}


TYPED_TEST(Vec4ScalarDivisionTests, DivideOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec / 0), ""); }


TYPED_TEST(Vec4ScalarDivisionTests, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{
    [[maybe_unused]] flcn::Vec4 newVec = this->_vec;
    EXPECT_DEBUG_DEATH(static_cast<void>(newVec /= 0), "");
}


TYPED_TEST(Vec4NormalizationTests, ZeroMagnitudeTriggersAssertInDebugMode)
{
    const flcn::Vec4<TypeParam> zVec(0, 0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(zVec.normalize()), "");
}


TYPED_TEST(Vec4NormalizationTests, StaticWrapper_ZeroMagnitudeTriggersAssertInDebugMode)
{
    const flcn::Vec4<TypeParam> zVec(0, 0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::Vec4<TypeParam>::normalize(zVec)), "");
}


TYPED_TEST(Vec4ProjectionTests, ProjectionOntoZeroVectorTriggersAssertionInCallback)
{
    const flcn::Vec4<TypeParam> zeroVec(0, 0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec.project(zeroVec)), "");
}


TYPED_TEST(Vec4ProjectionTests, StaticWrapper_ProjectionOntoZeroVectorTriggersAssertionInCallback)
{
    const flcn::Vec4<TypeParam> zeroVec(0, 0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::Vec4<TypeParam>::project(this->_vec, zeroVec)), "");
}

TYPED_TEST(Vec4RejectionTests, FromZeroVectorTriggersAssertionInCallback)
{
    const flcn::Vec4<TypeParam> zeroVec(0, 0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec.reject(zeroVec)), "");
}


TYPED_TEST(Vec4RejectionTests, StaticWrapper_FromZeroVectorTriggersAssertionInCallback)
{
    const flcn::Vec4<TypeParam> zeroVec(0, 0, 0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(flcn::Vec4<TypeParam>::reject(this->_vec, zeroVec)), "");
}

#endif
