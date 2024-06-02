#include <stdio.h>

void enterNumbers(int numbers[]);
int* sort(int numbers[], int length);
void printNumbers(int numbers[]);

int main() {
    int numbers[10];
    int length = sizeof(numbers) / sizeof(numbers[0]);

    enterNumbers(numbers);
    int* sortedNumbers = sort(numbers, length);
    printNumbers(sortedNumbers);
    return 0;
}