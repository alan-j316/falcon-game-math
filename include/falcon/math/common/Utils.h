#pragma once
/**
 * @file Utils.h
 * @author Alan Abraham P Kochumon
 * @date Created on: May 28, 2026
 *
 * @brief FALCON Helper and Utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Config.h"
#include "MathTraits.h"

namespace flcn::utils
{

    /**
     * @addtogroup FALCON_Utils
     * @{
     */

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
     * @param a The first operand.
     * @param b The second operand.
     *
     * @return A boolean whether the values are equal.
     */
    template <typename T>
        requires std::floating_point<T> || std::integral<T>
    constexpr bool compareEq(T a, T b) noexcept;



    /**
     * @brief Compute the square root of a number.
     * TODO: Move to Wrappers.h
     * @note Wrapper around the `std::sqrt` function with Newton-Raphson approximation for compile time evaluation.
     *
     * @tparam T Numeric type of the number. Must satisfy @ref StrictArithmetic.
     *
     * @param num     The number to take the square root of.
     * @param epsilon The precision required for the square-root.
     *                Default to falcon EPSILON.
     *
     * @return The square root of a number promoted to the near floating point type.
     */
    // template <Arithmetic T>
    // constexpr Magnitude<T> sqrt(T num, double epsilon = Config::EPSILON<Magnitude<T>>) noexcept;

    /** @} */

} // namespace flcn::utils


#include "Utils.tpp"
