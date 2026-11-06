#pragma once
/**
 * @file TypeTraits.h
 * @author Alan Abraham P Kochumon
 * @date Created on: September 09, 2026
 *
 * @brief Defines type traits and concepts for SIMD.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include <type_traits>

namespace flcn
{


    /**
     * Concept for constraining mixed type usage without explicit casting.
     *
     * @tparam From The incoming numeric type.
     * @tparam To   The expected numeric type.
     */
    template <typename From, typename To>
    concept SimdSafeConvertible = requires {
        requires std::is_convertible_v<From, To>;
        // Floating points cannot be converted to integrals due to precision loss.
        requires !(std::is_floating_point_v<From> && std::is_integral_v<To>);
        // The types must guarantee to fit.
        requires sizeof(From) <= sizeof(To);
    };


    // TODO: Move to separate type file
    //========================== BLEND MASK TYPES ==========================
    using BlendMask64_t = uint64_t; /// 64-bit integral mask using full 64-bit bits for masking.
    using BlendMask32_t = uint32_t; /// 32-bit integral mask using full 32-bit bits for masking.
    using BlendMask16_t = uint32_t; /// 32-bit integral mask using lower 16-bits for masking.
    using BlendMask8_t  = uint32_t; /// 32-bit integral mask using lower 8-bits for masking.
    using BlendMask4_t  = uint32_t; /// 32-bit integral mask using lower 4-bits for masking.


    //========================== CUSTOM INTEGRAL TYPES ==========================
    /// Structure for holding 128-bit integers(Emulated)
    struct u128
    {
        uint64_t upper;
        uint64_t lower;
    };


    /// Structure for holding 256-bit integers.
    struct u256
    {
        // Quad3 is the most significant part and Quad0 the least.
        uint64_t quad3, quad2, quad1, quad0;
    };

} // namespace flcn
