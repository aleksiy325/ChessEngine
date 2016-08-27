#include <stdio.h>
#include <assert.h> 
#include "engine.h"


void board_parse_fen(char* fen, p_board_t p_board){

}

//initialize or reset board
void board_reset(p_board_t p_board){ 
    int i = 0;

    for(i; i < BOARD_ARR_SIZE; i++){
        p_board->board_arr[i] = NOT_SQR;
    }

    for(i = 0; i < BOARD_SIZE; i++){
        p_board->board_arr[B120(i)] = EMPTY;
    }

    for(i = 0; i < 3; i++){
        p_board->not_pawns[i] = 0;
        p_board->bish_knight[i] = 0;
        p_board->rook_queen[i] = 0;
        p_board->pawns[i] = 0ULL;        
    }

    for(i = 0; i < 13; i++){
        p_board->num_piece[i] = 0;
    }

    p_board->king_sq[0] = NOT_SQR;
    p_board->king_sq[1] = NOT_SQR;

    p_board->side = BOTH;
    p_board->enpas = NOT_SQR;
    p_board->moves_made = 0;
    
    p_board->ply = 0;
    p_board->hply = 0;

    p_board->castle = 0;
    p_board->hkey = 0ULL;
}