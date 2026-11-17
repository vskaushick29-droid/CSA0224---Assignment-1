#include <stdio.h>

#define SLAB1_UNITS 100
#define SLAB2_UNITS 200
#define RATE1_PAISE 0
#define RATE2_PAISE 225
#define RATE3_PAISE 450
#define FIXED_CHARGE_PAISE 5000L

typedef unsigned short meter_t;

unsigned int consumption(meter_t previous, meter_t current) {
    return (unsigned int)(current - previous);
}

long compute_bill(int units) {
    long paise = FIXED_CHARGE_PAISE;
    
    #ifdef DEBUG
    printf("[DEBUG] Base fixed charge: %ld paise\n", paise);
    #endif

    if (units > SLAB2_UNITS) {
        paise += (long)(units - SLAB2_UNITS) * RATE3_PAISE;
        paise += (long)(SLAB2_UNITS - SLAB1_UNITS) * RATE2_PAISE;
    } else if (units > SLAB1_UNITS) {
        paise += (long)(units - SLAB1_UNITS) * RATE2_PAISE;
    }

    #ifdef DEBUG
    printf("[DEBUG] Final computed bill for %d units: %ld paise\n", units, paise);
    #endif

    return paise;
}

int main(void) {
    meter_t prev = 65400;
    meter_t curr = 120;
    unsigned int units = consumption(prev, curr);
    long total = compute_bill((int)units);

    printf("Consumed: %u units | Total Bill: Rs %ld.%02ld\n", units, total / 100, total % 100);
    return 0;
}
