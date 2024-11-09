#include "task.h"
#include <stdio.h>
#include <stdlib.h>

task_t *taskQueue = NULL;  // Опашка от задачи
task_t *RunningTask = NULL; // Текуща задача

// Функция за създаване на задача
void createTask(void (*func)()) {
    task_t *newTask = (task_t *)malloc(sizeof(task_t));
    if (newTask == NULL) {
        perror("Неуспешно заделяне на памет за нова задача");
        exit(1);
    }

    getcontext(&newTask->context);
    newTask->context.uc_stack.ss_sp = malloc(FIBER_STACK);
    newTask->context.uc_stack.ss_size = FIBER_STACK;
    newTask->context.uc_link = NULL;
    newTask->func = func;

    makecontext(&newTask->context, func, 0);

    // Добавяме задачата в опашката
    if (taskQueue == NULL) {
        taskQueue = newTask;
        newTask->next = newTask; // Оформяме цикличната опашка
    } else {
        newTask->next = taskQueue->next;
        taskQueue->next = newTask;
        taskQueue = newTask;
    }
}

// Функция за извеждане на символ "+"
void task1() {
    while (1) {
        printf("+\n");
        switchTask();  // Превключване на контекста към следващата задача
    }
}

// Функция за извеждане на символ "-"
void task2() {
    while (1) {
        printf("-\n");
        switchTask();  // Превключване на контекста към следващата задача
    }
}

// Функция за извеждане на символ "!"
void task3() {
    while (1) {
        printf("!\n");
        switchTask();  // Превключване на контекста към следващата задача
    }
}

// Функция за превключване на контекста между задачите
void switchTask() {
    task_t *nextTask = taskQueue->next;  // Извличаме следващата задача от опашката
    taskQueue = taskQueue->next;         // Преместваме taskQueue на следващата задача
    RunningTask = nextTask;              // Обновяваме текущата задача
    swapcontext(&taskQueue->context, &RunningTask->context);  // Превключваме контекста
}

// Основен планировчик на задачите
void taskScheduler() {
    while (1) {
        task_t *firstTask = taskQueue->next;
        taskQueue = taskQueue->next;
        RunningTask = firstTask;  // Превключваме към първата задача в опашката
        swapcontext(&taskQueue->context, &RunningTask->context); // Превключване към текущата задача
    }
}
