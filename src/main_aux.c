#include "main_aux.h"
#include <stdio.h>
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
