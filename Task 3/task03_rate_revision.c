/*
 * Task 03: Define Constants
 * Course: CSA0224 - C Programming
 *
 * Demonstrates #define, const, and enum, and implements the
 * assignment's slab-based billing function using tariff macros.
 */

#include <stdio.h>
#include <limits.h>

/* Tariff constants required by the assignment (amounts in paise). */
#define SLAB1_UNITS 100
#define SLAB2_UNITS 200
#define RATE1_PAISE 0
#define RATE2_PAISE 230
#define RATE3_PAISE 450
#define FIXED_CHARGE_PAISE 5000L

/* enum is suitable for named integral options/labels. */
enum ConsumerCategory {
    DOMESTIC = 1,
    COMMERCIAL = 2
};

/* const creates a typed, read-only object. */
static const int MAX_METER_UNITS = 65535;

/*
 * Returns the complete bill in paise, including the fixed charge.
 * Returns -1 for invalid negative consumption.
 */
long long compute_bill(int units)
{
    long long energy_charge = 0;

    if (units < 0) {
        return -1;
    }

    if (units <= SLAB1_UNITS) {
        energy_charge = (long long)units * RATE1_PAISE;
    } else if (units <= SLAB2_UNITS) {
        energy_charge =
            (long long)SLAB1_UNITS * RATE1_PAISE +
            (long long)(units - SLAB1_UNITS) * RATE2_PAISE;
    } else {
        energy_charge =
            (long long)SLAB1_UNITS * RATE1_PAISE +
            (long long)(SLAB2_UNITS - SLAB1_UNITS) * RATE2_PAISE +
            (long long)(units - SLAB2_UNITS) * RATE3_PAISE;
    }

    return energy_charge + FIXED_CHARGE_PAISE;
}

static void print_bill(int units)
{
    long long total_paise = compute_bill(units);

    if (total_paise < 0) {
        printf("%4d units | INVALID INPUT\n", units);
        return;
    }

    printf("%4d units | Energy: Rs %lld.%02lld | Fixed: Rs %lld.%02lld"
           " | Total: Rs %lld.%02lld\n",
           units,
           (total_paise - FIXED_CHARGE_PAISE) / 100,
           (total_paise - FIXED_CHARGE_PAISE) % 100,
           (long long)FIXED_CHARGE_PAISE / 100,
           (long long)FIXED_CHARGE_PAISE % 100,
           total_paise / 100,
           total_paise % 100);
}

int main(void)
{
    const int test_units[] = {0, 100, 150, 200, 350};
    const size_t count = sizeof(test_units) / sizeof(test_units[0]);

    printf("============================================================\n");
    printf(" TASK 03: DEFINING CONSTANTS IN C\n");
    printf("============================================================\n");

    printf("Tariff macros: slab1=%d, slab2=%d, rate2=%d paise, "
           "rate3=%d paise, fixed=%ld paise\n",
           SLAB1_UNITS, SLAB2_UNITS, RATE2_PAISE,
           RATE3_PAISE, FIXED_CHARGE_PAISE);
    printf("const example: MAX_METER_UNITS = %d\n", MAX_METER_UNITS);
    printf("enum example: DOMESTIC = %d, COMMERCIAL = %d\n",
           DOMESTIC, COMMERCIAL);

    printf("\n[1] REQUIRED BILLING TEST CASES\n");
    for (size_t i = 0; i < count; ++i) {
        print_bill(test_units[i]);
    }

    printf("\n[2] INVALID INPUT TEST\n");
    print_bill(-5);

    printf("\n[3] TARIFF REVISION TEST\n");
    printf("Change RATE2_PAISE from 225 to 230 and recompile.\n");
    printf("Expected revised totals: 0 units = Rs 50.00; "
           "150 units = Rs 165.00; 200 units = Rs 280.00; "
           "350 units = Rs 955.00.\n");

    printf("============================================================\n");
    return 0;
}
