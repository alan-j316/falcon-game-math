#pragma once
/**
 * @file DoxygenGroups.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 18, 2026
 *
 * @brief Doxygen groups for organizing FALCON Math test harness.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


// clang-format off
/**
 * @defgroup FALCONTestSuite Test Suite
 * @brief Master test suite for Falcon Game Math Library.
 * @{
 */
    
    /**
     * @defgroup MathTests Mathematics
     * @brief Test suite for mathematical components.
     * @ingroup FALCONTestSuite
     * @{
     */

        /**
         * @defgroup VectorTests Vectors
         * @brief Test suite for vectors.
         * @ingroup MathTests
         * @{
         */

            /**
             * @defgroup FALCON_CVec2_Tests Constexpr-Capable 2D Vector Tests
             * @brief Verification of 2D Euclidean vector operations.
             * @ingroup VectorTests
             * @{
             *   @defgroup T_FALCON_CVec2_Access Component Access and Mutation
             *   @defgroup T_FALCON_CVec2_Alias Spatial Aliasing
             *   @defgroup T_FALCON_CVec2_Const Vector Constants
             *   @defgroup T_FALCON_CVec2_Arithmetic Arithmetic Operations(+, -, *, /)
             *   @defgroup T_FALCON_CVec2_Bool_Bit Boolean Bitwise Operation
             *   @defgroup T_FALCON_CVec2_Comp Vector Comparisons(>, >=, <, <=)
             *   @defgroup T_FALCON_CVec2_Equality Component-wise and Masked Equality and Inequality
             *   @defgroup T_FALCON_CVec2_Init Initialization
             *   @defgroup T_FALCON_CVec2_Magnitude Scalar Length(Magnitude)
             *   @defgroup T_FALCON_CVec2_Norm P-Norm (Length)
             *   @defgroup T_FALCON_CVec2_Dist Vector Distance
             *   @defgroup T_FALCON_CVec2_Normalize Vector Normalization
             *   @defgroup T_FALCON_CVec2_Product Dot and Cross Product
             *   @defgroup T_FALCON_CVec2_Proj Vector Projection
             *   @defgroup T_FALCON_CVec2_Rej Vector Rejection
             *   @defgroup T_FALCON_CVec2_String_Repr Formatted String Representation
             *   @defgroup T_FALCON_CVec2_Type_Conv Conversion Constructor
             *   @defgroup T_FALCON_CVec2_Negation Negation(-)
             *   @defgroup T_FALCON_CVec2_Utils Vector Utilities
             *   @defgroup T_FALCON_CVec2_Swizzle Vector Swizzling
             *   @defgroup T_FALCON_CVec2_Ptr Internal Storage Access(Raw Pointer)
             * @}
             */

            /**
              * @defgroup FALCON_Vec2_Tests Simd-Accelerated 2D Vector Tests
              * @brief Verification of 2D Euclidean vector operations(Simd-Accelerated).
              * @ingroup VectorTests
              * @{
              *   @defgroup T_FALCON_Vec2_Access Component Access and Mutation
              *   @defgroup T_FALCON_Vec2_Alias Spatial Aliasing
              *   @defgroup T_FALCON_Vec2_Const Vector Constants
              *   @defgroup T_FALCON_Vec2_Arithmetic Arithmetic Operations(+, -, *, /)
              *   @defgroup T_FALCON_Vec2_Bool_Bit Boolean Bitwise Operation
              *   @defgroup T_FALCON_Vec2_Comp Vector Comparisons(>, >=, <, <=)
              *   @defgroup T_FALCON_Vec2_Equality Component-wise and Masked Equality and Inequality
              *   @defgroup T_FALCON_Vec2_Init Initialization
              *   @defgroup T_FALCON_Vec2_Magnitude Scalar Length(Magnitude)
              *   @defgroup T_FALCON_Vec2_Norm P-Norm (Length)
              *   @defgroup T_FALCON_Vec2_Dist Vector Distance
              *   @defgroup T_FALCON_Vec2_Normalize Vector Normalization
              *   @defgroup T_FALCON_Vec2_Product Dot and Cross Product
              *   @defgroup T_FALCON_Vec2_Proj Vector Projection
              *   @defgroup T_FALCON_Vec2_Rej Vector Rejection
              *   @defgroup T_FALCON_Vec2_String_Repr Formatted String Representation
              *   @defgroup T_FALCON_Vec2_Type_Conv Conversion Constructor
              *   @defgroup T_FALCON_Vec2_Negation Negation(-)
              *   @defgroup T_FALCON_Vec2_Utils Vector Utilities
              *   @defgroup T_FALCON_Vec2_Swizzle Vector Swizzling
              *   @defgroup T_FALCON_Vec2_Ptr Internal Storage Access(Raw Pointer)
              *   @defgroup T_FALCON_Vec2_Conv Constexpr Vec to SIMD Accelerated Vec conversion.
              * @}
              */


            /**
             * @defgroup FALCON_Vec3_Tests 3D Vector Tests
             * @brief Verification of 3D Euclidean vector operations.
             * @ingroup VectorTests
             * @{
             *   @defgroup T_FALCON_Vec3_Access Component Access and Mutation
             *   @defgroup T_FALCON_Vec3_Alias Spatial Aliasing
             *   @defgroup T_FALCON_Vec3_Const Vector Constants
             *   @defgroup T_FALCON_Vec3_Arithmetic Arithmetic Operations(+, -, *, /)
             *   @defgroup T_FALCON_Vec3_Bool_Bit Boolean Bitwise Operation
             *   @defgroup T_FALCON_Vec3_Comp Vector Comparisons(>, >=, <, <=)
             *   @defgroup T_FALCON_Vec3_Equality Component-wise and Masked Equality and Inequality
             *   @defgroup T_FALCON_Vec3_Init Initialization
             *   @defgroup T_FALCON_Vec3_Magnitude Scalar Length(Magnitude)
             *   @defgroup T_FALCON_Vec3_Norm P-Norm (Length)
             *   @defgroup T_FALCON_Vec3_Dist Vector Distance
             *   @defgroup T_FALCON_Vec3_Normalize Vector Normalization
             *   @defgroup T_FALCON_Vec3_Product Dot and Cross Product
             *   @defgroup T_FALCON_Vec3_Proj Vector Projection
             *   @defgroup T_FALCON_Vec3_Rej Vector Rejection
             *   @defgroup T_FALCON_Vec3_String_Repr Formatted String Representation
             *   @defgroup T_FALCON_Vec3_Type_Conv Conversion Constructor
             *   @defgroup T_FALCON_Vec3_Negation Negation(-)
             *   @defgroup T_FALCON_Vec3_Utils Vector Utilities
             *   @defgroup T_FALCON_Vec3_Swizzle Vector Swizzling
             *   @defgroup T_FALCON_Vec3_Ptr Internal Storage Access(Raw Pointer)
             *   @defgroup T_FALCON_Vec3_Conv Constexpr Vec to SIMD Accelerated Vec conversion.
             * @}
             */


            /**
             * @defgroup FALCON_Vec4_Tests 4D Vector Tests
             * @brief Verification of 4D Euclidean vector operations.
             * @ingroup VectorTests
             * @{
             *   @defgroup T_FALCON_Vec4_Access Component Access and Mutation
             *   @defgroup T_FALCON_Vec4_Alias Spatial Aliasing
             *   @defgroup T_FALCON_Vec4_Const Vector Constants
             *   @defgroup T_FALCON_Vec4_Arithmetic Arithmetic Operations(+, -, *, /)
             *   @defgroup T_FALCON_Vec4_Bool_Bit Boolean Bitwise Operation
             *   @defgroup T_FALCON_Vec4_Comp Vector Comparisons(>, >=, <, <=)
             *   @defgroup T_FALCON_Vec4_Equality Component-wise and Masked Equality and Inequality
             *   @defgroup T_FALCON_Vec4_Init Initialization
             *   @defgroup T_FALCON_Vec4_Magnitude Scalar Length(Magnitude)
             *   @defgroup T_FALCON_Vec4_Norm P-Norm (Length)
             *   @defgroup T_FALCON_Vec4_Dist Vector Distance
             *   @defgroup T_FALCON_Vec4_Normalize Vector Normalization
             *   @defgroup T_FALCON_Vec4_Product Dot Product
             *   @defgroup T_FALCON_Vec4_Proj Vector Projection
             *   @defgroup T_FALCON_Vec4_Rej Vector Rejection
             *   @defgroup T_FALCON_Vec4_String_Repr Formatted String Representation
             *   @defgroup T_FALCON_Vec4_Type_Conv Conversion Constructor
             *   @defgroup T_FALCON_Vec4_Negation Negation(-)
             *   @defgroup T_FALCON_Vec4_Utils Vector Utilities
             *   @defgroup T_FALCON_Vec4_Swizzle Vector Swizzling
             *   @defgroup T_FALCON_Vec4_Ptr Internal Storage Access(Raw Pointer)
             *   @defgroup T_FALCON_Vec4_Conv Constexpr Vec to SIMD Accelerated Vec conversion.
             * @}
             */

            /**
             * @defgroup FALCON_Point3_Tests 3D Point Tests
             * @brief Verification of 3D Point<x, y, z, w> operations.
             * @ingroup VectorTests
             * @{
             *   @defgroup T_FALCON_Point3_Addition Addition
             *   @defgroup T_FALCON_Point3_Subtraction Subtraction
             *   @defgroup T_FALCON_Point3_Init Initialization
             * @}
             */

        /** @} */ // End of VectorTests

    
        /**
         * @defgroup MatrixTests Matrices
         * @brief Test suite for vectors.
         * @ingroup MathTests
         * @{
         */
        
            /**
             * @defgroup FALCON_Mat2x2_Tests 2x2 Matrix Test Suite
             * @brief Verification of 2x2 square matrix operations.
             * @ingroup MatrixTests
             * @{
             *   @defgroup T_FALCON_Mat2x2_Access Component Access
             *   @defgroup T_FALCON_Mat2x2_Mutation Component Mutation
             *   @defgroup T_FALCON_Mat2x2_Alias Spatial Aliasing
             *   @defgroup T_FALCON_Mat2x2_Const Matrix Constants
             *   @defgroup T_FALCON_Mat2x2_Addition Addition
             *   @defgroup T_FALCON_Mat2x2_Subtraction Subtraction
             *   @defgroup T_FALCON_Mat2x2_Multiplication Scalar Multiplication
             *   @defgroup T_FALCON_Mat2x2_Division Scalar Division
             *   @defgroup T_FALCON_Mat2x2_Transpose Matrix Transpose
             *   @defgroup T_FALCON_Mat2x2_Inverse Matrix Inverse
             *   @defgroup T_FALCON_Mat2x2_Constant Matrix Constants
             *   @defgroup T_FALCON_Mat2x2_Equality Equality and Inequality
             *   @defgroup T_FALCON_Mat2x2_Init Initialization
             *   @defgroup T_FALCON_Mat2x2_String_Repr Formatted String Representation
             *   @defgroup T_FALCON_Mat2x2_Type_Conv Conversion Constructor
             *   @defgroup T_FALCON_Mat2x2_Negation Negation(-)
             *   @defgroup T_FALCON_Mat2x2_Det Determinants
             *   @defgroup T_FALCON_Mat2x2_Trace Trace
             *   @defgroup T_FALCON_Mat2x2_Transforms Transformation Factories
             *   @defgroup T_FALCON_Mat2x2_Utils Matrix Utilities
             *   @defgroup T_FALCON_Mat2x2_Assertion Matrix Death Tests
             * @}
             */

            /**
             * @defgroup FALCON_Mat2x3_Tests 2x3 Matrix Test Suite
             * @brief Verification of 2x3 matrix operations.
             * @ingroup MatrixTests
             * @{
             *   @defgroup T_FALCON_Mat2x3_Access Component Access
             *   @defgroup T_FALCON_Mat2x3_Mutation Component Mutation
             *   @defgroup T_FALCON_Mat2x3_Const Matrix Constants
             *   @defgroup T_FALCON_Mat2x3_Addition Addition
             *   @defgroup T_FALCON_Mat2x3_Subtraction Subtraction
             *   @defgroup T_FALCON_Mat2x3_Multiplication Scalar Multiplication
             *   @defgroup T_FALCON_Mat2x3_Comp Matrix Compositions
             *   @defgroup T_FALCON_Mat2x3_Geom Matrix Geometric Operations
             *   @defgroup T_FALCON_Mat2x3_Division Scalar Division
             *   @defgroup T_FALCON_Mat2x3_Transpose Matrix Transpose
             *   @defgroup T_FALCON_Mat2x3_Constant Matrix Constants
             *   @defgroup T_FALCON_Mat2x3_Equality Equality and Inequality
             *   @defgroup T_FALCON_Mat2x3_Init Initialization
             *   @defgroup T_FALCON_Mat2x3_String_Repr Formatted String Representation
             *   @defgroup T_FALCON_Mat2x3_Type_Conv Conversion Constructor
             *   @defgroup T_FALCON_Mat2x3_Negation Negation(-)
             *   @defgroup T_FALCON_Mat2x3_Utils Matrix Utilities
             *   @defgroup T_FALCON_Mat2x3_Assertion Matrix Death Tests
             * @}
             */

            /**
             * @defgroup FALCON_Mat2x4_Tests 2x4 Matrix Test Suite
             * @brief Verification of 2x4 matrix operations.
             * @ingroup MatrixTests
             * @{
             *   @defgroup T_FALCON_Mat2x4_Access Component Access
             *   @defgroup T_FALCON_Mat2x4_Mutation Component Mutation
             *   @defgroup T_FALCON_Mat2x4_Const Matrix Constants
             *   @defgroup T_FALCON_Mat2x4_Addition Addition
             *   @defgroup T_FALCON_Mat2x4_Subtraction Subtraction
             *   @defgroup T_FALCON_Mat2x4_Multiplication Scalar Multiplication
             *   @defgroup T_FALCON_Mat2x4_Comp Matrix Compositions
             *   @defgroup T_FALCON_Mat2x4_Geom Matrix Geometric Operations
             *   @defgroup T_FALCON_Mat2x4_Division Scalar Division
             *   @defgroup T_FALCON_Mat2x4_Transpose Matrix Transpose
             *   @defgroup T_FALCON_Mat2x4_Constant Matrix Constants
             *   @defgroup T_FALCON_Mat2x4_Equality Equality and Inequality
             *   @defgroup T_FALCON_Mat2x4_Init Initialization
             *   @defgroup T_FALCON_Mat2x4_String_Repr Formatted String Representation
             *   @defgroup T_FALCON_Mat2x4_Type_Conv Conversion Constructor
             *   @defgroup T_FALCON_Mat2x4_Negation Negation(-)
             *   @defgroup T_FALCON_Mat2x4_Utils Matrix Utilities
             *   @defgroup T_FALCON_Mat2x4_Assertion Matrix Death Tests
             * @}
             */


            /**
             * @defgroup FALCON_Mat3x2_Tests 3x2 Matrix Test Suite
             * @brief Verification of 3x2 matrix operations.
             * @ingroup MatrixTests
             * @{
             *   @defgroup T_FALCON_Mat3x2_Access Component Access
             *   @defgroup T_FALCON_Mat3x2_Mutation Component Mutation
             *   @defgroup T_FALCON_Mat3x2_Const Matrix Constants
             *   @defgroup T_FALCON_Mat3x2_Addition Addition
             *   @defgroup T_FALCON_Mat3x2_Subtraction Subtraction
             *   @defgroup T_FALCON_Mat3x2_Multiplication Scalar Multiplication
             *   @defgroup T_FALCON_Mat3x2_Comp Matrix Compositions
             *   @defgroup T_FALCON_Mat3x2_Geom Matrix Geometric Operations
             *   @defgroup T_FALCON_Mat3x2_Division Scalar Division
             *   @defgroup T_FALCON_Mat3x2_Transpose Matrix Transpose
             *   @defgroup T_FALCON_Mat3x2_Constant Matrix Constants
             *   @defgroup T_FALCON_Mat3x2_Equality Equality and Inequality
             *   @defgroup T_FALCON_Mat3x2_Init Initialization
             *   @defgroup T_FALCON_Mat3x2_String_Repr Formatted String Representation
             *   @defgroup T_FALCON_Mat3x2_Type_Conv Conversion Constructor
             *   @defgroup T_FALCON_Mat3x2_Negation Negation(-)
             *   @defgroup T_FALCON_Mat3x2_Utils Matrix Utilities
             *   @defgroup T_FALCON_Mat3x2_Assertion Matrix Death Tests
             * @}
             */

            /**
             * @defgroup FALCON_Mat3x3_Tests 3x3 Matrix Test Suite
             * @brief Verification of 3x3 square matrix operations.
             * @ingroup MatrixTests
             * @{
             *   @defgroup T_FALCON_Mat3x3_Access Component Access
             *   @defgroup T_FALCON_Mat3x3_Mutation Component Mutation
             *   @defgroup T_FALCON_Mat3x3_Alias Spatial Aliasing
             *   @defgroup T_FALCON_Mat3x3_Const Matrix Constants
             *   @defgroup T_FALCON_Mat3x3_Addition Addition
             *   @defgroup T_FALCON_Mat3x3_Subtraction Subtraction
             *   @defgroup T_FALCON_Mat3x3_Multiplication Scalar Multiplication
             *   @defgroup T_FALCON_Mat3x3_Division Scalar Division
             *   @defgroup T_FALCON_Mat3x3_Transpose Matrix Transpose
             *   @defgroup T_FALCON_Mat3x3_Inverse Matrix Inverse
             *   @defgroup T_FALCON_Mat3x3_Constant Matrix Constants
             *   @defgroup T_FALCON_Mat3x3_Equality Equality and Inequality
             *   @defgroup T_FALCON_Mat3x3_Init Initialization
             *   @defgroup T_FALCON_Mat3x3_String_Repr Formatted String Representation
             *   @defgroup T_FALCON_Mat3x3_Type_Conv Conversion Constructor
             *   @defgroup T_FALCON_Mat3x3_Negation Negation(-)
             *   @defgroup T_FALCON_Mat3x3_Det Determinants
             *   @defgroup T_FALCON_Mat3x3_Trace Trace
             *   @defgroup T_FALCON_Mat3x3_Transforms Transformation Factories
             *   @defgroup T_FALCON_Mat3x3_Utils Matrix Utilities
             *   @defgroup T_FALCON_Mat3x3_Assertion Matrix Death Tests
             * @}
             */

            /**
             * @defgroup FALCON_Mat3x4_Tests 3x4 Matrix Test Suite
             * @brief Verification of 3x4 matrix operations.
             * @ingroup MatrixTests
             * @{
             *   @defgroup T_FALCON_Mat3x4_Access Component Access
             *   @defgroup T_FALCON_Mat3x4_Mutation Component Mutation
             *   @defgroup T_FALCON_Mat3x4_Alias Spatial Aliasing
             *   @defgroup T_FALCON_Mat3x4_Const Matrix Constants
             *   @defgroup T_FALCON_Mat3x4_Addition Addition
             *   @defgroup T_FALCON_Mat3x4_Subtraction Subtraction
             *   @defgroup T_FALCON_Mat3x4_Multiplication Scalar Multiplication
             *   @defgroup T_FALCON_Mat3x4_Comp Matrix Compositions
             *   @defgroup T_FALCON_Mat3x4_Geom Matrix Geometric Operations
             *   @defgroup T_FALCON_Mat3x4_Division Scalar Division
             *   @defgroup T_FALCON_Mat3x4_Transpose Matrix Transpose
             *   @defgroup T_FALCON_Mat3x4_Inverse Matrix Inverse
             *   @defgroup T_FALCON_Mat3x4_Constant Matrix Constants
             *   @defgroup T_FALCON_Mat3x4_Equality Equality and Inequality
             *   @defgroup T_FALCON_Mat3x4_Init Initialization
             *   @defgroup T_FALCON_Mat3x4_String_Repr Formatted String Representation
             *   @defgroup T_FALCON_Mat3x4_Type_Conv Conversion Constructor
             *   @defgroup T_FALCON_Mat3x4_Negation Negation(-)
             *   @defgroup T_FALCON_Mat3x4_Det Determinants
             *   @defgroup T_FALCON_Mat3x4_Trace Trace
             *   @defgroup T_FALCON_Mat3x4_Utils Matrix Utilities
             *   @defgroup T_FALCON_Mat3x4_Assertion Matrix Death Tests
             * @}
             */


            /**
             * @defgroup FALCON_Mat4x2_Tests 4x2 Matrix Test Suite
             * @brief Verification of 4x2 matrix operations.
             * @ingroup MatrixTests
             * @{
             *   @defgroup T_FALCON_Mat4x2_Access Component Access
             *   @defgroup T_FALCON_Mat4x2_Mutation Component Mutation
             *   @defgroup T_FALCON_Mat4x2_Alias Spatial Aliasing
             *   @defgroup T_FALCON_Mat4x2_Const Matrix Constants
             *   @defgroup T_FALCON_Mat4x2_Addition Addition
             *   @defgroup T_FALCON_Mat4x2_Subtraction Subtraction
             *   @defgroup T_FALCON_Mat4x2_Multiplication Scalar Multiplication
             *   @defgroup T_FALCON_Mat4x2_Comp Matrix Compositions
             *   @defgroup T_FALCON_Mat4x2_Geom Matrix Geometric Operations
             *   @defgroup T_FALCON_Mat4x2_Division Scalar Division
             *   @defgroup T_FALCON_Mat4x2_Transpose Matrix Transpose
             *   @defgroup T_FALCON_Mat4x2_Inverse Matrix Inverse
             *   @defgroup T_FALCON_Mat4x2_Constant Matrix Constants
             *   @defgroup T_FALCON_Mat4x2_Equality Equality and Inequality
             *   @defgroup T_FALCON_Mat4x2_Init Initialization
             *   @defgroup T_FALCON_Mat4x2_String_Repr Formatted String Representation
             *   @defgroup T_FALCON_Mat4x2_Type_Conv Conversion Constructor
             *   @defgroup T_FALCON_Mat4x2_Negation Negation(-)
             *   @defgroup T_FALCON_Mat4x2_Det Determinants
             *   @defgroup T_FALCON_Mat4x2_Trace Trace
             *   @defgroup T_FALCON_Mat4x2_Utils Matrix Utilities
             *   @defgroup T_FALCON_Mat4x2_Assertion Matrix Death Tests
             * @}
             */


            /**
             * @defgroup FALCON_Mat4x3_Tests 4x3 Matrix Test Suite
             * @brief Verification of 4x3  matrix operations.
             * @ingroup MatrixTests
             * @{
             *   @defgroup T_FALCON_Mat4x3_Access Component Access
             *   @defgroup T_FALCON_Mat4x3_Mutation Component Mutation
             *   @defgroup T_FALCON_Mat4x3_Alias Spatial Aliasing
             *   @defgroup T_FALCON_Mat4x3_Const Matrix Constants
             *   @defgroup T_FALCON_Mat4x3_Addition Addition
             *   @defgroup T_FALCON_Mat4x3_Subtraction Subtraction
             *   @defgroup T_FALCON_Mat4x3_Multiplication Scalar Multiplication
             *   @defgroup T_FALCON_Mat4x3_Comp Matrix Compositions
             *   @defgroup T_FALCON_Mat4x3_Geom Matrix Geometric Operations
             *   @defgroup T_FALCON_Mat4x3_Division Scalar Division
             *   @defgroup T_FALCON_Mat4x3_Transpose Matrix Transpose
             *   @defgroup T_FALCON_Mat4x3_Inverse Matrix Inverse
             *   @defgroup T_FALCON_Mat4x3_Constant Matrix Constants
             *   @defgroup T_FALCON_Mat4x3_Equality Equality and Inequality
             *   @defgroup T_FALCON_Mat4x3_Init Initialization
             *   @defgroup T_FALCON_Mat4x3_String_Repr Formatted String Representation
             *   @defgroup T_FALCON_Mat4x3_Type_Conv Conversion Constructor
             *   @defgroup T_FALCON_Mat4x3_Negation Negation(-)
             *   @defgroup T_FALCON_Mat4x3_Det Determinants
             *   @defgroup T_FALCON_Mat4x3_Trace Trace
             *   @defgroup T_FALCON_Mat4x3_Utils Matrix Utilities
             *   @defgroup T_FALCON_Mat4x3_Assertion Matrix Death Tests
             * @}
             */


            /**
             * @defgroup FALCON_Mat4x4_Tests 4x4 Matrix Test Suite
             * @brief Verification of 4x4 square matrix operations.
             * @ingroup MatrixTests
             * @{
             *   @defgroup T_FALCON_Mat4x4_Access Component Access
             *   @defgroup T_FALCON_Mat4x4_Mutation Component Mutation
             *   @defgroup T_FALCON_Mat4x4_Alias Spatial Aliasing
             *   @defgroup T_FALCON_Mat4x4_Const Matrix Constants
             *   @defgroup T_FALCON_Mat4x4_Addition Addition
             *   @defgroup T_FALCON_Mat4x4_Subtraction Subtraction
             *   @defgroup T_FALCON_Mat4x4_Multiplication Scalar Multiplication
             *   @defgroup T_FALCON_Mat4x4_Division Scalar Division
             *   @defgroup T_FALCON_Mat4x4_Transpose Matrix Transpose
             *   @defgroup T_FALCON_Mat4x4_Inverse Matrix Inverse
             *   @defgroup T_FALCON_Mat4x4_Constant Matrix Constants
             *   @defgroup T_FALCON_Mat4x4_Equality Equality and Inequality
             *   @defgroup T_FALCON_Mat4x4_Init Initialization
             *   @defgroup T_FALCON_Mat4x4_String_Repr Formatted String Representation
             *   @defgroup T_FALCON_Mat4x4_Type_Conv Conversion Constructor
             *   @defgroup T_FALCON_Mat4x4_Negation Negation(-)
             *   @defgroup T_FALCON_Mat4x4_Det Determinants
             *   @defgroup T_FALCON_Mat4x4_Trace Trace
             *   @defgroup T_FALCON_Mat4x4_Transforms Transformation Factories
             *   @defgroup T_FALCON_Mat4x4_Utils Matrix Utilities
             *   @defgroup T_FALCON_Mat4x4_Assertion Matrix Death Tests
             * @}
             */

            /**
             * @defgroup FALCON_Transform4_Tests 4D Transformation Matrix Tests
             * @brief Verification of 4D transformation matrix operations.
             * @ingroup MatrixTests
             * @{
             *   @defgroup T_FALCON_Transform4_Access Component Access
             *   @defgroup T_FALCON_Transform4_Mutation Component Mutation
             *   @defgroup T_FALCON_Transform4_Alias Spatial Aliasing
             *   @defgroup T_FALCON_Transform4_Const Matrix Constants
             *   @defgroup T_FALCON_Transform4_Addition Addition
             *   @defgroup T_FALCON_Transform4_Subtraction Subtraction
             *   @defgroup T_FALCON_Transform4_Multiplication Scalar Multiplication
             *   @defgroup T_FALCON_Transform4_Division Scalar Division
             *   @defgroup T_FALCON_Transform4_Transpose Matrix Transpose
             *   @defgroup T_FALCON_Transform4_Inverse Matrix Inverse
             *   @defgroup T_FALCON_Transform4_Constant Matrix Constants
             *   @defgroup T_FALCON_Transform4_Equality Equality and Inequality
             *   @defgroup T_FALCON_Transform4_Init Initialization
             *   @defgroup T_FALCON_Transform4_String_Repr Formatted String Representation
             *   @defgroup T_FALCON_Transform4_Type_Conv Conversion Constructor
             *   @defgroup T_FALCON_Transform4_Negation Negation(-)
             *   @defgroup T_FALCON_Transform4_Det Determinants
             *   @defgroup T_FALCON_Transform4_Trace Trace
             *   @defgroup T_FALCON_Transform4_Transforms Transformation Factories
             *   @defgroup T_FALCON_Transform4_Utils Matrix Utilities
             * @}
             */

        /** @} */ // End of MatrixTests

        /**
         * @defgroup FALCON_Quaternion_Tests Quaternion Tests
         * @brief Verification of quaternion operations.
         * @ingroup VectorTests
         * @{
         *   @defgroup T_FALCON_Quaternion_Access_Mutate Component Access and Mutation
         *   @defgroup T_FALCON_Quaternion_Alias Spatial Aliasing
         *   @defgroup T_FALCON_Quaternion_Arithmetic Arithmetic Operations(+, -, *, /)
         *   @defgroup T_FALCON_Quaternion_Algebra Quaternion Algebra
         *   @defgroup T_FALCON_Quaternion_Calculus Quaternion Calculus(Analysis)
         *   @defgroup T_FALCON_Quaternion_Vector_Algebra Quaternion-Vector Algebra
         *   @defgroup T_FALCON_Quaternion_Bool_Bit Boolean Bitwise Operation
         *   @defgroup T_FALCON_Quaternion_Equality Component-wise, Masked and Vector Equality and Inequality
         *   @defgroup T_FALCON_Quaternion_Init Initialization
         *   @defgroup T_FALCON_Quaternion_Magnitude Scalar Length(Magnitude)
         *   @defgroup T_FALCON_Quaternion_String_Repr Formatted String Representation
         *   @defgroup T_FALCON_Quaternion_Type_Conv Conversion Constructor
         *   @defgroup T_FALCON_Quaternion_Negation Negation(-)
         *   @defgroup T_FALCON_Quaternion_Utils Quaternion Utilities
         * @}
         */

        /**
         * @defgroup FALCON_Common_Tests Common
         * @brief Verify general function operations exposed by FALCON library.
         * @ingroup MathTests
         * @{
         *   @defgroup T_Op_Status Operation Status
         *   @defgroup T_Wrappers Wrapper Utilities
         * @}
         */

        /**
        * @defgroup T_FALCON_Header_Alias Header Alias
        * @brief Verify FALCON Header Alias point to correct structs and functions.
        * @ingroup MathTests
        */

    /** @} */ // End of MathTests

    /**
     * @defgroup T_Utils Test Utilities
     * @brief Diagnostic and validation utilities for testing.
     * @ingroup FALCONTestSuite
     * @{
     *   @defgroup Vector_Utils Vector Validation Utilities
     *   @defgroup Matrix_Utils Matrix Validation Utilities
     * @}
     */


    /**
     * @defgroup T_Math_Traits Math Trait Static Tests
     * @brief Static tests verifying concepts and type alias.
     */


    /**
     * @defgroup T_FALCON_Trivial Class/Struct Triviality Tests
     * @brief Static tests verifying trivial behavior of classes and structs.
     */

    /**
     * @defgroup T_FALCON_Utils Utility Tests
     * @brief Validates logic of all fgm utility functions.
     */

/** @} */ // End of FALCONTestSuite
// clang-format on
