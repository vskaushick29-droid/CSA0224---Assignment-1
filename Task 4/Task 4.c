#include <stdio.h>

#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define RUPEES_TO_PAISE(rs) ((rs) * 100L)

int main(void) {
    int a = 5;
    int b = 10;
    
    printf("SQUARE(%d) = %d\n", a + 1, SQUARE(a + 1));
    printf("MAX(%d, %d) = %d\n", a, b, MAX(a, b));
    printf("Rs 150.50 in paise = %ld\n", RUPEES_TO_PAISE(150L));
    
    return 0;
}
