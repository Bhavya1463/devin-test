#include <stdio.h>
#include <string.h>
#include "game.h"

/* ------------------------------------------------------------------ */
/*  Minimal test harness                                              */
/* ------------------------------------------------------------------ */

static int tests_run    = 0;
static int tests_passed = 0;

#define TEST(name) static void name(void)
#define RUN(name)  do {                                 \
        tests_run++;                                    \
        printf("  %-50s ", #name);                      \
        name();                                         \
        tests_passed++;                                 \
        printf("[PASS]\n");                             \
    } while (0)

#define ASSERT(cond) do {                               \
        if (!(cond)) {                                  \
            printf("[FAIL]  %s:%d: %s\n",               \
                   __FILE__, __LINE__, #cond);          \
            return;                                     \
        }                                               \
    } while (0)

/* ------------------------------------------------------------------ */
/*  Tests: board initialisation                                       */
/* ------------------------------------------------------------------ */

TEST(test_init_board_all_empty)
{
    char board[BOARD_SIZE];
    game_init(board);
    for (int i = 0; i < BOARD_SIZE; i++)
        ASSERT(board[i] == EMPTY);
}

/* ------------------------------------------------------------------ */
/*  Tests: move validation                                            */
/* ------------------------------------------------------------------ */

TEST(test_valid_move)
{
    char board[BOARD_SIZE];
    game_init(board);
    ASSERT(game_make_move(board, 0, PLAYER_X) == MOVE_OK);
    ASSERT(board[0] == PLAYER_X);
}

TEST(test_move_out_of_range_negative)
{
    char board[BOARD_SIZE];
    game_init(board);
    ASSERT(game_make_move(board, -1, PLAYER_X) == MOVE_OUT_OF_RANGE);
}

TEST(test_move_out_of_range_high)
{
    char board[BOARD_SIZE];
    game_init(board);
    ASSERT(game_make_move(board, 9, PLAYER_X) == MOVE_OUT_OF_RANGE);
}

TEST(test_move_occupied)
{
    char board[BOARD_SIZE];
    game_init(board);
    game_make_move(board, 4, PLAYER_X);
    ASSERT(game_make_move(board, 4, PLAYER_O) == MOVE_OCCUPIED);
}

/* ------------------------------------------------------------------ */
/*  Tests: win detection                                              */
/* ------------------------------------------------------------------ */

TEST(test_x_wins_row)
{
    char board[BOARD_SIZE];
    game_init(board);
    board[0] = PLAYER_X; board[1] = PLAYER_X; board[2] = PLAYER_X;
    ASSERT(game_check_result(board) == RESULT_WIN_X);
}

TEST(test_o_wins_column)
{
    char board[BOARD_SIZE];
    game_init(board);
    board[1] = PLAYER_O; board[4] = PLAYER_O; board[7] = PLAYER_O;
    ASSERT(game_check_result(board) == RESULT_WIN_O);
}

TEST(test_x_wins_diagonal)
{
    char board[BOARD_SIZE];
    game_init(board);
    board[0] = PLAYER_X; board[4] = PLAYER_X; board[8] = PLAYER_X;
    ASSERT(game_check_result(board) == RESULT_WIN_X);
}

TEST(test_o_wins_anti_diagonal)
{
    char board[BOARD_SIZE];
    game_init(board);
    board[2] = PLAYER_O; board[4] = PLAYER_O; board[6] = PLAYER_O;
    ASSERT(game_check_result(board) == RESULT_WIN_O);
}

/* ------------------------------------------------------------------ */
/*  Tests: draw detection                                             */
/* ------------------------------------------------------------------ */

TEST(test_draw)
{
    char board[BOARD_SIZE];
    /* Classic draw layout:
       X O X
       X X O
       O X O  */
    board[0] = PLAYER_X; board[1] = PLAYER_O; board[2] = PLAYER_X;
    board[3] = PLAYER_X; board[4] = PLAYER_X; board[5] = PLAYER_O;
    board[6] = PLAYER_O; board[7] = PLAYER_X; board[8] = PLAYER_O;
    ASSERT(game_check_result(board) == RESULT_DRAW);
}

TEST(test_no_result_yet)
{
    char board[BOARD_SIZE];
    game_init(board);
    board[0] = PLAYER_X;
    ASSERT(game_check_result(board) == RESULT_NONE);
}

/* ------------------------------------------------------------------ */
/*  Tests: AI behaviour                                               */
/* ------------------------------------------------------------------ */

TEST(test_ai_takes_winning_move)
{
    char board[BOARD_SIZE];
    game_init(board);
    /* O has cells 0 and 1 -- should take 2 to win. */
    board[0] = PLAYER_O; board[1] = PLAYER_O;
    int move = game_ai_move(board, PLAYER_O);
    ASSERT(move == 2);
}

TEST(test_ai_blocks_opponent)
{
    char board[BOARD_SIZE];
    game_init(board);
    /* X has cells 3 and 6; O should block at 0. */
    board[3] = PLAYER_X; board[6] = PLAYER_X;
    int move = game_ai_move(board, PLAYER_O);
    ASSERT(move == 0);
}

TEST(test_ai_takes_center)
{
    char board[BOARD_SIZE];
    game_init(board);
    board[0] = PLAYER_X; /* only one piece, center open */
    int move = game_ai_move(board, PLAYER_O);
    ASSERT(move == 4);
}

TEST(test_ai_returns_valid_index)
{
    char board[BOARD_SIZE];
    game_init(board);
    int move = game_ai_move(board, PLAYER_O);
    ASSERT(move >= 0 && move < BOARD_SIZE);
    ASSERT(board[move] == EMPTY);
}

TEST(test_ai_full_board)
{
    char board[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++)
        board[i] = PLAYER_X;
    int move = game_ai_move(board, PLAYER_O);
    ASSERT(move == -1);
}

/* ------------------------------------------------------------------ */
/*  Runner                                                            */
/* ------------------------------------------------------------------ */

int main(void)
{
    printf("Running game logic tests...\n");

    RUN(test_init_board_all_empty);

    RUN(test_valid_move);
    RUN(test_move_out_of_range_negative);
    RUN(test_move_out_of_range_high);
    RUN(test_move_occupied);

    RUN(test_x_wins_row);
    RUN(test_o_wins_column);
    RUN(test_x_wins_diagonal);
    RUN(test_o_wins_anti_diagonal);

    RUN(test_draw);
    RUN(test_no_result_yet);

    RUN(test_ai_takes_winning_move);
    RUN(test_ai_blocks_opponent);
    RUN(test_ai_takes_center);
    RUN(test_ai_returns_valid_index);
    RUN(test_ai_full_board);

    printf("\n%d / %d tests passed.\n", tests_passed, tests_run);
    return (tests_passed == tests_run) ? 0 : 1;
}
