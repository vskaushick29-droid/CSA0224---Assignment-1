# Task 08 – Trace the Compilation Process

## Assignment
Design, Implement and Validate a Reliable Billing Program for a Rural Electricity Co-operative.

## Objective
Trace the C billing program through preprocessing, compilation, assembly, linking and execution; classify compile-time, link-time and run-time errors; and interpret GCC warnings.

## Source Program
`task08_billing.c` demonstrates the Grama Jyothi billing rules relevant to the assignment, including 16-bit meter rollover, slab charging and paise-based money storage.

## Compilation stages
| Stage | Command | Main output | Purpose |
|---|---|---|---|
| Preprocessing | `gcc -E task08_billing.c -o task08_billing.i` | `.i` | Expands headers/macros and removes comments/directives |
| Compilation | `gcc -S task08_billing.c -o task08_billing.s` | `.s` | Converts C into target assembly |
| Assembly | `gcc -c task08_billing.c -o task08_billing.o` | `.o` | Produces machine-code object file |
| Linking | `gcc task08_billing.o -o task08_billing` | executable | Resolves symbols and combines object/library code |

## What the preprocessor changed
- `#include <stdio.h>` was replaced by the contents needed from the standard header and its included declarations.
- `#define` tariff constants were substituted with their literal values during preprocessing.
- Preprocessor directives do not remain as executable C statements.
- Comments are removed from the preprocessed output.

See `preprocessor_evidence.txt` and `task08_billing.i` for evidence.

## Error classification
1. **Compile-time error:** `compile_error.c` has an invalid/missing syntax element. GCC rejects it before an executable is produced. Evidence: `compile_time_error.txt`.
2. **Link-time error:** `link_error.c` calls `missing_function()`, which has no definition. Compilation succeeds to an object, but the linker cannot resolve the symbol. Evidence: `link_time_error.txt`.
3. **Run-time error:** `runtime_error.c` performs integer division by zero. The program compiles and links, but fails during execution. Evidence: `runtime_error.txt`.

These examples are intentionally isolated from the main billing program so the working billing executable remains correct.

## GCC warnings
The billing source was checked with:
`gcc -Wall -Wextra -c task08_billing.c -o task08_billing_wall.o`

`warnings.txt` records the result. A clean result means no `-Wall`/`-Wextra` warnings were emitted for this source. The correct response to warnings is to inspect the referenced line and either fix the defect or justify the warning; warnings should not simply be suppressed.

## Verified output
The program tests a rollover reading from 65400 to 120. Unsigned 16-bit modular arithmetic gives 256 units. The bill is Rs 302.00 under the assignment tariff (Rs 50 fixed + Rs 202 energy).

See `run_output.txt`.

## Alternative: multiple source files
If the program is split into `input.c`, `tariff.c`, `report.c` and a shared `billing.h`, each `.c` file can be compiled separately:
- `gcc -c input.c -o input.o`
- `gcc -c tariff.c -o tariff.o`
- `gcc -c report.c -o report.o`
- `gcc input.o tariff.o report.o -o billing`

With a one-file design, changing one part normally requires recompiling the whole translation unit. With separate files, changing only `tariff.c` requires recompiling `tariff.c` and then relinking; unchanged object files can be reused. This can reduce incremental build time for larger projects.

Object-file storage is approximately the sum of the individual `.o` files plus the final executable's linked dependencies. Splitting into files can therefore increase intermediate disk usage, although only required objects are rebuilt.

### Complexity comparison
For `k` source files, if each file has approximately `n` lines:
- Monolithic rebuild after a local change: approximately `O(kn)` compilation work.
- Separate-file rebuild after changing one file: approximately `O(n)` compilation work for that file, plus linking.
- Initial full build still compiles all `k` files and links them.

## Files included
- `task08_billing.c` – working source
- `task08_billing.i` – preprocessed output
- `task08_billing.s` – assembly output
- `task08_billing.o` – object file
- `task08_billing` – linked executable
- `run_output.txt` – verified execution
- `warnings.txt` – GCC `-Wall -Wextra` result
- `preprocessor_evidence.txt` – macro-expansion evidence
- `compile_error.c` / `compile_time_error.txt`
- `link_error.c` / `link_time_error.txt`
- `runtime_error.c` / `runtime_error.txt`
- `commands.txt` – exact build commands
