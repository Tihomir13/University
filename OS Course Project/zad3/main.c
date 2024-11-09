#include "task.h"
#include <stdio.h>

int main() {
    // Създаване на задачи
    createTask(task1);
    createTask(task2);
    createTask(task3);

    RunningTask = taskQueue->next;  // Започваме с първата задача в опашката

    // Запускане на планировчика за задачи (безкраен цикъл)
    taskScheduler();

    return 0;
}

//gcc -o program main.c task.c -Wall