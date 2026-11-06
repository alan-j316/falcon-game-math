/**
 * @file SimdUtilsTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 30, 2026
 *
 * @brief Verifies SIMD utilities.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "CommonSetup.h"

#include <falcon/simd/utils/SIMDUtils.h>
#include <format>
#include <gtest/gtest.h>


/**
 * @addtogroup T_SIMD_Utils
 * @{
 */


namespace
{
    /**************************************
     *             TEST SETUP             *
     **************************************/

    struct TestPackingParams
    {
        std::size_t totalByteSize;
        std::size_t alignAs;
        std::size_t expectedByteSize;
        std::size_t padding;
        std::size_t packedRegisterWidth;
        std::size_t registerCount;
    };
    /** @brief Test fixture for register packed size calculation, parameterized by @ref TestPackingParams */
    class PackedSizeCalculatorTests: public testing::TestWithParam<TestPackingParams>
    {};



    /// +-----------------------------------------------------------------------------------------------------------+
    /// |                                   EXPAND BY FOUR TESTS                                                    |
    /// +-----------------------------------------------------------------------------------------------------------+

    /// @brief Test fixture for @ref flcn::expandFourFold.
    class ExpandFourFoldTests: public testing::TestWithParam<std::pair<flcn::BlendMask32_t, flcn::u128>>
    {};


    INSTANTIATE_TEST_SUITE_P(
        ExpandFourFoldTests, ExpandFourFoldTests,
        testing::Values(
            std::make_pair(0x0000FFFF, flcn::u128{ .upper = 0x0000000000000000, .lower = 0xFFFFFFFFFFFFFFFF }),
            std::make_pair(0xFFFFFFFF, flcn::u128{ .upper = 0xFFFFFFFFFFFFFFFF, .lower = 0xFFFFFFFFFFFFFFFF }),
            std::make_pair(0x00000000, flcn::u128{ .upper = 0x0000000000000000, .lower = 0x0000000000000000 }),
            std::make_pair(0xFFFF0000, flcn::u128{ .upper = 0xFFFFFFFFFFFFFFFF, .lower = 0x0000000000000000 }),
            std::make_pair(0x0F0F0F0F, flcn::u128{ .upper = 0x0000FFFF0000FFFF, .lower = 0x0000FFFF0000FFFF }),
            std::make_pair(0xF0F0F0F0, flcn::u128{ .upper = 0xFFFF0000FFFF0000, .lower = 0xFFFF0000FFFF0000 }),
            std::make_pair(0x79151FEE, flcn::u128{ .upper = 0x0FFFF00F000F0F0F, .lower = 0x000FFFFFFFF0FFF0 }),
            std::make_pair(0x2AC1FC11, flcn::u128{ .upper = 0x00F0F0F0FF00000F, .lower = 0xFFFFFF00000F000F }),
            std::make_pair(0xB8A6A044, flcn::u128{ .upper = 0xF0FFF000F0F00FF0, .lower = 0xF0F000000F000F00 }),
            std::make_pair(0xFE8D8D40, flcn::u128{ .upper = 0xFFFFFFF0F000FF0F, .lower = 0xF000FF0F0F000000 })),
        [](const testing::TestParamInfo<ExpandFourFoldTests::ParamType>& info) {
            const auto inParam = info.param.first;
            const auto upper   = info.param.second.upper;
            const auto lower   = info.param.second.lower;
            return std::format("{:#010X}_Returns_{:#018X}{:016X}", inParam, upper, lower);
        });


    /// +-----------------------------------------------------------------------------------------------------------+
    /// |                                  EXPAND BY EIGHT TESTS                                                    |
    /// +-----------------------------------------------------------------------------------------------------------+

    /// @brief Test fixture for @ref flcn::expandEightFold.
    class ExpandEightFoldTests: public testing::TestWithParam<std::pair<flcn::BlendMask32_t, flcn::u256>>
    {};

