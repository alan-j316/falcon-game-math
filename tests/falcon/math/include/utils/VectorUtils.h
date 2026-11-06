#pragma once
/**
 * @file MatrixUtils.h
 * @author Alan Abraham P Kochumon
 * @date Created on: February 16, 2026
 *
 * @brief Diagnostic and validation utilities for Vector types.
 *        Provides specialized testing helpers and assertion wrappers for @ref CVec2,
 *        @ref Vec3, and @ref Vec4 to ensure numerical stability and
 *        geometric correctness across the fgm library.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <cmath>
#include <falcon/math/common/MathTraits.h>
#include <falcon/math/vectors/CVec2.h>
#include <falcon/math/vectors/Vec2.h>
#include <falcon/math/vectors/Vec3.h>
#include <falcon/math/vectors/Vec4.h>
#include <gtest/gtest.h>
#include <type_traits>

namespace testutils
{

    /**
     * @addtogroup Vector_Utils
     * @{
     */

    /**
     * @brief Perform a component-wise equality comparison between two vectors of the same dimensions.
     *
     * @tparam T Numeric type of the expected vector components.
     * @tparam U Numeric type of the actual vector components.
     *
     * @param expected The vector serving as the reference for comparison.
     * @param actual   The vector being evaluated.
     *
     * @note Uses GoogleTest macros for validation. This function will trigger a non-fatal test failure
     *       if the vectors are not equal.
     * @note Triggers an assertion failure if vector dimensions are mismatched.
     */
    template <flcn::Vector T, flcn::Vector U>
    void EXPECT_VEC_EQ(const T& expected, const U& actual)
    {
        using ValueType = T::value_type;

        static_assert(T::DIMENSION == U::DIMENSION, "Vectors must have the same dimension (e.g. both 3D)");

        constexpr std::size_t elementCount = T::DIMENSION;

        for (std::size_t i = 0; i < elementCount; ++i)
        {
            if constexpr (std::is_same_v<ValueType, double>)
            {
                EXPECT_NEAR(expected[i], static_cast<ValueType>(actual[i]), flcn::Config::DOUBLE_EPSILON);
            }
            else if constexpr (std::is_floating_point_v<ValueType>)
            {
                EXPECT_NEAR(expected[i], static_cast<ValueType>(actual[i]), flcn::Config::FLOAT_EPSILON);
            }
            else
            {
                EXPECT_EQ(expected[i], static_cast<ValueType>(actual[i]));
            }
        }
    }


    /**
     * @brief Performs a strict component-wise validation of a @ref flcn::CVec2 against discrete scalar values.
     *
     * @tparam T Numeric type of the vector and scalar components.
     *
     * @param vector The 2D vector instance being evaluated.
     * @param x      The expected value for the x-component.
     * @param y      The expected value for the y-component.
     *
     * @note Uses GoogleTest macros. Triggers a non-fatal test failure if the vector's
     *       internal state does not match the provided scalars.
     */
    template <flcn::Arithmetic T>
    void EXPECT_VEC_CONTAINS(const flcn::CVec2<T>& vector, T x, T y)
    {
        if constexpr (std::is_same_v<T, float>)
        {
            EXPECT_FLOAT_EQ(x, vector.x());
            EXPECT_FLOAT_EQ(y, vector.y());
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            EXPECT_DOUBLE_EQ(x, vector.x());
            EXPECT_DOUBLE_EQ(y, vector.y());
        }
        else
        {
            EXPECT_EQ(x, vector.x());
            EXPECT_EQ(y, vector.y());
        }
    }

    /**
     * @brief Performs a strict component-wise validation of a @ref flcn::Vec2 against discrete scalar values.
     *
     * @tparam T Numeric type of the vector and scalar components.
     *
     * @param vector The 2D vector instance being evaluated.
     * @param x      The expected value for the x-component.
     * @param y      The expected value for the y-component.
     *
     * @note Uses GoogleTest macros. Triggers a non-fatal test failure if the vector's
     *       internal state does not match the provided scalars.
     */
    template <flcn::Arithmetic T>
    void EXPECT_VEC_CONTAINS(const flcn::Vec2<T>& vector, T x, T y)
    {
        if constexpr (std::is_same_v<T, float>)
        {
            EXPECT_FLOAT_EQ(x, vector.x());
            EXPECT_FLOAT_EQ(y, vector.y());
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            EXPECT_DOUBLE_EQ(x, vector.x());
            EXPECT_DOUBLE_EQ(y, vector.y());
        }
        else
        {
            EXPECT_EQ(x, vector.x());
            EXPECT_EQ(y, vector.y());
        }
    }


    /**
     * @brief Performs a strict component-wise validation of a @ref flcn::Vec3 against discrete scalar values.
     *
     * @tparam T Numeric type of the vector and scalar components.
     *
     * @param vector The 3D vector instance being evaluated.
     * @param x      The expected value for the x-component.
     * @param y      The expected value for the y-component.
     * @param z      The expected value for the z-component.
     *
     * @note Uses GoogleTest macros. Triggers a non-fatal test failure if the vector's
     *       internal state does not match the provided scalars.
     */
    template <flcn::Arithmetic T>
    void EXPECT_VEC_CONTAINS(const flcn::Vec3<T>& vector, T x, T y, T z)
    {
        if constexpr (std::is_same_v<T, float>)
        {
            EXPECT_FLOAT_EQ(x, vector.x());
            EXPECT_FLOAT_EQ(y, vector.y());
            EXPECT_FLOAT_EQ(z, vector.z());
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            EXPECT_DOUBLE_EQ(x, vector.x());
            EXPECT_DOUBLE_EQ(y, vector.y());
            EXPECT_DOUBLE_EQ(z, vector.z());
        }
        else
        {
            EXPECT_EQ(x, vector.x());
            EXPECT_EQ(y, vector.y());
            EXPECT_EQ(z, vector.z());
        }
    }


    /**
     * @brief Performs a strict component-wise validation of a @ref flcn::Vec4 against discrete scalar values.
     *
     * @tparam T Numeric type of the vector and scalar components.
     *
     * @param vector The 4D vector instance being evaluated.
     * @param x      The expected value for the x-component.
     * @param y      The expected value for the y-component.
     * @param z      The expected value for the z-component.
     * @param w      The expected value for the w-component.
     *
     * @note Uses GoogleTest macros. Triggers a non-fatal test failure if the vector's
     *       internal state does not match the provided scalars.
     */
    template <flcn::Arithmetic T>
    void EXPECT_VEC_CONTAINS(const flcn::Vec4<T>& vector, T x, T y, T z, T w)
    {
        if constexpr (std::is_same_v<T, float>)
        {
            EXPECT_FLOAT_EQ(x, vector.x());
            EXPECT_FLOAT_EQ(y, vector.y());
            EXPECT_FLOAT_EQ(z, vector.z());
            EXPECT_FLOAT_EQ(w, vector.w());
        }
        else if constexpr (std::is_floating_point_v<T>)
        {
            EXPECT_DOUBLE_EQ(x, vector.x());
            EXPECT_DOUBLE_EQ(y, vector.y());
            EXPECT_DOUBLE_EQ(z, vector.z());
            EXPECT_DOUBLE_EQ(w, vector.w());
        }
        else
        {
            EXPECT_EQ(x, vector.x());
            EXPECT_EQ(y, vector.y());
            EXPECT_EQ(z, vector.z());
            EXPECT_EQ(w, vector.w());
        }
    }


    /**
     * @brief Validates that the provided vector contains only unit components.
     *
     * @tparam T Numeric type of the actual vector components.
     *
     * @param vector The vector being evaluated.
     *
     * @note Uses GoogleTest macros for validation. This function will trigger a non-fatal test failure
     *       if any of the vectors components are not unit.
     */
    template <flcn::Vector T>
    void EXPECT_VEC_ONE(const T& vector)
    {
        using ValueType    = T::value_type;
        ValueType expected = ValueType(1);

        constexpr std::size_t elementCount = T::DIMENSION;

        for (std::size_t i = 0; i < elementCount; ++i)
        {
            if constexpr (std::is_same_v<ValueType, float>)
            {
                EXPECT_FLOAT_EQ(expected, static_cast<ValueType>(vector[i]));
            }
            else if constexpr (std::is_same_v<ValueType, double>)
            {
                EXPECT_DOUBLE_EQ(expected, static_cast<ValueType>(vector[i]));
            }
            else
            {
                EXPECT_EQ(expected, static_cast<ValueType>(vector[i]));
            }
        }
    }


    /**
     * @brief Validates that the provided vector contains only zero components.
     *
     * @tparam T Numeric type of the actual vector components.
     *
     * @param vector The vector being evaluated.
     *
     * @note Uses GoogleTest macros for validation. This function will trigger a non-fatal test failure
     *       if any of the vectors components are not zero.
     */
    template <flcn::Vector T>
    void EXPECT_VEC_ZERO(const T& vector)
    {
        using ValueType = T::value_type;

        constexpr std::size_t elementCount = T::DIMENSION;

        for (std::size_t i = 0; i < elementCount; ++i)
        {
            if constexpr (std::is_same_v<ValueType, float>)
            {
                EXPECT_FLOAT_EQ(0.0f, static_cast<ValueType>(vector[i]));
            }
            else if constexpr (std::is_same_v<ValueType, double>)
            {
                EXPECT_DOUBLE_EQ(0.0, static_cast<ValueType>(vector[i]));
            }
            else
            {
                EXPECT_EQ(ValueType(0), static_cast<ValueType>(vector[i]));
            }
        }
    }


    /**
     * @brief Validates that the provided vector contains only @ref INFINITY components.
     *
     * @tparam T Numeric type of the actual vector components.
     *
     * @param vector The vector being evaluated.
     *
     * @note Uses GoogleTest macros for validation. This function will trigger a non-fatal test failure
     *       if any of the vectors components are not @ref `INFINITY` or `-INFINITY`.
     */
    template <flcn::Vector T>
    void EXPECT_VEC_INF(const T& vector)
    {
        constexpr std::size_t elementCount = T::DIMENSION;
        if (std::is_floating_point_v<T>)
        {
            for (std::size_t i = 0; i < elementCount; ++i)
            {
                EXPECT_TRUE(std::isinf(vector[i]));
            }
        }
    }


    /**
     * @brief Validates that two scalar values are equal within a defined numerical tolerance.
     *
     * @tparam T Numeric type of the values being compared.
     *
     * @param expected The ground-truth reference value.
     * @param actual   The value being evaluated.
     *
     * @note Uses GoogleTest macros. Triggers a non-fatal failure if the absolute difference
     *       between expected and actual exceeds the library's standard epsilon.
     */
    template <flcn::StrictArithmetic T>
    void EXPECT_MAG_EQ(T expected, T actual)
    {
        if constexpr (std::is_same_v<T, float>)
        {
            EXPECT_FLOAT_EQ(expected, actual);
        }
        else if constexpr (std::is_floating_point_v<T>)
        {
            EXPECT_DOUBLE_EQ(expected, actual);
        }
        else
        {
            EXPECT_EQ(expected, actual);
        }
    }



    // clang-format off
    /**
     * @brief Validates that a @ref flcn::Vec4 components are positive `INFINITY`.
     *
     * @param Vec The vector to evaluate.
     */
    #define EXPECT_VEC4_POS_INF(vec) \
            EXPECT_TRUE(std::isinf((vec).x()) && !std::signbit((vec).x())); \
            EXPECT_TRUE(std::isinf((vec).y()) && !std::signbit((vec).y())); \
            EXPECT_TRUE(std::isinf((vec).z()) && !std::signbit((vec).z())); \
            EXPECT_TRUE(std::isinf((vec).w()) && !std::signbit((vec).w()));


    /**
     * @brief Validates that a @ref flcn::Vec4 components are negative `INFINITY`.
     *
     * @param Vec The vector to evaluate.
     */
    #define EXPECT_VEC4_NEG_INF(vec) \
            EXPECT_TRUE(std::isinf((vec).x()) && std::signbit((vec).x())); \
            EXPECT_TRUE(std::isinf((vec).y()) && std::signbit((vec).y())); \
            EXPECT_TRUE(std::isinf((vec).z()) && std::signbit((vec).z())); \
            EXPECT_TRUE(std::isinf((vec).w()) && std::signbit((vec).w()));


    /**
     * @brief Validates that a @ref flcn::Vec3 components are positive `INFINITY`.
     *
     * @param Vec The vector to evaluate.
     */
    #define EXPECT_VEC3_POS_INF(vec) \
            EXPECT_TRUE(std::isinf((vec).x()) && !std::signbit((vec).x())); \
            EXPECT_TRUE(std::isinf((vec).y()) && !std::signbit((vec).y())); \
            EXPECT_TRUE(std::isinf((vec).z()) && !std::signbit((vec).z()));


    /**
     * @brief Validates that a @ref flcn::Vec3 components are negative `INFINITY`.
     *
     * @param Vec The vector to evaluate.
     */
    #define EXPECT_VEC3_NEG_INF(vec) \
            EXPECT_TRUE(std::isinf((vec).x()) && std::signbit((vec).x())); \
            EXPECT_TRUE(std::isinf((vec).y()) && std::signbit((vec).y())); \
            EXPECT_TRUE(std::isinf((vec).z()) && std::signbit((vec).z()));


    /**
     * @brief Validates that a @ref flcn::CVec2 components are positive `INFINITY`.
     *
     * @param Vec The vector to evaluate.
     */
    #define EXPECT_VEC2_POS_INF(vec) \
            EXPECT_TRUE(std::isinf((vec).x()) && !std::signbit((vec).x())); \
            EXPECT_TRUE(std::isinf((vec).y()) && !std::signbit((vec).y()));


    /**
     * @brief Validates that a @ref flcn::CVec2 components are negative `INFINITY`.
     *
     * @param Vec The vector to evaluate.
     */
    #define EXPECT_VEC2_NEG_INF(vec) \
            EXPECT_TRUE(std::isinf((vec).x()) && std::signbit((vec).x())); \
            EXPECT_TRUE(std::isinf((vec).y()) && std::signbit((vec).y()));
    // clang-format on

    /** @} */

} // namespace testutils
