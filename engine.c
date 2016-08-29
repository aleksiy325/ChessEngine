#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <libgen.h>
#include "engine.h"


/*GLOBALS*/
//lookup tables
B120 B120_to_B64;
B64 B64_to_B120;

//bitmasks
bitboard_t setmask[64];
bitboard_t clearmask[64];

//hashkeys
uint64_t piece_keys[13][120];
uint64_t side_key;
uint64_t castle_key[16];

void init_hashkeys(){
    int i = 0;
    int j = 0;
    for(i; i < 13; i++){
        for(j; j < 120; j++){
            piece_keys[i][j] = RAND_64;
        }
    }
    side_key = RAND_64;
    for(i = 0; i < 16; i++){
        castle_key[i] = RAND_64;
    }
}

void init_bitmasks(){
    int i = 0;
    uint64_t set = 1;
    for(i; i < 64; i++){
        setmask[i] = set;
        set = set << 1;
        clearmask[i] = ~setmask[i];
    }
}

void print_bitmasks(){
    int i = 0;
    for(i; i < 64; i++){
       print_bitboard(clearmask[i]);
    }
}

void init_board_lookup(){
    //initialize lookup tables for 120 and 64 board conversions.
    int rank = R_1;
    int sq64 = 0;
    int sq120 = 0;

    int i = 0;
    for(i; i < BOARD_ARR_SIZE; i++){
        B120_to_B64[i] = NOT_SQR;
    }

    for(rank; rank <= R_8; rank++){
        int file = F_A;
        for(file; file <= F_H; file++){
            sq120 = 21 + file + (rank * 10);
            B64_to_B120[sq64]= sq120;
            B120_to_B64[sq120] = sq64;
            sq64++;
        }
    }

}

void print_lookup_boards(){
    //print 64
    int i = 0;
    for(i; i < 64; i++){
        if(i % 8 == 0 ){ printf("\n");}
        printf("%4d", B64_to_B120[i]);
    }
     printf("\n");
     //print 120
    i = 0;
    for(i; i < 120; i++){
        if(i % 10 == 0 ){ printf("\n");}
        printf("%4d", B120_to_B64[i]);
    }
    printf("\n");

}

int main ( int argc, char **argv ) {
    init_board_lookup();
    init_bitmasks();
    init_hashkeys();
    /*
    print_lookup_boards();
    bitboard_t test = 18446744073709551615;
    printf( "%d\n" , bitcount(test));
    bitpop(&test);
    print_bitboard(test);
    */

    board_t board;
    board_parse_fen(&board, START_FEN);
    board_print(&board);
    board_parse_fen(&board, TEST_FEN_1);
    board_print(&board);
    board_parse_fen(&board, TEST_FEN_2);
    board_print(&board);
    board_parse_fen(&board, TEST_FEN_3);
    board_print(&board);
    board_parse_fen(&board, TEST_FEN_4);
    board_print(&board);
    board_parse_fen(&board, TEST_FEN_5);
    board_print(&board);
    return 0; 
}