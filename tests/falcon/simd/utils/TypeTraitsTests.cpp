/**
 * @file TypeTraitsTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 09, 2026
 *
 * @brief Verify type traits and concepts.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include <cstdint>
#include <falcon/simd/utils/TypeTraits.h>

namespace
{
    namespace static_tests
    {
        using namespace flcn;

        /// @test Verify that @ref flcn::SimdSafeConvertible return appropriate values depending on type narrow.
        // uint8_t
        static_assert(SimdSafeConvertible<uint8_t, uint8_t>);
        static_assert(SimdSafeConvertible<uint8_t, uint16_t>);
        static_assert(SimdSafeConvertible<uint8_t, uint32_t>);
        static_assert(SimdSafeConvertible<uint8_t, uint64_t>);
        static_assert(SimdSafeConvertible<uint8_t, int8_t>); // Narrowing
        static_assert(SimdSafeConvertible<uint8_t, int16_t>);
        static_assert(SimdSafeConvertible<uint8_t, int32_t>);
        static_assert(SimdSafeConvertible<uint8_t, int64_t>);
        static_assert(SimdSafeConvertible<uint8_t, float>);
        static_assert(SimdSafeConvertible<uint8_t, double>);

        // uint16_t
        static_assert(!SimdSafeConvertible<uint16_t, uint8_t>); // Narrowing
        static_assert(SimdSafeConvertible<uint16_t, uint16_t>);
        static_assert(SimdSafeConvertible<uint16_t, uint32_t>);
        static_assert(SimdSafeConvertible<uint16_t, uint64_t>);
        static_assert(!SimdSafeConvertible<uint16_t, int8_t>); // Narrowing
        static_assert(SimdSafeConvertible<uint16_t, int16_t>);
        static_assert(SimdSafeConvertible<uint16_t, int32_t>);
        static_assert(SimdSafeConvertible<uint16_t, int64_t>);
        static_assert(SimdSafeConvertible<uint16_t, float>);
        static_assert(SimdSafeConvertible<uint16_t, double>);

        // uint32_t
        static_assert(!SimdSafeConvertible<uint32_t, uint8_t>);  // Narrowing
        static_assert(!SimdSafeConvertible<uint32_t, uint16_t>); // Narrowing
        static_assert(SimdSafeConvertible<uint32_t, uint32_t>);
        static_assert(SimdSafeConvertible<uint32_t, uint64_t>);
        static_assert(!SimdSafeConvertible<uint32_t, int8_t>);  // Narrowing
        static_assert(!SimdSafeConvertible<uint32_t, int16_t>); // Narrowing
        static_assert(SimdSafeConvertible<uint32_t, int32_t>);
        static_assert(SimdSafeConvertible<uint32_t, int64_t>);
        static_assert(SimdSafeConvertible<uint32_t, float>);
        static_assert(SimdSafeConvertible<uint32_t, double>);

        // uint64_t
        static_assert(!SimdSafeConvertible<uint64_t, uint8_t>);  // Narrowing
        static_assert(!SimdSafeConvertible<uint64_t, uint16_t>); // Narrowing
        static_assert(!SimdSafeConvertible<uint64_t, uint32_t>); // Narrowing
        static_assert(SimdSafeConvertible<uint64_t, uint64_t>);
        static_assert(!SimdSafeConvertible<uint64_t, int8_t>);  // Narrowing
        static_assert(!SimdSafeConvertible<uint64_t, int16_t>); // Narrowing
        static_assert(!SimdSafeConvertible<uint64_t, int32_t>); // Narrowing
        static_assert(SimdSafeConvertible<uint64_t, int64_t>);
        static_assert(!SimdSafeConvertible<uint64_t, float>); // Narrowing
        static_assert(SimdSafeConvertible<uint64_t, double>);

        // int8_t
        static_assert(SimdSafeConvertible<int8_t, uint8_t>);
        static_assert(SimdSafeConvertible<int8_t, uint16_t>);
        static_assert(SimdSafeConvertible<int8_t, uint32_t>);
        static_assert(SimdSafeConvertible<int8_t, uint64_t>);
        static_assert(SimdSafeConvertible<int8_t, int8_t>);
        static_assert(SimdSafeConvertible<int8_t, int16_t>);
        static_assert(SimdSafeConvertible<int8_t, int32_t>);
        static_assert(SimdSafeConvertible<int8_t, int64_t>);
        static_assert(SimdSafeConvertible<int8_t, float>);
        static_assert(SimdSafeConvertible<int8_t, double>);

        // int16_t
        static_assert(!SimdSafeConvertible<int16_t, uint8_t>); // Narrowing
        static_assert(SimdSafeConvertible<int16_t, uint16_t>);
        static_assert(SimdSafeConvertible<int16_t, uint32_t>);
        static_assert(SimdSafeConvertible<int16_t, uint64_t>);
        static_assert(!SimdSafeConvertible<int16_t, int8_t>); // Narrowing
        static_assert(SimdSafeConvertible<int16_t, int16_t>);
        static_assert(SimdSafeConvertible<int16_t, int32_t>);
        static_assert(SimdSafeConvertible<int16_t, int64_t>);
        static_assert(SimdSafeConvertible<int16_t, float>);
        static_assert(SimdSafeConvertible<int16_t, double>);

        // int32_t
        static_assert(!SimdSafeConvertible<int32_t, uint8_t>);  // Narrowing
        static_assert(!SimdSafeConvertible<int32_t, uint16_t>); // Narrowing
        static_assert(SimdSafeConvertible<int32_t, uint32_t>);
        static_assert(SimdSafeConvertible<int32_t, uint64_t>);
        static_assert(!SimdSafeConvertible<int32_t, int8_t>);  // Narrowing
        static_assert(!SimdSafeConvertible<int32_t, int16_t>); // Narrowing
        static_assert(SimdSafeConvertible<int32_t, int32_t>);
        static_assert(SimdSafeConvertible<int32_t, int64_t>);
        static_assert(SimdSafeConvertible<int32_t, float>);
        static_assert(SimdSafeConvertible<int32_t, double>);

        // int64_t
        static_assert(!SimdSafeConvertible<int64_t, uint8_t>);  // Narrowing
        static_assert(!SimdSafeConvertible<int64_t, uint16_t>); // Narrowing
        static_assert(!SimdSafeConvertible<int64_t, uint32_t>); // Narrowing
        static_assert(SimdSafeConvertible<int64_t, uint64_t>);
        static_assert(!SimdSafeConvertible<int64_t, int8_t>);  // Narrowing
        static_assert(!SimdSafeConvertible<int64_t, int16_t>); // Narrowing
        static_assert(!SimdSafeConvertible<int64_t, int32_t>); // Narrowing
        static_assert(SimdSafeConvertible<int64_t, int64_t>);
        static_assert(!SimdSafeConvertible<int64_t, float>);
        static_assert(SimdSafeConvertible<int64_t, double>);

        // float
        static_assert(!SimdSafeConvertible<float, uint8_t>);
        static_assert(!SimdSafeConvertible<float, uint16_t>);
        static_assert(!SimdSafeConvertible<float, uint32_t>);
        static_assert(!SimdSafeConvertible<float, uint64_t>);
        static_assert(!SimdSafeConvertible<float, int8_t>);
        static_assert(!SimdSafeConvertible<float, int16_t>);
        static_assert(!SimdSafeConvertible<float, int32_t>);
        static_assert(!SimdSafeConvertible<float, int64_t>);
        static_assert(SimdSafeConvertible<float, float>);
        static_assert(SimdSafeConvertible<float, double>);

        // double
        static_assert(!SimdSafeConvertible<double, uint8_t>);  // Narrowing
        static_assert(!SimdSafeConvertible<double, uint16_t>); // Narrowing
        static_assert(!SimdSafeConvertible<double, uint32_t>); // Narrowing
        static_assert(!SimdSafeConvertible<double, uint64_t>); // Narrowing
        static_assert(!SimdSafeConvertible<double, int8_t>);   // Narrowing
        static_assert(!SimdSafeConvertible<double, int16_t>);  // Narrowing
        static_assert(!SimdSafeConvertible<double, int32_t>);  // Narrowing
        static_assert(!SimdSafeConvertible<double, int64_t>);  // Narrowing
        static_assert(!SimdSafeConvertible<double, float>);    // Narrowing
        static_assert(SimdSafeConvertible<double, double>);


    } // namespace static_tests
} // namespace
