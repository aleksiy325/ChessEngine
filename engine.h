#include <stdint.h>


//Using 10x12 board representation https://chessprogramming.wikispaces.com/10x12+Board
#define BOARD_ARR_SIZE 120
#define BOARD_SIZE 64
#define MAX_GAME_PLYS 2048  

/* MACROS */

#define bitset(bb, i) ( bb |= (1 << i))
#define bitclear(bb, i) ( bb &= ~(1 << i))     
#define bittest(bb, i) (( bb >> i ) & 1 )



/*GLOBALS*/

//lookup table definitions
typedef uint16_t B120[BOARD_ARR_SIZE] ;
typedef uint16_t B64[BOARD_SIZE];
extern B120 B120_to_B64;
extern B64 B64_to_B120;

/*TYPEDEFS*/

typedef uint64_t bitboard_t;


//rank and file
enum{ R_1, R_2, R_3, R_4, R_5, R_6, R_7, R_8};
enum{ F_A, F_B, F_C, F_D, F_E, F_F, F_G, F_H};

//piece definitions
enum{ EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bQ, bK};
enum{ WHITE, BLACK, BOTH};


//board square definitions
enum{
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, NOT_SQR
};

//castle definitions
enum {WKSC = 1, WQSC = 2, BKSC = 4, BQSC = 8};


//undo for undoing moves
typedef struct undo{
    uint16_t move;
    uint16_t castle;
    uint16_t enpas;
    uint16_t moves_made;
    uint64_t pos_key;
}undo_t;

typedef struct board{
    uint16_t board_arr[BOARD_ARR_SIZE]; 
    bitboard_t pawns[3];                      // bit pawn representation, white, black, both
    uint16_t king_sq[2];                    //location of kings 
    uint16_t side;                          // turn to play
    uint16_t enpas;                         //en passant
    uint16_t moves_made;                    // number of moves made for 50 move rule;
    uint16_t ply;                           //half moves
    uint16_t hply;                          //history of half moves
    uint16_t castle;                        // 4 bit castle permissions


    //for evaluation indexed w , b, both.
    uint16_t num_piece[13];                 //stores the amount of each piece by index
    uint16_t not_pawns[3];
    uint16_t rook_queen[3];
    uint16_t bish_knight[3];

    undo_t history[MAX_GAME_PLYS];

    uint16_t pce_list[13][10];
    
    uint64_t pos_key;                       
} board_t;


/*FUNCTIONS*/

//engine funcs
void print_lookup_boards();
void init_board_lookup();


//bitboard funcs
uint32_t bitscan(bitboard_t bb);
uint32_t bitcount(bitboard_t bb);
void print_bitboard(bitboard_t bb);