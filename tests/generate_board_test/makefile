CC = gcc
EXEC = generate_board_test
COMP_FLAG = -ansi -Wall -Wextra -pedantic-errors

generate_board_test:
	$(CC) $(COMP_FLAG) main_aux.c solver.c game.c generate_board_test.c -o $(EXEC)

clean:
	rm -f $(EXEC)
