#pragma once
/**
 * @file Comp.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 25, 2026
 *
 * @brief Implementation non-square matrix compositions defined in Comp.h
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
    FALCON_INLINE constexpr PromotedMat2<T, U> operator*(const Mat2x3<T>& lhs, const Mat3x2<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat2{ // Row 1
                     R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0)),
                     R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1)),
                     // Row 2
                     R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0)),
                     R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat2x3<T, U> operator*(const Mat2x3<T>& lhs, const Mat3<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat2x3{ // Row 1
                       R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0)),
                       R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1)),
                       R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2) + lhs(0, 2) * rhs(2, 2)),
                       // Row 2
                       R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0)),
                       R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1)),
                       R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2) + lhs(1, 2) * rhs(2, 2))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat2x4<T, U> operator*(const Mat2x3<T>& lhs, const Mat3x4<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat2x4{ // Row 1
                       R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0)),
                       R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1)),
                       R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2) + lhs(0, 2) * rhs(2, 2)),
                       R(lhs(0, 0) * rhs(0, 3) + lhs(0, 1) * rhs(1, 3) + lhs(0, 2) * rhs(2, 3)),
                       // Row 2
                       R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0)),
                       R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1)),
                       R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2) + lhs(1, 2) * rhs(2, 2)),
                       R(lhs(1, 0) * rhs(0, 3) + lhs(1, 1) * rhs(1, 3) + lhs(1, 2) * rhs(2, 3))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat2x3<T, U> operator*(const Mat2<T>& lhs, const Mat2x3<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat2x3{
            // Row 1
            R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0)), R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1)),
            R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2)),
            // Row 2
            R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0)), R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1)),
            R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2))
        };
    }



    /**************************************
     *                                    *
     *            MATRIX 2x4              *
     *                                    *
     **************************************/

    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat2<T, U> operator*(const Mat2x4<T>& lhs, const Mat4x2<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat2{ // Row 1
                     R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0) + lhs(0, 3) * rhs(3, 0)),
                     R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1) + lhs(0, 3) * rhs(3, 1)),
                     // Row 2
                     R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0) + lhs(1, 3) * rhs(3, 0)),
                     R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1) + lhs(1, 3) * rhs(3, 1))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat2x3<T, U> operator*(const Mat2x4<T>& lhs, const Mat4x3<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat2x3{ // Row 1
                       R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0) + lhs(0, 3) * rhs(3, 0)),
                       R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1) + lhs(0, 3) * rhs(3, 1)),
                       R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2) + lhs(0, 2) * rhs(2, 2) + lhs(0, 3) * rhs(3, 2)),
                       // Row 2
                       R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0) + lhs(1, 3) * rhs(3, 0)),
                       R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1) + lhs(1, 3) * rhs(3, 1)),
                       R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2) + lhs(1, 2) * rhs(2, 2) + lhs(1, 3) * rhs(3, 2))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat2x4<T, U> operator*(const Mat2x4<T>& lhs, const Mat4<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat2x4{ // Row 1
                       R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0) + lhs(0, 3) * rhs(3, 0)),
                       R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1) + lhs(0, 3) * rhs(3, 1)),
                       R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2) + lhs(0, 2) * rhs(2, 2) + lhs(0, 3) * rhs(3, 2)),
                       R(lhs(0, 0) * rhs(0, 3) + lhs(0, 1) * rhs(1, 3) + lhs(0, 2) * rhs(2, 3) + lhs(0, 3) * rhs(3, 3)),
                       // Row 2
                       R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0) + lhs(1, 3) * rhs(3, 0)),
                       R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1) + lhs(1, 3) * rhs(3, 1)),
                       R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2) + lhs(1, 2) * rhs(2, 2) + lhs(1, 3) * rhs(3, 2)),
                       R(lhs(1, 0) * rhs(0, 3) + lhs(1, 1) * rhs(1, 3) + lhs(1, 2) * rhs(2, 3) + lhs(1, 3) * rhs(3, 3))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat2x4<T, U> operator*(const Mat2<T>& lhs, const Mat2x4<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat2x4{
            // Row 1
            R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0)), R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1)),
            R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2)), R(lhs(0, 0) * rhs(0, 3) + lhs(0, 1) * rhs(1, 3)),
            // Row 2
            R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0)), R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1)),
            R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2)), R(lhs(1, 0) * rhs(0, 3) + lhs(1, 1) * rhs(1, 3))
        };
    }




    /**************************************
     *                                    *
     *            MATRIX 3x2              *
     *                                    *
     **************************************/

    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat3x2<T, U> operator*(const Mat3x2<T>& lhs, const Mat2<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat3x2{
            // Row 1
            R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0)), R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1)),
            // Row 2
            R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0)), R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1)),
            // Row 3
            R(lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0)), R(lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat3<T, U> operator*(const Mat3x2<T>& lhs, const Mat2x3<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat3{ // Row 1
                     R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0)), R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1)),
                     R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2)),
                     // Row 2
                     R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0)), R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1)),
                     R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2)),
                     // Row 3
                     R(lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0)), R(lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1)),
                     R(lhs(2, 0) * rhs(0, 2) + lhs(2, 1) * rhs(1, 2))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat3x4<T, U> operator*(const Mat3x2<T>& lhs, const Mat2x4<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat3x4{
            // Row 1
            R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0)), R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1)),
            R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2)), R(lhs(0, 0) * rhs(0, 3) + lhs(0, 1) * rhs(1, 3)),
            // Row 2
            R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0)), R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1)),
            R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2)), R(lhs(1, 0) * rhs(0, 3) + lhs(1, 1) * rhs(1, 3)),
            // Row 3
            R(lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0)), R(lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1)),
            R(lhs(2, 0) * rhs(0, 2) + lhs(2, 1) * rhs(1, 2)), R(lhs(2, 0) * rhs(0, 3) + lhs(2, 1) * rhs(1, 3))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat3x2<T, U> operator*(const Mat3<T>& lhs, const Mat3x2<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat3x2{ // Row 1
                       R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0)),
                       R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1)),
                       // Row 2
                       R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0)),
                       R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1)),
                       // Row 3
                       R(lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0) + lhs(2, 2) * rhs(2, 0)),
                       R(lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1) + lhs(2, 2) * rhs(2, 1))
        };
    }



    /**************************************
     *                                    *
     *            MATRIX 3x4              *
     *                                    *
     **************************************/

    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat3x2<T, U> operator*(const Mat3x4<T>& lhs, const Mat4x2<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat3x2{ // Row 1
                       R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0) + lhs(0, 3) * rhs(3, 0)),
                       R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1) + lhs(0, 3) * rhs(3, 1)),
                       // Row 2
                       R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0) + lhs(1, 3) * rhs(3, 0)),
                       R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1) + lhs(1, 3) * rhs(3, 1)),
                       // Row 3
                       R(lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0) + lhs(2, 2) * rhs(2, 0) + lhs(2, 3) * rhs(3, 0)),
                       R(lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1) + lhs(2, 2) * rhs(2, 1) + lhs(2, 3) * rhs(3, 1))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat3<T, U> operator*(const Mat3x4<T>& lhs, const Mat4x3<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat3{
            // Row 1
            R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0) + lhs(0, 3) * rhs(3, 0)),
            R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1) + lhs(0, 3) * rhs(3, 1)),
            R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2) + lhs(0, 2) * rhs(2, 2) + lhs(0, 3) * rhs(3, 2)),
            // Row 2
            R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0) + lhs(1, 3) * rhs(3, 0)),
            R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1) + lhs(1, 3) * rhs(3, 1)),
            R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2) + lhs(1, 2) * rhs(2, 2) + lhs(1, 3) * rhs(3, 2)),
            // Row 3
            R(lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0) + lhs(2, 2) * rhs(2, 0) + lhs(2, 3) * rhs(3, 0)),
            R(lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1) + lhs(2, 2) * rhs(2, 1) + lhs(2, 3) * rhs(3, 1)),
            R(lhs(2, 0) * rhs(0, 2) + lhs(2, 1) * rhs(1, 2) + lhs(2, 2) * rhs(2, 2) + lhs(2, 3) * rhs(3, 2)),
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat3x4<T, U> operator*(const Mat3x4<T>& lhs, const Mat4<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat3x4{ // Row 1
                       R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0) + lhs(0, 3) * rhs(3, 0)),
                       R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1) + lhs(0, 3) * rhs(3, 1)),
                       R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2) + lhs(0, 2) * rhs(2, 2) + lhs(0, 3) * rhs(3, 2)),
                       R(lhs(0, 0) * rhs(0, 3) + lhs(0, 1) * rhs(1, 3) + lhs(0, 2) * rhs(2, 3) + lhs(0, 3) * rhs(3, 3)),
                       // Row 2
                       R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0) + lhs(1, 3) * rhs(3, 0)),
                       R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1) + lhs(1, 3) * rhs(3, 1)),
                       R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2) + lhs(1, 2) * rhs(2, 2) + lhs(1, 3) * rhs(3, 2)),
                       R(lhs(1, 0) * rhs(0, 3) + lhs(1, 1) * rhs(1, 3) + lhs(1, 2) * rhs(2, 3) + lhs(1, 3) * rhs(3, 3)),
                       // Row 3
                       R(lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0) + lhs(2, 2) * rhs(2, 0) + lhs(2, 3) * rhs(3, 0)),
                       R(lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1) + lhs(2, 2) * rhs(2, 1) + lhs(2, 3) * rhs(3, 1)),
                       R(lhs(2, 0) * rhs(0, 2) + lhs(2, 1) * rhs(1, 2) + lhs(2, 2) * rhs(2, 2) + lhs(2, 3) * rhs(3, 2)),
                       R(lhs(2, 0) * rhs(0, 3) + lhs(2, 1) * rhs(1, 3) + lhs(2, 2) * rhs(2, 3) + lhs(2, 3) * rhs(3, 3))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat3x4<T, U> operator*(const Mat3<T>& lhs, const Mat3x4<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat3x4{ // Row 1
                       R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0)),
                       R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1)),
                       R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2) + lhs(0, 2) * rhs(2, 2)),
                       R(lhs(0, 0) * rhs(0, 3) + lhs(0, 1) * rhs(1, 3) + lhs(0, 2) * rhs(2, 3)),
                       // Row 2
                       R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0)),
                       R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1)),
                       R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2) + lhs(1, 2) * rhs(2, 2)),
                       R(lhs(1, 0) * rhs(0, 3) + lhs(1, 1) * rhs(1, 3) + lhs(1, 2) * rhs(2, 3)),
                       // Row 3
                       R(lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0) + lhs(2, 2) * rhs(2, 0)),
                       R(lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1) + lhs(2, 2) * rhs(2, 1)),
                       R(lhs(2, 0) * rhs(0, 2) + lhs(2, 1) * rhs(1, 2) + lhs(2, 2) * rhs(2, 2)),
                       R(lhs(2, 0) * rhs(0, 3) + lhs(2, 1) * rhs(1, 3) + lhs(2, 2) * rhs(2, 3))
        };
    }



    /**************************************
     *                                    *
     *            MATRIX 4x2              *
     *                                    *
     **************************************/

    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat4x2<T, U> operator*(const Mat4x2<T>& lhs, const Mat2<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat4x2{
            // Row 1
            R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0)), R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1)),
            // Row 2
            R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0)), R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1)),
            // Row 3
            R(lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0)), R(lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1)),
            // Row 4
            R(lhs(3, 0) * rhs(0, 0) + lhs(3, 1) * rhs(1, 0)), R(lhs(3, 0) * rhs(0, 1) + lhs(3, 1) * rhs(1, 1))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat4x3<T, U> operator*(const Mat4x2<T>& lhs, const Mat2x3<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat4x3{
            // Row 1
            R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0)), R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1)),
            R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2)),
            // Row 2
            R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0)), R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1)),
            R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2)),
            // Row 3
            R(lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0)), R(lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1)),
            R(lhs(2, 0) * rhs(0, 2) + lhs(2, 1) * rhs(1, 2)),
            // Row 4
            R(lhs(3, 0) * rhs(0, 0) + lhs(3, 1) * rhs(1, 0)), R(lhs(3, 0) * rhs(0, 1) + lhs(3, 1) * rhs(1, 1)),
            R(lhs(3, 0) * rhs(0, 2) + lhs(3, 1) * rhs(1, 2))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat4<T, U> operator*(const Mat4x2<T>& lhs, const Mat2x4<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat4{ // Row 1
                     R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0)), R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1)),
                     R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2)), R(lhs(0, 0) * rhs(0, 3) + lhs(0, 1) * rhs(1, 3)),
                     // Row 2
                     R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0)), R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1)),
                     R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2)), R(lhs(1, 0) * rhs(0, 3) + lhs(1, 1) * rhs(1, 3)),
                     // Row 3
                     R(lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0)), R(lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1)),
                     R(lhs(2, 0) * rhs(0, 2) + lhs(2, 1) * rhs(1, 2)), R(lhs(2, 0) * rhs(0, 3) + lhs(2, 1) * rhs(1, 3)),
                     // Row 4
                     R(lhs(3, 0) * rhs(0, 0) + lhs(3, 1) * rhs(1, 0)), R(lhs(3, 0) * rhs(0, 1) + lhs(3, 1) * rhs(1, 1)),
                     R(lhs(3, 0) * rhs(0, 2) + lhs(3, 1) * rhs(1, 2)), R(lhs(3, 0) * rhs(0, 3) + lhs(3, 1) * rhs(1, 3))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat4x2<T, U> operator*(const Mat4<T>& lhs, const Mat4x2<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat4x2{
            // Row 1
            R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0) + lhs(0, 3) * rhs(3, 0)),
            R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1) + lhs(0, 3) * rhs(3, 1)),
            // Row 2
            R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0) + lhs(1, 3) * rhs(3, 0)),
            R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1) + lhs(1, 3) * rhs(3, 1)),
            // Row 3
            R(lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0) + lhs(2, 2) * rhs(2, 0) + lhs(2, 3) * rhs(3, 0)),
            R(lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1) + lhs(2, 2) * rhs(2, 1) + lhs(2, 3) * rhs(3, 1)),
            // Row 4
            R(lhs(3, 0) * rhs(0, 0) + lhs(3, 1) * rhs(1, 0) + lhs(3, 2) * rhs(2, 0) + lhs(3, 3) * rhs(3, 0)),
            R(lhs(3, 0) * rhs(0, 1) + lhs(3, 1) * rhs(1, 1) + lhs(3, 2) * rhs(2, 1) + lhs(3, 3) * rhs(3, 1)),
        };
    }



    /**************************************
     *                                    *
     *            MATRIX 4x3              *
     *                                    *
     **************************************/

    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat4x2<T, U> operator*(const Mat4x3<T>& lhs, const Mat3x2<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat4x2{ // Row 1
                       R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0)),
                       R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1)),
                       // Row 2
                       R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0)),
                       R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1)),
                       // Row 3
                       R(lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0) + lhs(2, 2) * rhs(2, 0)),
                       R(lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1) + lhs(2, 2) * rhs(2, 1)),
                       // Row 4
                       R(lhs(3, 0) * rhs(0, 0) + lhs(3, 1) * rhs(1, 0) + lhs(3, 2) * rhs(2, 0)),
                       R(lhs(3, 0) * rhs(0, 1) + lhs(3, 1) * rhs(1, 1) + lhs(3, 2) * rhs(2, 1))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat4x3<T, U> operator*(const Mat4x3<T>& lhs, const Mat3<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat4x3{
            // Row 1
            R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0)),
            R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1)),
            R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2) + lhs(0, 2) * rhs(2, 2)),
            // Row 2
            R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0)),
            R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1)),
            R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2) + lhs(1, 2) * rhs(2, 2)),
            // Row 3
            R(lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0) + lhs(2, 2) * rhs(2, 0)),
            R(lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1) + lhs(2, 2) * rhs(2, 1)),
            R(lhs(2, 0) * rhs(0, 2) + lhs(2, 1) * rhs(1, 2) + lhs(2, 2) * rhs(2, 2)),
            // Row 4
            R(lhs(3, 0) * rhs(0, 0) + lhs(3, 1) * rhs(1, 0) + lhs(3, 2) * rhs(2, 0)),
            R(lhs(3, 0) * rhs(0, 1) + lhs(3, 1) * rhs(1, 1) + lhs(3, 2) * rhs(2, 1)),
            R(lhs(3, 0) * rhs(0, 2) + lhs(3, 1) * rhs(1, 2) + lhs(3, 2) * rhs(2, 2)),
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat4<T, U> operator*(const Mat4x3<T>& lhs, const Mat3x4<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat4{ // Row 1
                     R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0)),
                     R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1)),
                     R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2) + lhs(0, 2) * rhs(2, 2)),
                     R(lhs(0, 0) * rhs(0, 3) + lhs(0, 1) * rhs(1, 3) + lhs(0, 2) * rhs(2, 3)),
                     // Row 2
                     R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0)),
                     R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1)),
                     R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2) + lhs(1, 2) * rhs(2, 2)),
                     R(lhs(1, 0) * rhs(0, 3) + lhs(1, 1) * rhs(1, 3) + lhs(1, 2) * rhs(2, 3)),
                     // Row 3
                     R(lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0) + lhs(2, 2) * rhs(2, 0)),
                     R(lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1) + lhs(2, 2) * rhs(2, 1)),
                     R(lhs(2, 0) * rhs(0, 2) + lhs(2, 1) * rhs(1, 2) + lhs(2, 2) * rhs(2, 2)),
                     R(lhs(2, 0) * rhs(0, 3) + lhs(2, 1) * rhs(1, 3) + lhs(2, 2) * rhs(2, 3)),
                     // Row 4
                     R(lhs(3, 0) * rhs(0, 0) + lhs(3, 1) * rhs(1, 0) + lhs(3, 2) * rhs(2, 0)),
                     R(lhs(3, 0) * rhs(0, 1) + lhs(3, 1) * rhs(1, 1) + lhs(3, 2) * rhs(2, 1)),
                     R(lhs(3, 0) * rhs(0, 2) + lhs(3, 1) * rhs(1, 2) + lhs(3, 2) * rhs(2, 2)),
                     R(lhs(3, 0) * rhs(0, 3) + lhs(3, 1) * rhs(1, 3) + lhs(3, 2) * rhs(2, 3))
        };
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat4x3<T, U> operator*(const Mat4<T>& lhs, const Mat4x3<U>& rhs) noexcept
    {
        using R = PromotedValue_t<T, U>;
        return Mat4x3{ // Row 1
                       R(lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0) + lhs(0, 3) * rhs(3, 0)),
                       R(lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1) + lhs(0, 3) * rhs(3, 1)),
                       R(lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2) + lhs(0, 2) * rhs(2, 2) + lhs(0, 3) * rhs(3, 2)),
                       // Row 2
                       R(lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0) + lhs(1, 3) * rhs(3, 0)),
                       R(lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1) + lhs(1, 3) * rhs(3, 1)),
                       R(lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2) + lhs(1, 2) * rhs(2, 2) + lhs(1, 3) * rhs(3, 2)),
                       // Row 3
                       R(lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0) + lhs(2, 2) * rhs(2, 0) + lhs(2, 3) * rhs(3, 0)),
                       R(lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1) + lhs(2, 2) * rhs(2, 1) + lhs(2, 3) * rhs(3, 1)),
                       R(lhs(2, 0) * rhs(0, 2) + lhs(2, 1) * rhs(1, 2) + lhs(2, 2) * rhs(2, 2) + lhs(2, 3) * rhs(3, 2)),
                       // Row 4
                       R(lhs(3, 0) * rhs(0, 0) + lhs(3, 1) * rhs(1, 0) + lhs(3, 2) * rhs(2, 0) + lhs(3, 3) * rhs(3, 0)),
                       R(lhs(3, 0) * rhs(0, 1) + lhs(3, 1) * rhs(1, 1) + lhs(3, 2) * rhs(2, 1) + lhs(3, 3) * rhs(3, 1)),
                       R(lhs(3, 0) * rhs(0, 2) + lhs(3, 1) * rhs(1, 2) + lhs(3, 2) * rhs(2, 2) + lhs(3, 3) * rhs(3, 2))
        };
    }

} // namespace flcn
