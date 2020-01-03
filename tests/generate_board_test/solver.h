#define SOLVER_H
#ifndef GAME_H
#include "game.h"
#endif
#define UNSOLVABLE NULL  /* Return value of solve functions if board is unsolvable */

/* Input: game_board, solved_board, fixed_board are EMPTY_CELL filled boards
Output: A puzzle with fixed_count fixed cells is randomly generated
The input boards contents are filled accordingly */
void generate_puzzle(int** board, int** solved_board, int** fixed_board, int fixed);

/* Copy in_board's contents to out_board */
void copy_board(int** out_board, int** in_board);

/* Solves game_board, randomly if random is not 0
A newly allocated solved board is returned if there is a solution
or NULL if there isn't one */
int** solve(int** game_board, int random); 
