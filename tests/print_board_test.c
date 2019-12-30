#include "main_aux.h"
#include <stdlib.h>
int main()
{
  int i = 0;
  int j = 0;
  int** game_board = malloc(sizeof(int*) * BOARD_WIDTH);
  int** fixed_board = malloc(sizeof(int*) * BOARD_WIDTH);
  for (i = 0; i < BOARD_WIDTH; i++)
  {
    game_board[i] = malloc(sizeof(int) * BOARD_HEIGHT);
    fixed_board[i] = malloc(sizeof(int) * BOARD_HEIGHT);
  }
  for (i = 0; i < BOARD_WIDTH; i++)
  {
    for (j = 0; j < BOARD_HEIGHT; j++)
    {
      game_board[i][j] = 5;
      fixed_board[i][j] = 0;
    }
  }
  print_board(game_board, fixed_board);
  for (i = 0; i < BOARD_WIDTH; i++)
  {
    free(game_board[i]);
    free(fixed_board[i]);
  }
  free(game_board);
  free(fixed_board);
  return 0;
}