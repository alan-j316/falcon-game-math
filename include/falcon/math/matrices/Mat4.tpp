#pragma once
/**
 * @file Mat4.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: February 15, 2026
 *
 * @brief @ref Mat4 template implementation.
 * @details This file contains the definitions of the template members declared in Mat4.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


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
    FALCON_INLINE constexpr Mat4<T>::Mat4(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21, T m22,
                                       T m23, T m30, T m31, T m32, T m33) noexcept
        : _data{ Vec4{ T(m00), T(m10), T(m20), T(m30) }, Vec4{ T(m01), T(m11), T(m21), T(m31) },
                 Vec4{ T(m02), T(m12), T(m22), T(m32) }, Vec4{ T(m03), T(m13), T(m23), T(m33) } }
    {}


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4<T>::Mat4(const Vec4<T>& col0, const Vec4<T>& col1, const Vec4<T>& col2,
                                       const Vec4<T>& col3) noexcept
        : _data{ col0, col1, col2, col3 }
    {}


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4<T>::Mat4(T d0, T d1, T d2, T d3) noexcept
        : _data{ Vec4{ T(d0), T(0), T(0), T(0) }, Vec4{ T(0), T(d1), T(0), T(0) }, Vec4{ T(0), T(0), T(d2), T(0) },
                 Vec4{ T(0), T(0), T(0), T(d3) } }
    {}


    template <Arithmetic T>
    template <Arithmetic U>
    FALCON_INLINE constexpr Mat4<T>::Mat4(const Mat4<U>& other) noexcept
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
        (*this)(3, 0) = static_cast<T>(other(3, 0));
        (*this)(3, 1) = static_cast<T>(other(3, 1));
        (*this)(3, 2) = static_cast<T>(other(3, 2));
        (*this)(3, 3) = static_cast<T>(other(3, 3));
    }


    /*************************************
     *                                   *
     *            ACCESSORS              *
     *                                   *
     *************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr Vec4<T>& Mat4<T>::operator[](std::size_t col) noexcept
    {
        FALCON_ASSERT_MSG(col < COLUMNS, flcn::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return _data[col];
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr const Vec4<T>& Mat4<T>::operator[](std::size_t col) const noexcept
    {
        FALCON_ASSERT_MSG(col < COLUMNS, flcn::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return _data[col];
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr T& Mat4<T>::operator()(std::size_t row, std::size_t col) noexcept
    {
        FALCON_ASSERT_MSG(col < COLUMNS && row < ROWS, flcn::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return _data[col][row];
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr const T& Mat4<T>::operator()(std::size_t row, std::size_t col) const noexcept
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
    FALCON_INLINE constexpr bool Mat4<T>::allEq(const Mat4<U>& rhs, double epsilon) const noexcept
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
    FALCON_INLINE constexpr bool Mat4<T>::allEq(const Mat4& lhs, const Mat4<U>& rhs, double epsilon) noexcept
    { return lhs.allEq(rhs, epsilon); }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Mat4<T>::anyNeq(const Mat4<U>& rhs, double epsilon) const noexcept
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
    FALCON_INLINE constexpr bool Mat4<T>::anyNeq(const Mat4& lhs, const Mat4<U>& rhs, double epsilon) noexcept
    { return lhs.anyNeq(rhs, epsilon); }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Mat4<T>::operator==(const Mat4<U>& rhs) const noexcept
    { return allEq(rhs); }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Mat4<T>::operator!=(const Mat4<U>& rhs) const noexcept
    { return anyNeq(rhs); }


    /**************************************
     *                                    *
     *        ARITHMETIC OPERATORS        *
     *                                    *
     **************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat4<T, U> Mat4<T>::operator+(const Mat4<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
        return Mat4<R>(_data[0] + rhs[0], _data[1] + rhs[1], _data[2] + rhs[2], _data[3] + rhs[3]);
    }

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    Mat4<T>& Mat4<T>::operator+=(const Mat4<U>& rhs) noexcept
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
    FALCON_INLINE constexpr PromotedMat4<T, U> Mat4<T>::operator-(const Mat4<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
        return Mat4<R>(_data[0] - rhs[0], _data[1] - rhs[1], _data[2] - rhs[2], _data[3] - rhs[3]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr Mat4<T>& Mat4<T>::operator-=(const Mat4<U>& rhs) noexcept
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
    FALCON_INLINE constexpr PromotedMat4<T, S> Mat4<T>::operator*(S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;
        return Mat4<R>(scalar * _data[0], scalar * _data[1], scalar * _data[2], scalar * _data[3]);
    }


    template <StrictArithmetic T, StrictArithmetic S>
    FALCON_INLINE constexpr PromotedMat4<T, S> operator*(S scalar, const Mat4<T>& matrix) noexcept
    { return matrix * scalar; }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr Mat4<T>& Mat4<T>::operator*=(S scalar) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] *= scalar;
        _data[1] *= scalar;
        _data[2] *= scalar;
        _data[3] *= scalar;
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedVec4<T, U> Mat4<T>::operator*(const Vec4<U>& vec) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
#if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__AVX2__)
        // #error "FMA ACTIVE!" // For checking if FMA execution path is active.
        if constexpr (std::is_floating_point_v<R>)
        {
            if (!std::is_constant_evaluated())
            {
                return Vec4<R>(std::fma(static_cast<R>(_data[0][0]), static_cast<R>(vec[0]),
                                        std::fma(static_cast<R>(_data[1][0]), static_cast<R>(vec[1]),
                                                 std::fma(static_cast<R>(_data[2][0]), static_cast<R>(vec[2]),
                                                          static_cast<R>(_data[3][0]) * static_cast<R>(vec[3])))), // x
                               std::fma(static_cast<R>(_data[0][1]), static_cast<R>(vec[0]),
                                        std::fma(static_cast<R>(_data[1][1]), static_cast<R>(vec[1]),
                                                 std::fma(static_cast<R>(_data[2][1]), static_cast<R>(vec[2]),
                                                          static_cast<R>(_data[3][1]) * static_cast<R>(vec[3])))), // y
                               std::fma(static_cast<R>(_data[0][2]), static_cast<R>(vec[0]),
                                        std::fma(static_cast<R>(_data[1][2]), static_cast<R>(vec[1]),
                                                 std::fma(static_cast<R>(_data[2][2]), static_cast<R>(vec[2]),
                                                          static_cast<R>(_data[3][2]) * static_cast<R>(vec[3])))), // z
                               std::fma(static_cast<R>(_data[0][3]), static_cast<R>(vec[0]),
                                        std::fma(static_cast<R>(_data[1][3]), static_cast<R>(vec[1]),
                                                 std::fma(static_cast<R>(_data[2][3]), static_cast<R>(vec[2]),
                                                          static_cast<R>(_data[3][3]) * static_cast<R>(vec[3]))))); // w
            }
        }
#endif
        R x = static_cast<R>(_data[0][0]) * static_cast<R>(vec[0]) +
            static_cast<R>(_data[1][0]) * static_cast<R>(vec[1]) +
            static_cast<R>(_data[2][0]) * static_cast<R>(vec[2]) + static_cast<R>(_data[3][0]) * static_cast<R>(vec[3]);

        R y = static_cast<R>(_data[0][1]) * static_cast<R>(vec[0]) +
            static_cast<R>(_data[1][1]) * static_cast<R>(vec[1]) +
            static_cast<R>(_data[2][1]) * static_cast<R>(vec[2]) + static_cast<R>(_data[3][1]) * static_cast<R>(vec[3]);

        R z = static_cast<R>(_data[0][2]) * static_cast<R>(vec[0]) +
            static_cast<R>(_data[1][2]) * static_cast<R>(vec[1]) +
            static_cast<R>(_data[2][2]) * static_cast<R>(vec[2]) + static_cast<R>(_data[3][2]) * static_cast<R>(vec[3]);

        R w = static_cast<R>(_data[0][3]) * static_cast<R>(vec[0]) +
            static_cast<R>(_data[1][3]) * static_cast<R>(vec[1]) +
            static_cast<R>(_data[2][3]) * static_cast<R>(vec[2]) + static_cast<R>(_data[3][3]) * static_cast<R>(vec[3]);

        return Vec4<R>(x, y, z, w);
    }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr PromotedVec4<T, U> operator*(const Vec4<T>& vec, const Mat4<U>& matrix) noexcept
    {
        using R = PromotedValue_t<T, U>;
#if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__AVX2__)
        // #error "FMA ACTIVE!" // For checking if FMA execution path is active.
        if constexpr (std::is_floating_point_v<R>)
        {
            if (!std::is_constant_evaluated())
            {
                return Vec4<R>(std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 0)),
                                        std::fma(static_cast<R>(vec[1]), static_cast<R>(matrix(1, 0)),
                                                 std::fma(static_cast<R>(vec[2]), static_cast<R>(matrix(2, 0)),
                                                          static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 0))))),
                               std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 1)),
                                        std::fma(static_cast<R>(vec[1]), static_cast<R>(matrix(1, 1)),
                                                 std::fma(static_cast<R>(vec[2]), static_cast<R>(matrix(2, 1)),
                                                          static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 1))))),
                               std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 2)),
                                        std::fma(static_cast<R>(vec[1]), static_cast<R>(matrix(1, 2)),
                                                 std::fma(static_cast<R>(vec[2]), static_cast<R>(matrix(2, 2)),
                                                          static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 2))))),
                               std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 3)),
                                        std::fma(static_cast<R>(vec[1]), static_cast<R>(matrix(1, 3)),
                                                 std::fma(static_cast<R>(vec[2]), static_cast<R>(matrix(2, 3)),
                                                          static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 3))))));
            }
        }

#endif
        R x = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 0)) +
            static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 0)) +
            static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 0)) +
            static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 0));

        R y = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 1)) +
            static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 1)) +
            static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 1)) +
            static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 1));

        R z = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 2)) +
            static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 2)) +
            static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 2)) +
            static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 2));

        R w = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 3)) +
            static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 3)) +
            static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 3)) +
            static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 3));

        return Vec4<R>(x, y, z, w);
    }


    template <StrictArithmetic T, StrictArithmetic U>
    FALCON_INLINE constexpr Vec4<T>& operator*=(Vec4<T>& vec, const Mat4<U>& matrix) noexcept
    {
        using R = PromotedValue_t<T, U>;
#if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__AVX2__)
        // #error "FMA ACTIVE!" // For checking if FMA execution path is active.
        if constexpr (std::is_floating_point_v<R>)
        {
            if (!std::is_constant_evaluated())
            {
                R x = std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 0)),
                               std::fma(static_cast<R>(vec[1]), static_cast<R>(matrix(1, 0)),
                                        std::fma(static_cast<R>(vec[2]), static_cast<R>(matrix(2, 0)),
                                                 static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 0)))));
                R y = std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 1)),
                               std::fma(static_cast<R>(vec[1]), static_cast<R>(matrix(1, 1)),
                                        std::fma(static_cast<R>(vec[2]), static_cast<R>(matrix(2, 1)),
                                                 static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 1)))));
                R z = std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 2)),
                               std::fma(static_cast<R>(vec[1]), static_cast<R>(matrix(1, 2)),
                                        std::fma(static_cast<R>(vec[2]), static_cast<R>(matrix(2, 2)),
                                                 static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 2)))));
                R w = std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 3)),
                               std::fma(static_cast<R>(vec[1]), static_cast<R>(matrix(1, 3)),
                                        std::fma(static_cast<R>(vec[2]), static_cast<R>(matrix(2, 3)),
                                                 static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 3)))));

                vec.x() = static_cast<T>(x);
                vec.y() = static_cast<T>(y);
                vec.z() = static_cast<T>(z);
                vec.w() = static_cast<T>(w);

                return vec;
            }
        }
#endif
        R x = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 0)) +
            static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 0)) +
            static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 0)) +
            static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 0));

        R y = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 1)) +
            static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 1)) +
            static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 1)) +
            static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 1));

        R z = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 2)) +
            static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 2)) +
            static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 2)) +
            static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 2));

        R w = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 3)) +
            static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 3)) +
            static_cast<R>(vec[2]) * static_cast<R>(matrix(2, 3)) +
            static_cast<R>(vec[3]) * static_cast<R>(matrix(3, 3));

        vec.x() = static_cast<T>(x);
        vec.y() = static_cast<T>(y);
        vec.z() = static_cast<T>(z);
        vec.w() = static_cast<T>(w);

        return vec;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat4<T, U> Mat4<T>::operator*(const Mat4<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
        return Mat4<R>(*this * rhs[0], *this * rhs[1], *this * rhs[2], *this * rhs[3]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr Mat4<T>& Mat4<T>::operator*=(const Mat4<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        const auto mat = *this * rhs;
        _data[0]       = static_cast<Vec4<T>>(mat[0]);
        _data[1]       = static_cast<Vec4<T>>(mat[1]);
        _data[2]       = static_cast<Vec4<T>>(mat[2]);
        _data[3]       = static_cast<Vec4<T>>(mat[3]);
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedMat4<T, S> Mat4<T>::operator/(const S& scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;
        if constexpr (std::is_floating_point_v<R>)
        {
            FALCON_ASSERT_MSG(flcn::abs(R(scalar)) > Config::EPSILON<R>, messages::assertion::MAT_DIV_BY_ZERO);
            R factor = R(1) / static_cast<R>(scalar);
            return Mat4<R>(_data[0] * factor, _data[1] * factor, _data[2] * factor, _data[3] * factor);
        }
        else
        {
            FALCON_ASSERT_MSG(scalar != S(0), messages::assertion::MAT_DIV_BY_ZERO);
            R tScalar = static_cast<R>(scalar);
            return Mat4<R>(_data[0] / tScalar, _data[1] / tScalar, _data[2] / tScalar, _data[3] / tScalar);
        }
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr Mat4<T>& Mat4<T>::operator/=(const S& scalar) noexcept
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

            _data[0][3] = static_cast<R>(_data[0][3]) * factor;
            _data[1][3] = static_cast<R>(_data[1][3]) * factor;
            _data[2][3] = static_cast<R>(_data[2][3]) * factor;
            _data[3][3] = static_cast<R>(_data[3][3]) * factor;
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

            _data[0][3] = static_cast<T>(_data[0][3] / static_cast<R>(scalar));
            _data[1][3] = static_cast<T>(_data[1][3] / static_cast<R>(scalar));
            _data[2][3] = static_cast<T>(_data[2][3] / static_cast<R>(scalar));
            _data[3][3] = static_cast<T>(_data[3][3] / static_cast<R>(scalar));
        }
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedMat4<T, S> Mat4<T>::safeDiv(S scalar, Mat4 fallback) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
        {
            if (flcn::abs(scalar) <= std::numeric_limits<R>::epsilon() || flcn::isnan(scalar) || hasNaN())
            {
                return static_cast<Mat4<R>>(fallback);
            }
        }
        if constexpr (std::is_integral_v<R>)
        {
            if (scalar == 0)
            {
                return static_cast<Mat4<R>>(fallback);
            }
        }

        return *this / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedMat4<T, S> Mat4<T>::safeDiv(const Mat4& mat, S scalar, Mat4 fallback) noexcept
        requires StrictArithmetic<T>
    { return mat.safeDiv(scalar, fallback); }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedMat4<T, S> Mat4<T>::tryDiv(S scalar, OperationStatus& status,
                                                            Mat4 fallback) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
        {
            // TODO: Check || vs | with benchmarks
            // Theoretically the slowest method since NaN checks are performed before division by zero
            if (static_cast<int>(hasNaN()) | static_cast<int>(flcn::isnan(scalar)))
            {
                status = OperationStatus::NANOPERAND;
                return static_cast<Mat4<R>>(fallback);
            }
            if (flcn::abs(scalar) <= std::numeric_limits<R>::epsilon())
            {
                status = OperationStatus::DIVISIONBYZERO;
                return static_cast<Mat4<R>>(fallback);
            }
        }

        if constexpr (std::is_integral_v<R>)
        {
            if (scalar == 0)
            {
                status = OperationStatus::DIVISIONBYZERO;
                return static_cast<Mat4<R>>(fallback);
            }
        }

        status = OperationStatus::SUCCESS;
        return *this / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedMat4<T, S> Mat4<T>::tryDiv(const Mat4& mat, S scalar, OperationStatus& status,
                                                            Mat4 fallback) noexcept
        requires StrictArithmetic<T>
    { return mat.tryDiv(scalar, status, fallback); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4<T> Mat4<T>::operator-() const noexcept
        requires SignedStrictArithmetic<T>
    { return Mat4{ -_data[0], -_data[1], -_data[2], -_data[3] }; }



    /**************************************
     *                                    *
     *           MATRIX ALGEBRA           *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T Mat4<T>::determinant() const noexcept
        requires SignedStrictArithmetic<T>
    {
        // TODO: Replace with flcn::swizzle after factor implementation
        auto a = _data[0].template swizzle<axis::X, axis::Y, axis::Z>();
        auto b = _data[1].template swizzle<axis::X, axis::Y, axis::Z>();
        auto c = _data[2].template swizzle<axis::X, axis::Y, axis::Z>();
        auto d = _data[3].template swizzle<axis::X, axis::Y, axis::Z>();

        auto x = _data[0][3];
        auto y = _data[1][3];
        auto z = _data[2][3];
        auto w = _data[3][3];

        auto s = a.cross(b);
        auto t = c.cross(d);
        auto u = y * a - x * b;
        auto v = w * c - z * d;

        return s.dot(v) + t.dot(u);
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Mat4<T>::determinant(const Mat4& matrix) noexcept
        requires SignedStrictArithmetic<T>
    { return matrix.determinant(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4<T> Mat4<T>::transpose() const noexcept
    {
        /**
         * @note Although the code doesn't seem to transpose, since we are storing in column major order
         *       _data[row][col] actually gives _data[col][row]
         */
        return Mat4(_data[0][0], _data[0][1], _data[0][2], _data[0][3], _data[1][0], _data[1][1], _data[1][2],
                    _data[1][3], _data[2][0], _data[2][1], _data[2][2], _data[2][3], _data[3][0], _data[3][1],
                    _data[3][2], _data[3][3]);
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4<T> Mat4<T>::transpose(const Mat4& matrix) noexcept
    { return matrix.transpose(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4<Magnitude<T>> Mat4<T>::inverse() const noexcept
        requires SignedStrictArithmetic<T>
    {
        using R = Magnitude<T>;

        auto a = static_cast<Vec3<R>>(_data[0].template swizzle<axis::X, axis::Y, axis::Z>());
        auto b = static_cast<Vec3<R>>(_data[1].template swizzle<axis::X, axis::Y, axis::Z>());
        auto c = static_cast<Vec3<R>>(_data[2].template swizzle<axis::X, axis::Y, axis::Z>());
        auto d = _data[3].template swizzle<axis::X, axis::Y, axis::Z>();

        // NOTE: NOT CONSTEXPR COMPATIBLE
        // const auto& a = reinterpret_cast<const Vec3<R>&>(_data[0]);
        // const auto& b = reinterpret_cast<const Vec3<R>&>(_data[1]);
        // const auto& c = reinterpret_cast<const Vec3<R>&>(_data[2]);
        // const auto& d = reinterpret_cast<const Vec3<R>&>(_data[3]);

        auto x = _data[0][3];
        auto y = _data[1][3];
        auto z = _data[2][3];
        auto w = _data[3][3];

        auto s = static_cast<Vec3<R>>(a.cross(b));
        auto t = c.cross(d);
        auto u = y * a - x * b;
        auto v = w * c - z * d;

        auto det = s.dot(v) + t.dot(u);
        FALCON_ASSERT_MSG(flcn::abs(det) > Config::EPSILON<R>, messages::assertion::MAT_INV_ZERO_DETERMINANT);

        auto invDet = R(1) / det;

        s *= invDet;
        t *= invDet;
        u *= invDet;
        v *= invDet;

        auto row0 = b.cross(v) + t * y;
        auto row1 = v.cross(a) - t * x;
        auto row2 = d.cross(u) + s * w;
        auto row3 = u.cross(c) - s * z;

        return Mat4<R>(row0.x(), row0.y(), row0.z(), -b.dot(t), row1.x(), row1.y(), row1.z(), a.dot(t), row2.x(),
                       row2.y(), row2.z(), -d.dot(s), row3.x(), row3.y(), row3.z(), c.dot(s));
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4<Magnitude<T>> Mat4<T>::inverse(const Mat4& matrix) noexcept
        requires SignedStrictArithmetic<T>
    { return matrix.inverse(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4<Magnitude<T>> Mat4<T>::safeInverse(Mat4 fallback) const noexcept
        requires SignedStrictArithmetic<T>
    {
        using R = Magnitude<T>;

        auto a = static_cast<Vec3<R>>(_data[0].template swizzle<axis::X, axis::Y, axis::Z>());
        auto b = static_cast<Vec3<R>>(_data[1].template swizzle<axis::X, axis::Y, axis::Z>());
        auto c = static_cast<Vec3<R>>(_data[2].template swizzle<axis::X, axis::Y, axis::Z>());
        auto d = _data[3].template swizzle<axis::X, axis::Y, axis::Z>();

        auto x = _data[0][3];
        auto y = _data[1][3];
        auto z = _data[2][3];
        auto w = _data[3][3];

        auto s = static_cast<Vec3<R>>(a.cross(b));
        auto t = c.cross(d);
        auto u = y * a - x * b;
        auto v = w * c - z * d;

        auto det = s.dot(v) + t.dot(u);

        if constexpr (std::is_floating_point_v<T>)
        {
            if (hasNaN() || flcn::abs(det) <= std::numeric_limits<T>::epsilon())
            {
                return static_cast<Mat4<R>>(fallback);
            }
        }
        if constexpr (std::is_integral_v<T>)
        {
            if (det == 0)
            {
                return static_cast<Mat4<R>>(fallback);
            }
        }

        auto invDet = R(1) / det;

        s *= invDet;
        t *= invDet;
        u *= invDet;
        v *= invDet;

        auto row0 = b.cross(v) + t * y;
        auto row1 = v.cross(a) - t * x;
        auto row2 = d.cross(u) + s * w;
        auto row3 = u.cross(c) - s * z;

        return Mat4<R>(row0.x(), row0.y(), row0.z(), -b.dot(t), row1.x(), row1.y(), row1.z(), a.dot(t), row2.x(),
                       row2.y(), row2.z(), -d.dot(s), row3.x(), row3.y(), row3.z(), c.dot(s));
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4<Magnitude<T>> Mat4<T>::safeInverseOf(const Mat4& matrix, Mat4 fallback) noexcept
        requires SignedStrictArithmetic<T>
    { return matrix.safeInverse(fallback); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4<Magnitude<T>> Mat4<T>::tryInverse(OperationStatus& status, Mat4 fallback) const noexcept
        requires SignedStrictArithmetic<T>
    {
        using R = Magnitude<T>;

        auto a = static_cast<Vec3<R>>(_data[0].template swizzle<axis::X, axis::Y, axis::Z>());
        auto b = static_cast<Vec3<R>>(_data[1].template swizzle<axis::X, axis::Y, axis::Z>());
        auto c = static_cast<Vec3<R>>(_data[2].template swizzle<axis::X, axis::Y, axis::Z>());
        auto d = _data[3].template swizzle<axis::X, axis::Y, axis::Z>();

        auto x = _data[0][3];
        auto y = _data[1][3];
        auto z = _data[2][3];
        auto w = _data[3][3];

        auto s = static_cast<Vec3<R>>(a.cross(b));
        auto t = c.cross(d);
        auto u = y * a - x * b;
        auto v = w * c - z * d;

        auto det = s.dot(v) + t.dot(u);

        if constexpr (std::is_floating_point_v<T>)
        {
            if (hasNaN())
            {
                status = OperationStatus::NANOPERAND;
                return static_cast<Mat4<R>>(fallback);
            }
            if (flcn::abs(det) <= std::numeric_limits<T>::epsilon())
            {
                status = OperationStatus::DIVISIONBYZERO;
                return static_cast<Mat4<R>>(fallback);
            }
        }

        auto invDet = R(1) / det;

        s *= invDet;
        t *= invDet;
        u *= invDet;
        v *= invDet;

        auto row0 = b.cross(v) + t * y;
        auto row1 = v.cross(a) - t * x;
        auto row2 = d.cross(u) + s * w;
        auto row3 = u.cross(c) - s * z;

        status = OperationStatus::SUCCESS;
        return Mat4<R>(row0.x(), row0.y(), row0.z(), -b.dot(t), row1.x(), row1.y(), row1.z(), a.dot(t), row2.x(),
                       row2.y(), row2.z(), -d.dot(s), row3.x(), row3.y(), row3.z(), c.dot(s));
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4<Magnitude<T>> Mat4<T>::tryInverseOf(const Mat4& matrix, OperationStatus& status,
                                                                  Mat4 fallback) noexcept
        requires SignedStrictArithmetic<T>
    { return matrix.tryInverse(status, fallback); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Mat4<T>::trace() const noexcept
        requires StrictArithmetic<T>
    { return _data[0][0] + _data[1][1] + _data[2][2] + _data[3][3]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Mat4<T>::trace(const Mat4& matrix) noexcept
        requires StrictArithmetic<T>
    { return matrix.trace(); }


    /**************************************
     *                                    *
     *             UTILITIES              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr bool Mat4<T>::hasInf() const noexcept
    { return _data[0].hasInf() || _data[1].hasInf() || _data[2].hasInf() || _data[3].hasInf(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool Mat4<T>::hasInf(const Mat4& matrix) noexcept
    { return matrix.hasInf(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool Mat4<T>::hasNaN() const noexcept
    { return _data[0].hasNaN() || _data[1].hasNaN() || _data[2].hasNaN() || _data[3].hasNaN(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool Mat4<T>::hasNaN(const Mat4& matrix) noexcept
    { return matrix.hasNaN(); }



    /**************************************
     *                                    *
     *       TRANSFORMATION FACTORIES     *
     *                                    *
     **************************************/

    template <Arithmetic T>
    template <std::floating_point U>
    FALCON_INLINE constexpr Mat4<T> Mat4<T>::makeRotationX(U angle) noexcept
        requires SignedStrictArithmetic<T>
    {
        using R  = PromotedValue_t<T, U>;
        R cosine = std::cos(angle);
        R sine   = std::sin(angle);
#ifdef FALCON_LEFT_HANDED
        return Mat4{
            T(1), T(0), T(0), T(0), T(0), cosine, sine, T(0), T(0), -sine, cosine, T(0), T(0), T(0), T(0), T(1)
        };
#else
        return Mat4{
            T(1), T(0), T(0), T(0), T(0), cosine, -sine, T(0), T(0), sine, cosine, T(0), T(0), T(0), T(0), T(1)
        };
#endif
    }


    template <Arithmetic T>
    template <std::floating_point U>
    FALCON_INLINE constexpr Mat4<T> Mat4<T>::makeRotationX(const U angle, const Vec3<T>& center) noexcept
        requires SignedStrictArithmetic<T>
    {
        using R  = PromotedValue_t<T, U>;
        R cosine = std::cos(angle);
        R sine   = std::sin(angle);
#ifdef FALCON_LEFT_HANDED
        return Mat4{ T(1), T(0),  T(0),   T(center.x()), T(0), cosine, sine, T(center.y()),
                     T(0), -sine, cosine, T(center.z()), T(0), T(0),   T(0), T(1) };
#else
        return Mat4{ T(1), T(0), T(0),   T(center.x()), T(0), cosine, -sine, T(center.y()),
                     T(0), sine, cosine, T(center.z()), T(0), T(0),   T(0),  T(1) };
#endif
    }


    template <Arithmetic T>
    template <std::floating_point U>
    FALCON_INLINE constexpr Mat4<T> Mat4<T>::makeRotationY(U angle) noexcept
        requires SignedStrictArithmetic<T>
    {
        using R  = PromotedValue_t<T, U>;
        R cosine = std::cos(angle);
        R sine   = std::sin(angle);
#ifdef FALCON_LEFT_HANDED
        return Mat4{
            cosine, T(0), -sine, T(0), T(0), T(1), T(0), T(0), sine, T(0), cosine, T(0), T(0), T(0), T(0), T(1)
        };
#else
        return Mat4{
            cosine, T(0), sine, T(0), T(0), T(1), T(0), T(0), -sine, T(0), cosine, T(0), T(0), T(0), T(0), T(1)
        };
#endif
    }


    template <Arithmetic T>
    template <std::floating_point U>
    FALCON_INLINE constexpr Mat4<T> Mat4<T>::makeRotationY(const U angle, const Vec3<T>& center) noexcept
        requires SignedStrictArithmetic<T>
    {
        using R  = PromotedValue_t<T, U>;
        R cosine = std::cos(angle);
        R sine   = std::sin(angle);
#ifdef FALCON_LEFT_HANDED
        return Mat4{ cosine, T(0), -sine,  T(center.x()), T(0), T(1), T(0), T(center.y()),
                     sine,   T(0), cosine, T(center.z()), T(0), T(0), T(0), T(1) };
#else
        return Mat4{ cosine, T(0), sine,   T(center.x()), T(0), T(1), T(0), T(center.y()),
                     -sine,  T(0), cosine, T(center.z()), T(0), T(0), T(0), T(1) };
#endif
    }


    template <Arithmetic T>
    template <std::floating_point U>
    FALCON_INLINE constexpr Mat4<T> Mat4<T>::makeRotationZ(U angle) noexcept
        requires SignedStrictArithmetic<T>
    {
        using R  = PromotedValue_t<T, U>;
        R cosine = std::cos(angle);
        R sine   = std::sin(angle);

#ifdef FALCON_LEFT_HANDED
        return Mat4{
            cosine, sine, T(0), T(0), -sine, cosine, T(0), T(0), T(0), T(0), T(1), T(0), T(0), T(0), T(0), T(1)
        };
#else
        return Mat4{
            cosine, -sine, T(0), T(0), sine, cosine, T(0), T(0), T(0), T(0), T(1), T(0), T(0), T(0), T(0), T(1)
        };
#endif
    }


    template <Arithmetic T>
    template <std::floating_point U>
    FALCON_INLINE constexpr Mat4<T> Mat4<T>::makeRotationZ(U angle, const Vec3<T>& center) noexcept
        requires SignedStrictArithmetic<T>
    {
        using R  = PromotedValue_t<T, U>;
        R cosine = std::cos(angle);
        R sine   = std::sin(angle);
#ifdef FALCON_LEFT_HANDED
        return Mat4{ cosine, sine, T(0), T(center.x()), -sine, cosine, T(0), T(center.y()),
                     T(0),   T(0), T(1), T(center.z()), T(0),  T(0),   T(0), T(1) };
#else
        return Mat4{ cosine, -sine, T(0), T(center.x()), sine, cosine, T(0), T(center.y()),
                     T(0),   T(0),  T(1), T(center.z()), T(0), T(0),   T(0), T(1) };
#endif
    }


    template <Arithmetic T>
    template <std::floating_point U>
    FALCON_INLINE constexpr PromotedFloatMat4<T, U> Mat4<T>::makeRotation(U angle, const Vec3<T>& axis) noexcept
        requires StrictArithmetic<T>
    {
        using S = Magnitude<std::common_type_t<T, U>>;

        S c = static_cast<S>(std::cos(angle));
#ifdef FALCON_LEFT_HANDED
        S s = -static_cast<S>(std::sin(angle));
#else
        S s = static_cast<S>(std::sin(angle));
#endif
        S d = 1 - c;

        S x = static_cast<S>(axis.x()) * d;
        S y = static_cast<S>(axis.y()) * d;
        S z = static_cast<S>(axis.z()) * d;

        S axay = x * axis.y();
        S axaz = x * axis.z();
        S ayaz = y * axis.z();

        return Mat4{ S(c + x * axis.x()),
                     S(axay - s * axis.z()),
                     S(axaz + s * axis.y()),
                     S(0),
                     S(axay + s * axis.z()),
                     S(c + y * axis.y()),
                     S(ayaz - s * axis.x()),
                     S(0),
                     S(axaz - s * axis.y()),
                     S(ayaz + s * axis.x()),
                     S(c + z * axis.z()),
                     S(0),
                     S(0),
                     S(0),
                     S(0),
                     S(1) };
    }


    template <Arithmetic T>
    template <std::floating_point U>
    FALCON_INLINE constexpr PromotedFloatMat4<T, U> Mat4<T>::makeRotation(U angle, const Vec3<T>& axis,
                                                                       const Vec3<T>& center) noexcept
        requires StrictArithmetic<T>
    {
        using S = Magnitude<std::common_type_t<T, U>>;

        S c = static_cast<S>(std::cos(angle));
#ifdef FALCON_LEFT_HANDED
        S s = -static_cast<S>(std::sin(angle));
#else
        S s = static_cast<S>(std::sin(angle));
#endif
        S d = 1 - c;

        S x = static_cast<S>(axis.x()) * d;
        S y = static_cast<S>(axis.y()) * d;
        S z = static_cast<S>(axis.z()) * d;

        S axay = x * axis.y();
        S axaz = x * axis.z();
        S ayaz = y * axis.z();

        return Mat4{ S(c + x * axis.x()),
                     S(axay - s * axis.z()),
                     S(axaz + s * axis.y()),
                     S(center.x()),
                     S(axay + s * axis.z()),
                     S(c + y * axis.y()),
                     S(ayaz - s * axis.x()),
                     S(center.y()),
                     S(axaz - s * axis.y()),
                     S(ayaz + s * axis.x()),
                     S(c + z * axis.z()),
                     S(center.z()),
                     S(0),
                     S(0),
                     S(0),
                     S(1) };
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4<T> Mat4<T>::makeScale(T scale) noexcept
        requires StrictArithmetic<T>
    {
        return Mat4{
            scale, T(0), T(0), T(0), T(0), scale, T(0), T(0), T(0), T(0), scale, T(0), T(0), T(0), T(0), T(1)
        };
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4<T> Mat4<T>::makeScale(T scaleX, T scaleY, T scaleZ) noexcept
        requires StrictArithmetic<T>
    {
        return Mat4{ scaleX, T(0), T(0),   T(0), T(0), scaleY, T(0), T(0),
                     T(0),   T(0), scaleZ, T(0), T(0), T(0),   T(0), T(1) };
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4<T> Mat4<T>::makeScale(T scale, const Vec3<T>& direction) noexcept
        requires SignedStrictArithmetic<T>
    {
        scale -= T(1);

        T x  = scale * direction.x() * direction.x() + 1;
        T y  = scale * direction.y() * direction.y() + 1;
        T z  = scale * direction.z() * direction.z() + 1;
        T xy = scale * direction.x() * direction.y();
        T yz = scale * direction.y() * direction.z();
        T zx = scale * direction.z() * direction.x();

        return Mat4{ x, xy, zx, T(0), xy, y, yz, T(0), zx, yz, z, T(0), T(0), T(0), T(0), T(1) };
    }

    template <Arithmetic T>
    template <reflect::RT On>
    FALCON_INLINE constexpr Mat4<T> Mat4<T>::makeReflection() noexcept
        requires SignedStrictArithmetic<T>
    {
        T reflectX = T(-2) * ((On & 0b00000100) >> 2) + T(1);
        T reflectY = T(-2) * ((On & 0b00000010) >> 1) + T(1);
        T reflectZ = T(-2) * (On & 0b00000001) + T(1);

        return Mat4{ reflectX, T(0), T(0),     T(0), T(0), reflectY, T(0), T(0),
                     T(0),     T(0), reflectZ, T(0), T(0), T(0),     T(0), T(1) };
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4<T> Mat4<T>::makeReflection(const Vec3<T>& normal) noexcept
        requires SignedStrictArithmetic<T>
    {

        T x  = static_cast<T>(1 - 2 * normal.x() * normal.x());
        T y  = static_cast<T>(1 - 2 * normal.y() * normal.y());
        T z  = static_cast<T>(1 - 2 * normal.z() * normal.z());
        T xy = static_cast<T>(-2 * normal.x() * normal.y());
        T yz = static_cast<T>(-2 * normal.y() * normal.z());
        T zx = static_cast<T>(-2 * normal.z() * normal.x());
        return Mat4{ T(x),  T(xy), T(zx), T(0), T(xy), T(y), T(yz), T(0),
                     T(zx), T(yz), T(z),  T(0), T(0),  T(0), T(0),  T(1) };
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4<T> Mat4<T>::makeInvolution(const Vec3<T>& normal) noexcept
        requires SignedStrictArithmetic<T>
    {
        T x  = static_cast<T>(2 * normal.x() * normal.x() - 1);
        T y  = static_cast<T>(2 * normal.y() * normal.y() - 1);
        T z  = static_cast<T>(2 * normal.z() * normal.z() - 1);
        T xy = static_cast<T>(2 * normal.x() * normal.y());
        T yz = static_cast<T>(2 * normal.y() * normal.z());
        T zx = static_cast<T>(2 * normal.z() * normal.x());
        return Mat4{ T(x),  T(xy), T(zx), T(0), T(xy), T(y), T(yz), T(0),
                     T(zx), T(yz), T(z),  T(0), T(0),  T(0), T(0),  T(1) };
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4<T> Mat4<T>::makeShearX(const T shearY, const T shearZ) noexcept
        requires StrictArithmetic<T>
    {
        return Mat4{
            T(1), T(0), T(0), T(0), shearY, T(1), T(0), T(0), shearZ, T(0), T(1), T(0), T(0), T(0), T(0), T(1)
        };
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4<T> Mat4<T>::makeShearY(const T shearX, const T shearZ) noexcept
        requires StrictArithmetic<T>
    {
        return Mat4{
            T(1), shearX, T(0), T(0), T(0), T(1), T(0), T(0), T(0), shearZ, T(1), T(0), T(0), T(0), T(0), T(1)
        };
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4<T> Mat4<T>::makeShearZ(const T shearX, const T shearY) noexcept
        requires StrictArithmetic<T>
    {
        return Mat4{
            T(1), T(0), shearX, T(0), T(0), T(1), shearY, T(0), T(0), T(0), T(1), T(0), T(0), T(0), T(0), T(1)
        };
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4<T> Mat4<T>::makeShearByAngle(T shearAngle, const Vec3<T>& direction,
                                                           const Vec3<T>& normal) noexcept
        requires std::floating_point<T>
    {
        const auto t = std::tan(shearAngle);
        T x          = direction.x() * t;
        T y          = direction.y() * t;
        T z          = direction.z() * t;
        return Mat4{ x * normal.x() + T(1),
                     x * normal.y(),
                     x * normal.z(),
                     T(0),
                     y * normal.x(),
                     y * normal.y() + T(1),
                     y * normal.z(),
                     T(0),
                     z * normal.x(),
                     z * normal.y(),
                     z * normal.z() + T(1),
                     T(0),
                     T(0),
                     T(0),
                     T(0),
                     T(1) };
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4<T> Mat4<T>::makeShear(T shearFactor, const Vec3<T>& direction,
                                                    const Vec3<T>& normal) noexcept
        requires std::floating_point<T>
    {
        T x = direction.x() * shearFactor;
        T y = direction.y() * shearFactor;
        T z = direction.z() * shearFactor;
        return Mat4{ x * normal.x() + T(1),
                     x * normal.y(),
                     x * normal.z(),
                     T(0),
                     y * normal.x(),
                     y * normal.y() + T(1),
                     y * normal.z(),
                     T(0),
                     z * normal.x(),
                     z * normal.y(),
                     z * normal.z() + T(1),
                     T(0),
                     T(0),
                     T(0),
                     T(0),
                     T(1) };
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat4<T> Mat4<T>::makeAffine(const Mat3<T>& linearTransform,
                                                     const Vec3<T>& translation) noexcept
    {
        return Mat4{ linearTransform(0, 0),
                     linearTransform(0, 1),
                     linearTransform(0, 2),
                     translation.x(),
                     linearTransform(1, 0),
                     linearTransform(1, 1),
                     linearTransform(1, 2),
                     translation.y(),
                     linearTransform(2, 0),
                     linearTransform(2, 1),
                     linearTransform(2, 2),
                     translation.z(),
                     T(0),
                     T(0),
                     T(0),
                     T(1) };
    }




} // namespace flcn


#if defined(__clang__)
    #pragma clang diagnostic pop
#endif
