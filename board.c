#include <stdio.h>
#include <stdlib.h>  
#include <assert.h> 
#include "engine.h"

char pcechar[] = ".PNBRQKpnbrqk";
char sidechar[] = "wb-";
char rankchar[] = "12345678";
char filechar[] = "abcdefgh";


void board_parse_fen(p_board_t p_board, char* fen){
    assert(fen != NULL);
    assert(p_board != NULL);

    uint16_t i = 0;
    uint16_t sq64 = 0;
    uint16_t pce = EMPTY;

    board_reset(p_board);

    while(fen[i] == ' '){i++;}

    while(sq64 < BOARD_SIZE){
        switch (fen[i]){
            case 'p': pce = bP; break;  //blacks
            case 'n': pce = bN; break;
            case 'b': pce = bB; break;
            case 'r': pce = bR; break;
            case 'q': pce = bQ; break;
            case 'k': pce = bK; break;

            case 'P': pce = wP; break; // white
            case 'N': pce = wN; break;
            case 'B': pce = wB; break;
            case 'R': pce = wR; break;
            case 'Q': pce = wQ; break;
            case 'K': pce = wK; break;

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                 sq64 += fen[i] - '0' - 1; // -1 for ++ later
                 pce = EMPTY;
                 break; 

            case '/': 
                assert(sq64 % 8 == 0);
                sq64--;
                break;
            
            default: 
                printf("FEN error: %d index of fen string.  Char: '%c' (POS)  \n", i, fen[i]); 
                return -1;
        }        

        p_board->board_arr[B120(BOARD_SIZE - sq64 - 1)] = pce;      //Correct for board orientation TODO reverse loop instead

        i++;
        sq64++;
    }
    assert(sq64 == BOARD_SIZE);

    //parse side to move 
    while(fen[i] == ' '){i++;} //skip spaces

    uint16_t side = NULL;

    switch (fen[i]){
        case 'w': side = WHITE; break;
        case 'b': side = BLACK; break;
        default: 
            printf("FEN error: %d index of fen string. Char: '%c' (SIDE)  \n", i, fen[i]); 
            return -1;
    }
    i++;

    p_board->side = side;

    //castle
    while(fen[i] == ' '){i++;} //skip spaces

    uint16_t cnt = 0;
    while( cnt < 4 && fen[i] != ' '){    // castle rights 4 chars or 2 dashes
        switch (fen[i]){
            case 'K': p_board->castle |= WKSC; break;
            case 'Q': p_board->castle |= WQSC; break;
            case 'k': p_board->castle |= BKSC; break;
            case 'q': p_board->castle |= BQSC; break;
            case '-': cnt+=3; break; 
            default: 
                printf("FEN error: %d index of fen string. Char: '%c' (CASTLE)  \n", i, fen[i]); 
                return -1;
        }
        cnt++;
        i++;
    }
    assert(cnt > 2 && cnt < 5);
    assert(p_board->castle >= 0 && p_board->castle <= 15);

    //enpas
    while(fen[i] == ' '){i++;} //skip spaces

    if( fen[i] != '-'){
        uint16_t f = fen[i] - 'a';
        uint16_t r = fen[++i] - '1';
        assert( f >= F_A && f <= F_H);
        assert(r >= R_1 && r <= R_8);
        p_board->enpas = FR2SQ(f,r);
    }

    //halfmoves 50 move rule
    //fullmoves 
    //TODO FIX


    /*
    char* end;
    uint16_t ply = strtol(fen +  , &end, 10 );
    uint16_t moves = strtol(end, &end, 10);
    printf("Plys: %d\n", ply);
    printf("Moves: %d\n", moves);
    */

    
    p_board->hkey = hash_board(p_board);
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

void board_print(const p_board_t p_board){
    int f,r, sq, piece;
    
    printf("\n");
    for(r = R_8; r >= R_1; r-- ){       // board
        printf("%3c", rankchar[r]);
        for(f = F_A; f <= F_H; f++){
            sq = FR2SQ(f,r);
            piece = p_board->board_arr[sq];
            printf("%3c", pcechar[piece]);
        }
        printf("\n");
    }

    printf("\n%3c", ' ');                 //labels
    for(f = F_A; f <= F_H; f++){
        printf("%3c", filechar[f]);
    }   

    printf("\n\n Castle: ");        //castling rights
    int b = 0;
    if(p_board->castle & 1){
        printf("K");
        b++;
    }
    if(p_board->castle & 2){
        printf("Q");
        b++;
    }
    if(p_board->castle & 4){
        printf("k");
        b++;
    }
    if(p_board->castle & 8){
        printf("q");
        b++;
    }
    if(!b){
        printf("-");
    }
    printf("\n");

    printf(" Side: %c\n", sidechar[p_board->side]); //side
    printf(" Hash: %x\n", p_board->hkey);           //hash

}