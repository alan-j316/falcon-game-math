#pragma once
/**
 * @file MatrixUtils.h
 * @author Alan Abraham P Kochumon
 * @date Created on: February 16, 2026
 *
 * @brief Diagnostic and validation utilities for Matrix types.
 *        Provides specialized testing helpers and assertion wrappers for @ref flcn::Mat2,
 *        @ref flcn::Mat3, and @ref flcn::Mat4 to ensure numerical stability and
 *        geometric correctness across the fgm library.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "FloatEquals.h"

#include <cassert>
#include <cmath>
#include <falcon/math/common/Utils.h>
#include <gtest/gtest.h>
#include <vector>



namespace testutils
{

    /**
     * @addtogroup Matrix_Utils
     * @{
     */

    /**
     * @brief Perform a component-wise strict equality comparison between two matrices of the same dimensions.
     *
     * @tparam T The type of expected matrix.
     * @tparam U The type of actual matrix.
     *
     * @param expected The matrix serving as the reference for comparison.
     * @param actual   The matrix being evaluated.
     * @param epsilon The precision threshold for IEEE-754 floating point numbers.
     *                Ignored for integrals.
     *
     * @note Uses GoogleTest macros for validation. This function will trigger a non-fatal test failure
     *       if the matrices are out of the @p tolerance range.
     * @note Triggers an assertion failure if matrix dimensions are mismatched.
     */
    template <flcn::Matrix T, flcn::Matrix U>
    void EXPECT_MAT_EQ(const T& expected, const U& actual, const double epsilon = std::is_same_v<T, double> ? 1e-14 : 1e-5)
    {
        using ValueType = T::value_type;

        static_assert(T::ROWS == U::ROWS && T::COLUMNS == U::COLUMNS,
                      "Matrices must of the same dimension, e.g: 3x3 and 3x3");

        for (std::size_t i = 0; i < T::ROWS; ++i)
        {
            for (std::size_t j = 0; j < T::COLUMNS; ++j)
            {
                if constexpr (std::is_floating_point_v<ValueType>)
                {
                    EXPECT_NEAR(expected(i, j), static_cast<ValueType>(actual(i, j)), epsilon);
                }
                else
                {
                    EXPECT_EQ(expected(i, j), static_cast<ValueType>(actual(i, j)));
                }
            }
        }
    }


    /**
     * @brief Perform a component-wise strict equality comparison of the data elements expected in the matrix
     *        with the actual matrix elements.
     *
     * @tparam T The numeric type of the expected data.
     * @tparam U The type of the actual matrix.
     *
     * @param expectedElements The elements in row-major order that forms the elements of the matrix.
     * @param actual           The matrix being evaluated.
     * @param epsilon The precision threshold for IEEE-754 floating point numbers.
     *                Ignored for integrals.
     *
     * @note Uses GoogleTest macros for validation. This function will trigger a non-fatal test failure
     *       if the matrix is not a zero matrix.
     * @note Triggers an assertion failure if matrix dimension doesn't match the size of data elements.
     */
    template <flcn::Arithmetic T, flcn::Matrix U>
    void EXPECT_MAT_CONTAINS(const std::vector<T>& expectedElements, const U& actual, const double epsilon = std::is_same_v<T, double> ? 1e-14 : 1e-5)
    {
        assert(expectedElements.size() == U::ROWS * U::COLUMNS &&
               "Size of data elements must match the matrix dimension, e.g: 9 to 3x3");

        for (std::size_t i = 0; i < U::ROWS; ++i)
        {
            for (std::size_t j = 0; j < U::COLUMNS; ++j)
            {

                if constexpr (std::is_floating_point_v<T>)
                {
                    EXPECT_NEAR(expectedElements[i * U::COLUMNS + j], static_cast<T>(actual(i, j)), epsilon);
                }
                else
                {
                    EXPECT_EQ(expectedElements[i * U::COLUMNS + j], static_cast<T>(actual(i, j)));
                }
            }
        }
    }

    /**
     * @brief Perform a component-wise strict equality comparison of the data elements expected in the matrix
     *        with the actual matrix elements at compile time.
     *
     * @tparam T The numeric type of the expected data.
     * @tparam U The type of the actual matrix.
     *
     * @param expectedElements The elements in row-major order that forms the elements of the matrix.
     * @param actual           The matrix being evaluated.
     *
     * @note Uses static asserts so the test should be compile time.
     */
    template <flcn::Arithmetic T, flcn::Matrix U>
    constexpr void EXPECT_MAT_CONTAINS_STATIC(const std::vector<T>& expectedElements, const U& actual)
    {
        assert(expectedElements.size() == U::ROWS * U::COLUMNS &&
               "Size of data elements must match the matrix dimension, e.g: 9 to 3x3");

        for (std::size_t i = 0; i < U::ROWS; ++i)
        {
            for (std::size_t j = 0; j < U::COLUMNS; ++j)
            {
                static_assert(COMPARE_EQ(expectedElements[i * U::COLUMNS + j], static_cast<T>(actual(i, j))));
            }
        }
    }


    /**
     * @brief Performs a component-wise approximate equality comparison using an absolute epsilon.
     *
     * @tparam T The type of expected matrix.
     * @tparam U The type of actual matrix.
     *
     * @param expected  The matrix serving as the ground truth.
     * @param actual    The matrix being evaluated.
     * @param tolerance The maximum allowable absolute difference between components.
     *
     * @note Uses GoogleTest macros for validation. This function will trigger a non-fatal test failure
     *       if the matrices are out of the @p tolerance range.
     * @note Triggers an assertion failure if matrix dimensions are mismatched.
     */
    template <flcn::Matrix T, flcn::Matrix U>
    void EXPECT_MAT_NEAR(const T& expected, const U& actual, double tolerance = 1e-5)
    {

        using ValueType = T::value_type;
        static_assert(T::ROWS == U::ROWS && T::COLUMNS == U::COLUMNS,
                      "Matrices must of the same dimension, e.g: 3x3 and 3x3");

        for (std::size_t i = 0; i < T::ROWS; ++i)
        {
            for (std::size_t j = 0; j < T::COLUMNS; ++j)
            {
                EXPECT_NEAR(expected(i, j), static_cast<ValueType>(actual(i, j)), tolerance);
            }
        }
    }


    /**
     * @brief Validates that the provided matrix conforms to an identity matrix within a standard epsilon.
     *
     * @tparam T The type of the matrix.
     *
     * @param actual The matrix to verify as an identity matrix.
     * @param epsilon The precision threshold for IEEE-754 floating point numbers.
     *                Ignored for integrals.
     *
     * @note Uses GoogleTest macros for validation. This function will trigger a non-fatal test failure
     *       if the matrix is not identity.
     * @note Triggers an assertion failure if matrix dimensions are mismatched.
     */
    template <flcn::Matrix T>
    void EXPECT_MAT_IDENTITY(const T& actual, const double epsilon = std::is_same_v<T, double> ? 1e-14 : 1e-5)
    {
        using ValueType = T::value_type;
        EXPECT_EQ(T::ROWS, T::COLUMNS) << "Identity matrices must be square(e.g: 3x3)\n";

        for (std::size_t i = 0; i < T::ROWS; ++i)
        {
            for (std::size_t j = 0; j < T::COLUMNS; ++j)
            {
                if constexpr (std::is_floating_point_v<ValueType>)
                {
                    EXPECT_NEAR(static_cast<double>(i == j), actual(i, j), epsilon);
                }
                else
                {
                    EXPECT_EQ(static_cast<int>(i == j), actual(i, j));
                }
            }
        }
    }


    /**
     * @brief Validates that the provided matrix contains only '1' as element.
     *
     * @tparam T The type of the matrix.
     *
     * @param actual The matrix to verify as an identity matrix.
     * @param epsilon The precision threshold for IEEE-754 floating point numbers.
     *                Ignored for integrals.
     *
     * @note Uses GoogleTest macros for validation. This function will trigger a non-fatal test failure
     *       if the matrix is not identity.
     * @note Triggers an assertion failure if matrix dimensions are mismatched.
     */
    template <flcn::Matrix T>
    void EXPECT_MAT_ONE(const T& actual, const double epsilon = std::is_same_v<T, double> ? 1e-14 : 1e-5)
    {
        using ValueType = T::value_type;

        for (std::size_t i = 0; i < T::ROWS; ++i)
        {
            for (std::size_t j = 0; j < T::COLUMNS; ++j)
            {
                if constexpr (std::is_floating_point_v<ValueType>)
                {
                    EXPECT_NEAR(static_cast<ValueType>(1), actual(i, j), epsilon);
                }
                else
                {
                    EXPECT_EQ(static_cast<ValueType>(1), actual(i, j));
                }
            }
        }
    }


    /**
     * @brief Validates that the provided matrix conforms to a zero matrix within a standard epsilon.
     *
     * @tparam T The type of the matrix.
     *
     * @param actual The matrix to verify as a zero matrix.
     * @param epsilon The precision threshold for IEEE-754 floating point numbers.
     *                Ignored for integrals.
     *
     * @note Uses GoogleTest macros for validation. This function will trigger a non-fatal test failure
     *       if the matrix is not a zero matrix.
     * @note Triggers an assertion failure if matrix dimensions are mismatched.
     */
    template <flcn::Matrix T>
    void EXPECT_MAT_ZERO(const T& actual, const double epsilon = std::is_same_v<T, double> ? 1e-14 : 1e-5)
    {
        using ValueType = T::value_type;

        for (std::size_t i = 0; i < T::ROWS; ++i)
        {
            for (std::size_t j = 0; j < T::COLUMNS; ++j)
            {
                if constexpr (std::is_floating_point_v<ValueType>)
                {
                    EXPECT_NEAR(static_cast<ValueType>(0), actual(i, j), epsilon);
                }
                else
                {
                    EXPECT_EQ(ValueType(0), actual(i, j));
                }
            }
        }
    }


    /**
     * @brief Validates that the provided matrix conforms to an infinity matrix.
     *
     * @tparam T The type of the matrix.
     *
     * @param actual The matrix to verify as an infinity matrix.
     *
     * @note Uses GoogleTest macros for validation. This function will trigger a non-fatal test failure
     *       if the matrix is not an infinity matrix.
     * @note Triggers an assertion failure if matrix dimensions are mismatched.
     */
    template <flcn::Matrix T>
    void EXPECT_MAT_INF(const T& actual)
    {
        for (std::size_t i = 0; i < T::ROWS; ++i)
        {
            for (std::size_t j = 0; j < T::COLUMNS; ++j)
            {
                EXPECT_TRUE(std::isinf(actual(i, j)));
            }
        }
    }

    /** @} */

} // namespace testutils