    INSTANTIATE_TEST_SUITE_P(ExpandEightFoldTests, ExpandEightFoldTests,
                             // clang-format off
        testing::Values(
            std::make_pair(0x0000FFFF, flcn::u256{ .quad3 = 0x0000000000000000, .quad2 = 0x0000000000000000, .quad1 = 0xFFFFFFFFFFFFFFFF, .quad0 = 0xFFFFFFFFFFFFFFFF }),
            std::make_pair(0xFFFFFFFF, flcn::u256{ .quad3 = 0xFFFFFFFFFFFFFFFF, .quad2 = 0xFFFFFFFFFFFFFFFF, .quad1 = 0xFFFFFFFFFFFFFFFF, .quad0 = 0xFFFFFFFFFFFFFFFF }),
            std::make_pair(0x00000000, flcn::u256{ .quad3 = 0x0000000000000000, .quad2 = 0x0000000000000000, .quad1 = 0x0000000000000000, .quad0 = 0x0000000000000000 }),
            std::make_pair(0xFFFF0000, flcn::u256{ .quad3 = 0xFFFFFFFFFFFFFFFF, .quad2 = 0xFFFFFFFFFFFFFFFF, .quad1 = 0x0000000000000000, .quad0 = 0x0000000000000000 }),
            std::make_pair(0x0F0F0F0F, flcn::u256{ .quad3 = 0x00000000FFFFFFFF, .quad2 = 0x00000000FFFFFFFF, .quad1 = 0x00000000FFFFFFFF, .quad0 = 0x00000000FFFFFFFF }),
            std::make_pair(0xF0F0F0F0, flcn::u256{ .quad3 = 0xFFFFFFFF00000000, .quad2 = 0xFFFFFFFF00000000, .quad1 = 0xFFFFFFFF00000000, .quad0 = 0xFFFFFFFF00000000 }),
            std::make_pair(0xC467E58A, flcn::u256{ .quad3 = 0xFFFF000000FF0000, .quad2 = 0x00FFFF0000FFFFFF, .quad1 = 0xFFFFFF0000FF00FF, .quad0 = 0xFF000000FF00FF00 }),
            std::make_pair(0xF2289174, flcn::u256{ .quad3 = 0xFFFFFFFF0000FF00, .quad2 = 0x0000FF00FF000000, .quad1 = 0xFF0000FF000000FF, .quad0 = 0x00FFFFFF00FF0000 }),
            std::make_pair(0x8AA344C7, flcn::u256{ .quad3 = 0xFF000000FF00FF00, .quad2 = 0xFF00FF000000FFFF, .quad1 = 0x00FF000000FF0000, .quad0 = 0xFFFF000000FFFFFF }),
            std::make_pair(0xAC728129, flcn::u256{ .quad3 = 0xFF00FF00FFFF0000, .quad2 = 0x00FFFFFF0000FF00, .quad1 = 0xFF000000000000FF, .quad0 = 0x0000FF00FF0000FF })),
            [](const testing::TestParamInfo<ExpandEightFoldTests::ParamType>& info) {
                const auto inParam = info.param.first;
                const auto quad3   = info.param.second.quad3;
                const auto quad2   = info.param.second.quad2;
                const auto quad1   = info.param.second.quad1;
                const auto quad0   = info.param.second.quad0;
                return std::format("{:#010X}_Returns_{:#018X}{:016X}{:016X}{:016X}", inParam, quad3, quad2, quad1, quad0);
        });
    // clang-format on


    template <typename>
    class GetAllOnesTests: public testing::Test
    {};

    TYPED_TEST_SUITE(GetAllOnesTests, SupportedArithmeticTypes);

    /**************************************
     *          STATIC TESTS              *
     **************************************/

    namespace static_tests
    {
        using namespace flcn::simd;
        constexpr bool T = true;
        constexpr bool F = false;

