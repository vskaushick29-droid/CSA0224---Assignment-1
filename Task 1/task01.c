/*
 * Assignment 1 - Task 01: Problem Analysis and Data Identification
 * Student: Kaushick V S | Register No: 1912260163
 * Course: CSA0224 - C Programming
 *
 * Demonstrates the identified data items, a hand-checkable billing example,
 * billing invariants, and integer-versus-string meter-reading trade-offs.
 * This is a Task 1 analysis demonstration, not the complete billing system.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

#define SLAB1_UNITS          100U
#define SLAB2_UNITS          200U
#define RATE1_PAISE            0LL
#define RATE2_PAISE          225LL
#define RATE3_PAISE          450LL
#define FIXED_CHARGE_PAISE  5000LL
#define DISTRICT_HOUSEHOLDS 800000ULL

typedef struct {
    unsigned long household_id;
    char category;
    unsigned short previous_reading;
    unsigned short current_reading;
} ConsumerInput;

typedef struct {
    unsigned int units_consumed;
    long long fixed_charge_paise;
    long long energy_charge_paise;
    long long total_bill_paise;
} BillOutput;

/* A fixed-width text field: 5 decimal digits + NUL + 2 reserved bytes. */
typedef struct {
    char previous_text[8];
    char current_text[8];
} StringReading;

static long long calculate_energy_charge(unsigned int units)
{
    unsigned int slab2_units = 0U;
    unsigned int slab3_units = 0U;

    if (units > SLAB1_UNITS) {
        slab2_units = (units < SLAB2_UNITS)
                    ? units - SLAB1_UNITS
                    : SLAB2_UNITS - SLAB1_UNITS;
    }
    if (units > SLAB2_UNITS) {
        slab3_units = units - SLAB2_UNITS;
    }

    return (long long)slab2_units * RATE2_PAISE
         + (long long)slab3_units * RATE3_PAISE
         + (long long)(units < SLAB1_UNITS ? units : SLAB1_UNITS) * RATE1_PAISE;
}

static int bill_invariants_hold(const BillOutput *bill)
{
    return bill->fixed_charge_paise >= 0
        && bill->energy_charge_paise >= 0
        && bill->total_bill_paise >= 0
        && bill->total_bill_paise == bill->fixed_charge_paise
                                      + bill->energy_charge_paise;
}

static void print_rupees(const char *label, long long paise)
{
    printf("  %-8s Rs %lld.%02lld\n", label, paise / 100LL, paise % 100LL);
}

