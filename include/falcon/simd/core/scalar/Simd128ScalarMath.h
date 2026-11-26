#pragma once
/**
 * @file Simd128ScalarMath.inl
 * @author Alan Abraham P Kochumon
 * @date Created on: November 18, 2026
 *
 * @brief Binary non-arithmetic math operations including min, max, etc.
 *
 * @note This header should not be directly included. Include SIMD128 will include the correct header file.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


namespace flcn
{
    namespace details
    {
        template <typename DataType, size_t Lane>
        using Reg128Scalar = Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>;
    }

    /**
     * @brief Get the minimum values from both the registers, packed into a single register.
     *
     * @tparam DataType The data type of the Simd128 register.
     * @tparam Lane     The number of lanes of the Simd128 register.
     *
     * @param[in] a The first register.
     * @param[in] b The second register.
     *
     * @return A Simd128 register with minimum values taken from both the registers.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr details::Reg128Scalar<DataType, Lane> min(details::Reg128Scalar<DataType, Lane> a,
                                                                      details::Reg128Scalar<DataType, Lane> b) noexcept;


    /**
     * @brief Get the maximum values from both the registers, packed into a single register.
     *
     * @tparam DataType The data type of the Simd128 register.
     * @tparam Lane     The number of lanes of the Simd128 register.
     *
     * @param[in] a The first register.
     * @param[in] b The second register.
     *
     * @return A Simd128 register with maximum values taken from both the registers.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr details::Reg128Scalar<DataType, Lane> max(details::Reg128Scalar<DataType, Lane> a,
                                                                      details::Reg128Scalar<DataType, Lane> b) noexcept;


    /**
     * @brief Compute the absolute value of each entry in the register.
     *
     * @note For unsigned types the value will not be affected.
     *
     * @tparam DataType The data type of the Simd128 register.
     * @tparam Lane     The number of lanes of the Simd128 register.
     *
     * @param[in] reg The register.
     *
     * @return A Simd128 register with absolute values.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr details::Reg128Scalar<DataType, Lane> abs(
        details::Reg128Scalar<DataType, Lane> reg) noexcept;


    /**
     * @brief Compute the square root of each entry in the register.
     *
     * @note For integral square roots less than zero, this will generate a zero value.
     *       For floating-point number, the function follow standard behavior of returning a NaN for negatives.
     *
     * @tparam DataType The data type of the Simd128 register.
     * @tparam Lane     The number of lanes of the Simd128 register.
     *
     * @param[in] reg The register.
     *
     * @return A Simd128 register with square root of each entry.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr details::Reg128Scalar<DataType, Lane> sqrt(
        details::Reg128Scalar<DataType, Lane> reg) noexcept;


    /**
     * @brief Perform a fused multiply and add (a * b + c).
     *
     * @note Register arithmetic is limited to same data types and lanes.
     * @param[in] a The register containing the multiplicand.
     * @param[in] b The register containing the multiplier.
     * @param[in] c The register containing the addend.
     *
     * @return A new register with the fused-multiply add result.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr details::Reg128Scalar<DataType, Lane> fma(details::Reg128Scalar<DataType, Lane> a,
                                                                      details::Reg128Scalar<DataType, Lane> b,
                                                                      details::Reg128Scalar<DataType, Lane> c) noexcept;


    /**
     * @brief Perform a fused multiply and subtract (this * b - c).
     *
     * @note Register arithmetic is limited to same data types and lanes.
     * @param[in] a The register containing the multiplicand.
     * @param[in] b The register containing the multiplier.
     * @param[in] c The register containing the subtrahend.
     *
     * @return A new register with the fused-multiply subtraction result.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr details::Reg128Scalar<DataType, Lane> fmSub(
        details::Reg128Scalar<DataType, Lane> a, details::Reg128Scalar<DataType, Lane> b,
        details::Reg128Scalar<DataType, Lane> c) noexcept;

} // namespace flcn

#include "Simd128ScalarMath.inl"
