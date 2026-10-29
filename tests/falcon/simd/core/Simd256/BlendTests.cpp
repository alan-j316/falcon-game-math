/**
 * @file BlendTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: October 06, 2026
 *
 * @brief Verifies Simd256 blending operations.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "SIMDTestSetup.h"

#include <array>
#include <bit>

// TODO: Remove Preprocessor after implementing individual simd paths
#if defined(FALCON_ENABLE_AVX512) || defined(FALCON_ENABLE_AVX2) || defined(FALCON_ENABLE_AVX) ||                      \
    defined(FALCON_ENABLE_SSE4) || defined(FALCON_ENABLE_SSE2)


/**
 * @addtogroup T_SIMD256_Shuffle
 * @{
 */

namespace
{
    using namespace simd::testing;

    // Test param to pass in a combination matrix for testing blend function.
    // since gtest doesn't natively support parameterized typed test(where you can pass in parameters against a type
    // vector)
    template <typename T, size_t Lanes, Array<T, Lanes> first, Array<T, Lanes> second, Array<T, Lanes> mask,
              Array<T, Lanes> expected>
    struct Simd256BlendTestParam
    {
        using Type                            = T;
        static constexpr size_t REGISTER_SIZE = 256;
        static constexpr size_t LaneCount     = Lanes;
        static constexpr auto First           = first;
        static constexpr auto Second          = second;
        static constexpr auto Mask            = mask;
        static constexpr auto Expected        = expected;
        const char* TypeName                  = typeid(Type).name();

        // TODO: Fix pretty function not being used.
        friend std::ostream& operator<<(std::ostream& os, const Simd256BlendTestParam& param)
        { return os << "Simd256BlendTestParam(Type=" << param.TypeName << ", Lanes" << param.LaneCount << ")"; }

        // friend void PrintTo(const Simd256BlendTestParam& param, std::ostream* os)
        // { *os << "Simd256BlendTestParam(Type=" << param.TypeName << ", Lanes" << param.LaneCount << ")"; }
    };

