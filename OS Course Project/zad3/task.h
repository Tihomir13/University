#ifndef TASK_H
#define TASK_H

#include <ucontext.h>

typedef struct task_t {
    ucontext_t context;
    void (*func)();
    int id;
    struct task_t *next;
    struct task_t *prev;
} task_t;

#endif // TASK_H
