/*
 * Task 02: Choosing Data Types and Handling Meter Rollover
 * Compile: gcc -Wall -Wextra -std=c11 Task02/task02.c -o Task02/task02
 */
#include <float.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

/* A 16-bit unsigned type matches the meter's 0..65535 register. */
typedef uint16_t meter_t;

/*
 * Unsigned 16-bit arithmetic wraps modulo 65536.
 * The cast makes the intended modulo-2^16 result explicit.
 * No if-else is required.
 */
static meter_t consumption(meter_t previous, meter_t current)
{
    return (meter_t)(current - previous);
}

int main(void)
{
    const meter_t previous_normal = 1200;
    const meter_t current_normal = 1530;
    const meter_t previous_rollover = 65400;
    const meter_t current_rollover = 120;

    printf("TASK 02: DATA TYPES, LIMITS AND METER ROLLOVER\n");
    printf("==============================================\n");
    printf("Compiler: C11-compatible GCC\n\n");

    printf("[1] TYPE SIZES ON THIS SYSTEM\n");
    printf("sizeof(char)       = %zu byte(s)\n", sizeof(char));
    printf("sizeof(short)      = %zu byte(s)\n", sizeof(short));
    printf("sizeof(int)        = %zu byte(s)\n", sizeof(int));
    printf("sizeof(long)       = %zu byte(s)\n", sizeof(long));
    printf("sizeof(long long)  = %zu byte(s)\n", sizeof(long long));
    printf("sizeof(float)      = %zu byte(s)\n", sizeof(float));
    printf("sizeof(double)     = %zu byte(s)\n", sizeof(double));
    printf("sizeof(meter_t)    = %zu byte(s)\n", sizeof(meter_t));
    printf("UINT16_MAX         = %u\n", (unsigned)UINT16_MAX);
    printf("INT_MAX            = %d\n", INT_MAX);
    printf("LLONG_MAX          = %lld\n", LLONG_MAX);
    printf("FLT_DIG            = %d decimal digits of precision\n", FLT_DIG);
    printf("DBL_DIG            = %d decimal digits of precision\n\n", DBL_DIG);

    printf("[2] METER CONSUMPTION TESTS\n");
    printf("Normal:   %u -> %u = %u units\n",
           (unsigned)previous_normal, (unsigned)current_normal,
           (unsigned)consumption(previous_normal, current_normal));
    printf("Rollover: %u -> %u = %u units\n",
           (unsigned)previous_rollover, (unsigned)current_rollover,
           (unsigned)consumption(previous_rollover, current_rollover));
    printf("Expected rollover result: (65536 - 65400) + 120 = 256 units\n\n");

    printf("[3] FLOATING-POINT ACCUMULATION VS INTEGER PAISE\n");
    {
        float float_total_rupees = 0.0f;
        int64_t exact_total_paise = 0;
        int i;
        for (i = 0; i < 4000; ++i) {
            /* Demonstration: repeatedly add one paise expressed as rupees. */
            float_total_rupees += 0.01f;
            exact_total_paise += 1;
        }
        printf("4000 additions of 0.01f rupees = %.9f rupees (float)\n",
               (double)float_total_rupees);
        printf("Integer-paise total             = %" PRId64 " paise = Rs %.2f\n",
               exact_total_paise, (double)exact_total_paise / 100.0);
        printf("The integer-paise result is exact; the float result has representation/accumulation error.\n");
    }

    printf("\n[4] DATA TYPE RECOMMENDATIONS\n");
    printf("Meter register: uint16_t (exactly 16 bits when available)\n");
    printf("Household ID:   uint32_t (sufficient for 800,000 IDs)\n");
    printf("Money:          int64_t in paise for safe totals\n");
    printf("Avoid float/double for storing payable money.\n");

    return 0;
}
