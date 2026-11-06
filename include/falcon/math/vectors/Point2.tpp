#pragma once
/**
 * @file Point2.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 30, 2026
 *
 * @brief Implementation of member function defined in Point2.h.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <falcon/core/Preprocessors.h>

namespace flcn
{

    template <StrictArithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedPoint2<T, U> Point2<T>::operator+(const CVec2<U>& vector) const noexcept
    {
        using R = std::common_type_t<T, U>;
        return Point2<R>(this->x() + vector.x(), this->y() + vector.y());
    }
    
    
    template <StrictArithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr Point2<T>& Point2<T>::operator+=(const CVec2<U>& vector) noexcept
    {
        this->x() += static_cast<T>(vector.x());
        this->y() += static_cast<T>(vector.y());
    
        return *this;
    }
    
    
    template <StrictArithmetic T>
    template <StrictArithmetic U>
        requires StrictSignedness<T, U>
    FALCON_INLINE constexpr PromotedCVec2<T, U> Point2<T>::operator-(const Point2<U>& rhs) const noexcept
    {
        using R = std::common_type_t<T, U>;
        return Point2<R>(this->x() - rhs.x(), this->y() - rhs.y());
    }


} // namespace flcn