        /// @test Verify that @ref flcn::simd::makeBlendMask32 returns a correct mask for 2 booleans
        static_assert(makeBlendMask32<2, T, F>() == 0x0000FFFF);
        static_assert(makeBlendMask32<2, F, T>() == 0xFFFF0000);

        /// @test Verify that @ref flcn::simd::makeBlendMask32 returns a correct mask for 4 booleans
        static_assert(makeBlendMask32<4, T, F, T, F>() == 0x00FF00FF);
        static_assert(makeBlendMask32<4, F, T, F, T>() == 0xFF00FF00);

        /// @test Verify that @ref flcn::simd::makeBlendMask32 returns a correct mask for 8 booleans
        static_assert(makeBlendMask32<8, T, F, T, F, T, F, T, F>() == 0x0F0F0F0F);
        static_assert(makeBlendMask32<8, F, T, F, T, F, T, F, T>() == 0xF0F0F0F0);


        /// @test Verify that @ref flcn::simd::makeBlendMask32 returns a correct mask for 16 booleans
        static_assert(makeBlendMask32<16, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F>() == 0x33333333);
        static_assert(makeBlendMask32<16, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T>() == 0xCCCCCCCC);

        /// @test Verify that @ref flcn::simd::makeBlendMask32 returns a correct mask for 32 booleans
        static_assert(makeBlendMask32<32, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F,
                                      T, F, T, F, T, F>() == 0x55555555);
        static_assert(makeBlendMask32<32, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T,
                                      F, T, F, T, F, T>() == 0xAAAAAAAA);


        /// @test Verify that @ref flcn::simd::expandFourFold returns a valid value expanded four folds
        static_assert(expandFourFold(0x79151FEE).upper == 0x0FFFF00F000F0F0F);
        static_assert(expandFourFold(0x79151FEE).lower == 0x000FFFFFFFF0FFF0);
        static_assert(expandFourFold(0x0000FFFF).upper == 0x0000000000000000);
        static_assert(expandFourFold(0x0000FFFF).lower == 0xFFFFFFFFFFFFFFFF);
        static_assert(expandFourFold(0xFFFF0000).upper == 0xFFFFFFFFFFFFFFFF);
        static_assert(expandFourFold(0xFFFF0000).lower == 0x0000000000000000);

        /// @test Verify that @ref flcn::simd::expandEightFold returns a valid value expanded eight folds
        static_assert(expandEightFold(0xC467E58A).quad3 == 0xFFFF000000FF0000);
        static_assert(expandEightFold(0xC467E58A).quad2 == 0x00FFFF0000FFFFFF);
        static_assert(expandEightFold(0xC467E58A).quad1 == 0xFFFFFF0000FF00FF);
        static_assert(expandEightFold(0xC467E58A).quad0 == 0xFF000000FF00FF00);
        static_assert(expandEightFold(0x0000FFFF).quad3 == 0x0000000000000000);
        static_assert(expandEightFold(0x0000FFFF).quad2 == 0x0000000000000000);
        static_assert(expandEightFold(0x0000FFFF).quad1 == 0xFFFFFFFFFFFFFFFF);
        static_assert(expandEightFold(0x0000FFFF).quad0 == 0xFFFFFFFFFFFFFFFF);
        static_assert(expandEightFold(0xFFFF0000).quad3 == 0xFFFFFFFFFFFFFFFF);
        static_assert(expandEightFold(0xFFFF0000).quad2 == 0xFFFFFFFFFFFFFFFF);
        static_assert(expandEightFold(0xFFFF0000).quad1 == 0x0000000000000000);
        static_assert(expandEightFold(0xFFFF0000).quad0 == 0x0000000000000000);

    } // namespace static_tests

} // namespace


/**
 * @test Verify that the packed size parameter returns the correct aligned byte size, padding, register width
 *        and count.
 */
