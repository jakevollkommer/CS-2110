#include<stdio.h>

int factorial(int n);

#define FACT_FORMAT "fact(%d) == %d == 0x%x\n"

void main() {
    printf(FACT_FORMAT, 1, factorial(1), factorial(1));
    printf(FACT_FORMAT, 2, factorial(2), factorial(2));
    printf(FACT_FORMAT, 5, factorial(5), factorial(5));
    printf(FACT_FORMAT, 1, factorial(7), factorial(7));
}

int factorial(int n) {
    if (n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

