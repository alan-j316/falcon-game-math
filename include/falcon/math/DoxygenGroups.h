#pragma once
/**
 * @file DoxygenGroups.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 18, 2026
 *
 * @brief Doxygen group for organizing Falcon Math library into modular units.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

// TODO: Update DOXYGEN Groups
// clang-format off
/**
 * @defgroup FALCON_Math Math Library
 * @brief Complete math library.
 * @{
 */
    
    /**
     * @defgroup FALCON_Core Core
     * @brief Fundamental mathematical structures and types.
     * @ingroup FALCON_Math
     * @{
     */

        /**
         * @defgroup FALCON_Core_SIMD SIMD Accelerated Math
         * @brief Fundamental mathematical structures with SIMD acceleration.
         * @ingroup FALCON_Core
         * @{
         */

            /**
             * @defgroup FALCON_Vectors Vectors
             * @brief N-dimensional Euclidean vector implementations.
             * @ingroup FALCON_Core_SIMD
             * @{
             */

                /**
                 * @defgroup FALCON_Point 2D Point
                 * @brief 2-dimensional point with an implicit z-value of 1.
                 * @ingroup FALCON_Vectors
                 * @{
                 *   @defgroup FALCON_Point2_Init Constructors
                 *   @defgroup FALCON_Point2_Arithmetic Arithmetic Operations
                 * @}
                 */

                /**
                 * @defgroup FALCON_Point 3D Point
                 * @brief 3-dimensional point with an implicit w-value of 1.
                 * @ingroup FALCON_Vectors
                 * @{
                 *   @defgroup FALCON_Point3_Init Constructors
                 *   @defgroup FALCON_Point3_Arithmetic Arithmetic Operations
                 * @}
                 */

                /**
                 * @defgroup FALCON_Vec2 2D Vectors
                 * @brief 2-dimensional Euclidean vectors (SIMD Accelerated).
                 * @ingroup FALCON_Vectors
                 * @{
                 *   @defgroup FALCON_Vec2_Members Class Members
                 *   @defgroup FALCON_Vec2_Init Constructors
                 *   @defgroup FALCON_Vec2_Access Accessors
                 *   @defgroup FALCON_Vec2_Arithmetic Arithmetic Operations
                 *   @defgroup FALCON_Vec2_Bitwise Boolean Bitwise Operations
                 *   @defgroup FALCON_Vec2_Equality Equality
                 *   @defgroup FALCON_Vec2_Comparison Comparisons
                 *   @defgroup FALCON_Vec2_Product Geometric Products
                 *   @defgroup FALCON_Vec2_Mag Vector Magnitude and Norms
                 *   @defgroup FALCON_Vec2_Dist Vector Distance
                 *   @defgroup FALCON_Vec2_Normalize Vector Normalization
                 *   @defgroup FALCON_Vec2_Proj Vector Projection and Rejection
                 *   @defgroup FALCON_Vec2_Alias Spatial Alias
                 *   @defgroup FALCON_Vec2_Log String Representation
                 *   @defgroup FALCON_Vec2_Const Vector Constants
                 *   @defgroup FALCON_Vec2_Utils Vector Utilities
                 *   @defgroup FALCON_Vec2_Swizzle Vector Swizzling
                 *   @defgroup FALCON_Vec2_Ptr Internal Storage Access
                 * @}
                 */

                /**
                 * @defgroup FALCON_Vec3 3D Vectors
                 * @brief 3-dimensional Euclidean vectors.
                 * @ingroup FALCON_Vectors
                 * @{
                 *   @defgroup FALCON_Vec3_Members Class Members
                 *   @defgroup FALCON_Vec3_Init Constructors
                 *   @defgroup FALCON_Vec3_Access Accessors
                 *   @defgroup FALCON_Vec3_Arithmetic Arithmetic Operations
                 *   @defgroup FALCON_Vec3_Bitwise Boolean Bitwise Operations
                 *   @defgroup FALCON_Vec3_Equality Equality
                 *   @defgroup FALCON_Vec3_Comparison Comparisons
                 *   @defgroup FALCON_Vec3_Product Geometric Products
                 *   @defgroup FALCON_Vec3_Mag Vector Magnitude and Norms
                 *   @defgroup FALCON_Vec3_Dist Vector Distance
                 *   @defgroup FALCON_Vec3_Normalize Vector Normalization
                 *   @defgroup FALCON_Vec3_Proj Vector Projection and Rejection
                 *   @defgroup FALCON_Vec3_Alias Spatial Alias
                 *   @defgroup FALCON_Vec3_Log String Representation
                 *   @defgroup FALCON_Vec3_Const Vector Constants
                 *   @defgroup FALCON_Vec3_Utils Vector Utilities
                 *   @defgroup FALCON_Vec3_Swizzle Vector Swizzling
                 *   @defgroup FALCON_Vec3_Ptr Internal Storage Access
                 * @}
                 */

                /**
                 * @defgroup FALCON_Vec4 4D Vectors
                 * @brief 4-dimensional Euclidean vectors.
                 * @ingroup FALCON_Vectors
                 * @{
                 *   @defgroup FALCON_Vec4_Members Class Members
                 *   @defgroup FALCON_Vec4_Init Constructors
                 *   @defgroup FALCON_Vec4_Access Accessors
                 *   @defgroup FALCON_Vec4_Arithmetic Arithmetic Operations
                 *   @defgroup FALCON_Vec4_Bitwise Boolean Bitwise Operations
                 *   @defgroup FALCON_Vec4_Equality Equality
                 *   @defgroup FALCON_Vec4_Comparison Comparisons
                 *   @defgroup FALCON_Vec4_Product Geometric Products
                 *   @defgroup FALCON_Vec4_Mag Vector Magnitude and Norms
                 *   @defgroup FALCON_Vec4_Dist Vector Distance
                 *   @defgroup FALCON_Vec4_Normalize Vector Normalization
                 *   @defgroup FALCON_Vec4_Proj Vector Projection and Rejection
                 *   @defgroup FALCON_Vec4_Alias Spatial Alias
                 *   @defgroup FALCON_Vec4_Log String Representation
                 *   @defgroup FALCON_Vec4_Const Vector Constants
                 *   @defgroup FALCON_Vec4_Utils Vector Utilities
                 *   @defgroup FALCON_Vec4_Swizzle Vector Swizzling
                 *   @defgroup FALCON_Vec4_Ptr Internal Storage Access
                 * @}
                 */

            /** @} */ // FALCON_Vectors

        /** @} */ // FALCON_Core_SIMD


        /**
         * @defgroup FALCON_Core_Const Compile-time Math (Scalar).
         * @brief Fundamental mathematical structures with constexpr evaluation and auto-vectorization.
         * @ingroup FALCON_Core
         * @{
         */

            /**
             * @defgroup FALCON_Vectors Vectors
             * @brief N-dimensional Euclidean vector implementations.
             * @ingroup FALCON_Core_Const
             * @{
             */

                /**
                 * @defgroup FALCON_Point 2D Point
                 * @brief 2-dimensional point with an implicit z-value of 1.
                 * @ingroup FALCON_Vectors
                 * @{
                 *   @defgroup FALCON_Point2_Init Constructors
                 *   @defgroup FALCON_Point2_Arithmetic Arithmetic Operations
                 * @}
                 */

                /**
                 * @defgroup FALCON_Point 3D Point
                 * @brief 3-dimensional point with an implicit w-value of 1.
                 * @ingroup FALCON_Vectors
                 * @{
                 *   @defgroup FALCON_Point3_Init Constructors
                 *   @defgroup FALCON_Point3_Arithmetic Arithmetic Operations
                 * @}
                 */

                /**
                 * @defgroup FALCON_CVec2 2D Vectors
                 * @brief 2-dimensional Euclidean vectors.
                 * @ingroup FALCON_Vectors
                 * @{
                 *   @defgroup FALCON_CVec2_Members Class Members
                 *   @defgroup FALCON_CVec2_Init Constructors
                 *   @defgroup FALCON_CVec2_Access Accessors
                 *   @defgroup FALCON_CVec2_Arithmetic Arithmetic Operations
                 *   @defgroup FALCON_CVec2_Bitwise Boolean Bitwise Operations
                 *   @defgroup FALCON_CVec2_Equality Equality
                 *   @defgroup FALCON_CVec2_Comparison Comparisons
                 *   @defgroup FALCON_CVec2_Product Geometric Products
                 *   @defgroup FALCON_CVec2_Mag Vector Magnitude and Norms
                 *   @defgroup FALCON_CVec2_Dist Vector Distance
                 *   @defgroup FALCON_CVec2_Normalize Vector Normalization
                 *   @defgroup FALCON_CVec2_Proj Vector Projection and Rejection
                 *   @defgroup FALCON_CVec2_Alias Spatial Alias
                 *   @defgroup FALCON_CVec2_Log String Representation
                 *   @defgroup FALCON_CVec2_Const Vector Constants
                 *   @defgroup FALCON_CVec2_Utils Vector Utilities
                 *   @defgroup FALCON_CVec2_Swizzle Vector Swizzling
                 *   @defgroup FALCON_CVec2_Ptr Internal Storage Access
                 * @}
                 */

                /**
                 * @defgroup FALCON_Vec3 3D Vectors
                 * @brief 3-dimensional Euclidean vectors.
                 * @ingroup FALCON_Vectors
                 * @{
                 *   @defgroup FALCON_CVec3_Members Class Members
                 *   @defgroup FALCON_CVec3_Init Constructors
                 *   @defgroup FALCON_CVec3_Access Accessors
                 *   @defgroup FALCON_CVec3_Arithmetic Arithmetic Operations
                 *   @defgroup FALCON_CVec3_Bitwise Boolean Bitwise Operations
                 *   @defgroup FALCON_CVec3_Equality Equality
                 *   @defgroup FALCON_CVec3_Comparison Comparisons
                 *   @defgroup FALCON_CVec3_Product Geometric Products
                 *   @defgroup FALCON_CVec3_Mag Vector Magnitude and Norms
                 *   @defgroup FALCON_CVec3_Dist Vector Distance
                 *   @defgroup FALCON_CVec3_Normalize Vector Normalization
                 *   @defgroup FALCON_CVec3_Proj Vector Projection and Rejection
                 *   @defgroup FALCON_CVec3_Alias Spatial Alias
                 *   @defgroup FALCON_CVec3_Log String Representation
                 *   @defgroup FALCON_CVec3_Const Vector Constants
                 *   @defgroup FALCON_CVec3_Utils Vector Utilities
                 *   @defgroup FALCON_CVec3_Swizzle Vector Swizzling
                 *   @defgroup FALCON_CVec3_Ptr Internal Storage Access
                 * @}
                 */

                /**
                 * @defgroup FALCON_Vec4 4D Vectors
                 * @brief 4-dimensional Euclidean vectors.
                 * @ingroup FALCON_Vectors
                 * @{
                 *   @defgroup FALCON_CVec4_Members Class Members
                 *   @defgroup FALCON_CVec4_Init Constructors
                 *   @defgroup FALCON_CVec4_Access Accessors
                 *   @defgroup FALCON_CVec4_Arithmetic Arithmetic Operations
                 *   @defgroup FALCON_CVec4_Bitwise Boolean Bitwise Operations
                 *   @defgroup FALCON_CVec4_Equality Equality
                 *   @defgroup FALCON_CVec4_Comparison Comparisons
                 *   @defgroup FALCON_CVec4_Product Geometric Products
                 *   @defgroup FALCON_CVec4_Mag Vector Magnitude and Norms
                 *   @defgroup FALCON_CVec4_Dist Vector Distance
                 *   @defgroup FALCON_CVec4_Normalize Vector Normalization
                 *   @defgroup FALCON_CVec4_Proj Vector Projection and Rejection
                 *   @defgroup FALCON_CVec4_Alias Spatial Alias
                 *   @defgroup FALCON_CVec4_Log String Representation
                 *   @defgroup FALCON_CVec4_Const Vector Constants
                 *   @defgroup FALCON_CVec4_Utils Vector Utilities
                 *   @defgroup FALCON_CVec4_Swizzle Vector Swizzling
                 *   @defgroup FALCON_CVec4_Ptr Internal Storage Access
                 * @}
                 */

            /** @} */ // FALCON_Vectors

        /** @} */

        /**
         * @defgroup FALCON_Matrices Matrices
         * @brief MxN-dimensional Matrix implementations.
         * @ingroup FALCON_Core
         * @{
         */
            
            /**
             * @defgroup FALCON_Mat2x2 2x2 Square Matrix
             * @brief 2x2 Square Matrix.
             * @ingroup FALCON_Matrices
             * @{
             *   @defgroup FALCON_Mat2x2_Members Class Members
             *   @defgroup FALCON_Mat2x2_Init Constructors
             *   @defgroup FALCON_Mat2x2_Access Accessors
             *   @defgroup FALCON_Mat2x2_Arithmetic Arithmetic Operations
             *   @defgroup FALCON_Mat2x2_Algebra Matrix Algebra
             *   @defgroup FALCON_Mat2x2_Equality Equality
             *   @defgroup FALCON_Mat2x2_Geom Geometric Operations
             *   @defgroup FALCON_Mat2x2_Comp Matrix Compositions
             *   @defgroup FALCON_Mat2x2_Log String Representation
             *   @defgroup FALCON_Mat2x2_Const Matrix Constants
             *   @defgroup FALCON_Mat2x2_Utils Matrix Utilities
             *   @defgroup FALCON_Mat2x2_Transforms Matrix Transformation Factories
             * @}
             */


            /**
             * @defgroup FALCON_Mat2x3 2x3 Matrix
             * @brief 2x3 Matrix.
             * @ingroup FALCON_Matrices
             * @{
             *   @defgroup FALCON_Mat2x3_Members Class Members
             *   @defgroup FALCON_Mat2x3_Init Constructors
             *   @defgroup FALCON_Mat2x3_Access Accessors
             *   @defgroup FALCON_Mat2x3_Arithmetic Arithmetic Operations
             *   @defgroup FALCON_Mat2x3_Algebra Matrix Algebra
             *   @defgroup FALCON_Mat2x3_Equality Equality
             *   @defgroup FALCON_Mat2x3_Geom Geometric Operations
             *   @defgroup FALCON_Mat2x3_Comp Matrix Compositions
             *   @defgroup FALCON_Mat2x3_Log String Representation
             *   @defgroup FALCON_Mat2x3_Const Matrix Constants
             *   @defgroup FALCON_Mat2x3_Utils Matrix Utilities
             *   @defgroup FALCON_Mat2x3_Transforms Matrix Transformation Factories
             * @}
             */


            /**
             * @defgroup FALCON_Mat2x4 2x4 Matrix
             * @brief 2x4 Matrix.
             * @ingroup FALCON_Matrices
             * @{
             *   @defgroup FALCON_Mat2x4_Members Class Members
             *   @defgroup FALCON_Mat2x4_Init Constructors
             *   @defgroup FALCON_Mat2x4_Access Accessors
             *   @defgroup FALCON_Mat2x4_Arithmetic Arithmetic Operations
             *   @defgroup FALCON_Mat2x4_Algebra Matrix Algebra
             *   @defgroup FALCON_Mat2x4_Equality Equality
             *   @defgroup FALCON_Mat2x4_Geom Geometric Operations
             *   @defgroup FALCON_Mat2x4_Comp Matrix Compositions
             *   @defgroup FALCON_Mat2x4_Log String Representation
             *   @defgroup FALCON_Mat2x4_Const Matrix Constants
             *   @defgroup FALCON_Mat2x4_Utils Matrix Utilities
             *   @defgroup FALCON_Mat2x4_Transforms Matrix Transformation Factories
             * @}
             */


            /**
            * @defgroup FALCON_Mat3x2 3x2 Matrix
            * @brief 3x2 Matrix.
            * @ingroup FALCON_Matrices
            * @{
            *   @defgroup FALCON_Mat3x2_Members Class Members
            *   @defgroup FALCON_Mat3x2_Init Constructors
            *   @defgroup FALCON_Mat3x2_Access Accessors
            *   @defgroup FALCON_Mat3x2_Arithmetic Arithmetic Operations
            *   @defgroup FALCON_Mat3x2_Algebra Matrix Algebra
            *   @defgroup FALCON_Mat3x2_Equality Equality
            *   @defgroup FALCON_Mat3x2_Geom Geometric Operations
            *   @defgroup FALCON_Mat3x2_Comp Matrix Compositions
            *   @defgroup FALCON_Mat3x2_Log String Representation
            *   @defgroup FALCON_Mat3x2_Const Matrix Constants
            *   @defgroup FALCON_Mat3x2_Utils Matrix Utilities
            *   @defgroup FALCON_Mat3x2_Transforms Matrix Transformation Factories
            * @}
            */


            /**
             * @defgroup FALCON_Mat3x3 3x3 Square Matrix
             * @brief 3x3 Square Matrix.
             * @ingroup FALCON_Matrices
             * @{
             *   @defgroup FALCON_Mat3x3_Members Class Members
             *   @defgroup FALCON_Mat3x3_Init Constructors
             *   @defgroup FALCON_Mat3x3_Access Accessors
             *   @defgroup FALCON_Mat3x3_Arithmetic Arithmetic Operations
             *   @defgroup FALCON_Mat3x3_Algebra Matrix Algebra
             *   @defgroup FALCON_Mat3x3_Equality Equality
             *   @defgroup FALCON_Mat3x3_Geom Geometric Operations
             *   @defgroup FALCON_Mat3x3_Comp Matrix Compositions
             *   @defgroup FALCON_Mat3x3_Log String Representation
             *   @defgroup FALCON_Mat3x3_Const Matrix Constants
             *   @defgroup FALCON_Mat3x3_Utils Matrix Utilities
             *   @defgroup FALCON_Mat3x3_Transforms Matrix Transformation Factories
             * @}
             */


            /**
            * @defgroup FALCON_Mat3x4 3x4 Matrix
            * @brief 3x4 Matrix.
            * @ingroup FALCON_Matrices
            * @{
            *   @defgroup FALCON_Mat3x4_Members Class Members
            *   @defgroup FALCON_Mat3x4_Init Constructors
            *   @defgroup FALCON_Mat3x4_Access Accessors
            *   @defgroup FALCON_Mat3x4_Arithmetic Arithmetic Operations
            *   @defgroup FALCON_Mat3x4_Algebra Matrix Algebra
            *   @defgroup FALCON_Mat3x4_Equality Equality
            *   @defgroup FALCON_Mat3x4_Geom Geometric Operations
            *   @defgroup FALCON_Mat3x4_Comp Matrix Compositions
            *   @defgroup FALCON_Mat3x4_Log String Representation
            *   @defgroup FALCON_Mat3x4_Const Matrix Constants
            *   @defgroup FALCON_Mat3x4_Utils Matrix Utilities
            * @}
            */


            /**
             * @defgroup FALCON_Mat4x2 4x2 Matrix
             * @brief 4x2 Matrix.
             * @ingroup FALCON_Matrices
             * @{
             *   @defgroup FALCON_Mat4x2_Members Class Members
             *   @defgroup FALCON_Mat4x2_Init Constructors
             *   @defgroup FALCON_Mat4x2_Access Accessors
             *   @defgroup FALCON_Mat4x2_Arithmetic Arithmetic Operations
             *   @defgroup FALCON_Mat4x2_Algebra Matrix Algebra
             *   @defgroup FALCON_Mat4x2_Equality Equality
             *   @defgroup FALCON_Mat4x2_Geom Geometric Operations
             *   @defgroup FALCON_Mat4x2_Comp Matrix Compositions
             *   @defgroup FALCON_Mat4x2_Log String Representation
             *   @defgroup FALCON_Mat4x2_Const Matrix Constants
             *   @defgroup FALCON_Mat4x2_Utils Matrix Utilities
             * @}
             */


            /**
             * @defgroup FALCON_Mat4x3 4x3 Matrix
             * @brief 4x3 Matrix.
             * @ingroup FALCON_Matrices
             * @{
             *   @defgroup FALCON_Mat4x3_Members Class Members
             *   @defgroup FALCON_Mat4x3_Init Constructors
             *   @defgroup FALCON_Mat4x3_Access Accessors
             *   @defgroup FALCON_Mat4x3_Arithmetic Arithmetic Operations
             *   @defgroup FALCON_Mat4x3_Equality Equality
             *   @defgroup FALCON_Mat4x3_Geom Geometric Operations
             *   @defgroup FALCON_Mat4x3_Comp Matrix Compositions
             *   @defgroup FALCON_Mat4x3_Log String Representation
             *   @defgroup FALCON_Mat4x3_Const Matrix Constants
             *   @defgroup FALCON_Mat4x3_Utils Matrix Utilities
             * @}
             */


            /**
             * @defgroup FALCON_Mat4x4 4x4 Square Matrix
             * @brief 4x4 Square Matrix.
             * @ingroup FALCON_Matrices
             * @{
             *   @defgroup FALCON_Mat4x4_Members Class Members
             *   @defgroup FALCON_Mat4x4_Init Constructors
             *   @defgroup FALCON_Mat4x4_Access Accessors
             *   @defgroup FALCON_Mat4x4_Arithmetic Arithmetic Operations
             *   @defgroup FALCON_Mat4x4_Algebra Matrix Algebra
             *   @defgroup FALCON_Mat4x4_Equality Equality
             *   @defgroup FALCON_Mat4x4_Geom Geometric Products
             *   @defgroup FALCON_Mat4x4_Comp Matrix Compositions
             *   @defgroup FALCON_Mat4x4_Log String Representation
             *   @defgroup FALCON_Mat4x4_Const Matrix Constants
             *   @defgroup FALCON_Mat4x4_Utils Matrix Utilities
             *   @defgroup FALCON_Mat4x4_Transforms Matrix Transformation Factories
             * @}
             */


            /**
            * @defgroup FALCON_Transform4 4x4 Transformation Matrix
            * @brief 4D Matrix used for transformation with inherent assumption that last row is <0, 0, 0, 1>.
            * @ingroup FALCON_Matrices
            * @{
            *   @defgroup FALCON_Transform4_Init Constructors
            *   @defgroup FALCON_Transform4_Access Accessors
            *   @defgroup FALCON_Transform4_Arithmetic Arithmetic Operations
            *   @defgroup FALCON_Transform4_Algebra Matrix Algebra
            *   @defgroup FALCON_Transform4_Equality Equality
            *   @defgroup FALCON_Transform4_Geom Geometric Products
            *   @defgroup FALCON_Transform4_Comp Matrix Compositions
            *   @defgroup FALCON_Transform4_Log String Representation
            *   @defgroup FALCON_Transform4_Const Matrix Constants
            *   @defgroup FALCON_Transform4_Utils Matrix Utilities
            *   @defgroup FALCON_Transform4_Transforms Matrix Transformation Factories
            * @}
            */
        
        /** @} */ // FALCON_Matrices

        /**
        * @defgroup FALCON_Quaternion Quaternions
        * @brief Quaternions
        * @ingroup FALCON_Core
        * @{
        *   @defgroup FALCON_Quaternion_Members Class Members
        *   @defgroup FALCON_Quaternion_Init Constructors
        *   @defgroup FALCON_Quaternion_Access Accessors
        *   @defgroup FALCON_Quaternion_Arithmetic Arithmetic Operations
        *   @defgroup FALCON_Quaternion_Algebra Quaternion Algebra
        *   @defgroup FALCON_Quaternion_Calculus Quaternion Calculus(Analysis)
        *   @defgroup FALCON_Quaternion_Vector_Algebra Quaternion-Vector Algebra
        *   @defgroup FALCON_Quaternion_Equality Equality
        *   @defgroup FALCON_Quaternion_Comparison Comparisons
        *   @defgroup FALCON_Quaternion_Product Geometric Products
        *   @defgroup FALCON_Quaternion_Mag Quaternion Magnitude
        *   @defgroup FALCON_Quaternion_Log String Representation
        *   @defgroup FALCON_Quaternion_Const Quaternion Constants
        * @}
        */

    /** @} */ // End of FALCON_Core

    /**
     * @defgroup FALCON_Concepts Concepts
     * @brief Fundamental mathematical constraints.
     * @ingroup FALCON_Math
     */

    /**
     * @defgroup FALCON_Header_Alias Header Alias
     * @brief Header Alias for FALCON Mathematical structures for easier include and access.
     * @ingroup FALCON_Math
     */

    /**
     * @defgroup FALCON_Types Type Alias
     * @brief Extended Type Alias.
     * @ingroup FALCON_Math
     */
    
    /**
     * @defgroup FALCON_Math_Config Library Configuration
     * @brief Configurations that dictate certain library behaviors.
     * @ingroup FALCON_Math
     */

    /**
     * @defgroup FALCON_Math_Constants Library Constants
     * @brief Constants defined in FALCON.
     * @ingroup FALCON_Math
     */

    /**
     * @defgroup FALCON_Math_Common Library Utilities
     * @brief Common utilities used by FALCON.
     * @ingroup FALCON_Math
     */

    /**
     * @defgroup FALCON_Wrappers Wrapper Functions
     * @brief Wrapper for `std` functions to enable compile time evaluation in pre-C++23/26.
     * @ingroup FALCON_Math
     */

    /**
     * @defgroup FALCON_Macro Preprocessor Macros
     * @brief Preprocessor macro for assertions and compiler intrinsic debug breaks.
     * @ingroup FALCON_Math
     */

    /**
     * @defgroup FALCON_Messages Messages
     * @brief Central repository for all library string resources.
     * @ingroup FALCON_Math
     */

    /**
     * @defgroup FALCON_Utils Utility functions
     * @brief Helper utilities for FALCON.
     * @ingroup FALCON_Math
     */

/** @} */ // End of FALCON_Math

// clang-format on
