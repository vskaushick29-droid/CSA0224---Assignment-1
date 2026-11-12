# Task 06 – Input and Output in C

## Included files
- `task06.c` – checked input, billing output, and `fgets` + `strtol` parser example
- `billing.c`, `billing.h` – billing calculation used by the program
- `analysis.md` – format specifiers, validation, buffer size, complexity, and observations
- `valid_input_output.txt` – run using 150
- `invalid_input_output.txt` – run using abc
- `compile.log` – compiler commands and results
- `output.png` – terminal-style output capture

## Compile (GCC / MSYS2 UCRT64)
```bash
gcc -std=c11 -Wall -Wextra -Wpedantic task06.c billing.c -o task06.exe
```

## Run
```bash
./task06.exe
```
Enter `150` to test valid input. Enter `abc` to test invalid input.

## Important
The program checks the return value of `scanf`. It also demonstrates a line-based alternative using `fgets()` and `strtol()`.
