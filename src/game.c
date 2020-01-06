#include "game.h"
#include <stdio.h>
/* function new_board
Creates a new board, with all cells set to EMPTY_CELL
*/
int** new_board()
{
  int i, j;
  int** board = malloc(sizeof(int*) * BOARD_SIZE);
  if(board == NULL)
  {
    printf("Error: malloc failed\n");
    exit(-1);
  }
  for (i = 0; i < BOARD_SIZE; i++)
  {
    board[i] = calloc(BOARD_SIZE, sizeof(int));
    if(board[i] == NULL)
    {
      printf("Error: calloc failed\n");
      exit(-1);
    }
  }
  /* initialize board to contain empty cells */
  for (i = 0; i < BOARD_SIZE; i++) {
      for (j = 0; j < BOARD_SIZE; j++) {
          board[i][j] = EMPTY_CELL;
      }
  }
  return board;
}
/* function free_board
frees the memory that the board uses.
*/
void free_board(int** board) {
    int iter;
    for (iter=0; iter < BOARD_SIZE; iter++) {
        free(board[iter]);
    }
    free(board);
}

/* function validate
Checkes whether <board> is solvable or not.
returns 1 if solvable, 0 otherwise.
if is solvable, updates <solution> to match current valid solution.
*/
int validate(int** board, int** solution) {
    int** temp_solution = solve(board, 0);
    if (temp_solution == UNSOLVABLE) {
        return 0;
    }
    copy_board(solution, temp_solution);
    free_board(temp_solution);
    return 1;
}

/* function is_legal
checks if placing <val> in <x,y> is a valid move according to sudoku rules of placement.
input:
<board> - the game board
<x,y> - coordiantes (0-indexed)
<val> - value to place (1-9 or EMPTY_CELL)
returns LEGAL_MOVE if it is, INVALID_VALUE if not.
*/
int is_legal(int** board, int x, int y, int val) {
    int i, j;
    int x_block_offset = x/3;
    int y_block_offset = y/3;
    int old_val;
    /* Cleaning a cell is always valid */
    if (val == EMPTY_CELL) {
        return LEGAL_MOVE;
    }
    /* Ignore current cell value */
    old_val = board[x][y];
    board[x][y] = -1;
    /* Check column and row */
    for (i = 0; i < BOARD_SIZE; i++) {
        if (board[x][i] == val || board[i][y] == val) {
            board[x][y] = old_val;
            return INVALID_VALUE;
        }
    }
    /* Check block */
    for (i = 0; i < BLOCK_SIZE; i++) {
        for (j = 0; j < BLOCK_SIZE; j++) {
            if (board[i + x_block_offset*BLOCK_SIZE][j + y_block_offset*BLOCK_SIZE] == val) {
                board[x][y] = old_val;
                return INVALID_VALUE;
            }
        }
    }
    board[x][y] = old_val;
    return LEGAL_MOVE;
}

/* function set
Validates the given move and performs it if valid.
Returns:
LEGAL_MOVE if move was valid
INVALID_VALUE if <x,y,val> not in valid range or if column, row or block already contains <val>
FIXED_VALUE if cell is fixed and cannot be changed
*/
int set(int** board, int** fixed, int x, int y, int val) {
    /* If out of bounds */
    if (val < 0 || val > BOARD_SIZE || x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
        return INVALID_VALUE;
    }
    /* Checks if the cell <x,y> is fixed */
    if (fixed[x][y] != EMPTY_CELL) {
        return FIXED_VALUE;
    }
    if (is_legal(board, x, y, val) == INVALID_VALUE) {
        return INVALID_VALUE;
    }
    board[x][y] = val;
    return LEGAL_MOVE;
}

/*
Returns a hint to <x, y> according to <solved_board>
*/
int hint(int** solved_board, int x, int y) {
    return solved_board[x][y];
}


/*
Checks if the board is full.
returns 1 if is full, 0 else.
Assumption is that full board == solved board
*/
int is_full(int** board) {
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY_CELL) {
                return 0;
            }
        }
    }
    return 1;
}