#pragma once
/**
 * @file Simd256AVX.inl
 * @author Alan Abraham P Kochumon
 * @date Created on: September 26, 2026
 *
 * @brief Implementation of templated functions declared in Simd256AVX.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Simd256AVX.h"
#include "falcon/simd/utils/SIMDUtils.h"

#include <immintrin.h>

namespace flcn
{
/// Macro for differentiating SIMD256 pathways based on architectural support.
#define _FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType)                                                             \
    (std::floating_point<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX) ||                                \
        CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX2

    template <typename DataType, size_t Lane>
    template <typename... Args>
        requires(SimdSafeConvertible<Args, DataType> && ...)
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane>::Simd256(Args&&... data) noexcept
    {
        /// If only single argument is provided then it will be broadcast otherwise the data will be filled
        /// from bottom to top, with zeroes in unoccupied spaces.
        if constexpr (sizeof...(data) == 1)
        {
            broadcast(std::forward<Args>(data)...);
        }
        else
        {
            set(std::forward<Args>(data)...);
        }
    }


    // template <typename DataType, size_t Lane>
    // template <typename T>
    // FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, T, Lane> Simd256<SimdBackend::ARCH_AVX, DataType,
    //                                                                          Lane>::cast() const noexcept
    // { return Simd256(_lower.template cast<T>(), _upper.template cast<T>()); }
    //
    //
    // template <typename DataType, size_t Lane>
    // template <typename T>
    // FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, T, Lane> Simd256<SimdBackend::ARCH_AVX, DataType,
    //                                                                          Lane>::cast() noexcept
    // { return Simd256(_lower.template cast<T>(), _upper.template cast<T>()); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane>::Simd256(
        const std::span<const DataType> values) noexcept
    { loadAligned(values.data()); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane>::Simd256(const DataType* pBuffer) noexcept
    { loadAligned(pBuffer); }


    template <typename DataType, size_t Lane>
    template <typename... Args>
        requires(sizeof...(Args) <= Lane) && (std::same_as<Args, DataType> && ...) &&
        (SimdSafeConvertible<Args, DataType> && ...)
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane>& Simd256<SimdBackend::ARCH_AVX, DataType,
                                                                                    Lane>::set(Args... args)
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            alignas(Alignment) DataType _data[MaxLaneCount]{ std::forward<Args>(args)... };
            if constexpr (types::IsFP64<DataType>)
            {
                _reg = _mm256_load_pd(_data);
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                _reg = _mm256_load_ps(_data);
            }
            else
            {
                _reg = _mm256_load_si256(reinterpret_cast<__m256i*>(_data));
            }
        }
        else
        {
            // Emulated Register will `set` the correct values so we don't need to assign.
            _reg.template set<Args...>(std::forward<Args>(args)...);
        }

        return *this;
    }

    // FIXME : Alignment and assert alignment in load aligned
    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_AVX, DataType, Lane>::loadAligned(
        const DataType* data) noexcept
    {
        // TODO: Add death tests
        FALCON_ASSERT_MSG(
            (reinterpret_cast<uintptr_t>(data) & (Alignment - 1)) == 0,
            "[Falcon Simd]: Loading from unaligned memory when aligned address was expected. Use load() instead.");
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                _reg = _mm256_load_pd(data);
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                _reg = _mm256_load_ps(data);
            }
            else
            {
                _reg = _mm256_load_si256(reinterpret_cast<const __m256i*>(data));
            }
        }
        else
        {
            _reg.loadAligned(data);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_AVX, DataType, Lane>::load(const DataType* data) noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                _reg = _mm256_loadu_pd(data);
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                _reg = _mm256_loadu_ps(data);
            }
            else
            {
                _reg = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(data));
            }
        }
        else
        {
            _reg.load(data);
        }
    }

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_AVX, DataType, Lane>::broadcast(DataType value) noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                _reg = _mm256_set1_pd(value);
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                _reg = _mm256_set1_ps(value);
            }
            else if constexpr (sizeof(DataType) == 8)
            {
                _reg = _mm256_set1_epi64x(value);
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                _reg = _mm256_set1_epi32(value);
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                _reg = _mm256_set1_epi16(value);
            }
            else // if constexpr(sizeof(DataType) == 2)
            {
                _reg = _mm256_set1_epi8(value);
            }
        }
        else
        {
            _reg.broadcast(value);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_AVX, DataType, Lane>::setZero() noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                _reg = _mm256_setzero_pd();
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                _reg = _mm256_setzero_ps();
            }
            else
            {
                _reg = _mm256_setzero_si256();
            }
        }
        else
        {
            _reg.setZero();
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_AVX, DataType, Lane>::setOne() noexcept
    { broadcast(DataType(simd::getAllOnes<DataType>())); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_AVX, DataType, Lane>::store(DataType* pBuffer) const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                _mm256_storeu_pd(pBuffer, _reg);
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                _mm256_storeu_ps(pBuffer, _reg);
            }
            else
            {
                _mm256_storeu_si256(reinterpret_cast<__m256i*>(pBuffer), _reg);
            }
        }
        else
        {
            _reg.store(pBuffer);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_AVX, DataType, Lane>::storeAligned(
        DataType* pBuffer) const noexcept
    {
        // TODO: Add death tests
        FALCON_ASSERT_MSG(
            (reinterpret_cast<uintptr_t>(pBuffer) & (Alignment - 1)) == 0,
            "[Falcon Simd]: Storing to unaligned memory when a aligned one was expected. Use store() instead.");
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                _mm256_store_pd(pBuffer, _reg);
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                _mm256_store_ps(pBuffer, _reg);
            }
            else
            {
                _mm256_store_si256(reinterpret_cast<__m256i*>(pBuffer), _reg);
            }
        }
        else
        {
            _reg.storeAligned(pBuffer);
        }
    }



    /**************************************
     *          GETTERS/SETTERS           *
     **************************************/

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd256<SimdBackend::ARCH_AVX, DataType, Lane>::getAt(size_t index) const noexcept
    {
        // TODO: Extract out message
        // TODO: Add death test
        FALCON_ASSERT_MSG(
            index < Lane,
            std::format("Out of bounds access. Idx must be less than {}. But it is currently {}.", Lane, index)
                .c_str());

        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            // We can use the compress and extract trick from CVL2(Agner Fog)
            // But that instruction is available only in AVX512F + AVX512VL
            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
            {
                // 1u << index creates a mask that selects the lane we want to index into
                // Eg: For index 4 the mask is 1 << 4 => 0001 0000 instead of 0000 1000
                auto mask = static_cast<__mmask8>(1u << index);
                if constexpr (types::IsFP64<DataType>)
                {
                    auto reg = _mm256_mask_compress_pd(mask, _reg);
                    return _mm256_cvtsd_f64(reg);
                }
                else if constexpr (types::IsFP32<DataType>)
                {
                    auto reg = _mm256_maskz_compress_ps(mask, _reg);
                    return _mm256_cvtss_f32(reg);
                }
                else if constexpr (sizeof(DataType) == 8)
                {
                    auto reg = _mm256_maskz_compress_epi64(mask, _reg);
                    return std::bit_cast<DataType>(_mm256_extract_epi64(reg, 0));
                }
                else if constexpr (sizeof(DataType) == 4)
                {
                    auto reg = _mm256_maskz_compress_epi32(mask, _reg);
                    return std::bit_cast<DataType>(_mm256_cvtsi256_si32(reg));
                }
                else if constexpr (sizeof(DataType) == 2)
                {
                    // Compress will zero out the upper lanes we can extract the lowest 32-bit and static cast
                    // it to a 16-bit integer.
                    // Note: epi8 version require __mask16
                    auto reg = _mm256_maskz_compress_epi16(static_cast<__mmask16>(1u << index), _reg);
                    return static_cast<DataType>(_mm256_cvtsi256_si32(reg));
                }
                else // if constexpr (sizeof(DataType) == 1)
                {
                    // Note: epi8 version of maskz_compress require __mmask32 and there is no standalone
                    //       variant of cvtsi128 for converting to 8-bit integral
                    auto reg = _mm256_maskz_compress_epi8(static_cast<__mmask32>(1u << index), _reg);
                    return static_cast<DataType>(_mm_cvtsi256_si32(reg));
                }
            }
            else
            {
                alignas(Alignment) DataType buffer[Lane]{};
                store(buffer);
                return buffer[index];
            }
        }
        else
        {
            return _reg.getAt(index);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_AVX, DataType, Lane>::setAt(const size_t index,
                                                                                       const DataType value) noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            // Stack spill and insert
            alignas(Alignment) DataType data[Lane]{};
            storeAligned(data);
            data[index] = value;
            loadAligned(data);
        }
        else
        {
            return _reg.setAt(index, value);
        }
    }


    template <typename DataType, size_t Lane>
    template <size_t Index>
        requires(Index < Lane)
    FALCON_INLINE constexpr DataType Simd256<SimdBackend::ARCH_AVX, DataType, Lane>::getAt() const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                // For floating point types if the indices are lower than half of max index
                // 2 for double, then we can cast it to an XMM register and extract values.
                // If the index is in the upper lane however, we need to extract the upper 128-bits
                // and then extract the values(with applied index offset, 2 in case of doubles).
                if constexpr (Index < 2)
                {
                    const auto reg128 = _mm_castpd_si128(_mm256_castpd256_pd128(_reg));
                    return std::bit_cast<double>(_mm_extract_epi64(reg128, Index));
                }
                else
                {
                    const auto upperReg = _mm_castpd_si128(_mm256_extractf128_pd(_reg, 1));
                    return std::bit_cast<double>(_mm_extract_epi64(upperReg, Index - 2)); // 2 is the offset.
                }
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                if constexpr (Index < 4)
                {
                    const auto reg128 = _mm256_castps256_ps128(_reg);
                    return std::bit_cast<float>(_mm_extract_ps(reg128, Index));
                }
                else
                {
                    const auto upperReg = _mm256_extractf128_ps(_reg, 1);
                    return std::bit_cast<float>(_mm_extract_ps(upperReg, Index - 4)); // 4 is the offset.
                }
            }
            else if constexpr (sizeof(DataType) == 8)
            {
                return std::bit_cast<DataType>(_mm256_extract_epi64(_reg, Index));
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                return std::bit_cast<DataType>(_mm256_extract_epi32(_reg, Index));
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                return static_cast<DataType>(_mm256_extract_epi16(_reg, Index));
            }
            else // if constexpr (sizeof(DataType) == 1)
            {
                return static_cast<DataType>(_mm256_extract_epi8(_reg, Index));
            }
        }
        else
        {
            return _reg.template getAt<Index>();
        }
    }


    template <typename DataType, size_t Lane>
    template <size_t Index>
        requires(Index < Lane)
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_AVX, DataType, Lane>::setAt(DataType value) noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                // For floating point types if the indices are lower than half of max index,
                // 2 for double, then we can cast it to an XMM register and insert the value
                // and insert the register into the lower lane.
                // If the index is in the upper lane however, we need to extract the upper 128-bits
                // and then insert the value(with applied index offset, 2 in case of doubles).
                if constexpr (Index < 2)
                {
                    auto lowerReg = _mm_castpd_si128(_mm256_castpd256_pd128(_reg));
                    lowerReg      = _mm_insert_epi64(lowerReg, std::bit_cast<uint64_t>(value), Index);
                    _reg          = _mm256_insertf128_pd(_reg, _mm_castsi128_pd(lowerReg), 0);
                }
                else
                {
                    auto upperReg = _mm_castpd_si128(_mm256_extractf128_pd(_reg, 1));
                    upperReg =
                        _mm_insert_epi64(upperReg, std::bit_cast<uint64_t>(value), Index - 2); // 2 is the offset.
                    _reg = _mm256_insertf128_pd(_reg, _mm_castsi128_pd(upperReg), 1);
                }
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                if constexpr (Index < 4)
                {
                    auto lowerReg = _mm_castps_si128(_mm256_castps256_ps128(_reg));
                    lowerReg      = _mm_insert_epi32(lowerReg, std::bit_cast<uint32_t>(value), Index);
                    _reg          = _mm256_insertf128_ps(_reg, _mm_castsi128_ps(lowerReg), 0);
                }
                else
                {
                    auto upperReg = _mm_castps_si128(_mm256_extractf128_ps(_reg, 1));
                    upperReg =
                        _mm_insert_epi32(upperReg, std::bit_cast<uint32_t>(value), Index - 4); // 4 is the offset.
                    _reg = _mm256_insertf128_ps(_reg, _mm_castsi128_ps(upperReg), 1);
                }
            }
            else if constexpr (sizeof(DataType) == 8)
            {
                _reg = _mm256_insert_epi64(_reg, value, Index);
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                _reg = _mm256_insert_epi32(_reg, value, Index);
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                _reg = _mm256_insert_epi16(_reg, value, Index);
            }
            else // if constexpr (sizeof(DataType) == 1)
            {
                _reg = _mm256_insert_epi8(_reg, value, Index);
            }
        }
        else
        {
            _reg.template setAt<Index>(value);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd256<SimdBackend::ARCH_AVX, DataType, Lane>::extractFirst() noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                return _mm256_cvtsd_f64(_reg);
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return _mm256_cvtss_f32(_reg);
            }
            else if constexpr (sizeof(DataType) == 8)
            {
                return std::bit_cast<DataType>(_mm256_extract_epi64(_reg, 0));
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                return std::bit_cast<DataType>(_mm256_cvtsi256_si32(_reg));
            }
            else // if constexpr (sizeof(DataType) == 2)
            {
                // Note: No separate instruction for si16/si8(epi/epu)
                return static_cast<DataType>(_mm256_cvtsi256_si32(_reg));
            }
        }
        else
        {
            return _reg.extractFirst();
        }
    }



    /**************************************
     *          BITWISE OPERATORS         *
     **************************************/

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<SimdBackend::ARCH_AVX, DataType,
                                                                                   Lane>::operator~() const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            Simd256 one;
            one.setOne();
            if constexpr (types::IsFP64<DataType>)
            {
                return Simd256(_mm256_andnot_pd(_reg, *one));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return Simd256(_mm256_andnot_ps(_reg, *one));
            }
            else // if constexpr (std::integral<DataType>)
            {
                return Simd256(_mm256_andnot_si256(_reg, *one));
            }
        }
        else
        {
            return ~_reg;
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator&(const Simd256 other) const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                return Simd256(_mm256_and_pd(_reg, *other));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return Simd256(_mm256_and_ps(_reg, *other));
            }
            else // if constexpr (std::integral<DataType>)
            {
                return Simd256(_mm256_and_si256(_reg, *other));
            }
        }
        else
        {
            return _reg & other._reg;
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator|(const Simd256 other) const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                return Simd256(_mm256_or_pd(_reg, *other));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return Simd256(_mm256_or_ps(_reg, *other));
            }
            else // if constexpr (std::integral<DataType>)
            {
                return Simd256(_mm256_or_si256(_reg, *other));
            }
        }
        else
        {
            return _reg | other._reg;
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator^(const Simd256 other) const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                return Simd256(_mm256_xor_pd(_reg, *other));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return Simd256(_mm256_xor_ps(_reg, *other));
            }
            else // if constexpr (std::integral<DataType>)
            {
                return Simd256(_mm256_xor_si256(_reg, *other));
            }
        }
        else
        {
            return _reg ^ other._reg;
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::andNot(const Simd256 other) const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                return Simd256(_mm256_andnot_pd(_reg, *other));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return Simd256(_mm256_andnot_ps(_reg, *other));
            }
            else // if constexpr (std::integral<DataType>)
            {
                return Simd256(_mm256_andnot_si256(_reg, *other));
            }
        }
        else
        {
            return _reg.andNot(*other);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd256<SimdBackend::ARCH_AVX, DataType, Lane>::horizontalOr() const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                // [A4, A3, A2, A1]
                // Extract the upper and lower lanes and or them
                const auto lower     = _mm256_castpd256_pd128(_reg);   // [A2, A1]
                const auto upper     = _mm256_extractf128_pd(_reg, 1); // [A4, A3]
                const auto disjunct1 = _mm_or_pd(lower, upper);        // [A2 | A4, A1 | A3]
                // Then, shuffle the upper terms(A4 | A2) to the lower lane.
                const auto shifted = _mm_shuffle_pd(disjunct1, disjunct1, 1); // [A2 | A4, A2 | A4]
                // Perform logical OR
                const auto disjunct2 = _mm_or_pd(disjunct1, shifted); // [_, A1 | A2 | A3 | A4]
                // Extract the lowest lane
                return _mm_cvtsd_f64(disjunct2);
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                const auto lower = _mm256_castps256_ps128(_reg);
                const auto upper = _mm256_extractf128_ps(_reg, 1);
                // [A8 | A4, A7 | A3, A6 | A2, A5 | A1]
                // [S4, S3, S2, S1]
                const auto disjunct1 = _mm_or_ps(lower, upper);
                // [_, _, S4, S3]
                const auto shuffle1 = _mm_shuffle_ps(disjunct1, disjunct1, _MM_SHUFFLE(2, 3, 2, 3));
                // [_, _, S2 | S4, S1 | S3]
                const auto disjunct2 = _mm_or_ps(disjunct1, shuffle1);
                // [_, _, _, S2 | S4]
                const auto shuffle2  = _mm_shuffle_ps(disjunct2, disjunct2, _MM_SHUFFLE(1, 1, 1, 1));
                const auto disjunct3 = _mm_or_ps(disjunct2, shuffle2);
                return _mm_cvtss_f32(disjunct3);
            }
            else if constexpr (sizeof(DataType) == 8)
            {
                // Extract the upper and lower lanes and disjunct them
                const auto lower     = _mm256_castsi256_si128(_reg);      // [A2, A1]
                const auto upper     = _mm256_extracti128_si256(_reg, 1); // [A4, A3]
                const auto disjunct1 = _mm_or_si128(lower, upper);        // [A2 | A4, A1 | A3]
                const auto shifted   = _mm_srli_si128(disjunct1, 8);      // [_, A2 | A4]
                const auto disjunct2 = _mm_or_si128(disjunct1, shifted);  // [_, A1 | A2 | A3 | A4]
                return std::bit_cast<DataType>(_mm_cvtsi128_si64x(disjunct2));
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                const auto lower = _mm256_castsi256_si128(_reg);
                const auto upper = _mm256_extracti128_si256(_reg, 1);
                // [A8 | A4, A7 | A3, A6 | A2, A5 | A1]
                // [S4, S3, S2, S1]
                const auto disjunct1 = _mm_or_si128(lower, upper);
                // [_, _, S4, S3]
                const auto shuffle1 = _mm_shuffle_epi32(disjunct1, _MM_SHUFFLE(2, 3, 2, 3));
                // [_, _, S2 | S4, S1 | S3]
                const auto disjunct2 = _mm_or_si128(disjunct1, shuffle1);
                // [_, _, _, S2 | S4]
                const auto shuffle2 = _mm_shuffle_epi32(disjunct2, _MM_SHUFFLE(1, 1, 1, 1));
                // [_, _, _, S2 | S4 | S1 | S3]
                const auto disjunct3 = _mm_or_si128(disjunct2, shuffle2);
                return std::bit_cast<DataType>(_mm_cvtsi128_si32(disjunct3));
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                const auto lower = _mm256_castsi256_si128(_reg);
                const auto upper = _mm256_extracti128_si256(_reg, 1);
                // [A16 | A15, A14 | A13, A12 | A11, A10 | A9, A8 | A4, A7 | A3, A6 | A2, A5 | A1]
                // [S8, S7, S6, S5, S4, S3, S2, S1]
                const auto disjunct1 = _mm_or_si128(lower, upper);
                // [_, _, _, _, S8, S7, S6, S5]
                const auto shifted1 = _mm_srli_si128(disjunct1, 8);
                // [_, _, _, _, S4 | S8, S3 | S7, S2 | S6, S1 | S5]
                const auto disjunct2 = _mm_or_si128(disjunct1, shifted1);
                // [_, _, _, _, _, _, S4 | S8, S3 | S7]
                const auto shifted2 = _mm_srli_si128(disjunct2, 4);
                // [_, _, _, _, _, _, S2 | S6 | S4 | S8, S1 | S5 | S3 | S7]
                const auto disjunct3 = _mm_or_si128(disjunct2, shifted2);
                // [_, _, _, _, _, _, _, S2 | S6 | S4 | S8]
                const auto shifted3 = _mm_srli_si128(disjunct3, 2);
                // [_, _, _, _, _, _, _, S2 | S6 | S4 | S8 | S1 | S5 | S3 | S7]
                const auto disjunct4 = _mm_or_si128(disjunct3, shifted3);
                return static_cast<DataType>(_mm_cvtsi128_si32(disjunct4));
            }
            else // if constexpr (sizeof(DataType) == 1)
            {
                const auto lower = _mm256_castsi256_si128(_reg);
                const auto upper = _mm256_extracti128_si256(_reg, 1);
                // [A32 | A31, A30 | A29, ...., A6 | A2, A5 | A1]
                // [S16, S15, S14, ..., S3, S2, S1]
                const auto disjunct1 = _mm_or_si128(lower, upper);
                // [_, _, _, _, _, _, _, _, S16, S15, S14, S13, S12, S11, S10, S9]
                const auto shifted1 = _mm_srli_si128(disjunct1, 8);
                // [_, _, _, _, _, _, _, _, S8 | S16, S7 | S15, S6 | S14, ..., S3 | S11, S2 | S10, S1 | S9]
                const auto disjunct2 = _mm_or_si128(disjunct1, shifted1);
                // [_, _, _, _, _, _, _, _, S8 | S16, S7 | S15, S6 | S14, S5 | S13]
                const auto shifted2 = _mm_srli_si128(disjunct2, 4);
                // [_, ..., S8 | S16 | S4 | S12, S3 | S11 | S7 | S15, S2 | S10 | S6 | S14, S1 | S9 | S5 | S13]
                const auto disjunct3 = _mm_or_si128(disjunct2, shifted2);
                // [_, ..., S8 | S16 | S4 | S12, S3 | S11 | S7 | S15]
                const auto shifted3 = _mm_srli_si128(disjunct3, 2);
                // [_, ..., S8 | S16 | S4 | S12 | S2 | S10 | S6 | S14, S3 | S11 | S7 | S15 | S1 | S9 | S5 | S13]
                const auto disjunct4 = _mm_or_si128(disjunct3, shifted3);
                // [_, ..., _, S8 | S16 | S4 | S12 | S2 | S10 | S6 | S14]
                const auto shifted4 = _mm_srli_si128(disjunct4, 1);
                // [_, ..., S8 | S16 | S4 | S12 | S2 | S10 | S6 | S14 | S3 | S11 | S7 | S15 | S1 | S9 | S5 | S13]
                const auto disjunct5 = _mm_or_si128(disjunct4, shifted4);
                return static_cast<DataType>(_mm_cvtsi128_si32(disjunct5));
            }
        }
        else
        {
            return Simd256(_reg.horizontalOr());
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd256<SimdBackend::ARCH_AVX, DataType, Lane>::horizontalAnd() const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                // [A4, A3, A2, A1]
                // Extract the upper and lower lanes and AND them
                const auto lower     = _mm256_castpd256_pd128(_reg);   // [A2, A1]
                const auto upper     = _mm256_extractf128_pd(_reg, 1); // [A4, A3]
                const auto conjunct1 = _mm_and_pd(lower, upper);       // [A2 & A4, A1 & A3]
                // Then, shuffle the upper terms(A4 & A2) to the lower lane.
                const auto shifted = _mm_shuffle_pd(conjunct1, conjunct1, 1); // [A2 & A4, A2 & A4]
                // Perform logical AND
                const auto conjunct2 = _mm_and_pd(conjunct1, shifted); // [_, A1 & A2 & A3 & A4]
                // Extract the lowest lane
                return _mm_cvtsd_f64(conjunct2);
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                const auto lower = _mm256_castps256_ps128(_reg);
                const auto upper = _mm256_extractf128_ps(_reg, 1);
                // [A8 & A4, A7 & A3, A6 & A2, A5 & A1]
                // [S4, S3, S2, S1]
                const auto conjunct1 = _mm_and_ps(lower, upper);
                // [_, _, S4, S3]
                const auto shuffle1 = _mm_shuffle_ps(conjunct1, conjunct1, _MM_SHUFFLE(2, 3, 2, 3));
                // [_, _, S2 & S4, S1 & S3]
                const auto conjunct2 = _mm_and_ps(conjunct1, shuffle1);
                // [_, _, _, S2 & S4]
                const auto shuffle2 = _mm_shuffle_ps(conjunct2, conjunct2, _MM_SHUFFLE(1, 1, 1, 1));
                // [_, _, _, S2 & S4 & S1 & S3]
                const auto conjunct3 = _mm_and_ps(conjunct2, shuffle2);
                return _mm_cvtss_f32(conjunct3);
            }
            else if constexpr (sizeof(DataType) == 8)
            {
                const auto lower     = _mm256_castsi256_si128(_reg);      // [A2, A1]
                const auto upper     = _mm256_extracti128_si256(_reg, 1); // [A4, A3]
                const auto conjunct1 = _mm_and_si128(lower, upper);       // [A2 & A4, A1 & A3]
                const auto shifted   = _mm_srli_si128(conjunct1, 8);      // [_, A2 & A4]
                // Or the results together
                const auto conjunct2 = _mm_and_si128(conjunct1, shifted); // [_, A1 & A2 & A3 & A4]
                return std::bit_cast<DataType>(_mm_cvtsi128_si64x(conjunct2));
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                const auto lower = _mm256_castsi256_si128(_reg);
                const auto upper = _mm256_extracti128_si256(_reg, 1);
                // [A8 & A4, A7 & A3, A6 & A2, A5 & A1]
                // [S4, S3, S2, S1]
                const auto conjunct1 = _mm_and_si128(lower, upper);
                // [_, _, S4, S3]
                const auto shuffle1 = _mm_shuffle_epi32(conjunct1, _MM_SHUFFLE(2, 3, 2, 3));
                // [_, _, S2 & S4, S1 & S3]
                const auto conjunct2 = _mm_and_si128(conjunct1, shuffle1);
                // [_, _, _, S2 & S4]
                const auto shuffle2 = _mm_shuffle_epi32(conjunct2, _MM_SHUFFLE(1, 1, 1, 1));
                // [_, _, _, S2 & S4 & S1 & S3]
                const auto conjunct3 = _mm_and_si128(conjunct2, shuffle2);
                return std::bit_cast<DataType>(_mm_cvtsi128_si32(conjunct3));
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                const auto lower = _mm256_castsi256_si128(_reg);
                const auto upper = _mm256_extracti128_si256(_reg, 1);
                // [A16 & A15, A14 & A13, A12 & A11, A10 & A9, A8 & A4, A7 & A3, A6 & A2, A5 & A1]
                // [S8, S7, S6, S5, S4, S3, S2, S1]
                const auto conjunct1 = _mm_and_si128(lower, upper);
                // [_, _, _, _, S8, S7, S6, S5]
                const auto shifted1 = _mm_srli_si128(conjunct1, 8);
                // [_, _, _, _, S4 & S8, S3 & S7, S2 & S6, S1 & S5]
                const auto conjunct2 = _mm_and_si128(conjunct1, shifted1);
                // [_, _, _, _, _, _, S4 & S8, S3 & S7]
                const auto shifted2 = _mm_srli_si128(conjunct2, 4);
                // [_, _, _, _, _, _, S2 & S6 & S4 & S8, S1 & S5 & S3 & S7]
                const auto conjunct3 = _mm_and_si128(conjunct2, shifted2);
                // [_, _, _, _, _, _, _, S2 & S6 & S4 & S8]
                const auto shifted3 = _mm_srli_si128(conjunct3, 2);
                // [_, _, _, _, _, _, _, S2 & S6 & S4 & S8 & S1 & S5 & S3 & S7]
                const auto conjunct4 = _mm_and_si128(conjunct3, shifted3);
                return static_cast<DataType>(_mm_cvtsi128_si32(conjunct4));
            }
            else // if constexpr (sizeof(DataType) == 1)
            {
                const auto lower = _mm256_castsi256_si128(_reg);
                const auto upper = _mm256_extracti128_si256(_reg, 1);
                // [A32 & A31, A30 & A29, ...., A6 & A2, A5 & A1]
                // [S16, S15, S14, ..., S3, S2, S1]
                const auto conjunct1 = _mm_and_si128(lower, upper);
                // [_, _, _, _, _, _, _, _, S16, S15, S14, S13, S12, S11, S10, S9]
                const auto shifted1 = _mm_srli_si128(conjunct1, 8);
                // [_, _, _, _, _, _, _, _, S8 & S16, S7 & S15, S6 & S14, ..., S3 & S11, S2 & S10, S1 & S9]
                const auto conjunct2 = _mm_and_si128(conjunct1, shifted1);
                // [_, _, _, _, _, _, _, _, S8 & S16, S7 & S15, S6 & S14, S5 & S13]
                const auto shifted2 = _mm_srli_si128(conjunct2, 4);
                // [_, ..., S8 & S16 & S4 & S12, S3 & S11 & S7 & S15, S2 & S10 & S6 & S14, S1 & S9 & S5 & S13]
                const auto conjunct3 = _mm_and_si128(conjunct2, shifted2);
                // [_, ..., S8 & S16 & S4 & S12, S3 & S11 & S7 & S15]
                const auto shifted3 = _mm_srli_si128(conjunct3, 2);
                // [_, ..., S8 & S16 & S4 & S12 & S2 & S10 & S6 & S14, S3 & S11 & S7 & S15 & S1 & S9 & S5 & S13]
                const auto conjunct4 = _mm_and_si128(conjunct3, shifted3);
                // [_, ..., _, S8 & S16 & S4 & S12 & S2 & S10 & S6 & S14]
                const auto shifted4 = _mm_srli_si128(conjunct4, 1);
                // [_, ..., S8 & S16 & S4 & S12 & S2 & S10 & S6 & S14 & S3 & S11 & S7 & S15 & S1 & S9 & S5 & S13]
                const auto conjunct5 = _mm_and_si128(conjunct4, shifted4);
                return static_cast<DataType>(_mm_cvtsi128_si32(conjunct5));
            }
        }
        else
        {
            return Simd256(_reg.horizontalAnd());
        }
    }



    /**************************************
     *       ARITHMETIC OPERATORS         *
     **************************************/

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator+(const Simd256 other) const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                return Simd256(_mm256_add_pd(_reg, *other));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return Simd256(_mm256_add_ps(_reg, *other));
            }
            else if constexpr (sizeof(DataType) == 8)
            {
                return Simd256(_mm256_add_epi64(_reg, *other));
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                return Simd256(_mm256_add_epi32(_reg, *other));
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                return Simd256(_mm256_add_epi16(_reg, *other));
            }
            else // if constexpr (sizeof(DataType) == 1)
            {
                return Simd256(_mm256_add_epi8(_reg, *other));
            }
        }
        else
        {
            return _reg + other._reg;
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane>& Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator+=(const Simd256 other) noexcept
    {
        *this = *this + other;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator-(const Simd256 other) const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                return Simd256(_mm256_sub_pd(_reg, *other));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return Simd256(_mm256_sub_ps(_reg, *other));
            }
            else if constexpr (sizeof(DataType) == 8)
            {
                return Simd256(_mm256_sub_epi64(_reg, *other));
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                return Simd256(_mm256_sub_epi32(_reg, *other));
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                return Simd256(_mm256_sub_epi16(_reg, *other));
            }
            else // if constexpr (sizeof(DataType) == 1)
            {
                return Simd256(_mm256_sub_epi8(_reg, *other));
            }
        }
        else
        {
            return _reg - other._reg;
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane>& Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator-=(const Simd256 other) noexcept
    {
        *this = *this - other;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<SimdBackend::ARCH_AVX, DataType,
                                                                                   Lane>::operator-() const noexcept
    {
        Simd256 zero;
        zero.setZero();
        return zero - *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator*(const Simd256 other) const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                return Simd256(_mm256_mul_pd(_reg, *other));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return Simd256(_mm256_mul_ps(_reg, *other));
            }
            else if constexpr (sizeof(DataType) == 8)
            {
                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX) // AVX512DQ + VL
                {
                    return Simd256(_mm256_mullo_epi64(_reg, *other));
                }
                else
                {
                    // Split the integer into low and high parts and multiply and join
                    // A * B = (A_Hi * 2^32 + A_Lo) * (B_Hi * 2^32 + B_Lo)
                    // (A_Hi * 2^32 * B_Low) + (A_Lo * B_Hi * 2^32) + (A_Lo * B_Lo) + (A_Hi * B_Hi * 2^64)
                    // Last term is discarded due to overflow

                    // (A_Lo * B_Lo)
                    const auto prodLo = _mm256_mul_epu32(_reg, *other);

                    // Shift the upper registers to lower lane to facilitate multiplication
                    const auto aHi = _mm256_srli_epi64(_reg, 32);
                    const auto bHi = _mm256_srli_epi64(*other, 32);
                    // (A_Hi *  B_Low)
                    const auto aHiBLo = _mm256_mul_epu32(aHi, *other);
                    // (A_Lo * B_Hi)
                    const auto aLoBHi = _mm256_mul_epu32(_reg, bHi);

                    // Add the shift
                    // (A_Hi *  B_Low) + (A_Lo * B_Hi)
                    const auto sumHi = _mm256_add_epi64(aHiBLo, aLoBHi);
                    // (A_Hi *  B_Low) + (A_Lo * B_Hi) * 2^32
                    const auto shiftedHi = _mm256_slli_epi64(sumHi, 32);

                    // Add and return the upper and lower portions
                    return Simd256(_mm256_add_epi64(prodLo, shiftedHi));
                }
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                return Simd256(_mm256_mullo_epi32(_reg, *other));
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                return Simd256(_mm256_mullo_epi16(_reg, *other));
            }
            else // if constexpr (sizeof(DataType) == 1)
            {
                // There is 8-bit integral multiplication
                // So we can do two 2 16-bit multiplication and pack the results
                // When blending we can only select the lower 8 lanes so we can directly multiply
                // without zeroing out the upper lanes
                const auto evenProd = _mm256_mullo_epi16(_reg, *other);
                // Move the integers in the upper lanes to lower lanes
                const auto oddA = _mm256_srli_epi16(_reg, 8);
                const auto oddB = _mm256_srli_epi16(*other, 8);
                auto oddProd    = _mm256_mullo_epi16(oddA, oddB);
                // Move the odd products to the upper lanes
                oddProd = _mm256_slli_epi16(oddProd, 8);


                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX) // AVX512F + BW
                {
                    // 0x5555 -> 0b010101.. which selects the 8-bits form oddReg, evenReg...
                    return Simd256(_mm_mask_mov_epi8(oddProd, 0x5555, evenProd));
                }
                const auto mask = _mm256_set1_epi16(0x00FF); // 0000 0000 1111 1111
                // TODO: Replace with blend
                return Simd256(_mm256_or_si256(_mm256_and_si256(mask, evenProd), _mm256_andnot_si256(mask, oddProd)));
            }
        }
        else
        {
            return _reg * other._reg;
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane>& Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator*=(const Simd256 other) noexcept
    {
        *this = *this * other;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::divReg(const Simd256 other) const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                return Simd256(_mm256_div_pd(_reg, *other));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return Simd256(_mm256_div_ps(_reg, *other));
            }
            else if constexpr (sizeof(DataType) == 8)
            {
                // The only possible combination lane count is 4(since we forbids initializing a 64x4 Simd256).
                // so we can manually calculate the division for 4 integers without loops
                alignas(Alignment) DataType a[Lane]{}, b[Lane]{};
                storeAligned(a);
                other.storeAligned(b);
                a[0] /= b[0];
                a[1] /= b[1];
                a[2] /= b[2];
                a[3] /= b[3];

                return Simd256(a);
            }
            else if constexpr (types::IsDWord<DataType>)
            {
                // For signed integers we need to convert them to doubles
                // and then perform the multiplication and pack them
                const auto loA = _mm256_cvtepi32_pd(_mm256_castsi256_si128(_reg));
                const auto loB = _mm256_cvtepi32_pd(_mm256_castsi256_si128(*other));

                const auto hiA = _mm256_cvtepi32_pd(_mm256_extractf128_si256(_reg, 1));
                const auto hiB = _mm256_cvtepi32_pd(_mm256_extractf128_si256(*other, 1));

                // Perform Division
                const auto loProd = _mm256_div_pd(loA, loB);
                const auto hiProd = _mm256_div_pd(hiA, hiB);

                // Convert to integrals
                const auto loInt = _mm256_castsi128_si256(_mm256_cvttpd_epi32(loProd));
                const auto hiInt = _mm256_cvttpd_epi32(hiProd);

                // Pack them
                return Simd256(_mm256_inserti128_si256(loInt, hiInt, 1));
            }
            else if constexpr (types::IsUDWord<DataType>)
            {
                // cvtepu32_pd and cvtpd_epu32 only available with AVX512F + VL
                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX)
                {
                    // For signed integers we need to convert them to doubles
                    // and then perform the multiplication and pack them
                    const auto loA = _mm256_cvtepu32_pd(_mm256_castsi256_si128(_reg));
                    const auto loB = _mm256_cvtepu32_pd(_mm256_castsi256_si128(*other));

                    const auto hiA = _mm256_cvtepu32_pd(_mm256_extractf128_si256(_reg, 1));
                    const auto hiB = _mm256_cvtepu32_pd(_mm256_extractf128_si256(*other, 1));

                    // Perform Division
                    const auto loProd = _mm256_div_pd(loA, loB);
                    const auto hiProd = _mm256_div_pd(hiA, hiB);

                    // Convert to integrals
                    const auto loInt = _mm256_castsi128_si256(_mm256_cvttpd_epu32(loProd));
                    const auto hiInt = _mm256_cvttpd_epu32(hiProd);

                    // Pack them
                    return Simd256(_mm256_inserti128_si256(loInt, hiInt, 1));
                }
                else
                {
                    // Use stack spill and perform division
                    alignas(Alignment) DataType a[Lane]{}, b[Lane]{};
                    storeAligned(a);
                    other.storeAligned(b);
                    a[0] /= b[0];
                    a[1] /= b[1];
                    a[2] /= b[2];
                    a[3] /= b[3];
                    a[4] /= b[4];
                    a[5] /= b[5];
                    a[6] /= b[6];
                    a[7] /= b[7];

                    return Simd256(a);
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
                const auto signExtLoA = _mm256_srai_epi32(_mm256_unpacklo_epi16(_reg, _reg), 16);
                const auto signExtLoB = _mm256_srai_epi32(_mm256_unpacklo_epi16(*other, *other), 16);
                const auto signExtHiA = _mm256_srai_epi32(_mm256_unpackhi_epi16(_reg, _reg), 16);
                const auto signExtHiB = _mm256_srai_epi32(_mm256_unpackhi_epi16(*other, *other), 16);

                // Convert to float
                const auto loA = _mm256_cvtepi32_ps(signExtLoA);
                const auto loB = _mm256_cvtepi32_ps(signExtLoB);
                const auto hiA = _mm256_cvtepi32_ps(signExtHiA);
                const auto hiB = _mm256_cvtepi32_ps(signExtHiB);

                // Perform division
                const auto loRes = _mm256_div_ps(loA, loB);
                const auto hiRes = _mm256_div_ps(hiA, hiB);

                // Convert to integers
                const auto loInt = _mm256_cvttps_epi32(loRes); // (Q3, Q2, Q1, Q0)
                const auto hiInt = _mm256_cvttps_epi32(hiRes); // (Q7, Q6, Q5, Q4)
                return Simd256(_mm256_packs_epi32(loInt, hiInt));
            }
            // else if constexpr (sizeof(DataType) == 1)
            // else if constexpr (types::IsUWord<DataType>)
            else
            {
                using Simd16 = Simd128<SimdBackend::ARCH_SSE2, DataType, LaneCount / 2>;
                // TODO: Update with lower/upper
                Simd16 loA(_mm256_castsi256_si128(_reg));
                Simd16 loB(_mm256_castsi256_si128(*other));
                Simd16 hiA(_mm256_extracti128_si256(_reg, 1));
                Simd16 hiB(_mm256_extracti128_si256(*other, 1));

                const Simd16 loDiv = loA.divReg(loB);
                const Simd16 hiDiv = hiA.divReg(hiB);

                const auto lo256 = _mm256_castsi128_si256(*loDiv);
                return Simd256(_mm256_inserti128_si256(lo256, *hiDiv, 1));
            }
        }
        else
        {
            return _reg.divReg(*other);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator/(const DataType scalar) const noexcept
    { return divReg(Simd256(scalar)); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane>& Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator/=(const DataType scalar) noexcept
    {
        *this = *this / scalar;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::fma(const Simd256 b, const Simd256 c) const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (FALCON_FMA_ENABLED && types::IsFP64<DataType>)
            {
                return Simd256(_mm256_fmadd_pd(_reg, *b, *c));
            }
            else if constexpr (FALCON_FMA_ENABLED && types::IsFP32<DataType>)
            {
                return Simd256(_mm256_fmadd_ps(_reg, *b, *c));
            }
            else
            {
                return (*this * b) + c;
            }
        }
        else
        {
            return Simd256(_reg.fma(*b, *c));
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd256<SimdBackend::ARCH_AVX, DataType, Lane>::horizontalAdd() const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                // [A4, A3, A2, A1]
                if constexpr (FALCON_ENABLE_HADD_INTRINSIC)
                {
                    // [A4 + A3, A4 + A3, A2 + A1, A2 + A1]
                    const auto hSum = _mm256_hadd_pd(_reg, _reg);

                    // Extract the lower lanes from both the registers; add and return.
                    const auto lower       = _mm256_castpd256_pd128(hSum);   // [A2 + A1, A2 + A1]
                    const auto upper       = _mm256_extractf128_pd(hSum, 1); // [A4 + A3, A4 + A3]
                    const auto lowerScalar = _mm_cvtsd_f64(lower);           // A2 + A1
                    const auto upperScalar = _mm_cvtsd_f64(upper);           // A4 + A3
                    return lowerScalar + upperScalar;
                }
                else
                {
                    // Extract the upper and lower lanes and sum them
                    const auto lower = _mm256_castpd256_pd128(_reg);   // [A2, A1]
                    const auto upper = _mm256_extractf128_pd(_reg, 1); // [A4, A3]
                    const auto sum1  = _mm_add_pd(lower, upper);       // [A2 + A4, A1 + A3]
                    // Then, shuffle the upper terms(A4 + A2) to the lower lane.
                    const auto shifted = _mm_shuffle_pd(sum1, sum1, 1); // [A2 + A4, A2 + A4]
                    // Add the results together
                    const auto sum2 = _mm_add_pd(sum1, shifted); // [_, A1 + A2 + A3 + A4]
                    // Extract the lowest lane
                    return _mm_cvtsd_f64(sum2);
                }
            }
            else if constexpr (types::IsFP32<DataType>)
            {

                // [A8, A7, A6, A5, A4, A3, A2, A1]
                if constexpr (FALCON_ENABLE_HADD_INTRINSIC)
                {
                    // [A8 + A7, A8 + A7, A6 + A5, A6 + A5, A4 + A3, A4 + A3, A2 + A1, A2 + A1]
                    // The sums can be rewritten as S<n>
                    // [S4, S4, S3, S3, S2, S2, S1, S1]
                    const auto hSum1 = _mm256_hadd_ps(_reg, _reg);
                    // [S4, S4, S4, S4, S2, S2, S2, S2]
                    const auto shuffled = _mm256_shuffle_ps(hSum1, hSum1, _MM_SHUFFLE(1, 3, 1, 3));
                    // [_, _, S3 + S4, S3 + S4, _, _, S1 + S2, S1 + S2]
                    const auto hSum2 = _mm256_hadd_ps(hSum1, shuffled);
                    // Extract the lower and upper lanes and sum the values in the lowest lanes
                    const auto lower = _mm256_castps256_ps128(hSum2);   // [_, _, S3 + S4, S3 + S4]
                    const auto upper = _mm256_extractf128_ps(hSum2, 1); // [_, _, S1 + S2, S1 + S2]
                    return _mm_cvtss_f32(lower) + _mm_cvtss_f32(upper);
                }
                else
                {
                    // Extract the lower and upper 128-bit lanes and add them
                    const auto lower = _mm256_castps256_ps128(_reg);
                    const auto upper = _mm256_extractf128_ps(_reg, 1);
                    // [A8 + A4, A7 + A3, A6 + A2, A5 + A1]
                    // [S4, S3, S2, S1]
                    const auto sum1 = _mm_add_ps(lower, upper);
                    // Shuffle the upper two lanes into lower lanes and sum them
                    // [_, _, S4, S3]
                    const auto shuffle1 = _mm_shuffle_ps(sum1, sum1, _MM_SHUFFLE(2, 3, 2, 3));
                    // Add the shuffled sum with the sum
                    // [_, _, S2 + S4, S1 + S3]
                    const auto sum2 = _mm_add_ps(sum1, shuffle1);
                    // Shuffle the second lane to the lowest lane
                    // [_, _, _, S2 + S4]
                    const auto shuffle2 = _mm_shuffle_ps(sum2, sum2, _MM_SHUFFLE(1, 1, 1, 1));
                    // Sum it and return the value in the lowest lane
                    // [_, _, _, S2 + S4 + S1 + S3]
                    const auto sum3 = _mm_add_ps(sum2, shuffle2);
                    return _mm_cvtss_f32(sum3);
                }
            }
            else if constexpr (sizeof(DataType) == 8)
            {
                // Extract the upper and lower lanes and sum them
                const auto lower = _mm256_castsi256_si128(_reg);      // [A2, A1]
                const auto upper = _mm256_extracti128_si256(_reg, 1); // [A4, A3]
                const auto sum1  = _mm_add_epi64(lower, upper);       // [A2 + A4, A1 + A3]
                // Then, shift the upper terms(A4 + A2) into the lower lanes.
                const auto shifted = _mm_srli_si128(sum1, 8); // [_, A2 + A4]
                // Add the results together
                const auto sum2 = _mm_add_epi64(sum1, shifted); // [_, A1 + A2 + A3 + A4]
                // Extract the lowest lane
                return std::bit_cast<DataType>(_mm_cvtsi128_si64x(sum2));
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                // [A8, A7, A6, A5, A4, A3, A2, A1]
                if constexpr (FALCON_ENABLE_HADD_INTRINSIC)
                {
                    // [A8 + A7, A8 + A7, A6 + A5, A6 + A5 | A4 + A3, A4 + A3, A2 + A1, A2 + A1]
                    // The sums can be rewritten as S<n>
                    //   3   2   1   0    3   2   1   0 (Shuffle Index)
                    // [S4, S4, S3, S3 | S2, S2, S1, S1]
                    const auto hSum1 = _mm256_hadd_epi32(_reg, _reg);
                    //   3   3   3   3    3   3   3   3 (Shuffle Index)
                    // [S4, S4, S4, S4 | S2, S2, S2, S2]
                    const auto shuffled = _mm256_shuffle_epi32(hSum1, _MM_SHUFFLE(3, 3, 3, 3));
                    // [_, _, S3 + S4, S3 + S4 | _, _, S1 + S2, S1 + S2]
                    const auto hSum2 = _mm256_hadd_epi32(hSum1, shuffled);
                    // Extract the lower and upper lanes and sum the values in the lowest lanes
                    const auto lower = _mm256_castsi256_si128(hSum2);      // [_, _, S3 + S4, S3 + S4]
                    const auto upper = _mm256_extracti128_si256(hSum2, 1); // [_, _, S1 + S2, S1 + S2]
                    return _mm_cvtsi128_si32(lower) + _mm_cvtsi128_si32(upper);
                }
                else
                {
                    // Extract the lower and upper 128-bit lanes and add them
                    const auto lower = _mm256_castsi256_si128(_reg);
                    const auto upper = _mm256_extracti128_si256(_reg, 1);
                    // [A8 + A4, A7 + A3, A6 + A2, A5 + A1]
                    // [S4, S3, S2, S1]
                    const auto sum1 = _mm_add_epi32(lower, upper);
                    // Shuffle the upper two lanes into lower lanes and sum them
                    // [_, _, S4, S3]
                    const auto shuffle1 = _mm_shuffle_epi32(sum1, _MM_SHUFFLE(2, 3, 2, 3));
                    // Add the shuffled sum with the sum
                    // [_, _, S2 + S4, S1 + S3]
                    const auto sum2 = _mm_add_epi32(sum1, shuffle1);
                    // Shuffle the second lane to the lowest lane
                    // [_, _, _, S2 + S4]
                    const auto shuffle2 = _mm_shuffle_epi32(sum2, _MM_SHUFFLE(1, 1, 1, 1));
                    // Sum it and return the value in the lowest lane
                    // [_, _, S2 + S4 + S1 + S3]
                    const auto sum3 = _mm_add_epi32(sum2, shuffle2);
                    return std::bit_cast<DataType>(_mm_cvtsi128_si32(sum3));
                }
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                // [A16, A15, A14, A13, A12, A11, A10, A9, A8, A7, A6, A5, A4, A3, A2, A1]
                if constexpr (FALCON_ENABLE_HADD_INTRINSIC)
                {
                    // [A16 + A15, A14 + A13, A12 + A11, A10 + A9, A16 + A15, A14 + A13, A12 + A11, A10 + A9 |
                    //  A8 + A7, A6 + A5, A4 + A3, A2 + A1, A8 + A7, A6 + A5, A4 + A3, A2 + A1 ]
                    // [S8, S7, S6, S5, S8, S7, S6, S5 | S4, S3, S2, S1, S4, S3, S2, S1 ]
                    const auto sum1 = _mm256_hadd_epi16(_reg, _reg);

                    // Extract the lower and upper lanes
                    const auto lower = _mm256_castsi256_si128(sum1);      // [ S4, S3, S2, S1, S4, S3, S2, S1 ]
                    const auto upper = _mm256_extracti128_si256(sum1, 1); // [S8, S7, S6, S5, S8, S7, S6, S5 ]

                    // Perform horizontal add with the 128 bit registers
                    // [S8 + S7, S6 + S5, S8 + S7, S6 + S5, S4 + S3, S2 + S1, S4 + S3, S2 + S1]
                    const auto sum2 = _mm_hadd_epi16(lower, upper);
                    // Shift the upper 2 sums to the lower two lanes
                    const auto shifted1 = _mm_srli_si128(sum2, 12); // [_, _, _, _, _, _, S8 + S7, S6 + S5]

                    // Perform horizontal add
                    // [_, _, _, S8 + S7 + S6 + S5, _, _, _, S4 + S3 + S2 + S1]
                    const auto sum3 = _mm_hadd_epi16(sum2, shifted1);
                    // Shift the sum to the lowest lane and extract and add the two sums
                    // [_, _, _, _, _, _, _, S8 + S7 + S6 + S5]
                    const auto shifted2 = _mm_srli_si128(sum3, 8);
                    return static_cast<DataType>(_mm_cvtsi128_si32(sum3)) +
                        static_cast<DataType>(_mm_cvtsi128_si32(shifted2));
                }
                else
                {
                    const auto lower = _mm256_castsi256_si128(_reg);
                    const auto upper = _mm256_extracti128_si256(_reg, 1);
                    // [A16 + A15, A14 + A13, A12 + A11, A10 + A9, A8 + A4, A7 + A3, A6 + A2, A5 + A1]
                    // [S8, S7, S6, S5, S4, S3, S2, S1]
                    const auto sum1 = _mm_add_epi16(lower, upper);
                    // [_, _, _, _, S8, S7, S6, S5]
                    const auto shifted1 = _mm_srli_si128(sum1, 8);
                    // [_, _, _, _, S4 + S8, S3 + S7, S2 + S6, S1 + S5]
                    const auto sum2 = _mm_add_epi16(sum1, shifted1);
                    // [_, _, _, _, _, _, S4 + S8, S3 + S7]
                    const auto shifted2 = _mm_srli_si128(sum2, 4);
                    // [_, _, _, _, _, _, S2 + S6 + S4 + S8, S1 + S5 + S3 + S7]
                    const auto sum3 = _mm_add_epi16(sum2, shifted2);
                    // [_, _, _, _, _, _, _, S2 + S6 + S4 + S8]
                    const auto shifted3 = _mm_srli_si128(sum3, 2);
                    // [_, _, _, _, _, _, _, S2 + S6 + S4 + S8 + S1 + S5 + S3 + S7]
                    const auto sum4 = _mm_add_epi16(sum3, shifted3);
                    return static_cast<DataType>(_mm_cvtsi128_si32(sum4));
                }
            }
            else // if constexpr (sizeof(DataType) == 1)
            {
                const auto lower = _mm256_castsi256_si128(_reg);
                const auto upper = _mm256_extracti128_si256(_reg, 1);
                // [A32 + A31, A30 + A29, ...., A6 + A2, A5 + A1]
                // [S16, S15, S14, ..., S3, S2, S1]
                const auto sum1 = _mm_add_epi8(lower, upper);
                // [_, _, _, _, _, _, _, _, S16, S15, S14, S13, S12, S11, S10, S9]
                const auto shifted1 = _mm_srli_si128(sum1, 8);
                // [_, _, _, _, _, _, _, _, S8 + S16, S7 + S15, S6 + S14, ..., S3 + S11, S2 + S10, S1 + S9]
                const auto sum2 = _mm_add_epi8(sum1, shifted1);
                // [_, _, _, _, _, _, _, _, S8 + S16, S7 + S15, S6 + S14, S5 + S13]
                const auto shifted2 = _mm_srli_si128(sum2, 4);
                // [_, ..., S8 + S16 + S4 + S12, S3 + S11 + S7 + S15, S2 + S10 + S6 + S14, S1 + S9 + S5 + S13]
                const auto sum3 = _mm_add_epi8(sum2, shifted2);
                // [_, ..., S8 + S16 + S4 + S12, S3 + S11 + S7 + S15]
                const auto shifted3 = _mm_srli_si128(sum3, 2);
                // [_, ..., S8 + S16 + S4 + S12 + S2 + S10 + S6 + S14, S3 + S11 + S7 + S15 + S1 + S9 + S5 + S13]
                const auto sum4 = _mm_add_epi8(sum3, shifted3);
                // [_, ..., _, S8 + S16 + S4 + S12 + S2 + S10 + S6 + S14]
                const auto shifted4 = _mm_srli_si128(sum4, 1);
                // [_, ..., _, S8 + S16 + S4 + S12 + S2 + S10 + S6 + S14 + S3 + S11 + S7 + S15 + S1 + S9 + S5 + S13]
                const auto sum5 = _mm_add_epi8(sum4, shifted4);
                return static_cast<DataType>(_mm_cvtsi128_si32(sum5));
            }
        }
        else
        {
            return Simd256(_reg.horizontalAdd());
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd256<SimdBackend::ARCH_AVX, DataType, Lane>::horizontalSub() const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                // NOTE: A is stored in the lowest lane.
                // To perform A-B-C-D, we can invert the flag bits of B, C, and D.
                // A + (-B) + (-C) + (-D)
                constexpr auto zero   = 0x0000000000000000ULL;
                constexpr auto sign   = 0x8000000000000000ULL;
                const auto flipMask   = _mm256_castsi256_pd(_mm256_setr_epi64x(zero, sign, sign, sign));
                const auto flippedReg = _mm256_xor_pd(_reg, flipMask);
                return Simd256(flippedReg).horizontalAdd();
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                // NOTE: A is stored in the lowest lane.
                // To perform A-B-C-D, we can invert the flag bits of B, C, and D.
                // A + (-B) + (-C) + (-D)
                constexpr auto zero = 0x00000000ULL;
                constexpr auto sign = 0x80000000ULL;
                const auto flipMask =
                    _mm256_castsi256_ps(_mm256_setr_epi32(zero, sign, sign, sign, sign, sign, sign, sign));
                const auto flippedReg = _mm256_xor_ps(_reg, flipMask);
                return Simd256(flippedReg).horizontalAdd();
            }
            else if constexpr (sizeof(DataType) == 8)
            {
                // NOTE: A is stored in the lowest lane.
                // For integrals we can use 2A - (A + B + C + D) to get A - B - C - D
                const auto a = _mm256_cvtsi256_si64(_reg);
                return (2 * a) - horizontalAdd();
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                const auto a = std::bit_cast<DataType>(_mm256_cvtsi256_si32(_reg));
                return (2 * a) - horizontalAdd();
            }
            else // if constexpr (sizeof(DataType) == 2)
            {
                const auto a = static_cast<DataType>(_mm256_cvtsi256_si32(_reg));
                return (2 * a) - horizontalAdd();
            }
        }
        else
        {
            return Simd256(_reg.horizontalSub());
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator==(const Simd256 other) const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                return Simd256(_mm256_cmp_pd(_reg, *other, _CMP_EQ_OQ));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return Simd256(_mm256_cmp_ps(_reg, *other, _CMP_EQ_OQ));
            }
            else if constexpr (sizeof(DataType) == 8)
            {
                return Simd256(_mm256_cmpeq_epi64(_reg, *other));
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                return Simd256(_mm256_cmpeq_epi32(_reg, *other));
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                return Simd256(_mm256_cmpeq_epi16(_reg, *other));
            }
            else // if constexpr (sizeof(DataType) == 1)
            {
                return Simd256(_mm256_cmpeq_epi8(_reg, *other));
            }
        }
        else
        {
            return Simd256(_reg == *other);
        }
    }



    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator!=(const Simd256 other) const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                return Simd256(_mm256_cmp_pd(_reg, *other, _CMP_NEQ_UQ));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return Simd256(_mm256_cmp_ps(_reg, *other, _CMP_NEQ_UQ));
            }
            else
            {
                return ~(*this == other);
            }
        }
        else
        {
            return Simd256(_reg != *other);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator>(const Simd256 other) const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                return Simd256(_mm256_cmp_pd(_reg, *other, _CMP_GT_OQ));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return Simd256(_mm256_cmp_ps(_reg, *other, _CMP_GT_OQ));
            }
            // Signed types
            else if constexpr (types::IsQWord<DataType>)
            {
                return Simd256(_mm256_cmpgt_epi64(_reg, *other));
            }
            else if constexpr (types::IsDWord<DataType>)
            {
                return Simd256(_mm256_cmpgt_epi32(_reg, *other));
            }
            else if constexpr (types::IsWord<DataType>)
            {
                return Simd256(_mm256_cmpgt_epi16(_reg, *other));
            }
            else if constexpr (types::IsByte<DataType>)
            {
                return Simd256(_mm256_cmpgt_epi8(_reg, *other));
            }
            // Unsigned types
            // For unsigned types we need to offset the sign bit before comparison
            else if constexpr (types::IsUQWord<DataType>)
            {
                const auto bias    = _mm256_set1_epi64x(0x8000000000000000ULL);
                const auto biasedA = _mm256_sub_epi64(_reg, bias);
                const auto biasedB = _mm256_sub_epi64(*other, bias);
                return Simd256(_mm256_cmpgt_epi64(biasedA, biasedB));
            }
            else if constexpr (types::IsUDWord<DataType>)
            {
                const auto bias    = _mm256_set1_epi32(0x80000000);
                const auto biasedA = _mm256_sub_epi32(_reg, bias);
                const auto biasedB = _mm256_sub_epi32(*other, bias);
                return Simd256(_mm256_cmpgt_epi32(biasedA, biasedB));
            }
            else if constexpr (types::IsUWord<DataType>)
            {
                const auto bias    = _mm256_set1_epi16(static_cast<uint16_t>(0x8000));
                const auto biasedA = _mm256_sub_epi16(_reg, bias);
                const auto biasedB = _mm256_sub_epi16(*other, bias);
                return Simd256(_mm256_cmpgt_epi16(biasedA, biasedB));
            }
            else // if constexpr (types::IsUByte<DataType>)
            {
                const auto bias    = _mm256_set1_epi8(static_cast<uint8_t>(0x80));
                const auto biasedA = _mm256_sub_epi8(_reg, bias);
                const auto biasedB = _mm256_sub_epi8(*other, bias);
                return Simd256(_mm256_cmpgt_epi8(biasedA, biasedB));
            }
        }
        else
        {
            return Simd256(_reg > *other);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator>=(const Simd256 other) const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                return Simd256(_mm256_cmp_pd(_reg, *other, _CMP_GE_OQ));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return Simd256(_mm256_cmp_ps(_reg, *other, _CMP_GE_OQ));
            }
            else
            {
                // A >= B == ~(A < B)
                return ~(*this < other);
            }
        }
        else
        {
            return Simd256(_reg >= *other);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator<(const Simd256 other) const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                return Simd256(_mm256_cmp_pd(_reg, *other, _CMP_LT_OQ));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return Simd256(_mm256_cmp_ps(_reg, *other, _CMP_LT_OQ));
            }
            else
            {
                // A < B == B > A
                return other > *this;
            }
        }
        else
        {
            return Simd256(_reg < *other);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator<=(const Simd256 other) const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                return Simd256(_mm256_cmp_pd(_reg, *other, _CMP_LE_OQ));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return Simd256(_mm256_cmp_ps(_reg, *other, _CMP_LE_OQ));
            }
            else
            {
                // A <= B == ~(A > B)
                return ~(*this > other);
            }
        }
        else
        {
            return Simd256(_reg <= *other);
        }
    }


    ///+=+=+=+=+=
    /// SHIFTING
    ///+=+=+=+=+=

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator<<(const uint32_t count) const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            const auto countReg = _mm_cvtsi32_si128(count);
            if constexpr (types::IsFP64<DataType>)
            {
                const auto intReg     = _mm256_castpd_si256(_reg);
                const auto shiftedReg = intrin::_mm256_sll_epi64_custom(intReg, countReg);
                return Simd256(_mm256_castsi256_pd(shiftedReg));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                const auto intReg     = _mm256_castps_si256(_reg);
                const auto shiftedReg = intrin::_mm256_sll_epi32_custom(intReg, countReg);
                return Simd256(_mm256_castsi256_ps(shiftedReg));
            }
            else if constexpr (sizeof(DataType) == 8)
            {
                return Simd256(intrin::_mm256_sll_epi64_custom(_reg, countReg));
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                return Simd256(intrin::_mm256_sll_epi32_custom(_reg, countReg));
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                return Simd256(_mm256_sll_epi16(_reg, countReg));
            }
            else // if constexpr (sizeof(DataType) == 1)
            {


                return Simd256(intrin::_mm256_sll_epi8_custom(_reg, count));
            }
        }
        else
        {
            return Simd256(_reg << count);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane>& Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator<<=(const uint32_t count) noexcept
    {
        *this = *this << count;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator>>(const uint32_t count) const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            const auto countReg = _mm_cvtsi32_si128(count);
            if constexpr (types::IsFP64<DataType>)
            {
                const auto intReg     = _mm256_castpd_si256(_reg);
                const auto shiftedReg = intrin::_mm256_sra_epi64_custom(intReg, countReg);
                return Simd256(_mm256_castsi256_pd(shiftedReg));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                const auto intReg     = _mm256_castps_si256(_reg);
                const auto shiftedReg = intrin::_mm256_sra_epi32_custom(intReg, countReg);
                return Simd256(_mm256_castsi256_ps(shiftedReg));
            }
            else if constexpr (types::IsQWord<DataType>)
            {
                return Simd256(intrin::_mm256_sra_epi64_custom(_reg, countReg));
            }
            else if constexpr (types::IsDWord<DataType>)
            {
                return Simd256(intrin::_mm256_sra_epi32_custom(_reg, countReg));
            }
            else if constexpr (types::IsWord<DataType>)
            {
                return Simd256(_mm256_sra_epi16(_reg, countReg));
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
                const auto isolatedSignBit = intrin::_mm256_srli_epi8_custom<7>(_reg);
                const auto tReg            = _mm256_sub_epi8(_mm256_setzero_si256(), isolatedSignBit);
                const auto xXorTReg        = _mm256_xor_si256(_reg, tReg);
                const auto shiftedXor      = intrin::_mm256_srl_epi8_custom(xXorTReg, count);
                return Simd256(_mm256_xor_si256(shiftedXor, tReg));
            }
            else // if (std::is_unsigned_v<DataType>)
            {
                return shiftRightLogical(count);
            }
        }
        else
        {
            return Simd256(_reg << count);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane>& Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator>>=(const uint32_t count) noexcept
    {
        *this = *this >> count;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::shiftRightLogical(const uint32_t count) const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            const auto countReg = _mm_cvtsi32_si128(count);
            if constexpr (types::IsFP64<DataType>)
            {
                const auto intReg     = _mm256_castpd_si256(_reg);
                const auto shiftedReg = intrin::_mm256_srl_epi64_custom(intReg, countReg);
                return Simd256(_mm256_castsi256_pd(shiftedReg));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                const auto intReg     = _mm256_castps_si256(_reg);
                const auto shiftedReg = intrin::_mm256_srl_epi32_custom(intReg, countReg);
                return Simd256(_mm256_castsi256_ps(shiftedReg));
            }
            else if constexpr (sizeof(DataType) == 8)
            {
                return Simd256(intrin::_mm256_srl_epi64_custom(_reg, countReg));
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                return Simd256(intrin::_mm256_srl_epi32_custom(_reg, countReg));
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                return Simd256(_mm256_srl_epi16(_reg, countReg));
            }
            else // if constexpr (sizeof(DataType) == 1)
            {
                return Simd256(intrin::_mm256_srl_epi8_custom(_reg, count));
            }
        }
        else
        {
            return Simd256(_reg.shiftRightLogical(count));
        }
    }


    template <typename DataType, size_t Lane>
    template <uint32_t Count>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<SimdBackend::ARCH_AVX, DataType,
                                                                                   Lane>::shiftLeft() const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                const auto intReg     = _mm256_castpd_si256(_reg);
                const auto shiftedReg = intrin::_mm256_slli_epi64_custom<Count>(intReg);
                return Simd256(_mm256_castsi256_pd(shiftedReg));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                const auto intReg     = _mm256_castps_si256(_reg);
                const auto shiftedReg = intrin::_mm256_slli_epi32_custom<Count>(intReg);
                return Simd256(_mm256_castsi256_ps(shiftedReg));
            }
            else if constexpr (sizeof(DataType) == 8)
            {
                return Simd256(intrin::_mm256_slli_epi64_custom<Count>(_reg));
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                return Simd256(intrin::_mm256_slli_epi32_custom<Count>(_reg));
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                return Simd256(_mm256_slli_epi16(_reg, Count));
            }
            else // if constexpr (sizeof(DataType) == 1)
            {
                return Simd256(intrin::_mm256_slli_epi8_custom<Count>(_reg));
            }
        }
        else
        {
            return Simd256(_reg.template shiftLeft<Count>());
        }
    }


    template <typename DataType, size_t Lane>
    template <uint32_t Count>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::shiftRightArithmetic() const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                const auto intReg     = _mm256_castpd_si256(_reg);
                const auto shiftedReg = intrin::_mm256_srai_epi64_custom<Count>(intReg);
                return Simd256(_mm256_castsi256_pd(shiftedReg));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                const auto intReg     = _mm256_castps_si256(_reg);
                const auto shiftedReg = intrin::_mm256_srai_epi32_custom<Count>(intReg);
                return Simd256(_mm256_castsi256_ps(shiftedReg));
            }
            else if constexpr (types::IsQWord<DataType>)
            {
                return Simd256(intrin::_mm256_srai_epi64_custom<Count>(_reg));
            }
            else if constexpr (types::IsDWord<DataType>)
            {
                return Simd256(intrin::_mm256_srai_epi32_custom<Count>(_reg));
            }
            else if constexpr (types::IsWord<DataType>)
            {
                return Simd256(_mm256_srai_epi16(_reg, Count));
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
                const auto isolatedSignBit = intrin::_mm256_srli_epi8_custom<7>(_reg);
                const auto tReg            = _mm256_sub_epi8(_mm256_setzero_si256(), isolatedSignBit);
                const auto xXorTReg        = _mm256_xor_si256(_reg, tReg);
                const auto shiftedXor      = intrin::_mm256_srli_epi8_custom<Count>(xXorTReg);
                return Simd256(_mm256_xor_si256(shiftedXor, tReg));
            }
            else // if (std::is_unsigned_v<DataType>)
            {
                return shiftRightLogical<Count>();
            }
        }
        else
        {
            return Simd256(_reg.template shiftRightArithmetic<Count>());
        }
    }


    template <typename DataType, size_t Lane>
    template <uint32_t Count>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::shiftRightLogical() const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                const auto intReg     = _mm256_castpd_si256(_reg);
                const auto shiftedReg = intrin::_mm256_srli_epi64_custom<Count>(intReg);
                return Simd256(_mm256_castsi256_pd(shiftedReg));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                const auto intReg     = _mm256_castps_si256(_reg);
                const auto shiftedReg = intrin::_mm256_srli_epi32_custom<Count>(intReg);
                return Simd256(_mm256_castsi256_ps(shiftedReg));
            }
            else if constexpr (sizeof(DataType) == 8)
            {
                return Simd256(intrin::_mm256_srli_epi64_custom<Count>(_reg));
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                return Simd256(intrin::_mm256_srli_epi32_custom<Count>(_reg));
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                return Simd256(_mm256_srli_epi16(_reg, Count));
            }
            else // if constexpr (sizeof(DataType) == 1)
            {
                return Simd256(intrin::_mm256_srli_epi8_custom<Count>(_reg));
            }
        }
        else
        {
            return Simd256(_reg.template shiftRightLogical<Count>());
        }
    }


    /// +-------------------------------------------------------------------------------------------------------------+
    /// |                                           BLENDING AND SHUFFLING                                            |
    /// +-------------------------------------------------------------------------------------------------------------+

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::blend(const Simd256 other, const Simd256 mask) const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                return Simd256(_mm256_blendv_pd(_reg, *other, *mask));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return Simd256(_mm256_blendv_ps(_reg, *other, *mask));
            }
            else
            {
                return Simd256(_mm256_blendv_epi8(_reg, *other, *mask));
            }
        }
        else
        {
            return Simd256(_reg.blend(other, mask));
        }
    }


    template <typename DataType, size_t Lane>
    template <BlendMask32_t Mask>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::blend(const Simd256 other) const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (types::IsFP64<DataType>)
            {
                constexpr auto Imm8 = simd::packToNBits<4>(Mask);
                return Simd256(_mm256_blend_pd(_reg, *other, Imm8));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                constexpr auto Imm8 = simd::packToNBits<8>(Mask);
                return Simd256(_mm256_blend_ps(_reg, *other, Imm8));
            }
            else if constexpr (sizeof(DataType) == 8)
            {
                constexpr auto Imm8 = simd::packToNBits<4>(Mask);
                const auto dblReg1  = _mm256_castsi256_pd(_reg);
                const auto dblReg2  = _mm256_castsi256_pd(*other);
                return Simd256(_mm256_castpd_si256(_mm256_blend_pd(dblReg1, dblReg2, Imm8)));
            }
            else if constexpr (sizeof(DataType) == 4)
            {
                constexpr auto Imm8 = simd::packToNBits<8>(Mask);
                return Simd256(_mm256_blend_epi32(_reg, *other, Imm8));
            }
            else if constexpr (sizeof(DataType) == 2)
            {
                // _mm256_blend only works on 128-bits using the same mask for lower and upper lanes
                // so we will need to split the masks and do 2 blends on the upper and lower lanes
                // and then combine them.
                // NOTE: We need to pack these to 16 bits and not 8 because packing to 8 bits means we take the LSB
                //       from groups of 4 and not groups of 2, essentially cutting the mask information in half.
                //       0000 00000 0000 0000 1111 1100 1111 0011, if we pack to 8 then we would get 0000 1011,
                //       but the mask value needs to be 1110 1101(LSB from groups of 2)
                constexpr auto Imm8Lower = simd::packToNBits<16>(Mask & 0x0000FFFF);
                constexpr auto Imm8Upper = simd::packToNBits<16>(Mask >> 16);
                // Perform the blending
                const auto lowerBlend = _mm256_blend_epi16(_reg, *other, Imm8Lower);
                // Cast the lower portion to a 128-bit register to insert it into the upper blended register.
                const auto lowerCast  = _mm256_castsi256_si128(lowerBlend);
                const auto upperBlend = _mm256_blend_epi16(_reg, *other, Imm8Upper);
                // Blend the lower lanes of the register
                return Simd256(_mm256_inserti128_si256(upperBlend, lowerCast, 0));
            }
            else // if constexpr (sizeof(DataType) == 1)
            {
                // Expand the mask in a 256 bit register
                constexpr auto mask = simd::expandEightFold(Mask);
                const auto maskReg  = _mm256_set_epi64x(mask.quad3, mask.quad2, mask.quad1, mask.quad0);
                // Blend using blendv
                return Simd256(_mm256_blendv_epi8(_reg, *other, maskReg));
            }
        }
        else
        {
            return Simd256(_reg.template blend<Mask>(other));
        }
    }


    // template <typename DataType, size_t Lane>
    // template <uint8_t... ShuffleIndex>
    // FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<SimdBackend::ARCH_AVX,
    // DataType,
    //                                                                                 Lane>::shuffle() const
    //                                                                                 noexcept
    // {
    //     static_assert(sizeof...(ShuffleIndex) == Lane && "There must be <Lane> shuffle indices.");
    //     static_assert(((ShuffleIndex < Lane) && ...) && "Indices must be between 0(inclusive) and
    //     <Lane>(exclusive).");
    //
    //     // For shuffling we need to perform a normalized shuffle(range between 0 - Max_128_Lane_Count)
    //     // and then use a mask to select values from appropriate register lanes.
    //
    //     // Packed indexing is not support until C++26, we need to use this workaround
    //     // For shuffling with two indices we need to transform the array values(indices)
    //     // to be between 0 - MAX_LANE_COUNT(exclusive)
    //     constexpr uint8_t normalizedIndices[MaxLaneCount]{ { (
    //         static_cast<uint8_t>(ShuffleIndex % Max128BitLaneCount))... } };
    //
    //     // Masks for selecting values for the upper and lower 128-bit lanes.
    //     const auto makeMask = [&]<size_t Offset, size_t... Index>(std::index_sequence<Index...>) {
    //         constexpr uint8_t ShuffleIndices[MaxLaneCount]{ { ShuffleIndex... } };
    //         return simd::makeBlendMask32<Max128BitLaneCount,
    //                                      (ShuffleIndices[Offset + Index] >= Max128BitLaneCount)...>();
    //     };
    //     // [up_mask1, up_mask0, lo_mask1, lo_mask0]
    //     constexpr BlendMask32_t upperMask =
    //         makeMask.template operator()<Max128BitLaneCount>(std::make_index_sequence<Max128BitLaneCount>{});
    //     constexpr BlendMask32_t lowerMask =
    //         makeMask.template operator()<0>(std::make_index_sequence<Max128BitLaneCount>{});
    //
    //     // low          hi
    //     // | a1 | b1 | | c1 | d1 |
    //     // -----------------------
    //     // lolo | a1 | b1 | <--
    //     // lohi | a1 | b1 |    | <===
    //     // hilo | c1 | d1 | <--     |
    //     // hihi | c1 | d1 |      <===
    //     // Select hilo if Mask[i] is true and lolo otherwise
    //     // Select hihi if Mask[i] is true and lohi otherwise
    //
    //     // NOTE: Lambda needs to invoked using .template operator() since the compiler can get confused
    //     //       by the <0> as less operator.
    //
    //     // Upper part of the register with lower and upper indices(hilo, lohi)
    //     auto shuffleUpper = [&]<size_t Offset, size_t... Index>(std::index_sequence<Index...>) {
    //         return _upper.template shuffle<normalizedIndices[Offset + Index]...>();
    //     };
    //     auto upperShuffledWithUpperIndices =
    //         shuffleUpper.template
    //         operator()<Max128BitLaneCount>(std::make_index_sequence<UPPER_LANE_COUNT>{});
    //     auto upperShuffledWithLowerIndices =
    //         shuffleUpper.template operator()<0>(std::make_index_sequence<UPPER_LANE_COUNT>{});
    //
    //     // Lower part of register with lower and upper indices (lolo, lohi)
    //     auto shuffleLower = [&]<size_t Offset, size_t... Index>(std::index_sequence<Index...>) {
    //         return _lower.template shuffle<normalizedIndices[Offset + Index]...>();
    //     };
    //     auto lowerShuffledWithUpperIndices =
    //         shuffleLower.template
    //         operator()<Max128BitLaneCount>(std::make_index_sequence<LOWER_LANE_COUNT>{});
    //     auto lowerShuffledWithLowerIndices =
    //         shuffleLower.template operator()<0>(std::make_index_sequence<LOWER_LANE_COUNT>{});
    //
    //     // select(lolo, hilo, mask), select(lohi, hihi, mask)
    //     return Simd256{ lowerShuffledWithLowerIndices.template
    //     blend<lowerMask>(upperShuffledWithLowerIndices),
    //                     lowerShuffledWithUpperIndices.template
    //                     blend<upperMask>(upperShuffledWithUpperIndices) };
    // }
    //
    //
    // template <typename DataType, size_t Lane>
    // FALCON_INLINE constexpr DataType Simd256<SimdBackend::ARCH_AVX, DataType, Lane>::horizontalMin() const
    // noexcept { return std::min(_lower.horizontalMin(), _upper.horizontalMin()); }
    //
    //
    // template <typename DataType, size_t Lane>
    // FALCON_INLINE constexpr DataType Simd256<SimdBackend::ARCH_AVX, DataType, Lane>::horizontalMax() const
    // noexcept { return std::max(_lower.horizontalMax(), _upper.horizontalMax()); }
    //
    //
    // template <typename DataType, size_t Lane>
    // FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<SimdBackend::ARCH_AVX,
    // DataType,
    //                                                                                 Lane>::abs() const
    //                                                                                 noexcept
    // { return Simd256(_lower.abs(), _upper.abs()); }
    //
    //
    // template <typename DataType, size_t Lane>
    // FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<SimdBackend::ARCH_AVX,
    // DataType,
    //                                                                                 Lane>::sqrt() const
    //                                                                                 noexcept
    // { return Simd256(_lower.sqrt(), _upper.sqrt()); }
    //
    //
    // template <typename DataType, size_t Lane>
    // FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<SimdBackend::ARCH_AVX,
    // DataType,
    //                                                                                 Lane>::hasNan() const
    //                                                                                 noexcept
    // { return Simd256(_lower.hasNan(), _upper.hasNan()); }
    //
    //
    // template <typename DataType, size_t Lane>
    // FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<SimdBackend::ARCH_AVX,
    // DataType,
    //                                                                                 Lane>::hasInf() const
    //                                                                                 noexcept
    // { return Simd256(_lower.hasInf(), _upper.hasInf()); }

#undef _FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC

} // namespace flcn
