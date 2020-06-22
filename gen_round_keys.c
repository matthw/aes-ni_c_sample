#include <stdio.h>
#include <stdint.h>
#include <wmmintrin.h>

//    main key
const uint8_t aes_key[16]  = {0x6d, 0x79, 0x80, 0xb9, 0xa5, 0x0a, 0x97, 0x24, 0x0d, 0x2d, 0xfc, 0x36, 0x0d, 0x95, 0x55, 0xaa};

inline __attribute__((always_inline)) __m128i get_round_key(__m128i key, uint8_t round) {

    __m128i xmm0 = key;
    __m128i xmm1;
    __m128i xmm2;

    xmm2 = _mm_xor_si128(xmm2, xmm2);

    xmm1 = _mm_aeskeygenassist_si128(key, round);
    xmm1 = _mm_shuffle_epi32(xmm1, 0xff);

    xmm2 = (__m128i)_mm_shuffle_ps((__m128)xmm2, (__m128)xmm0, 0x10);
    xmm0 = _mm_xor_si128(xmm0, xmm2);

    xmm2 = (__m128i)_mm_shuffle_ps((__m128)xmm2, (__m128)xmm0, 0x8c);
    xmm0 = _mm_xor_si128(xmm0, xmm2);

    xmm0 = _mm_xor_si128(xmm0, xmm1);

    return xmm0;
}

void dump_128(__m128i brol) {
    char *lol = (char *)&brol;
    for (uint8_t i = 0; i < 16; i++)
          printf("0x%02hhx, ", lol[i]);
    puts("");
}


int main(void) {
    __m128i tmp;


    puts("Encryption round keys");
    tmp = get_round_key(_mm_loadu_si128((__m128i *)aes_key), 0x1);
    dump_128(tmp);
    tmp = get_round_key(tmp, 0x2);
    dump_128(tmp);
    tmp = get_round_key(tmp, 0x4);
    dump_128(tmp);
    tmp = get_round_key(tmp, 0x8);
    dump_128(tmp);
    tmp = get_round_key(tmp, 0x10);
    dump_128(tmp);
    tmp = get_round_key(tmp, 0x20);
    dump_128(tmp);
    tmp = get_round_key(tmp, 0x40);
    dump_128(tmp);
    tmp = get_round_key(tmp, 0x80);
    dump_128(tmp);
    tmp = get_round_key(tmp, 0x1b);
    dump_128(tmp);
    tmp = get_round_key(tmp, 0x36);
    dump_128(tmp);

    return 0;
}
    
