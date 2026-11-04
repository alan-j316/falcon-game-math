/**
 * @file BlendTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 05, 2026
 *
 * @brief Verifies Simd128 blending operations.
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
 * @addtogroup T_SIMD128_Permute
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
    struct Simd128BlendTestParam
    {
        using Type                            = T;
        static constexpr size_t REGISTER_SIZE = 128;
        static constexpr size_t LaneCount     = Lanes;
        static constexpr auto First           = first;
        static constexpr auto Second          = second;
        static constexpr auto Mask            = mask;
        static constexpr auto Expected        = expected;
        const char* TypeName                  = typeid(Type).name();

        // TODO: Fix pretty function not being used.
        friend std::ostream& operator<<(std::ostream& os, const Simd128BlendTestParam& param)
        { return os << "Simd128BlendTestParam(Type=" << param.TypeName << ", Lanes" << param.LaneCount << ")"; }

        // friend void PrintTo(const Simd128BlendTestParam& param, std::ostream* os)
        // { *os << "Simd128BlendTestParam(Type=" << param.TypeName << ", Lanes" << param.LaneCount << ")"; }
    };


    using Simd128BlendTestTypeHints = testing::Types<
        // Unsigned types
        Simd128BlendTestParam<U8, 2, Array<U8, 2>{ 100, 24 }, Array<U8, 2>{ 32, 15 }, Array<U8, 2>{ 0, ONE<U8> },
                              Array<U8, 2>{ 100, 15 }>,
        Simd128BlendTestParam<U8, 4, Array<U8, 4>{ 100, 24, 13, 15 }, Array<U8, 4>{ 32, 15, 61, 14 },
                              Array<U8, 4>{ 0, ONE<U8>, ONE<U8>, 0 }, Array<U8, 4>{ 100, 15, 61, 15 }>,
        Simd128BlendTestParam<U8, 8, Array<U8, 8>{ 100, 24, 13, 15, 32, 15, 71, 44 },
                              Array<U8, 8>{ 32, 15, 61, 14, 46, 55, 21, 74 },
                              Array<U8, 8>{ 0, ONE<U8>, ONE<U8>, 0, ONE<U8>, 0, 0, ONE<U8> },
                              Array<U8, 8>{ 100, 15, 61, 15, 46, 15, 71, 74 }>,
        Simd128BlendTestParam<U8, 16, Array<U8, 16>{ 100, 24, 13, 15, 32, 15, 71, 44, 100, 24, 13, 15, 32, 15, 71, 44 },
                              Array<U8, 16>{ 32, 15, 61, 14, 46, 55, 21, 74, 32, 15, 61, 14, 46, 55, 21, 74 },
                              Array<U8, 16>{ 0, ONE<U8>, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, 0, ONE<U8>, ONE<U8>, 0,
                                             ONE<U8>, 0, 0, ONE<U8>, 0 },
                              Array<U8, 16>{ 100, 15, 61, 15, 46, 15, 21, 44, 32, 15, 13, 14, 32, 15, 21, 44 }>,

        Simd128BlendTestParam<U16, 2, Array<U16, 2>{ 100, 24 }, Array<U16, 2>{ 32, 15 }, Array<U16, 2>{ 0, ONE<U16> },
                              Array<U16, 2>{ 100, 15 }>,
        Simd128BlendTestParam<U16, 4, Array<U16, 4>{ 100, 24, 13, 15 }, Array<U16, 4>{ 32, 15, 61, 14 },
                              Array<U16, 4>{ 0, ONE<U16>, ONE<U16>, 0 }, Array<U16, 4>{ 100, 15, 61, 15 }>,
        Simd128BlendTestParam<U16, 8, Array<U16, 8>{ 100, 24, 13, 15, 32, 15, 71, 44 },
                              Array<U16, 8>{ 32, 15, 61, 14, 46, 55, 21, 74 },
                              Array<U16, 8>{ 0, ONE<U16>, ONE<U16>, 0, ONE<U16>, 0, 0, ONE<U16> },
                              Array<U16, 8>{ 100, 15, 61, 15, 46, 15, 71, 74 }>,

        Simd128BlendTestParam<U32, 2, Array<U32, 2>{ 100, 24 }, Array<U32, 2>{ 32, 15 }, Array<U32, 2>{ 0, ONE<U32> },
                              Array<U32, 2>{ 100, 15 }>,
        Simd128BlendTestParam<U32, 4, Array<U32, 4>{ 100, 24, 13, 15 }, Array<U32, 4>{ 32, 15, 61, 14 },
                              Array<U32, 4>{ 0, ONE<U32>, ONE<U32>, 0 }, Array<U32, 4>{ 100, 15, 61, 15 }>,
        Simd128BlendTestParam<U64, 2, Array<U64, 2>{ 100, 24 }, Array<U64, 2>{ 32, 15 }, Array<U64, 2>{ 0, ONE<U32> },
                              Array<U64, 2>{ 100, 15 }>,

        // Signed types
        Simd128BlendTestParam<I8, 2, Array<I8, 2>{ 100, 24 }, Array<I8, 2>{ 32, 15 }, Array<I8, 2>{ 0, ONE<I8> },
                              Array<I8, 2>{ 100, 15 }>,
        Simd128BlendTestParam<I8, 4, Array<I8, 4>{ 100, 24, 13, 15 }, Array<I8, 4>{ 32, 15, 61, 14 },
                              Array<I8, 4>{ 0, ONE<I8>, ONE<I8>, 0 }, Array<I8, 4>{ 100, 15, 61, 15 }>,
        Simd128BlendTestParam<I8, 8, Array<I8, 8>{ 100, 24, 13, 15, 32, 15, 71, 44 },
                              Array<I8, 8>{ 32, 15, 61, 14, 46, 55, 21, 74 },
                              Array<I8, 8>{ 0, ONE<I8>, ONE<I8>, 0, ONE<I8>, 0, 0, ONE<I8> },
                              Array<I8, 8>{ 100, 15, 61, 15, 46, 15, 71, 74 }>,

        Simd128BlendTestParam<I8, 16, Array<I8, 16>{ 100, 24, 13, 15, 32, 15, 71, 44, 100, 24, 13, 15, 32, 15, 71, 44 },
                              Array<I8, 16>{ 32, 15, 61, 14, 46, 55, 21, 74, 32, 15, 61, 14, 46, 55, 21, 74 },
                              Array<I8, 16>{ 0, ONE<I8>, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, 0, ONE<I8>, ONE<I8>, 0,
                                             ONE<I8>, 0, 0, ONE<I8>, 0 },
                              Array<I8, 16>{ 100, 15, 61, 15, 46, 15, 21, 44, 32, 15, 13, 14, 32, 15, 21, 44 }>,

        Simd128BlendTestParam<I16, 2, Array<I16, 2>{ 100, 24 }, Array<I16, 2>{ 32, 15 }, Array<I16, 2>{ 0, ONE<I16> },
                              Array<I16, 2>{ 100, 15 }>,
        Simd128BlendTestParam<I16, 4, Array<I16, 4>{ 100, 24, 13, 15 }, Array<I16, 4>{ 32, 15, 61, 14 },
                              Array<I16, 4>{ 0, ONE<I16>, ONE<I16>, 0 }, Array<I16, 4>{ 100, 15, 61, 15 }>,
        Simd128BlendTestParam<I16, 8, Array<I16, 8>{ 100, 24, 13, 15, 32, 15, 71, 44 },
                              Array<I16, 8>{ 32, 15, 61, 14, 46, 55, 21, 74 },
                              Array<I16, 8>{ 0, ONE<I16>, ONE<I16>, 0, ONE<I16>, 0, 0, ONE<I16> },
                              Array<I16, 8>{ 100, 15, 61, 15, 46, 15, 71, 74 }>,

        Simd128BlendTestParam<I32, 2, Array<I32, 2>{ 100, 24 }, Array<I32, 2>{ 32, 15 }, Array<I32, 2>{ 0, ONE<I32> },
                              Array<I32, 2>{ 100, 15 }>,
        Simd128BlendTestParam<I32, 4, Array<I32, 4>{ 100, 24, 13, 15 }, Array<I32, 4>{ 32, 15, 61, 14 },
                              Array<I32, 4>{ 0, ONE<I32>, ONE<I32>, 0 }, Array<I32, 4>{ 100, 15, 61, 15 }>,
        Simd128BlendTestParam<I64, 2, Array<I64, 2>{ 100, 24 }, Array<I64, 2>{ 32, 15 }, Array<I64, 2>{ 0, ONE<I32> },
                              Array<I64, 2>{ 100, 15 }>,

        // Floating point types
        Simd128BlendTestParam<FP32, 2, Array<FP32, 2>{ 100.0f, 24.123849f }, Array<FP32, 2>{ 32.123f, 15.456f },
                              Array<FP32, 2>{ 0, ONE<FP32> }, Array<FP32, 2>{ 100.0f, 15.456f }>,
        Simd128BlendTestParam<FP32, 4, Array<FP32, 4>{ 100.0f, 24.123849f, 13.1234f, 15.482f },
                              Array<FP32, 4>{ 32.123f, 15.456f, 61.512f, 14.256f },
                              Array<FP32, 4>{ 0, ONE<FP32>, ONE<FP32>, 0 },
                              Array<FP32, 4>{ 100.0f, 15.456f, 61.512f, 15.482f }>,
        Simd128BlendTestParam<FP64, 2, Array<FP64, 2>{ 100.0, 24.123849 }, Array<FP64, 2>{ 32.123, 15.456 },
                              Array<FP64, 2>{ 0, ONE<FP64> }, Array<FP64, 2>{ 100.0, 15.456 }>>;

    /// @brief Test fixture for Simd128 blending operations.
    template <typename>
    class Simd128BlendTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Simd128BlendTests, Simd128BlendTestTypeHints);

} // namespace


TYPED_TEST(Simd128BlendTests, RuntimeBlendingWithMask_ReturnsRegisterWithCorrectValues)
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
    flcn::Simd128_t<Type, Lanes> regA{}, regB{}, mask{};
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

template <typename T, size_t Size>
constexpr std::array<bool, Size> ArrToBool(const std::array<T, Size>& array)
{
    std::array<bool, Size> boolArr;
    for (size_t i = 0; i < Size; ++i)
    {
        boolArr[i] = static_cast<bool>(array[i]);
    }
    return boolArr;
}



/// =============================== START COMPILE TIME BLEND TESTS ===============================

    #define SIMD128_COMPILE_TIME_BLEND_TESTS(TestSuffix, Type, Lanes, First, Second, Expected, ...)                    \
        TEST(Simd128BlendTests, CompileTimeBlendingWithMask_ReturnsValidRegister_For##TestSuffix)                      \
        {                                                                                                              \
            flcn::Simd128_t<Type, Lanes> regA{}, regB{};                                                             \
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
static Array<U8, 2> arrU8x2_First{ 100, 24 };
static Array<U8, 2> arrU8x2_Second{ 32, 15 };
static Array<U8, 2> arrU8x2_SelectMixed{ 32, 24 };
SIMD128_COMPILE_TIME_BLEND_TESTS(U8_2Lanes_SelectFirst, U8, 2, arrU8x2_First, arrU8x2_Second, arrU8x2_First, F, F)
SIMD128_COMPILE_TIME_BLEND_TESTS(U8_2Lanes_SelectSecond, U8, 2, arrU8x2_First, arrU8x2_Second, arrU8x2_Second, T, T)
SIMD128_COMPILE_TIME_BLEND_TESTS(U8_2Lanes_SelectMixed, U8, 2, arrU8x2_First, arrU8x2_Second, arrU8x2_SelectMixed, T, F)

static Array<U8, 4> arrU8x4_First{ 100, 24, 121, 53 };
static Array<U8, 4> arrU8x4_Second{ 32, 15, 67, 12 };
static Array<U8, 4> arrU8x4_SelectMixed{ 32, 24, 67, 53 };
SIMD128_COMPILE_TIME_BLEND_TESTS(U8_4Lanes_SelectFirst, U8, 4, arrU8x4_First, arrU8x4_Second, arrU8x4_First, F, F, F, F)
SIMD128_COMPILE_TIME_BLEND_TESTS(U8_4Lanes_SelectSecond, U8, 4, arrU8x4_First, arrU8x4_Second, arrU8x4_Second, T, T, T, T)
SIMD128_COMPILE_TIME_BLEND_TESTS(U8_4Lanes_SelectMixed, U8, 4, arrU8x4_First, arrU8x4_Second, arrU8x4_SelectMixed, T, F, T, F)

static Array<U8, 8> arrU8x8_First{ 100, 28, 121, 53, 8, 34, 21, 24 }; // 28, 53, 34, 24
static Array<U8, 8> arrU8x8_Second{ 32, 15, 67, 12, 93, 32, 98, 47 }; // 32, 28, 67, 53, 93, 34, 98, 24
static Array<U8, 8> arrU8x8_SelectMixed{ 32, 28, 67, 53, 93, 34, 98, 24 };
SIMD128_COMPILE_TIME_BLEND_TESTS(U8_8Lanes_SelectFirst, U8, 8, arrU8x8_First, arrU8x8_Second, arrU8x8_First, F, F, F, F, F, F, F, F)
SIMD128_COMPILE_TIME_BLEND_TESTS(U8_8Lanes_SelectSecond, U8, 8, arrU8x8_First, arrU8x8_Second, arrU8x8_Second, T, T, T, T, T, T, T, T)
SIMD128_COMPILE_TIME_BLEND_TESTS(U8_8Lanes_SelectMixed, U8, 8, arrU8x8_First, arrU8x8_Second, arrU8x8_SelectMixed, T, F, T, F, T, F, T, F)

static Array<U8, 16> arrU8x16_First{ 100, 123, 121, 53, 16, 34, 21, 24, 33, 15, 121, 127, 35, 14, 96, 88 };
static Array<U8, 16> arrU8x16_Second{ 32, 15, 67, 12, 93, 32, 12, 47, 4, 120, 11, 31, 12, 7, 82, 99 };
static Array<U8, 16> arrU8x16_SelectMixed{ 32, 123, 67, 53, 93, 34, 12, 24, 4, 15, 11, 127, 12, 14, 82, 88 };
SIMD128_COMPILE_TIME_BLEND_TESTS(U8_16Lanes_SelectFirst, U8, 16, arrU8x16_First, arrU8x16_Second, arrU8x16_First, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F)
SIMD128_COMPILE_TIME_BLEND_TESTS(U8_16Lanes_SelectSecond, U8, 16, arrU8x16_First, arrU8x16_Second, arrU8x16_Second, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T)
SIMD128_COMPILE_TIME_BLEND_TESTS(U8_16Lanes_SelectMixed, U8, 16, arrU8x16_First, arrU8x16_Second, arrU8x16_SelectMixed, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F)

static Array<U16, 2> arrU16x2_First{ 100, 24 };
static Array<U16, 2> arrU16x2_Second{ 32, 15 };
static Array<U16, 2> arrU16x2_SelectMixed{ 32, 24 };
SIMD128_COMPILE_TIME_BLEND_TESTS(U16_2Lanes_SelectFirst, U16, 2, arrU16x2_First, arrU16x2_Second, arrU16x2_First, F, F)
SIMD128_COMPILE_TIME_BLEND_TESTS(U16_2Lanes_SelectSecond, U16, 2, arrU16x2_First, arrU16x2_Second, arrU16x2_Second, T, T)
SIMD128_COMPILE_TIME_BLEND_TESTS(U16_2Lanes_SelectMixed, U16, 2, arrU16x2_First, arrU16x2_Second, arrU16x2_SelectMixed, T, F)

static Array<U16, 4> arrU16x4_First{ 100, 24, 121, 53 };
static Array<U16, 4> arrU16x4_Second{ 32, 15, 67, 12 };
static Array<U16, 4> arrU16x4_SelectMixed{ 32, 24, 67, 53 };
SIMD128_COMPILE_TIME_BLEND_TESTS(U16_4Lanes_SelectFirst, U16, 4, arrU16x4_First, arrU16x4_Second, arrU16x4_First, F, F, F, F)
SIMD128_COMPILE_TIME_BLEND_TESTS(U16_4Lanes_SelectSecond, U16, 4, arrU16x4_First, arrU16x4_Second, arrU16x4_Second, T, T, T, T)
SIMD128_COMPILE_TIME_BLEND_TESTS(U16_4Lanes_SelectMixed, U16, 4, arrU16x4_First, arrU16x4_Second, arrU16x4_SelectMixed, T, F, T, F)

static Array<U16, 8> arrU16x8_First{ 100, 28, 121, 53, 8, 34, 21, 24 };
static Array<U16, 8> arrU16x8_Second{ 32, 15, 67, 12, 93, 32, 98, 47 };
static Array<U16, 8> arrU16x8_SelectMixed{ 32, 28, 67, 53, 93, 34, 98, 24 };
SIMD128_COMPILE_TIME_BLEND_TESTS(U16_8Lanes_SelectFirst, U16, 8, arrU16x8_First, arrU16x8_Second, arrU16x8_First, F, F, F, F, F, F, F, F)
SIMD128_COMPILE_TIME_BLEND_TESTS(U16_8Lanes_SelectSecond, U16, 8, arrU16x8_First, arrU16x8_Second, arrU16x8_Second, T, T, T, T, T, T, T, T)
SIMD128_COMPILE_TIME_BLEND_TESTS(U16_8Lanes_SelectMixed, U16, 8, arrU16x8_First, arrU16x8_Second, arrU16x8_SelectMixed, T, F, T, F, T, F, T, F)

static Array<U32, 2> arrU32x2_First{ 100, 24 };
static Array<U32, 2> arrU32x2_Second{ 32, 15 };
static Array<U32, 2> arrU32x2_SelectMixed{ 32, 24 };
SIMD128_COMPILE_TIME_BLEND_TESTS(U32_2Lanes_SelectFirst, U32, 2, arrU32x2_First, arrU32x2_Second, arrU32x2_First, F, F)
SIMD128_COMPILE_TIME_BLEND_TESTS(U32_2Lanes_SelectSecond, U32, 2, arrU32x2_First, arrU32x2_Second, arrU32x2_Second, T, T)
SIMD128_COMPILE_TIME_BLEND_TESTS(U32_2Lanes_SelectMixed, U32, 2, arrU32x2_First, arrU32x2_Second, arrU32x2_SelectMixed, T, F)

static Array<U32, 4> arrU32x4_First{ 100, 24, 121, 53 };
static Array<U32, 4> arrU32x4_Second{ 32, 15, 67, 12 };
static Array<U32, 4> arrU32x4_SelectMixed{ 32, 24, 67, 53 };
SIMD128_COMPILE_TIME_BLEND_TESTS(U32_4Lanes_SelectFirst, U32, 4, arrU32x4_First, arrU32x4_Second, arrU32x4_First, F, F, F, F)
SIMD128_COMPILE_TIME_BLEND_TESTS(U32_4Lanes_SelectSecond, U32, 4, arrU32x4_First, arrU32x4_Second, arrU32x4_Second, T, T, T, T)
SIMD128_COMPILE_TIME_BLEND_TESTS(U32_4Lanes_SelectMixed, U32, 4, arrU32x4_First, arrU32x4_Second, arrU32x4_SelectMixed, T, F, T, F)

static Array<U64, 2> arrU64x2_First{ 100, 24 };
static Array<U64, 2> arrU64x2_Second{ 32, 15 };
static Array<U64, 2> arrU64x2_SelectMixed{ 32, 24 };
SIMD128_COMPILE_TIME_BLEND_TESTS(U64_2Lanes_SelectFirst, U64, 2, arrU64x2_First, arrU64x2_Second, arrU64x2_First, F, F)
SIMD128_COMPILE_TIME_BLEND_TESTS(U64_2Lanes_SelectSecond, U64, 2, arrU64x2_First, arrU64x2_Second, arrU64x2_Second, T, T)
SIMD128_COMPILE_TIME_BLEND_TESTS(U64_2Lanes_SelectMixed, U64, 2, arrU64x2_First, arrU64x2_Second, arrU64x2_SelectMixed, T, F)

// Signed Integrals
static Array<I8, 2> arrI8x2_First{ 100, 24 };
static Array<I8, 2> arrI8x2_Second{ 32, 15 };
static Array<I8, 2> arrI8x2_SelectMixed{ 32, 24 };
SIMD128_COMPILE_TIME_BLEND_TESTS(I8_2Lanes_SelectFirst, I8, 2, arrI8x2_First, arrI8x2_Second, arrI8x2_First, F, F)
SIMD128_COMPILE_TIME_BLEND_TESTS(I8_2Lanes_SelectSecond, I8, 2, arrI8x2_First, arrI8x2_Second, arrI8x2_Second, T, T)
SIMD128_COMPILE_TIME_BLEND_TESTS(I8_2Lanes_SelectMixed, I8, 2, arrI8x2_First, arrI8x2_Second, arrI8x2_SelectMixed, T, F)

static Array<I8, 4> arrI8x4_First{ 100, 24, 121, 53 };
static Array<I8, 4> arrI8x4_Second{ 32, 15, 67, 12 };
static Array<I8, 4> arrI8x4_SelectMixed{ 32, 24, 67, 53 };
SIMD128_COMPILE_TIME_BLEND_TESTS(I8_4Lanes_SelectFirst, I8, 4, arrI8x4_First, arrI8x4_Second, arrI8x4_First, F, F, F, F)
SIMD128_COMPILE_TIME_BLEND_TESTS(I8_4Lanes_SelectSecond, I8, 4, arrI8x4_First, arrI8x4_Second, arrI8x4_Second, T, T, T, T)
SIMD128_COMPILE_TIME_BLEND_TESTS(I8_4Lanes_SelectMixed, I8, 4, arrI8x4_First, arrI8x4_Second, arrI8x4_SelectMixed, T, F, T, F)

static Array<I8, 8> arrI8x8_First{ 100, 28, 121, 53, 8, 34, 21, 24 };
static Array<I8, 8> arrI8x8_Second{ 32, 15, 67, 12, 93, 32, 98, 47 };
static Array<I8, 8> arrI8x8_SelectMixed{ 32, 28, 67, 53, 93, 34, 98, 24 };
SIMD128_COMPILE_TIME_BLEND_TESTS(I8_8Lanes_SelectFirst, I8, 8, arrI8x8_First, arrI8x8_Second, arrI8x8_First, F, F, F, F, F, F, F, F)
SIMD128_COMPILE_TIME_BLEND_TESTS(I8_8Lanes_SelectSecond, I8, 8, arrI8x8_First, arrI8x8_Second, arrI8x8_Second, T, T, T, T, T, T, T, T)
SIMD128_COMPILE_TIME_BLEND_TESTS(I8_8Lanes_SelectMixed, I8, 8, arrI8x8_First, arrI8x8_Second, arrI8x8_SelectMixed, T, F, T, F, T, F, T, F)

static Array<I8, 16> arrI8x16_First{ 100, 123, 121, 53, 16, 34, 21, 24, 33, 15, 121, 127, 35, 14, 96, 88 };
static Array<I8, 16> arrI8x16_Second{ 32, 15, 67, 12, 93, 32, 12, 47, 4, 120, 11, 31, 12, 7, 82, 99 };
static Array<I8, 16> arrI8x16_SelectMixed{ 32, 123, 67, 53, 93, 34, 12, 24, 4, 15, 11, 127, 12, 14, 82, 88 };
SIMD128_COMPILE_TIME_BLEND_TESTS(I8_16Lanes_SelectFirst, I8, 16, arrI8x16_First, arrI8x16_Second, arrI8x16_First, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F)
SIMD128_COMPILE_TIME_BLEND_TESTS(I8_16Lanes_SelectSecond, I8, 16, arrI8x16_First, arrI8x16_Second, arrI8x16_Second, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T)
SIMD128_COMPILE_TIME_BLEND_TESTS(I8_16Lanes_SelectMixed, I8, 16, arrI8x16_First, arrI8x16_Second, arrI8x16_SelectMixed, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F)

static Array<I16, 2> arrI16x2_First{ 100, 24 };
static Array<I16, 2> arrI16x2_Second{ 32, 15 };
static Array<I16, 2> arrI16x2_SelectMixed{ 32, 24 };
SIMD128_COMPILE_TIME_BLEND_TESTS(I16_2Lanes_SelectFirst, I16, 2, arrI16x2_First, arrI16x2_Second, arrI16x2_First, F, F)
SIMD128_COMPILE_TIME_BLEND_TESTS(I16_2Lanes_SelectSecond, I16, 2, arrI16x2_First, arrI16x2_Second, arrI16x2_Second, T, T)
SIMD128_COMPILE_TIME_BLEND_TESTS(I16_2Lanes_SelectMixed, I16, 2, arrI16x2_First, arrI16x2_Second, arrI16x2_SelectMixed, T, F)

static Array<I16, 4> arrI16x4_First{ 100, 24, 121, 53 };
static Array<I16, 4> arrI16x4_Second{ 32, 15, 67, 12 };
static Array<I16, 4> arrI16x4_SelectMixed{ 32, 24, 67, 53 };
SIMD128_COMPILE_TIME_BLEND_TESTS(I16_4Lanes_SelectFirst, I16, 4, arrI16x4_First, arrI16x4_Second, arrI16x4_First, F, F, F, F)
SIMD128_COMPILE_TIME_BLEND_TESTS(I16_4Lanes_SelectSecond, I16, 4, arrI16x4_First, arrI16x4_Second, arrI16x4_Second, T, T, T, T)
SIMD128_COMPILE_TIME_BLEND_TESTS(I16_4Lanes_SelectMixed, I16, 4, arrI16x4_First, arrI16x4_Second, arrI16x4_SelectMixed, T, F, T, F)

static Array<I16, 8> arrI16x8_First{ 100, 28, 121, 53, 8, 34, 21, 24 };
static Array<I16, 8> arrI16x8_Second{ 32, 15, 67, 12, 93, 32, 98, 47 };
static Array<I16, 8> arrI16x8_SelectMixed{ 32, 28, 67, 53, 93, 34, 98, 24 };
SIMD128_COMPILE_TIME_BLEND_TESTS(I16_8Lanes_SelectFirst, I16, 8, arrI16x8_First, arrI16x8_Second, arrI16x8_First, F, F, F, F, F, F, F, F)
SIMD128_COMPILE_TIME_BLEND_TESTS(I16_8Lanes_SelectSecond, I16, 8, arrI16x8_First, arrI16x8_Second, arrI16x8_Second, T, T, T, T, T, T, T, T)
SIMD128_COMPILE_TIME_BLEND_TESTS(I16_8Lanes_SelectMixed, I16, 8, arrI16x8_First, arrI16x8_Second, arrI16x8_SelectMixed, T, F, T, F, T, F, T, F)

static Array<I32, 2> arrI32x2_First{ 100, 24 };
static Array<I32, 2> arrI32x2_Second{ 32, 15 };
static Array<I32, 2> arrI32x2_SelectMixed{ 32, 24 };
SIMD128_COMPILE_TIME_BLEND_TESTS(I32_2Lanes_SelectFirst, I32, 2, arrI32x2_First, arrI32x2_Second, arrI32x2_First, F, F)
SIMD128_COMPILE_TIME_BLEND_TESTS(I32_2Lanes_SelectSecond, I32, 2, arrI32x2_First, arrI32x2_Second, arrI32x2_Second, T, T)
SIMD128_COMPILE_TIME_BLEND_TESTS(I32_2Lanes_SelectMixed, I32, 2, arrI32x2_First, arrI32x2_Second, arrI32x2_SelectMixed, T, F)

static Array<I32, 4> arrI32x4_First{ 100, 24, 121, 53 };
static Array<I32, 4> arrI32x4_Second{ 32, 15, 67, 12 };
static Array<I32, 4> arrI32x4_SelectMixed{ 32, 24, 67, 53 };
SIMD128_COMPILE_TIME_BLEND_TESTS(I32_4Lanes_SelectFirst, I32, 4, arrI32x4_First, arrI32x4_Second, arrI32x4_First, F, F, F, F)
SIMD128_COMPILE_TIME_BLEND_TESTS(I32_4Lanes_SelectSecond, I32, 4, arrI32x4_First, arrI32x4_Second, arrI32x4_Second, T, T, T, T)
SIMD128_COMPILE_TIME_BLEND_TESTS(I32_4Lanes_SelectMixed, I32, 4, arrI32x4_First, arrI32x4_Second, arrI32x4_SelectMixed, T, F, T, F)

static Array<I64, 2> arrI64x2_First{ 100, 24 };
static Array<I64, 2> arrI64x2_Second{ 32, 15 };
static Array<I64, 2> arrI64x2_SelectMixed{ 32, 24 };
SIMD128_COMPILE_TIME_BLEND_TESTS(I64_2Lanes_SelectFirst, I64, 2, arrI64x2_First, arrI64x2_Second, arrI64x2_First, F, F)
SIMD128_COMPILE_TIME_BLEND_TESTS(I64_2Lanes_SelectSecond, I64, 2, arrI64x2_First, arrI64x2_Second, arrI64x2_Second, T, T)
SIMD128_COMPILE_TIME_BLEND_TESTS(I64_2Lanes_SelectMixed, I64, 2, arrI64x2_First, arrI64x2_Second, arrI64x2_SelectMixed, T, F)


// Floating Point Types
static Array<FP32, 2> arrFP32x2_First{ 100, 24 };
static Array<FP32, 2> arrFP32x2_Second{ 32, 15 };
static Array<FP32, 2> arrFP32x2_SelectMixed{ 32, 24 };
SIMD128_COMPILE_TIME_BLEND_TESTS(FP32_2Lanes_SelectFirst, FP32, 2, arrFP32x2_First, arrFP32x2_Second, arrFP32x2_First, F, F)
SIMD128_COMPILE_TIME_BLEND_TESTS(FP32_2Lanes_SelectSecond, FP32, 2, arrFP32x2_First, arrFP32x2_Second, arrFP32x2_Second, T, T)
SIMD128_COMPILE_TIME_BLEND_TESTS(FP32_2Lanes_SelectMixed, FP32, 2, arrFP32x2_First, arrFP32x2_Second, arrFP32x2_SelectMixed, T, F)

static Array<FP32, 4> arrFP32x4_First{ 100, 24, 121, 53 };
static Array<FP32, 4> arrFP32x4_Second{ 32, 15, 67, 12 };
static Array<FP32, 4> arrFP32x4_SelectMixed{ 32, 24, 67, 53 };
SIMD128_COMPILE_TIME_BLEND_TESTS(FP32_4Lanes_SelectFirst, FP32, 4, arrFP32x4_First, arrFP32x4_Second, arrFP32x4_First, F, F, F, F)
SIMD128_COMPILE_TIME_BLEND_TESTS(FP32_4Lanes_SelectSecond, FP32, 4, arrFP32x4_First, arrFP32x4_Second, arrFP32x4_Second, T, T, T, T)
SIMD128_COMPILE_TIME_BLEND_TESTS(FP32_4Lanes_SelectMixed, FP32, 4, arrFP32x4_First, arrFP32x4_Second, arrFP32x4_SelectMixed, T, F, T, F)

static Array<FP64, 2> arrFP64x2_First{ 100, 24 };
static Array<FP64, 2> arrFP64x2_Second{ 32, 15 };
static Array<FP64, 2> arrFP64x2_SelectMixed{ 32, 24 };
SIMD128_COMPILE_TIME_BLEND_TESTS(FP64_2Lanes_SelectFirst, FP64, 2, arrFP64x2_First, arrFP64x2_Second, arrFP64x2_First, F, F)
SIMD128_COMPILE_TIME_BLEND_TESTS(FP64_2Lanes_SelectSecond, FP64, 2, arrFP64x2_First, arrFP64x2_Second, arrFP64x2_Second, T, T)
SIMD128_COMPILE_TIME_BLEND_TESTS(FP64_2Lanes_SelectMixed, FP64, 2, arrFP64x2_First, arrFP64x2_Second, arrFP64x2_SelectMixed, T, F)

// clang-format on
/// ================================ END COMPILE TIME BLEND TESTS ================================



/** @} */

#endif
