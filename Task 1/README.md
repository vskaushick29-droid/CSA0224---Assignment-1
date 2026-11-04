# Task 01 – Submission files

- `analysis.md` – problem analysis, data dictionary, tariff rules, invariants, worked example and alternative-concept analysis.
- `task01.c` – C demonstration source.
- `output.png` – terminal-style capture based on the actual execution output in `run_output.txt`.
- `run_output.txt` – raw stdout from the compiled program.
- `memory_layout.png` – conceptual field-size diagram (not a compiler-specific struct-offset map).
- `compile.log` – compiler command and result.

Compile and run:

```sh
gcc -Wall -Wextra -Wpedantic -std=c11 -O2 -o task01 task01.c
./task01
```

The displayed `sizeof` values depend on the compiler and target platform. Recompile in the same environment used for submission and retain that environment's actual output.
