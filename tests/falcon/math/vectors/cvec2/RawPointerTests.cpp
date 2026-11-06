/**
 * @file RawPointerTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 25, 2026
 *
 * @brief Verify that `ptr` and unary `operator*` return the memory address for internal storage.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CVec2TestSetup.h"

/**
 * @addtogroup T_FALCON_CVec2_Ptr
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::CVec2 ptr.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class CVec2StoragePtrTests: public testing::Test
    {
    protected:
        flcn::CVec2<T> _vec;

        void SetUp() override { _vec = { T(7), T(12) }; }
    };
    TYPED_TEST_SUITE(CVec2StoragePtrTests, SupportedArithmeticTypes);
} // namespace


TYPED_TEST(CVec2StoragePtrTests, Ptr_ReturnsAPointerToTheInternalData)
{
    TypeParam* data = this->_vec.ptr();
    EXPECT_EQ(this->_vec[0], data[0]);
    EXPECT_EQ(this->_vec[1], data[1]);
}


TYPED_TEST(CVec2StoragePtrTests, StaticWrapper_Ptr_ReturnsAPointerToTheInternalData)
{
    TypeParam* data = flcn::CVec2<TypeParam>::ptr(this->_vec);
    EXPECT_EQ(this->_vec[0], data[0]);
    EXPECT_EQ(this->_vec[1], data[1]);
}


TYPED_TEST(CVec2StoragePtrTests, Ptr_OnConstVec_ReturnsAConstPointerToTheInternalData)
{
    const flcn::CVec2 vec(this->_vec.x(), this->_vec.y());
    const TypeParam* data = vec.ptr();
    EXPECT_EQ(vec[0], data[0]);
    EXPECT_EQ(vec[1], data[1]);
}


TYPED_TEST(CVec2StoragePtrTests, StaticWrapper_Ptr_OnConstVec_ReturnsAConstPointerToTheInternalData)
{
    const flcn::CVec2 vec(this->_vec.x(), this->_vec.y());
    const TypeParam* data = flcn::CVec2<TypeParam>::ptr(vec);
    EXPECT_EQ(vec[0], data[0]);
    EXPECT_EQ(vec[1], data[1]);
}


TYPED_TEST(CVec2StoragePtrTests, UnaryOperatorTimes_ReturnsAPointerToTheInternalData)
{
    TypeParam* data = *this->_vec;
    EXPECT_EQ(this->_vec[0], data[0]);
    EXPECT_EQ(this->_vec[1], data[1]);
}


TYPED_TEST(CVec2StoragePtrTests, UnaryOperatorTimes_OnConstVec_ReturnsAConstPointerToTheInternalData)
{
    const flcn::CVec2 vec(this->_vec.x(), this->_vec.y());
    const TypeParam* data = *vec;
    EXPECT_EQ(vec[0], data[0]);
    EXPECT_EQ(vec[1], data[1]);
}

/** @} */
