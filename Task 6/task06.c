#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include "billing.h"

/*
 * Alternative robust line parser:
 * - fgets reads at most buffer_size - 1 characters.
 * - strtol converts the numeric text.
 * - errno and end-pointer checks reject overflow and extra characters.
 */
int parse_units_line(const char *line, int *units)
{
    char *end;
    long value;

    if (line == NULL || units == NULL) {
        return 0;
    }

    errno = 0;
    value = strtol(line, &end, 10);

    if (line == end || errno == ERANGE || value < 0 || value > INT_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        end++;
    }

    if (*end != '\0') {
        return 0;
    }

    *units = (int)value;
    return 1;
}

/* Demonstrates parsing with fgets + strtol without waiting for user input. */
void demonstrate_line_parser(void)
{
    const char *samples[] = {"150\n", "abc\n", "-10\n", "200 units\n"};
    int count = (int)(sizeof(samples) / sizeof(samples[0]));

    printf("\nFGETS + STRTOL VALIDATION EXAMPLES\n");
    for (int i = 0; i < count; i++) {
        int units;
        if (parse_units_line(samples[i], &units)) {
            printf("Input text: %-12s -> accepted (%d units)\n",
                   samples[i], units);
        } else {
            printf("Input text: %-12s -> rejected\n", samples[i]);
        }
    }
}

int main(void)
{
    int units;
    int scan_result;
    long long bill_paise;

    printf("Grama Jyothi Electricity Billing\n");
    printf("Enter electricity consumption in units: ");

    /*
     * scanf returns the number of successfully assigned items.
     * For one %d conversion, success must return 1.
     */
    scan_result = scanf("%d", &units);

    if (scan_result != 1) {
        int ch;
        /* Clear the rest of the invalid input line. */
        while ((ch = getchar()) != '\n' && ch != EOF) {
            /* discard invalid characters */
        }
        printf("Invalid input: please enter a whole number.\n");
        demonstrate_line_parser();
        return 1;
    }

    if (units < 0) {
        printf("Invalid input: units cannot be negative.\n");
        demonstrate_line_parser();
        return 1;
    }

    bill_paise = compute_bill(units);
    if (bill_paise < 0) {
        printf("Unable to calculate bill.\n");
        return 1;
    }

    printf("\nBILL DETAILS\n");
    printf("Consumption : %d units\n", units);
    printf("Energy + fixed charge: Rs.%lld.%02lld\n",
           bill_paise / 100, bill_paise % 100);

    demonstrate_line_parser();
    return 0;
}
