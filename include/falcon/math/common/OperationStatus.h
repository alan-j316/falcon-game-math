#pragma once
/**
 * @file OperationStatus.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 28, 2026
 *
 * @brief Operation status flags in use by "try..." variants of math functions that can trigger a hardware exception.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Messages.h"

#include <cstdint>


namespace flcn
{

    /**
     * @addtogroup FALCON_Math_Common
     * @{
     */

    /** @brief Operation status flags used for flagging exceptions and unexpected behavior. */
    enum class OperationStatus : uint8_t
    {
        SUCCESS = 0,    ///< Flag indicating operation success.
        DIVISIONBYZERO, ///< Flag indicating that division by zero has occured.
        NANOPERAND      ///< Flag indicating that one or more operands are NaN.
    };


    /**
     * @brief Translates @ref OperationStatus into a verbose message.
     *
     * @param[in] status The status to convert.
     *
     * @return The status message.
     */
    constexpr std::string_view getStatusMessage(const OperationStatus status) noexcept
    {
        switch (status)
        {
            case OperationStatus::SUCCESS:
                return messages::opstatus::OPERATION_SUCCESS;
            case OperationStatus::DIVISIONBYZERO:
                return messages::opstatus::OPERATION_DIV_BY_ZERO;
            case OperationStatus::NANOPERAND:
                return messages::opstatus::OPERATION_NAN_OPERAND;
            default:
                return messages::opstatus::OPERATION_UNKNOWN_FAILURE;
        }
    }

    /** @} */

} // namespace flcn
