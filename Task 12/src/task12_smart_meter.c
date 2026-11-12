/*
 * Task 12 - Smart Meter Billing Redesign
 * Design:
 *   - 64-bit unsigned cumulative watt-hour meter reading
 *   - Runtime tariff configuration (tariff.conf)
 *   - 15-minute interval input
 *   - 6 PM <= time < 10 PM peak surcharge
 *   - Integer paise arithmetic; final fractional-paise result is rounded half-up
 *
 * Input format:
 *   previous_wh current_wh HH:MM
 *
 * Example:
 *   0 5000 17:45
 *   5000 15000 18:00
 *   15000 20000 21:45
 *
 * A line is one 15-minute interval. For simplicity, fixed charge is applied
 * once per run/bill, while energy charge is calculated for all intervals.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <limits.h>

#define CONFIG_FILE "tariff.conf"
#define LINE_SIZE 256
#define PEAK_START_MIN  (18 * 60)
#define PEAK_END_MIN    (22 * 60)

typedef struct {
    uint64_t slab1_wh;          /* first slab boundary, in Wh */
    uint64_t slab2_wh;          /* second slab boundary, in Wh */
    uint64_t rate1_paise_kwh;
    uint64_t rate2_paise_kwh;
    uint64_t rate3_paise_kwh;
    uint64_t fixed_charge_paise;
    uint64_t peak_percent;
} Tariff;

typedef struct {
    uint64_t previous_wh;
    uint64_t current_wh;
    unsigned hour;
    unsigned minute;
} Reading;

/* Return 1 if the interval begins during 18:00 <= time < 22:00. */
static int is_peak(unsigned hour, unsigned minute)
{
    unsigned total_minutes = hour * 60u + minute;
    return total_minutes >= PEAK_START_MIN && total_minutes < PEAK_END_MIN;
}

/*
 * Smart-meter readings are uint64_t cumulative Wh values.  Normal subtraction
 * is sufficient for a non-wrapping counter.  If the 64-bit counter wraps,
 * unsigned arithmetic gives the modulo-2^64 difference.
 */
static uint64_t consumption_wh(uint64_t previous, uint64_t current)
{
    return current - previous;
}

/* Charge for energy in one slab, represented as a numerator in paise*Wh. */
static uint64_t slab_charge_numerator(uint64_t wh, uint64_t rate_paise_kwh)
{
    return wh * rate_paise_kwh;
}

/* Round a paise*Wh numerator divided by 1000 to nearest paise, half-up. */
static uint64_t numerator_to_paise(uint64_t numerator)
{
    return (numerator + 500u) / 1000u;
}

/*
 * Calculate energy-charge numerator for one interval.
 * The slab boundaries are expressed in Wh because 1 unit = 1 kWh = 1000 Wh.
 * Peak surcharge is applied to the applicable rate.
 */
static uint64_t energy_charge_numerator(uint64_t cumulative_units_wh,
                                        uint64_t interval_wh,
                                        const Tariff *t,
                                        int peak)
{
    uint64_t rate1 = t->rate1_paise_kwh;
    uint64_t rate2 = t->rate2_paise_kwh;
    uint64_t rate3 = t->rate3_paise_kwh;

    if (peak) {
        rate1 = rate1 + (rate1 * t->peak_percent) / 100u;
        rate2 = rate2 + (rate2 * t->peak_percent) / 100u;
        rate3 = rate3 + (rate3 * t->peak_percent) / 100u;
    }

    /* Determine how much of this interval lies in each cumulative slab. */
    uint64_t before = cumulative_units_wh;
    uint64_t after = cumulative_units_wh + interval_wh;

    uint64_t slab1_before = before < t->slab1_wh ? before : t->slab1_wh;
    uint64_t slab1_after  = after  < t->slab1_wh ? after  : t->slab1_wh;
    uint64_t first_wh = slab1_after > slab1_before
                     ? slab1_after - slab1_before : 0;

    uint64_t slab2_before = before < t->slab2_wh ? before : t->slab2_wh;
    uint64_t slab2_after  = after  < t->slab2_wh ? after  : t->slab2_wh;
    uint64_t second_wh = slab2_after > slab2_before
                      ? slab2_after - slab2_before : 0;

    uint64_t used_first_two = first_wh + second_wh;
    uint64_t third_wh = interval_wh > used_first_two
                      ? interval_wh - used_first_two : 0;

    return slab_charge_numerator(first_wh, rate1)
         + slab_charge_numerator(second_wh, rate2)
         + slab_charge_numerator(third_wh, rate3);
}

