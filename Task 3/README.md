# Task 03 – Define Constants

## Files
- `task03.c` – C source code implementing the tariff macros and `compute_bill()`.
- `analysis.md` – explanation of `#define`, `const`, `enum`, slab calculations and tests.
- `run_output.txt` – output from the original tariff build.
- `compile.log` – compiler output.
- `output.png` – terminal-style output image.

## Compile and run (GCC)
```bash
gcc -Wall -Wextra -std=c11 Task03/task03.c -o Task03/task03
./Task03/task03
```
If already inside the `Task03` directory:
```bash
gcc -Wall -Wextra -std=c11 task03.c -o task03
./task03
```

## Tariff revision experiment
Change `RATE2_PAISE` from `225` to `230` in `task03.c`, compile again, and rerun. The expected revised totals are listed in `analysis.md`.

The included output is for the original tariff (225 paise). Re-run on your own college/Windows compiler and save that actual output as submission evidence.

## Verified tariff revision
The separate `task03_rate_revision.c` changes `RATE2_PAISE` to 230. It was compiled independently with GCC and executed. See `tariff_revision_output.txt` for the actual output.
