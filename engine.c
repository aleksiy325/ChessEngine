#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <libgen.h>
#include "engine.h"


//GLOBALS
B120 B120_to_B64;
B64 B64_to_B120;

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
    print_lookup_boards();
    bitboard_t test = 18446744073709551615;
    printf( "%d\n" , bitcount(test));
    print_bitboard(test);
    return 0; 
}