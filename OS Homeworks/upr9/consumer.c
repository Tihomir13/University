#include <stdio.h>
#include <shared.h>

typedef struct shared_mem {
    volatile char counter;
    volatile int lock;
    volatile int lock1;
} memory;

int main() {
    memory *data;
    int i, value;

    data = (memory *)getmem(1322);

    for (i = 97; i <= 122; i++) {
        while (testandset(&(data->lock)));

        value = (char)data->counter;

        printf("%c\n", (char)value);

        data->lock1 = 0;
        for(int k = 0; k < 1000000; k++);
    }

    return 0;
}