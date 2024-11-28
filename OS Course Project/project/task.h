#ifndef TASK_H
#define TASK_H

#include <ucontext.h>

// Forward declaration на TaskQueue
struct TaskQueue;

typedef struct task_t {
    ucontext_t context;
    void (*func)();
    int id;
    struct task_t *next;
    struct task_t *prev;
} task_t;

// Декларация на функцията за създаване на задача
void createTask(struct TaskQueue *queue, void (*func)(), int id, ucontext_t *mainContext);

#endif // TASK_H
