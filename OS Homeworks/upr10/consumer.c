#include <stdio.h>
#include <shared.h>

int main() {
        char* data;
        sem_t sem_pro, sem_con;
        data = (char *)getmem(1322);
        sem_pro = sem_init(2322);
        sem_con = sem_init(3322);

        for (int i = 97; i <= 122; i++) {
          PS(sem_con);
          printf("%c\n", *data);
          VS(sem_pro);

        }

    sem_remove(sem_pro);
    sem_remove(sem_con);

    return 0;
}