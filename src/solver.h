int** new_board(int width, int height);
void copy_board(int** out_board, int** in_board, int width, int height);
int** solve_deterministic(int** game_board, int width, int height);
int advance_position(int* next_i, int* next_j, int i, int j, int width, int height)
