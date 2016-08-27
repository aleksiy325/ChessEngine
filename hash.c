#include "engine.h"



uint64_t hash_board(const board_t *board){
    int i = 0;
    uint64_t hkey;
    int piece = EMPTY;
    
    //pieces
    for(i; i < BOARD_ARR_SIZE; i++){
        piece = board->board_arr[i];

        if(piece != NOT_SQR && piece != EMPTY){
            hkey ^= piece_keys[piece][i];
        }
    }

    //side to move
    if(board->side == WHITE){
        hkey ^= side_key;
    }
    
    //enpas
    if(board->enpas != NOT_SQR){
        hkey ^= piece_keys[EMPTY][board->enpas];
    }

    //castle
    hkey ^= castle_key[board->castle];

    return hkey;

}