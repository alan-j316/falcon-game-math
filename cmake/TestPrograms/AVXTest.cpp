/**
 * @file AVXTest.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 10, 2026
 *
 * @brief Test program for verifying AVX512 support.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include <immintrin.h>

int main()
{
    float data[8] = {0};
    const __m256 a = _mm256_setzero_ps();
    _mm256_storeu_ps(data, a);
    return 0;
}