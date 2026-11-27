#pragma once
/**
 * @file Math.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 26, 2026
 *
 * @brief Implementation of member functions declared in Math.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Preprocessors.h"

#include <bit>
#include <cmath>
#include <type_traits>

namespace flcn
{
    template <Arithmetic T>
    FALCON_INLINE constexpr bool isNaN(T num) noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            if (std::is_constant_evaluated())
            {
                // noinspection CppEqualOperandsInBinaryExpression
                return num != num; // NOLINT
            }
            return std::isnan(num);
        }
        else
        {
            return false;
        }
    }


    template <StrictArithmetic T>
    FALCON_INLINE constexpr T abs(T num) noexcept
    {
        // Return the number, if it's an unsigned number.
        if constexpr (std::is_unsigned_v<T>)
        {
            return num;
        }
        // Else proceed to taking absolute values
        else
        {
            if (std::is_constant_evaluated())
            {

                if constexpr (std::is_floating_point_v<T>)
                {
                    // In MSVC, taking abs with NaN returns wrong results, so an explicit check is required.
                    // #ifdef _MSC_VER
                    //                if (flcn::isnan(num))
                    //                    return num;
                    // #endif
                    if constexpr (sizeof(T) == 4)
                    {
                        auto bits = std::bit_cast<std::uint32_t>(num);
                        return std::bit_cast<T>(bits & 0x7FFFFFFFu);
                    }
                    else if constexpr (sizeof(T) == 8)
                    {
                        auto bits = std::bit_cast<std::uint64_t>(num);
                        return std::bit_cast<T>(bits & 0x7FFFFFFFFFFFFFFFull);
                    }
                    else
                    {
                        return num < T(0) ? -num : num;
                    }
                }
                else
                {
                    return num < T(0) ? -num : num;
                }
            }
            else
            {
                if constexpr (std::is_floating_point_v<T>)
                {
                    return static_cast<T>(std::fabs(num));
                }
                else
                {
                    return static_cast<T>(std::abs(num));
                }
            }
        }
    }

    template <Arithmetic T>
    FALCON_INLINE constexpr bool isInf(T num) noexcept
    {
        if (std::is_constant_evaluated())
        {
            if constexpr (std::numeric_limits<T>::has_infinity)
            {
                return std::numeric_limits<T>::infinity() == num || -std::numeric_limits<T>::infinity() == num;
            }
            else
            {
                return false;
            }
        }
        return std::isinf(num);
    }


    template <Arithmetic T, Arithmetic U>
    FALCON_INLINE constexpr PromotedValue_t<T, U> diffAbs(T lhs, U rhs) noexcept
    {
        // Only one side of the expression is evaluated to a non-zero number.
        // So, if either side of + underflows, it will be canceled out by the boolean expression.
        return PromotedValue_t<T, U>((lhs - rhs) * (lhs >= rhs) + (rhs - lhs) * (lhs < rhs));
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool compareEq(const T a, const T b) noexcept
    {
        if constexpr (std::integral<T>)
        {
            return a == b;
        }
        else
        {
            return flcn::abs(a - b) <= std::numeric_limits<T>::epsilon() * std::max(flcn::abs(a), flcn::abs(b));
        }
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr T min(const T& a, const T& b) noexcept
    {
        // std::min is constexpr from c++14 the library provides only a no-cost wrapper abstraction
        return std::min(a, b);
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr T min(std::initializer_list<T> iList) noexcept
    {
        // std::min is constexpr from c++14.
        return std::min(iList);
    }


    // template <Arithmetic T>
    // constexpr Magnitude<T> sqrt(T num, double epsilon) noexcept
    //{
    //     if (std::is_constant_evaluated())
    //     {
    //         // Compile time evaluation
    //         using R = Magnitude<T>;

    //        const R fpNum = static_cast<R>(num);
    //        R guess    = fpNum / 2; // Initial guess num / 2.

    //        while (guess * guess - fpNum > epsilon)
    //        {
    //            guess = guess - ((guess * guess - num) / (2 * guess));
    //        }
    //        return guess;
    //    }
    //    else
    //    {
    //        return static_cast<Magnitude<T>>(std::sqrt(num));
    //    }
    //}

} // namespace flcn
