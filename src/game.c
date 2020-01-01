#include game.h

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
    board[i] = calloc(sizeof(int) * BOARD_SIZE);
    if(board[i] == NULL)
    {
      exit(-1);
    }
  }
  return board;
}