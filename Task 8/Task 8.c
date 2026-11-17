#include <stdio.h>

int compute_total(int base, int extra) {
    return base + extra;
}

int main(void) {
    int base_charge = 5000;
    int energy_charge = 4500;
    int total = compute_total(base_charge, energy_charge);
    printf("Total Bill in Paise: %d\n", total);
    return 0;
}
