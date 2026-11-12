# Task 11 – Recommend and Defend the Final Design

## Objective
Recommend and defend the final data types, constants and preprocessor strategy for the
Grama Jyothi billing system using evidence from Tasks 2, 9 and 10.

## Final recommendation

### 1. Meter readings
Use:
```c
typedef unsigned short meter_t;
```
The existing requirement is a 16-bit meter register. `unsigned short` represents the
non-negative meter range on the target implementation and is sufficient for 0–65535.
The rollover calculation explicitly handles the 65535 -> 0 boundary.

### 2. Money
Use:
```c
long long
```
for paise.

Money should not be stored as floating-point rupees. Integer paise gives exact arithmetic
and avoids binary floating-point rounding. Task 10 demonstrated that a signed 32-bit
`int` cannot safely hold the district-scale example of 76,000,000,000 paise, while a
64-bit `long long` can.

### 3. Tariff constants
Keep tariff values in one location:
- `SLAB1_UNITS`
- `SLAB2_UNITS`
- `RATE1_PAISE`
- `RATE2_PAISE`
- `RATE3_PAISE`
- `FIXED_CHARGE_PAISE`

`#define` is appropriate for these compile-time constants in this assignment because
the task explicitly studies preprocessor features and the values are not intended to
change during execution.

### 4. Tariff revision SOP
1. Open the single tariff-definition section.
2. Change the required rate/limit in paise.
3. Recompile the program.
4. Run the boundary test set: 0, 100, 150, 200, 350 units.
5. Run rollover test: 65400 -> 120.
6. Run the full regression test matrix.
7. Verify the expected output before redistributing the executable.

This prevents tariff values from being edited in multiple billing statements.

## District-scale defence

For the Task 10 representative case of 350 units:
- one bill = Rs 950.00 = 95,000 paise
- 800,000 bills = 76,000,000,000 paise
- this is greater than `INT_MAX = 2,147,483,647`
- the value fits comfortably in signed 64-bit `long long`

Thus the final money type remains correct at district scale for the tested design.

## Limitations

1. The 16-bit meter model is appropriate for the current register requirement but is not
   suitable for the later smart-meter requirement in Task 12, where readings are received
   every 15 minutes in watt-hours.
2. `#define` tariffs require recompilation after a revision.
3. The design assumes a valid 16-bit meter register and uses an explicit rollover pattern.
4. The fixed three-slab tariff is less flexible than a runtime configuration system.

## Alternative: runtime tariff configuration

Instead of compiling tariff values into the executable, a configuration file such as
`tariff.conf` could be read at startup.

If there are `t` tariff values:
- startup parsing: O(t)
- configuration storage: O(t)
- tariff revision: edit configuration and restart, without recompiling
- deployment: less need to rebuild and redistribute the executable

The trade-off is extra startup I/O, file validation, and the need to handle missing,
malformed, or inconsistent configuration values.

For the current assignment, compile-time constants are simpler and safer. For a production
system with frequent tariff revisions, runtime configuration is the more scalable design.

## Complexity

Billing a single bill uses a fixed number of slab calculations:
- Time: O(1)
- Extra working space: O(1)

For N bills:
- Time: O(N)
- Accumulator space: O(1)

## Evidence files

- `task11_final_design.c` – working demonstration
- `execution_output.txt` – GCC execution evidence
- `compile_output.txt` – warning/error evidence
- `design_specification.txt` – final engineering specification
- `tariff_revision_SOP.txt` – step-by-step revision procedure
- `configuration_analysis.txt` – runtime configuration comparison
- `commands.txt` – exact commands
