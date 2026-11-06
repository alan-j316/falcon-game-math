#pragma once
/**
 * @file Comp.h
 * @author Alan Abraham P Kochumon
 * @date Created on: July 17, 2026
 *
 * @brief Defines all non-square matrix composition operations (Mat(m,n) * Mat(n, o)).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "falcon/math/common/Types.h"
#include "falcon/math/matrices/Mat2.h"
#include "falcon/math/matrices/Mat2x3.h"
#include "falcon/math/matrices/Mat2x4.h"
#include "falcon/math/matrices/Mat3.h"
#include "falcon/math/matrices/Mat3x2.h"
#include "falcon/math/matrices/Mat3x4.h"
#include "falcon/math/matrices/Mat4.h"
#include "falcon/math/matrices/Mat4x2.h"
#include "falcon/math/matrices/Mat4x3.h"

// TODO: Add Implementation
// Implementations
// 3x3 * 3x4
//
// 4x4 * 4x2
// 4x4 * 4x3

namespace flcn
{

    /**
     * @addtogroup FALCON_Mat2x3_Comp
     * @{
     */

    /**
     * @brief Multiply a 2x3 matrix with a 3x2 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat2<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 2x3 matrix on the left hand side.
     * @param[in] rhs The 3x2 matrix on the right hand side.
     *
     * @return A new 2D matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat2<T, U> operator*(const Mat2x3<T>& lhs, const Mat3x2<U>& rhs) noexcept;


    /**
     * @brief Multiply a 2x3 matrix with a 3D matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat2x3<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 2x3 matrix on the left hand side.
     * @param[in] rhs The 3D matrix on the right hand side.
     *
     * @return A new 2x3 matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat2x3<T, U> operator*(const Mat2x3<T>& lhs, const Mat3<U>& rhs) noexcept;


    /**
     * @brief Multiply a 2x3 matrix with a 3x4 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat2x4<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 2x3 matrix on the left hand side.
     * @param[in] rhs The 3x4 matrix on the right hand side.
     *
     * @return A new 2x4 matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat2x4<T, U> operator*(const Mat2x3<T>& lhs, const Mat3x4<U>& rhs) noexcept;


    /**
     * @brief Multiply a 2D matrix with a 2x3 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat2x3<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 2D matrix on the left hand side.
     * @param[in] rhs The 2x3 matrix on the right hand side.
     *
     * @return A new 2x3 matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat2x3<T, U> operator*(const Mat2<T>& lhs, const Mat2x3<U>& rhs) noexcept;

    /** @} */



    /**
     * @addtogroup FALCON_Mat2x4_Comp
     * @{
     */


    /**
     * @brief Multiply a 2x4 matrix with a 4x2 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat2<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 2x4 matrix on the left hand side.
     * @param[in] rhs The 4x2 matrix on the right hand side.
     *
     * @return A new 2D matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat2<T, U> operator*(const Mat2x4<T>& lhs, const Mat4x2<U>& rhs) noexcept;


    /**
     * @brief Multiply a 2x4 matrix with a 4x3 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat2x3<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 2x4 matrix on the left hand side.
     * @param[in] rhs The 4x3 matrix on the right hand side.
     *
     * @return A new 2x3 matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat2x3<T, U> operator*(const Mat2x4<T>& lhs, const Mat4x3<U>& rhs) noexcept;


    /**
     * @brief Multiply a 2x4 matrix with a 4D matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat2x4<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 2x4 matrix on the left hand side.
     * @param[in] rhs The 4D matrix on the right hand side.
     *
     * @return A new 2x4 matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat2x4<T, U> operator*(const Mat2x4<T>& lhs, const Mat4<U>& rhs) noexcept;


    /**
     * @brief Multiply a 2D matrix with a 2x4 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat2x4<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 2D matrix on the left hand side.
     * @param[in] rhs The 2x4 matrix on the right hand side.
     *
     * @return A new 2x4 matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat2x4<T, U> operator*(const Mat2<T>& lhs, const Mat2x4<U>& rhs) noexcept;

    /** @} */



    /**
     * @addtogroup FALCON_Mat3x2_Comp
     * @{
     */

    /**
     * @brief Multiply a 3x2 matrix with a 2D matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat3x2<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 3x2 matrix on the left hand side.
     * @param[in] rhs The 2D matrix on the right hand side.
     *
     * @return A new 3x2 matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat3x2<T, U> operator*(const Mat3x2<T>& lhs, const Mat2<U>& rhs) noexcept;


    /**
     * @brief Multiply a 3x2 matrix with a 2x3 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat3<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 3x2 matrix on the left hand side.
     * @param[in] rhs The 2x3 matrix on the right hand side.
     *
     * @return A new 3D matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat3<T, U> operator*(const Mat3x2<T>& lhs, const Mat2x3<U>& rhs) noexcept;


    /**
     * @brief Multiply a 3x2 matrix with a 2x4 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat3x4<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 3x2 matrix on the left hand side.
     * @param[in] rhs The 2x4 matrix on the right hand side.
     *
     * @return A new 3x4 matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat3x4<T, U> operator*(const Mat3x2<T>& lhs, const Mat2x4<U>& rhs) noexcept;


    /**
     * @brief Multiply a 3D matrix with a 3x2 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat3x2<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 3D matrix on the left hand side.
     * @param[in] rhs The 3x2 matrix on the right hand side.
     *
     * @return A new 3x2 matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat3x2<T, U> operator*(const Mat3<T>& lhs, const Mat3x2<U>& rhs) noexcept;

    /** @} */



    /**
     * @addtogroup FALCON_Mat3x4_Comp
     * @{
     */

    /**
     * @brief Multiply a 3x4 matrix with a 4x2 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat3x2<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 3x4 matrix on the left hand side.
     * @param[in] rhs The 4x2 matrix on the right hand side.
     *
     * @return A new 3x2 matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat3x2<T, U> operator*(const Mat3x4<T>& lhs, const Mat4x2<U>& rhs) noexcept;


    /**
     * @brief Multiply a 3x4 matrix with a 4x3 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat3<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 3x4 matrix on the left hand side.
     * @param[in] rhs The 4x3 matrix on the right hand side.
     *
     * @return A new 3D matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat3<T, U> operator*(const Mat3x4<T>& lhs, const Mat4x3<U>& rhs) noexcept;


    /**
     * @brief Multiply a 3x4 matrix with a 4D matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat3x4<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 3x4 matrix on the left hand side.
     * @param[in] rhs The 4D matrix on the right hand side.
     *
     * @return A new 3x4 matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat3x4<T, U> operator*(const Mat3x4<T>& lhs, const Mat4<U>& rhs) noexcept;


    /**
     * @brief Multiply a 3D matrix with a 3x4 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat3x4<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 3D matrix on the left hand side.
     * @param[in] rhs The 3x4 matrix on the right hand side.
     *
     * @return A new 3x4 matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat3x4<T, U> operator*(const Mat3<T>& lhs, const Mat3x4<U>& rhs) noexcept;

    /** @} */



    /**
     * @addtogroup FALCON_Mat4x2_Comp
     * @{
     */

    /**
     * @brief Multiply a 4x2 matrix with a 2D matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat4x2<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 4x2 matrix on the left hand side.
     * @param[in] rhs The 2D matrix on the right hand side.
     *
     * @return A new 4x2 matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat4x2<T, U> operator*(const Mat4x2<T>& lhs, const Mat2<U>& rhs) noexcept;


    /**
     * @brief Multiply a 4x2 matrix with a 2x3 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat4x3<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 4x2 matrix on the left hand side.
     * @param[in] rhs The 2x3 matrix on the right hand side.
     *
     * @return A new 4x3 matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat4x3<T, U> operator*(const Mat4x2<T>& lhs, const Mat2x3<U>& rhs) noexcept;


    /**
     * @brief Multiply a 4x2 matrix with a 2x4 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat4<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 4x2 matrix on the left hand side.
     * @param[in] rhs The 2x4 matrix on the right hand side.
     *
     * @return A new 4D matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat4<T, U> operator*(const Mat4x2<T>& lhs, const Mat2x4<U>& rhs) noexcept;


    /**
     * @brief Multiply a 4D matrix with a 4x2 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat4x2<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 4D matrix on the left hand side.
     * @param[in] rhs The 4x2 matrix on the right hand side.
     *
     * @return A new 4x2 matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat4x2<T, U> operator*(const Mat4<T>& lhs, const Mat4x2<U>& rhs) noexcept;

    /** @} */



    /**
     * @addtogroup FALCON_Mat4x3_Comp
     * @{
     */

    /**
     * @brief Multiply a 4x3 matrix with a 3x2 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat4x2<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 4x2 matrix on the left hand side.
     * @param[in] rhs The 3x2 matrix on the right hand side.
     *
     * @return A new 4x2 matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat4x2<T, U> operator*(const Mat4x3<T>& lhs, const Mat3x2<U>& rhs) noexcept;


    /**
     * @brief Multiply a 4x3 matrix with a 3D matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat4x3<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 4x3 matrix on the left hand side.
     * @param[in] rhs The 3D matrix on the right hand side.
     *
     * @return A new 4x3 matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat4x3<T, U> operator*(const Mat4x3<T>& lhs, const Mat3<U>& rhs) noexcept;


    /**
     * @brief Multiply a 4x3 matrix with a 3x4 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat4<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 4x3 matrix on the left hand side.
     * @param[in] rhs The 3x4 matrix on the right hand side.
     *
     * @return A new 4D matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat4<T, U> operator*(const Mat4x3<T>& lhs, const Mat3x4<U>& rhs) noexcept;


    /**
     * @brief Multiply a 4D matrix with a 4x3 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat4x3<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] lhs The 4D matrix on the left hand side.
     * @param[in] rhs The 4x3 matrix on the right hand side.
     *
     * @return A new 4x3 matrix.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedMat4x3<T, U> operator*(const Mat4<T>& lhs, const Mat4x3<U>& rhs) noexcept;


    /** @} */

} // namespace flcn


#include "Comp.tpp"
