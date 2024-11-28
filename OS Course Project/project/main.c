#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "clock.h"
#include "queue.h"

#define FIBER_STACK 1024 * 64

ucontext_t mainContext; // Контекст на главната програма
TaskQueue taskQueue;    // Опашка за задачите
task_t *RunningTask = NULL; // Текущо изпълняваща се задача

void createTask(TaskQueue *queue, void (*func)(), int id) {
    task_t *newTask = (task_t *)malloc(sizeof(task_t));
    newTask->func = func;
    newTask->id = id;

    getcontext(&newTask->context);
    newTask->context.uc_stack.ss_sp = malloc(FIBER_STACK);
    newTask->context.uc_stack.ss_size = FIBER_STACK;
    newTask->context.uc_link = &mainContext;

    makecontext(&newTask->context, func, 0);
    addElement(queue, newTask);
}

void taskFunc1() {
    while (1) {
        printf("+\n");
        swapcontext(&RunningTask->context, &mainContext);
    }
}

void taskFunc2() {
    while (1) {
        printf("-\n");
        swapcontext(&RunningTask->context, &mainContext);
    }
}

void taskFunc3() {
    while (1) {
        printf("!\n");
        swapcontext(&RunningTask->context, &mainContext);
    }
}

int main() {
    setup_clock();

    taskQueue.head = NULL;
    taskQueue.tail = NULL;

    createTask(&taskQueue, taskFunc1, 1);
    createTask(&taskQueue, taskFunc2, 2);
    createTask(&taskQueue, taskFunc3, 3);

    while (1) {
        if (RunningTask != NULL) {
            addElement(&taskQueue, RunningTask);
        }

        RunningTask = getFirstElement(&taskQueue);

        if (RunningTask != NULL) {
            swapcontext(&mainContext, &RunningTask->context);
        }
    }

    return 0;
}
