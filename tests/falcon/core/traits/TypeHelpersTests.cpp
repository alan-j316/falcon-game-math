/**
 * @file TypeHelpersTests.cpp
 * @author Alan Abraham
 * @date Created on: August 21, 2026
 *
 * @brief Verifies falcon core type traits.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <falcon/core/traits/TypeHelpers.h>


/** @addtogroup TFalcon_Type
 *  @{
 */

namespace
{
    /**************************************
     *          STATIC TESTS              *
     **************************************/
    namespace static_tests
    {
        using namespace flcn::types;

        /// @test Verify that IsByte returns true only for 8-bit signed integrals.
        static_assert(IsByte<uint8_t> == false);
        static_assert(IsByte<uint16_t> == false);
        static_assert(IsByte<uint32_t> == false);
        static_assert(IsByte<uint64_t> == false);
        static_assert(IsByte<int8_t> == true);
        static_assert(IsByte<int16_t> == false);
        static_assert(IsByte<int32_t> == false);
        static_assert(IsByte<int64_t> == false);
        static_assert(IsByte<float> == false);
        static_assert(IsByte<double> == false);

        /// @test Verify that IsWord returns true only for 16-bit signed integrals.
        static_assert(IsWord<uint8_t> == false);
        static_assert(IsWord<uint16_t> == false);
        static_assert(IsWord<uint32_t> == false);
        static_assert(IsWord<uint64_t> == false);
        static_assert(IsWord<int8_t> == false);
        static_assert(IsWord<int16_t> == true);
        static_assert(IsWord<int32_t> == false);
        static_assert(IsWord<int64_t> == false);
        static_assert(IsWord<float> == false);
        static_assert(IsWord<double> == false);

        /// @test Verify that IsDWord returns true only for 32-bit signed integrals.
        static_assert(IsDWord<uint8_t> == false);
        static_assert(IsDWord<uint16_t> == false);
        static_assert(IsDWord<uint32_t> == false);
        static_assert(IsDWord<uint64_t> == false);
        static_assert(IsDWord<int8_t> == false);
        static_assert(IsDWord<int16_t> == false);
        static_assert(IsDWord<int32_t> == true);
        static_assert(IsDWord<int64_t> == false);
        static_assert(IsDWord<float> == false);
        static_assert(IsDWord<double> == false);

        /// @test Verify that IsQWord returns true only for 64-bit signed integrals.
        static_assert(IsQWord<uint8_t> == false);
        static_assert(IsQWord<uint16_t> == false);
        static_assert(IsQWord<uint32_t> == false);
        static_assert(IsQWord<uint64_t> == false);
        static_assert(IsQWord<int8_t> == false);
        static_assert(IsQWord<int16_t> == false);
        static_assert(IsQWord<int32_t> == false);
        static_assert(IsQWord<int64_t> == true);
        static_assert(IsQWord<float> == false);
        static_assert(IsQWord<double> == false);

        /// @test Verify that IsUByte returns true only for 8-bit unsigned integrals.
        static_assert(IsUByte<uint8_t> == true);
        static_assert(IsUByte<uint16_t> == false);
        static_assert(IsUByte<uint32_t> == false);
        static_assert(IsUByte<uint64_t> == false);
        static_assert(IsUByte<int8_t> == false);
        static_assert(IsUByte<int16_t> == false);
        static_assert(IsUByte<int32_t> == false);
        static_assert(IsUByte<int64_t> == false);
        static_assert(IsUByte<float> == false);
        static_assert(IsUByte<double> == false);

        /// @test Verify that IsUWord returns true only for 16-bit unsigned integrals.
        static_assert(IsUWord<uint8_t> == false);
        static_assert(IsUWord<uint16_t> == true);
        static_assert(IsUWord<uint32_t> == false);
        static_assert(IsUWord<uint64_t> == false);
        static_assert(IsUWord<int8_t> == false);
        static_assert(IsUWord<int16_t> == false);
        static_assert(IsUWord<int32_t> == false);
        static_assert(IsUWord<int64_t> == false);
        static_assert(IsUWord<float> == false);
        static_assert(IsUWord<double> == false);

        /// @test Verify that IsUDWord returns true only for 32-bit unsigned integrals.
        static_assert(IsUDWord<uint8_t> == false);
        static_assert(IsUDWord<uint16_t> == false);
        static_assert(IsUDWord<uint32_t> == true);
        static_assert(IsUDWord<uint64_t> == false);
        static_assert(IsUDWord<int8_t> == false);
        static_assert(IsUDWord<int16_t> == false);
        static_assert(IsUDWord<int32_t> == false);
        static_assert(IsUDWord<int64_t> == false);
        static_assert(IsUDWord<float> == false);
        static_assert(IsUDWord<double> == false);

        /// @test Verify that IsUQWord returns true only for 64-bit unsigned integrals.
        static_assert(IsUQWord<uint8_t> == false);
        static_assert(IsUQWord<uint16_t> == false);
        static_assert(IsUQWord<uint32_t> == false);
        static_assert(IsUQWord<uint64_t> == true);
        static_assert(IsUQWord<int8_t> == false);
        static_assert(IsUQWord<int16_t> == false);
        static_assert(IsUQWord<int32_t> == false);
        static_assert(IsUQWord<int64_t> == false);
        static_assert(IsUQWord<float> == false);
        static_assert(IsUQWord<double> == false);

        /// @test Verify that IsFP32 returns true only for 32-bit floats.
        static_assert(IsFP32<uint8_t> == false);
        static_assert(IsFP32<uint16_t> == false);
        static_assert(IsFP32<uint32_t> == false);
        static_assert(IsFP32<uint64_t> == false);
        static_assert(IsFP32<int8_t> == false);
        static_assert(IsFP32<int16_t> == false);
        static_assert(IsFP32<int32_t> == false);
        static_assert(IsFP32<int64_t> == false);
        static_assert(IsFP32<float> == true);
        static_assert(IsFP32<double> == false);

        /// @test Verify that IsFP64 returns true only for 64-bit floats.
        static_assert(IsFP64<uint8_t> == false);
        static_assert(IsFP64<uint16_t> == false);
        static_assert(IsFP64<uint32_t> == false);
        static_assert(IsFP64<uint64_t> == false);
        static_assert(IsFP64<int8_t> == false);
        static_assert(IsFP64<int16_t> == false);
        static_assert(IsFP64<int32_t> == false);
        static_assert(IsFP64<int64_t> == false);
        static_assert(IsFP64<float> == false);
        static_assert(IsFP64<double> == true);

        /// @test Verify that UInt_t returns the unsigned integral counterpart for all types.
        static_assert(std::is_same_v<UInt_t<int8_t>, uint8_t>);
        static_assert(std::is_same_v<UInt_t<int16_t>, uint16_t>);
        static_assert(std::is_same_v<UInt_t<int32_t>, uint32_t>);
        static_assert(std::is_same_v<UInt_t<int64_t>, uint64_t>);

        static_assert(std::is_same_v<UInt_t<uint8_t>, uint8_t>);
        static_assert(std::is_same_v<UInt_t<uint16_t>, uint16_t>);
        static_assert(std::is_same_v<UInt_t<uint32_t>, uint32_t>);
        static_assert(std::is_same_v<UInt_t<uint64_t>, uint64_t>);

        static_assert(std::is_same_v<UInt_t<double>, uint64_t>);
        static_assert(std::is_same_v<UInt_t<float>, uint32_t>);
        static_assert(std::is_same_v<UInt_t<bool>, uint8_t>);

    } // namespace static_tests
} // namespace

/** @} */
