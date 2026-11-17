#include <stdio.h>

int main(void) {
    unsigned int prev;
    unsigned int curr;
    long total_paise;
    int result;

    printf("Enter previous meter reading and current meter reading: ");
    result = scanf("%u %u", &prev, &curr);

    if (result != 2) {
        printf("Error: Invalid input format. Please enter numeric values.\n");
        return 1;
    }

    if (curr < prev) {
        printf("Note: Meter rollover detected.\n");
    }

    unsigned int units = (curr >= prev) ? (curr - prev) : ((65535 - prev) + curr + 1);
    total_paise = 5000L;

    if (units > 200) {
        total_paise += (long)(units - 200) * 450 + 100 * 225;
    } else if (units > 100) {
        total_paise += (long)(units - 100) * 225;
    }

    printf("Units Consumed: %u\n", units);
    printf("Total Bill: Rs %ld.%02ld\n", total_paise / 100, total_paise % 100);

    return 0;
}
