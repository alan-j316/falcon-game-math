#pragma once
/**
 * @file Vec2TestSetup.h
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Define test setups common to all @ref CVec3 tests.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */
// TODO: Rename all preprocessor to start with FALCON_ prefix
#define ENABLE_FALCON_SHADER_OPERATORS

#include "CommonSetup.h"
#include "utils/VectorUtils.h"

#include <falcon/math/common/MathTraits.h>
#include <falcon/math/vectors/simd/Vec2.h>
#include <gtest/gtest.h>


using namespace testutils;
