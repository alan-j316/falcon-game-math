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


#include "CustomX86Intrin.inl"
#include "falcon/simd/core/x86/Simd256SSE.h"
#include "falcon/simd/utils/SIMDUtils.h"
#include "internal/MaskHelpers.h"

#include <immintrin.h>

namespace flcn
{
/// Macro for differentiating SIMD256 pathways based on architectural support.
#define _FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType)                                                             \
    (std::floating_point<DataType> && CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX) ||                                \
        (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX2)


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


    template <typename DataType, size_t Lane>
    template <typename T>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, T, Lane> Simd256<SimdBackend::ARCH_AVX, DataType,
                                                                            Lane>::cast() const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (std::is_same_v<DataType, T>)
            {
                return Simd256(_reg);
            }
            else if constexpr (types::IsFP64<DataType>)
            {
                if constexpr (types::IsFP32<T>)
                {
                    return Simd256<SimdBackend::ARCH_AVX, T, Lane>(_mm256_castpd_ps(_reg));
                }
                else if constexpr (std::is_integral_v<T>)
                {
                    if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX2)
                    {
                        return Simd256<SimdBackend::ARCH_AVX, T, Lane>(_mm256_castpd_si256(_reg));
                    }
                    else
                    {
                        // For "casting" float-reg to integral we need to extract the 128-bit lanes
                        // and initialize the fallback/emulated register
                        const auto loLane = Simd128<SimdBackend::ARCH_SSE2, T, Lane / 2>(
                            _mm_castpd_si128(_mm256_castpd256_pd128(_reg)));
                        const auto hiLane = Simd128<SimdBackend::ARCH_SSE2, T, Lane / 2>(
                            _mm_castpd_si128(_mm256_extractf128_pd(_reg, 1)));
                        const auto emulated =
                            typename simd::internal::Simd256Register<SimdBackend::ARCH_AVX, T, Lane>::Type(loLane,
                                                                                                           hiLane);
                        return Simd256<SimdBackend::ARCH_AVX, T, Lane>(emulated);
                    }
                }
                else
                {
                    return Simd256<SimdBackend::ARCH_AVX, T, Lane>(_reg);
                }
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                if constexpr (types::IsFP64<T>)
                {
                    return Simd256<SimdBackend::ARCH_AVX, T, Lane>(_mm256_castps_pd(_reg));
                }
                else if constexpr (std::is_integral_v<T>)
                {
                    if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX2)
                    {
                        return Simd256<SimdBackend::ARCH_AVX, T, Lane>(_mm256_castps_si256(_reg));
                    }
                    else
                    {
                        // For "casting" float-reg to integral we need to extract the 128-bit lanes
                        // and initialize the fallback/emulated register
                        const auto loLane = Simd128<SimdBackend::ARCH_SSE2, T, Lane / 2>(
                            _mm_castps_si128(_mm256_castps256_ps128(_reg)));
                        const auto hiLane = Simd128<SimdBackend::ARCH_SSE2, T, Lane / 2>(
                            _mm_castps_si128(_mm256_extractf128_ps(_reg, 1)));
                        const auto emulated =
                            typename simd::internal::Simd256Register<SimdBackend::ARCH_AVX, T, Lane>::Type(loLane,
                                                                                                           hiLane);
                        return Simd256<SimdBackend::ARCH_AVX, T, Lane>(emulated);
                    }
                }
                else
                {
                    return Simd256<SimdBackend::ARCH_AVX, T, Lane>(_reg);
                }
            }
            else // Integral to floating point.
            {
                if constexpr (types::IsFP64<T>)
                {
                    if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX2)
                    {
                        return Simd256<SimdBackend::ARCH_AVX, T, Lane>(_mm256_castsi256_pd(_reg));
                    }
                    else
                    {
                        // For converting a Simd256 emulated into a native register we need extract them
                        // and set the upper and lower lanes
                        const auto loLane = *((*_reg).lower);
                        const auto hiLane = *((*_reg).upper);
                        const auto castReg = _mm256_castpd_si256(_mm256_setr_m128d(loLane, hiLane));
                        return Simd256<SimdBackend::ARCH_AVX, T, Lane>(castReg);
                    }
                }
                else if constexpr (types::IsFP32<T>)
                {
                    if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX2)
                    {
                        return Simd256<SimdBackend::ARCH_AVX, T, Lane>(_mm256_castsi256_ps(_reg));
                    }
                    else
                    {
                        // For converting a Simd256 emulated into a native register we need extract them
                        // and set the upper and lower lanes
                        const auto loLane = *((*_reg).lower);
                        const auto hiLane = *((*_reg).upper);
                        const auto castReg = _mm256_castps_si256(_mm256_setr_m128(loLane, hiLane));
                        return Simd256<SimdBackend::ARCH_AVX, T, Lane>(castReg);
                    }
                }
                else
                {
                    return Simd256<SimdBackend::ARCH_AVX, T, Lane>(_reg);
                }
            }
        }
        else
        {
            return Simd256<SimdBackend::ARCH_AVX, T, Lane>(_reg.template cast<T>());
        }
    }


    template <typename DataType, size_t Lane>
    template <typename T>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, T, Lane> Simd256<SimdBackend::ARCH_AVX, DataType,
                                                                            Lane>::cast() noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            if constexpr (std::is_same_v<DataType, T>)
            {
                return Simd256(_reg);
            }
            else if constexpr (types::IsFP64<DataType>)
            {
                if constexpr (types::IsFP32<T>)
                {
                    return Simd256<SimdBackend::ARCH_AVX, T, Lane>(_mm256_castpd_ps(_reg));
                }
                else if constexpr (std::is_integral_v<T>)
                {
                    return Simd256<SimdBackend::ARCH_AVX, T, Lane>(_mm256_castpd_si256(_reg));
                }
                else
                {
                    return Simd256<SimdBackend::ARCH_AVX, T, Lane>(_reg);
                }
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                if constexpr (types::IsFP64<T>)
                {
                    return Simd256<SimdBackend::ARCH_AVX, T, Lane>(_mm256_castps_pd(_reg));
                }
                else if constexpr (std::is_integral_v<T>)
                {
                    return Simd256<SimdBackend::ARCH_AVX, T, Lane>(_mm256_castps_si256(_reg));
                }
                else
                {
                    return Simd256<SimdBackend::ARCH_AVX, T, Lane>(_reg);
                }
            }
            else // Integral to floating point.
            {
                if constexpr (types::IsFP64<T>)
                {
                    return Simd256<SimdBackend::ARCH_AVX, T, Lane>(_mm256_castsi256_pd(_reg));
                }
                else if constexpr (types::IsFP32<T>)
                {
                    return Simd256<SimdBackend::ARCH_AVX, T, Lane>(_mm256_castsi256_ps(_reg));
                }
                else
                {
                    return Simd256<SimdBackend::ARCH_AVX, T, Lane>(_reg);
                }
            }
        }
        else
        {
            // Emulated Register will `set` the correct values so we don't need to assign.
            return Simd256<SimdBackend::ARCH_AVX, T, Lane>(_reg.template cast<T>());
        }
    }


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
                    //       variant of cvtsi256 for converting to 8-bit integral
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
            return Simd256(~_reg);
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
            return Simd256(_reg & other._reg);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane>& Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator&=(Simd256 other) noexcept
    {
        *this = *this & other;
        return *this;
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
            return Simd256(_reg | other._reg);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane>& Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator|=(Simd256 other) noexcept
    {
        *this = *this | other;
        return *this;
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
            return Simd256(_reg ^ other._reg);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane>& Simd256<
        SimdBackend::ARCH_AVX, DataType, Lane>::operator^=(Simd256 other) noexcept
    {
        *this = *this ^ other;
        return *this;
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
            return Simd256(_reg.andNot(*other));
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
                return std::bit_cast<DataType>(_mm_cvtsi128_si64(disjunct2));
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
            return _reg.horizontalOr();
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
                return std::bit_cast<DataType>(_mm_cvtsi128_si64(conjunct2));
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
            return _reg.horizontalAnd();
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
            return Simd256(_reg + other._reg);
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
            return Simd256(_reg - other._reg);
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
            return Simd256(_reg * other._reg);
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
            return Simd256(_reg.divReg(*other));
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
                return std::bit_cast<DataType>(_mm_cvtsi128_si64(sum2));
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
            return _reg.horizontalAdd();
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
                constexpr auto zero = static_cast<int>(0x00000000ULL);
                constexpr auto sign = static_cast<int>(0x80000000ULL);
                const auto flipMask =
                    _mm256_castsi256_ps(_mm256_setr_epi32(zero, sign, sign, sign, sign, sign, sign, sign));
                const auto flippedReg = _mm256_xor_ps(_reg, flipMask);
                return Simd256(flippedReg).horizontalAdd();
            }
            else if constexpr (sizeof(DataType) == 8)
            {
                // NOTE: A is stored in the lowest lane.
                // For integrals we can use 2A - (A + B + C + D) to get A - B - C - D
                const auto a = _mm_cvtsi128_si64(_mm256_castsi256_si128(_reg));
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
            return _reg.horizontalSub();
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
            return Simd256(_reg >> count);
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
            return Simd256(_reg.blend(*other, *mask));
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
            return Simd256(_reg.template blend<Mask>(*other));
        }
    }


    template <typename DataType, size_t Lane>
    template <uint8_t... PermuteIndex>
        requires(sizeof...(PermuteIndex) == Lane)
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<SimdBackend::ARCH_AVX, DataType,
                                                                                   Lane>::permute() const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            constexpr uint8_t indices[sizeof...(PermuteIndex)]{ PermuteIndex... };

            /// We can assert if the permute are in-bounds i.e they must be less than the lane count.
            // constexpr auto inBounds = [&]<size_t... Index>(std::index_sequence<Index...>) {
            //     return ((shuffleIndices[Index] < Lane) && ...);
            // };
            constexpr bool inBounds = ((PermuteIndex < Lane) && ...);
            static_assert(inBounds && "Invalid Shuffle Index. Must be between 0 and <Lane - 1>");

            /// No permute is required if the indices are in ascending order
            constexpr auto requireNoPermute = [&]<size_t... Index>(std::index_sequence<Index...>) constexpr {
                return ((indices[Index] == Index) && ...);
            }(std::make_index_sequence<sizeof...(PermuteIndex)>());

            /// There is no lane cross over if the indices for the upper half are above the middle index(inclusive)
            /// and for the lower half are below the middle index.
            /// For example for a register with 8 lanes, the middle boundary is 4
            /// So all the indices in the lower 4 lanes must be less than 4 and in the upper lanes must be greater
            /// than 4.
            constexpr auto noLaneCross = [&]<size_t... Index>(std::index_sequence<Index...>) constexpr {
                constexpr auto middleBoundary = Lane / 2;
                return (((Index < middleBoundary && indices[Index] < middleBoundary) ||
                         (Index >= middleBoundary && indices[Index] >= middleBoundary)) &&
                        ...);
            }(std::make_index_sequence<sizeof...(PermuteIndex)>());

            /// Check whether the upper and lower indices are the same.
            /// Eg [7, 6, 5, 4 | 3, 2, 1, 0] (4 is the 0th index in the upper lane)
            constexpr auto hasSameUpperAndLowerIndices = [&]<size_t... Index>(std::index_sequence<Index...>) constexpr {
                const auto offset = sizeof...(Index) / 2;
                return ((indices[Index] == (indices[offset + Index] % offset)) && ...);
            }(std::make_index_sequence<sizeof...(PermuteIndex) / 2>());

            if constexpr (requireNoPermute)
            {
                return *this;
            }
            else if constexpr (noLaneCross)
            {
                // If there are no lane cross we an use permute on double precision regardless of whether have
                // the same selection for upper and lower boundaries since `_mm256_permute_pd` doesn't reuse
                // the selection bits but for floats.
                // For integrals we can stitch together the _mm256_shuffle_epi8 to perform both same index and
                // different index shuffle for upper and lower lanes.
                if constexpr (types::IsFP64<DataType>)
                {
                    // NOTE: Since the permutation indices needs to either 0 or 1 we need to perform modulo
                    //       arithmetic to ensure the upper indices are written in-terms of them.
                    //       For example, 3 would be the 1st index of the upper lane.
                    //       [3, 2 | 1, 0] -> [1, 0 | 1, 0]
                    constexpr auto PERMUTE_IDX =
                        (indices[3] % 2) << 3 | (indices[2] % 2) << 2 | indices[1] << 1 | indices[0];
                    return Simd256(_mm256_permute_pd(_reg, PERMUTE_IDX));
                }
                else if constexpr (sizeof(DataType) == 2)
                {
                    // While there are shuffelo and shufflehi epi16 instructions the immediate values
                    // only switch the 64-bits out of the 128 bits but we can stitch together a epi8 instruction
                    // like what is done with epi64
                    const auto idx =
                        _mm256_set_epi8((indices[15] * 2) + 1, indices[15] * 2, (indices[14] * 2) + 1, indices[14] * 2,
                                        (indices[13] * 2) + 1, indices[13] * 2, (indices[12] * 2) + 1, indices[12] * 2,
                                        (indices[11] * 2) + 1, indices[11] * 2, (indices[10] * 2) + 1, indices[10] * 2,
                                        (indices[9] * 2) + 1, indices[9] * 2, (indices[8] * 2) + 1, indices[8] * 2,
                                        (indices[7] * 2) + 1, indices[7] * 2, (indices[6] * 2) + 1, indices[6] * 2,
                                        (indices[5] * 2) + 1, indices[5] * 2, (indices[4] * 2) + 1, indices[4] * 2,
                                        (indices[3] * 2) + 1, indices[3] * 2, (indices[2] * 2) + 1, indices[2] * 2,
                                        (indices[1] * 2) + 1, indices[1] * 2, (indices[0] * 2) + 1, indices[0] * 2);
                    return Simd256(_mm256_shuffle_epi8(_reg, idx));
                }
                else if constexpr (sizeof(DataType) == 1)
                {
                    const auto idx = _mm256_set_epi8(
                        indices[31], indices[30], indices[29], indices[28], indices[27], indices[26], indices[25],
                        indices[24], indices[23], indices[22], indices[21], indices[20], indices[19], indices[18],
                        indices[17], indices[16], indices[15], indices[14], indices[13], indices[12], indices[11],
                        indices[10], indices[9], indices[8], indices[7], indices[6], indices[5], indices[4], indices[3],
                        indices[2], indices[1], indices[0]);
                    return Simd256(_mm256_shuffle_epi8(_reg, idx));
                }
                else
                {
                    // No boundary cross and same indices
                    if constexpr (hasSameUpperAndLowerIndices)
                    {
                        // If the boundary is not crossed both upper and lower 128-bit lanes have the same
                        // indices then we can perform a shuffle.
                        if constexpr (types::IsFP32<DataType>)
                        {
                            // Only first 4 indices are used since we can assume there is lane crossing
                            constexpr auto PERMUTE_IDX = _MM_SHUFFLE(indices[3], indices[2], indices[1], indices[0]);
                            return Simd256(_mm256_permute_ps(_reg, PERMUTE_IDX));
                        }
                        else if constexpr (sizeof(DataType) == 8)
                        {
                            // Since there is not shuffle for epi64 we can "stitch" together a epi32 shuffle
                            // by shuffle the two adjacent 32-bit block to ith index and (i + 1)th index.
                            // But since we are dealing with 2-bit imm8 we we need to multiply the indices by 2
                            // So for moving from 0 -> 1, our final offset should be (1 * 2) + 1 and 1 * 2 or 3, 2.
                            // [--1--, --0--] int64
                            // [3, 2,   1, 0] int32
                            constexpr auto PERMUTE_IDX =
                                _MM_SHUFFLE(indices[1] * 2 + 1, indices[1] * 2, indices[0] * 2 + 1, indices[0] * 2);
                            return Simd256(_mm256_shuffle_epi32(_reg, PERMUTE_IDX));
                        }
                        else if constexpr (sizeof(DataType) == 4)
                        {
                            constexpr auto PERMUTE_IDX = _MM_SHUFFLE(indices[3], indices[2], indices[1], indices[0]);
                            return Simd256(_mm256_shuffle_epi32(_reg, PERMUTE_IDX));
                        }
                        else
                        {
                            return Simd256(_mm256_setzero_si256());
                        }
                    }
                    else // No boundary cross but different indices
                    {
                        // If the boundary is not crossed then perform simple shuffles
                        if constexpr (types::IsFP32<DataType>)
                        {
                            // TODO: May not be the optimal way
                            if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX2)
                            {
                                const auto idx = _mm256_set_epi32(indices[7], indices[6], indices[5], indices[4],
                                                                  indices[3], indices[2], indices[1], indices[0]);
                                return Simd256(_mm256_permutevar8x32_ps(_reg, idx));
                            }
                            else
                            {
                                constexpr auto hLane = Lane / 2; // Half Lane
                                // InLane = 1, LaneCross = 0
                                constexpr auto inLaneBlendMask = simd::internal::createInLaneBlendMask<Lane>(indices);
                                // The indices must be between 0 - 3(inclusive)
                                // [7, 6, 5, 4 | 3, 2, 1, 0]
                                // [3, 2, 1, 0 | 3, 2, 1, 0]
                                // NOTE: We could use shifts and `std::countr_zero` to do modulo but since this will be
                                //       resolved at compile time, we can use % directly as there is no runtime impact.
                                const auto idx = _mm256_set_epi32(
                                    indices[7] % hLane, indices[6] % hLane, indices[5] % hLane, indices[4] % hLane,
                                    indices[3] % hLane, indices[2] % hLane, indices[1] % hLane, indices[0] % hLane);
                                // Mask 0b01 swaps the upper lanes in the lower and lower into upper.
                                // [b1, b0] [a1, a0] // Both a and b are same registers here.
                                //  3    2    1   0
                                const auto exchanged = _mm256_permute2f128_ps(_reg, _reg, 0x1);

                                // Perform the shuffles
                                const auto inLanePermute    = _mm256_permutevar_ps(_reg, idx);
                                const auto crossLanePermute = _mm256_permutevar_ps(exchanged, idx);

                                // Blend both the results and return.
                                return Simd256(_mm256_blend_ps(crossLanePermute, inLanePermute, inLaneBlendMask));
                            }
                        }
                        else if constexpr (sizeof(DataType) == 8)
                        {
                            // We can stitch together epi8 shuffle to do same lane shuffle with 64-bit integrals
                            // clang-format off
                            const auto idx = _mm256_set_epi8(
                                    (indices[3] * 8 + 7), (indices[3] * 8 + 6), (indices[3] * 8 + 5), (indices[3] * 8 + 4),
                                    (indices[3] * 8 + 3), (indices[3] * 8 + 2), (indices[3] * 8 + 1), (indices[3] * 8),
                                    (indices[2] * 8 + 7), (indices[2] * 8 + 6), (indices[2] * 8 + 5), (indices[2] * 8 + 4),
                                    (indices[2] * 8 + 3), (indices[2] * 8 + 2), (indices[2] * 8 + 1), (indices[2] * 8),
                                    (indices[1] * 8 + 7), (indices[1] * 8 + 6), (indices[1] * 8 + 5), (indices[1] * 8 + 4),
                                    (indices[1] * 8 + 3), (indices[1] * 8 + 2), (indices[1] * 8 + 1), (indices[1] * 8),
                                    (indices[0] * 8 + 7), (indices[0] * 8 + 6), (indices[0] * 8 + 5), (indices[0] * 8 + 4),
                                    (indices[0] * 8 + 3), (indices[0] * 8 + 2), (indices[0] * 8 + 1), (indices[0] * 8)
                                );
                            // clang-format on
                            return Simd256(_mm256_shuffle_epi8(_reg, idx));
                        }
                        else if constexpr (sizeof(DataType) == 4)
                        {
                            // We can stitch together epi8 shuffle to do same lane shuffle with 32-bit integrals
                            // clang-format off
                            const auto idx = _mm256_set_epi8(
                                    (indices[7] * 4 + 3), (indices[7] * 4 + 2), (indices[7] * 4 + 1), (indices[7] * 4),
                                    (indices[6] * 4 + 3), (indices[6] * 4 + 2), (indices[6] * 4 + 1), (indices[6] * 4),
                                    (indices[5] * 4 + 3), (indices[5] * 4 + 2), (indices[5] * 4 + 1), (indices[5] * 4),
                                    (indices[4] * 4 + 3), (indices[4] * 4 + 2), (indices[4] * 4 + 1), (indices[4] * 4),
                                    (indices[3] * 4 + 3), (indices[3] * 4 + 2), (indices[3] * 4 + 1), (indices[3] * 4),
                                    (indices[2] * 4 + 3), (indices[2] * 4 + 2), (indices[2] * 4 + 1), (indices[2] * 4),
                                    (indices[1] * 4 + 3), (indices[1] * 4 + 2), (indices[1] * 4 + 1), (indices[1] * 4),
                                    (indices[0] * 4 + 3), (indices[0] * 4 + 2), (indices[0] * 4 + 1), (indices[0] * 4)
                                );
                            // clang-format on
                            return Simd256(_mm256_shuffle_epi8(_reg, idx));
                        }
                        // 2-byte and 1-byte integrals are handle in the top most conditional block.
                        else
                        {
                            // Shouldn't reach this point.
                            static_assert(false && "[Simd256AVX(permute)]: Unsupported data type.");
                            return Simd256(_mm256_setzero_si256());
                        }
                    }
                }
            }
            else // Cross-Boundary Permute
            {
                // If the boundary has been crossed then do permutation
                // NOTE: Mixed naming convention used to hint that one is fully
                //       compile-time evaluated and one is runtime(PERMUTE_IDX vs idx).
                if constexpr (types::IsFP64<DataType>)
                {
                    if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX2)
                    {
                        constexpr auto PERMUTE_IDX = _MM_SHUFFLE(indices[3], indices[2], indices[1], indices[0]);
                        return Simd256(_mm256_permute4x64_pd(_reg, PERMUTE_IDX));
                    }
                    else
                    {
                        const auto hLane = Lane / 2; // Half Lane
                        // Create a blend mask to blend all values that have cross the 128-bit boundary
                        // with the ones that haven't.
                        constexpr auto inLaneBlendMask = simd::internal::createInLaneBlendMask<Lane>(indices);

                        // Normalized the indices to be between 0 and Lane / 2 since we are
                        // permuting between the single lane
                        constexpr auto normalizedIdx = (indices[3] % hLane << 3) | (indices[2] % hLane << 2) |
                            (indices[1] % hLane << 1) | (indices[0] % hLane);

                        // Swap the upper and lower lanes
                        // We need to swap upper and lower lane so the flag is 0b00000001
                        const auto swapped = _mm256_permute2f128_pd(_reg, _reg, 0x1);
                        // Shuffle both registers
                        const auto inLane    = _mm256_permute_pd(_reg, normalizedIdx);
                        const auto crossLane = _mm256_permute_pd(swapped, normalizedIdx);
                        // Blend both the registers by the blend mask.
                        return Simd256(_mm256_blend_pd(crossLane, inLane, inLaneBlendMask));
                    }
                }
                else if constexpr (types::IsFP32<DataType>)
                {
                    if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX2)
                    {
                        const auto idx = _mm256_set_epi32(indices[7], indices[6], indices[5], indices[4], indices[3],
                                                          indices[2], indices[1], indices[0]);
                        return Simd256(_mm256_permutevar8x32_ps(_reg, idx));
                    }
                    else
                    {
                        constexpr auto hLane = Lane / 2; // Half Lane
                        // InLane = 1, LaneCross = 0
                        constexpr auto inLaneBlendMask = simd::internal::createInLaneBlendMask<Lane>(indices);
                        // The indices must be between 0 - 3(inclusive)
                        // [7, 6, 5, 4 | 3, 2, 1, 0]
                        // [3, 2, 1, 0 | 3, 2, 1, 0]
                        // NOTE: We could use shifts and `std::countr_zero` to do modulo but since this will be
                        //       resolved at compile time, we can use % directly as there is no runtime impact.
                        const auto idx = _mm256_set_epi32(indices[7] % hLane, indices[6] % hLane, indices[5] % hLane,
                                                          indices[4] % hLane, indices[3] % hLane, indices[2] % hLane,
                                                          indices[1] % hLane, indices[0] % hLane);
                        // Mask 0b01 swaps the upper lanes in the lower and lower into upper.
                        // [b1, b0] [a1, a0] // Both a and b are same registers here.
                        //  3    2    1   0
                        const auto exchanged = _mm256_permute2f128_ps(_reg, _reg, 0x1);

                        // Perform the shuffles
                        const auto inLanePermute    = _mm256_permutevar_ps(_reg, idx);
                        const auto crossLanePermute = _mm256_permutevar_ps(exchanged, idx);

                        // Blend both the results and return.
                        return Simd256(_mm256_blend_ps(crossLanePermute, inLanePermute, inLaneBlendMask));
                    }
                }
                else if constexpr (sizeof(DataType) == 8)
                {
                    constexpr auto PERMUTE_IDX = _MM_SHUFFLE(indices[3], indices[2], indices[1], indices[0]);
                    return Simd256(_mm256_permute4x64_epi64(_reg, PERMUTE_IDX));
                }
                else if constexpr (sizeof(DataType) == 4)
                {
                    const auto idx = _mm256_set_epi32(indices[7], indices[6], indices[5], indices[4], indices[3],
                                                      indices[2], indices[1], indices[0]);
                    return Simd256(_mm256_permutevar8x32_epi32(_reg, idx));
                }
                else if constexpr (sizeof(DataType) == 2)
                {
                    if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX) // AVX512VL
                    {
                        const auto idx =
                            _mm256_set_epi16(indices[15], indices[14], indices[13], indices[12], indices[11],
                                             indices[10], indices[9], indices[8], indices[7], indices[6], indices[5],
                                             indices[4], indices[3], indices[2], indices[1], indices[0]);
                        return Simd256(_mm256_permutexvar_epi16(idx, _reg));
                    }
                    else
                    {
                        //     3,    2 |    1,    0  Index
                        // [  55,   43 |    4,    6] Register values
                        // [   0,    2 |    3,    1] Shuffle Index
                        //
                        // [0x80,    2 | 0x80,    1] In-lane mask
                        // [   0, 0x80 |    3, 0x80] Cross-lane mask
                        //
                        // [   4,    6 |   55,   43] Upper-Lower exchanged.
                        //
                        // After shuffle (epi8)
                        // [   0,   43 |    0,    4] In-lane shuffle
                        // [   6,    0 |   55,    0] Cross-lane shuffle
                        // [   6,   43 |   55,    4] OR result(permuted)
                        // [MaskInLane, MaskPermute]
                        // Create two masks with in-lane and cross-lane shuffles within the 128-bit boundary.
                        constexpr auto masks = simd::internal::mm256Epi16PermMask<Lane, PermuteIndex...>();
                        const auto maskInLane =
                            _mm256_load_si256(reinterpret_cast<__m256i const*>(masks.inLaneMask.data()));
                        const auto maskPermute =
                            _mm256_load_si256(reinterpret_cast<__m256i const*>(masks.crossLaneMask.data()));

                        // Permutate the upper lanes into lower and lower to upper
                        // [1, 0 | 1, 0] -> Relative index of the 64-bit blocks.
                        // [3, 2 | 1, 0]
                        // [1, 0 | 3, 2]
                        // The block's relative index to the 128-bit register needs to be preserved.
                        const auto shuffledReg = _mm256_permute4x64_epi64(_reg, _MM_SHUFFLE(1, 0, 3, 2));

                        // Perform the shuffle(any index with 0x80 value will be set to 0)
                        const auto inLanePerm    = _mm256_shuffle_epi8(_reg, maskInLane);
                        const auto crossLanePerm = _mm256_shuffle_epi8(shuffledReg, maskPermute);

                        // Since the shuffles are mutually exclusive we can or the shuffled registers to get the full
                        // premuted register.
                        return Simd256(_mm256_or_si256(inLanePerm, crossLanePerm));
                    }
                }
                else if constexpr (sizeof(DataType) == 1)
                {
                    if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX) // AVX512VL
                    {
                        const auto idx = _mm256_set_epi8(
                            indices[31], indices[30], indices[29], indices[28], indices[27], indices[26], indices[25],
                            indices[24], indices[23], indices[22], indices[21], indices[20], indices[19], indices[18],
                            indices[17], indices[16], indices[15], indices[14], indices[13], indices[12], indices[11],
                            indices[10], indices[9], indices[8], indices[7], indices[6], indices[5], indices[4],
                            indices[3], indices[2], indices[1], indices[0]);
                        return Simd256(_mm256_permutexvar_epi8(idx, _reg));
                    }
                    else
                    {
                        // Same technique as for epi16
                        // [MaskInLane, MaskPermute]
                        constexpr auto masks = simd::internal::mm256Epi8PermMask<Lane, PermuteIndex...>();
                        const auto maskInLane =
                            _mm256_load_si256(reinterpret_cast<__m256i const*>(masks.inLaneMask.data()));
                        const auto maskPermute =
                            _mm256_load_si256(reinterpret_cast<__m256i const*>(masks.crossLaneMask.data()));
                        // std::cout << "Shuffle Index\n";
                        // for (const auto m : indices)
                        // {
                        //     std::cout << static_cast<int>(m) << ", ";
                        // }
                        // std::cout << "\nMask In Lane\n";
                        // for (const auto m : masks.first)
                        // {
                        //     std::cout << static_cast<int>(m) << ", ";
                        // }
                        // std::cout << "\nCross Lane\n";
                        // for (const auto m : masks.second)
                        // {
                        //     std::cout << static_cast<int>(m) << ", ";
                        // }
                        // std::cout << "\n";

                        // Permutate the upper lanes into lower and lower to upper
                        // [1, 0 | 1, 0] -> Relative index of the 64-bit blocks.
                        // [3, 2 | 1, 0]
                        // [1, 0 | 3, 2]
                        // The block's relative index to the 128-bit register needs to be preserved.
                        const auto shuffledReg = _mm256_permute4x64_epi64(_reg, _MM_SHUFFLE(1, 0, 3, 2));

                        // Perform the shuffle(any index with 0x80 value will be set to 0)
                        const auto inLanePerm    = _mm256_shuffle_epi8(_reg, maskInLane);
                        const auto crossLanePerm = _mm256_shuffle_epi8(shuffledReg, maskPermute);

                        // Since the shuffles are mutually exclusive we can or the shuffled registers to get the full
                        // permuted register.
                        return Simd256(_mm256_or_si256(inLanePerm, crossLanePerm));
                    }
                }
                else
                {
                    // Shouldn't reach this point.
                    static_assert(false && "[Simd256AVX(permute)]: Unsupported data type.");
                    return Simd256(_mm256_setzero_si256());
                }
            }
        }
        else
        {
            return Simd256(_reg.template permute<PermuteIndex...>());
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd256<SimdBackend::ARCH_AVX, DataType, Lane>::horizontalMin() const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            constexpr auto halfLane = Lane / 2;
            // TODO: Replace std::min with flcn::min
            if constexpr (types::IsFP64<DataType>)
            {
                auto loLane = _mm256_castpd256_pd128(_reg);
                auto hiLane = _mm256_extractf128_pd(_reg, 1);

                return std::min(Simd128<SimdBackend::ARCH_SSE2, DataType, halfLane>(loLane).horizontalMin(),
                                Simd128<SimdBackend::ARCH_SSE2, DataType, halfLane>(hiLane).horizontalMin());
            }
            if constexpr (types::IsFP32<DataType>)
            {
                auto loLane = _mm256_castps256_ps128(_reg);
                auto hiLane = _mm256_extractf128_ps(_reg, 1);

                return std::min(Simd128<SimdBackend::ARCH_SSE2, DataType, halfLane>(loLane).horizontalMin(),
                                Simd128<SimdBackend::ARCH_SSE2, DataType, halfLane>(hiLane).horizontalMin());
            }
            else if constexpr (std::is_integral_v<DataType>)
            {
                auto loLane = _mm256_castsi256_si128(_reg);
                auto hiLane = _mm256_extracti128_si256(_reg, 1);

                return std::min(Simd128<SimdBackend::ARCH_SSE2, DataType, halfLane>(loLane).horizontalMin(),
                                Simd128<SimdBackend::ARCH_SSE2, DataType, halfLane>(hiLane).horizontalMin());
            }
            else
            {
                // Should hit this case
                static_assert("[Simd256AVX/HMax]: Unsupported data type.");
                return DataType(0);
            }
        }
        else
        {
            return _reg.horizontalMin();
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd256<SimdBackend::ARCH_AVX, DataType, Lane>::horizontalMax() const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            constexpr auto halfLane = Lane / 2;
            // TODO: Replace std::min with flcn::max
            if constexpr (types::IsFP64<DataType>)
            {
                auto loLane = _mm256_castpd256_pd128(_reg);
                auto hiLane = _mm256_extractf128_pd(_reg, 1);

                return std::max(Simd128<SimdBackend::ARCH_SSE2, DataType, halfLane>(loLane).horizontalMax(),
                                Simd128<SimdBackend::ARCH_SSE2, DataType, halfLane>(hiLane).horizontalMax());
            }
            if constexpr (types::IsFP32<DataType>)
            {
                auto loLane = _mm256_castps256_ps128(_reg);
                auto hiLane = _mm256_extractf128_ps(_reg, 1);

                return std::max(Simd128<SimdBackend::ARCH_SSE2, DataType, halfLane>(loLane).horizontalMax(),
                                Simd128<SimdBackend::ARCH_SSE2, DataType, halfLane>(hiLane).horizontalMax());
            }
            else if constexpr (std::is_integral_v<DataType>)
            {
                auto loLane = _mm256_castsi256_si128(_reg);
                auto hiLane = _mm256_extracti128_si256(_reg, 1);

                return std::max(Simd128<SimdBackend::ARCH_SSE2, DataType, halfLane>(loLane).horizontalMax(),
                                Simd128<SimdBackend::ARCH_SSE2, DataType, halfLane>(hiLane).horizontalMax());
            }
            else
            {
                // Should hit this case
                static_assert("[Simd256AVX/HMax]: Unsupported data type.");
                return DataType(0);
            }
        }
        else
        {
            return _reg.horizontalMax();
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<SimdBackend::ARCH_AVX, DataType,
                                                                                   Lane>::abs() const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            // There is no intrinsic for floating point abs so we have to use a sign flag mask and use AND
            // 1 101 1010
            // 0 111 1111 &
            // 0 101 1010

            // For integrals use the trick from Hackers Delight[2-4]
            // y = x a>> (sizeof(DataType) * 8 - 1) (for int32 its y = x >> 31)
            // (x xor y) - y
            // -7  1001
            // t = 1111 xor
            //   = 0110
            //   = 1111 -
            //   = 0111 (7)
            if constexpr (std::is_unsigned_v<DataType>)
            {
                return Simd256(_reg);
            }
            else if constexpr (types::IsFP64<DataType>)
            {
                // We can take the abs of a register by using a flag mask and ANDing it with our register.
                const auto flagReg = _mm256_set1_epi64x(0x7FFFFFFFFFFFFFFF); // 0b0111..1111
                const auto intReg  = _mm256_castpd_si256(_reg);
                const auto absReg  = _mm256_and_si256(intReg, flagReg);
                return Simd256(_mm256_castsi256_pd(absReg));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                // We can take the abs of a register by using a flag mask and ANDing it with our register.
                const auto flagReg = _mm256_set1_epi32(0x7FFFFFFF); // 0b0111..1111
                const auto intReg  = _mm256_castps_si256(_reg);
                const auto absReg  = _mm256_and_si256(intReg, flagReg);
                return Simd256(_mm256_castsi256_ps(absReg));
            }
            else if constexpr (types::IsQWord<DataType>)
            {
                if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX) // AVX512F + VL
                {
                    return Simd128(_mm_abs_epi64(_reg));
                }
                else
                {
                    // t = x a>> 63; abs = (x xor t) - t;
                    const auto t      = *shiftRightArithmetic<63>();
                    const auto xorReg = _mm256_xor_si256(_reg, t);
                    return Simd256(_mm256_sub_epi64(xorReg, t));
                }
            }
            else if constexpr (types::IsDWord<DataType>)
            {
                return Simd256(_mm256_abs_epi32(_reg));
            }
            else if constexpr (types::IsWord<DataType>)
            {
                return Simd256(_mm256_abs_epi16(_reg));
            }
            else if constexpr (types::IsByte<DataType>)
            {
                return Simd256(_mm256_abs_epi8(_reg));
            }
            else
            {
                static_assert("[Simd256AVX/Abs]: Unsupported data type.");
                return Simd256{};
            }
        }
        else
        {
            return _reg.abs();
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<SimdBackend::ARCH_AVX, DataType,
                                                                                   Lane>::sqrt() const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            // For floating point numbers shift the sign bit and compare the exponents.
            // For infinity exponents are all ones 0xFFE(0b11111111111) for doubles and 0xFF(0b00000000).
            if constexpr (types::IsFP64<DataType>)
            {
                return Simd256(_mm256_sqrt_pd(_reg));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return Simd256(_mm256_sqrt_ps(_reg));
            }
            else if constexpr (std::is_integral_v<DataType>)
            {
                // TODO: Integral sqrt may not be optimal
                if constexpr (sizeof(DataType) == 8)
                {
                    // There must only 4 lanes for 64-bit integrals
                    alignas(Alignment) DataType array[Lane]{};
                    if constexpr (std::is_signed_v<DataType>)
                    {
                        // For signed integrals we must clamp to zero to prevent negative integral square roots
                        // And we need to clamp to zero.
                        const auto clamped = *max(*this, Simd256(_mm256_setzero_si256()));
                        _mm256_store_si256(reinterpret_cast<__m256i*>(array), clamped);
                    }
                    else
                    {
                        storeAligned(array);
                    }
                    return Simd256(
                        static_cast<DataType>(std::sqrt(array[0])), static_cast<DataType>(std::sqrt(array[1])),
                        static_cast<DataType>(std::sqrt(array[2])), static_cast<DataType>(std::sqrt(array[3])));
                }
                else if constexpr (sizeof(DataType) == 4)
                {
                    // There are no sqrt for integrals so we can convert to double
                    // and take sqrt and convert back
                    const auto loLane = _mm256_castsi256_si128(_reg);
                    const auto hiLane = _mm256_extracti128_si256(_reg, 1);

                    if constexpr (std::is_signed_v<DataType>)
                    {
                        // Clamp the value to >= 0.
                        const auto zero      = _mm_setzero_si128();
                        const auto loClamped = _mm_max_epi32(loLane, zero);
                        const auto hiClamped = _mm_max_epi32(hiLane, zero);
                        // Convert to float
                        const auto loFloat = _mm256_cvtepi32_pd(loClamped);
                        const auto hiFloat = _mm256_cvtepi32_pd(hiClamped);
                        // Take the sqrt
                        const auto loSqrt = _mm256_sqrt_pd(loFloat);
                        const auto hiSqrt = _mm256_sqrt_pd(hiFloat);

                        // [3, 2, 1, 0]
                        const auto loSqrtInt = _mm256_cvttpd_epi32(loSqrt);
                        // [7, 6, 5, 4]
                        const auto hiSqrtInt = _mm256_cvttpd_epi32(hiSqrt);

                        // Insert the 128-bit register into the upper lane.
                        return Simd256(_mm256_setr_m128i(loSqrtInt, hiSqrtInt));
                    }
                    else
                    {
                        if constexpr (CURRENT_SIMD_BACKEND >= SimdBackend::ARCH_AVX512EX) // AVX512F + VL
                        {
                            // EPU32 to PD and PD to EPU32 require AVX512F + VL
                            const auto loFloat = _mm256_cvtepu32_pd(loLane);
                            const auto hiFloat = _mm256_cvtepu32_pd(hiLane);

                            // Take the sqrt
                            const auto loSqrt = _mm256_sqrt_pd(loFloat);
                            const auto hiSqrt = _mm256_sqrt_pd(hiFloat);

                            // [3, 2, 1, 0]
                            const auto loSqrtInt = _mm256_cvttpd_epu32(loSqrt);
                            // [7, 6, 5, 4]
                            const auto hiSqrtInt = _mm256_cvttpd_epu32(hiSqrt);

                            // Insert the 128-bit register into the upper lane.
                            return Simd256(_mm256_setr_m128i(loSqrtInt, hiSqrtInt));
                        }
                        else
                        {
                            // For 32-bit integers since we don't have an epu32_pd
                            // when having an int with the MSB `ON`, it will get interpreted as a negative double.
                            // To convert that negative interpretation to a positive number
                            // we add the int32-max, which will reset the negative number to our original number
                            // If our number is 111...111 it will get interpreted as -1, although it is (2^32) - 1 or
                            // 4294967295 but adding 2^32 to the -1 yields our original number.
                            const auto offset = _mm256_set1_pd(4294967296.0);
                            const auto zero   = _mm256_setzero_pd();

                            // If hardware created a negative double, it was a large unsigned int
                            // so add an offset to it
                            const auto loFloatReg  = _mm256_cvtepi32_pd(loLane);
                            const auto loMask      = _mm256_cmp_pd(loFloatReg, zero, _CMP_LT_OQ);
                            const auto loFilter    = _mm256_and_pd(loMask, offset);
                            const auto loCorrected = _mm256_add_pd(loFloatReg, loFilter);
                            const auto loSqrt      = _mm256_sqrt_pd(loCorrected);
                            const auto loSqrtInt   = _mm256_cvttpd_epi32(loSqrt);

                            const auto hiFloatReg  = _mm256_cvtepi32_pd(hiLane);
                            const auto hiMask      = _mm256_cmp_pd(hiFloatReg, zero, _CMP_LT_OQ);
                            const auto hiFilter    = _mm256_and_pd(offset, hiMask);
                            const auto hiCorrected = _mm256_add_pd(hiFloatReg, hiFilter);
                            const auto hiSqrt      = _mm256_sqrt_pd(hiCorrected);
                            const auto hiSqrtInt   = _mm256_cvttpd_epi32(hiSqrt);

                            return Simd256(_mm256_setr_m128i(loSqrtInt, hiSqrtInt));
                        }
                    }
                }
                else if constexpr (sizeof(DataType) == 2)
                {
                    // Clamp the register values to greater than or equal to zero, if the register is signed.
                    auto reg = _reg;
                    if constexpr (std::is_signed_v<DataType>)
                    {
                        reg = _mm256_max_epi16(reg, _mm256_setzero_si256());
                    }
                    return Simd256(intrin::_mm256_sqrt_epi16_custom(reg));
                }
                else if constexpr (sizeof(DataType) == 1)
                {
                    // Clamp the register values to greater than or equal to zero, if the register is signed.
                    auto reg        = _reg;
                    const auto zero = _mm256_setzero_si256();
                    if constexpr (std::is_signed_v<DataType>)
                    {
                        reg = _mm256_max_epi8(reg, zero);
                    }
                    // Unpack to 16-bit integral and take sqrt
                    const auto loLane = _mm256_unpacklo_epi8(reg, zero);
                    const auto hiLane = _mm256_unpackhi_epi8(reg, zero);
                    // Compute the square root
                    const auto loSqrt = intrin::_mm256_sqrt_epi16_custom(loLane);
                    const auto hiSqrt = intrin::_mm256_sqrt_epi16_custom(hiLane);

                    // Pack the 16-bits to 8-bit integral
                    return Simd256(_mm256_packs_epi16(loSqrt, hiSqrt));
                }
                else
                {
                    static_assert("[Simd256AVX/Sqrt]: Unsupported data type.");
                    return Simd256{};
                }
            }
            else
            {
                static_assert("[Simd256AVX/Sqrt]: Unsupported data type.");
                return Simd256{};
            }
        }
        else
        {
            return Simd256(_reg.sqrt());
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<SimdBackend::ARCH_AVX, DataType,
                                                                                   Lane>::hasNan() const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            // For floating point numbers shift the sign bit and compare the exponents.
            // For infinity exponents are all ones 0xFFE(0b11111111111) for doubles and 0xFF(0b00000000).
            if constexpr (types::IsFP64<DataType>)
            {
                return Simd256(_mm256_cmp_pd(_reg, _reg, _CMP_UNORD_Q));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                return Simd256(_mm256_cmp_ps(_reg, _reg, _CMP_UNORD_Q));
            }
            else if constexpr (std::is_integral_v<DataType>)
            {
                return Simd256(_mm256_setzero_si256());
            }
            else
            {
                static_assert("[Simd256AVX/HasNan]: Unsupported data type.");
                return Simd256{};
            }
        }
        else
        {
            return Simd256(_reg.hasNan());
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_AVX, DataType, Lane> Simd256<SimdBackend::ARCH_AVX, DataType,
                                                                                   Lane>::hasInf() const noexcept
    {
        if constexpr (_FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC(DataType))
        {
            // For floating point numbers shift the sign bit and compare the exponents.
            // For infinity exponents are all ones 0xFFE(0b11111111111) for doubles and 0xFF(0b00000000).
            if constexpr (types::IsFP64<DataType>)
            {
                const auto shifted = cast<uint64_t>().template shiftLeft<1>();
                const auto res     = shifted == Simd256<SimdBackend::ARCH_AVX, uint64_t, Lane>(0xFFE0000000000000ULL);
                return Simd256(_mm256_castsi256_pd(*res));
            }
            else if constexpr (types::IsFP32<DataType>)
            {
                const auto shifted = cast<uint32_t>().template shiftLeft<1>();
                const auto res     = shifted == Simd256<SimdBackend::ARCH_AVX, uint32_t, Lane>(0xFF000000U);
                return Simd256(_mm256_castsi256_ps(*res));
            }
            else if constexpr (std::is_integral_v<DataType>)
            {
                return Simd256(_mm256_setzero_si256());
            }
            else
            {
                static_assert("[Simd256AVX/HasInf]: Unsupported data type.");
                return Simd256{};
            }
        }
        else
        {
            return Simd256(_reg.hasInf());
        }
    }

#undef _FALCON_SIMD256_SUPPORT_NATIVE_INTRINSIC

} // namespace flcn