TEST_P(PackedSizeCalculatorTests, CalculatesCorrectSize)
{
    // Given an arbitrary data type size and total byte size
    const auto [totalByteSize, alignAs, expectedByteSize, expectedPadding, expectedPackedRegisterWidth,
                expectedRegisterCount] = GetParam();

    // When packed size is calculated
    const auto [alignedByteSize, padding, packedRegisterWidth, registerCount] =
        flcn::simd::calculatePackedSize(totalByteSize, alignAs);

    // It gives the nearest packed size and padding
    EXPECT_EQ(expectedByteSize, alignedByteSize);
    EXPECT_EQ(expectedPadding, padding);
    EXPECT_EQ(expectedPackedRegisterWidth, packedRegisterWidth);
    EXPECT_EQ(expectedRegisterCount, registerCount);
}

INSTANTIATE_TEST_SUITE_P(
    PackedSizeCalculatorTestSuite, PackedSizeCalculatorTests,
    ::testing::Values(
        // SSE
        TestPackingParams{ 1, 16, 16, 15, 16, 1 }, TestPackingParams{ 4, 16, 16, 12, 16, 1 },
        TestPackingParams{ 8, 16, 16, 8, 16, 1 }, TestPackingParams{ 12, 16, 16, 4, 16, 1 },
        TestPackingParams{ 16, 16, 16, 0, 16, 1 }, TestPackingParams{ 20, 16, 32, 12, 16, 2 },
        TestPackingParams{ 24, 16, 32, 8, 16, 2 }, TestPackingParams{ 32, 16, 32, 0, 16, 2 },
        TestPackingParams{ 48, 16, 64, 16, 16, 4 }, TestPackingParams{ 56, 16, 64, 8, 16, 4 },
        TestPackingParams{ 64, 16, 64, 0, 16, 4 }, TestPackingParams{ 72, 16, 128, 56, 16, 8 },
        TestPackingParams{ 80, 16, 128, 48, 16, 8 }, TestPackingParams{ 128, 16, 128, 0, 16, 8 },
        TestPackingParams{ 192, 16, 256, 64, 16, 16 }, TestPackingParams{ 256, 16, 256, 0, 16, 16 },
        TestPackingParams{ 512, 16, 512, 0, 16, 32 }, TestPackingParams{ 777, 16, 1024, 247, 16, 64 },
        TestPackingParams{ 1024, 16, 1024, 0, 16, 64 },
        // AVX/AVX2
        TestPackingParams{ 1, 32, 16, 15, 16, 1 }, TestPackingParams{ 4, 32, 16, 12, 16, 1 },
        TestPackingParams{ 8, 32, 16, 8, 16, 1 }, TestPackingParams{ 12, 32, 16, 4, 16, 1 },
        TestPackingParams{ 16, 32, 16, 0, 16, 1 }, TestPackingParams{ 20, 32, 32, 12, 32, 1 },
        TestPackingParams{ 24, 32, 32, 8, 32, 1 }, TestPackingParams{ 32, 32, 32, 0, 32, 1 },
        TestPackingParams{ 48, 32, 64, 16, 32, 2 }, TestPackingParams{ 56, 32, 64, 8, 32, 2 },
        TestPackingParams{ 64, 32, 64, 0, 32, 2 }, TestPackingParams{ 72, 32, 128, 56, 32, 4 },
        TestPackingParams{ 80, 32, 128, 48, 32, 4 }, TestPackingParams{ 128, 32, 128, 0, 32, 4 },
        TestPackingParams{ 192, 32, 256, 64, 32, 8 }, TestPackingParams{ 256, 32, 256, 0, 32, 8 },
        TestPackingParams{ 512, 32, 512, 0, 32, 16 }, TestPackingParams{ 777, 32, 1024, 247, 32, 32 },
        TestPackingParams{ 1024, 32, 1024, 0, 32, 32 },
        // AVX512
        TestPackingParams{ 1, 64, 16, 15, 16, 1 }, TestPackingParams{ 4, 64, 16, 12, 16, 1 },
        TestPackingParams{ 8, 64, 16, 8, 16, 1 }, TestPackingParams{ 12, 64, 16, 4, 16, 1 },
        TestPackingParams{ 16, 64, 16, 0, 16, 1 }, TestPackingParams{ 20, 64, 32, 12, 32, 1 },
        TestPackingParams{ 24, 64, 32, 8, 32, 1 }, TestPackingParams{ 32, 64, 32, 0, 32, 1 },
        TestPackingParams{ 48, 64, 64, 16, 64, 1 }, TestPackingParams{ 56, 64, 64, 8, 64, 1 },
        TestPackingParams{ 64, 64, 64, 0, 64, 1 }, TestPackingParams{ 72, 64, 128, 56, 64, 2 },
        TestPackingParams{ 80, 64, 128, 48, 64, 2 }, TestPackingParams{ 128, 64, 128, 0, 64, 2 },
        TestPackingParams{ 192, 64, 256, 64, 64, 4 }, TestPackingParams{ 256, 64, 256, 0, 64, 4 },
        TestPackingParams{ 512, 64, 512, 0, 64, 8 }, TestPackingParams{ 777, 64, 1024, 247, 64, 16 },
        TestPackingParams{ 1024, 64, 1024, 0, 64, 16 }));



