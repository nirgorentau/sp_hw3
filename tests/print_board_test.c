#include "main_aux.h"
int main()
{
  int i = 0;
  int j = 0;
  int game_board[9][9];
  int fixed_board[9][9];
  for (i = 0; i < 9; i++)
  {
    for (j = 0; j < 9; j++)
    {
      game_board[i][j] = 5;
      fixed_board[i][j] = 0;
    }
  }
  print_board(game_board, fixed_board);
  return 0;
}