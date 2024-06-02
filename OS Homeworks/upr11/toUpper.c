#include <stdio.h>
#include <shared.h>
#include <ctype.h>

int main() {

        char* data1;
        char* data2;
        char a;
        sem_t sem_pro, sem_proUpp, sem_uppCon, sem_con;

        data1 = (char *)getmem(1322);
        data2 = (char *)getmem(2322);

        sem_pro = sem_init(3322);
        sem_proUpp = sem_init(4322);
        sem_uppCon = sem_init(5322);
        sem_con = sem_init(6322);

    for (char i = 97; i <= 122; i++) {
        PS(sem_proUpp);
        a = toupper(*data1);
        VS(sem_pro);
        PS(sem_uppCon);
        *data2 = a;
        VS(sem_con);
    }

    return 0;
}