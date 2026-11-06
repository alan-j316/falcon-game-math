#pragma once
/**
 * @file Preprocessors.h
 * @author Alan Abraham P Kochumon
 * @date Created on: August 14, 2026
 *
 * @brief Preprocessor directives for compiler intrinsic debug breaks, and assertions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <iostream>
#include <string>
#include <type_traits>


/**
 * @addtogroup Falcon_Core_Preprocessors
 * @{
 */

/**
 * @brief Triggers a compiler-specific breakpoint.
 */
#ifdef _MSC_VER
    #define FALCON_DEBUG_BREAK() __debugbreak()
#elif defined(__clang__) || defined(__GNUC__)
    #define FALCON_DEBUG_BREAK() __builtin_trap()
#else
    #include <signal.h>
    #define FALCON_DEBUG_BREAK() raise(SIGTRAP)
#endif

/**
 * @brief API directive for handle DLL exports.
 */
#ifdef _WIN32
    #define FALCON_API __declspec(dllimport)
#else
    #if __GNUC__ >= 4 || defined(__clang__)
        #define FALCON_API __attribute__((visibility("default")))
    #else
        #define FALCON_API
    #endif
#endif



namespace flcn::internal
{
    /**
     * @brief An internal function used for triggering compile time error with assertions.
     *        Since all the functions are marked as noexcept, throwing inside `std::is_constant_evaluated`
     *        will not work. So by calling a non constexpr function inside a constexpr function, it will trigger
     *        a no-compile error.
     */
    inline void compileTimeErrorTrap() {}

} // namespace flcn::internal


/**
 * @brief Log the assertion message and status to console.
 *
 * @param condition The condition that triggered the assertion.
 * @param message   An optional message, stating the reason behind assertion failure.
 * @param file      The name of the file that triggered the assertion.
 * @param line      The line number of hte code that triggered the assertion.
 */
inline void logAssertion(const char* condition, const char* message, const char* file, const int line)
{
    std::cerr << "[Falcon ASSERTION FAILED]\n"
              << "Condition: " << condition << '\n'
              << "Message:   " << (message ? message : "None") << '\n'
              << "Location:  " << file << ":" << line << '\n';
}


/**
 * @def FALCON_ASSERT_MSG(condition, message)
 * @brief Asserts a condition is `true`, breaking into the debugger with a custom message if `false`.
 *
 * @note This macro is strictly active only in **Debug** builds. In **Release** builds
 *       (when `NDEBUG` is defined), it expands into a zero-cost void cast.
 * @note To ensure that the macro support compile-time evaluation an exception is thrown,
 *       instead of logging during compile time.
 *
 * @param condition The boolean expression to evaluate.
 * @param message   A string literal or streamable object providing context on the failure.
 */
#ifndef NDEBUG
    #define FALCON_ASSERT_MSG(condition, message)                                                                 \
        do                                                                                                             \
        {                                                                                                              \
            if (std::is_constant_evaluated())                                                                          \
            {                                                                                                          \
                if (!(condition))                                                                                      \
                    flcn::internal::compileTimeErrorTrap();                                                             \
            }                                                                                                          \
            else                                                                                                       \
            {                                                                                                          \
                if (!(condition))                                                                                      \
                {                                                                                                      \
                    logAssertion(#condition, message, __FILE__, __LINE__);                                             \
                    FALCON_DEBUG_BREAK();                                                                         \
                }                                                                                                      \
            }                                                                                                          \
        } while (false)
#else
    #define FALCON_ASSERT_MSG(condition, message) ((void) 0)
#endif

/**
 * @def FALCON_ASSERT(condition)
 * @brief Asserts a condition is `true`, breaking into the debugger if `false`.
 *
 * @note This macro is strictly active only in **Debug** builds. In **Release** builds
 *       (when `NDEBUG` is defined), it expands into a zero-cost void cast.
 * @note To ensure that the macro support compile-time evaluation an exception is thrown,
 *       instead of logging during compile time.
 *
 * @param condition The boolean expression to evaluate.
 */
#ifndef NDEBUG
    #define FALCON_ASSERT(condition)                                                                              \
        do                                                                                                             \
        {                                                                                                              \
            if (std::is_constant_evaluated())                                                                          \
            {                                                                                                          \
                if (!(condition))                                                                                      \
                    flcn::internal::compileTimeErrorTrap();                                                             \
            }                                                                                                          \
            else                                                                                                       \
            {                                                                                                          \
                if (!(condition))                                                                                      \
                {                                                                                                      \
                    logAssertion(#condition, "", __FILE__, __LINE__);                                                  \
                    FALCON_DEBUG_BREAK();                                                                         \
                }                                                                                                      \
            }                                                                                                          \
        } while (false)
#else
    #define FALCON_ASSERT(condition) ((void) 0)
#endif


/**
 * @brief Compiler specific inlining syntax.
 */
#if defined(_MSC_VER) && !defined(__clang__)
    #define FALCON_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
    #define FALCON_INLINE inline __attribute__((always_inline))
#else
    #define FALCON_INLINE inline
#endif

/** @} */
