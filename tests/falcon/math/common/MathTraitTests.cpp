/**
 * @file MathTraitTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 25, 2026
 *
 * @brief Verify that all falcon math concepts constraints to expected types.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <array>
#include <cstdint>
#include <falcon/math/common/MathTraits.h>
#include <vector>


/**
 * @addtogroup T_Math_Traits
 * @{
 */

namespace
{
    /** @test Verify that@ref flcn::Arithmetic concept constraints integrals and floating point types. */
    namespace
    {
        static_assert(flcn::Arithmetic<uint8_t> == true);
        static_assert(flcn::Arithmetic<uint16_t> == true);
        static_assert(flcn::Arithmetic<uint32_t> == true);
        static_assert(flcn::Arithmetic<uint64_t> == true);

        static_assert(flcn::Arithmetic<int8_t> == true);
        static_assert(flcn::Arithmetic<int16_t> == true);
        static_assert(flcn::Arithmetic<int32_t> == true);
        static_assert(flcn::Arithmetic<int64_t> == true);

        static_assert(flcn::Arithmetic<float> == true);
        static_assert(flcn::Arithmetic<double> == true);
        static_assert(flcn::Arithmetic<bool> == true);

        static_assert(flcn::Arithmetic<std::vector<int>> == false);
        static_assert(flcn::Arithmetic<std::array<int, 5>> == false);

    } // namespace


    /**
     * @test Verify that@ref flcn::SignedStrictArithmetic concept constraints signed integrals
     *        and floating point types.
     */
    namespace
    {
        static_assert(flcn::SignedStrictArithmetic<uint8_t> == false);
        static_assert(flcn::SignedStrictArithmetic<uint16_t> == false);
        static_assert(flcn::SignedStrictArithmetic<uint32_t> == false);
        static_assert(flcn::SignedStrictArithmetic<uint64_t> == false);
        static_assert(flcn::SignedStrictArithmetic<bool> == false);

        static_assert(flcn::SignedStrictArithmetic<int8_t> == true);
        static_assert(flcn::SignedStrictArithmetic<int16_t> == true);
        static_assert(flcn::SignedStrictArithmetic<int32_t> == true);
        static_assert(flcn::SignedStrictArithmetic<int64_t> == true);

        static_assert(flcn::SignedStrictArithmetic<float> == true);
        static_assert(flcn::SignedStrictArithmetic<double> == true);
    } // namespace


    /**
     * @test Verify that@ref flcn::StrictArithmetic concept constraints all signed integrals
     *        and floating point types except `bool`.
     */
    namespace
    {
        static_assert(flcn::StrictArithmetic<uint8_t> == true);
        static_assert(flcn::StrictArithmetic<uint16_t> == true);
        static_assert(flcn::StrictArithmetic<uint32_t> == true);
        static_assert(flcn::StrictArithmetic<uint64_t> == true);

        static_assert(flcn::StrictArithmetic<int8_t> == true);
        static_assert(flcn::StrictArithmetic<int16_t> == true);
        static_assert(flcn::StrictArithmetic<int32_t> == true);
        static_assert(flcn::StrictArithmetic<int64_t> == true);

        static_assert(flcn::StrictArithmetic<float> == true);
        static_assert(flcn::StrictArithmetic<double> == true);

        static_assert(flcn::StrictArithmetic<bool> == false);

    } // namespace


    /** @test Verify that@ref flcn::WeakArithmetic concept constraints integrals and floating point types. */
    namespace
    {
        static_assert(flcn::WeakArithmetic<uint8_t> == true);
        static_assert(flcn::WeakArithmetic<uint16_t> == true);
        static_assert(flcn::WeakArithmetic<uint32_t> == true);
        static_assert(flcn::WeakArithmetic<uint64_t> == true);

        static_assert(flcn::WeakArithmetic<int8_t> == true);
        static_assert(flcn::WeakArithmetic<int16_t> == true);
        static_assert(flcn::WeakArithmetic<int32_t> == true);
        static_assert(flcn::WeakArithmetic<int64_t> == true);

        static_assert(flcn::WeakArithmetic<float> == true);
        static_assert(flcn::WeakArithmetic<double> == true);
        static_assert(flcn::WeakArithmetic<bool> == true);

        static_assert(flcn::WeakArithmetic<std::vector<int>> == false);
        static_assert(flcn::WeakArithmetic<std::array<int, 5>> == false);

    } // namespace


