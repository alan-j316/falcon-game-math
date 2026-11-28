#pragma once
/**
 * @file Projection.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 28, 2026
 *
 * @brief Implementation of member function declared in Projection.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

namespace flcn
{
    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedFloatVec2<T, U> project(const Vec2<T>& vec, const Vec2<U>& onto) noexcept
    { return vec.project(onto); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedVec2<T, U> projectNorm(const Vec2<T>& vec, const Vec2<U>& onto) noexcept
    { return vec.projectNorm(onto); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedFloatVec2<T, U> safeProject(const Vec2<T>& vec, const Vec2<U>& onto) noexcept
    { return vec.safeProject(onto); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedVec2<T, U> safeProjectNorm(const Vec2<T>& vec, const Vec2<U>& onto) noexcept
    { return vec.safeProjectNorm(onto); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedFloatVec2<T, U> tryProject(const Vec2<T>& vec, const Vec2<U>& onto,
                                                               OperationStatus& status) noexcept
    { return vec.tryProject(onto, status); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedVec2<T, U> tryProjectNorm(const Vec2<T>& vec, const Vec2<U>& onto,
                                                              OperationStatus& status) noexcept
    { return vec.tryProjectNorm(onto, status); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedFloatVec2<T, U> reject(const Vec2<T>& vec, const Vec2<U>& from) noexcept
    { return vec.reject(from); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedVec2<T, U> rejectNorm(const Vec2<T>& vec, const Vec2<U>& from) noexcept
    { return vec.rejectNorm(from); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedFloatVec2<T, U> safeReject(const Vec2<T>& vec, const Vec2<U>& from) noexcept
    { return vec.safeReject(from); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedVec2<T, U> safeRejectNorm(const Vec2<T>& vec, const Vec2<U>& from) noexcept
    { return vec.safeRejectNorm(from); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedFloatVec2<T, U> tryReject(const Vec2<T>& vec, const Vec2<U>& from,
                                                              OperationStatus& status) noexcept
    { return vec.tryReject(from, status); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedVec2<T, U> tryRejectNorm(const Vec2<T>& vec, const Vec2<U>& from,
                                                             OperationStatus& status) noexcept
    { return vec.tryRejectNorm(from, status); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedFloatVec3<T, U> project(const Vec3<T>& vec, const Vec3<U>& onto) noexcept
    { return vec.project(onto); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedVec3<T, U> projectNorm(const Vec3<T>& vec, const Vec3<U>& onto) noexcept
    { return vec.projectNorm(onto); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedFloatVec3<T, U> safeProject(const Vec3<T>& vec, const Vec3<U>& onto) noexcept
    { return vec.safeProject(onto); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedVec3<T, U> safeProjectNorm(const Vec3<T>& vec, const Vec3<U>& onto) noexcept
    { return vec.safeProjectNorm(onto); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedFloatVec3<T, U> tryProject(const Vec3<T>& vec, const Vec3<U>& onto,
                                                               OperationStatus& status) noexcept
    { return vec.tryProject(onto, status); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedVec3<T, U> tryProjectNorm(const Vec3<T>& vec, const Vec3<U>& onto,
                                                              OperationStatus& status) noexcept
    { return vec.tryProjectNorm(onto, status); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedFloatVec3<T, U> reject(const Vec3<T>& vec, const Vec3<U>& from) noexcept
    { return vec.reject(from); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedVec3<T, U> rejectNorm(const Vec3<T>& vec, const Vec3<U>& from) noexcept
    { return vec.rejectNorm(from); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedFloatVec3<T, U> safeReject(const Vec3<T>& vec, const Vec3<U>& from) noexcept
    { return vec.safeReject(from); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedVec3<T, U> safeRejectNorm(const Vec3<T>& vec, const Vec3<U>& from) noexcept
    { return vec.safeRejectNorm(from); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedFloatVec3<T, U> tryReject(const Vec3<T>& vec, const Vec3<U>& from,
                                                              OperationStatus& status) noexcept
    { return vec.tryReject(from, status); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedVec3<T, U> tryRejectNorm(const Vec3<T>& vec, const Vec3<U>& from,
                                                             OperationStatus& status) noexcept
    { return vec.tryRejectNorm(from, status); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedFloatVec4<T, U> project(const Vec4<T>& vec, const Vec4<U>& onto) noexcept
    { return vec.project(onto); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedVec4<T, U> projectNorm(const Vec4<T>& vec, const Vec4<U>& onto) noexcept
    { return vec.projectNorm(onto); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedFloatVec4<T, U> safeProject(const Vec4<T>& vec, const Vec4<U>& onto) noexcept
    { return vec.safeProject(onto); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedVec4<T, U> safeProjectNorm(const Vec4<T>& vec, const Vec4<U>& onto) noexcept
    { return vec.safeProjectNorm(onto); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedFloatVec4<T, U> tryProject(const Vec4<T>& vec, const Vec4<U>& onto,
                                                               OperationStatus& status) noexcept
    { return vec.tryProject(onto, status); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedVec4<T, U> tryProjectNorm(const Vec4<T>& vec, const Vec4<U>& onto,
                                                              OperationStatus& status) noexcept
    { return vec.tryProjectNorm(onto, status); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedFloatVec4<T, U> reject(const Vec4<T>& vec, const Vec4<U>& from) noexcept
    { return vec.reject(from); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedVec4<T, U> rejectNorm(const Vec4<T>& vec, const Vec4<U>& from) noexcept
    { return vec.rejectNorm(from); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedFloatVec4<T, U> safeReject(const Vec4<T>& vec, const Vec4<U>& from) noexcept
    { return vec.safeReject(from); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedVec4<T, U> safeRejectNorm(const Vec4<T>& vec, const Vec4<U>& from) noexcept
    { return vec.safeRejectNorm(from); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedFloatVec4<T, U> tryReject(const Vec4<T>& vec, const Vec4<U>& from,
                                                              OperationStatus& status) noexcept
    { return vec.tryReject(from, status); }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedVec4<T, U> tryRejectNorm(const Vec4<T>& vec, const Vec4<U>& from,
                                                             OperationStatus& status) noexcept
    { return vec.tryRejectNorm(from, status); }


    template <FPArithmetic T>
    FALCON_INLINE constexpr simd::Vec2<T> project(const simd::Vec2<T>& vec, const simd::Vec2<T>& onto) noexcept
    { return vec.project(onto); }


    template <FPArithmetic T>
    FALCON_INLINE constexpr simd::Vec2<T> projectNorm(const simd::Vec2<T>& vec, const simd::Vec2<T>& onto) noexcept
    { return vec.projectNorm(onto); }


    template <FPArithmetic T>
    FALCON_INLINE constexpr simd::Vec2<T> safeProject(const simd::Vec2<T>& vec, const simd::Vec2<T>& onto) noexcept
    { return vec.safeProject(onto); }


    template <FPArithmetic T>
    FALCON_INLINE constexpr simd::Vec2<T> safeProjectNorm(const simd::Vec2<T>& vec, const simd::Vec2<T>& onto) noexcept
    { return vec.safeProjectNorm(onto); }


    template <FPArithmetic T>
    FALCON_INLINE constexpr simd::Vec2<T> tryProject(const simd::Vec2<T>& vec, const simd::Vec2<T>& onto,
                                                     OperationStatus& status) noexcept
    { return vec.tryProject(onto, status); }


    template <FPArithmetic T>
    FALCON_INLINE constexpr simd::Vec2<T> tryProjectNorm(const simd::Vec2<T>& vec, const simd::Vec2<T>& onto,
                                                         OperationStatus& status) noexcept
    { return vec.tryProjectNorm(onto, status); }


    template <FPArithmetic T>
    FALCON_INLINE constexpr simd::Vec2<T> reject(const simd::Vec2<T>& vec, const simd::Vec2<T>& from) noexcept
    { return vec.reject(from); }


    template <FPArithmetic T>
    FALCON_INLINE constexpr simd::Vec2<T> rejectNorm(const simd::Vec2<T>& vec, const simd::Vec2<T>& from) noexcept
    { return vec.rejectNorm(from); }


    template <FPArithmetic T>
    FALCON_INLINE constexpr simd::Vec2<T> safeReject(const simd::Vec2<T>& vec, const simd::Vec2<T>& from) noexcept
    { return vec.safeReject(from); }


    template <FPArithmetic T>
    FALCON_INLINE constexpr simd::Vec2<T> safeRejectNorm(const simd::Vec2<T>& vec, const simd::Vec2<T>& from) noexcept
    { return vec.safeRejectNorm(from); }


    template <FPArithmetic T>
    FALCON_INLINE constexpr simd::Vec2<T> tryReject(const simd::Vec2<T>& vec, const simd::Vec2<T>& from,
                                                    OperationStatus& status) noexcept
    { return vec.tryReject(from, status); }


    template <FPArithmetic T>
    FALCON_INLINE constexpr simd::Vec2<T> tryRejectNorm(const simd::Vec2<T>& vec, const simd::Vec2<T>& from,
                                                        OperationStatus& status) noexcept
    { return vec.tryRejectNorm(from, status); }
} // namespace flcn
