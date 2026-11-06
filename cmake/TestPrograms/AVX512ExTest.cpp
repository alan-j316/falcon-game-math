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
    const __m128i a = _mm_setzero_si128();
    const __m128i b = _mm_setzero_si128();
    // -mavx512cd;-mavx512fp16;
    // AVX512DQ/VL Instruction
    [[maybe_unused]] const __m128i result = _mm_mullo_epi64(a, b);
    // AVX512BW
    [[maybe_unused]] const __m512i result2 = _mm512_abs_epi16(_mm512_setzero_si512());
    // AVX512_VBMI2
    [[maybe_unused]] const __m512i result3 =
        _mm512_shldv_epi16(_mm512_setzero_si512(), _mm512_setzero_si512(), _mm512_setzero_si512());
    // AVX512FP16
    [[maybe_unused]] const __m128h result4 = _mm_setzero_ph();
    // AVX512CD + VL
    [[maybe_unused]] const __m128i result5 = _mm_lzcnt_epi32(_mm_setzero_si128());
    return 0;
}
