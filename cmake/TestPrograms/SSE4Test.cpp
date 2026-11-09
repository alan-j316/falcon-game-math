/**
 * @file SSE4Test.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 14, 2026
 *
 * @brief Test program for verifying SSE4 support.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "../../../../../../../Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.51.36231/include/emmintrin.h"

#include <immintrin.h>
#include <smmintrin.h>

int main()
{
    const __m128d data                   = _mm_set_pd1(124.56);
    const auto rounded                   = _mm_ceil_pd(data);
    [[maybe_unused]] volatile int scalar = _mm_cvtpd_epi32(rounded);
    return 0;
}
