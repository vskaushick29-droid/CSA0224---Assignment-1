#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int hour;
    int minute;
    unsigned int watt_hours;
} MeterReading;

typedef struct {
    long base_charge_paise;
    long rate_normal_paise_per_kwh;
    long rate_peak_paise_per_kwh;
} TariffConfig;

TariffConfig load_tariff_runtime(void) {
    TariffConfig config;
    config.base_charge_paise = 5000L;
    config.rate_normal_paise_per_kwh = 225L;
    config.rate_peak_paise_per_kwh = 270L; 
    return config;
}

unsigned long long compute_smart_bill(MeterReading readings[], int count, TariffConfig config) {
    unsigned long long total_normal_wh = 0;
    unsigned long long total_peak_wh = 0;
    int i;

    for (i = 0; i < count; i++) {
        int h = readings[i].hour;
        if (h >= 18 && h < 22) {
            total_peak_wh += readings[i].watt_hours;
        } else {
            total_normal_wh += readings[i].watt_hours;
        }
    }

    unsigned long long normal_kwh_units = total_normal_wh / 1000ULL;
    unsigned long long peak_kwh_units = total_peak_wh / 1000ULL;

    unsigned long long energy_cost = (normal_kwh_units * config.rate_normal_paise_per_kwh) +
                                     (peak_kwh_units * config.rate_peak_paise_per_kwh);

    return (unsigned long long)config.base_charge_paise + energy_cost;
}

int main(void) {
    TariffConfig tariff = load_tariff_runtime();

    MeterReading sample_readings[4] = {
        {10, 0, 250},
        {19, 15, 400},
        {20, 30, 350},
        {23, 0, 150}
    };

    int num_readings = 4;
    unsigned long long bill_paise = compute_smart_bill(sample_readings, num_readings, tariff);

    printf("Runtime Tariff Loaded Successfully.\n");
    printf("Total Annual/Batch Bill: Rs %llu.%02llu\n", bill_paise / 100, bill_paise % 100);
    return 0;
}
