#include <stdio.h>
#include <shared.h>

int main() {

        char* data;
        sem_t sem_pro, sem_con;
        data = (char *)getmem(1322);
        sem_pro = sem_init(2322);
        sem_con = sem_init(3322);

    for (char i = 97; i <= 122; i++) {
        PS(sem_pro);
        *data = i;
        VS(sem_con);

    }

    return 0;
}