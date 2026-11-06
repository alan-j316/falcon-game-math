/**
 * @file LoadStoreTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 16, 2026
 *
 * @brief Verify @ref flcn::Simd128 register loading and storing in a platform agnostic manner.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "SIMDTestSetup.h"

#include <array>
#include <falcon/simd/core/Simd128.h>


/**
 * @addtogroup T_SIMD128_Load_Store
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
    class Simd128LoadStoreTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Simd128LoadStoreTests, Simd128RegisterTypeHints);

} // namespace


TYPED_TEST(Simd128LoadStoreTests, LoadAligned_LoadsAndStoresDataWithoutCorruption)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> data{};

    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = static_cast<Type>(i + 11);
    }

    flcn::Simd128_t<Type, Lane> reg;
    reg.loadAligned(data.data());

    alignas(16) std::array<Type, Lane> result{};
    reg.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(data[i], result[i]);
    }
}


TYPED_TEST(Simd128LoadStoreTests, Load_LoadsDataFromUnalignedMemory)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(8) std::array<Type, Lane> data{}; // Min alignment possible is 8

    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = static_cast<Type>(i + 11);
    }

    flcn::Simd128_t<Type, Lane> reg;
    reg.load(data.data());

    alignas(16) std::array<Type, Lane> result{};
    reg.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(data[i], result[i]);
    }
}


TYPED_TEST(Simd128LoadStoreTests, Store_StoresDataIntoUnalignedMemory)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> data{}; // Min alignment possible is 8

    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = static_cast<Type>(i + 11);
    }

    flcn::Simd128_t<Type, Lane> reg;
    reg.loadAligned(data.data());

    alignas(8) std::array<Type, Lane> result{};

    reg.store(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(data[i], result[i]);
    }
}


TYPED_TEST(Simd128LoadStoreTests, Broadcast_StoresASingleValueIntoTheRegister)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    Type data = Type(7);
    flcn::Simd128_t<Type, Lane> reg;
    reg.broadcast(data);

    alignas(16) std::array<Type, Lane> result{};
    reg.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(data, result[i]);
    }
}


TYPED_TEST(Simd128LoadStoreTests, SetZero_ZeroesOutTheRegister)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    flcn::Simd128_t<Type, Lane> reg;
    reg.setZero();

    alignas(16) std::array<Type, Lane> result{};

    reg.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(Type(0), result[i]);
    }
}

#endif

/** @} */
