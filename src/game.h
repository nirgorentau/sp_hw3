#define GAME.H
#ifndef SOLVER.H
#include "solver.h"
#endif
#include <stddef.h>
#define BOARD_SIZE 9
#define BLOCK_SIZE 3
#define EMPTY_CELL 0

int** new_board(); /* allocates a new board and returns a pointer to it */
void free_board(int** board); /* frees a board's allocated memory */
int validate(int** board, int** solution);
/* validates that the current state of the board is solvable.
If is, sets solution to point at a valid solution. */
int is_legal(int** board, int x, int y, int val); /* checks that the move is legal */
int set(int** board, int x, int y, int val); /* sets the move if it is legal */
int hint(int** solved_board, int x, int y); /* gives a hint from the solved board */

