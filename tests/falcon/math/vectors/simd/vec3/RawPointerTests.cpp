/**
 * @file RawPointerTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 26, 2026
 *
 * @brief Verify that `store` can write internal memory location storage.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3TestSetup.h"

/**
 * @addtogroup T_Falcon_Vec3_Ptr
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::simd::Vec3 store and storeUnaligned.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class SimdVec3StorageTests: public testing::Test
    {
    protected:
        flcn::simd::Vec3<T> _vec;

        void SetUp() override { _vec = { T(7), T(12), T(5) }; }
    };
    TYPED_TEST_SUITE(SimdVec3StorageTests, SupportedArithmeticTypes);
} // namespace


TYPED_TEST(SimdVec3StorageTests, Store_WritesDataToAlignedBuffer)
{
    alignas(32) std::array<TypeParam, 4> data;
    this->_vec.store(data.data());

    EXPECT_EQ(this->_vec[0], data[0]);
    EXPECT_EQ(this->_vec[1], data[1]);
    EXPECT_EQ(this->_vec[2], data[2]);
}


TYPED_TEST(SimdVec3StorageTests, StaticWrapper_Store_WritesDataToAlignedBuffer)
{
    alignas(32) std::array<TypeParam, 4> data;
    this->_vec.store(data.data());

    EXPECT_EQ(this->_vec[0], data[0]);
    EXPECT_EQ(this->_vec[1], data[1]);
    EXPECT_EQ(this->_vec[2], data[2]);
}

TYPED_TEST(SimdVec3StorageTests, StoreUnaligned_WritesDataToNonAlignedBuffer)
{
    alignas(8) std::array<TypeParam, 4> data;
    this->_vec.storeUnaligned(data.data());

    EXPECT_EQ(this->_vec[0], data[0]);
    EXPECT_EQ(this->_vec[1], data[1]);
    EXPECT_EQ(this->_vec[2], data[2]);
}


TYPED_TEST(SimdVec3StorageTests, StaticWrapper_StoreUnaligned_WritesDataToNonAlignedBuffer)
{
    alignas(8) std::array<TypeParam, 4> data;
    this->_vec.storeUnaligned(data.data());

    EXPECT_EQ(this->_vec[0], data[0]);
    EXPECT_EQ(this->_vec[1], data[1]);
    EXPECT_EQ(this->_vec[2], data[2]);
}

/** @} */
