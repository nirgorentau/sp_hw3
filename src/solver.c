#include "solver.h"

int advance_position(int* next_i, int* next_j, int i, int j)
{
  if (i >= BOARD_SIZE-1 && j >= BOARD_SIZE-1) /* can't advance */
  {
    return 1;
  }
  else
  {
    if (j < BOARD_SIZE - 1)
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

void copy_board(int** out_board, int** in_board);
{
  int i; int j;
  for (i = 0; i < BOARD_SIZE; i++)
  {
    for (j = 0;j < BOARD_SIZE; j++)
    {
      out_board[i][j] = in_board[i][j];
    }
  }
}

int get_valid_options(int** valid_options, int** game_board, int i, int j)
{
  int k;
  int n;
  *valid_options = malloc(sizeof(int) * BOARD_SIZE);
  if(valid_options == NULL) 
  {
    exit(-1); /* malloc failed */
  }
  n = 0;
  for (k = 1; k < BOARD_SIZE+1; k++)
  {
    if(valid_move(game_board, i, j, k))
    {
      (*valid_options)[n] = k; /* add valid move */
      n++; /* update size */
    }
  }
  return n; /* the number of valid options */
}

/* i is the chosen index, k is the current "turn" */
void update_options(int* valid_options, int k, int offset)
{
  int i;
  i = k + offset;
  for (; i > k; i--)
  {
    valid_options[i+1] = valid_options[i];
  }
}

int solve_rec(int** game_board, int i, int j, int random);
{
  int k;
  int offset;
  int number_of_options;
  int next_i;
  int next_j;
  int* valid_options;
  if (game_board[i][j] == EMPTY_CELL)
  {
    number_of_options = get_valid_options(&valid_options, game_board, i, j);
    for(k = 0; k < number_of_options; k++)
    {
      offset = 0;
      if(random && (number_of_options - k) > 1) offset = rand()%(number_of_options - k);
      game_board[i][j] = valid_options[k+offset];
      update_options(valid_options, k, offset);
      if(advance_position(&next_i, &next_j, i, j) != 1)
      {
        if(solve_rec(game_board, next_i, next_j, random))
        {
          free(valid_options);
          return 1; /* solved */
        }
      }
      else /*we have a valid option for the last cell */
      {
        free(valid_options);
        return 1;
      } 
    }
    /* not solvable */
    game_board[i][j] = EMPTY_CELL;
    free(valid_options);
    return 0;
    }
  }
  else /* not an empty cell */
  {
    if(advance_position(&next_i, &next_j, i, j) != 1))
    {
      return solve_rec(game_board, next_i, next_j);
    }
    else /* last cell */
    {
      return 1;
    }
  } 
}

int** solve(int** game_board, int random)
{
  int** solved_board = new_board();
  copy_board(solved_board, game_board);
  if (solve_rec(board, 0, 0, random) return solved_board;
  else
  {
    free_board(board);
    return NULL;
  }
}

void generate_puzzle(int** game_board, int** solved_board ,int** fixed_board, int fixed)
{
  int k = 0;
  int i;
  int j;
  solve(solved_board, 1); /* solve an empty board randomly */
  copy_board(game_board, solved_board);

  while (k < fixed)
  {
    i = rand()%BOARD_SIZE;
    j = rand()%BOARD_SIZE;
    if (!fixed_board[i][j])
    {
      fixed_board[i][j] = 1;
      k++;
    }
  }

  /* empty non-fixed cells */
  for (k = 0; k < BOARD_SIZE*BOARD_SIZE; k++)
  {
    i = k/BOARD_SIZE;
    j = k%BOARD_SIZE;
    if(!fixed_board[i][j]) game_board[i][j] = EMPTY_CELL;
  }
  
}