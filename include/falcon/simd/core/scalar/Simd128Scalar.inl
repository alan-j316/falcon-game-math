#pragma once
/**
 * @file Simd128Scalar.inl
 * @author Alan Abraham P Kochumon
 * @date Created on: November 18, 2026
 *
 * @brief Implementation of templated functions declared in Simd128SSE.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <falcon/core/Bitwise.h>
#include <falcon/core/Constants.h>

#include <bit>
#include <cmath>

namespace flcn::details
{

    /// +---------------------------------------------------------------------------------------+
    /// |                                INITIALIZATION                                         |
    /// +---------------------------------------------------------------------------------------+

    template <typename DataType, size_t Lane>
    template <typename... Args>
        requires(SimdSafeConvertible<Args, DataType> && ...)
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::Simd128(Args... data) noexcept
    {
        // If 1 argument broadcast, else load into the array.
        if constexpr (sizeof...(Args) == 1)
        {
            broadcast(static_cast<DataType>(data)...);
        }
        else
        {
            set(static_cast<DataType>(data)...);
        }
    }


    template <typename DataType, size_t Lane>
    template <typename T>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, T, Lane> Simd128<SimdBackend::ARCH_UNKNOWN, DataType,
                                                                                Lane>::cast() const noexcept
    {
        if constexpr (std::is_same_v<T, DataType>)
        {
            return *this;
        }
        else
        {
            Simd128<SimdBackend::ARCH_UNKNOWN, T, Lane> retReg;
            for (size_t i = 0; i < Lane; ++i)
            {
                retReg._reg[i] = static_cast<T>(_reg[i]);
            }
            return retReg;
        }
    }


    template <typename DataType, size_t Lane>
    template <typename T>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, T, Lane> Simd128<SimdBackend::ARCH_UNKNOWN, DataType,
                                                                                Lane>::cast() noexcept
    {
        if constexpr (std::is_same_v<T, DataType>)
        {
            return *this;
        }
        else
        {
            Simd128<SimdBackend::ARCH_UNKNOWN, T, Lane> retReg;
            for (size_t i = 0; i < Lane; ++i)
            {
                retReg._reg[i] = static_cast<T>(_reg[i]);
            }
            return retReg;
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::Simd128(
        std::span<const DataType> values) noexcept
    { _reg = std::to_array(values); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::Simd128(const DataType* pBuffer) noexcept
    { std::copy_n(pBuffer, Lane, _reg.begin()); }


    template <typename DataType, size_t Lane>
    template <typename... Args>
        requires(sizeof...(Args) <= Lane) && (std::same_as<Args, DataType> && ...)
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>& Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::set(Args... args)
    {
        _reg = std::array<DataType, Lane>{ args... };
        return *this;
    }


    template <typename DataType, size_t Lane>
    template <typename DataType2>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::Simd128(
        const Simd128<SimdBackend::ARCH_UNKNOWN, DataType2, Lane>& other)
    { *this = cast<DataType>(other); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::setZero() noexcept
    { _reg.fill(0); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::setOne() noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            _reg.fill(std::bit_cast<double>(~0ULL));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            _reg.fill(std::bit_cast<float>(~0U));
        }
        else
        {
            _reg.fill(static_cast<DataType>(~0ULL));
        }
    }



    /// +---------------------------------------------------------------------------------------+
    /// |                                LOAD AND STORE                                         |
    /// +---------------------------------------------------------------------------------------+

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::loadAligned(
        const DataType* pData) noexcept
    {
        // TODO: Add death tests
        FALCON_ASSERT_MSG(
            (reinterpret_cast<uintptr_t>(pData) & (ALIGNMENT - 1)) == 0,
            "[Falcon Simd]: Loading from unaligned memory when aligned address was expected. Use load() instead.");
        std::copy_n(pData, Lane, _reg.begin());
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::load(const DataType* pData) noexcept
    { std::copy_n(pData, Lane, _reg.begin()); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::broadcast(DataType value) noexcept
    { _reg.fill(value); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::store(
        DataType* pBuffer) const noexcept
    { std::copy_n(_reg.begin(), Lane, pBuffer); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::storeAligned(
        DataType* pBuffer) const noexcept
    {
        FALCON_ASSERT_MSG(
            (reinterpret_cast<uintptr_t>(pBuffer) & (ALIGNMENT - 1)) == 0,
            "[Falcon Simd]: Storing to unaligned memory when a aligned one was expected. Use store() instead.");
        std::copy_n(_reg.begin(), Lane, pBuffer);
    }



    /// +---------------------------------------------------------------------------------------+
    /// |                                    SET/GET                                            |
    /// +---------------------------------------------------------------------------------------+

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::getAt(
        size_t index) const noexcept
    { return _reg[index]; }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::setAt(size_t index,
                                                                                           DataType value) noexcept
    { _reg[index] = value; }


    template <typename DataType, size_t Lane>
    template <size_t Index>
        requires(Index < Lane)
    FALCON_INLINE constexpr DataType Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::getAt() const noexcept
    { return _reg[Index]; }


    template <typename DataType, size_t Lane>
    template <size_t Index>
        requires(Index < Lane)
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::setAt(DataType value) noexcept
    { _reg[Index] = value; }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::extractFirst() noexcept
    { return _reg[0]; }



    /// +---------------------------------------------------------------------------------------+
    /// |                              BITWISE OPERATIONS                                       |
    /// +---------------------------------------------------------------------------------------+

    template <typename DataType, size_t Lane>
    constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<SimdBackend::ARCH_UNKNOWN, DataType,
                                                                         Lane>::operator~() const noexcept
    {
        Simd128 retReg{};
        using Uint = types::UInt_t<DataType>;
        for (size_t i = 0; i < Lane; ++i)
        {
            // NOTE: Static cast is require as C++ will upcast bytes and words into ints.
            const auto res = static_cast<Uint>(~std::bit_cast<Uint>(_reg[i]));
            retReg._reg[i] = std::bit_cast<DataType>(res);
        }
        return retReg;
    }


    template <typename DataType, size_t Lane>
    constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<SimdBackend::ARCH_UNKNOWN, DataType,
                                                                         Lane>::operator&(Simd128 other) const noexcept
    {
        Simd128 retReg{};
        using Uint = types::UInt_t<DataType>;
        for (size_t i = 0; i < Lane; ++i)
        {
            // NOTE: Static cast is require as C++ will upcast bytes and words into ints.
            const auto res = static_cast<Uint>(std::bit_cast<Uint>(_reg[i]) & std::bit_cast<Uint>(other._reg[i]));
            retReg._reg[i] = std::bit_cast<DataType>(res);
        }
        return retReg;
    }


    template <typename DataType, size_t Lane>
    constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>& Simd128<SimdBackend::ARCH_UNKNOWN, DataType,
                                                                          Lane>::operator&=(Simd128 other) noexcept
    {
        *this = *this & other;
        return *this;
    }


    template <typename DataType, size_t Lane>
    constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<SimdBackend::ARCH_UNKNOWN, DataType,
                                                                         Lane>::operator|(Simd128 other) const noexcept
    {
        Simd128 retReg{};
        using Uint = types::UInt_t<DataType>;
        for (size_t i = 0; i < Lane; ++i)
        {
            // NOTE: Static cast is require as C++ will upcast bytes and words into ints.
            const auto res = static_cast<Uint>(std::bit_cast<Uint>(_reg[i]) | std::bit_cast<Uint>(other._reg[i]));
            retReg._reg[i] = std::bit_cast<DataType>(res);
        }
        return retReg;
    }


    template <typename DataType, size_t Lane>
    constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>& Simd128<SimdBackend::ARCH_UNKNOWN, DataType,
                                                                          Lane>::operator|=(Simd128 other) noexcept
    {
        *this = *this | other;
        return *this;
    }


    template <typename DataType, size_t Lane>
    constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<SimdBackend::ARCH_UNKNOWN, DataType,
                                                                         Lane>::operator^(Simd128 other) const noexcept
    {
        Simd128 retReg{};
        using Uint = types::UInt_t<DataType>;
        for (size_t i = 0; i < Lane; ++i)
        {
            // NOTE: Static cast is require as C++ will upcast bytes and words into ints.
            const auto res = static_cast<Uint>(std::bit_cast<Uint>(_reg[i]) ^ std::bit_cast<Uint>(other._reg[i]));
            retReg._reg[i] = std::bit_cast<DataType>(res);
        }
        return retReg;
    }


    template <typename DataType, size_t Lane>
    constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>& Simd128<SimdBackend::ARCH_UNKNOWN, DataType,
                                                                          Lane>::operator^=(Simd128 other) noexcept
    {
        *this = *this ^ other;
        return *this;
    }


    template <typename DataType, size_t Lane>
    constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<SimdBackend::ARCH_UNKNOWN, DataType,
                                                                         Lane>::andNot(Simd128 other) const noexcept
    { return (~*this) & other; }


    template <typename DataType, size_t Lane>
    constexpr DataType Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::horizontalOr() const noexcept
    {
        using Uint = types::UInt_t<DataType>;
        Uint retVal{};
        for (size_t i = 0; i < Lane; ++i)
        {
            retVal |= std::bit_cast<Uint>(_reg[i]);
        }
        return std::bit_cast<DataType>(retVal);
    }


    template <typename DataType, size_t Lane>
    constexpr DataType Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::horizontalAnd() const noexcept
    {
        using Uint  = types::UInt_t<DataType>;
        Uint retVal = static_cast<Uint>(~0ULL);
        for (size_t i = 0; i < Lane; ++i)
        {
            retVal &= std::bit_cast<Uint>(_reg[i]);
        }
        return std::bit_cast<DataType>(retVal);
    }



    /// +---------------------------------------------------------------------------------------+
    /// |                            SHIFTING OPERATIONS                                        |
    /// +---------------------------------------------------------------------------------------+

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::operator<<(uint32_t count) const noexcept
    {
        Simd128 retReg{};
        using Uint = types::UInt_t<DataType>;
        for (size_t i = 0; i < Lane; ++i)
        {
            auto res       = static_cast<Uint>(std::bit_cast<Uint>(_reg[i]) << count);
            retReg._reg[i] = std::bit_cast<DataType>(res);
        }
        return retReg;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>& Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::operator<<=(uint32_t count) noexcept
    {
        *this = *this << count;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::operator>>(uint32_t count) const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            Simd128 retReg{};
            for (size_t i = 0; i < Lane; ++i)
            {
                retReg._reg[i] = std::bit_cast<double>(std::bit_cast<uint64_t>(_reg[i]) >> count);
            }
            return retReg;
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            Simd128 retReg{};
            for (size_t i = 0; i < Lane; ++i)
            {
                retReg._reg[i] = std::bit_cast<float>(std::bit_cast<uint32_t>(_reg[i]) >> count);
            }
            return retReg;
        }
        else
        {
            Simd128 retReg{};
            for (size_t i = 0; i < Lane; ++i)
            {
                retReg._reg[i] = _reg[i] >> count;
            }
            return retReg;
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>& Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::operator>>=(uint32_t count) noexcept
    {
        *this = *this >> count;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::shiftRightLogical(uint32_t count) const noexcept
    {
        Simd128 retReg{};
        using Uint = types::UInt_t<DataType>;
        for (size_t i = 0; i < Lane; ++i)
        {
            const auto res = static_cast<Uint>(std::bit_cast<Uint>(_reg[i]) >> count);
            retReg._reg[i] = std::bit_cast<DataType>(res);
        }
        return retReg;
    }


    template <typename DataType, size_t Lane>
    template <uint32_t Count>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::shiftLeft() const noexcept
    { return *this << Count; }


    template <typename DataType, size_t Lane>
    template <uint32_t Count>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::shiftRightArithmetic() const noexcept
    { return *this >> Count; }


    template <typename DataType, size_t Lane>
    template <uint32_t Count>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::shiftRightLogical() const noexcept
    { return shiftRightLogical(Count); }



    /// +---------------------------------------------------------------------------------------+
    /// |                                     UTILITIES                                         |
    /// +---------------------------------------------------------------------------------------+

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::blend(Simd128 other, Simd128 mask) const noexcept
    {
        constexpr auto trueMask = constants::TrueMask<DataType>;
        Simd128 retReg{};
        // Select the element from other register for a true mask value and from this register for a false value
        // on a per-lane basis.
        for (size_t i = 0; i < Lane; ++i)
        {
            retReg._reg[i] = flcn::bitEq(mask._reg[i], trueMask) ? other._reg[i] : _reg[i];
        }

        return retReg;
    }


    template <typename DataType, size_t Lane>
    template <BlendMask32_t Mask>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::blend(Simd128 other) const noexcept
    {
        constexpr auto maskTypeBitSize = sizeof(BlendMask32_t) * 8;
        constexpr auto maskWidth       = maskTypeBitSize / MAX_LANE_COUNT;
        // Create the extraction mask for extracting the bits for a given index.
        // 11111111 >> (bitSize - maskWidth) = 11111111 >> (8 - 2) = 00000011
        constexpr auto extractMask = constants::TrueMask<BlendMask32_t> >> (maskTypeBitSize - maskWidth);
        Simd128 retReg{};
        // Select the element from other register for a true mask value and from this register for a false value
        // on a per-lane basis.
        for (size_t i = 0; i < Lane; ++i)
        {
            // Assuming an 8-bit mask for simplicity with MaxLanes of 4 and sizeof(BlendMask32_t) = 8 bits
            // maskWidth = 8 / 4 = 2 bits.
            // Extract Mask = 00000011
            // Mask = 11000011
            // Mask(0) = 11000011 & (00000011 << (0 * maskWidth)) = 00000011
            // Mask(1) = 11000011 & (00000011 << (1 * maskWidth)) = 00000000
            // Mask(2) = 11000011 & (00000011 << (2 * maskWidth)) = 00000000
            // Mask(3) = 11000011 & (00000011 << (3 * maskWidth)) = 11000000
            const auto curMask = Mask & (extractMask << (i * maskWidth));
            // Here instead of doing a truthy compare we can do a comparison with zero since the
            // bit-width will be different based on the Lanes, requiring an expansion to the full 32-bits.
            // Instead, we can compare if it's a zero and select the value at that location based
            // on that falsy comparison.
            retReg._reg[i] = (curMask == 0) ? _reg[i] : other._reg[i];
        }
        return retReg;
    }


    template <typename DataType, size_t Lane>
    template <uint8_t... PermuteIndex>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::permute() const noexcept
    {
        const std::array<DataType, Lane> permuted{ _reg[PermuteIndex]... };
        return Simd128(permuted.data());
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::horizontalMin() const noexcept
    {
        // TODO: Update to flcn::min
        DataType min{ _reg[0] };
        for (size_t i = 1; i < Lane; ++i)
        {
            min = std::min(min, _reg[i]);
        }
        return min;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::horizontalMax() const noexcept
    {
        // TODO: Update to flcn::max
        DataType max{ _reg[0] };
        for (size_t i = 1; i < Lane; ++i)
        {
            max = std::max(max, _reg[i]);
        }
        return max;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::abs() const noexcept
    {
        if constexpr (std::is_unsigned_v<DataType>)
        {
            return *this;
        }
        else
        {
            Simd128 retReg{};
            for (size_t i = 0; i < Lane; ++i)
            {
                // TODO: Update to flcn::abs
                retReg._reg[i] = static_cast<DataType>(std::abs(_reg[i]));
            }
            return retReg;
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::sqrt() const noexcept
    {
        Simd128 retReg{};
        for (size_t i = 0; i < Lane; ++i)
        {
            // TODO: Update to flcn::sqrt
            // NOTE: sqrt of negative numbers are undefined and returns a zero.
            retReg._reg[i] = static_cast<DataType>(std::sqrt(std::max(_reg[i], DataType(0))));
        }
        return retReg;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::hasNan() const noexcept
    {
        Simd128 retReg{};
        if constexpr (std::is_integral_v<DataType>)
        {
            retReg.setZero();
        }
        else
        {
            for (size_t i = 0; i < Lane; ++i)
            {
                // TODO: Update to flcn::isnan
                retReg._reg[i] = std::isnan(_reg[i]) ? constants::TrueMask<DataType> : constants::FalseMask<DataType>;
            }
        }
        return retReg;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::hasInf() const noexcept
    {
        Simd128 retReg{};
        if constexpr (std::is_integral_v<DataType>)
        {
            retReg.setZero();
        }
        else
        {
            for (size_t i = 0; i < Lane; ++i)
            {
                // TODO: Update to flcn::isinf
                retReg._reg[i] = std::isinf(_reg[i]) ? constants::TrueMask<DataType> : constants::FalseMask<DataType>;
            }
        }
        return retReg;
    }



    /// +---------------------------------------------------------------------------------------+
    /// |                            ARITHMETIC OPERATIONS                                      |
    /// +---------------------------------------------------------------------------------------+

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::operator+(Simd128 other) const noexcept
    {
        Simd128 retReg{};
        for (size_t i = 0; i < Lane; ++i)
        {
            retReg._reg[i] = _reg[i] + other._reg[i];
        }
        return retReg;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>& Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::operator+=(Simd128 other) noexcept
    {
        *this = *this + other;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::operator-(Simd128 other) const noexcept
    {
        Simd128 retReg{};
        for (size_t i = 0; i < Lane; ++i)
        {
            retReg._reg[i] = _reg[i] - other._reg[i];
        }
        return retReg;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::operator-() const noexcept
    {
        Simd128 retReg{};
        if constexpr (std::is_signed_v<DataType>)
        {
            for (size_t i = 0; i < Lane; ++i)
            {
                retReg._reg[i] = -_reg[i];
            }
        }
        else
        {
            for (size_t i = 0; i < Lane; ++i)
            {
                retReg._reg[i] = static_cast<DataType>(-1 * _reg[i]);
            }
        }
        return retReg;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>& Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::operator-=(Simd128 other) noexcept
    {
        *this = *this - other;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::operator*(Simd128 other) const noexcept
    {
        Simd128 retReg{};
        for (size_t i = 0; i < Lane; ++i)
        {
            retReg._reg[i] = _reg[i] * other._reg[i];
        }
        return retReg;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>& Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::operator*=(Simd128 other) noexcept
    {
        *this = *this * other;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::divReg(Simd128 other) const noexcept
    {
        Simd128 retReg{};
        for (size_t i = 0; i < Lane; ++i)
        {
            retReg._reg[i] = _reg[i] / other._reg[i];
        }
        return retReg;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::operator/(DataType scalar) const noexcept
    {
        Simd128 retReg{};
        for (size_t i = 0; i < Lane; ++i)
        {
            retReg._reg[i] = _reg[i] / scalar;
        }
        return retReg;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>& Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::operator/=(DataType scalar) noexcept
    {
        *this = *this / scalar;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::fma(Simd128 b, Simd128 c) const noexcept
    { return *this * b + c; }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::fmSub(Simd128 b, Simd128 c) const noexcept
    { return *this * b - c; }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::horizontalAdd() const noexcept
    {
        DataType sum{};
        for (size_t i = 0; i < Lane; ++i)
        {
            sum += _reg[i];
        }
        return sum;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::horizontalSub() const noexcept
    {
        DataType diff{ _reg[0] };
        for (size_t i = 1; i < Lane; ++i)
        {
            diff -= _reg[i];
        }
        return diff;
    }



    /// +---------------------------------------------------------------------------------------+
    /// |                              EQUALITY OPERATIONS                                      |
    /// +---------------------------------------------------------------------------------------+

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::operator==(Simd128 other) const noexcept
    {
        Simd128 mask{};
        for (size_t i = 0; i < Lane; ++i)
        {
            mask._reg[i] = (_reg[i] == other._reg[i]) ? constants::TrueMask<DataType> : constants::FalseMask<DataType>;
        }
        return mask;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::operator!=(Simd128 other) const noexcept
    {
        Simd128 mask{};
        for (size_t i = 0; i < Lane; ++i)
        {
            mask._reg[i] = (_reg[i] != other._reg[i]) ? constants::TrueMask<DataType> : constants::FalseMask<DataType>;
        }
        return mask;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::operator>(Simd128 other) const noexcept
    {
        Simd128 mask{};
        for (size_t i = 0; i < Lane; ++i)
        {
            mask._reg[i] = (_reg[i] > other._reg[i]) ? constants::TrueMask<DataType> : constants::FalseMask<DataType>;
        }
        return mask;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::operator>=(Simd128 other) const noexcept
    {
        Simd128 mask{};
        for (size_t i = 0; i < Lane; ++i)
        {
            mask._reg[i] = (_reg[i] >= other._reg[i]) ? constants::TrueMask<DataType> : constants::FalseMask<DataType>;
        }
        return mask;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::operator<(Simd128 other) const noexcept
    {
        Simd128 mask{};
        for (size_t i = 0; i < Lane; ++i)
        {
            mask._reg[i] = (_reg[i] < other._reg[i]) ? constants::TrueMask<DataType> : constants::FalseMask<DataType>;
        }
        return mask;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane> Simd128<
        SimdBackend::ARCH_UNKNOWN, DataType, Lane>::operator<=(Simd128 other) const noexcept
    {
        Simd128 mask{};
        for (size_t i = 0; i < Lane; ++i)
        {
            mask._reg[i] = (_reg[i] <= other._reg[i]) ? constants::TrueMask<DataType> : constants::FalseMask<DataType>;
        }
        return mask;
    }

} // namespace flcn
