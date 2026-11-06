/**
 * @file MultiplicationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 31, 2026
 *
 * @brief Verify @ref flcn::Transform4 multiplication logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Transform4TestSetup.h"



/**
 * @addtogroup T_FALCON_Transform4_Multiplication
 * @{
 */

namespace
{

    /**************************************
     *             TEST SETUP             *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Transform4 transform(matrix) multiplication.
     *
     * @tparam T The scalar type (e.g., uint32_t, int32_t, float, double) used for the values.
     */
    template <typename T>
    class Transform4TransformMultiplicationTests: public testing::Test
    {
    protected:
        flcn::Transform4<T> _transformA, _transformB, _expectedFPTransform, _expectedIntTransform;

        void SetUp() override
        {
            _transformA = {
                { T(7.12345678912345), T(6.12345678912345), T(1.2389123488213) },
                { T(5.12345678912345), T(4.12345678912345), T(2.53283924821338) },
                { T(1.32189342348), T(8.238192312343), T(5.12398423821223) },
                { T(4.8934233348), T(1.9233212312343), T(4.3984231212233) },
            };
            _transformB = {
                { T(3.12345678912345), T(5.12345678912345), T(1.213849123421) },
                { T(8.12345678912345), T(3.12345678912345), T(2.3218934118233) },
                { T(7.23912389492341), T(4.291238423419123), T(4.18234983241234) },
                { T(5.932123894923), T(3.338423419123), T(7.3498324123324) },
            };

            _expectedFPTransform  = { { T(50.10419811337752805), T(50.25262787869461789), T(23.06632540504888595) },
                                      { T(76.93928493851146300), T(81.75128018451636080), T(29.87281012174309325) },
                                      { T(79.08218162897063053), T(96.47820080937790976), T(41.26795171031561438) },
                                      { T(73.97061482922748610), T(112.56360315835962638), T(57.86391996678334948) } };
            _expectedIntTransform = { { 47, 46, 18 }, { 73, 76, 24 }, { 73, 90, 35 }, { 61, 99, 50 }

            };
        }
    };
    TYPED_TEST_SUITE(Transform4TransformMultiplicationTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref flcn::Transform4 vector multiplication.
     *
     * @tparam T The scalar type (e.g., uint32_t, int32_t, float, double) used for the values.
     */
    template <typename T>
    class Transform4VectorMultiplicationTests: public testing::Test
    {
    protected:
        flcn::Transform4<T> _transform;
        flcn::Vec3<T> _vec;
        flcn::Vec3<T> _expectedFPVector, _expectedIntVector;

        void SetUp() override
        {
            _transform = {
                { T(7.12345678912345), T(6.12345678912345), T(1.2389123488213) },
                { T(5.12345678912345), T(4.12345678912345), T(2.53283924821338) },
                { T(1.32189342348), T(8.238192312343), T(5.12398423821223) },
                { T(4.8934233348), T(1.9233212312343), T(4.3984231212233) },
            };
            _vec               = { T(2.123456789123456), T(3.123456832912), T(1.2318492394128) };
            _expectedFPVector  = { T(32.75762220530739910), T(36.03054610906941946), T(16.85396698133816074) };
            _expectedIntVector = { T(30), T(32), T(13) };
        }
    };
    TYPED_TEST_SUITE(Transform4VectorMultiplicationTests, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref flcn::Transform4 point multiplication.
     *
     * @tparam T The scalar type (e.g., uint32_t, int32_t, float, double) used for the values.
     */
    template <typename T>
    class Transform4PointMultiplicationTests: public testing::Test
    {
    protected:
        flcn::Transform4<T> _transform;
        flcn::Point3<T> _point;
        flcn::Point3<T> _expectedFPPoint, _expectedIntPoint;

        void SetUp() override
        {
            _transform = {
                { T(7.12345678912345), T(6.12345678912345), T(1.2389123488213) },
                { T(5.12345678912345), T(4.12345678912345), T(2.53283924821338) },
                { T(1.32189342348), T(8.238192312343), T(5.12398423821223) },
                { T(4.8934233348), T(1.9233212312343), T(4.3984231212233) },
            };
            _point            = { T(2.123456789123456), T(3.123456832912), T(1.2318492394128) };
            _expectedFPPoint  = { T(37.65104554010739690), T(37.95386734030372367), T(21.25239010256146344) };
            _expectedIntPoint = { T(34), T(33), T(17) };
        }
    };
    TYPED_TEST_SUITE(Transform4PointMultiplicationTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr flcn::Transform4 TRANSFORM_A(7, 5, 1, 4, 6, 4, 8, 1, 1, 2, 5, 4);
        constexpr flcn::Transform4 TRANSFORM_B(3, 8, 7, 5, 5, 3, 4, 3, 1, 2, 4, 7);
        constexpr flcn::Vec3 VECTOR(2, 3, 1);
        constexpr flcn::Point3 POINT(2, 3, 1);


        /// @test Verify that Transform4 * Transform4 returns a valid Transform4 at compile time.
        constexpr auto TRANSFORMED_MAT = TRANSFORM_A * TRANSFORM_B;
        static_assert(TRANSFORMED_MAT[0] == flcn::Vec3{ 47, 46, 18 });
        static_assert(TRANSFORMED_MAT[1] == flcn::Vec3{ 73, 76, 24 });
        static_assert(TRANSFORMED_MAT[2] == flcn::Vec3{ 73, 90, 35 });
        static_assert(TRANSFORMED_MAT[3] == flcn::Vec3{ 61, 99, 50 });


        /// @test Verify that Transform4 * Vec3 returns a valid Vec3 at compile time.
        constexpr auto TRANSFORMED_VECTOR = TRANSFORM_A * VECTOR;
        static_assert(TRANSFORMED_VECTOR[0] == 30);
        static_assert(TRANSFORMED_VECTOR[1] == 32);
        static_assert(TRANSFORMED_VECTOR[2] == 13);


        /// @test Verify that Transform4 * Point3 returns a valid Point3 at compile time.
        constexpr auto TRANSFORMED_POINT = TRANSFORM_A * POINT;
        static_assert(TRANSFORMED_POINT[0] == 34);
        static_assert(TRANSFORMED_POINT[1] == 33);
        static_assert(TRANSFORMED_POINT[2] == 17);

    } // namespace static_tests

} // namespace




/**************************************
 *    VECTOR MULTIPLICATION TESTS     *
 **************************************/

/**
 * @test Verify that the binary vector multiplication operation perform linear transformation
 *        and returns a new column vector(<x, y, z, 0>).
 */
TYPED_TEST(Transform4VectorMultiplicationTests, MatrixTimesVectorReturnsATransformedVector)
{
    const auto transformedVector = this->_transform * this->_vec;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFPVector, transformedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntVector, transformedVector);
    }
}


