#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <stdint.h>

#define FIXED_CHARGE_PAISE 5000LL
#define RATE2_PAISE 225LL
#define RATE3_PAISE 450LL

static long long bill_paise(unsigned units)
{
    unsigned slab2 = units > 100 ? (units < 200 ? units - 100 : 100) : 0;
    unsigned slab3 = units > 200 ? units - 200 : 0;
    return FIXED_CHARGE_PAISE
         + (long long)slab2 * RATE2_PAISE
         + (long long)slab3 * RATE3_PAISE;
}

static double bill_rupees_double(unsigned units)
{
    double energy = 0.0;
    if (units > 100) {
        unsigned n = units < 200 ? units - 100 : 100;
        energy += n * 2.25;
    }
    if (units > 200)
        energy += (units - 200) * 4.50;
    return energy + 50.0;
}

static float bill_rupees_float(unsigned units)
{
    float energy = 0.0f;
    if (units > 100) {
        unsigned n = units < 200 ? units - 100 : 100;
        energy += n * 2.25f;
    }
    if (units > 200)
        energy += (units - 200) * 4.50f;
    return energy + 50.0f;
}

int main(void)
{
    const unsigned scales[] = {4000, 60000, 800000};
    const unsigned units = 350; /* deterministic load: same bill per household */
    const size_t n = sizeof(scales) / sizeof(scales[0]);

    printf("Task 10 - Expectation vs Execution\n");
    printf("Representative bill: %u units\n\n", units);

    printf("Type sizes on this system:\n");
    printf("sizeof(int) = %zu bytes, range = %d .. %d\n",
           sizeof(int), INT_MIN, INT_MAX);
    printf("sizeof(long) = %zu bytes, range = %ld .. %ld\n",
           sizeof(long), LONG_MIN, LONG_MAX);
    printf("sizeof(long long) = %zu bytes, range = %lld .. %lld\n",
           sizeof(long long), LLONG_MIN, LLONG_MAX);
    printf("sizeof(float) = %zu bytes, FLT_DIG = %d\n", sizeof(float), FLT_DIG);
    printf("sizeof(double) = %zu bytes, DBL_DIG = %d\n\n", sizeof(double), DBL_DIG);

    printf("Scale comparison:\n");
    for (size_t i = 0; i < n; ++i) {
        unsigned long long paise_sum = (unsigned long long)bill_paise(units) * scales[i];
        double double_sum = bill_rupees_double(units) * scales[i];
        float float_sum = bill_rupees_float(units) * scales[i];
        double paise_as_double = paise_sum / 100.0;
        double float_error = (double)float_sum - paise_as_double;
        double double_error = double_sum - paise_as_double;

        printf("\n%u bills:\n", scales[i]);
        printf("  long long paise = %llu paise (Rs %.2f)\n",
               paise_sum, paise_sum / 100.0);
        printf("  float rupees    = %.2f\n", (double)float_sum);
        printf("  double rupees   = %.2f\n", double_sum);
        printf("  float difference from paise = %.10f rupees\n", float_error);
        printf("  double difference from paise = %.10f rupees\n", double_error);
    }

    printf("\nOverflow boundary for a signed 32-bit int:\n");
    printf("INT_MAX = %d paise = Rs %.2f\n", INT_MAX, INT_MAX / 100.0);
    printf("At Rs %.2f per bill, about %.0f bills reach INT_MAX paise.\n",
           bill_paise(units) / 100.0,
           INT_MAX / (double)bill_paise(units));

    printf("\nDistrict-scale 800,000-bill result:\n");
    unsigned long long district = (unsigned long long)bill_paise(units) * 800000ULL;
    printf("  long long paise = %llu\n", district);
    printf("  exceeds INT_MAX? %s\n", district > (unsigned long long)INT_MAX ? "YES" : "NO");
    printf("  exceeds LONG_MAX? %s\n",
           district > (unsigned long long)LONG_MAX ? "YES" : "NO");

    printf("\nDouble vs long long:\n");
    printf("double stores approximately %d decimal digits; long long stores exact integer paise.\n", DBL_DIG);
    printf("For this district total, double can represent the integer magnitude exactly,\n");
    printf("but long long is preferred for billing because paise arithmetic is exact by construction.\n");

    return 0;
}
