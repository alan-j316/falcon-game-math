#pragma once
/**
 * @file Math.h
 * @author Alan Abraham P Kochumon
 * @date Created on: November 26, 2026
 *
 * @brief Scalar math helpers & Wrappers.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "traits/MathTraits.h"
#include <concepts>


namespace flcn
{
    // ABS, MIN, MAX, ISNAN, ISINF, SQRT, RSQRT, EXP, EXP2, LOG, LOG2, LOG10, SIN, COS, TAN, ASIN, ACOS, ATAN, ATAN2
    // CEIL, FLOOR, TRUNCATE, SIGNBIT, CLAMP,
    // template<Arithmetic

    /**
     * @brief Compute the absolute value of an integral or floating-point value.
     *        Wrapper around the `std::abs`/`std::fabs` function, to enable constexpr evaluation in pre-C++23.
     *
     * @tparam T The numeric type of the value. Must satisfy @ref SignedStrictArithmetic.
     *
     * @param[in] num The number to take the absolute value of.
     *
     * @return Return the absolute value of @p value.
     */
    template <StrictArithmetic T>
    [[nodiscard]] constexpr T abs(T num) noexcept;


    /**
     * @brief Determine if a floating-point value is a Not-a-Number(NaN) value.
     *        Wrapper around the `std::isnan` function, to enable constexpr evaluation in pre-C++23.
     *
     * @tparam T The numeric type of the value. Must satisfy @ref Arithmetic.
     *
     * @param[in] num The number to check for NaN.
     *
     * @return Return the absolute value of @p value.
     */
    template <Arithmetic T>
    [[nodiscard]] constexpr bool isNaN(T num) noexcept;


    /**
     * @brief Determine if a floating-point value is positive or negative infinity.
     *        Wrapper around the `std::isinf` function, to enable constexpr evaluation in pre-C++23.
     *
     * @tparam T The numeric type of the value. Must satisfy @ref Arithmetic.
     *
     * @param[in] num The number to check for indefinite value.
     *
     * @return Return the absolute value of @p value.
     */
    template <Arithmetic T>
    [[nodiscard]] constexpr bool isInf(T num) noexcept;


    /**
     * @brief Compute the absolute difference between two numeric values.
     *
     * @details This function calculates `|lhs - rhs|` while mathematically guaranteeing
     *          that unsigned underflow cannot occur. By evaluating the relative magnitude before
     *          subtracting, it prevents the catastrophic wrap-around that happens when subtracting
     *          a larger unsigned integer from a smaller one.
     *
     * @note This is the mandatory operation for L1/L2 distance calculations in unsigned
     *       spaces (e.g., screen coordinates or pixel buffers).
     *
     * @tparam T Numeric type of the first operand. Must satisfy @ref Arithmetic.
     * @tparam U Numeric type of the second operand. Must satisfy @ref Arithmetic.
     *
     * @param[in] lhs The first operand.
     * @param[in] rhs The second operand.
     *
     * @return The absolute difference, safely promoted to the wider of the two types.
     */
    template <Arithmetic T, Arithmetic U>
    constexpr PromotedValue_t<T, U> diffAbs(T lhs, U rhs) noexcept;


    /**
     * @brief Compare two values for equality.
     *
     * @details Compares if two numbers are equal. For floating point numbers, a relative equality
     *          based on machine epsilon is used.
     *
     * @tparam T The type of operands. Must satisfy `std::floating_point` or `std::integral`.
     *
     * @param[in] a The first operand.
     * @param[in] b The second operand.
     *
     * @return A boolean whether the values are equal.
     */
    template <typename T>
        requires std::floating_point<T> || std::integral<T>
    constexpr bool compareEq(T a, T b) noexcept;

    /**
 * @brief Compute the square root of a number.
 *
 * @note Wrapper around the `std::sqrt` function with Newton-Raphson approximation for compile time evaluation.
 *
 * @tparam T Numeric type of the number. Must satisfy @ref StrictArithmetic.
 *
 * @param[in] num     The number to take the square root of.
 * @param[in] epsilon The precision required for the square-root.
 *                Default to falcon EPSILON.
 *
 * @return The square root of a number promoted to the near floating point type.
 */
    // template <Arithmetic T>
    // constexpr Magnitude<T> sqrt(T num, double epsilon = Config::EPSILON<Magnitude<T>>) noexcept;
} // namespace flcn

#include "Math.tpp"
