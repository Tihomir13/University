#include <stdio.h>

int* sort(int numbers[], int length) {
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (numbers[i] < numbers[j]) {
                int temp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = temp;
            }
        }
    }
    return numbers;
}