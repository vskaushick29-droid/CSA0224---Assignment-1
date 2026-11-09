#include <stdio.h>
#include "billing.h"

int main(void)
{
    int test_units[] = {0, 100, 150, 200, 350, -5};
    int count = (int)(sizeof(test_units) / sizeof(test_units[0]));

#ifdef DEBUG
    printf("[DEBUG] Billing program started. Test count = %d\n", count);
    printf("[DEBUG] Fixed charge = %ld paise\n", FIXED_CHARGE_PAISE);
#endif

    for (int i = 0; i < count; i++) {
        int units = test_units[i];
        long long bill_paise = compute_bill(units);

#ifdef DEBUG
        printf("[DEBUG] Processing test %d: units = %d\n", i + 1, units);
#endif

        if (bill_paise < 0) {
            printf("Units: %d -> Invalid consumption\n", units);
        } else {
            printf("Units: %d -> Bill: Rs.%lld.%02lld\n",
                   units, bill_paise / 100, bill_paise % 100);
        }
    }

#ifdef DEBUG
    printf("[DEBUG] Billing program finished.\n");
#endif

    return 0;
}