    // clang-format off
    using Simd256BlendTestTypeHints = testing::Types<
        // Unsigned types
        // Uint8t
        Simd256BlendTestParam<
            U8, 32,
            Array<U8, 32>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21, 39, 43, 16, 29, 94, 28, 69, 110, 58, 26, 7, 30, 89, 67, 1, 113 },
            Array<U8, 32>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71, 10, 86, 87, 79, 88, 66, 96, 2, 60, 76, 74, 32, 76, 93, 74, 105 },
            Array<U8, 32>{
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            },
            Array<U8, 32>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21, 39, 43, 16, 29, 94, 28, 69, 110, 58, 26, 7, 30, 89, 67, 1, 113 }
        >,
        Simd256BlendTestParam<
            U8, 32,
            Array<U8, 32>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21, 39, 43, 16, 29, 94, 28, 69, 110, 58, 26, 7, 30, 89, 67, 1, 113 },
            Array<U8, 32>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71, 10, 86, 87, 79, 88, 66, 96, 2, 60, 76, 74, 32, 76, 93, 74, 105 },
            Array<U8, 32>{
                ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>,
                ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>, ONE<U8>
            },
            Array<U8, 32>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71, 10, 86, 87, 79, 88, 66, 96, 2, 60, 76, 74, 32, 76, 93, 74, 105 }
        >,
        Simd256BlendTestParam<
            U8, 32,
            Array<U8, 32>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21, 39, 43, 16, 29, 94, 28, 69, 110, 58, 26, 7, 30, 89, 67, 1, 113 },
            Array<U8, 32>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71, 10, 86, 87, 79, 88, 66, 96, 2, 60, 76, 74, 32, 76, 93, 74, 105 },
            Array<U8, 32>{
                ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0,
                ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0
            },
            Array<U8, 32>{ 107, 14, 5, 47, 97, 38, 28, 40, 87, 73, 127, 24, 62, 40, 65, 21, 10, 43, 87, 29, 88, 28, 96, 110, 60, 26, 74, 30, 76, 67, 74, 113 }
        >,
        Simd256BlendTestParam<
                U8, 32,
                Array<U8, 32>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21, 39, 43, 16, 29, 94, 28, 69, 110, 58, 26, 7, 30, 89, 67, 1, 113 },
                Array<U8, 32>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71, 10, 86, 87, 79, 88, 66, 96, 2, 60, 76, 74, 32, 76, 93, 74, 105 },
                Array<U8, 32>{
                    0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>,
                    0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>,
                },
                Array<U8, 32>{ 105, 43, 68, 57, 127, 118, 32, 4, 117, 8, 19, 2, 85, 126, 59, 71, 39, 86, 16, 79, 94, 66, 69, 2, 58, 76, 7, 32, 89, 93, 1, 105 }
        >,

        // Uint16t
        Simd256BlendTestParam<
            U16, 16,
            Array<U16, 16>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21 },
            Array<U16, 16>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71 },
            Array<U16, 16>{
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            },
            Array<U16, 16>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21 }
        >,
        Simd256BlendTestParam<
            U16, 16,
            Array<U16, 16>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21 },
            Array<U16, 16>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71},
            Array<U16, 16>{
                ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>, ONE<U16>
            },
            Array<U16, 16>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71 }
        >,
        Simd256BlendTestParam<
            U16, 16,
            Array<U16, 16>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21 },
            Array<U16, 16>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71 },
            Array<U16, 16>{
                ONE<U16>, 0, ONE<U16>, 0, ONE<U16>, 0, ONE<U16>, 0, ONE<U16>, 0, ONE<U16>, 0, ONE<U16>, 0, ONE<U16>, 0
            },
            Array<U16, 16>{ 107, 14, 5, 47, 97, 38, 28, 40, 87, 73, 127, 24, 62, 40, 65, 21 }
        >,
        Simd256BlendTestParam<
                U16, 16,
                Array<U16, 16>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21 },
                Array<U16, 16>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71 },
                Array<U16, 16>{
                    0, ONE<U16>, 0, ONE<U16>, 0, ONE<U16>, 0, ONE<U16>, 0, ONE<U16>, 0, ONE<U16>, 0, ONE<U16>, 0, ONE<U16>
                },
                Array<U16, 16>{ 105, 43, 68, 57, 127, 118, 32, 4, 117, 8, 19, 2, 85, 126, 59, 71 }
        >,

        // Uint32t
        Simd256BlendTestParam<
            U32, 8,
            Array<U32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
            Array<U32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
            Array<U32, 8>{
                0, 0, 0, 0, 0, 0, 0, 0
            },
            Array<U32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 }
        >,
        Simd256BlendTestParam<
            U32, 8,
            Array<U32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
            Array<U32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
            Array<U32, 8>{
                ONE<U32>, ONE<U32>, ONE<U32>, ONE<U32>, ONE<U32>, ONE<U32>, ONE<U32>, ONE<U32>
            },
            Array<U32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 }
        >,
        Simd256BlendTestParam<
            U32, 8,
            Array<U32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
            Array<U32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
            Array<U32, 8>{
                ONE<U32>, 0, ONE<U32>, 0, ONE<U32>, 0, ONE<U32>, 0
            },
            Array<U32, 8>{ 107, 14, 5, 47, 97, 38, 28, 40 }
        >,
        Simd256BlendTestParam<
                U32, 8,
                Array<U32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
                Array<U32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
                Array<U32, 8>{
                    0, ONE<U32>, 0, ONE<U32>, 0, ONE<U32>, 0, ONE<U32>
                },
                Array<U32, 8>{ 105, 43, 68, 57, 127, 118, 32, 4 }
        >,

        // Uint64t
        Simd256BlendTestParam<
            U64, 4,
            Array<U64, 4>{ 105, 14, 64, 47 },
            Array<U64, 4>{ 107, 43, 5, 57 },
            Array<U64, 4>{ 0, 0, 0, 0 },
            Array<U64, 4>{ 105, 14, 64, 47 }
        >,
        Simd256BlendTestParam<
            U64, 4,
            Array<U64, 4>{ 105, 14, 64, 47 },
            Array<U64, 4>{ 107, 43, 5, 57 },
            Array<U64, 4>{ ONE<U64>, ONE<U64>, ONE<U64>, ONE<U64> },
            Array<U64, 4>{ 107, 43, 5, 57 }
        >,
        Simd256BlendTestParam<
            U64, 4,
            Array<U64, 4>{ 105, 14, 64, 47 },
            Array<U64, 4>{ 107, 43, 5, 57 },
            Array<U64, 4>{ ONE<U64>, 0, ONE<U64>, 0 },
            Array<U64, 4>{ 107, 14, 5, 47 }
        >,
        Simd256BlendTestParam<
                U64, 4,
                Array<U64, 4>{ 105, 14, 64, 47 },
                Array<U64, 4>{ 107, 43, 5, 57 },
                Array<U64, 4>{ 0, ONE<U64>, 0, ONE<U64> },
                Array<U64, 4>{ 105, 43, 64, 57 }
        >,

        // Signed types
        // Int8t
        Simd256BlendTestParam<
            I8, 32,
            Array<I8, 32>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21, 39, 43, 16, 29, 94, 28, 69, 110, 58, 26, 7, 30, 89, 67, 1, 113 },
            Array<I8, 32>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71, 10, 86, 87, 79, 88, 66, 96, 2, 60, 76, 74, 32, 76, 93, 74, 105 },
            Array<I8, 32>{
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            },
            Array<I8, 32>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21, 39, 43, 16, 29, 94, 28, 69, 110, 58, 26, 7, 30, 89, 67, 1, 113 }
        >,
        Simd256BlendTestParam<
            I8, 32,
            Array<I8, 32>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21, 39, 43, 16, 29, 94, 28, 69, 110, 58, 26, 7, 30, 89, 67, 1, 113 },
            Array<I8, 32>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71, 10, 86, 87, 79, 88, 66, 96, 2, 60, 76, 74, 32, 76, 93, 74, 105 },
            Array<I8, 32>{
                ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>,
                ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>, ONE<I8>
            },
            Array<I8, 32>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71, 10, 86, 87, 79, 88, 66, 96, 2, 60, 76, 74, 32, 76, 93, 74, 105 }
        >,
        Simd256BlendTestParam<
            I8, 32,
            Array<I8, 32>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21, 39, 43, 16, 29, 94, 28, 69, 110, 58, 26, 7, 30, 89, 67, 1, 113 },
            Array<I8, 32>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71, 10, 86, 87, 79, 88, 66, 96, 2, 60, 76, 74, 32, 76, 93, 74, 105 },
            Array<I8, 32>{
                ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0,
                ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0
            },
            Array<I8, 32>{ 107, 14, 5, 47, 97, 38, 28, 40, 87, 73, 127, 24, 62, 40, 65, 21, 10, 43, 87, 29, 88, 28, 96, 110, 60, 26, 74, 30, 76, 67, 74, 113 }
        >,
        Simd256BlendTestParam<
                I8, 32,
                Array<I8, 32>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21, 39, 43, 16, 29, 94, 28, 69, 110, 58, 26, 7, 30, 89, 67, 1, 113 },
                Array<I8, 32>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71, 10, 86, 87, 79, 88, 66, 96, 2, 60, 76, 74, 32, 76, 93, 74, 105 },
                Array<I8, 32>{
                    0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>,
                    0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>,
                },
                Array<I8, 32>{ 105, 43, 68, 57, 127, 118, 32, 4, 117, 8, 19, 2, 85, 126, 59, 71, 39, 86, 16, 79, 94, 66, 69, 2, 58, 76, 7, 32, 89, 93, 1, 105 }
        >,

        // Int16t
        Simd256BlendTestParam<
            I16, 16,
            Array<I16, 16>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21 },
            Array<I16, 16>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71 },
            Array<I16, 16>{
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            },
            Array<I16, 16>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21 }
        >,
        Simd256BlendTestParam<
            I16, 16,
            Array<I16, 16>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21 },
            Array<I16, 16>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71},
            Array<I16, 16>{
                ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>, ONE<I16>
            },
            Array<I16, 16>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71 }
        >,
        Simd256BlendTestParam<
            I16, 16,
            Array<I16, 16>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21 },
            Array<I16, 16>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71 },
            Array<I16, 16>{
                ONE<I16>, 0, ONE<I16>, 0, ONE<I16>, 0, ONE<I16>, 0, ONE<I16>, 0, ONE<I16>, 0, ONE<I16>, 0, ONE<I16>, 0
            },
            Array<I16, 16>{ 107, 14, 5, 47, 97, 38, 28, 40, 87, 73, 127, 24, 62, 40, 65, 21 }
        >,
        Simd256BlendTestParam<
                I16, 16,
                Array<I16, 16>{ 105, 14, 68, 47, 127, 38, 32, 40, 117, 73, 19, 24, 85, 40, 59, 21 },
                Array<I16, 16>{ 107, 43, 5, 57, 97, 118, 28, 4, 87, 8, 127, 2, 62, 126, 65, 71 },
                Array<I16, 16>{
                    0, ONE<I16>, 0, ONE<I16>, 0, ONE<I16>, 0, ONE<I16>, 0, ONE<I16>, 0, ONE<I16>, 0, ONE<I16>, 0, ONE<I16>
                },
                Array<I16, 16>{ 105, 43, 68, 57, 127, 118, 32, 4, 117, 8, 19, 2, 85, 126, 59, 71 }
        >,

        // Int32t
        Simd256BlendTestParam<
            I32, 8,
            Array<I32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
            Array<I32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
            Array<I32, 8>{
                0, 0, 0, 0, 0, 0, 0, 0
            },
            Array<I32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 }
        >,
        Simd256BlendTestParam<
            I32, 8,
            Array<I32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
            Array<I32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
            Array<I32, 8>{
                ONE<I32>, ONE<I32>, ONE<I32>, ONE<I32>, ONE<I32>, ONE<I32>, ONE<I32>, ONE<I32>
            },
            Array<I32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 }
        >,
        Simd256BlendTestParam<
            I32, 8,
            Array<I32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
            Array<I32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
            Array<I32, 8>{
                ONE<I32>, 0, ONE<I32>, 0, ONE<I32>, 0, ONE<I32>, 0
            },
            Array<I32, 8>{ 107, 14, 5, 47, 97, 38, 28, 40 }
        >,
        Simd256BlendTestParam<
                I32, 8,
                Array<I32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
                Array<I32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
                Array<I32, 8>{
                    0, ONE<I32>, 0, ONE<I32>, 0, ONE<I32>, 0, ONE<I32>
                },
                Array<I32, 8>{ 105, 43, 68, 57, 127, 118, 32, 4 }
        >,

        // Int64t
        Simd256BlendTestParam<
            I64, 4,
            Array<I64, 4>{ 105, 14, 64, 47 },
            Array<I64, 4>{ 107, 43, 5, 57 },
            Array<I64, 4>{ 0, 0, 0, 0 },
            Array<I64, 4>{ 105, 14, 64, 47 }
        >,
        Simd256BlendTestParam<
            I64, 4,
            Array<I64, 4>{ 105, 14, 64, 47 },
            Array<I64, 4>{ 107, 43, 5, 57 },
            Array<I64, 4>{ ONE<I64>, ONE<I64>, ONE<I64>, ONE<I64> },
            Array<I64, 4>{ 107, 43, 5, 57 }
        >,
        Simd256BlendTestParam<
            I64, 4,
            Array<I64, 4>{ 105, 14, 64, 47 },
            Array<I64, 4>{ 107, 43, 5, 57 },
            Array<I64, 4>{ ONE<I64>, 0, ONE<I64>, 0 },
            Array<I64, 4>{ 107, 14, 5, 47 }
        >,
        Simd256BlendTestParam<
                I64, 4,
                Array<I64, 4>{ 105, 14, 64, 47 },
                Array<I64, 4>{ 107, 43, 5, 57 },
                Array<I64, 4>{ 0, ONE<I64>, 0, ONE<I64> },
                Array<I64, 4>{ 105, 43, 64, 57 }
        >,

        // Floating point types
        // FP32
        Simd256BlendTestParam<
            FP32, 8,
            Array<FP32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
            Array<FP32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
            Array<FP32, 8>{
                0, 0, 0, 0, 0, 0, 0, 0
            },
            Array<FP32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 }
        >,
        Simd256BlendTestParam<
            FP32, 8,
            Array<FP32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
            Array<FP32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
            Array<FP32, 8>{
                ONE<FP32>, ONE<FP32>, ONE<FP32>, ONE<FP32>, ONE<FP32>, ONE<FP32>, ONE<FP32>, ONE<FP32>
            },
            Array<FP32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 }
        >,
        Simd256BlendTestParam<
            FP32, 8,
            Array<FP32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
            Array<FP32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
            Array<FP32, 8>{
                ONE<FP32>, 0, ONE<FP32>, 0, ONE<FP32>, 0, ONE<FP32>, 0
            },
            Array<FP32, 8>{ 107, 14, 5, 47, 97, 38, 28, 40 }
        >,
        Simd256BlendTestParam<
                FP32, 8,
                Array<FP32, 8>{ 105, 14, 68, 47, 127, 38, 32, 40 },
                Array<FP32, 8>{ 107, 43, 5, 57, 97, 118, 28, 4 },
                Array<FP32, 8>{
                    0, ONE<FP32>, 0, ONE<FP32>, 0, ONE<FP32>, 0, ONE<FP32>
                },
                Array<FP32, 8>{ 105, 43, 68, 57, 127, 118, 32, 4 }
        >,

        // FP64
        Simd256BlendTestParam<
            FP64, 4,
            Array<FP64, 4>{ 105, 14, 64, 47 },
            Array<FP64, 4>{ 107, 43, 5, 57 },
            Array<FP64, 4>{ 0, 0, 0, 0 },
            Array<FP64, 4>{ 105, 14, 64, 47 }
        >,
        Simd256BlendTestParam<
            FP64, 4,
            Array<FP64, 4>{ 105, 14, 64, 47 },
            Array<FP64, 4>{ 107, 43, 5, 57 },
            Array<FP64, 4>{ ONE<FP64>, ONE<FP64>, ONE<FP64>, ONE<FP64> },
            Array<FP64, 4>{ 107, 43, 5, 57 }
        >,
        Simd256BlendTestParam<
            FP64, 4,
            Array<FP64, 4>{ 105, 14, 64, 47 },
            Array<FP64, 4>{ 107, 43, 5, 57 },
            Array<FP64, 4>{ ONE<FP64>, 0, ONE<FP64>, 0 },
            Array<FP64, 4>{ 107, 14, 5, 47 }
        >,
        Simd256BlendTestParam<
                FP64, 4,
                Array<FP64, 4>{ 105, 14, 64, 47 },
                Array<FP64, 4>{ 107, 43, 5, 57 },
                Array<FP64, 4>{ 0, ONE<FP64>, 0, ONE<FP64> },
                Array<FP64, 4>{ 105, 43, 64, 57 }
        >
    >;
    // clang-format on


    /// @brief Test fixture for Simd256 blending operations.
    template <typename>
    class Simd256BlendTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Simd256BlendTests, Simd256BlendTestTypeHints);

} // namespace


