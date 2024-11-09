#ifndef TASK_H
#define TASK_H

#include "descriptor.h"
#include <ucontext.h>

#define FIBER_STACK 1024 * 64

typedef struct tcb_t task_t;
struct tcb_t
{
    ucontext_t context;
    void (*func)(); // Функцията на задачата
    task_t *next;   // Указател към следващата задача в опашката
};

// Декларации на функциите
void createTask(void (*func)());
void task1();
void task2();
void task3();
void taskScheduler();
void switchTask();

// Глобални променливи за опашката на задачите
extern task_t *taskQueue;
extern task_t *RunningTask;

#endif // TASK_H