TEST(Transform4VectorMultiplicationTests, MatTimesVec_MixedTypeScalarMultiplicationPromotesType)
{
    const flcn::Transform4 mat{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    const flcn::Vec3 vec{ 2, 1, 3 };

    [[maybe_unused]] const auto transformedVector = mat * vec;
    static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
}


/**
 * @test Verify that the binary vector multiplication operation perform linear transformation
 *        and returns a new point(<x, y, z, 1>).
 */
TYPED_TEST(Transform4PointMultiplicationTests, MatrixTimesPointReturnsATransformedPoint)
{
    const auto transformedVector = this->_transform * this->_point;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFPPoint, transformedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntPoint, transformedVector);
    }
}


TEST(Transform4PointMultiplicationTests, MatTimesVec_MixedTypeScalarMultiplicationPromotesType)
{
    const flcn::Transform4 mat{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    const flcn::Point3 point{ 2, 1, 3 };

    [[maybe_unused]] const auto transformedPoint = mat * point;
    static_assert(std::is_same_v<decltype(transformedPoint)::value_type, double>);
}



/**************************************
 *    MATRIX MULTIPLICATION TESTS     *
 **************************************/

TYPED_TEST(Transform4TransformMultiplicationTests, TimesOperator_ReturnsValidTransformMatrix)
{
    const auto transformResult = this->_transformA * this->_transformB;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPTransform, transformResult);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntTransform, transformResult);
    }
}


TEST(Transform4TransformMultiplicationTests, TimesOperator_MixedTypes_PromotesToWiderType)
{
    const flcn::Transform4 transformA{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    const flcn::Transform4 transformB{ 2, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    [[maybe_unused]] const auto transformedVector = transformA * transformB;
    static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
}


TYPED_TEST(Transform4TransformMultiplicationTests, TimesEqualOperator_MutatesCurrentTransformMatrix)
{
    this->_transformA *= this->_transformB;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPTransform, this->_transformA);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntTransform, this->_transformA);
    }
}


TEST(Transform4TransformMultiplicationTests, TimesEqualOperator_MixedTypes_DoesNotPromotesToWiderType)
{
    flcn::Transform4 transformA{ 2, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    const flcn::Transform4 transformB{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };

    transformA *= transformB;
    static_assert(std::is_same_v<decltype(transformA)::value_type, int>);
}

/** @} */