static int parse_config(const char *filename, Tariff *t)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Cannot open tariff configuration");
        return 0;
    }

    char line[LINE_SIZE];
    char key[64];
    unsigned long long value;
    int found = 0;

    while (fgets(line, sizeof line, fp) != NULL) {
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\0')
            continue;
        if (sscanf(line, "%63s %llu", key, &value) != 2)
            continue;

        if (strcmp(key, "SLAB1_UNITS") == 0) {
            t->slab1_wh = (uint64_t)value * 1000u;
            found++;
        } else if (strcmp(key, "SLAB2_UNITS") == 0) {
            t->slab2_wh = (uint64_t)value * 1000u;
            found++;
        } else if (strcmp(key, "RATE1_PAISE_PER_KWH") == 0) {
            t->rate1_paise_kwh = (uint64_t)value;
            found++;
        } else if (strcmp(key, "RATE2_PAISE_PER_KWH") == 0) {
            t->rate2_paise_kwh = (uint64_t)value;
            found++;
        } else if (strcmp(key, "RATE3_PAISE_PER_KWH") == 0) {
            t->rate3_paise_kwh = (uint64_t)value;
            found++;
        } else if (strcmp(key, "FIXED_CHARGE_PAISE") == 0) {
            t->fixed_charge_paise = (uint64_t)value;
            found++;
        } else if (strcmp(key, "PEAK_PERCENT") == 0) {
            t->peak_percent = (uint64_t)value;
            found++;
        }
    }

    fclose(fp);
    return found == 7;
}

static int parse_reading(const char *line, Reading *r)
{
    unsigned long long prev, cur;
    unsigned h, m;

    if (sscanf(line, "%llu %llu %u:%u", &prev, &cur, &h, &m) != 4)
        return 0;

    if (h > 23 || m > 59)
        return 0;

    r->previous_wh = (uint64_t)prev;
    r->current_wh = (uint64_t)cur;
    r->hour = h;
    r->minute = m;
    return 1;
}

static void print_money(uint64_t paise)
{
    printf("Rs %" PRIu64 ".%02" PRIu64, paise / 100u, paise % 100u);
}

int main(void)
{
    Tariff tariff = {0};
    char line[LINE_SIZE];
    uint64_t total_wh = 0;
    uint64_t total_energy_numerator = 0;
    unsigned interval_count = 0;

    if (!parse_config(CONFIG_FILE, &tariff)) {
        fprintf(stderr, "Invalid tariff configuration.\n");
        return EXIT_FAILURE;
    }

    printf("Smart Meter Billing - 15 minute readings\n");
    printf("Peak period: 18:00 to 21:45 (20%% surcharge by default)\n");
    printf("Enter previous_wh current_wh HH:MM, one interval per line.\n");
    printf("Press EOF (Ctrl+D on Linux) after the last interval.\n\n");

    while (fgets(line, sizeof line, stdin) != NULL) {
        Reading r;
        if (!parse_reading(line, &r)) {
            fprintf(stderr, "Invalid input line: %s", line);
            continue;
        }

        uint64_t wh = consumption_wh(r.previous_wh, r.current_wh);
        int peak = is_peak(r.hour, r.minute);

        total_wh += wh;
        total_energy_numerator +=
            energy_charge_numerator(total_wh - wh, wh, &tariff, peak);
        interval_count++;

        printf("Interval %u: %" PRIu64 " Wh at %02u:%02u [%s]\n",
               interval_count, wh, r.hour, r.minute,
               peak ? "PEAK" : "NORMAL");
    }

    uint64_t energy_paise = numerator_to_paise(total_energy_numerator);
    uint64_t total_paise = tariff.fixed_charge_paise + energy_paise;

    printf("\nIntervals processed : %u\n", interval_count);
    printf("Energy consumed     : %" PRIu64 " Wh (%.3f kWh)\n",
           total_wh, (double)total_wh / 1000.0);
    printf("Fixed charge        : ");
    print_money(tariff.fixed_charge_paise);
    printf("\nEnergy charge       : ");
    print_money(energy_paise);
    printf("\nTotal bill          : ");
    print_money(total_paise);
    printf("\n");

    return EXIT_SUCCESS;
}
