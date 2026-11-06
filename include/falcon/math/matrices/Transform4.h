#pragma once
/**
 * @file Transform4.h
 * @author Alan Abraham P Kochumon
 * @date Created on: July 30, 2026
 *
 * @brief Specialization of @ref Mat4 used for 3D transformations with the inherent assumption that
 *        Row 4 is <0, 0, 0, 1>.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4.h"
#include "falcon/math/vectors/Point3.h"


namespace flcn
{
    template <StrictArithmetic T>
    struct Transform4: Mat4<T>
    {

        /**
         * @addtogroup FALCON_Transform4_Members
         * @{
         */
        using value_type = T; ///< The numeric type of the transform elements.

        static constexpr std::size_t COLUMNS = 4; ///< Matrix column count.
        static constexpr std::size_t ROWS    = 3; ///< Matrix row count (This is a pseudo-row count).

        /** @} */


        /**
         * @addtogroup FALCON_Transform4_Init
         * @{
         */

        /**
         * @brief Initialize a @ref Transform4 instance with uninitialized(garbage) values.
         *
         * @warning The components are left uninitialized (containing garbage data)
         *          to maximize SIMD optimization and maintain triviality.
         *
         * @note Use value-initialization (`{}`) to guarantee a zeroed matrix.
         */
        Transform4() = default;


        /**
         * @brief Initialize a 4D transformation matrix from the passed-in scalar elements.
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
         *
         */
        [[nodiscard]] constexpr Transform4(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21, T m22,
                                           T m23) noexcept;


        /**
         * @brief Initialize a 4D transformation matrix from the passed-in axis and a point of origin.
         *
         * @param[in] firstAxis  The 3D-vector to use as the first orthogonal axis.
         * @param[in] secondAxis The 3D-vector to use as the second orthogonal axis.
         * @param[in] thirdAxis  The 3D-vector to use as the third orthogonal axis.
         * @param[in] origin     The origin point.
         */
        [[nodiscard]] constexpr Transform4(const Vec3<T>& firstAxis, const Vec3<T>& secondAxis,
                                           const Vec3<T>& thirdAxis, const Point3<T>& origin) noexcept;

        /**
         * @brief Initialize @ref Transform4 from another @ref Transform4 of a different type.
         *
         * @tparam U Numeric type of the source transform matrix.
         *
         * @param[in] other The source transform matrix to be converted.
         */
        template <StrictArithmetic U>
        [[nodiscard]] explicit constexpr Transform4(const Transform4<U>& other) noexcept;

        /** @} */



        /**
         * @addtogroup FALCON_Transform4_Access
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
        [[nodiscard]] constexpr auto operator[](std::size_t col) const noexcept;


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



        /**
         * @brief Get the translation vector of this transformation matrix.
         * @return A Point3 representing the translation vector.
         */
        [[nodiscard]] constexpr auto getTranslation() const noexcept;


        /**
         * @brief Set the translation vector of this transformation matrix.
         * @param translation The translation vector/point.
         */
        constexpr void setTranslation(const Point3<T>& translation) noexcept;

        /** @} */



        /**
         * @addtogroup FALCON_Mat4x4_Geom
         * @{
         */

        /**
         * @brief Transform the @p Vec **column vector** by this matrix.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} & A_{03} \\
         *                 A_{10} & A_{11} & A_{12} & A_{13} \\
         *                 A_{20} & A_{21} & A_{22} & A_{23} \\
         *                      0 &      0 &      0 &      1
         *            \end{bmatrix}
         *            \cdot
         *            \begin{bmatrix}
         *                  x \\ y \\ z \\ 0 (implied)
         *            \end{bmatrix}
         *            =
         *            \begin{bmatrix}
         *                  x' \\ y' \\ z' \\ 0 (implied)
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


        /**
         * @brief Transform the @p point by this matrix.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} & A_{03} \\
         *                 A_{10} & A_{11} & A_{12} & A_{13} \\
         *                 A_{20} & A_{21} & A_{22} & A_{23} \\
         *                      0 &      0 &      0 &      1
         *            \end{bmatrix}
         *            \cdot
         *            \begin{bmatrix}
         *                  x \\ y \\ z \\ 1 (implied)
         *            \end{bmatrix}
         *            =
         *            \begin{bmatrix}
         *                  x' \\ y' \\ z' \\ 1 (implied)
         *            \end{bmatrix}
         *        \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedPoint3<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the point. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] point The point to transform.
         *
         * @return A new @ref Point3 with applied linear transformations.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedPoint3<T, U> operator*(const Point3<U>& point) const noexcept
            requires StrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FALCON_Transform4_Comp
         * @{
         */

        /**
         * @brief Compose this transformation matrix with @p rhs matrix to form a new transformation matrix.
         *
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} & A_{03} \\
         *                 A_{10} & A_{11} & A_{12} & A_{13} \\
         *                 A_{20} & A_{21} & A_{22} & A_{23} \\
         *                      0 &      0 &      0 &      1
         *            \end{bmatrix}
         *            \cdot
         *            \begin{bmatrix}
         *                 B_{00} & B_{01} & B_{02} & B_{03} \\
         *                 B_{10} & B_{11} & B_{12} & B_{13} \\
         *                 B_{20} & B_{21} & B_{22} & B_{23} \\
         *                      0 &      0 &      0 &      1
         *            \end{bmatrix}
         *            =
         *            \begin{bmatrix}
         *                 C_{00} & C_{01} & C_{02} & C_{03} \\
         *                 C_{10} & C_{11} & C_{12} & C_{13} \\
         *                 C_{20} & C_{21} & C_{22} & C_{23} \\
         *                      0 &      0 &      0 &      1
         *            \end{bmatrix}
         *        \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedTransform4<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS matrix. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The matrix to multiply.
         *
         * @return A new @ref Transform4 containing the composition of linear transformations.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedTransform4<T, U> operator*(const Transform4<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compose this transformation matrix with @p rhs matrix in-place.
         *
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} & A_{03} \\
         *                 A_{10} & A_{11} & A_{12} & A_{13} \\
         *                 A_{20} & A_{21} & A_{22} & A_{23} \\
         *                      0 &      0 &      0 &      1
         *            \end{bmatrix}
         *            \cdot
         *            \begin{bmatrix}
         *                 B_{00} & B_{01} & B_{02} & B_{03} \\
         *                 B_{10} & B_{11} & B_{12} & B_{13} \\
         *                 B_{20} & B_{21} & B_{22} & B_{23} \\
         *                      0 &      0 &      0 &      1
         *            \end{bmatrix}
         *            =
         *            \begin{bmatrix}
         *                 C_{00} & C_{01} & C_{02} & C_{03} \\
         *                 C_{10} & C_{11} & C_{12} & C_{13} \\
         *                 C_{20} & C_{21} & C_{22} & C_{23} \\
         *                      0 &      0 &      0 &      1
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
        constexpr Transform4& operator*=(const Transform4<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /** @} */



        /**
         * @addtogroup FALCON_Transform4_Geom
         * @{
         */

        /**
         * @brief Compute the inverse of this transform.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} & A_{03} \\
         *                 A_{10} & A_{11} & A_{12} & A_{13} \\
         *                 A_{20} & A_{21} & A_{22} & A_{23} \\
         *                 A_{30} & A_{31} & A_{32} & A_{33}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{det(A)}
         *            \begin{bmatrix}
         *                     C_{00} & C_{10} & C_{20} & C_{30} \\
         *                     C_{01} & C_{11} & C_{21} & C_{31} \\
         *                     C_{02} & C_{12} & C_{22} & C_{32} \\
         *                     C_{03} & C_{13} & C_{23} & C_{33}
         *            \end{bmatrix}
         *            \\
         *            \begin{text}
         *                where C_{ij} = [\text{adj}(A)]_{ij} = (-1)^{i+j} \det(M_{ji})
         *            \end{text}
         *        \f$
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Performs assertion for division by zero (singular transform) in **Debug mode**.
         *
         * @return A new @ref Transform4 such that \f$ A \cdot A^{-1} = I \f$.
         */
        [[nodiscard("Inverse does not mutate the transform. Discarding the result will not produce any change.")]]
        constexpr Transform4<Magnitude<T>> inverse() const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the inverse of a transform.
         *        \f$
         *            \begin{bmatrix}
         *                 A_{00} & A_{01} & A_{02} & A_{03} \\
         *                 A_{10} & A_{11} & A_{12} & A_{13} \\
         *                 A_{20} & A_{21} & A_{22} & A_{23} \\
         *                 A_{30} & A_{31} & A_{32} & A_{33}
         *            \end{bmatrix}^{-1}
         *            =
         *            \frac{1}{det(A)}
         *            \begin{bmatrix}
         *                     C_{00} & C_{10} & C_{20} & C_{30} \\
         *                     C_{01} & C_{11} & C_{21} & C_{31} \\
         *                     C_{02} & C_{12} & C_{22} & C_{32} \\
         *                     C_{03} & C_{13} & C_{23} & C_{33}
         *            \end{bmatrix}
         *            \\
         *            \begin{text}
         *                where C_{ij} = [\text{adj}(A)]_{ij} = (-1)^{i+j} \det(M_{ji})
         *            \end{text}
         *        \f$
         *
         * @note Promotes the result to a floating point result using @ref Magnitude.
         * @note Operation is restricted to **signed** numeric types via @ref SignedStrictArithmetic.
         * @note Performs assertion for division by zero (singular transform) in **Debug mode**.
         *
         * @param[in] transform The transform to invert.
         *
         * @return A new @ref Transform4 such that \f$ A \cdot A^{-1} = I \f$.
         */
        [[nodiscard("Inverse does not mutate the transform. Discarding the result will not produce any change.")]]
        static constexpr Transform4<Magnitude<T>> inverse(const Transform4& transform) noexcept
            requires SignedStrictArithmetic<T>;

        /** @} */
    };


    /** @brief Template deduction guide for Transform4. */
    template <StrictArithmetic T, StrictArithmetic... Args>
        requires(std::is_same_v<T, Args> && ...) && (sizeof...(Args) == 11)
    Transform4(T, Args...) -> Transform4<T>;

    template <StrictArithmetic T>
    Transform4(Vec3<T>, Vec3<T>, Vec3<T>, Point3<T>) -> Transform4<T>;

} // namespace flcn


#include "Transform4.tpp"
