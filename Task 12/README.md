# Task 12 – Re-evaluate and Adapt the Design

## Title
Smart Meter Billing Redesign for 15-Minute Watt-Hour Readings and Time-of-Day Tariffs

## A. Impact Analysis

The original design used a 16-bit unsigned meter register and compile-time tariff macros. The changed
requirement introduces:

1. Smart-meter readings every 15 minutes: 35,040 readings per house per year.
2. Readings are in watt-hours (Wh), so the meter value is finer-grained than the original unit/kWh reading.
3. A 6 PM–10 PM peak period with a 20% higher tariff.
4. Tariff values must be changed without recompiling.

The original 16-bit register is no longer a suitable long-lived Wh counter. Its maximum is 65,535 Wh,
so it represents only 65.535 kWh before a wrap. For example, at an average 10 kWh/day, that capacity
would be exhausted in about 6.55 days. The exact number of days depends on actual consumption.

For annual accumulation, even if every 15-minute interval were as large as 65,535 Wh, one house could
accumulate:

35,040 × 65,535 Wh = 2,296,346,400 Wh

This is greater than INT_MAX (2,147,483,647), so a signed 32-bit int is insufficient for that worst-case
annual sum. A 64-bit unsigned integer provides a much larger working range.

The original #define tariff values are also no longer appropriate because the board requires tariff
changes without recompilation.

## B. Evaluation of the Original Design

### Original design that can be retained
- Integer paise for money remains appropriate because it avoids floating-point money errors.
- Fixed-width/explicitly sized integer reasoning remains important.
- Input validation remains necessary.
- Slab-based billing logic remains conceptually useful.

### Original design that must change
- `unsigned short` meter type -> 64-bit unsigned Wh type.
- Compile-time tariff `#define` values -> runtime configuration structure loaded from `tariff.conf`.
- Single fixed-rate billing -> interval-aware time-of-day tariff engine.
- Unit-only arithmetic -> Wh-to-kWh tariff calculation.

## C. Adaptation / Redesign

The supplied program in `src/task12_smart_meter.c` implements the redesign.

### Data design
- `uint64_t` stores cumulative watt-hour readings.
- `uint64_t` stores energy totals and paise totals.
- `Tariff` structure stores all tariff values at runtime.
- `Reading` structure stores a 15-minute interval reading and its timestamp.

### Runtime tariff configuration
`tariff.conf` contains:
- first slab boundary
- second slab boundary
- rates in paise/kWh
- fixed charge in paise
- peak surcharge percentage

Changing these values changes the next execution without recompiling.

### Peak-hour engine
Peak is active for:
- 18:00 inclusive
- before 22:00

Thus 18:00–21:45 interval readings receive the 20% surcharge.

### Rounding
The program performs energy charging using an integer numerator in paise×Wh and converts the final
result to paise with half-up rounding. This avoids using floating-point rupees for the monetary
calculation.

## D. Evidence-Based Defence

The redesign is justified by the following measurements:

| Quantity | Result | Design consequence |
|---|---:|---|
| 16-bit maximum Wh reading | 65,535 Wh | Too small for a long-lived cumulative Wh counter |
| Equivalent energy | 65.535 kWh | Only a small amount of cumulative capacity |
| Readings/year/house | 35,040 | Much higher processing frequency |
| Worst-case annual sum | 2,296,346,400 Wh | Exceeds signed 32-bit INT_MAX |
| 800,000 houses × 35,040 readings | 28,032,000,000 readings/year | Requires efficient O(1) interval processing |
| Peak surcharge | 20% | Requires runtime time-of-day logic |

### Complexity
For N interval readings:
- Time: O(N)
- Extra memory: O(1) apart from the input line buffer and tariff structure.
- Each interval performs a fixed number of arithmetic operations.

### Trade-offs
The 64-bit design uses more memory than a 16-bit reading, but the memory cost is tiny for one
record and the much larger range is required by the new specification.

Runtime configuration adds startup parsing time proportional to the number of tariff parameters, O(t),
and O(t) storage for the tariff configuration. In exchange, a tariff revision does not require
recompilation or redistribution of the executable.

The redesigned solution is therefore a MODIFY -> REDESIGN hybrid:
- retain integer-money and slab concepts,
- widen meter/accumulator types,
- move tariff data to runtime configuration,
- add time-of-day billing.

## Test cases

### Test 1 – Normal interval
Input:
`0 50000 17:45`

Expected consumption: 50,000 Wh = 50 kWh.
The first 50 kWh is in the free slab, so the energy charge is Rs 0.00.

### Test 2 – Peak interval
Input:
`50000 150000 18:00`

Consumption: 100 kWh. It is peak time, so the rate for the applicable paid slab is increased by 20%.
Because the cumulative total moves from 50 kWh to 150 kWh, 50 kWh enters the second slab.

### Test 3 – Peak boundary at 22:00
Input:
`150000 160000 22:00`

Consumption: 10 kWh. 22:00 is outside the peak period, so the normal tariff applies.

### Test 4 – 64-bit scale
The C type is `uint64_t`; the program accepts values far above 65,535 Wh, demonstrating that the
original 16-bit limitation is removed.

### Test 5 – Runtime tariff revision
Change `PEAK_PERCENT 20` to another percentage in `tariff.conf`, then rerun the same executable.
No recompilation is required.

## Compile and run

GCC command:

```bash
gcc -std=c11 -Wall -Wextra -pedantic src/task12_smart_meter.c -o task12_smart_meter
```

Run:

```bash
./task12_smart_meter < tests/sample_input.txt
```

## Important assumption

The assignment specifies the 15-minute Wh readings and the peak window, but it does not specify an
actual household load profile or whether the meter register itself wraps. The implementation therefore
treats the 64-bit reading as a cumulative counter and uses unsigned subtraction, while the report uses
the 16-bit capacity calculation only to demonstrate why the original type is inadequate.

The assignment also does not specify a different peak tariff table, so the original tariff rates are
retained and a configurable 20% surcharge is applied during peak intervals.
