/**
 * @file RawPointerTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 25, 2026
 *
 * @brief Verify that `ptr` and unary `operator*` return the memory address for internal storage.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"

/**
 * @addtogroup T_Falcon_Vec2_Ptr
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Vec2 ptr.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class Vec2StoragePtrTests: public testing::Test
    {
    protected:
        flcn::Vec2<T> _vec;

        void SetUp() override { _vec = { T(7), T(12) }; }
    };
    TYPED_TEST_SUITE(Vec2StoragePtrTests, SupportedArithmeticTypes);
} // namespace


TYPED_TEST(Vec2StoragePtrTests, Ptr_ReturnsAPointerToTheInternalData)
{
    TypeParam* data = this->_vec.ptr();
    EXPECT_EQ(this->_vec[0], data[0]);
    EXPECT_EQ(this->_vec[1], data[1]);
}


TYPED_TEST(Vec2StoragePtrTests, StaticWrapper_Ptr_ReturnsAPointerToTheInternalData)
{
    TypeParam* data = flcn::Vec2<TypeParam>::ptr(this->_vec);
    EXPECT_EQ(this->_vec[0], data[0]);
    EXPECT_EQ(this->_vec[1], data[1]);
}


TYPED_TEST(Vec2StoragePtrTests, Ptr_OnConstVec_ReturnsAConstPointerToTheInternalData)
{
    const flcn::Vec2 vec(this->_vec.x(), this->_vec.y());
    const TypeParam* data = vec.ptr();
    EXPECT_EQ(vec[0], data[0]);
    EXPECT_EQ(vec[1], data[1]);
}


TYPED_TEST(Vec2StoragePtrTests, StaticWrapper_Ptr_OnConstVec_ReturnsAConstPointerToTheInternalData)
{
    const flcn::Vec2 vec(this->_vec.x(), this->_vec.y());
    const TypeParam* data = flcn::Vec2<TypeParam>::ptr(vec);
    EXPECT_EQ(vec[0], data[0]);
    EXPECT_EQ(vec[1], data[1]);
}


TYPED_TEST(Vec2StoragePtrTests, UnaryOperatorTimes_ReturnsAPointerToTheInternalData)
{
    TypeParam* data = *this->_vec;
    EXPECT_EQ(this->_vec[0], data[0]);
    EXPECT_EQ(this->_vec[1], data[1]);
}


TYPED_TEST(Vec2StoragePtrTests, UnaryOperatorTimes_OnConstVec_ReturnsAConstPointerToTheInternalData)
{
    const flcn::Vec2 vec(this->_vec.x(), this->_vec.y());
    const TypeParam* data = *vec;
    EXPECT_EQ(vec[0], data[0]);
    EXPECT_EQ(vec[1], data[1]);
}

/** @} */
