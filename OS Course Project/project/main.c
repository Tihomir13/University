#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "clock.h"
#include "task.h"
#include "queue.h"

// Функции на задачите
void taskFunc1() {
    while (1) {
        printf("+\n");
    }
}

void taskFunc2() {
    while (1) {
        printf("-\n");
    }
}

void taskFunc3() {
    while (1) {
        printf("!\n");
    }
}

int main() {
    // Инициализиране на опашката
    TaskQueue taskQueue = {NULL};

    // Създаване на задачи
    ucontext_t mainContext;
    createTask(&taskQueue, taskFunc1, 1, &mainContext);
    createTask(&taskQueue, taskFunc2, 2, &mainContext);
    createTask(&taskQueue, taskFunc3, 3, &mainContext);

    // Настройка на виртуалния часовник
    setup_clock(&taskQueue);

    // Главен цикъл
    while (1) {
        pause(); // Изчакване на сигнал
    }

    return 0;
}
