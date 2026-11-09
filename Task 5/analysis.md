# Task 05 – Header Files and Conditional Compilation

## 1. Purpose
This task separates the billing program into multiple source files and demonstrates header files, include guards, and conditional compilation.

## 2. File organization
- `billing.h`: shared tariff constants and the `compute_bill()` function prototype.
- `billing.c`: implementation of `compute_bill()`.
- `main.c`: test inputs, function calls, and displayed results.

The header file contains declarations, while the `.c` file contains the function definition. This avoids duplicating the function implementation in every source file.

## 3. Include guards
`billing.h` uses:
```c
#ifndef BILLING_H
#define BILLING_H
/* declarations */
#endif
```
The first inclusion defines `BILLING_H`. If the same header is encountered again in the same translation unit, its contents are skipped. This prevents repeated declarations caused by multiple inclusion.

## 4. Conditional compilation with DEBUG
The statements inside `#ifdef DEBUG` are included only when the `DEBUG` macro is defined during preprocessing.

Compile normally:
```bash
gcc -std=c11 -Wall -Wextra main.c billing.c -o billing
```
Run:
```bash
./billing
```

Compile with debug messages:
```bash
gcc -std=c11 -Wall -Wextra -DDEBUG main.c billing.c -o billing_debug
```
Run:
```bash
./billing_debug
```

`-DDEBUG` defines the macro before preprocessing. Therefore, debug statements appear in the debug build but are removed from the normal build. This is compile-time selection, not a run-time check.

## 5. Angle brackets versus quotation marks
- `#include <stdio.h>`: normally searches the compiler's configured system-header locations.
- `#include "billing.h"`: normally searches the source file's local directory first, then configured include locations.

Exact search order can vary with compiler options and implementation.

## 6. Compile-time DEBUG versus run-time debug variable
`#ifdef DEBUG` decides whether debug code exists in the compiled program. A run-time variable such as `int debug = 1;` leaves the debug code in the executable and decides during execution whether to print messages.

Compile-time selection can reduce the normal executable's debug code and avoid run-time checks. A run-time variable is more flexible because the setting can change while the program runs, but the debug code remains compiled.

## 7. Complexity and memory
The billing calculation uses a fixed number of comparisons and arithmetic operations, so its time complexity is O(1) per bill. The test loop processes `n` cases, so total test execution is O(n). The program uses a fixed-size test array, so its auxiliary memory is O(1) with respect to the number of bills in this demonstration.

## 8. Validation
The normal build should print only bill results. The debug build should print additional messages showing program start, test count, each input, and program finish. Both builds should produce identical bill values.

## 9. Conclusion
Using a header file and separate implementation file improves organization and reuse. Include guards prevent repeated header inclusion, while `#ifdef DEBUG` allows diagnostic output to be included only in a debug build.
