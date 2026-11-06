#pragma once
/**
 * @file Config.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 16, 2026
 *
 * @brief Global configuration for FALCON library.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "MathTraits.h"

#include <concepts>
#include <falcon/core/Preprocessors.h>

namespace flcn
{

    /**
     * @addtogroup FALCON_Math_Config
     * @{
     */

    struct Config
    {
        /** @brief Standard precision for logging and debugging. */
        static constexpr unsigned int LOG_PRECISION = 4;

        /** @brief Defines the maximum reliable decimal precision for 32-bit floating point types. */
        static constexpr unsigned int FLOAT_PRECISION = 5;

        /** @brief Defines the maximum reliable decimal precision for 64-bit floating point types. */
        static constexpr unsigned int DOUBLE_PRECISION = 15;

        /**
         * @brief Toggles between standard logging precision and type-specific maximum precision.
         */
        static inline bool useFullPrecision = false;



        /***********************************!***
         *                                    *
         *            CUSTOM EPSILON          *
         *                                    *
         **************************************/

        /** @brief The smallest positive value such that 1.0 + EPSILON != 1.0 for 32-bit floats. */
        static constexpr double FLOAT_EPSILON = 1e-5;

        /** @brief The smallest positive value such that 1.0 + EPSILON != 1.0 for 64-bit floats. */
        static constexpr double DOUBLE_EPSILON = 1e-13;

        /** @brief The smallest positive value such that 1.0 + EPSILON != 1.0 for floating point types. */
        template <typename T>
            requires Arithmetic<T>
        static constexpr double EPSILON =
            std::is_floating_point_v<T> ? std::is_same_v<T, double> ? DOUBLE_EPSILON : FLOAT_EPSILON : T(0);

        /**
         * @brief The squared tolerance threshold for floating-point zero-state comparisons.
         *
         * @details Used primarily to safely evaluate squared vector magnitudes (e.g., dot products) against zero
         *          without incurring the performance penalty of a square root operation.
         *          Mathematically calibrated to prevent underflow when comparing squared lengths.
         */
        template <typename T>
            requires std::floating_point<T>
        static constexpr double EPSILON_SQUARE = std::is_same_v<T, double> ? 1e-24 : 1e-10;
    };

    /** @} */


} // namespace flcn
