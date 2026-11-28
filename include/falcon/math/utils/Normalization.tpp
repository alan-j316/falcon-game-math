#pragma once
/**
 * @file Normalization.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 28, 2026
 *
 * @brief Implementation of member function declared in Normalization.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include <falcon/core/Preprocessors.h>

namespace flcn
{
    template <StrictArithmetic T>
    FALCON_INLINE constexpr Vec2<Magnitude<T>> normalize(const Vec2<T>& vec) noexcept
    { return vec.normalize(); }


    template <StrictArithmetic T>
    FALCON_INLINE constexpr Vec2<Magnitude<T>> safeNormalize(const Vec2<T>& vec) noexcept
        requires StrictArithmetic<T>
    { return vec.safeNormalize(); }


    template <StrictArithmetic T>
    FALCON_INLINE constexpr Vec2<Magnitude<T>> tryNormalize(const Vec2<T>& vec, OperationStatus& status) noexcept
    { return vec.tryNormalize(status); }


    template <StrictArithmetic T>
    FALCON_INLINE constexpr Vec3<Magnitude<T>> normalize(const Vec3<T>& vec) noexcept
    { return vec.normalize(); }


    template <StrictArithmetic T>
    FALCON_INLINE constexpr Vec3<Magnitude<T>> safeNormalize(const Vec3<T>& vec) noexcept
        requires StrictArithmetic<T>
    { return vec.safeNormalize(); }


    template <StrictArithmetic T>
    FALCON_INLINE constexpr Vec3<Magnitude<T>> tryNormalize(const Vec3<T>& vec, OperationStatus& status) noexcept
    { return vec.tryNormalize(status); }


    template <StrictArithmetic T>
    FALCON_INLINE constexpr Vec4<Magnitude<T>> normalize(const Vec4<T>& vec) noexcept
    { return vec.normalize(); }


    template <StrictArithmetic T>
    FALCON_INLINE constexpr Vec4<Magnitude<T>> safeNormalize(const Vec4<T>& vec) noexcept
        requires StrictArithmetic<T>
    { return vec.safeNormalize(); }


    template <StrictArithmetic T>
    FALCON_INLINE constexpr Vec4<Magnitude<T>> tryNormalize(const Vec4<T>& vec, OperationStatus& status) noexcept
    { return vec.tryNormalize(status); }


    template <FPArithmetic T>
    FALCON_INLINE constexpr simd::Vec2<T> normalize(const simd::Vec2<T>& vec) noexcept
    { return vec.normalize(); }


    template <FPArithmetic T>
    FALCON_INLINE constexpr simd::Vec2<T> safeNormalize(const simd::Vec2<T>& vec) noexcept
    { return vec.safeNormalize(); }


    template <FPArithmetic T>
    FALCON_INLINE constexpr simd::Vec2<T> tryNormalize(const simd::Vec2<T>& vec, OperationStatus& status) noexcept
    { return vec.tryNormalize(status); }


    template <FPArithmetic T>
    FALCON_INLINE constexpr simd::Vec3<T> normalize(const simd::Vec3<T>& vec) noexcept
    { return vec.normalize(); }


    template <FPArithmetic T>
    FALCON_INLINE constexpr simd::Vec3<T> safeNormalize(const simd::Vec3<T>& vec) noexcept
    { return vec.safeNormalize(); }


    template <FPArithmetic T>
    FALCON_INLINE constexpr simd::Vec3<T> tryNormalize(const simd::Vec3<T>& vec, OperationStatus& status) noexcept
    { return vec.tryNormalize(status); }

} // namespace flcn
