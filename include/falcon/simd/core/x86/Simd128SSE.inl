#pragma once
/**
 * @file Simd128SSE.inl
 * @author Alan Abraham P Kochumon
 * @date Created on: September 03, 2026
 *
 * @brief Implementation of templated functions declared in Simd128SSE.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Simd128SSE.h"
#include "falcon/simd/utils/SIMDUtils.h"

#include <bitset>

namespace flcn
{

    /**************************************
     *         SETTERS/GETTERS            *
     **************************************/

    template <typename DataType, size_t Lane>
    template <typename... Args>
        requires(SimdSafeConvertible<Args, DataType> && ...)
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::Simd128(Args... data) noexcept
    {
        static_assert(sizeof...(Args) <= Lane && "Number of argument exceeded the register lane count");
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
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, T, Lane> Simd128<SimdBackend::ARCH_SSE2, DataType,
                                                                             Lane>::cast() const noexcept
    {
        if constexpr (std::is_same_v<DataType, T>)
        {
            return Simd128(_register);
        }
        else if constexpr (types::IsFP64<DataType>)
        {
            if constexpr (types::IsFP32<T>)
            {
                return Simd128<SimdBackend::ARCH_SSE2, T, Lane>(_mm_castpd_ps(_register));
            }
            else if constexpr (std::is_integral_v<T>)
            {
                return Simd128<SimdBackend::ARCH_SSE2, T, Lane>(_mm_castpd_si128(_register));
            }
            else
            {
                return Simd128<SimdBackend::ARCH_SSE2, T, Lane>(_register);
            }
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            if constexpr (types::IsFP64<T>)
            {
                return Simd128<SimdBackend::ARCH_SSE2, T, Lane>(_mm_castps_pd(_register));
            }
            else if constexpr (std::is_integral_v<T>)
            {
                return Simd128<SimdBackend::ARCH_SSE2, T, Lane>(_mm_castps_si128(_register));
            }
            else
            {
                return Simd128<SimdBackend::ARCH_SSE2, T, Lane>(_register);
            }
        }
        else // Integral to floating point.
        {
            if constexpr (types::IsFP64<T>)
            {
                return Simd128<SimdBackend::ARCH_SSE2, T, Lane>(_mm_castsi128_pd(_register));
            }
            else if constexpr (types::IsFP32<T>)
            {
                return Simd128<SimdBackend::ARCH_SSE2, T, Lane>(_mm_castsi128_ps(_register));
            }
            else
            {
                return Simd128<SimdBackend::ARCH_SSE2, T, Lane>(_register);
            }
        }
    }


    template <typename DataType, size_t Lane>
    template <typename T>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, T, Lane> Simd128<SimdBackend::ARCH_SSE2, DataType,
                                                                             Lane>::cast() noexcept
    {
        if constexpr (std::is_same_v<DataType, T>)
        {
            return Simd128(_register);
        }
        else if constexpr (types::IsFP64<DataType>)
        {
            if constexpr (types::IsFP32<T>)
            {
                return Simd128<SimdBackend::ARCH_SSE2, T, Lane>(_mm_castpd_ps(_register));
            }
            else if constexpr (std::is_integral_v<T>)
            {
                return Simd128<SimdBackend::ARCH_SSE2, T, Lane>(_mm_castpd_si128(_register));
            }
            else
            {
                return Simd128<SimdBackend::ARCH_SSE2, T, Lane>(_register);
            }
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            if constexpr (types::IsFP64<T>)
            {
                return Simd128<SimdBackend::ARCH_SSE2, T, Lane>(_mm_castps_pd(_register));
            }
            else if constexpr (std::is_integral_v<T>)
            {
                return Simd128<SimdBackend::ARCH_SSE2, T, Lane>(_mm_castps_si128(_register));
            }
            else
            {
                return Simd128<SimdBackend::ARCH_SSE2, T, Lane>(_register);
            }
        }
        else // Integral to floating point.
        {
            if constexpr (types::IsFP64<T>)
            {
                return Simd128<SimdBackend::ARCH_SSE2, T, Lane>(_mm_castsi128_pd(_register));
            }
            else if constexpr (types::IsFP32<T>)
            {
                return Simd128<SimdBackend::ARCH_SSE2, T, Lane>(_mm_castsi128_ps(_register));
            }
            else
            {
                return Simd128<SimdBackend::ARCH_SSE2, T, Lane>(_register);
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::Simd128(
        std::span<const DataType> values) noexcept
    { loadAligned(values.data()); }

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::Simd128(const DataType* buffer) noexcept
    { loadAligned(buffer); }

    template <typename DataType, size_t Lane>
    template <typename... Args>
        requires(sizeof...(Args) <= Lane) && (std::same_as<Args, DataType> && ...)
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>& Simd128<SimdBackend::ARCH_SSE2, DataType,
                                                                                     Lane>::set(Args... args)

    {
        constexpr auto MaxLanes = 128 / sizeof(DataType);
        // By packing to a compile time array and adding values
        alignas(16) std::array<DataType, MaxLanes> data{ args... };
        loadAligned(data.data());

        return *this;
    }


    template <typename DataType, size_t Lane>
    template <typename DataType2>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::Simd128(
        const Simd128<SimdBackend::ARCH_SSE2, DataType2, Lane>& other)
    {
        if constexpr (types::IsFP64<DataType2>)
        {
            if constexpr (types::IsFP64<DataType>)
            {
                _register = other.naive();
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                _register = _mm_cvtpd_ps(other.naive());
            }
            else
            {
                _register = _mm_cvtpd_epi32(other.naive());
            }
        }
        else if constexpr (types::IsFP32<DataType2>)
        {
            if constexpr (types::IsFP64<DataType>)
            {
                _register = _mm_cvtps_pd(other.naive());
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                _register = other.naive();
            }
            else
            {
                _register = _mm_cvtps_epi32(other.naive());
            }
        }
        else
        {
            if constexpr (types::IsFP64<DataType>)
            {
                _register = _mm_cvtepi32_pd(other.naive());
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                _register = _mm_cvtepi32_ps(other.naive());
            }
            else
            {
                _register = other.naive();
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::loadAligned(
        const DataType* data) noexcept
    {
        // We are using sizes for loading integers since we are storing both signed and unsigned types into the
        // register as bits, with packing.
        if constexpr (types::IsFP64<DataType>)
        {
            _register = _mm_load_pd(data);
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            if constexpr (Lane == 2)
            {
                _register = _mm_loadl_pi(_mm_setzero_ps(), reinterpret_cast<const __m64*>(data));
            }
            else
            {
                _register = _mm_load_ps(data);
            }
        }
        else
        {

            if constexpr (sizeof(DataType) * Lane == 16)
            {
                _register = _mm_load_si128(reinterpret_cast<const __m128i*>(data));
            }
            else if constexpr (sizeof(DataType) * Lane == 8)
            {
                _register = _mm_loadu_si64(data);
            }
            else if constexpr (sizeof(DataType) * Lane == 4)
            {
                _register = _mm_loadu_si32(data);
            }
            else // Lane * Size = 2
            {
                _register = _mm_loadu_si16(data);
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::load(const DataType* data) noexcept
    {
        // We are using sizes for loading integers since we are storing both signed and unsigned types into the
        // register as bits, with packing.
        if constexpr (types::IsFP64<DataType>)
        {
            _register = _mm_loadu_pd(data);
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            if constexpr (Lane == 2)
            {
                _register = _mm_loadl_pi(_mm_setzero_ps(), reinterpret_cast<const __m64*>(data));
            }
            else
            {
                _register = _mm_loadu_ps(data);
            }
        }
        else
        {

            if constexpr (sizeof(DataType) * Lane == 16)
            {
                _register = _mm_loadu_si128(reinterpret_cast<const __m128i*>(data));
            }
            else if constexpr (sizeof(DataType) * Lane == 8)
            {
                _register = _mm_loadu_si64(data);
            }
            else if constexpr (sizeof(DataType) * Lane == 4)
            {
                _register = _mm_loadu_si32(data);
            }
            else // Lane * Size = 2
            {
                _register = _mm_loadu_si16(data);
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::broadcast(
        const DataType value) noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            _register = _mm_set1_pd(value);
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            _register = _mm_set1_ps(value);
        }
        else
        {
            if constexpr (sizeof(DataType) == 8)
            {
                _register = _mm_set1_epi64x(value);
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                _register = _mm_set1_epi32(value);
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                _register = _mm_set1_epi16(value);
            }
            else if constexpr (sizeof(DataType) == 1)
            {
                _register = _mm_set1_epi8(value);
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::setZero() noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            _register = _mm_setzero_pd();
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            _register = _mm_setzero_ps();
        }
        else
        {
            _register = _mm_setzero_si128();
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::setOne() noexcept
    {
        // Since we can't direction negate zero for floating point numbers we need to negate an appropriately sized
        // 0 and bit cast them to respective floating point types.
        if constexpr (types::IsFP64<DataType>)
        {
            constexpr auto ONE = std::bit_cast<double>(~static_cast<uint64_t>(0));
            _register          = _mm_set1_pd(ONE);
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            constexpr auto ONE = std::bit_cast<float>(~static_cast<uint32_t>(0));
            _register          = _mm_set1_ps(ONE);
        }
        else
        {
            constexpr auto ONE = ~static_cast<int32_t>(0);
            _register          = _mm_set1_epi32(ONE);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::store(
        DataType* pBuffer) const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            _mm_storeu_pd(pBuffer, _register);
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            if constexpr (Lane == 2)
            {
                _mm_storel_pi(reinterpret_cast<__m64*>(pBuffer), _register);
            }
            else
            {
                _mm_storeu_ps(pBuffer, _register);
            }
        }
        else
        {
            if constexpr (sizeof(DataType) * Lane == 16)
            {
                _mm_storeu_si128(reinterpret_cast<__m128i*>(pBuffer), _register);
            }
            else if constexpr (sizeof(DataType) * Lane == 8)
            {
                _mm_storeu_si64(pBuffer, _register);
            }
            else if constexpr (sizeof(DataType) * Lane == 4)
            {
                _mm_storeu_si32(pBuffer, _register);
            }
            else // Size * Lane == 2
            {
                _mm_storeu_si16(pBuffer, _register);
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::storeAligned(
        DataType* pBuffer) const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            _mm_store_pd(pBuffer, _register);
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            if constexpr (Lane == 2)
            {
                _mm_storel_pi(reinterpret_cast<__m64*>(pBuffer), _register);
                // _mm_store_sd(reinterpret_cast<double*>(pBuffer), _mm_castps_pd(_register));
            }
            else
            {
                _mm_store_ps(pBuffer, _register);
            }
        }
        else
        {
            if constexpr (sizeof(DataType) * Lane == 16)
            {
                _mm_store_si128(reinterpret_cast<__m128i*>(pBuffer), _register);
            }
            else if constexpr (sizeof(DataType) * Lane == 8)
            {
                _mm_storeu_si64(pBuffer, _register);
            }
            else if constexpr (sizeof(DataType) * Lane == 4)
            {
                _mm_storeu_si32(pBuffer, _register);
            }
            else // Size * Lane == 2
            {
                _mm_storeu_si16(pBuffer, _register);
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::getAt(
        const size_t index) const noexcept
    {
        // TODO: Extract out message
        // TODO: Add death test
        FALCON_ASSERT_MSG(
            index < Lane,
            std::format("Out of bounds access. Idx must be less than {}. But it is currently {}.", Lane, index)
                .c_str());

        // We can use the compress and extract trick from CVL2(Agner Fog)
        // But that instruction is available only in AVX512F + AVX512VL
        // https://github.com/vectorclass/version2/blob/master/vectori128.h
        if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
        {
            // 1u << index creates a mask that selects the lane we want to index into
            // Eg: For index 4 the mask is 1 << 4 => 0001 0000 instead of 0000 1000
            auto mask = static_cast<__mmask8>(1u << index);
            if constexpr (types::IsFP64<DataType>)
            {
                auto reg = _mm_maskz_compress_pd(mask, _register);
                return _mm_cvtsd_f64(reg);
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                auto reg = _mm_maskz_compress_ps(mask, _register);
                return _mm_cvtss_f32(reg);
            }
            else if constexpr (sizeof(DataType) == 8)
            {
                auto reg = _mm_maskz_compress_epi64(mask, _register);
                return std::bit_cast<DataType>(_mm_cvtsi128_si64(reg));
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                auto reg = _mm_maskz_compress_epi32(mask, _register);
                return std::bit_cast<DataType>(_mm_cvtsi128_si32(reg));
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                auto reg = _mm_maskz_compress_epi16(mask, _register);
                return std::bit_cast<DataType>(_mm_cvtsi128_si16(reg));
            }
            else // if constexpr (sizeof(DataType) == 2)
            {
                // Note: epi8 version of maskz_compress require __mmask16 and there is no standalone
                //       variant of cvtsi128 for converting to 8-bit integral
                auto reg = _mm_maskz_compress_epi8(static_cast<__mmask16>(1u << index), _register);
                return static_cast<DataType>(_mm_cvtsi128_si16);
            }
            return static_cast<DataType>(index);
        }
        else
        {
            alignas(16) std::array<DataType, Lane> buffer{};
            store(buffer.data());
            return buffer[index];
        }
    }


    template <typename DataType, size_t Lane>
    constexpr void Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::setAt(size_t index, DataType value) noexcept
    {
        // TODO: Extract out message
        // TODO: Add death test
        FALCON_ASSERT_MSG(
            index < Lane,
            std::format("Out of bounds access. Idx must be less than {}. But it is currently {}.", Lane, index)
                .c_str());

        // Since insert and blend function require the selector to be an immediate value know at compile-time
        // for compile-indexing, we can only store the data from register, update the value
        // and then load the updated value.
        // Due to stack-spilling it is not recommended to use this setter unless absolutely necessary.
        alignas(16) std::array<DataType, Lane> interArray{};
        storeAligned(interArray.data());
        interArray[index] = value;
        loadAligned(interArray.data());
    }


    template <typename DataType, size_t Lane>
    template <size_t Index>
        requires(Index < Lane)
    FALCON_INLINE constexpr DataType Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::getAt() const noexcept
    {
        // For extracting integrals(other than 16-bits) before SSE4.1 we need shift and extract
        // Extracting a value at index, say 2, we need to first move it
        // to the 0th lane and extract it using cvtsi128_si32 and then cast it to a DataType
        //         3 |         2 |         1 |         0 Indices
        // 1111 1101 | 0011 1101 | 0111 1010 | 0111 1111 (Extract Index 2)
        // Shift the register to the left by Index * DataSize(si128 shifts) Here Index * sizeof(DataType)
        // 0000 0000 | 0000 0000 | 1111 1101 | 0011 1101
        // Now extract using _mm_cvtsi128_si32(si64) and cast it down to DataType integral.

        if constexpr (types::IsFP64<DataType>)
        {
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
            {
                return std::bit_cast<double>(_mm_extract_epi64(_mm_castpd_si128(_register), Index));
            }
            else
            {
                constexpr auto shiftAmt = Index * sizeof(DataType);
                const auto shiftedReg   = _mm_srli_si128(_mm_castpd_si128(_register), shiftAmt);
                return _mm_cvtsd_f64(_mm_castsi128_pd(shiftedReg));
            }
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
            {
                // _mm_extract_ps returns an int so we need to bit cast it a float
                return std::bit_cast<float>(_mm_extract_ps(_register, Index));
            }
            else
            {
                constexpr auto shiftAmt = Index * sizeof(DataType);
                const auto shiftedReg   = _mm_srli_si128(_mm_castps_si128(_register), shiftAmt);
                return _mm_cvtss_f32(_mm_castsi128_ps(shiftedReg));
            }
        }
        else if constexpr (sizeof(DataType) == 8)
        {
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
            {
                return static_cast<DataType>(_mm_extract_epi64(_register, Index));
            }
            else
            {
                constexpr auto shiftAmt = Index * sizeof(DataType);
                const auto shiftedReg   = _mm_srli_si128(_register, shiftAmt);
                return static_cast<DataType>(_mm_cvtsi128_si64(shiftedReg));
            }
        }
        else if constexpr (sizeof(DataType) == 4)
        {
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
            {
                return static_cast<DataType>(_mm_extract_epi32(_register, Index));
            }
            else
            {
                constexpr auto shiftAmt = Index * sizeof(DataType);
                const auto shiftedReg   = _mm_srli_si128(_register, shiftAmt);
                return static_cast<DataType>(_mm_cvtsi128_si32(shiftedReg));
            }
        }
        // While both Byte and Word can have the same code, it can given index warning
        // when used with a single else expression.
        else if constexpr (sizeof(DataType) == 2)
        {
            return static_cast<DataType>(_mm_extract_epi16(_register, Index));
        }
        else // if constexpr(sizeof(DataType) == 1)
        {
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
            {
                return static_cast<DataType>(_mm_extract_epi8(_register, Index)); // SSE4.1
            }
            else
            {
                constexpr auto shiftAmt = Index * sizeof(DataType);
                const auto shiftedReg   = _mm_srli_si128(_register, shiftAmt);
                return static_cast<DataType>(_mm_cvtsi128_si32(shiftedReg));
            }
        }
    }


    template <typename DataType, size_t Lane>
    template <size_t Index>
        requires(Index < Lane)
    FALCON_INLINE constexpr void Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::setAt(
        [[maybe_unused]] const DataType value) noexcept
    {
        // TODO: Remove may be unused.
        if constexpr (types::IsFP64<DataType>)
        {
            // There is no insert instruction for pd so we need to use our knowledge of indices at compile and
            // insert it using unpacking.
            const auto valueReg = _mm_set1_pd(value);
            if constexpr (Index == 0)
            {
                // If index is zero we can load a register with and unpack it to the lower lane
                _register = _mm_unpackhi_pd(valueReg, _register);
            }
            else
            {
                // And if the index is 1 we can insert it to the upper lane
                _register = _mm_unpackhi_pd(_register, valueReg);
            }
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            // For floats we can use bit_cast and the insertion technique used by 32-bit integrals but by using a cast
            const auto integralValue = std::bit_cast<uint32_t>(value);
            const auto integralReg   = _mm_castps_si128(_register);
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
            {
                _register = _mm_castsi128_ps(_mm_insert_epi32(integralReg, integralValue, Index));
            }
            else
            {
                // Don't assign the upperFilledReg to _register before inserting the upper half as it can cause errors.
                const auto upperFilledReg = _mm_insert_epi16(integralReg, integralValue & 0xFFFF, 2 * Index);
                _register = _mm_castsi128_ps(_mm_insert_epi16(upperFilledReg, integralValue >> 16, 2 * Index + 1));
            }
        }
        else if constexpr (sizeof(DataType) == 8)
        {
            // Since our index is known at compile time, we can use set and unpack since it's faster
            // than 4 insert_epi16
            const auto valueReg = _mm_set1_epi64x(value);
            if constexpr (Index == 0)
            {
                // If index is zero we can load a register with and unpack it to the lower lane
                _register = _mm_unpackhi_epi64(valueReg, _register);
            }
            else
            {
                // And if the index is 1 we can insert it to the upper lane
                _register = _mm_unpackhi_epi64(_register, valueReg);
            }
        }
        else if constexpr (sizeof(DataType) == 4)
        {

            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
            {
                _register = _mm_insert_epi32(_register, value, Index);
            }
            else
            {
                // SSE2 doesn't have an insert_epi16 function so we need to insert it in two parts
                // first the lower part and then the upper part(after shifting)
                // There are 8 16-bit lanes compared to 4 32-bit lanes so we need to use 2 * Index and 2 * Index + 1
                // adjacent indices.
                // [     3     ] [     2     ] [     1     ] [     0     ] 4x32
                // [[ 7 ] [ 6 ]] [[ 5 ] [ 4 ]] [[ 3 ] [ 2 ]] [[ 1 ] [ 0 ]] 8x16
                _register = _mm_insert_epi16(_register, value & 0xFFFF, 2 * Index);  // Insert the lower part into index
                _register = _mm_insert_epi16(_register, value >> 16, 2 * Index + 1); // And upper part into Index + 1
            }
        }
        else if constexpr (sizeof(DataType) == 2)
        {
            _register = _mm_insert_epi16(_register, value, Index);
        }
        else // if constexpr (sizeof(DataType) == 1)
        {
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
            {
                _register = _mm_insert_epi8(_register, value, Index);
            }
            else
            {
                // For inserting the values into we can unpack the values into upper and lower lanes
                // insert the value using _mm_insert_epi16 and pack them into the 8-bit register
                const auto zero = _mm_setzero_si128();
                auto lowerLane  = _mm_unpacklo_epi8(_register, zero);
                auto upperLane  = _mm_unpackhi_epi8(_register, zero);
                if constexpr (Index < 8) // Our data is in the lower lane
                {
                    lowerLane = _mm_insert_epi16(lowerLane, value, Index);
                }
                else
                {
                    // We need to subtract 8 from index since for 16 bit registers, only indices are 0-7
                    upperLane = _mm_insert_epi16(upperLane, value, Index - 8);
                }
                if constexpr (std::is_signed_v<DataType>)
                {
                    _register = _mm_packs_epi16(lowerLane, upperLane);
                }
                else
                {
                    _register = _mm_packus_epi16(lowerLane, upperLane);
                }
            }
        }
    }


    template <typename DataType, size_t Lane>
    constexpr DataType Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::extractFirst() noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            return _mm_cvtsd_f64(_register);
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            return _mm_cvtss_f32(_register);
        }
        else if constexpr (sizeof(DataType) == 8)
        {
            return static_cast<DataType>(_mm_cvtsi128_si64(_register));
        }
        else // if constexpr (sizeof(DataType) == 4)
        {
            // All values from 8-32 bits can use the same function and static cast
            // which will perform truncation.
            return static_cast<DataType>(_mm_cvtsi128_si32(_register));
        }
    }


    /**************************************
     *        BITWISE OPERATIONS          *
     **************************************/

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<SimdBackend::ARCH_SSE2, DataType,
                                                                                    Lane>::operator~() const noexcept
    {
        // There is no direct invert instruction so we have to use and_not = ~a ^ b and set b = 1(~0)
        Simd128 oneReg{};
        oneReg.setOne();
        if constexpr (std::is_same_v<DataType, double>)
        {
            return Simd128(_mm_andnot_pd(_register, oneReg.naive()));
        }
        else if constexpr (std::is_same_v<DataType, float>)
        {
            return Simd128(_mm_andnot_ps(_register, oneReg.naive()));
        }
        else
        {
            return Simd128(_mm_andnot_si128(_register, oneReg.naive()));
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator&(const Simd128 other) const noexcept
    {
        if constexpr (std::is_same_v<DataType, double>)
        {
            return Simd128(_mm_and_pd(_register, other.naive()));
        }
        else if constexpr (std::is_same_v<DataType, float>)
        {
            return Simd128(_mm_and_ps(_register, other.naive()));
        }
        else
        {
            return Simd128(_mm_and_si128(_register, other.naive()));
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator|(const Simd128 other) const noexcept
    {
        if constexpr (std::is_same_v<DataType, double>)
        {
            return Simd128(_mm_or_pd(_register, other.naive()));
        }
        else if constexpr (std::is_same_v<DataType, float>)
        {
            return Simd128(_mm_or_ps(_register, other.naive()));
        }
        else
        {
            return Simd128(_mm_or_si128(_register, other.naive()));
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator^(const Simd128 other) const noexcept
    {
        if constexpr (std::is_same_v<DataType, double>)
        {
            return Simd128(_mm_xor_pd(_register, other.naive()));
        }
        else if constexpr (std::is_same_v<DataType, float>)
        {
            return Simd128(_mm_xor_ps(_register, other.naive()));
        }
        else
        {
            return Simd128(_mm_xor_si128(_register, other.naive()));
        }
    }


    template <typename DataType, size_t Lane>
    constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::andNot(
        const Simd128 other) const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            return Simd128(_mm_andnot_pd(_register, other.naive()));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            return Simd128(_mm_andnot_ps(_register, other.naive()));
        }
        else
        {
            return Simd128(_mm_andnot_si128(_register, other.naive()));
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::horizontalOr() const noexcept
    {
        // There is no dedicated horizontal OR so we need to shuffle or shift the registers
        // and or them together.
        if constexpr (types::IsFP64<DataType>)
        {
            const auto shifted = _mm_srli_si128(_mm_castpd_si128(_register), 8);
            const auto orReg   = _mm_or_pd(_register, _mm_castsi128_pd(shifted));
            return _mm_cvtsd_f64(orReg);
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            // For floats we need to do shifts
            // A,     B, C,     D
            // 0,     A, B,     C
            // _, A | B, _, C | D
            // _,     _, _, A | B
            // _,     _, _, A | B | C | D
            // But if only two lanes are filled, we can do just 1 shift return the value from lower lane.
            const auto shifted1 = _mm_srli_si128(_mm_castps_si128(_register), 4);
            const auto orReg1   = _mm_or_ps(_register, _mm_castsi128_ps(shifted1));
            if constexpr (LaneCount == 2)
            {
                return _mm_cvtss_f32(orReg1);
            }
            else
            {
                const auto shifted2 = _mm_srli_si128(_mm_castps_si128(orReg1), 8);
                const auto orReg2   = _mm_or_ps(orReg1, _mm_castsi128_ps(shifted2));
                return _mm_cvtss_f32(orReg2);
            }
        }
        else if constexpr (sizeof(DataType) == 8)
        {
            const auto shifted = _mm_srli_si128(_register, 8);
            const auto orReg   = _mm_or_si128(_register, shifted);
            return _mm_cvtsi128_si64(orReg);
        }
        else if constexpr (sizeof(DataType) == 4)
        {
            const auto shifted1 = _mm_srli_si128(_register, 4);
            const auto orReg1   = _mm_or_si128(_register, shifted1);
            if constexpr (LaneCount == 2)
            {
                return _mm_cvtsi128_si32(orReg1);
            }
            else
            {
                const auto shifted2 = _mm_srli_si128(orReg1, 8);
                const auto orReg2   = _mm_or_si128(orReg1, shifted2);
                return _mm_cvtsi128_si32(orReg2);
            }
        }
        else if constexpr (sizeof(DataType) == 2)
        {
            const auto shifted1 = _mm_srli_si128(_register, 2);
            const auto orReg1   = _mm_or_si128(_register, shifted1);
            if constexpr (LaneCount == 2)
            {
                return static_cast<DataType>(_mm_cvtsi128_si32(orReg1));
            }
            else
            {
                const auto shifted2 = _mm_srli_si128(orReg1, 4);
                const auto orReg2   = _mm_or_si128(orReg1, shifted2);
                if constexpr (LaneCount == 4)
                {
                    return static_cast<DataType>(_mm_cvtsi128_si32(orReg2));
                }
                else
                {
                    const auto shifted3 = _mm_srli_si128(orReg2, 8);
                    const auto orReg3   = _mm_or_si128(orReg2, shifted3);
                    return static_cast<DataType>(_mm_cvtsi128_si32(orReg3));
                }
            }
        }
        else // if constexpr (sizeof(DataType) == 1)
        {
            const auto shifted1 = _mm_srli_si128(_register, 1);
            const auto orReg1   = _mm_or_si128(_register, shifted1);
            if constexpr (LaneCount == 2)
            {
                return static_cast<DataType>(_mm_cvtsi128_si32(orReg1));
            }
            else
            {
                const auto shifted2 = _mm_srli_si128(orReg1, 2);
                const auto orReg2   = _mm_or_si128(orReg1, shifted2);
                if constexpr (LaneCount == 4)
                {
                    return static_cast<DataType>(_mm_cvtsi128_si32(orReg2));
                }
                else
                {
                    const auto shifted3 = _mm_srli_si128(orReg2, 4);
                    const auto orReg3   = _mm_or_si128(orReg2, shifted3);
                    if constexpr (LaneCount == 8)
                    {
                        return static_cast<DataType>(_mm_cvtsi128_si32(orReg3));
                    }
                    else
                    {
                        const auto shifted4 = _mm_srli_si128(orReg3, 8);
                        const auto orReg4   = _mm_or_si128(orReg3, shifted4);
                        return static_cast<DataType>(_mm_cvtsi128_si32(orReg4));
                    }
                }
            }
        }
    }


    template <typename DataType, size_t Lane>
    constexpr DataType Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::horizontalAnd() const noexcept
    {
        // There is no dedicated horizontal AND so we need to shuffle or shift the registers
        // and & them together.
        if constexpr (types::IsFP64<DataType>)
        {
            const auto shifted = _mm_srli_si128(_mm_castpd_si128(_register), 8);
            const auto andReg  = _mm_and_pd(_register, _mm_castsi128_pd(shifted));
            return _mm_cvtsd_f64(andReg);
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            // For floats we need to do shifts
            // A,     B, C,     D
            // 0,     A, B,     C
            // _, A & B, _, C & D
            // _,     _, _, A & B
            // _,     _, _, A & B & C & D
            // But if only two lanes are filled, we can do just 1 shift return the value from lower lane.
            const auto shifted1 = _mm_srli_si128(_mm_castps_si128(_register), 4);
            const auto andReg1  = _mm_and_ps(_register, _mm_castsi128_ps(shifted1));
            if constexpr (LaneCount == 2)
            {
                return _mm_cvtss_f32(andReg1);
            }
            else
            {
                const auto shifted2 = _mm_srli_si128(_mm_castps_si128(andReg1), 8);
                const auto andReg2  = _mm_and_ps(andReg1, _mm_castsi128_ps(shifted2));
                return _mm_cvtss_f32(andReg2);
            }
        }
        else if constexpr (sizeof(DataType) == 8)
        {
            const auto shifted = _mm_srli_si128(_register, 8);
            const auto andReg  = _mm_and_si128(_register, shifted);
            return _mm_cvtsi128_si64(andReg);
        }
        else if constexpr (sizeof(DataType) == 4)
        {
            const auto shifted1 = _mm_srli_si128(_register, 4);
            const auto andReg1  = _mm_and_si128(_register, shifted1);
            if constexpr (LaneCount == 2)
            {
                return _mm_cvtsi128_si32(andReg1);
            }
            else
            {
                const auto shifted2 = _mm_srli_si128(andReg1, 8);
                const auto andReg2  = _mm_and_si128(andReg1, shifted2);
                return _mm_cvtsi128_si32(andReg2);
            }
        }
        else if constexpr (sizeof(DataType) == 2)
        {
            const auto shifted1 = _mm_srli_si128(_register, 2);
            const auto andReg1  = _mm_and_si128(_register, shifted1);
            if constexpr (LaneCount == 2)
            {
                return static_cast<DataType>(_mm_cvtsi128_si32(andReg1));
            }
            else
            {
                const auto shifted2 = _mm_srli_si128(andReg1, 4);
                const auto andReg2  = _mm_and_si128(andReg1, shifted2);
                if constexpr (LaneCount == 4)
                {
                    return static_cast<DataType>(_mm_cvtsi128_si32(andReg2));
                }
                else
                {
                    const auto shifted3 = _mm_srli_si128(andReg2, 8);
                    const auto andReg3  = _mm_and_si128(andReg2, shifted3);
                    return static_cast<DataType>(_mm_cvtsi128_si32(andReg3));
                }
            }
        }
        else // if constexpr (sizeof(DataType) == 1)
        {
            const auto shifted1 = _mm_srli_si128(_register, 1);
            const auto andReg1  = _mm_and_si128(_register, shifted1);
            if constexpr (LaneCount == 2)
            {
                return static_cast<DataType>(_mm_cvtsi128_si32(andReg1));
            }
            else
            {
                const auto shifted2 = _mm_srli_si128(andReg1, 2);
                const auto andReg2  = _mm_and_si128(andReg1, shifted2);
                if constexpr (LaneCount == 4)
                {
                    return static_cast<DataType>(_mm_cvtsi128_si32(andReg2));
                }
                else
                {
                    const auto shifted3 = _mm_srli_si128(andReg2, 4);
                    const auto andReg3  = _mm_and_si128(andReg2, shifted3);
                    if constexpr (LaneCount == 8)
                    {
                        return static_cast<DataType>(_mm_cvtsi128_si32(andReg3));
                    }
                    else
                    {
                        const auto shifted4 = _mm_srli_si128(andReg3, 8);
                        const auto andReg4  = _mm_and_si128(andReg3, shifted4);
                        return static_cast<DataType>(_mm_cvtsi128_si32(andReg4));
                    }
                }
            }
        }
    }



    /**************************************
     *       EQUALITY OPERATIONS          *
     **************************************/

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator==(const Simd128 other) const noexcept
    {
        if constexpr (std::is_same_v<DataType, double>)
        {
            return Simd128(_mm_cmpeq_pd(_register, other.naive()));
        }
        else if constexpr (std::is_same_v<DataType, float>)
        {
            return Simd128(_mm_cmpeq_ps(_register, other.naive()));
        }
        else
        {
            if constexpr (sizeof(DataType) == 8)
            {

                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
                {
                    // Equality operator for epi64 was introduced in SSE4.2
                    return Simd128(_mm_cmpeq_epi64(_register, other.naive()));
                }
                else
                {
                    // Compare high and low in one go
                    const auto eqHiLo = _mm_cmpeq_epi32(_register, other.naive());
                    // Shuffle the high bits into the lower portion
                    const auto eqHi =
                        _mm_shuffle_epi32(eqHiLo, _MM_SHUFFLE(3, 3, 1, 1)); // (A_Hi1, A_Hi1, A_Hi0, A_Hi0)
                    // And(&&) the result and extend it into lower higher lanes
                    const auto result = _mm_and_si128(eqHiLo, eqHi);
                    return Simd128(_mm_shuffle_epi32(result, _MM_SHUFFLE(2, 2, 0, 0)));
                }
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                return Simd128(_mm_cmpeq_epi32(_register, other.naive()));
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                return Simd128(_mm_cmpeq_epi16(_register, other.naive()));
            }
            else // if constexpr(sizeof(DataType) == 1)
            {
                return Simd128(_mm_cmpeq_epi8(_register, other.naive()));
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator!=(const Simd128 other) const noexcept
    {
        if constexpr (std::is_same_v<DataType, double>)
        {
            return Simd128(_mm_cmpneq_pd(_register, other.naive()));
        }
        else if constexpr (std::is_same_v<DataType, float>)
        {
            return Simd128(_mm_cmpneq_ps(_register, other.naive()));
        }
        else
        {
            return ~(*this == other);
        }
    }



    /**************************************
     *       ARITHMETIC OPERATIONS        *
     **************************************/

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator+(const Simd128 other) const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            return Simd128(_mm_add_pd(_register, other.naive()));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            return Simd128(_mm_add_ps(_register, other.naive()));
        }
        else
        {
            if constexpr (sizeof(DataType) == 8)
            {
                return Simd128(_mm_add_epi64(_register, other.naive()));
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                return Simd128(_mm_add_epi32(_register, other.naive()));
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                return Simd128(_mm_add_epi16(_register, other.naive()));
            }
            else
            {
                return Simd128(_mm_add_epi8(_register, other.naive()));
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>& Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator+=(const Simd128 other) noexcept
    {
        *this = *this + other;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator-(const Simd128 other) const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            return Simd128(_mm_sub_pd(_register, other.naive()));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            return Simd128(_mm_sub_ps(_register, other.naive()));
        }
        else
        {
            if constexpr (sizeof(DataType) == 8)
            {
                return Simd128(_mm_sub_epi64(_register, other.naive()));
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                return Simd128(_mm_sub_epi32(_register, other.naive()));
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                return Simd128(_mm_sub_epi16(_register, other.naive()));
            }
            else
            {
                return Simd128(_mm_sub_epi8(_register, other.naive()));
            }
        }
    }


    template <typename DataType, size_t Lane>
    constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<SimdBackend::ARCH_SSE2, DataType,
                                                                      Lane>::operator-() const noexcept
    {
        // NOTE: Since we are using Templated parameters CTAD won't work inside the class and zero will decay to NP.
        return Simd128(static_cast<DataType>(0)) - *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>& Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator-=(const Simd128 other) noexcept
    {
        *this = *this - other;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator*(const Simd128 other) const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            return Simd128(_mm_mul_pd(_register, other.naive()));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            return Simd128(_mm_mul_ps(_register, other.naive()));
        }
        else
        {
            if constexpr (sizeof(DataType) == 8)
            {

                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
                {
                    return Simd128(_mm_mullo_epi64(_register, other.naive()));
                }
                else
                {
                    // Since there are no EPI64 instructions less than AVX512DQ/VL architecture
                    // we need to resort to splitting low and high part and multiplying.
                    // So, we can replace A x B with (A_Hi * 2^32 + A_Lo ) * (B_Hi * 2^32 + B_Lo)
                    // A_Hi * 2^32 * B_Hi * 2^32 + A_Hi * 2^32 * B_Lo + B_Hi * 2^32 * A_Lo + A_Lo * B_Lo
                    // But since the first part (A_Hi * B_Hi * 2^64) will overflow we can ignore it.
                    // A_Lo * B_Lo + A_Hi * 2^32 * B_Lo + B_Hi * 2^32 * A_Lo
                    // This works similar to how Base-10 multiplication can be done.
                    // E.g: (22 * 25) => (20 + 2) * (20 + 5) = 400 + 40 + 100 + 10 = 550.
                    // We can get the product of the lower half and and get the cross product (A upper x B upper)
                    // and add them together.
                    const auto lowProd = _mm_mul_epu32(_register, other.naive());

                    // Extract the higher lanes
                    const auto aHi = _mm_srli_epi64(_register, 32);
                    const auto bHi = _mm_srli_epi64(other.naive(), 32);

                    // Multiply A's upper part with B' lower and and vice-versa
                    const auto aUpperProdB = _mm_mul_epu32(aHi, other.naive());
                    const auto bUpperProdA = _mm_mul_epu32(bHi, _register);

                    // Add the sums of the products
                    const auto crossSum = _mm_add_epi64(aUpperProdB, bUpperProdA);
                    // Shift the cross sum to the upper lanes
                    const auto shiftedSum = _mm_slli_epi64(crossSum, 32);

                    // Add the upper and lower products joining them together(Low + High << 32)
                    return Simd128(_mm_add_epi64(lowProd, shiftedSum));
                }
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
                {
                    return Simd128(_mm_mullo_epi32(_register, other.naive()));
                }
                else
                {
                    // Agner Fog's VCL: https://github.com/vectorclass/version2/blob/master/vectori128.h
                    // Since EPU multiplication instruction in SSE2 multiplies only the low part of "64-bit"
                    // integers aka the even lanes we need to shuffle and put the numbers in the odd lane to the
                    // even lanes and perform two separate multiplication and then pack them together
                    __m128i oddA = _mm_shuffle_epi32(_register, _MM_SHUFFLE(3, 3, 1, 1));
                    __m128i oddB = _mm_shuffle_epi32(other.naive(), _MM_SHUFFLE(3, 3, 1, 1));

                    __m128i evenProduct = _mm_mul_epu32(_register, other.naive());
                    __m128i oddProduct  = _mm_mul_epu32(oddA, oddB);

                    // Pack the odd and even register so that their lower part is filled appropriately
                    // G -> Garbage
                    // even(_, 2, _, 0) + odd(_, 3, _, 1) =packed=> Lo(_, _, 1, 0) & Hi(_, _, 3, 2)
                    __m128i packedLowerHalf = _mm_unpacklo_epi32(evenProduct, oddProduct);
                    __m128i packedhighHalf  = _mm_unpackhi_epi32(evenProduct, oddProduct);

                    // Pack the packed 32-bits into 2 64-bit lanes
                    // Lo(_, _, 1, 0) & Hi(_, _, 3, 2) =packed=> (3, 2, 1, 0)
                    return Simd128(_mm_unpacklo_epi64(packedLowerHalf, packedhighHalf));
                }
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                return Simd128(_mm_mullo_epi16(_register, other.naive()));
            }
            else
            {
                // Agner Fog's VCL: https://github.com/vectorclass/version2/blob/master/vectori128.h
                /// Split the numbers into even and odd lanes
                /// Since we dont have a problem corrupting the even lanes
                /// we don't need to mask them
                const __m128i oddA = _mm_srli_epi16(_register, 8); // Shift right by 8-bits
                const __m128i oddB = _mm_srli_epi16(other.naive(), 8);

                const __m128i evenProduct = _mm_mullo_epi16(_register, other.naive());
                __m128i oddProduct        = _mm_mullo_epi16(oddA, oddB);

                // Shift the odd product to left to prepare for 'OR'ing
                oddProduct = _mm_slli_epi16(oddProduct, 8);

                // OR together with a mask since pure OR can collect the garbage values from even product
                // For blend 0 select first bit from first register and 1 selects bits from second register
                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
                {
                    /// 0x5555 translates to 0b010101.. which select the 8-bits from oddReg, then evenReg etc.
                    return Simd128(_mm_mask_mov_epi8(oddProduct, 0x5555, evenProduct));
                }
                else
                {
                    const auto mask = Simd128(_mm_set1_epi16(0xFF00));
                    return Simd128(evenProduct).blend(Simd128(oddProduct), mask);
                }
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>& Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator*=(const Simd128 other) noexcept
    {
        *this = *this * other;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::divReg(const Simd128 other) const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            return Simd128(_mm_div_pd(_register, other.naive()));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            return Simd128(_mm_div_ps(_register, other.naive()));
        }
        else
        {
            // Since double can have only 53-bits of precision
            // we need to either use the division by constant algorithm by Donald E. Knuth
            // or unload the register do the division with IDIV and load the result to a new register.
            // Latter is implemented here and former for operator/(TODO)
            if constexpr (sizeof(DataType) == 8)
            {
                // The only possible combination for b lane is 2.
                // so we can manually calculate the division for 2 integers without loops
                alignas(16) std::array<DataType, Lane> a{}, b{};
                store(a.data());
                other.store(b.data());

                a[0] /= b[0];
                a[1] /= b[1];

                return Simd128(a);
            }
            else if constexpr (types::IsDWord<DataType>)
            {
                // Since floats cannot fully represent 32-bit integers
                // we need to unpack them to doubles across 2 registers
                // perform the division and cast back and pack
                const __m128d lowA = _mm_cvtepi32_pd(_register); // (3, 2, 1, 0) => (1, 0)
                const __m128d lowB = _mm_cvtepi32_pd(other.naive());

                // Since epi32_pd takes bytes from lower lane, we need shift the upper bytes to lower lanes by
                // 8-bytes and cast to packed doubles (3, 2, 1, 0) => (_, _, 3, 2) => (3, 2)
                const __m128d highA = _mm_cvtepi32_pd(_mm_srli_si128(_register, 8));
                const __m128d highB = _mm_cvtepi32_pd(_mm_srli_si128(other.naive(), 8));

                // Perform division
                const __m128d resultLow  = _mm_div_pd(lowA, lowB);
                const __m128d resultHigh = _mm_div_pd(highA, highB);

                // Convert back to integers with truncation (cvt"t")
                const __m128i intLow  = _mm_cvttpd_epi32(resultLow);  // (_, _, 1, 0)
                const __m128i intHigh = _mm_cvttpd_epi32(resultHigh); // (_, _, 3, 2)

                // Pack and return
                // Here we can use unpack to "pack" the lower lanes
                return Simd128(_mm_unpacklo_epi64(intLow, intHigh)); // (3, 2, 1, 0)
            }
            else if constexpr (types::IsUDWord<DataType>)
            {
                // Unsigned integer to double packing is only supported on AVX512F/VL
                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
                {
                    // Since floats cannot fully represent 32-bit integers
                    // we need to unpack them to doubles across 2 registers
                    // perform the division and cast back and pack
                    const __m128d lowA = _mm_cvtepu32_pd(_register); // (3, 2, 1, 0) => (1, 0)
                    const __m128d lowB = _mm_cvtepu32_pd(other.naive());

                    // Since epi32_pd takes bytes from lower lane, we need shift the upper bytes to lower lanes by
                    // 8-bytes and cast to packed doubles (3, 2, 1, 0) => (_, _, 3, 2) => (3, 2)
                    const __m128d highA = _mm_cvtepu32_pd(_mm_srli_si128(_register, 8));
                    const __m128d highB = _mm_cvtepu32_pd(_mm_srli_si128(other.naive(), 8));

                    // Perform division
                    const __m128d resultLow  = _mm_div_pd(lowA, lowB);
                    const __m128d resultHigh = _mm_div_pd(highA, highB);

                    // Convert back to integers with truncation (cvt"t")
                    const __m128i intLow  = _mm_cvttpd_epu32(resultLow);  // (_, _, 1, 0)
                    const __m128i intHigh = _mm_cvttpd_epu32(resultHigh); // (_, _, 3, 2)

                    // Pack and return
                    // Here we can use unpack to "pack" the lower lanes
                    return Simd128(_mm_unpacklo_epi64(intLow, intHigh)); // (3, 2, 1, 0)
                }
                else
                {
                    alignas(16) std::array<DataType, Lane> a{}, b{};
                    store(a.data());
                    other.store(b.data());
                    for (size_t i = 0; i < Lane; ++i)
                    {
                        a[i] /= b[i];
                    }
                    return Simd128(a);
                }
            }
            else if constexpr (types::IsWord<DataType>)
            {
                // Similar logic to 32-bit integrals but we can use floats since
                // they have 23-bits of precision
                // Due to the lack of direct conversion from epi16 to ps we need to unpack and then convert
                //
                // To sign extend we can pack the register with itself and arithmetic shift to the right by 16 bits
                // which fills the upper lane with 1 if negative
                // Eg: Take -7: 1001 => 1001 1001, which we need to shift by 4 times since that is width of our data
                // 1001 1001 => 1100 1100 => 1110 0110 => 1111 0011 => 1111 1001, which is -7(2's complement)
                const __m128i signExtLowA  = _mm_srai_epi32(_mm_unpacklo_epi16(_register, _register), 16);
                const __m128i signExtLowB  = _mm_srai_epi32(_mm_unpacklo_epi16(other.naive(), other.naive()), 16);
                const __m128i signExtHighA = _mm_srai_epi32(_mm_unpackhi_epi16(_register, _register), 16);
                const __m128i signExtHighB = _mm_srai_epi32(_mm_unpackhi_epi16(other.naive(), other.naive()), 16);

                // Convert to float
                const __m128 lowA  = _mm_cvtepi32_ps(signExtLowA);
                const __m128 lowB  = _mm_cvtepi32_ps(signExtLowB);
                const __m128 highA = _mm_cvtepi32_ps(signExtHighA);
                const __m128 highB = _mm_cvtepi32_ps(signExtHighB);

                // Perform division
                const __m128 resultLow  = _mm_div_ps(lowA, lowB);
                const __m128 resultHigh = _mm_div_ps(highA, highB);

                // Convert to integers
                const __m128i intLow  = _mm_cvttps_epi32(resultLow);  // (Q3, Q2, Q1, Q0)
                const __m128i intHigh = _mm_cvttps_epi32(resultHigh); // (Q7, Q6, Q5, Q4)
                return Simd128(_mm_packs_epi32(intLow, intHigh));
            }
            else if constexpr (types::IsUWord<DataType>)
            {
                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
                {
                    // Extend the 16 unsigned integrals to 32 bit signed integrals
                    const __m128i extLowA  = _mm_cvtepu16_epi32(_register);
                    const __m128i extLowB  = _mm_cvtepu16_epi32(other.naive());
                    const __m128i extHighA = _mm_cvtepu16_epi32(_mm_srli_si128(_register, 8));
                    const __m128i extHighB = _mm_cvtepu16_epi32(_mm_srli_si128(other.naive(), 8));

                    // Convert to floating point registers
                    const __m128 lowA  = _mm_cvtepi32_ps(extLowA);
                    const __m128 lowB  = _mm_cvtepi32_ps(extLowB);
                    const __m128 highA = _mm_cvtepi32_ps(extHighA);
                    const __m128 highB = _mm_cvtepi32_ps(extHighB);

                    // Perform the division
                    const __m128 resultLow  = _mm_div_ps(lowA, lowB);
                    const __m128 resultHigh = _mm_div_ps(highA, highB);

                    // Convert back to integrals
                    const __m128i intLow  = _mm_cvttps_epi32(resultLow);
                    const __m128i intHigh = _mm_cvttps_epi32(resultHigh);
                    return Simd128(_mm_packus_epi32(intLow, intHigh));
                }
                else
                {
                    // TODO: Add Simd if possible
                    std::array<DataType, Lane> a{}, b{}, result{};
                    store(a.data());
                    other.store(b.data());
                    for (size_t i = 0; i < Lane; ++i)
                    {
                        result[i] = a[i] / b[i];
                    }
                    Simd128 reg;
                    reg.load(result.data());
                    return reg;
                }
            }
            else if constexpr (types::IsByte<DataType>)
            {

                // We have a total of 8 registers containing the unpacked 8 x 8 values L -> Low and H -> High
                // abbreviated to prevent confusion
                __m128i sExtLowAL;
                __m128i sExtLowAH;
                __m128i sExtLowBL;
                __m128i sExtLowBH;
                __m128i sExtHighAL;
                __m128i sExtHighAH;
                __m128i sExtHighBL;
                __m128i sExtHighBH;
                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
                {
                    // To convert the 8-bit register from 8-bit to 32-bits directly we need to use
                    // shifts in combination with cvt(only available in SSE4.1 and above)
                    //                (highAH, highAL, lowAH, lowAL)
                    // Shift amount        12,      8,     4,     0
                    sExtLowAL  = _mm_cvtepi8_epi32(_register);
                    sExtLowAH  = _mm_cvtepi8_epi32(_mm_srli_si128(_register, 4));
                    sExtHighAL = _mm_cvtepi8_epi32(_mm_srli_si128(_register, 8));
                    sExtHighAH = _mm_cvtepi8_epi32(_mm_srli_si128(_register, 12));

                    sExtLowBL  = _mm_cvtepi8_epi32(other.naive());
                    sExtLowBH  = _mm_cvtepi8_epi32(_mm_srli_si128(other.naive(), 4));
                    sExtHighBL = _mm_cvtepi8_epi32(_mm_srli_si128(other.naive(), 8));
                    sExtHighBH = _mm_cvtepi8_epi32(_mm_srli_si128(other.naive(), 12));
                }
                else
                {
                    // For processing bytes we need first promoted to word (16-bit registers
                    // and then to qword or 32-bit integral with sign extension
                    // and then to float perform division and pack them back
                    // Sign extend from 8 - 16 bits
                    const __m128i sExtWordLowA  = _mm_srai_epi16(_mm_unpacklo_epi8(_register, _register), 8);
                    const __m128i sExtWordLowB  = _mm_srai_epi16(_mm_unpacklo_epi8(other.naive(), other.naive()), 8);
                    const __m128i sExtWordHighA = _mm_srai_epi16(_mm_unpackhi_epi8(_register, _register), 8);
                    const __m128i sExtWordHighB = _mm_srai_epi16(_mm_unpackhi_epi8(other.naive(), other.naive()), 8);


                    sExtLowAL = _mm_srai_epi32(_mm_unpacklo_epi16(sExtWordLowA, sExtWordLowA), 16);
                    sExtLowAH = _mm_srai_epi32(_mm_unpackhi_epi16(sExtWordLowA, sExtWordLowA), 16);
                    sExtLowBL = _mm_srai_epi32(_mm_unpacklo_epi16(sExtWordLowB, sExtWordLowB), 16);
                    sExtLowBH = _mm_srai_epi32(_mm_unpackhi_epi16(sExtWordLowB, sExtWordLowB), 16);

                    // Sign extend from 16 - 32 bits
                    sExtHighAL = _mm_srai_epi32(_mm_unpacklo_epi16(sExtWordHighA, sExtWordHighA), 16);
                    sExtHighAH = _mm_srai_epi32(_mm_unpackhi_epi16(sExtWordHighA, sExtWordHighA), 16);
                    sExtHighBL = _mm_srai_epi32(_mm_unpacklo_epi16(sExtWordHighB, sExtWordHighB), 16);
                    sExtHighBH = _mm_srai_epi32(_mm_unpackhi_epi16(sExtWordHighB, sExtWordHighB), 16);
                }

                // Convert to 32-bit floats
                const __m128 lowAL = _mm_cvtepi32_ps(sExtLowAL);
                const __m128 lowBL = _mm_cvtepi32_ps(sExtLowBL);
                const __m128 lowAH = _mm_cvtepi32_ps(sExtLowAH);
                const __m128 lowBH = _mm_cvtepi32_ps(sExtLowBH);

                const __m128 highAL = _mm_cvtepi32_ps(sExtHighAL);
                const __m128 highBL = _mm_cvtepi32_ps(sExtHighBL);
                const __m128 highAH = _mm_cvtepi32_ps(sExtHighAH);
                const __m128 highBH = _mm_cvtepi32_ps(sExtHighBH);

                // Perform division
                const __m128 resLowL  = _mm_div_ps(lowAL, lowBL);
                const __m128 resLowH  = _mm_div_ps(lowAH, lowBH);
                const __m128 resHighL = _mm_div_ps(highAL, highBL);
                const __m128 resHighH = _mm_div_ps(highAH, highBH);

                // Convert to 32-bit integral with truncation
                const __m128i iResLowL  = _mm_cvttps_epi32(resLowL);
                const __m128i iResLowH  = _mm_cvttps_epi32(resLowH);
                const __m128i iResHighL = _mm_cvttps_epi32(resHighL);
                const __m128i iResHighH = _mm_cvttps_epi32(resHighH);

                // Unpack to 8 bit register(32->16->8)
                const __m128i iLow  = _mm_packs_epi32(iResLowL, iResLowH);
                const __m128i iHigh = _mm_packs_epi32(iResHighL, iResHighH);

                return Simd128(_mm_packs_epi16(iLow, iHigh));
            }
            else
            {
                __m128i extLowAL;
                __m128i extLowAH;
                __m128i extHighAL;
                __m128i extHighAH;
                __m128i extLowBL;
                __m128i extLowBH;
                __m128i extHighBL;
                __m128i extHighBH;

                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
                {
                    // To convert the 8-bit register from 8-bit to 32-bits directly we need to use
                    // shifts in combination with cvt(only available in SSE4.1 and above)
                    // Register     (highAH, highAL, lowAH, lowAL)
                    // Shift amount      12,      8,     4,     0
                    extLowAL  = _mm_cvtepu8_epi32(_register);
                    extLowAH  = _mm_cvtepu8_epi32(_mm_srli_si128(_register, 4));
                    extHighAL = _mm_cvtepu8_epi32(_mm_srli_si128(_register, 8));
                    extHighAH = _mm_cvtepu8_epi32(_mm_srli_si128(_register, 12));

                    extLowBL  = _mm_cvtepu8_epi32(other.naive());
                    extLowBH  = _mm_cvtepu8_epi32(_mm_srli_si128(other.naive(), 4));
                    extHighBL = _mm_cvtepu8_epi32(_mm_srli_si128(other.naive(), 8));
                    extHighBH = _mm_cvtepu8_epi32(_mm_srli_si128(other.naive(), 12));
                }
                else
                {
                    // To perform unsigned divide we need to first unpack to 8 bits into
                    // 16 and then 32 with zero bits interleaved
                    const __m128i zero = _mm_setzero_si128();
                    // Unpack from 8 bit to 16 bits with zero extension
                    const __m128i extLowA  = _mm_unpacklo_epi8(_register, zero);
                    const __m128i extHighA = _mm_unpackhi_epi8(_register, zero);
                    const __m128i extLowB  = _mm_unpacklo_epi8(other.naive(), zero);
                    const __m128i extHighB = _mm_unpackhi_epi8(other.naive(), zero);

                    // Unpack from 16 bits to 32 bit with zero extension
                    extLowAL  = _mm_unpacklo_epi16(extLowA, zero);
                    extLowAH  = _mm_unpackhi_epi16(extLowA, zero);
                    extHighAL = _mm_unpacklo_epi16(extHighA, zero);
                    extHighAH = _mm_unpackhi_epi16(extHighA, zero);

                    extLowBL  = _mm_unpacklo_epi16(extLowB, zero);
                    extLowBH  = _mm_unpackhi_epi16(extLowB, zero);
                    extHighBL = _mm_unpacklo_epi16(extHighB, zero);
                    extHighBH = _mm_unpackhi_epi16(extHighB, zero);
                }


                // Convert to 32-bit floats
                const __m128 lowAL = _mm_cvtepi32_ps(extLowAL);
                const __m128 lowBL = _mm_cvtepi32_ps(extLowBL);
                const __m128 lowAH = _mm_cvtepi32_ps(extLowAH);
                const __m128 lowBH = _mm_cvtepi32_ps(extLowBH);

                const __m128 highAL = _mm_cvtepi32_ps(extHighAL);
                const __m128 highBL = _mm_cvtepi32_ps(extHighBL);
                const __m128 highAH = _mm_cvtepi32_ps(extHighAH);
                const __m128 highBH = _mm_cvtepi32_ps(extHighBH);

                // Perform division
                const __m128 resLowL  = _mm_div_ps(lowAL, lowBL);
                const __m128 resLowH  = _mm_div_ps(lowAH, lowBH);
                const __m128 resHighL = _mm_div_ps(highAL, highBL);
                const __m128 resHighH = _mm_div_ps(highAH, highBH);

                // Convert to 32-bit integral with truncation
                const __m128i iResLowL  = _mm_cvttps_epi32(resLowL);
                const __m128i iResLowH  = _mm_cvttps_epi32(resLowH);
                const __m128i iResHighL = _mm_cvttps_epi32(resHighL);
                const __m128i iResHighH = _mm_cvttps_epi32(resHighH);


                // Unpack to 8 bit register(32->16->8)
                // Since we are converting from 32 to 8 we can use signed packing
                // for 32-bit to 16-bit since the maximum saturation of 32,767 will never
                // be hit, since the max value for 8-bit is 255
                const __m128i iLow  = _mm_packs_epi32(iResLowL, iResLowH);
                const __m128i iHigh = _mm_packs_epi32(iResHighL, iResHighH);

                return Simd128(_mm_packus_epi16(iLow, iHigh));
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator/(const DataType scalar) const noexcept
    {
        Simd128 divisor;
        divisor.broadcast(scalar);
        return divReg(divisor);
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>& Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator/=(const DataType scalar) noexcept
    {
        *this = *this / scalar;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<SimdBackend::ARCH_SSE2, DataType,
                                                                                    Lane>::fma(Simd128 b,
                                                                                               Simd128 c) const noexcept
    {
        if constexpr (FALCON_FMA_ENABLED && types::IsFP64<DataType>)
        {
            return Simd128(_mm_fmadd_pd(_register, b.naive(), c.naive()));
        }
        else if constexpr (FALCON_FMA_ENABLED && types::IsFP32<DataType>)
        {
            return Simd128(_mm_fmadd_ps(_register, b.naive(), c.naive()));
        }
        else
        {
            return (*this * b) + c;
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::horizontalAdd() const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4 && FALCON_ENABLE_HADD_INTRINSIC)
            {
                const auto sum = _mm_hadd_pd(_register, _register);
                return _mm_cvtsd_f64(sum);
            }
            else
            {
                // To add two register we can shift the register
                // add them together and take the value at the 0th position.
                // [A, B] +
                // [A, A]
                // [2A, B + A]
                const auto shifted = _mm_shuffle_pd(_register, _register, 1);
                const auto sum     = _mm_add_pd(_register, shifted);
                return _mm_cvtsd_f64(sum);
            }
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4 && FALCON_ENABLE_HADD_INTRINSIC)
            {
                // We need 2 hadd to get the sum up 4 lanes
                // [_, _, a + b, c + d]
                const auto firstSum = _mm_hadd_ps(_register, _register);
                // If there are only 2 lanes we can return from here
                if constexpr (LaneCount == 2)
                {
                    return _mm_cvtss_f32(firstSum);
                }
                else
                {
                    // [_, _, _, a + b + c + d]
                    const auto secondSum = _mm_hadd_ps(firstSum, firstSum);
                    return _mm_cvtss_f32(secondSum);
                }
            }
            else
            {
                // For FP32 we need to do 2 shifts and adds
                // [A, B, C, D] +
                // [A, B, A, B] Shift 1
                // [2A, 2B, C+A, D+B] +
                // [C+A, C+A, C+A, C+A] Shift 2
                // [_, _, _, D+B+C+A] (_ means we don't care about those values)
                // https://github.com/vectorclass/version2/blob/master/vectorf128.h
                const auto firstShift  = _mm_movehl_ps(_register, _register);
                const auto firstSum    = _mm_add_ps(_register, firstShift);
                const auto secondShift = _mm_shuffle_ps(firstSum, firstSum, _MM_SHUFFLE(1, 1, 1, 1));
                const auto secondSum   = _mm_add_ps(firstSum, secondShift);
                return _mm_cvtss_f32(secondSum);
            }
        }
        else if constexpr (sizeof(DataType) == 8)
        {
            // [a,     b]
            // [0,     a] + (64-bit >>)
            // [a, a + b]
            const auto shifted = _mm_srli_si128(_register, 8);
            const auto sum     = _mm_add_epi64(_register, shifted);
            return static_cast<DataType>(_mm_cvtsi128_si64(sum));
        }
        else if constexpr (sizeof(DataType) == 4)
        {
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4 && FALCON_ENABLE_HADD_INTRINSIC)
            {
                // We need 2 hadd to get the sum up 4 lanes
                // [_, _, a + b, c + d]
                const auto firstSum = _mm_hadd_epi32(_register, _register);
                // If there are only 2 lanes we can return from here
                if constexpr (LaneCount == 2)
                {
                    return static_cast<DataType>(_mm_cvtsi128_si32(firstSum));
                }
                else
                {
                    // [_, _, _, a + b + c + d]
                    const auto secondSum = _mm_hadd_epi32(firstSum, firstSum);
                    return static_cast<DataType>(_mm_cvtsi128_si32(secondSum));
                }
            }
            else
            {
                // [a,     b,     c,     d]
                // [0,     a,     b,     c] (32-bit >>)
                // [a, a + b, c + b, d + c]
                const auto firstShift = _mm_srli_si128(_register, 4);
                const auto firstSum   = _mm_add_epi32(_register, firstShift);

                // If there are only two lanes we can return from here
                if constexpr (LaneCount == 2)
                {
                    return static_cast<DataType>(_mm_cvtsi128_si32(firstSum));
                }
                else
                {
                    // The sum we need are in the odd lanes
                    // So shift the register to line up the terms
                    // [a, a + b, c + b, d + c]
                    // [_,     _,     _, a + b] + (64-bit >>)
                    // [_,     _,     _, a + b + c + d]
                    const auto secondShift = _mm_srli_si128(firstSum, 8);
                    const auto secondSum   = _mm_add_epi32(firstSum, secondShift);

                    // Then extract
                    return static_cast<DataType>(_mm_cvtsi128_si32(secondSum));
                }
            }
        }
        else if constexpr (sizeof(DataType) == 2)
        {
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4 && FALCON_ENABLE_HADD_INTRINSIC)
            {
                // We need 3 hadd to get the sum up 8 lanes
                // NOTE: The sum in the upper and lower lanes will be the same, but we only consider the lower lanes.
                // NOTE: The conditionals are nested since some compilers can give unreachable code warning.
                // [_, _, _, _, a + b, c + d, e + f, g + h]
                const auto firstSum = _mm_hadd_epi16(_register, _register);
                // If there are only 2 lanes we can return from here
                if constexpr (LaneCount == 2)
                {
                    return static_cast<DataType>(_mm_cvtsi128_si32(firstSum));
                }
                else
                {
                    // [_, _, _, _, _, _, a + b + c + d, e + f + g + h]
                    const auto secondSum = _mm_hadd_epi16(firstSum, firstSum);
                    // If there are only 4 lanes we can return from here
                    // If there are only 2 lanes we can return from here
                    if constexpr (LaneCount == 4)
                    {
                        return static_cast<DataType>(_mm_cvtsi128_si32(secondSum));
                    }
                    else
                    {
                        // [_, _, _, _, _, _, _, a + b + c + d + e + f + g + h]
                        const auto thirdSum = _mm_hadd_epi16(secondSum, secondSum);
                        return static_cast<DataType>(_mm_cvtsi128_si32(thirdSum));
                    }
                }
            }
            else
            {
                // [a,     b,     c,     d,     e,     f,     g,     h]
                // [0,     a,     b,     c,     d,     e,     f,     g] (16-bit >>)
                // [a, a + b, c + b, d + c, e + d, f + e, g + f, h + g]
                const auto firstShift = _mm_srli_si128(_register, 2);
                const auto firstSum   = _mm_add_epi16(_register, firstShift);

                // For 2 lanes the sum will be already computed in the lower lane,
                // so we can return from here.
                if constexpr (LaneCount == 2)
                {
                    return static_cast<DataType>(_mm_cvtsi128_si32(firstSum));
                }
                else
                {
                    // The sum we need are in the odd lanes
                    // So shift the register to line up the terms
                    // [a, a + b, c + b,         d + c, e + d, f + e, g + f, h + g]
                    // [_,     _,     _,         a + b,     _,     _,     _, f + e] + (32-bit >>)
                    // [_,     _,     _, a + b + c + d,     _,     _,     _, e + f + g + h]
                    const auto secondShift = _mm_srli_si128(firstSum, 4);
                    const auto secondSum   = _mm_add_epi16(firstSum, secondShift);

                    // For 4 lanes we can return second sum
                    if constexpr (LaneCount == 4)
                    {
                        return static_cast<DataType>(_mm_cvtsi128_si32(secondSum));
                    }
                    else
                    {
                        // Again shift and add
                        // [_,     _,     _, a + b + c + d,     _,     _,     _, e + f + g + h]
                        // [_,     _,     _,            _,     _,     _,      _, a + b + c + d] + (64-bit >>)
                        const auto thirdShift = _mm_srli_si128(secondSum, 8);
                        const auto finalSum   = _mm_add_epi16(secondSum, thirdShift);

                        return static_cast<DataType>(_mm_cvtsi128_si32(finalSum));
                    }
                }
            }
        }
        else // if constexpr(sizeof(DataType) == 1)
        {
            // https://fgiesen.wordpress.com/2016/04/03/sse-mind-the-gap/
            // sad_epu8 find the abs difference between a and b and the first 8 lanes and put them into
            // first 16-bit of the upper and lower 64-bit lanes.
            // NOTE: Only 8 lanes shown in sample, real epi8/epu8 will have 16 lanes.
            // [h, g, f, e, d, c, b, a] = [h + g + f + e, d + c + b + a]
            // [sum1, sum0] +
            // [sum1, sum1] // Shifted
            // [2sum1, sum0 + sum1]
            const auto firstSum = _mm_sad_epu8(_register, _mm_setzero_si128());
            if constexpr (LaneCount <= 8)
            {
                // If the lane count is less than 8 then all the sum will be in the lower lanes.
                return static_cast<DataType>(_mm_cvtsi128_si32(firstSum));
            }
            else
            {
                const auto shifted   = _mm_unpackhi_epi64(firstSum, firstSum);
                const auto secondSum = _mm_add_epi64(firstSum, shifted);
                return static_cast<DataType>(_mm_cvtsi128_si32(secondSum));
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::horizontalSub() const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            // To perform A-B, we can invert the flag bits of B.
            // A + (-B)
            // Note: Mask is flipped due to how set_epi64x works.
            // Setting and casting will prevent any compiler optimization where -0.0 will be regarded
            // as 0.0 in some cases.
            const auto flipMask   = _mm_castsi128_pd(_mm_set_epi64x(0x8000000000000000, 0x0000000000000000));
            const auto flippedReg = _mm_xor_pd(_register, flipMask);
            return Simd128(flippedReg).horizontalAdd();
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            // To perform A-B-C-D, we can invert the flag bits of B, C, and D.
            // A + (-B) + (-C) + (-D)
            const auto flipMask   = _mm_castsi128_ps(_mm_setr_epi32(0x00000000, 0x80000000, 0x80000000, 0x80000000));
            const auto flippedReg = _mm_xor_ps(_register, flipMask);
            return Simd128(flippedReg).horizontalAdd();
        }
        else if constexpr (sizeof(DataType) == 8)
        {
            // For integrals we can use 2A - (A + B + C + D) to get A - B - C - D
            const auto sum  = horizontalAdd();
            const auto twoA = static_cast<DataType>(_mm_cvtsi128_si64(_register)) * 2;
            return twoA - sum;
        }
        else if constexpr (sizeof(DataType) == 4)
        {
            const auto sum  = horizontalAdd();
            const auto twoA = static_cast<DataType>(_mm_cvtsi128_si32(_register)) * 2;
            return twoA - sum;
        }
        else if constexpr (sizeof(DataType) == 2)
        {
            const auto sum = horizontalAdd();
            // To get a we need to unpack the 16-bit register into a 32-bit one si128_si16 until AVX512_FP16
            DataType twoA = 0;
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
            {
                twoA = static_cast<DataType>(_mm_cvtsi128_si16(_register)) * 2;
            }
            else
            {
                const auto unpacked = _mm_unpacklo_epi16(_register, _mm_setzero_si128());
                twoA                = static_cast<DataType>(_mm_cvtsi128_si32(unpacked)) * 2;
            }
            return twoA - sum;
        }
        else // if constexpr(sizeof(DataType) == 1)
        {
            const auto sum = horizontalAdd();
            // To get a we need to unpack the 16-bit register into a 32-bit one si128_si16 until AVX512_FP16
            // For 8-bit integers we need to unpack first for 16-bit int and then to 32-bit integral
            DataType twoA         = 0;
            const auto unpacked16 = _mm_unpacklo_epi8(_register, _mm_setzero_si128());
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
            {
                twoA = static_cast<DataType>(_mm_cvtsi128_si16(unpacked16)) * 2;
            }
            else
            {
                const auto unpacked32 = _mm_unpacklo_epi16(unpacked16, _mm_setzero_si128());
                twoA                  = static_cast<DataType>(_mm_cvtsi128_si32(unpacked32)) * 2;
            }
            return twoA - sum;
        }
    }



    /**************************************
     *       COMPARISON OPERATIONS        *
     **************************************/

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator>(const Simd128 other) const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            return Simd128(_mm_cmpgt_pd(_register, other.naive()));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            return Simd128(_mm_cmpgt_ps(_register, other.naive()));
        }
        else if constexpr (types::IsQWord<DataType>)
        {

            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
            {
                // Only SSE4.2 and above have _mm_cmpgt_epi64
                return Simd128(_mm_cmpgt_epi64(_register, other.naive()));
            }
            else
            {
                // Formula A_Hi > B_Hi | ((A_Hi == B_Hi) & A_Lo > B_Lo)
                // For signed numbers the upper lane comparisons are direct,
                // but for lower lanes we need we need to bias it, since the lower 31st bit is not a sign bit
                // which the epi32 comparison expected

                // Move the high bits into the lower lanes
                const auto aHi = _mm_shuffle_epi32(_register, _MM_SHUFFLE(3, 3, 1, 1)); // (A_Hi1, A_Hi1, A_Hi0, A_Hi0)
                const auto bHi =
                    _mm_shuffle_epi32(other.naive(), _MM_SHUFFLE(3, 3, 1, 1)); // (B_Hi1, B_Hi1, B_Hi0, B_Hi0)
                const auto gtHi = _mm_cmpgt_epi32(aHi, bHi);
                const auto eqHi = _mm_cmpeq_epi32(aHi, bHi);

                // Offset the lower portion
                const auto bias      = _mm_set1_epi32(static_cast<uint32_t>(0x80000000));
                const auto biasedALo = _mm_sub_epi32(_register, bias);
                const auto biasedBLo = _mm_sub_epi32(other.naive(), bias);
                const auto gtLo      = _mm_cmpgt_epi32(biasedALo, biasedBLo);
                const auto resLo     = _mm_or_si128(gtHi, _mm_and_si128(eqHi, gtLo));
                // Result is stored in low memory so we need to copy them to high memory
                return Simd128(_mm_shuffle_epi32(resLo, _MM_SHUFFLE(2, 2, 0, 0)));
            }
        }
        else if constexpr (types::IsDWord<DataType>)
        {
            return Simd128(_mm_cmpgt_epi32(_register, other.naive()));
        }
        else if constexpr (types::IsWord<DataType>)
        {
            return Simd128(_mm_cmpgt_epi16(_register, other.naive()));
        }
        else if constexpr (types::IsByte<DataType>)
        {
            return Simd128(_mm_cmpgt_epi8(_register, other.naive()));
        }
        // We don't instruction for comparing unsigned integers
        // so need bias the numbers by the minimum signed integer of respective size
        // and then used signed comparison
        // For signed the range for 8-bit number are -128 to 127
        // and for unsigned int, it's from 0 to 255, but by biasing by -128(0x80),
        // we have changed it to -128 to 127, and thus we can use signed comparison
        // For details see: https://fgiesen.wordpress.com/2016/04/03/sse-mind-the-gap/

        else if constexpr (types::IsUQWord<DataType>)
        {
            // For unsigned integers we need to bias both lower lanes and upper lanes, since both expect a signed
            // bit of for 31st bits
            const auto bias            = _mm_set1_epi32(static_cast<uint32_t>(0x80000000));
            const auto biasedRegisterA = _mm_sub_epi32(_register, bias);
            const auto biasedRegisterB = _mm_sub_epi32(other.naive(), bias);


            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
            {
                return Simd128(_mm_cmpgt_epi64(biasedRegisterA, biasedRegisterB));
            }
            else
            {
                // Formula A_Hi > B_Hi | ((A_Hi == B_Hi) & A_Lo > B_Lo)
                const auto gtLo = _mm_cmpgt_epi32(biasedRegisterA, biasedRegisterB); // A_Lo > B_Lo
                const auto aHi =
                    _mm_shuffle_epi32(biasedRegisterA, _MM_SHUFFLE(3, 3, 1, 1)); // (A_Hi1, A_Hi1, A_Hi0, A_Hi0)
                const auto bHi =
                    _mm_shuffle_epi32(biasedRegisterB, _MM_SHUFFLE(3, 3, 1, 1)); // (B_Hi1, B_Hi1, B_Hi0, B_Hi0)
                const auto gtHi = _mm_cmpgt_epi32(aHi, bHi);                     // A_Hi > B_Hi
                const auto eqHi = _mm_cmpeq_epi32(aHi, bHi);                     // (A_Hi == B_Hi)

                const auto resLo = _mm_or_si128(gtHi, _mm_and_si128(eqHi, gtLo));
                // Since we have used epi32 comparison, the lower lanes contain the comparison result
                // So, we need to copy the low bits to the high bits
                return Simd128(_mm_shuffle_epi32(resLo, _MM_SHUFFLE(2, 2, 0, 0)));
            }
        }
        else if constexpr (types::IsUDWord<DataType>)
        {
            const auto bias            = _mm_set1_epi32(static_cast<uint32_t>(0x80000000));
            const auto biasedRegisterA = _mm_sub_epi32(_register, bias);
            const auto biasedRegisterB = _mm_sub_epi32(other.naive(), bias);
            return Simd128(_mm_cmpgt_epi32(biasedRegisterA, biasedRegisterB));
        }
        else if constexpr (types::IsUWord<DataType>)
        {
            const auto bias            = _mm_set1_epi16(static_cast<uint16_t>(0x8000));
            const auto biasedRegisterA = _mm_sub_epi16(_register, bias);
            const auto biasedRegisterB = _mm_sub_epi16(other.naive(), bias);
            return Simd128(_mm_cmpgt_epi16(biasedRegisterA, biasedRegisterB));
        }
        else // if constexpr (types::IsUByte<DataType>)
        {
            const auto bias            = _mm_set1_epi8(static_cast<uint8_t>(0x80));
            const auto biasedRegisterA = _mm_sub_epi8(_register, bias);
            const auto biasedRegisterB = _mm_sub_epi8(other.naive(), bias);
            return Simd128(_mm_cmpgt_epi8(biasedRegisterA, biasedRegisterB));
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator>=(const Simd128 other) const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            return Simd128(_mm_cmpge_pd(_register, *other));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            return Simd128(_mm_cmpge_ps(_register, *other));
        }
        else
        {
            // A >= B == ~(A < B)
            return ~(*this < other);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator<(const Simd128 other) const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            return Simd128(_mm_cmplt_pd(_register, *other));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            return Simd128(_mm_cmplt_ps(_register, *other));
        }
        else
        {
            // A < B == B > A
            return other > *this;
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator<=(const Simd128 other) const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            return Simd128(_mm_cmple_pd(_register, *other));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            return Simd128(_mm_cmple_ps(_register, *other));
        }
        else
        {
            // A <= B == ~(A > B)
            return ~(*this > other);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator<<(const uint32_t count) const noexcept
    {
        const auto countReg = _mm_cvtsi32_si128(count);
        // For floating point numbers we need to convert them to integral of similar Lane width
        // perform the shifting and convert them back.
        if constexpr (types::IsFP64<DataType>)
        {
            auto integralReg = _mm_castpd_si128(_register);
            auto shifted     = _mm_sll_epi64(integralReg, countReg);
            return Simd128(_mm_castsi128_pd(shifted));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            auto integralReg = _mm_castps_si128(_register);
            auto shifted     = _mm_sll_epi32(integralReg, countReg);
            return Simd128(_mm_castsi128_ps(shifted));
        }
        else if constexpr (sizeof(DataType) == 8)
        {
            return Simd128(_mm_sll_epi64(_register, countReg));
        }
        else if constexpr (sizeof(DataType) == 4)
        {
            return Simd128(_mm_sll_epi32(_register, countReg));
        }
        else if constexpr (sizeof(DataType) == 2)
        {
            return Simd128(_mm_sll_epi16(_register, countReg));
        }
        else // if constexpr (sizeof(DataType) == 1))
        {
            // Since there is no direct shift operation for 8-bit integers
            // we need to shift using epi16 and apply a mask to the overflow
            // ([1001 1001] [1001 1001]) << 3 = [1100 1000] [1100 1000]
            // We first mask out the bit that will be zero when shifted
            // [1111 1111] >> 3 -> [0001 1111] Create the mask
            // [1001 1001] & [0001 1111] = [0001 1001] And apply it
            const auto mask    = 0xff >> count;
            const auto maskReg = _mm_set1_epi8(static_cast<int8_t>(mask));
            const auto andReg  = _mm_and_si128(_register, maskReg);
            // Now we shift the entire register to the left by shiftCount
            // since the overflown values are already zero-ed out shifting this will
            // create the correct put.
            // ([0001 1001] ... [0001 1001] [0001 1001]) << 3
            //  [1100 1000] ... [1100 1000] [1100 1000]
            return Simd128(_mm_sll_epi16(andReg, countReg));
        }
    }

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>& Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator<<=(uint32_t count) noexcept
    {
        *this = *this << count;
        return *this;
    }


    template <typename DataType, size_t Lane>
    constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<SimdBackend::ARCH_SSE2, DataType,
                                                                      Lane>::operator>>(uint32_t count) const noexcept
    {
        const auto countReg = _mm_cvtsi32_si128(count);
        // For floating point numbers we need to convert them to integral of similar Lane width
        // perform the shifting and convert them back.
        if constexpr (types::IsFP64<DataType>)
        {
            auto integralReg = _mm_castpd_si128(_register);
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
            {
                auto shifted = _mm_sra_epi64(integralReg, countReg);
                return Simd128(_mm_castsi128_pd(shifted));
            }
            else
            {
                auto shifted = _mm_sra_epi64_custom(integralReg, count);
                return Simd128(_mm_castsi128_pd(shifted));
            }
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            auto integralReg = _mm_castps_si128(_register);
            auto shifted     = _mm_sra_epi32(integralReg, countReg);
            return Simd128(_mm_castsi128_ps(shifted));
        }
        // Signed Types
        else if constexpr (types::IsQWord<DataType>)
        {
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
            {
                return Simd128(_mm_sra_epi64(_register, countReg));
            }
            else
            {
                return Simd128(_mm_sra_epi64_custom(_register, count));
            }
        }
        else if constexpr (types::IsDWord<DataType>)
        {
            return Simd128(_mm_sra_epi32(_register, countReg));
        }
        else if constexpr (types::IsWord<DataType>)
        {
            return Simd128(_mm_sra_epi16(_register, countReg));
        }
        else if constexpr (types::IsByte<DataType>)
        {
            // Hacker Delight Ch.2 (2-7)
            // t = -(x >> 7)
            // ((x xor t) >> n) xor t)
            // For positive number all the shifts t results in a zero which when xored returns the same result.
            // But for negative number, the first xor converts it to a positive number and the next one undoes
            // that converting the positive shifted number to a negative.
            // -7(1101) >> 2 = -1(1111)  | 5(0101) >>  2 = 1(0001)   |
            // 1101 >>     3 = 0001      | 0101 >>     3 = 0000      |
            // 0000  -  0001 = 1111 (t)  | 0000 -   0000 = 0000 (t)  |
            // 1101 xor 1111 = 0010      | 0101 xor 0000 = 0101      |
            // 0011 >>     3 = 0000      | 0101 >>     3 = 0001      |
            // 0000 xor 1111 = 1111      | 0000 xor 0001 = 0001      |
            const auto isolatedSignBit = _mm_srli_epi8_custom<7>(_register);
            const auto tReg            = _mm_sub_epi8(_mm_setzero_si128(), isolatedSignBit);
            const auto xXorTReg        = _mm_xor_si128(_register, tReg);
            const auto shiftedXor      = _mm_srl_epi8_custom(xXorTReg, count);
            return Simd128(_mm_xor_si128(shiftedXor, tReg));
        }
        // Unsigned types
        else // if (std::is_unsigned_v<DataType>)
        {
            return shiftRightLogical(count);
        }
    }

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>& Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator>>=(uint32_t count) noexcept
    {
        *this = *this >> count;
        return *this;
    }

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::shiftRightLogical(uint32_t count) const noexcept
    {
        const auto countReg = _mm_cvtsi32_si128(count);
        /// Floating point numbers needs to be cast to use integrals since there is no
        /// intrinsics for floating point shifts
        if constexpr (types::IsFP64<DataType>)
        {
            const auto integralRegister = _mm_castpd_si128(_register);
            const auto shifted          = _mm_srl_epi64(integralRegister, countReg);
            return Simd128(_mm_castsi128_pd(shifted));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            const auto integralRegister = _mm_castps_si128(_register);
            const auto shifted          = _mm_srl_epi32(integralRegister, countReg);
            return Simd128(_mm_castsi128_ps(shifted));
        }
        else if constexpr (sizeof(DataType) == 8)
        {
            return Simd128(_mm_srl_epi64(_register, countReg));
        }
        else if constexpr (sizeof(DataType) == 4)
        {
            return Simd128(_mm_srl_epi32(_register, countReg));
        }
        else if constexpr (sizeof(DataType) == 2)
        {
            return Simd128(_mm_srl_epi16(_register, countReg));
        }
        else // if constexpr (sizeof(DataType) == 1)
        {
            return Simd128(_mm_srl_epi8_custom(_register, count));
        }
    }


    template <typename DataType, size_t Lane>
    template <uint32_t Count>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<SimdBackend::ARCH_SSE2, DataType,
                                                                                    Lane>::shiftLeft() const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            const auto integralRegister = _mm_castpd_si128(_register);
            const auto shifted          = _mm_slli_epi64(integralRegister, Count);
            return Simd128(_mm_castsi128_pd(shifted));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            const auto integralRegister = _mm_castps_si128(_register);
            const auto shifted          = _mm_slli_epi32(integralRegister, Count);
            return Simd128(_mm_castsi128_ps(shifted));
        }
        else if constexpr (sizeof(DataType) == 8)
        {
            return Simd128(_mm_slli_epi64(_register, Count));
        }
        else if constexpr (sizeof(DataType) == 4)
        {
            return Simd128(_mm_slli_epi32(_register, Count));
        }
        else if constexpr (sizeof(DataType) == 2)
        {
            return Simd128(_mm_slli_epi16(_register, Count));
        }
        else // if constexpr(sizeof(DataType) == 1)
        {
            return Simd128(_mm_slli_epi8_custom<Count>(_register));
        }
    }


    template <typename DataType, size_t Lane>
    template <uint32_t Count>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::shiftRightArithmetic() const noexcept
    {
        // For floating points we need to cast registers to integrals do shifting and convert back.
        if constexpr (types::IsFP64<DataType>)
        {
            const auto integralReg = _mm_castpd_si128(_register);
            // AVX512F + VL has srai_epi64
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
            {
                const auto shifted = _mm_srai_epi64(integralReg, Count);
                return Simd128(_mm_castsi128_pd(shifted));
            }
            else
            {
                const auto shifted = _mm_srai_epi64_custom<Count>(integralReg);
                return Simd128(_mm_castsi128_pd(shifted));
            }
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            const auto integralReg = _mm_castps_si128(_register);
            const auto shifted     = _mm_srai_epi32(integralReg, Count);
            return Simd128(_mm_castsi128_ps(shifted));
        }
        // Signed types
        else if constexpr (types::IsQWord<DataType>)
        {
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
            {
                return Simd128(_mm_srai_epi64(_register, Count));
            }
            else
            {
                return Simd128(_mm_srai_epi64_custom<Count>(_register));
            }
        }
        else if constexpr (types::IsDWord<DataType>)
        {
            return Simd128(_mm_srai_epi32(_register, Count));
        }
        else if constexpr (types::IsWord<DataType>)
        {
            return Simd128(_mm_srai_epi16(_register, Count));
        }
        else if constexpr (types::IsByte<DataType>)
        {
            return Simd128(_mm_srai_epi8_custom<Count>(_register));
        }
        // Unsigned
        else // if (std::is_unsigned_v<DataType>)
        {
            return shiftRightLogical<Count>();
        }
    }


    template <typename DataType, size_t Lane>
    template <uint32_t Count>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::shiftRightLogical() const noexcept
    {
        // Floating point types
        if constexpr (types::IsFP64<DataType>)
        {
            const auto integralReg = _mm_castpd_si128(_register);
            const auto shiftedReg  = _mm_srli_epi64(integralReg, Count);
            return Simd128(_mm_castsi128_pd(shiftedReg));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            const auto integralReg = _mm_castps_si128(_register);
            const auto shiftedReg  = _mm_srli_epi32(integralReg, Count);
            return Simd128(_mm_castsi128_ps(shiftedReg));
        }
        else if constexpr (sizeof(DataType) == 8)
        {
            return Simd128(_mm_srli_epi64(_register, Count));
        }
        else if constexpr (sizeof(DataType) == 4)
        {
            return Simd128(_mm_srli_epi32(_register, Count));
        }
        else if constexpr (sizeof(DataType) == 2)
        {
            return Simd128(_mm_srli_epi16(_register, Count));
        }
        else // if constexpr (sizeof(DataType) == 1)
        {
            return Simd128(_mm_srli_epi8_custom<Count>(_register));
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::blend(const Simd128 other, const Simd128 mask) const noexcept
    {
        // Blend functions are only available from SSE 4.1
        if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
        {
            if constexpr (types::IsFP64<DataType>)
            {
                return Simd128(_mm_blendv_pd(_register, other.naive(), mask.naive()));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return Simd128(_mm_blendv_ps(_register, other.naive(), mask.naive()));
            }
            else
            {
                return Simd128(_mm_blendv_epi8(_register, other.naive(), mask.naive()));
            }
        }
        else
        {
            // Pick from this register whenever value of zero is encountered(~mask) and from other whenever 1 is
            // encountered
            // return *this & ~mask | other & mask;
            return mask.andNot(*this) | (other & mask);
        }
    }


    template <typename DataType, size_t Lane>
    template <BlendMask32_t Mask>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<
        SimdBackend::ARCH_SSE2, DataType, Lane>::blend(const Simd128 other) const noexcept
    {
        // For fallback we can use (A & ~Mask) | (B & Mask)
        // But we need to perform a bitwise expansion on the mask and then forward it to a register.
        // NOTE: Defined as a macro as some compilers can throw unreachable code when the code is not in
        //       an else block since there will be 2 returns.
#define _SIMD128_CONST_BLEND_FALLBACK()                                                                                \
    do                                                                                                                 \
    {                                                                                                                  \
        const auto [upper, lower] = simd::expandFourFold(Mask);                                                        \
        Simd128 maskReg;                                                                                               \
        if constexpr (std::same_as<DataType, double>)                                                                  \
        {                                                                                                              \
            maskReg = Simd128(_mm_castsi128_pd(_mm_set_epi64x(upper, lower)));                                         \
        }                                                                                                              \
        else if constexpr (std::same_as<DataType, float>)                                                              \
        {                                                                                                              \
            maskReg = Simd128(_mm_castsi128_ps(_mm_set_epi64x(upper, lower)));                                         \
        }                                                                                                              \
        else if constexpr (std::integral<DataType>)                                                                    \
        {                                                                                                              \
            maskReg = Simd128(_mm_set_epi64x(upper, lower));                                                           \
        }                                                                                                              \
        return maskReg.andNot(*this) | (other & maskReg);                                                              \
    } while (0)


        if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX2 && std::is_integral_v<DataType> &&
                      sizeof(DataType) == 4)
        {
            constexpr auto Imm8 = simd::packToNBits<4>(Mask);
            return Simd128(_mm_blend_epi32(_register, other._register, Imm8));
        }
        else if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
        {
            if constexpr (types::IsFP64<DataType>)
            {
                constexpr auto Imm8 = simd::packToNBits<2>(Mask);
                return Simd128(_mm_blend_pd(_register, other._register, Imm8));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                constexpr auto Imm8 = simd::packToNBits<4>(Mask);
                return Simd128(_mm_blend_ps(_register, other._register, Imm8));
            }
            else if constexpr (sizeof(DataType) == 8)
            {
                constexpr auto Imm8 = simd::packToNBits<2>(Mask);
                const auto dblReg1  = _mm_castsi128_pd(_register);
                const auto dblReg2  = _mm_castsi128_pd(*other);
                return Simd128(_mm_castpd_si128(_mm_blend_pd(dblReg1, dblReg2, Imm8)));
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                constexpr auto Imm8 = simd::packToNBits<4>(Mask);
                const auto fltReg1  = _mm_castsi128_ps(_register);
                const auto fltReg2  = _mm_castsi128_ps(*other);
                return Simd128(_mm_castps_si128(_mm_blend_ps(fltReg1, fltReg2, Imm8)));
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                constexpr auto Imm8 = simd::packToNBits<8>(Mask);
                return Simd128(_mm_blend_epi16(_register, other._register, Imm8));
            }
            else
            {
                _SIMD128_CONST_BLEND_FALLBACK();
            }
        }
        else
        {
            _SIMD128_CONST_BLEND_FALLBACK();
        }

#undef _SIMD128_CONST_BLEND_FALLBACK
    }


    template <typename DataType, size_t Lane>
    template <uint8_t... ShuffleIdx>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<SimdBackend::ARCH_SSE2, DataType,
                                                                                    Lane>::shuffle() const noexcept
    {
        // NOTE: Shuffle mask must be evaluated as a separate const-expression since GCC
        //       is very strict about the immediate value being constexpr, which is guaranteed for constexpr lvalues.
        // NOTE: _MM_SHUFFLE takes indices in the opposite order
        static_assert(sizeof...(ShuffleIdx) == Lane && "There must be <Lane> shuffle indices.");
        static_assert(((ShuffleIdx < Lane) && ...) && "Indices must be between 0(inclusive) and <Lane>(exclusive).");

        // 128(16 bytes) / sizeof bits give the maximum lanes possible
        // and this can be used to remove conditions since the unoccupied values by pack expansion will be zero.
        constexpr size_t MaxLanes = 16 / sizeof(DataType);
        // Since packed indexing is not support until C++26, we need to use this workaround
        constexpr std::array<uint8_t, MaxLanes> indices{ { ShuffleIdx... } };

        if constexpr (types::IsFP64<DataType>)
        {
            constexpr int shuffleMask = indices[1] << 1 | indices[0];
            return Simd128(_mm_shuffle_pd(_register, _register, shuffleMask));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            // Evaluated at compile-time
            // Since there is a possibility that indices can be 2 but _MM_SHUFFLE
            // only takes 4 values, so we need to use 0 indices for the other indices

            constexpr int shuffleMask = _MM_SHUFFLE(indices[3], indices[2], indices[1], indices[0]);
            return Simd128(_mm_shuffle_ps(_register, _register, shuffleMask));
        }
        else
        {
            if constexpr (sizeof(DataType) == 8)
            {
                // Intel's x86 doesn't provide a epi64 version of shuffle
                // so we need to use the epi32 version and use the shuffle indices twice since
                // the 64-bit lanes are just 2 32-bit lanes <64, 64> = <32, 32, 32, 32>
                // We need to scale the indices from 2 to 4 since the 64 bit register is placed in two
                // adjacent 32-bit registers
                // So multiplication maps from 0, 1 to 0, 2 and addition selects pair <0, 1> and <2, 3>
                constexpr auto firstIndex  = indices[0] * 2;
                constexpr auto secondIndex = indices[0] * 2 + 1;
                constexpr auto thirdIndex  = indices[1] * 2;
                constexpr auto fourthIndex = indices[1] * 2 + 1;
                constexpr int shuffleMask  = _MM_SHUFFLE(fourthIndex, thirdIndex, secondIndex, firstIndex);
                auto reg                   = _mm_shuffle_epi32(_register, shuffleMask);
                return Simd128(reg);
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                constexpr int shuffleMask = _MM_SHUFFLE(indices[3], indices[2], indices[1], indices[0]);
                return Simd128(_mm_shuffle_epi32(_register, shuffleMask));
            }
            else if constexpr (sizeof(DataType) == 2)
            {

                if constexpr (Lane < 5)
                {
                    // NOTE: Due to the static assert above it can be guaranteed that indices[i] won't be
                    //       greater than 3(0b11) and hence will not give overflow errors, which is not the case with
                    //       lanes greater than 4.
                    constexpr int shuffleMask = _MM_SHUFFLE(indices[3], indices[2], indices[1], indices[0]);
                    return Simd128(_mm_shufflelo_epi16(_register, shuffleMask));
                }
                // We only need to shuffle the high lanes if Lane(s) are larger than 4
                else
                {
                    // Since we need to cross lanes when lanes are greater than 5
                    // we need to perform 4 shuffles
                    // 1. Lower Lane with the first 4 indices
                    // 2. Higher Lane with the first 4 indices
                    // 3. Lower Lane with the last 4 indices
                    // 4. Higher Lane with the last 4 indices
                    constexpr int firstIdx   = indices[0] > 3 ? indices[0] - 4 : indices[0];
                    constexpr int secondIdx  = indices[1] > 3 ? indices[1] - 4 : indices[1];
                    constexpr int thirdIdx   = indices[2] > 3 ? indices[2] - 4 : indices[2];
                    constexpr int fourthIdx  = indices[3] > 3 ? indices[3] - 4 : indices[3];
                    constexpr int fifthIdx   = indices[4] > 3 ? indices[4] - 4 : indices[4];
                    constexpr int sixthIdx   = indices[5] > 3 ? indices[5] - 4 : indices[5];
                    constexpr int seventhIdx = indices[6] > 3 ? indices[6] - 4 : indices[6];
                    constexpr int eighthIdx  = indices[7] > 3 ? indices[7] - 4 : indices[7];

                    ///-------------- LOWER LANE SHUFFLE --------------
                    // NOTE: Here Lo refers to Lower indices(< 4) and A and B are the lower and upper lanes.
                    // (_, _, _, _, A_Lo3, A_Lo2, A_Lo1, A_Lo0)
                    constexpr int shuffleMaskA = _MM_SHUFFLE(fourthIdx, thirdIdx, secondIdx, firstIdx);
                    auto shuffleLoLo           = _mm_shufflelo_epi16(_register, shuffleMaskA);
                    // (A_Hi7, A_Hi6, A_Hi5, A_Hi4, _, _, _, _)
                    auto shuffleHiLo = _mm_shufflehi_epi16(_register, shuffleMaskA);
                    // We need to shuffle the data back into the lower lanes since shufflehi puts them in upper lane
                    // (_, _, _, _, A_Hi7, A_Hi6, A_Hi5, A_Hi4)
                    shuffleHiLo = _mm_srli_si128(shuffleHiLo, 8);

                    ///-------------- UPPER LANE SHUFFLE --------------
                    constexpr int shuffleMaskB = _MM_SHUFFLE(eighthIdx, seventhIdx, sixthIdx, fifthIdx);
                    // (_, _, _, _, B_Lo3, B_Lo2, B_Lo1, B_Lo0)
                    auto shuffleLoHi = _mm_shufflelo_epi16(_register, shuffleMaskB);
                    // For the upper shuffle we need to shift the lower lanes to the upper lanes.
                    // (B_Lo3, B_Lo2, B_Lo1, B_Lo0, _, _, _, _)
                    shuffleLoHi = _mm_slli_si128(shuffleLoHi, 8);
                    // (B_Hi7, B_Hi6, B_Hi5, B_Hi4, _, _, _, _)
                    auto shuffleHiHi = _mm_shufflehi_epi16(_register, shuffleMaskB);

                    ///-------------- MASKING --------------
                    // Now that we have the two registers each filled with values from upper and lower lanes
                    // we need to select the correct one with each entry with a mask.
                    // For indices are greater than 3 the value in the upper(..Hi) will be selected
                    // and values from lower shuffled register otherwise.
                    const auto digitToCompare = _mm_set1_epi16(3);
                    // The number of lanes here should be 8 since there we cannot create a non-power of 2 lanes
                    // and less than 5 lanes are handled in the if block.
                    // While the first 2 checks for indices.size() are unnecessary it is left for completion
                    // and no runtime const is incurred since all the variables are known at compile time.
                    const auto indexReg = _mm_setr_epi16(indices[0], indices[1], indices[2], indices[3], indices[4],
                                                         indices[5], indices[6], indices[7]);
                    auto mask           = _mm_cmpgt_epi16(indexReg, digitToCompare);

                    ///-------------- PACKING --------------
                    // TODO: Update to use ctor based inits
                    auto blendedLo = Simd128(shuffleLoLo).blend(Simd128(shuffleHiLo), Simd128(mask));
                    auto blendedHi = Simd128(shuffleLoHi).blend(Simd128(shuffleHiHi), Simd128(mask));

                    // Before we unpack we need to shift the upper lanes of blendedHi to the lower lanes
                    // since _mm_unpacklo_epi64 expects both the values to be in the lower lane.
                    auto shiftedHi = _mm_srli_si128(blendedHi.naive(), 8);
                    // We need to unpack the lower 64-bits from shuffle low and high
                    // Since unpack takes the lower 64-bits from the first argument,
                    // we need to pass the low part first.
                    return Simd128(_mm_unpacklo_epi64(blendedLo.naive(), shiftedHi));
                }
            }
            else
            {
                // TODO: Update to ctor based Simd128 construction in else path
                // _mm_shuffle_epi8 is supported from SSSE3 but since we only provide
                // two categories for SSE, anything below SSE4.2 will use the SSE2 fallback.
                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
                {
                    alignas(16) std::array<DataType, Lane> mask{ ShuffleIdx... };
                    const Simd128 maskReg{ mask };
                    return Simd128(_mm_shuffle_epi8(_register, *maskReg));
                }
                else
                {
                    // Store the data into an stack-array
                    alignas(16) std::array<DataType, Lane> stored{};
                    store(stored.data());
                    // Create a new array using shuffleIdx and parameter unpacking
                    alignas(16) std::array<DataType, Lane> res{ stored[ShuffleIdx]... };
                    // Loading it into a new register and return it.
                    return Simd128(res);
                }
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::horizontalMin() const noexcept
    {
        // There is no dedicated horizontal min so we need to shuffle or shift the registers
        // and take min each shifted registers.
        if constexpr (types::IsFP64<DataType>)
        {
            const auto shifted = _mm_srli_si128(_mm_castpd_si128(_register), 8);
            const auto minReg  = *flcn::min(*this, Simd128(_mm_castsi128_pd(shifted)));
            return _mm_cvtsd_f64(minReg);
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            // For floats we need to do 2 shifts
            // A,         B, C, D
            // 0,         A, B, C
            // _, min(A, B), _, min(C, D)
            // _,         _, _, min(A, B)
            // _,         _, _, min(A, B, C, D)
            // But if only two lanes are filled, we can do just 1 shift return the value from lower lane.
            const auto shifted1 = _mm_srli_si128(_mm_castps_si128(_register), 4);
            const auto minReg1  = *flcn::min(*this, Simd128(_mm_castsi128_ps(shifted1)));
            if constexpr (LaneCount == 2)
            {
                return _mm_cvtss_f32(minReg1);
            }
            else
            {
                const auto shifted2 = _mm_srli_si128(_mm_castps_si128(minReg1), 8);
                const auto minReg2  = *flcn::min(Simd128(minReg1), Simd128(_mm_castsi128_ps(shifted2)));
                return _mm_cvtss_f32(minReg2);
            }
        }
        else if constexpr (sizeof(DataType) == 8)
        {
            const auto shifted = _mm_srli_si128(_register, 8);
            const auto minReg  = *flcn::min(*this, Simd128(shifted));
            return _mm_cvtsi128_si64(minReg);
        }
        else if constexpr (sizeof(DataType) == 4)
        {
            const auto shifted1 = _mm_srli_si128(_register, 4);
            const auto minReg1  = *flcn::min(*this, Simd128(shifted1));
            if constexpr (LaneCount == 2)
            {
                return _mm_cvtsi128_si32(minReg1);
            }
            else
            {
                const auto shifted2 = _mm_srli_si128(minReg1, 8);
                const auto minReg2  = *flcn::min(Simd128(minReg1), Simd128(shifted2));
                return _mm_cvtsi128_si32(minReg2);
            }
        }
        else if constexpr (sizeof(DataType) == 2)
        {
            const auto shifted1 = _mm_srli_si128(_register, 2);
            const auto minReg1  = *flcn::min(*this, Simd128(shifted1));
            if constexpr (LaneCount == 2)
            {
                return static_cast<DataType>(_mm_cvtsi128_si32(minReg1));
            }
            else
            {
                const auto shifted2 = _mm_srli_si128(minReg1, 4);
                const auto minReg2  = *flcn::min(Simd128(minReg1), Simd128(shifted2));
                if constexpr (LaneCount == 4)
                {
                    return static_cast<DataType>(_mm_cvtsi128_si32(minReg2));
                }
                else
                {
                    const auto shifted3 = _mm_srli_si128(minReg2, 8);
                    const auto minReg3  = *flcn::min(Simd128(minReg2), Simd128(shifted3));
                    return static_cast<DataType>(_mm_cvtsi128_si32(minReg3));
                }
            }
        }
        else // if constexpr (sizeof(DataType) == 1)
        {
            const auto shifted1 = _mm_srli_si128(_register, 1);
            const auto minReg1  = *flcn::min(*this, Simd128(shifted1));
            if constexpr (LaneCount == 2)
            {
                return static_cast<DataType>(_mm_cvtsi128_si32(minReg1));
            }
            else
            {
                const auto shifted2 = _mm_srli_si128(minReg1, 2);
                const auto minReg2  = *flcn::min(Simd128(minReg1), Simd128(shifted2));
                if constexpr (LaneCount == 4)
                {
                    return static_cast<DataType>(_mm_cvtsi128_si32(minReg2));
                }
                else
                {
                    const auto shifted3 = _mm_srli_si128(minReg2, 4);
                    const auto minReg3  = *flcn::min(Simd128(minReg2), Simd128(shifted3));
                    if constexpr (LaneCount == 8)
                    {
                        return static_cast<DataType>(_mm_cvtsi128_si32(minReg3));
                    }
                    else
                    {
                        const auto shifted4 = _mm_srli_si128(minReg3, 8);
                        const auto minReg4  = *flcn::min(Simd128(minReg3), Simd128(shifted4));
                        return static_cast<DataType>(_mm_cvtsi128_si32(minReg4));
                    }
                }
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::horizontalMax() const noexcept
    {
        // There is no dedicated horizontal max so we need to shuffle or shift the registers
        // and take max each shifted registers.
        if constexpr (types::IsFP64<DataType>)
        {
            const auto shifted = _mm_srli_si128(_mm_castpd_si128(_register), 8);
            const auto maxReg  = *flcn::max(*this, Simd128(_mm_castsi128_pd(shifted)));
            return _mm_cvtsd_f64(maxReg);
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            // For floats we need to do 2 shifts
            // A,         B, C, D
            // 0,         A, B, C
            // _, max(A, B), _, max(C, D)
            // _,         _, _, max(A, B)
            // _,         _, _, max(A, B, C, D)
            // But if only two lanes are filled, we can do just 1 shift return the value from lower lane.
            const auto shifted1 = _mm_srli_si128(_mm_castps_si128(_register), 4);
            const auto maxReg1  = *flcn::max(*this, Simd128(_mm_castsi128_ps(shifted1)));
            if constexpr (LaneCount == 2)
            {
                return _mm_cvtss_f32(maxReg1);
            }
            else
            {
                const auto shifted2 = _mm_srli_si128(_mm_castps_si128(maxReg1), 8);
                const auto maxReg2  = *flcn::max(Simd128(maxReg1), Simd128(_mm_castsi128_ps(shifted2)));
                return _mm_cvtss_f32(maxReg2);
            }
        }
        else if constexpr (sizeof(DataType) == 8)
        {
            const auto shifted = _mm_srli_si128(_register, 8);
            const auto maxReg  = *flcn::max(*this, Simd128(shifted));
            return _mm_cvtsi128_si64(maxReg);
        }
        else if constexpr (sizeof(DataType) == 4)
        {
            const auto shifted1 = _mm_srli_si128(_register, 4);
            const auto maxReg1  = *flcn::max(*this, Simd128(shifted1));
            if constexpr (LaneCount == 2)
            {
                return _mm_cvtsi128_si32(maxReg1);
            }
            else
            {
                const auto shifted2 = _mm_srli_si128(maxReg1, 8);
                const auto maxReg2  = *flcn::max(Simd128(maxReg1), Simd128(shifted2));
                return _mm_cvtsi128_si32(maxReg2);
            }
        }
        else if constexpr (sizeof(DataType) == 2)
        {
            const auto shifted1 = _mm_srli_si128(_register, 2);
            const auto maxReg1  = *flcn::max(*this, Simd128(shifted1));
            if constexpr (LaneCount == 2)
            {
                return static_cast<DataType>(_mm_cvtsi128_si32(maxReg1));
            }
            else
            {
                const auto shifted2 = _mm_srli_si128(maxReg1, 4);
                const auto maxReg2  = *flcn::max(Simd128(maxReg1), Simd128(shifted2));
                if constexpr (LaneCount == 4)
                {
                    return static_cast<DataType>(_mm_cvtsi128_si32(maxReg2));
                }
                else
                {
                    const auto shifted3 = _mm_srli_si128(maxReg2, 8);
                    const auto maxReg3  = *flcn::max(Simd128(maxReg2), Simd128(shifted3));
                    return static_cast<DataType>(_mm_cvtsi128_si32(maxReg3));
                }
            }
        }
        else // if constexpr (sizeof(DataType) == 1)
        {
            const auto shifted1 = _mm_srli_si128(_register, 1);
            const auto maxReg1  = *flcn::max(*this, Simd128(shifted1));
            if constexpr (LaneCount == 2)
            {
                return static_cast<DataType>(_mm_cvtsi128_si32(maxReg1));
            }
            else
            {
                const auto shifted2 = _mm_srli_si128(maxReg1, 2);
                const auto maxReg2  = *flcn::max(Simd128(maxReg1), Simd128(shifted2));
                if constexpr (LaneCount == 4)
                {
                    return static_cast<DataType>(_mm_cvtsi128_si32(maxReg2));
                }
                else
                {
                    const auto shifted3 = _mm_srli_si128(maxReg2, 4);
                    const auto maxReg3  = *flcn::max(Simd128(maxReg2), Simd128(shifted3));
                    if constexpr (LaneCount == 8)
                    {
                        return static_cast<DataType>(_mm_cvtsi128_si32(maxReg3));
                    }
                    else
                    {
                        const auto shifted4 = _mm_srli_si128(maxReg3, 8);
                        const auto maxReg4  = *flcn::max(Simd128(maxReg3), Simd128(shifted4));
                        return static_cast<DataType>(_mm_cvtsi128_si32(maxReg4));
                    }
                }
            }
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<SimdBackend::ARCH_SSE2, DataType,
                                                                                    Lane>::abs() const noexcept
    {
        // There is no intrinsic for floating point abs so we have to use a sign flag mask and use AND
        // 1 101 1010
        // 0 111 1111 &
        // 0 101 1010

        // For integral we can use the trick mention in Hackers Delight[2-4]
        // y = x a>> (sizeof(DataType) * 8 - 1) (for int32 its y = x >> 31)
        // (x xor y) - y
        // -7  1001
        // t = 1111 xor
        //   = 0110
        //   = 1111 -
        //   = 0111 (7)
        if constexpr (std::is_unsigned_v<DataType>)
        {
            return Simd128(_register);
        }
        else if constexpr (types::IsFP64<DataType>)
        {
            // We can take the abs of a register by using a flag mask and ANDing it with our register.
            const auto flagMask    = _mm_set1_epi64x(0x7FFFFFFFFFFFFFFF); // 0b0111..1111
            const auto integralReg = _mm_castpd_si128(_register);
            const auto absReg      = _mm_and_si128(integralReg, flagMask);
            return Simd128(_mm_castsi128_pd(absReg));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            // We can take the abs of a register by using a flag mask and ANDing it with our register.
            const auto flagMask    = _mm_set1_epi32(0x7FFFFFFF); // 0b0111..1111
            const auto integralReg = _mm_castps_si128(_register);
            const auto absReg      = _mm_and_si128(integralReg, flagMask);
            return Simd128(_mm_castsi128_ps(absReg));
        }
        else if constexpr (types::IsQWord<DataType>)
        {
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
            {
                return Simd128(_mm_abs_epi64(_register));
            }
            else
            {
                // t = x a>> 63; abs = (x xor t) - t;
                const auto t      = *shiftRightArithmetic<63>();
                const auto xorReg = _mm_xor_si128(_register, t);
                return Simd128(_mm_sub_epi64(xorReg, t));
            }
        }
        else if constexpr (types::IsDWord<DataType>)
        {
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
            {
                return Simd128(_mm_abs_epi32(_register));
            }
            else
            {
                // t = x a>> 31; abs = (x xor t) - t;
                const auto t      = *shiftRightArithmetic<31>();
                const auto xorReg = _mm_xor_si128(_register, t);
                return Simd128(_mm_sub_epi32(xorReg, t));
            }
        }
        else if constexpr (types::IsWord<DataType>)
        {
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
            {
                return Simd128(_mm_abs_epi16(_register));
            }
            else
            {
                // t = x a>> 15; abs = (x xor t) - t;
                const auto t      = *shiftRightArithmetic<15>();
                const auto xorReg = _mm_xor_si128(_register, t);
                return Simd128(_mm_sub_epi16(xorReg, t));
            }
        }
        else // if constexpr (types::IsByte<DataType>)
        {
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_SSE4)
            {
                return Simd128(_mm_abs_epi8(_register));
            }
            else
            {
                // t = x a>> 7; abs = (x xor t) - t;
                const auto t      = *shiftRightArithmetic<7>();
                const auto xorReg = _mm_xor_si128(_register, t);
                return Simd128(_mm_sub_epi8(xorReg, t));
            }
        }
    }


    template <typename DataType, size_t Lane>
    constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::sqrt()
        const noexcept
    {
        // For integrals we need to convert them to fp-register, and do the sqrt and then
        // convert them back with truncation.
        if constexpr (types::IsFP64<DataType>)
        {
            return Simd128(_mm_sqrt_pd(_register));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            return Simd128(_mm_sqrt_ps(_register));
        }
        else if constexpr (sizeof(DataType) == 8)
        {
            // There must only 2 lanes for 64-bit integrals
            alignas(16) std::array<DataType, 2> array{};
            if constexpr (std::is_signed_v<DataType>)
            {
                // For signed integrals we must clamp to zero to prevent negative integral square roots
                // And we need to clamp to zero.
                const auto clamped = *max(*this, Simd128(_mm_setzero_si128()));
                _mm_store_si128(reinterpret_cast<__m128i*>(array.data()), clamped);
            }
            else
            {
                storeAligned(array.data());
            }
            return Simd128(static_cast<DataType>(std::sqrt(array[0])), static_cast<DataType>(std::sqrt(array[1])));
        }
        // Since there is no epu32 to pd instruction we need to split paths for unsigned
        // and signed 32-bit integers
        else if constexpr (types::IsDWord<DataType>)
        {
            // For EPI32 we need to convert them to 64-bit integrals and then to doubles
            // to ensure minimal precision loss.
            const auto doubleRegLo = _mm_cvtepi32_pd(_register);
            const auto clampedLo   = _mm_max_pd(doubleRegLo, _mm_setzero_pd());
            const auto sqrtLo      = _mm_sqrt_pd(clampedLo);
            auto intSqrtLo         = _mm_cvttpd_epi32(sqrtLo); // (0, 0, B, A)
            if constexpr (Lane == 2)
            {
                return Simd128(intSqrtLo);
            }
            else
            {
                const auto shifted     = _mm_srli_si128(_register, 8);
                const auto doubleRegHi = _mm_cvtepi32_pd(shifted);
                const auto clampedHi   = _mm_max_pd(doubleRegHi, _mm_setzero_pd());
                const auto sqrtHi      = _mm_sqrt_pd(clampedHi);
                const auto intSqrtHi   = _mm_cvttpd_epi32(sqrtHi);        // (0, 0, D, C)
                return Simd128(_mm_unpacklo_epi64(intSqrtLo, intSqrtHi)); // (D, C, B, A)
            }
        }
        else if constexpr (types::IsUDWord<DataType>)
        {
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
            {
                const auto doubleRegLo = _mm_cvtepu32_pd(_register);
                const auto sqrtLo      = _mm_sqrt_pd(doubleRegLo);
                const auto intSqrtLo   = _mm_cvttpd_epi32(sqrtLo);
                if constexpr (Lane == 2)
                {
                    return Simd128(intSqrtLo);
                }
                else
                {
                    // Shift the upper 2 lanes to the lower lanes since the cvtepi converts values in the lower lane
                    const auto shiftedHi   = _mm_srli_si128(_register, 8);
                    const auto doubleRegHi = _mm_cvtepu32_pd(shiftedHi);
                    const auto sqrtHi      = _mm_sqrt_pd(doubleRegHi);
                    const auto intSqrtHi   = _mm_cvttpd_epi32(sqrtHi);

                    return Simd128(_mm_unpacklo_epi64(intSqrtLo, intSqrtHi));
                }
            }
            else
            {
                // For 32-bit integers since we don't have an epu32_pd(unless in AVX512F+VL)
                // when having an int with the MSB `ON`, it will get interpreted as a negative double.
                // To convert that negative interpretation to a positive number
                // we add the int32-max, which will reset the negative number to our original number
                // If our number is 111.111 it will get interpreted as -1 although it is (2^32) - 1 or 4294967295
                // but adding 2^32 to the -1 yields our original number.
                const auto offset = _mm_set1_pd(4294967296.0);
                const auto zero   = _mm_setzero_pd();

                // If hardware created a negative double, it was a large unsigned int
                // so add an offset to it
                const auto doubleRegLo = _mm_cvtepi32_pd(_register);
                const auto maskLo      = _mm_cmplt_pd(doubleRegLo, zero);
                const auto filterLo    = _mm_and_pd(maskLo, offset);
                const auto correctedLo = _mm_add_pd(doubleRegLo, filterLo);
                const auto sqrtLo      = _mm_sqrt_pd(correctedLo);
                const auto intSqrtLo   = _mm_cvttpd_epi32(sqrtLo);
                if constexpr (Lane == 2)
                {
                    return Simd128(intSqrtLo);
                }
                else
                {
                    // Shift the upper 2 lanes to the lower lanes since the cvtepi converts values in the lower lane
                    const auto shiftedHi   = _mm_srli_si128(_register, 8);
                    const auto doubleRegHi = _mm_cvtepi32_pd(shiftedHi);
                    const auto maskHi      = _mm_cmplt_pd(doubleRegHi, zero);
                    const auto filterHi    = _mm_and_pd(offset, maskHi);
                    const auto correctedHi = _mm_add_pd(doubleRegHi, filterHi);
                    const auto sqrtHi      = _mm_sqrt_pd(correctedHi);
                    const auto intSqrtHi   = _mm_cvttpd_epi32(sqrtHi);

                    return Simd128(_mm_unpacklo_epi64(intSqrtLo, intSqrtHi));
                }
            }
        }
        else if constexpr (sizeof(DataType) == 2)
        {
            // For Epi16 we need to unpack to a 32-integral register,
            // convert it to a float register, perform the sqrt and then pack it back into a 16-bit integral register.
            // We only need to sqrt with the lower lane if lane count is less than or equal to 4.
            // For byte-wide register we need to convert them into 4(D, C, B, A) 32 bit registers and
            // perform sqrt and then packed them
            auto reg = _register;
            // Clamp the register values to greater than or equal to zero, if the register is signed.
            if constexpr (std::is_signed_v<DataType>)
            {
                reg = *max(*this, Simd128(_mm_setzero_si128()));
            }
            const auto regLo = _mm_unpacklo_saturated_custom(reg);
            // NOTE: We need to clamp negative numbers to zero since we cannot have negative sqrt(imaginary numbers)
            const auto floatRegLo = _mm_cvtepi32_ps(regLo);
            const auto sqrtLo     = _mm_sqrt_ps(floatRegLo);
            const auto intSqrtLo  = _mm_cvttps_epi32(sqrtLo);
            if constexpr (Lane <= 4)
            {
                return Simd128(_mm_packs_epi32(intSqrtLo, _mm_setzero_si128()));
            }
            else
            {
                const auto regHi      = _mm_unpackhi_saturated_custom(reg);
                const auto floatRegHi = _mm_cvtepi32_ps(regHi);
                const auto sqrtHi     = _mm_sqrt_ps(floatRegHi);
                const auto intSqrtHi  = _mm_cvttps_epi32(sqrtHi);
                return Simd128(_mm_packs_epi32(intSqrtLo, intSqrtHi));
            }
        }
        else if constexpr (sizeof(DataType) == 1)
        {
            // For byte-wide register we need to convert them into 4(D, C, B, A) 32 bit registers and
            // perform sqrt and then packed them
            // 1-bytex16 packed register => <ZYXW ,VUTS, RQPO, NMLK>
            // Unpack the last two to 2-bytex8 registers => <RQ, PO, NM, LK> (<D, C, B, A> in the code eg.)
            // Unpack them further to 4-bytex4 registers => <N, M, L, K>

            // Clamp the register values to greater than or equal to zero, if the register is signed.
            auto reg = _register;
            if constexpr (std::is_signed_v<DataType>)
            {
                reg = *max(*this, Simd128(_mm_setzero_si128()));
            }
            const auto regLo = _mm_unpacklo_saturated_custom(reg);   // Unpacked 16-bit register
            const auto regA  = _mm_unpacklo_saturated_custom(regLo); // <_, _, _, A>
            // NOTE: We need to clamp negative numbers to zero since we cannot have negative sqrt(imaginary numbers)
            const auto floatRegA  = _mm_cvtepi32_ps(regA);
            const auto sqrtA      = _mm_sqrt_ps(floatRegA);
            const auto intSqrtA   = _mm_cvttps_epi32(sqrtA);
            const auto packedRegA = _mm_packs_epi32(intSqrtA, _mm_setzero_si128());
            if constexpr (Lane <= 4)
            {
                return Simd128(_mm_packs_epi16(packedRegA, _mm_setzero_si128()));
            }
            else
            {
                const auto regB        = _mm_unpackhi_saturated_custom(regLo); // <_, _, B, _>
                const auto floatRegB   = _mm_cvtepi32_ps(regB);
                const auto sqrtB       = _mm_sqrt_ps(floatRegB);
                const auto intSqrtB    = _mm_cvttps_epi32(sqrtB);
                const auto packedRegBA = _mm_packs_epi32(intSqrtA, intSqrtB);
                if constexpr (Lane <= 8)
                {
                    return Simd128(_mm_packs_epi16(packedRegBA, _mm_setzero_si128()));
                }
                else
                {
                    const auto regHi      = _mm_unpackhi_saturated_custom(_register);
                    const auto regC       = _mm_unpacklo_saturated_custom(regHi); // <_, C, _, _>
                    const auto floatRegC  = _mm_cvtepi32_ps(regC);
                    const auto sqrtC      = _mm_sqrt_ps(floatRegC);
                    const auto intSqrtC   = _mm_cvttps_epi32(sqrtC);
                    const auto packedRegC = _mm_packs_epi32(intSqrtC, _mm_setzero_si128());
                    if constexpr (Lane <= 12)
                    {
                        return Simd128(_mm_packs_epi16(packedRegBA, packedRegC));
                    }
                    else
                    {
                        const auto regD        = _mm_unpackhi_saturated_custom(regHi); // <D, _, _, _>
                        const auto floatRegD   = _mm_cvtepi32_ps(regD);
                        const auto sqrtD       = _mm_sqrt_ps(floatRegD);
                        const auto intSqrtD    = _mm_cvttps_epi32(sqrtD);
                        const auto packedRegDC = _mm_packs_epi32(intSqrtC, intSqrtD);
                        return Simd128(_mm_packs_epi16(packedRegBA, packedRegDC));
                    }
                }
            }
        }
        else
        {
            // Note: This branch shouldn't hit for normal numbers, unless using FP16 or something
            //       which is UB in the current version of the library.
            return *this;
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<SimdBackend::ARCH_SSE2, DataType,
                                                                                    Lane>::hasNan() const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX)
            {
                return Simd128(_mm_cmp_pd(_register, _register, _CMP_UNORD_Q));
            }
            else
            {
                return Simd128(_mm_cmpunord_pd(_register, _register));
            }
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX)
            {
                return Simd128(_mm_cmp_ps(_register, _register, _CMP_UNORD_Q));
            }
            else
            {
                return Simd128(_mm_cmpunord_ps(_register, _register));
            }
        }
        else // if constexpr (std::is_integral_v<DataType>)
        {
            return Simd128(_mm_setzero_si128());
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd128<SimdBackend::ARCH_SSE2, DataType, Lane> Simd128<SimdBackend::ARCH_SSE2, DataType,
                                                                                    Lane>::hasInf() const noexcept
    {
        if constexpr (types::IsFP64<DataType>)
        {
            // Infinity: 0x7FF0000000000000 (All exponents bits set to 1)
            // For checking for infinity we cast the register to a integral, shift to remove the sign bit
            // and then check if the first 10-bits are 1 or (0xFFE0 0000 0000 0000).
            const auto shifted = cast<uint64_t>().template shiftLeft<1>();
            const auto res     = shifted == Simd128<SimdBackend::ARCH_SSE2, uint64_t, Lane>(0xFFE0000000000000ULL);
            return Simd128(_mm_castsi128_pd(*res));
        }
        else if constexpr (types::IsFP32<DataType>)
        {
            // AVL2 Library: https://github.com/vectorclass/version2/blob/master/vectorf128.h
            const auto shifted = cast<uint32_t>().template shiftLeft<1>();
            const auto res     = shifted == Simd128<SimdBackend::ARCH_SSE2, uint32_t, Lane>(0xFF000000U);
            return Simd128(_mm_castsi128_ps(*res));
        }
        else // if constexpr (std::is_integral_v<DataType>)
        {
            return Simd128(_mm_setzero_si128());
        }
    }



    ///+=+=+=+=+=+=+=+=+=+=+=+=+=
    ///    PRIVATE FUNCTIONS
    ///+=+=+=+=+=+=+=+=+=+=+=+=+=

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr __m128i Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::_mm_srl_epi8_custom(
        const __m128i reg, const uint32_t count) noexcept
    {
        // Since there is no direct shift operation for 8-bit integers
        // we need to shift using epi16 and apply a mask to the overflow
        // ([1001 1001] [1001 1001]) >> 3 = [0010 0110] [0010 0110]
        // We first mask out the bit that will be zero when shifted
        // [1111 1111] << 3 -> [1111 1000] Create the mask
        // [1001 1001] & [1111 1000] = [1001 1000] And apply it
        const auto countReg = _mm_cvtsi32_si128(count); // Load the shift value into the lower 32-bit lanes
        const auto mask     = 0xff << count;
        const auto maskReg  = _mm_set1_epi8(static_cast<int8_t>(mask));
        const auto andReg   = _mm_and_si128(reg, maskReg);
        // Now we shift the entire register to the left by shiftCount
        // since the overflown values are already zero-ed out shifting this will
        // create the correct put.
        // [1001 1000] [1001 1000] >> 3
        // [0010 1100] [0010 1100]
        return _mm_srl_epi16(andReg, countReg);
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr __m128i Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::_mm_sra_epi64_custom(
        const __m128i reg, const uint32_t count) noexcept
    {
        const auto countReg = _mm_cvtsi32_si128(count);
        // Hacker Delight Ch.2 (2-7)
        // ((x + 0x8000..00) u>> n) - (0x8000.000 u>> n)
        // For signed shift we need to first remove the sign bit or add it (if its a positive number)
        // and then we shift both the sum and the sign by the shifted amount.
        // Finally subtracting the sign will remove the sign if it was a unsigned number(or positive signed
        // number) or if it was a negative number, it will cause an signed overflow since we are subtracting a
        // smaller number from a larger number(sign will be larger), which will fill all the shifted spaces with 1.
        // -7(1101) >> 2 = -1(1111)                          | 5(0101) >> 2 = 1(0001)                        |
        // 1101 + 1000 = 0101 (Overflow)                     | 0101 + 1000  = 1101                           |
        // 0101 >> 2   = 0001                                | 1101 >> 2    = 0011                           |
        // 1000 >> 2   = 0010                                | 1000 >> 2    = 0010                           |
        // 0001 - 0010 = 1111 (Borrowed bit signed overflow) | 0011 - 0010  = 0001                           |
        const auto signReg        = _mm_set1_epi64x(0x8000000000000000ULL);
        const auto sumReg         = _mm_add_epi64(reg, signReg);
        const auto shiftedSumReg  = _mm_srl_epi64(sumReg, countReg);
        const auto shiftedSignReg = _mm_srl_epi64(signReg, countReg);
        return _mm_sub_epi64(shiftedSumReg, shiftedSignReg);
    }


    template <typename DataType, size_t Lane>
    template <uint32_t Count>
    FALCON_INLINE constexpr __m128i Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::_mm_slli_epi8_custom(
        const __m128i reg) noexcept
    {
        // 8-bit integrals have no right or left shift operations so, we need to mask out the overflow bits
        // and then do a shift using the epi16 intrinsic.
        // Since this is a left shift operations values to to the right will need to be masked.
        constexpr auto mask = 0xFF >> Count;                             // 0b0011 1111(Assume Count = 2)
        const auto maskReg  = _mm_set1_epi8(static_cast<uint8_t>(mask)); // [0b00111111, 0b00111111, ..]
        const auto andReg   = _mm_and_si128(reg, maskReg);               // [00xxxxxx, 00xxxxxx, 00xxxxxx,..]
        return _mm_slli_epi16(andReg, Count);
    }


    template <typename DataType, size_t Lane>
    template <uint32_t Count>
    FALCON_INLINE constexpr __m128i Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::_mm_srai_epi64_custom(
        const __m128i reg) noexcept
    {
        // Until AVX512F + VL there is no dedicated srai function so, we need to use xor to convert the signed
        // values to unsigned and then shifted and the sign bits.
        // Hacker Delight Ch.2 (2-7) (See a detailed example in operator>> definition)
        // t = -(x u>> 63) // This is -1(0b111..111) for negative numbers and 0 for positive numbers.
        // res = ((x xor t) u>> Count) xor t
        const auto signShifted   = _mm_srli_epi64(reg, 63); // x u>> 63
        const auto t             = _mm_sub_epi64(_mm_setzero_si128(), signShifted);
        const auto signIsolated  = _mm_xor_si128(reg, t);               // x xor t
        const auto unsignedShift = _mm_srli_epi64(signIsolated, Count); // (x xor t) u>> Count
        return _mm_xor_si128(unsignedShift, t);
    }


    template <typename DataType, size_t Lane>
    template <uint32_t Count>
    FALCON_INLINE constexpr __m128i Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::_mm_srli_epi8_custom(
        const __m128i reg) noexcept
    {
        // Since we don't have 8-bit integral logical right shift intrinsic we need to use masks to mask out all the
        // bits that are not overflown, and then use epi16 shifts.
        // See _mm_srl_epi8_custom for a detailed example.
        constexpr auto mask = 0xff << Count; // 0b11111100 (Assume Count = 2)
        const auto maskReg  = _mm_set1_epi8(static_cast<uint8_t>(mask));
        // This essentially pseudo-shifts by zeroing out the bit in that would have zeroed out if
        // performed the shift.
        const auto andReg = _mm_and_si128(reg, maskReg);
        // The final shift, shifts the binary values to their shifted place.
        return _mm_srli_epi16(andReg, Count);
    }


    template <typename DataType, size_t Lane>
    template <uint32_t Count>
    FALCON_INLINE constexpr __m128i Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::_mm_srai_epi8_custom(
        const __m128i reg) noexcept
    {
        // For arithmetic shifts we can use the XOR trick from Hackers Delight explained in operator>> or
        // _mm_srai_epi64_custom implementation.
        const auto shiftedSign = _mm_srli_epi8_custom<7>(reg);                   // Extract the sign bit to the LSB
        const auto t           = _mm_sub_epi8(_mm_setzero_si128(), shiftedSign); // t = -(x u>> 7)
        const auto unsignedReg = _mm_xor_si128(reg, t);                          // x xor t => Remove the sign bit
        const auto shiftedReg  = _mm_srli_epi8_custom<Count>(unsignedReg);       // x xor t u>> Count.
        // Add back the sign bit and return
        return _mm_xor_si128(shiftedReg, t); // ((x xor t) u>> Count) xor t
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr __m128i Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::_mm_unpacklo_saturated_custom(
        const __m128i reg) noexcept
    {
        // NOTE: Floats are not handled.
        // For unpacking signed numbers, we need to unpack a number with itself and
        // expands its sign bits through arithmetic right shift.
        // For expanding 1011 we can do
        // Unpack 1011 1011 a>> 4 bits
        // Res    1111 1011
        // Signed integrals
        if constexpr (types::IsDWord<DataType>)
        {
            /// Since there is no srai for epi64 we can create a sign bit mask
            /// with srai
            /// 1000 1011 = 1111 1111
            /// and unpack the sign bits with the register
            /// 1111 1011
            const auto signBits = _mm_srai_epi32(reg, 31);
            return _mm_unpacklo_epi32(reg, signBits);
        }
        else if constexpr (types::IsWord<DataType>)
        {
            const auto unpacked = _mm_unpacklo_epi16(reg, reg);
            return _mm_srai_epi32(unpacked, 16);
        }
        else if constexpr (types::IsByte<DataType>)
        {
            const auto unpacked = _mm_unpacklo_epi8(reg, reg);
            return _mm_srai_epi16(unpacked, 8);
        }
        // Unsigned integrals
        else if constexpr (types::IsUDWord<DataType>)
        {
            return _mm_unpacklo_epi32(reg, _mm_setzero_si128());
        }
        else if constexpr (types::IsUWord<DataType>)
        {
            return _mm_unpacklo_epi16(reg, _mm_setzero_si128());
        }
        else if constexpr (types::IsUByte<DataType>)
        {
            return _mm_unpacklo_epi8(reg, _mm_setzero_si128());
        }
        else
        {
            // 64-bit integrals are not unpacked further
            return reg;
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr __m128i Simd128<SimdBackend::ARCH_SSE2, DataType, Lane>::_mm_unpackhi_saturated_custom(
        const __m128i reg) noexcept
    {
        // NOTE: Floats are not handled.
        // For unpacking signed numbers, we need to unpack a number with itself and
        // expands its sign bits through arithmetic right shift.
        // For expanding 1011 we can do
        // Unpack 1011 1011 a>> 4 bits
        // Res    1111 1011
        // Signed integrals
        if constexpr (types::IsDWord<DataType>)
        {
            /// Since there is no srai for epi64 we can create a sign bit mask
            /// with srai
            /// 1000 1011 = 1111 1111
            /// and unpack the sign bits with the register
            /// 1111 1011
            const auto signBits = _mm_srai_epi32(reg, 31);
            return _mm_unpackhi_epi32(reg, signBits);
        }
        else if constexpr (types::IsWord<DataType>)
        {
            const auto unpacked = _mm_unpackhi_epi16(reg, reg);
            return _mm_srai_epi32(unpacked, 16);
        }
        else if constexpr (types::IsByte<DataType>)
        {
            const auto unpacked = _mm_unpackhi_epi8(reg, reg);
            return _mm_srai_epi16(unpacked, 8);
        }
        // Unsigned integrals
        else if constexpr (types::IsUDWord<DataType>)
        {
            return _mm_unpackhi_epi32(reg, _mm_setzero_si128());
        }
        else if constexpr (types::IsUWord<DataType>)
        {
            return _mm_unpackhi_epi16(reg, _mm_setzero_si128());
        }
        else if constexpr (types::IsUByte<DataType>)
        {
            return _mm_unpackhi_epi8(reg, _mm_setzero_si128());
        }
        else
        {
            // 64-bit integrals are not unpacked further
            return reg;
        }
    }

} // namespace flcn
