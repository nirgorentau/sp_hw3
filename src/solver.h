#define SOLVER.H
#ifndef GAME.H
#include "game.h"
#endif
void generate_puzzle(int** board, int** solved_board, int** fixed_board, int fixed);

/* copy in_board to out_board */
void copy_board(int** out_board, int** in_board);

/* return a new allocated board,
or NULL if no solution exists */
int** solve(int** game_board, int random); 

int advance_position(int* next_i, int* next_j, int i, int j);
