#pragma once
/**
 * @file Quaternion.h
 * @author Alan Abraham P Kochumon
 * @date Created on: August 01, 2026
 *
 * @brief Templated Quaternion supporting integral, floating-point, and boolean types.
 *
 * @details Provides high-performance 4D quaternion implementation with SIMD acceleration
 *          and support for component-wise operations. ::TODO::
 *
 * @tparam T Type of @ref Quaternion components. Must satisfy @ref Arithmetic.
 *
 * @note Arithmetic operations are restricted to numeric types via @ref StrictArithmetic.
 *
 * @par Configuration ::TODO::Update
 * - Define `ENABLE_FALCON_SHADER_OPERATORS` to enable comparison operators (`,`, `<`, etc.).
 *   Even if disabled, functional comparisons like @ref gt remain available.
 * - Define `FORCE_SCALAR` to disable SIMD optimizations (enabled by default on supported hardware).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "Quaternion.h"
#include "common/MathTraits.h"
#include "vectors/Vec3.h"

#include <array>


namespace flcn
{

    /**
     * @brief Quaternion data structure.
     *
     * @note While a quaternion can be initialized in any order <vector, scalar> or <scalar, vector>,
     *       it strictly follows the <vector, scalar> or <x, y, z, w> order internally.
     *
     * @tparam T The numeric type of the real and complex components. Must satisfy @ref Arithmetic.
     *
     */
    template <Arithmetic T>
    struct Quaternion
    {

        using value_type = T; /// The numeric type of member variables.


        /**
         * @addtogroup FALCON_Quaternion_Init
         * @{
         */

        /**
         * @brief Initialize an uninitialized @ref Quaternion instance.
         *
         * @warning The components are left uninitialized (containing garbage data)
         *          to maximize SIMD optimization and maintain triviality.
         *
         * @note Use value-initialization (`{}`) to guarantee a zeroed quaternion.
         */
        Quaternion() = default;


        /**
         * @brief Initialize @ref Quaternion with passed-in values.
         *
         * @param[in] x The first vector component.
         * @param[in] y The second vector component.
         * @param[in] z The third vector component.
         * @param[in] w The scalar component.
         */
        [[nodiscard]] constexpr Quaternion(T x, T y, T z, T w) noexcept;


        /**
         * @brief Initialize @ref Quaternion with a complex and real component.
         *
         * @param[in] complex The complex/vector component.
         * @param[in] real The real/scalar component.
         */
        [[nodiscard]] constexpr Quaternion(const Vec3<T>& complex, T real) noexcept;


        /**
         * @brief Initialize @ref Quaternion with a real and complex component.
         *
         * @param[in] complex The complex/vector component.
         * @param[in] real The real/scalar component.
         */
        [[nodiscard]] constexpr Quaternion(T real, const Vec3<T>& complex) noexcept;


        /**
         * @brief Initialize @ref Quaternion from another @ref Quaternion of a different type.
         *
         * @tparam U Numeric type of the source quaternion.
         *
         * @param[in] other The source quaternion to be converted.
         */
        template <Arithmetic U>
        [[nodiscard]] explicit constexpr Quaternion(const Quaternion<U>& other) noexcept;

        /** @} */



        /**
         * @addtogroup FALCON_Quaternion_Access
         * @{
         */

        /**
         * @brief Get the first vector component.
         */
        [[nodiscard]] constexpr T x() const noexcept;


        /**
         * @brief Get a reference to the first vector component.
         */
        [[nodiscard]] constexpr T& x() noexcept;


        /**
         * @brief Get the second vector component.
         */
        [[nodiscard]] constexpr T y() const noexcept;


        /**
         * @brief Get a reference to the second vector component.
         */
        [[nodiscard]] constexpr T& y() noexcept;


        /**
         * @brief Get the third vector component.
         */
        [[nodiscard]] constexpr T z() const noexcept;


        /**
         * @brief Get a reference to the third vector component.
         */
        [[nodiscard]] constexpr T& z() noexcept;


        /**
         * @brief Get the scalar component (last component).
         */
        [[nodiscard]] constexpr T w() const noexcept;


        /**
         * @brief Get a reference to the scalar component (last component).
         */
        [[nodiscard]] constexpr T& w() noexcept;


        /**
         * @brief Get the first vector component.
         */
        [[nodiscard]] constexpr T i() const noexcept;


        /**
         * @brief Get a reference to the first vector component.
         */
        [[nodiscard]] constexpr T& i() noexcept;


        /**
         * @brief Get the second vector component.
         */
        [[nodiscard]] constexpr T j() const noexcept;


        /**
         * @brief Get a reference to the second vector component.
         */
        [[nodiscard]] constexpr T& j() noexcept;


        /**
         * @brief Get the third vector component.
         */
        [[nodiscard]] constexpr T k() const noexcept;


        /**
         * @brief Get a reference to the third vector component.
         */
        [[nodiscard]] constexpr T& k() noexcept;


        /**
         * @brief Get the scalar component (last component).
         */
        [[nodiscard]] constexpr T s() const noexcept;


        /**
         * @brief Get a reference to the scalar component (last component).
         */
        [[nodiscard]] constexpr T& s() noexcept;


        /**
         * @brief Get the vector/complex part of this quaternion.
         *
         * @return A *new* 3D Vector containing the complex part (i, j, k) of the quaternion.
         */
        [[nodiscard]] constexpr Vec3<T> getVectorPart() const noexcept;


        /**
         * @brief Get the scalar part of this quaternion.
         */
        [[nodiscard]] constexpr T getScalarPart() const noexcept;

        /** @} */


        /**
         * @addtogroup FALCON_Quaternion_Arithmetic
         * @{
         */

        /**
         * @brief Compute the component-wise sum of two quaternions.
         *
         * @tparam U The numeric type of RHS quaternion. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The quaternion to add.
         *
         * @return A new @ref Quaternion with the component-wise sum.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        constexpr PromotedQuaternion<T, U> operator+(const Quaternion<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise sum of two quaternions in-place.
         *
         * @tparam U The numeric type of RHS quaternion. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The quaternion to add.
         *
         * @return A reference to this quaternion (*this).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        constexpr Quaternion& operator+=(const Quaternion<U>& rhs) noexcept
            requires StrictArithmetic<T>;

        /**
         * @brief Compute the component-wise difference between two quaternions.
         *
         * @tparam U The numeric type of RHS quaternion. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The quaternion to subtract.
         *
         * @return A new @ref Quaternion with the component-wise difference.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        constexpr PromotedQuaternion<T, U> operator-(const Quaternion<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise difference between two quaternions in-place.
         *
         * @tparam U The numeric type of RHS quaternion. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The quaternion to subtract.
         *
         * @return A reference to this quaternion (*this).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        constexpr Quaternion& operator-=(const Quaternion<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise product of this quaternion with @p scalar.
         *
         * @tparam S The numeric type of RHS quaternion. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The scalar to multiply.
         *
         * @return A new @ref Quaternion scaled by @p scalar.
         */
        template <StrictArithmetic S>
            requires StrictSignedness<T, S>
        constexpr PromotedQuaternion<T, S> operator*(S scalar) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise product of this quaternion with @p scalar in-place.
         *
         * @tparam S The numeric type of RHS quaternion. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The scalar to multiply.
         *
         * @return A reference to this quaternion (*this).
         */
        template <StrictArithmetic S>
            requires StrictSignedness<T, S>
        constexpr Quaternion& operator*=(S scalar) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Divide this quaternion by @p scalar component-wise.
         *
         * @note Checks for division by zero and presence of NaN components in *Debug Mode*.
         *
         * @tparam S The numeric type of RHS quaternion. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The scalar to divide by.
         *
         * @return A new @ref Quaternion inverse-scaled by @p scalar.
         */
        template <StrictArithmetic S>
            requires StrictSignedness<T, S>
        constexpr PromotedQuaternion<T, S> operator/(S scalar) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Divide this quaternion by @p scalar component-wise in-place.
         *
         * @note Checks for division by zero and presence of NaN components in *Debug Mode*.
         *
         * @tparam S The numeric type of RHS quaternion. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The scalar to divide by.
         *
         * @return A reference to this quaternion (*this).
         */
        template <StrictArithmetic S>
            requires StrictSignedness<T, S>
        constexpr Quaternion& operator/=(S scalar) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Negate each component of this quaternion and return a new @ref Quaternion<T>.
         *
         * @note Operation is restricted to numeric types via @ref SignedStrictArithmetic.
         *
         * @return A new @ref flcn::Quaternion with negated components.
         */
        [[nodiscard]] constexpr Quaternion operator-() const noexcept
            requires SignedStrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FALCON_Quaternion_Equality
         * @{
         */

        /**
         * @brief Compare all components of this quaternion with @p rhs quaternion for equality.
         *        Perform a component-wise comparison and returns true only if every element pair
         *        satisfies the equality condition within the given @p epsilon.
         *
         * @note To obtain a component-wise boolean mask, use @ref eq.
         *
         * @tparam U Numeric type of the RHS quaternion. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs     The quaternion to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if all components are equivalent within @p epsilon.
         *
         * @relatedalso vecEq()
         * @relatedalso eq()
         * @relatedalso anyNeq()
         * @relatedalso neq()
         * @relatedalso vecNeq()
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr bool allEq(const Quaternion<U>& rhs,
                                           double epsilon = Config::EPSILON<std::common_type_t<T, U>>) const noexcept;


        /**
         * @brief Compare all components of @p lhs quaternion with @p rhs quaternion for equality.
         *        Perform a component-wise comparison and returns `true` only if every element pair
         *        satisfies the equality condition within the given @p epsilon.
         *
         * @note To obtain a component-wise boolean mask, use @ref eq.
         *
         * @tparam U Numeric type of the RHS quaternion. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The quaternion to compare.
         * @param[in] rhs     The quaternion to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if all components are equivalent within @p epsilon.
         *
         * @relatedalso vecEq()
         * @relatedalso eq()
         * @relatedalso anyNeq()
         * @relatedalso neq()
         * @relatedalso vecNeq()
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr bool allEq(const Quaternion& lhs, const Quaternion<U>& rhs,
                                                  double epsilon = Config::EPSILON<std::common_type_t<T, U>>) noexcept;


        /**
         * @brief Compare all components of this quaternion with @p rhs quaternion for inequality.
         *        Perform a component-wise comparison and returns `true` if any corresponding elements differ by more
         *        than @p epsilon.
         *
         * @note To obtain a component-wise boolean mask, use @ref neq.
         *
         * @tparam U Numeric type of the RHS quaternion. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs     The quaternion to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if any of the components are not equivalent within @p epsilon.
         *
         * @relatedalso allEq()
         * @relatedalso vecEq()
         * @relatedalso eq()
         * @relatedalso neq()
         * @relatedalso vecNeq()
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr bool anyNeq(const Quaternion<U>& rhs,
                                            double epsilon = Config::EPSILON<std::common_type_t<T, U>>) const noexcept;


        /**
         * @brief Compare all components of @p lhs quaternion with @p rhs quaternion for inequality.
         *        Perform a component-wise comparison and returns `true` if any corresponding elements differ by more
         *        than @p epsilon.
         *
         * @note To obtain a component-wise boolean mask, use @ref neq.
         *
         * @tparam U Numeric type of the RHS quaternion. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The quaternion to compare.
         * @param[in] rhs     The quaternion to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if any of the components are not equivalent within @p epsilon.
         *
         * @relatedalso allEq()
         * @relatedalso vecEq()
         * @relatedalso eq()
         * @relatedalso neq()
         * @relatedalso vecNeq()
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr bool anyNeq(const Quaternion& lhs, const Quaternion<U>& rhs,
                                                   double epsilon = Config::EPSILON<std::common_type_t<T, U>>) noexcept;


        /**
         * @brief Perform component-wise equality check between this quaternion and @p rhs quaternion.
         *        Compare each component pair and returns a boolean mask.
         *
         * @note To obtain a single scalar result, use @ref allEq or @ref operator==.
         *
         * @tparam U Numeric type of the RHS quaternion. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs     The quaternion to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return A @ref Quaternion<bool> mask containing the results of each component comparison.
         *
         * @relatedalso allEq()
         * @relatedalso vecEq()
         * @relatedalso anyNeq()
         * @relatedalso neq()
         * @relatedalso vecNeq()
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr Quaternion<bool> eq(
            const Quaternion<U>& rhs, double epsilon = Config::EPSILON<std::common_type_t<T, U>>) const noexcept;


        /**
         * @brief Perform component-wise equality check between @p lhs and @p rhs quaternion.
         *        Compare each component pair and returns a boolean mask.
         *
         * @tparam U Numeric type of the RHS quaternion. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The quaternion to compare.
         * @param[in] rhs     The quaternion to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return A @ref Quaternion<bool> mask containing the results of each component comparison.
         *
         * @relatedalso allEq()
         * @relatedalso vecEq()
         * @relatedalso anyNeq()
         * @relatedalso neq()
         * @relatedalso vecNeq()
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr Quaternion<bool> eq(
            const Quaternion& lhs, const Quaternion<U>& rhs,
            double epsilon = Config::EPSILON<std::common_type_t<T, U>>) noexcept;


        /**
         * @brief Perform component-wise inequality check between this quaternion and @p rhs quaternion.
         *        Compare each component pair and returns a boolean mask.
         *
         * @note To obtain a single scalar result, use @ref anyNeq or @ref operator!=.
         *
         * @tparam U Numeric type of the RHS quaternion. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs     The quaternion to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return A @ref Quaternion<bool> mask containing the results of each component comparison.
         *
         * @relatedalso allEq()
         * @relatedalso vecEq()
         * @relatedalso eq()
         * @relatedalso anyNeq()
         * @relatedalso vecNeq()
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr Quaternion<bool> neq(
            const Quaternion<U>& rhs, double epsilon = Config::EPSILON<std::common_type_t<T, U>>) const noexcept;


        /**
         * @brief Perform component-wise inequality check between @p lhs quaternion and @p rhs quaternion.
         *        Compare each component pair and returns a boolean mask.
         *
         * @tparam U Numeric type of the RHS quaternion. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The quaternion to compare.
         * @param[in] rhs     The quaternion to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return A @ref Quaternion<bool> mask containing the results of each component comparison.
         *
         * @relatedalso allEq()
         * @relatedalso vecEq()
         * @relatedalso eq()
         * @relatedalso anyNeq()
         * @relatedalso vecNeq()
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr Quaternion<bool> neq(
            const Quaternion& lhs, const Quaternion<U>& rhs,
            double epsilon = Config::EPSILON<std::common_type_t<T, U>>) noexcept;


        /**
         * @brief Perform component-wise equality check between the vector part of this quaternion
         *        and @p rhs quaternion.
         *
         * @note To obtain a single scalar result, use @ref allEq or @ref operator==.
         *
         * @tparam U Numeric type of the RHS quaternion. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs     The quaternion to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if all components of the vector part(i, j, k) are equivalent within @p epsilon.
         *
         * @relatedalso allEq()
         * @relatedalso eq()
         * @relatedalso anyNeq()
         * @relatedalso neq()
         * @relatedalso vecNeq()
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr bool vecEq(const Quaternion<U>& rhs,
                                           double epsilon = Config::EPSILON<std::common_type_t<T, U>>) const noexcept;


        /**
         * @brief Perform component-wise equality check between the vector part of @p lhs and @p rhs quaternion.
         *
         * @tparam U Numeric type of the RHS quaternion. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The quaternion to compare.
         * @param[in] rhs     The quaternion to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if all components of the vector part(i, j, k) are equivalent within @p epsilon.
         *
         * @relatedalso allEq()
         * @relatedalso eq()
         * @relatedalso anyNeq()
         * @relatedalso neq()
         * @relatedalso vecNeq()
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr bool vecEq(const Quaternion& lhs, const Quaternion<U>& rhs,
                                                  double epsilon = Config::EPSILON<std::common_type_t<T, U>>) noexcept;


        /**
         * @brief Perform component-wise inequality check between the vector part of this quaternion
         *        and @p rhs quaternion.
         *
         * @note To obtain a single scalar result, use @ref allEq or @ref operator==.
         *
         * @tparam U Numeric type of the RHS quaternion. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs     The quaternion to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if any components of the vector part(i, j, k) are not equivalent within @p epsilon.
         *
         * @relatedalso allEq()
         * @relatedalso vecNeq()
         * @relatedalso eq()
         * @relatedalso anyNeq()
         * @relatedalso neq()
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr bool vecNeq(const Quaternion<U>& rhs,
                                            double epsilon = Config::EPSILON<std::common_type_t<T, U>>) const noexcept;


        /**
         * @brief Perform component-wise inequality check between the vector part of @p lhs and @p rhs quaternion.
         *
         * @tparam U Numeric type of the RHS quaternion. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The quaternion to compare.
         * @param[in] rhs     The quaternion to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if any components of the vector part(i, j, k) are not equivalent within @p epsilon.
         *
         * @relatedalso allEq()
         * @relatedalso vecNeq()
         * @relatedalso eq()
         * @relatedalso anyNeq()
         * @relatedalso neq()
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr bool vecNeq(const Quaternion& lhs, const Quaternion<U>& rhs,
                                                   double epsilon = Config::EPSILON<std::common_type_t<T, U>>) noexcept;


        /**
         * @copybrief allEq(const Quaternion<U>&, double) const
         *
         * @note To obtain a component-wise boolean mask, use @ref eq.
         *
         * @tparam U Numeric type of the RHS quaternion. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs The quaternion to compare against.
         *
         * @return True if all components are equivalent within the default epsilon.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr bool operator==(const Quaternion<U>& rhs) const noexcept;


        /**
         * @copybrief anyNeq(const Quaternion<U>&, double) const
         *
         * @note To obtain a component-wise boolean mask, use @ref eq.
         *
         * @tparam U Numeric type of the RHS quaternion. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs The quaternion to compare against.
         *
         * @return True if any of the components are not equivalent within the default epsilon.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr bool operator!=(const Quaternion<U>& rhs) const noexcept;


        /** @} */



        /**
         * @addtogroup FALCON_Quaternion_Algebra
         * @{
         */

        /**
         * @brief Compute the product of this quaternion with @p other quaternion.
         *
         * @tparam U The numeric type of RHS quaternion. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] other The quaternion to multiply.
         *
         * @return A new @ref Quaternion scaled by @p scalar.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        constexpr PromotedQuaternion<T, U> operator*(const Quaternion<U>& other) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the product of this quaternion with @p other quaternion in-place.
         *
         * @tparam U The numeric type of RHS quaternion. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] other The quaternion to multiply.
         *
         * @return A reference to this quaternion (*this).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        constexpr Quaternion& operator*=(const Quaternion<U>& other) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the conjugate of this quaternion.
         *        \f$ \mathbf{q^*} = [\mathbf{v} \quad w]^* = [-\mathbf{v} \quad w] \f$
         *
         * @note Operation is restricted to signed numeric types via @ref SignedStrictArithmetic.
         *
         * @return A new @ref flcn::Quaternion with negated vector components.
         */
        [[nodiscard]] constexpr Quaternion conjugate() const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the conjugate of a quaternion.
         *        \f$ \mathbf{q^*} = [\mathbf{v} \quad w]^* = [-\mathbf{v} \quad w] \f$
         *
         * @note Operation is restricted to signed numeric types via @ref SignedStrictArithmetic.
         *
         * @return A new @ref flcn::Quaternion with negated vector components.
         */
        [[nodiscard]] static constexpr Quaternion conjugate(const Quaternion& quat) noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the magnitude of this quaternion.
         *        \f$ \|\mathbf{q}\| = \sqrt{\mathbf{\|v\|^2} + w^2} \f$
         *
         * @note To avoid precision loss, integral types are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         * @note If you only want the magnitude squared, use @ref dot,
         *       which is faster due to be the absense of sqrt.
         *
         * @return The scalar magnitude of the quaternion.
         */
        [[nodiscard]] constexpr Magnitude<T> mag() const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the magnitude of @p quat.
         *        \f$ \|\mathbf{q}\| = \sqrt{\mathbf{\|v\|^2} + w^2} \f$
         *
         * @note To avoid precision loss, integral types are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         * @note If you only want the magnitude squared, use @ref dot,
         *       which is faster due to be the absense of sqrt.
         *
         * @param[in] quat The quaternion to compute the magnitude of.
         *
         * @return The scalar magnitude of @p quat.
         */
        [[nodiscard]] static constexpr Magnitude<T> mag(const Quaternion& quat) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the inverse of this quaternion.
         *        \f$ \mathbf{q^{-1}} = \frac{\mathbf{q^*}}{\|q\|^2} \f$
         *
         * @note To avoid precision loss, integral types are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @note Operation is restricted to signed numeric types via @ref SignedStrictArithmetic.
         *
         * @return A new @ref flcn::Quaternion which satisfies q * inv(q) = [0 0 0 1].
         */
        [[nodiscard]] constexpr Quaternion<Magnitude<T>> inverse() const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the inverse of a quaternion.
         *        \f$ \mathbf{q^{-1}} = \frac{\mathbf{q^*}}{\|q\|^2} \f$
         *
         * @note To avoid precision loss, integral types are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @note Operation is restricted to signed numeric types via @ref SignedStrictArithmetic.
         *
         * @return A new @ref flcn::Quaternion which satisfies q * inv(q) = [0 0 0 1].
         */
        [[nodiscard]] static constexpr Quaternion<Magnitude<T>> inverse(const Quaternion& quat) noexcept
            requires SignedStrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FALCON_Quaternion_Vector_Algebra
         * @{
         */

        /**
         * @brief Compute the dot product with another quaternion.
         *        \f$ \mathbf{a} \cdot \mathbf{b} = \sum_{i=1}^{4} a_i b_i \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedValue_t<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS quaternion. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The quaternion to compute the dot product with.
         *
         * @return The scalar dot product of the two quaternion.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedValue_t<T, U> dot(const Quaternion<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the dot product of two quaternions.
         *        \f$ \mathbf{a} \cdot \mathbf{b} = \sum_{i=1}^{4} a_i b_i \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedValue_t<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS quaternion. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] lhs The first quaternion to compute the dot product with.
         * @param[in] rhs The second quaternion to compute the dot product with.
         *
         * @return The scalar dot product of @p lhs and @p rhs.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedValue_t<T, U> dot(const Quaternion& lhs,
                                                                 const Quaternion<U>& rhs) noexcept
            requires StrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FALCON_Quaternion_Utils
         * @{
         */

        /**
         * @brief Check if any component of this quaternion is an IEEE 754 infinity.
         *
         * @note Always return false for integral types.
         *
         * @return True if at least one component is positive or negative infinity.
         */
        [[nodiscard]] constexpr bool hasInf() const noexcept;


        /**
         * @brief Check if any component of a quaternion is an IEEE 754 infinity.
         *
         * @note Always return false for integral types.
         *
         * @param[in] quat The quaternion to evaluate for indefinite components.
         *
         * @return True if at least one component is positive or negative infinity.
         */
        [[nodiscard]] static constexpr bool hasInf(const Quaternion& quat) noexcept;


        /**
         * @brief Check if any component of this quaternion is an IEEE NaN(Not-a-Number).
         *
         * @note Always return false for integral types.
         *
         * @return True if at least one component is NaN.
         */
        [[nodiscard]] constexpr bool hasNaN() const noexcept;


        /**
         * @brief Check if any component of this quaternion is an IEEE NaN(Not-a-Number).
         *
         * @note Always return false for integral types.
         *
         * @param[in] quat The quaternion to evaluate for NaN components.
         *
         * @return True if at least one component is NaN.
         */
        [[nodiscard]] static constexpr bool hasNaN(const Quaternion& quat) noexcept;

        /** @} */


        /**
         * @addtogroup FALCON_Quaternion_Const
         * @{
         */

        /**
         * @brief A quaternion with zero vector part and unit scalar part (0i, 0j, 0k, 1).
         */
        static constexpr Quaternion identity()
            requires StrictArithmetic<T>
        { return Quaternion{ T(0), T(0), T(0), T(1) }; }


        /**
         * @brief A quaternion with unit vector part and scalar part (1i, 1j, 1k, 1).
         */
        static constexpr Quaternion one()
            requires StrictArithmetic<T>
        { return Quaternion{ T(1), T(1), T(1), T(1) }; }


        /**
         * @brief A quaternion with all components set to zero (0i, 0j, 0k, 0).
         */
        static constexpr Quaternion zero()
            requires StrictArithmetic<T>
        { return Quaternion{ T(0), T(0), T(0), T(0) }; }

        /** @} */



    private:
        std::array<T, 4> _data;
    };



    /**
     * @addtogroup FALCON_Quaternion_Arithmetic
     * @{
     */

    /**
     * @brief Compute the component-wise product of this quaternion with @p scalar.
     *
     * @tparam S The numeric type of RHS quaternion. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] scalar The scalar to multiply.
     * @param[in] quat   The quaternion to multiply.
     *
     * @return A new @ref Quaternion scaled by @p scalar.
     */
    template <StrictArithmetic T, StrictArithmetic S>
        requires StrictSignedness<T, S>
    constexpr PromotedQuaternion<T, S> operator*(S scalar, const Quaternion<T>& quat) noexcept;

    /** @} */



    /** @brief Template deduction guide for Quaternion. */
    template <typename T>
        requires Arithmetic<T>
    Quaternion(T, T, T, T) -> Quaternion<T>;

    template <typename T>
        requires Arithmetic<T>
    Quaternion(Vec3<T>, T) -> Quaternion<T>;

} // namespace flcn



#include "Quaternion.tpp"
