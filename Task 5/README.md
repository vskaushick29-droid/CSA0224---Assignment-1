# Task 05 – Header Files and Conditional Compilation

## Files
- `main.c` – test driver and optional debug messages
- `billing.c` – billing function implementation
- `billing.h` – tariff constants, prototype, and include guard
- `analysis.md` – explanations and observations
- `run_output.txt` – normal build output
- `debug_output.txt` – debug build output
- `compile.log` – compiler commands and results
- `output.png` – captured terminal output

## Compile and run (GCC / MSYS2 UCRT64)

Normal build:
```bash
gcc -std=c11 -Wall -Wextra main.c billing.c -o billing.exe
./billing.exe
```

Debug build:
```bash
gcc -std=c11 -Wall -Wextra -DDEBUG main.c billing.c -o billing_debug.exe
./billing_debug.exe
```

If using Windows Command Prompt, run `billing.exe` or `billing_debug.exe`.

## Expected billing values
- 0 units: Rs.50.00
- 100 units: Rs.50.00
- 150 units: Rs.162.50
- 200 units: Rs.275.00
- 350 units: Rs.950.00
- -5 units: Invalid consumption

The debug build adds diagnostic lines; the billing results remain the same.
