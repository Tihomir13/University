#include <shared.h>

int main(){

        char* data1;
        char* data2;
        sem_t sem_pro;
        sem_t sem_proUpp;
        sem_t sem_uppCon;
        sem_t sem_con;

        data1 = (char *)getmem(1322);
        data2 = (char *)getmem(2322);

        sem_pro = sem_init(3322);
        sem_proUpp = sem_init(4322);
        sem_uppCon = sem_init(5322);
        sem_con = sem_init(6322);


        sem_set (sem_pro, 1);
        sem_set (sem_proUpp, 0);
        sem_set (sem_uppCon, 1);
        sem_set (sem_con, 0);
}