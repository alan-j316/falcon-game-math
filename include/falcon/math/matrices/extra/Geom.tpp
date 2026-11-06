#pragma once
/**
 * @file MatMul.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 17, 2026
 *
 * @brief Implementation of functions defined in MatMul.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

namespace flcn
{

    /**************************************
     *                                    *
     *            MATRIX 2x3              *
     *                                    *
     **************************************/

    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec2<T, U> operator*(const Mat2x3<T>& mat, const Vec3<U>& vec) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return CVec2{ R(mat[0].x() * vec.x() + mat[1].x() * vec.y() + mat[2].x() * vec.z()),
                     R(mat[0].y() * vec.x() + mat[1].y() * vec.y() + mat[2].y() * vec.z()) };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedVec3<T, U> operator*(const CVec2<T>& vec, const Mat2x3<U>& mat) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Vec3{ R(vec.x() * mat(0, 0) + vec.y() * mat(1, 0)), R(vec.x() * mat(0, 1) + vec.y() * mat(1, 1)),
                     R(vec.x() * mat(0, 2) + vec.y() * mat(1, 2)) };
    }



    /**************************************
     *                                    *
     *            MATRIX 2x4              *
     *                                    *
     **************************************/

    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec2<T, U> operator*(const Mat2x4<T>& mat, const Vec4<U>& vec) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return CVec2{ R(mat[0].x() * vec.x() + mat[1].x() * vec.y() + mat[2].x() * vec.z() + mat[3].x() * vec.w()),
                     R(mat[0].y() * vec.x() + mat[1].y() * vec.y() + mat[2].y() * vec.z() + mat[3].y() * vec.w()) };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedVec4<T, U> operator*(const CVec2<T>& vec, const Mat2x4<U>& mat) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Vec4{ R(vec.x() * mat(0, 0) + vec.y() * mat(1, 0)), R(vec.x() * mat(0, 1) + vec.y() * mat(1, 1)),
                     R(vec.x() * mat(0, 2) + vec.y() * mat(1, 2)), R(vec.x() * mat(0, 3) + vec.y() * mat(1, 3)) };
    }



    /**************************************
     *                                    *
     *            MATRIX 3x2              *
     *                                    *
     **************************************/

    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedVec3<T, U> operator*(const Mat3x2<T>& mat, const CVec2<U>& vec) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Vec3{ R(mat[0].x() * vec.x() + mat[1].x() * vec.y()), R(mat[0].y() * vec.x() + mat[1].y() * vec.y()),
                     R(mat[0].z() * vec.x() + mat[1].z() * vec.y()) };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec2<T, U> operator*(const Vec3<T>& vec, const Mat3x2<U>& mat) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return CVec2{ R(vec.x() * mat(0, 0) + vec.y() * mat(1, 0) + vec.z() * mat(2, 0)),
                     R(vec.x() * mat(0, 1) + vec.y() * mat(1, 1) + vec.z() * mat(2, 1)) };
    }



    /**************************************
     *                                    *
     *            MATRIX 3x4              *
     *                                    *
     **************************************/

    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedVec3<T, U> operator*(const Mat3x4<T>& mat, const Vec4<U>& vec) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Vec3{ R(mat[0].x() * vec.x() + mat[1].x() * vec.y() + mat[2].x() * vec.z() + mat[3].x() * vec.w()),
                     R(mat[0].y() * vec.x() + mat[1].y() * vec.y() + mat[2].y() * vec.z() + mat[3].y() * vec.w()),
                     R(mat[0].z() * vec.x() + mat[1].z() * vec.y() + mat[2].z() * vec.z() + mat[3].z() * vec.w()) };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedVec4<T, U> operator*(const Vec3<T>& vec, const Mat3x4<U>& mat) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Vec4{ R(vec.x() * mat(0, 0) + vec.y() * mat(1, 0) + vec.z() * mat(2, 0)),
                     R(vec.x() * mat(0, 1) + vec.y() * mat(1, 1) + vec.z() * mat(2, 1)),
                     R(vec.x() * mat(0, 2) + vec.y() * mat(1, 2) + vec.z() * mat(2, 2)),
                     R(vec.x() * mat(0, 3) + vec.y() * mat(1, 3) + vec.z() * mat(2, 3)) };
    }



    /**************************************
     *                                    *
     *            MATRIX 4x2              *
     *                                    *
     **************************************/

    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedVec4<T, U> operator*(const Mat4x2<T>& mat, const CVec2<U>& vec) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Vec4{ R(mat[0].x() * vec.x() + mat[1].x() * vec.y()), R(mat[0].y() * vec.x() + mat[1].y() * vec.y()),
                     R(mat[0].z() * vec.x() + mat[1].z() * vec.y()), R(mat[0].w() * vec.x() + mat[1].w() * vec.y()) };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec2<T, U> operator*(const Vec4<T>& vec, const Mat4x2<U>& mat) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return CVec2{ R(vec.x() * mat(0, 0) + vec.y() * mat(1, 0) + vec.z() * mat(2, 0) + vec.w() * mat(3, 0)),
                     R(vec.x() * mat(0, 1) + vec.y() * mat(1, 1) + vec.z() * mat(2, 1) + vec.w() * mat(3, 1)) };
    }


    /**************************************
     *                                    *
     *            MATRIX 4x3              *
     *                                    *
     **************************************/

    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedVec4<T, U> operator*(const Mat4x3<T>& mat, const Vec3<U>& vec) noexcept
    {

        using R = PromotedValue_t<T, U>;
        return Vec4{ R(mat[0].x() * vec.x() + mat[1].x() * vec.y() + mat[2].x() * vec.z()),
                     R(mat[0].y() * vec.x() + mat[1].y() * vec.y() + mat[2].y() * vec.z()),
                     R(mat[0].z() * vec.x() + mat[1].z() * vec.y() + mat[2].z() * vec.z()),
                     R(mat[0].w() * vec.x() + mat[1].w() * vec.y() + mat[2].w() * vec.z()) };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedVec3<T, U> operator*(const Vec4<U>& vec, const Mat4x3<T>& mat) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Vec3{ R(vec.x() * mat(0, 0) + vec.y() * mat(1, 0) + vec.z() * mat(2, 0) + vec.w() * mat(3, 0)),
                     R(vec.x() * mat(0, 1) + vec.y() * mat(1, 1) + vec.z() * mat(2, 1) + vec.w() * mat(3, 1)),
                     R(vec.x() * mat(0, 2) + vec.y() * mat(1, 2) + vec.z() * mat(2, 2) + vec.w() * mat(3, 2)) };
    }

} // namespace flcn
