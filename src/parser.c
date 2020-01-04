#include "parser.h"

/* function load_ints
A support function for read_command.
Loads the first <count> integers from input into <target>.
We assume that we already recieved a valid command.
returns CMD_ERR if not enough integers were provided. otherwise returns CMD_SUCCESS
*/
int load_ints(int* target, int count) {
    int iter;
    char* tmp;
    for (iter = 0; iter < count; iter++) {
        tmp = strtok(NULL, " \t\r\n");
        if (tmp == NULL) {
            return CMD_ERR;
        }
        target[iter] = atoi(tmp);
    }
    return CMD_SUCCESS;
}

/* function parser
Recieves a line from the main function and parses it.
Also requires the game-board, the fixed-board and a pointer to receive a solution
if parsed command requires it.

Returns:
    CMD_SUCCESS on success
    CMD_ERR if command is invalid
    CMD_EXIT if command is "exit"
    CMD_RESTART if command is "restart"
*/
int read_command(char* line, int** board, int** fixed, int** solution) {
    char* cmd;
    int ret;
    int values[3]; /* Will conatin x, y, val in order */
    cmd = strtok(line, " \t\r\n");
    if (cmd == NULL) {
        return CMD_SUCCESS;
    }
    /* test for every valid command */
    if (strcmp(cmd, "exit") == 0) {
        return CMD_EXIT;
    } else if (strcmp(cmd, "restart") == 0) {
        return CMD_RESTART;
    } else if (is_full(board) == 0) { /* We want to accept any other commands only if the game isn't finished */
        if (strcmp(cmd, "set") == 0) {
            if (load_ints(values, 3) == CMD_ERR) {
                return CMD_ERR;
            }
            ret = set(board, fixed, values[0]-1, values[1]-1, values[2]);
            if (ret == LEGAL_MOVE) {
                print_board(board, fixed);
                if (is_full(board)) {
                    printf("Puzzle solved successfully\n");
                }
            } else if (ret == INVALID_VALUE) {
                printf("Error: value is invalid\n");
            } else {
                printf("Error: cell is fixed\n");
            }
        } else if (strcmp(cmd, "hint") == 0) {
            if (load_ints(values, 2) == CMD_ERR) {
                return CMD_ERR;
            }
            printf("Hint: set cell to %d\n", hint(solution, values[0]-1, values[1]-1));
        } else if (strcmp(cmd, "validate") == 0) {
            if (validate(board, solution)) {
                printf("Validation passed: board is solvable\n");
            } else {
                printf("Validation failed: board is unsolvable\n");
            }
        } else {
            return CMD_ERR;
        }
    } else {
        return CMD_ERR;
    }
    return CMD_SUCCESS;
}