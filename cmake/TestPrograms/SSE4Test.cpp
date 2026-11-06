/**
 * @file AVX512Test.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 14, 2026
 *
 * @brief Test program for verifying SSE4 support.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include <immintrin.h>
#include <smmintrin.h>

int main()
{
    const __m128d data                  = _mm_set_pd1(124.56);
    [[maybe_unused]] const auto rounded = _mm_ceil_pd(data);
    return 0;
}
