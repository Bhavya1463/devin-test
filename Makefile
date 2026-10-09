CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -pedantic
LDFLAGS = -lncurses

.PHONY: all clean test

all: tictactoe

tictactoe: main.o game.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test_game: test_game.o game.o
	$(CC) $(CFLAGS) -o $@ $^

test_linked_list_bin: test_linked_list.o linked_list.o
	$(CC) $(CFLAGS) -o test_linked_list $^

main.o: main.c game.h
	$(CC) $(CFLAGS) -c main.c

game.o: game.c game.h
	$(CC) $(CFLAGS) -c game.c

linked_list.o: linked_list.c linked_list.h
	$(CC) $(CFLAGS) -c linked_list.c

test_game.o: test_game.c game.h
	$(CC) $(CFLAGS) -c test_game.c

test_linked_list.o: test_linked_list.c linked_list.h
	$(CC) $(CFLAGS) -c test_linked_list.c

test: test_game
	./test_game

test_linked_list: test_linked_list_bin
	./test_linked_list

clean:
	rm -f *.o tictactoe test_game test_linked_list
