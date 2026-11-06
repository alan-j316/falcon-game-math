#pragma once
/**
 * @file Point3.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 30, 2026
 *
 * @brief Implementation of member function defined in Point3.h.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <falcon/core/Preprocessors.h>

namespace flcn
{

    template <StrictArithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedPoint3<T, U> Point3<T>::operator+(const Vec3<U>& vector) const noexcept
    {
        using R = std::common_type_t<T, U>;
        return Point3<R>(this->x() + vector.x(), this->y() + vector.y(), this->z() + vector.z());
    }


    template <StrictArithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr Point3<T>& Point3<T>::operator+=(const Vec3<U>& vector) noexcept
    {
        this->x() += static_cast<T>(vector.x());
        this->y() += static_cast<T>(vector.y());
        this->z() += static_cast<T>(vector.z());

        return *this;
    }


    template <StrictArithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedVec3<T, U> Point3<T>::operator-(const Point3<U>& rhs) const noexcept
    {
        using R = std::common_type_t<T, U>;
        return Point3<R>(this->x() - rhs.x(), this->y() - rhs.y(), this->z() - rhs.z());
    }


} // namespace flcn
