/**
 * @file AVX512FTest.cpp
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
    const __m128i a                       = _mm_setzero_si128();
    const __m128i b                       = _mm_setzero_si128();
    // AVX512DQ/VL Instruction
    [[maybe_unused]] const __m128i result = _mm_mullo_epi64(a, b);
    return 0;
}
