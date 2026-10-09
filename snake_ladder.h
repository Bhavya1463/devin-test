#ifndef SNAKE_LADDER_H
#define SNAKE_LADDER_H

#define SNL_BOARD_SIZE 100
#define SNL_PLAYER_COUNT 2

typedef struct {
    int positions[SNL_PLAYER_COUNT];
    int current_player;
} SnlGame;

/* Initialise both players off the board at square zero. */
void snl_init(SnlGame *game);

/* Return a random dice value from 1 through 6. */
int snl_roll(void);

/* Move from position by roll, applying any snake or ladder.
   A roll beyond square 100 leaves the position unchanged. */
int snl_apply_move(int position, int roll);

/* Return non-zero when position is the winning square. */
int snl_is_winner(int position);

#endif /* SNAKE_LADDER_H */
