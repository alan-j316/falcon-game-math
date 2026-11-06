#pragma once
/**
 * @file Point2.h
 * @author Alan Abraham P Kochumon
 * @date Created on: July 30, 2026
 *
 * @brief 3D point representation with an implicit w value of 1 <x, y, z, 1>.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CVec2.h"
#include "falcon/math/common/Types.h"


namespace flcn
{
    template <StrictArithmetic T>
    struct Point2: CVec2<T>
    {

        /**
         * @addtogroup FALCON_Point2_Init
         * @{
         */

        /// @brief @ref flcn::CVec2 CTORs
        using CVec2<T>::CVec2;

        /** @} */



        /**
         * @addtogroup FALCON_Point2_Arithmetic
         * @{
         */

        /**
         * @brief Add a vector(direction) to this point.
         *
         * @note Promotes the result to the wider type using @ref PromotedPoint2<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vector The vector to add.
         *
         * @return A new @ref Point2 representing a translated point.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedPoint2<T, U> operator+(const CVec2<U>& vector) const noexcept;


        /**
         * @brief Add a vector(direction) to this point in-place.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vector The vector to add.
         *
         * @return A reference to the current Point2 instance (*this).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        constexpr Point2& operator+=(const CVec2<U>& vector) noexcept;


        /**
         * @brief Subtract a point from this point yielding a direction.
         *
         * @note Promotes the result to the wider type using @ref PromotedCVec2<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS point. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The point to subtract.
         *
         * @return A new @ref CVec2 representing a direction vector.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedCVec2<T, U> operator-(const Point2<U>& rhs) const noexcept;

        /** @} */
    };



    /** @brief Template deduction guide for Point2 */
    template <typename T>
        requires StrictArithmetic<T>
    Point2(T, T) -> Point2<T>;

    template <typename T, typename U>
        requires StrictArithmetic<T> && StrictArithmetic<U>
    Point2(T, U) -> Point2<std::common_type_t<T, U>>;

    template <typename T>
        requires StrictArithmetic<T>
    Point2(T) -> Point2<T>;

} // namespace flcn


#include "Point2.tpp"
