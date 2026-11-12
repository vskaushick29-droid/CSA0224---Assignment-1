#include "billing.h"

long long compute_bill(int units)
{
    long long energy_charge_paise;

    if (units < 0) {
        return -1;
    }

    if (units <= SLAB1_UNITS) {
        energy_charge_paise = RATE1_PAISE * units;
    } else if (units <= SLAB2_UNITS) {
        energy_charge_paise =
            (long long)(units - SLAB1_UNITS) * RATE2_PAISE;
    } else {
        energy_charge_paise =
            (long long)(SLAB2_UNITS - SLAB1_UNITS) * RATE2_PAISE
            + (long long)(units - SLAB2_UNITS) * RATE3_PAISE;
    }

    return energy_charge_paise + FIXED_CHARGE_PAISE;
}
