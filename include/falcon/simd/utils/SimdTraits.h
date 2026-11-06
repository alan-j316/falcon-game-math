#pragma once
/**
 * @file SimdTraits.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 12, 2026
 *
 * @brief Platform/ISA agnostic register type mappings.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

// FALCON_ENABLE_SSE, SSE2, SSE4
// FALCON_ENABLE_AVX
// FALCON_ENABLE_AVX2
// FALCON_ENABLE_AVX512
// FALCON_ENABLE_AVX10
// FALCON_ENABLE_NEON
// FALCON_ENABLE_SVE
// FALCON_DISABLE_SIMD
// #define FALCON_ENABLE_SSE

#include "falcon/core/Preprocessors.h"

#include <type_traits>

namespace flcn
{
    /**
     * @brief Backends Supported by Falcon SIMD.
     */
    enum class SimdBackend : uint8_t
    {
        ARCH_AVX10    = 7, // TODO: Future impl
        ARCH_AVX512EX = 6, // Extended for AVX512VL, AVX512BW, and AVX512DQ
        ARCH_AVX512F  = 5,
        ARCH_AVX2     = 4,
        ARCH_AVX      = 3,
        ARCH_SSE4     = 2,
        ARCH_SSE2     = 1,
        ARCH_NEON     = 101,
        ARCH_UNKNOWN  = 0,
    };

    // TODO: Test Function
    /// @brief Return whether a given backend belongs to x86 CPU instruction set.
    FALCON_INLINE constexpr bool isX86ISA(const SimdBackend backend)
    { return static_cast<uint8_t>(backend) < 100 && static_cast<uint8_t>(backend) > 0; }


    /// @brief Return whether a given backend belongs to ARM CPU instruction set.
    FALCON_INLINE constexpr bool isArmISA(const SimdBackend backend) { return static_cast<uint8_t>(backend) > 100; }


    // -mavx512f -mavx512cd -mavx512bw -mavx512dq -mavx512vl
    // TODO: Test Function
    FALCON_INLINE constexpr std::string toString(const SimdBackend backend)
    {
        switch (backend)
        {
            case SimdBackend::ARCH_SSE2:
                return "Streaming SIMD Extensions 2 (SSE2)";
            case SimdBackend::ARCH_SSE4:
                return "Streaming SIMD Extensions 4 (SSE4)";
            case SimdBackend::ARCH_AVX:
                return "Advanced Vector Extensions (AVX)";
            case SimdBackend::ARCH_AVX2:
                return "Advanced Vector Extensions 2 (AVX2)";
            case SimdBackend::ARCH_AVX512F:
                return "Advanced Vector Extensions 512 Foundation (AVX512F)";
            case SimdBackend::ARCH_AVX512EX:
                return "Advanced Vector Extensions 512 (AVX512BW/DQ/VL)";
            case SimdBackend::ARCH_AVX10:
                return "Advanced Vector Extensions 10 (AVX10)";
            case SimdBackend::ARCH_NEON:
                return "Arm Neon";
            default:
                return "Unsupported SIMD Instruction set";
        }
    }
} // namespace flcn


/// Switch Alignment and Backend Variable based on highest supported backend.
/// ALIGNMENT Gives the maximum alignment required.
/// CURRENT_SIMD_BACKEND The current SIMD backend used by the target application.
#if defined(FALCON_ENABLE_SSE2)

inline constexpr size_t ALIGNMENT          = 16;
inline constexpr size_t SIMD_LANE_WIDTH    = 128;
inline constexpr auto CURRENT_SIMD_BACKEND = flcn::SimdBackend::ARCH_SSE2;
    #define FALCON_PLATFORM_X86

#elif defined(FALCON_ENABLE_SSE4)

inline constexpr size_t ALIGNMENT          = 16;
inline constexpr size_t SIMD_LANE_WIDTH    = 128;
inline constexpr auto CURRENT_SIMD_BACKEND = flcn::SimdBackend::ARCH_SSE4;
    #define FALCON_PLATFORM_X86

#elif defined(FALCON_ENABLE_AVX)

inline constexpr size_t ALIGNMENT          = 32;
inline constexpr size_t SIMD_LANE_WIDTH    = 256;
inline constexpr auto CURRENT_SIMD_BACKEND = flcn::SimdBackend::ARCH_AVX;
    #define FALCON_PLATFORM_X86

#elif defined(FALCON_ENABLE_AVX2)

inline constexpr size_t ALIGNMENT          = 32;
inline constexpr size_t SIMD_LANE_WIDTH    = 256;
inline constexpr auto CURRENT_SIMD_BACKEND = flcn::SimdBackend::ARCH_AVX2;
    #define FALCON_PLATFORM_X86

#elif defined(FALCON_ENABLE_AVX512F)

inline constexpr size_t ALIGNMENT          = 64;
inline constexpr size_t SIMD_LANE_WIDTH    = 512;
inline constexpr auto CURRENT_SIMD_BACKEND = flcn::SimdBackend::ARCH_AVX512F;
    #define FALCON_PLATFORM_X86

#elif defined(FALCON_ENABLE_AVX512EX)

inline constexpr size_t ALIGNMENT          = 64;
inline constexpr size_t SIMD_LANE_WIDTH    = 512;
inline constexpr auto CURRENT_SIMD_BACKEND = flcn::SimdBackend::ARCH_AVX512EX;
    #define FALCON_PLATFORM_X86

#elif defined(FALCON_ENABLE_AVX10)

inline constexpr size_t ALIGNMENT          = 32;  // TODO: TBD
inline constexpr size_t SIMD_LANE_WIDTH    = 256; // TODO: TBD
inline constexpr auto CURRENT_SIMD_BACKEND = flcn::SimdBackend::ARCH_AVX10;
    #define FALCON_PLATFORM_X86

#elif defined(FALCON_ENABLE_NEON)

inline constexpr size_t ALIGNMENT          = 16;
inline constexpr size_t SIMD_LANE_WIDTH    = 128;
inline constexpr auto CURRENT_SIMD_BACKEND = flcn::SimdBackend::ARCH_NEON;
    #define FALCON_PLATFORM_NEON

#else

inline constexpr size_t ALIGNMENT          = 16;
inline constexpr size_t SIMD_LANE_WIDTH    = 64; // GP Register Width on 64-bit machines
inline constexpr auto CURRENT_SIMD_BACKEND = flcn::SimdBackend::ARCH_UNKNOWN;

#endif


/// FMA SUPPORT FLAGS
#if defined(FALCON_ENABLE_FMA) || defined(FALCON_ENABLE_FMA3) || defined(FALCON_ENABLE_FMA4)
inline constexpr bool FALCON_FMA_ENABLED = true;
#else
inline constexpr bool FALCON_FMA_ENABLED = false;
#endif


/// Force enables Horizontal Add cpu intrinsics which will be otherwise emulated (which is faster).
/// TODO: Add this a library flag
#ifdef FALCON_FORCE_HADD_INTRIN
inline constexpr bool FALCON_ENABLE_HADD_INTRINSIC = true;
#else
inline constexpr bool FALCON_ENABLE_HADD_INTRINSIC = false;
#endif
