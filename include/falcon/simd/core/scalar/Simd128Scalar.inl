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


namespace flcn
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
            broadcast(data...);
        }
        else
        {
            set(data...);
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
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::Simd128(const DataType* buffer) noexcept
    { std::copy_n(buffer, Lane, _reg.begin()); }


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
        const DataType* data) noexcept
    {
        // TODO: Add death tests
        FALCON_ASSERT_MSG(
            (reinterpret_cast<uintptr_t>(data) & (ALIGNMENT - 1)) == 0,
            "[Falcon Simd]: Loading from unaligned memory when aligned address was expected. Use load() instead.");
        std::copy_n(data, Lane, _reg.begin());
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_UNKNOWN, DataType, Lane>::load(const DataType* data) noexcept
    { std::copy_n(data, Lane, _reg.begin()); }


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
    /// |                                INITIALIZATION                                         |
    /// +---------------------------------------------------------------------------------------+

} // namespace flcn
