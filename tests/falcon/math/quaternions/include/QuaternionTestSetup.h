#pragma once
/**
 * @file QuaternionTestSetup.h
 * @author Alan Abraham P Kochumon
 * @date Created on: August 1, 2026
 *
 * @brief Test setup common to quaternion operations.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "CommonSetup.h"

#include <cmath>
#include <falcon/math/Quaternion.h>
#include <type_traits>



/**
 * @addtogroup Quaternion_Utils
 * @{
 */

#define EXPECT_QUAT_EQ(q1, q2)                                                                                         \
    do                                                                                                                 \
    {                                                                                                                  \
        flcn::testutils::expectQuaternionEq(q1, q2);                                                                    \
    } while (0)


#define EXPECT_QUAT_CONTAINS(quat, x, y, z, w)                                                                         \
    do                                                                                                                 \
    {                                                                                                                  \
        flcn::testutils::expectQuaternionContains(quat, x, y, z, w);                                                    \
    } while (0)


#define EXPECT_QUAT_INF(quat)                                                                                          \
    do                                                                                                                 \
    {                                                                                                                  \
        flcn::testutils::expectQuatInf(quat);                                                                           \
    } while (0)


namespace flcn::testutils
{
    /**
     * @brief Perform a component-wise equality between two quaternions.
     *
     * @tparam T Numeric type of the expected quaternion components.
     * @tparam U Numeric type of the actual quaternion components.
     *
     * @param expected The quaternion serving as the reference for comparison.
     * @param actual   The quaternion being evaluated.
     *
     * @note Uses GoogleTest macros for validation. This function will trigger a non-fatal test failure
     *       if the quaternions are not equal.
     */
    template <Arithmetic T, Arithmetic U>
    constexpr void expectQuaternionEq(const Quaternion<T>& expected, const Quaternion<U>& actual)
    {
        using ValueType = std::common_type_t<T, U>;
        if constexpr (std::is_same_v<ValueType, double>)
        {
            EXPECT_DOUBLE_EQ(expected.x(), static_cast<ValueType>(actual.x()));
            EXPECT_DOUBLE_EQ(expected.y(), static_cast<ValueType>(actual.y()));
            EXPECT_DOUBLE_EQ(expected.z(), static_cast<ValueType>(actual.z()));
            EXPECT_DOUBLE_EQ(expected.w(), static_cast<ValueType>(actual.w()));
        }
        else if constexpr (std::is_floating_point_v<ValueType>)
        {
            EXPECT_FLOAT_EQ(expected.x(), static_cast<ValueType>(actual.x()));
            EXPECT_FLOAT_EQ(expected.y(), static_cast<ValueType>(actual.y()));
            EXPECT_FLOAT_EQ(expected.z(), static_cast<ValueType>(actual.z()));
            EXPECT_FLOAT_EQ(expected.w(), static_cast<ValueType>(actual.w()));
        }
        else
        {
            EXPECT_EQ(expected.x(), static_cast<ValueType>(actual.x()));
            EXPECT_EQ(expected.y(), static_cast<ValueType>(actual.y()));
            EXPECT_EQ(expected.z(), static_cast<ValueType>(actual.z()));
            EXPECT_EQ(expected.w(), static_cast<ValueType>(actual.w()));
        }
    }


    /**
     * @brief Performs a strict component-wise validation of a @ref flcn::Quaternion against discrete scalar values.
     *
     * @tparam T Numeric type of the quaternion's vector and scalar components.
     *
     * @param quat   The quaternion instance being evaluated.
     * @param x      The expected value for the x-component.
     * @param y      The expected value for the y-component.
     * @param z      The expected value for the z-component.
     * @param w      The expected value for the w-component.
     *
     * @note Uses GoogleTest macros. Triggers a non-fatal test failure if the quaternions's
     *       internal state does not match the provided scalars.
     */
    template <Arithmetic T>
    void expectQuaternionContains(const Quaternion<T>& quat, T x, T y, T z, T w)
    {
        if constexpr (std::is_same_v<T, float>)
        {
            EXPECT_FLOAT_EQ(x, quat.x());
            EXPECT_FLOAT_EQ(y, quat.y());
            EXPECT_FLOAT_EQ(z, quat.z());
            EXPECT_FLOAT_EQ(w, quat.w());
        }
        else if constexpr (std::is_floating_point_v<T>)
        {
            EXPECT_DOUBLE_EQ(x, quat.x());
            EXPECT_DOUBLE_EQ(y, quat.y());
            EXPECT_DOUBLE_EQ(z, quat.z());
            EXPECT_DOUBLE_EQ(w, quat.w());
        }
        else
        {
            EXPECT_EQ(x, quat.x());
            EXPECT_EQ(y, quat.y());
            EXPECT_EQ(z, quat.z());
            EXPECT_EQ(w, quat.w());
        }
    }


    /**
     * @brief Validates that the provided quaternion contains only @ref INFINITY components.
     *
     * @tparam T Numeric type of the actual quaternion components.
     *
     * @param quat The quaternion being evaluated.
     *
     * @note Uses GoogleTest macros for validation. This function will trigger a non-fatal test failure
     *       if any of the quaternion components are not @ref `INFINITY` or `-INFINITY`.
     */
    template <Arithmetic T>
    void expectQuatInf(const Quaternion<T>& quat)
    {
        if (std::is_floating_point_v<T>)
        {
            EXPECT_TRUE(std::isinf(quat.x()) || std::isinf(quat.y()) || std::isinf(quat.z()) || std::isinf(quat.w()));
        }
    }

} // namespace flcn::testutils
