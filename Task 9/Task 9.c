#include <stdio.h>

#define SLAB1_UNITS 100
#define SLAB2_UNITS 200
#define RATE1_PAISE 0
#define RATE2_PAISE 225
#define RATE3_PAISE 450
#define FIXED_CHARGE_PAISE 5000L

typedef unsigned short meter_t;

unsigned int calculate_units(meter_t previous, meter_t current) {
    if (current >= previous) {
        return (unsigned int)(current - previous);
    } else {
        return (unsigned int)((65535 - previous) + current + 1);
    }
}

long compute_bill(unsigned int units) {
    long paise = FIXED_CHARGE_PAISE;
    if (units > SLAB2_UNITS) {
        paise += (long)(units - SLAB2_UNITS) * RATE3_PAISE;
        paise += (long)(SLAB2_UNITS - SLAB1_UNITS) * RATE2_PAISE;
    } else if (units > SLAB1_UNITS) {
        paise += (long)(units - SLAB1_UNITS) * RATE2_PAISE;
    }
    return paise;
}

int main(void) {
    meter_t test_prev[] = {1000, 1000, 1000, 1000, 65400};
    meter_t test_curr[] = {1000, 1100, 1200, 1350, 120};
    int n = 5;
    int i;

    for (i = 0; i < n; i++) {
        unsigned int units = calculate_units(test_prev[i], test_curr[i]);
        long paise = compute_bill(units);
        printf("Test %d: Prev=%u, Curr=%u -> Units=%u | Bill=Rs %ld.%02ld\n",
               i + 1, test_prev[i], test_curr[i], units, paise / 100, paise % 100);
    }

    return 0;
}
