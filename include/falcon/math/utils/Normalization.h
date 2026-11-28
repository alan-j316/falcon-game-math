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


#include "falcon/math/vectors/Vec2.h"
#include "falcon/math/vectors/Vec3.h"
#include "falcon/math/vectors/Vec4.h"
#include "falcon/math/vectors/simd/Vec2.h"
#include "falcon/math/vectors/simd/Vec3.h"


/**
 *  @addtogroup Falcon_Math_Normalization
 *  @{
 */

namespace flcn
{
    /// +---------------------------------------------------------------------------------------+
    /// |                            VEC2, VEC3, VEC4 (SCALAR)                                  |
    /// +---------------------------------------------------------------------------------------+

    // ------------------------ VEC2(SCALAR) ------------------------
    /**
     * @brief Compute the normalized (unit) form of @p Vec.
     *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
     *
     * @note To maintain precision, result components are promoted to their
     *       corresponding floating-point representation via @ref Magnitude.
     * @note Performs assertion for division by zero, resulting from zero-length vector, in **Debug mode**.
     *
     * @param[in] vec The vector to normalize.
     *
     * @return A new @ref Vec2 with a magnitude of 1.0.
     */
    template <StrictArithmetic T>
    [[nodiscard]] constexpr Vec2<Magnitude<T>> normalize(const Vec2<T>& vec) noexcept;


    /**
     * @brief Compute the normalized (unit) form of @p Vec.
     *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
     *
     * @note This is a safe operation. If the vector's magnitude falls below the internal
     *       epsilon, or if it contains NaN components, division by zero is bypassed.
     * @note To maintain precision, result components are promoted to their
     *       corresponding floating-point representation via @ref Magnitude.
     *
     * @param[in] vec The vector to be normalized.
     *
     * @return A @ref flcn::Vec2 with a magnitude of 1.0, or a zero-vector if the original magnitude is below the
     *         epsilon threshold or if the vector has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T>
    [[nodiscard]] constexpr Vec2<Magnitude<T>> safeNormalize(const Vec2<T>& vec) noexcept
        requires StrictArithmetic<T>;


    /**
     * @brief Compute the normalized (unit) form of @p Vec and
     *        set @p status to the normalization operation result.
     *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
     *
     * @note This is a safe operation. If the vector's magnitude falls below the internal
     *       epsilon, or if it contains NaN components, division by zero is bypassed.
     * @note To maintain precision, result components are promoted to their
     *       corresponding floating-point representation via @ref Magnitude.
     *
     * @param[in] vec     The vector to be normalized.
     * @param[out] status The status flag to store the status of the current operation result.*
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return A @ref flcn::Vec2 with a magnitude of 1.0, or a zero-vector if the original magnitude is below the
     *         epsilon threshold or if the vector has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T>
    [[nodiscard]] constexpr Vec2<Magnitude<T>> tryNormalize(const Vec2<T>& vec,
                                                                   OperationStatus& status) noexcept;


    // ------------------------ VEC3(SCALAR) ------------------------

    /**
     * @brief Compute the normalized (unit) form of @p Vec.
     *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
     *
     * @note To maintain precision, result components are promoted to their
     *       corresponding floating-point representation via @ref Magnitude.
     * @note Performs assertion for division by zero, resulting from zero-length vector, in **Debug mode**.
     *
     * @param[in] vec The vector to normalize.
     *
     * @return A new @ref Vec3 with a magnitude of 1.0.
     */
    template <StrictArithmetic T>
    [[nodiscard]] constexpr Vec3<Magnitude<T>> normalize(const Vec3<T>& vec) noexcept;


    /**
     * @brief Compute the normalized (unit) form of @p Vec.
     *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
     *
     * @note This is a safe operation. If the vector's magnitude falls below the internal
     *       epsilon, or if it contains NaN components, division by zero is bypassed.
     * @note To maintain precision, result components are promoted to their
     *       corresponding floating-point representation via @ref Magnitude.
     *
     * @param[in] vec The vector to be normalized.
     *
     * @return A @ref flcn::Vec3 with a magnitude of 1.0, or a zero-vector if the original magnitude is below the
     *         epsilon threshold or if the vector has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T>
    [[nodiscard]] constexpr Vec3<Magnitude<T>> safeNormalize(const Vec3<T>& vec) noexcept
        requires StrictArithmetic<T>;


    /**
     * @brief Compute the normalized (unit) form of @p Vec and
     *        set @p status to the normalization operation result.
     *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
     *
     * @note This is a safe operation. If the vector's magnitude falls below the internal
     *       epsilon, or if it contains NaN components, division by zero is bypassed.
     * @note To maintain precision, result components are promoted to their
     *       corresponding floating-point representation via @ref Magnitude.
     *
     * @param[in] vec     The vector to be normalized.
     * @param[out] status The status flag to store the status of the current operation result.*
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return A @ref flcn::Vec3 with a magnitude of 1.0, or a zero-vector if the original magnitude is below the
     *         epsilon threshold or if the vector has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T>
    [[nodiscard]] constexpr Vec3<Magnitude<T>> tryNormalize(const Vec3<T>& vec,
                                                                   OperationStatus& status) noexcept;


    // ------------------------ VEC4(SCALAR) ------------------------

/**
     * @brief Compute the normalized (unit) form of @p Vec.
     *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
     *
     * @note To maintain precision, result components are promoted to their
     *       corresponding floating-point representation via @ref Magnitude.
     * @note Performs assertion for division by zero, resulting from zero-length vector, in **Debug mode**.
     *
     * @param[in] vec The vector to normalize.
     *
     * @return A new @ref Vec4 with a magnitude of 1.0.
     */
    template <StrictArithmetic T>
    [[nodiscard]] constexpr Vec4<Magnitude<T>> normalize(const Vec4<T>& vec) noexcept;