int main(void)
{
    const ConsumerInput consumer = {1001UL, 'D', 1200U, 1530U};
    BillOutput bill;
    StringReading text_reading = {{0}, {0}};
    unsigned long previous_from_text;
    unsigned long current_from_text;
    size_t integer_memory;
    size_t string_memory;

    (void)snprintf(text_reading.previous_text, sizeof text_reading.previous_text, "%05u",
                   (unsigned int)consumer.previous_reading);
    (void)snprintf(text_reading.current_text, sizeof text_reading.current_text, "%05u",
                   (unsigned int)consumer.current_reading);

    bill.units_consumed = (unsigned int)consumer.current_reading
                        - (unsigned int)consumer.previous_reading;
    bill.fixed_charge_paise = FIXED_CHARGE_PAISE;
    bill.energy_charge_paise = calculate_energy_charge(bill.units_consumed);
    bill.total_bill_paise = bill.fixed_charge_paise + bill.energy_charge_paise;

    printf("======================================================================\n");
    printf(" TASK 01: PROBLEM ANALYSIS AND DATA IDENTIFICATION\n");
    printf(" Student: Kaushick V S | Register: 1912260163 | Compiler: GCC %s\n", __VERSION__);
    printf("======================================================================\n");

    printf("\n[1] DATA ITEMS AND ACTUAL STORAGE SIZES ON THIS SYSTEM\n");
    printf("  %-24s %-20s %zu byte(s)\n", "household_id", "unsigned long", sizeof(unsigned long));
    printf("  %-24s %-20s %zu byte(s)\n", "category", "char", sizeof(char));
    printf("  %-24s %-20s %zu byte(s)\n", "previous_reading", "unsigned short", sizeof(unsigned short));
    printf("  %-24s %-20s %zu byte(s)\n", "current_reading", "unsigned short", sizeof(unsigned short));
    printf("  %-24s %-20s %zu byte(s)\n", "units_consumed", "unsigned int", sizeof(unsigned int));
    printf("  %-24s %-20s %zu byte(s)\n", "money fields", "long long (paise)", sizeof(long long));
    printf("  unsigned short range: 0 to %u (verified from USHRT_MAX)\n", (unsigned int)USHRT_MAX);
    printf("  unsigned int range:   0 to %u (verified from UINT_MAX)\n", UINT_MAX);
    printf("  unsigned long range:  0 to %lu (verified from ULONG_MAX)\n", ULONG_MAX);

    printf("\n[2] INPUTS, BILLING EXAMPLE, OUTPUTS AND INVARIANTS\n");
    printf("  Inputs: household ID=%lu, category=%c, previous=%hu, current=%hu\n",
           consumer.household_id, consumer.category,
           consumer.previous_reading, consumer.current_reading);
    printf("  Units consumed: %u - %u = %u units\n",
           (unsigned int)consumer.current_reading,
           (unsigned int)consumer.previous_reading, bill.units_consumed);
    printf("  Slabs: first 100 free; next 100 at Rs 2.25; above 200 at Rs 4.50\n");
    print_rupees("Fixed", bill.fixed_charge_paise);
    print_rupees("Energy", bill.energy_charge_paise);
    print_rupees("Total", bill.total_bill_paise);
    printf("  Invariant 1 (non-negative charges): %s\n",
           (bill.fixed_charge_paise >= 0 && bill.energy_charge_paise >= 0) ? "PASS" : "FAIL");
    printf("  Invariant 2 (total = fixed + energy): %s\n",
           (bill.total_bill_paise == bill.fixed_charge_paise + bill.energy_charge_paise) ? "PASS" : "FAIL");
    printf("  Overall invariant validation: %s\n", bill_invariants_hold(&bill) ? "PASS" : "FAIL");

    printf("\n[3] INTEGER VERSUS STRING REPRESENTATION\n");
    printf("  Integer reading (unsigned short): %zu byte(s) per reading\n", sizeof(unsigned short));
    printf("  Text reading \"%s\": %zu characters; char[8] field = %zu bytes\n",
           text_reading.current_text, strlen(text_reading.current_text),
           sizeof text_reading.current_text);
    printf("  Note: a minimally sized C string needs d+1 bytes; char[8] reserves 8 bytes.\n");
    previous_from_text = strtoul(text_reading.previous_text, NULL, 10);
    current_from_text = strtoul(text_reading.current_text, NULL, 10);
    printf("  strtoul conversion: %lu - %lu = %lu units\n",
           current_from_text, previous_from_text,
           current_from_text - previous_from_text);
    printf("  Integer arithmetic: O(1) for fixed-width values.\n");
    printf("  String conversion/comparison: O(d), where d is the number of digits.\n");

    integer_memory = (size_t)DISTRICT_HOUSEHOLDS * 2U * sizeof(unsigned short);
    string_memory = (size_t)DISTRICT_HOUSEHOLDS * 2U * sizeof text_reading.current_text;
    printf("  For %llu households and 2 readings each:\n", DISTRICT_HOUSEHOLDS);
    printf("    Integer storage: %zu bytes (%.2f MiB)\n", integer_memory,
           (double)integer_memory / (1024.0 * 1024.0));
    printf("    char[8] storage: %zu bytes (%.2f MiB)\n", string_memory,
           (double)string_memory / (1024.0 * 1024.0));

    printf("\n[4] DESIGN CONSIDERATIONS IDENTIFIED\n");
    printf("  Negative readings: reject as invalid input; valid meter values are non-negative.\n");
    printf("  Fractional currency: store money as integer paise to avoid float rounding drift.\n");
    printf("  Large totals: use a 64-bit accumulator (for example, long long) for aggregate revenue.\n");
    printf("  Meter rollover: a 16-bit register wraps after 65535; handle it in Task 2.\n");
    printf("  Tariff constants: centralise slab limits, rates and fixed charge.\n");
    printf("======================================================================\n");

    return bill_invariants_hold(&bill) ? EXIT_SUCCESS : EXIT_FAILURE;
}
