#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <stdint.h>

static void demonstrate_conversions(void)
{
    int whole = 7;
    int divisor = 2;
    double integer_division = whole / divisor;
    double floating_division = (double)whole / divisor;
    double explicit_cast = (double)(whole / divisor);

    long long large_value = 3000000000LL;
    int narrowed_value = (int)large_value; /* Result is implementation-defined if out of int range. */

    printf("TYPE CONVERSION AND DIVISION\n");
    printf("int 7 / int 2 assigned to double = %.2f\n", integer_division);
    printf("(double)7 / 2                  = %.2f\n", floating_division);
    printf("(double)(7 / 2)                = %.2f\n", explicit_cast);
    printf("Large long long value          = %lld\n", large_value);
    printf("After conversion to int        = %d (implementation-defined if out of range)\n",
           narrowed_value);
}

static void demonstrate_expressions(void)
{
    int a = 5;
    int b = 2;
    int x = 3;

    printf("\nEXPRESSIONS THAT MAY SURPRISE BEGINNERS\n");
    printf("5 / 2       = %d (integer division discards fractional part)\n", a / b);
    printf("5 %% 2       = %d (remainder operator)\n", a % b);
    printf("x += 2 * 3  -> ");
    x += 2 * 3;
    printf("%d (multiplication happens before addition)\n", x);
}

static void demonstrate_currency_rounding(void)
{
    double amount_rupees = 162.499;
    long long rounded_paise = llround(amount_rupees * 100.0);

    printf("\nCURRENCY ROUNDING EXAMPLE\n");
    printf("Amount before rounding = Rs.%.3f\n", amount_rupees);
    printf("Rounded integer paise  = %lld paise\n", rounded_paise);
    printf("Displayed amount       = Rs.%lld.%02lld\n",
           rounded_paise / 100, rounded_paise % 100);
}

static void compare_float_and_integer_paise(void)
{
    const int household_counts[] = {4000, 60000, 800000};
    const int number_of_cases =
        (int)(sizeof(household_counts) / sizeof(household_counts[0]));

    printf("\nFLOATING-POINT VS INTEGER PAISE ACCUMULATION\n");
    printf("Each household contributes Rs.0.01 (1 paise).\n");
    printf("%-12s %-20s %-20s %-16s\n",
           "Households", "Float total (Rs.)", "Integer total (Rs.)", "Float error (Rs.)");

    for (int i = 0; i < number_of_cases; i++) {
        int n = household_counts[i];
        float float_total = 0.0f;
        long long integer_total_paise = 0;

        for (int j = 0; j < n; j++) {
            float_total += 0.01f;
            integer_total_paise += 1;
        }

        double integer_total_rupees = (double)integer_total_paise / 100.0;
        double float_error = (double)float_total - integer_total_rupees;

        printf("%-12d %-20.6f %-20.2f %+.8f\n",
               n, (double)float_total, integer_total_rupees, float_error);
    }
}

int main(void)
{
    printf("TASK 07 - TYPE CONVERSION AND PRECISION\n");
    printf("int range: %d to %d\n", INT_MIN, INT_MAX);
    printf("float decimal digits of precision (FLT_DIG): %d\n", FLT_DIG);
    printf("double decimal digits of precision (DBL_DIG): %d\n", DBL_DIG);
    printf("Size of int: %zu bytes; float: %zu bytes; double: %zu bytes\n",
           sizeof(int), sizeof(float), sizeof(double));

    demonstrate_conversions();
    demonstrate_expressions();
    demonstrate_currency_rounding();
    compare_float_and_integer_paise();

    return 0;
}
