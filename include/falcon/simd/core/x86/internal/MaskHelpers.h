#pragma once
/**
 * @file MaskHelpers.h
 * @author Alan Abraham P Kochumon
 * @date Created on: November 04, 2026
 *
 * @brief Helper utilities for SIMD mask creation and shuffling.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <array>
#include <cstddef>
#include <cstdint>


namespace flcn::simd::internal
{
    /**
     * Generate a suitable shuffle mask set for 16x16 register(mm256).
     * @tparam Lane  The number of lanes in the register.
     * @tparam Index The shuffle indices.
     * @return Selection indices for original and permuted array.
     *         First -  Selection index for in-lane shuffling
     *         Second - Selection index for permuted register.
     *         Return 0x80 for element if the current index is out-of-lane.
     */
    template <size_t Lane, uint8_t... Index>
        requires(sizeof...(Index) == 16)
    consteval std::pair<std::array<uint8_t, 32>, std::array<uint8_t, 32>> mm256Epi16PermMask() noexcept
    {
        constexpr uint8_t indices[]{ Index... };

        // In Lane Index  - Shuffling indices of elements in the same lane.
        // Permuted Index - Shuffling indices of elements that has cross lanes.
        std::array<uint8_t, 32> inLaneIdx{}, permutedIdx{};

        constexpr auto HalfLane = Lane >> 2; // Lane / 2

        for (size_t i = 0; i < sizeof...(Index); ++i)
        {
            // Lane is crossed if the we are iterating the lower Lane / 2 indices and the index is greater than or
            // equal to the middle index or if a index less than Lane / 2 is found in the upper portion.
            // Example: [1, 7, 5, 4| 2, 3, 6, 0]
            //          Here, 1 crossed the lane since it's greater than 4 (4-7 is the upper lane index).
            //          6 crossed because its greater than 3(0-3 is the lower lane)
            const bool inSameLane =
                (i >= HalfLane && indices[i] >= HalfLane) || (i < HalfLane && indices[i] < HalfLane);
            // If the indices are in the same lane, we can just pass it as it is but
            // switch the permuted to 0x80
            if (inSameLane)
            {
                // NOTE: We can only shuffle within the 16 positions so the the positions are split into
                //       [16-0 | 16-0] so we need to % by Lane or 16 to index the values in that range.
                // We mod by the Lane since we are take a 16 indices and transforming it to 32
                // by using adjacency.
                //
                // We need to update 2 indices as we want to shuffle a epi16 register with 8-bit shuffle.
                // so 2n and 2n+1 gives the adjacent registers.
                inLaneIdx[i * 2]     = (indices[i] * 2) % Lane;
                inLaneIdx[i * 2 + 1] = (indices[i] * 2 + 1) % Lane;

                permutedIdx[i * 2]     = 0x80;
                permutedIdx[i * 2 + 1] = 0x80;
            }
            else
            {
                permutedIdx[i * 2]     = (indices[i] * 2) % Lane;
                permutedIdx[i * 2 + 1] = (indices[i] * 2 + 1) % Lane;

                inLaneIdx[i * 2]     = 0x80;
                inLaneIdx[i * 2 + 1] = 0x80;
            }
        }
        return { inLaneIdx, permutedIdx };
    }
} // namespace flcn::simd::internal
