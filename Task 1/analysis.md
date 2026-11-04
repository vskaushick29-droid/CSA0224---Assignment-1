# Task 01 – Understand the Problem and Identify the Data

**Student:** Kaushick V S  
**Register number:** 1912260163  
**Course:** CSA0224 – C Programming  
**Case study:** Grama Jyothi Rural Electricity Co-operative  
**Marks:** 4

## 1. Problem statement

Grama Jyothi prepares monthly electricity bills for households. The present spreadsheet-based process has risks involving floating-point rounding, 16-bit meter-register rollover, and tariff values being repeated in multiple formulas. The billing program must use meter readings and household details to calculate electricity consumption and the amount payable accurately.

The system is expected to grow from approximately 4,000 village households to 60,000 taluk households and 800,000 district households. The design should therefore consider both an individual bill and the memory and numeric range required when processing many bills.

## 2. Inputs, outputs and constants

| Item | Role | Meaning / example | Initial representation considered |
|---|---|---|---|
| `household_id` | Input | Unique household identifier, e.g. 1001 | `unsigned long` |
| `category` | Input | Household category, e.g. `D` for domestic | `char` |
| `previous_reading` | Input | Previous meter-register value | `unsigned short` for a 16-bit register |
| `current_reading` | Input | Current meter-register value | `unsigned short` for a 16-bit register |
| `units_consumed` | Calculated/output | Difference between readings, after rollover handling | `unsigned int` |
| `fixed_charge` | Output | Fixed charge, represented in paise | integer type; `long long` used in the demonstration |
| `energy_charge` | Output | Slab-based charge, represented in paise | integer type; `long long` used in the demonstration |
| `total_bill` | Output | Fixed charge plus energy charge, in paise | integer type; `long long` used in the demonstration |

Tariff constants supplied in the assignment:

| Constant | Value | Meaning |
|---|---:|---|
| `SLAB1_UNITS` | 100 units | First 100 units are free |
| `SLAB2_UNITS` | 200 units | Upper boundary of the second slab |
| `RATE1_PAISE` | 0 paise/unit | Rate for first 100 units |
| `RATE2_PAISE` | 225 paise/unit | Rate for units 101–200 (₹2.25/unit) |
| `RATE3_PAISE` | 450 paise/unit | Rate above 200 units (₹4.50/unit) |
| `FIXED_CHARGE_PAISE` | 5,000 paise | Fixed charge of ₹50.00 |

These are tariff configuration values for the stated assignment scenario. They should be defined centrally rather than copied into multiple calculations.

## 3. Values and data conditions to consider

- **Negative values:** A valid meter reading and a valid bill amount should not be negative. Negative readings should be rejected as invalid input. If the current 16-bit register value is less than the previous value, it may indicate register rollover; it must not automatically be treated as a negative consumption. The rollover calculation is implemented and tested in Task 2.
- **Fractional currency:** A tariff such as ₹2.25 contains paise. Storing rupee amounts in binary floating-point can introduce representation and rounding differences. Representing money as integer paise makes the stated tariff arithmetic exact for these values.
- **Large values:** The number of households can reach 800,000. Individual values and especially aggregate revenue must be checked against the selected type's range. A 64-bit accumulator such as `long long` is appropriate for large aggregate monetary totals; the exact required range should be calculated for the workload.
- **Meter limits:** A 16-bit unsigned register represents 0 through 65,535. The register rollover rule is addressed in Task 2. This task assumes a single rollover at most within the billing interval only as a design assumption to be checked against the meter-reading interval and maximum possible consumption.
- **Invalid input:** Non-numeric readings, readings outside the meter range, unknown categories and inconsistent records should be rejected or reported rather than silently billed.

## 4. Billing rules and invariants

For a valid bill, the following conditions should hold:

