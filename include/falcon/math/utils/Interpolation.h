#pragma once
/**
 * @file Interpolation.h
 * @author Alan Abraham P Kochumon
 * @date Created on: November 26, 2026
 *
 * @brief Vector and Quaternion interpolation functions(mix, slerp).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "falcon/math/vectors/Vec2.h"
#include "falcon/math/vectors/Vec3.h"
#include "falcon/math/vectors/Vec4.h"
#include "falcon/math/vectors/simd/Vec2.h"
#include "falcon/math/vectors/simd/Vec3.h"


/**
 *  @addtogroup Falcon_Math_Interpolation
 *  @{
 */

namespace flcn
{

    /// +---------------------------------------------------------------------------------------+
    /// |                            VEC2, VEC3, VEC4 (SCALAR)                                  |
    /// +---------------------------------------------------------------------------------------+

    /**
     * @brief Linearly interpolate between @p vecA and @p vecB by @p factor.
     * @details
     *        \f[
     *            \mathbf{mixed} = (\text{(1 - factor)} \times \mathbf{a}) - (\text{factor} \times \mathbf{b})
     *        \f]
     * @note Factor must be between 0.0f and 1.0f and must be a float.
     *
     * @tparam T The numeric type of vector. Must satisfy @ref flcn::Arithmetic.
     * @tparam F The numeric type of factor. Must satisfy `std::floating_point_v`.
     *
     * @param[in] vecA The first vector.
     * @param[in] vecB The second vector.
     * @param[in] factor The mix factor.
     * @return A 2D vector with interpolated values between @p vecA and @p vecB.
     */
    template <Arithmetic T, std::floating_point F>
    [[nodiscard]] constexpr Vec2<T> mix(const Vec2<T>& vecA, const Vec2<T>& vecB, F factor) noexcept;


    /**
     * @brief Linearly interpolate between @p vecA and @p vecB by @p factor.
     * @details
     *        \f[
     *            \mathbf{mixed} = (\text{(1 - factor)} \times \mathbf{a}) - (\text{factor} \times \mathbf{b})
     *        \f]
     * @note Factor must be between 0.0f and 1.0f and must be a float.
     *
     * @tparam T The numeric type of vector. Must satisfy @ref flcn::Arithmetic.
     * @tparam F The numeric type of factor. Must satisfy `std::floating_point_v`.
     *
     * @param[in] vecA The first vector.
     * @param[in] vecB The second vector.
     * @param[in] factor The mix factor.
     * @return A 3D vector with interpolated values between @p vecA and @p vecB.
     */
    template <Arithmetic T, std::floating_point F>
    [[nodiscard]] constexpr Vec3<T> mix(const Vec3<T>& vecA, const Vec3<T>& vecB, F factor) noexcept;


    /**
     * @brief Linearly interpolate between @p vecA and @p vecB by @p factor.
     * @details
     *        \f[
     *            \mathbf{mixed} = (\text{(1 - factor)} \times \mathbf{a}) - (\text{factor} \times \mathbf{b})
     *        \f]
     * @note Factor must be between 0.0f and 1.0f and must be a float.
     *
     * @tparam T The numeric type of vector. Must satisfy @ref flcn::Arithmetic.
     * @tparam F The numeric type of factor. Must satisfy `std::floating_point_v`.
     *
     * @param[in] vecA The first vector.
     * @param[in] vecB The second vector.
     * @param[in] factor The mix factor.
     * @return A 4D vector with interpolated values between @p vecA and @p vecB.
     */
    template <Arithmetic T, std::floating_point F>
    [[nodiscard]] constexpr Vec4<T> mix(const Vec4<T>& vecA, const Vec4<T>& vecB, F factor) noexcept;



    /// +---------------------------------------------------------------------------------------+
    /// |                            VEC2, VEC3, VEC4 (SIMD)                                    |
    /// +---------------------------------------------------------------------------------------+

    /**
     * @brief Linearly interpolate between @p vecA and @p vecB by @p factor.
     * @details
     *        \f[
     *            \mathbf{mixed} = (\text{(1 - factor)} \times \mathbf{a}) - (\text{factor} \times \mathbf{b})
     *        \f]
     * @note Factor must be between 0.0f and 1.0f and must be a float.
     *
     * @tparam T The numeric type of the vectors and the factor. Must satisfy `std::floating_point_v`.
     * @tparam F The numeric type of factor. Must satisfy `std::floating_point_v`.
     *
     * @param[in] vecA The first vector.
     * @param[in] vecB The second vector.
     * @param[in] factor The mix factor.
     * @return A 2D vector (SIMD) with interpolated values between @p vecA and @p vecB.
     */
    template <std::floating_point T, std::floating_point F>
    [[nodiscard]] constexpr simd::Vec2<T> mix(const simd::Vec2<T>& vecA, const simd::Vec2<T>& vecB,
                                                     F factor) noexcept;


    /**
     * @brief Linearly interpolate between @p vecA and @p vecB by @p factor.
     * @details
     *        \f[
     *            \mathbf{mixed} = (\text{(1 - factor)} \times \mathbf{a}) - (\text{factor} \times \mathbf{b})
     *        \f]
     * @note Factor must be between 0.0f and 1.0f and must be a float.
     *
     * @tparam T The numeric type of the vectors and the factor. Must satisfy `std::floating_point_v`.
     * @tparam F The numeric type of factor. Must satisfy `std::floating_point_v`.
     *
     * @param[in] vecA The first vector.
     * @param[in] vecB The second vector.
     * @param[in] factor The mix factor.
     * @return A 3D vector (SIMD) with interpolated values between @p vecA and @p vecB.
     */
    template <std::floating_point T, std::floating_point F>
    [[nodiscard]] constexpr simd::Vec3<T> mix(const simd::Vec3<T>& vecA, const simd::Vec3<T>& vecB,
                                                     F factor) noexcept;



    /// +---------------------------------------------------------------------------------------+
    /// |                                    QUATERNION                                         |
    /// +---------------------------------------------------------------------------------------+

} // namespace flcn

/** @} */

#include "Interpolation.tpp"
