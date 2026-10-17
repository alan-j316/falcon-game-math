#pragma once
/**
 * @file Simd256X86Math.inl
 * @author Alan Abraham P Kochumon
 * @date Created on: September 29, 2026
 *
 * @brief Binary non-arithmetic math operations including min, max, etc.
 *
 * @note This header should not be directly included. Include SIMD256 will include the correct header file.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


namespace flcn
{
    /// +=============================================================================================================+
    /// |                                             SSE(EMULATED)                                                   |
    /// +=============================================================================================================+

    template <typename DataType, size_t Lane>
    using _REG_256_SSE = Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>;

    /**
     * @brief Get the minimum values from both the registers, packed into a single register.
     *
     * @tparam DataType The data type of the Simd256 register.
     * @tparam Lane     The number of lanes of the Simd256 register.
     *
     * @param a The first register.
     * @param b The second register.
     *
     * @return A Simd256 register with minimum values taken from both the registers.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr _REG_256_SSE<DataType, Lane> min(_REG_256_SSE<DataType, Lane> a,
                                                             _REG_256_SSE<DataType, Lane> b) noexcept;


    /**
     * @brief Get the maximum values from both the registers, packed into a single register.
     *
     * @tparam DataType The data type of the Simd256 register.
     * @tparam Lane     The number of lanes of the Simd256 register.
     *
     * @param a The first register.
     * @param b The second register.
     *
     * @return A Simd256 register with maximum values taken from both the registers.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr _REG_256_SSE<DataType, Lane> max(_REG_256_SSE<DataType, Lane> a,
                                                             _REG_256_SSE<DataType, Lane> b) noexcept;


    /**
     * @brief Compute the absolute value of each entry in the register.
     *
     * @note For unsigned types the value will not be affected.
     *
     * @tparam DataType The data type of the Simd256 register.
     * @tparam Lane     The number of lanes of the Simd256 register.
     *
     * @param reg The register.
     *
     * @return A Simd256 register with absolute values.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr _REG_256_SSE<DataType, Lane> abs(_REG_256_SSE<DataType, Lane> reg) noexcept;


    /**
     * @brief Compute the square root of each entry in the register.
     *
     * @note For integral square roots less than zero, this will generate a zero value.
     *       For floating-point number, the function follow standard behavior of returning a NaN for negatives.
     *
     * @tparam DataType The data type of the Simd256 register.
     * @tparam Lane     The number of lanes of the Simd256 register.
     *
     * @param reg The register.
     *
     * @return A Simd256 register with square root of each entry.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr _REG_256_SSE<DataType, Lane> sqrt(_REG_256_SSE<DataType, Lane> reg) noexcept;



    /// +=============================================================================================================+
    /// |                                                 AVX                                                         |
    /// +=============================================================================================================+

    template <typename DataType, size_t Lane>
    using _REG_256_AVX = Simd256<SimdBackend::ARCH_AVX, DataType, Lane>;

    /**
     * @brief Get the minimum values from both the registers, packed into a single register.
     *
     * @tparam DataType The data type of the Simd256 register.
     * @tparam Lane     The number of lanes of the Simd256 register.
     *
     * @param a The first register.
     * @param b The second register.
     *
     * @return A Simd256 register with minimum values taken from both the registers.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr _REG_256_AVX<DataType, Lane> min(_REG_256_AVX<DataType, Lane> a,
                                                             _REG_256_AVX<DataType, Lane> b) noexcept;


    /**
     * @brief Get the maximum values from both the registers, packed into a single register.
     *
     * @tparam DataType The data type of the Simd256 register.
     * @tparam Lane     The number of lanes of the Simd256 register.
     *
     * @param a The first register.
     * @param b The second register.
     *
     * @return A Simd256 register with maximum values taken from both the registers.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr _REG_256_AVX<DataType, Lane> max(_REG_256_AVX<DataType, Lane> a,
                                                             _REG_256_AVX<DataType, Lane> b) noexcept;


} // namespace flcn

#include "Simd256X86Math.inl"
