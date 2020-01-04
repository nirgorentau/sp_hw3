#define MAIN_AUX_H
#ifndef GAME_H
#include "game.h"
#endif
#define SEPERATOR_ROW "----------------------------------\n"

/* Print the board to stdout */
void print_board(int** game_board, int** fixed_board);
int init(int** board, int** fixed, int** sol);
