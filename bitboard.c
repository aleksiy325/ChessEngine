#include "engine.h"
#include <assert.h>

const uint32_t lsb_64_table[64] =
{
   63, 30,  3, 32, 59, 14, 11, 33,
   60, 24, 50,  9, 55, 19, 21, 34,
   61, 29,  2, 53, 51, 23, 41, 18,
   56, 28,  1, 43, 46, 27,  0, 35,
   62, 31, 58,  4,  5, 49, 54,  6,
   15, 52, 12, 40,  7, 42, 45, 16,
   25, 57, 48, 13, 10, 39,  8, 44,
   20, 47, 38, 22, 17, 37, 36, 26
};
 

uint32_t bitpop(p_bitboard_t bb) {
   
   //assert (bb != 0);
   bitboard_t nb = *bb ^ *bb - 1;
   uint32_t folded = (int) *bb ^ (*bb >> 32);
   *bb &= *bb - 1;
   return lsb_64_table[folded * 0x78291ACF >> 26];
}

// 64 bit hamming weight function https://en.wikipedia.org/wiki/Hamming_weight
uint32_t bitcount(bitboard_t bb){
    bb = bb - ((bb >> 1) & 0x5555555555555555);
    bb = (bb & 0x3333333333333333) + ((bb >> 2) & 0x3333333333333333);
    return (((bb + (bb >> 4)) & 0xF0F0F0F0F0F0F0F) * 0x101010101010101) >> 56;
}


void print_bitboard(bitboard_t bb){
    int i = 0;
    for(i; i < sizeof(bitboard_t) * 8; i++){
        if(i % 8 == 0 ){ printf("\n"); }
        printf("%2d", bittest(bb, i));
    }
    printf("\n");
}