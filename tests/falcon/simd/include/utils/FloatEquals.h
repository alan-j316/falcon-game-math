#pragma once

#include <algorithm>
#include <cmath>
#include <limits>
// TODO: Refactor
inline bool floatEquals(float a, float b)
{
    return std::abs(a - b) <= std::numeric_limits<float>::epsilon() * std::max(std::abs(a), std::abs(b));
}
