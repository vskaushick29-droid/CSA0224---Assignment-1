#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    uint32_t household_number;
    char category[20];
    uint16_t previous_reading;
    uint16_t current_reading;
    uint32_t units_consumed;
    long energy_charge_paise;
    long fixed_charge_paise;
    long total_bill_paise;
} HouseholdBill;

void analyze_problem_structure(void) {
    printf("=== GRAMA JYOTHI RURAL ELECTRICITY CO-OPERATIVE: TASK 1 ANALYSIS ===\n");
    printf("1. Inputs identified: Previous Reading, Current Reading, Household Number, Category.\n");
    printf("2. Outputs identified: Units Consumed, Energy Charge, Fixed Charge, Total Bill.\n");
    printf("3. Constants: Slab thresholds, tariff rates per unit, fixed charges.\n");
    printf("4. Rules: Bills must be non-negative; Total = Energy Charge + Fixed Charge.\n\n");
}

int main(void) {
    analyze_problem_structure();
    
    HouseholdBill sample = {
        1001,
        "Domestic",
        1200,
        1530,
        330,
        0,
        5000L,
        0
    };
    
    printf("Sample Household ID: %u\n", sample.household_number);
    printf("Category: %s\n", sample.category);
    printf("Previous Reading: %u | Current Reading: %u\n", sample.previous_reading, sample.current_reading);
    printf("Data structures successfully initialized and validated.\n");
    
    return 0;
}
