# Task 09 – Implement and Test the Billing Program

## Objective
Implement the complete Grama Jyothi electricity billing program and validate it against normal,
boundary, rollover, invalid-input, and hand-calculated cases.

## Tariff
- First 100 units: free
- Next 100 units: Rs 2.25/unit
- Above 200 units: Rs 4.50/unit
- Fixed charge: Rs 50.00

Money is stored as integer paise to avoid floating-point rounding errors.

## Rollover rule
The meter is a 16-bit unsigned register (0–65535). A decrease is treated as rollover only when
the previous reading is at least 65000 and the new reading is at most 1000. Other decreases are
rejected as invalid input.

For example:
65400 -> 120
= (65536 - 65400) + 120
= 256 units.

## Build
GCC:
```bash
gcc -std=c11 -Wall -Wextra -pedantic -o task09_billing task09_billing.c
```

## Run
```bash
./task09_billing
```

On Windows PowerShell:
```powershell
gcc -std=c11 -Wall -Wextra -pedantic -o task09_billing.exe task09_billing.c
.\task09_billing.exe
```

## Required test cases

| Test | Previous | Current | Expected units | Expected bill |
|---|---:|---:|---:|---:|
| Normal slab 1 | 1000 | 1000 | 0 | Rs 50.00 |
| Normal slab 2 | 1000 | 1150 | 150 | Rs 162.50 |
| Normal slab 3 | 1000 | 1350 | 350 | Rs 950.00 |
| Boundary 100 | 1000 | 1100 | 100 | Rs 50.00 |
| Boundary 200 | 1000 | 1200 | 200 | Rs 275.00 |
| Zero units | 5000 | 5000 | 0 | Rs 50.00 |
| Rollover | 65400 | 120 | 256 | Rs 527.00 |
| Invalid decrease | 3000 | 2500 | rejected | rejected |
| Invalid letters | abc | 1200 | rejected | rejected |
| Invalid negative | -10 | 1200 | rejected | rejected |

### Important correction
For 256 units:
- first 100 = Rs 0
- next 100 = 100 × Rs 2.25 = Rs 225
- remaining 56 = 56 × Rs 4.50 = Rs 252
- energy charge = Rs 477
- fixed charge = Rs 50
- total = **Rs 527.00**

## Five-bill hand calculation

1. 0 units → Rs 50.00
2. 100 units → Rs 50.00
3. 150 units → Rs 162.50
4. 200 units → Rs 275.00
5. 350 units → Rs 950.00

Total = **Rs 1,487.50**

## Alternative array-driven design

The fixed implementation uses a small, fixed number of slab tests. If limits and rates were
stored in arrays and processed by a loop over `s` slabs, each bill would take O(s) time and
O(s) configuration space. This is easier to modify when the tariff contains many slabs because
new slab entries can be added without rewriting the billing logic. The fixed design is simpler
and has effectively constant work because the current tariff has only three slabs.

## Evidence
`test_results.txt` contains the expected-vs-actual validation matrix.
`run_outputs.txt` contains representative successful and rejected runs.
`compile_output.txt` contains the GCC compilation result.
