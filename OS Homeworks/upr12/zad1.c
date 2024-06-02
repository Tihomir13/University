#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

char letter;
pthread_mutex_t mu;
sem_t sem_send;
sem_t sem_print;

void* sending(void* arg) {
    for (int i = 'a'; i <= 'z'; i++) {
        sem_wait(&sem_send);
        pthread_mutex_lock(&mu);
        letter = (char)i;
        pthread_mutex_unlock(&mu);
        sem_post(&sem_print);
    }
}

void* printing(void* arg) {
    for (int i = 'a'; i <= 'z'; i++) {
        sem_wait(&sem_print);
        pthread_mutex_lock(&mu);
        printf("%c\n", letter);
        pthread_mutex_unlock(&mu);
        sem_post(&sem_send);
    }
}

int main(int argc, char* argv[]) {
    pthread_t t1, t2;

    pthread_mutex_init(&mu, NULL);
    sem_init(&sem_send, 0, 1);
    sem_init(&sem_print, 0, 0);

    pthread_create(&t1, NULL, sending, NULL);
    pthread_create(&t2, NULL, printing, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mu);
    sem_destroy(&sem_send);
    sem_destroy(&sem_print);
    pthread_exit(NULL);

    return 0;
}