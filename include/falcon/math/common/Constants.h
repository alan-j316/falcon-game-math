#pragma once
/**
 * @file Constants.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 21, 2026
 *
 * @brief Constant definitions of FALCON.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <concepts>
#include <cstdint>
#include <limits>
#include <numbers>


/**
 * @addtogroup FALCON_Math_Constants
 * @{
 */
namespace flcn::constants
{

    /** @brief Positive infinity for single-precision floats. */
    inline constexpr float INFINITY_F = std::numeric_limits<float>::infinity();

    /** @brief Positive infinity for double-precision floats. */
    inline constexpr double INFINITY_D = std::numeric_limits<double>::infinity();

    /** @brief Quiet Not-a-Number for single-precision floats. */
    inline constexpr float NaN = std::numeric_limits<float>::quiet_NaN();

    /** @brief Quiet Not-a-Number for double-precision floats. */
    inline constexpr double NaN_D = std::numeric_limits<double>::quiet_NaN();

    /** @brief The maximum possible swizzling dimension allowable for @ref flcn::Vector. */
    inline constexpr std::size_t MAX_VECTOR_SWIZZLE_DIMENSION = 4; // TODO: Remove

    /** @brief Standard value for PI. */
    template <std::floating_point T>
    inline constexpr T PI = std::numbers::pi_v<T>;

    /** @brief Standard value for inverse of PI (1/PI). */
    template <std::floating_point T>
    inline constexpr T INV_PI = std::numbers::inv_pi_v<T>;

    /** @brief Standard value for TAU (2.PI). */
    template <std::floating_point T>
    inline constexpr T TAU = std::numbers::pi_v<T> * T(2);

    /// Bitwise comparison mask representing truthiness.
    /// @note Not recommended for direct comparison with floating point numbers,
    ///       as the mask is a NaN for floating-point types.
    template <typename T>
    inline constexpr T TrueMask = static_cast<T>(~0ULL);

    /// Bitwise comparison mask representing falsiness.
    template <typename T>
    inline constexpr T FalseMask = static_cast<T>(0);

} // namespace flcn::constants


namespace flcn::reflect
{
    // NOTE: The last 3 bits are treated as x,y,z indicating in which axis reflection takes place.
    using RT                   = uint8_t;
    inline constexpr RT XY     = 0b00000001; ///< Alias for xy-plane reflection
    inline constexpr RT YZ     = 0b00000100; ///< Alias for yz-plane reflection
    inline constexpr RT ZX     = 0b00000010; ///< Alias for zx-plane reflection
    inline constexpr RT X      = 0b00000011; ///< Alias for x-axis reflection
    inline constexpr RT Y      = 0b00000101; ///< Alias for y-axis reflection
    inline constexpr RT Z      = 0b00000110; ///< Alias for z-axis reflection
    inline constexpr RT ORIGIN = 0b00000111; ///< Alias for origin reflection

} // namespace flcn::reflect


namespace flcn::axis
{
    /// @brief Alias for axis used in falcon.
    /// @typedef AT stands for Axis Type, which is uint8_t by default.
    using AT              = uint8_t;
    inline constexpr AT X = 0; ///< Alias for x-coordinate
    inline constexpr AT Y = 1; ///< Alias for y-coordinate
    inline constexpr AT Z = 2; ///< Alias for z-coordinate
    inline constexpr AT W = 3; ///< Alias for w-coordinate
} // namespace flcn::axis


namespace flcn::colors
{
    inline constexpr std::size_t R = 0; ///< Alias for red channel
    inline constexpr std::size_t G = 1; ///< Alias for green channel
    inline constexpr std::size_t B = 2; ///< Alias for blue channel
    inline constexpr std::size_t A = 3; ///< Alias for alpha channel
} // namespace flcn::colors


namespace flcn::stp
{
    inline constexpr std::size_t S = 0; ///< Alias for s-coordinate
    inline constexpr std::size_t T = 1; ///< Alias for t-coordinate
    inline constexpr std::size_t P = 2; ///< Alias for p-coordinate
    inline constexpr std::size_t Q = 3; ///< Alias for q-coordinate
} // namespace flcn::stp

/**
 * @}
 */
