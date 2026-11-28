#pragma once
/**
 * @file Bounds.h
 * @author Alan Abraham P Kochumon
 * @date Created on: November 26, 2026
 *
 * @brief Math functions for computing mathematical bounds and clamping.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "falcon/math/vectors/Vec2.h"
#include "falcon/math/vectors/Vec3.h"
#include "falcon/math/vectors/Vec4.h"
#include "falcon/math/vectors/simd/Vec2.h"
#include "falcon/math/vectors/simd/Vec3.h"


/**
 *  @addtogroup Falcon_Math_Bounds
 *  @{
 */

namespace flcn
{

    /// +---------------------------------------------------------------------------------------+
    /// |                            VEC2, VEC3, VEC4 (SCALAR)                                  |
    /// +---------------------------------------------------------------------------------------+

    /**
     * @brief Select the minimum components from each vector.
     * @tparam T The numeric type of the vectors. Must satisfy @ref Arithmetic.
     * @param vecA The first vector.
     * @param vecB The second vector.
     * @return A 2D vector with the minimum components of the two.
     */
    template <Arithmetic T>
    [[nodiscard]] constexpr Vec2<T> min(const Vec2<T>& vecA, const Vec2<T>& vecB) noexcept;


    /**
     * @brief Select the maximum components from each vector.
     * @tparam T The numeric type of the vectors. Must satisfy @ref Arithmetic.
     * @param vecA The first vector.
     * @param vecB The second vector.
     * @return A 2D vector with the maximum components of the two.
     */
    template <Arithmetic T>
    [[nodiscard]] constexpr Vec2<T> max(const Vec2<T>& vecA, const Vec2<T>& vecB) noexcept;


    /**
     * @brief Select the minimum components from each vector.
     * @tparam T The numeric type of the vectors. Must satisfy @ref Arithmetic.
     * @param vecA The first vector.
     * @param vecB The second vector.
     * @return A 3D vector with the minimum components of the two.
     */
    template <Arithmetic T>
    [[nodiscard]] constexpr Vec3<T> min(const Vec3<T>& vecA, const Vec3<T>& vecB) noexcept;


    /**
     * @brief Select the maximum components from each vector.
     * @tparam T The numeric type of the vectors. Must satisfy @ref Arithmetic.
     * @param vecA The first vector.
     * @param vecB The second vector.
     * @return A 3D vector with the maximum components of the two.
     */
    template <Arithmetic T>
    [[nodiscard]] constexpr Vec3<T> max(const Vec3<T>& vecA, const Vec3<T>& vecB) noexcept;


    /**
     * @brief Select the minimum components from each vector.
     * @tparam T The numeric type of the vectors. Must satisfy @ref Arithmetic.
     * @param vecA The first vector.
     * @param vecB The second vector.
     * @return A 4D vector with the minimum components of the two.
     */
    template <Arithmetic T>
    [[nodiscard]] constexpr Vec4<T> min(const Vec4<T>& vecA, const Vec4<T>& vecB) noexcept;


    /**
     * @brief Select the maximum components from each vector.
     * @tparam T The numeric type of the vectors. Must satisfy @ref Arithmetic.
     * @param vecA The first vector.
     * @param vecB The second vector.
     * @return A 4D vector with the maximum components of the two.
     */
    template <Arithmetic T>
    [[nodiscard]] constexpr Vec4<T> max(const Vec4<T>& vecA, const Vec4<T>& vecB) noexcept;



    /// +---------------------------------------------------------------------------------------+
    /// |                             VEC2, VEC3, VEC4 (SIMD)                                   |
    /// +---------------------------------------------------------------------------------------+

    /**
     * @brief Select the minimum components from each vector.
     * @tparam T The numeric type of the vectors. Must satisfy @ref Arithmetic.
     * @param vecA The first vector.
     * @param vecB The second vector.
     * @return A 2D vector with the minimum components of the two.
     */
    template <Arithmetic T>
    [[nodiscard]] constexpr simd::Vec2<T> min(const simd::Vec2<T>& vecA, const simd::Vec2<T>& vecB) noexcept;


    /**
     * @brief Select the maximum components from each vector.
     * @tparam T The numeric type of the vectors. Must satisfy @ref Arithmetic.
     * @param vecA The first vector.
     * @param vecB The second vector.
     * @return A 2D vector with the maximum components of the two.
     */
    template <Arithmetic T>
    [[nodiscard]] constexpr simd::Vec2<T> max(const simd::Vec2<T>& vecA, const simd::Vec2<T>& vecB) noexcept;


    /**
     * @brief Select the minimum components from each vector.
     * @tparam T The numeric type of the vectors. Must satisfy @ref Arithmetic.
     * @param vecA The first vector.
     * @param vecB The second vector.
     * @return A 3D vector with the minimum components of the two.
     */
    template <Arithmetic T>
    [[nodiscard]] constexpr simd::Vec3<T> min(const simd::Vec3<T>& vecA, const simd::Vec3<T>& vecB) noexcept;


    /**
     * @brief Select the maximum components from each vector.
     * @tparam T The numeric type of the vectors. Must satisfy @ref Arithmetic.
     * @param vecA The first vector.
     * @param vecB The second vector.
     * @return A 3D vector with the maximum components of the two.
     */
    template <Arithmetic T>
    [[nodiscard]] constexpr simd::Vec3<T> max(const simd::Vec3<T>& vecA, const simd::Vec3<T>& vecB) noexcept;

} // namespace flcn

/** @} */

#include "Bounds.tpp"
