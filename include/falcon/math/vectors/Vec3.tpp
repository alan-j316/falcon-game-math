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
    FALCON_INLINE constexpr Vec3<T>::Vec3(T v1, T v2, T v3) noexcept: _data{ v1, v2, v3, T(0) }
    {}

    // TODO: Update (Vec2, T) and (T, Vec2) inits to use direct register loads instead of access and loads
    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T>::Vec3(const Vec2<T> vec, T v) noexcept: _data{ vec.x(), vec.y(), v, T(0) }
    {}


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T>::Vec3(T v, const Vec2<T> vec) noexcept: _data{ v, vec.x(), vec.y(), T(0) }
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



} // namespace flcn
