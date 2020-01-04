#include "main_aux.h"
#include <stdio.h>

/* Print the board to stdout */
void print_board(int** game_board, int** fixed_board)
{
  int i = 0;
  int j = 0;
  for (i = 0; i < BOARD_SIZE; i++)
  {
    if((i % 3) == 0) printf(SEPERATOR_ROW); /* row seperator before every 4 rows */
    for (j = 0; j < BOARD_SIZE; j++)
    {
      if ((j % 3) == 0) /* pipe before every 3 cells */
      {
        if(j != 0) putchar(' '); /* no space at row start */
        putchar('|');
      }
      putchar(' ');
      if(fixed_board[j][i]) putchar('.'); /* fixed cell */
      else putchar(' '); /* non-fixed cell */
      if(game_board[j][i]) putchar('0'+game_board[j][i]); /* non-blank cell */
      else putchar(' '); /* blank cell */
    }
    /* end of row */
    putchar(' ');
    putchar('|');
    putchar('\n');
  }
  printf(SEPERATOR_ROW); /* final row seperator */
}

/* Initalization. Sets board to a new board with <fixed_count> empty cells. */
int init(int** board, int** fixed, int** sol) {
  int fixed_count;
  int** empty = new_board();
  copy_board(board, empty);
  copy_board(fixed, empty);
  copy_board(sol, empty);
  printf("Please enter the number of cells to fill [0-80]:\n");
  scanf("%d", &fixed_count);
  if (feof(stdin)) {
    printf("Exiting...\n");
    free_board(board);
    free_board(fixed);
    free_board(sol);
    return 0;
  }
  while (fixed_count < 0 || fixed_count > 80) {
    printf("Error: invalid number of cells to fill (should be between 0 and 80)\n");
    scanf("%d", &fixed_count);
    if (feof(stdin)) {
      printf("Exiting...\n");
      free_board(board);
      free_board(fixed);
      free_board(sol);
      return 0;
    }
  }
  generate_puzzle(board, sol, fixed, fixed_count);
  print_board(board, fixed);
  return 1;
}