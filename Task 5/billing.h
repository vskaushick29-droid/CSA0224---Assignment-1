#ifndef BILLING_H
#define BILLING_H

/* Shared tariff constants and function declarations. */
#define SLAB1_UNITS 100
#define SLAB2_UNITS 200
#define RATE1_PAISE 0L
#define RATE2_PAISE 225L
#define RATE3_PAISE 450L
#define FIXED_CHARGE_PAISE 5000L

/* Returns the complete bill in paise. Negative units are invalid. */
long long compute_bill(int units);

#endif /* BILLING_H */
