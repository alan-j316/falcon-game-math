#pragma once
/**
 * @file Interpolation.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 26, 2026
 *
 * @brief Implementation of member functions declared in Interpolation.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

namespace flcn
{
    template <Arithmetic T, std::floating_point F>
    FALCON_INLINE constexpr Vec2<T> mix(const Vec2<T>& vecA, const Vec2<T>& vecB, const F factor) noexcept
    { return vecA.mix(vecB, factor); }


    template <Arithmetic T, std::floating_point F>
    FALCON_INLINE constexpr Vec3<T> mix(const Vec3<T>& vecA, const Vec3<T>& vecB, const F factor) noexcept
    { return vecA.mix(vecB, factor); }


    template <Arithmetic T, std::floating_point F>
    FALCON_INLINE constexpr Vec4<T> mix(const Vec4<T>& vecA, const Vec4<T>& vecB, const F factor) noexcept
    { return vecA.mix(vecB, factor); }


    template <std::floating_point T, std::floating_point F>
    FALCON_INLINE constexpr simd::Vec2<T> mix(const simd::Vec2<T>& vecA, const simd::Vec2<T>& vecB, const F factor) noexcept
    { return vecA.mix(vecB, static_cast<T>(factor)); }

    template <std::floating_point T, std::floating_point F>
    FALCON_INLINE constexpr simd::Vec3<T> mix(const simd::Vec3<T>& vecA, const simd::Vec3<T>& vecB, const F factor) noexcept
    { return vecA.mix(vecB, static_cast<T>(factor)); }

} // namespace flcn
