#pragma once
/**
 * @file Transform4.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 30, 2026
 *
 * @brief Implementation of member functions declared in Transform4.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <falcon/core/Preprocessors.h>


namespace flcn
{

    /**************************************
     *                                    *
     *            INITIALIZERS            *
     *                                    *
     **************************************/

    template <StrictArithmetic T>
    FALCON_INLINE constexpr Transform4<T>::Transform4(const T m00, const T m01, const T m02, const T m03, const T m10,
                                                   const T m11, const T m12, const T m13, const T m20, const T m21,
                                                   const T m22, const T m23) noexcept
        : Mat4<T>{ m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, T(0), T(0), T(0), T(1) }
    {}


    template <StrictArithmetic T>
    FALCON_INLINE constexpr Transform4<T>::Transform4(const Vec3<T>& firstAxis, const Vec3<T>& secondAxis,
                                                   const Vec3<T>& thirdAxis, const Point3<T>& origin) noexcept
        : Mat4<T>{ firstAxis.x(), secondAxis.x(), thirdAxis.x(), origin.x(),
                   firstAxis.y(), secondAxis.y(), thirdAxis.y(), origin.y(),
                   firstAxis.z(), secondAxis.z(), thirdAxis.z(), origin.z(),
                   T(0),          T(0),           T(0),          T(1) }
    {}


    template <StrictArithmetic T>
    template <StrictArithmetic U>
    FALCON_INLINE constexpr Transform4<T>::Transform4(const Transform4<U>& other) noexcept
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

    template <StrictArithmetic T>
    FALCON_INLINE constexpr Vec3<T>& Transform4<T>::operator[](std::size_t col) noexcept
    {
        FALCON_ASSERT_MSG(col < COLUMNS, flcn::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return *reinterpret_cast<Vec3<T>*>(&(this->_data[col]));
    }


    template <StrictArithmetic T>
    FALCON_INLINE constexpr auto Transform4<T>::operator[](std::size_t col) const noexcept
    {
        FALCON_ASSERT_MSG(col < COLUMNS, flcn::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        if (std::is_constant_evaluated())
        {
            return this->_data[col].template swizzle<axis::X, axis::Y, axis::Z>();
        }
        else
        {
            return *reinterpret_cast<const Vec3<T>*>(&(this->_data[col]));
        }
    }


    template <StrictArithmetic T>
    FALCON_INLINE constexpr T& Transform4<T>::operator()(std::size_t row, std::size_t col) noexcept
    {
        FALCON_ASSERT_MSG(col < COLUMNS && row < ROWS, flcn::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return this->_data[col][row];
    }


    template <StrictArithmetic T>
    FALCON_INLINE constexpr const T& Transform4<T>::operator()(std::size_t row, std::size_t col) const noexcept
    {
        FALCON_ASSERT_MSG(col < COLUMNS && row < ROWS, flcn::messages::assertion::MAT_OUT_OF_BOUNDS_ACCESS);
        return this->_data[col][row];
    }


    template <StrictArithmetic T>
    FALCON_INLINE constexpr auto Transform4<T>::getTranslation() const noexcept
    { return Point3<T>{ (*this)(0, 3), (*this)(1, 3), (*this)(2, 3) }; }


    template <StrictArithmetic T>
    FALCON_INLINE constexpr void Transform4<T>::setTranslation(const Point3<T>& translation) noexcept
    {
        (*this)(0, 3) = translation.x();
        (*this)(1, 3) = translation.y();
        (*this)(2, 3) = translation.z();
    }


    template <StrictArithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedVec3<T, U> Transform4<T>::operator*(const Vec3<U>& vec) const noexcept
        requires StrictArithmetic<T>
    {
        // NOTE: The last column entry is ignored since we have an implied w entry for Vec3 of 0 (<x, y, z, 0>).
        using R = std::common_type_t<T, U>;
        return Vec3<R>{ static_cast<R>((*this)(0, 0) * vec.x() + (*this)(0, 1) * vec.y() + (*this)(0, 2) * vec.z()),
                        static_cast<R>((*this)(1, 0) * vec.x() + (*this)(1, 1) * vec.y() + (*this)(1, 2) * vec.z()),
                        static_cast<R>((*this)(2, 0) * vec.x() + (*this)(2, 1) * vec.y() + (*this)(2, 2) * vec.z()) };
    }


    template <StrictArithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr PromotedPoint3<T, U> Transform4<T>::operator*(const Point3<U>& point) const noexcept
        requires StrictArithmetic<T>
    {
        // NOTE: The last column entry is added since we have an implied w entry for Point3 of 1 (<x, y, z, 1>).
        using R = std::common_type_t<T, U>;
        return Point3<R>{ static_cast<R>((*this)(0, 0) * point.x() + (*this)(0, 1) * point.y() +
                                         (*this)(0, 2) * point.z() + (*this)(0, 3)),
                          static_cast<R>((*this)(1, 0) * point.x() + (*this)(1, 1) * point.y() +
                                         (*this)(1, 2) * point.z() + (*this)(1, 3)),
                          static_cast<R>((*this)(2, 0) * point.x() + (*this)(2, 1) * point.y() +
                                         (*this)(2, 2) * point.z() + (*this)(2, 3)) };
    }



    /**************************************
     *                                    *
     *       ARITHMETIC OPERATIONS        *
     *                                    *
     **************************************/

    template <StrictArithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedTransform4<T, U> Transform4<T>::operator*(const Transform4<U>& rhs) const noexcept
        requires StrictArithmetic<T>
    {
        using R = std::common_type_t<T, U>;
        return Transform4<R>{
            // First Row
            static_cast<R>((*this)(0, 0) * rhs(0, 0) + (*this)(0, 1) * rhs(1, 0) + (*this)(0, 2) * rhs(2, 0)),
            static_cast<R>((*this)(0, 0) * rhs(0, 1) + (*this)(0, 1) * rhs(1, 1) + (*this)(0, 2) * rhs(2, 1)),
            static_cast<R>((*this)(0, 0) * rhs(0, 2) + (*this)(0, 1) * rhs(1, 2) + (*this)(0, 2) * rhs(2, 2)),
            static_cast<R>((*this)(0, 0) * rhs(0, 3) + (*this)(0, 1) * rhs(1, 3) + (*this)(0, 2) * rhs(2, 3) +
                           (*this)(0, 3)),
            // Second Row
            static_cast<R>((*this)(1, 0) * rhs(0, 0) + (*this)(1, 1) * rhs(1, 0) + (*this)(1, 2) * rhs(2, 0)),
            static_cast<R>((*this)(1, 0) * rhs(0, 1) + (*this)(1, 1) * rhs(1, 1) + (*this)(1, 2) * rhs(2, 1)),
            static_cast<R>((*this)(1, 0) * rhs(0, 2) + (*this)(1, 1) * rhs(1, 2) + (*this)(1, 2) * rhs(2, 2)),
            static_cast<R>((*this)(1, 0) * rhs(0, 3) + (*this)(1, 1) * rhs(1, 3) + (*this)(1, 2) * rhs(2, 3) +
                           (*this)(1, 3)),
            // Third Row
            static_cast<R>((*this)(2, 0) * rhs(0, 0) + (*this)(2, 1) * rhs(1, 0) + (*this)(2, 2) * rhs(2, 0)),
            static_cast<R>((*this)(2, 0) * rhs(0, 1) + (*this)(2, 1) * rhs(1, 1) + (*this)(2, 2) * rhs(2, 1)),
            static_cast<R>((*this)(2, 0) * rhs(0, 2) + (*this)(2, 1) * rhs(1, 2) + (*this)(2, 2) * rhs(2, 2)),
            static_cast<R>((*this)(2, 0) * rhs(0, 3) + (*this)(2, 1) * rhs(1, 3) + (*this)(2, 2) * rhs(2, 3) +
                           (*this)(2, 3))
        };
    }


    template <StrictArithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    constexpr Transform4<T>& Transform4<T>::operator*=(const Transform4<U>& rhs) noexcept
        requires StrictArithmetic<T>
    {
        // We need an intermediate since the multiplication can override the values in "this" matrix
        // leading to incorrect values when multiplying the next (row, col).
        const auto intermediate = (*this) * rhs;
        (*this)                 = static_cast<Transform4<T>>(intermediate);
        return *this;
    }


    /**************************************
     *                                    *
     *           MATRIX ALGEBRA           *
     *                                    *
     **************************************/

    template <StrictArithmetic T>
    FALCON_INLINE constexpr Transform4<Magnitude<T>> Transform4<T>::inverse() const noexcept
        requires SignedStrictArithmetic<T>
    {
        using R = Magnitude<T>;

        auto a = static_cast<Vec3<R>>((*this)[0]);
        auto b = static_cast<Vec3<R>>((*this)[1]);
        auto c = static_cast<Vec3<R>>((*this)[2]);
        auto d = static_cast<Vec3<R>>((*this)[3]);

        auto s = a.cross(b);
        auto t = c.cross(d);

        FALCON_ASSERT_MSG(flcn::abs(s.dot(c)) > Config::EPSILON<R>, messages::assertion::MAT_INV_ZERO_DETERMINANT);

        R invDet = R(1) / s.dot(c);
        s *= invDet;
        t *= invDet;
        auto v = c * invDet;

        auto r0 = b.cross(v);
        auto r1 = v.cross(a);

        return Transform4<R>{ r0.x(), r0.y(),   r0.z(), -b.dot(t), r1.x(), r1.y(),
                              r1.z(), a.dot(t), s.x(),  s.y(),     s.z(),  -d.dot(s) };
    }


    template <StrictArithmetic T>
    FALCON_INLINE constexpr Transform4<Magnitude<T>> Transform4<T>::inverse(const Transform4& transform) noexcept
        requires SignedStrictArithmetic<T>
    { return transform.inverse(); }

} // namespace flcn
