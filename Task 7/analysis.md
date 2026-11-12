# Task 07 – Type Conversion and Precision

## 1. Implicit type conversion
C can automatically convert a value from one arithmetic type to another. For example:
```c
int count = 5;
double result = count;  /* int is converted to double */
```
The assignment converts the integer value to a floating-point representation. Conversions to a type with a smaller range or precision may lose information.

## 2. Integer division
When both operands are integers, division produces an integer result. The fractional part is discarded:
```c
int result = 7 / 2;  /* result is 3 */
```
Assigning that result to a `double` does not restore the discarded fraction. Use a floating-point operand or cast before division:
```c
double result = (double)7 / 2; /* 3.5 */
```
By contrast, `(double)(7 / 2)` first performs integer division and then converts 3 to 3.0.

## 3. Explicit casting and narrowing
A cast requests a conversion, such as `(double)whole`. It does not guarantee that the value is representable in the destination type.

The program converts `3000000000LL` to `int`. If the value is outside the range of `int`, the result is implementation-defined in C. It must not be assumed to wrap in a particular way. Check the destination range before narrowing in production code.

## 4. Three expressions that can surprise beginners
- `5 / 2` evaluates to `2`, because both operands are integers.
- `5 % 2` evaluates to `1`, the remainder after integer division.
- `x += 2 * 3` adds 6 to `x`, because multiplication has higher precedence than addition.

These are defined language rules, not compiler bugs.

## 5. Currency precision and rounding
Binary floating-point types cannot represent many decimal fractions exactly. Repeated calculations with `float` or `double` can accumulate small representation errors.

For currency, storing whole paise in an integer type is usually safer. For example, ₹162.50 is stored as 16250 paise. Display it using integer division and remainder:
```c
printf("Rs.%lld.%02lld", paise / 100, paise % 100);
```

If a decimal amount must be converted to paise, an explicit rounding policy is required. The program demonstrates `llround(amount_rupees * 100.0)`. A real billing system should define the legally/business-approved rounding rule and apply it consistently.

## 6. Float versus integer paise experiment
The program repeatedly adds ₹0.01 using `float` and separately adds exactly 1 integer paise. It compares totals at 4,000, 60,000, and 800,000 contributions. The float result may differ slightly from the exact integer-paise total; the measured error depends on the C implementation and floating-point arithmetic.

Integer paise provides exact addition as long as the chosen integer type does not overflow. For these experiment sizes, the exact total is at most 800,000 paise (₹8,000).

## 7. Time and space complexity
For `n` contributions, both accumulation loops take O(n) time. The float and integer accumulators each use a fixed amount of storage, so auxiliary space is O(1). Integer arithmetic is not automatically faster on every processor; the important benefit here is exact representation of whole paise within the selected range.

## 8. Recommendations
- Use integer paise (`long long`) for billing amounts and totals.
- Use floating-point types for measurements or calculations where approximation is acceptable, not as the authoritative stored currency value.
- Use explicit casts to make intended conversions clear.
- Check ranges before converting a large integer to a smaller type.
- Define and test a consistent rounding policy for any decimal-to-paise conversion.

## 9. Conclusion
Understanding integer division, implicit conversion, explicit casting, and floating-point precision prevents subtle billing errors. Integer paise is a simple and reliable representation for this tariff system when overflow limits are checked.
