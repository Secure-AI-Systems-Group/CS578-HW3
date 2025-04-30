#include <stdio.h>
#include "ops.h"

int main(void) {
    int a = 5;
    int b = 10;
    int sum = mysum(a, b);
    printf("The sum of %d and %d is %d\n", a, b, sum);
    return 0;
}
