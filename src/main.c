#include "main_aux.h"
#include "game.h"
#include "parser.h"
#include "solver.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  int cmd_code = CMD_SUCCESS;
  int** board=new_board();
  int** fixed=new_board();
  int** sol=new_board();
  char* line = malloc(sizeof(char)*1024);
  if (argc >= 2) { /* HW3 works without command-line arguments */
    srand(atoi(argv[1]));
  }
  if (!init(board, fixed, sol)) {
    return 0;
  }
  while(cmd_code != CMD_EXIT) {
    if (fgets(line, 1024, stdin) == NULL) {
      printf("Exiting...\n");
      free_board(board);
      free_board(fixed);
      free_board(sol);
      free(line);
      return 0;
    }
    cmd_code = read_command(line, board, fixed, sol);
    if (cmd_code == CMD_ERR) {
      printf("Error: invalid command\n");
    } else if (cmd_code == CMD_RESTART) {
      if (!init(board, fixed, sol)) {
        return 0;
      }
    }
  }
  printf("Exiting...\n");
  free_board(board);
  free_board(fixed);
  free_board(sol);
  free(line);
  return 0;
}
