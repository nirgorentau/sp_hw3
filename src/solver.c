#include "solver.h"
int** new_board(int width, int height)
{
  int i = 0;
  int** board = malloc(sizeof(int*) * width);
  for (i = 0; i < width; i++)
  {
    game_board[i] = malloc(sizeof(int) * height);
  }
  return board;
}

void copy_board(int** out_board, int** in_board, int width, int height);
{
  int i; int j;
  for (i = 0; i < width; i++)
  {
    for (j = 0;j < height; j++)
    {
      out_board[i][j] = in_board[i][j];
    }
  }
}

int advance_position(int* next_i, int* next_j, int i, int j, int width, int height)
{
  if (i >= width-1 && j >= height-1) /* can't advance */
  {
    return 1;
  }
  else
  {
    if (j < height - 1)
    {
      next_j* = j + 1;
    }
    else /* next column */
    {
      next_j* = 0;
      next_i* = i + 1;
    }
  }
  return 0;
}

int solve_deterministic_rec(int** game_board, int i, int j, int width, int height);
{
  int k;
  int next_i;
  int next_j;
  if (game_board[i][j] != 0)
  {
    for (k = 1; k < 10; k++)
    {
      if(valid_move(game_board, i, j, k, width, height))
      {
        game_board[i][j] = k;
        if(advance_position(&next_i, &next_j, i, j, width, height) != 1)
        {
          if(solve_deterministic_rec(game_board, next_i, next_j, width, height))
          return 1; /* solved */
        }
      }
      return 0 /* not solvable */;
    }
  }
  else
  {
    if(advance_position(&next_i, &next_j, i, j, width, height) != 1))
  }
  
}

int** solve_deterministic(int** game_board, int width, int height)
{
  int** board = new_board(width, height);
  copy_board(board, game_board, width, height);
  solve_deterministic_rec()
}
