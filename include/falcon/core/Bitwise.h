#pragma once
/**
 * @file Bitwise.h
 * @author Alan Abraham P Kochumon
 * @date Created on: November 23, 2026
 *
 * @brief Bitwise operations.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include <bit>
#include <type_traits>

// TODO: Add test for isEqualBitwise and remove form test helper
namespace flcn
{

    /**
     * @brief Perform a bitwise equality among the operands.
     * @tparam T The numeric type of the values.
     * @param a The first operand.
     * @param b The second operand.
     * @return True if both the operands are bitwise equal.
     * @return False otherwise.
     */
    template <typename T>
    constexpr bool bitEq(T a, T b)
    {
        if constexpr (std::is_same_v<T, double>)
        {
            return std::bit_cast<uint64_t>(a) == std::bit_cast<uint64_t>(b);
        }
        else if constexpr (std::is_same_v<T, float>)
        {
            return std::bit_cast<uint32_t>(a) == std::bit_cast<uint32_t>(b);
        }
        else
        {
            return a == b;
        }
    }
} // namespace flcn
