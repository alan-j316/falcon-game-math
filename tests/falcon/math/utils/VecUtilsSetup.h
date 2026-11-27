#pragma once
/**
 * @file VecUtilsSetup.h
 * @author Alan Abraham P Kochumon
 * @date Created on: November 26, 2026
 *
 * @brief Define test setups common to all @ref Vec3 tests.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#define FORCE_SCALAR
#define ENABLE_FALCON_SHADER_OPERATORS

#include "BoundsTestFixture.h"
#include "InterpolationTestFixture.h"
#include "utils/VectorUtils.h"

#include <../../../../include/falcon/core/traits/MathTraits.h>
#include <falcon/math/utils/Bounds.h>
#include <falcon/math/utils/Interpolation.h>
#include <gtest/gtest.h>

using namespace testutils;
