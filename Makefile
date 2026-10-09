CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -pedantic
LDFLAGS = -lncurses

.PHONY: all clean test

all: tictactoe

tictactoe: main.o game.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test_game: test_game.o game.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c game.h
	$(CC) $(CFLAGS) -c main.c

game.o: game.c game.h
	$(CC) $(CFLAGS) -c game.c

test_game.o: test_game.c game.h
	$(CC) $(CFLAGS) -c test_game.c

test: test_game
	./test_game

clean:
	rm -f *.o tictactoe test_game
