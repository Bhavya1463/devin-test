# KAN-9 Test Report – Snake and Ladder

- **Branch:** `devin/KAN-9-snake-and-ladder`
- **Commit under test:** `80c41f2 feat(KAN-9): add snake and ladder game`
- **Tester:** automated C build/test run
- **Report generated:** test-reports/KAN-9.md

## Commands Run

```bash
cd /home/girish/bhavya/devin/devin-test
git checkout devin/KAN-9-snake-and-ladder
make clean
make
make test
```

A separate strict-lint pass was also performed with the AGENTS.md-required flags:

```bash
gcc -std=c99 -Wall -Wextra -pedantic -c snake_ladder.c
gcc -std=c99 -Wall -Wextra -pedantic -c snake_ladder_main.c
gcc -std=c99 -Wall -Wextra -pedantic -c test_snake_ladder.c
```

## Results Summary

| Metric | Value |
|--------|-------|
| Build target `snake_ladder` | Built cleanly |
| Test binary `test_snake_ladder` | Built cleanly |
| Tests run | 6 |
| Tests passed | 6 |
| Tests failed | 0 |
| Pass rate | 100 % |
| Strict compilation warnings/errors | 0 |
| `make clean` removes artifacts | Yes |

Approximate wall-clock duration for `make clean && make && make test`: **~0.09 s**.

## Test Output

```text
rm -f *.o snake_ladder test_snake_ladder
gcc -std=c99 -Wall -Wextra -pedantic -c snake_ladder_main.c
gcc -std=c99 -Wall -Wextra -pedantic -c snake_ladder.c
gcc -std=c99 -Wall -Wextra -pedantic -o snake_ladder snake_ladder_main.o snake_ladder.o
gcc -std=c99 -Wall -Wextra -pedantic -c test_snake_ladder.c
gcc -std=c99 -Wall -Wextra -pedantic -o test_snake_ladder test_snake_ladder.o snake_ladder.o
./test_snake_ladder
Running Snake and Ladder logic tests...
  test_init                                          [PASS]
  test_dice_range                                    [PASS]
  test_ladder_jump                                   [PASS]
  test_snake_penalty                                 [PASS]
  test_exact_winning_landing                         [PASS]
  test_overshoot_stays_in_place                      [PASS]

6 / 6 tests passed.
```

## Acceptance Criteria Checklist

| # | Criterion | Status | Evidence |
|---|-----------|--------|----------|
| 1 | Simple Snake and Ladder C program exists under `devin-test/` | **Met** | `snake_ladder.c`, `snake_ladder.h`, `snake_ladder_main.c`, `test_snake_ladder.c` present |
| 2 | 100-square board | **Met** | `snake_ladder.h:4` defines `SNL_BOARD_SIZE 100`; `snl_is_winner` checks `position == 100`; overshoot logic uses `SNL_BOARD_SIZE` |
| 3 | Dice roll in range 1-6 | **Met** | `snake_ladder.c:28` implements `rand() % 6 + 1`; `test_dice_range` validates 1000 rolls are within `[1,6]` |
| 4 | Snakes move down and ladders move up | **Met** | `snake_ladder.c:8-13` defines `TRANSITIONS` with ladders (e.g., `1 -> 38`) and snakes (e.g., `16 -> 6`); `test_ladder_jump` and `test_snake_penalty` pass |
| 5 | First player to land exactly on 100 wins | **Met** | `snl_apply_move` returns position unchanged for overshoot > 100; `snl_is_winner` returns true only on `position == 100`; `snake_ladder_main.c` prints winner and exits on exact 100 |
| 6 | New Makefile target `make snake_ladder` | **Met** | `Makefile:8-9` defines `snake_ladder:` target; verified it builds the executable |
| 7 | Does not break `make` | **Met** | `make` default target builds `snake_ladder` cleanly |
| 8 | Does not break `make test` | **Met** | `make test` builds and runs `test_snake_ladder`, 6/6 pass |
| 9 | Does not break `make clean` | **Met** | `make clean` removes `*.o`, `snake_ladder`, `test_snake_ladder` without touching source files |
| 10 | Compiles clean under `gcc -std=c99 -Wall -Wextra -pedantic` | **Met** | Makefile already uses these flags; no warnings/errors emitted for any source file |
| 11 | Unit tests use TEST/RUN/ASSERT harness style | **Met** | `test_snake_ladder.c:13-32` defines `TEST`, `RUN`, and `ASSERT` macros and runs six test cases with them |

## New Tests Added / Missing Coverage

### Tests present in `test_snake_ladder.c`

1. `test_init` – verifies initial player positions and current player.
2. `test_dice_range` – rolls 1000 times and checks `1 <= roll <= 6`.
3. `test_ladder_jump` – verifies ladder move from square 1 to 38.
4. `test_snake_penalty` – verifies snake move from square 98 to 78.
5. `test_exact_winning_landing` – verifies exact roll to 100 and winner detection.
6. `test_overshoot_stays_in_place` – verifies overshoot beyond 100 leaves position unchanged.

### Coverage gaps (not blockers)

- No automated test for the interactive 2-player turn loop in `snake_ladder_main.c`.
- No explicit test for EOF / stdin handling branch in `snake_ladder_main.c`.
- Not every snake/ladder transition is individually asserted (only representative cases).
- No test verifying that a roll of `0` or negative values are impossible (function contract assumes `roll >= 1`).

## Verdict

**PASS**

All acceptance criteria are satisfied: the code builds cleanly with the required strict flags, the new `snake_ladder` Makefile target works, the existing `make` / `make test` / `make clean` targets remain functional, and the unit tests cover the core board, dice, snake, ladder, and winning rules.
