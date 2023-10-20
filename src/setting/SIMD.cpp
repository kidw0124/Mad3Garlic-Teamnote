#include <immintrin.h>
alignas(32) int A[8]{ 1, 2, 3, 1, 2, 3, 1, 2 }, B[8]{ 1, 2, 3, 4, 5, 6, 7, 8 };
alignas(32) int C[8]; // alignas(bit size of <type>) <type> var[256/(bit size)]
// Must compute "index is multiply of 256bit"(ex> short->16k, int->8k, ...)
__m256i a = _mm256_load_si256((__m256i*)A);
__m256i b = _mm256_load_si256((__m256i*)B);
__m256i c = _mm256_add_epi32(a, b);
_mm256_store_si256((__m256i*)C, c);

__m256i _mm256_abs_epi32 (__m256i a)
_mm256_set1_epi32(__m256i a, __m256i b)
__m256i _mm256_and_si256 (__m256i a, __m256i b)
__m256i _mm256_setzero_si256 (void)
_mm256_add_pd(__m256d a, __m256d b) // double precision(64-bit)
_mm256_sub_pd(__m256 a, __m256 b) // double precision(64-bit)
__m256d _mm256_andnot_pd (__m256d a, __m256d b) // (~a)&b
__m256i _mm256_avg_epu16 (__m256i a, __m256i b) // unsigned, (a+b+1)>>1
__m256d _mm256_ceil_pd (__m256d a)
__m256d _mm256_floor_pd (__m256d a)
__m256i _mm256_cmpeq_epi64 (__m256i a, __m256i b)
__m256i _mm256_cmpgt_epi16 (__m256i a, __m256i b)
__m256d _mm256_div_pd (__m256d a, __m256d b)
__m256i _mm256_max_epi32 (__m256i a, __m256i b)
__m256i _mm256_mul_epi32 (__m256i a, __m256i b)
__m256 _mm256_rcp_ps (__m256 a) // 1/a
__m256 _mm256_rsqrt_ps (__m256 a) // 1/sqrt(a)
__m256i _mm256_set1_epi64x (long long a)
__m256i _mm256_sign_epi16 (__m256i a, __m256i b) // a*(sign(b))
__m256i _mm256_sll_epi32 (__m256i a, __m128i count) // a << count
__m256d _mm256_sqrt_pd (__m256d a)
__m256i _mm256_sra_epi16 (__m256i a, __m128i count)
__m256i _mm256_xor_si256 (__m256i a, __m256i b)
void _mm256_zeroall (void)
void _mm256_zeroupper (void)