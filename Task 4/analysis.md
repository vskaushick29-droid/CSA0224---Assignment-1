# Task 04: Use Macros Safely

## Objective
Understand how the C preprocessor expands macros, identify common macro errors, and decide when a function or `static inline` function is safer.

## 1. Preprocessing
The C preprocessor handles directives such as `#include` and `#define` before normal compilation. Use:
```bash
gcc -E task04.c -o task04_preprocessed.i
```
The `.i` file shows the preprocessed translation unit. It can be large because included header contents are expanded too. Search in it for `main`, `SQUARE`, or the expanded expressions.

## 2. Operator precedence: `SQUARE`
Unsafe definition:
```c
#define SQUARE(x) x * x
```
For `SQUARE(1 + 2)`, substitution produces:
```c
1 + 2 * 1 + 2
```
Multiplication happens before addition, so the result is 5, not 9.

Safer definition:
```c
#define SQUARE_SAFE(x) ((x) * (x))
```
The argument and the whole replacement expression are parenthesized. `SQUARE_SAFE(1 + 2)` evaluates to 9.

## 3. Repeated evaluation: `MAX`
Example:
```c
#define MAX_UNSAFE(a, b) ((a) > (b) ? (a) : (b))
```
Calling `MAX_UNSAFE(i++, 4)` may evaluate `i++` more than once because the argument appears more than once in the replacement text. With `i` initially 5, the comparison evaluates `i++`, then the selected expression may evaluate it again. This changes `i` unexpectedly.

Parentheses do not solve repeated evaluation:
```c
#define MAX_SAFE(a, b) (((a) > (b)) ? (a) : (b))
```
This version has safer precedence but still may evaluate an argument multiple times. Do not pass expressions with side effects (such as `i++`) to this macro.

Prefer a function:
```c
static int max_function(int a, int b)
{
    return (a > b) ? a : b;
}
```
Function arguments are evaluated before entry; each parameter is initialized from its corresponding argument expression once. (The relative evaluation order of separate function arguments is unspecified in C, so avoid multiple side effects across arguments.)

## 4. When is a function better?
Prefer a function when:
- arguments may have side effects;
- type checking and debugging are important;
- the operation is more complex than a simple textual substitution;
- the expression must be evaluated exactly once.

A `static inline` function has normal function semantics and gives the compiler an opportunity to inline it. The `inline` keyword is a request/optimization hint, not a guarantee that the compiler will inline it.

## 5. Macro versus function code size
For a macro used at `k` call sites, the replacement expression is expanded at each site. A large macro can therefore duplicate generated instructions and increase code size. A normal function generally has one body plus call instructions. A `static inline` function may be expanded at call sites or emitted as a callable function depending on compiler decisions and optimization settings.

There is no universal fixed code-size result. It depends on the compiler, optimization flags, target architecture, and the function body. A fair experiment should compile the same program with and without optimization and inspect object/executable sizes or assembly.

## 6. Complexity
The demonstrated square and maximum operations each perform a fixed number of operations: O(1) time and O(1) auxiliary space. Macro expansion occurs during preprocessing; its source expansion cost depends on the amount of replacement text and number of uses.

## 7. Conclusion
Macros are useful for symbolic constants and conditional compilation, but function-like macros are textual substitutions and can cause precedence and repeated-evaluation bugs. Parenthesize macro parameters and the whole expression, avoid side effects in macro arguments, and prefer ordinary or `static inline` functions when safer function semantics are needed.
