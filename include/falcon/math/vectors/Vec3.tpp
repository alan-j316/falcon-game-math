#pragma once
/**
 * @file Vec3.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 10, 2026
 *
 * @brief @ref Vec3 template implementation.
 * @details This file contains the definitions of the template members declared in Vec3.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

namespace flcn
{
    /// +---------------------------------------------------------------------------------------+
    /// |                               INITIALIZERS                                            |
    /// +---------------------------------------------------------------------------------------+

    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T>::Vec3(T val) noexcept: _data{ val, val, val, T(0) }
    {}


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T>::Vec3(const typename internal::Vec3SimdStore<T>::Type& reg) noexcept: _data{ reg }
    {}


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T>::Vec3(T v1, T v2, T v3) noexcept: _data{ v1, v2, v3, T(0) }
    {}

    // TODO: Update (Vec2, T) and (T, Vec2) inits to use direct register loads instead of access and loads
    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T>::Vec3(const Vec2<T> vec, T v) noexcept
        : _data{ vec.template get<0>(), vec.template get<1>(), v, T(0) }
    {}


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T>::Vec3(T v, const Vec2<T> vec) noexcept
        : _data{ v, vec.template get<0>(), vec.template get<1>(), T(0) }
    {}

    // TODO: Add
    // template <Arithmetic T>
    // FALCON_INLINE constexpr Vec2<T>::Vec2(const Simd128_t<T, DIMENSION>& reg) noexcept: _data{ reg }
    // {}
    //
    //     template <Arithmetic T>
    // FALCON_INLINE constexpr CVec2<T> Vec2<T>::toCVec2() const noexcept
    // {
    //     CVec2<T> cVec{};
    //     _data.store(cVec._data.data());
    //     return cVec;
    // }
    //
    // template <Arithmetic T>
    // FALCON_INLINE constexpr CVec2<T> Vec2<T>::toCVec2(const Vec2& vec) noexcept
    // { return vec.toCVec2(); }
    //


    template <Arithmetic T>
    template <Arithmetic U>
    FALCON_INLINE constexpr Vec3<T>::Vec3(const Vec3<U>& other) noexcept
    { _data.set(static_cast<T>(other.x()), static_cast<T>(other.y()), static_cast<T>(other.z()), T(0)); }



    /// +---------------------------------------------------------------------------------------+
    /// |                                 ACCESSORS                                             |
    /// +---------------------------------------------------------------------------------------+

    /**************************************
     *        SPATIAL COORDINATES         *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec3<T>::x() const noexcept
    { return _data.template getAt<0>(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T>::template ConstIndexableProxy<0> Vec3<T>::x() noexcept
    { return ConstIndexableProxy<0>(*this); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec3<T>::y() const noexcept
    { return _data.template getAt<1>(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T>::template ConstIndexableProxy<1> Vec3<T>::y() noexcept
    { return ConstIndexableProxy<1>(*this); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec3<T>::z() const noexcept
    { return _data.template getAt<2>(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T>::template ConstIndexableProxy<2> Vec3<T>::z() noexcept
    { return ConstIndexableProxy<2>(*this); }


    /**************************************
     *          STP COORDINATES           *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec3<T>::s() const noexcept
    { return _data.template getAt<0>(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T>::template ConstIndexableProxy<0> Vec3<T>::s() noexcept
    { return ConstIndexableProxy<0>(*this); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec3<T>::t() const noexcept
    { return _data.template getAt<1>(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T>::template ConstIndexableProxy<1> Vec3<T>::t() noexcept
    { return ConstIndexableProxy<1>(*this); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec3<T>::p() const noexcept
    { return _data.template getAt<2>(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T>::template ConstIndexableProxy<2> Vec3<T>::p() noexcept
    { return ConstIndexableProxy<2>(*this); }



    /**************************************
     *         COLOR COORDINATES          *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec3<T>::r() const noexcept
    { return _data.template getAt<0>(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T>::template ConstIndexableProxy<0> Vec3<T>::r() noexcept
    { return ConstIndexableProxy<0>(*this); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec3<T>::g() const noexcept
    { return _data.template getAt<1>(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T>::template ConstIndexableProxy<1> Vec3<T>::g() noexcept
    { return ConstIndexableProxy<1>(*this); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec3<T>::b() const noexcept
    { return _data.template getAt<2>(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T>::template ConstIndexableProxy<2> Vec3<T>::b() noexcept
    { return ConstIndexableProxy<2>(*this); }



    /**************************************
     *              INDEXING              *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T>::IndexableProxy Vec3<T>::operator[](size_t idx) noexcept
    {
        FALCON_ASSERT_MSG(idx < DIMENSION, flcn::messages::assertion::VEC_OUT_OF_BOUNDS_ACCESS);
        return IndexableProxy(*this, idx);
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Vec3<T>::operator[](const size_t idx) const noexcept
    {
        FALCON_ASSERT_MSG(idx < DIMENSION, flcn::messages::assertion::VEC_OUT_OF_BOUNDS_ACCESS);
        return _data.getAt(idx);
    }


    template <Arithmetic T>
    template <size_t Index>
    FALCON_INLINE constexpr T Vec3<T>::get() const noexcept
    {
        static_assert(Index < DIMENSION && "[Vec3]: Out of bounds access");
        return _data.template getAt<Index>();
    }


    template <Arithmetic T>
    template <size_t Index>
    FALCON_INLINE constexpr T Vec3<T>::get() noexcept
    {
        static_assert(Index < DIMENSION && "[Vec3]: Out of bounds access");
        return _data.template getAt<Index>();
    }


    template <Arithmetic T>
    template <size_t Index>
    FALCON_INLINE constexpr void Vec3<T>::set(T value) noexcept
    {
        static_assert(Index < DIMENSION && "[Vec3]: Out of bounds mutation");
        _data.template setAt<Index>(value);
    }



    /// +---------------------------------------------------------------------------------------+
    /// |                                 SWIZZLING                                             |
    /// +---------------------------------------------------------------------------------------+

    template <Arithmetic T>
    template <size_t... Indices>
    FALCON_INLINE constexpr auto Vec3<T>::swizzle() const noexcept
    {
        constexpr size_t swizzleDimension = sizeof...(Indices);

        static_assert(((Indices < DIMENSION) && ...), "Index out of bounds!");
        static_assert(swizzleDimension > 0 && swizzleDimension <= DIMENSION &&
                      "Swizzle must return a scalar, or a 2D, or 3D vector.");

        if constexpr (swizzleDimension == 3)
        {
            return Vec3(_data.template getAt<Indices>()...);
        }
        else if constexpr (swizzleDimension == 2)
        {
            return Vec2(_data.template getAt<Indices>()...);
        }
        else
        {
            return T(_data.template getAt<Indices>()...);
        }
    }


    template <Arithmetic T>
    template <size_t... Indices>
    FALCON_INLINE constexpr auto Vec3<T>::swizzle(const Vec3& vec) noexcept
    { return vec.swizzle<Indices...>(); }



    /// +---------------------------------------------------------------------------------------+
    /// |                                   STORAGE                                             |
    /// +---------------------------------------------------------------------------------------+

    template <Arithmetic T>
    FALCON_INLINE constexpr void Vec3<T>::store(T* pBuffer) const noexcept
    {
        // TODO: Add death test for Vec3 and Vec2 unaligned address with aligned store
        [[maybe_unused]] constexpr size_t alignment = sizeof(T) > 4 ? 32 : 16;
        FALCON_ASSERT_MSG(reinterpret_cast<uintptr_t>(pBuffer) % alignment == 0,
                          "[Vec3/Store]: pBuffer must be aligned to 32(double, uint64_t, int64_t) or 16 bytes (for "
                          "other types). For unaligned store, use storeUnaligned");
        _data.storeAligned(pBuffer);
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr void Vec3<T>::store(const Vec3& vec, T* pBuffer) noexcept
    { vec.store(pBuffer); }


    template <Arithmetic T>
    FALCON_INLINE constexpr void Vec3<T>::storeUnaligned(T* pBuffer) const noexcept
    { _data.store(pBuffer); }


    template <Arithmetic T>
    FALCON_INLINE constexpr void Vec3<T>::storeUnaligned(const Vec3& vec, T* pBuffer) noexcept
    { vec.storeUnaligned(pBuffer); }



    /// +---------------------------------------------------------------------------------------+
    /// |                              EQUALITY OPERATORS                                       |
    /// +---------------------------------------------------------------------------------------+

    template <Arithmetic T>
    FALCON_INLINE constexpr bool Vec3<T>::allEq(const Vec3& rhs) const noexcept
    {
        const auto mask = _data == rhs._data;
        return static_cast<bool>(mask.horizontalAnd());
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool Vec3<T>::allEq(const Vec3& lhs, const Vec3& rhs) noexcept
    { return lhs.allEq(rhs); }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool Vec3<T>::anyNeq(const Vec3& rhs) const noexcept
    {
        const auto mask = _data != rhs._data;
        return static_cast<bool>(mask.horizontalOr());
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool Vec3<T>::anyNeq(const Vec3& lhs, const Vec3& rhs) noexcept
    { return lhs.anyNeq(rhs); }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool Vec3<T>::operator==(const Vec3& rhs) const noexcept
    { return allEq(rhs); }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool Vec3<T>::operator!=(const Vec3& rhs) const noexcept
    { return anyNeq(rhs); }



    /// +---------------------------------------------------------------------------------------+
    /// |                                EQUALITY (MASK)                                        |
    /// +---------------------------------------------------------------------------------------+

    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<Mask_t<T>> Vec3<T>::eq(const Vec3& rhs) const noexcept
    { return Vec3<Mask_t<T>>((_data == rhs._data).template cast<Mask_t<T>>()); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<Mask_t<T>> Vec3<T>::eq(const Vec3& lhs, const Vec3& rhs) noexcept
    { return lhs.eq(rhs); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<Mask_t<T>> Vec3<T>::neq(const Vec3& rhs) const noexcept
    { return Vec3<Mask_t<T>>((_data != rhs._data).template cast<Mask_t<T>>()); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<Mask_t<T>> Vec3<T>::neq(const Vec3& lhs, const Vec3& rhs) noexcept
    { return lhs.neq(rhs); }



    /// +---------------------------------------------------------------------------------------+
    /// |                                   COMPARISONS                                         |
    /// +---------------------------------------------------------------------------------------+

    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<typename UInt<T>::type> Vec3<T>::gt(const Vec3& rhs) const noexcept
        requires StrictArithmetic<T>
    { return Vec3<Mask_t<T>>((_data > rhs._data).template cast<Mask_t<T>>()); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<Mask_t<T>> Vec3<T>::gt(const Vec3& lhs, const Vec3& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.gt(rhs); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<Mask_t<T>> Vec3<T>::gte(const Vec3& rhs) const noexcept
        requires StrictArithmetic<T>
    { return Vec3<Mask_t<T>>((_data >= rhs._data).template cast<Mask_t<T>>()); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<Mask_t<T>> Vec3<T>::gte(const Vec3& lhs, const Vec3& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.gte(rhs); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<Mask_t<T>> Vec3<T>::lt(const Vec3& rhs) const noexcept
        requires StrictArithmetic<T>
    { return Vec3<Mask_t<T>>((_data < rhs._data).template cast<Mask_t<T>>()); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<Mask_t<T>> Vec3<T>::lt(const Vec3& lhs, const Vec3& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.lt(rhs); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<Mask_t<T>> Vec3<T>::lte(const Vec3& rhs) const noexcept
        requires StrictArithmetic<T>
    { return Vec3<Mask_t<T>>((_data <= rhs._data).template cast<Mask_t<T>>()); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<Mask_t<T>> Vec3<T>::lte(const Vec3& lhs, const Vec3& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.lte(rhs); }



    /// +---------------------------------------------------------------------------------------+
    /// |                             COMPARISON OPERATORS                                      |
    /// +---------------------------------------------------------------------------------------+

#ifdef ENABLE_FALCON_SHADER_OPERATORS

    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<Mask_t<T>> Vec3<T>::operator>(const Vec3& rhs) const noexcept
        requires StrictArithmetic<T>
    { return this->gt(rhs); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<Mask_t<T>> Vec3<T>::operator>=(const Vec3& rhs) const noexcept
        requires StrictArithmetic<T>
    { return this->gte(rhs); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<Mask_t<T>> Vec3<T>::operator<(const Vec3& rhs) const noexcept
        requires StrictArithmetic<T>
    { return this->lt(rhs); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<Mask_t<T>> Vec3<T>::operator<=(const Vec3& rhs) const noexcept
        requires StrictArithmetic<T>
    { return this->lte(rhs); }

#endif


    // TODO: BITWISE OPS



    /// +---------------------------------------------------------------------------------------+
    /// |                             ARITHMETIC OPERATORS                                      |
    /// +---------------------------------------------------------------------------------------+

    /*************************************
     *            ADDITION               *
     *************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T> Vec3<T>::operator+(const Vec3& rhs) const noexcept
        requires StrictArithmetic<T>
    { return Vec3(_data + rhs._data); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T>& Vec3<T>::operator+=(const Vec3& rhs) noexcept
        requires StrictArithmetic<T>
    {
        *this = *this + rhs;
        return *this;
    }


    /*************************************
     *           SUBTRACTION             *
     *************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T> Vec3<T>::operator-(const Vec3 rhs) const noexcept
        requires StrictArithmetic<T>
    { return Vec3(_data - rhs._data); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T>& Vec3<T>::operator-=(const Vec3& rhs) noexcept
        requires StrictArithmetic<T>
    {
        *this = *this - rhs;
        return *this;
    }


    /**************************************
     *         INVERT OPERATION           *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T> Vec3<T>::operator-() const noexcept
        requires SignedStrictArithmetic<T>
    { return Vec3(-_data); }


    /*************************************
     *           MULTIPLICATION          *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr Vec3<T> Vec3<T>::operator*(S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using RegType = internal::Vec3SimdStore<T>::Type;
        return Vec3(_data * RegType(static_cast<T>(scalar)));
    }


    template <StrictArithmetic T, StrictArithmetic S>
    FALCON_INLINE constexpr Vec3<T> operator*(S scalar, const Vec3<T>& vector) noexcept
        requires StrictArithmetic<T>
    { return vector * scalar; }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr Vec3<T>& Vec3<T>::operator*=(S scalar) noexcept
        requires StrictArithmetic<T>
    {
        *this = *this * scalar;
        return *this;
    }



    /*************************************
     *             DIVISION              *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr Vec3<T> Vec3<T>::operator/(S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            FALCON_ASSERT_MSG(flcn::abs(scalar) >= flcn::Config::EPSILON<T>,
                              flcn::messages::assertion::VEC_DIV_BY_ZERO);
        }
        else
        {
            FALCON_ASSERT_MSG(scalar != 0, flcn::messages::assertion::VEC_DIV_BY_ZERO);
        }

        // TODO: Benchmark this vs 1.0 / scalar and then multiplying
        return Vec3(_data / static_cast<T>(scalar));
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr Vec3<T>& Vec3<T>::operator/=(S scalar) noexcept
        requires StrictArithmetic<T>
    {
        *this = *this / scalar;
        return *this;
    }



    /// +---------------------------------------------------------------------------------------+
    /// |                               UTILITIES                                               |
    /// +---------------------------------------------------------------------------------------+

    template <Arithmetic T>
    FALCON_INLINE constexpr bool Vec3<T>::hasNaN() const noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            // Since nan is not equal to anything we need to query for nan
            // and use that property to convert from -nan(returned if an entry is nan) to a boolean.
            T isNan = _data.hasNan().horizontalOr();
            return isNan != isNan;
        }
        else
        {
            return false;
        }
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool Vec3<T>::hasNaN(const Vec3& vec) noexcept
    { return vec.hasNaN(); }


    // template <Arithmetic T>
    // template <StrictArithmetic S>
    // FALCON_INLINE constexpr Vec3<T> Vec3<T>::safeDiv(S scalar) const noexcept
    //     requires StrictArithmetic<T>
    // {
    //     if constexpr (std::is_floating_point_v<T>)
    //     {
    //         if (hasNaN() | flcn::isnan(scalar) | (flcn::abs(scalar) <= std::numeric_limits<S>::epsilon()))
    //         {
    //             return Vec3<T>::zero();
    //         }
    //     }
    //     if constexpr (std::is_integral_v<T>)
    //     {
    //         if (scalar == 0)
    //         {
    //             return Vec3<T>::zero();
    //         }
    //     }
    //
    //     return *this / scalar;
    // }
    //
    // template <Arithmetic T>
    // template <StrictArithmetic S>
    // FALCON_INLINE constexpr Vec3<T> Vec3<T>::safeDiv(const Vec3& vec, S scalar) noexcept
    //     requires StrictArithmetic<T>
    // { return vec.safeDiv(scalar); }
    //
    //
    // template <Arithmetic T>
    // template <StrictArithmetic S>
    // FALCON_INLINE constexpr Vec3<T> Vec3<T>::tryDiv(S scalar, OperationStatus& status) const noexcept
    //     requires StrictArithmetic<T>
    // {
    //     if constexpr (std::is_floating_point_v<T>)
    //     {
    //         if (hasNaN() | flcn::isnan(scalar))
    //         {
    //             status = OperationStatus::NANOPERAND;
    //             return Vec3<T>::zero();
    //         }
    //         if (flcn::abs(scalar) <= std::numeric_limits<S>::epsilon())
    //         {
    //             status = OperationStatus::DIVISIONBYZERO;
    //             return Vec3<T>::zero();
    //         }
    //     }
    //
    //     if constexpr (std::is_integral_v<T>)
    //     {
    //         if (scalar == 0)
    //         {
    //             status = OperationStatus::DIVISIONBYZERO;
    //             return Vec3<T>::zero();
    //         }
    //     }
    //
    //     status = OperationStatus::SUCCESS;
    //     return *this / scalar;
    // }
    //
    //
    // template <Arithmetic T>
    // template <StrictArithmetic S>
    // FALCON_INLINE constexpr Vec3<T> Vec3<T>::tryDiv(const Vec3& vec, S scalar, OperationStatus& status) noexcept
    //     requires StrictArithmetic<T>
    // { return vec.tryDiv(scalar, status); }


} // namespace flcn
