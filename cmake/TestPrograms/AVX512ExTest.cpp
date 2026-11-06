/**
 * @file AVX512ExTest.cpp
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
    float data[16] {0};
    const __m512 a = _mm512_setzero_ps();
    _mm512_storeu_ps(data, a);
    return 0;
}