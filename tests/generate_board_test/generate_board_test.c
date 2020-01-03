#include "main_aux.h"
#include "game.h"
#include "solver.h"
int main()
{
  int** game_board = new_board();
  int** fixed_board = new_board();
  int** sol_board = new_board();
  generate_puzzle(game_board, sol_board, fixed_board, 20);
  print_board(game_board, fixed_board);
  print_board(sol_board, fixed_board);
  free_board(game_board);
  free_board(fixed_board);
  free_board(sol_board);
  return 0;
}