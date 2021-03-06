#include "game.h"

int** new_board()
{
  int i;
  int** board = malloc(sizeof(int*) * BOARD_SIZE);
  if(board == NULL)
  {
    exit(-1);
  }
  for (i = 0; i < BOARD_SIZE; i++)
  {
    board[i] = calloc(BOARD_SIZE, sizeof(int));
    if(board[i] == NULL)
    {
      exit(-1);
    }
  }
  return board;
}

void free_board(int** board) {
    int iter;
    for (iter=0; iter < BOARD_SIZE; iter++) {
        free(board[iter]);
    }
    free(board);
}

int validate(int** board, int** solution) {
    int** temp_solution = solve(board, 0);
    if (temp_solution == UNSOLVABLE) {
        return 0;
    }
    free(solution);
    solution = temp_solution;
    return 1;
}

int is_legal(int** board, int x, int y, int val) {
    int iter;
    int x_block_offset = x/3;
    int y_block_offset = y/3;
    if (val == EMPTY_CELL) {
        return 1;
    }
    if (val < 0 || val > BOARD_SIZE) {
        return 0;
    }
    for (iter = 0; iter < BOARD_SIZE; iter++) {
        if (board[x][iter] == val || board[iter][y] == val) {
            return 0;
        }
    }
    for (iter = 0; iter < BOARD_SIZE; iter++) {
        if (board[(iter%BLOCK_SIZE) + x_block_offset*BLOCK_SIZE][(iter/BLOCK_SIZE) + y_block_offset*BLOCK_SIZE] == val) {
            return 0;
        }

    }
    return 1;
}

int set(int** board, int** fixed, int x, int y, int val) {
    if (is_legal(board, x, y, val && !fixed[x][y])) {
        board[x][y] = val;
        return 1;
    }
    return 0;
}

int hint(int** solved_board, int x, int y) {
    return solved_board[x][y];
}

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