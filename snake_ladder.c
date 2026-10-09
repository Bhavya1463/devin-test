#include "snake_ladder.h"

#include <stdlib.h>

/* ------------------------------------------------------------------ */
/*  Board transitions: positive values are destination squares.       */
/* ------------------------------------------------------------------ */
static const int TRANSITIONS[SNL_BOARD_SIZE + 1] = {
    [1] = 38, [4] = 14, [9] = 31, [21] = 42, [28] = 84,
    [36] = 44, [51] = 67, [71] = 91, [80] = 100,
    [16] = 6, [47] = 26, [49] = 11, [56] = 53, [62] = 19,
    [64] = 60, [87] = 24, [93] = 73, [95] = 75, [98] = 78
};

/* ------------------------------------------------------------------ */
void snl_init(SnlGame *game)
{
    int player;

    for (player = 0; player < SNL_PLAYER_COUNT; player++)
        game->positions[player] = 0;
    game->current_player = 0;
}

/* ------------------------------------------------------------------ */
int snl_roll(void)
{
    return rand() % 6 + 1;
}

/* ------------------------------------------------------------------ */
int snl_apply_move(int position, int roll)
{
    int destination = position + roll;

    if (destination > SNL_BOARD_SIZE)
        return position;
    if (TRANSITIONS[destination] != 0)
        return TRANSITIONS[destination];
    return destination;
}

/* ------------------------------------------------------------------ */
int snl_is_winner(int position)
{
    return position == SNL_BOARD_SIZE;
}
