/**
 * @file FMATest.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: September 12, 2026
 *
 * @brief Test program for verifying FMA support.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include <immintrin.h>

int main()
{
    const __m128 a = _mm_set1_ps(0.5f);
    const __m128 b = _mm_set1_ps(1.5f);
    const __m128 c = _mm_set1_ps(2.5f);

    [[maybe_unused]] __m128 result = _mm_fmadd_ps(a, b, c);
}