    /** @test Verify that@ref flcn::StrictSignedness concept constraints two types of similar signedness. */
    namespace
    {
        // Unsigned types
        static_assert(flcn::StrictSignedness<uint8_t, uint8_t> == true);
        static_assert(flcn::StrictSignedness<uint16_t, uint8_t> == true);
        static_assert(flcn::StrictSignedness<uint32_t, uint8_t> == true);
        static_assert(flcn::StrictSignedness<uint64_t, uint8_t> == true);

        static_assert(flcn::StrictSignedness<uint16_t, uint16_t> == true);
        static_assert(flcn::StrictSignedness<uint32_t, uint16_t> == true);
        static_assert(flcn::StrictSignedness<uint64_t, uint16_t> == true);

        static_assert(flcn::StrictSignedness<uint32_t, uint32_t> == true);
        static_assert(flcn::StrictSignedness<uint64_t, uint32_t> == true);

        static_assert(flcn::StrictSignedness<uint64_t, uint64_t> == true);

        static_assert(flcn::StrictSignedness<uint8_t, float> == false);
        static_assert(flcn::StrictSignedness<uint16_t, float> == false);
        static_assert(flcn::StrictSignedness<uint32_t, float> == false);
        static_assert(flcn::StrictSignedness<uint64_t, float> == false);

        static_assert(flcn::StrictSignedness<uint8_t, double> == false);
        static_assert(flcn::StrictSignedness<uint16_t, double> == false);
        static_assert(flcn::StrictSignedness<uint32_t, double> == false);
        static_assert(flcn::StrictSignedness<uint64_t, double> == false);

        // Signed types
        static_assert(flcn::StrictSignedness<int8_t, int8_t> == true);
        static_assert(flcn::StrictSignedness<int16_t, int8_t> == true);
        static_assert(flcn::StrictSignedness<int32_t, int8_t> == true);
        static_assert(flcn::StrictSignedness<int64_t, int8_t> == true);

        static_assert(flcn::StrictSignedness<int16_t, int16_t> == true);
        static_assert(flcn::StrictSignedness<int32_t, int16_t> == true);
        static_assert(flcn::StrictSignedness<int64_t, int16_t> == true);

        static_assert(flcn::StrictSignedness<int32_t, int32_t> == true);
        static_assert(flcn::StrictSignedness<int64_t, int32_t> == true);

        static_assert(flcn::StrictSignedness<int64_t, int64_t> == true);

        static_assert(flcn::StrictSignedness<int8_t, float> == true);
        static_assert(flcn::StrictSignedness<int16_t, float> == true);
        static_assert(flcn::StrictSignedness<int32_t, float> == true);
        static_assert(flcn::StrictSignedness<int64_t, float> == true);

        static_assert(flcn::StrictSignedness<int8_t, double> == true);
        static_assert(flcn::StrictSignedness<int16_t, double> == true);
        static_assert(flcn::StrictSignedness<int32_t, double> == true);
        static_assert(flcn::StrictSignedness<int64_t, double> == true);

        // Mixed types
        static_assert(flcn::StrictSignedness<uint8_t, int8_t> == false);
        static_assert(flcn::StrictSignedness<uint16_t, int8_t> == false);
        static_assert(flcn::StrictSignedness<uint32_t, int8_t> == false);
        static_assert(flcn::StrictSignedness<uint64_t, int8_t> == false);

        static_assert(flcn::StrictSignedness<uint8_t, int16_t> == false);
        static_assert(flcn::StrictSignedness<uint16_t, int16_t> == false);
        static_assert(flcn::StrictSignedness<uint32_t, int16_t> == false);
        static_assert(flcn::StrictSignedness<uint64_t, int16_t> == false);

        static_assert(flcn::StrictSignedness<uint8_t, int32_t> == false);
        static_assert(flcn::StrictSignedness<uint16_t, int32_t> == false);
        static_assert(flcn::StrictSignedness<uint32_t, int32_t> == false);
        static_assert(flcn::StrictSignedness<uint64_t, int32_t> == false);

        static_assert(flcn::StrictSignedness<uint8_t, int64_t> == false);
        static_assert(flcn::StrictSignedness<uint16_t, int64_t> == false);
        static_assert(flcn::StrictSignedness<uint32_t, int64_t> == false);
        static_assert(flcn::StrictSignedness<uint64_t, int64_t> == false);

    } // namespace

} // namespace

/** @} */
