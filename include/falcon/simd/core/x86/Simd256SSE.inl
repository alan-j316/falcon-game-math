#pragma once
/**
 * @file Simd256SSE.inl
 * @author Alan Abraham P Kochumon
 * @date Created on: September 26, 2026
 *
 * @brief Implementation of templated functions declared in Simd256SSE.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "falcon/simd/utils/SIMDUtils.h"

namespace flcn
{
    template <typename DataType, size_t Lane>
    template <typename... Args>
        requires(SimdSafeConvertible<Args, DataType> && ...)
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::Simd256(Args&&... data) noexcept
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
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, T, Lane> Simd256<SimdBackend::ARCH_SSE2, DataType,
                                                                             Lane>::cast() const noexcept
    { return Simd256(_lower.template cast<T>(), _upper.template cast<T>()); }


    template <typename DataType, size_t Lane>
    template <typename T>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, T, Lane> Simd256<SimdBackend::ARCH_SSE2, DataType,
                                                                             Lane>::cast() noexcept
    { return Simd256(_lower.template cast<T>(), _upper.template cast<T>()); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::Simd256(
        std::span<const DataType> values) noexcept
    { loadAligned(values.data()); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::Simd256(const DataType* pBuffer) noexcept
    { loadAligned(pBuffer); }


    template <typename DataType, size_t Lane>
    template <typename... Args>
        requires(sizeof...(Args) <= Lane) && (std::same_as<Args, DataType> && ...) &&
        (SimdSafeConvertible<Args, DataType> && ...)
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>& Simd256<SimdBackend::ARCH_SSE2, DataType,
                                                                                     Lane>::set(Args... args)
    {
        // TODO: Apply this to SIMD128
        // To support variable argument passing we need to return pass down a zero for all the lanes that are
        // not provided.
        constexpr auto argCount  = sizeof...(args);
        const DataType arr[Lane] = { args... };

        // Fill the upper lane
        if constexpr (argCount <= LOWER_LANE_COUNT)
        {
            _upper.setZero();
        }
        else
        {
            auto fillUpper = [&]<size_t... Indices>(std::index_sequence<Indices...>) {
                _upper.set(arr[LOWER_LANE_COUNT + Indices]...);
            };
            fillUpper(std::make_index_sequence<UPPER_LANE_COUNT>{});
        }
        // Fill the lower lane
        auto fillLower = [&]<size_t... Indices>(std::index_sequence<Indices...>) {
            _lower.set(arr[Indices]...);
        };
        fillLower(std::make_index_sequence<LOWER_LANE_COUNT>{});

        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::loadAligned(
        const DataType* data) noexcept
    {
        _lower.loadAligned(data);
        _upper.loadAligned(data + LOWER_LANE_COUNT);
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::load(const DataType* data) noexcept
    {
        _lower.load(data);
        _upper.load(data + LOWER_LANE_COUNT);
    }

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::broadcast(DataType value) noexcept
    {
        _lower.broadcast(value);
        _upper.broadcast(value);
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::setZero() noexcept
    {
        _lower.setZero();
        _upper.setZero();
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::setOne() noexcept
    {
        _lower.setOne();
        _upper.setOne();
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::store(
        DataType* pBuffer) const noexcept
    {
        _lower.store(pBuffer);
        _upper.store(pBuffer + LOWER_LANE_COUNT);
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::storeAligned(
        DataType* pBuffer) const noexcept
    {
        _lower.storeAligned(pBuffer);
        _upper.storeAligned(pBuffer + LOWER_LANE_COUNT);
    }



    /**************************************
     *          GETTERS/SETTERS           *
     **************************************/

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::getAt(size_t index) const noexcept
    { return index >= LOWER_LANE_COUNT ? _upper.getAt(index - LOWER_LANE_COUNT) : _lower.getAt(index); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::setAt(size_t index,
                                                                                        DataType value) noexcept
    {
        // TODO: Optimize with masks
        index >= LOWER_LANE_COUNT ? _upper.setAt(index - LOWER_LANE_COUNT, value) : _lower.setAt(index, value);
    }


    template <typename DataType, size_t Lane>
    template <size_t Index>
        requires(Index < Lane)
    FALCON_INLINE constexpr DataType Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::getAt() const noexcept
    {
        if constexpr (Index >= LOWER_LANE_COUNT)
        {
            return _upper.template getAt<Index - LOWER_LANE_COUNT>();
        }
        else
        {
            return _lower.template getAt<Index>();
        }
    }


    template <typename DataType, size_t Lane>
    template <size_t Index>
        requires(Index < Lane)
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::setAt(DataType value) noexcept
    {
        if constexpr (Index >= LOWER_LANE_COUNT)
        {
            _upper.template setAt<Index - LOWER_LANE_COUNT>(value);
        }
        else
        {
            _lower.template setAt<Index>(value);
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::extractFirst() noexcept
    { return _lower.extractFirst(); }



    /**************************************
     *          BITWISE OPERATORS         *
     **************************************/

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<SimdBackend::ARCH_SSE2, DataType,
                                                                                    Lane>::operator~() const noexcept
    { return Simd256(~_lower, ~_upper); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator&(const Simd256 other) const noexcept
    { return Simd256(_lower & other._lower, _upper & other._upper); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator|(const Simd256 other) const noexcept
    { return Simd256(_lower | other._lower, _upper | other._upper); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator^(const Simd256 other) const noexcept
    { return Simd256(_lower ^ other._lower, _upper ^ other._upper); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::andNot(const Simd256 other) const noexcept
    { return Simd256(_lower.andNot(other._lower), _upper.andNot(other._upper)); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::horizontalOr() const noexcept
    {
        const auto lower = _lower.horizontalOr();
        const auto upper = _upper.horizontalOr();
        if constexpr (std::is_same_v<DataType, double>)
        {
            return std::bit_cast<double>(std::bit_cast<uint64_t>(lower) | std::bit_cast<uint64_t>(upper));
        }
        else if constexpr (std::is_same_v<DataType, float>)
        {
            return std::bit_cast<float>(std::bit_cast<uint32_t>(lower) | std::bit_cast<uint32_t>(upper));
        }
        else
        {
            return lower | upper;
        }
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::horizontalAnd() const noexcept
    {
        const auto lower = _lower.horizontalAnd();
        const auto upper = _upper.horizontalAnd();
        if constexpr (std::is_same_v<DataType, double>)
        {
            return std::bit_cast<double>(std::bit_cast<uint64_t>(lower) & std::bit_cast<uint64_t>(upper));
        }
        else if constexpr (std::is_same_v<DataType, float>)
        {
            return std::bit_cast<float>(std::bit_cast<uint32_t>(lower) & std::bit_cast<uint32_t>(upper));
        }
        else
        {
            return lower & upper;
        }
    }



    /**************************************
     *       ARITHMETIC OPERATORS         *
     **************************************/

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator+(const Simd256 other) const noexcept
    { return Simd256(_lower + other._lower, _upper + other._upper); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>& Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator+=(const Simd256 other) noexcept
    {
        *this = *this + other;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator-(const Simd256 other) const noexcept
    { return Simd256(_lower - other._lower, _upper - other._upper); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>& Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator-=(const Simd256 other) noexcept
    {
        *this = *this - other;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<SimdBackend::ARCH_SSE2, DataType,
                                                                                    Lane>::operator-() const noexcept
    { return Simd256(-_lower, -_upper); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator*(const Simd256 other) const noexcept
    { return Simd256(_lower * other._lower, _upper * other._upper); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>& Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator*=(const Simd256 other) noexcept
    {
        *this = *this * other;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::divReg(const Simd256 other) const noexcept
    { return Simd256(_lower.divReg(other._lower), _upper.divReg(other._upper)); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator/(DataType scalar) const noexcept
    { return Simd256(_lower / scalar, _upper / scalar); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>& Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator/=(DataType scalar) noexcept
    {
        *this = *this / scalar;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<SimdBackend::ARCH_SSE2, DataType,
                                                                                    Lane>::fma(const Simd256 b,
                                                                                               Simd256 c) const noexcept
    { return Simd256(_lower.fma(b._lower, c._lower), _upper.fma(b._upper, c._upper)); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::horizontalAdd() const noexcept
    { return _lower.horizontalAdd() + _upper.horizontalAdd(); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::horizontalSub() const noexcept
    {
        // NOTE: For horizontal sub to work like A - B - C - D
        //       We need to use a horizontal sub and horizontal add
        //       and take the difference of the results.
        //       A - B - (C + D)
        return _lower.horizontalSub() - _upper.horizontalAdd();
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator==(const Simd256 other) const noexcept
    { return Simd256(_lower == other._lower, _upper == other._upper); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator!=(const Simd256 other) const noexcept
    { return Simd256(_lower != other._lower, _upper != other._upper); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator>(const Simd256 other) const noexcept
    { return Simd256(_lower > other._lower, _upper > other._upper); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator>=(const Simd256 other) const noexcept
    { return Simd256(_lower >= other._lower, _upper >= other._upper); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator<(const Simd256 other) const noexcept
    { return Simd256(_lower < other._lower, _upper < other._upper); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator<=(const Simd256 other) const noexcept
    { return Simd256(_lower <= other._lower, _upper <= other._upper); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator<<(uint32_t count) const noexcept
    { return Simd256(_lower << count, _upper << count); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>& Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator<<=(uint32_t count) noexcept
    {
        *this = *this << count;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator>>(uint32_t count) const noexcept
    { return Simd256(_lower >> count, _upper >> count); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>& Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::operator>>=(uint32_t count) noexcept
    {
        *this = *this >> count;
        return *this;
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::shiftRightLogical(uint32_t count) const noexcept
    { return Simd256(_lower.shiftRightLogical(count), _upper.shiftRightLogical(count)); }


    template <typename DataType, size_t Lane>
    template <uint32_t Count>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<SimdBackend::ARCH_SSE2, DataType,
                                                                                    Lane>::shiftLeft() const noexcept
    { return Simd256(_lower.template shiftLeft<Count>(), _upper.template shiftLeft<Count>()); }


    template <typename DataType, size_t Lane>
    template <uint32_t Count>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::shiftRightArithmetic() const noexcept
    { return Simd256(_lower.template shiftRightArithmetic<Count>(), _upper.template shiftRightArithmetic<Count>()); }


    template <typename DataType, size_t Lane>
    template <uint32_t Count>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::shiftRightLogical() const noexcept
    { return Simd256(_lower.template shiftRightLogical<Count>(), _upper.template shiftRightLogical<Count>()); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::blend(const Simd256 other, Simd256 mask) const noexcept
    { return Simd256{ _lower.blend(other._lower, mask._lower), _upper.blend(other._upper, mask._upper) }; }


    template <typename DataType, size_t Lane>
    template <BlendMask32_t Mask>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<
        SimdBackend::ARCH_SSE2, DataType, Lane>::blend(const Simd256 other) const noexcept
    {
        // Lower Mask only takes into account the lower 16-bits(expanded to 32-bits).
        // Upper mask the upper 16-bits but shifted to to the lower lane(expanded to 32-bits).
        constexpr auto lowerMask = static_cast<BlendMask32_t>(simd::expandTwoFold(Mask & 0x0000FFFF));
        constexpr auto upperMask = static_cast<BlendMask32_t>(simd::expandTwoFold(Mask >> 16));
        return Simd256(_lower.template blend<lowerMask>(other._lower), _upper.template blend<upperMask>(other._upper));
    }


    template <typename DataType, size_t Lane>
    template <uint8_t... ShuffleIndex>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<SimdBackend::ARCH_SSE2, DataType,
                                                                                    Lane>::shuffle() const noexcept
    {
        static_assert(sizeof...(ShuffleIndex) == Lane && "There must be <Lane> shuffle indices.");
        static_assert(((ShuffleIndex < Lane) && ...) && "Indices must be between 0(inclusive) and <Lane>(exclusive).");

        // For shuffling we need to perform a normalized shuffle(range between 0 - Max_128_Lane_Count)
        // and then use a mask to select values from appropriate register lanes.

        // Packed indexing is not support until C++26, we need to use this workaround
        // For shuffling with two indices we need to transform the array values(indices)
        // to be between 0 - MAX_LANE_COUNT(exclusive)
        constexpr std::array<uint8_t, MaxLaneCount> normalizedIndices{ { (
            static_cast<uint8_t>(ShuffleIndex % Max128BitLaneCount))... } };

        // Masks for selecting values for the upper and lower 128-bit lanes.
        const auto makeMask = [&]<size_t Offset, size_t... Index>(std::index_sequence<Index...>) {
            constexpr std::array<uint8_t, MaxLaneCount> ShuffleIndices{ { ShuffleIndex... } };
            return simd::makeBlendMask32<Max128BitLaneCount,
                                         (ShuffleIndices[Offset + Index] >= Max128BitLaneCount)...>();
        };
        // [up_mask1, up_mask0, lo_mask1, lo_mask0]
        constexpr BlendMask32_t upperMask =
            makeMask.template operator()<Max128BitLaneCount>(std::make_index_sequence<Max128BitLaneCount>{});
        constexpr BlendMask32_t lowerMask =
            makeMask.template operator()<0>(std::make_index_sequence<Max128BitLaneCount>{});

        // low          hi
        // | a1 | b1 | | c1 | d1 |
        // -----------------------
        // lolo | a1 | b1 | <--
        // lohi | a1 | b1 |    | <===
        // hilo | c1 | d1 | <--     |
        // hihi | c1 | d1 |      <===
        // Select hilo if Mask[i] is true and lolo otherwise
        // Select hihi if Mask[i] is true and lohi otherwise

        // NOTE: Lambda needs to invoked using .template operator() since the compiler can get confused
        //       by the <0> as less operator.

        // Upper part of the register with lower and upper indices(hilo, lohi)
        auto shuffleUpper = [&]<size_t Offset, size_t... Index>(std::index_sequence<Index...>) {
            return _upper.template shuffle<normalizedIndices[Offset + Index]...>();
        };
        auto upperShuffledWithUpperIndices =
            shuffleUpper.template operator()<Max128BitLaneCount>(std::make_index_sequence<UPPER_LANE_COUNT>{});
        auto upperShuffledWithLowerIndices =
            shuffleUpper.template operator()<0>(std::make_index_sequence<UPPER_LANE_COUNT>{});

        // Lower part of register with lower and upper indices (lolo, lohi)
        auto shuffleLower = [&]<size_t Offset, size_t... Index>(std::index_sequence<Index...>) {
            return _lower.template shuffle<normalizedIndices[Offset + Index]...>();
        };
        auto lowerShuffledWithUpperIndices =
            shuffleLower.template operator()<Max128BitLaneCount>(std::make_index_sequence<LOWER_LANE_COUNT>{});
        auto lowerShuffledWithLowerIndices =
            shuffleLower.template operator()<0>(std::make_index_sequence<LOWER_LANE_COUNT>{});

        // select(lolo, hilo, mask), select(lohi, hihi, mask)
        return Simd256{ lowerShuffledWithLowerIndices.template blend<lowerMask>(upperShuffledWithLowerIndices),
                        lowerShuffledWithUpperIndices.template blend<upperMask>(upperShuffledWithUpperIndices) };
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::horizontalMin() const noexcept
    { return std::min(_lower.horizontalMin(), _upper.horizontalMin()); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr DataType Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::horizontalMax() const noexcept
    { return std::max(_lower.horizontalMax(), _upper.horizontalMax()); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<SimdBackend::ARCH_SSE2, DataType,
                                                                                    Lane>::abs() const noexcept
    { return Simd256(_lower.abs(), _upper.abs()); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<SimdBackend::ARCH_SSE2, DataType,
                                                                                    Lane>::sqrt() const noexcept
    { return Simd256(_lower.sqrt(), _upper.sqrt()); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<SimdBackend::ARCH_SSE2, DataType,
                                                                                    Lane>::hasNan() const noexcept
    { return Simd256(_lower.hasNan(), _upper.hasNan()); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane> Simd256<SimdBackend::ARCH_SSE2, DataType,
                                                                                    Lane>::hasInf() const noexcept
    { return Simd256(_lower.hasInf(), _upper.hasInf()); }


} // namespace flcn
