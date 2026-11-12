#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef unsigned short meter_t;

/* Tariff constants: all money values are stored as paise. */
#define SLAB1_UNITS 100U
#define SLAB2_UNITS 100U
#define RATE1_PAISE 0LL
#define RATE2_PAISE 225LL
#define RATE3_PAISE 450LL
#define FIXED_CHARGE_PAISE 5000LL

/* A decrease is accepted as rollover only for a reading near the
   16-bit upper boundary followed by a small reading. */
#define ROLLOVER_MIN_PREVIOUS 65000U
#define ROLLOVER_MAX_CURRENT  1000U

typedef struct {
    meter_t previous;
    meter_t current;
    unsigned int units;
    long long energy_paise;
    long long fixed_paise;
    long long total_paise;
} Bill;

static int read_meter(const char *prompt, unsigned int *value)
{
    char line[128];
    char extra;

    printf("%s", prompt);
    if (!fgets(line, sizeof line, stdin))
        return 0;

    if (sscanf(line, "%u %c", value, &extra) != 1)
        return 0;

    if (*value > USHRT_MAX)
        return 0;

    return 1;
}

static int consumption(meter_t previous, meter_t current, unsigned int *units)
{
    if (current >= previous) {
        *units = (unsigned int)current - (unsigned int)previous;
        return 1;
    }

    if ((unsigned int)previous >= ROLLOVER_MIN_PREVIOUS &&
        (unsigned int)current <= ROLLOVER_MAX_CURRENT) {
        /* 16-bit counter range is 0..65535, so the rollover distance is:
           (65536 - previous) + current. */
        *units = (unsigned int)(USHRT_MAX + 1U)
              - (unsigned int)previous + (unsigned int)current;
        return 1;
    }

    return 0;
}

static long long compute_energy_paise(unsigned int units)
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

static void print_bill(const Bill *b)
{
    printf("\n--- Electricity Bill ---\n");
    printf("Previous reading : %u\n", (unsigned)b->previous);
    printf("Current reading  : %u\n", (unsigned)b->current);
    printf("Units consumed   : %u\n", b->units);
    printf("Energy charge    : ");
    print_money(b->energy_paise);
    printf("\nFixed charge     : ");
    print_money(b->fixed_paise);
    printf("\nTotal bill       : ");
    print_money(b->total_paise);
    printf("\n");
}

int main(void)
{
    unsigned int prev_input, curr_input;
    Bill bill;

    printf("Grama Jyothi Rural Electricity Co-operative\n");
    printf("Tariff: first 100 units free; next 100 at Rs 2.25; above 200 at Rs 4.50\n");
    printf("Fixed charge: Rs 50.00\n");

    if (!read_meter("Enter previous meter reading (0-65535): ", &prev_input)) {
        fprintf(stderr, "Invalid previous reading.\n");
        return EXIT_FAILURE;
    }

    if (!read_meter("Enter current meter reading (0-65535): ", &curr_input)) {
        fprintf(stderr, "Invalid current reading.\n");
        return EXIT_FAILURE;
    }

    bill.previous = (meter_t)prev_input;
    bill.current = (meter_t)curr_input;

    if (!consumption(bill.previous, bill.current, &bill.units)) {
        fprintf(stderr,
                "Invalid reading sequence: current reading is lower than previous "
                "without a valid 16-bit rollover.\n");
        return EXIT_FAILURE;
    }

    bill.energy_paise = compute_energy_paise(bill.units);
    bill.fixed_paise = FIXED_CHARGE_PAISE;
    bill.total_paise = bill.energy_paise + bill.fixed_paise;

    if (bill.total_paise < bill.fixed_paise) {
        fprintf(stderr, "Internal validation error: negative energy charge.\n");
        return EXIT_FAILURE;
    }

    print_bill(&bill);
    return EXIT_SUCCESS;
}
