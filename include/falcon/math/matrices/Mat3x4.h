#pragma once
/**
 * @file Mat3x4.h
 * @author Alan Abraham P Kochumon
 * @date Created on: July 20, 2026
 *
 * @brief Templated 3x4 Matrix supporting integral, floating-point, and boolean types.
 *
 * @details Provide high-performance 3x4 matrix implementation with SIMD acceleration
 *          and support for element-wise operations.
 *
 * @note Arithmetic operations are limited to numeric types via `StrictArithmetic` concept.
 * @note Matrices utilize a strict column-major internal memory layout. To align with standard mathematical notations,
 *       scalar constructors accept elements in row-major reading order. Vector-based constructors and array-style
 *       access (operator[]) operate directly on columns.
 *
 * @par Configuration
 *      Define `FORCE_SCALAR` to turn off SIMD which is on by default on supported hardware.
 *      Define `FALCON_LEFT_HANDED` to configure library to use left-handed coordinated system.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "falcon/math/common/Types.h"
#include "falcon/math/vectors/Vec3.h"

#include <array>
#include <type_traits>


namespace flcn
{
    template <Arithmetic T>
    struct Mat3x4
    {

        /**
         * @addtogroup FALCON_Mat3x4_Members
         * @{
         */

        using value_type = T; ///< The numeric type of the matrix elements.

        static constexpr std::size_t COLUMNS = 4; ///< Matrix column count.
        static constexpr std::size_t ROWS    = 3; ///< Matrix row count.


        /** @} */



        /**
         * @addtogroup FALCON_Mat3x4_Init
         * @{
         */

        /**
         * @brief Initialize an uninitialized @ref Mat3x4 instance.
         *
         * @warning The components are left uninitialized (containing garbage data)
         *          to maximize SIMD optimization and maintain triviality.
         *
         * @note Use value-initialization (`{}`) or the static helper
         *       @ref flcn::Mat3x4<T>::zero() to guarantee a zeroed matrix.
         */
        Mat3x4() = default;


        /**
         * @brief Initialize a 3x4 matrix from the passed-in scalar elements.
         *
         * @param[in] m00 The element to insert into row one, column one.
         * @param[in] m01 The element to insert into row one, column two.
         * @param[in] m02 The element to insert into row one, column three.
         * @param[in] m03 The element to insert into row one, column four.
         * @param[in] m10 The element to insert into row two, column one.
         * @param[in] m11 The element to insert into row two, column two.
         * @param[in] m12 The element to insert into row two, column three.
         * @param[in] m13 The element to insert into row two, column four.
         * @param[in] m20 The element to insert into row three, column one.
         * @param[in] m21 The element to insert into row three, column two.
         * @param[in] m22 The element to insert into row three, column three.
         * @param[in] m23 The element to insert into row three, column four.
         */
        [[nodiscard]] constexpr Mat3x4(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21, T m22,
                                       T m23) noexcept;


        /**
         * @brief Initialize a 3x4 matrix from the passed-in vectors as columns.
         *
         * @param[in] col0 The 3D vector to use as the first column entry.
         * @param[in] col1 The 3D vector to use as the second column entry.
         * @param[in] col2 The 3D vector to use as the third column entry.
         * @param[in] col3 The 3D vector to use as the fourth column entry.
         */
        [[nodiscard]] constexpr Mat3x4(const Vec3<T>& col0, const Vec3<T>& col1, const Vec3<T>& col2,
                                       const Vec3<T>& col3) noexcept;



        /**
         * @brief Initialize @ref Mat3x4 from another @ref Mat3x4 of a different type.
         *
         * @tparam U Numeric type of the source matrix.
         *
         * @param[in] other The source matrix to be converted.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] explicit constexpr Mat3x4(const Mat3x4<U>& other) noexcept;

        /** @} */



        /**
         * @addtogroup FALCON_Mat3x4_Access
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
         * @addtogroup FALCON_Mat3x4_Equality
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
        [[nodiscard]] constexpr bool allEq(const Mat3x4<U>& rhs,
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
        [[nodiscard]] static constexpr bool allEq(const Mat3x4& lhs, const Mat3x4<U>& rhs,
                                                  double epsilon = std::is_same_v<T, double> ||
                                                          std::is_same_v<U, double>
                                                      ? Config::DOUBLE_EPSILON
                                                      : Config::FLOAT_EPSILON) noexcept;


        /**
         * @brief Compare all elements of this matrix for equality with another matrix.
         *        Perform an element-wise comparison and returns true if any corresponding elements differ by
         more
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
        [[nodiscard]] constexpr bool anyNeq(const Mat3x4<U>& rhs,
                                            double epsilon = std::is_same_v<T, double> || std::is_same_v<U, double>
                                                ? Config::DOUBLE_EPSILON
                                                : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @brief Compare all elements of this matrix for equality with another matrix.
         *        Perform an element-wise comparison and returns true if any corresponding elements differ by
         more
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
        [[nodiscard]] static constexpr bool anyNeq(const Mat3x4& lhs, const Mat3x4<U>& rhs,
                                                   double epsilon = std::is_same_v<T, double> ||
                                                           std::is_same_v<U, double>
                                                       ? Config::DOUBLE_EPSILON
                                                       : Config::FLOAT_EPSILON) noexcept;


        /**
         * @copybrief allEq(const Mat3x4<U>&, double) const noexcept
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
        [[nodiscard]] constexpr bool operator==(const Mat3x4<U>& rhs) const noexcept;


        /**
         * @copybrief anyNeq(const Mat3x4<U>&, double) const noexcept
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
        [[nodiscard]] constexpr bool operator!=(const Mat3x4<U>& rhs) const noexcept;

        /** @} */



        /**
         * @addtogroup FALCON_Mat3x4_Arithmetic
         * @{
         */

        /**
         * @brief Compute the element-wise sum of this matrix with @p rhs matrix and return a new matrix.
         *
         * @note Promotes the result to the wider type using @ref PromotedMat3x4<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The matrix to add.
         *
         * @return A new @ref Mat3x4 containing the element-wise sum.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedMat3x4<T, U> operator+(const Mat3x4<U>& rhs) const noexcept
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
        Mat3x4& operator+=(const Mat3x4<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise difference between this matrix and @p rhs matrix
         *        and return a new matrix.
         *
         * @note Promotes the result to the wider type using @ref PromotedMat3x4<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The matrix to subtract.
         *
         * @return A new @ref Mat3x4 containing the element-wise difference.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedMat3x4<T, U> operator-(const Mat3x4<U>& rhs) const noexcept
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
        constexpr Mat3x4& operator-=(const Mat3x4<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise product between this matrix and @p scalar and return a new matrix.
         *
         * @note Promotes the result to the wider type using @ref PromotedMat3x4<T, S>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A new @ref Mat3x4 scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedMat3x4<T, S> operator*(S scalar) const noexcept
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
        constexpr Mat3x4& operator*=(S scalar) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise division of this matrix by @p scalar and return a new matrix.
         *
         * @note Promotes the result to the wider type using @ref PromotedMat3x4<T, S>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Performs assertion for division by zero in **Debug mode**.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A new @ref Mat3x4 inverse scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedMat3x4<T, S> operator/(S scalar) const noexcept
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
        constexpr Mat3x4& operator/=(S scalar) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise division of this matrix by @p scalar and return a new matrix.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this matrix contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to the wider type using @ref PromotedMat3x4<T, S>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Returns @p fallback if attempting to divide by zero (or below the epsilon threshold), or if any
         *       operand contains NaN.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar   The value to divide the matrix elements by.
         * @param[in] fallback The default matrix to return, when an invalid case is hit like a zero scalar
         *                     or a NaN element.
         *
         * @return A new @ref Mat3x4 resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has a NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedMat3x4<T, S> safeDiv(S scalar, Mat3x4 fallback = Mat3x4::zero()) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise division of @p mat by @p scalar and return a new matrix.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this matrix contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to the wider type using @ref PromotedMat3x4<T, S>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Returns @p fallback if attempting to divide by zero (or below the epsilon threshold), or if any
         *       operand contains NaN.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] mat      The matrix to divide.
         * @param[in] scalar   The value to divide the matrix elements by.
         * @param[in] fallback The default matrix to return, when an invalid case is hit like a zero scalar
         *                     or a NaN element.
         *
         * @return A new @ref Mat3x4 resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has a NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] static constexpr PromotedMat3x4<T, S> safeDiv(const Mat3x4& mat, S scalar,
                                                                    Mat3x4 fallback = Mat3x4::zero()) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise division of this matrix by @p scalar, return a new matrix,
         *        and updates @p status to reflect the result of the operation.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this vector contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to the wider type using @ref PromotedMat3x4<T, S>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Returns @ref fallback if attempting to divide by zero (or below the epsilon threshold), or if any
         *       operand contains NaN.
         * @note In the event of multiple failure conditions, data corruption (NaN) takes precedence over
         mathematical
         *       invalidity (Division by Zero) when reporting status.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar   The value to divide the matrix elements by.
         * @param[out] status  The status flag to store the status of the current operation result.
         *                     For details on status codes see @ref OperationStatus.
         * @param[in] fallback The default matrix to return, when an invalid case is hit like a zero scalar
         *                     or a NaN element.
         *
         * @return A new @ref Mat3x4 resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedMat3x4<T, S> tryDiv(S scalar, OperationStatus& status,
                                                            Mat3x4 fallback = Mat3x4::zero()) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the element-wise division of @p Vec by @p scalar, return a new matrix,
         *        and updates @p status to reflect the result of the operation.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this matrix contains NaN elements,
         *       returns @p fallback.
         * @note Promotes the result to the wider type using @ref PromotedMat3x4<T, S>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Returns @ref fallback if attempting to divide by zero (or below the epsilon threshold), or if any
         *       operand contains NaN.
         * @note In the event of multiple failure conditions, data corruption (NaN) takes precedence over
         mathematical
         *       invalidity (Division by Zero) when reporting status.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] mat      The matrix to divide.
         * @param[in] scalar   The value to divide the matrix elements by.
         * @param[out] status  The status flag to store the status of the current operation result.
         *                     For details on status codes see @ref OperationStatus.
         * @param[in] fallback The default matrix to return, when an invalid case is hit like a zero scalar
         *                     or a NaN element.
         *
         * @return A new @ref Mat3x4 resulting from the division or @p fallback if the @p scalar is below the
         *         epsilon threshold or if the matrix has NaN(Not-a-Number) element(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] static constexpr PromotedMat3x4<T, S> tryDiv(const Mat3x4& mat, S scalar, OperationStatus& status,
                                                                   Mat3x4 fallback = Mat3x4::zero()) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Negate each element of this matrix and return a new @ref Mat3x4<T>.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @return A new @ref flcn::Mat3x4 with negated elements.
         */
        [[nodiscard]] constexpr Mat3x4 operator-() const noexcept
            requires SignedStrictArithmetic<T>;

        /** @} */


        /**
         * @addtogroup FALCON_Mat3x2_Algebra
         * @{
         */

        /**
         * @brief Transpose this matrix by swapping its rows and columns.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} & A_{03} \\
         *                 A_{10} & A_{11} & A_{12} & A_{13} \\
         *                 A_{20} & A_{21} & A_{22} & A_{23}
         *            \end{bmatrix} ^ \top
         *            =
         *            \begin{bmatrix}
         *                 A_{00} & A_{10} & A_{20} \\
         *                 A_{01} & A_{11} & A_{21} \\
         *                 A_{02} & A_{12} & A_{22} \\
         *                 A_{03} & A_{13} & A_{23}
         *            \end{bmatrix}
         *        \f$
         *
         * @return A new @ref Mat4x3 with its elements flipped along the diagonal.
         */
        [[nodiscard("Transpose does not mutate the matrix. Discarding the result will not produce any change.")]]
        constexpr Mat4x3<T> transpose() const noexcept;


        /**
         * @brief Transpose @p matrix by swapping its rows and columns.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} & A_{03} \\
         *                 A_{10} & A_{11} & A_{12} & A_{13} \\
         *                 A_{20} & A_{21} & A_{22} & A_{23}
         *            \end{bmatrix} ^ \top
         *            =
         *            \begin{bmatrix}
         *                 A_{00} & A_{10} & A_{20} \\
         *                 A_{01} & A_{11} & A_{21} \\
         *                 A_{02} & A_{12} & A_{22} \\
         *                 A_{03} & A_{13} & A_{23}
         *            \end{bmatrix}
         *        \f$
         *
         * @param matrix The matrix to transpose.
         *
         * @return A new @ref Mat4x3 with its elements flipped along the diagonal.
         */
        [[nodiscard("Transpose does not mutate the matrix. Discarding the result will not produce any change.")]]
        static constexpr Mat4x3<T> transpose(const Mat3x4& matrix) noexcept;

        /** @} */



        /**
         * @addtogroup FALCON_Mat3x4_Utils
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
        [[nodiscard]] static constexpr bool hasInf(const Mat3x4& matrix) noexcept;


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
        [[nodiscard]] static constexpr bool hasNaN(const Mat3x4& matrix) noexcept;

        /** @} */


        /**
         * @addtogroup T_FALCON_Mat3x4_Constant
         * @{
         */

        /**************************************
         *                                    *
         *             CONSTANTS              *
         *                                    *
         **************************************/

        /**
         * @brief A 3x4 matrix with all elements being one.
         *
         * @note Constrained to @ref StrictArithmetic types.
         */
        static constexpr Mat3x4 one()
            requires flcn::StrictArithmetic<T>
        { return Mat3x4{ T(1), T(1), T(1), T(1), T(1), T(1), T(1), T(1), T(1), T(1), T(1), T(1) }; }


        /**
         * @brief A 3x4 matrix with all elements being zero.
         *
         * @note Constrained to @ref StrictArithmetic types.
         */
        static constexpr Mat3x4 zero()
            requires flcn::StrictArithmetic<T>
        { return Mat3x4{ T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0) }; }

        /** @} */



        /**
         * @addtogroup FALCON_Mat3x4_Log
         * @{
         */

        /**
         * @brief Write the matrix to an output stream in **row-major** order.
         *        Format the matrix as
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{10} & A_{20} & A_{30} \\
         *                 A_{01} & A_{11} & A_{21} & A_{31} \\
         *                 A_{02} & A_{12} & A_{22} & A_{32}
         *            \end{bmatrix}
         *        \f$ string representation for debugging or logging.
         *
         * @param os     The output stream to write to.
         * @param matrix The matrix to be streamed.
         *
         * @return A reference to the output stream @p os.
         */
        friend std::ostream& operator<<(std::ostream& os, const Mat3x4& matrix)
        {
            const std::streamsize oldPrecision     = os.precision();
            const std::ios_base::fmtflags oldFlags = os.flags();

            auto precision = Config::useFullPrecision
                ? std::is_same_v<T, double> ? Config::DOUBLE_PRECISION : Config::FLOAT_PRECISION
                : Config::LOG_PRECISION;
            os << std::setprecision(precision) << std::fixed;
            os << "|" << matrix._data[0][0] << " " << matrix._data[1][0] << " " << matrix._data[2][0] << " "
               << matrix._data[3][0] << "|\n";
            os << "|" << matrix._data[0][1] << " " << matrix._data[1][1] << " " << matrix._data[2][1] << " "
               << matrix._data[3][1] << "|\n";
            os << "|" << matrix._data[0][2] << " " << matrix._data[1][2] << " " << matrix._data[2][2] << " "
               << matrix._data[3][2] << "|\n";

            os.precision(oldPrecision);
            os.flags(oldFlags);

            return os;
        }

        /** @} */


    private:
        std::array<Vec3<T>, COLUMNS> _data;
    };



    /**
     * @addtogroup FALCON_Mat3x4_Alias
     * @{
     */

    /*************************************
     *                                   *
     *             ALIASES               *
     *                                   *
     *************************************/

    using Mat3x4B   = Mat3x4<int8_t>;   ///< Signed Byte (8-bit) matrix
    using Mat3x4UB  = Mat3x4<uint8_t>;  ///< Unsigned Byte (8-bit) matrix
    using Mat3x4I   = Mat3x4<int32_t>;  ///< Signed Int (32-bit) matrix
    using Mat3x4U   = Mat3x4<uint32_t>; ///< Unsigned Int (32-bit) matrix
    using Mat3x4F   = Mat3x4<float>;    ///< Single Precision Floating Point (32-bit) matrix
    using Mat3x4LL  = Mat3x4<int64_t>;  ///< Signed Long Long (64-bit) matrix
    using Mat3x4D   = Mat3x4<double>;   ///< Double Precision Floating Point (64-bit) matrix
    using Mat3x4ULL = Mat3x4<uint64_t>; ///< Unsigned Long Long (64-bit) matrix

    /** @} */



    /**
     * @brief Compute the element-wise product between @p scalar and @p matrix and return a new matrix.
     *
     * @note Promotes the result to the wider type using @ref PromotedMat3x4<T, S>.
     *
     * @tparam T Numeric type of the matrix. Must satisfy @ref StrictArithmetic.
     * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] scalar The value to scale by.
     * @param[in] matrix The matrix to scale.
     *
     * @return A new @ref Mat3x4 scaled by @p scalar.
     */
    template <StrictArithmetic T, StrictArithmetic S>
    [[nodiscard]] static constexpr PromotedMat3x4<T, S> operator*(S scalar, const Mat3x4<T>& matrix) noexcept
        requires StrictArithmetic<T>;


    /** @brief Template deduction guide for Mat3x4. */
    template <Arithmetic T, Arithmetic... Args>
        requires(std::is_same_v<T, Args> && ...) && (sizeof...(Args) == 11)
    Mat3x4(T, Args...) -> Mat3x4<T>;

} // namespace flcn


#include "Mat3x4.tpp"
