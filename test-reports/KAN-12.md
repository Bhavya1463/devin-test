# KAN-12 Test Report

## Branch
`devin/KAN-12-swap-numbers` in `/home/girish/bhavya/devin/devin-test`

## Tests Run

1. **Branch check** — `devin/KAN-12-swap-numbers` is checked out.
2. **Compile** —
   ```bash
   gcc -std=c99 -Wall -Wextra -pedantic -o /tmp/swap_numbers swap_numbers.c
   ```
   Result: exit code 0, zero warnings/errors.
3. **Run** —
   ```bash
   /tmp/swap_numbers
   ```
   Output:
   ```text
   Before swap: a = 42, b = 17
   After swap:  a = 17, b = 42
   ```
   Result: values correctly swapped, exit code 0.
4. **Scope check** — `git diff origin/main...HEAD` adds only:
   - `swap_numbers.c`
   - `test-reports/KAN-12.md`
   No existing tracked files were modified.
5. **`make test`** — No `Makefile` or `test` target exists; `make test` fails with `No rule to make target 'test'`. This is expected for this standalone C program.

## Untracked Workspace Artifacts Noted
- `devin-python-test/`
- `string_reverse`
- `swap_numbers` (binary)
- `test_linked_list`

These are pre-existing untracked artifacts and were not modified by this task.

## Summary
- Compile: **PASS**
- Runtime/output: **PASS**
- Exit code: **PASS**
- Scope/change-set: **PASS**
- `make test`: **N/A** (no test target configured)

VERDICT: PASS