TYPED_TEST(GetAllOnesTests, ReturnsValueWithOneInAllBits)
{
    const auto value = flcn::simd::getAllOnes<TypeParam>();
    if constexpr (std::same_as<double, TypeParam>)
    {
        EXPECT_EQ(0xFFFFFFFFFFFFFFFF, std::bit_cast<uint64_t>(value));
    }
    else if constexpr (std::same_as<float, TypeParam>)
    {
        EXPECT_EQ(0xFFFFFFFF, std::bit_cast<uint32_t>(value));
    }
    else
    {
        EXPECT_EQ(static_cast<TypeParam>(0xFFFFFFFFFFFFFFFF), value);
    }
}


TEST_P(ExpandFourFoldTests, ExpandsEachBitBy4TimesAndReturnsAValidPair)
{
    const auto [blendMask, expectedValue] = GetParam();
    const auto value                      = flcn::simd::expandFourFold(blendMask);
    EXPECT_EQ(expectedValue.upper, value.upper);
    EXPECT_EQ(expectedValue.lower, value.lower);
}


TEST_P(ExpandEightFoldTests, ExpandsEachBitBy8TimesAndReturnsAValidPair)
{
    const auto [blendMask, expectedValue] = GetParam();
    const auto value                      = flcn::simd::expandEightFold(blendMask);
    EXPECT_EQ(expectedValue.quad3, value.quad3);
    EXPECT_EQ(expectedValue.quad2, value.quad2);
    EXPECT_EQ(expectedValue.quad1, value.quad1);
    EXPECT_EQ(expectedValue.quad0, value.quad0);
}

/// =============================== START MAKE_BLEND_MASK_32 ===============================

