#include <stdio.h>

void enterNumbers(int numbers[]) {
    printf("Enter 10 numbers:\n");
    for (int i = 0; i < 10; i++) {
        printf("Enter %d: ", i+1);
        scanf("%d", &numbers[i]);
    }
}