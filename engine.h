#include <stdint.h>


//Using 10x12 board representation https://chessprogramming.wikispaces.com/10x12+Board
#define BOARD_ARR_SIZE 120
#define BOARD_SIZE 64
#define MAX_GAME_PLYS 2048
#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define TEST_FEN_1 "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"
#define TEST_FEN_2 "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"
#define TEST_FEN_3 "1B4r1/1bP4p/4N3/4P1p1/6PR/q2p4/2pN4/k4K2 w - - 0 1"
#define TEST_FEN_4 "1r3qr1/3P4/1p2n3/p2BPk2/8/2p4R/2Pb3p/7K w - - 0 1"
#define TEST_FEN_5 "4R3/4P3/P3p3/3P4/P4K2/8/N4n1k/8 w - - 0 1"


/* MACROS */
#define bitset(bb, i) ( bb |= setmask[i])
#define bitclear(bb, i) ( bb &= clearmask[i])     
#define bittest(bb, i) ((bb & setmask[i]) > 0)

#define RAND_64 (   (uint64_t) rand() | \
                    (uint64_t) rand() << 15 |  \
                    (uint64_t) rand() << 30 |  \
                    (uint64_t) rand() << 45 |  \
                    (uint64_t) rand() << 30 | \
                    ((uint64_t) rand() & 0xF) << 60 )

//board conversion macros
#define B64(i) (B120_to_B64[i])
#define B120(i) (B64_to_B120[i])
#define FR2SQ(f,r) ( (21 + (f) ) + ( (r) * 10 ) ) 

/*TYPEDEFS*/

typedef uint64_t bitboard_t;
typedef bitboard_t* p_bitboard_t;


//rank and file
enum{ R_1, R_2, R_3, R_4, R_5, R_6, R_7, R_8};
enum{ F_A, F_B, F_C, F_D, F_E, F_F, F_G, F_H};

//piece definitions
enum{ EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK};
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
    uint64_t hkey;
}undo_t;

typedef struct board{
    uint16_t board_arr[BOARD_ARR_SIZE]; 
    bitboard_t pawns[3];                    // bit pawn representation, white, black, both
    uint16_t king_sq[2];                    //location of kings 
    uint16_t side;                          // turn to play
    uint16_t enpas;                         //en passant
    uint16_t moves_made;                    // number of moves made for 50 move rule;
    uint16_t ply;                           //half moves
    uint16_t hply;                          //history of half moves
    uint16_t castle;                        // 4 bit castle permissions


    //for evaluation indexed w , b, both.
    uint16_t num_piece[13];                 //stores the amount of each piece by index
    uint16_t not_pawns[3];                  //big
    uint16_t rook_queen[3];                 //maj
    uint16_t bish_knight[3];                //min

    undo_t history[MAX_GAME_PLYS];

    uint16_t pce_list[13][10];
    
    uint64_t hkey;                       
} board_t;

typedef board_t* p_board_t;

/*GLOBALS*/

//lookup table definitions
typedef uint16_t B120[BOARD_ARR_SIZE] ;
typedef uint16_t B64[BOARD_SIZE];
extern B120 B120_to_B64;
extern B64 B64_to_B120;


//masks
extern bitboard_t setmask[64];
extern bitboard_t clearmask[64];

//hashing tables
extern uint64_t piece_keys[13][120];
extern uint64_t side_key;
extern uint64_t castle_key[16];

//print board defs
extern char pcechar[];
extern char sidechar[];
extern char rankchar[];
extern char filechar[];

/*FUNCTIONS*/
//bitboard funcs
uint32_t bitpop(p_bitboard_t bb);
uint32_t bitcount(bitboard_t bb);
void print_bitboard(bitboard_t bb);

//hash func;
uint64_t hash_board(p_board_t p_board);

//board funcs
void board_reset(p_board_t p_board);
void board_parse_fen(p_board_t p_board, char* fen);
void board_print(const p_board_t p_board);
