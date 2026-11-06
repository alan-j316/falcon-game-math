#pragma once
/**
 * @file TypeHelpers.h
 * @author Alan Abraham
 * @date Created on: August 21, 2026
 *
 * @brief Type trait wrappers.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <cstdint>
#include <type_traits>


/** @addtogroup Falcon_Core_Types
 *  @{
 */

namespace flcn::types
{
    /// Return whether a given type is 32-bit floating point number.
    template <typename T>
    constexpr auto IsFP64 = std::is_same_v<T, double>;

    /// Return whether a given type is 32-bit floating point number.
    template <typename T>
    constexpr auto IsFP32 = std::is_same_v<T, float>;

    /// Return whether a given type is 8-bit signed integral.
    template <typename T>
    constexpr auto IsByte = std::is_same_v<T, int8_t>;

    /// Return whether a given type is 16-bit signed integral.
    template <typename T>
    constexpr auto IsWord = std::is_same_v<T, int16_t>;

    /// Return whether a given type is 32-bit signed integral (double word).
    template <typename T>
    constexpr auto IsDWord = std::is_same_v<T, int32_t>;

    /// Return whether a given type is 64-bit signed integral (double word).
    template <typename T>
    constexpr auto IsQWord = std::is_same_v<T, int64_t>;


    /// Return whether a given type is 8-bit unsigned integral.
    template <typename T>
    constexpr auto IsUByte = std::is_same_v<T, uint8_t>;

    /// Return whether a given type is 16-bit unsigned integral.
    template <typename T>
    constexpr auto IsUWord = std::is_same_v<T, uint16_t>;

    /// Return whether a given type is 32-bit unsigned integral (double word).
    template <typename T>
    constexpr auto IsUDWord = std::is_same_v<T, uint32_t>;

    /// Return whether a given type is 64-bit unsigned integral (double word).
    template <typename T>
    constexpr auto IsUQWord = std::is_same_v<T, uint64_t>;


    /// @brief Convert any type to an equally-sized unsigned integral.
    template <typename T>
    struct UInt
    {
        using type = std::make_unsigned_t<T>;
    };

    template <>
    struct UInt<float>
    {
        using type = uint32_t;
    };

    template <>
    struct UInt<double>
    {
        using type = uint64_t;
    };

    template <>
    struct UInt<bool>
    {
        using type = uint8_t;
    };

    /// @brief Variable template helper for @ref flcn::UInt<T>::type.
    template <typename T>
    using UInt_t = UInt<T>::type;


} // namespace flcn::types

/** @} */
