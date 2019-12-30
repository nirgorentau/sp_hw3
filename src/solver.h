#define SOLVER.H
#ifndef GAME.H
#include "game.h"
#endif
void generate_puzzle(int** board);
void copy_board(int** out_board, int** in_board);
int** solve_deterministic(int** game_board);
int** solve_random(int** game_board);
int advance_position(int* next_i, int* next_j, int i, int j);
