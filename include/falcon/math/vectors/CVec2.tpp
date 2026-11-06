#pragma once
/**
 * @file CVec2.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: January 24, 2026
 *
 * @brief @ref CVec2 template implementation.
 * @details This file contains the definitions of the template members declared in CVec2.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "falcon/math/common/Messages.h"
#include "falcon/math/common/Types.h"
#include "falcon/math/common/Utils.h"
#include "falcon/math/common/Wrappers.h"

#include <algorithm>
#include <cmath>
#include <type_traits>


#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wbitwise-instead-of-logical"
#endif


namespace flcn
{
    /*************************************
     *            INITIALIZERS           *
     *************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr CVec2<T>::CVec2(T val) noexcept: _data{ val, val }
    {}


    template <Arithmetic T>
    FALCON_INLINE constexpr CVec2<T>::CVec2(T v1, T v2) noexcept: _data{ v1, v2 }
    {}


    template <Arithmetic T>
    template <Arithmetic U>
    FALCON_INLINE constexpr CVec2<T>::CVec2(const CVec2<U>& other) noexcept
    {
        _data[0] = static_cast<T>(other.x());
        _data[1] = static_cast<T>(other.y());
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> CVec2<T>::toVec2() const noexcept
    {
        return Vec2<T>(_data[0], _data[1]);
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec2<T> CVec2<T>::toVec2(const CVec2& vec) noexcept
    {
        return vec.toVec2();
    }



    /*************************************
     *            ACCESSORS              *
     *************************************/

    /**************************************
     *        SPATIAL COORDINATES         *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec2<T>::x() const noexcept
    { return _data[0]; }


    template <Arithmetic T>
    constexpr T& CVec2<T>::x() noexcept
    { return _data[0]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec2<T>::y() const noexcept
    { return _data[1]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T& CVec2<T>::y() noexcept
    { return _data[1]; }


    /**************************************
     *           STP COORDINATES          *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec2<T>::s() const noexcept
    { return _data[0]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T& CVec2<T>::s() noexcept
    { return _data[0]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec2<T>::t() const noexcept
    { return _data[1]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T& CVec2<T>::t() noexcept
    { return _data[1]; }


    /**************************************
     *         COLOR COORDINATES          *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec2<T>::r() const noexcept
    { return _data[0]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T& CVec2<T>::r() noexcept
    { return _data[0]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec2<T>::g() const noexcept
    { return _data[1]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T& CVec2<T>::g() noexcept
    { return _data[1]; }


    /**************************************
     *              INDEXING              *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T& CVec2<T>::operator[](const std::size_t idx) noexcept
    {
        FALCON_ASSERT_MSG(idx < DIMENSION, flcn::messages::assertion::VEC_OUT_OF_BOUNDS_ACCESS);
        return _data[idx];
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr const T& CVec2<T>::operator[](const std::size_t idx) const noexcept
    {
        FALCON_ASSERT_MSG(idx < DIMENSION, flcn::messages::assertion::VEC_OUT_OF_BOUNDS_ACCESS);
        return _data[idx];
    }


    /**************************************
     *             SWIZZLING              *
     **************************************/

    template <Arithmetic T>
    template <std::size_t... Indices>
    FALCON_INLINE constexpr auto CVec2<T>::swizzle() const noexcept
    {
        constexpr std::size_t swizzleDimension = sizeof...(Indices);

        static_assert(((Indices < DIMENSION) && ...), "Index out of bounds!");
        static_assert(swizzleDimension > 0 && swizzleDimension <= DIMENSION &&
                      "Swizzle must return a scalar, or a 2D vector.");
        if constexpr (swizzleDimension == 2)
        {
            return CVec2(_data[Indices]...);
        }
        else
        {
            return T(_data[Indices]...);
        }
    }


    template <Arithmetic T>
    template <std::size_t... Indices>
    FALCON_INLINE constexpr auto CVec2<T>::swizzle(const CVec2& vec) noexcept
    { return vec.swizzle<Indices...>(); }


    /***************************************
     *          STORAGE ACCESSORS          *
     ***************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr const T* CVec2<T>::ptr() const noexcept
    { return _data.data();}


    template <Arithmetic T>
    FALCON_INLINE constexpr T* CVec2<T>::ptr() noexcept
    { return _data.data(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr const T* CVec2<T>::ptr(const CVec2& vec) noexcept
    { return vec.ptr(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T* CVec2<T>::ptr(CVec2& vec) noexcept
    { return vec.ptr(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T* CVec2<T>::operator*() noexcept
    { return ptr(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr const T* CVec2<T>::operator*() const noexcept
    { return ptr(); }


    /***************************************
     *         EQUALITY (ABSOLUTE)         *
     ***************************************/

    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool CVec2<T>::allEq(const CVec2<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        {
            return _data[0] == rhs[0] && _data[1] == rhs[1];
        }
        else
        /** @note Direct equality check is required to handle @ref INFINITY cases, as Inf - Inf results in NAN_F. */
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
            return (_data[0] == rhs[0] || flcn::abs(_data[0] - rhs[0]) <= epsilon) &&
                (_data[1] == rhs[1] || flcn::abs(_data[1] - rhs[1]) <= epsilon);
        }
    }

    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool CVec2<T>::allEq(const CVec2& lhs, const CVec2<U>& rhs, const double epsilon) noexcept
    { return lhs.allEq(rhs, epsilon); }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool CVec2<T>::anyNeq(const CVec2<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        {
            return _data[0] != rhs[0] || _data[1] != rhs[1];
        }
        else
        {
            /** @note Identity check and inverted logic handle NAN_F and INFINITY per IEEE 754. */
            return (_data[0] != rhs[0] && !(flcn::abs(_data[0] - rhs[0]) <= epsilon)) ||
                (_data[1] != rhs[1] && !(flcn::abs(_data[1] - rhs[1]) <= epsilon));
        }
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool CVec2<T>::anyNeq(const CVec2& lhs, const CVec2<U>& rhs, const double epsilon) noexcept
    { return lhs.anyNeq(rhs, epsilon); }


    /**************************************
     *                                    *
     *         EQUALITY OPERATORS         *
     *                                    *
     **************************************/

    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool CVec2<T>::operator==(const CVec2<U>& rhs) const noexcept
    { return this->allEq(rhs); }

    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool CVec2<T>::operator!=(const CVec2<U>& rhs) const noexcept
    { return this->anyNeq(rhs); }


    /***************************************
     *                                     *
     *           EQUALITY (MASK)           *
     *                                     *
     ***************************************/

    // TODO: Add MSVC NaN check tests + add new implementation as required.
    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec2<bool> CVec2<T>::eq(const CVec2<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        {
            return CVec2<bool>(_data[0] == rhs[0], _data[1] == rhs[1]);
        }
        else
        {
            /** @note Direct equality check is required to handle @ref INFINITY cases, as Inf - Inf results in NAN_F. */
            return CVec2<bool>(_data[0] == rhs[0] || flcn::abs(_data[0] - rhs[0]) <= epsilon,
                               _data[1] == rhs[1] || flcn::abs(_data[1] - rhs[1]) <= epsilon);
        }
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec2<bool> CVec2<T>::eq(const CVec2& lhs, const CVec2<U>& rhs,
                                                     const double epsilon) noexcept
    { return lhs.eq(rhs, epsilon); }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec2<bool> CVec2<T>::neq(const CVec2<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        {
            return CVec2<bool>(_data[0] != rhs[0], _data[1] != rhs[1]);
        }
        else
        {
            /** @note Identity check and inverted logic handle NAN_F and INFINITY per IEEE 754. */
            return CVec2<bool>(_data[0] != rhs[0] && !(flcn::abs(_data[0] - rhs[0]) <= epsilon),
                               _data[1] != rhs[1] && !(flcn::abs(_data[1] - rhs[1]) <= epsilon));
        }
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec2<bool> CVec2<T>::neq(const CVec2& lhs, const CVec2<U>& rhs,
                                                      const double epsilon) noexcept
    { return lhs.neq(rhs, epsilon); }


    /***************************************
     *                                     *
     *            COMPARISONS              *
     *                                     *
     ***************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec2<bool> CVec2<T>::gt(const CVec2<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    { return CVec2<bool>(_data[0] > rhs[0], _data[1] > rhs[1]); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec2<bool> CVec2<T>::gt(const CVec2& lhs, const CVec2<U>& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.gt(rhs); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec2<bool> CVec2<T>::gte(const CVec2<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    { return CVec2<bool>(_data[0] >= rhs[0], _data[1] >= rhs[1]); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec2<bool> CVec2<T>::gte(const CVec2& lhs, const CVec2<U>& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.gte(rhs); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec2<bool> CVec2<T>::lt(const CVec2<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    { return CVec2<bool>(_data[0] < rhs[0], _data[1] < rhs[1]); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec2<bool> CVec2<T>::lt(const CVec2& lhs, const CVec2<U>& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.lt(rhs); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec2<bool> CVec2<T>::lte(const CVec2<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = Magnitude<PromotedValue_t<T, U>>;
        return CVec2<bool>(static_cast<R>(_data[0]) <= static_cast<R>(rhs[0]),
                           static_cast<R>(_data[1]) <= static_cast<R>(rhs[1]));
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec2<bool> CVec2<T>::lte(const CVec2& lhs, const CVec2<U>& rhs) noexcept
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
    FALCON_INLINE constexpr CVec2<bool> CVec2<T>::operator>(const CVec2<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    { return this->gt(rhs); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec2<bool> CVec2<T>::operator>=(const CVec2<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    { return this->gte(rhs); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec2<bool> CVec2<T>::operator<(const CVec2<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    { return this->lt(rhs); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec2<bool> CVec2<T>::operator<=(const CVec2<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    { return this->lte(rhs); }

#endif


    /***************************************
     *                                     *
     *      BOOLEAN BITWISE OPERATORS      *
     *                                     *
     ***************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr CVec2<T> CVec2<T>::operator&(const CVec2& rhs) const noexcept
        requires std::is_same_v<T, bool>
    { return CVec2(_data[0] & rhs[0], _data[1] & rhs[1]); }


    template <Arithmetic T>
    FALCON_INLINE constexpr CVec2<T>& CVec2<T>::operator&=(const CVec2& rhs) noexcept
        requires std::is_same_v<T, bool>
    {
        *this = *this & rhs;
        return *this;
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr CVec2<T> CVec2<T>::operator|(const CVec2& rhs) const noexcept
        requires std::is_same_v<T, bool>
    { return CVec2(_data[0] | rhs[0], _data[1] | rhs[1]); }


    template <Arithmetic T>
    FALCON_INLINE constexpr CVec2<T>& CVec2<T>::operator|=(const CVec2& rhs) noexcept
        requires std::is_same_v<T, bool>
    {
        *this = *this & rhs;
        return *this;
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr CVec2<T> CVec2<T>::operator!() const noexcept
        requires std::is_same_v<T, bool>
    { return CVec2(!_data[0], !_data[1]); }


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
    FALCON_INLINE constexpr PromotedCVec2<T, U> CVec2<T>::operator+(const CVec2<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
        return CVec2<R>(_data[0] + rhs[0], _data[1] + rhs[1]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec2<T>& CVec2<T>::operator+=(const CVec2<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] += static_cast<T>(rhs[0]);
        _data[1] += static_cast<T>(rhs[1]);
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
    FALCON_INLINE constexpr PromotedCVec2<T, U> CVec2<T>::operator-(const CVec2<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
        return CVec2<R>(_data[0] - rhs[0], _data[1] - rhs[1]);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr CVec2<T>& CVec2<T>::operator-=(const CVec2<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] -= static_cast<T>(rhs[0]);
        _data[1] -= static_cast<T>(rhs[1]);
        return *this;
    }


    /**************************************
     *                                    *
     *         INVERT OPERATION           *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr CVec2<T> CVec2<T>::operator-() const noexcept
        requires SignedStrictArithmetic<T>
    { return CVec2(-_data[0], -_data[1]); }


    /*************************************
     *                                   *
     *           MULTIPLICATION          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedCVec2<T, S> CVec2<T>::operator*(const S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;
        return CVec2<R>(static_cast<R>(_data[0]) * static_cast<R>(scalar),
                        static_cast<R>(_data[1]) * static_cast<R>(scalar));
    }


    template <StrictArithmetic T, StrictArithmetic S>
    FALCON_INLINE constexpr PromotedCVec2<T, S> operator*(const S scalar, const CVec2<T>& vector) noexcept
        requires StrictArithmetic<T>
    { return vector * scalar; }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr CVec2<T>& CVec2<T>::operator*=(const S scalar) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] = static_cast<T>(scalar * _data[0]);
        _data[1] = static_cast<T>(scalar * _data[1]);
        return *this;
    }


    /*************************************
     *                                   *
     *             DIVISION              *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedCVec2<T, S> CVec2<T>::operator/(const S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;
        if constexpr (std::is_floating_point_v<R>)
        {
            FALCON_ASSERT_MSG(flcn::abs(scalar) >= flcn::Config::EPSILON<R>, flcn::messages::assertion::VEC_DIV_BY_ZERO);

            R factor = R(1) / static_cast<R>(scalar);
            return CVec2<R>(_data[0] * factor, _data[1] * factor);
        }
        else
        {
            FALCON_ASSERT_MSG(scalar != 0, flcn::messages::assertion::VEC_DIV_BY_ZERO);
            R tScalar = static_cast<R>(scalar);
            return CVec2<R>(_data[0] / tScalar, _data[1] / tScalar);
        }
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr CVec2<T>& CVec2<T>::operator/=(const S scalar) noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;

        FALCON_ASSERT_MSG(flcn::abs(scalar) > flcn::Config::EPSILON<S>, flcn::messages::assertion::VEC_DIV_BY_ZERO);
        if constexpr (std::is_floating_point_v<R>)
        {
            R factor = R(1) / static_cast<R>(scalar);

            _data[0] = static_cast<T>(factor * _data[0]);
            _data[1] = static_cast<T>(factor * _data[1]);
        }
        else
        {
            _data[0] = static_cast<T>(_data[0] / static_cast<R>(scalar));
            _data[1] = static_cast<T>(_data[1] / static_cast<R>(scalar));
        }

        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedCVec2<T, S> CVec2<T>::safeDiv(const S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
        {
            if (hasNaN() | flcn::isnan(scalar) | (flcn::abs(scalar) <= std::numeric_limits<S>::epsilon()))
            {
                return CVec2<R>::zero();
            }
        }
        if constexpr (std::is_integral_v<R>)
        {
            if (scalar == 0)
            {
                return CVec2<R>::zero();
            }
        }

        return *this / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedCVec2<T, S> CVec2<T>::safeDiv(const CVec2& vec, const S scalar) noexcept
        requires StrictArithmetic<T>
    { return vec.safeDiv(scalar); }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedCVec2<T, S> CVec2<T>::tryDiv(S scalar, OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
        {
            if (hasNaN() | flcn::isnan(scalar))
            {
                status = OperationStatus::NANOPERAND;
                return CVec2<R>::zero();
            }
            if (flcn::abs(scalar) <= std::numeric_limits<S>::epsilon())
            {
                status = OperationStatus::DIVISIONBYZERO;
                return CVec2<R>::zero();
            }
        }

        if constexpr (std::is_integral_v<R>)
        {
            if (scalar == 0)
            {
                status = OperationStatus::DIVISIONBYZERO;
                return CVec2<R>::zero();
            }
        }


        status = OperationStatus::SUCCESS;
        return *this / scalar;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
    FALCON_INLINE constexpr PromotedCVec2<T, S> CVec2<T>::tryDiv(const CVec2& vec, S scalar,
                                                                 OperationStatus& status) noexcept
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
    FALCON_INLINE constexpr PromotedValue_t<T, U> CVec2<T>::dot(const CVec2<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
#if defined(FP_FAST_FMA) || defined(FP_FAST_FMAF) || defined(__FMA__) || defined(__FMA4__) || defined(__AVX2__)
        using R = PromotedValue_t<T, U>;
        if constexpr (std::is_floating_point_v<R>)
        {
            return std::fma(static_cast<R>(_data[0]), static_cast<R>(rhs[0]),
                            std::fma(static_cast<R>(_data[1]), static_cast<R>(rhs[1]), T(0)));
        }
        else
        {
            return _data[0] * rhs[0] + _data[1] * rhs[1];
        }
#else
        return _data[0] * rhs[0] + _data[1] * rhs[1];
#endif
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedValue_t<T, U> CVec2<T>::dot(const CVec2& lhs, const CVec2<U>& rhs) noexcept
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
    FALCON_INLINE constexpr PromotedMat2<T, U> CVec2<T>::tensorProduct(const CVec2<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        return Mat2{ R(this->x() * rhs.x()), R(this->x() * rhs.y()), R(this->y() * rhs.x()), R(this->y() * rhs.y()) };
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedMat2<T, U> CVec2<T>::tensorProduct(const CVec2& lhs, const CVec2<U>& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.tensorProduct(rhs); }


    /*************************************
     *                                   *
     *       VECTOR CROSS PRODUCT        *
     *                                   *
     *************************************/

    template <Arithmetic T>
    template <SignedStrictArithmetic U>
    FALCON_INLINE constexpr PromotedValue_t<T, U> CVec2<T>::cross(const CVec2<U>& rhs) const noexcept
        requires SignedStrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;
        return R(_data[0] * rhs[1] - _data[1] * rhs[0]);
    }


    template <Arithmetic T>
    template <SignedStrictArithmetic U>
    FALCON_INLINE constexpr PromotedValue_t<T, U> CVec2<T>::cross(const CVec2& lhs, const CVec2<U>& rhs) noexcept
        requires SignedStrictArithmetic<T>
    { return lhs.cross(rhs); }


    /*************************************
     *                                   *
     *         VECTOR MAGNITUDE          *
     *                                   *
     *************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr Magnitude<T> CVec2<T>::mag() const noexcept
        requires StrictArithmetic<T>
    {
        using M = Magnitude<T>;

        M tX = static_cast<M>(_data[0]);
        M tY = static_cast<M>(_data[1]);

        return sqrt(tX * tX + tY * tY);
    }

    template <Arithmetic T>
    FALCON_INLINE constexpr Magnitude<T> CVec2<T>::mag(const CVec2& vec) noexcept
        requires StrictArithmetic<T>
    { return vec.mag(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec2<T>::magSq() const noexcept
        requires StrictArithmetic<T>
    {
        // return _data[0] * _data[0] + _data[1] * _data[1];
        return this->dot(*this);
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec2<T>::magSq(const CVec2& vec) noexcept
        requires StrictArithmetic<T>
    { return vec.magSq(); }


    /**************************************
     *                                    *
     *           MANHATTAN NORM           *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec2<T>::manhattanNorm() const noexcept
        requires StrictArithmetic<T>
    { return flcn::abs(_data[0]) + flcn::abs(_data[1]); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec2<T>::manhattanNorm(const CVec2& vec) noexcept
        requires StrictArithmetic<T>
    { return vec.manhattanNorm(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec2<T>::chebyshevNorm() const noexcept
        requires StrictArithmetic<T>
    { return std::max(flcn::abs(_data[0]), flcn::abs(_data[1])); }


    template <Arithmetic T>
    FALCON_INLINE constexpr T CVec2<T>::chebyshevNorm(const CVec2& vec) noexcept
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
    FALCON_INLINE constexpr Magnitude<PromotedValue_t<T, U>> CVec2<T>::dist(const CVec2<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R       = Magnitude<PromotedValue_t<T, U>>;
        const auto dx = utils::diffAbs(_data[0], rhs[0]);
        const auto dy = utils::diffAbs(_data[1], rhs[1]);
        return static_cast<R>(std::sqrt(dx * dx + dy * dy));
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr Magnitude<PromotedValue_t<T, U>> CVec2<T>::dist(const CVec2<U>& lhs,
                                                                            const CVec2<U>& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.dist(rhs); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedValue_t<T, U> CVec2<T>::distSq(const CVec2<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        const auto dx = utils::diffAbs(_data[0], rhs[0]);
        const auto dy = utils::diffAbs(_data[1], rhs[1]);

        return dx * dx + dy * dy;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedValue_t<T, U> CVec2<T>::distSq(const CVec2& lhs, const CVec2<U>& rhs) noexcept
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
    FALCON_INLINE constexpr PromotedValue_t<T, U> CVec2<T>::manhattanDist(const CVec2<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    { return utils::diffAbs(_data[0], rhs[0]) + utils::diffAbs(_data[1], rhs[1]); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedValue_t<T, U> CVec2<T>::manhattanDist(const CVec2& lhs,
                                                                          const CVec2<U>& rhs) noexcept
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
    FALCON_INLINE constexpr PromotedValue_t<T, U> CVec2<T>::chebyshevDist(const CVec2<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    { return std::max(utils::diffAbs(_data[0], rhs[0]), utils::diffAbs(_data[1], rhs[1])); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedValue_t<T, U> CVec2<T>::chebyshevDist(const CVec2& lhs,
                                                                          const CVec2<U>& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.chebyshevDist(rhs); }



    /*************************************
     *                                   *
     *       VECTOR NORMALIZATION        *
     *                                   *
     *************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr CVec2<Magnitude<T>> CVec2<T>::normalize() const noexcept
        requires StrictArithmetic<T>
    {
        const auto magnitude = mag();
        FALCON_ASSERT_MSG(magnitude >= flcn::Config::EPSILON<decltype(magnitude)>,
                          flcn::messages::assertion::VEC_NORMALIZE_DIV_BY_ZERO);
        return *this / magnitude;
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr CVec2<Magnitude<T>> CVec2<T>::normalize(const CVec2& vec) noexcept
        requires StrictArithmetic<T>
    { return vec.normalize(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr CVec2<Magnitude<T>> CVec2<T>::safeNormalize() const noexcept
        requires StrictArithmetic<T>
    {
        using R     = Magnitude<T>;
        R magnitude = mag();
        if (flcn::isnan(magnitude))
        {
            return CVec2<R>::zero();
        }
        if (magnitude <= Config::EPSILON_SQUARE<R>)
        {
            return CVec2<R>::zero();
        }

        return *this / magnitude;
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr CVec2<Magnitude<T>> CVec2<T>::safeNormalize(const CVec2& vec) noexcept
        requires StrictArithmetic<T>
    { return vec.safeNormalize(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr CVec2<Magnitude<T>> CVec2<T>::tryNormalize(OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        using R     = Magnitude<T>;
        R magnitude = mag();
        if (flcn::isnan(magnitude))
        {
            status = OperationStatus::NANOPERAND;
            return CVec2<R>::zero();
        }
        if (magnitude <= Config::EPSILON_SQUARE<R>)
        {
            status = OperationStatus::DIVISIONBYZERO;
            return CVec2<R>::zero();
        }

        status = OperationStatus::SUCCESS;
        return *this / magnitude;
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr CVec2<Magnitude<T>> CVec2<T>::tryNormalize(const CVec2& vec,
                                                                       OperationStatus& status) noexcept
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
    FALCON_INLINE constexpr PromotedFloatCVec2<T, U> CVec2<T>::project(const CVec2<U>& onto) const noexcept
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
    FALCON_INLINE constexpr PromotedCVec2<T, U> CVec2<T>::projectNorm(const CVec2<U>& onto) const noexcept
        requires StrictArithmetic<T>
    {
        return this->dot(onto) * onto; // a.dot(b) * b
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedFloatCVec2<T, U> CVec2<T>::project(const CVec2& vec, const CVec2<U>& onto) noexcept
        requires StrictArithmetic<T>
    { return vec.project(onto); }

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec2<T, U> CVec2<T>::projectNorm(const CVec2& vec, const CVec2<U>& onto) noexcept
        requires StrictArithmetic<T>
    { return vec.projectNorm(onto); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedFloatCVec2<T, U> CVec2<T>::safeProject(const CVec2<U>& onto) const noexcept
        requires StrictArithmetic<T>
    {
        using R       = PromotedValue_t<T, U>;
        using MagType = Magnitude<R>;

        /** @note Static cast ensures integral type dots don't lose much precision */
        const auto ontoSquared = static_cast<MagType>(onto.dot(onto));

        if (hasNaN() | flcn::isnan(ontoSquared))
        {
            return CVec2<MagType>::zero();
        }

        if (ontoSquared <= Config::EPSILON_SQUARE<MagType>)
        {
            return CVec2<MagType>::zero();
        }

        return this->dot(onto) / ontoSquared * onto; // a.dot(b) / b.dot(b) * b
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec2<T, U> CVec2<T>::safeProjectNorm(const CVec2<U>& onto) const noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, U>;

        if (hasNaN() || onto.hasNaN())
        {
            return CVec2<R>::zero();
        }

        return this->dot(onto) * onto;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedFloatCVec2<T, U> CVec2<T>::safeProject(const CVec2& vec,
                                                                           const CVec2<U>& onto) noexcept
        requires StrictArithmetic<T>
    { return vec.safeProject(onto); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec2<T, U> CVec2<T>::safeProjectNorm(const CVec2& vec,
                                                                          const CVec2<U>& onto) noexcept
        requires StrictArithmetic<T>
    { return vec.safeProjectNorm(onto); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedFloatCVec2<T, U> CVec2<T>::tryProject(const CVec2<U>& onto,
                                                                          OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        using R       = PromotedValue_t<T, U>;
        using MagType = Magnitude<R>;

        /** @note Static cast ensures integral type dots don't lose too much precision. */
        const auto ontoSquared = static_cast<MagType>(onto.dot(onto));

        if (hasNaN() | flcn::isnan(ontoSquared))
        {
            status = OperationStatus::NANOPERAND;
            return CVec2<MagType>::zero();
        }

        if (ontoSquared <= Config::EPSILON_SQUARE<MagType>)
        {
            status = OperationStatus::DIVISIONBYZERO;
            return CVec2<MagType>::zero();
        }

        status = OperationStatus::SUCCESS;
        return this->dot(onto) / ontoSquared * onto; // a.dot(b) / b.dot(b) * b
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec2<T, U> CVec2<T>::tryProjectNorm(const CVec2<U>& onto,
                                                                         OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        using R       = PromotedValue_t<T, U>;
        using MagType = Magnitude<R>;

        if (hasNaN() || onto.hasNaN())
        {
            status = OperationStatus::NANOPERAND;
            return CVec2<MagType>::zero();
        }

        status = OperationStatus::SUCCESS;
        return this->dot(onto) * onto;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedFloatCVec2<T, U> CVec2<T>::tryProject(const CVec2& vec, const CVec2<U>& onto,
                                                                          OperationStatus& status) noexcept
        requires StrictArithmetic<T>
    { return vec.tryProject(onto, status); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec2<T, U> CVec2<T>::tryProjectNorm(const CVec2& vec, const CVec2<U>& onto,
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
    FALCON_INLINE constexpr PromotedFloatCVec2<T, U> CVec2<T>::reject(const CVec2<U>& from) const noexcept
        requires StrictArithmetic<T>
    { return static_cast<PromotedFloatCVec2<T, U>>(*this) - this->project(from); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec2<T, U> CVec2<T>::rejectNorm(const CVec2<U>& from) const noexcept
        requires StrictArithmetic<T>
    { return *this - this->projectNorm(from); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedFloatCVec2<T, U> CVec2<T>::reject(const CVec2& vec, const CVec2<U>& from) noexcept
        requires StrictArithmetic<T>
    { return vec.reject(from); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec2<T, U> CVec2<T>::rejectNorm(const CVec2& vec, const CVec2<U>& from) noexcept
        requires StrictArithmetic<T>
    { return vec.rejectNorm(from); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedFloatCVec2<T, U> CVec2<T>::safeReject(const CVec2<U>& from) const noexcept
        requires StrictArithmetic<T>
    {
        if (hasNaN() || from.hasNaN())
        {
            return CVec2<Magnitude<PromotedValue_t<T, U>>>::zero();
        }

        return static_cast<PromotedFloatCVec2<T, U>>(*this) - safeProject(from);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec2<T, U> CVec2<T>::safeRejectNorm(const CVec2<U>& from) const noexcept
        requires StrictArithmetic<T>
    {
        if (hasNaN() || from.hasNaN())
        {
            return CVec2<PromotedValue_t<T, U>>::zero();
        }

        return *this - safeProjectNorm(from);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedFloatCVec2<T, U> CVec2<T>::safeReject(const CVec2& vec,
                                                                          const CVec2<U>& from) noexcept
        requires StrictArithmetic<T>
    { return vec.safeReject(from); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec2<T, U> CVec2<T>::safeRejectNorm(const CVec2& vec,
                                                                         const CVec2<U>& from) noexcept
        requires StrictArithmetic<T>
    { return vec.safeRejectNorm(from); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedFloatCVec2<T, U> CVec2<T>::tryReject(const CVec2<U>& from,
                                                                         OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        if (hasNaN() || from.hasNaN())
        {
            status = OperationStatus::NANOPERAND;
            return CVec2<Magnitude<PromotedValue_t<T, U>>>::zero();
        }

        return static_cast<PromotedFloatCVec2<T, U>>(*this) - this->tryProject(from, status);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec2<T, U> CVec2<T>::tryRejectNorm(const CVec2<U>& from,
                                                                        OperationStatus& status) const noexcept
        requires StrictArithmetic<T>
    {
        if (hasNaN() || from.hasNaN())
        {
            status = OperationStatus::NANOPERAND;
            return CVec2<PromotedValue_t<T, U>>::zero();
        }

        return *this - this->tryProjectNorm(from, status);
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedFloatCVec2<T, U> CVec2<T>::tryReject(const CVec2& vec, const CVec2<U>& from,
                                                                         OperationStatus& status) noexcept
        requires StrictArithmetic<T>
    { return vec.tryReject(from, status); }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec2<T, U> CVec2<T>::tryRejectNorm(const CVec2& vec, const CVec2<U>& from,
                                                                        OperationStatus& status) noexcept
        requires StrictArithmetic<T>
    { return vec.tryRejectNorm(from, status); }


    /**************************************
     *                                    *
     *             UTILITIES              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr bool CVec2<T>::hasInf() const noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            return flcn::isinf(_data[0]) | flcn::isinf(_data[1]);
        }
        else
        {
            return false;
        }
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool CVec2<T>::hasInf(const CVec2& vec) noexcept
    { return vec.hasInf(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool CVec2<T>::hasNaN() const noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            return flcn::isnan(_data[0]) | flcn::isnan(_data[1]);
        }
        else
        {
            return false;
        }
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool CVec2<T>::hasNaN(const CVec2& vec) noexcept
    { return vec.hasNaN(); }
} // namespace flcn

#if defined(__clang__)
    #pragma clang diagnostic pop
#endif
