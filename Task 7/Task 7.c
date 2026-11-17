#include <stdio.h>

int main(void) {
    int units = 150;
    int rate = 225;
    
    double surprise1 = units / 100 * rate;
    double surprise2 = (double)units / 100 * rate;
    long large_val = 3000000000L;
    int cast_val = (int)large_val;

    printf("Surprise 1 (integer division trap): %.2f\n", surprise1);
    printf("Surprise 2 (with explicit casting): %.2f\n", surprise2);
    printf("Surprise 3 (overflow/truncation on cast): long=%ld -> int=%d\n", large_val, cast_val);

    return 0;
}
