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
    FALCON_INLINE constexpr _REG_128_SCALAR<DataType, Lane> min(_REG_128_SCALAR<DataType, Lane> a,
                                                             _REG_128_SCALAR<DataType, Lane> b) noexcept
    {
        _REG_128_SCALAR<DataType, Lane> retReg{};
        for (size_t i = 0; i < Lane; ++i)
        {
            retReg._reg[i] = std::min(a._reg[i], b._reg[i]);
        }
        return retReg;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr _REG_128_SCALAR<DataType, Lane> max(_REG_128_SCALAR<DataType, Lane> a,
                                                             _REG_128_SCALAR<DataType, Lane> b) noexcept
    {
        _REG_128_SCALAR<DataType, Lane> retReg{};
        for (size_t i = 0; i < Lane; ++i)
        {
            retReg._reg[i] = std::max(a._reg[i], b._reg[i]);
        }
        return retReg;
    }
    //
    //
    //     template <typename DataType, size_t Lane>
    //     FALCON_INLINE constexpr _REG_128_SCALAR<DataType, Lane> abs(_REG_128_SCALAR<DataType, Lane> reg) noexcept
    //     { return reg.abs(); }
    //
    //
    //     template <typename DataType, size_t Lane>
    //     FALCON_INLINE constexpr _REG_128_SCALAR<DataType, Lane> sqrt(_REG_128_SCALAR<DataType, Lane> reg) noexcept
    //     { return reg.sqrt(); }
    //

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr _REG_128_SCALAR<DataType, Lane> fma(_REG_128_SCALAR<DataType, Lane> a,
                                                                _REG_128_SCALAR<DataType, Lane> b,
                                                                _REG_128_SCALAR<DataType, Lane> c) noexcept
    { return a.fma(b, c); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr _REG_128_SCALAR<DataType, Lane> fmSub(_REG_128_SCALAR<DataType, Lane> a,
                                                                  _REG_128_SCALAR<DataType, Lane> b,
                                                                  _REG_128_SCALAR<DataType, Lane> c) noexcept
    { return a.fmSub(b, c); }

} // namespace flcn
