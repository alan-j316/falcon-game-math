/**
 * @file TrivialTypeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 27, 2026.
 *
 * @brief Verify @ref fgm classes and structs are trivial types.
 *
 * @copyright Copyright (c) a Alan Abraham P Kochumon
 */


#include "utils/TypeUtils.h"

#include <falcon/math/Quaternion.h>
#include <falcon/math/matrices/Mat2.h>
#include <falcon/math/matrices/Mat2x3.h>
#include <falcon/math/matrices/Mat2x4.h>
#include <falcon/math/matrices/Mat3.h>
#include <falcon/math/matrices/Mat3x2.h>
#include <falcon/math/matrices/Mat3x4.h>
#include <falcon/math/matrices/Mat4.h>
#include <falcon/math/matrices/Mat4x2.h>
#include <falcon/math/matrices/Mat4x3.h>
#include <falcon/math/vectors/CVec2.h>
#include <falcon/math/vectors/Vec3.h>
#include <falcon/math/vectors/Vec4.h>

/**
 * @addtogroup T_FALCON_Trivial
 * @{
 */

/** @test Verify that @ref fgm Vectors are trivial types. */
ASSERT_TRIVIAL_TYPE(flcn::CVec2<float>);
ASSERT_TRIVIAL_TYPE(flcn::Vec3<float>);
ASSERT_TRIVIAL_TYPE(flcn::Vec4<float>);


/** @test Verify that @ref fgm Matrices are trivial types. */
ASSERT_TRIVIAL_TYPE(flcn::Mat2<float>);
ASSERT_TRIVIAL_TYPE(flcn::Mat2x3<float>);
ASSERT_TRIVIAL_TYPE(flcn::Mat2x4<float>);
ASSERT_TRIVIAL_TYPE(flcn::Mat3<float>);
ASSERT_TRIVIAL_TYPE(flcn::Mat3x2<float>);
ASSERT_TRIVIAL_TYPE(flcn::Mat3x4<float>);
ASSERT_TRIVIAL_TYPE(flcn::Mat4<float>);
ASSERT_TRIVIAL_TYPE(flcn::Mat4x2<float>);
ASSERT_TRIVIAL_TYPE(flcn::Mat4x3<float>);


/** @test Verify that @ref fgm Quaternions are trivial types. */
ASSERT_TRIVIAL_TYPE(flcn::Quaternion<float>);

/** @} */
