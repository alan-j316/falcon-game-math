/**
 * @file AVX512Test.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 14, 2026
 *
 * @brief Test program for verifying Arm Neon support.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include <arm_neon.h>

int main()
{
    const float rawData[4] = { 1.0f, 2.0f, 3.0f, 4.0f };
    const float32x4_t data = vld1q_f32(rawData);
    return 0;
}
