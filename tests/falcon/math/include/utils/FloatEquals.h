#pragma once

#include <algorithm>
#include <cmath>
#include <limits>
// TODO: Refactor to macro/update naming


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
constexpr bool COMPARE_EQ(const T a, const T b) noexcept
{
    if constexpr (std::integral<T>)
    {
        return a == b;
    }
    else
    {
        return std::abs(a - b) <= std::numeric_limits<T>::epsilon() * std::max(std::abs(a), std::abs(b));
    }
}
