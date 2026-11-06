#pragma once
/**
 * @file TypeUtils.h
 * @author Alan Abraham P Kochumon
 * @date Created on: May 27, 2026.
 *
 * @brief Helper utilities for testing of C++ types.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <type_traits>



/** @brief Assert that @p Klass is a C++ trivial type. */
#define ASSERT_TRIVIAL_TYPE(Klass)                                                                                     \
    static_assert(std::is_trivial_v<Klass>);                                                                           \
    static_assert(std::is_trivially_default_constructible_v<Klass>);                                                   \
    static_assert(std::is_trivially_copy_constructible_v<Klass>);                                                      \
    static_assert(std::is_trivially_copy_assignable_v<Klass>);                                                         \
    static_assert(std::is_trivially_copyable_v<Klass>);                                                                \
    static_assert(std::is_trivially_move_constructible_v<Klass>);                                                      \
    static_assert(std::is_trivially_move_assignable_v<Klass>);                                                         \
    static_assert(std::is_trivially_destructible_v<Klass>)
