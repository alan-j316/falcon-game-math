#pragma once
/**
 * @file Wrappers.h
 * @author Alan Abraham P Kochumon
 * @date Created on: April 20, 2026
 *
 * @brief Wrapper for C++ `std` functions, to enable constexpr evaluation in pre-C++23.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MathTraits.h"



namespace flcn
{

    /**
     * @addtogroup FALCON_Wrappers
     * @{
     */

    /**
     * @brief Compute the absolute value of an integral or floating-point value.
     *        Wrapper around the `std::abs`/`std::fabs` function, to enable constexpr evaluation in pre-C++23.
     *
     * @tparam T The numeric type of the value. Must satisfy @ref SignedStrictArithmetic.
     *
     * @param num The number to take the absolute value of.
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
     * @param num The number to check for NaN.
     *
     * @return Return the absolute value of @p value.
     */
    template <Arithmetic T>
    [[nodiscard]] constexpr bool isnan(T num) noexcept;


    /**
     * @brief Determine if a floating-point value is positive or negative infinity.
     *        Wrapper around the `std::isinf` function, to enable constexpr evaluation in pre-C++23.
     *
     * @tparam T The numeric type of the value. Must satisfy @ref Arithmetic.
     *
     * @param num The number to check for indefinite value.
     *
     * @return Return the absolute value of @p value.
     */
    template <Arithmetic T>
    [[nodiscard]] constexpr bool isinf(T num) noexcept;

    /** @} */

} // namespace flcn


#include "Wrappers.tpp"
