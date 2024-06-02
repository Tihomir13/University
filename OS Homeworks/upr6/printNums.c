#include <stdio.h>

void printNumbers(int numbers[]) {
    printf("Sorted numbers are:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
}