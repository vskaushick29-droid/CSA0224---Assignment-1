#include <stdio.h>

#define FIXED_CHARGE_PAISE 5000
#define SLAB1_UNITS 100
#define SLAB2_UNITS 100
#define RATE1_PAISE 225
#define RATE2_PAISE 450

static unsigned int consumption(unsigned short previous, unsigned short current)
{
    return (unsigned int)((unsigned short)(current - previous));
}

static long long compute_bill(unsigned int units)
{
    long long energy = 0;
    if (units > SLAB1_UNITS) {
        unsigned int second = units - SLAB1_UNITS;
        if (second > SLAB2_UNITS) second = SLAB2_UNITS;
        energy += (long long)second * RATE1_PAISE;
    }
    if (units > SLAB1_UNITS + SLAB2_UNITS) {
        energy += (long long)(units - (SLAB1_UNITS + SLAB2_UNITS)) * RATE2_PAISE;
    }
    return FIXED_CHARGE_PAISE + energy;
}

int main(void)
{
    unsigned short previous = 65400;
    unsigned short current = 120;
    unsigned int units = consumption(previous, current);
    long long bill = compute_bill(units);

    printf("Previous reading : %u\n", (unsigned)previous);
    printf("Current reading  : %u\n", (unsigned)current);
    printf("Units consumed   : %u\n", units);
    printf("Total bill       : Rs %lld.%02lld\n", bill / 100, bill % 100);
    return 0;
}
