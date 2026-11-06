#pragma once
/**
 * @file Mat3.h
 * @author Alan Abraham P Kochumon
 * @date Created on: February 15, 2026
 *
 * @brief Templated 3x3 Matrix supporting integral, floating-point, and boolean types.
 *
 * @details Provide high-performance 3x3 matrix implementation with SIMD acceleration
 *          and support for element-wise operations.
 *
 * @note Arithmetic operations are limited to numeric types via `StrictArithmetic` concept.
 * @note Matrices utilize a strict column-major internal memory layout. To align with standard mathematical notations,
 *       scalar constructors accept elements in row-major reading order. Vector-based constructors and array-style
 *       access (operator[]) operate directly on columns.
 * @note FALCON uses **Right-Handed** coordinate system by default. To use **Left-Handed** coordinate system define
 *       `FALCON_LEFT_HANDED` preprocessor macro.
 *
 * @par Configuration
 *      Define `FORCE_SCALAR` to turn off SIMD which is on by default on supported hardware.
 *      Define `FALCON_LEFT_HANDED` to configure library to use left-handed coordinated system.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "falcon/math/common/Config.h"
#include "falcon/math/common/MathTraits.h"
#include "falcon/math/common/Types.h"
#include "falcon/math/vectors/Vec3.h"

#include <array>
#include <cstdint>


// TODO: Add Mat3 Transformation factory, projections.

namespace flcn
{
    template <Arithmetic T>
    struct Mat3
    {
        /**
         * @addtogroup FALCON_Mat3x3_Members
         * @{
         */

        using value_type = T; ///< The numeric type of the matrix elements.

        static constexpr std::size_t COLUMNS = 3; ///< Matrix column count.
        static constexpr std::size_t ROWS    = 3; ///< Matrix row count.

        /** @} */


        /**
         * @addtogroup FALCON_Mat3x3_Init
         * @{
         */

        /**
         * @brief Initialize an uninitialized @ref Mat3 instance.
         *
         * @warning The components are left uninitialized (containing garbage data)
         *          to maximize SIMD optimization and maintain triviality.
         *
         * @note Use value-initialization (`{}`) or the static helper
         *       @ref flcn::Mat3<T>::zero() to guarantee a zeroed matrix.
         */
        Mat3() = default;


        /**
         * @brief Initialize a 3x3 matrix from the passed-in scalar elements.
         *
         * @param[in] m00 The element to insert into row one, column one.
         * @param[in] m01 The element to insert into row one, column two.
         * @param[in] m02 The element to insert into row one, column three.
         * @param[in] m10 The element to insert into row two, column one.
         * @param[in] m11 The element to insert into row two, column two.
         * @param[in] m12 The element to insert into row two, column three.
         * @param[in] m20 The element to insert into row three, column one.
         * @param[in] m21 The element to insert into row three, column two.
         * @param[in] m22 The element to insert into row three, column three.
         */
        [[nodiscard]] constexpr Mat3(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22) noexcept;


        /**
         * @brief Initialize a 3x3 matrix from the passed-in vectors as columns.
         *
         * @param[in] col0 The 3D-vector to use as the first column entry.
         * @param[in] col1 The 3D-vector to use as the second column entry.
         * @param[in] col2 The 3D-vector to use as the third column entry.
         */
        [[nodiscard]] constexpr Mat3(const Vec3<T>& col0, const Vec3<T>& col1, const Vec3<T>& col2) noexcept;


        /**
         * @brief Initialize a diagonal matrix from the passed-in scalar entries.
         *        All non-diagonal elements are initialized to zero.
         *
         * @param[in] d0 The first diagonal entry of the matrix (m00).
         * @param[in] d1 The second diagonal entry of the matrix (m11).
         * @param[in] d2 The third diagonal entry of the matrix (m22).
         */
        [[nodiscard]] constexpr Mat3(T d0, T d1, T d2) noexcept;


        /**
         * @brief Initialize @ref Mat3 from another @ref Mat3 of a different type.
         *
         * @tparam U Numeric type of the source matrix.
         *
         * @param[in] other The source matrix to be converted.
         */
        template <Arithmetic U>
        [[nodiscard]] explicit constexpr Mat3(const Mat3<U>& other) noexcept;

        /** @} */


        /**
         * @addtogroup FALCON_Mat3x3_Access
         * @{
         */

        /**
         * @brief Access the column vector at the specified location (read-write access).
         *
         * @note Performs bounds checking in **DEBUG MODE**.
         *
         * @param[in] col The column index of the matrix.
         *
         * @return A reference to the column vector.
         */
        [[nodiscard]] constexpr Vec3<T>& operator[](std::size_t col) noexcept;


        /**
         * @brief Access the column vector at the specified location (read-only).
         *
         * @note Performs bounds checking in **DEBUG MODE**.
         *
         * @param[in] col The column index of the matrix.
         *
         * @return A const reference to the column vector.
         */
        [[nodiscard]] constexpr const Vec3<T>& operator[](std::size_t col) const noexcept;


        /**
         * @brief Access the element at the specified row, column index (read-write access).
         *
         * @note Performs bounds checking in **DEBUG MODE**.
         *
         * @param[in] row The row index of the matrix entry.
         * @param[in] col The column index of the matrix entry.
         *
         * @return A reference to the element at row, col.
         */
        [[nodiscard]] constexpr T& operator()(std::size_t row, std::size_t col) noexcept;


        /**
         * @brief Access the element at the specified row, column index (read-only).
         *
         * @note Performs bounds checking in **DEBUG MODE**.
         *
         * @param[in] row The row index of the matrix entry.
         * @param[in] col The column index of the matrix entry.
         *
         * @return A const reference to the element at row, col.
         */
        [[nodiscard]] constexpr const T& operator()(std::size_t row, std::size_t col) const noexcept;

        /** @} */



        /**
         * @addtogroup FALCON_Mat3x3_Equality
         * @{
         */

        /**
         * @brief Compare all elements of this matrix for equality with another matrix.
         *        Perform an element-wise comparison and returns true only if every element pair
         *        satisfies the equality condition within the given @p epsilon.
         *
         * @note Implements an explicit constexpr MSVC workaround to ensure IEEE 754 NaN compliance
         *       during static evaluation.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs     The matrix to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if all elements are equivalent within @p epsilon.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr bool allEq(const Mat3<U>& rhs,
                                           double epsilon = std::is_same_v<T, double> || std::is_same_v<U, double>
                                               ? Config::DOUBLE_EPSILON
                                               : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @brief Compare all elements of a matrix for equality with another matrix.
         *        Perform an element-wise comparison and returns true only if every element pair
         *        satisfies the equality condition within the given @p epsilon.
         *
         * @note Implements an explicit constexpr MSVC workaround to ensure IEEE 754 NaN compliance
         *       during static evaluation.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The matrix to compare.
         * @param[in] rhs     The matrix to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if all elements are equivalent within @p epsilon.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr bool allEq(const Mat3& lhs, const Mat3<U>& rhs,
                                                  double epsilon = std::is_same_v<T, double> ||
                                                          std::is_same_v<U, double>
                                                      ? Config::DOUBLE_EPSILON
                                                      : Config::FLOAT_EPSILON) noexcept;


        /**
         * @brief Compare all elements of this matrix for equality with another matrix.
         *        Perform an element-wise comparison and returns true if any corresponding elements differ by more
         *        than @p epsilon.
         *
         * @note Implements an explicit constexpr MSVC workaround to ensure IEEE 754 NaN compliance
         *       during static evaluation.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs     The matrix to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if all elements are equivalent within @p epsilon.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr bool anyNeq(const Mat3<U>& rhs,
                                            double epsilon = std::is_same_v<T, double> || std::is_same_v<U, double>
                                                ? Config::DOUBLE_EPSILON
                                                : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @brief Compare all elements of this matrix for equality with another matrix.
         *        Perform an element-wise comparison and returns true if any corresponding elements differ by more
         *        than @p epsilon.
         *
         * @note Implements an explicit constexpr MSVC workaround to ensure IEEE 754 NaN compliance
         *       during static evaluation.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The matrix to compare.
         * @param[in] rhs     The matrix to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if all elements are equivalent within @p epsilon.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr bool anyNeq(const Mat3& lhs, const Mat3<U>& rhs,
                                                   double epsilon = std::is_same_v<T, double> ||
                                                           std::is_same_v<U, double>
                                                       ? Config::DOUBLE_EPSILON
                                                       : Config::FLOAT_EPSILON) noexcept;


        /**
         * @copybrief allEq(const Mat3<U>&, double) const noexcept
         *
         * @note Implements an explicit constexpr MSVC workaround to ensure IEEE 754 NaN compliance
         *       during static evaluation.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs The matrix to compare against.
         *
         * @return True if all elements are equivalent within the default epsilon.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr bool operator==(const Mat3<U>& rhs) const noexcept;


        /**
         * @copybrief anyNeq(const Mat3<U>&, double) const noexcept
         *
         * @note Implements an explicit constexpr MSVC workaround to ensure IEEE 754 NaN compliance
         *       during static evaluation.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs The matrix to compare against.
         *
         * @return True if any of the elements are not equivalent within the default epsilon.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr bool operator!=(const Mat3<U>& rhs) const noexcept;

        /** @} */


        /**
         * @addtogroup FALCON_Mat3x3_Arithmetic
         * @{
         */

        /**
         * @brief Compute the element-wise sum of this matrix with @p rhs matrix and return a new matrix.
         *
         * @note Promotes the result to the wider type using @ref PromotedMat3<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The matrix to add.
         *
         * @return A new @ref Mat3 containing the element-wise sum.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedMat3<T, U> operator+(const Mat3<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise sum of this matrix with @p rhs matrix in-place.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The matrix to add.
         *
         * @return A reference to this matrix (*this).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        Mat3& operator+=(const Mat3<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise difference between this matrix and @p rhs matrix and return a new matrix.
         *
         * @note Promotes the result to the wider type using @ref PromotedMat3<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The matrix to subtract.
         *
         * @return A new @ref Mat3 containing the element-wise difference.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedMat3<T, U> operator-(const Mat3<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise difference between this matrix and @p rhs matrix in-place.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The matrix to subtract.
         *
         * @return A reference to this matrix (*this).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        constexpr Mat3& operator-=(const Mat3<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise product between this matrix and @p scalar and
         *
         * @note Promotes the result to the wider type using @ref PromotedMat3<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A new @ref Mat3 scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedMat3<T, S> operator*(S scalar) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise product between this matrix and @p scalar in-place.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A reference to this matrix (*this).
         */
        template <StrictArithmetic S>
        constexpr Mat3& operator*=(S scalar) noexcept
            requires StrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FALCON_Mat3x3_Geom
         * @{
         */

        /**
         * @brief Transform the @p Vec **column vector** by this matrix.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} \\
         *                 A_{10} & A_{11} & A_{12} \\
         *                 A_{20} & A_{21} & A_{22}
         *            \end{bmatrix}
         *            \cdot
         *            \begin{bmatrix}
         *                  x \\ y \\ z
         *            \end{bmatrix}
         *            =
         *            \begin{bmatrix}
         *                  x' \\ y' \\ z'
         *            \end{bmatrix}
         *        \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedVec3<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the column vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec The column vector to transform.
         *
         * @return A new @ref Vec3 with applied linear transformations.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedVec3<T, U> operator*(const Vec3<U>& vec) const noexcept
            requires StrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FALCON_Mat3x3_Comp
         * @{
         */

        /**
         * @brief Compose this matrix with @p rhs matrix to form a new matrix.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} \\
         *                 A_{10} & A_{11} & A_{12} \\
         *                 A_{20} & A_{21} & A_{22}
         *            \end{bmatrix}
         *            \cdot
         *            \begin{bmatrix}
         *                  B_{00} & B_{01} & B_{02} \\
         *                  B_{10} & B_{11} & B_{12} \\
         *                  B_{20} & B_{21} & B_{22}
         *            \end{bmatrix}
         *            =
         *            \begin{bmatrix}
         *                  C_{00} & C_{01} & C_{02} \\
         *                  C_{10} & C_{11} & B_{12} \\
         *                  C_{20} & C_{21} & C_{22}
         *            \end{bmatrix}
         *        \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedMat3<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The matrix to multiply.
         *
         * @return A new @ref Mat3 containing the composition of linear transformations.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedMat3<T, U> operator*(const Mat3<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compose this matrix with @p rhs matrix in-place.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} \\
         *                 A_{10} & A_{11} & A_{12} \\
         *                 A_{20} & A_{21} & A_{22}
         *            \end{bmatrix}
         *            \cdot
         *            \begin{bmatrix}
         *                  B_{00} & B_{01} & B_{02} \\
         *                  B_{10} & B_{11} & B_{12} \\
         *                  B_{20} & B_{21} & B_{22}
         *            \end{bmatrix}
         *            =
         *            \begin{bmatrix}
         *                  C_{00} & C_{01} & C_{02} \\
         *                  C_{10} & C_{11} & B_{12} \\
         *                  C_{20} & C_{21} & C_{22}
         *            \end{bmatrix}
         *        \f$
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The matrix to multiply.
         *
         * @return A reference to this matrix (*this).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        constexpr Mat3& operator*=(const Mat3<U>& rhs) noexcept
            requires StrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FALCON_Mat3x3_Algebra
         * @{
         */

        /**
         * @brief Compute the element-wise division of this matrix by @p scalar and return a new matrix.
         *
         * @note Promotes the result to the wider type using @ref PromotedMat3<T, S>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Performs assertion for division by zero in **Debug mode**.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A new @ref Mat3 inverse scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedMat3<T, S> operator/(S scalar) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise division of this matrix by @p scalar in-place.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Performs assertion for division by zero in **Debug mode**.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A reference to this matrix (*this).
         */
        template <StrictArithmetic S>
        constexpr Mat3& operator/=(S scalar) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise division of this matrix by @p scalar and return a new matrix.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this matrix contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to the wider type using @ref PromotedMat3<T, S>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Returns @p fallback if attempting to divide by zero (or below the epsilon threshold), or if any
         *       operand contains NaN.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar   The value to divide the matrix elements by.
         * @param[in] fallback The default matrix to return, when an invalid case is hit like a zero scalar or a NaN
         *                     element.
         *
         * @return A new @ref Mat3 resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has a NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedMat3<T, S> safeDiv(S scalar, Mat3 fallback = Mat3::identity()) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise division of @p mat by @p scalar and return a new matrix.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this matrix contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to the wider type using @ref PromotedMat3<T, S>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Returns @p fallback if attempting to divide by zero (or below the epsilon threshold), or if any
         *       operand contains NaN.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] mat      The matrix to divide.
         * @param[in] scalar   The value to divide the matrix elements by.
         * @param[in] fallback The default matrix to return, when an invalid case is hit like a zero scalar or a NaN
         *                     element.
         *
         * @return A new @ref Mat3 resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has a NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] static constexpr PromotedMat3<T, S> safeDiv(const Mat3& mat, S scalar,
                                                                  Mat3 fallback = Mat3::identity()) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise division of this matrix by @p scalar, return a new matrix,
         *        and updates @p status to reflect the result of the operation.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this vector contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to the wider type using @ref PromotedMat3<T, S>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Returns @ref fallback if attempting to divide by zero (or below the epsilon threshold), or if any
         *       operand contains NaN.
         * @note In the event of multiple failure conditions, data corruption (NaN) takes precedence over mathematical
         *       invalidity (Division by Zero) when reporting status.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar   The value to divide the matrix elements by.
         * @param[out] status  The status flag to store the status of the current operation result.
         *                     For details on status codes see @ref OperationStatus.
         * @param[in] fallback The default matrix to return, when an invalid case is hit like a zero scalar or a NaN
         *                     element.
         *
         * @return A new @ref Mat3 resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedMat3<T, S> tryDiv(S scalar, OperationStatus& status,
                                                          Mat3 fallback = Mat3::identity()) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise division of @p Vec by @p scalar, return a new matrix,
         *        and updates @p status to reflect the result of the operation.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this matrix contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to the wider type using @ref PromotedMat3<T, S>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Returns @ref fallback if attempting to divide by zero (or below the epsilon threshold), or if any
         *       operand contains NaN.
         * @note In the event of multiple failure conditions, data corruption (NaN) takes precedence over mathematical
         *       invalidity (Division by Zero) when reporting status.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] mat      The matrix to divide.
         * @param[in] scalar   The value to divide the matrix elements by.
         * @param[out] status  The status flag to store the status of the current operation result.
         *                     For details on status codes see @ref OperationStatus.
         * @param[in] fallback The default matrix to return, when an invalid case is hit like a zero scalar or a NaN
         *                     element.
         *
         * @return A new @ref Mat3 resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] static constexpr PromotedMat3<T, S> tryDiv(const Mat3& mat, S scalar, OperationStatus& status,
                                                                 Mat3 fallback = Mat3::identity()) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Negate each element of this matrix and return a new @ref Mat3<T>.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @return A new @ref flcn::Mat3 with negated elements.
         */
        [[nodiscard]] constexpr Mat3 operator-() const noexcept
            requires SignedStrictArithmetic<T>;

        /** @} */


        /**
         * @addtogroup FALCON_Mat3x3_Algebra
         * @{
         */

        /**
         * @brief Compute the determinant (scaling factor) of this matrix.
         *        \f$
         *            \begin{align*}
         *                \text{det(A)} &= A_{00} \cdot (A_{11} \cdot A_{22} - A_{21} \cdot A_{12}) \\
         *                              &- A_{01} \cdot (A_{10} \cdot A_{22} - A_{20} \cdot A_{12}) \\
         *                              &+ A_{02} \cdot (A_{10} \cdot A_{21} - A_{20} \cdot A_{11})
         *            \end{align*}
         *        \f$
         *
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         *
         * @return A non-zero scalar if the matrix is non-singular, else zero.
         */
        [[nodiscard]] constexpr T determinant() const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the determinant (scaling factor) of @p matrix.
         *        \f$
         *            \begin{align*}
         *                \text{det(A)} &= A_{00} \cdot (A_{11} \cdot A_{22} - A_{21} \cdot A_{12}) \\
         *                              &- A_{01} \cdot (A_{10} \cdot A_{22} - A_{20} \cdot A_{12}) \\
         *                              &+ A_{02} \cdot (A_{10} \cdot A_{21} - A_{20} \cdot A_{12})
         *            \end{align*}
         *        \f$
         *
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         *
         * @param matrix The matrix to compute the determinant of.
         *
         * @return A non-zero scalar if the matrix is non-singular, else zero.
         */
        static constexpr T determinant(const Mat3& matrix) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Transpose this matrix by swapping its rows and columns.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} \\
         *                 A_{10} & A_{11} & A_{12} \\
         *                 A_{20} & A_{21} & A_{22}
         *            \end{bmatrix} ^ \top
         *            =
         *            \begin{bmatrix}
         *                 A_{00} & A_{10} & A_{20} \\
         *                 A_{01} & A_{11} & A_{21} \\
         *                 A_{02} & A_{12} & A_{22}
         *            \end{bmatrix}
         *        \f$
         *
         * @return A new @ref Mat3 with its elements flipped along the diagonal.
         */
        [[nodiscard("Transpose does not mutate the matrix. Discarding the result will not produce any change.")]]
        constexpr Mat3 transpose() const noexcept;


        /**
         * @brief Transpose @p matrix by swapping its rows and columns.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} \\
         *                 A_{10} & A_{11} & A_{12} \\
         *                 A_{20} & A_{21} & A_{22}
         *            \end{bmatrix} ^ \top
         *            =
         *            \begin{bmatrix}
         *                 A_{00} & A_{10} & A_{20} \\
         *                 A_{01} & A_{11} & A_{21} \\
         *                 A_{02} & A_{12} & A_{22}
         *            \end{bmatrix}
         *        \f$
         *
         * @param matrix The matrix to transpose.
         *
         * @return A new @ref Mat3 with its elements flipped along the diagonal.
         */
        [[nodiscard("Transpose does not mutate the matrix. Discarding the result will not produce any change.")]]
        static constexpr Mat3 transpose(const Mat3& matrix) noexcept;


        /**
         * @brief Compute the inverse of this matrix.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} \\
         *                 A_{10} & A_{11} & A_{12} \\
         *                 A_{20} & A_{21} & A_{22}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{det(A)}
         *            \begin{bmatrix}
         *                 b  \times c \\
         *                 c  \times a \\
         *                 a  \times b
         *            \end{bmatrix}
         *        \f$
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Performs assertion for division by zero (singular matrix) in **Debug mode**.
         *
         * @return A new @ref Mat3 such that \f$ A \cdot A^{-1} = I \f$.
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
        constexpr Mat3<Magnitude<T>> inverse() const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the inverse of a matrix.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} \\
         *                 A_{10} & A_{11} & A_{12} \\
         *                 A_{20} & A_{21} & A_{22}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{det(A)}
         *            \begin{bmatrix}
         *                 b  \times c \\
         *                 c  \times a \\
         *                 a  \times b
         *            \end{bmatrix}
         *        \f$
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Performs assertion for division by zero (singular matrix) in **Debug mode**.
         *
         * @param[in] matrix The matrix to invert.
         *
         * @return A new @ref Mat3 such that \f$ A \cdot A^{-1} = I \f$.
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
        static constexpr Mat3<Magnitude<T>> inverse(const Mat3& matrix) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the inverse of this matrix.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} \\
         *                 A_{10} & A_{11} & A_{12} \\
         *                 A_{20} & A_{21} & A_{22}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{det(A)}
         *            \begin{bmatrix}
         *                 b  \times c \\
         *                 c  \times a \\
         *                 a  \times b
         *            \end{bmatrix}
         *        \f$
         *
         * @note If the determinant is zero (or below the epsilon threshold) or this matrix contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Returns @p fallback if attempting to invert a singular matrix or a matrix with NaN entries.
         *
         * @param[in] fallback The default matrix to return, when an invalid case is encountered.
         *
         * @return  A new @ref Mat3 such that \f$ A \cdot A^{-1} = I \f$ or
         *          @p fallback if this matrix is a singular matrix or has NaN(Not-a-Number) element(s).
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
        constexpr Mat3<Magnitude<T>> safeInverse(Mat3 fallback = Mat3::identity()) const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the inverse of @p matrix.
         *        \f$
         *            \begin{bmatrix}
         *                A_{00} & A_{01} & A_{02} \\
         *                A_{10} & A_{11} & A_{12} \\
         *                A_{20} & A_{21} & A_{22}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{det(A)}
         *            \begin{bmatrix}
         *                 b  \times c \\
         *                 c  \times a \\
         *                 a  \times b
         *            \end{bmatrix}
         *        \f$
         *
         * @note If the determinant is zero (or below the epsilon threshold) or this matrix contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Returns @p fallback if attempting to invert a singular matrix or a matrix with NaN entries.
         *
         * @param[in] matrix   The matrix to invert.
         * @param[in] fallback The default matrix to return, when an invalid case is encountered.
         *
         * @return  A new @ref Mat3 such that \f$ A \cdot A^{-1} = I \f$ or
         *          @p fallback if this matrix is a singular matrix or has NaN(Not-a-Number) element(s).
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
        static constexpr Mat3<Magnitude<T>> safeInverseOf(const Mat3& matrix, Mat3 fallback = Mat3::identity()) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the inverse of this matrix and set @p status to the matrix inversion result.
         *        \f$
         *            \begin{bmatrix}
         *                A_{00} & A_{01} & A_{02} \\
         *                A_{10} & A_{11} & A_{12} \\
         *                A_{20} & A_{21} & A_{22}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{det(A)}
         *            \begin{bmatrix}
         *                 b  \times c \\
         *                 c  \times a \\
         *                 a  \times b
         *            \end{bmatrix}
         *        \f$
         *
         * @note If the determinant is zero (or below the epsilon threshold) or this matrix contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Returns @p fallback if attempting to invert a singular matrix or a matrix with NaN entries.
         *
         * @param[out] status  The status flag to store the status of the current operation result.
         *                     For details on status codes see @ref OperationStatus.
         * @param[in] fallback The default matrix to return, when an invalid case is encountered.
         *
         * @return  A new @ref Mat3 such that \f$ A \cdot A^{-1} = I \f$ or
         *          @p fallback if this matrix is a singular matrix or has NaN(Not-a-Number) element(s).
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
        constexpr Mat3<Magnitude<T>> tryInverse(OperationStatus& status,
                                                Mat3 fallback = Mat3::identity()) const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the inverse of @p matrix and set @p status to the matrix inversion result.
         *        \f$
         *            \begin{bmatrix}
         *                A_{00} & A_{01} & A_{02} \\
         *                A_{10} & A_{11} & A_{12} \\
         *                A_{20} & A_{21} & A_{22}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{det(A)}
         *            \begin{bmatrix}
         *                 b  \times c \\
         *                 c  \times a \\
         *                 a  \times b
         *            \end{bmatrix}
         *        \f$
         *
         * @note If the determinant is zero (or below the epsilon threshold) or this matrix contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Returns @p fallback if attempting to invert a singular matrix or a matrix with NaN entries.
         *
         * @param[in] matrix   The matrix to invert.
         * @param[out] status  The status flag to store the status of the current operation result.
         *                     For details on status codes see @ref OperationStatus.
         * @param[in] fallback The default matrix to return, when an invalid case is encountered.
         *
         * @return  A new @ref Mat3 such that \f$ A \cdot A^{-1} = I \f$ or
         *          @p fallback if this matrix is a singular matrix or has NaN(Not-a-Number) element(s).
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
        static constexpr Mat3<Magnitude<T>> tryInverseOf(const Mat3& matrix, OperationStatus& status,
                                                         Mat3 fallback = Mat3::identity()) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the sum of diagonal entries of this matrix.
         *
         * @return The sum of entries along the main diagonal of this matrix.
         */
        [[nodiscard]] constexpr T trace() const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the sum of diagonal entries of @p matrix.
         *
         * @param matrix The matrix whose trace is to be computed.
         *
         * @return The sum of entries along the main diagonal of the given matrix.
         */
        [[nodiscard]] static constexpr T trace(const Mat3& matrix) noexcept
            requires StrictArithmetic<T>;

        /** @} */


        /**
         * @addtogroup FALCON_Mat3x3_Utils
         * @{
         */

        /**
         * @brief Check if any element of this matrix is an IEEE 754 infinity.
         *
         * @note Always returns false for integral types.
         *
         * @return True if at least one element is positive or negative infinity.
         */
        [[nodiscard]] constexpr bool hasInf() const noexcept;


        /**
         * @brief Check if any element of @p matrix is an IEEE 754 infinity.
         *
         * @note Always returns false for integral types.
         *
         * @param matrix The matrix to evaluate for indefinite elements.
         *
         * @return True if at least one element is positive or negative infinity.
         */
        [[nodiscard]] static constexpr bool hasInf(const Mat3& matrix) noexcept;


        /**
         * @brief Check if any element of this matrix is an IEEE NaN(Not-a-Number).
         *
         * @note Always return false for integral types.
         *
         * @return True if at least one element is NaN.
         */
        [[nodiscard]] constexpr bool hasNaN() const noexcept;


        /**
         * @brief Check if any element of @p matrix is an IEEE NaN(Not-a-Number).
         *
         * @note Always return false for integral types.
         *
         * @param matrix The matrix to evaluate for indefinite elements.
         *
         * @return True if at least one element is NaN.
         */
        [[nodiscard]] static constexpr bool hasNaN(const Mat3& matrix) noexcept;

        /** @} */


        /**
         * @addtogroup FALCON_Mat3x3_Log
         * @{
         */

        /**
         * @brief Write the matrix to an output stream in **row-major** order.
         *        Format the matrix as
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{10} & A_{20} \\
         *                 A_{01} & A_{11} & A_{21} \\
         *                 A_{02} & A_{12} & A_{22}
         *            \end{bmatrix}
         *        \f$ string representation for debugging or logging.
         *
         * @param os     The output stream to write to.
         * @param matrix The matrix to be streamed.
         *
         * @return A reference to the output stream @p os.
         */
        friend std::ostream& operator<<(std::ostream& os, const Mat3& matrix)
        {
            const std::streamsize oldPrecision     = os.precision();
            const std::ios_base::fmtflags oldFlags = os.flags();

            auto precision = Config::useFullPrecision
                ? std::is_same_v<T, double> ? Config::DOUBLE_PRECISION : Config::FLOAT_PRECISION
                : Config::LOG_PRECISION;
            os << std::setprecision(precision) << std::fixed;
            os << "|" << matrix._data[0][0] << " " << matrix._data[1][0] << " " << matrix._data[2][0] << "|\n";
            os << "|" << matrix._data[0][1] << " " << matrix._data[1][1] << " " << matrix._data[2][1] << "|\n";
            os << "|" << matrix._data[0][2] << " " << matrix._data[1][2] << " " << matrix._data[2][2] << "|\n";

            os.precision(oldPrecision);
            os.flags(oldFlags);

            return os;
        }

        /** @} */

        /**
         * @addtogroup FALCON_Mat3x3_Transforms
         * @{
         */

        /**
         * @brief Construct a 3D rotation matrix in the x-axis for a given angle.
         *
         * @details The layout of the returned matrix adapts to the library's active coordinate system:
         *          - **Right-Handed (Default):**
         *            \f$
         *                \begin{bmatrix}
         *                    1 &            0 &            0 \\
         *                    0 &  cos(\theta) & -sin(\theta) \\
         *                    0 &  sin(\theta) &  cos(\theta)
         *                \end{bmatrix}
         *            \f$
         *          - **Left-Handed (FALCON_LEFT_HANDED):**
         *            \f$
         *                \begin{bmatrix}
         *                    1 &            0 &           0 \\
         *                    0 &  cos(\theta) & sin(\theta) \\
         *                    0 & -sin(\theta) & cos(\theta)
         *                \end{bmatrix}
         *            \f$
         *
         * @note While it is possible to create a rotation matrix of any **signed type**, it is strongly discouraged.
         *       Trigonometric results will be truncated, resulting in severe precision loss and potential zero-matrices
         *       for integral types.
         *
         * @tparam U Numeric type of the angle. Must satisfy `std::floating_point`.
         *
         * @param[in] angle The rotation angle in radians.
         *
         * @return A new @ref Mat3 representing the linear rotation around x-axis.
         */
        template <std::floating_point U>
        [[nodiscard]] static constexpr Mat3 makeRotationX(U angle) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Construct a 3D rotation matrix in the y-axis for a given angle.
         *
         * @details The layout of the returned matrix adapts to the library's active coordinate system:
         *          - **Right-Handed (Default):**
         *            \f$
         *                \begin{bmatrix}
         *                     cos(\theta) & 0 & sin(\theta) \\
         *                     0           & 1 &           0 \\
         *                    -sin(\theta) & 0 & cos(\theta)
         *                \end{bmatrix}
         *            \f$
         *          - **Left-Handed (FALCON_LEFT_HANDED):**
         *            \f$
         *                \begin{bmatrix}
         *                    cos(\theta) & 0 & -sin(\theta) \\
         *                    0           & 1 &           0 \\
         *                    sin(\theta) & 0 &  cos(\theta)
         *                \end{bmatrix}
         *            \f$
         *
         * @note While it is possible to create a rotation matrix of any **signed type**, it is strongly discouraged.
         *       Trigonometric results will be truncated, resulting in severe precision loss and potential zero-matrices
         *       for integral types.
         *
         * @tparam U Numeric type of the angle. Must satisfy `std::floating_point`.
         *
         * @param[in] angle The rotation angle in radians.
         *
         * @return A new @ref Mat3 representing the linear rotation around y-axis.
         */
        template <std::floating_point U>
        [[nodiscard]] static constexpr Mat3 makeRotationY(U angle) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Construct a 3D rotation matrix in the z-axis for a given angle.
         *
         * @details The layout of the returned matrix adapts to the library's active coordinate system:
         *          - **Right-Handed (Default):**
         *            \f$
         *                \begin{bmatrix}
         *                     cos(\theta) & -sin(\theta) & 0 \\
         *                     sin(\theta) &  cos(\theta) & 0 \\
         *                               0 &            0 & 1
         *                \end{bmatrix}
         *            \f$
         *          - **Left-Handed (FALCON_LEFT_HANDED):**
         *            \f$
         *                \begin{bmatrix}
         *                     cos(\theta) & sin(\theta) & 0 \\
         *                    -sin(\theta) & cos(\theta) & 0 \\
         *                               0 &            0 & 1
         *                \end{bmatrix}
         *            \f$
         *
         * @note While it is possible to create a rotation matrix of any **signed type**, it is strongly discouraged.
         *       Trigonometric results will be truncated, resulting in severe precision loss and potential zero-matrices
         *       for integral types.
         *
         * @tparam U Numeric type of the angle. Must satisfy `std::floating_point`.
         *
         * @param[in] angle The rotation angle in radians.
         *
         * @return A new @ref Mat3 representing the linear rotation around z-axis.
         */
        template <std::floating_point U>
        [[nodiscard]] static constexpr Mat3 makeRotationZ(U angle) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Construct a 2D affine rotation matrix around @p center.
         *
         * @details The layout of the returned matrix adapts to the library's active coordinate system:
         *          - **Right-Handed (Default):**
         *            \f$
         *                \begin{bmatrix}
         *                     cos(\theta) & -sin(\theta) & x \\
         *                     sin(\theta) &  cos(\theta) & y \\
         *                               0 &            0 & 1
         *                \end{bmatrix}
         *            \f$
         *          - **Left-Handed (FALCON_LEFT_HANDED):**
         *            \f$
         *                \begin{bmatrix}
         *                     cos(\theta) & sin(\theta) & x \\
         *                    -sin(\theta) & cos(\theta) & y \\
         *                               0 &           0 & 1
         *                \end{bmatrix}
         *            \f$
         *
         * @note While it is possible to create a rotation matrix of any **signed type**, it is strongly discouraged.
         *       Trigonometric results will be truncated, resulting in severe precision loss and potential zero-matrices
         *       for integral types.
         *
         * @tparam U Numeric type of the angle. Must satisfy `std::floating_point`.
         *
         * @param[in] angle  The rotation angle in radians.
         * @param[in] center The center of rotation.
         *
         * @return A new @ref Mat3 representing a 2D affine rotation.
         */
        template <std::floating_point U>
        [[nodiscard]] static constexpr Mat3 makeRotation(U angle, const CVec2<T>& center) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Construct a 3D rotation matrix about the @p axis (normalized) for a given angle.
         *
         * @details The layout of the returned matrix adapts to the library's active coordinate system:
         *          - **Right-Handed (Default):** Anticlockwise Rotation
         *          - **Left-Handed (FALCON_LEFT_HANDED):** Clockwise Rotation
         *          - Uses Rodrigues' formula
         *            \f$
         *            \textbf{v}_{Rot} =
         *                              \textbf{v} \cos{\theta} +
         *                              \textbf{k}(\textbf{k}\cdot\textbf{v})(1-\cos{\theta}) +
         *                              (\textbf{k} \times \textbf{v}) \sin{\theta}
         *            \f$
         *
         * @tparam U Numeric type of the angle. Must satisfy `std::floating_point`.
         *
         * @param[in] angle The rotation angle in radians.
         * @param[in] axis  The axis of rotation. Must be a unit vector.
         *
         * @return A new @ref Mat3 representing the linear rotation around @p axis
         *         promoted to the nearest floating point type.
         *
         * @relatedalso makeRotationNonNorm(U, const Vec3<T>&) // TODO:
         * @relatedalso makeRotation(U, const Vec3<T>&, const Vec3<T>&)
         * @relatedalso makeRotationX(U)
         * @relatedalso makeRotationX(U, const Vec3<T>&)
         * @relatedalso makeRotationY(U)
         * @relatedalso makeRotationY(U, const Vec3<T>&)
         * @relatedalso makeRotationZ(U)
         * @relatedalso makeRotationZ(U, const Vec3<T>&)
         */
        template <std::floating_point U>
        [[nodiscard]] static constexpr PromotedFloatMat3<T, U> makeRotation(U angle, const Vec3<T>& axis) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Construct a uniform scale 3D matrix.
         *
         * @param[in] scale The scale factor.
         *
         * @return A new @ref Mat3 representing the uniform scale.
         */
        [[nodiscard]] static constexpr Mat3 makeScale(T scale) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Construct a non-uniform scale 3D matrix.
         *
         * @param[in] scaleX The scale factor in the x-direction.
         * @param[in] scaleY The scale factor in the y-direction.
         * @param[in] scaleZ The scale factor in the z-direction.
         *
         * @return A new @ref Mat3 representing the non-uniform scale.
         */
        [[nodiscard]] static constexpr Mat3 makeScale(T scaleX, T scaleY, T scaleZ) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Construct a 3D scale matrix for scaling along @p direction.
         *
         * @note While it is possible to create a scale matrix of any **signed type**, it is strongly discouraged
         *       in favor of floating point types due loss of precision from rounding, often resulting in a zero
         *       matrix.
         *
         * @param[in] scale       The scale factor.
         * @param[in] direction   The direction to scale along. Must be a unit vector.
         *
         * @return A new @ref Mat3 representing the scale matrix along a given direction.
         */
        [[nodiscard]] static constexpr Mat3 makeScale(T scale, const Vec3<T>& direction) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Construct a 3D reflection matrix across coordinate axis, any 2D plane formed by the axes,
         *        or the origin.
         *
         * @note Factory is constrained to matrices of signed types.
         *
         * @tparam On The plane or axis to reflect across. For more details @ref flcn::reflect for more details.
         *
         * @return A new @ref Mat3 representing the reflection across coordinate axis, plane or the origin.
         *
         * @relatedalso makeReflection(const Vec3<T>&)
         */
        template <reflect::RT On>
        [[nodiscard]] static constexpr Mat3 makeReflection() noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Construct a 3D reflection matrix across any plane through the origin with @p normal.
         *
         * @note Ensure that @p normal is the normal to the plane. If you want coordinate axis reflection you should
         *       pass the axis perpendicular to the axes that forms the plane. For example, you need to make sure to
         *       pass in <0, 0, 1>(z-axis) for reflection in the yz-plane, not <1, 1, 0>.
         * @note While it is possible to create a rotation matrix of any **signed type**, it is strongly discouraged
         *       in favor of floating point types due loss of precision from rounding, often resulting in a zero
         *       matrix.
         *
         * @param[in] normal Normal of the reflection plane. Must be a unit vector.
         *
         * @return A new @ref Mat3 representing the reflection matrix across a given plane.
         *
         * @relatedalso makeReflection<RT>()
         */
        [[nodiscard]] static constexpr Mat3 makeReflection(const Vec3<T>& normal) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Construct a 3D involution matrix across any plane through the origin with @p normal.
         *
         * @note While it is possible to create a involution matrix of any **signed type**, it is strongly discouraged
         *       in favor of floating point types due loss of precision from rounding, often resulting in a zero
         *       matrix.
         *
         * @param[in] normal Normal of the reflection plane. Must be a unit vector.
         *
         * @return A new @ref Mat3 representing the involution matrix across a given plane.
         */
        [[nodiscard]] static constexpr Mat3 makeInvolution(const Vec3<T>& normal) noexcept
            requires SignedStrictArithmetic<T>;



        /**
         * @brief Construct a 2D affine shear matrix along the x-axis (horizontal axis).
         *
         * @param[in] shear The shear amount.
         *
         * @return A new @ref Mat2 representing the affine shear transform by the x-axis.
         *
         * @relatedalso makeShearY2D(T)
         * @relatedalso makeShearX3D(T, T)
         * @relatedalso makeShearY3D(T, T)
         * @relatedalso makeShearZ3D(T, T)
         * @relatedalso makeShearByAngle(T, const Vec3<T>&, const Vec3<T>&)
         */
        [[nodiscard]] static constexpr Mat3 makeShearX2D(T shear) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Construct a 2D affine shear matrix along the y-axis (vertical axis).
         *
         * @param[in] shear The shear amount.
         *
         * @return A new @ref Mat3 representing the affine shear transform by the y-axis.
         *
         * @relatedalso makeShearX2D(T)
         * @relatedalso makeShearX3D(T, T)
         * @relatedalso makeShearY3D(T, T)
         * @relatedalso makeShearZ3D(T, T)
         * @relatedalso makeShearByAngle(T, const Vec3<T>&, const Vec3<T>&)
         * @relatedalso makeShear(T, const Vec3<T>&, const Vec3<T>&)
         */
        [[nodiscard]] static constexpr Mat3 makeShearY2D(T shear) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Construct a 3D shear matrix along the x-axis (YZ plane).
         *
         * @param[in] shearY The shear amount on the y-axis.
         * @param[in] shearZ The shear amount on the z-axis.
         *
         * @return A new @ref Mat3 representing the shear transform by the x-axis.
         *
         * @relatedalso makeShearX2D(T)
         * @relatedalso makeShearY2D(T)
         * @relatedalso makeShearY3D(T, T)
         * @relatedalso makeShearZ3D(T, T)
         * @relatedalso makeShearByAngle(T, const Vec3<T>&, const Vec3<T>&)
         * @relatedalso makeShear(T, const Vec3<T>&, const Vec3<T>&)
         */
        [[nodiscard]] static constexpr Mat3 makeShearX3D(T shearY, T shearZ) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Construct a 3D shear matrix along the y-axis (ZX plane).
         *
         * @param[in] shearX The shear amount on the x-axis.
         * @param[in] shearZ The shear amount on the z-axis.
         *
        * @return A new @ref Mat3 representing the shear transform by the y-axis.
        *
         * @relatedalso makeShearX2D(T)
         * @relatedalso makeShearY2D(T)
         * @relatedalso makeShearX3D(T, T)
         * @relatedalso makeShearZ3D(T, T)
         * @relatedalso makeShearByAngle(T, const Vec3<T>&, const Vec3<T>&)
         * @relatedalso makeShear(T, const Vec3<T>&, const Vec3<T>&)
         */
        [[nodiscard]] static constexpr Mat3 makeShearY3D(T shearX, T shearZ) noexcept
            requires StrictArithmetic<T>;
        // TODO: Update parameters to be reversed

        /**
         * @brief Construct a 3D shear matrix along the y-axis (XY plane).
         *
         * @param[in] shearX The shear amount on the x-axis.
         * @param[in] shearY The shear amount on the y-axis.
         *
         * @return A new @ref Mat3 representing the shear transform by the z-axis.
         *
         * @relatedalso makeShearX2D(T)
         * @relatedalso makeShearY2D(T)
         * @relatedalso makeShearX3D(T, T)
         * @relatedalso makeShearY3D(T, T)
         * @relatedalso makeShearByAngle(T, const Vec3<T>&, const Vec3<T>&)
         * @relatedalso makeShear(T, const Vec3<T>&, const Vec3<T>&)
         */
        [[nodiscard]] static constexpr Mat3 makeShearZ3D(T shearX, T shearY) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Construct a 3D transformation matrix that shears by @p shearAngle along @p direction.
         *
         * @note For value-based shears use @ref makeShear or any of the component axis variants.
         * @note Constrained to floating point types via `std::floating_point<T>`.
         *
         * @param[in] shearAngle The shear angle in radians.
         * @param[in] direction  The direction of shear. Must be a unit vector.
         * @param[in] normal     The unit vector orthogonal to shear direction.
         *
         * @code
         *      const flcn::Vec3 xAxis(1.0f, 0.0f, 0.0f);
         *      const flcn::Vec3 zAxis(0.0f, 0.0f, 1.0f);
         *      const auto shearAngle = 3.1415f / 4.0f;
         *      const auto shearMat = flcn::Mat3<float>::makeShearByAngle(shearAngle, xAxis, zAxis);
         * @endcode
         *
         * @return A new @ref Mat3 representing the affine shear transform.
         *
         * @relatedalso makeShearX2D(T)
         * @relatedalso makeShearY2D(T)
         * @relatedalso makeShearX3D(T, T)
         * @relatedalso makeShearY3D(T, T)
         * @relatedalso makeShearZ3D(T, T)
         * @relatedalso makeShear(T, const Vec3<T>&, const Vec3<T>&)
         */
        [[nodiscard]] static constexpr Mat3 makeShearByAngle(T shearAngle, const Vec3<T>& direction,
                                                             const Vec3<T>& normal) noexcept
            requires std::floating_point<T>;


        /**
         * @brief Construct a 3D transformation matrix that shears by @p shearFactor along @p direction.
         *
         * @note For angle based shears use @ref makeShearByAngle.
         * @note Constrained to floating point types via `std::floating_point<T>`.
         *
         * @param[in] shearFactor The shear angle in radians.
         * @param[in] direction  The direction of shear. Must be a unit vector.
         * @param[in] normal     The unit vector orthogonal to shear direction.
         *
         * @code
         *      const flcn::Vec3 xAxis(1.0f, 0.0f, 0.0f);
         *      const flcn::Vec3 zAxis(0.0f, 0.0f, 1.0f);
         *      const auto shearAngle = 3.1415f / 4.0f;
         *      const auto shearValue = std::tan(shearAngle);
         *      const auto shearMat = flcn::Mat3<float>makeShear(shearValue, xAxis, zAxis);
         * @endcode
         *
         * @return A new @ref Mat3 representing the affine shear transform.
         *
         * @relatedalso makeShearX2D(T)
         * @relatedalso makeShearY2D(T)
         * @relatedalso makeShearX3D(T, T)
         * @relatedalso makeShearY3D(T, T)
         * @relatedalso makeShearZ3D(T, T)
         * @relatedalso makeShearByAngle(T, const Vec3<T>&, const Vec3<T>&)
         */
        [[nodiscard]] static constexpr Mat3 makeShear(T shearFactor, const Vec3<T>& direction,
                                                      const Vec3<T>& normal) noexcept
            requires std::floating_point<T>;


        /**
         * @brief Construct a 2D affine transform matrix from a 2D linear transform matrix and a 2D translation vector.
         * @param linearTransform The 2D linear transformation matrix.
         * @param translation     The 2D translation vector.
         * @return A @ref Mat3 containing the 2D affine transformation.
         */
        [[nodiscard]] static constexpr Mat3 makeAffine(const Mat2<T>& linearTransform,
                                                       const CVec2<T>& translation) noexcept;

        /** @} */


        /**
         * @addtogroup T_FALCON_Mat3x3_Constant
         * @{
         */

        // NOLINTBEGIN

        /**************************************
         *                                    *
         *             CONSTANTS              *
         *                                    *
         **************************************/

        /**
         * @brief A 3D matrix with ones on the main diagonal and zeros elsewhere.
         *
         * @note Constrained to @ref StrictArithmetic types.
         */
        static constexpr Mat3 identity()
            requires flcn::StrictArithmetic<T>
        { return Mat3{ T(1), T(0), T(0), T(0), T(1), T(0), T(0), T(0), T(1) }; }


        /**
         * @brief A 3D matrix with all zero elements.
         *
         * @note Constrained to @ref StrictArithmetic types.
         */
        static constexpr Mat3 zero()
            requires flcn::StrictArithmetic<T>
        { return Mat3{ T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0) }; }

        // NOLINTEND

        /** @} */

    private:
        std::array<Vec3<T>, COLUMNS> _data;
    };


    /**
     * @addtogroup FALCON_Ma3x3_Alias
     * @{
     */

    /*************************************
     *                                   *
     *             ALIASES               *
     *                                   *
     *************************************/

    using Mat3B   = Mat3<int8_t>;   ///< Signed Byte (8-bit) matrix
    using Mat3UB  = Mat3<uint8_t>;  ///< Unsigned Byte (8-bit) matrix
    using Mat3I   = Mat3<int32_t>;  ///< Signed Int (32-bit) matrix
    using Mat3U   = Mat3<uint32_t>; ///< Unsigned Int (32-bit) matrix
    using Mat3F   = Mat3<float>;    ///< Single Precision Floating Point (32-bit) matrix
    using Mat3LL  = Mat3<int64_t>;  ///< Signed Long Long (64-bit) matrix
    using Mat3D   = Mat3<double>;   ///< Double Precision Floating Point (64-bit) matrix
    using Mat3ULL = Mat3<uint64_t>; ///< Unsigned Long Long (64-bit) matrix

    /** @} */



    /**************************************
     *                                    *
     *        NON-MEMBER FUNCTIONS        *
     *                                    *
     **************************************/

    /**
     * @addtogroup FALCON_Mat3x3_Arithmetic
     * @{
     */

    /**
     * @brief Compute the element-wise product between @p matrix and @p scalar and return a new matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat3<T, S>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] scalar The value to scale by.
     * @param[in] matrix The matrix to scale.
     *
     * @return A new @ref Mat3 scaled by @p scalar.
     */
    template <StrictArithmetic T, StrictArithmetic S>
    [[nodiscard]] constexpr PromotedMat3<T, S> operator*(S scalar, const Mat3<T>& matrix) noexcept;

    /** @} */



    /**
     * @addtogroup FALCON_Mat3x3_Geom
     * @{
     */

    /**
     * @brief Transform the @p Vec **row vector** by @p matrix.
     *        \f$
     *            \begin{bmatrix}
     *                x & y & z
     *            \end{bmatrix}
     *            \cdot
     *            \begin{bmatrix}
     *                A_{00} & A_{01} & A_{02} \\
     *                A_{10} & A_{11} & A_{12} \\
     *                A_{20} & A_{21} & A_{22}
     *            \end{bmatrix}
     *            =
     *            \begin{bmatrix}
     *                x' & y' & z'
     *            \end{bmatrix}
     *        \f$
     *
     * @note Promotes the result to the wider type using @ref PromotedVec3<T, S>.
     * @tparam T Numeric type of the row vector. Must satisfy @ref StrictArithmetic.
     * @tparam S Numeric type of the transformation matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec    The row vector to transform.
     * @param[in] matrix The transformation matrix.
     *
     * @return The passed-in @p Vec with the transformations applied.
     */
    template <StrictArithmetic T, StrictArithmetic S>
    static constexpr PromotedVec3<T, S> operator*(const Vec3<T>& vec, const Mat3<S>& matrix) noexcept;


    /**
     * @brief Transform the @p Vec **row vector** by @p matrix.
     *        Perform the linear transformation:
     *        \f$
     *            \begin{bmatrix}
     *                x & y & z
     *            \end{bmatrix}
     *            \cdot
     *            \begin{bmatrix}
     *                A_{00} & A_{01} & A_{02} \\
     *                A_{10} & A_{11} & A_{12} \\
     *                A_{20} & A_{21} & A_{22}
     *            \end{bmatrix}
     *            =
     *            \begin{bmatrix}
     *                x' & y' & z'
     *            \end{bmatrix}
     *        \f$
     *
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam T Numeric type of the row vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the transformation matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec The row vector to transform.
     * @param[in] matrix The transformation matrix.
     *
     * @return The passed-in @p Vec with the transformations applied.
     */
    template <StrictArithmetic T, StrictArithmetic U>
    static constexpr Vec3<T>& operator*=(Vec3<T>& vec, const Mat3<U>& matrix) noexcept;

    /** @} */


    /** @brief Template deduction guide for Mat3. */
    template <Arithmetic T, Arithmetic... Args>
        requires(std::is_same_v<T, Args> && ...) && (sizeof...(Args) == 8)
    Mat3(T, Args...) -> Mat3<T>;

} // namespace flcn


#include "Mat3.tpp"
