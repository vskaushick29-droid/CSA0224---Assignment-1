/*
 * Task 04: Use Macros Safely
 * Demonstrates macro precedence, repeated evaluation, preprocessing,
 * and comparison with functions/static inline functions.
 */
#include <stdio.h>

/* Intentionally unsafe examples for demonstration. */
#define SQUARE(x) x * x
#define MAX_UNSAFE(a, b) ((a) > (b) ? (a) : (b))

/* Safer macro: parenthesize the whole expression and each argument. */
#define SQUARE_SAFE(x) ((x) * (x))
#define MAX_SAFE(a, b) (((a) > (b)) ? (a) : (b))

/* Functions evaluate each argument once. */
static int square_function(int x)
{
    return x * x;
}

static inline int square_inline(int x)
{
    return x * x;
}

static int max_function(int a, int b)
{
    return (a > b) ? a : b;
}

int main(void)
{
    int i;
    int a;
    int b;

    puts("==================================================");
    puts(" TASK 04: USING MACROS SAFELY");
    puts("==================================================");

    puts("\n[1] SQUARE MACRO PRECEDENCE");
    printf("SQUARE(1 + 2)      = %d  (unexpected: expansion lacks parentheses)\n",
           SQUARE(1 + 2));
    printf("SQUARE_SAFE(1 + 2) = %d  (expected: 9)\n",
           SQUARE_SAFE(1 + 2));
    printf("square_function(3) = %d\n", square_function(3));
    printf("square_inline(3)   = %d\n", square_inline(3));

    puts("\n[2] DOUBLE EVALUATION IN A MACRO");
    i = 5;
    a = MAX_UNSAFE(i++, 4);
    printf("MAX_UNSAFE(i++, 4) result = %d, i after call = %d\n", a, i);
    puts("The selected argument can be evaluated more than once.");

    i = 5;
    a = max_function(i++, 4);
    printf("max_function(i++, 4) result = %d, i after call = %d\n", a, i);
    puts("The function evaluates the argument expression once.");

    puts("\n[3] MACRO ARGUMENT SIDE-EFFECT WARNING");
    i = 5;
    b = MAX_SAFE(i++, 4);
    printf("MAX_SAFE(i++, 4) result = %d, i after call = %d\n", b, i);
    puts("Parentheses fix precedence, but do NOT prevent repeated evaluation.");
    puts("Avoid side effects in arguments to function-like macros.");

    puts("\n[4] WHEN TO USE WHICH");
    puts("- Use #define for simple symbolic constants and conditional compilation.");
    puts("- Prefer a function when arguments may have side effects or type checking matters.");
    puts("- static inline functions provide function semantics and may be optimized inline.");

    puts("\n[5] CODE-SIZE / USAGE COMPARISON");
    puts("A macro body is substituted at each of k call sites; this can increase");
    puts("generated code size when the expression is large.");
    puts("A normal function has one function body plus calls; static inline may");
    puts("be inlined by the compiler, so actual size depends on optimization.");
    puts("No fixed byte count is portable; inspect compiler output for a given build.");

    puts("==================================================");
    return 0;
}
