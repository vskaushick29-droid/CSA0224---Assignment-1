#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

/*
 * Final design recommendation demonstration.
 * Money is represented in integer paise.
 * Meter readings use an unsigned 16-bit type.
 */
typedef unsigned short meter_t;

#define SLAB1_UNITS 100U
#define SLAB2_UNITS 100U
#define RATE1_PAISE 0LL
#define RATE2_PAISE 225LL
#define RATE3_PAISE 450LL
#define FIXED_CHARGE_PAISE 5000LL

#define ROLLOVER_MIN_PREVIOUS 65000U
#define ROLLOVER_MAX_CURRENT 1000U

static unsigned int consumption(meter_t previous, meter_t current)
{
    if (current >= previous)
        return (unsigned int)current - (unsigned int)previous;

    if ((unsigned int)previous >= ROLLOVER_MIN_PREVIOUS &&
        (unsigned int)current <= ROLLOVER_MAX_CURRENT)
        return (unsigned int)(USHRT_MAX + 1U)
             - (unsigned int)previous + (unsigned int)current;

    return UINT_MAX;
}

static long long energy_charge_paise(unsigned int units)
{
    unsigned int slab1 = units < SLAB1_UNITS ? units : SLAB1_UNITS;
    unsigned int remaining = units - slab1;
    unsigned int slab2 = remaining < SLAB2_UNITS ? remaining : SLAB2_UNITS;

    remaining -= slab2;

    return (long long)slab1 * RATE1_PAISE
         + (long long)slab2 * RATE2_PAISE
         + (long long)remaining * RATE3_PAISE;
}

static void print_money(long long paise)
{
    printf("Rs %lld.%02lld", paise / 100, llabs(paise % 100));
}

int main(void)
{
    const unsigned int samples[] = {0U, 100U, 150U, 200U, 350U, 256U};
    const size_t n = sizeof(samples) / sizeof(samples[0]);

    printf("Task 11 - Final Design Recommendation Demonstration\n");
    printf("Types: meter_t=unsigned short, money=long long paise\n");
    printf("District-safe money accumulator: long long\n\n");

    for (size_t i = 0; i < n; ++i) {
        long long total = FIXED_CHARGE_PAISE + energy_charge_paise(samples[i]);
        printf("%3u units -> ", samples[i]);
        print_money(total);
        printf("\n");
    }

    unsigned int rollover = consumption((meter_t)65400, (meter_t)120);
    printf("\nRollover test: 65400 -> 120 = %u units\n", rollover);

    {
        unsigned long long district_paise =
            (unsigned long long)95000 * 800000ULL;
        printf("District example: 800000 x Rs 950.00 = %llu paise\n",
               district_paise);
        printf("Fits long long: %s\n",
               district_paise <= (unsigned long long)LLONG_MAX ? "YES" : "NO");
    }

    return EXIT_SUCCESS;
}
