#include <stdio.h>
#include <stdint.h>

#define SLAB1_UNITS 100
#define SLAB2_UNITS 200
#define RATE1_PAISE 0
#define RATE2_PAISE 225
#define RATE3_PAISE 450
#define FIXED_CHARGE_PAISE 5000L

typedef unsigned short meter_t;

unsigned long long compute_district_revenue(int household_count) {
    unsigned long long total_revenue_paise = 0;
    int i;
    for (i = 0; i < household_count; i++) {
        long sample_bill_paise = 16250L;
        total_revenue_paise += sample_bill_paise;
    }
    return total_revenue_paise;
}

int main(void) {
    int districts[] = {4000, 60000, 800000};
    int i;
    
    for (i = 0; i < 3; i++) {
        unsigned long long rev = compute_district_revenue(districts[i]);
        printf("Scale: %d households -> Total Revenue: Rs %llu.%02llu\n",
               districts[i], rev / 100, rev % 100);
    }
    
    return 0;
}
