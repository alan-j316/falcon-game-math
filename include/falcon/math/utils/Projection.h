#pragma once
/**
 * @file Projection.h
 * @author Alan Abraham P Kochumon
 * @date Created on: November 28, 2026
 *
 * @brief Vector projection and rejection.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "falcon/math/vectors/Vec2.h"
#include "falcon/math/vectors/Vec3.h"
#include "falcon/math/vectors/Vec4.h"
#include "falcon/math/vectors/simd/Vec2.h"
#include "falcon/math/vectors/simd/Vec3.h"


/**
 *  @addtogroup Falcon_Math_Projection
 *  @{
 */

namespace flcn
{
    /// +---------------------------------------------------------------------------------------+
    /// |                            VEC2, VEC3, VEC4 (SCALAR)                                  |
    /// +---------------------------------------------------------------------------------------+

    // ------------------------ VEC2(SCALAR) ------------------------

    /**
     * @brief Project the @p Vec vector onto the @p onto vector.
     *        \f$
     *          \text{proj}_{\mathbf{b}} \mathbf{a} =
     *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
     *        \f$
     *
     * @note Promotes the result to the wider type using @ref PromotedFloatVec2<T, U>.
     * @note If @p onto is normalized, use @ref projectNorm as it is a faster implementation for unit vectors.
     * @note Performs assertion for division by zero, resulting from zero-length vector, in **Debug mode**.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to project.
     * @param[in] onto The vector to project onto.
     *
     * @return The projected @ref Vec2.
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedFloatVec2<T, U> project(const Vec2<T>& vec, const Vec2<U>& onto) noexcept;


    /**
     * @brief Project the @p Vec vector onto the **unit** @p onto vector.
     *        \f$
     *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
     *        \f$
     *
     * @note Promotes the result to the wider type using @ref PromotedFloatVec2<T, U>.
     * @note Only use this method if @p onto is normalized. If not, use @ref project.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to project.
     * @param[in] onto The vector to project onto.
     *
     * @return The projected @ref Vec2.
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedVec2<T, U> projectNorm(const Vec2<T>& vec, const Vec2<U>& onto) noexcept;


    /**
     * @brief Project the @p Vec vector onto the @p onto vector.
     *        \f$
     *          \text{proj}_{\mathbf{b}} \mathbf{a} =
     *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
     *        \f$
     *
     * @note This is a safe operation. If the @p onto vector's magnitude falls below the internal
     *       epsilon, or if either vector contains NaN components, projection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedFloatVec2<T, U>.
     * @note If @p onto is normalized, use @ref safeProjectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to project.
     * @param[in] onto The vector to project onto.
     *
     * @return The projected @ref Vec2 or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedFloatVec2<T, U> safeProject(const Vec2<T>& vec, const Vec2<U>& onto) noexcept;


    /**
     * @brief Project the @p Vec vector onto the **unit** @p onto vector.
     *        \f$
     *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
     *        \f$
     *
     * @note This is a safe operation. If either vector contains NaN components, projection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedVec2<T, U>.
     * @note Only use this method if @p onto is normalized. If not, use @ref safeProject.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to project.
     * @param[in] onto The vector to project onto.
     *
     * @return The projected @ref Vec2 or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedVec2<T, U> safeProjectNorm(const Vec2<T>& vec, const Vec2<U>& onto) noexcept;


    /**
     * @brief Project the @p Vec vector onto the @p onto vector and set @p status to the
     *        projection operation result.
     *        \f$
     *          \text{proj}_{\mathbf{b}} \mathbf{a} =
     *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
     *        \f$
     *
     * @note This is a safe operation. If the @p onto vector's magnitude falls below the internal
     *       epsilon, or if either vector contains NaN components, projection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedFloatVec2<T, U>.
     * @note If @p onto is normalized, use @ref tryProjectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec     The vector to project.
     * @param[in] onto    The vector to project onto.
     * @param[out] status The status flag to store the status of the current operation result.
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return The projected @ref Vec2 or a zero-vector if projected onto a zero-length vector or if either
     *         vector has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedFloatVec2<T, U> tryProject(const Vec2<T>& vec, const Vec2<U>& onto,
                                                               OperationStatus& status) noexcept;


    /**
     * @brief Project the @p Vec vector onto the **unit** @p onto vector and set @p status to the
     *        projection operation result.
     *        \f$
     *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
     *        \f$
     *
     * @note This is a safe operation. If either vector contains NaN components, projection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedVec2<T, U>.
     * @note To maintain precision, result components are promoted to their
     *       corresponding floating-point representation via @ref Magnitude.
     * @note Only use this method if @p onto is normalized. If not, use @ref tryProject.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec     The vector to project.
     * @param[in] onto    The vector to project onto.
     * @param[out] status The status flag to store the status of the current operation result.
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return The projected @ref Vec2 or a zero-vector if projected onto a zero-length vector or if either
     *         vector has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedVec2<T, U> tryProjectNorm(const Vec2<T>& vec, const Vec2<U>& onto,
                                                              OperationStatus& status) noexcept;


    /**
     * @brief Reject the @p Vec vector from the @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note Promotes the result to the wider type using @ref PromotedFloatVec2<T, U>.
     * @note If @p from is normalized, use @ref rejectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to be rejected.
     * @param[in] from The vector to reject from.
     *
     * @return The perpendicular @ref Vec2 component.
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedFloatVec2<T, U> reject(const Vec2<T>& vec, const Vec2<U>& from) noexcept;


    /**
     * @brief Reject the @p Vec vector from the **unit** @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note Promotes the result to the wider type using @ref PromotedVec2<T, U>.
     * @note Only use this method if @p from is normalized. If not, use @ref reject.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to be rejected.
     * @param[in] from The vector to reject from.
     *
     * @return The perpendicular @ref Vec2 component.
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedVec2<T, U> rejectNorm(const Vec2<T>& vec, const Vec2<U>& from) noexcept;


    /**
     * @brief Reject the @p Vec vector from the @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note This is a safe operation. If the @p from vector's magnitude falls below the internal
     *       epsilon, or if either vector contains NaN components, rejection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedFloatVec2<T, U>.
     * @note If @p from is normalized, use @ref safeRejectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to reject.
     * @param[in] from The vector to reject from.
     *
     * @return The perpendicular @ref Vec2 component or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedFloatVec2<T, U> safeReject(const Vec2<T>& vec, const Vec2<U>& from) noexcept;


    /**
     * @brief Reject the @p Vec vector from the **unit** @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note This is a safe operation. If either vector contains NaN components, rejection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedVec2<T, U>.
     * @note Only use this method if @p from is normalized. If not, use @ref safeReject.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to reject.
     * @param[in] from The vector to reject from.
     *
     * @return The perpendicular @ref Vec2 component or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedVec2<T, U> safeRejectNorm(const Vec2<T>& vec, const Vec2<U>& from) noexcept;


    /**
     * @brief Reject the @p Vec vector from the @p from vector and set @p status to the result of
     *        rejection operation.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note This is a safe operation. If the @p from vector's magnitude falls below the internal
     *       epsilon, or if either vector contains NaN components, rejection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedFloatVec2<T, U>.
     * @note If @p from is normalized, use @ref tryRejectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec     The vector to reject.
     * @param[in] from    The vector to reject from.
     * @param[out] status The status flag to store the status of the current operation result.
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return The perpendicular @ref Vec2 component or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedFloatVec2<T, U> tryReject(const Vec2<T>& vec, const Vec2<U>& from,
                                                              OperationStatus& status) noexcept;


    /**
     * @brief Reject the @p Vec vector from the **unit** @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note This is a safe operation. If either vector contains NaN components, rejection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedVec2<T, U>.
     * @note Only use this method if @p from is normalized. If not, use @ref tryReject.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec     The vector to reject.
     * @param[in] from    The vector to reject from.
     * @param[out] status The status flag to store the status of the current operation result.
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return The perpendicular @ref Vec2 component or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedVec2<T, U> tryRejectNorm(const Vec2<T>& vec, const Vec2<U>& from,
                                                             OperationStatus& status) noexcept;


    // ------------------------ VEC3(SCALAR) ------------------------
    /**
     * @brief Project the @p Vec vector onto the @p onto vector.
     *        \f$
     *          \text{proj}_{\mathbf{b}} \mathbf{a} =
     *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
     *        \f$
     *
     * @note Promotes the result to the wider type using @ref PromotedFloatVec3<T, U>.
     * @note If @p onto is normalized, use @ref projectNorm as it is a faster implementation for unit vectors.
     * @note Performs assertion for division by zero, resulting from zero-length vector, in **Debug mode**.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to project.
     * @param[in] onto The vector to project onto.
     *
     * @return The projected @ref Vec3.
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedFloatVec3<T, U> project(const Vec3<T>& vec, const Vec3<U>& onto) noexcept;


    /**
     * @brief Project the @p Vec vector onto the **unit** @p onto vector.
     *        \f$
     *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
     *        \f$
     *
     * @note Promotes the result to the wider type using @ref PromotedFloatVec3<T, U>.
     * @note Only use this method if @p onto is normalized. If not, use @ref project.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to project.
     * @param[in] onto The vector to project onto.
     *
     * @return The projected @ref Vec3.
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedVec3<T, U> projectNorm(const Vec3<T>& vec, const Vec3<U>& onto) noexcept;


    /**
     * @brief Project the @p Vec vector onto the @p onto vector.
     *        \f$
     *          \text{proj}_{\mathbf{b}} \mathbf{a} =
     *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
     *        \f$
     *
     * @note This is a safe operation. If the @p onto vector's magnitude falls below the internal
     *       epsilon, or if either vector contains NaN components, projection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedFloatVec3<T, U>.
     * @note If @p onto is normalized, use @ref safeProjectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to project.
     * @param[in] onto The vector to project onto.
     *
     * @return The projected @ref Vec3 or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedFloatVec3<T, U> safeProject(const Vec3<T>& vec, const Vec3<U>& onto) noexcept;


    /**
     * @brief Project the @p Vec vector onto the **unit** @p onto vector.
     *        \f$
     *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
     *        \f$
     *
     * @note This is a safe operation. If either vector contains NaN components, projection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedVec3<T, U>.
     * @note Only use this method if @p onto is normalized. If not, use @ref safeProject.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to project.
     * @param[in] onto The vector to project onto.
     *
     * @return The projected @ref Vec3 or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedVec3<T, U> safeProjectNorm(const Vec3<T>& vec, const Vec3<U>& onto) noexcept;


    /**
     * @brief Project the @p Vec vector onto the @p onto vector and set @p status to the
     *        projection operation result.
     *        \f$
     *          \text{proj}_{\mathbf{b}} \mathbf{a} =
     *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
     *        \f$
     *
     * @note This is a safe operation. If the @p onto vector's magnitude falls below the internal
     *       epsilon, or if either vector contains NaN components, projection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedFloatVec3<T, U>.
     * @note If @p onto is normalized, use @ref tryProjectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec     The vector to project.
     * @param[in] onto    The vector to project onto.
     * @param[out] status The status flag to store the status of the current operation result.
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return The projected @ref Vec3 or a zero-vector if projected onto a zero-length vector or if either
     *         vector has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedFloatVec3<T, U> tryProject(const Vec3<T>& vec, const Vec3<U>& onto,
                                                               OperationStatus& status) noexcept;


    /**
     * @brief Project the @p Vec vector onto the **unit** @p onto vector and set @p status to the
     *        projection operation result.
     *        \f$
     *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
     *        \f$
     *
     * @note This is a safe operation. If either vector contains NaN components, projection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedVec3<T, U>.
     * @note To maintain precision, result components are promoted to their
     *       corresponding floating-point representation via @ref Magnitude.
     * @note Only use this method if @p onto is normalized. If not, use @ref tryProject.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec     The vector to project.
     * @param[in] onto    The vector to project onto.
     * @param[out] status The status flag to store the status of the current operation result.
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return The projected @ref Vec3 or a zero-vector if projected onto a zero-length vector or if either
     *         vector has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedVec3<T, U> tryProjectNorm(const Vec3<T>& vec, const Vec3<U>& onto,
                                                              OperationStatus& status) noexcept;


    /**
     * @brief Reject the @p Vec vector from the @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note Promotes the result to the wider type using @ref PromotedFloatVec3<T, U>.
     * @note If @p from is normalized, use @ref rejectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to be rejected.
     * @param[in] from The vector to reject from.
     *
     * @return The perpendicular @ref Vec3 component.
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedFloatVec3<T, U> reject(const Vec3<T>& vec, const Vec3<U>& from) noexcept;


    /**
     * @brief Reject the @p Vec vector from the **unit** @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note Promotes the result to the wider type using @ref PromotedVec3<T, U>.
     * @note Only use this method if @p from is normalized. If not, use @ref reject.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to be rejected.
     * @param[in] from The vector to reject from.
     *
     * @return The perpendicular @ref Vec3 component.
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedVec3<T, U> rejectNorm(const Vec3<T>& vec, const Vec3<U>& from) noexcept;


    /**
     * @brief Reject the @p Vec vector from the @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note This is a safe operation. If the @p from vector's magnitude falls below the internal
     *       epsilon, or if either vector contains NaN components, rejection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedFloatVec3<T, U>.
     * @note If @p from is normalized, use @ref safeRejectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to reject.
     * @param[in] from The vector to reject from.
     *
     * @return The perpendicular @ref Vec3 component or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedFloatVec3<T, U> safeReject(const Vec3<T>& vec, const Vec3<U>& from) noexcept;


    /**
     * @brief Reject the @p Vec vector from the **unit** @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note This is a safe operation. If either vector contains NaN components, rejection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedVec3<T, U>.
     * @note Only use this method if @p from is normalized. If not, use @ref safeReject.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to reject.
     * @param[in] from The vector to reject from.
     *
     * @return The perpendicular @ref Vec3 component or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedVec3<T, U> safeRejectNorm(const Vec3<T>& vec, const Vec3<U>& from) noexcept;


    /**
     * @brief Reject the @p Vec vector from the @p from vector and set @p status to the result of
     *        rejection operation.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note This is a safe operation. If the @p from vector's magnitude falls below the internal
     *       epsilon, or if either vector contains NaN components, rejection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedFloatVec3<T, U>.
     * @note If @p from is normalized, use @ref tryRejectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec     The vector to reject.
     * @param[in] from    The vector to reject from.
     * @param[out] status The status flag to store the status of the current operation result.
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return The perpendicular @ref Vec3 component or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedFloatVec3<T, U> tryReject(const Vec3<T>& vec, const Vec3<U>& from,
                                                              OperationStatus& status) noexcept;


    /**
     * @brief Reject the @p Vec vector from the **unit** @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note This is a safe operation. If either vector contains NaN components, rejection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedVec3<T, U>.
     * @note Only use this method if @p from is normalized. If not, use @ref tryReject.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec     The vector to reject.
     * @param[in] from    The vector to reject from.
     * @param[out] status The status flag to store the status of the current operation result.
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return The perpendicular @ref Vec3 component or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedVec3<T, U> tryRejectNorm(const Vec3<T>& vec, const Vec3<U>& from,
                                                             OperationStatus& status) noexcept;


    // ------------------------ VEC4(SCALAR) ------------------------

    /**
     * @brief Project the @p Vec vector onto the @p onto vector.
     *        \f$
     *          \text{proj}_{\mathbf{b}} \mathbf{a} =
     *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
     *        \f$
     *
     * @note Promotes the result to the wider type using @ref PromotedFloatVec4<T, U>.
     * @note If @p onto is normalized, use @ref projectNorm as it is a faster implementation for unit vectors.
     * @note Performs assertion for division by zero, resulting from zero-length vector, in **Debug mode**.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to project.
     * @param[in] onto The vector to project onto.
     *
     * @return The projected @ref Vec4.
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedFloatVec4<T, U> project(const Vec4<T>& vec, const Vec4<U>& onto) noexcept;


    /**
     * @brief Project the @p Vec vector onto the **unit** @p onto vector.
     *        \f$
     *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
     *        \f$
     *
     * @note Promotes the result to the wider type using @ref PromotedFloatVec4<T, U>.
     * @note Only use this method if @p onto is normalized. If not, use @ref project.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to project.
     * @param[in] onto The vector to project onto.
     *
     * @return The projected @ref Vec4.
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedVec4<T, U> projectNorm(const Vec4<T>& vec, const Vec4<U>& onto) noexcept;


    /**
     * @brief Project the @p Vec vector onto the @p onto vector.
     *        \f$
     *          \text{proj}_{\mathbf{b}} \mathbf{a} =
     *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
     *        \f$
     *
     * @note This is a safe operation. If the @p onto vector's magnitude falls below the internal
     *       epsilon, or if either vector contains NaN components, projection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedFloatVec4<T, U>.
     * @note If @p onto is normalized, use @ref safeProjectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to project.
     * @param[in] onto The vector to project onto.
     *
     * @return The projected @ref Vec4 or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedFloatVec4<T, U> safeProject(const Vec4<T>& vec, const Vec4<U>& onto) noexcept;


    /**
     * @brief Project the @p Vec vector onto the **unit** @p onto vector.
     *        \f$
     *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
     *        \f$
     *
     * @note This is a safe operation. If either vector contains NaN components, projection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedVec4<T, U>.
     * @note Only use this method if @p onto is normalized. If not, use @ref safeProject.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to project.
     * @param[in] onto The vector to project onto.
     *
     * @return The projected @ref Vec4 or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedVec4<T, U> safeProjectNorm(const Vec4<T>& vec, const Vec4<U>& onto) noexcept;


    /**
     * @brief Project the @p Vec vector onto the @p onto vector and set @p status to the
     *        projection operation result.
     *        \f$
     *          \text{proj}_{\mathbf{b}} \mathbf{a} =
     *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
     *        \f$
     *
     * @note This is a safe operation. If the @p onto vector's magnitude falls below the internal
     *       epsilon, or if either vector contains NaN components, projection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedFloatVec4<T, U>.
     * @note If @p onto is normalized, use @ref tryProjectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec     The vector to project.
     * @param[in] onto    The vector to project onto.
     * @param[out] status The status flag to store the status of the current operation result.
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return The projected @ref Vec4 or a zero-vector if projected onto a zero-length vector or if either
     *         vector has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedFloatVec4<T, U> tryProject(const Vec4<T>& vec, const Vec4<U>& onto,
                                                               OperationStatus& status) noexcept;


    /**
     * @brief Project the @p Vec vector onto the **unit** @p onto vector and set @p status to the
     *        projection operation result.
     *        \f$
     *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
     *        \f$
     *
     * @note This is a safe operation. If either vector contains NaN components, projection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedVec4<T, U>.
     * @note To maintain precision, result components are promoted to their
     *       corresponding floating-point representation via @ref Magnitude.
     * @note Only use this method if @p onto is normalized. If not, use @ref tryProject.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec     The vector to project.
     * @param[in] onto    The vector to project onto.
     * @param[out] status The status flag to store the status of the current operation result.
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return The projected @ref Vec4 or a zero-vector if projected onto a zero-length vector or if either
     *         vector has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedVec4<T, U> tryProjectNorm(const Vec4<T>& vec, const Vec4<U>& onto,
                                                              OperationStatus& status) noexcept;


    /**
     * @brief Reject the @p Vec vector from the @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note Promotes the result to the wider type using @ref PromotedFloatVec4<T, U>.
     * @note If @p from is normalized, use @ref rejectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to be rejected.
     * @param[in] from The vector to reject from.
     *
     * @return The perpendicular @ref Vec4 component.
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedFloatVec4<T, U> reject(const Vec4<T>& vec, const Vec4<U>& from) noexcept;


    /**
     * @brief Reject the @p Vec vector from the **unit** @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note Promotes the result to the wider type using @ref PromotedVec4<T, U>.
     * @note Only use this method if @p from is normalized. If not, use @ref reject.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to be rejected.
     * @param[in] from The vector to reject from.
     *
     * @return The perpendicular @ref Vec4 component.
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedVec4<T, U> rejectNorm(const Vec4<T>& vec, const Vec4<U>& from) noexcept;


    /**
     * @brief Reject the @p Vec vector from the @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note This is a safe operation. If the @p from vector's magnitude falls below the internal
     *       epsilon, or if either vector contains NaN components, rejection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedFloatVec4<T, U>.
     * @note If @p from is normalized, use @ref safeRejectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to reject.
     * @param[in] from The vector to reject from.
     *
     * @return The perpendicular @ref Vec4 component or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedFloatVec4<T, U> safeReject(const Vec4<T>& vec, const Vec4<U>& from) noexcept;


    /**
     * @brief Reject the @p Vec vector from the **unit** @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note This is a safe operation. If either vector contains NaN components, rejection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedVec4<T, U>.
     * @note Only use this method if @p from is normalized. If not, use @ref safeReject.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec  The vector to reject.
     * @param[in] from The vector to reject from.
     *
     * @return The perpendicular @ref Vec4 component or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedVec4<T, U> safeRejectNorm(const Vec4<T>& vec, const Vec4<U>& from) noexcept;


    /**
     * @brief Reject the @p Vec vector from the @p from vector and set @p status to the result of
     *        rejection operation.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note This is a safe operation. If the @p from vector's magnitude falls below the internal
     *       epsilon, or if either vector contains NaN components, rejection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedFloatVec4<T, U>.
     * @note If @p from is normalized, use @ref tryRejectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec     The vector to reject.
     * @param[in] from    The vector to reject from.
     * @param[out] status The status flag to store the status of the current operation result.
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return The perpendicular @ref Vec4 component or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedFloatVec4<T, U> tryReject(const Vec4<T>& vec, const Vec4<U>& from,
                                                              OperationStatus& status) noexcept;


    /**
     * @brief Reject the @p Vec vector from the **unit** @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note This is a safe operation. If either vector contains NaN components, rejection is bypassed.
     * @note Promotes the result to the wider type using @ref PromotedVec4<T, U>.
     * @note Only use this method if @p from is normalized. If not, use @ref tryReject.
     *
     * @tparam T Numeric type of the LHS vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec     The vector to reject.
     * @param[in] from    The vector to reject from.
     * @param[out] status The status flag to store the status of the current operation result.
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return The perpendicular @ref Vec4 component or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <StrictArithmetic T, StrictArithmetic U>
    [[nodiscard]] constexpr PromotedVec4<T, U> tryRejectNorm(const Vec4<T>& vec, const Vec4<U>& from,
                                                             OperationStatus& status) noexcept;



    /// +---------------------------------------------------------------------------------------+
    /// |                             VEC2, VEC3, VEC4 (SIMD)                                   |
    /// +---------------------------------------------------------------------------------------+

    // ------------------------ VEC2(SIMD) ------------------------

    /**
     * @brief Project the @p Vec vector onto the @p onto vector.
     *        \f$
     *          \text{proj}_{\mathbf{b}} \mathbf{a} =
     *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
     *        \f$
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @note If @p onto is normalized, use @ref projectNorm as it is a faster implementation for unit vectors.
     * @note Performs assertion for division by zero, resulting from zero-length vector, in **Debug mode**.
     *
     * @param[in] vec  The vector to project.
     * @param[in] onto The vector to project onto.
     *
     * @return The projected @ref simd::Vec2<T>.
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec2<T> project(const simd::Vec2<T>& vec, const simd::Vec2<T>& onto) noexcept;


    /**
     * @brief Project the @p Vec vector onto the **unit** @p onto vector.
     *        \f$
     *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
     *        \f$
     *
     * @note Only use this method if @p onto is normalized. If not, use @ref project.
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @param[in] vec  The vector to project.
     * @param[in] onto The vector to project onto.
     *
     * @return The projected @ref simd::Vec2<T>.
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec2<T> projectNorm(const simd::Vec2<T>& vec, const simd::Vec2<T>& onto) noexcept;


    /**
     * @brief Project the @p Vec vector onto the @p onto vector.
     *        \f$
     *          \text{proj}_{\mathbf{b}} \mathbf{a} =
     *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
     *        \f$
     *
     * @note This is a safe operation. If the @p onto vector's magnitude falls below the internal
     *       epsilon, or if either vector contains NaN components, projection is bypassed.
     * @note If @p onto is normalized, use @ref safeProjectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @param[in] vec  The vector to project.
     * @param[in] onto The vector to project onto.
     *
     * @return The projected @ref simd::Vec2<T> or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec2<T> safeProject(const simd::Vec2<T>& vec, const simd::Vec2<T>& onto) noexcept;


    /**
     * @brief Project the @p Vec vector onto the **unit** @p onto vector.
     *        \f$
     *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
     *        \f$
     *
     * @note This is a safe operation. If either vector contains NaN components, projection is bypassed.
     * @note Only use this method if @p onto is normalized. If not, use @ref safeProject.
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @param[in] vec  The vector to project.
     * @param[in] onto The vector to project onto.
     *
     * @return The projected @ref simd::Vec2<T> or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec2<T> safeProjectNorm(const simd::Vec2<T>& vec, const simd::Vec2<T>& onto) noexcept;


    /**
     * @brief Project the @p Vec vector onto the @p onto vector and set @p status to the
     *        projection operation result.
     *        \f$
     *          \text{proj}_{\mathbf{b}} \mathbf{a} =
     *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
     *        \f$
     *
     * @note This is a safe operation. If the @p onto vector's magnitude falls below the internal
     *       epsilon, or if either vector contains NaN components, projection is bypassed.
     * @note If @p onto is normalized, use @ref tryProjectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @param[in] vec     The vector to project.
     * @param[in] onto    The vector to project onto.
     * @param[out] status The status flag to store the status of the current operation result.
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return The projected @ref simd::Vec2<T> or a zero-vector if projected onto a zero-length vector or if
     *         either vector has NaN(Not-a-Number) component(s).
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec2<T> tryProject(const simd::Vec2<T>& vec, const simd::Vec2<T>& onto,
                                                     OperationStatus& status) noexcept;


    /**
     * @brief Project the @p Vec vector onto the **unit** @p onto vector and set @p status to the
     *        projection operation result.
     *        \f$
     *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
     *        \f$
     *
     * @note This is a safe operation. If either vector contains NaN components, projection is bypassed.
     * @note Only use this method if @p onto is normalized. If not, use @ref tryProject.
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @param[in] vec     The vector to project.
     * @param[in] onto    The vector to project onto.
     * @param[out] status The status flag to store the status of the current operation result.
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return The projected @ref simd::Vec2<T> or a zero-vector if projected onto a zero-length vector or if
     *         either vector has NaN(Not-a-Number) component(s).
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec2<T> tryProjectNorm(const simd::Vec2<T>& vec, const simd::Vec2<T>& onto,
                                                         OperationStatus& status) noexcept;


    /**
     * @brief Reject the @p Vec vector from the @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note If @p from is normalized, use @ref rejectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @param[in] vec  The vector to be rejected.
     * @param[in] from The vector to reject from.
     *
     * @return The perpendicular @ref simd::Vec2<T> component.
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec2<T> reject(const simd::Vec2<T>& vec, const simd::Vec2<T>& from) noexcept;


    /**
     * @brief Reject the @p Vec vector from the **unit** @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note Only use this method if @p from is normalized. If not, use @ref reject.
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @param[in] vec The vector to be rejected.
     * @param[in] from   The vector to reject from.
     *
     * @return The perpendicular @ref simd::Vec2<T> component.
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec2<T> rejectNorm(const simd::Vec2<T>& vec, const simd::Vec2<T>& from) noexcept;


    /**
     * @brief Reject the @p Vec vector from the @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note This is a safe operation. If the @p from vector's magnitude falls below the internal
     *       epsilon, or if either vector contains NaN components, rejection is bypassed.
     * @note If @p from is normalized, use @ref safeRejectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @param[in] vec  The vector to reject.
     * @param[in] from The vector to reject from.
     *
     * @return The perpendicular @ref simd::Vec2<T> component or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec2<T> safeReject(const simd::Vec2<T>& vec, const simd::Vec2<T>& from) noexcept;


    /**
     * @brief Reject the @p Vec vector from the **unit** @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note This is a safe operation. If either vector contains NaN components, rejection is bypassed.
     * @note Only use this method if @p from is normalized. If not, use @ref safeReject.
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @param[in] vec  The vector to reject.
     * @param[in] from The vector to reject from.
     *
     * @return The perpendicular @ref simd::Vec2<T> component or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec2<T> safeRejectNorm(const simd::Vec2<T>& vec, const simd::Vec2<T>& from) noexcept;


    /**
     * @brief Reject the @p Vec vector from the @p from vector and set @p status to the result of
     *        rejection operation.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note This is a safe operation. If the @p from vector's magnitude falls below the internal
     *       epsilon, or if either vector contains NaN components, rejection is bypassed.
     * @note If @p from is normalized, use @ref tryRejectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @param[in] vec     The vector to reject.
     * @param[in] from    The vector to reject from.
     * @param[out] status The status flag to store the status of the current operation result.
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return The perpendicular @ref simd::Vec2<T> component or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec2<T> tryReject(const simd::Vec2<T>& vec, const simd::Vec2<T>& from,
                                                    OperationStatus& status) noexcept;


    /**
     * @brief Reject the @p Vec vector from the **unit** @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note This is a safe operation. If either vector contains NaN components, rejection is bypassed.
     * @note Only use this method if @p from is normalized. If not, use @ref tryReject.
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @param[in] vec     The vector to reject.
     * @param[in] from    The vector to reject from.
     * @param[out] status The status flag to store the status of the current operation result.
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return The perpendicular @ref simd::Vec2<T> component or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec2<T> tryRejectNorm(const simd::Vec2<T>& vec, const simd::Vec2<T>& from,
                                                        OperationStatus& status) noexcept;


    // ------------------------ VEC3(SIMD) ------------------------

    /**
     * @brief Project the @p Vec vector onto the @p onto vector.
     *        \f$
     *          \text{proj}_{\mathbf{b}} \mathbf{a} =
     *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
     *        \f$
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @note If @p onto is normalized, use @ref projectNorm as it is a faster implementation for unit vectors.
     * @note Performs assertion for division by zero, resulting from zero-length vector, in **Debug mode**.
     *
     * @param[in] vec  The vector to project.
     * @param[in] onto The vector to project onto.
     *
     * @return The projected @ref simd::Vec3<T>.
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec3<T> project(const simd::Vec3<T>& vec, const simd::Vec3<T>& onto) noexcept;


    /**
     * @brief Project the @p Vec vector onto the **unit** @p onto vector.
     *        \f$
     *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
     *        \f$
     *
     * @note Only use this method if @p onto is normalized. If not, use @ref project.
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @param[in] vec  The vector to project.
     * @param[in] onto The vector to project onto.
     *
     * @return The projected @ref simd::Vec3<T>.
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec3<T> projectNorm(const simd::Vec3<T>& vec, const simd::Vec3<T>& onto) noexcept;


    /**
     * @brief Project the @p Vec vector onto the @p onto vector.
     *        \f$
     *          \text{proj}_{\mathbf{b}} \mathbf{a} =
     *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
     *        \f$
     *
     * @note This is a safe operation. If the @p onto vector's magnitude falls below the internal
     *       epsilon, or if either vector contains NaN components, projection is bypassed.
     * @note If @p onto is normalized, use @ref safeProjectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @param[in] vec  The vector to project.
     * @param[in] onto The vector to project onto.
     *
     * @return The projected @ref simd::Vec3<T> or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec3<T> safeProject(const simd::Vec3<T>& vec, const simd::Vec3<T>& onto) noexcept;


    /**
     * @brief Project the @p Vec vector onto the **unit** @p onto vector.
     *        \f$
     *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
     *        \f$
     *
     * @note This is a safe operation. If either vector contains NaN components, projection is bypassed.
     * @note Only use this method if @p onto is normalized. If not, use @ref safeProject.
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @param[in] vec  The vector to project.
     * @param[in] onto The vector to project onto.
     *
     * @return The projected @ref simd::Vec3<T> or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec3<T> safeProjectNorm(const simd::Vec3<T>& vec, const simd::Vec3<T>& onto) noexcept;


    /**
     * @brief Project the @p Vec vector onto the @p onto vector and set @p status to the
     *        projection operation result.
     *        \f$
     *          \text{proj}_{\mathbf{b}} \mathbf{a} =
     *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
     *        \f$
     *
     * @note This is a safe operation. If the @p onto vector's magnitude falls below the internal
     *       epsilon, or if either vector contains NaN components, projection is bypassed.
     * @note If @p onto is normalized, use @ref tryProjectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @param[in] vec     The vector to project.
     * @param[in] onto    The vector to project onto.
     * @param[out] status The status flag to store the status of the current operation result.
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return The projected @ref simd::Vec3<T> or a zero-vector if projected onto a zero-length vector or if
     *         either vector has NaN(Not-a-Number) component(s).
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec3<T> tryProject(const simd::Vec3<T>& vec, const simd::Vec3<T>& onto,
                                                     OperationStatus& status) noexcept;


    /**
     * @brief Project the @p Vec vector onto the **unit** @p onto vector and set @p status to the
     *        projection operation result.
     *        \f$
     *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
     *        \f$
     *
     * @note This is a safe operation. If either vector contains NaN components, projection is bypassed.
     * @note Only use this method if @p onto is normalized. If not, use @ref tryProject.
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @param[in] vec     The vector to project.
     * @param[in] onto    The vector to project onto.
     * @param[out] status The status flag to store the status of the current operation result.
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return The projected @ref simd::Vec3<T> or a zero-vector if projected onto a zero-length vector or if
     *         either vector has NaN(Not-a-Number) component(s).
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec3<T> tryProjectNorm(const simd::Vec3<T>& vec, const simd::Vec3<T>& onto,
                                                         OperationStatus& status) noexcept;


    /**
     * @brief Reject the @p Vec vector from the @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note If @p from is normalized, use @ref rejectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @param[in] vec  The vector to be rejected.
     * @param[in] from The vector to reject from.
     *
     * @return The perpendicular @ref simd::Vec3<T> component.
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec3<T> reject(const simd::Vec3<T>& vec, const simd::Vec3<T>& from) noexcept;


    /**
     * @brief Reject the @p Vec vector from the **unit** @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note Only use this method if @p from is normalized. If not, use @ref reject.
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @param[in] vec The vector to be rejected.
     * @param[in] from   The vector to reject from.
     *
     * @return The perpendicular @ref simd::Vec3<T> component.
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec3<T> rejectNorm(const simd::Vec3<T>& vec, const simd::Vec3<T>& from) noexcept;


    /**
     * @brief Reject the @p Vec vector from the @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note This is a safe operation. If the @p from vector's magnitude falls below the internal
     *       epsilon, or if either vector contains NaN components, rejection is bypassed.
     * @note If @p from is normalized, use @ref safeRejectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @param[in] vec  The vector to reject.
     * @param[in] from The vector to reject from.
     *
     * @return The perpendicular @ref simd::Vec3<T> component or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec3<T> safeReject(const simd::Vec3<T>& vec, const simd::Vec3<T>& from) noexcept;


    /**
     * @brief Reject the @p Vec vector from the **unit** @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note This is a safe operation. If either vector contains NaN components, rejection is bypassed.
     * @note Only use this method if @p from is normalized. If not, use @ref safeReject.
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @param[in] vec  The vector to reject.
     * @param[in] from The vector to reject from.
     *
     * @return The perpendicular @ref simd::Vec3<T> component or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec3<T> safeRejectNorm(const simd::Vec3<T>& vec, const simd::Vec3<T>& from) noexcept;


    /**
     * @brief Reject the @p Vec vector from the @p from vector and set @p status to the result of
     *        rejection operation.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note This is a safe operation. If the @p from vector's magnitude falls below the internal
     *       epsilon, or if either vector contains NaN components, rejection is bypassed.
     * @note If @p from is normalized, use @ref tryRejectNorm as it is a faster implementation for unit vectors.
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @param[in] vec     The vector to reject.
     * @param[in] from    The vector to reject from.
     * @param[out] status The status flag to store the status of the current operation result.
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return The perpendicular @ref simd::Vec3<T> component or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec3<T> tryReject(const simd::Vec3<T>& vec, const simd::Vec3<T>& from,
                                                    OperationStatus& status) noexcept;


    /**
     * @brief Reject the @p Vec vector from the **unit** @p from vector.
     *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
     *
     * @note This is a safe operation. If either vector contains NaN components, rejection is bypassed.
     * @note Only use this method if @p from is normalized. If not, use @ref tryReject.
     *
     * @tparam T Numeric type of the vectors. Must satisfy @ref FPArithmetic.
     *
     * @param[in] vec     The vector to reject.
     * @param[in] from    The vector to reject from.
     * @param[out] status The status flag to store the status of the current operation result.
     *                    For details on status codes see @ref OperationStatus.
     *
     * @return The perpendicular @ref simd::Vec3<T> component or a zero-vector if projected onto a zero-length vector
     *         or if either of the vectors has NaN(Not-a-Number) component(s).
     */
    template <FPArithmetic T>
    [[nodiscard]] constexpr simd::Vec3<T> tryRejectNorm(const simd::Vec3<T>& vec, const simd::Vec3<T>& from,
                                                        OperationStatus& status) noexcept;



    // ------------------------ VEC4(SIMD) ------------------------


} // namespace flcn

/** @} */

#include "Projection.tpp"

