#ifndef GAME_H
#define GAME_H

#define BOARD_SIZE 9
#define EMPTY ' '
#define PLAYER_X 'X'
#define PLAYER_O 'O'

typedef enum {
    RESULT_NONE,
    RESULT_WIN_X,
    RESULT_WIN_O,
    RESULT_DRAW
} GameResult;

typedef enum {
    MOVE_OK,
    MOVE_OUT_OF_RANGE,
    MOVE_OCCUPIED
} MoveStatus;

/* Initialise every cell to EMPTY. */
void game_init(char board[BOARD_SIZE]);

/* Try to place `player` at `index` (0-8).
   Returns MOVE_OK on success or an error code. */
MoveStatus game_make_move(char board[BOARD_SIZE], int index, char player);

/* Check the board state and return the current result. */
GameResult game_check_result(const char board[BOARD_SIZE]);

/* Return the index (0-8) chosen by the AI for `player`. 
   Returns -1 if the board is full (should not happen in normal play). */
int game_ai_move(const char board[BOARD_SIZE], char player);

#endif /* GAME_H */
