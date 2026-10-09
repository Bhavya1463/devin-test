#include "game.h"
#include <stdlib.h>
#include <time.h>

/* ------------------------------------------------------------------ */
/*  Win-line table: each entry is a set of three indices.             */
/* ------------------------------------------------------------------ */
static const int WIN_LINES[8][3] = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8},   /* rows    */
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8},   /* columns */
    {0, 4, 8}, {2, 4, 6}               /* diags   */
};

/* ------------------------------------------------------------------ */
void game_init(char board[BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
        board[i] = EMPTY;
}

/* ------------------------------------------------------------------ */
MoveStatus game_make_move(char board[BOARD_SIZE], int index, char player)
{
    if (index < 0 || index >= BOARD_SIZE)
        return MOVE_OUT_OF_RANGE;
    if (board[index] != EMPTY)
        return MOVE_OCCUPIED;
    board[index] = player;
    return MOVE_OK;
}

/* ------------------------------------------------------------------ */
GameResult game_check_result(const char board[BOARD_SIZE])
{
    for (int i = 0; i < 8; i++) {
        char a = board[WIN_LINES[i][0]];
        char b = board[WIN_LINES[i][1]];
        char c = board[WIN_LINES[i][2]];
        if (a != EMPTY && a == b && b == c) {
            return (a == PLAYER_X) ? RESULT_WIN_X : RESULT_WIN_O;
        }
    }
    /* Check for draw (no empty cells). */
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i] == EMPTY)
            return RESULT_NONE;
    }
    return RESULT_DRAW;
}

/* ------------------------------------------------------------------ */
/*  Simple AI: try to win, then block, then take center, then random. */
/* ------------------------------------------------------------------ */

/* Return the index that completes a line for `player`, or -1. */
static int find_winning_move(const char board[BOARD_SIZE], char player)
{
    for (int i = 0; i < 8; i++) {
        int idx[3] = {WIN_LINES[i][0], WIN_LINES[i][1], WIN_LINES[i][2]};
        int count = 0;
        int empty_idx = -1;
        for (int j = 0; j < 3; j++) {
            if (board[idx[j]] == player)
                count++;
            else if (board[idx[j]] == EMPTY)
                empty_idx = idx[j];
        }
        if (count == 2 && empty_idx != -1)
            return empty_idx;
    }
    return -1;
}

static char opponent(char player)
{
    return (player == PLAYER_X) ? PLAYER_O : PLAYER_X;
}

int game_ai_move(const char board[BOARD_SIZE], char player)
{
    /* 1. Win if possible. */
    int move = find_winning_move(board, player);
    if (move != -1)
        return move;

    /* 2. Block opponent's winning move. */
    move = find_winning_move(board, opponent(player));
    if (move != -1)
        return move;

    /* 3. Take center. */
    if (board[4] == EMPTY)
        return 4;

    /* 4. Take a corner. */
    static const int corners[] = {0, 2, 6, 8};
    for (int i = 0; i < 4; i++) {
        if (board[corners[i]] == EMPTY)
            return corners[i];
    }

    /* 5. Take any remaining cell. */
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i] == EMPTY)
            return i;
    }

    return -1; /* board full */
}