TYPED_TEST(Simd256BlendTests, BlendingWithMaskReturnsRegisterWithCorrectValues)
{
    // Get all the parameters from the types
    using Type                            = TypeParam::Type;
    constexpr size_t Lanes                = TypeParam::LaneCount;
    constexpr Array<Type, Lanes> First    = TypeParam::First;
    constexpr Array<Type, Lanes> Second   = TypeParam::Second;
    constexpr Array<Type, Lanes> Mask     = TypeParam::Mask;
    constexpr Array<Type, Lanes> Expected = TypeParam::Expected;

    // Create the register and load them
    // Note: While const cast is not recommended in such a situation since the underlying buffer
    //       non-const, we can cast this as internally the load function doesn't mutate the parameters.
    flcn::Simd256_t<Type, Lanes> regA{}, regB{}, mask{};
    regA.load(const_cast<Type*>(First.data()));
    regB.load(const_cast<Type*>(Second.data()));
    mask.load(const_cast<Type*>(Mask.data()));

    // Perform the blending
    Array<Type, Lanes> result{};
    const auto resultReg = regA.blend(regB, mask);
    resultReg.store(result.data());

    // Compare and assert the result.
    for (size_t i = 0; i < Lanes; ++i)
    {
        EXPECT_ANY_EQ(Expected[i], result[i]);
    }
}


