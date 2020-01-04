#include "solver.h"

/*Set next_i and next_j to point to the next cell
Return 1 if i and j point to the last cell */
int advance_position(int* next_i, int* next_j, int i, int j)
{
  if (i >= BOARD_SIZE-1 && j >= BOARD_SIZE-1) /* can't advance */
  {
    return 1;
  }
  else
  {
    if (i < BOARD_SIZE - 1)
    {
      *next_i = i + 1;
      *next_j = j;
    }
    else /* next row */
    {
      *next_i = 0;
      *next_j = j + 1;
    }
  }
  return 0;
}

/* Copy in_board's contents to out_board */
void copy_board(int** out_board, int** in_board)
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

/*Allocate and fill valid_options with the valid options for cell i,j
in game_board
Return the number of valid options */
int get_valid_options(int** valid_options, int** game_board, int i, int j)
{
  int k;
  int n;
  *valid_options = malloc(sizeof(int) * BOARD_SIZE);
  if(valid_options == NULL) 
  {
    /* TODO: print error message */
    exit(-1); /* malloc failed */
  }
  n = 0;
  for (k = 1; k < BOARD_SIZE+1; k++)
  {
    if(is_legal(game_board, i, j, k) == LEGAL_MOVE)
    {
      (*valid_options)[n] = k; /* add valid move */
      n++; /* update size */
    }
  }
  return n; /* the number of valid options */
}

/* Shift the contents of valid_options based on the chosen option 
offset is the chosen index, k is the current "turn" */
void update_options(int* valid_options, int k, int offset)
{
  int i;
  i = k + offset;
  for (; i > k; i--)
  {
    valid_options[i] = valid_options[i-1];
  }
}

/* Solve and update board with the solution using recursion
If random is set to 1, the next option from the list of valid options
for a cell is chosen randomly */
int solve_rec(int** board, int i, int j, int random)
{
  int k;
  int offset;
  int number_of_options;
  int next_i;
  int next_j;
  int* valid_options;
  if (board[i][j] == EMPTY_CELL)
  {
    number_of_options = get_valid_options(&valid_options, board, i, j);
    for(k = 0; k < number_of_options; k++)
    {
      offset = 0; /* always choose the first valid option not yet tried if random=0 */
      if(random && (number_of_options - k) > 1) offset = rand()%(number_of_options - k);
      board[i][j] = valid_options[k+offset];
      update_options(valid_options, k, offset);
      if(advance_position(&next_i, &next_j, i, j) != 1)
      {
        if(solve_rec(board, next_i, next_j, random))
        {
          free(valid_options);
          return 1; /* solved */
        }
      }
      else /* we have a valid option for the last cell */
      {
        free(valid_options);
        return 1;
      } 
    }
    /* not solvable */
    board[i][j] = EMPTY_CELL;
    free(valid_options);
    return 0;
  }
  else /* not an empty cell */
  {
    if(advance_position(&next_i, &next_j, i, j) != 1)
    {
      return solve_rec(board, next_i, next_j, random);
    }
    else /* last cell */
    {
      return 1;
    }
  } 
}

/* Solves game_board, randomly if random is not 0
A newly allocated solved board is returned if there is a solution
or NULL if there isn't one */
int** solve(int** game_board, int random)
{
  int** solved_board = new_board();
  copy_board(solved_board, game_board);
  if (solve_rec(solved_board, 0, 0, random)) return solved_board;
  else
  {
    free_board(solved_board);
    return NULL;
  }
}

/* Input: game_board, solved_board, fixed_board are EMPTY_CELL filled boards
Output: A puzzle with fixed_count fixed cells is randomly generated
The input boards contents are filled accordingly */
void generate_puzzle(int** game_board, int** solved_board ,int** fixed_board, int fixed_count)
{
  int k = 0;
  int i;
  int j;
  int** temp_board;
  temp_board = solve(game_board, 1); /* solve an empty board randomly */
  copy_board(game_board, temp_board);
  copy_board(solved_board, temp_board);
  free_board(temp_board);

  /* choose fixed cells */
  while (k < fixed_count)
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