    /**
     * @brief Compute the normalized (unit) form of @p Vec.
     *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
     *
     * @note This is a safe operation. If the vector's magnitude falls below the internal
     *       epsilon, or if it contains NaN components, division by zero is bypassed.
     * @note To maintain precision, result components are promoted to their
     *       corresponding floating-point representation via @ref Magnitude.
     *
     * @param[in] vec The vector to be normalized.
     *
     * @return A @ref flcn::Vec4 with a magnitude of 1.0, or a zero-vector if the original magnitude is below the
     *         epsilon threshold or if the vector has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T>
    [[nodiscard]] constexpr Vec4<Magnitude<T>> safeNormalize(const Vec4<T>& vec) noexcept
        requires StrictArithmetic<T>;


    /**
     * @brief Compute the normalized (unit) form of @p Vec and
     *        set @p status to the normalization operation result.
     *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
     *
     * @note This is a safe operation. If the vector's magnitude falls below the internal
     *       epsilon, or if it contains NaN components, division by zero is bypassed.
     * @note To maintain precision, result components are promoted to their
     *       corresponding floating-point representation via @ref Magnitude.
     *
     * @param[in] vec     The vector to be normalized.
     * @param[out] status The status flag to store the status of the current operation result.*
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return A @ref flcn::Vec4 with a magnitude of 1.0, or a zero-vector if the original magnitude is below the
     *         epsilon threshold or if the vector has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T>
    [[nodiscard]] constexpr Vec4<Magnitude<T>> tryNormalize(const Vec4<T>& vec,
                                                                   OperationStatus& status) noexcept;



    /// +---------------------------------------------------------------------------------------+
    /// |                             VEC2, VEC3, VEC4 (SIMD)                                   |
    /// +---------------------------------------------------------------------------------------+


    // ------------------------ VEC2(SIMD) ------------------------
    /**
     * @brief Compute the normalized (unit) form of @p Vec.
     *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
     *
     * @note Restricted to floating point types via @ref FPArithmetic.
     * @note Performs assertion for division by zero, resulting from zero-length vector, in **Debug mode**.
     *
     * @param[in] vec The vector to normalize.
     *
     * @return A new @ref Vec2 with a magnitude of 1.0.
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec2<T> normalize(const simd::Vec2<T>& vec) noexcept;
    template <FPArithmetic T>
    constexpr simd::Vec2<T> normalize(const simd::Vec2<T>& vec) noexcept;


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
     * @return A @ref flcn::simd::Vec2 with a magnitude of 1.0, or a zero-vector if the original
     *         magnitude is below the epsilon threshold or if the vector has NaN(Not-a-Number) component(s).
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec2<T> safeNormalize(const simd::Vec2<T>& vec) noexcept;


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
     * @return A @ref flcn::simd::Vec2 with a magnitude of 1.0, or a zero-vector if the original
     *         magnitude is below the epsilon threshold or if the vector has NaN(Not-a-Number) component(s).
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec2<T> tryNormalize(const simd::Vec2<T>& vec,
                                                              OperationStatus& status) noexcept;



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
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec3<T> normalize(const simd::Vec3<T>& vec) noexcept;


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
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec3<T> safeNormalize(const simd::Vec3<T>& vec) noexcept;


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
     *         magnitude is below the epsilon threshold or if the vector has NaN(Not-a-Number) component(s).
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec3<T> tryNormalize(const simd::Vec3<T>& vec,
                                                              OperationStatus& status) noexcept;



    // ------------------------ VEC4(SIMD) ------------------------

} // namespace flcn

/** @} */

#include "Normalization.tpp"
