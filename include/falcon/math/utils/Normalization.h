#pragma once
/**
 * @file Normalization.h
 * @author Alan Abraham P Kochumon
 * @date Created on: November 28, 2026
 *
 * @brief Vector normalization.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


namespace flcn
{
    /// +---------------------------------------------------------------------------------------+
    /// |                            VEC2, VEC3, VEC4 (SCALAR)                                  |
    /// +---------------------------------------------------------------------------------------+




    /// +---------------------------------------------------------------------------------------+
    /// |                             VEC2, VEC3, VEC4 (SIMD)                                   |
    /// +---------------------------------------------------------------------------------------+


    // ------------------------ VEC2(SIMD) ------------------------



    // ------------------------ VEC3(SIMD) ------------------------
    /**
     * @brief Compute the normalized (unit) form of @p Vec.
     *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
     *
     * @note Restricted to floating point types via @ref FPArithmetic.
     * @note Performs assertion for division by zero, resulting from zero-length vector, in **Debug mode**.
     *
     * @param[in] vec The vector to normalize.
     *
     * @return A new @ref Vec3 with a magnitude of 1.0.
     */
    [[nodiscard]] static constexpr Vec3 normalize(const Vec3& vec) noexcept
        requires FPArithmetic<T>;


    /**
     * @brief Compute the normalized (unit) form of @p Vec.
     *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
     *
     * @note This is a safe operation. If the vector's magnitude falls below the internal
     *       epsilon, or if it contains NaN components, division by zero is bypassed.
     * @note Restricted to floating point types via @ref FPArithmetic.
     *
     * @param[in] vec The vector to be normalized.
     *
     * @return A @ref flcn::simd::Vec3 with a magnitude of 1.0, or a zero-vector if the original
     *         magnitude is below the epsilon threshold or if the vector has NaN(Not-a-Number) component(s).
     */
    [[nodiscard]] static constexpr Vec3 safeNormalize(const Vec3& vec) noexcept
        requires FPArithmetic<T>;


    /**
     * @brief Compute the normalized (unit) form of @p Vec and
     *        set @p status to the normalization operation result.
     *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
     *
     * @note This is a safe operation. If the vector's magnitude falls below the internal
     *       epsilon, or if it contains NaN components, division by zero is bypassed.
     * @note Restricted to floating point types via @ref FPArithmetic.
     *
     * @param[in] vec     The vector to be normalized.
     * @param[out] status The status flag to store the status of the current operation result.*
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return A @ref flcn::simd::Vec3 with a magnitude of 1.0, or a zero-vector if the original
     magnitude is below the
     *         epsilon threshold or if the vector has NaN(Not-a-Number) component(s).
     */
    [[nodiscard]] static constexpr Vec3 tryNormalize(const Vec3& vec, OperationStatus& status) noexcept
        requires FPArithmetic<T>;



    // ------------------------ VEC4(SIMD) ------------------------


} // namespace flcn


#include "Normalization.tpp"
