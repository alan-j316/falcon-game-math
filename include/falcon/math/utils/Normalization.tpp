#pragma once
/**
 * @file Normalization.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: November 28, 2026
 *
 * @brief Implementation of member function declared in Normalization.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include <falcon/core/Preprocessors.h>

namespace flcn
{



    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T> Vec3<T>::normalize(const Vec3& vec) noexcept
        requires FPArithmetic<T>
    { return vec.normalize(); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T> Vec3<T>::safeNormalize(const Vec3& vec) noexcept
        requires FPArithmetic<T>
    { return vec.safeNormalize(vec); }


    template <Arithmetic T>
    FALCON_INLINE constexpr Vec3<T> Vec3<T>::tryNormalize(const Vec3& vec, OperationStatus& status) noexcept
        requires FPArithmetic<T>
    { return vec.tryNormalize(status); }

} // namespace flcn
