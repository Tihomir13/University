#include <shared.h>

int main(){
        char* data;
        sem_t sem_pro;
        sem_t sem_con;

        data = (char *)getmem(1322);

        sem_pro = sem_init(2322);
        sem_con = sem_init(3322);

        sem_set (sem_pro, 1);
        sem_set (sem_con, 0);
}