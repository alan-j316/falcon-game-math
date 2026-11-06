/**
 * @file LoadStoreTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 16, 2026
 *
 * @brief Verify @ref flcn::Simd256 register loading and storing in a platform agnostic manner.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "SIMDTestSetup.h"

#include <array>


/**
 * @addtogroup T_SIMD256_Load_Store
 * @{
 */

// TODO: Remove Preprocessor after implementing individual simd paths
#if defined(FALCON_ENABLE_AVX512) || defined(FALCON_ENABLE_AVX2) || defined(FALCON_ENABLE_AVX) ||                      \
    defined(FALCON_ENABLE_SSE4) || defined(FALCON_ENABLE_SSE2)
namespace
{
    /**
     * @brief Test Fixture for Simd256 load and store operations.
     */
    template <typename>
    class Simd256LoadStoreTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Simd256LoadStoreTests, Simd256RegisterTypeHints);

} // namespace


TYPED_TEST(Simd256LoadStoreTests, LoadAligned_LoadsAndStoresDataWithoutCorruption)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(32) std::array<Type, Lane> data{};

    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = static_cast<Type>(i + 11);
    }

    flcn::Simd256_t<Type, Lane> reg;
    reg.loadAligned(data.data());

    alignas(32) std::array<Type, Lane> result{};
    reg.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(data[i], result[i]);
    }
}


TYPED_TEST(Simd256LoadStoreTests, Load_LoadsDataFromUnalignedMemory)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(8) std::array<Type, Lane> data{}; // Min alignment possible is 8

    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = static_cast<Type>(i + 11);
    }

    flcn::Simd256_t<Type, Lane> reg;
    reg.load(data.data());

    alignas(32) std::array<Type, Lane> result{};
    reg.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(data[i], result[i]);
    }
}


TYPED_TEST(Simd256LoadStoreTests, Store_StoresDataIntoUnalignedMemory)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(32) std::array<Type, Lane> data{}; // Min alignment possible is 8

    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = static_cast<Type>(i + 11);
    }

    flcn::Simd256_t<Type, Lane> reg;
    reg.loadAligned(data.data());

    alignas(8) std::array<Type, Lane> result{};

    reg.store(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(data[i], result[i]);
    }
}


TYPED_TEST(Simd256LoadStoreTests, Broadcast_StoresASingleValueIntoTheRegister)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    Type data = Type(7);
    flcn::Simd256_t<Type, Lane> reg;
    reg.broadcast(data);

    alignas(32) std::array<Type, Lane> result{};
    reg.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(data, result[i]);
    }
}


TYPED_TEST(Simd256LoadStoreTests, SetZero_ZeroesOutTheRegister)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    flcn::Simd256_t<Type, Lane> reg;
    reg.setZero();

    alignas(32) std::array<Type, Lane> result{};

    reg.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(Type(0), result[i]);
    }
}

#endif

/** @} */
