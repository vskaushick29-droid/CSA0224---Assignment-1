# Task 10 – Compare Expectations with Execution

## Objective
Compare the expected behaviour of the billing design with measured results at village,
taluk and district scale.

## Experiment
A deterministic load of **350 units per household** is used for all three scales so that
the comparison is reproducible.

For 350 units:
- first 100 units = free
- next 100 units = 100 × Rs 2.25 = Rs 225
- remaining 150 units = 150 × Rs 4.50 = Rs 675
- energy = Rs 900
- fixed = Rs 50
- total = **Rs 950.00 per bill = 95,000 paise**

Therefore:
- 4,000 bills = Rs 3,800,000.00 = 380,000,000 paise
- 60,000 bills = Rs 57,000,000.00 = 5,700,000,000 paise
- 800,000 bills = Rs 760,000,000.00 = 76,000,000,000 paise

## Expected vs observed

The `float`, `double`, and integer-paise calculations are compared by the program.
Because the test bill is an exact two-decimal monetary value and the scale is below the
precision limit of `double`, the `double` result is expected to agree with the paise result
for these totals. `float` may show representation/accumulation differences because it has
only about 6–7 decimal digits of precision.

### Integer overflow
At district scale the total is 76,000,000,000 paise.

- Signed 32-bit `int` maximum: 2,147,483,647 paise.
- Therefore the district total **overflows a signed 32-bit int**.
- A 64-bit `long long` easily holds 76 billion paise.

On common 64-bit Linux/GCC systems, `long` is 64-bit; on Windows LLP64, `long` is
typically 32-bit. The program prints the actual `sizeof` and range on the execution system
instead of assuming one ABI.

## Standard minimum sizes
The C standard guarantees minimum ranges, not one universal byte size for every type.
`sizeof` and limits printed by the program show the actual implementation.

## Double alternative
A `double` has about 15–16 decimal digits of precision on typical IEEE-754 systems.
The district total is far below that magnitude, so a `double` can represent the district
total with sufficient practical precision here. However, integer paise remains preferable
for financial correctness because each addition is an exact integer operation and there
is no binary floating-point rounding.

### Complexity
For `N` bills:
- Time: O(N) additions.
- Paise accumulator: O(1) extra space.
- Double accumulator: O(1) extra space.
- Per-variable storage is normally 8 bytes for both `long long` and `double`, but
  exact sizes are confirmed by `sizeof` in the execution output.

## Files
- `task10_expectation_execution.c` – experiment source
- `experiment_output.txt` – actual GCC execution
- `type_sizes.txt` – type-size/range evidence
- `comparison.csv` – scale comparison
- `analysis.txt` – written interpretation
- `commands.txt` – exact build/run commands
