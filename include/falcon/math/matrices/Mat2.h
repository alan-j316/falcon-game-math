#pragma once
/**
 * @file Mat2.h
 * @author Alan Abraham P Kochumon
 * @date Created on: January 30, 2026
 *
 * @brief Templated 2x2 Matrix supporting integral, floating-point, and boolean types.
 *
 * @details Provide high-performance 2x2 matrix implementation with SIMD acceleration
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


#include "falcon/math/common/Types.h"
#include "falcon/math/vectors/CVec2.h"

#include <array>
#include <cstdint>
#include <type_traits>


namespace flcn
{
    template <Arithmetic T>
    struct Mat2
    {

        /**
         * @addtogroup FALCON_Mat2x2_Members
         * @{
         */

        using value_type = T; ///< The numeric type of the matrix elements.

        static constexpr std::size_t COLUMNS = 2; ///< Matrix column count.
        static constexpr std::size_t ROWS    = 2; ///< Matrix row count.


        /** @} */



        /**
         * @addtogroup FALCON_Mat2x2_Init
         * @{
         */

        /**
         * @brief Initialize an uninitialized @ref Mat2 instance.
         *
         * @warning The components are left uninitialized (containing garbage data)
         *          to maximize SIMD optimization and maintain triviality.
         *
         * @note Use value-initialization (`{}`) or the static helper
         *       @ref flcn::Mat2<T>::zero() to guarantee a zeroed matrix.
         */
        Mat2() = default;


        /**
         * @brief Initialize a 2x2 matrix from the passed-in scalar elements.
         *
         * @param[in] m00 The element to insert into row one, column one.
         * @param[in] m01 The element to insert into row one, column two.
         * @param[in] m10 The element to insert into row two, column one.
         * @param[in] m11 The element to insert into row two, column two.
         */
        [[nodiscard]] constexpr Mat2(T m00, T m01, T m10, T m11) noexcept;


        /**
         * @brief Initialize a 2x2 matrix from the passed-in vectors as columns.
         *
         * @param[in] col0 The 2D-vector to use as the first column entry.
         * @param[in] col1 The 2D-vector to use as the second column entry.
         */
        [[nodiscard]] constexpr Mat2(const CVec2<T>& col0, const CVec2<T>& col1) noexcept;


        /**
         * @brief Initialize a diagonal matrix from the passed-in scalar entries.
         *        All non-diagonal elements are initialized to zero.
         *
         * @param[in] d0 The first diagonal entry of the matrix (m00).
         * @param[in] d1 The second diagonal entry of the matrix (m11).
         */
        [[nodiscard]] constexpr Mat2(T d0, T d1) noexcept;


        /**
         * @brief Initialize @ref Mat2 from another @ref Mat2 of a different type.
         *
         * @tparam U Numeric type of the source matrix.
         *
         * @param[in] other The source matrix to be converted.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] explicit constexpr Mat2(const Mat2<U>& other) noexcept;

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
        [[nodiscard]] constexpr CVec2<T>& operator[](std::size_t col) noexcept;


        /**
         * @brief Access the column vector at the specified location (read-only).
         *
         * @note Performs bounds checking in **DEBUG MODE**.
         *
         * @param[in] col The column index of the matrix.
         *
         * @return A const reference to the column vector.
         */
        [[nodiscard]] constexpr const CVec2<T>& operator[](std::size_t col) const noexcept;


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
         * @addtogroup FALCON_Mat2x2_Equality
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
        [[nodiscard]] constexpr bool allEq(const Mat2<U>& rhs,
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
        [[nodiscard]] static constexpr bool allEq(const Mat2& lhs, const Mat2<U>& rhs,
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
        [[nodiscard]] constexpr bool anyNeq(const Mat2<U>& rhs,
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
        [[nodiscard]] static constexpr bool anyNeq(const Mat2& lhs, const Mat2<U>& rhs,
                                                   double epsilon = std::is_same_v<T, double> ||
                                                           std::is_same_v<U, double>
                                                       ? Config::DOUBLE_EPSILON
                                                       : Config::FLOAT_EPSILON) noexcept;


        /**
         * @copybrief allEq(const Mat2<U>&, double) const noexcept
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
        [[nodiscard]] constexpr bool operator==(const Mat2<U>& rhs) const noexcept;


        /**
         * @copybrief anyNeq(const Mat2<U>&, double) const noexcept
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
        [[nodiscard]] constexpr bool operator!=(const Mat2<U>& rhs) const noexcept;

        /** @} */



        /**
         * @addtogroup FALCON_Mat2x2_Arithmetic
         * @{
         */

        /**
         * @brief Compute the element-wise sum of this matrix with @p rhs matrix and return a new matrix.
         *
         * @note Promotes the result to the wider type using @ref PromotedMat2<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The matrix to add.
         *
         * @return A new @ref Mat2 containing the element-wise sum.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedMat2<T, U> operator+(const Mat2<U>& rhs) const noexcept
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
        Mat2& operator+=(const Mat2<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise difference between this matrix and @p rhs matrix and return a new matrix.
         *
         * @note Promotes the result to the wider type using @ref PromotedMat2<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The matrix to subtract.
         *
         * @return A new @ref Mat2 containing the element-wise difference.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedMat2<T, U> operator-(const Mat2<U>& rhs) const noexcept
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
        constexpr Mat2& operator-=(const Mat2<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise product between this matrix and @p scalar and return a new matrix.
         *
         * @note Promotes the result to the wider type using @ref PromotedMat2<T, S>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A new @ref Mat2 scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedMat2<T, S> operator*(S scalar) const noexcept
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
        constexpr Mat2& operator*=(S scalar) noexcept
            requires StrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FALCON_Mat2x2_Geom
         * @{
         */

        /**
         * @brief Transform the @p Vec **column vector** by this matrix.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} \\
         *                 A_{10} & A_{11}
         *            \end{bmatrix}
         *            \cdot
         *            \begin{bmatrix}
         *                  x \\ y
         *            \end{bmatrix}
         *            =
         *            \begin{bmatrix}
         *                  x' \\ y'
         *            \end{bmatrix}
         *        \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedCVec2<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the column vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec The column vector to transform.
         *
         * @return A new @ref CVec2 with applied linear transformations.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedCVec2<T, U> operator*(const CVec2<U>& vec) const noexcept
            requires StrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FALCON_Mat2x2_Comp
         * @{
         */

        /**
         * @brief Compose this matrix with @p rhs matrix to form a new matrix.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} \\
         *                 A_{10} & A_{11}
         *            \end{bmatrix}
         *            \cdot
         *            \begin{bmatrix}
         *                  B_{00} & B_{01} \\
         *                  B_{10} & B_{11}
         *            \end{bmatrix}
         *            =
         *            \begin{bmatrix}
         *                  C_{00} & C_{01} \\
         *                  C_{10} & C_{11}
         *            \end{bmatrix}
         *        \f$
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Promotes the result to the wider type using @ref PromotedMat2<T, U>.
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The matrix to multiply.
         *
         * @return A new @ref Mat2 containing the composition of linear transformations.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedMat2<T, U> operator*(const Mat2<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compose this matrix with @p rhs matrix in-place.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} \\
         *                 A_{10} & A_{11}
         *            \end{bmatrix}
         *            \cdot
         *            \begin{bmatrix}
         *                  B_{00} & B_{01} \\
         *                  B_{10} & B_{11}
         *            \end{bmatrix}
         *            =
         *            \begin{bmatrix}
         *                  C_{00} & C_{01} \\
         *                  C_{10} & C_{11}
         *            \end{bmatrix}
         *        \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedMat2<T, U>.
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
        constexpr Mat2& operator*=(const Mat2<U>& rhs) noexcept
            requires StrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FALCON_Mat2x2_Algebra
         * @{
         */

        /**
         * @brief Compute the element-wise division of this matrix by @p scalar and return a new matrix.
         *
         * @note Promotes the result to the wider type using @ref PromotedMat2<T, S>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Performs assertion for division by zero in **Debug mode**.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A new @ref Mat2 inverse scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedMat2<T, S> operator/(const S& scalar) const noexcept
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
        constexpr Mat2& operator/=(const S& scalar) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise division of this matrix by @p scalar and return a new matrix.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this matrix contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to the wider type using @ref PromotedMat2<T, S>.
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
         * @return A new @ref Mat2 resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has a NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedMat2<T, S> safeDiv(S scalar, Mat2 fallback = Mat2::identity()) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise division of @p mat by @p scalar and return a new matrix.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this matrix contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to the wider type using @ref PromotedMat2<T, S>.
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
         * @return A new @ref Mat2 resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has a NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] static constexpr PromotedMat2<T, S> safeDiv(const Mat2& mat, S scalar,
                                                                  Mat2 fallback = Mat2::identity()) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise division of this matrix by @p scalar, return a new matrix,
         *        and updates @p status to reflect the result of the operation.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this vector contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to the wider type using @ref PromotedMat2<T, S>.
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
         * @return A new @ref Mat2 resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedMat2<T, S> tryDiv(S scalar, OperationStatus& status,
                                                          Mat2 fallback = Mat2::identity()) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise division of @p Vec by @p scalar, return a new matrix,
         *        and updates @p status to reflect the result of the operation.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this matrix contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to the wider type using @ref PromotedMat2<T, S>.
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
         * @return A new @ref Mat2 resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] static constexpr PromotedMat2<T, S> tryDiv(const Mat2& mat, S scalar, OperationStatus& status,
                                                                 Mat2 fallback = Mat2::identity()) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Negate each element of this matrix and return a new @ref Mat2<T>.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @return A new @ref flcn::Mat2 with negated elements.
         */
        [[nodiscard]] constexpr Mat2 operator-() const noexcept
            requires SignedStrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FALCON_Mat2x2_Algebra
         * @{
         */

        /**
         * @brief Compute the determinant (scaling factor) of this matrix.
         *        \f$
         *            \text{det(A)} = A_{00} \cdot A_{11} - A_{01} \cdot A_{10}
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
         *            \text{det(A)} = A_{00} \cdot A_{11} - A_{01} \cdot A_{10}
         *        \f$
         *
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         *
         * @param matrix The matrix to compute the determinant of.
         *
         * @return A non-zero scalar if the matrix is non-singular, else zero.
         */
        static constexpr T determinant(const Mat2& matrix) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Transpose this matrix by swapping its rows and columns.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} \\
         *                 A_{10} & A_{11}
         *            \end{bmatrix} ^ \top
         *            =
         *            \begin{bmatrix}
         *                 A_{00} & A_{10} \\
         *                 A_{01} & A_{11}
         *            \end{bmatrix}
         *        \f$
         *
         * @return A new @ref Mat2 with its elements flipped along the diagonal.
         */
        [[nodiscard("Transpose does not mutate the matrix. Discarding the result will not produce any change.")]]
        constexpr Mat2 transpose() const noexcept;


        /**
         * @brief Transpose @p matrix by swapping its rows and columns.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} \\
         *                 A_{10} & A_{11}
         *            \end{bmatrix} ^ \top
         *            =
         *            \begin{bmatrix}
         *                 A_{00} & A_{10} \\
         *                 A_{01} & A_{11}
         *            \end{bmatrix}
         *        \f$
         *
         * @param matrix The matrix to transpose.
         *
         * @return A new @ref Mat2 with its elements flipped along the diagonal.
         */
        [[nodiscard("Transpose does not mutate the matrix. Discarding the result will not produce any change.")]]
        static constexpr Mat2 transpose(const Mat2& matrix) noexcept;


        /**
         * @brief Compute the inverse of this matrix.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} \\
         *                 A_{10} & A_{11}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{det(A)}
         *            \begin{bmatrix}
         *                 A_{11} & -A_{01} \\
         *                 -A_{10} & A_{00}
         *            \end{bmatrix}
         *        \f$
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Performs assertion for division by zero (singular matrix) in **Debug mode**.
         *
         * @return A new @ref Mat2 such that \f$ A \cdot A^{-1} = I \f$.
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
        constexpr Mat2<Magnitude<T>> inverse() const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the inverse of a matrix.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} \\
         *                 A_{10} & A_{11}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{det(A)}
         *            \begin{bmatrix}
         *                 A_{11} & -A_{01} \\
         *                 -A_{10} & A_{00}
         *            \end{bmatrix}
         *        \f$
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Performs assertion for division by zero (singular matrix) in **Debug mode**.
         *
         * @param[in] matrix The matrix to invert.
         *
         * @return A new @ref Mat2 such that \f$ A \cdot A^{-1} = I \f$.
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
        static constexpr Mat2<Magnitude<T>> inverse(const Mat2& matrix) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the inverse of this matrix.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} \\
         *                 A_{10} & A_{11}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{A_{00}A_{11} - A_{01}A_{10}}
         *            \begin{bmatrix}
         *                 A_{11} & -A_{01} \\
         *                 -A_{10} & A_{00}
         *            \end{bmatrix}
         *        \f$
         * @note If the determinant is zero (or below the epsilon threshold) or this matrix contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Returns @p fallback if attempting to invert a singular matrix or a matrix with NaN entries.
         *
         * @param[in] fallback The default matrix to return, when an invalid case is encountered.
         *
         * @return  A new @ref Mat2 such that \f$ A \cdot A^{-1} = I \f$ or
         *          @p fallback if this matrix is a singular matrix or has NaN(Not-a-Number) element(s).
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
        constexpr Mat2<Magnitude<T>> safeInverse(Mat2 fallback = Mat2::identity()) const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the inverse @p matrix.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} \\
         *                 A_{10} & A_{11}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{A_{00}A_{11} - A_{01}A_{10}}
         *            \begin{bmatrix}
         *                 A_{11} & -A_{01} \\
         *                 -A_{10} & A_{00}
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
         * @return  A new @ref Mat2 such that \f$ A \cdot A^{-1} = I \f$ or
         *          @p fallback if this matrix is a singular matrix or has NaN(Not-a-Number) element(s).
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
        static constexpr Mat2<Magnitude<T>> safeInverseOf(const Mat2& matrix, Mat2 fallback = Mat2::identity()) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the inverse of this matrix and set @p status to the matrix inversion result.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} \\
         *                 A_{10} & A_{11}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{A_{00}A_{11} - A_{01}A_{10}}
         *            \begin{bmatrix}
         *                 A_{11} & -A_{01} \\
         *                 -A_{10} & A_{00}
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
         * @return  A new @ref Mat2 such that \f$ A \cdot A^{-1} = I \f$ or
         *          @p fallback if this matrix is a singular matrix or has NaN(Not-a-Number) element(s).
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
        constexpr Mat2<Magnitude<T>> tryInverse(OperationStatus& status,
                                                Mat2 fallback = Mat2::identity()) const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the inverse of @p matrix and set @p status to the matrix inversion result.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} \\
         *                 A_{10} & A_{11}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{A_{00}A_{11} - A_{01}A_{10}}
         *            \begin{bmatrix}
         *                 A_{11} & -A_{01} \\
         *                 -A_{10} & A_{00}
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
         * @return  A new @ref Mat2 such that \f$ A \cdot A^{-1} = I \f$ or
         *          @p fallback if this matrix is a singular matrix or has NaN(Not-a-Number) element(s).
         */
        [[nodiscard("Inverse does not mutate the matrix. Discarding the result will not produce any change.")]]
        static constexpr Mat2<Magnitude<T>> tryInverseOf(const Mat2& matrix, OperationStatus& status,
                                                         Mat2 fallback = Mat2::identity()) noexcept
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
        [[nodiscard]] static constexpr T trace(const Mat2& matrix) noexcept
            requires StrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FALCON_Mat2x2_Utils
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
        [[nodiscard]] static constexpr bool hasInf(const Mat2& matrix) noexcept;


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
        [[nodiscard]] static constexpr bool hasNaN(const Mat2& matrix) noexcept;

        /** @} */



        /**
         * @addtogroup FALCON_Mat2x2_Log
         * @{
         */

        /**
         * @brief Write the matrix to an output stream in **row-major** order.
         *        Format the matrix as
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{10} \\
         *                 A_{01} & A_{11}
         *            \end{bmatrix}
         *        \f$ string representation for debugging or logging.
         *
         * @param os     The output stream to write to.
         * @param matrix The matrix to be streamed.
         *
         * @return A reference to the output stream @p os.
         */
        friend std::ostream& operator<<(std::ostream& os, const Mat2& matrix)
        {
            const std::streamsize oldPrecision     = os.precision();
            const std::ios_base::fmtflags oldFlags = os.flags();

            auto precision = Config::useFullPrecision
                ? std::is_same_v<T, double> ? Config::DOUBLE_PRECISION : Config::FLOAT_PRECISION
                : Config::LOG_PRECISION;
            os << std::setprecision(precision) << std::fixed;
            os << "|" << matrix._data[0][0] << " " << matrix._data[1][0] << "|\n";
            os << "|" << matrix._data[0][1] << " " << matrix._data[1][1] << "|\n";

            os.precision(oldPrecision);
            os.flags(oldFlags);

            return os;
        }

        /** @} */



        /**
         * @addtogroup FALCON_Mat2x2_Transforms
         * @{
         */

        /**
         * @brief Construct a 2D rotation matrix for a given angle.
         *
         * @details The layout of the returned matrix adapts to the library's active coordinate system:
         *          - **Right-Handed (Default):**
         *            \f$
         *                \begin{bmatrix}
         *                    cos(\theta) & -sin(\theta) \\
         *                    sin(\theta) & cos(\theta)
         *                \end{bmatrix}
         *            \f$
         *          - **Left-Handed (FALCON_LEFT_HANDED):**
         *            \f$
         *                \begin{bmatrix}
         *                    cos(\theta) & sin(\theta) \\
         *                    -sin(\theta) & cos(\theta)
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
         * @return A new @ref Mat2 representing the linear rotation.
         */
        template <std::floating_point U>
        [[nodiscard]] static constexpr Mat2 makeRotation(U angle) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Construct a uniform scale 2D matrix.
         *
         * @param[in] scale The scale factor.
         *
         * @return A new @ref Mat2 representing the uniform scale.
         */
        [[nodiscard]] static constexpr Mat2 makeScale(T scale) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Construct a non-uniform scale 2D matrix.
         *
         * @param[in] scaleX The scale factor in the x-direction.
         * @param[in] scaleY The scale factor in the y-direction.
         *
         * @return A new @ref Mat2 representing the non-uniform scale.
         */
        [[nodiscard]] static constexpr Mat2 makeScale(T scaleX, T scaleY) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Construct a 2D reflection matrix across coordinate axis.
         *
         * @tparam On The axis to reflect across. For more details @ref flcn::reflect for more details.
         *
         * @return A new @ref Mat2 representing the reflection across coordinate axis, or the origin.
         */
        template <reflect::RT On>
        [[nodiscard]] static constexpr Mat2 makeReflection() noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Construct a 2D shear matrix along the x-axis (horizontal axis).
         *
         * @param[in] shear The shear amount.
         *
         * @return A new @ref Mat2 representing the shear transform by the x-axis.
         */
        [[nodiscard]] static constexpr Mat2 makeShearX(T shear) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Construct a 2D shear matrix along the y-axis (vertical axis).
         *
         * @param[in] shear The shear amount.
         *
         * @return A new @ref Mat2 representing the shear transform by the y-axis.
         */
        [[nodiscard]] static constexpr Mat2 makeShearY(T shear) noexcept
            requires StrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup T_FALCON_Mat2x2_Constant
         * @{
         */

        // NOLINTBEGIN

        /**************************************
         *                                    *
         *             CONSTANTS              *
         *                                    *
         **************************************/

        /**
         * @brief A 2D matrix with ones on the main diagonal and zeros elsewhere.
         *
         * @note Constrained to @ref StrictArithmetic types.
         */
        static constexpr Mat2 identity()
            requires flcn::StrictArithmetic<T>
        { return Mat2{ T(1), T(0), T(0), T(1) }; }


        /**
         * @brief A 2D matrix with all zero elements.
         *
         * @note Constrained to @ref StrictArithmetic types.
         */
        static constexpr Mat2 zero()
            requires flcn::StrictArithmetic<T>
        { return Mat2{ T(0), T(0), T(0), T(0) }; }


        // NOLINTEND

        /** @} */


    private:
        std::array<CVec2<T>, COLUMNS> _data;
    };



    /**
     * @addtogroup FALCON_Mat2x2_Alias
     * @{
     */

    /*************************************
     *                                   *
     *             ALIASES               *
     *                                   *
     *************************************/

    using Mat2B   = Mat2<int8_t>;   ///< Signed Byte (8-bit) matrix
    using Mat2UB  = Mat2<uint8_t>;  ///< Unsigned Byte (8-bit) matrix
    using Mat2I   = Mat2<int32_t>;  ///< Signed Int (32-bit) matrix
    using Mat2U   = Mat2<uint32_t>; ///< Unsigned Int (32-bit) matrix
    using Mat2F   = Mat2<float>;    ///< Single Precision Floating Point (32-bit) matrix
    using Mat2LL  = Mat2<int64_t>;  ///< Signed Long Long (64-bit) matrix
    using Mat2D   = Mat2<double>;   ///< Double Precision Floating Point (64-bit) matrix
    using Mat2ULL = Mat2<uint64_t>; ///< Unsigned Long Long (64-bit) matrix

    /** @} */



    /**************************************
     *                                    *
     *        NON-MEMBER FUNCTIONS        *
     *                                    *
     **************************************/

    /**
     * @addtogroup FALCON_Mat2x2_Arithmetic
     * @{
     */

    /**
     * @brief Compute the element-wise product between @p matrix and @p scalar and return a new matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat2<T, S>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] scalar The value to scale by.
     * @param[in] matrix The matrix to scale.
     *
     * @return A new @ref Mat2 scaled by @p scalar.
     */
    template <StrictArithmetic T, StrictArithmetic S>
    [[nodiscard]] constexpr PromotedMat2<T, S> operator*(S scalar, const Mat2<T>& matrix) noexcept;

    /** @} */



    /**
     * @addtogroup FALCON_Mat2x2_Geom
     * @{
     */

    /**
     * @brief Transform the @p Vec **row vector** by @p matrix.
     *        \f$
     *            \begin{bmatrix}
     *                x & y
     *            \end{bmatrix}
     *            \cdot
     *            \begin{bmatrix}
     *                A_{00} & A_{01} \\
     *                A_{10} & A_{11}
     *            \end{bmatrix}
     *            =
     *            \begin{bmatrix}
     *                x' & y'
     *            \end{bmatrix}
     *        \f$
     *
     * @note Promotes the result to the wider type using @ref PromotedCVec2<T, U>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam T Numeric type of the row vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the transformation matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec    The row vector to transform.
     * @param[in] matrix The transformation matrix.
     *
     * @return The passed-in @p Vec with the transformations applied.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    static constexpr PromotedCVec2<T, U> operator*(const CVec2<T>& vec, const Mat2<U>& matrix) noexcept;


    /**
     * @brief Transform the @p Vec **row vector** by @p matrix.
     *        Perform the linear transformation:
     *        \f$
     *            \begin{bmatrix}
     *                x & y
     *            \end{bmatrix}
     *            \cdot
     *            \begin{bmatrix}
     *                A_{00} & A_{01} \\
     *                A_{10} & A_{11}
     *            \end{bmatrix}
     *            =
     *            \begin{bmatrix}
     *                x' & y'
     *            \end{bmatrix}
     *        \f$
     *
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam T Numeric type of the row vector. Must satisfy @ref StrictArithmetic.
     * @tparam U Numeric type of the transformation matrix. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] vec    The row vector to transform.
     * @param[in] matrix The transformation matrix.
     *
     * @return The passed-in @p Vec with the transformations applied.
     */
    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    static constexpr CVec2<T>& operator*=(CVec2<T>& vec, const Mat2<U>& matrix) noexcept;

    /** @} */



    /** @brief Template deduction guide for Mat2. */
    template <Arithmetic T, Arithmetic... Args>
        requires(std::is_same_v<T, Args> && ...) && (sizeof...(Args) == 4)
    Mat2(T, Args...) -> Mat2<T>;



} // namespace flcn


#include "Mat2.tpp"
