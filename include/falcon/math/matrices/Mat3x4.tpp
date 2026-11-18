#pragma once
/**
 * @file Mat3x4.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 20, 2026
 *
 * @brief @ref Mat3x4 template implementation.
 * @details This file contains the definitions of the template members declared in Mat3x4.h
 *
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "falcon/math/common/Types.h"
#include "falcon/math/common/Wrappers.h"

#include <type_traits>


#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wbitwise-instead-of-logical"
#endif

namespace flcn
{

    /*************************************
     *                                   *
     *            INITIALIZERS           *
     *                                   *
     *************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr Mat3x4<T>::Mat3x4(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21, T m22,
                                           T m23) noexcept
        : _data{ Vec3<T>(m00, m10, m20), Vec3<T>(m01, m11, m21), Vec3<T>(m02, m12, m22), Vec3<T>(m03, m13, m23) }
    {}


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat3x4<T>::Mat3x4(const Vec3<T>& col0, const Vec3<T>& col1, const Vec3<T>& col2,
                                           const Vec3<T>& col3) noexcept
        : _data{ col0, col1, col2, col3 }
    {}


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr Mat3x4<T>::Mat3x4(const Mat3x4<U>& other) noexcept
    {
        (*this)(0, 0) = static_cast<T>(other(0, 0));
        (*this)(0, 1) = static_cast<T>(other(0, 1));
        (*this)(0, 2) = static_cast<T>(other(0, 2));
        (*this)(0, 3) = static_cast<T>(other(0, 3));

        (*this)(1, 0) = static_cast<T>(other(1, 0));
        (*this)(1, 1) = static_cast<T>(other(1, 1));
        (*this)(1, 2) = static_cast<T>(other(1, 2));
        (*this)(1, 3) = static_cast<T>(other(1, 3));

        (*this)(2, 0) = static_cast<T>(other(2, 0));
        (*this)(2, 1) = static_cast<T>(other(2, 1));
        (*this)(2, 2) = static_cast<T>(other(2, 2));
        (*this)(2, 3) = static_cast<T>(other(2, 3));
    }



    /*************************************
     *                                   *
     *            ACCESSORS              *
     *                                   *
     *************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T>& Mat3x4<T>::operator[](const std::size_t col) noexcept
    {
        FALCON_ASSERT_MSG(col < COLUMNS, flcn::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return _data[col];
    }

    template <Arithmetic T>
    FALCON_INLINE constexpr const Vec3<T>& Mat3x4<T>::operator[](const std::size_t col) const noexcept
    {
        FALCON_ASSERT_MSG(col < COLUMNS, flcn::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return _data[col];
    }

    template <Arithmetic T>
    FALCON_INLINE constexpr T& Mat3x4<T>::operator()(const std::size_t row, const std::size_t col) noexcept
    {
        FALCON_ASSERT_MSG(col < COLUMNS && row < ROWS, flcn::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return _data[col][row];
    }

    template <Arithmetic T>
    FALCON_INLINE constexpr const T& Mat3x4<T>::operator()(const std::size_t row, const std::size_t col) const noexcept
    {
        FALCON_ASSERT_MSG(col < COLUMNS && row < ROWS, flcn::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return _data[col][row];
    }


    /***************************************
     *                                     *
     *             EQUALITY                *
     *                                     *
     ***************************************/

    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Mat3x4<T>::allEq(const Mat3x4<U>& rhs, const double epsilon) const noexcept
    {
        // MSVC's FALCON_INLINE constexpr evaluator incorrectly yields true for NaN relational comparisons.
        // To enforce strict IEEE 754 compliance at compile-time, we explicitly short-circuit
        // if a NaN is detected. Runtime evaluation is safely deferred to hardware intrinsics.
#ifdef _MSC_VER
        if (std::is_constant_evaluated())
        {
            if (hasNaN() || rhs.hasNaN())
            {
                return false;
            }
        }
#endif
        return _data[0].allEq(rhs[0], epsilon) && _data[1].allEq(rhs[1], epsilon) && _data[2].allEq(rhs[2], epsilon) &&
            _data[3].allEq(rhs[3], epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Mat3x4<T>::allEq(const Mat3x4& lhs, const Mat3x4<U>& rhs, const double epsilon) noexcept
    { return lhs.allEq(rhs, epsilon); }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Mat3x4<T>::anyNeq(const Mat3x4<U>& rhs, const double epsilon) const noexcept
    {
        // MSVC's FALCON_INLINE constexpr evaluator incorrectly yields true for NaN relational comparisons.
        // To enforce strict IEEE 754 compliance at compile-time, we explicitly short-circuit
        // if a NaN is detected. Runtime evaluation is safely deferred to hardware intrinsics.
#ifdef _MSC_VER
        if (std::is_constant_evaluated())
        {
            if (hasNaN() || rhs.hasNaN())
            {
                return true;
            }
        }
#endif
        return _data[0].anyNeq(rhs[0], epsilon) || _data[1].anyNeq(rhs[1], epsilon) ||
            _data[2].anyNeq(rhs[2], epsilon) || _data[3].anyNeq(rhs[3], epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Mat3x4<T>::anyNeq(const Mat3x4& lhs, const Mat3x4<U>& rhs, const double epsilon) noexcept
    { return lhs.anyNeq(rhs, epsilon); }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Mat3x4<T>::operator==(const Mat3x4<U>& rhs) const noexcept
    { return allEq(rhs); }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Mat3x4<T>::operator!=(const Mat3x4<U>& rhs) const noexcept
    { return anyNeq(rhs); }



    /**************************************
     *                                    *
     *        ARITHMETIC OPERATORS        *
     *                                    *
     **************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat3x4<T, U> Mat3x4<T>::operator+(const Mat3x4<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
        return Mat3x4<R>(_data[0] + rhs[0], _data[1] + rhs[1], _data[2] + rhs[2], _data[3] + rhs[3]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    Mat3x4<T>& Mat3x4<T>::operator+=(const Mat3x4<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] += rhs[0];
        _data[1] += rhs[1];
        _data[2] += rhs[2];
        _data[3] += rhs[3];
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat3x4<T, U> Mat3x4<T>::operator-(const Mat3x4<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
        return Mat3x4<R>(_data[0] - rhs[0], _data[1] - rhs[1], _data[2] - rhs[2], _data[3] - rhs[3]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr Mat3x4<T>& Mat3x4<T>::operator-=(const Mat3x4<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] -= rhs[0];
        _data[1] -= rhs[1];
        _data[2] -= rhs[2];
        _data[3] -= rhs[3];
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedMat3x4<T, S> Mat3x4<T>::operator*(const S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;
        return Mat3x4<R>(scalar * _data[0], scalar * _data[1], scalar * _data[2], scalar * _data[3]);
    }


    template <StrictArithmetic T, StrictArithmetic S>
    FALCON_INLINE constexpr PromotedMat3x4<T, S> operator*(S scalar, const Mat3x4<T>& matrix) noexcept
        requires StrictArithmetic<T>
    { return matrix * scalar; }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr Mat3x4<T>& Mat3x4<T>::operator*=(const S scalar) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] *= scalar;
        _data[1] *= scalar;
        _data[2] *= scalar;
        _data[3] *= scalar;
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedMat3x4<T, S> Mat3x4<T>::operator/(S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;
        if constexpr (std::is_floating_point_v<R>)
        {
            FALCON_ASSERT_MSG(flcn::abs(R(scalar)) > Config::EPSILON<R>, messages::assertion::MAT_DIV_BY_ZERO);
            R factor = R(1) / static_cast<R>(scalar);
            return Mat3x4<R>(_data[0] * factor, _data[1] * factor, _data[2] * factor, _data[3] * factor);
        }
        else
        {
            FALCON_ASSERT_MSG(scalar != S(0), messages::assertion::MAT_DIV_BY_ZERO);
            R tScalar = static_cast<R>(scalar);
            return Mat3x4<R>(_data[0] / tScalar, _data[1] / tScalar, _data[2] / tScalar, _data[3] / tScalar);
        }
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr Mat3x4<T>& Mat3x4<T>::operator/=(const S scalar) noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;

        FALCON_ASSERT_MSG(flcn::abs(scalar) > Config::EPSILON<S>, messages::assertion::MAT_DIV_BY_ZERO);

        if constexpr (std::is_floating_point_v<R>)
        {
            R factor = R(1) / static_cast<R>(scalar);

            _data[0][0] = static_cast<R>(_data[0][0]) * factor;
            _data[1][0] = static_cast<R>(_data[1][0]) * factor;
            _data[2][0] = static_cast<R>(_data[2][0]) * factor;
            _data[3][0] = static_cast<R>(_data[3][0]) * factor;

            _data[0][1] = static_cast<R>(_data[0][1]) * factor;
            _data[1][1] = static_cast<R>(_data[1][1]) * factor;
            _data[2][1] = static_cast<R>(_data[2][1]) * factor;
            _data[3][1] = static_cast<R>(_data[3][1]) * factor;

            _data[0][2] = static_cast<R>(_data[0][2]) * factor;
            _data[1][2] = static_cast<R>(_data[1][2]) * factor;
            _data[2][2] = static_cast<R>(_data[2][2]) * factor;
            _data[3][2] = static_cast<R>(_data[3][2]) * factor;
        }
        else
        {
            _data[0][0] = static_cast<T>(_data[0][0] / static_cast<R>(scalar));
            _data[1][0] = static_cast<T>(_data[1][0] / static_cast<R>(scalar));
            _data[2][0] = static_cast<T>(_data[2][0] / static_cast<R>(scalar));
            _data[3][0] = static_cast<T>(_data[3][0] / static_cast<R>(scalar));

            _data[0][1] = static_cast<T>(_data[0][1] / static_cast<R>(scalar));
            _data[1][1] = static_cast<T>(_data[1][1] / static_cast<R>(scalar));
            _data[2][1] = static_cast<T>(_data[2][1] / static_cast<R>(scalar));
            _data[3][1] = static_cast<T>(_data[3][1] / static_cast<R>(scalar));

            _data[0][2] = static_cast<T>(_data[0][2] / static_cast<R>(scalar));
            _data[1][2] = static_cast<T>(_data[1][2] / static_cast<R>(scalar));
            _data[2][2] = static_cast<T>(_data[2][2] / static_cast<R>(scalar));
            _data[3][2] = static_cast<T>(_data[3][2] / static_cast<R>(scalar));
        }
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedMat3x4<T, S> Mat3x4<T>::safeDiv(const S scalar, Mat3x4 fallback) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
        {
            if (flcn::abs(scalar) <= std::numeric_limits<R>::epsilon() || flcn::isnan(scalar) || hasNaN())
            {
                return static_cast<Mat3x4<R>>(fallback);
            }
        }
        if constexpr (std::is_integral_v<R>)
        {
            if (scalar == 0)
            {
                return static_cast<Mat3x4<R>>(fallback);
            }
        }

        return *this / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedMat3x4<T, S> Mat3x4<T>::safeDiv(const Mat3x4& mat, const S scalar,
                                                                 Mat3x4 fallback) noexcept
        requires StrictArithmetic<T>
    { return mat.safeDiv(scalar, fallback); }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedMat3x4<T, S> Mat3x4<T>::tryDiv(const S scalar, OperationStatus& status,
                                                                Mat3x4 fallback) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
        { // TODO: Check || vs | with benchmarks
            if (static_cast<int>(hasNaN()) | static_cast<int>(flcn::isnan(scalar)))
            {
                status = OperationStatus::NANOPERAND;
                return static_cast<Mat3x4<R>>(fallback);
            }
            if (flcn::abs(scalar) <= std::numeric_limits<R>::epsilon())
            {
                status = OperationStatus::DIVISIONBYZERO;
                return static_cast<Mat3x4<R>>(fallback);
            }
        }

        if constexpr (std::is_integral_v<R>)
        {
            if (scalar == 0)
            {
                status = OperationStatus::DIVISIONBYZERO;
                return static_cast<Mat3x4<R>>(fallback);
            }
        }


        status = OperationStatus::SUCCESS;
        return *this / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedMat3x4<T, S> Mat3x4<T>::tryDiv(const Mat3x4& mat, const S scalar,
                                                                OperationStatus& status, Mat3x4 fallback) noexcept
        requires StrictArithmetic<T>
    { return mat.tryDiv(scalar, status, fallback); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat3x4<T> Mat3x4<T>::operator-() const noexcept
        requires SignedStrictArithmetic<T>
    { return Mat3x4{ -_data[0], -_data[1], -_data[2], -_data[3] }; }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4x3<T> Mat3x4<T>::transpose() const noexcept
    {
        return Mat4x3{ _data[0][0], _data[0][1], _data[0][2], _data[1][0], _data[1][1], _data[1][2],
                       _data[2][0], _data[2][1], _data[2][2], _data[3][0], _data[3][1], _data[3][2] };
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4x3<T> Mat3x4<T>::transpose(const Mat3x4& matrix) noexcept
    { return matrix.transpose(); }


    /**************************************
     *                                    *
     *           MATRIX ALGEBRA           *
     *                                    *
     **************************************/

    //
    //
    //     template <Arithmetic T>
    //     FALCON_INLINE constexpr Mat3x4<T> Mat3x4<T>::transpose() const noexcept
    //     {
    //         // NOTE: _data is a column major vector so _data[0][1] gives element at first row and zeroth column.
    //         return Mat3x4(_data[0][0], _data[0][1], _data[1][0], _data[1][1]);
    //     }
    //
    //
    //     template <Arithmetic T>
    //     FALCON_INLINE constexpr Mat3x4<T> Mat3x4<T>::transpose(const Mat3x4& matrix) noexcept
    //     {
    //         return matrix.transpose();
    //     }



    /**************************************
     *                                    *
     *             UTILITIES              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr bool Mat3x4<T>::hasInf() const noexcept
    { return _data[0].hasInf() || _data[1].hasInf() || _data[2].hasInf() || _data[3].hasInf(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool Mat3x4<T>::hasInf(const Mat3x4& matrix) noexcept
    { return matrix.hasInf(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool Mat3x4<T>::hasNaN() const noexcept
    { return _data[0].hasNaN() || _data[1].hasNaN() || _data[2].hasNaN() || _data[3].hasNaN(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool Mat3x4<T>::hasNaN(const Mat3x4& matrix) noexcept
    { return matrix.hasNaN(); }


} // namespace flcn


#if defined(__clang__)
    #pragma clang diagnostic pop
#endif
