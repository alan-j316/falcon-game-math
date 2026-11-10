#pragma once
/**
 * @file CVec3.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: January 19, 2026
 *
 * @brief @ref CVec3 template implementation.
 * @details This file contains the definitions of the template members declared in CVec3.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <algorithm>

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
    FALCON_INLINE constexpr CVec3<T>::CVec3(T v1, T v2, T v3) noexcept: _data{ v1, v2, v3 }
    {}


    template <Arithmetic T>
    FALCON_INLINE constexpr CVec3<T>::CVec3(CVec2<T> vec, T v) noexcept: _data{ vec[0], vec[1], v }
    {}


    template <Arithmetic T>
    FALCON_INLINE constexpr CVec3<T>::CVec3(T v, CVec2<T> vec) noexcept: _data{ v, vec[0], vec[1] }
    {}


    template <Arithmetic T>
    template <Arithmetic U>
    FALCON_INLINE constexpr CVec3<T>::CVec3(const CVec3<U>& other) noexcept
    {
        _data[0] = static_cast<T>(other[0]);
        _data[1] = static_cast<T>(other[1]);
        _data[2] = static_cast<T>(other[2]);
    }


    /*************************************
     *                                   *
     *            ACCESSORS              *
     *                                   *
     *************************************/

    /**************************************
     *                                    *
     *        SPATIAL COORDINATES         *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec3<T>::x() const noexcept
    { return _data[0]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T& CVec3<T>::x() noexcept
    { return _data[0]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec3<T>::y() const noexcept
    { return _data[1]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T& CVec3<T>::y() noexcept
    { return _data[1]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec3<T>::z() const noexcept
    { return _data[2]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T& CVec3<T>::z() noexcept
    { return _data[2]; }


    /**************************************
     *                                    *
     *           STP COORDINATES          *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec3<T>::s() const noexcept
    { return _data[0]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T& CVec3<T>::s() noexcept
    { return _data[0]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec3<T>::t() const noexcept
    { return _data[1]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T& CVec3<T>::t() noexcept
    { return _data[1]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec3<T>::p() const noexcept
    { return _data[2]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T& CVec3<T>::p() noexcept
    { return _data[2]; }


    /**************************************
     *                                    *
     *         COLOR COORDINATES          *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec3<T>::r() const noexcept
    { return _data[0]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T& CVec3<T>::r() noexcept
    { return _data[0]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec3<T>::g() const noexcept
    { return _data[1]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T& CVec3<T>::g() noexcept
    { return _data[1]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec3<T>::b() const noexcept
    { return _data[2]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T& CVec3<T>::b() noexcept
    { return _data[2]; }


    /**************************************
     *                                    *
     *              INDEXING              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T& CVec3<T>::operator[](const std::size_t idx) noexcept
    {
        FALCON_ASSERT_MSG(idx < DIMENSION, flcn::messages::assertion::VEC_OUT_OF_BOUNDS_ACCESS);
        return _data[idx];
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr const T& CVec3<T>::operator[](const std::size_t idx) const noexcept
    {
        FALCON_ASSERT_MSG(idx < DIMENSION, flcn::messages::assertion::VEC_OUT_OF_BOUNDS_ACCESS);
        return _data[idx];
    }



    /**************************************
     *                                    *
     *             SWIZZLING              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    template <std::size_t... Indices>
    FALCON_INLINE constexpr auto CVec3<T>::swizzle() const noexcept
    {
        constexpr std::size_t swizzleDimension = sizeof...(Indices);

        static_assert(((Indices < DIMENSION) && ...), "Index out of bounds!");
        static_assert(swizzleDimension > 0 && swizzleDimension <= DIMENSION &&
                      "Swizzle must return a scalar, or a 2D, or 3D vector.");
        if constexpr (swizzleDimension == 3)
        {
            return CVec3(_data[Indices]...);
        }
        else if constexpr (swizzleDimension == 2)
        {
            return CVec2<T>(_data[Indices]...);
        }
        else
        {
            return T(_data[Indices]...);
        }
    }


    template <Arithmetic T>
    template <std::size_t... Indices>
    FALCON_INLINE constexpr auto CVec3<T>::swizzle(const CVec3& vec) noexcept
    { return vec.swizzle<Indices...>(); }



    /***************************************
     *                                     *
     *         EQUALITY (ABSOLUTE)         *
     *                                     *
     ***************************************/

    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool CVec3<T>::allEq(const CVec3<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        {
            return _data[0] == rhs[0] && _data[1] == rhs[1] && _data[2] == rhs[2];
        }
        else
        {
// MSVC's constexpr evaluator incorrectly yields true for NaN relational comparisons.
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
            /** @note Direct equality check is required to handle @ref INFINITY cases, as Inf - Inf results in NAN_F. */
            return (_data[0] == rhs[0] || flcn::abs(_data[0] - rhs[0]) <= epsilon) &&
                (_data[1] == rhs[1] || flcn::abs(_data[1] - rhs[1]) <= epsilon) &&
                (_data[2] == rhs[2] || flcn::abs(_data[2] - rhs[2]) <= epsilon);
        }
    }

    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool CVec3<T>::allEq(const CVec3& lhs, const CVec3<U>& rhs, const double epsilon) noexcept
    { return lhs.allEq(rhs, epsilon); }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool CVec3<T>::anyNeq(const CVec3<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        {
            return _data[0] != rhs[0] || _data[1] != rhs[1] || _data[2] != rhs[2];
        }
        else
        {
            /** @note Identity check and inverted logic handle NAN_F and INFINITY per IEEE 754. */
            return (_data[0] != rhs[0] && !(flcn::abs(_data[0] - rhs[0]) <= epsilon)) ||
                (_data[1] != rhs[1] && !(flcn::abs(_data[1] - rhs[1]) <= epsilon)) ||
                (_data[2] != rhs[2] && !(flcn::abs(_data[2] - rhs[2]) <= epsilon));
        }
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool CVec3<T>::anyNeq(const CVec3& lhs, const CVec3<U>& rhs, const double epsilon) noexcept
    { return lhs.anyNeq(rhs, epsilon); }


    /**************************************
     *                                    *
     *         EQUALITY OPERATORS         *
     *                                    *
     **************************************/

    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool CVec3<T>::operator==(const CVec3<U>& rhs) const noexcept
    { return this->allEq(rhs); }

    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool CVec3<T>::operator!=(const CVec3<U>& rhs) const noexcept
    { return this->anyNeq(rhs); }


    /***************************************
     *                                     *
     *           EQUALITY (MASK)           *
     *                                     *
     ***************************************/

    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec3<bool> CVec3<T>::eq(const CVec3<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        {
            return CVec3<bool>(_data[0] == rhs[0], _data[1] == rhs[1], _data[2] == rhs[2]);
        }
        else
        {
            /** @note Direct equality check is required to handle @ref INFINITY cases, as Inf - Inf results in NAN_F. */
            return CVec3<bool>(_data[0] == rhs[0] || flcn::abs(_data[0] - rhs[0]) <= epsilon,
                              _data[1] == rhs[1] || flcn::abs(_data[1] - rhs[1]) <= epsilon,
                              _data[2] == rhs[2] || flcn::abs(_data[2] - rhs[2]) <= epsilon);
        }
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec3<bool> CVec3<T>::eq(const CVec3& lhs, const CVec3<U>& rhs, const double epsilon) noexcept
    { return lhs.eq(rhs, epsilon); }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec3<bool> CVec3<T>::neq(const CVec3<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        {
            return CVec3<bool>(_data[0] != rhs[0], _data[1] != rhs[1], _data[2] != rhs[2]);
        }
        else
        {
            /** @note Identity check and inverted logic handle NAN_F and INFINITY per IEEE 754. */
            return CVec3<bool>(_data[0] != rhs[0] && !(flcn::abs(_data[0] - rhs[0]) <= epsilon),
                              _data[1] != rhs[1] && !(flcn::abs(_data[1] - rhs[1]) <= epsilon),
                              _data[2] != rhs[2] && !(flcn::abs(_data[2] - rhs[2]) <= epsilon));
        }
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec3<bool> CVec3<T>::neq(const CVec3& lhs, const CVec3<U>& rhs, const double epsilon) noexcept
    { return lhs.neq(rhs, epsilon); }


    /***************************************
     *                                     *
     *            COMPARISONS              *
     *                                     *
     ***************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec3<bool> CVec3<T>::gt(const CVec3<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    { return CVec3<bool>(_data[0] > rhs[0], _data[1] > rhs[1], _data[2] > rhs[2]); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec3<bool> CVec3<T>::gt(const CVec3& lhs, const CVec3<U>& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.gt(rhs); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec3<bool> CVec3<T>::gte(const CVec3<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    { return CVec3<bool>(_data[0] >= rhs[0], _data[1] >= rhs[1], _data[2] >= rhs[2]); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec3<bool> CVec3<T>::gte(const CVec3& lhs, const CVec3<U>& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.gte(rhs); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec3<bool> CVec3<T>::lt(const CVec3<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    { return CVec3<bool>(_data[0] < rhs[0], _data[1] < rhs[1], _data[2] < rhs[2]); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec3<bool> CVec3<T>::lt(const CVec3& lhs, const CVec3<U>& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.lt(rhs); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec3<bool> CVec3<T>::lte(const CVec3<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = Magnitude<PromotedValue_t<T, U>>;
        return CVec3<bool>(static_cast<R>(_data[0]) <= static_cast<R>(rhs[0]),
                          static_cast<R>(_data[1]) <= static_cast<R>(rhs[1]),
                          static_cast<R>(_data[2]) <= static_cast<R>(rhs[2]));
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec3<bool> CVec3<T>::lte(const CVec3& lhs, const CVec3<U>& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.lte(rhs); }


    /***************************************
     *                                     *
     *        COMPARISON OPERATORS         *
     *                                     *
     ***************************************/

#ifdef ENABLE_FALCON_SHADER_OPERATORS

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec3<bool> CVec3<T>::operator>(const CVec3<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    { return this->gt(rhs); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec3<bool> CVec3<T>::operator>=(const CVec3<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    { return this->gte(rhs); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec3<bool> CVec3<T>::operator<(const CVec3<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    { return this->lt(rhs); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec3<bool> CVec3<T>::operator<=(const CVec3<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    { return this->lte(rhs); }

#endif


    /***************************************
     *                                     *
     *      BOOLEAN BITWISE OPERATORS      *
     *                                     *
     ***************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr CVec3<T> CVec3<T>::operator&(const CVec3& rhs) const noexcept
        requires std::is_same_v<T, bool>
    { return CVec3(_data[0] & rhs[0], _data[1] & rhs[1], _data[2] & rhs[2]); }


    template <Arithmetic T>
    FALCON_INLINE constexpr CVec3<T>& CVec3<T>::operator&=(const CVec3& rhs) noexcept
        requires std::is_same_v<T, bool>
    {
        *this = *this & rhs;
        return *this;
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr CVec3<T> CVec3<T>::operator|(const CVec3& rhs) const noexcept
        requires std::is_same_v<T, bool>
    { return CVec3(_data[0] | rhs[0], _data[1] | rhs[1], _data[2] | rhs[2]); }


    template <Arithmetic T>
    FALCON_INLINE constexpr CVec3<T>& CVec3<T>::operator|=(const CVec3& rhs) noexcept
        requires std::is_same_v<T, bool>
    {
        *this = *this & rhs;
        return *this;
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr CVec3<T> CVec3<T>::operator!() const noexcept
        requires std::is_same_v<T, bool>
    { return CVec3(!_data[0], !_data[1], !_data[2]); }



    /*************************************
     *                                   *
     *      ARITHMETIC OPERATORS         *
     *                                   *
     *************************************/

    /*************************************
     *                                   *
     *            ADDITION               *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec3<T, U> CVec3<T>::operator+(const CVec3<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
        return CVec3<R>(_data[0] + rhs[0], _data[1] + rhs[1], _data[2] + rhs[2]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec3<T>& CVec3<T>::operator+=(const CVec3<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] += static_cast<T>(rhs[0]);
        _data[1] += static_cast<T>(rhs[1]);
        _data[2] += static_cast<T>(rhs[2]);
        return *this;
    }


    /*************************************
     *                                   *
     *           SUBTRACTION             *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec3<T, U> CVec3<T>::operator-(const CVec3<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
        return CVec3<R>(_data[0] - rhs[0], _data[1] - rhs[1], _data[2] - rhs[2]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec3<T>& CVec3<T>::operator-=(const CVec3<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] -= static_cast<T>(rhs[0]);
        _data[1] -= static_cast<T>(rhs[1]);
        _data[2] -= static_cast<T>(rhs[2]);
        return *this;
    }


    /**************************************
     *                                    *
     *         INVERT OPERATION           *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr CVec3<T> CVec3<T>::operator-() const noexcept
        requires SignedStrictArithmetic<T>
    { return CVec3(-_data[0], -_data[1], -_data[2]); }


    /*************************************
     *                                   *
     *           MULTIPLICATION          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedCVec3<T, S> CVec3<T>::operator*(const S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;
        return CVec3<R>(_data[0] * scalar, _data[1] * scalar, _data[2] * scalar);
    }


    template <StrictArithmetic T, StrictArithmetic S>
    FALCON_INLINE constexpr auto operator*(const S scalar, const CVec3<T>& vector) noexcept -> CVec3<PromotedValue_t<T, S>>
        requires StrictArithmetic<T>
    { return vector * scalar; }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr CVec3<T>& CVec3<T>::operator*=(const S scalar) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] = static_cast<T>(scalar * _data[0]);
        _data[1] = static_cast<T>(scalar * _data[1]);
        _data[2] = static_cast<T>(scalar * _data[2]);
        return *this;
    }


    /*************************************
     *                                   *
     *             DIVISION              *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedCVec3<T, S> CVec3<T>::operator/(const S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;
        if constexpr (std::is_floating_point_v<R>)
        {
            FALCON_ASSERT_MSG(flcn::abs(scalar) >= flcn::Config::EPSILON<R>, flcn::messages::assertion::VEC_DIV_BY_ZERO);
            R factor = R(1) / static_cast<R>(scalar);
            return CVec3<R>(_data[0] * factor, _data[1] * factor, _data[2] * factor);
        }
        else
        {
            FALCON_ASSERT_MSG(scalar != 0, flcn::messages::assertion::VEC_DIV_BY_ZERO);
            R tScalar = static_cast<R>(scalar);
            return CVec3<R>(_data[0] / tScalar, _data[1] / tScalar, _data[2] / tScalar);
        }
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr CVec3<T>& CVec3<T>::operator/=(const S scalar) noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;

        FALCON_ASSERT_MSG(flcn::abs(scalar) > flcn::Config::EPSILON<S>, flcn::messages::assertion::VEC_DIV_BY_ZERO);
        if constexpr (std::is_floating_point_v<R>)
        {
            R factor = R(1) / static_cast<R>(scalar);

            _data[0] = static_cast<T>(factor * _data[0]);
            _data[1] = static_cast<T>(factor * _data[1]);
            _data[2] = static_cast<T>(factor * _data[2]);
        }
        else
        {
            _data[0] = static_cast<T>(_data[0] / static_cast<R>(scalar));
            _data[1] = static_cast<T>(_data[1] / static_cast<R>(scalar));
            _data[2] = static_cast<T>(_data[2] / static_cast<R>(scalar));
        }

        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedCVec3<T, S> CVec3<T>::safeDiv(const S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
        {
            if (hasNaN() | flcn::isnan(scalar) | (flcn::abs(scalar) <= std::numeric_limits<S>::epsilon()))
            {
                return CVec3<R>::zero();
            }
        }
        if constexpr (std::is_integral_v<R>)
        {
            if (scalar == 0)
            {
                return CVec3<R>::zero();
            }
        }

        return *this / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedCVec3<T, S> CVec3<T>::safeDiv(const CVec3& vec, const S scalar) noexcept
        requires StrictArithmetic<T>
    { return vec.safeDiv(scalar); }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedCVec3<T, S> CVec3<T>::tryDiv(S scalar, OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
        {
            if (hasNaN() | flcn::isnan(scalar))
            {
                status = OperationStatus::NANOPERAND;
                return CVec3<R>::zero();
            }
            if (flcn::abs(scalar) <= std::numeric_limits<S>::epsilon())
            {
                status = OperationStatus::DIVISIONBYZERO;
                return CVec3<R>::zero();
            }
        }

        if constexpr (std::is_integral_v<R>)
        {
            if (scalar == 0)
            {
                status = OperationStatus::DIVISIONBYZERO;
                return CVec3<R>::zero();
            }
        }


        status = OperationStatus::SUCCESS;
        return *this / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedCVec3<T, S> CVec3<T>::tryDiv(const CVec3& vec, S scalar, OperationStatus& status) noexcept
        requires StrictArithmetic<T>
    { return vec.tryDiv(scalar, status); }


    /*************************************
     *                                   *
     *        VECTOR DOT PRODUCT         *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr auto CVec3<T>::dot(const CVec3<U>& rhs) const noexcept -> PromotedValue_t<T, U>
        requires StrictArithmetic<T>
    {
#if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__FMA4__) || defined(__AVX2__)
        using R = PromotedValue_t<T, U>;
        if constexpr (std::is_floating_point_v<R>)
        {
            if (!std::is_constant_evaluated())
            {
                return std::fma(static_cast<R>(_data[0]), static_cast<R>(rhs[0]),
                                std::fma(static_cast<R>(_data[1]), static_cast<R>(rhs[1]),
                                         std::fma(static_cast<R>(_data[2]), static_cast<R>(rhs[2]), T(0))));
            }
        }
        return _data[0] * rhs[0] + _data[1] * rhs[1] + _data[2] * rhs[2];
#else
        return _data[0] * rhs[0] + _data[1] * rhs[1] + _data[2] * rhs[2];
#endif
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr auto CVec3<T>::dot(const CVec3& lhs, const CVec3<U>& rhs) noexcept -> PromotedValue_t<T, U>
        requires StrictArithmetic<T>
    { return lhs.dot(rhs); }



    /*************************************
     *                                   *
     *        VECTOR INNER PRODUCT       *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat3<T, U> CVec3<T>::tensorProduct(const CVec3<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        return Mat3{
            R(this->x() * rhs.x()), R(this->x() * rhs.y()), R(this->x() * rhs.z()),
            R(this->y() * rhs.x()), R(this->y() * rhs.y()), R(this->y() * rhs.z()),
            R(this->z() * rhs.x()), R(this->z() * rhs.y()), R(this->z() * rhs.z())
        };
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat3<T, U> CVec3<T>::tensorProduct(const CVec3& lhs, const CVec3<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        return lhs.tensorProduct(rhs);
    }



    /*************************************
     *                                   *
     *       VECTOR CROSS PRODUCT        *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <SignedStrictArithmetic U>
    FALCON_INLINE constexpr PromotedCVec3<T, U> CVec3<T>::cross(const CVec3<U>& rhs) const noexcept
        requires SignedStrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
        return CVec3<R>(_data[1] * rhs[2] - _data[2] * rhs[1], _data[2] * rhs[0] - _data[0] * rhs[2],
                       _data[0] * rhs[1] - _data[1] * rhs[0]);
    }


    template <Arithmetic T>
    template <SignedStrictArithmetic U>
    FALCON_INLINE constexpr PromotedCVec3<T, U> CVec3<T>::cross(const CVec3& lhs, const CVec3<U>& rhs) noexcept
        requires SignedStrictArithmetic<T>
    { return lhs.cross(rhs); }


    /*************************************
     *                                   *
     *         VECTOR MAGNITUDE          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr Magnitude<T> CVec3<T>::mag() const noexcept
        requires StrictArithmetic<T>
    {
        using M = Magnitude<T>;

        M tX = static_cast<M>(_data[0]);
        M tY = static_cast<M>(_data[1]);
        M tZ = static_cast<M>(_data[2]);

        return std::sqrt(tX * tX + tY * tY + tZ * tZ);
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Magnitude<T> CVec3<T>::mag(const CVec3& vec) noexcept
        requires StrictArithmetic<T>
    { return vec.mag(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec3<T>::magSq() const noexcept
        requires StrictArithmetic<T>
    { return this->dot(*this); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec3<T>::magSq(const CVec3& vector) noexcept
        requires StrictArithmetic<T>
    { return vector.magSq(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec3<T>::manhattanNorm() const noexcept
        requires StrictArithmetic<T>
    { return flcn::abs(_data[0]) + flcn::abs(_data[1]) + flcn::abs(_data[2]); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec3<T>::manhattanNorm(const CVec3& vec) noexcept
        requires StrictArithmetic<T>
    { return vec.manhattanNorm(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec3<T>::chebyshevNorm() const noexcept
        requires StrictArithmetic<T>
    { return std::max({ flcn::abs(_data[0]), flcn::abs(_data[1]), flcn::abs(_data[2]) }); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec3<T>::chebyshevNorm(const CVec3& vec) noexcept
        requires StrictArithmetic<T>
    { return vec.chebyshevNorm(); }



    /**************************************
     *                                    *
     *         VECTOR DISTANCE            *
     *                                    *
     **************************************/

    /**************************************
     *                                    *
     *             EUCLIDEAN              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr Magnitude<PromotedValue_t<T, U>> CVec3<T>::dist(const CVec3<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R       = Magnitude<PromotedValue_t<T, U>>;
        const auto dx = utils::diffAbs(_data[0], rhs[0]);
        const auto dy = utils::diffAbs(_data[1], rhs[1]);
        const auto dz = utils::diffAbs(_data[2], rhs[2]);
        return static_cast<R>(std::sqrt(dx * dx + dy * dy + dz * dz));
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr Magnitude<PromotedValue_t<T, U>> CVec3<T>::dist(const CVec3<U>& lhs, const CVec3<U>& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.dist(rhs); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedValue_t<T, U> CVec3<T>::distSq(const CVec3<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        const auto dx = utils::diffAbs(_data[0], rhs[0]);
        const auto dy = utils::diffAbs(_data[1], rhs[1]);
        const auto dz = utils::diffAbs(_data[2], rhs[2]);

        return dx * dx + dy * dy + dz * dz;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedValue_t<T, U> CVec3<T>::distSq(const CVec3<U>& lhs, const CVec3<U>& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.distSq(rhs); }



    /**************************************
     *                                    *
     *             MANHATTAN              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedValue_t<T, U> CVec3<T>::manhattanDist(const CVec3<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    { return utils::diffAbs(_data[0], rhs[0]) + utils::diffAbs(_data[1], rhs[1]) + utils::diffAbs(_data[2], rhs[2]); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedValue_t<T, U> CVec3<T>::manhattanDist(const CVec3<U>& lhs, const CVec3<U>& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.manhattanDist(rhs); }



    /**************************************
     *                                    *
     *             CHEBYSHEV              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedValue_t<T, U> CVec3<T>::chebyshevDist(const CVec3<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        return std::max(utils::diffAbs(_data[0], rhs[0]),
                        std::max(utils::diffAbs(_data[1], rhs[1]), utils::diffAbs(_data[2], rhs[2])));
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedValue_t<T, U> CVec3<T>::chebyshevDist(const CVec3<U>& lhs, const CVec3<U>& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.chebyshevDist(rhs); }



    /*************************************
     *                                   *
     *       VECTOR NORMALIZATION        *
     *                                   *
     *************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr CVec3<Magnitude<T>> CVec3<T>::normalize() const noexcept
        requires StrictArithmetic<T>
    {
        const auto magnitude = mag();
        FALCON_ASSERT_MSG(magnitude >= flcn::Config::EPSILON<decltype(magnitude)>,
                       flcn::messages::assertion::VEC_NORMALIZE_DIV_BY_ZERO);
        return *this / magnitude;
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr CVec3<Magnitude<T>> CVec3<T>::normalize(const CVec3& vec) noexcept
        requires StrictArithmetic<T>
    { return vec.normalize(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr CVec3<Magnitude<T>> CVec3<T>::safeNormalize() const noexcept
        requires StrictArithmetic<T>
    {
        using R     = Magnitude<T>;
        R magnitude = mag();
        if (flcn::isnan(magnitude))
        {
            return CVec3<R>::zero();
        }
        if (magnitude <= Config::EPSILON_SQUARE<R>)
        {
            return CVec3<R>::zero();
        }

        return *this / magnitude;
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr CVec3<Magnitude<T>> CVec3<T>::safeNormalize(const CVec3& vec) noexcept
        requires StrictArithmetic<T>
    { return vec.safeNormalize(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr CVec3<Magnitude<T>> CVec3<T>::tryNormalize(OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        using R     = Magnitude<T>;
        R magnitude = mag();
        if (flcn::isnan(magnitude))
        {
            status = OperationStatus::NANOPERAND;
            return CVec3<R>::zero();
        }
        if (magnitude <= Config::EPSILON_SQUARE<R>)
        {
            status = OperationStatus::DIVISIONBYZERO;
            return CVec3<R>::zero();
        }

        status = OperationStatus::SUCCESS;
        return *this / magnitude;
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr CVec3<Magnitude<T>> CVec3<T>::tryNormalize(const CVec3& vec, OperationStatus& status) noexcept
        requires StrictArithmetic<T>
    { return vec.tryNormalize(status); }


    /*************************************
     *                                   *
     *        VECTOR PROJECTION          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedFloatCVec3<T, U> CVec3<T>::project(const CVec3<U>& onto) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;

        /** @note Static cast ensures integral type dots don't lose much precision */
        const auto b2 = static_cast<Magnitude<R>>(onto.dot(onto));

        FALCON_ASSERT_MSG(b2 >= flcn::Config::EPSILON_SQUARE<Magnitude<R>>,
                       flcn::messages::assertion::VEC_PROJECT_DIV_BY_ZERO);

        return this->dot(onto) / b2 * onto; // a.dot(b) / b.dot(b) * b
    }

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec3<T, U> CVec3<T>::projectNorm(const CVec3<U>& onto) const noexcept
        requires StrictArithmetic<T>
    {
        return this->dot(onto) * onto; // a.dot(b) * b
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedFloatCVec3<T, U> CVec3<T>::project(const CVec3& vec, const CVec3<U>& onto) noexcept
        requires StrictArithmetic<T>
    { return vec.project(onto); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec3<T, U> CVec3<T>::projectNorm(const CVec3& vec, const CVec3<U>& onto) noexcept
        requires StrictArithmetic<T>
    { return vec.projectNorm(onto); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedFloatCVec3<T, U> CVec3<T>::safeProject(const CVec3<U>& onto) const noexcept
        requires StrictArithmetic<T>
    {
        using R       = PromotedValue_t<T, U>;
        using MagType = Magnitude<R>;

        /** @note Static cast ensures integral type dots don't lose much precision */
        const auto ontoSquared = static_cast<MagType>(onto.dot(onto));

        if (hasNaN() | flcn::isnan(ontoSquared))
        {
            return CVec3<MagType>::zero();
        }

        if (ontoSquared <= Config::EPSILON_SQUARE<MagType>)
        {
            return CVec3<MagType>::zero();
        }

        return this->dot(onto) / ontoSquared * onto; // a.dot(b) / b.dot(b) * b
    }

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec3<T, U> CVec3<T>::safeProjectNorm(const CVec3<U>& onto) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;

        if (hasNaN() || onto.hasNaN())
        {
            return CVec3<R>::zero();
        }
        return this->dot(onto) * onto;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedFloatCVec3<T, U> CVec3<T>::safeProject(const CVec3& vec, const CVec3<U>& onto) noexcept
        requires StrictArithmetic<T>
    { return vec.safeProject(onto); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec3<T, U> CVec3<T>::safeProjectNorm(const CVec3& vec, const CVec3<U>& onto) noexcept
        requires StrictArithmetic<T>
    { return vec.safeProjectNorm(onto); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedFloatCVec3<T, U> CVec3<T>::tryProject(const CVec3<U>& onto,
                                                                     OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        using R       = PromotedValue_t<T, U>;
        using MagType = Magnitude<R>;


        /** @note Static cast ensures integral type dots don't lose much precision */
        const auto ontoSquared = static_cast<MagType>(onto.dot(onto));

        if (hasNaN() | flcn::isnan(ontoSquared))
        {
            status = OperationStatus::NANOPERAND;
            return CVec3<MagType>::zero();
        }

        if (ontoSquared <= Config::EPSILON_SQUARE<MagType>)
        {
            status = OperationStatus::DIVISIONBYZERO;
            return CVec3<MagType>::zero();
        }

        status = OperationStatus::SUCCESS;
        return this->dot(onto) / ontoSquared * onto; // a.dot(b) / b.dot(b) * b
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec3<T, U> CVec3<T>::tryProjectNorm(const CVec3<U>& onto,
                                                                    OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        using R       = PromotedValue_t<T, U>;
        using MagType = Magnitude<R>;

        if (hasNaN() | onto.hasNaN())
        {
            status = OperationStatus::NANOPERAND;
            return CVec3<MagType>::zero();
        }
        status = OperationStatus::SUCCESS;
        return this->dot(onto) * onto;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedFloatCVec3<T, U> CVec3<T>::tryProject(const CVec3& vec, const CVec3<U>& onto,
                                                                     OperationStatus& status) noexcept
        requires StrictArithmetic<T>
    { return vec.tryProject(onto, status); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec3<T, U> CVec3<T>::tryProjectNorm(const CVec3& vec, const CVec3<U>& onto,
                                                                    OperationStatus& status) noexcept
        requires StrictArithmetic<T>
    { return vec.tryProjectNorm(onto, status); }


    /*************************************
     *                                   *
     *         VECTOR REJECTION          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedFloatCVec3<T, U> CVec3<T>::reject(const CVec3<U>& from) const noexcept
        requires StrictArithmetic<T>
    { return static_cast<PromotedFloatCVec3<T, U>>(*this) - this->project(from); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec3<T, U> CVec3<T>::rejectNorm(const CVec3<U>& from) const noexcept
        requires StrictArithmetic<T>
    { return *this - this->projectNorm(from); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedFloatCVec3<T, U> CVec3<T>::reject(const CVec3& vector, const CVec3<U>& from) noexcept
        requires StrictArithmetic<T>
    { return vector.reject(from); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec3<T, U> CVec3<T>::rejectNorm(const CVec3& vector, const CVec3<U>& from) noexcept
        requires StrictArithmetic<T>
    { return vector.rejectNorm(from); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedFloatCVec3<T, U> CVec3<T>::safeReject(const CVec3<U>& from) const noexcept
        requires StrictArithmetic<T>
    {
        if (hasNaN() || from.hasNaN())
        {
            return CVec3<Magnitude<PromotedValue_t<T, U>>>::zero();
        }

        return static_cast<PromotedFloatCVec3<T, U>>(*this) - safeProject(from);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec3<T, U> CVec3<T>::safeRejectNorm(const CVec3<U>& from) const noexcept
        requires StrictArithmetic<T>
    {
        if (hasNaN() || from.hasNaN())
        {
            return CVec3<PromotedValue_t<T, U>>::zero();
        }

        return *this - safeProjectNorm(from);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedFloatCVec3<T, U> CVec3<T>::safeReject(const CVec3& vec, const CVec3<U>& from) noexcept
        requires StrictArithmetic<T>
    { return vec.safeReject(from); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec3<T, U> CVec3<T>::safeRejectNorm(const CVec3& vec, const CVec3<U>& from) noexcept
        requires StrictArithmetic<T>
    { return vec.safeRejectNorm(from); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedFloatCVec3<T, U> CVec3<T>::tryReject(const CVec3<U>& from,
                                                                    OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        if (hasNaN() || from.hasNaN())
        {
            status = OperationStatus::NANOPERAND;
            return CVec3<Magnitude<PromotedValue_t<T, U>>>::zero();
        }

        return static_cast<PromotedFloatCVec3<T, U>>(*this) - this->tryProject(from, status);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec3<T, U> CVec3<T>::tryRejectNorm(const CVec3<U>& from,
                                                                   OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        if (hasNaN() || from.hasNaN())
        {
            status = OperationStatus::NANOPERAND;
            return CVec3<PromotedValue_t<T, U>>::zero();
        }

        return *this - this->tryProjectNorm(from, status);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedFloatCVec3<T, U> CVec3<T>::tryReject(const CVec3& vec, const CVec3<U>& from,
                                                                    OperationStatus& status) noexcept
        requires StrictArithmetic<T>
    { return vec.tryReject(from, status); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec3<T, U> CVec3<T>::tryRejectNorm(const CVec3& vec, const CVec3<U>& from,
                                                                   OperationStatus& status) noexcept
        requires StrictArithmetic<T>
    { return vec.tryRejectNorm(from, status); }


    /**************************************
     *                                    *
     *             UTILITIES              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr bool CVec3<T>::hasInf() const noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            return flcn::isinf(_data[0]) | flcn::isinf(_data[1]) | flcn::isinf(_data[2]);
        }
        else
        {
            return false;
        }
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool CVec3<T>::hasInf(const CVec3& vec) noexcept
    { return vec.hasInf(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool CVec3<T>::hasNaN() const noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            return flcn::isnan(_data[0]) | flcn::isnan(_data[1]) | flcn::isnan(_data[2]);
        }
        else
        {
            return false;
        }
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool CVec3<T>::hasNaN(const CVec3& vec) noexcept
    { return vec.hasNaN(); }
} // namespace flcn


#if defined(__clang__)
    #pragma clang diagnostic pop
#endif
