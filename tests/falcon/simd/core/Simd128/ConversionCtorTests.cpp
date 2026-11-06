/**
 * @file LoadStoreTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 18, 2026
 *
 * @brief Verify @ref flcn::Simd128 conversion constructors.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "SIMDTestSetup.h"

#include <array>
#include <falcon/simd/core/Simd128.h>

/**
 * @addtogroup T_SIMD128_ConvCtor
 * @{
 */

// TODO: Remove Preprocessor after implementing individual simd paths
#if defined(FALCON_ENABLE_AVX512) || defined(FALCON_ENABLE_AVX2) || defined(FALCON_ENABLE_AVX) ||                      \
    defined(FALCON_ENABLE_SSE4) || defined(FALCON_ENABLE_SSE2)
namespace
{
    /**
     * @brief Test Fixture for Simd128 load and store operations.
     */
    template <typename>
    class Simd128ConversionCtorTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Simd128ConversionCtorTests, Simd128RegisterTypeHints);

} // namespace


TYPED_TEST(Simd128ConversionCtorTests, PromotesRegisterType)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;
    using PromotedType    = double;

    flcn::Simd128_t<Type, Lane> regA{};
    [[maybe_unused]] flcn::Simd128_t<PromotedType, Lane> regB(regA);

    #if defined(__GNUC__) || defined(__clang__)
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wignored-attributes"
    #endif

    // Compile time check -> Immediate feedback
    static_assert(std::is_same_v<decltype(regB.naive()), flcn::simd::internal::SSERegister_t<PromotedType>>);
    // Runtime check
    const bool result = std::is_same_v<decltype(regB.naive()), flcn::simd::internal::SSERegister_t<PromotedType>>;
    EXPECT_TRUE(result);

    #if defined(__GNUC__) || defined(__clang__)
        #pragma GCC diagnostic pop
    #endif
}


TYPED_TEST(Simd128ConversionCtorTests, DemotesRegisterType)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;
    using PromotedType    = uint8_t;

    flcn::Simd128_t<Type, Lane> regA{};
    [[maybe_unused]] flcn::Simd128_t<PromotedType, Lane> regB(regA);

    #if defined(__GNUC__) || defined(__clang__)
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wignored-attributes"
    #endif

    // Compile time check -> Immediate feedback
    static_assert(std::is_same_v<decltype(regB.naive()), flcn::simd::internal::SSERegister_t<PromotedType>>);
    // Runtime check
    const bool result = std::is_same_v<decltype(regB.naive()), flcn::simd::internal::SSERegister_t<PromotedType>>;
    EXPECT_TRUE(result);

    #if defined(__GNUC__) || defined(__clang__)
        #pragma GCC diagnostic pop
    #endif
}

#endif

/** @} */
