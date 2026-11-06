# Task 02 – Choose Appropriate Data Types

**Student:** Kaushick V S  
**Register Number:** 1912260163  
**Course:** CSA0224 – C Programming  
**Marks:** 4

## 1. Purpose of this task

This task selects C data types for the rural electricity billing system, checks their storage sizes and ranges, explains why money should not be stored as floating-point rupees, and implements the 16-bit meter rollover calculation without `if-else`.

## 2. Data type selection

| Data | Recommended type | Reason |
|---|---|---|
| Meter register reading | `uint16_t` (`meter_t`) | Represents exactly 0 through 65,535 when the exact-width type is provided by the implementation. |
| Household ID | `uint32_t` | Can represent at least 800,000 distinct positive IDs. |
| Consumption units | `uint32_t` | A non-negative integer result; wider than the meter register type. |
| Individual charge in paise | `int64_t` | Stores money as whole paise and provides a wide range for calculations. |
| District-level accumulated amount | `int64_t` or `uint64_t` after range analysis | A total across many households can exceed a 32-bit signed integer. |
| Category | `char` or an `enum` | A small set of category codes. |

`uint16_t`, `uint32_t`, and `int64_t` are exact-width types declared in `<stdint.h>`. They are available when the C implementation supports the corresponding exact widths. The program uses `sizeof()` to report actual storage sizes on the machine where it is compiled. Sizes of types such as `long`, `int`, `float`, and `double` can vary by platform; do not assume the Linux and Windows results are identical.

## 3. Limits and precision

The program prints useful limits from `<limits.h>` and precision information from `<float.h>`, including `UINT16_MAX`, `INT_MAX`, `LLONG_MAX`, `FLT_DIG`, and `DBL_DIG`.

For a 16-bit unsigned meter register:

\[
0 \leq reading \leq 2^{16}-1 = 65535
\]

## 4. Why money should be stored as integer paise

Decimal fractions such as 0.01 cannot generally be represented exactly in binary floating-point. Repeated floating-point additions can therefore accumulate a small representation error. The C demonstration adds `0.01f` rupees 4,000 times and compares the result with an exact integer-paise total:

- Floating-point demonstration: approximately ₹39.999294281.
- Integer representation: 4,000 paise = exactly ₹40.00.

This is a precision demonstration using one-paise increments; it is not a substitute for calculating the actual tariff slabs. For billing, convert tariff amounts to paise (for example, ₹2.25 = 225 paise) and perform the monetary calculations using integer types. Use a sufficiently wide type for accumulated totals.

## 5. 16-bit meter rollover – required TODO implementation

A 16-bit unsigned meter has 65,536 possible values: 0 to 65,535. If the register reaches 65,535 and then increments, it wraps to 0. For one rollover, the consumption is:

\[
consumption = (65536 - previous) + current
\]

The required function is implemented without `if-else`:

```c
typedef uint16_t meter_t;

meter_t consumption(meter_t previous, meter_t current)
{
    return (meter_t)(current - previous);
}
```

The subtraction is converted back to `meter_t`. Conversion to an unsigned 16-bit type gives the result modulo 65,536, which handles the single-wrap case without a conditional branch. This assumes no more than one complete register cycle occurred between readings, consistent with the assignment's meter model.

### Required test cases

| Previous | Current | Expected consumption | Explanation |
|---:|---:|---:|---|
| 1,200 | 1,530 | 330 | Normal reading |
| 65,400 | 120 | 256 | (65,536 − 65,400) + 120 |

## 6. Build and test

Compile with warnings enabled:

```sh
gcc -Wall -Wextra -std=c11 Task02/task02.c -o Task02/task02
```

Run:

```sh
./Task02/task02
```

The program reports `sizeof(meter_t) = 2` and `UINT16_MAX = 65535` on the tested system, produces 330 units for the normal test, and 256 units for the rollover test. It also displays the floating-point versus integer-paise comparison.

## 7. Conclusion

Use an exact 16-bit unsigned type for the physical meter register, a wider integer type for household identifiers and consumption, and integer paise with a 64-bit accumulator for money. The modulo conversion in `consumption()` correctly handles the assignment's one-rollover example without `if-else`. Always check `sizeof()` and limits on the target compiler because some C type sizes are implementation-dependent.
