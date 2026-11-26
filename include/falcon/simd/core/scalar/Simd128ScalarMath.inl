#pragma once
/**
 * @file Simd128ScalarMath.inl
 * @author Alan Abraham P Kochumon
 * @date Created on: November 18, 2026
 *
 * @brief Implementation of function declared in Simd128ScalarMath.h.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


namespace flcn
{
    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr details::Reg128Scalar<DataType, Lane> min(details::Reg128Scalar<DataType, Lane> a,
                                                                      details::Reg128Scalar<DataType, Lane> b) noexcept
    {
        details::Reg128Scalar<DataType, Lane> retReg{};
        for (size_t i = 0; i < Lane; ++i)
        {
            retReg.setAt(i, std::min((*a)[i], (*b)[i]));
        }
        return retReg;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr details::Reg128Scalar<DataType, Lane> max(details::Reg128Scalar<DataType, Lane> a,
                                                                      details::Reg128Scalar<DataType, Lane> b) noexcept
    {
        details::Reg128Scalar<DataType, Lane> retReg{};
        for (size_t i = 0; i < Lane; ++i)
        {
            retReg.setAt(i, std::max((*a)[i], (*b)[i]));
        }
        return retReg;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr details::Reg128Scalar<DataType, Lane> abs(
        details::Reg128Scalar<DataType, Lane> reg) noexcept
    { return reg.abs(); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr details::Reg128Scalar<DataType, Lane> sqrt(
        details::Reg128Scalar<DataType, Lane> reg) noexcept
    { return reg.sqrt(); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr details::Reg128Scalar<DataType, Lane> fma(details::Reg128Scalar<DataType, Lane> a,
                                                                      details::Reg128Scalar<DataType, Lane> b,
                                                                      details::Reg128Scalar<DataType, Lane> c) noexcept
    { return a.fma(b, c); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr details::Reg128Scalar<DataType, Lane> fmSub(
        details::Reg128Scalar<DataType, Lane> a, details::Reg128Scalar<DataType, Lane> b,
        details::Reg128Scalar<DataType, Lane> c) noexcept
    { return a.fmSub(b, c); }

} // namespace flcn
