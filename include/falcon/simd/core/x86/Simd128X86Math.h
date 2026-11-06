#pragma once
/**
 * @file Simd128X86Math.inl
 * @author Alan Abraham P Kochumon
 * @date Created on: September 18, 2026
 *
 * @brief Binary non-arithmetic math operations including min, max, etc.
 *
 * @note This header should not be directly included. Include SIMD128 will include the correct header file.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


namespace flcn
{
    template <typename DataType, size_t Lane>
    using _REG_128_SSE = Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>;

    /**
     * @brief Get the minimum values from both the registers, packed into a single register.
     *
     * @tparam DataType The data type of the Simd128 register.
     * @tparam Lane     The number of lanes of the Simd128 register.
     *
     * @param a The first register.
     * @param b The second register.
     *
     * @return A Simd128 register with minimum values taken from both the registers.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr _REG_128_SSE<DataType, Lane> min(_REG_128_SSE<DataType, Lane> a,
                                                             _REG_128_SSE<DataType, Lane> b) noexcept;


    /**
     * @brief Get the maximum values from both the registers, packed into a single register.
     *
     * @tparam DataType The data type of the Simd128 register.
     * @tparam Lane     The number of lanes of the Simd128 register.
     *
     * @param a The first register.
     * @param b The second register.
     *
     * @return A Simd128 register with maximum values taken from both the registers.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr _REG_128_SSE<DataType, Lane> max(_REG_128_SSE<DataType, Lane> a,
                                                             _REG_128_SSE<DataType, Lane> b) noexcept;


    /**
     * @brief Compute the absolute value of each entry in the register.
     *
     * @note For unsigned types the value will not be affected.
     *
     * @tparam DataType The data type of the Simd128 register.
     * @tparam Lane     The number of lanes of the Simd128 register.
     *
     * @param reg The register.
     *
     * @return A Simd128 register with absolute values.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr _REG_128_SSE<DataType, Lane> abs(_REG_128_SSE<DataType, Lane> reg) noexcept;


    /**
     * @brief Compute the square root of each entry in the register.
     *
     * @note For integral square roots less than zero, this will generate a zero value.
     *       For floating-point number, the function follow standard behavior of returning a NaN for negatives.
     *
     * @tparam DataType The data type of the Simd128 register.
     * @tparam Lane     The number of lanes of the Simd128 register.
     *
     * @param reg The register.
     *
     * @return A Simd128 register with square root of each entry.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr _REG_128_SSE<DataType, Lane> sqrt(_REG_128_SSE<DataType, Lane> reg) noexcept;

} // namespace flcn

#include "Simd128X86Math.inl"
