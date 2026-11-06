# Task 03: Define Constants in C

**Course:** CSA0224 – C Programming  
**Assignment:** Reliable Billing Program for a Rural Electricity Co-operative  
**Student:** Kaushick V S  
**Register Number:** 1912260163  
**Marks:** 3

## 1. Objective

Define tariff values in one place so that the billing program does not repeat values throughout its formulas. This makes tariff maintenance easier and reduces the risk of updating one formula but missing another.

## 2. Constants required by the assignment

All monetary rates are stored as integer paise to avoid floating-point rounding errors.

| Name | Value | Meaning |
|---|---:|---|
| `SLAB1_UNITS` | 100 | First slab limit |
| `SLAB2_UNITS` | 200 | Second slab limit |
| `RATE1_PAISE` | 0 | Rate for first 100 units |
| `RATE2_PAISE` | 225 | Rate for units 101–200 |
| `RATE3_PAISE` | 450 | Rate for units above 200 |
| `FIXED_CHARGE_PAISE` | 5000L | Fixed charge of ₹50.00 |

## 3. Difference between `#define`, `const`, and `enum`

### `#define`
A preprocessor macro. The preprocessor replaces the macro name with its replacement text before the compiler proper processes the source. It does not create a typed C variable.

Example:
```c
#define RATE2_PAISE 225
```
Use it for the assignment's tariff values that are centrally defined and may need to be revised.

### `const`
Declares an object that cannot be modified through that identifier after initialization.

Example:
```c
const int MAX_METER_UNITS = 65535;
```
Unlike a macro, it has a C type and follows C scope and type rules. A `const` object is not generally interchangeable with a preprocessor macro in every compile-time context.

### `enum`
Defines named integer constants, commonly used for a set of related integral choices.

Example:
```c
enum ConsumerCategory {
    DOMESTIC = 1,
    COMMERCIAL = 2
};
```
An enum is suitable for named categories or states, not for fractional values or arbitrary monetary calculations.

## 4. Slab billing logic

The function `compute_bill(int units)` returns the total bill in paise, including the fixed charge.

- First 100 units: 0 paise per unit.
- Units 101–200: 225 paise per unit.
- Units above 200: 450 paise per unit.
- Fixed charge: 5000 paise.

For 350 units:

- First slab: 100 × 0 = 0 paise.
- Second slab: 100 × 225 = 22,500 paise.
- Third slab: 150 × 450 = 67,500 paise.
- Energy charge = 90,000 paise = ₹900.00.
- Fixed charge = 5,000 paise = ₹50.00.
- Total = 95,000 paise = ₹950.00.

## 5. Required test cases

| Units | Energy charge | Fixed charge | Total bill |
|---:|---:|---:|---:|
| 0 | ₹0.00 | ₹50.00 | ₹50.00 |
| 100 | ₹0.00 | ₹50.00 | ₹50.00 |
| 150 | ₹112.50 | ₹50.00 | ₹162.50 |
| 200 | ₹225.00 | ₹50.00 | ₹275.00 |
| 350 | ₹900.00 | ₹50.00 | ₹950.00 |

The program also checks negative units and reports them as invalid.

## 6. Tariff revision experiment

Change:
```c
#define RATE2_PAISE 225
```
to:
```c
#define RATE2_PAISE 230
```
Then recompile and rerun. Expected revised totals:

| Units | Revised total |
|---:|---:|
| 0 | ₹50.00 |
| 100 | ₹50.00 |
| 150 | ₹165.00 |
| 200 | ₹280.00 |
| 350 | ₹955.00 |

Only the macro definition needs to change; the billing formulas remain unchanged. This demonstrates centralized tariff maintenance.

## 7. Complexity

The billing function uses a fixed number of slab checks and arithmetic operations. Therefore, its time complexity is **O(1)** and its auxiliary space complexity is **O(1)**.

## 8. Conclusion

The program uses `#define` for the tariff values required by the assignment, `const` for a typed read-only limit, and `enum` for named consumer categories. Storing money in paise and centralizing tariff values improves calculation accuracy and maintainability.

### Actual revised-build verification
A separate copy, `task03_rate_revision.c`, was compiled after changing `RATE2_PAISE` to 230. Its execution output is saved in `tariff_revision_output.txt`. This is a separate build, not merely a printed prediction.
