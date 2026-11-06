#pragma once
/**
 * @file Geom.h
 * @author Alan Abraham P Kochumon
 * @date Created on: July 25, 2026
 *
 * @brief Defines all non-square matrix Geometric Operations like Matrix-Vector multiplication and Matrix Tranpose.
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
#include "falcon/math/vectors/CVec2.h"
#include "falcon/math/vectors/Vec3.h"
#include "falcon/math/vectors/Vec4.h"



/// TODO: Not implemented or tested
// TODO: Add Groups
// TODO: Transpose
// Mat3x2
// Mat3x4
// Mat4x2
// Mat4x3


namespace flcn
{

    /**
     * @addtogroup FALCON_Mat2x3_Geom
     * @{
     */

    /**
     * @brief Multiply a 2x3 matrix with a 3D column vector.
     *
     * @note Promotes the result to the wider type using @ref PromotedVector2<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the column vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] mat The matrix to multiply.
     * @param[in] vec The column vector to multiply with.
     *
     * @return A new 2D column vector.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedCVec2<T, U> operator*(const Mat2x3<T>& mat, const Vec3<U>& vec) noexcept;


    /**
     * @brief Multiply a 2D row vector with a 2x3 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedVec3<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec The row vector to multiply.
     * @param[in] mat The matrix to multiply with.
     *
     * @return A new 3D row vector.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedVec3<T, U> operator*(const CVec2<T>& vec, const Mat2x3<U>& mat) noexcept;

    /** @} */



    /**
     * @addtogroup FALCON_Mat2x4_Geom
     * @{
     */

    /**
     * @brief Multiply a 2x4 matrix with a 4D column vector.
     *
     * @note Promotes the result to the wider type using @ref PromotedVector2<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the column vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] mat The matrix to multiply.
     * @param[in] vec The column vector to multiply with.
     *
     * @return A new 2D column vector.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedCVec2<T, U> operator*(const Mat2x4<T>& mat, const Vec4<U>& vec) noexcept;


    /**
     * @brief Multiply a 2D row vector with a 2x4 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedVec4<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec The row vector to multiply.
     * @param[in] mat The matrix to multiply with.
     *
     * @return A new 4D row vector.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedVec4<T, U> operator*(const CVec2<T>& vec, const Mat2x4<U>& mat) noexcept;

    /** @} */



    /**
     * @addtogroup FALCON_Mat3x2_Geom
     * @{
     */

    /**
     * @brief Multiply a 3x2 matrix with a 2D column vector.
     *
     * @note Promotes the result to the wider type using @ref PromotedVector3<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the column vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] mat The matrix to multiply.
     * @param[in] vec The column vector to multiply with.
     *
     * @return A new 3D column vector.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedVec3<T, U> operator*(const Mat3x2<T>& mat, const CVec2<U>& vec) noexcept;


    /**
     * @brief Multiply a 3D row vector with a 3x2 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedCVec2<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec The row vector to multiply.
     * @param[in] mat The matrix to multiply with.
     *
     * @return A new 2D row vector.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedCVec2<T, U> operator*(const Vec3<T>& vec, const Mat3x2<U>& mat) noexcept;

    /** @} */



    /**
     * @addtogroup FALCON_Mat3x4_Geom
     * @{
     */

    /**
     * @brief Multiply a 3x4 matrix with a 4D column vector.
     *
     * @note Promotes the result to the wider type using @ref PromotedVector3<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the column vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] mat The matrix to multiply.
     * @param[in] vec The column vector to multiply with.
     *
     * @return A new 3D column vector.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedVec3<T, U> operator*(const Mat3x4<T>& mat, const Vec4<U>& vec) noexcept;


    /**
     * @brief Multiply a 3D row vector with a 3x4 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedVec4<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec The row vector to multiply.
     * @param[in] mat The matrix to multiply with.
     *
     * @return A new 4D row vector.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedVec4<T, U> operator*(const Vec3<T>& vec, const Mat3x4<U>& mat) noexcept;


    /** @} */



    /**
     * @addtogroup FALCON_Mat4x2_Geom
     * @{
     */

    /**
     * @brief Multiply a 4x2 matrix with a 2D column vector.
     *
     * @note Promotes the result to the wider type using @ref PromotedVector4<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the column vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] mat The matrix to multiply.
     * @param[in] vec The column vector to multiply with.
     *
     * @return A new 4D column vector.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedVec4<T, U> operator*(const Mat4x2<T>& mat, const CVec2<U>& vec) noexcept;


    /**
     * @brief Multiply a 4D row vector with a 4x2 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedCVec2<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the second matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec The row vector to multiply.
     * @param[in] mat The matrix to multiply with.
     *
     * @return A new 4D row vector.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedCVec2<T, U> operator*(const Vec4<T>& vec, const Mat4x2<U>& mat) noexcept;

    /** @} */



    /**
     * @addtogroup FALCON_Mat4x3_Geom
     * @{
     */

    /**
     * @brief Multiply a 4x3 matrix with a 3D column vector.
     *
     * @note Promotes the result to the wider type using @ref PromotedVector4<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the column vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] mat The matrix to multiply.
     * @param[in] vec The column vector to multiply with.
     *
     * @return A new 4D column vector.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedVec4<T, U> operator*(const Mat4x3<T>& mat, const Vec3<U>& vec) noexcept;


    /**
     * @brief Multiply a 4D row vector with a 4x3 matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedVector3<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam U Numeric type of the column vector. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec The row vector to multiply.
     * @param[in] mat The matrix to multiply with.
     *
     * @return A new 3D row vector.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    [[nodiscard]] constexpr PromotedVec3<T, U> operator*( const Vec4<U>& vec, const Mat4x3<T>& mat) noexcept;

    /** @} */

} // namespace flcn


#include "Geom.tpp"
