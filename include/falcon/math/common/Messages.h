#pragma once
/**
 * @file Messages.h
 * @author Alan Abraham P Kochumon
 * @date Created on: April 25, 2026
 *
 * @brief Central repository for all library string resources like assertion messages.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <string_view>


/**
 * @addtogroup FALCON_Messages
 * @{
 */

namespace flcn::messages
{
    namespace assertion
    {
        /** @brief Assertion message thrown when a matrix division by zero occurs. */
        inline constexpr auto MAT_DIV_BY_ZERO          = "[Matrix]: Division by zero";
        inline constexpr auto MAT_DET_DIV_BY_ZERO      = "[Matrix Determinant]: Division by zero.";
        inline constexpr auto MAT_INV_ZERO_DETERMINANT = "[Matrix Inverse]: Zero Determinant.";
        inline constexpr auto MAT_OUT_OF_BOUNDS_ACCESS = "[Matrix]: Out of bounds.";

        inline constexpr auto VEC_DIV_BY_ZERO           = "[Vector]: Division by zero";
        inline constexpr auto VEC_NORMALIZE_DIV_BY_ZERO = "[Vector Normalization]: Division by zero.";
        inline constexpr auto VEC_PROJECT_DIV_BY_ZERO   = "[Vector Projection]: Division by zero.";
        inline constexpr auto VEC_REJECT_DIV_BY_ZERO    = "[Vector Rejection]: Division by zero.";
        inline constexpr auto VEC_OUT_OF_BOUNDS_ACCESS  = "[Vector]: Out of bounds.";

        inline constexpr auto QUAT_DIV_BY_ZERO = "[Quaternion]: Division by zero";
        inline constexpr auto QUAT_HAS_NAN     = "[Quaternion]: Invalid operation. NaN found!";

    } // namespace assertion


    /** @brief Message mapping for @ref OperationStatus status code. */
    namespace opstatus
    {
        inline constexpr std::string_view OPERATION_SUCCESS         = "Operation success!";
        inline constexpr std::string_view OPERATION_DIV_BY_ZERO     = "Failure: Division by Zero";
        inline constexpr std::string_view OPERATION_NAN_OPERAND     = "Failure: NaN operand encountered";
        inline constexpr std::string_view OPERATION_UNKNOWN_FAILURE = "Failure: Unknown error";

    } // namespace opstatus

} // namespace flcn::messages

/** @} */
