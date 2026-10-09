#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include "game.h"

/* ------------------------------------------------------------------ */
/*  Drawing helpers                                                   */
/* ------------------------------------------------------------------ */

static void draw_board(const char board[BOARD_SIZE])
{
    clear();
    mvprintw(0, 0, "=== Tic-Tac-Toe ===");
    mvprintw(1, 0, "You are X, Computer is O");
    mvprintw(2, 0, "Enter index 0-8 to move.");
    mvprintw(4, 0, " %c | %c | %c ", board[0], board[1], board[2]);
    mvprintw(5, 0, "---+---+---");
    mvprintw(6, 0, " %c | %c | %c ", board[3], board[4], board[5]);
    mvprintw(7, 0, "---+---+---");
    mvprintw(8, 0, " %c | %c | %c ", board[6], board[7], board[8]);

    /* Show index reference. */
    mvprintw(4, 16, "0 | 1 | 2");
    mvprintw(6, 16, "3 | 4 | 5");
    mvprintw(8, 16, "6 | 7 | 8");
}

static void show_message(const char *msg)
{
    mvprintw(10, 0, "                                        "); /* clear line */
    mvprintw(10, 0, "%s", msg);
}

/* ------------------------------------------------------------------ */
/*  Main game loop                                                    */
/* ------------------------------------------------------------------ */

int main(void)
{
    /* ncurses setup */
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(1);

    char board[BOARD_SIZE];
    game_init(board);

    GameResult result = RESULT_NONE;

    while (result == RESULT_NONE) {
        draw_board(board);
        show_message("Your move (0-8): ");
        refresh();

        /* Read a single character for the move. */
        int ch = getch();
        if (ch == 'q' || ch == 'Q') {
            break; /* quit */
        }

        if (!isdigit(ch)) {
            show_message("Invalid input. Enter a digit 0-8.");
            refresh();
            napms(800);
            continue;
        }

        int index = ch - '0';
        MoveStatus status = game_make_move(board, index, PLAYER_X);
        if (status == MOVE_OUT_OF_RANGE) {
            show_message("Out of range! Enter 0-8.");
            refresh();
            napms(800);
            continue;
        }
        if (status == MOVE_OCCUPIED) {
            show_message("Cell already occupied!");
            refresh();
            napms(800);
            continue;
        }

        result = game_check_result(board);
        if (result != RESULT_NONE)
            break;

        /* Computer turn */
        int ai = game_ai_move(board, PLAYER_O);
        if (ai >= 0)
            game_make_move(board, ai, PLAYER_O);

        result = game_check_result(board);
    }

    /* Final screen */
    draw_board(board);
    switch (result) {
        case RESULT_WIN_X: show_message("You win! Press any key to exit."); break;
        case RESULT_WIN_O: show_message("Computer wins! Press any key to exit."); break;
        case RESULT_DRAW:  show_message("It's a draw! Press any key to exit."); break;
        default:           show_message("Goodbye! Press any key to exit."); break;
    }
    refresh();
    getch();

    endwin();
    return 0;
}
