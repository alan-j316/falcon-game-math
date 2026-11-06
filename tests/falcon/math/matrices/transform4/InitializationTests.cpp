/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 30, 2026
 *
 * @brief Verify @ref flcn::Transform4 initialization.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Transform4TestSetup.h"



/**
 * @addtogroup T_FALCON_Transform4_Init
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref flcn::Transform4 initialization.
     *
     * @tparam T The scalar type (e.g., uint32_t, int32_t, float, double) used for the values.
     */
    template <typename T>
    class Transform4InitializationTests: public testing::Test
    {
    protected:
        std::vector<T> _elements;
        std::vector<T> _expectedElements;
        flcn::Vec3<T> _firstAxis, _secondAxis, _thirdAxis;
        flcn::Point3<T> _translation;
        T _diagonal0, _diagonal1, _diagonal2, _diagonal3;

        void SetUp() override
        {
            _elements         = { T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8), T(9), T(10), T(11), T(12) };
            _expectedElements = { T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8), T(9), T(10), T(11), T(12) };
            _firstAxis        = flcn::Vec3{ T(1), T(5), T(9) };
            _secondAxis       = flcn::Vec3{ T(2), T(6), T(10) };
            _thirdAxis        = flcn::Vec3{ T(3), T(7), T(11) };
            _translation      = flcn::Point3{ T(4), T(8), T(12) };
        }
    };
    TYPED_TEST_SUITE(Transform4InitializationTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that the matrix can be initialized at compile time using scalar values.
        constexpr flcn::Transform4 ROW_COL_INIT_MAT(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
        static_assert(ROW_COL_INIT_MAT(0, 0) == 1);
        static_assert(ROW_COL_INIT_MAT(0, 1) == 2);
        static_assert(ROW_COL_INIT_MAT(0, 2) == 3);
        static_assert(ROW_COL_INIT_MAT(0, 3) == 4);
        static_assert(ROW_COL_INIT_MAT(1, 0) == 5);
        static_assert(ROW_COL_INIT_MAT(1, 1) == 6);
        static_assert(ROW_COL_INIT_MAT(1, 2) == 7);
        static_assert(ROW_COL_INIT_MAT(1, 3) == 8);
        static_assert(ROW_COL_INIT_MAT(2, 0) == 9);
        static_assert(ROW_COL_INIT_MAT(2, 1) == 10);
        static_assert(ROW_COL_INIT_MAT(2, 2) == 11);
        static_assert(ROW_COL_INIT_MAT(2, 3) == 12);


        /// @test Verify that the matrix can be initialized at compile time using transformation axis and an origin
        /// point.
        constexpr flcn::Transform4 MAT2(flcn::Vec3(1, 5, 9), flcn::Vec3(2, 6, 10), flcn::Vec3(3, 7, 11),
                                       flcn::Point3(4, 8, 12));
        static_assert(MAT2(0, 0) == 1);
        static_assert(MAT2(0, 1) == 2);
        static_assert(MAT2(0, 2) == 3);
        static_assert(MAT2(0, 3) == 4);
        static_assert(MAT2(1, 0) == 5);
        static_assert(MAT2(1, 1) == 6);
        static_assert(MAT2(1, 2) == 7);
        static_assert(MAT2(1, 3) == 8);
        static_assert(MAT2(2, 0) == 9);
        static_assert(MAT2(2, 1) == 10);
        static_assert(MAT2(2, 2) == 11);
        static_assert(MAT2(2, 3) == 12);


        /// @test Verify that the matrix can be initialized at compile time using value initialization.
        constexpr flcn::Transform4<int> MAT4{};
        static_assert(MAT4(0, 0) == 0);
        static_assert(MAT4(0, 1) == 0);
        static_assert(MAT4(0, 2) == 0);
        static_assert(MAT4(0, 3) == 0);
        static_assert(MAT4(1, 0) == 0);
        static_assert(MAT4(1, 1) == 0);
        static_assert(MAT4(1, 2) == 0);
        static_assert(MAT4(1, 3) == 0);
        static_assert(MAT4(2, 0) == 0);
        static_assert(MAT4(2, 1) == 0);
        static_assert(MAT4(2, 2) == 0);
        static_assert(MAT4(2, 3) == 0);

    } // namespace static_tests


} // namespace



/**************************************
 *            RUNTIME TESTS           *
 **************************************/

TYPED_TEST(Transform4InitializationTests, EmptyCtor_ReturnsIdentityMatrix)
{
    constexpr flcn::Transform4<TypeParam> matrix{};

    EXPECT_MAT_ZERO(matrix);
}


TYPED_TEST(Transform4InitializationTests, ParameterizedCtor_InitializesMatrixWithElements)
{
    const flcn::Transform4<TypeParam> matrix(this->_elements[0], this->_elements[1], this->_elements[2],
                                            this->_elements[3], this->_elements[4], this->_elements[5],
                                            this->_elements[6], this->_elements[7], this->_elements[8],
                                            this->_elements[9], this->_elements[10], this->_elements[11]);
    EXPECT_MAT_CONTAINS(this->_expectedElements, matrix);
}


TYPED_TEST(Transform4InitializationTests, ParameterizedCtor_InitializesMatrixWithAxisAndOriginPoint)
{
    const flcn::Transform4<TypeParam> matrix{ this->_firstAxis, this->_secondAxis, this->_thirdAxis,
                                             this->_translation };
    EXPECT_MAT_CONTAINS(this->_expectedElements, matrix);
}


/** @test Verify that a matrix can be initialized with implicit braced initialization. */
TYPED_TEST(Transform4InitializationTests, CanBeConstructedWithBracedInitialization)
{
    const flcn::Transform4<TypeParam> matrix = { { TypeParam(1), TypeParam(5), TypeParam(9) },
                                                { TypeParam(2), TypeParam(6), TypeParam(10) },
                                                { TypeParam(3), TypeParam(7), TypeParam(11) },
                                                { TypeParam(4), TypeParam(8), TypeParam(12) } };
    EXPECT_MAT_CONTAINS(this->_expectedElements, matrix);
}

/** @} */
