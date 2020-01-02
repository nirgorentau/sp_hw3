#include "parser.h"

/*
A support function for read_command.
Loads the first <count> integers in <line> into <target>.
We assume that <line> is a valid command (since we only call if if it's a valid command)
*/
int load_ints(int* target, int count, char* line) {
    int iter;
    char* tmp = strtok(line, " \t\r\n"); /* Skip the first word, as we can assume it's a command */
    for (iter = 0; iter < count; iter++) {
        tmp = strtok(NULL, " \t\r\n");
        if (tmp == NULL) {
            return CMD_ERR;
        }
        target[iter] = atoi(tmp);
    }
    return CMD_SUCCESS;
}

/*
Recieves a line from the main function and parses it.
Also requires the game-board, the fixed-board and a pointer to receive a solution
if parsed command requires it.

Returns:
    CMD_SUCCESS on success
    CMD_ERR if command is invalid
    CMD_EXIT if command is "exit"
    CMD_RESTART if command is "restart"
*/
int read_command(char* line, int** board, int** fixed, int** getSol) {
    char* cmd;
    int values[3]; /* Will conatin x, y, val in order */
    cmd = strtok(line, " \t\r\n");
    if (strcmp(cmd, "exit") == 0) {
        return CMD_EXIT;
    } else if (strcmp(cmd, "restart") == 0) {
        printf("restart");
        return CMD_RESTART;
    } else if (!is_full(board)) { /* We want to accept any other commands only if the game isn't finished */
        if (strcmp(cmd, "set") == 0) {
            if (load_ints(values, 3, cmd) == CMD_ERR) {
                return CMD_ERR;
            }
            if (set(board, fixed, values[0]-1, values[1]-1, values[2])) {
                print_board(board, fixed);
            }
        } else if (strcmp(cmd, "hint") == 0) {
            if (load_ints(values, 2, cmd) == CMD_ERR) {
                return CMD_ERR;
            }
            hint(board, values[0]-1, values[1]-1);
        } else if (strcmp(cmd, "validate") == 0) {
            validate(board, getSol);
        } else {
            return CMD_ERR;
        }
    } else {
        return CMD_ERR;
    }
    return CMD_SUCCESS;
}