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

        for (int i = 97; i <= 122; i++) {
          PS(sem_con);
          printf("%c\n", *data2);
          VS(sem_uppCon);

        }

    sem_remove(sem_pro);
    sem_remove(sem_proUpp);
    sem_remove(sem_uppCon);
    sem_remove(sem_con);

    return 0;
}