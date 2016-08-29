#include "engine.h"



uint64_t hash_board(const p_board_t p_board){
    int i = 0;
    uint64_t hkey;
    int piece = EMPTY;
    
    //pieces
    for(i; i < BOARD_ARR_SIZE; i++){
        piece = p_board->board_arr[i];

        if(piece != NOT_SQR && piece != EMPTY){
            hkey ^= piece_keys[piece][i];
        }
    }

    //side to move
    if(p_board->side == WHITE){
        hkey ^= side_key;
    }
    
    //enpas
    if(p_board->enpas != NOT_SQR){
        hkey ^= piece_keys[EMPTY][p_board->enpas];
    }

    //castle
    hkey ^= castle_key[p_board->castle];

    return hkey;
}