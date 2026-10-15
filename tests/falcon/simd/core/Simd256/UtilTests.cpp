/**
 * @file UtilTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 16, 2026
 *
 * @brief Verifies Simd256 utilities like hasNaN or hasInf masked.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "SIMDTestSetup.h"


// TODO: Remove Preprocessor after implementing individual simd paths
#if defined(FALCON_ENABLE_AVX512) || defined(FALCON_ENABLE_AVX2) || defined(FALCON_ENABLE_AVX) ||                      \
    defined(FALCON_ENABLE_SSE4) || defined(FALCON_ENABLE_SSE2)


/**
 * @addtogroup T_SIMD256_Utils
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /// @brief Test fixture for hasNan utility.
    /// @tparam T The numeric type and Lane of test values.
    template <typename T>
    class Simd256UtilsTests: public testing::Test
    {
    public:
        using Type                = T::Type;
        static constexpr auto max = std::numeric_limits<Type>::max();
        static constexpr auto min = std::numeric_limits<Type>::min();
        // Note: Min is swapped with 1 in b to prevent seh
        std::array<typename T::Type, 32> nanVec, infVec, expectedNanVec, expectedInfVec;

    protected:
        void SetUp() override
        {
            if constexpr (std::is_floating_point_v<T>)
            {
                Type nan       = std::numeric_limits<Type>::quiet_NaN();
                Type inf       = std::numeric_limits<Type>::infinity();
                nanVec         = { nan, -5, nan, 2, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12,
                                   nan, -5, nan, 2, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12 };
                expectedNanVec = { Type(~0), 0, Type(~0), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   Type(~0), 0, Type(~0), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
                infVec         = { inf, -inf, inf, -inf, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12,
                                   inf, -inf, inf, -inf, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12 };
                expectedInfVec = { Type(~0), Type(~0), Type(~0), Type(~0), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   Type(~0), Type(~0), Type(~0), Type(~0), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            }
            else
            {
                nanVec         = { max, min, max, min, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12,
                                   max, min, max, min, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12 };
                infVec         = { max, min, max, min, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12,
                                   max, min, max, min, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12 };
                expectedNanVec = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
                expectedInfVec = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            }
        }
    };

    TYPED_TEST_SUITE(Simd256UtilsTests, Simd256RegisterTypeHints);

} // namespace


// template <typename T>
// static constexpr T NaN = std::numeric_limits<T>::quiet_NaN();
//
// template <typename T>
// static constexpr T Inf = std::numeric_limits<T>::infinity();
//

// TYPED_TEST(Simd256UtilsTests, HasNaN_ReturnsValidMask)
// {
//     using Type            = TypeParam::Type;
//     constexpr size_t Lane = TypeParam::VALUE;
//
//     alignas(32) std::array<Type, Lane> data{}, resultMask;
//     for (size_t i = 0; i < Lane; ++i)
//     {
//         data[i] = this->nanVec[i];
//     }
//     flcn::Simd256_t<Type, Lane> regA{ data };
//
//     auto regRes = regA.hasNan();
//
//     regRes.storeAligned(resultMask.data());
//
//     for (size_t i = 0; i < Lane; ++i)
//     {
//         EXPECT_ANY_EQ(this->expectedNanVec[i], resultMask[i]);
//     }
// }
//
//
// TYPED_TEST(Simd256UtilsTests, HasInf_ReturnsValidMask)
// {
//     using Type            = TypeParam::Type;
//     constexpr size_t Lane = TypeParam::VALUE;
//
//     alignas(32) std::array<Type, Lane> data{}, resultMask;
//     for (size_t i = 0; i < Lane; ++i)
//     {
//         data[i] = this->infVec[i];
//     }
//     flcn::Simd256_t<Type, Lane> regA{ data };
//
//     auto regRes = regA.hasInf();
//
//     regRes.storeAligned(resultMask.data());
//
//     for (size_t i = 0; i < Lane; ++i)
//     {
//         EXPECT_ANY_EQ(this->expectedInfVec[i], resultMask[i]);
//     }
// }



using namespace simd::testing;

// /// @test Verify that hasNan returns the correct simd mask for floating point types with various data patterns.
//     #define SIMD256_HAS_NAN_TESTS_FP(TestName, Type, Lane, Data, Expected)                                             \
//         TEST(Simd256_HasNaNTests, ReturnsValidMaskGiven_##TestName)                                                    \
//         {                                                                                                              \
//             flcn::Simd256_t<Type, Lane> regA{ Data };                                                                  \
//                                                                                                                        \
//             alignas(32) std::array<Type, Lane> resultMask{};                                                           \
//             auto regRes = regA.hasNan();                                                                               \
//             regRes.storeAligned(resultMask.data());                                                                    \
//                                                                                                                        \
//             for (size_t i = 0; i < Lane; ++i)                                                                          \
//             {                                                                                                          \
//                 EXPECT_ANY_EQ(Expected[i], resultMask[i]);                                                             \
//             }                                                                                                          \
//         }
//
// alignas(32) constexpr auto DATA_FP32_8LANES_NO_NAN = Array<FP32, 8>{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f };
// alignas(32) constexpr auto RES_FP32_8LANES_NO_NAN  = Array<FP32, 8>{ 0, 0, 0, 0, 0, 0, 0, 0 };
// SIMD256_HAS_NAN_TESTS_FP(FP32_8Lanes_NonNaN, FP32, 8, DATA_FP32_8LANES_NO_NAN, RES_FP32_8LANES_NO_NAN)
//
// alignas(32) constexpr auto DATA_FP32_8LANES_FULL_NAN =
//     Array<FP32, 8>{ NaN<FP32>, NaN<FP32>, NaN<FP32>, NaN<FP32>, NaN<FP32>, NaN<FP32>, NaN<FP32>, NaN<FP32> };
// alignas(32) constexpr auto RES_FP32_8LANES_FULL_NAN =
//     Array<FP32, 8>{ NaN<FP32>, NaN<FP32>, NaN<FP32>, NaN<FP32>, NaN<FP32>, NaN<FP32>, NaN<FP32>, NaN<FP32> };
// SIMD256_HAS_NAN_TESTS_FP(FP32_8Lanes_FullNaN, FP32, 8, DATA_FP32_8LANES_FULL_NAN, RES_FP32_8LANES_FULL_NAN)
//
// alignas(32) constexpr auto DATA_FP32_8LANES_MIXED_NAN =
//     Array<FP32, 8>{ 1.0f, NaN<FP32>, 1.0f, NaN<FP32>, 1.0f, NaN<FP32>, 1.0f, NaN<FP32> };
// alignas(32) constexpr auto RES_FP32_8LANES_MIXED_NAN = Array<FP32, 8>{ 0, NaN<FP32>, 0, NaN<FP32>, 0, NaN<FP32>, 0, NaN<FP32> };
// SIMD256_HAS_NAN_TESTS_FP(FP32_8Lanes_AlternatingNaN, FP32, 8, DATA_FP32_8LANES_MIXED_NAN, RES_FP32_8LANES_MIXED_NAN)
//
// alignas(32) constexpr auto DATA_FP64_4LANES_NO_NAN = Array<FP64, 4>{ 1.0f, 2.0f, 3.0f, 4.0f };
// alignas(32) constexpr auto RES_FP64_4LANES_NO_NAN  = Array<FP64, 4>{ 0, 0, 0, 0 };
// SIMD256_HAS_NAN_TESTS_FP(FP64_4Lanes_NonNaN, FP64, 4, DATA_FP64_4LANES_NO_NAN, RES_FP64_4LANES_NO_NAN)
//
// alignas(32) constexpr auto DATA_FP64_4LANES_FULL_NAN = Array<FP64, 4>{ NaN<FP64>, NaN<FP64>, NaN<FP64>, NaN<FP64> };
// alignas(32) constexpr auto RES_FP64_4LANES_FULL_NAN  = Array<FP64, 4>{ NaN<FP64>, NaN<FP64>, NaN<FP64>, NaN<FP64> };
// SIMD256_HAS_NAN_TESTS_FP(FP64_4Lanes_FullNaN, FP64, 4, DATA_FP64_4LANES_FULL_NAN, RES_FP64_4LANES_FULL_NAN)
//
// alignas(32) constexpr auto DATA_FP64_4LANES_MIXED_NAN = Array<FP64, 4>{ 1.0f, NaN<FP64>, 1.0f, NaN<FP64> };
// alignas(32) constexpr auto RES_FP64_4LANES_MIXED_NAN  = Array<FP64, 4>{ 0, NaN<FP64>, 0, NaN<FP64> };
// SIMD256_HAS_NAN_TESTS_FP(FP64_4Lanes_AlternatingNaN, FP64, 4, DATA_FP64_4LANES_MIXED_NAN, RES_FP64_4LANES_MIXED_NAN)
//
//
//
// /// @test Verify that hasInf returns the correct simd mask for floating point types with various data patterns.
//     #define SIMD256_HAS_INF_TESTS_FP(TestName, Type, Lane, Data, Expected)                                             \
//         TEST(Simd256_HasInfTests, ReturnsValidMaskGiven_##TestName)                                                    \
//         {                                                                                                              \
//             flcn::Simd256_t<Type, Lane> regA{ Data };                                                                  \
//                                                                                                                        \
//             alignas(32) std::array<Type, Lane> resultMask{};                                                           \
//             auto regRes = regA.hasInf();                                                                               \
//             regRes.storeAligned(resultMask.data());                                                                    \
//                                                                                                                        \
//             for (size_t i = 0; i < Lane; ++i)                                                                          \
//             {                                                                                                          \
//                 EXPECT_ANY_EQ(Expected[i], resultMask[i]);                                                             \
//             }                                                                                                          \
//         }
//
// alignas(32) constexpr auto DATA_FP32_8LANES_NO_INF = Array<FP32, 8>{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f };
// alignas(32) constexpr auto RES_FP32_8LANES_NO_INF  = Array<FP32, 8>{ 0, 0, 0, 0, 0, 0, 0, 0 };
// SIMD256_HAS_INF_TESTS_FP(FP32_8Lanes_NonInf, FP32, 8, DATA_FP32_8LANES_NO_INF, RES_FP32_8LANES_NO_INF)
//
// alignas(32) constexpr auto DATA_FP32_8LANES_FULL_INF =
//     Array<FP32, 8>{ Inf<FP32>, Inf<FP32>, Inf<FP32>, Inf<FP32>, Inf<FP32>, Inf<FP32>, Inf<FP32>, Inf<FP32> };
// alignas(32) constexpr auto RES_FP32_8LANES_FULL_INF =
//     Array<FP32, 8>{ NaN<FP32>, NaN<FP32>, NaN<FP32>, NaN<FP32>, NaN<FP32>, NaN<FP32>, NaN<FP32>, NaN<FP32> };
// SIMD256_HAS_INF_TESTS_FP(FP32_8Lanes_FullInf, FP32, 8, DATA_FP32_8LANES_FULL_INF, RES_FP32_8LANES_FULL_INF)
//
// alignas(32) constexpr auto DATA_FP32_8LANES_MIXED_INF =
//     Array<FP32, 8>{ 1.0f, Inf<FP32>, 1.0f, Inf<FP32>, 1.0f, Inf<FP32>, 1.0f, Inf<FP32> };
// alignas(32) constexpr auto RES_FP32_8LANES_MIXED_INF = Array<FP32, 8>{ 0, NaN<FP32>, 0, NaN<FP32>, 0, NaN<FP32>, 0, NaN<FP32> };
// SIMD256_HAS_INF_TESTS_FP(FP32_8Lanes_AlternatingInf, FP32, 8, DATA_FP32_8LANES_MIXED_INF, RES_FP32_8LANES_MIXED_INF)
//
// alignas(32) constexpr auto DATA_FP64_4LANES_NO_INF = Array<FP64, 4>{ 1.0f, 2.0f, 3.0f, 4.0f };
// alignas(32) constexpr auto RES_FP64_4LANES_NO_INF  = Array<FP64, 4>{ 0, 0, 0, 0 };
// SIMD256_HAS_INF_TESTS_FP(FP64_4Lanes_NonInf, FP64, 4, DATA_FP64_4LANES_NO_INF, RES_FP64_4LANES_NO_INF)
//
// alignas(32) constexpr auto DATA_FP64_4LANES_FULL_INF = Array<FP64, 4>{ Inf<FP64>, Inf<FP64>, Inf<FP64>, Inf<FP64> };
// alignas(32) constexpr auto RES_FP64_4LANES_FULL_INF  = Array<FP64, 4>{ NaN<FP64>, NaN<FP64>, NaN<FP64>, NaN<FP64> };
// SIMD256_HAS_INF_TESTS_FP(FP64_4Lanes_FullInf, FP64, 4, DATA_FP64_4LANES_FULL_INF, RES_FP64_4LANES_FULL_INF)
//
// alignas(32) constexpr auto DATA_FP64_4LANES_MIXED_INF = Array<FP64, 4>{ 1.0f, Inf<FP64>, 1.0f, Inf<FP64> };
// alignas(32) constexpr auto RES_FP64_4LANES_MIXED_INF  = Array<FP64, 4>{ 0, NaN<FP64>, 0, NaN<FP64> };
// SIMD256_HAS_INF_TESTS_FP(FP64_4Lanes_AlternatingInf, FP64, 4, DATA_FP64_4LANES_MIXED_INF, RES_FP64_4LANES_MIXED_INF)


/// =============================== START MAKE_BLEND_MASK ===============================

    /// @test Verify that makeBlendMask returns a correct mask a datatype and lane count.
    #define SIMD256_MAKE_BLEND_MASK_TESTS(TestSuffix, DataType, ExpectedMask, RegCount, ...)                           \
        TEST(Simd256_MakeBlendMaskTests, ReturnsValidMask_For##TestSuffix)                                             \
        {                                                                                                              \
            const flcn::Simd256_t<DataType, RegCount> reg{ DataType(0) };                                              \
            EXPECT_EQ(ExpectedMask, (reg.makeBlendMask<__VA_ARGS__>()));                                               \
        }

// Aliasing to make testing easier.
constexpr bool T = true;
constexpr bool F = false;

// clang-format off
// Unsigned types
SIMD256_MAKE_BLEND_MASK_TESTS(U8_ThirtyTwoLanes_AllTrue, U8, 0xFFFFFFFF, 32, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T)
SIMD256_MAKE_BLEND_MASK_TESTS(U8_ThirtyTwoLanes_AlternatingTrueFalse, U8, 0x55555555, 32, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F)
SIMD256_MAKE_BLEND_MASK_TESTS(U8_ThirtyTwoLanes_AlternatingFalseTrue, U8, 0xAAAAAAAA, 32, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T)
SIMD256_MAKE_BLEND_MASK_TESTS(U8_ThirtyTwoLanes_AllFalse, U8, 0x00000000, 32, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F)

SIMD256_MAKE_BLEND_MASK_TESTS(U16_SixteenLanes_WithAllTrue, U16, 0xFFFFFFFF, 16, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T)
SIMD256_MAKE_BLEND_MASK_TESTS(U16_SixteenLanes_WithAlternatingTrueFalse,U16, 0x33333333,  16, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F)
SIMD256_MAKE_BLEND_MASK_TESTS(U16_SixteenLanes_WithAlternatingFalseTrue,U16, 0xCCCCCCCC,  16, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T)
SIMD256_MAKE_BLEND_MASK_TESTS(U16_SixteenLanes_WithAllFalse, U16, 0x00000000, 16, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F)

SIMD256_MAKE_BLEND_MASK_TESTS(U32_EightLanes_WithAllTrue, U32, 0xFFFFFFFF, 8, T, T, T, T, T, T, T, T)
SIMD256_MAKE_BLEND_MASK_TESTS(U32_EightLanes_WithAlternatingTrueFalse, U32, 0x0F0F0F0F, 8, T, F, T, F, T, F, T, F)
SIMD256_MAKE_BLEND_MASK_TESTS(U32_EightLanes_WithAlternatingFalseTrue, U32, 0xF0F0F0F0, 8, F, T, F, T, F, T, F, T)
SIMD256_MAKE_BLEND_MASK_TESTS(U32_EightLanes_WithAllFalse, U32, 0x00000000, 8, F, F, F, F, F, F, F, F)

SIMD256_MAKE_BLEND_MASK_TESTS(U64_FourLanes_WithAllTrue, U64, 0xFFFFFFFF, 4, T, T, T, T)
SIMD256_MAKE_BLEND_MASK_TESTS(U64_FourLanes_WithAlternatingTrueFalse, U64, 0x00FF00FF, 4, T, F, T, F)
SIMD256_MAKE_BLEND_MASK_TESTS(U64_FourLanes_WithAlternatingFalseTrue, U64, 0xFF00FF00, 4, F, T, F, T)
SIMD256_MAKE_BLEND_MASK_TESTS(U64_FourLanes_WithAllFalse, U64, 0x00000000, 4, F, F, F, F)


// Signed Integrals
SIMD256_MAKE_BLEND_MASK_TESTS(I8_ThirtyTwoLanes_AllTrue, I8, 0xFFFFFFFF, 32, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T)
SIMD256_MAKE_BLEND_MASK_TESTS(I8_ThirtyTwoLanes_AlternatingTrueFalse, I8, 0x55555555, 32, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F)
SIMD256_MAKE_BLEND_MASK_TESTS(I8_ThirtyTwoLanes_AlternatingFalseTrue, I8, 0xAAAAAAAA, 32, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T)
SIMD256_MAKE_BLEND_MASK_TESTS(I8_ThirtyTwoLanes_AllFalse, I8, 0x00000000, 32, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F)

SIMD256_MAKE_BLEND_MASK_TESTS(I16_SixteenLanes_WithAllTrue, I16, 0xFFFFFFFF, 16, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T)
SIMD256_MAKE_BLEND_MASK_TESTS(I16_SixteenLanes_WithAlternatingTrueFalse,I16, 0x33333333,  16, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F)
SIMD256_MAKE_BLEND_MASK_TESTS(I16_SixteenLanes_WithAlternatingFalseTrue,I16, 0xCCCCCCCC,  16, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T)
SIMD256_MAKE_BLEND_MASK_TESTS(I16_SixteenLanes_WithAllFalse, I16, 0x00000000, 16, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F)

SIMD256_MAKE_BLEND_MASK_TESTS(I32_EightLanes_WithAllTrue, I32, 0xFFFFFFFF, 8, T, T, T, T, T, T, T, T)
SIMD256_MAKE_BLEND_MASK_TESTS(I32_EightLanes_WithAlternatingTrueFalse, I32, 0x0F0F0F0F, 8, T, F, T, F, T, F, T, F)
SIMD256_MAKE_BLEND_MASK_TESTS(I32_EightLanes_WithAlternatingFalseTrue, I32, 0xF0F0F0F0, 8, F, T, F, T, F, T, F, T)
SIMD256_MAKE_BLEND_MASK_TESTS(I32_EightLanes_WithAllFalse, I32, 0x00000000, 8, F, F, F, F, F, F, F, F)

SIMD256_MAKE_BLEND_MASK_TESTS(I64_FourLanes_WithAllTrue, I64, 0xFFFFFFFF, 4, T, T, T, T)
SIMD256_MAKE_BLEND_MASK_TESTS(I64_FourLanes_WithAlternatingTrueFalse, I64, 0x00FF00FF, 4, T, F, T, F)
SIMD256_MAKE_BLEND_MASK_TESTS(I64_FourLanes_WithAlternatingFalseTrue, I64, 0xFF00FF00, 4, F, T, F, T)
SIMD256_MAKE_BLEND_MASK_TESTS(I64_FourLanes_WithAllFalse, I64, 0x00000000, 4, F, F, F, F)


// Floating Point Types
SIMD256_MAKE_BLEND_MASK_TESTS(FP32_EightLanes_WithAllTrue, FP32, 0xFFFFFFFF, 8, T, T, T, T, T, T, T, T)
SIMD256_MAKE_BLEND_MASK_TESTS(FP32_EightLanes_WithAlternatingTrueFalse, FP32, 0x0F0F0F0F, 8, T, F, T, F, T, F, T, F)
SIMD256_MAKE_BLEND_MASK_TESTS(FP32_EightLanes_WithAlternatingFalseTrue, FP32, 0xF0F0F0F0, 8, F, T, F, T, F, T, F, T)
SIMD256_MAKE_BLEND_MASK_TESTS(FP32_EightLanes_WithAllFalse, FP32, 0x00000000, 8, F, F, F, F, F, F, F, F)

SIMD256_MAKE_BLEND_MASK_TESTS(FP64_FourLanes_WithAllTrue, FP64, 0xFFFFFFFF, 4, T, T, T, T)
SIMD256_MAKE_BLEND_MASK_TESTS(FP64_FourLanes_WithAlternatingTrueFalse, FP64, 0x00FF00FF, 4, T, F, T, F)
SIMD256_MAKE_BLEND_MASK_TESTS(FP64_FourLanes_WithAlternatingFalseTrue, FP64, 0xFF00FF00, 4, F, T, F, T)
SIMD256_MAKE_BLEND_MASK_TESTS(FP64_FourLanes_WithAllFalse, FP64, 0x00000000, 4, F, F, F, F)

#undef SIMD256_MAKE_BLEND_MASK_TESTS
// clang-format on

/// ================================ END MAKE_BLEND_MASK ================================

/** @} */

#endif
