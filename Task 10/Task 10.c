#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void) {
    long long total_paise_accum = 0;
    double total_rupees_accum = 0.0;
    int households[] = {4000, 60000, 800000};
    int i, h;

    for (i = 0; i < 3; i++) {
        int count = households[i];
        total_paise_accum = 0;
        total_rupees_accum = 0.0;

        for (h = 0; h < count; h++) {
            long sample_bill_paise = 16250L; 
            total_paise_accum += sample_bill_paise;
            total_rupees_accum += (double)sample_bill_paise / 100.0;
        }

        printf("Scale: %d households\n", count);
        printf("  Integer Paise Accumulator : %lld paise (Rs %.2f)\n", 
               total_paise_accum, (double)total_paise_accum / 100.0);
        printf("  Double Rupees Accumulator : Rs %.2f\n\n", total_rupees_accum);
    }

    printf("sizeof(long long) = %zu bytes, Max = %lld\n", sizeof(long long), LLONG_MAX);
    return 0;
}
