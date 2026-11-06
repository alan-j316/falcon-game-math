#pragma once
/**
 * @file Point3.h
 * @author Alan Abraham P Kochumon
 * @date Created on: July 30, 2026
 *
 * @brief 3D point representation with a implicit w values of 1 <x, y, z, 1>.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec3.h"
#include "falcon/math/common/Types.h"


namespace flcn
{
    template <StrictArithmetic T>
    struct Point3: Vec3<T>
    {

        /**
         * @addtogroup FALCON_Point3_Init
         * @{
         */

        /// @brief @ref flcn::Vec3 CTORs
        using Vec3<T>::Vec3;

        /** @} */



        /**
         * @addtogroup FALCON_Point3_Arithmetic
         * @{
         */

        /**
         * @brief Add a vector(direction) to this point.
         *
         * @note Promotes the result to the wider type using @ref PromotedPoint3<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vector The vector to add.
         *
         * @return A new @ref Point3 representing a translated point.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedPoint3<T, U> operator+(const Vec3<U>& vector) const noexcept;


        /**
         * @brief Add a vector(direction) to this point in-place.
         *
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS vector. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] vector The vector to add.
         *
         * @return A reference to the current Point3 instance (*this).
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        constexpr Point3& operator+=(const Vec3<U>& vector) noexcept;


        /**
         * @brief Subtract a point from this point yielding a direction.
         *
         * @note Promotes the result to the wider type using @ref PromotedVec3<T, U>.
         * @note Operation is restricted to numeric types via @ref StrictArithmetic.
         *
         * @tparam U Numeric type of the RHS point. Must satisfy @ref StrictArithmetic.
         *
         * @param[in] rhs The point to subtract.
         *
         * @return A new @ref Vec3 representing a direction vector.
         */
        template <StrictArithmetic U>
            requires StrictSignedness<T, U>
        [[nodiscard]] constexpr PromotedVec3<T, U> operator-(const Point3<U>& rhs) const noexcept;

        /** @} */
    };



    /** @brief Template deduction guide for Point3 */
    template <typename T>
        requires StrictArithmetic<T>
    Point3(T, T, T) -> Point3<T>;

    template <typename T, typename U, typename V>
        requires StrictArithmetic<T> && StrictArithmetic<U> && StrictArithmetic<V>
    Point3(T, U, V) -> Point3<std::common_type_t<std::common_type_t<T, U>, V>>;

    template <typename T>
        requires StrictArithmetic<T>
    Point3(T) -> Point3<T>;

} // namespace flcn


#include "Point3.tpp"
