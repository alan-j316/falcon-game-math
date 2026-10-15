/**
 * @file UtilTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 16, 2026
 *
 * @brief Verifies Simd128 utilities like hasNaN or hasInf masked.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "SIMDTestSetup.h"


// TODO: Remove Preprocessor after implementing individual simd paths
#if defined(FALCON_ENABLE_AVX512) || defined(FALCON_ENABLE_AVX2) || defined(FALCON_ENABLE_AVX) ||                      \
    defined(FALCON_ENABLE_SSE4) || defined(FALCON_ENABLE_SSE2)


/**
 * @addtogroup T_SIMD128_Utils
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
    class Simd128UtilsTests: public testing::Test
    {
    public:
        using Type                = T::Type;
        static constexpr auto max = std::numeric_limits<Type>::max();
        static constexpr auto min = std::numeric_limits<Type>::min();
        // Note: Min is swapped with 1 in b to prevent seh
        std::array<typename T::Type, 16> nanVec, infVec, expectedNanVec, expectedInfVec;

    protected:
        void SetUp() override
        {
            if constexpr (std::is_floating_point_v<T>)
            {
                Type nan       = std::numeric_limits<Type>::quiet_NaN();
                Type inf       = std::numeric_limits<Type>::infinity();
                nanVec         = { nan, -5, nan, 2, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12 };
                expectedNanVec = { Type(~0), 0, Type(~0), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
                infVec         = { inf, -inf, inf, -inf, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12 };
                expectedInfVec = { Type(~0), Type(~0), Type(~0), Type(~0), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            }
            else
            {
                nanVec         = { max, min, max, min, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12 };
                infVec         = { max, min, max, min, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12 };
                expectedNanVec = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
                expectedInfVec = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            }
        }
    };

    TYPED_TEST_SUITE(Simd128UtilsTests, Simd128RegisterTypeHints);

} // namespace


template <typename T>
static constexpr T NaN = std::numeric_limits<T>::quiet_NaN();

template <typename T>
static constexpr T Inf = std::numeric_limits<T>::infinity();

TYPED_TEST(Simd128UtilsTests, HasNaN_ReturnsValidMask)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> data{}, resultMask;
    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = this->nanVec[i];
    }
    flcn::Simd128_t<Type, Lane> regA{ data };

    auto regRes = regA.hasNan();

    regRes.storeAligned(resultMask.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(this->expectedNanVec[i], resultMask[i]);
    }
}


TYPED_TEST(Simd128UtilsTests, HasInf_ReturnsValidMask)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> data{}, resultMask;
    for (size_t i = 0; i < Lane; ++i)
    {
        data[i] = this->infVec[i];
    }
    flcn::Simd128_t<Type, Lane> regA{ data };

    auto regRes = regA.hasInf();

    regRes.storeAligned(resultMask.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(this->expectedInfVec[i], resultMask[i]);
    }
}



using namespace simd::testing;

/// =============================== START HAS_NAN ===============================

/// @test Verify that hasNan returns the correct simd mask for floating point types with various data patterns.
    #define SIMD128_HAS_NAN_TESTS_FP(TestName, Type, Lane, Data, Expected)                                             \
        TEST(Simd128_HasNaNTests, ReturnsValidMaskGiven_##TestName)                                                    \
        {                                                                                                              \
            flcn::Simd128_t<Type, Lane> regA{ Data };                                                          \
                                                                                                                       \
            alignas(16) std::array<Type, Lane> resultMask{};                                                           \
            auto regRes = regA.hasNan();                                                                               \
            regRes.storeAligned(resultMask.data());                                                                    \
                                                                                                                       \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                EXPECT_ANY_EQ(Expected[i], resultMask[i]);                                                             \
            }                                                                                                          \
        }

alignas(16) constexpr auto DATA_FP32_2LANES_NO_NAN = Array<FP32, 2>{ 1.0f, 2.0f };
alignas(16) constexpr auto RES_FP32_2LANES_NO_NAN  = Array<FP32, 2>{ 0, 0 };
SIMD128_HAS_NAN_TESTS_FP(FP32_2Lanes_NonNaN, FP32, 2, DATA_FP32_2LANES_NO_NAN, RES_FP32_2LANES_NO_NAN)

alignas(16) constexpr auto DATA_FP32_2LANES_FULL_NAN = Array<FP32, 2>{ NaN<FP32>, NaN<FP32> };
alignas(16) constexpr auto RES_FP32_2LANES_FULL_NAN  = Array<FP32, 2>{ NaN<FP32>, NaN<FP32> };
SIMD128_HAS_NAN_TESTS_FP(FP32_2Lanes_FullNaN, FP32, 2, DATA_FP32_2LANES_FULL_NAN, RES_FP32_2LANES_FULL_NAN)

alignas(16) constexpr auto DATA_FP32_2LANES_MIXED_NAN = Array<FP32, 2>{ 1.0f, NaN<FP32> };
alignas(16) constexpr auto RES_FP32_2LANES_MIXED_NAN  = Array<FP32, 2>{ 0, NaN<FP32> };
SIMD128_HAS_NAN_TESTS_FP(FP32_2Lanes_AlternatingNaN, FP32, 2, DATA_FP32_2LANES_MIXED_NAN, RES_FP32_2LANES_MIXED_NAN)

alignas(16) constexpr auto DATA_FP32_4LANES_NO_NAN = Array<FP32, 4>{ 1.0f, 2.0f, 3.0f, 4.0f };
alignas(16) constexpr auto RES_FP32_4LANES_NO_NAN  = Array<FP32, 4>{ 0, 0, 0, 0 };
SIMD128_HAS_NAN_TESTS_FP(FP32_4Lanes_NonNaN, FP32, 4, DATA_FP32_4LANES_NO_NAN, RES_FP32_4LANES_NO_NAN)

alignas(16) constexpr auto DATA_FP32_4LANES_FULL_NAN = Array<FP32, 4>{ NaN<FP32>, NaN<FP32>, NaN<FP32>, NaN<FP32> };
alignas(16) constexpr auto RES_FP32_4LANES_FULL_NAN  = Array<FP32, 4>{ NaN<FP32>, NaN<FP32>, NaN<FP32>, NaN<FP32> };
SIMD128_HAS_NAN_TESTS_FP(FP32_4Lanes_FullNaN, FP32, 4, DATA_FP32_4LANES_FULL_NAN, RES_FP32_4LANES_FULL_NAN)

alignas(16) constexpr auto DATA_FP32_4LANES_MIXED_NAN = Array<FP32, 4>{ 1.0f, NaN<FP32>, 1.0f, NaN<FP32> };
alignas(16) constexpr auto RES_FP32_4LANES_MIXED_NAN  = Array<FP32, 4>{ 0, NaN<FP32>, 0, NaN<FP32> };
SIMD128_HAS_NAN_TESTS_FP(FP32_4Lanes_AlternatingNaN, FP32, 4, DATA_FP32_4LANES_MIXED_NAN, RES_FP32_4LANES_MIXED_NAN)

alignas(16) constexpr auto DATA_FP64_2LANES_NO_NAN = Array<FP64, 2>{ 1.0f, 2.0f };
alignas(16) constexpr auto RES_FP64_2LANES_NO_NAN  = Array<FP64, 2>{ 0, 0 };
SIMD128_HAS_NAN_TESTS_FP(FP64_2Lanes_NonNaN, FP64, 2, DATA_FP64_2LANES_NO_NAN, RES_FP64_2LANES_NO_NAN)

alignas(16) constexpr auto DATA_FP64_2LANES_FULL_NAN = Array<FP64, 2>{ NaN<FP64>, NaN<FP64> };
alignas(16) constexpr auto RES_FP64_2LANES_FULL_NAN  = Array<FP64, 2>{ NaN<FP64>, NaN<FP64> };
SIMD128_HAS_NAN_TESTS_FP(FP64_2Lanes_FullNaN, FP64, 2, DATA_FP64_2LANES_FULL_NAN, RES_FP64_2LANES_FULL_NAN)

alignas(16) constexpr auto DATA_FP64_2LANES_MIXED_NAN = Array<FP64, 2>{ 1.0f, NaN<FP64> };
alignas(16) constexpr auto RES_FP64_2LANES_MIXED_NAN  = Array<FP64, 2>{ 0, NaN<FP64> };
SIMD128_HAS_NAN_TESTS_FP(FP64_2Lanes_AlternatingNaN, FP64, 2, DATA_FP64_2LANES_MIXED_NAN, RES_FP64_2LANES_MIXED_NAN)

    #undef SIMD128_HAS_NAN_TESTS_FP

/// ================================ END HAS_INF ================================



/// =============================== START HAS_INF ===============================

/// @test Verify that hasInf returns the correct simd mask for floating point types with various data patterns.
    #define SIMD128_HAS_INF_TESTS_FP(TestName, Type, Lane, Data, Expected)                                             \
        TEST(Simd128_HasInfTests, ReturnsValidMaskGiven_##TestName)                                                    \
        {                                                                                                              \
            flcn::Simd128_t<Type, Lane> regA{ Data };                                                                  \
                                                                                                                       \
            alignas(16) std::array<Type, Lane> resultMask{};                                                           \
            auto regRes = regA.hasInf();                                                                               \
            regRes.storeAligned(resultMask.data());                                                                    \
                                                                                                                       \
            for (size_t i = 0; i < Lane; ++i)                                                                          \
            {                                                                                                          \
                EXPECT_ANY_EQ(Expected[i], resultMask[i]);                                                             \
            }                                                                                                          \
        }

alignas(16) constexpr auto DATA_FP32_2LANES_NO_INF = Array<FP32, 2>{ 1.0f, 2.0f };
alignas(16) constexpr auto RES_FP32_2LANES_NO_INF  = Array<FP32, 2>{ 0, 0 };
SIMD128_HAS_INF_TESTS_FP(FP32_2Lanes_NonInf, FP32, 2, DATA_FP32_2LANES_NO_INF, RES_FP32_2LANES_NO_INF)

alignas(16) constexpr auto DATA_FP32_2LANES_FULL_INF = Array<FP32, 2>{ Inf<FP32>, -Inf<FP32> };
alignas(16) constexpr auto RES_FP32_2LANES_FULL_INF  = Array<FP32, 2>{ NaN<FP32>, NaN<FP32> };
SIMD128_HAS_INF_TESTS_FP(FP32_2Lanes_FullInf, FP32, 2, DATA_FP32_2LANES_FULL_INF, RES_FP32_2LANES_FULL_INF)

alignas(16) constexpr auto DATA_FP32_2LANES_MIXED_INF = Array<FP32, 2>{ 1.0f, Inf<FP32> };
alignas(16) constexpr auto RES_FP32_2LANES_MIXED_INF  = Array<FP32, 2>{ 0, NaN<FP32> };
SIMD128_HAS_INF_TESTS_FP(FP32_2Lanes_AlternatingInf, FP32, 2, DATA_FP32_2LANES_MIXED_INF, RES_FP32_2LANES_MIXED_INF)

alignas(16) constexpr auto DATA_FP32_4LANES_NO_INF = Array<FP32, 4>{ 1.0f, 2.0f, 3.0f, 4.0f };
alignas(16) constexpr auto RES_FP32_4LANES_NO_INF  = Array<FP32, 4>{ 0, 0, 0, 0 };
SIMD128_HAS_INF_TESTS_FP(FP32_4Lanes_NonInf, FP32, 4, DATA_FP32_4LANES_NO_INF, RES_FP32_4LANES_NO_INF)

alignas(16) constexpr auto DATA_FP32_4LANES_FULL_INF = Array<FP32, 4>{ Inf<FP32>, -Inf<FP32>, Inf<FP32>, -Inf<FP32> };
alignas(16) constexpr auto RES_FP32_4LANES_FULL_INF  = Array<FP32, 4>{ NaN<FP32>, NaN<FP32>, NaN<FP32>, NaN<FP32> };
SIMD128_HAS_INF_TESTS_FP(FP32_4Lanes_FullInf, FP32, 4, DATA_FP32_4LANES_FULL_INF, RES_FP32_4LANES_FULL_INF)

alignas(16) constexpr auto DATA_FP32_4LANES_MIXED_INF = Array<FP32, 4>{ 1.0f, -Inf<FP32>, 1.0f, -Inf<FP32> };
alignas(16) constexpr auto RES_FP32_4LANES_MIXED_INF  = Array<FP32, 4>{ 0, NaN<FP32>, 0, NaN<FP32> };
SIMD128_HAS_INF_TESTS_FP(FP32_4Lanes_AlternatingInf, FP32, 4, DATA_FP32_4LANES_MIXED_INF, RES_FP32_4LANES_MIXED_INF)

alignas(16) constexpr auto DATA_FP64_2LANES_NO_INF = Array<FP64, 2>{ 1.0f, 2.0f };
alignas(16) constexpr auto RES_FP64_2LANES_NO_INF  = Array<FP64, 2>{ 0, 0 };
SIMD128_HAS_INF_TESTS_FP(FP64_2Lanes_NonInf, FP64, 2, DATA_FP64_2LANES_NO_INF, RES_FP64_2LANES_NO_INF)

alignas(16) constexpr auto DATA_FP64_2LANES_FULL_INF = Array<FP64, 2>{ -Inf<FP64>, Inf<FP64> };
alignas(16) constexpr auto RES_FP64_2LANES_FULL_INF  = Array<FP64, 2>{ NaN<FP64>, NaN<FP64> };
SIMD128_HAS_INF_TESTS_FP(FP64_2Lanes_FullInf, FP64, 2, DATA_FP64_2LANES_FULL_INF, RES_FP64_2LANES_FULL_INF)

alignas(16) constexpr auto DATA_FP64_2LANES_MIXED_INF = Array<FP64, 2>{ 1.0f, -Inf<FP64> };
alignas(16) constexpr auto RES_FP64_2LANES_MIXED_INF  = Array<FP64, 2>{ 0, NaN<FP64> };
SIMD128_HAS_INF_TESTS_FP(FP64_2Lanes_AlternatingInf, FP64, 2, DATA_FP64_2LANES_MIXED_INF, RES_FP64_2LANES_MIXED_INF)

    #undef SIMD128_HAS_INF_TESTS_FP

/// ================================ END HAS_INF ================================



/// =============================== START MAKE_BLEND_MASK ===============================

    /// @test Verify that makeBlendMask returns a correct mask a datatype and lane count.
    #define SIMD128_MAKE_BLEND_MASK_TESTS(TestSuffix, DataType, ExpectedMask, RegCount, ...)                           \
        TEST(Simd128_MakeBlendMaskTests, ReturnsValidMask_For##TestSuffix)                                             \
        {                                                                                                              \
            const flcn::Simd128_t<DataType, RegCount> reg{ DataType(0) };                                              \
            EXPECT_EQ(ExpectedMask, (reg.makeBlendMask<__VA_ARGS__>()));                                               \
        }

// Aliasing to make testing easier.
constexpr bool T = true;
constexpr bool F = false;

// clang-format off
// Unsigned types
SIMD128_MAKE_BLEND_MASK_TESTS(U8_TwoLanes_TwoBoolsWithAllTrue, U8, 0x0000000F, 2, T, T)
SIMD128_MAKE_BLEND_MASK_TESTS(U8_TwoLanes_TwoBoolsWithAlternatingTrueFalse, U8, 0x00000003, 2, T, F)
SIMD128_MAKE_BLEND_MASK_TESTS(U8_TwoLanes_TwoBoolsWithAlternatingFalseTrue, U8, 0x0000000C, 2, F, T)
SIMD128_MAKE_BLEND_MASK_TESTS(U8_TwoLanes_TwoBoolsWithAllFalse, U8, 0x00000000, 2, F, F)

SIMD128_MAKE_BLEND_MASK_TESTS(U8_FourLanes_FourBoolsWithAllTrue, U8, 0x000000FF, 16, T, T, T, T)
SIMD128_MAKE_BLEND_MASK_TESTS(U8_FourLanes_FourBoolsWithAlternatingTrueFalse, U8, 0x00000033, 16, T, F, T, F)
SIMD128_MAKE_BLEND_MASK_TESTS(U8_FourLanes_FourBoolsWithAlternatingFalseTrue, U8, 0x000000CC, 16, F, T, F, T)
SIMD128_MAKE_BLEND_MASK_TESTS(U8_FourLanes_FourBoolsWithAllFalse, U8, 0x00000000, 16, F, F, F, F)

SIMD128_MAKE_BLEND_MASK_TESTS(U8_EightLanes_EightBoolsWithAllTrue, U8, 0x0000FFFF, 16, T, T, T, T, T, T, T, T)
SIMD128_MAKE_BLEND_MASK_TESTS(U8_EightLanes_EightBoolsWithAlternatingTrueFalse, U8, 0x00003333, 16, T, F, T, F, T, F, T, F)
SIMD128_MAKE_BLEND_MASK_TESTS(U8_EightLanes_EightBoolsWithAlternatingFalseTrue, U8, 0x0000CCCC, 16, F, T, F, T, F, T, F, T)
SIMD128_MAKE_BLEND_MASK_TESTS(U8_EightLanes_EightBoolsWithAllFalse, U8, 0x00000000, 16, F, F, F, F, F, F, F, F)

SIMD128_MAKE_BLEND_MASK_TESTS(U8_SixteenLanes_SixteenBoolsWithAllTrue, U8, 0xFFFFFFFF, 16, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T)
SIMD128_MAKE_BLEND_MASK_TESTS(U8_SixteenLanes_SixteenBoolsWithAlternatingTrueFalse, U8, 0x33333333, 16, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F)
SIMD128_MAKE_BLEND_MASK_TESTS(U8_SixteenLanes_SixteenBoolsWithAlternatingFalseTrue, U8, 0xCCCCCCCC, 16, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T)
SIMD128_MAKE_BLEND_MASK_TESTS(U8_SixteenLanes_SixteenBoolsWithAllFalse, U8, 0x00000000, 16, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F)


SIMD128_MAKE_BLEND_MASK_TESTS(U16_TwoLanes_TwoBoolsWithAllTrue, U16, 0x000000FF, 8, T, T)
SIMD128_MAKE_BLEND_MASK_TESTS(U16_TwoLanes_TwoBoolsWithAlternatingTrueFalse, U16, 0x0000000F, 8, T, F)
SIMD128_MAKE_BLEND_MASK_TESTS(U16_TwoLanes_TwoBoolsWithAlternatingFalseTrue, U16, 0x000000F0, 8, F, T)
SIMD128_MAKE_BLEND_MASK_TESTS(U16_TwoLanes_TwoBoolsWithAllFalse, U16, 0x00000000, 8, F, F)

SIMD128_MAKE_BLEND_MASK_TESTS(U16_FourLanes_FourBoolsWithAllTrue, U16, 0x0000FFFF, 8, T, T, T, T)
SIMD128_MAKE_BLEND_MASK_TESTS(U16_FourLanes_FourBoolsWithAlternatingTrueFalse, U16, 0x00000F0F, 8, T, F, T, F)
SIMD128_MAKE_BLEND_MASK_TESTS(U16_FourLanes_FourBoolsWithAlternatingFalseTrue, U16, 0x0000F0F0, 8, F, T, F, T)
SIMD128_MAKE_BLEND_MASK_TESTS(U16_FourLanes_FourBoolsWithAllFalse, U16, 0x00000000, 8, F, F, F, F)

SIMD128_MAKE_BLEND_MASK_TESTS(U16_EightLanes_EightBoolsWithAllTrue, U16, 0xFFFFFFFF, 8, T, T, T, T, T, T, T, T)
SIMD128_MAKE_BLEND_MASK_TESTS(U16_EightLanes_EightBoolsWithAlternatingTrueFalse,U16, 0x0F0F0F0F,  8, T, F, T, F, T, F, T, F)
SIMD128_MAKE_BLEND_MASK_TESTS(U16_EightLanes_EightBoolsWithAlternatingFalseTrue,U16, 0xF0F0F0F0,  8, F, T, F, T, F, T, F, T)
SIMD128_MAKE_BLEND_MASK_TESTS(U16_EightLanes_EightBoolsWithAllFalse, U16, 0x00000000, 8, F, F, F, F, F, F, F, F)


SIMD128_MAKE_BLEND_MASK_TESTS(U32_TwoLanes_TwoBoolsWithAllTrue, U32, 0x0000FFFF, 4, T, T)
SIMD128_MAKE_BLEND_MASK_TESTS(U32_TwoLanes_TwoBoolsWithAlternatingTrueFalse, U32, 0x000000FF, 4, T, F)
SIMD128_MAKE_BLEND_MASK_TESTS(U32_TwoLanes_TwoBoolsWithAlternatingFalseTrue, U32, 0x0000FF00, 4, F, T)
SIMD128_MAKE_BLEND_MASK_TESTS(U32_TwoLanes_TwoBoolsWithAllFalse, U32, 0x00000000, 4, F, F)

SIMD128_MAKE_BLEND_MASK_TESTS(U32_FourLanes_FourBoolsWithAllTrue, U32, 0xFFFFFFFF, 4, T, T, T, T)
SIMD128_MAKE_BLEND_MASK_TESTS(U32_FourLanes_FourBoolsWithAlternatingTrueFalse, U32, 0x00FF00FF, 4, T, F, T, F)
SIMD128_MAKE_BLEND_MASK_TESTS(U32_FourLanes_FourBoolsWithAlternatingFalseTrue, U32, 0xFF00FF00, 4, F, T, F, T)
SIMD128_MAKE_BLEND_MASK_TESTS(U32_FourLanes_FourBoolsWithAllFalse, U32, 0x00000000, 4, F, F, F, F)


SIMD128_MAKE_BLEND_MASK_TESTS(U64_TwoLanes_TwoBoolsWithAllTrue, U64, 0xFFFFFFFF, 2, T, T)
SIMD128_MAKE_BLEND_MASK_TESTS(U64_TwoLanes_TwoBoolsWithAlternatingTrueFalse, U64, 0x0000FFFF, 2, T, F)
SIMD128_MAKE_BLEND_MASK_TESTS(U64_TwoLanes_TwoBoolsWithAlternatingFalseTrue, U64, 0xFFFF0000, 2, F, T)
SIMD128_MAKE_BLEND_MASK_TESTS(U64_TwoLanes_TwoBoolsWithAllFalse, U64, 0x00000000, 2, F, F)



// Signed Integrals
SIMD128_MAKE_BLEND_MASK_TESTS(I8_TwoLanes_TwoBoolsWithAllTrue, I8, 0x0000000F, 2, T, T)
SIMD128_MAKE_BLEND_MASK_TESTS(I8_TwoLanes_TwoBoolsWithAlternatingTrueFalse, I8, 0x00000003, 2, T, F)
SIMD128_MAKE_BLEND_MASK_TESTS(I8_TwoLanes_TwoBoolsWithAlternatingFalseTrue, I8, 0x0000000C, 2, F, T)
SIMD128_MAKE_BLEND_MASK_TESTS(I8_TwoLanes_TwoBoolsWithAllFalse, I8, 0x00000000, 2, F, F)

SIMD128_MAKE_BLEND_MASK_TESTS(I8_FourLanes_FourBoolsWithAllTrue, I8, 0x000000FF, 16, T, T, T, T)
SIMD128_MAKE_BLEND_MASK_TESTS(I8_FourLanes_FourBoolsWithAlternatingTrueFalse, I8, 0x00000033, 16, T, F, T, F)
SIMD128_MAKE_BLEND_MASK_TESTS(I8_FourLanes_FourBoolsWithAlternatingFalseTrue, I8, 0x000000CC, 16, F, T, F, T)
SIMD128_MAKE_BLEND_MASK_TESTS(I8_FourLanes_FourBoolsWithAllFalse, I8, 0x00000000, 16, F, F, F, F)

SIMD128_MAKE_BLEND_MASK_TESTS(I8_EightLanes_EightBoolsWithAllTrue, I8, 0x0000FFFF, 16, T, T, T, T, T, T, T, T)
SIMD128_MAKE_BLEND_MASK_TESTS(I8_EightLanes_EightBoolsWithAlternatingTrueFalse, I8, 0x00003333, 16, T, F, T, F, T, F, T, F)
SIMD128_MAKE_BLEND_MASK_TESTS(I8_EightLanes_EightBoolsWithAlternatingFalseTrue, I8, 0x0000CCCC, 16, F, T, F, T, F, T, F, T)
SIMD128_MAKE_BLEND_MASK_TESTS(I8_EightLanes_EightBoolsWithAllFalse, I8, 0x00000000, 16, F, F, F, F, F, F, F, F)

SIMD128_MAKE_BLEND_MASK_TESTS(I8_SixteenLanes_SixteenBoolsWithAllTrue, I8, 0xFFFFFFFF, 16, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T)
SIMD128_MAKE_BLEND_MASK_TESTS(I8_SixteenLanes_SixteenBoolsWithAlternatingTrueFalse, I8, 0x33333333, 16, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F)
SIMD128_MAKE_BLEND_MASK_TESTS(I8_SixteenLanes_SixteenBoolsWithAlternatingFalseTrue, I8, 0xCCCCCCCC, 16, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T)
SIMD128_MAKE_BLEND_MASK_TESTS(I8_SixteenLanes_SixteenBoolsWithAllFalse, I8, 0x00000000, 16, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F)


SIMD128_MAKE_BLEND_MASK_TESTS(I16_TwoLanes_TwoBoolsWithAllTrue, I16, 0x000000FF, 8, T, T)
SIMD128_MAKE_BLEND_MASK_TESTS(I16_TwoLanes_TwoBoolsWithAlternatingTrueFalse, I16, 0x0000000F, 8, T, F)
SIMD128_MAKE_BLEND_MASK_TESTS(I16_TwoLanes_TwoBoolsWithAlternatingFalseTrue, I16, 0x000000F0, 8, F, T)
SIMD128_MAKE_BLEND_MASK_TESTS(I16_TwoLanes_TwoBoolsWithAllFalse, I16, 0x00000000, 8, F, F)

SIMD128_MAKE_BLEND_MASK_TESTS(I16_FourLanes_FourBoolsWithAllTrue, I16, 0x0000FFFF, 8, T, T, T, T)
SIMD128_MAKE_BLEND_MASK_TESTS(I16_FourLanes_FourBoolsWithAlternatingTrueFalse, I16, 0x00000F0F, 8, T, F, T, F)
SIMD128_MAKE_BLEND_MASK_TESTS(I16_FourLanes_FourBoolsWithAlternatingFalseTrue, I16, 0x0000F0F0, 8, F, T, F, T)
SIMD128_MAKE_BLEND_MASK_TESTS(I16_FourLanes_FourBoolsWithAllFalse, I16, 0x00000000, 8, F, F, F, F)

SIMD128_MAKE_BLEND_MASK_TESTS(I16_EightLanes_EightBoolsWithAllTrue, I16, 0xFFFFFFFF, 8, T, T, T, T, T, T, T, T)
SIMD128_MAKE_BLEND_MASK_TESTS(I16_EightLanes_EightBoolsWithAlternatingTrueFalse,I16, 0x0F0F0F0F,  8, T, F, T, F, T, F, T, F)
SIMD128_MAKE_BLEND_MASK_TESTS(I16_EightLanes_EightBoolsWithAlternatingFalseTrue,I16, 0xF0F0F0F0,  8, F, T, F, T, F, T, F, T)
SIMD128_MAKE_BLEND_MASK_TESTS(I16_EightLanes_EightBoolsWithAllFalse, I16, 0x00000000, 8, F, F, F, F, F, F, F, F)


SIMD128_MAKE_BLEND_MASK_TESTS(I32_TwoLanes_TwoBoolsWithAllTrue, I32, 0x0000FFFF, 4, T, T)
SIMD128_MAKE_BLEND_MASK_TESTS(I32_TwoLanes_TwoBoolsWithAlternatingTrueFalse, I32, 0x000000FF, 4, T, F)
SIMD128_MAKE_BLEND_MASK_TESTS(I32_TwoLanes_TwoBoolsWithAlternatingFalseTrue, I32, 0x0000FF00, 4, F, T)
SIMD128_MAKE_BLEND_MASK_TESTS(I32_TwoLanes_TwoBoolsWithAllFalse, I32, 0x00000000, 4, F, F)

SIMD128_MAKE_BLEND_MASK_TESTS(I32_FourLanes_FourBoolsWithAllTrue, I32, 0xFFFFFFFF, 4, T, T, T, T)
SIMD128_MAKE_BLEND_MASK_TESTS(I32_FourLanes_FourBoolsWithAlternatingTrueFalse, I32, 0x00FF00FF, 4, T, F, T, F)
SIMD128_MAKE_BLEND_MASK_TESTS(I32_FourLanes_FourBoolsWithAlternatingFalseTrue, I32, 0xFF00FF00, 4, F, T, F, T)
SIMD128_MAKE_BLEND_MASK_TESTS(I32_FourLanes_FourBoolsWithAllFalse, I32, 0x00000000, 4, F, F, F, F)


SIMD128_MAKE_BLEND_MASK_TESTS(I64_TwoLanes_TwoBoolsWithAllTrue, I64, 0xFFFFFFFF, 2, T, T)
SIMD128_MAKE_BLEND_MASK_TESTS(I64_TwoLanes_TwoBoolsWithAlternatingTrueFalse, I64, 0x0000FFFF, 2, T, F)
SIMD128_MAKE_BLEND_MASK_TESTS(I64_TwoLanes_TwoBoolsWithAlternatingFalseTrue, I64, 0xFFFF0000, 2, F, T)
SIMD128_MAKE_BLEND_MASK_TESTS(I64_TwoLanes_TwoBoolsWithAllFalse, I64, 0x00000000, 2, F, F)


// Floating Point Types
SIMD128_MAKE_BLEND_MASK_TESTS(FP32_TwoLanes_TwoBoolsWithAllTrue, FP32, 0x0000FFFF, 4, T, T)
SIMD128_MAKE_BLEND_MASK_TESTS(FP32_TwoLanes_TwoBoolsWithAlternatingTrueFalse, FP32, 0x000000FF, 4, T, F)
SIMD128_MAKE_BLEND_MASK_TESTS(FP32_TwoLanes_TwoBoolsWithAlternatingFalseTrue, FP32, 0x0000FF00, 4, F, T)
SIMD128_MAKE_BLEND_MASK_TESTS(FP32_TwoLanes_TwoBoolsWithAllFalse, FP32, 0x00000000, 4, F, F)

SIMD128_MAKE_BLEND_MASK_TESTS(FP32_FourLanes_FourBoolsWithAllTrue, FP32, 0xFFFFFFFF, 4, T, T, T, T)
SIMD128_MAKE_BLEND_MASK_TESTS(FP32_FourLanes_FourBoolsWithAlternatingTrueFalse, FP32, 0x00FF00FF, 4, T, F, T, F)
SIMD128_MAKE_BLEND_MASK_TESTS(FP32_FourLanes_FourBoolsWithAlternatingFalseTrue, FP32, 0xFF00FF00, 4, F, T, F, T)
SIMD128_MAKE_BLEND_MASK_TESTS(FP32_FourLanes_FourBoolsWithAllFalse, FP32, 0x00000000, 4, F, F, F, F)


SIMD128_MAKE_BLEND_MASK_TESTS(FP64_TwoLanes_TwoBoolsWithAllTrue, FP64, 0xFFFFFFFF, 2, T, T)
SIMD128_MAKE_BLEND_MASK_TESTS(FP64_TwoLanes_TwoBoolsWithAlternatingTrueFalse, FP64, 0x0000FFFF, 2, T, F)
SIMD128_MAKE_BLEND_MASK_TESTS(FP64_TwoLanes_TwoBoolsWithAlternatingFalseTrue, FP64, 0xFFFF0000, 2, F, T)
SIMD128_MAKE_BLEND_MASK_TESTS(FP64_TwoLanes_TwoBoolsWithAllFalse, FP64, 0x00000000, 2, F, F)

#undef SIMD128_MAKE_BLEND_MASK_TESTS

// clang-format on
/// ================================ END MAKE_BLEND_MASK ================================

/** @} */

#endif
