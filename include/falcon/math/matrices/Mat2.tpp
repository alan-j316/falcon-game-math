#pragma once
/**
 * @file Mat2.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: January 30, 2026
 *
 * @brief @ref Mat2 template implementation.
 * @details This file contains the definitions of the template members declared in Mat2.h
 *
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "falcon/math/common/Wrappers.h"

#include <type_traits>
#include <valarray>


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
    FALCON_INLINE constexpr Mat2<T>::Mat2(const T m00, const T m01, const T m10, const T m11) noexcept
        : _data{ CVec2<T>(m00, m10), CVec2<T>(m01, m11) }
    {}


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat2<T>::Mat2(const CVec2<T>& col0, const CVec2<T>& col1) noexcept: _data{ col0, col1 }
    {}


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat2<T>::Mat2(const T d0, const T d1) noexcept: _data{ CVec2<T>(d0, 0), CVec2<T>(0, d1) }
    {}


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr Mat2<T>::Mat2(const Mat2<U>& other) noexcept
    {
        (*this)(0, 0) = static_cast<T>(other(0, 0));
        (*this)(0, 1) = static_cast<T>(other(0, 1));
        (*this)(1, 0) = static_cast<T>(other(1, 0));
        (*this)(1, 1) = static_cast<T>(other(1, 1));
    }



    /*************************************
     *                                   *
     *            ACCESSORS              *
     *                                   *
     *************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr CVec2<T>& Mat2<T>::operator[](const std::size_t col) noexcept
    {
        FALCON_ASSERT_MSG(col < COLUMNS, flcn::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return _data[col];
    }

    template <Arithmetic T>
    FALCON_INLINE constexpr const CVec2<T>& Mat2<T>::operator[](const std::size_t col) const noexcept
    {
        FALCON_ASSERT_MSG(col < COLUMNS, flcn::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return _data[col];
    }

    template <Arithmetic T>
    FALCON_INLINE constexpr T& Mat2<T>::operator()(const std::size_t row, const std::size_t col) noexcept
    {
        FALCON_ASSERT_MSG(col < COLUMNS && row < ROWS, flcn::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return _data[col][row];
    }

    template <Arithmetic T>
    FALCON_INLINE constexpr const T& Mat2<T>::operator()(const std::size_t row, const std::size_t col) const noexcept
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
    FALCON_INLINE constexpr bool Mat2<T>::allEq(const Mat2<U>& rhs, const double epsilon) const noexcept
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
        return _data[0].allEq(rhs[0], epsilon) && _data[1].allEq(rhs[1], epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Mat2<T>::allEq(const Mat2& lhs, const Mat2<U>& rhs, const double epsilon) noexcept
    { return lhs.allEq(rhs, epsilon); }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Mat2<T>::anyNeq(const Mat2<U>& rhs, const double epsilon) const noexcept
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
        return _data[0].anyNeq(rhs[0], epsilon) || _data[1].anyNeq(rhs[1], epsilon);
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Mat2<T>::anyNeq(const Mat2& lhs, const Mat2<U>& rhs, const double epsilon) noexcept
    { return lhs.anyNeq(rhs, epsilon); }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Mat2<T>::operator==(const Mat2<U>& rhs) const noexcept
    { return allEq(rhs); }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Mat2<T>::operator!=(const Mat2<U>& rhs) const noexcept
    { return anyNeq(rhs); }



    /**************************************
     *                                    *
     *        ARITHMETIC OPERATORS        *
     *                                    *
     **************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat2<T, U> Mat2<T>::operator+(const Mat2<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
        return Mat2<R>(_data[0] + rhs[0], _data[1] + rhs[1]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    Mat2<T>& Mat2<T>::operator+=(const Mat2<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] += rhs[0];
        _data[1] += rhs[1];
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat2<T, U> Mat2<T>::operator-(const Mat2<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
        return Mat2<R>(_data[0] - rhs[0], _data[1] - rhs[1]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr Mat2<T>& Mat2<T>::operator-=(const Mat2<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] -= rhs[0];
        _data[1] -= rhs[1];
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedMat2<T, S> Mat2<T>::operator*(const S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;
        return Mat2<R>(scalar * _data[0], scalar * _data[1]);
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr Mat2<T>& Mat2<T>::operator*=(const S scalar) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] *= scalar;
        _data[1] *= scalar;
        return *this;
    }

    template <StrictArithmetic T, StrictArithmetic S>
    FALCON_INLINE constexpr PromotedMat2<T, S> operator*(const S scalar, const Mat2<T>& matrix) noexcept
    { return matrix * scalar; }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec2<T, U> Mat2<T>::operator*(const CVec2<U>& vec) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
#if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__AVX2__)
        // #error "FMA ACTIVE!" // For checking if FMA execution path is active.
        if constexpr (std::is_floating_point_v<R>)
        {
            if (!std::is_constant_evaluated())
            {
                return CVec2<R>(std::fma(static_cast<R>(_data[0][0]), static_cast<R>(vec[0]),
                                        static_cast<R>(_data[1][0]) * static_cast<R>(vec[1])),
                               std::fma(static_cast<R>(_data[0][1]), static_cast<R>(vec[0]),
                                        static_cast<R>(_data[1][1]) * static_cast<R>(vec[1])));
            }
        }
#endif

        R x =
            static_cast<R>(_data[0][0]) * static_cast<R>(vec[0]) + static_cast<R>(_data[1][0]) * static_cast<R>(vec[1]);
        R y =
            static_cast<R>(_data[0][1]) * static_cast<R>(vec[0]) + static_cast<R>(_data[1][1]) * static_cast<R>(vec[1]);

        return CVec2<R>(x, y);
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec2<T, U> operator*(const CVec2<T>& vec, const Mat2<U>& matrix) noexcept
    {
        using R = PromotedValue_t<T, U>;
#if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__AVX2__)
        // #error "FMA ACTIVE!" // For checking if FMA execution path is active.
        if constexpr (std::is_floating_point_v<R>)
        {
            if (!std::is_constant_evaluated())
            {
                return CVec2<R>(std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 0)),
                                        static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 0))),
                               std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 1)),
                                        static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 1))));
            }
        }

#endif
        R x = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 0)) +
            static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 0));
        R y = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 1)) +
            static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 1));

        return CVec2<R>(x, y);
    }


    template <StrictArithmetic T, StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec2<T>& operator*=(CVec2<T>& vec, const Mat2<U>& matrix) noexcept
    {
        using R = PromotedValue_t<T, U>;
#if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__AVX2__)
        // #error "FMA ACTIVE!" // For checking if FMA execution path is active.
        if constexpr (std::is_floating_point_v<R>)
        {
            if (!std::is_constant_evaluated())
            {
                R x = std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 0)),
                               static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 0)));
                R y = std::fma(static_cast<R>(vec[0]), static_cast<R>(matrix(0, 1)),
                               static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 1)));

                vec.x() = static_cast<T>(x);
                vec.y() = static_cast<T>(y);

                return vec;
            }
        }
#endif
        R x = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 0)) +
            static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 0));
        R y = static_cast<R>(vec[0]) * static_cast<R>(matrix(0, 1)) +
            static_cast<R>(vec[1]) * static_cast<R>(matrix(1, 1));

        vec.x() = static_cast<T>(x);
        vec.y() = static_cast<T>(y);

        return vec;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat2<T, U> Mat2<T>::operator*(const Mat2<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
        return Mat2<R>(*this * rhs[0], *this * rhs[1]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr Mat2<T>& Mat2<T>::operator*=(const Mat2<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        const auto mat = *this * rhs;
        _data[0]       = static_cast<CVec2<T>>(mat[0]);
        _data[1]       = static_cast<CVec2<T>>(mat[1]);
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedMat2<T, S> Mat2<T>::operator/(const S& scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;
        if constexpr (std::is_floating_point_v<R>)
        {
            FALCON_ASSERT_MSG(flcn::abs(R(scalar)) > Config::EPSILON<R>, messages::assertion::MAT_DIV_BY_ZERO);
            R factor = R(1) / static_cast<R>(scalar);
            return Mat2<R>(_data[0] * factor, _data[1] * factor);
        }
        else
        {
            FALCON_ASSERT_MSG(scalar != S(0), messages::assertion::MAT_DIV_BY_ZERO);
            R tScalar = static_cast<R>(scalar);
            return Mat2<R>(_data[0] / tScalar, _data[1] / tScalar);
        }
    }



    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr Mat2<T>& Mat2<T>::operator/=(const S& scalar) noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;

        FALCON_ASSERT_MSG(flcn::abs(scalar) > Config::EPSILON<S>, messages::assertion::MAT_DIV_BY_ZERO);

        if constexpr (std::is_floating_point_v<R>)
        {
            R factor = R(1) / static_cast<R>(scalar);

            _data[0][0] = static_cast<R>(_data[0][0]) * factor;
            _data[1][0] = static_cast<R>(_data[1][0]) * factor;

            _data[0][1] = static_cast<R>(_data[0][1]) * factor;
            _data[1][1] = static_cast<R>(_data[1][1]) * factor;
        }
        else
        {
            _data[0][0] = static_cast<T>(_data[0][0] / static_cast<R>(scalar));
            _data[1][0] = static_cast<T>(_data[1][0] / static_cast<R>(scalar));

            _data[0][1] = static_cast<T>(_data[0][1] / static_cast<R>(scalar));
            _data[1][1] = static_cast<T>(_data[1][1] / static_cast<R>(scalar));
        }
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedMat2<T, S> Mat2<T>::safeDiv(const S scalar, Mat2 fallback) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
        {
            if (flcn::abs(scalar) <= std::numeric_limits<R>::epsilon() || flcn::isnan(scalar) || hasNaN())
            {
                return static_cast<Mat2<R>>(fallback);
            }
        }
        if constexpr (std::is_integral_v<R>)
        {
            if (scalar == 0)
            {
                return static_cast<Mat2<R>>(fallback);
            }
        }

        return *this / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedMat2<T, S> Mat2<T>::safeDiv(const Mat2& mat, const S scalar, Mat2 fallback) noexcept
        requires StrictArithmetic<T>
    { return mat.safeDiv(scalar, fallback); }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedMat2<T, S> Mat2<T>::tryDiv(const S scalar, OperationStatus& status,
                                                            Mat2 fallback) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
        { // TODO: Check || vs | with benchmarks
            if (static_cast<int>(hasNaN()) | static_cast<int>(flcn::isnan(scalar)))
            {
                status = OperationStatus::NANOPERAND;
                return static_cast<Mat2<R>>(fallback);
            }
            if (flcn::abs(scalar) <= std::numeric_limits<R>::epsilon())
            {
                status = OperationStatus::DIVISIONBYZERO;
                return static_cast<Mat2<R>>(fallback);
            }
        }

        if constexpr (std::is_integral_v<R>)
        {
            if (scalar == 0)
            {
                status = OperationStatus::DIVISIONBYZERO;
                return static_cast<Mat2<R>>(fallback);
            }
        }


        status = OperationStatus::SUCCESS;
        return *this / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedMat2<T, S> Mat2<T>::tryDiv(const Mat2& mat, const S scalar, OperationStatus& status,
                                                            Mat2 fallback) noexcept
        requires StrictArithmetic<T>
    { return mat.tryDiv(scalar, status, fallback); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat2<T> Mat2<T>::operator-() const noexcept
        requires SignedStrictArithmetic<T>
    { return Mat2{ -_data[0], -_data[1] }; }




    /**************************************
     *                                    *
     *           MATRIX ALGEBRA           *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T Mat2<T>::determinant() const noexcept
        requires SignedStrictArithmetic<T>
    { return _data[0][0] * _data[1][1] - _data[0][1] * _data[1][0]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Mat2<T>::determinant(const Mat2& matrix) noexcept
        requires SignedStrictArithmetic<T>
    { return matrix.determinant(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat2<T> Mat2<T>::transpose() const noexcept
    {
        // NOTE: _data is a column major vector so _data[0][1] gives element at first row and zeroth column.
        return Mat2(_data[0][0], _data[0][1], _data[1][0], _data[1][1]);
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat2<T> Mat2<T>::transpose(const Mat2& matrix) noexcept
    { return matrix.transpose(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat2<Magnitude<T>> Mat2<T>::inverse() const noexcept
        requires SignedStrictArithmetic<T>
    {
        using R = Magnitude<T>;

        T det = determinant();

        if constexpr (std::is_floating_point_v<T>)
        {
            FALCON_ASSERT_MSG(flcn::abs(det) > Config::EPSILON<R>, messages::assertion::MAT_DET_DIV_BY_ZERO);
        }
        else
        {
            FALCON_ASSERT_MSG(flcn::abs(det) != T(0), messages::assertion::MAT_DET_DIV_BY_ZERO);
        }

        R factor = R(1) / det;

        return Mat2<R>(static_cast<R>(_data[1][1]) * factor, static_cast<R>(-_data[1][0]) * factor,
                       static_cast<R>(-_data[0][1]) * factor, static_cast<R>(_data[0][0]) * factor);
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat2<Magnitude<T>> Mat2<T>::inverse(const Mat2& matrix) noexcept
        requires SignedStrictArithmetic<T>
    { return matrix.inverse(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat2<Magnitude<T>> Mat2<T>::safeInverse(Mat2 fallback) const noexcept
        requires SignedStrictArithmetic<T>
    {
        using R = Magnitude<T>;

        T det = determinant();
        // TODO: Update to use directly compute inverse to reduce operation
        // TODO: Do similar in code cleaning in tryInverse
        if constexpr (std::is_floating_point_v<T>)
        {
            if (hasNaN() || flcn::abs(det) <= std::numeric_limits<T>::epsilon())
            {
                return static_cast<Mat2<R>>(fallback);
            }
        }
        if constexpr (std::is_integral_v<T>)
        {
            if (det == 0)
            {
                return static_cast<Mat2<R>>(fallback);
            }
        }

        return inverse();
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat2<Magnitude<T>> Mat2<T>::safeInverseOf(const Mat2& matrix, Mat2 fallback) noexcept
        requires SignedStrictArithmetic<T>
    { return matrix.safeInverse(fallback); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat2<Magnitude<T>> Mat2<T>::tryInverse(OperationStatus& status, Mat2 fallback) const noexcept
        requires SignedStrictArithmetic<T>
    {
        using R = Magnitude<T>;

        T det = determinant();

        if constexpr (std::is_floating_point_v<T>)
        {
            if (hasNaN())
            {
                status = OperationStatus::NANOPERAND;
                return static_cast<Mat2<R>>(fallback);
            }
            if (flcn::abs(det) <= std::numeric_limits<T>::epsilon())
            {
                status = OperationStatus::DIVISIONBYZERO;
                return static_cast<Mat2<R>>(fallback);
            }
        }

        if constexpr (std::is_integral_v<T>)
        {
            if (det == 0)
            {
                status = OperationStatus::DIVISIONBYZERO;
                return static_cast<Mat2<R>>(fallback);
            }
        }


        status = OperationStatus::SUCCESS;
        return inverse();
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat2<Magnitude<T>> Mat2<T>::tryInverseOf(const Mat2& matrix, OperationStatus& status,
                                                                  Mat2 fallback) noexcept
        requires SignedStrictArithmetic<T>
    { return matrix.tryInverse(status, fallback); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Mat2<T>::trace() const noexcept
        requires StrictArithmetic<T>
    { return _data[0][0] + _data[1][1]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Mat2<T>::trace(const Mat2& matrix) noexcept
        requires StrictArithmetic<T>
    { return matrix.trace(); }



    /**************************************
     *                                    *
     *             UTILITIES              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr bool Mat2<T>::hasInf() const noexcept
    { return _data[0].hasInf() || _data[1].hasInf(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool Mat2<T>::hasInf(const Mat2& matrix) noexcept
    { return matrix.hasInf(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool Mat2<T>::hasNaN() const noexcept
    { return _data[0].hasNaN() || _data[1].hasNaN(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool Mat2<T>::hasNaN(const Mat2& matrix) noexcept
    { return matrix.hasNaN(); }




    /**************************************
     *                                    *
     *       TRANSFORMATION FACTORIES     *
     *                                    *
     **************************************/

    template <Arithmetic T>
    template <std::floating_point U>
    FALCON_INLINE constexpr Mat2<T> Mat2<T>::makeRotation(const U angle) noexcept
        requires SignedStrictArithmetic<T>
    {
        using R  = PromotedValue_t<T, U>;
        R cosine = std::cos(angle);
        R sine   = std::sin(angle);
#ifdef FALCON_LEFT_HANDED
        return Mat2(cosine, sine, -sine, cosine);
#else
        return Mat2(cosine, -sine, sine, cosine);
#endif
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat2<T> Mat2<T>::makeScale(const T scale) noexcept
        requires StrictArithmetic<T>
    { return Mat2(scale, T(0), T(0), scale); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat2<T> Mat2<T>::makeScale(const T scaleX, const T scaleY) noexcept
        requires StrictArithmetic<T>
    { return Mat2(scaleX, T(0), T(0), scaleY); }


    template <Arithmetic T>
    template <reflect::RT On>
    FALCON_INLINE constexpr Mat2<T> Mat2<T>::makeReflection() noexcept
        requires SignedStrictArithmetic<T>
    {
        T reflectX = T(-2) * ((On & 0b00000100) >> 2) + T(1);
        T reflectY = T(-2) * ((On & 0b00000010) >> 1) + T(1);

        return Mat2{ reflectX, T(0), T(0), reflectY };
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat2<T> Mat2<T>::makeShearX(T shear) noexcept
        requires StrictArithmetic<T>
    { return Mat2{ T(1), shear, T(0), T(1) }; }


    template <Arithmetic T>
    FALCON_INLINE constexpr Mat2<T> Mat2<T>::makeShearY(T shear) noexcept
        requires StrictArithmetic<T>
    { return Mat2{ T(1), T(0), shear, T(1) }; }

} // namespace flcn


#if defined(__clang__)
    #pragma clang diagnostic pop
#endif
