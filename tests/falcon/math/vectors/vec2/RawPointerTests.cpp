/**
 * @file RawPointerTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 26, 2026
 *
 * @brief Verify that `store` can write internal memory location storage.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"

/**
 * @addtogroup T_FALCON_Vec2_Ptr
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Vec2 store and storeUnaligned.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class Vec2StorageTests: public testing::Test
    {
    protected:
        flcn::Vec2<T> _vec;

        void SetUp() override { _vec = { T(7), T(12) }; }
    };
    TYPED_TEST_SUITE(Vec2StorageTests, SupportedArithmeticTypes);
} // namespace


TYPED_TEST(Vec2StorageTests, Store_WritesDataToAlignedBuffer)
{
    alignas(16) TypeParam data[2];
    this->_vec.store(data);

    EXPECT_EQ(this->_vec[0], data[0]);
    EXPECT_EQ(this->_vec[1], data[1]);
}


TYPED_TEST(Vec2StorageTests, StaticWrapper_Store_WritesDataToAlignedBuffer)
{
    alignas(16) TypeParam data[2];
    this->_vec.store(data);

    EXPECT_EQ(this->_vec[0], data[0]);
    EXPECT_EQ(this->_vec[1], data[1]);
}

TYPED_TEST(Vec2StorageTests, StoreUnaligned_WritesDataToNonAlignedBuffer)
{

    alignas(8) TypeParam data[2];
    this->_vec.storeUnaligned(data);

    EXPECT_EQ(this->_vec[0], data[0]);
    EXPECT_EQ(this->_vec[1], data[1]);
}


TYPED_TEST(Vec2StorageTests, StaticWrapper_StoreUnaligned_WritesDataToNonAlignedBuffer)
{
    alignas(8) TypeParam data[2];
    this->_vec.storeUnaligned(data);

    EXPECT_EQ(this->_vec[0], data[0]);
    EXPECT_EQ(this->_vec[1], data[1]);
}

/** @} */
