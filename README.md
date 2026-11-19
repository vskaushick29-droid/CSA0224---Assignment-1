# CSA02 - C Programming: Assignment 1

**Design, Implement and Validate a Reliable Billing Program for a Rural Electricity Co-operative (Grama Jyothi)**

## Student Details

* **Student Name:** Kaushick V S

* **Register Number:** 1912260163

* **Course Code:** CSA02 – C Programming (CO1)

* **Institution:** Saveetha Institute of Medical and Technical Sciences (SIMATS)

## Compiler & Environment Details

* **Compiler:** GCC (MinGW-w64 / TDM-GCC)

* **Compiler Version:** GCC 13.2.0 (or your installed version; verify via `gcc --version`)

* **C Standard:** C99 / C11

## Compilation & Execution Instructions

### Exact GCC Compilation Command

To compile any task with all standard warnings enabled, navigate to the respective task folder (`Task01` through `Task12`) and run:

```
gcc -Wall -Wextra -std=c99 <source_file>.c -o <executable_name>

```

*(Note: For **Task 5**, compile with `-DDEBUG` to enable diagnostic debug output:)*

```
gcc -Wall -Wextra -std=c99 -DDEBUG Task05_HeaderAndDebug.c -o Task05

```

### Steps to Execute Each Program

1. Open your terminal or command prompt and navigate to the task directory:

   ```
   cd Task01
   
   ```

2. Compile the `.c` file using the GCC command shown above.

3. Run the compiled executable:

   * **On Windows:**

     ```
     Task01.exe
     
     ```

   * **On Linux / macOS:**

     ```
     ./Task01
     
     ```

## Repository Structure & Task Results Summary

Each task is organized into its own dedicated folder (`Task01` to `Task12`) containing the C source code, sample input files (where applicable), and execution output screenshots.

| Folder | Source File | Short Explanation of Result | 
| ----- | ----- | ----- | 
| **Task01** | `Task01_ProblemAnalysis.c` | Successfully modeled household billing records using structures and validated inputs, outputs, constants, and non-negativity rules. | 
| **Task02** | `Task02_DataTypes.c` | Verified `unsigned short` (2 bytes, max `65535`) meter rollover arithmetic (`65400` to `120` = `256` units) without `if-else` branching and eliminated floating-point drift by storing currency in integer paise. | 
| **Task03** | `Task03_Constants.c` | Centralized slab thresholds and tariff rates using `#define` macros, ensuring consistent bill calculations across all consumption slabs and verifying easy single-point tariff updates. | 
| **Task04** | `Task04_Macros.c` | Implemented fully parenthesized macros (`SQUARE`, `MAX`, `RUPEES_TO_PAISE`) and verified safe token expansion via `gcc -E` to prevent operator precedence bugs. | 
| **Task05** | `Task05_HeaderAndDebug.c` | Structured constants and prototypes cleanly and implemented conditional compilation (`#ifdef DEBUG`) to toggle intermediate billing logs without runtime overhead in production. | 
| **Task06** | `Task06_FormattedIO.c` | Implemented interactive input handling using `scanf` return-value validation to reject invalid non-numeric inputs and formatted integer paise cleanly as `Rs X.XX`. | 
| **Task07** | `Task07_TypeConversion.c` | Demonstrated and resolved three type-conversion pitfalls: integer division truncation, implicit promotion, and narrowing cast overflow (`long` to `int`). | 
| **Task08** | `Task08_Compilation.c` | Traced all four compilation stages (`-E` preprocessing, `-S` assembly, `-c` object generation, and linking) and resolved compiler warnings under `-Wall -Wextra`. | 
| **Task09** | `Task09_BillingProgram.c` | Executed the complete billing engine across zero-unit, slab boundary (`100`, `200`, `350` units), and meter rollover (`65400` to `120`) test cases, matching expected outputs 100%. | 
| **Task10** | `Task10_ScaleComparison.c` | Benchmarked village (`4,000`), taluk (`60,000`), and district (`800,000`) scales, proving `long long` paise accumulators prevent both 32-bit overflow and `double` precision drift. | 
| **Task11** | `Task11_FinalRecommendation.c` | Validated the final recommended architecture (`uint16_t` meter readings + `long`/`long long` paise currency + centralized macros) across district-level revenue aggregations. | 
| **Task12** | `Task12_SmartMeterDesign.c` | **Day-4 Design Challenge:** Redesigned the billing system for 15-minute smart meter watt-hour intervals (`35,040` readings/year), runtime-configurable tariffs (`TariffConfig`), 64-bit accumulators, and a 20% peak-hour surcharge (6 PM – 10 PM). | 
