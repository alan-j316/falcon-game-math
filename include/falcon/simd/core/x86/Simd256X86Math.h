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

    namespace details
    {
        
        template <typename DataType, size_t Lane>
        using Reg256SSE = details::Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>;
    }

    /**
     * @brief Get the minimum values from both the registers, packed into a single register.
     *
     * @tparam DataType The data type of the Simd256 register.
     * @tparam Lane     The number of lanes of the Simd256 register.
     *
     * @param[in] a The first register.
     * @param[in] b The second register.
     *
     * @return A Simd256 register with minimum values taken from both the registers.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr details::Reg256SSE<DataType, Lane> min(details::Reg256SSE<DataType, Lane> a,
                                                             details::Reg256SSE<DataType, Lane> b) noexcept;


    /**
     * @brief Get the maximum values from both the registers, packed into a single register.
     *
     * @tparam DataType The data type of the Simd256 register.
     * @tparam Lane     The number of lanes of the Simd256 register.
     *
     * @param[in] a The first register.
     * @param[in] b The second register.
     *
     * @return A Simd256 register with maximum values taken from both the registers.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr details::Reg256SSE<DataType, Lane> max(details::Reg256SSE<DataType, Lane> a,
                                                             details::Reg256SSE<DataType, Lane> b) noexcept;


    /**
     * @brief Compute the absolute value of each entry in the register.
     *
     * @note For unsigned types the value will not be affected.
     *
     * @tparam DataType The data type of the Simd256 register.
     * @tparam Lane     The number of lanes of the Simd256 register.
     *
     * @param[in] reg The register.
     *
     * @return A Simd256 register with absolute values.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr details::Reg256SSE<DataType, Lane> abs(details::Reg256SSE<DataType, Lane> reg) noexcept;


    /**
     * @brief Compute the square root of each entry in the register.
     *
     * @note For integral square roots less than zero, this will generate a zero value.
     *       For floating-point number, the function follow standard behavior of returning a NaN for negatives.
     *
     * @tparam DataType The data type of the Simd256 register.
     * @tparam Lane     The number of lanes of the Simd256 register.
     *
     * @param[in] reg The register.
     *
     * @return A Simd256 register with square root of each entry.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr details::Reg256SSE<DataType, Lane> sqrt(details::Reg256SSE<DataType, Lane> reg) noexcept;


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
    [[nodiscard]] constexpr details::Reg256SSE<DataType, Lane> fma(details::Reg256SSE<DataType, Lane> a,
                                                             details::Reg256SSE<DataType, Lane> b,
                                                             details::Reg256SSE<DataType, Lane> c) noexcept;


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
    [[nodiscard]] constexpr details::Reg256SSE<DataType, Lane> fmSub(details::Reg256SSE<DataType, Lane> a,
                                                               details::Reg256SSE<DataType, Lane> b,
                                                               details::Reg256SSE<DataType, Lane> c) noexcept;



    /// +=============================================================================================================+
    /// |                                                 AVX                                                         |
    /// +=============================================================================================================+

    namespace details
    {
        template <typename DataType, size_t Lane>
        using Reg256AVX = details::Simd256<SimdBackend::ARCH_AVX, DataType, Lane>;
    }

    /**
     * @brief Get the minimum values from both the registers, packed into a single register.
     *
     * @tparam DataType The data type of the Simd256 register.
     * @tparam Lane     The number of lanes of the Simd256 register.
     *
     * @param[in] a The first register.
     * @param[in] b The second register.
     *
     * @return A Simd256 register with minimum values taken from both the registers.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr details::Reg256AVX<DataType, Lane> min(details::Reg256AVX<DataType, Lane> a,
                                                             details::Reg256AVX<DataType, Lane> b) noexcept;


    /**
     * @brief Get the maximum values from both the registers, packed into a single register.
     *
     * @tparam DataType The data type of the Simd256 register.
     * @tparam Lane     The number of lanes of the Simd256 register.
     *
     * @param[in] a The first register.
     * @param[in] b The second register.
     *
     * @return A Simd256 register with maximum values taken from both the registers.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr details::Reg256AVX<DataType, Lane> max(details::Reg256AVX<DataType, Lane> a,
                                                             details::Reg256AVX<DataType, Lane> b) noexcept;


    /**
     * @brief Compute the absolute value of each entry in the register.
     *
     * @note For unsigned types the value will not be affected.
     *
     * @tparam DataType The data type of the Simd256 register.
     * @tparam Lane     The number of lanes of the Simd256 register.
     *
     * @param[in] reg The register.
     *
     * @return A Simd256 register with absolute values.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr details::Reg256AVX<DataType, Lane> abs(details::Reg256AVX<DataType, Lane> reg) noexcept;


    /**
     * @brief Compute the square root of each entry in the register.
     *
     * @note For integral square roots less than zero, this will generate a zero value.
     *       For floating-point number, the function follow standard behavior of returning a NaN for negatives.
     *
     * @tparam DataType The data type of the Simd256 register.
     * @tparam Lane     The number of lanes of the Simd256 register.
     *
     * @param[in] reg The register.
     *
     * @return A Simd256 register with square root of each entry.
     */
    template <typename DataType, size_t Lane>
    [[nodiscard]] constexpr details::Reg256AVX<DataType, Lane> sqrt(details::Reg256AVX<DataType, Lane> reg) noexcept;



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
    [[nodiscard]] constexpr details::Reg256AVX<DataType, Lane> fma(details::Reg256AVX<DataType, Lane> a,
                                                             details::Reg256AVX<DataType, Lane> b,
                                                             details::Reg256AVX<DataType, Lane> c) noexcept;


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
    [[nodiscard]] constexpr details::Reg256AVX<DataType, Lane> fmSub(details::Reg256AVX<DataType, Lane> a,
                                                               details::Reg256AVX<DataType, Lane> b,
                                                               details::Reg256AVX<DataType, Lane> c) noexcept;

} // namespace flcn

#include "Simd256X86Math.inl"