/// =============================== START COMPILE TIME BLEND TESTS ===============================

    #define SIMD256_COMPILE_TIME_BLEND_TESTS(TestSuffix, Type, Lanes, First, Second, Expected, ...)                    \
        TEST(Simd256BlendTests, CompileTimeBlendingWithMask_ReturnsValidRegister_For##TestSuffix)                      \
        {                                                                                                              \
            flcn::Simd256_t<Type, Lanes> regA{}, regB{};                                                               \
            constexpr auto mask = regA.makeBlendMask<__VA_ARGS__>();                                                   \
            regA.load(First.data());                                                                                   \
            regB.load(Second.data());                                                                                  \
                                                                                                                       \
            Array<Type, Lanes> result{};                                                                               \
            const auto resultReg = regA.template blend<mask>(regB);                                                    \
            resultReg.store(result.data());                                                                            \
                                                                                                                       \
            for (size_t i = 0; i < Lanes; ++i)                                                                         \
            {                                                                                                          \
                EXPECT_ANY_EQ(Expected[i], result[i]);                                                                 \
            }                                                                                                          \
        }

constexpr bool T = true;
constexpr bool F = false;

// clang-format off
// Unsigned integers
static Array<U8, 32> arrU8x32_First{ 9, 3, 9, 79, 123, 75, 107, 55, 115, 122, 32, 76, 100, 127, 0, 65, 118, 4, 74, 67, 54, 61, 83, 47, 79, 61, 70, 79, 115, 48, 4, 97 };
static Array<U8, 32> arrU8x32_Second{ 50, 112, 22, 123, 86, 66, 6, 127, 17, 60, 12, 62, 120, 24, 20, 102, 21, 48, 73, 32, 100, 43, 108, 124, 25, 48, 99, 32, 106, 26, 2, 114 };
static Array<U8, 32> arrU8x32_SelectMixed{ 50, 3, 22, 79, 86, 75, 6, 55, 17, 122, 12, 76, 120, 127, 20, 65, 21, 4, 73, 67, 100, 61, 108, 47, 25, 61, 99, 79, 106, 48, 2, 97 };
SIMD256_COMPILE_TIME_BLEND_TESTS(U8_32Lanes_SelectFirst, U8, 32, arrU8x32_First, arrU8x32_Second, arrU8x32_First, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F)
SIMD256_COMPILE_TIME_BLEND_TESTS(U8_32Lanes_SelectSecond, U8, 32, arrU8x32_First, arrU8x32_Second, arrU8x32_Second, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T)
SIMD256_COMPILE_TIME_BLEND_TESTS(U8_32Lanes_SelectMixed, U8, 32, arrU8x32_First, arrU8x32_Second, arrU8x32_SelectMixed, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F)

static Array<U16, 16> arrU16x16_First{ 100, 123, 121, 53, 16, 34, 21, 24, 33, 15, 121, 127, 35, 14, 96, 88 };
static Array<U16, 16> arrU16x16_Second{ 32, 15, 67, 12, 93, 32, 12, 47, 4, 120, 11, 31, 12, 7, 82, 99 };
static Array<U16, 16> arrU16x16_SelectMixed{ 32, 123, 67, 53, 93, 34, 12, 24, 4, 15, 11, 127, 12, 14, 82, 88 };
SIMD256_COMPILE_TIME_BLEND_TESTS(U16_16Lanes_SelectFirst, U16, 16, arrU16x16_First, arrU16x16_Second, arrU16x16_First, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F)
SIMD256_COMPILE_TIME_BLEND_TESTS(U16_16Lanes_SelectSecond, U16, 16, arrU16x16_First, arrU16x16_Second, arrU16x16_Second, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T)
SIMD256_COMPILE_TIME_BLEND_TESTS(U16_16Lanes_SelectMixed, U16, 16, arrU16x16_First, arrU16x16_Second, arrU16x16_SelectMixed, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F)

static Array<U32, 8> arrU32x8_First{ 100, 28, 121, 53, 8, 34, 21, 24 };
static Array<U32, 8> arrU32x8_Second{ 32, 15, 67, 12, 93, 32, 98, 47 };
static Array<U32, 8> arrU32x8_SelectMixed{ 32, 28, 67, 53, 93, 34, 98, 24 };
SIMD256_COMPILE_TIME_BLEND_TESTS(U32_8Lanes_SelectFirst, U32, 8, arrU32x8_First, arrU32x8_Second, arrU32x8_First, F, F, F, F, F, F, F, F)
SIMD256_COMPILE_TIME_BLEND_TESTS(U32_8Lanes_SelectSecond, U32, 8, arrU32x8_First, arrU32x8_Second, arrU32x8_Second, T, T, T, T, T, T, T, T)
SIMD256_COMPILE_TIME_BLEND_TESTS(U32_8Lanes_SelectMixed, U32, 8, arrU32x8_First, arrU32x8_Second, arrU32x8_SelectMixed, T, F, T, F, T, F, T, F)

static Array<U64, 4> arrU64x4_First{ 100, 24, 121, 53 };
static Array<U64, 4> arrU64x4_Second{ 32, 15, 67, 12 };
static Array<U64, 4> arrU64x4_SelectMixed{ 32, 24, 67, 53 };
SIMD256_COMPILE_TIME_BLEND_TESTS(U64_4Lanes_SelectFirst, U64, 4, arrU64x4_First, arrU64x4_Second, arrU64x4_First, F, F, F, F)
SIMD256_COMPILE_TIME_BLEND_TESTS(U64_4Lanes_SelectSecond, U64, 4, arrU64x4_First, arrU64x4_Second, arrU64x4_Second, T, T, T, T)
SIMD256_COMPILE_TIME_BLEND_TESTS(U64_4Lanes_SelectMixed, U64, 4, arrU64x4_First, arrU64x4_Second, arrU64x4_SelectMixed, T, F, T, F)


// Signed Integrals
static Array<I8, 32> arrI8x32_First{ 9, 3, 9, 79, 123, 75, 107, 55, 115, 122, 32, 76, 100, 127, 0, 65, 118, 4, 74, 67, 54, 61, 83, 47, 79, 61, 70, 79, 115, 48, 4, 97 };
static Array<I8, 32> arrI8x32_Second{ 50, 112, 22, 123, 86, 66, 6, 127, 17, 60, 12, 62, 120, 24, 20, 102, 21, 48, 73, 32, 100, 43, 108, 124, 25, 48, 99, 32, 106, 26, 2, 114 };
static Array<I8, 32> arrI8x32_SelectMixed{ 50, 3, 22, 79, 86, 75, 6, 55, 17, 122, 12, 76, 120, 127, 20, 65, 21, 4, 73, 67, 100, 61, 108, 47, 25, 61, 99, 79, 106, 48, 2, 97 };
SIMD256_COMPILE_TIME_BLEND_TESTS(I8_32Lanes_SelectFirst, I8, 32, arrI8x32_First, arrI8x32_Second, arrI8x32_First, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F)
SIMD256_COMPILE_TIME_BLEND_TESTS(I8_32Lanes_SelectSecond, I8, 32, arrI8x32_First, arrI8x32_Second, arrI8x32_Second, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T)
SIMD256_COMPILE_TIME_BLEND_TESTS(I8_32Lanes_SelectMixed, I8, 32, arrI8x32_First, arrI8x32_Second, arrI8x32_SelectMixed, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F)

static Array<I16, 16> arrI16x16_First{ 100, 123, 121, 53, 16, 34, 21, 24, 33, 15, 121, 127, 35, 14, 96, 88 };
static Array<I16, 16> arrI16x16_Second{ 32, 15, 67, 12, 93, 32, 12, 47, 4, 120, 11, 31, 12, 7, 82, 99 };
static Array<I16, 16> arrI16x16_SelectMixed{ 32, 123, 67, 53, 93, 34, 12, 24, 4, 15, 11, 127, 12, 14, 82, 88 };
SIMD256_COMPILE_TIME_BLEND_TESTS(I16_16Lanes_SelectFirst, I16, 16, arrI16x16_First, arrI16x16_Second, arrI16x16_First, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F)
SIMD256_COMPILE_TIME_BLEND_TESTS(I16_16Lanes_SelectSecond, I16, 16, arrI16x16_First, arrI16x16_Second, arrI16x16_Second, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T)
SIMD256_COMPILE_TIME_BLEND_TESTS(I16_16Lanes_SelectMixed, I16, 16, arrI16x16_First, arrI16x16_Second, arrI16x16_SelectMixed, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F)

static Array<I32, 8> arrI32x8_First{ 100, 28, 121, 53, 8, 34, 21, 24 };
static Array<I32, 8> arrI32x8_Second{ 32, 15, 67, 12, 93, 32, 98, 47 };
static Array<I32, 8> arrI32x8_SelectMixed{ 32, 28, 67, 53, 93, 34, 98, 24 };
SIMD256_COMPILE_TIME_BLEND_TESTS(I32_8Lanes_SelectFirst, I32, 8, arrI32x8_First, arrI32x8_Second, arrI32x8_First, F, F, F, F, F, F, F, F)
SIMD256_COMPILE_TIME_BLEND_TESTS(I32_8Lanes_SelectSecond, I32, 8, arrI32x8_First, arrI32x8_Second, arrI32x8_Second, T, T, T, T, T, T, T, T)
SIMD256_COMPILE_TIME_BLEND_TESTS(I32_8Lanes_SelectMixed, I32, 8, arrI32x8_First, arrI32x8_Second, arrI32x8_SelectMixed, T, F, T, F, T, F, T, F)

static Array<I64, 4> arrI64x4_First{ 100, 24, 121, 53 };
static Array<I64, 4> arrI64x4_Second{ 32, 15, 67, 12 };
static Array<I64, 4> arrI64x4_SelectMixed{ 32, 24, 67, 53 };
SIMD256_COMPILE_TIME_BLEND_TESTS(I64_4Lanes_SelectFirst, I64, 4, arrI64x4_First, arrI64x4_Second, arrI64x4_First, F, F, F, F)
SIMD256_COMPILE_TIME_BLEND_TESTS(I64_4Lanes_SelectSecond, I64, 4, arrI64x4_First, arrI64x4_Second, arrI64x4_Second, T, T, T, T)
SIMD256_COMPILE_TIME_BLEND_TESTS(I64_4Lanes_SelectMixed, I64, 4, arrI64x4_First, arrI64x4_Second, arrI64x4_SelectMixed, T, F, T, F)


// Floating Point Types
static Array<FP32, 8> arrFP32x8_First{ 100, 28, 121, 53, 8, 34, 21, 24 };
static Array<FP32, 8> arrFP32x8_Second{ 32, 15, 67, 12, 93, 32, 98, 47 };
static Array<FP32, 8> arrFP32x8_SelectMixed{ 32, 28, 67, 53, 93, 34, 98, 24 };
SIMD256_COMPILE_TIME_BLEND_TESTS(FP32_8Lanes_SelectFirst, FP32, 8, arrFP32x8_First, arrFP32x8_Second, arrFP32x8_First, F, F, F, F, F, F, F, F)
SIMD256_COMPILE_TIME_BLEND_TESTS(FP32_8Lanes_SelectSecond, FP32, 8, arrFP32x8_First, arrFP32x8_Second, arrFP32x8_Second, T, T, T, T, T, T, T, T)
SIMD256_COMPILE_TIME_BLEND_TESTS(FP32_8Lanes_SelectMixed, FP32, 8, arrFP32x8_First, arrFP32x8_Second, arrFP32x8_SelectMixed, T, F, T, F, T, F, T, F)

static Array<FP64, 4> arrFP64x4_First{ 100, 24, 121, 53 };
static Array<FP64, 4> arrFP64x4_Second{ 32, 15, 67, 12 };
static Array<FP64, 4> arrFP64x4_SelectMixed{ 32, 24, 67, 53 };
SIMD256_COMPILE_TIME_BLEND_TESTS(FP64_4Lanes_SelectFirst, FP64, 4, arrFP64x4_First, arrFP64x4_Second, arrFP64x4_First, F, F, F, F)
SIMD256_COMPILE_TIME_BLEND_TESTS(FP64_4Lanes_SelectSecond, FP64, 4, arrFP64x4_First, arrFP64x4_Second, arrFP64x4_Second, T, T, T, T)
SIMD256_COMPILE_TIME_BLEND_TESTS(FP64_4Lanes_SelectMixed, FP64, 4, arrFP64x4_First, arrFP64x4_Second, arrFP64x4_SelectMixed, T, F, T, F)

// clang-format on


/// ================================ END COMPILE TIME BLEND TESTS ================================

/** @} */

#endif