1. **Non-negative components:** fixed charge, energy charge and total bill are non-negative.
2. **Component sum:** `total_bill = fixed_charge + energy_charge` (all monetary values in the same unit, paise).
3. **Slab accounting:** every consumed unit is counted in exactly one tariff slab; no unit is omitted or counted twice.
4. **Monotonicity:** with the same tariff and fixed charge, a larger consumption must not produce a smaller bill.
5. **Meter rollover:** for a 16-bit register with one rollover, consumption is `(65536 - previous_reading) + current_reading` when the current reading is lower than the previous reading. Task 2 implements the required unsigned modular arithmetic.

## 5. Worked example: 330 units

Given previous reading = 1,200 and current reading = 1,530:

`units_consumed = 1530 - 1200 = 330 units`

| Slab | Units charged | Rate | Charge |
|---|---:|---:|---:|
| First 100 units | 100 | ₹0.00 | ₹0.00 |
| Next 100 units | 100 | ₹2.25 | ₹225.00 |
| Above 200 units | 130 | ₹4.50 | ₹585.00 |
| **Energy charge** | **330** | | **₹810.00** |
| Fixed charge | | | ₹50.00 |
| **Total bill** | | | **₹860.00** |

In paise: energy charge = `100 × 0 + 100 × 225 + 130 × 450 = 81,000 paise`; total = `81,000 + 5,000 = 86,000 paise`.

Invariant checks: ₹860.00 is non-negative, and ₹50.00 + ₹810.00 = ₹860.00.

## 6. Alternative concept: meter readings as strings or integers

A meter display or incoming text record might contain a reading such as `"01530"`. The same numerical value can be represented as integer `1530`.

| Comparison | Integer representation | String representation |
|---|---|---|
| Example | `unsigned short` value `1530` | character sequence `"01530"` |
| Leading zeros | Not retained as part of the numeric value | Preserved exactly |
| Arithmetic | Direct numeric operations | Must validate and convert (e.g. `strtoul`) before arithmetic |
| Time | Fixed-width integer arithmetic is O(1) | Parsing or character-by-character comparison is O(d), where d is the digit count |
| Storage | `sizeof(unsigned short)` on the target system | A minimal C string needs d+1 bytes including `\0`; a fixed `char[8]` field reserves 8 bytes |

For the demonstration's fixed `char[8]` representation, each reading uses 8 bytes, compared with 2 bytes for the `unsigned short` on the tested system. With two readings for 800,000 households:

- Integer storage: `800,000 × 2 × 2 = 3,200,000 bytes` (about 3.05 MiB).
- Fixed `char[8]` storage: `800,000 × 2 × 8 = 12,800,000 bytes` (about 12.21 MiB).

This comparison is specifically for the chosen fixed-size `char[8]` field. A minimally sized five-digit C string needs 6 bytes, not 8. Strings remain useful for preserving raw input and validating its format, but numeric integer storage is more convenient for meter arithmetic.

## 7. Demonstration program and memory layout

`task01.c` demonstrates the data items, prints `sizeof` and integer limits on the machine where it is compiled, calculates the 330-unit example using the stated slab tariff, checks billing invariants, and converts the example text readings using `strtoul`.

`memory_layout.png` is a conceptual field-size diagram for the input and output records. It shows field sizes separately; it does not claim exact structure offsets or padding, which are compiler/ABI dependent.

## 8. Build and run

From the directory containing this file:

```sh
gcc -Wall -Wextra -Wpedantic -std=c11 -O2 -o task01 task01.c
./task01
```

The included `output.png` is a terminal-style capture of the actual output produced by the included source using GCC 14.2.0 in the current Linux environment. The actual `sizeof` values are platform-dependent. On this run, `unsigned long` and `long long` are 8 bytes; on 64-bit Windows/MSYS2 UCRT64, `unsigned long` is commonly 4 bytes. Do not copy one platform's sizes as universal C guarantees; use the values printed by the compiler environment used for submission.

## 9. Task 1 conclusion

The billing problem's inputs, outputs, tariff constants, invalid/edge values and invariants have been identified. The worked tariff calculation is consistent with the assignment, and the alternative string-versus-integer representation has been compared in time and memory terms. The demonstration program provides executable evidence for the worked example and invariant checks. Detailed rollover implementation, data-type selection for the complete system, and further validation are developed in later tasks.
