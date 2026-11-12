# Task 06 – Input and Output in C

## 1. Common format specifiers

| Format | Data type / purpose |
|---|---|
| `%d` | `int` |
| `%u` | `unsigned int` |
| `%ld` | `long` |
| `%lld` | `long long` |
| `%f` | `float` when printing; `double` when reading with `scanf` |
| `%lf` | `double` when reading with `scanf` |
| `%c` | character |
| `%s` | character string |
| `%zu` | `size_t` |

For `printf`, a `float` argument is promoted to `double`, so `%f` is used to print both `float` and `double`. For `scanf`, `%f` expects `float *`, while `%lf` expects `double *`.

## 2. Wrong format specifier example
Using `printf("%d", a_long_long_value)` is incorrect because `%d` expects an `int`, not a `long long`. The correct specifier is `%lld`. A mismatched variadic format specifier causes undefined behavior; it is not guaranteed to print a merely incorrect value.

## 3. Checking scanf return value
The program reads one integer with `scanf("%d", &units)`. It checks whether the return value is exactly `1`, meaning one conversion succeeded. If the input is text such as `abc`, conversion fails and the program reports invalid input. It also clears the rest of that input line before continuing/exiting.

## 4. Printing rupees and paise
The billing calculation stores money as integer paise. To display it as rupees and paise:
```c
printf("Rs.%lld.%02lld", bill_paise / 100, bill_paise % 100);
```
For example, 16250 paise is displayed as `Rs.162.50`. `%02lld` ensures the paise part has two digits, including a leading zero when needed.

## 5. Alternative: fgets + strtol
`fgets()` reads a complete line into a bounded character array. `strtol()` converts the numeric portion and provides an end pointer, allowing the program to detect empty input, trailing characters, and out-of-range values. The implementation checks `errno`, the end pointer, and the allowed range.

Example:
```c
char buffer[100];
if (fgets(buffer, sizeof buffer, stdin) != NULL) {
    char *end;
    long value = strtol(buffer, &end, 10);
    /* Check that conversion occurred, no range error occurred,
       and only whitespace remains after the number. */
}
```

## 6. Buffer size and complexity
For a buffer of `B` characters, `fgets()` stores at most `B - 1` input characters plus the terminating null character. A 100-byte buffer is sufficient for a short integer entry, but a production program should detect whether a line was truncated if longer input is possible.

Reading and validating a line of length `L` takes O(L) time. The buffer uses O(B) memory. With a fixed-size buffer, this is constant auxiliary memory.

## 7. Invalid input recovery
After a failed `scanf`, the invalid characters can remain in the input stream. Repeating the same `scanf` without consuming them can cause repeated failures. The example consumes the remainder of the line. For a more robust interactive application, line-based input using `fgets()` and `strtol()` is generally easier to validate and recover from.

## 8. Test observations
- Input `150` is accepted and produces a bill of Rs.162.50.
- Input `abc` is rejected because it is not an integer.
- Negative units are rejected.
- The line-parser demonstration accepts `150` and rejects `abc`, `-10`, and `200 units`.

## 9. Conclusion
Correct format specifiers are essential for reliable C input/output. Checking `scanf`'s return value prevents invalid input from being treated as valid. Integer paise avoids floating-point currency formatting errors, and `fgets()` with `strtol()` provides stronger control over line validation.
