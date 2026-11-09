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
    const __m128i result = _mm_mullo_epi64(a, b);
    // AVX512BW
    const __m512i result2 = _mm512_abs_epi16(_mm512_setzero_si512());
    // AVX512_VBMI2
    const __m512i result3 = _mm512_shldv_epi16(_mm512_setzero_si512(), _mm512_setzero_si512(), _mm512_setzero_si512());
    // AVX512FP16
    const __m128h result4 = _mm_setzero_ph();
    // AVX512CD + VL
    const __m128i result5 = _mm_lzcnt_epi32(_mm_setzero_si128());

    [[maybe_unused]] volatile int sink = _mm_cvtsi128_si32(result) + _mm_cvtsi128_si32(_mm512_castsi512_si128(result2)) +
        _mm_cvtsi128_si32(_mm512_castsi512_si128(result3)) + _mm_cvtsi128_si32(_mm_castph_si128(result2)) +
        _mm_cvtsi128_si32(result5);

    return 0;
}
