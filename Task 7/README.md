# Task 07 – Type Conversion and Precision

## Included files
- `task07.c` – conversion, expression, rounding, and precision experiments
- `analysis.md` – explanations, observations, complexity, and recommendations
- `run_output.txt` – program output
- `compile.log` – compiler command and result
- `output.png` – terminal-style output capture

## Compile (GCC / MSYS2 UCRT64)
```bash
gcc -std=c11 -Wall -Wextra -Wpedantic task07.c -lm -o task07.exe
```

## Run
```bash
./task07.exe
```

The `-lm` option links the math library for `llround()` on GCC toolchains that require it.

## Important note
Converting a value outside the range of `int` to `int` is implementation-defined in C. Do not assume a particular wraparound result. The program labels this case accordingly.
