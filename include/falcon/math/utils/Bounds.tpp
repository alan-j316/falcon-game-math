#pragma once
/**
 * @file Bounds.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 26, 2026
 *
 * @brief Implementation of member functions declared in Bounds.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "falcon/core/Preprocessors.h"


namespace flcn
{
    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> min(const Vec2<T>& vecA, const Vec2<T>& vecB) noexcept
    { return vecA.min(vecB); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> max(const Vec2<T>& vecA, const Vec2<T>& vecB) noexcept
    { return vecA.max(vecB); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T> min(const Vec3<T>& vecA, const Vec3<T>& vecB) noexcept
    { return vecA.min(vecB); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T> max(const Vec3<T>& vecA, const Vec3<T>& vecB) noexcept
    { return vecA.max(vecB); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec4<T> min(const Vec4<T>& vecA, const Vec4<T>& vecB) noexcept
    { return vecA.min(vecB); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec4<T> max(const Vec4<T>& vecA, const Vec4<T>& vecB) noexcept
    { return vecA.max(vecB); }


    template <Arithmetic T>
    FALCON_INLINE constexpr simd::Vec2<T> min(const simd::Vec2<T>& vecA, const simd::Vec2<T>& vecB) noexcept
    { return vecA.min(vecB); }


    template <Arithmetic T>
    FALCON_INLINE constexpr simd::Vec2<T> max(const simd::Vec2<T>& vecA, const simd::Vec2<T>& vecB) noexcept
    { return vecA.max(vecB); }


    template <Arithmetic T>
    FALCON_INLINE constexpr simd::Vec3<T> min(const simd::Vec3<T>& vecA, const simd::Vec3<T>& vecB) noexcept
    { return vecA.min(vecB); }


    template <Arithmetic T>
    FALCON_INLINE constexpr simd::Vec3<T> max(const simd::Vec3<T>& vecA, const simd::Vec3<T>& vecB) noexcept
    { return vecA.max(vecB); }


} // namespace flcn
