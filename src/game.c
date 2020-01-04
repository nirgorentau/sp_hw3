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
        return LEGAL_MOVE;
    }
    if (val < 0 || val > BOARD_SIZE || x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
        return INVALID_VALUE;
    }
    for (iter = 0; iter < BOARD_SIZE; iter++) {
        if (board[x][iter] == val || board[iter][y] == val) {
            return INVALID_VALUE;
        }
    }
    for (iter = 0; iter < BOARD_SIZE; iter++) {
        if (board[(iter%BLOCK_SIZE) + x_block_offset**BLOCK_SIZE][(iter/BLOCK_SIZE) + y_block_offset**BLOCK_SIZE] == val) {
            return INVALID_VALUE;
        }

    }
    return LEGAL_MOVE;
}

int set(int** board, int** fixed, int x, int y, int val) {
    if (is_legal(board, x, y, val) == INVALID_VALUE) {
        return INVALID_VALUE;
    }
    if (fixed[x][y] == 1) {
        return FIXED_VALUE;
    }
    board[x][y] = val;
    return LEGAL_MOVE;
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