/// @test Verify that makeBlendMask32 returns a correct mask given all mask combinations.
#define TEST_SIMD_UTILS_MAKE_BLEND_MASK(TestSuffix, ExpectedMask, RegCount, ...)                                       \
    TEST(MakeBlendMask32Tests, ReturnsValidMask_For##TestSuffix)                                                       \
    { EXPECT_EQ(ExpectedMask, (flcn::simd::makeBlendMask32<RegCount, __VA_ARGS__>())); }

// Aliasing to make testing easier.
constexpr bool T = true;
constexpr bool F = false;

TEST_SIMD_UTILS_MAKE_BLEND_MASK(TwoLanes_TwoBoolsWithAllTrue, 0xFFFFFFFF, 2, T, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(TwoLanes_TwoBoolsWithAlternatingTrueFalse, 0x0000FFFF, 2, T, F)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(TwoLanes_TwoBoolsWithAlternatingFalseTrue, 0xFFFF0000, 2, F, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(TwoLanes_TwoBoolsWithAllFalse, 0x00000000, 2, F, F)

TEST_SIMD_UTILS_MAKE_BLEND_MASK(FourLanes_TwoBoolsWithAllTrue, 0x0000FFFF, 4, T, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(FourLanes_TwoBoolsWithAlternatingTrueFalse, 0x000000FF, 4, T, F)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(FourLanes_TwoBoolsWithAlternatingFalseTrue, 0x0000FF00, 4, F, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(FourLanes_TwoBoolsWithAllFalse, 0x00000000, 4, F, F)

TEST_SIMD_UTILS_MAKE_BLEND_MASK(FourLanes_FourBoolsWithAllTrue, 0xFFFFFFFF, 4, T, T, T, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(FourLanes_FourBoolsWithAlternatingTrueFalse, 0x00FF00FF, 4, T, F, T, F)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(FourLanes_FourBoolsWithAlternatingFalseTrue, 0xFF00FF00, 4, F, T, F, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(FourLanes_FourBoolsWithAllFalse, 0x00000000, 4, F, F, F, F)

TEST_SIMD_UTILS_MAKE_BLEND_MASK(EightLanes_TwoBoolsWithAllTrue, 0x000000FF, 8, T, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(EightLanes_TwoBoolsWithAlternatingTrueFalse, 0x0000000F, 8, T, F)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(EightLanes_TwoBoolsWithAlternatingFalseTrue, 0x000000F0, 8, F, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(EightLanes_TwoBoolsWithAllFalse, 0x00000000, 8, F, F)

TEST_SIMD_UTILS_MAKE_BLEND_MASK(EightLanes_FourBoolsWithAllTrue, 0x0000FFFF, 8, T, T, T, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(EightLanes_FourBoolsWithAlternatingTrueFalse, 0x00000F0F, 8, T, F, T, F)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(EightLanes_FourBoolsWithAlternatingFalseTrue, 0x0000F0F0, 8, F, T, F, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(EightLanes_FourBoolsWithAllFalse, 0x00000000, 8, F, F, F, F)

TEST_SIMD_UTILS_MAKE_BLEND_MASK(EightLanes_EightBoolsWithAllTrue, 0xFFFFFFFF, 8, T, T, T, T, T, T, T, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(EightLanes_EightBoolsWithAlternatingTrueFalse, 0x0F0F0F0F, 8, T, F, T, F, T, F, T, F)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(EightLanes_EightBoolsWithAlternatingFalseTrue, 0xF0F0F0F0, 8, F, T, F, T, F, T, F, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(EightLanes_EightBoolsWithAllFalse, 0x00000000, 8, F, F, F, F, F, F, F, F)

TEST_SIMD_UTILS_MAKE_BLEND_MASK(SixteenLanes_TwoBoolsWithAllTrue, 0x0000000F, 16, T, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(SixteenLanes_TwoBoolsWithAlternatingTrueFalse, 0x00000003, 16, T, F)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(SixteenLanes_TwoBoolsWithAlternatingFalseTrue, 0x0000000C, 16, F, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(SixteenLanes_TwoBoolsWithAllFalse, 0x00000000, 16, F, F)

TEST_SIMD_UTILS_MAKE_BLEND_MASK(SixteenLanes_FourBoolsWithAllTrue, 0x000000FF, 16, T, T, T, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(SixteenLanes_FourBoolsWithAlternatingTrueFalse, 0x00000033, 16, T, F, T, F)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(SixteenLanes_FourBoolsWithAlternatingFalseTrue, 0x000000CC, 16, F, T, F, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(SixteenLanes_FourBoolsWithAllFalse, 0x00000000, 16, F, F, F, F)

TEST_SIMD_UTILS_MAKE_BLEND_MASK(SixteenLanes_EightBoolsWithAllTrue, 0x0000FFFF, 16, T, T, T, T, T, T, T, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(SixteenLanes_EightBoolsWithAlternatingTrueFalse, 0x00003333, 16, T, F, T, F, T, F, T, F)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(SixteenLanes_EightBoolsWithAlternatingFalseTrue, 0x0000CCCC, 16, F, T, F, T, F, T, F, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(SixteenLanes_EightBoolsWithAllFalse, 0x00000000, 16, F, F, F, F, F, F, F, F)

TEST_SIMD_UTILS_MAKE_BLEND_MASK(SixteenLanes_SixteenBoolsWithAllTrue, 0xFFFFFFFF, 16, T, T, T, T, T, T, T, T, T, T, T,
                                T, T, T, T, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(SixteenLanes_SixteenBoolsWithAlternatingTrueFalse, 0x33333333, 16, T, F, T, F, T, F, T,
                                F, T, F, T, F, T, F, T, F)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(SixteenLanes_SixteenBoolsWithAlternatingFalseTrue, 0xCCCCCCCC, 16, F, T, F, T, F, T, F,
                                T, F, T, F, T, F, T, F, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(SixteenLanes_SixteenBoolsWithAllFalse, 0x00000000, 16, F, F, F, F, F, F, F, F, F, F, F,
                                F, F, F, F, F)

TEST_SIMD_UTILS_MAKE_BLEND_MASK(ThirtyTwoLanes_TwoBoolsWithAllTrue, 0x00000003, 32, T, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(ThirtyTwoLanes_TwoBoolsWithAlternatingTrueFalse, 0x00000001, 32, T, F)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(ThirtyTwoLanes_TwoBoolsWithAlternatingFalseTrue, 0x00000002, 32, F, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(ThirtyTwoLanes_TwoBoolsWithAllFalse, 0x00000000, 32, F, F)

TEST_SIMD_UTILS_MAKE_BLEND_MASK(ThirtyTwo_FourBoolsWithAllTrue, 0x0000000F, 32, T, T, T, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(ThirtyTwo_FourBoolsWithAlternatingTrueFalse, 0x00000005, 32, T, F, T, F)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(ThirtyTwo_FourBoolsWithAlternatingFalseTrue, 0x0000000A, 32, F, T, F, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(ThirtyTwo_FourBoolsWithAllFalse, 0x00000000, 32, F, F, F, F)

TEST_SIMD_UTILS_MAKE_BLEND_MASK(ThirtyTwo_EightBoolsWithAllTrue, 0x000000FF, 32, T, T, T, T, T, T, T, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(ThirtyTwo_EightBoolsWithAlternatingTrueFalse, 0x00000055, 32, T, F, T, F, T, F, T, F)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(ThirtyTwo_EightBoolsWithAlternatingFalseTrue, 0x000000AA, 32, F, T, F, T, F, T, F, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(ThirtyTwo_EightBoolsWithAllFalse, 0x00000000, 32, F, F, F, F, F, F, F, F)

TEST_SIMD_UTILS_MAKE_BLEND_MASK(ThirtyTwo_SixteenBoolsWithAllTrue, 0x0000FFFF, 32, T, T, T, T, T, T, T, T, T, T, T, T,
                                T, T, T, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(ThirtyTwo_SixteenBoolsWithAlternatingTrueFalse, 0x00005555, 32, T, F, T, F, T, F, T, F,
                                T, F, T, F, T, F, T, F)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(ThirtyTwo_SixteenBoolsWithAlternatingFalseTrue, 0x0000AAAA, 32, F, T, F, T, F, T, F, T,
                                F, T, F, T, F, T, F, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(ThirtyTwo_SixteenBoolsWithAllFalse, 0x00000000, 32, F, F, F, F, F, F, F, F, F, F, F, F,
                                F, F, F, F)

TEST_SIMD_UTILS_MAKE_BLEND_MASK(ThirtyTwo_ThirtyTwoBoolsWithAllTrue, 0xFFFFFFFF, 32, T, T, T, T, T, T, T, T, T, T, T, T,
                                T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(ThirtyTwo_ThirtyTwoBoolsWithAlternatingTrueFalse, 0x55555555, 32, T, F, T, F, T, F, T,
                                F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(ThirtyTwo_ThirtyTwoBoolsWithAlternatingFalseTrue, 0xAAAAAAAA, 32, F, T, F, T, F, T, F,
                                T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T, F, T)
TEST_SIMD_UTILS_MAKE_BLEND_MASK(ThirtyTwo_ThirtyTwoBoolsWithAllFalse, 0x00000000, 32, F, F, F, F, F, F, F, F, F, F, F,
                                F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F)

#undef TEST_SIMD_UTILS_MAKE_BLEND_MASK

/// ================================ END MAKE_BLEND_MASK_32 ================================



/// =============================== START PACK_TO_N_BIT ===============================

#define TEST_SIMD_UTILS_PACK_TO_N_BITS(TestSuffix, BitCount, InputMask, ExpectedValue)                                 \
    TEST(PackToNBitsTests, ReturnsValidMask_WhenCompressedTo##TestSuffix)                                              \
    {                                                                                                                  \
        const auto packed = flcn::simd::packToNBits<BitCount>(InputMask);                                              \
        EXPECT_EQ(ExpectedValue, packed);                                                                              \
    }

TEST_SIMD_UTILS_PACK_TO_N_BITS(2Bits_FullOnes, 2, 0xFFFFFFFF, 0x00000003)
TEST_SIMD_UTILS_PACK_TO_N_BITS(2Bits_FullZeroes, 2, 0x0000000, 0x00000000)
TEST_SIMD_UTILS_PACK_TO_N_BITS(2Bits_Alternating, 2, 0xFFFF0000, 0x00000002) // 0b10
TEST_SIMD_UTILS_PACK_TO_N_BITS(2Bits_Random, 2, 0x0000FFFF, 0x00000001)      // 0b01

TEST_SIMD_UTILS_PACK_TO_N_BITS(4Bits_FullOnes, 4, 0xFFFFFFFF, 0x0000000F)
TEST_SIMD_UTILS_PACK_TO_N_BITS(4Bits_FullZeroes, 4, 0x0000000, 0x00000000)
TEST_SIMD_UTILS_PACK_TO_N_BITS(4Bits_Alternating, 4, 0xFF00FF00, 0x0000000A) // 0b1010
TEST_SIMD_UTILS_PACK_TO_N_BITS(4Bits_Random, 4, 0xFF00FFFF, 0x0000000B)      // 0b1011

TEST_SIMD_UTILS_PACK_TO_N_BITS(8Bits_FullOnes, 8, 0xFFFFFFFF, 0x000000FF)
TEST_SIMD_UTILS_PACK_TO_N_BITS(8Bits_FullZeroes, 8, 0x0000000, 0x00000000)
TEST_SIMD_UTILS_PACK_TO_N_BITS(8Bits_Alternating, 8, 0xF0F0F0F0, 0x000000AA) // 0b10101010
TEST_SIMD_UTILS_PACK_TO_N_BITS(8Bits_Random, 8, 0xFF00F00F, 0x000000C9)      // 0b11001001

TEST_SIMD_UTILS_PACK_TO_N_BITS(16Bits_FullOnes, 16, 0xFFFFFFFF, 0x0000FFFF)
TEST_SIMD_UTILS_PACK_TO_N_BITS(16Bits_FullZeroes, 16, 0x0000000, 0x00000000)
TEST_SIMD_UTILS_PACK_TO_N_BITS(16Bits_Alternating, 16, 0xCCCCCCCC, 0x0000AAAA) // 0b1010101010101010
TEST_SIMD_UTILS_PACK_TO_N_BITS(16Bits_Random, 16, 0xCF0CCF0C, 0x0000B2B2)      // 0b1011001010110010

#undef TEST_SIMD_UTILS_PACK_TO_N_BITS

/// ================================ END PACK_TO_N_BIT ================================
/** @} */
