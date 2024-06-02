#include <stdio.h>
#include <shared.h>

int main() {

    char *buffer;
    buffer = (char *)getmem(1322);

    for (int i = 0; i < 26; i++) {
        *buffer = 'a' + i;
        for (int k = 0; k < 10000000; k++);
    }
    return 0;
}