#pragma once
/**
 * @file Simd256ScalarMath.inl
 * @author Alan Abraham P Kochumon
 * @date Created on: November 18, 2026
 *
 * @brief Implementation of function declared in Simd256ScalarMath.h.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


namespace flcn
{
    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr details::Reg256Scalar<DataType, Lane> min(details::Reg256Scalar<DataType, Lane> a,
                                                                      details::Reg256Scalar<DataType, Lane> b) noexcept
    {
        details::Reg256Scalar<DataType, Lane> retReg{};
        for (size_t i = 0; i < Lane; ++i)
        {
            retReg.setAt(i, std::min((*a)[i], (*b)[i]));
        }
        return retReg;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr details::Reg256Scalar<DataType, Lane> max(details::Reg256Scalar<DataType, Lane> a,
                                                                      details::Reg256Scalar<DataType, Lane> b) noexcept
    {
        details::Reg256Scalar<DataType, Lane> retReg{};
        for (size_t i = 0; i < Lane; ++i)
        {
            retReg.setAt(i, std::max((*a)[i], (*b)[i]));
        }
        return retReg;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr details::Reg256Scalar<DataType, Lane> abs(
        details::Reg256Scalar<DataType, Lane> reg) noexcept
    { return reg.abs(); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr details::Reg256Scalar<DataType, Lane> sqrt(
        details::Reg256Scalar<DataType, Lane> reg) noexcept
    { return reg.sqrt(); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr details::Reg256Scalar<DataType, Lane> fma(details::Reg256Scalar<DataType, Lane> a,
                                                                      details::Reg256Scalar<DataType, Lane> b,
                                                                      details::Reg256Scalar<DataType, Lane> c) noexcept
    { return a.fma(b, c); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr details::Reg256Scalar<DataType, Lane> fmSub(
        details::Reg256Scalar<DataType, Lane> a, details::Reg256Scalar<DataType, Lane> b,
        details::Reg256Scalar<DataType, Lane> c) noexcept
    { return a.fmSub(b, c); }

} // namespace flcn
