#include <stdio.h>
#include <shared.h>

int main() {

        char* data1;
        char* data2;
        sem_t sem_pro, sem_proUpp, sem_uppCon, sem_con;

        data1 = (char *)getmem(1322);
        data2 = (char *)getmem(2322);

        sem_pro = sem_init(3322);
        sem_proUpp = sem_init(4322);
        sem_uppCon = sem_init(5322);
        sem_con = sem_init(6322);

    for (char i = 97; i <= 122; i++) {
        PS(sem_pro);
        *data1 = (char)i;
        VS(sem_proUpp);

    }

    return 0;
}