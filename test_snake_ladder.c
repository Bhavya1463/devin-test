#include <stdio.h>
#include <stdlib.h>

#include "snake_ladder.h"

/* ------------------------------------------------------------------ */
/*  Minimal test harness                                              */
/* ------------------------------------------------------------------ */
static int tests_run = 0;
static int tests_passed = 0;
static int current_test_passed = 1;

#define TEST(name) static void name(void)
#define RUN(name) do {                                  \
        tests_run++;                                    \
        current_test_passed = 1;                        \
        printf("  %-50s ", #name);                      \
        name();                                         \
        if (current_test_passed) {                      \
            tests_passed++;                             \
            printf("[PASS]\n");                         \
        }                                               \
    } while (0)

#define ASSERT(cond) do {                               \
        if (!(cond)) {                                  \
            printf("[FAIL]  %s:%d: %s\n",               \
                   __FILE__, __LINE__, #cond);          \
            current_test_passed = 0;                    \
            return;                                     \
        }                                               \
    } while (0)

/* ------------------------------------------------------------------ */
TEST(test_init)
{
    SnlGame game;

    snl_init(&game);
    ASSERT(game.positions[0] == 0);
    ASSERT(game.positions[1] == 0);
    ASSERT(game.current_player == 0);
}

TEST(test_dice_range)
{
    int i;

    srand(1);
    for (i = 0; i < 1000; i++) {
        int roll = snl_roll();
        ASSERT(roll >= 1 && roll <= 6);
    }
}

TEST(test_ladder_jump)
{
    ASSERT(snl_apply_move(0, 1) == 38);
}

TEST(test_snake_penalty)
{
    ASSERT(snl_apply_move(92, 6) == 78);
}

TEST(test_exact_winning_landing)
{
    ASSERT(snl_apply_move(94, 6) == 100);
    ASSERT(snl_is_winner(100));
}

TEST(test_overshoot_stays_in_place)
{
    ASSERT(snl_apply_move(97, 4) == 97);
    ASSERT(!snl_is_winner(97));
}

/* ------------------------------------------------------------------ */
int main(void)
{
    printf("Running Snake and Ladder logic tests...\n");

    RUN(test_init);
    RUN(test_dice_range);
    RUN(test_ladder_jump);
    RUN(test_snake_penalty);
    RUN(test_exact_winning_landing);
    RUN(test_overshoot_stays_in_place);

    printf("\n%d / %d tests passed.\n", tests_passed, tests_run);
    return (tests_passed == tests_run) ? 0 : 1;
}
