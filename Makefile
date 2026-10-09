CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -pedantic

.PHONY: all clean test

all: snake_ladder

snake_ladder: snake_ladder_main.o snake_ladder.o
	$(CC) $(CFLAGS) -o $@ $^

test_snake_ladder: test_snake_ladder.o snake_ladder.o
	$(CC) $(CFLAGS) -o $@ $^

snake_ladder_main.o: snake_ladder_main.c snake_ladder.h
	$(CC) $(CFLAGS) -c snake_ladder_main.c

snake_ladder.o: snake_ladder.c snake_ladder.h
	$(CC) $(CFLAGS) -c snake_ladder.c

test_snake_ladder.o: test_snake_ladder.c snake_ladder.h
	$(CC) $(CFLAGS) -c test_snake_ladder.c

test: test_snake_ladder
	./test_snake_ladder

clean:
	rm -f *.o snake_ladder test_snake_ladder
