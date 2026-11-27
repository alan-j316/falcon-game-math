#pragma once
#include "common/Types.h"
/**
 * @file Quaternion.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 1, 2026
 *
 * @brief Implementation of member function declared in Quaternion.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

namespace flcn
{

    /**************************************
     *                                    *
     *            INITIALIZERS            *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr Quat<T>::Quat(const T x, const T y, const T z, const T w) noexcept
    {
        _data[0] = x;
        _data[1] = y;
        _data[2] = z;
        _data[3] = w;
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Quat<T>::Quat(const Vec3<T>& complex, T real) noexcept
    {
        _data[0] = complex.x();
        _data[1] = complex.y();
        _data[2] = complex.z();
        _data[3] = real;
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Quat<T>::Quat(T real, const Vec3<T>& complex) noexcept
    {
        _data[0] = complex.x();
        _data[1] = complex.y();
        _data[2] = complex.z();
        _data[3] = real;
    }


    template <Arithmetic T>
    template <Arithmetic U>
    FALCON_INLINE constexpr Quat<T>::Quat(const Quat<U>& other) noexcept
    {
        x() = static_cast<T>(other.x());
        y() = static_cast<T>(other.y());
        z() = static_cast<T>(other.z());
        w() = static_cast<T>(other.w());
    }



    /**************************************
     *                                    *
     *             ACCESSORS              *
     *                                    *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr T Quat<T>::x() const noexcept
    { return _data[0]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T& Quat<T>::x() noexcept
    { return _data[0]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Quat<T>::y() const noexcept
    { return _data[1]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T& Quat<T>::y() noexcept
    { return _data[1]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Quat<T>::z() const noexcept
    { return _data[2]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T& Quat<T>::z() noexcept
    { return _data[2]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Quat<T>::w() const noexcept
    { return _data[3]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T& Quat<T>::w() noexcept
    { return _data[3]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Quat<T>::i() const noexcept
    { return _data[0]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T& Quat<T>::i() noexcept
    { return _data[0]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Quat<T>::j() const noexcept
    { return _data[1]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T& Quat<T>::j() noexcept
    { return _data[1]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Quat<T>::k() const noexcept
    { return _data[2]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T& Quat<T>::k() noexcept
    { return _data[2]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Quat<T>::s() const noexcept
    { return _data[3]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T& Quat<T>::s() noexcept
    { return _data[3]; }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T> Quat<T>::getVectorPart() const noexcept
    { return Vec3<T>{ _data[0], _data[1], _data[2] }; }


    template <Arithmetic T>
    FALCON_INLINE constexpr T Quat<T>::getScalarPart() const noexcept
    { return _data[3]; }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedQuaternion<T, U> Quat<T>::operator+(const Quat<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        return Quat<R>{ R(_data[0] + rhs.i()), R(_data[1] + rhs.j()), R(_data[2] + rhs.k()),
                              R(_data[3] + rhs.s()) };
    }

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr Quat<T>& Quat<T>::operator+=(const Quat<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] = static_cast<T>(_data[0] + rhs.i());
        _data[1] = static_cast<T>(_data[1] + rhs.j());
        _data[2] = static_cast<T>(_data[2] + rhs.k());
        _data[3] = static_cast<T>(_data[3] + rhs.s());

        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedQuaternion<T, U> Quat<T>::operator-(const Quat<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        return Quat<R>{ R(_data[0] - rhs.i()), R(_data[1] - rhs.j()), R(_data[2] - rhs.k()),
                              R(_data[3] - rhs.s()) };
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr Quat<T>& Quat<T>::operator-=(const Quat<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] = static_cast<T>(_data[0] - rhs.i());
        _data[1] = static_cast<T>(_data[1] - rhs.j());
        _data[2] = static_cast<T>(_data[2] - rhs.k());
        _data[3] = static_cast<T>(_data[3] - rhs.s());

        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
        requires StrictSignedness<T, S>
    FALCON_INLINE constexpr PromotedQuaternion<T, S> Quat<T>::operator*(S scalar) const noexcept
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, S>;
        return Quat<R>{ R(_data[0] * scalar), R(_data[1] * scalar), R(_data[2] * scalar), R(_data[3] * scalar) };
    }


    template <StrictArithmetic T, StrictArithmetic S>
        requires StrictSignedness<T, S>
    FALCON_INLINE constexpr PromotedQuaternion<T, S> operator*(S scalar, const Quat<T>& quat) noexcept
    { return quat * scalar; }


    template <Arithmetic T>
    template <StrictArithmetic S>
        requires StrictSignedness<T, S>
    FALCON_INLINE constexpr Quat<T>& Quat<T>::operator*=(S scalar) noexcept
        requires StrictArithmetic<T>
    {
        _data[0] = static_cast<T>(_data[0] * scalar);
        _data[1] = static_cast<T>(_data[1] * scalar);
        _data[2] = static_cast<T>(_data[2] * scalar);
        _data[3] = static_cast<T>(_data[3] * scalar);

        return *this;
    }



    /**************************************
     *         QUATERNION ALGEBRA         *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr Quat<T> Quat<T>::conjugate() const noexcept
        requires SignedStrictArithmetic<T>
    { return Quat{ T(-_data[0]), T(-_data[1]), T(-_data[2]), T(_data[3]) }; }


    template <Arithmetic T>
    FALCON_INLINE constexpr Quat<T> Quat<T>::conjugate(const Quat& quat) noexcept
        requires SignedStrictArithmetic<T>
    { return quat.conjugate(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Magnitude<T> Quat<T>::mag() const noexcept
        requires StrictArithmetic<T>
    {
        // TODO: Update to use flcn::sqrt
        return Magnitude<T>(std::sqrt(dot(*this)));
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Magnitude<T> Quat<T>::mag(const Quat& quat) noexcept
        requires StrictArithmetic<T>
    { return quat.mag(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Quat<Magnitude<T>> Quat<T>::inverse() const noexcept
        requires SignedStrictArithmetic<T>
    {
        // note: this->conjugate(this is implied)
        FALCON_ASSERT_MSG(dot(*this) > 0, flcn::messages::assertion::QUAT_DIV_BY_ZERO);
        using M = Magnitude<T>;
        return static_cast<Quat<M>>(conjugate()) / static_cast<M>(dot(*this));
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Quat<Magnitude<T>> Quat<T>::inverse(const Quat& quat) noexcept
        requires SignedStrictArithmetic<T>
    { return quat.inverse(); }



    /**************************************
     *           VECTOR ALGEBRA           *
     **************************************/

    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedQuaternion<T, U> Quat<T>::operator*(const Quat<U>& other) const noexcept
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        return Quat<R>{ R(w() * other.x() + x() * other.w() + y() * other.z() - z() * other.y()),
                              R(w() * other.y() - x() * other.z() + y() * other.w() + z() * other.x()),
                              R(w() * other.z() + x() * other.y() - y() * other.x() + z() * other.w()),
                              R(w() * other.w() - x() * other.x() - y() * other.y() - z() * other.z()) };
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr Quat<T>& Quat<T>::operator*=(const Quat<U>& other) noexcept
        requires StrictArithmetic<T>
    {

        // We need an intermediate since every quaternion components participate
        // in determining each component of result.
        auto intermediate = (*this) * other;
        *this             = static_cast<Quat<T>>(intermediate);
        return *this;
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedValue_t<T, U> Quat<T>::dot(const Quat<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        return R(x() * rhs.x() + y() * rhs.y() + z() * rhs.z() + w() * rhs.w());
    }


    template <Arithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedValue_t<T, U> Quat<T>::dot(const Quat& lhs,
                                                                  const Quat<U>& rhs) noexcept
        requires StrictArithmetic<T>
    { return lhs.dot(rhs); }


    template <Arithmetic T>
    template <StrictArithmetic S>
        requires StrictSignedness<T, S>
    FALCON_INLINE constexpr PromotedQuaternion<T, S> Quat<T>::operator/(S scalar) const noexcept
        requires StrictArithmetic<T>
    {

        using R = PromotedValue_t<T, S>;


        if constexpr (std::is_floating_point_v<R>)
        {
            FALCON_ASSERT_MSG(flcn::abs(scalar) >= flcn::Config::EPSILON<R>, flcn::messages::assertion::QUAT_DIV_BY_ZERO);
            FALCON_ASSERT_MSG(!flcn::isNaN(scalar) && !hasNaN(), flcn::messages::assertion::QUAT_HAS_NAN);

            R factor = R(1) / static_cast<R>(scalar);
            return Quat<R>(_data[0] * factor, _data[1] * factor, _data[2] * factor, _data[3] * factor);
        }
        else
        {
            FALCON_ASSERT_MSG(flcn::abs(scalar) != R(0), flcn::messages::assertion::QUAT_DIV_BY_ZERO);
            R tScalar = static_cast<R>(scalar);
            return Quat<R>(_data[0] / tScalar, _data[1] / tScalar, _data[2] / tScalar, _data[3] / tScalar);
        }
    }


    template <Arithmetic T>
    template <StrictArithmetic S>
        requires StrictSignedness<T, S>
    FALCON_INLINE constexpr Quat<T>& Quat<T>::operator/=(S scalar) noexcept
        requires StrictArithmetic<T>
    {
        using R = PromotedValue_t<T, S>;

        if constexpr (std::is_floating_point_v<R>)
        {
            FALCON_ASSERT_MSG(flcn::abs(scalar) > flcn::Config::EPSILON<S>, flcn::messages::assertion::QUAT_DIV_BY_ZERO);
            FALCON_ASSERT_MSG(!flcn::isNaN(scalar) && !hasNaN(), flcn::messages::assertion::QUAT_HAS_NAN);

            R factor = R(1) / static_cast<R>(scalar);

            _data[0] = static_cast<T>(factor * _data[0]);
            _data[1] = static_cast<T>(factor * _data[1]);
            _data[2] = static_cast<T>(factor * _data[2]);
            _data[3] = static_cast<T>(factor * _data[3]);
        }
        else
        {
            FALCON_ASSERT_MSG(flcn::abs(scalar) != R(0), flcn::messages::assertion::QUAT_DIV_BY_ZERO);
            _data[0] = static_cast<T>(_data[0] / static_cast<R>(scalar));
            _data[1] = static_cast<T>(_data[1] / static_cast<R>(scalar));
            _data[2] = static_cast<T>(_data[2] / static_cast<R>(scalar));
            _data[3] = static_cast<T>(_data[3] / static_cast<R>(scalar));
        }

        return *this;
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr Quat<T> Quat<T>::operator-() const noexcept
        requires SignedStrictArithmetic<T>
    { return Quat{ T(-_data[0]), T(-_data[1]), T(-_data[2]), T(-_data[3]) }; }



    /**************************************
     *             EQUALITY              *
     **************************************/

    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Quat<T>::allEq(const Quat<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        {
            return x() == rhs.x() && y() == rhs.y() && z() == rhs.z() && w() == rhs.w();
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
            return (x() == rhs.x() || flcn::abs(x() - rhs.x()) <= epsilon) &&
                (y() == rhs.y() || flcn::abs(y() - rhs.y()) <= epsilon) &&
                (z() == rhs.z() || flcn::abs(z() - rhs.z()) <= epsilon) &&
                (w() == rhs.w() || flcn::abs(w() - rhs.w()) <= epsilon);
        }
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Quat<T>::allEq(const Quat& lhs, const Quat<U>& rhs,
                                                   const double epsilon) noexcept
    { return lhs.allEq(rhs, epsilon); }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Quat<T>::anyNeq(const Quat<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        {
            return x() != rhs.x() || y() != rhs.y() || z() != rhs.z() || w() != rhs.w();
        }
        else
        {
            /** @note Identity check and inverted logic handle NAN_F and INFINITY per IEEE 754. */
            return (x() != rhs.x() && !(flcn::abs(x() - rhs.x()) <= epsilon)) ||
                (y() != rhs.y() && !(flcn::abs(y() - rhs.y()) <= epsilon)) ||
                (z() != rhs.z() && !(flcn::abs(z() - rhs.z()) <= epsilon)) ||
                (w() != rhs.w() && !(flcn::abs(w() - rhs.w()) <= epsilon));
        }
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Quat<T>::anyNeq(const Quat& lhs, const Quat<U>& rhs,
                                                    const double epsilon) noexcept
    { return lhs.anyNeq(rhs, epsilon); }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr Quat<bool> Quat<T>::eq(const Quat<U>& rhs,
                                                            const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        {
            return Quat<bool>{ x() == rhs.x(), y() == rhs.y(), z() == rhs.z(), w() == rhs.w() };
        }
        else
        {
            /** @note Direct equality check is required to handle @ref INFINITY cases, as Inf - Inf results in NAN_F. */
            return Quat<bool>{ x() == rhs.x() || flcn::abs(x() - rhs.x()) <= epsilon,
                                     y() == rhs.y() || flcn::abs(y() - rhs.y()) <= epsilon,
                                     z() == rhs.z() || flcn::abs(z() - rhs.z()) <= epsilon,
                                     w() == rhs.w() || flcn::abs(w() - rhs.w()) <= epsilon };
        }
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr Quat<bool> Quat<T>::eq(const Quat& lhs, const Quat<U>& rhs,
                                                            const double epsilon) noexcept
    { return lhs.eq(rhs, epsilon); }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr Quat<bool> Quat<T>::neq(const Quat<U>& rhs, double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        {
            return Quat<bool>{ x() != rhs.x(), y() != rhs.y(), z() != rhs.z(), w() != rhs.w() };
        }
        else
        {
            /** @note Identity check and inverted logic handle NAN_F and INFINITY per IEEE 754. */
            return Quat<bool>{ x() != rhs.x() && !(flcn::abs(x() - rhs.x()) <= epsilon),
                                     y() != rhs.y() && !(flcn::abs(y() - rhs.y()) <= epsilon),
                                     z() != rhs.z() && !(flcn::abs(z() - rhs.z()) <= epsilon),
                                     w() != rhs.w() && !(flcn::abs(w() - rhs.w()) <= epsilon) };
        }
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr Quat<bool> Quat<T>::neq(const Quat& lhs, const Quat<U>& rhs,
                                                             double epsilon) noexcept
    { return lhs.neq(rhs, epsilon); }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Quat<T>::vecEq(const Quat<U>& rhs, const double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        {
            return x() == rhs.x() && y() == rhs.y() && z() == rhs.z(); // Scalar part is not considered
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
            return (x() == rhs.x() || flcn::abs(x() - rhs.x()) <= epsilon) &&
                (y() == rhs.y() || flcn::abs(y() - rhs.y()) <= epsilon) &&
                (z() == rhs.z() || flcn::abs(z() - rhs.z()) <= epsilon);
        }
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Quat<T>::vecEq(const Quat& lhs, const Quat<U>& rhs,
                                                   const double epsilon) noexcept
    { return lhs.vecEq(rhs, epsilon); }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Quat<T>::vecNeq(const Quat<U>& rhs, double epsilon) const noexcept
    {
        if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        {
            return x() != rhs.x() || y() != rhs.y() || z() != rhs.z(); // Scalar part is ignored
        }
        else
        {
            /** @note Identity check and inverted logic handle NAN_F and INFINITY per IEEE 754. */
            return (x() != rhs.x() && !(flcn::abs(x() - rhs.x()) <= epsilon)) ||
                (y() != rhs.y() && !(flcn::abs(y() - rhs.y()) <= epsilon)) ||
                (z() != rhs.z() && !(flcn::abs(z() - rhs.z()) <= epsilon));
        }
    }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Quat<T>::vecNeq(const Quat& lhs, const Quat<U>& rhs,
                                                    double epsilon) noexcept
    { return lhs.vecNeq(rhs, epsilon); }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Quat<T>::operator==(const Quat<U>& rhs) const noexcept
    { return allEq(rhs); }


    template <Arithmetic T>
    template <Arithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr bool Quat<T>::operator!=(const Quat<U>& rhs) const noexcept
    { return anyNeq(rhs); }




    /**************************************
     *             UTILITIES              *
     **************************************/

    template <Arithmetic T>
    FALCON_INLINE constexpr bool Quat<T>::hasInf() const noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            return flcn::isInf(_data[0]) || flcn::isInf(_data[1]) || flcn::isInf(_data[2]) || flcn::isInf(_data[3]);
        }
        else
        {
            return false;
        }
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool Quat<T>::hasInf(const Quat& quat) noexcept
    { return quat.hasInf(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool Quat<T>::hasNaN() const noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            return flcn::isNaN(_data[0]) || flcn::isNaN(_data[1]) || flcn::isNaN(_data[2]) || flcn::isNaN(_data[3]);
        }
        else
        {
            return false;
        }
    }


    template <Arithmetic T>
    FALCON_INLINE constexpr bool Quat<T>::hasNaN(const Quat& quat) noexcept
    { return quat.hasNaN(); }


} // namespace flcn
