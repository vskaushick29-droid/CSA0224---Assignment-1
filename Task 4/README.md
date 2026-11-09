# Task 04 – Use Macros Safely

## Files
- `task04.c` – demonstrations of macro precedence, repeated evaluation, and functions.
- `analysis.md` – explanation and comparison.
- `run_output.txt` – actual program output.
- `compile.log` – compiler command and diagnostics.
- `task04_preprocessed.i` – output of GCC preprocessing (`gcc -E`).

## Compile and run
```bash
gcc -Wall -Wextra -std=c11 task04.c -o task04
./task04
```

## Inspect preprocessing
```bash
gcc -E task04.c -o task04_preprocessed.i
```
The preprocessed file can be large because it contains expanded standard headers.

## Notes
The program intentionally includes unsafe macro examples to demonstrate why they are unsafe. Do not use those definitions in production billing code. `SQUARE_SAFE` fixes precedence but a macro can still evaluate an argument more than once.
