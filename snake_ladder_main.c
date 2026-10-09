#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "snake_ladder.h"

/* ------------------------------------------------------------------ */
int main(void)
{
    SnlGame game;
    char input[32];

    snl_init(&game);
    srand((unsigned int)time(NULL));

    printf("Snake and Ladder\n");
    printf("First player to reach square 100 wins.\n\n");

    while (1) {
        int player = game.current_player;
        int previous = game.positions[player];
        int roll;

        printf("Player %d is on square %d. Press Enter to roll: ",
               player + 1, previous);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\nGame ended.\n");
            return 0;
        }

        roll = snl_roll();
        game.positions[player] = snl_apply_move(previous, roll);
        printf("Player %d rolled %d and moved to square %d.\n",
               player + 1, roll, game.positions[player]);

        if (game.positions[player] == previous &&
            previous + roll > SNL_BOARD_SIZE)
            printf("An exact roll is needed to reach square 100.\n");
        else if (game.positions[player] < previous + roll)
            printf("A snake sent Player %d down!\n", player + 1);
        else if (game.positions[player] > previous + roll)
            printf("A ladder moved Player %d up!\n", player + 1);

        if (snl_is_winner(game.positions[player])) {
            printf("Player %d wins!\n", player + 1);
            return 0;
        }

        game.current_player = (player + 1) % SNL_PLAYER_COUNT;
    }
}
