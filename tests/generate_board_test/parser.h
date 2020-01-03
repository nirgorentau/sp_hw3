#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef GAME_H
#include "game.h"
#endif
#ifndef MAIN_AUX_H
#include "main_aux.h"
#endif
#define CMD_SUCCESS 0
#define CMD_ERR -1
#define CMD_EXIT 1
#define CMD_RESTART 2
int read_command(char* line, int** board, int** fixed, int** getSol);
