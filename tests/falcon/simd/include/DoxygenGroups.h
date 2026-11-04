#pragma once
/**
 * @file DoxygenGroups.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 18, 2026
 *
 * @brief Doxygen groups for organizing FALCON SIMD test harness.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


// clang-format off
/**
 * @defgroup SIMD_Test_Suite Falcon SIMD Test Suite
 * @brief Falcon SIMD Library Test Suite.
 * @{
 */

    /**
     * @defgroup T_SIMD_Reg SIMD Register Types
     * @brief Verifies the wrapper for x86/ARM(Not supported yet) registers.
     * @ingroup T_SIMD_Reg.
     */

    /**
     * @defgroup T_SIMD_Utils Utility Tests
     * @brief Validates logic of all SIMD utility functions.
     * @ingroup T_SIMD_Reg.
     */

    /**
     * @defgroup T_SIMD128 Simd 128 Tests
     * @brief Verifies functions provided by Simd128
     * @ingroup T_SIMD_Reg.
     *
     * @{
     *   @defgroup T_SIMD128_Arithmetic Arithmetic Tests
     *   @defgroup T_SIMD128_Ctor Constructor Tests
     *   @defgroup T_SIMD128_ConvCtor Conversion Constructors Tests
     *   @defgroup T_SIMD128_Get_Set Getters/Setters Tests
     *   @defgroup T_SIMD128_Load_Store Load/Store Tests
     *   @defgroup T_SIMD128_Cmp Comparison operation Tests(>, <, >=, <=, ==, !=)
     *   @defgroup T_SIMD128_Bit Bitwise operation Tests(>, <, >=, <=, ==, !=)
     *   @defgroup T_SIMD128_Permute Permutation and Blending Operations
     *   @defgroup T_SIMD128_Utils Simd Utilities.
     *   @defgroup T_SIMD128_Math Basic Math Operations(min, max, abs...).
     * @}
    */


    /**
     * @defgroup T_SIMD256 Simd 256 Tests
     * @brief Verifies functions provided by Simd256
     * @ingroup T_SIMD_Reg.
     *
     * @{
     *   @defgroup T_SIMD256_Arithmetic Arithmetic Tests
     *   @defgroup T_SIMD256_Ctor Constructor Tests
     *   @defgroup T_SIMD256_ConvCtor Conversion Constructors Tests
     *   @defgroup T_SIMD256_Get_Set Getters/Setters Tests
     *   @defgroup T_SIMD256_Load_Store Load/Store Tests
     *   @defgroup T_SIMD256_Cmp Comparison operation Tests(>, <, >=, <=, ==, !=)
     *   @defgroup T_SIMD256_Bit Bitwise operation Tests(>, <, >=, <=, ==, !=)
     *   @defgroup T_SIMD256_Permute Permutation and Blending Operations
     *   @defgroup T_SIMD256_Utils Simd Utilities.
     *   @defgroup T_SIMD256_Math Basic Math Operations(min, max, abs...).
     * @}
     */


    /**
     * @defgroup T_SIMD512 Simd 512 Tests
     * @brief Verifies functions provided by Simd512
     * @ingroup T_SIMD_Reg.
     *
     * @{
     *   @defgroup T_SIMD512_Arithmetic Arithmetic Tests
     *   @defgroup T_SIMD512_Ctor Constructor Tests
     *   @defgroup T_SIMD512_ConvCtor Conversion Constructors Tests
     *   @defgroup T_SIMD512_Get_Set Getters/Setters Tests
     *   @defgroup T_SIMD512_Load_Store Load/Store Tests
     *   @defgroup T_SIMD512_Cmp Comparison operation Tests(>, <, >=, <=, ==, !=)
     *   @defgroup T_SIMD512_Bit Bitwise operation Tests(>, <, >=, <=, ==, !=)
     *   @defgroup T_SIMD512_Permute Permutation and Blending Operations
     *   @defgroup T_SIMD512_Utils Simd Utilities.
     *   @defgroup T_SIMD512_Math Basic Math Operations(min, max, abs...).
     * @}
     */

    /** @} */ // End of T_SIMD128


/** @} */ // End of SIMD_Test_Suite

// clang-format on
