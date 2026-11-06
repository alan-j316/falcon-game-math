#pragma once
/**
 * @file CVec2.h
 * @author Alan Abraham P Kochumon
 * @date Created on: January 24, 2026
 *
 * @brief Templated 2D Vector supporting integral, floating-point, and boolean types.
 *
 * @details Provide high-performance 2D vector implementation with SIMD acceleration
 *          and support for component-wise operations.
 *
 * @note Arithmetic operations are limited to numeric types via `StrictArithmetic` concept.
 *
 * @par Configuration
 * Define `ENABLE_FALCON_SHADER_OPERATORS` to enable comparison operators (>, <, etc.).
 * Even if disabled, functional comparisons like `greaterThan()` remain available.
 * Define `FORCE_SCALAR` to turn off SIMD which is on by default on supported hardware.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "falcon/math/common/Config.h"
#include "falcon/math/common/Constants.h"
#include "falcon/math/common/MathTraits.h"
#include "falcon/math/common/OperationStatus.h"
#include "falcon/math/common/Types.h"

#include <array>
#include <iomanip>
#include <type_traits>


namespace flcn
{
    template <Arithmetic T>
    struct CVec2
    {
        /**
         * @addtogroup FALCON_CVec2_Members
         * @{
         */

        using value_type = T; ///< The numeric type of the vector components.

        static constexpr std::size_t DIMENSION = 2; ///< The number of components of the vector.

        /** @} */


        /**
         * @addtogroup FALCON_CVec2_Init
         * @{
         */

        /**
         * @brief Initialize an uninitialized @ref CVec2 instance.
         *
         * @warning The components are left uninitialized (containing garbage data)
         *          to maximize SIMD optimization and maintain triviality.
         *
         * @note Use value-initialization (`{}`) or the static helper
         *       @ref flcn::CVec2<T>::zero() to guarantee a zeroed vector.
         */
        CVec2() = default;


        /**
         * @brief Initialize @ref CVec2 with a single value broadcast across its components.
         *
         * @param[in] val The value to use broadcast across all vector components.
         */
        [[nodiscard]] explicit constexpr CVec2(T val) noexcept;


        /**
         * @brief Initialize @ref CVec2 with passed in values.
         *
         * @param[in] v1 The first entry of @ref CVec2.
         * @param[in] v2 The second entry of @ref CVec2.
         */
        [[nodiscard]] constexpr CVec2(T v1, T v2) noexcept;


        /**
         * @brief Initialize @ref CVec2 from another @ref CVec2 of a different type.
         *
         * @tparam U Numeric type of the source vector.
         *
         * @param[in] other The source vector to be converted.
         */
        template <Arithmetic U>
        [[nodiscard]] explicit constexpr CVec2(const CVec2<U>& other) noexcept;


        /// @brief Convert this CVec2 to a Simd accelerated Vec2.
        /// @note Use this minimally, as these can add unnecessary overheads.
        [[nodiscard]] constexpr Vec2<T> toVec2() const noexcept;


        /// @brief Convert @p vec to a Simd accelerated Vec2.
        /// @note Use this minimally, as these can add unnecessary overheads.
        [[nodiscard]] static constexpr Vec2<T> toVec2(const CVec2& vec) noexcept;

        /** @} */


        /**
         * @addtogroup FALCON_CVec2_Access
         * @{
         */

        /**
         * @brief Access the element at the first location.
         * @return A copy of the first vector element.
         */
        [[nodiscard]] constexpr T x() const noexcept;


        /**
         * @brief Access the element at the first location (read-write access).
         * @return A reference to the first element of the vector.
         */
        [[nodiscard]] constexpr T& x() noexcept;


        /**
         * @brief Access the element at the last location.
         * @return A copy of the last vector element.
         */
        [[nodiscard]] constexpr T y() const noexcept;


        /**
         * @brief Access the element at the last location (read-write access).
         * @return A reference to the last element of the vector.
         */
        [[nodiscard]] constexpr T& y() noexcept;


        /**
         * @brief Access the element at the first location.
         * @return A copy of the first vector element.
         */
        [[nodiscard]] constexpr T s() const noexcept;


        /**
         * @brief Access the element at the first location (read-write access).
         * @return A reference to the first element of the vector.
         */
        [[nodiscard]] constexpr T& s() noexcept;


        /**
         * @brief Access the element at the last location.
         * @return A copy of the last vector element.
         */
        [[nodiscard]] constexpr T t() const noexcept;


        /**
         * @brief Access the element at the last location (read-write access).
         * @return A reference to the last element of the vector.
         */
        [[nodiscard]] constexpr T& t() noexcept;


        /**
         * @brief Access the element at the first location.
         * @return A copy of the first vector element.
         */
        [[nodiscard]] constexpr T r() const noexcept;


        /**
         * @brief Access the element at the first location (read-write access).
         * @return A reference to the first element of the vector.
         */
        [[nodiscard]] constexpr T& r() noexcept;


        /**
         * @brief Access the element at the last location.
         * @return A copy of the last vector element.
         */
        [[nodiscard]] constexpr T g() const noexcept;


        /**
         * @brief Access the element at the last location (read-write access).
         * @return A reference to the last element of the vector.
         */
        [[nodiscard]] constexpr T& g() noexcept;


        /**
         * @brief Access the element at the specified location.
         *        Provide read-write access to the element.
         *
         * @note Performs bounds checking in **DEBUG MODE**.
         *
         * @param[in] idx The index of the vector component.
         *
         * @return A reference to the vector component.
         */
        constexpr T& operator[](std::size_t idx) noexcept;


        /**
         * @brief Access the element at the specified location.
         *
         * @note Performs bounds checking in **DEBUG MODE**.
         *
         * @param[in] idx The index of the vector component.
         *
         * @return A copy of the vector component.
         */
        constexpr const T& operator[](std::size_t idx) const noexcept;

        /** @} */


        /**
         * @addtogroup FALCON_CVec2_Swizzle
         * @{
         */

        /**
         * @brief Construct a new vector by rearranging, duplicating, or isolating components of this vector.
         *
         * @note Bounds checking for the provided indices is strictly enforced at compile-time.
         *       Providing an out-of-bounds index will result in a compilation error, guaranteeing zero runtime
         *       overhead.
         *
         * @tparam Indices The component indices used to construct the new vector.
         *                 See @ref flcn::axis, @ref flcn::colors, and @ref flcn::stp for available swizzle aliases.
         *
         * @return A new vector containing the requested components or the component if @p Indices is 1.
         *         The dimension of the returned vector perfectly matches the number of indices provided.
         */
        template <std::size_t... Indices>
        [[nodiscard("Swizzling returns a new vector and does not mutate the original.")]]
        constexpr auto swizzle() const noexcept;


        /**
         * @brief Construct a new vector by rearranging, duplicating, or isolating components of @p Vec.
         *
         * @note Bounds checking for the provided indices is strictly enforced at compile-time.
         *       Providing an out-of-bounds index will result in a compilation error, guaranteeing zero runtime
         *       overhead.
         *
         * @tparam Indices The component indices used to construct the new vector.
         *                 See @ref flcn::axis, @ref flcn::colors, and @ref flcn::stp for available swizzle aliases.
         *
         * @param vec The vector to shuffle, rearrange or isolate components.
         *
         * @return A new vector containing the requested components or the component if @p Indices is 1.
         *         The dimension of the returned vector perfectly matches the number of indices provided.
         */
        template <std::size_t... Indices>
        [[nodiscard("Swizzling returns a new vector and does not mutate the original.")]]
        static constexpr auto swizzle(const CVec2& vec) noexcept;

        /** @} */



        /**
         * @addtogroup FALCON_CVec2_Ptr
         * @{
         */

        /// @brief Get the internal storage of the vector as a pointer.
        [[nodiscard]] constexpr const T* ptr() const noexcept;

        /// @brief Get the internal storage of the vector as a pointer (non-const).
        [[nodiscard]] constexpr T* ptr() noexcept;

        /// @brief Get the internal storage of @p vec as a pointer.
        [[nodiscard]] static constexpr const T* ptr(const CVec2& vec) noexcept;

        /// @brief Get the internal storage of @p vec as a pointer.
        [[nodiscard]] static constexpr T* ptr(CVec2& vec) noexcept;

        /// @brief Get the internal storage of @p vec as a pointer (non-const).
        [[nodiscard]] constexpr T* operator*() noexcept;

        /// @brief Get the internal storage of @p vec as a pointer (non-const).
        [[nodiscard]] constexpr const T* operator*() const noexcept;

        /** @} */



        /**
         * @addtogroup FALCON_CVec2_Equality
         * @{
         */

        /**
         * @brief Compare all components of this vector with @p rhs vector for equality.
         *        Perform a component-wise comparison and returns true only if every element pair
         *        satisfies the equality condition within the given @p epsilon.
         *
         * @note To obtain a component-wise boolean mask, use @ref eq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs     The vector to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return True if all components are equivalent within @p epsilon.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr bool allEq(const CVec2<U>& rhs,
                                           double epsilon = std::is_same_v<T, double> || std::is_same_v<U, double>
                                               ? Config::DOUBLE_EPSILON
                                               : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @brief Compare all components of @p lhs vector with @p rhs vector for equality.
         *        Perform a component-wise comparison and returns `true` only if every element pair
         *        satisfies the equality condition within the given @p epsilon.
         *
         * @note To obtain a component-wise boolean mask, use @ref eq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The vector to compare.
         * @param[in] rhs     The vector to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         * @return `true` if all components are equivalent within @p epsilon.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr bool allEq(const CVec2& lhs, const CVec2<U>& rhs,
                                                  double epsilon = std::is_same_v<T, double> ||
                                                          std::is_same_v<U, double>
                                                      ? Config::DOUBLE_EPSILON
                                                      : Config::FLOAT_EPSILON) noexcept;


        /**
         * @brief Compare all components of this vector with @p rhs vector for inequality.
         *        Perform a component-wise comparison and returns `true` if any corresponding elements differ by more
         *        than @p epsilon.
         *
         * @note To obtain a component-wise boolean mask, use @ref neq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs     The vector to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return `true` if any of the components are not equivalent within @p epsilon.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr bool anyNeq(const CVec2<U>& rhs,
                                            double epsilon = std::is_same_v<T, double> || std::is_same_v<U, double>
                                                ? Config::DOUBLE_EPSILON
                                                : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @brief Compare all components of @p lhs vector with @p rhs vector for inequality.
         *        Perform a component-wise comparison and returns `true` if any corresponding elements differ by more
         *        than @p epsilon.
         *
         * @note To obtain a component-wise boolean mask, use @ref neq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The vector to compare.
         * @param[in] rhs     The vector to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return `true` if any of the components are not equivalent within @p epsilon.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr bool anyNeq(const CVec2& lhs, const CVec2<U>& rhs,
                                                   double epsilon = std::is_same_v<T, double> ||
                                                           std::is_same_v<U, double>
                                                       ? Config::DOUBLE_EPSILON
                                                       : Config::FLOAT_EPSILON) noexcept;


        /**
         * @copybrief allEq(const CVec2<U>&, double) const
         *
         * @note To obtain a component-wise boolean mask, use @ref eq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs The vector to compare against.
         *
         * @return True if all components are equivalent within the default epsilon.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr bool operator==(const CVec2<U>& rhs) const noexcept;


        /**
         * @copybrief anyNeq(const CVec2<U>&, double) const
         *
         * @note To obtain a component-wise boolean mask, use @ref eq.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs The vector to compare against.
         *
         * @return True if any of the components are not equivalent within the default epsilon.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr bool operator!=(const CVec2<U>& rhs) const noexcept;


        /**
         * @brief Perform component-wise equality check between this vector and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
         *
         * @note To obtain a single scalar result, use @ref allEq or @ref operator==.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs     The vector to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return A @ref CVec2<bool> mask containing the results of each component comparison.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr CVec2<bool> eq(const CVec2<U>& rhs,
                                               double epsilon = std::is_same_v<T, double> || std::is_same_v<U, double>
                                                   ? Config::DOUBLE_EPSILON
                                                   : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @brief Perform component-wise equality check between @p lhs and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The vector to compare.
         * @param[in] rhs     The vector to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return A @ref CVec2<bool> mask containing the results of each component comparison.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr CVec2<bool> eq(const CVec2& lhs, const CVec2<U>& rhs,
                                                      double epsilon = std::is_same_v<T, double> ||
                                                              std::is_same_v<U, double>
                                                          ? Config::DOUBLE_EPSILON
                                                          : Config::FLOAT_EPSILON) noexcept;


        /**
         * @brief Perform component-wise inequality check between this vector and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
         *
         * @note To obtain a single scalar result, use @ref anyNeq or @ref operator!=.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] rhs     The vector to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return A @ref CVec2<bool> mask containing the results of each component comparison.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr CVec2<bool> neq(const CVec2<U>& rhs,
                                                double epsilon = std::is_same_v<T, double> || std::is_same_v<U, double>
                                                    ? Config::DOUBLE_EPSILON
                                                    : Config::FLOAT_EPSILON) const noexcept;


        /**
         * @brief Perform component-wise inequality check between @p lhs vector and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref Arithmetic.
         *
         * @param[in] lhs     The vector to compare.
         * @param[in] rhs     The vector to compare against.
         * @param[in] epsilon The maximum allowable difference for `std::floating_point` types.
         *                    Defaults to @ref DOUBLE_EPSILON or @ref FLOAT_EPSILON based on type promotion.
         *
         * @return A @ref CVec2<bool> mask containing the results of each component comparison.
         */
        template <Arithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr CVec2<bool> neq(const CVec2& lhs, const CVec2<U>& rhs,
                                                       double epsilon = std::is_same_v<T, double> ||
                                                               std::is_same_v<U, double>
                                                           ? Config::DOUBLE_EPSILON
                                                           : Config::FLOAT_EPSILON) noexcept;

        /** @} */


        /**
         * @addtogroup FALCON_CVec2_Comparison
         * @{
         */

        /**
         * @brief Perform component-wise greater-than comparison between this vector and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to compare against.
         *
         * @return A @ref CVec2<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr CVec2<bool> gt(const CVec2<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise greater-than comparison between @p lhs vector and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in]  lhs The vector to compare.
         * @param[in]  rhs The vector to compare against.
         *
         * @return A @ref CVec2<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr CVec2<bool> gt(const CVec2& lhs, const CVec2<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise greater-than-or-equal comparison between this vector and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to compare against.
         *
         * @return A @ref CVec2<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr CVec2<bool> gte(const CVec2<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise greater-than-or-equal comparison between @p lhs vector and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in]  lhs The vector to compare.
         * @param[in]  rhs The vector to compare against.
         *
         * @return A @ref CVec2<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr CVec2<bool> gte(const CVec2& lhs, const CVec2<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise less-than comparison between this vector and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
         *
         * @note On MSVC, constexpr comparisons involving NaN may return incorrect results due to compiler-level
         *       constant folding bugs. Runtime execution remains IEEE 754 compliant under /fp:strict.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to compare against.
         *
         * @return A @ref CVec2<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr CVec2<bool> lt(const CVec2<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise less-than comparison between @p lhs vector and @p rhs vector.
         *        Compare each component pair and returns a boolean mask.
         *
         * @note On MSVC, constexpr comparisons involving NaN may return incorrect results due to compiler-level
         *       constant folding bugs. Runtime execution remains IEEE 754 compliant under /fp:strict
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in]  lhs The vector to compare.
         * @param[in]  rhs The vector to compare against.
         *
         * @return A @ref CVec2<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr CVec2<bool> lt(const CVec2& lhs, const CVec2<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise less-than-or-equal comparison between this vector and @p rhs vector.
         *        Compares each component pair and returns a boolean mask.
         *
         * @note On MSVC, constexpr comparisons involving NaN may return incorrect results due to compiler-level
         *       constant folding bugs. Runtime execution remains IEEE 754 compliant under /fp:strict
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to compare against.
         *
         * @return A @ref CVec2<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr CVec2<bool> lte(const CVec2<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Perform component-wise less-than-or-equal comparison between @p lhs vector and @p rhs vector.
         *        Compares each component pair and returns a boolean mask.
         *
         * @note On MSVC, constexpr comparisons involving NaN may return incorrect results due to compiler-level
         *       constant folding bugs. Runtime execution remains IEEE 754 compliant under /fp:strict
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in]  lhs The vector to compare.
         * @param[in]  rhs The vector to compare against.
         *
         * @return A @ref CVec2<bool> mask containing the results of each component comparison.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr CVec2<bool> lte(const CVec2& lhs, const CVec2<U>& rhs) noexcept
            requires StrictArithmetic<T>;


#ifdef ENABLE_FALCON_SHADER_OPERATORS

        /**
         * @copydoc gt(const CVec2<U>&) const
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr CVec2<bool> operator>(const CVec2<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copydoc gte(const CVec2<U>&) const
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr CVec2<bool> operator>=(const CVec2<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copydoc lt(const CVec2<U>&) const
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr CVec2<bool> operator<(const CVec2<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @copydoc lte(const CVec2<U>&) const
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr CVec2<bool> operator<=(const CVec2<U>& rhs) const noexcept
            requires StrictArithmetic<T>;
#endif

        /** @} */


        /**
         * @addtogroup FALCON_CVec2_Bitwise
         * @{
         */

        /**
         * @brief Perform component-wise logical AND between this vector and @p rhs vector.
         *        Compute the conjunction between each component pair.
         *
         * @note Only available for @ref bCVec2 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A @ref CVec2<bool> mask containing the results of component-wise AND.
         */
        [[nodiscard]] constexpr CVec2 operator&(const CVec2& rhs) const noexcept
            requires std::is_same_v<T, bool>;


        /**
         * @brief Perform an in-place component-wise logical AND between this vector and @p rhs vector.
         *        Compute the conjunction between each component pair in-place and update the calling vector.
         *
         * @note Only available for @ref bCVec2 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A reference to this vector (*this).
         */
        constexpr CVec2& operator&=(const CVec2& rhs) noexcept
            requires std::is_same_v<T, bool>;


        /**
         * @brief Perform component-wise logical OR between this vector and @p rhs vector.
         *        Compute the disjunction between each component pair.
         *
         * @note Only available for @ref bCVec2 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A @ref CVec2<bool> mask containing the results of component-wise OR.
         */
        [[nodiscard]] constexpr CVec2 operator|(const CVec2& rhs) const noexcept
            requires std::is_same_v<T, bool>;


        /**
         * @brief Perform an in-place component-wise logical OR between this vector and @p rhs vector.
         *        Compute the disjunction between each component pair in-place and update the calling vector.
         *
         * @note Only available for @ref bCVec2 and vectors with `bool` value_type.
         *
         * @param[in] rhs The vector to combine with.
         *
         * @return A reference to this vector (*this).
         */
        constexpr CVec2& operator|=(const CVec2& rhs) noexcept
            requires std::is_same_v<T, bool>;


        /**
         * @brief Apply a component-wise logical NOT on this vector.
         *        Invert each boolean component and returns a new @ref CVec2<bool>.
         *
         * @note Only available for @ref bCVec2 and vectors with `bool` value_type.
         *
         * @return A @ref CVec2<bool> with inverted values.
         */
        [[nodiscard]] constexpr CVec2 operator!() const noexcept
            requires std::is_same_v<T, bool>;

        /** @} */


        /**
         * @addtogroup FALCON_CVec2_Arithmetic
         * @{
         */

        /**
         * @brief Compute the component-wise sum of this vector with @p rhs vector and return a new vector.
         *
         * @note Promotes the result to the wider type using @ref PromotedCVec2<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to add.
         *
         * @return A new @ref CVec2 containing the component-wise sum.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedCVec2<T, U> operator+(const CVec2<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise sum of this vector with @p rhs vector in-place.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to add.
         *
         * @return A reference to this vector (*this).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        constexpr CVec2& operator+=(const CVec2<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise difference between this vector and @p rhs vector and return a new vector.
         *
         * @note Promotes the result to the wider type using @ref PromotedCVec2<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to subtract.
         *
         * @return A new @ref CVec2 containing the component-wise difference.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedCVec2<T, U> operator-(const CVec2<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise difference between this vector and @p rhs vector in-place.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to subtract.
         *
         * @return A reference to this vector (*this).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        constexpr CVec2& operator-=(const CVec2<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Negate each component of this vector and return a new @ref CVec2<T>.
         *
         * @note Operation is restricted to numeric types via @ref SignedStrictArithmetic.
         *
         * @return A new @ref flcn::CVec2 with negated components.
         */
        [[nodiscard]] constexpr CVec2 operator-() const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the component-wise product between this vector and @p scalar and return a new vector.
         *
         * @note Promotes the result to the wider type using @ref PromotedCVec2<T, S>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A new @ref CVec2 scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedCVec2<T, S> operator*(S scalar) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise product between this vector and @p scalar in-place.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A reference to this vector (*this).
         */
        template <StrictArithmetic S>
        constexpr CVec2& operator*=(S scalar) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise division of this vector by @p scalar and return a new vector.
         *
         * @note Promotes the result to the wider type using @ref PromotedCVec2<T, S>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Performs assertion for division by zero in **Debug mode**.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A new @ref CVec2 scaled by @p scalar.
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedCVec2<T, S> operator/(S scalar) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise division of this vector by @p scalar in-place.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         * @note Performs assertion for division by zero in **Debug mode**.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] scalar The value to scale by.
         *
         * @return A reference to this vector (*this).
         */
        template <StrictArithmetic S>
        constexpr CVec2& operator/=(S scalar) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise division of this vector by @p scalar and return a new vector.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this vector contains NaN components,
         *       returns a zero vector.
         * @note Promotes the result to the wider type using @ref PromotedCVec2<T, S>.
         * @note Operation is restricted to numeric types via @ref flcn::StrictArithmetic.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref flcn::StrictArithmetic.
         *
         * @param[in] scalar The value to divide the vector components by.
         *
         * @return A new @ref CVec2 resulting from the division or a zero-vector if the @p scalar is below the
         *         epsilon threshold or if either of the vectors contains NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedCVec2<T, S> safeDiv(S scalar) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise division of @p Vec by @p scalar and return a new vector.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this vector contains NaN components,
         *       returns a zero vector.
         * @note Promotes the result to the wider type using @ref PromotedCVec2<T, S>.
         * @note Operation is restricted to numeric types via @ref flcn::StrictArithmetic.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref flcn::StrictArithmetic.
         *
         * @param[in] vec The vector to divide.
         * @param[in] scalar The value to divide the vector components by.
         *
         * @return A new @ref CVec2 resulting from the division or a zero-vector if the @p scalar is below the
         *         epsilon threshold or if either of the vectors contains NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] static constexpr PromotedCVec2<T, S> safeDiv(const CVec2& vec, S scalar) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise division of this vector by @p scalar, return a new vector,
         *        and updates @p status to reflect the result of the operation.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this vector contains NaN components,
         *       returns a zero vector.
         * @note Promotes the result to the wider type using @ref PromotedCVec2<T, S>.
         * @note Operation is restricted to numeric types via @ref flcn::StrictArithmetic.
         * @note In the event of multiple failure conditions, data corruption (NaN) takes precedence over mathematical
         *       invalidity (Division by Zero) when reporting status.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref flcn::StrictArithmetic.
         *
         * @param[in] scalar  The value to divide the vector components by.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return A new @ref CVec2 resulting from the division or a zero-vector if the @p scalar is below the
         *         epsilon threshold or if either of the vectors+ has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] constexpr PromotedCVec2<T, S> tryDiv(S scalar, OperationStatus& status) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the component-wise division of @p Vec by @p scalar, return a new vector,
         *        and updates @p status to reflect the result of the operation.
         *
         * @note If @p scalar is zero (or below the epsilon threshold) or this vector contains NaN components,
         *       returns a zero vector.
         * @note Promotes the result to the wider type using @ref PromotedCVec2<T, S>.
         * @note Operation is restricted to numeric types via @ref flcn::StrictArithmetic.
         * @note In the event of multiple failure conditions, data corruption (NaN) takes precedence over mathematical
         *       invalidity (Division by Zero) when reporting status.
         *
         * @tparam S Numeric type of the scalar. Must satisfy @ref flcn::StrictArithmetic.
         *
         * @param[in] vec     The vector to divide.
         * @param[in] scalar  The value to divide the vector components by.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return A new @ref CVec2 resulting from the division or a zero-vector if the @p scalar is below the
         *         epsilon threshold or if either of the vectors+ has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic S>
        [[nodiscard]] static constexpr PromotedCVec2<T, S> tryDiv(const CVec2& vec, S scalar,
                                                                  OperationStatus& status) noexcept
            requires StrictArithmetic<T>;

        /** @} */


        /**
         * @addtogroup FALCON_CVec2_Product
         * @{
         */

        /**
         * @brief Compute the dot product with another vector.
         *        \f$ \mathbf{a} \cdot \mathbf{b} = \sum_{i=1}^{2} a_i b_i \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedValue_t<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to compute the dot product with.
         *
         * @return The scalar dot product of the two vectors.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedValue_t<T, U> dot(const CVec2<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the dot product of two vectors.
         *        \f$ \mathbf{a} \cdot \mathbf{b} = \sum_{i=1}^{2} a_i b_i \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedValue_t<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] lhs The first vector to compute the dot product with.
         * @param[in] rhs The second vector to compute the dot product with.
         *
         * @return The scalar dot product of @p lhs and @p rhs.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedValue_t<T, U> dot(const CVec2& lhs, const CVec2<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the tensor product with another vector.
         *        \f$ \mathbf{u} \otimes \mathbf{v} = u v^\top \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedMat2<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to compute the tensor product with.
         *
         * @return A new 2D matrix containing the tensor product.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedMat2<T, U> tensorProduct(const CVec2<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the dot product of two vectors.
         *        \f$ \mathbf{u} \otimes \mathbf{v} = u v^\top \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedMat2<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] lhs The first vector to compute the tensor product with.
         * @param[in] rhs The second vector to compute the tensor product with.
         *
         * @return A new 2D matrix containing the tensor product.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedMat2<T, U> tensorProduct(const CVec2& lhs, const CVec2<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the 2D pseudo-cross product with another vector.
         *        \f$ \mathbf{a} \times \mathbf{b} = (x_1 \cdot y_2 - x_2 \cdot y_1) \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedValue_t<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The vector to compute the cross product with.
         *
         * @return The pseudo-cross cross product of the two vectors.
         */
        template <SignedStrictArithmetic U>
        constexpr PromotedValue_t<T, U> cross(const CVec2<U>& rhs) const noexcept
            requires SignedStrictArithmetic<T>;


        /**
         * @brief Compute the 2D pseudo-cross product of two vectors.
         *        \f$ \mathbf{a} \times \mathbf{b} = (x_1 \cdot y_2 - x_2 \cdot y_1) \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedValue_t<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] lhs The first vector to compute the cross product with.
         * @param[in] rhs The second vector to compute the cross product with.
         *
         * @return The pseudo-cross product of the two vectors.
         */
        template <SignedStrictArithmetic U>
        static constexpr PromotedValue_t<T, U> cross(const CVec2& lhs, const CVec2<U>& rhs) noexcept
            requires SignedStrictArithmetic<T>;

        /** @} */


        /**
         * @addtogroup FALCON_CVec2_Mag
         * @{
         */

        /**
         * @brief Compute the magnitude (Euclidean Norm) of this vector.
         *        \f$ \|\mathbf{v}\| = \sqrt{\mathbf{v} \cdot \mathbf{v}} \f$
         *
         * @note To avoid precision loss, integral types are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @return The scalar magnitude of the vector.
         */
        [[nodiscard]] constexpr Magnitude<T> mag() const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the magnitude (Euclidean Norm) of @p Vec.
         *        \f$ \|\mathbf{v}\| = \sqrt{\mathbf{v} \cdot \mathbf{v}} \f$
         *
         * @note To avoid precision loss, integral types are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @param[in] vec The vector to compute the magnitude of.
         *
         * @return The scalar magnitude of @p Vec.
         */
        [[nodiscard]] static constexpr Magnitude<T> mag(const CVec2& vec) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the magnitude square (Euclidean Norm) of this vector.
         *        \f$ \|\mathbf{v}\| = \mathbf{v} \cdot \mathbf{v} \f$
         *
         * @return The scalar magnitude of the vector.
         */
        [[nodiscard]] constexpr T magSq() const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the magnitude square (Euclidean Norm) of @p Vec.
         *        \f$ \|\mathbf{v}\| = \mathbf{v} \cdot \mathbf{v} \f$
         *
         * @param[in] vec The vector to compute the magnitude of.
         *
         * @return The scalar magnitude of @p Vec.
         */
        [[nodiscard]] static constexpr T magSq(const CVec2& vec) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the Manhattan length (L1 Norm) of this vector.
         *        \f$ \|\mathbf{v}\|_1 = |x| + |y| \f$
         *
         * @return The Manhattan length.
         */
        [[nodiscard]] constexpr T manhattanNorm() const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the Manhattan length (L1 Norm) of @p Vec.
         *        \f$ \|\mathbf{v}\|_1 = |x| + |y| \f$
         *
         * @param[in] vec The vector to compute the taxicab norm of.
         *
         * @return The Manhattan length.
         */
        [[nodiscard]] static constexpr T manhattanNorm(const CVec2& vec) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the Chebyshev length (L∞ Norm) of this vector.
         *        \f$ \|\mathbf{v}\|_{\infty} = max(|x|, |y|) \f$
         *
         * @return The Chebyshev length.
         */
        [[nodiscard]] constexpr T chebyshevNorm() const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the Chebyshev length (L∞ Norm) of @p Vec.
         *        \f$ \|\mathbf{v}\|_{\infty} = max(|x|, |y|) \f$
         *
         * @param[in] vec The vector to compute the taxicab norm of.
         *
         * @return The Chebyshev length.
         */
        [[nodiscard]] static constexpr T chebyshevNorm(const CVec2& vec) noexcept
            requires StrictArithmetic<T>;

        /** @} */


        /**
         * @addtogroup FALCON_CVec2_Dist
         * @{
         */

        /**
         * @brief Compute the Euclidean (L2) distance between this vector and the @p rhs vector.
         *        \f$ d = \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2} \f$
         *
         * @note Mathematically, distance is a metric between points, not directional vectors.
         *       This operation treats both vectors as position vectors (coordinates in affine space).
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The target position vector.
         *
         * @return The Euclidean distance promoted as the promoted floating-point type.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr Magnitude<PromotedValue_t<T, U>> dist(const CVec2<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the Euclidean (L2) distance between two vectors.
         *        \f$ d = \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2} \f$
         *
         * @note Mathematically, distance is a metric between points, not directional vectors.
         *       This operation treats both vectors as position vectors (coordinates in affine space).
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] lhs The first position vector.
         * @param[in] rhs The second position vector.
         *
         * @return The Euclidean distance as the promoted floating-point type.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr Magnitude<PromotedValue_t<T, U>> dist(const CVec2<U>& lhs,
                                                                             const CVec2<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the squared Euclidean (L2) distance between this vector and the @p rhs vector.
         *        \f$ d = (x_2 - x_1)^2 + (y_2 - y_1)^2 \f$
         *
         * @note Mathematically, distance is a metric between points, not directional vectors.
         *       This operation treats both vectors as position vectors (coordinates in affine space).
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The target position vector.
         *
         * @return The squared Euclidean distance.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedValue_t<T, U> distSq(const CVec2<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the squared Euclidean (L2) distance between two vectors.
         *        \f$ d = (x_2 - x_1)^2 + (y_2 - y_1)^2 \f$
         *
         * @note Mathematically, distance is a metric between points, not directional vectors.
         *       This operation treats both vectors as position vectors (coordinates in affine space).
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] lhs The first position vector.
         * @param[in] rhs The second position vector.
         *
         * @return The squared Euclidean distance.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedValue_t<T, U> distSq(const CVec2& lhs, const CVec2<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the Manhattan (L1) distance between this vector and the @p rhs vector.
         *        \f$ d = |x_1 - x_2| + |y_1 - y_2| \f$
         *
         * @note Mathematically, distance is a metric between points, not directional vectors.
         *       This operation treats both vectors as position vectors (coordinates in affine space).
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The target position vector.
         *
         * @return The Manhattan (Taxicab) distance.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedValue_t<T, U> manhattanDist(const CVec2<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the Manhattan (L1) distance between two vectors.
         *        \f$ d = |x_1 - x_2| + |y_1 - y_2| \f$
         *
         * @note Mathematically, distance is a metric between points, not directional vectors.
         *       This operation treats both vectors as position vectors (coordinates in affine space).
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] lhs The first position vector.
         * @param[in] rhs The second position vector.
         *
         * @return The Manhattan(Taxicab) distance.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedValue_t<T, U> manhattanDist(const CVec2& lhs,
                                                                           const CVec2<U>& rhs) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the Chebyshev (L∞) distance between this vector and the @p rhs vector.
         *        \f$ d = \max{(|x_2 - x_1|, |y_2 - y_1|)} \f$
         *
         * @note Mathematically, distance is a metric between points, not directional vectors.
         *       This operation treats both vectors as position vectors (coordinates in affine space).
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The target position vector.
         *
         * @return The Chebyshev distance.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedValue_t<T, U> chebyshevDist(const CVec2<U>& rhs) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the Chebyshev (L∞) distance between two vectors.
         *        \f$ d = \max{(|x_2 - x_1|, |y_2 - y_1|)} \f$
         *
         * @note Mathematically, distance is a metric between points, not directional vectors.
         *       This operation treats both vectors as position vectors (coordinates in affine space).
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] lhs The first position vector.
         * @param[in] rhs The second position vector.
         *
         * @return The Chebyshev distance.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedValue_t<T, U> chebyshevDist(const CVec2& lhs,
                                                                           const CVec2<U>& rhs) noexcept
            requires StrictArithmetic<T>;

        /** @} */



        /**
         * @addtogroup FALCON_CVec2_Normalize
         * @{
         */

        /**
         * @brief Compute the normalized (unit) form of this vector.
         *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
         *
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         * @note Performs assertion for division by zero, resulting from zero-length vector, in **Debug mode**.
         *
         * @return A new @ref CVec2 with a magnitude of 1.0.
         */
        [[nodiscard]] constexpr CVec2<Magnitude<T>> normalize() const noexcept
            requires StrictArithmetic<T>;


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
         * @return A new @ref CVec2 with a magnitude of 1.0.
         */
        [[nodiscard]] static constexpr CVec2<Magnitude<T>> normalize(const CVec2& vec) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the normalized (unit) form of this vector.
         *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
         *
         * @note This is a safe operation. If the vector's magnitude falls below the internal
         *       epsilon, or if it contains NaN components, division by zero is bypassed.
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @return A @ref CVec2 with a magnitude of 1.0, or a zero-vector if the original magnitude is below the
         *         epsilon threshold or if this vector has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] constexpr CVec2<Magnitude<T>> safeNormalize() const noexcept
            requires StrictArithmetic<T>;


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
         * @return A @ref flcn::CVec2 with a magnitude of 1.0, or a zero-vector if the original magnitude is below the
         *         epsilon threshold or if the vector has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] static constexpr CVec2<Magnitude<T>> safeNormalize(const CVec2& vec) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Compute the normalized (unit) form of this vector and
         *        set @p status to the normalization operation result.
         *        \f$ \mathbf{\hat{v}} = \frac{\mathbf{v}}{\|\mathbf{v}\|} \f$
         *
         * @note This is a safe operation. If the vector's magnitude falls below the internal
         *       epsilon, or if it contains NaN components, division by zero is bypassed.
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         *
         * @param[out] status The status flag to store the status of the current operation result.*
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return A @ref flcn::CVec2 with a magnitude of 1.0, or a zero-vector if the original magnitude is below the
         *         epsilon threshold or if this vector has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] constexpr CVec2<Magnitude<T>> tryNormalize(OperationStatus& status) const noexcept
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
         * @return A @ref flcn::CVec2 with a magnitude of 1.0, or a zero-vector if the original magnitude is below the
         *         epsilon threshold or if the vector has NaN(Not-a-Number) component(s).
         */
        [[nodiscard]] static constexpr CVec2<Magnitude<T>> tryNormalize(const CVec2& vec,
                                                                        OperationStatus& status) noexcept
            requires StrictArithmetic<T>;

        /** @} */


        /**
         * @addtogroup FALCON_CVec2_Proj
         * @{
         */

        /**
         * @brief Project this vector onto the @p onto vector.
         *        \f$
         *          \text{proj}_{\mathbf{b}} \mathbf{a} =
         *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
         *        \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedFloatCVec2<T, U>.
         * @note If @p onto is normalized, use @ref projectNorm as it is a faster implementation for unit vectors.
         * @note Performs assertion for division by zero, resulting from zero-length vector, in **Debug mode**.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] onto The vector to project onto.
         *
         * @return The projected @ref CVec2.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedFloatCVec2<T, U> project(const CVec2<U>& onto) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Project this vector onto the **unit** @p onto vector.
         *        \f$
         *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
         *        \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedCVec2<T, U>.
         * @note Only use this method if @p onto is normalized. If not, use @ref project.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] onto The vector to project onto.
         *
         * @return The projected @ref CVec2.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedCVec2<T, U> projectNorm(const CVec2<U>& onto) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Project the @p Vec vector onto the @p onto vector.
         *        \f$
         *          \text{proj}_{\mathbf{b}} \mathbf{a} =
         *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
         *        \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedFloatCVec2<T, U>.
         * @note If @p onto is normalized, use @ref projectNorm as it is a faster implementation for unit vectors.
         * @note Performs assertion for division by zero, resulting from zero-length vector, in **Debug mode**.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec  The vector to project.
         * @param[in] onto The vector to project onto.
         *
         * @return The projected @ref CVec2.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedFloatCVec2<T, U> project(const CVec2& vec, const CVec2<U>& onto) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Project the @p Vec vector onto the **unit** @p onto vector.
         *        \f$
         *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
         *        \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedFloatCVec2<T, U>.
         * @note Only use this method if @p onto is normalized. If not, use @ref project.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec  The vector to project.
         * @param[in] onto The vector to project onto.
         *
         * @return The projected @ref CVec2.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedCVec2<T, U> projectNorm(const CVec2& vec, const CVec2<U>& onto) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Project this vector onto the @p onto vector.
         *        \f$
         *          \text{proj}_{\mathbf{b}} \mathbf{a} =
         *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
         *        \f$
         *
         * @note This is a safe operation. If the @p onto vector's magnitude falls below the internal
         *       epsilon, or if either vector contains NaN components, projection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedFloatCVec2<T, U>.
         * @note If @p onto is normalized, use @ref safeProjectNorm as it is a faster implementation for unit vectors.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] onto The vector to project onto.
         *
         * @return The projected @ref CVec2 or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedFloatCVec2<T, U> safeProject(const CVec2<U>& onto) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Project this vector onto the **unit** @p onto vector.
         *        \f$
         *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
         *        \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, projection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedCVec2<T, U>.
         * @note Only use this method if @p onto is normalized. If not, use @ref safeProject.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] onto           The vector to project onto.
         *
         * @return The projected @ref CVec2 or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedCVec2<T, U> safeProjectNorm(const CVec2<U>& onto) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Project the @p Vec vector onto the @p onto vector.
         *        \f$
         *          \text{proj}_{\mathbf{b}} \mathbf{a} =
         *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
         *        \f$
         *
         * @note This is a safe operation. If the @p onto vector's magnitude falls below the internal
         *       epsilon, or if either vector contains NaN components, projection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedFloatCVec2<T, U>.
         * @note If @p onto is normalized, use @ref safeProjectNorm as it is a faster implementation for unit vectors.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec  The vector to project.
         * @param[in] onto The vector to project onto.
         *
         * @return The projected @ref CVec2 or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedFloatCVec2<T, U> safeProject(const CVec2& vec,
                                                                            const CVec2<U>& onto) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Project the @p Vec vector onto the **unit** @p onto vector.
         *        \f$
         *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
         *        \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, projection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedCVec2<T, U>.
         * @note Only use this method if @p onto is normalized. If not, use @ref safeProject.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec  The vector to project.
         * @param[in] onto The vector to project onto.
         *
         * @return The projected @ref CVec2 or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedCVec2<T, U> safeProjectNorm(const CVec2& vec,
                                                                           const CVec2<U>& onto) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Project this vector onto the @p onto vector and set @p status to the
         *        projection operation result.
         *        \f$
         *          \text{proj}_{\mathbf{b}} \mathbf{a} =
         *          \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{b}\|^2} \mathbf{b}
         *        \f$
         *
         * @note This is a safe operation. If the @p onto vector's magnitude falls below the internal
         *       epsilon, or if either vector contains NaN components, projection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedFloatCVec2<T, U>.
         * @note If @p onto is normalized, use @ref tryProjectNorm as it is a faster implementation for unit vectors.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] onto    The vector to project onto.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The projected @ref CVec2 or a zero-vector if projected onto a zero-length vector or if either
         *         vector has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedFloatCVec2<T, U> tryProject(const CVec2<U>& onto,
                                                                    OperationStatus& status) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Project this vector onto the **unit** @p onto vector and set @p status to the
         *        projection operation result.
         *        \f$
         *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
         *        \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, projection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedCVec2<T, U>.
         * @note Only use this method if @p onto is normalized. If not, use @ref tryProject.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] onto    The vector to project onto.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The projected @ref CVec2 or a zero-vector if projected onto a zero-length vector or if either
         *         vector has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedCVec2<T, U> tryProjectNorm(const CVec2<U>& onto,
                                                                   OperationStatus& status) const noexcept
            requires StrictArithmetic<T>;


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
         * @note Promotes the result to the wider type using @ref PromotedFloatCVec2<T, U>.
         * @note If @p onto is normalized, use @ref tryProjectNorm as it is a faster implementation for unit vectors.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec     The vector to project.
         * @param[in] onto    The vector to project onto.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The projected @ref CVec2 or a zero-vector if projected onto a zero-length vector or if either
         *         vector has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedFloatCVec2<T, U> tryProject(const CVec2& vec, const CVec2<U>& onto,
                                                                           OperationStatus& status) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Project the @p Vec vector onto the **unit** @p onto vector and set @p status to the
         *        projection operation result.
         *        \f$
         *            \text{proj}_{\mathbf{b}} \mathbf{a} = (\mathbf{a} \cdot \mathbf{b}) \mathbf{\hat{b}}
         *        \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, projection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedCVec2<T, U>.
         * @note To maintain precision, result components are promoted to their
         *       corresponding floating-point representation via @ref Magnitude.
         * @note Only use this method if @p onto is normalized. If not, use @ref tryProject.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec     The vector to project.
         * @param[in] onto    The vector to project onto.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The projected @ref CVec2 or a zero-vector if projected onto a zero-length vector or if either
         *         vector has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedCVec2<T, U> tryProjectNorm(const CVec2& vec, const CVec2<U>& onto,
                                                                          OperationStatus& status) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject this vector from the @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedFloatCVec2<T, U>.
         * @note If @p from is normalized, use @ref rejectNorm as it is a faster implementation for unit vectors.
         * @note Performs assertion for division by zero, resulting from zero-length vector, in **Debug mode**.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] from The vector to reject from.
         *
         * @return The perpendicular @ref CVec2 component.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedFloatCVec2<T, U> reject(const CVec2<U>& from) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject this vector from the **unit** @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedFloatCVec2<T, U>.
         * @note Only use this method if @p from is normalized. If not, use @ref reject.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] from The vector to reject from.
         *
         * @return The perpendicular @ref CVec2 component.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedCVec2<T, U> rejectNorm(const CVec2<U>& from) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject the @p Vec vector from the @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedFloatCVec2<T, U>.
         * @note If @p from is normalized, use @ref rejectNorm as it is a faster implementation for unit vectors.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec  The vector to be rejected.
         * @param[in] from The vector to reject from.
         *
         * @return The perpendicular @ref CVec2 component.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedFloatCVec2<T, U> reject(const CVec2& vec, const CVec2<U>& from) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject the @p Vec vector from the **unit** @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note Promotes the result to the wider type using @ref PromotedCVec2<T, U>.
         * @note Only use this method if @p from is normalized. If not, use @ref reject.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec  The vector to be rejected.
         * @param[in] from The vector to reject from.
         *
         * @return The perpendicular @ref CVec2 component.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedCVec2<T, U> rejectNorm(const CVec2& vec, const CVec2<U>& from) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject this vector from the @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If the @p from vector's magnitude falls below the internal
         *       epsilon, or if either vector contains NaN components, rejection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedFloatCVec2<T, U>.
         * @note If @p from is normalized, use @ref safeRejectNorm as it is a faster implementation for unit vectors.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] from The vector to reject from.
         *
         * @return The perpendicular @ref CVec2 component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedFloatCVec2<T, U> safeReject(const CVec2<U>& from) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject this vector from the **unit** @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, rejection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedCVec2<T, U>.
         * @note Only use this method if @p from is normalized. If not, use @ref safeReject.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] from The vector to reject from.
         *
         * @return The perpendicular @ref CVec2 component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedCVec2<T, U> safeRejectNorm(const CVec2<U>& from) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject the @p Vec vector from the @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If the @p from vector's magnitude falls below the internal
         *       epsilon, or if either vector contains NaN components, rejection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedFloatCVec2<T, U>.
         * @note If @p from is normalized, use @ref safeRejectNorm as it is a faster implementation for unit vectors.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec  The vector to reject.
         * @param[in] from The vector to reject from.
         *
         * @return The perpendicular @ref CVec2 component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedFloatCVec2<T, U> safeReject(const CVec2& vec,
                                                                           const CVec2<U>& from) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject the @p Vec vector from the **unit** @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, rejection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedCVec2<T, U>.
         * @note Only use this method if @p from is normalized. If not, use @ref safeReject.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec  The vector to reject.
         * @param[in] from The vector to reject from.
         *
         * @return The perpendicular @ref CVec2 component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedCVec2<T, U> safeRejectNorm(const CVec2& vec,
                                                                          const CVec2<U>& from) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject this vector from the @p from vector and set @p status to the result of rejection operation.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If the @p from vector's magnitude falls below the internal
         *       epsilon, or if either vector contains NaN components, rejection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedFloatCVec2<T, U>.
         * @note If @p from is normalized, use @ref tryRejectNorm as it is a faster implementation for unit vectors.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] from    The vector to reject from
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The perpendicular @ref CVec2 component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedFloatCVec2<T, U> tryReject(const CVec2<U>& from,
                                                                   OperationStatus& status) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject this vector from the **unit** @p from vector and set @p status to the result of
         *        rejection operation.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, rejection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedCVec2<T, U>.
         * @note Only use this method if @p from is normalized. If not, use @ref tryReject.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] from    The vector to reject from
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The perpendicular @ref CVec2 component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedCVec2<T, U> tryRejectNorm(const CVec2<U>& from,
                                                                  OperationStatus& status) const noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject the @p Vec vector from the @p from vector and set @p status to the result of
         *        rejection operation.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If the @p from vector's magnitude falls below the internal
         *       epsilon, or if either vector contains NaN components, rejection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedFloatCVec2<T, U>.
         * @note If @p from is normalized, use @ref tryRejectNorm as it is a faster implementation for unit vectors.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec     The vector to reject.
         * @param[in] from    The vector to reject from.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The perpendicular @ref CVec2 component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedFloatCVec2<T, U> tryReject(const CVec2& vec, const CVec2<U>& from,
                                                                          OperationStatus& status) noexcept
            requires StrictArithmetic<T>;


        /**
         * @brief Reject the @p Vec vector from the **unit** @p from vector.
         *        \f$ \text{rej}_{\mathbf{b}} \mathbf{a} = \mathbf{a} - \text{proj}_{\mathbf{b}} \mathbf{a} \f$
         *
         * @note This is a safe operation. If either vector contains NaN components, rejection is bypassed.
         * @note Promotes the result to the wider type using @ref PromotedCVec2<T, U>.
         * @note Only use this method if @p from is normalized. If not, use @ref tryReject.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vec     The vector to reject.
         * @param[in] from    The vector to reject from.
         * @param[out] status The status flag to store the status of the current operation result.
         *                    For details on status codes see @ref OperationStatus.
         *
         * @return The perpendicular @ref CVec2 component or a zero-vector if projected onto a zero-length vector
         *         or if either of the vectors has NaN(Not-a-Number) component(s).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] static constexpr PromotedCVec2<T, U> tryRejectNorm(const CVec2& vec, const CVec2<U>& from,
                                                                         OperationStatus& status) noexcept
            requires StrictArithmetic<T>;

        /** @} */


        /**
         * @addtogroup FALCON_CVec2_Utils
         * @{
         */

        /**
         * @brief Check if any component of this vector is an IEEE 754 infinity.
         *
         * @note Always return false for integral types.
         *
         * @return True if at least one component is positive or negative infinity.
         */
        [[nodiscard]] constexpr bool hasInf() const noexcept;


        /**
         * @brief Check if any component of a vector is an IEEE 754 infinity.
         *
         * @note Always return false for integral types.
         *
         * @param[in] vec The vector to evaluate for indefinite components.
         *
         * @return True if at least one component is positive or negative infinity.
         */
        [[nodiscard]] static constexpr bool hasInf(const CVec2& vec) noexcept;


        /**
         * @brief Check if any component of this vector is an IEEE NaN(Not-a-Number).
         *
         * @note Always return false for integral types.
         *
         * @return True if at least one component is NaN.
         */
        [[nodiscard]] constexpr bool hasNaN() const noexcept;


        /**
         * @brief Check if any component of this vector is an IEEE NaN(Not-a-Number).
         *
         * @note Always return false for integral types.
         *
         * @param[in] vec The vector to evaluate for indefinite components.
         *
         * @return True if at least one component is NaN.
         */
        [[nodiscard]] static constexpr bool hasNaN(const CVec2& vec) noexcept;

        /** @} */


        /**
         * @addtogroup FALCON_CVec2_Log
         * @{
         */

        /**
         * @brief Write the vector to an output stream.
         *        Format the vector as <x, y> string representation for debugging or logging.
         *
         * @param os     The output stream to write to.
         * @param vector The vector to be streamed.
         *
         * @return A reference to the output stream @p os.
         */
        friend std::ostream& operator<<(std::ostream& os, const CVec2& vector)
        {
            const std::streamsize oldPrecision     = os.precision();
            const std::ios_base::fmtflags oldFlags = os.flags();

            auto precision = Config::useFullPrecision
                ? std::is_same_v<T, double> ? Config::DOUBLE_PRECISION : Config::FLOAT_PRECISION
                : Config::LOG_PRECISION;
            os << std::setprecision(precision) << std::fixed;
            os << "<" << vector[0] << ", " << vector[1] << ">\n";

            os.precision(oldPrecision);
            os.flags(oldFlags);

            return os;
        }

        /** @} */

        /**
         * @addtogroup FALCON_CVec2_Const
         * @{
         */

        /*************************************
         *                                   *
         *            CONSTANTS              *
         *                                   *
         *************************************/

        // NOLINTBEGIN

        /**
         * @brief A 2D vector with all components set to one (1, 1).
         */
        static constexpr CVec2 one()
            requires StrictArithmetic<T>
        { return CVec2{ T(1), T(1) }; }


        /**
         * @brief A 2D vector with all components set to zero (0, 0).
         */
        static constexpr CVec2 zero()
            requires StrictArithmetic<T>
        { return CVec2{ T(0), T(0) }; }


        /**
         * @brief A 2D vector with all components set to positive infinity.
         *
         * @note Constrained to floating point types.
         */
        static constexpr CVec2 inf()
            requires std::floating_point<T>
        { return CVec2{ T(constants::INFINITY_D), T(constants::INFINITY_D) }; }


        /**
         * @brief A 2D vector with all components set to negative infinity.
         *
         * @note Constrained to floating point types.
         */
        static constexpr CVec2 infNeg()
            requires std::floating_point<T>
        { return CVec2{ T(-constants::INFINITY_D), T(-constants::INFINITY_D) }; }


        /**
         * @brief A 2D vector with all components set to Not-A-Number (NaN).
         *
         * @note Constrained to floating point types.
         */
        static constexpr CVec2 qnan()
            requires std::floating_point<T>
        { return CVec2{ T(constants::NaN_D), T(constants::NaN_D) }; }


        /**
         * @brief A 2D unit vector aligned with the positive X-axis (1, 0).
         *
         * @note Constrained to signed types.
         */
        static constexpr CVec2 right()
            requires std::is_signed_v<T>
        { return CVec2{ T(1), T(0) }; }


        /**
         * @brief A 2D unit vector aligned with the negative X-axis (-1, 0).
         *
         * @note Constrained to signed types.
         */
        static constexpr CVec2 left()
            requires std::is_signed_v<T>
        { return CVec2{ T(-1), T(0) }; }


        /**
         * @brief A 2D unit vector aligned with the positive Y-axis (0, 1).
         *
         * @note Constrained to signed types.
         */
        static constexpr CVec2 up()
            requires std::is_signed_v<T>
        { return CVec2{ T(0), T(1) }; }


        /**
         * @brief A 2D unit vector aligned with the negative Y-axis (0, -1).
         *
         * @note Constrained to signed types.
         */
        static constexpr CVec2 down()
            requires std::is_signed_v<T>
        { return CVec2{ T(0), T(-1) }; }

        // NOLINTEND

        /** @} */

        /// Vec2 is declared a friend to enable toCVec2 to directly usage the buffer of CVec2,
        /// without writing to a temporary.
        friend struct Vec2<T>;

    private:
        std::array<T, DIMENSION> _data;
    };

    /*************************************
     *                                   *
     *       NON-MEMBER FUNCTIONS        *
     *                                   *
     *************************************/

    /**
     * @addtogroup FALCON_CVec2_Arithmetic
     * @{
     */

    /**
     * @brief Scale the vector by a scalar value.
     *        Multiply @p scalar by each component of the vector and returns a new vector.
     *
     * @note Promotes the result to the wider type using @ref PromotedCVec2<T, S>.
     * @note Operation is restricted to numeric types via @ref StrictArithmetic.
     *
     * @tparam S Numeric type of the scalar. Must satisfy @ref StrictArithmetic.
     *
     * @param[in] scalar The value to scale by.
     * @param[in] vector The vector to scale[RHS].
     *
     * @return A new @ref CVec2 scaled by @p scalar.
     */
    template <StrictArithmetic T, StrictArithmetic S>
    [[nodiscard]] constexpr PromotedCVec2<T, S> operator*(S scalar, const CVec2<T>& vector) noexcept
        requires StrictArithmetic<T>;

    /** @} */


    /**
     * @addtogroup FALCON_CVec2_Alias
     * @{
     */

    /*************************************
     *                                   *
     *             ALIASES               *
     *                                   *
     *************************************/

    using CVec2B   = CVec2<int8_t>;   ///< Signed Byte (8-bit) vector
    using CVec2UB  = CVec2<uint8_t>;  ///< Unsigned Byte (8-bit) vector
    using CVec2I   = CVec2<int32_t>;  ///< Signed Int (32-bit) vector
    using CVec2U   = CVec2<uint32_t>; ///< Unsigned Int (32-bit) vector
    using CVec2F   = CVec2<float>;    ///< Single Precision Floating Point (32-bit) vector
    using CVec2LL  = CVec2<int64_t>;  ///< Signed Long Long (64-bit) vector
    using CVec2D   = CVec2<double>;   ///< Double Precision Floating Point (64-bit) vector
    using CVec2ULL = CVec2<uint64_t>; ///< Unsigned Long Long (64-bit) vector

    /** @} */


    /** @brief Template deduction guide for CVec2 */
    template <typename T>
        requires Arithmetic<T>
    CVec2(T, T) -> CVec2<T>;

} // namespace flcn


#include "CVec2.tpp"
