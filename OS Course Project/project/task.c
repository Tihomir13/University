#include <stdlib.h>
#include <stdio.h>
#include "task.h"
#include "queue.h"

#define FIBER_STACK 1024 * 64

void createTask(TaskQueue *queue, void (*func)(), int id, ucontext_t *mainContext) {
    task_t *newTask = (task_t *)malloc(sizeof(task_t));
    if (!newTask) {
        perror("Failed to allocate memory for task");
        exit(EXIT_FAILURE);
    }

    // Allocate stack for the task
    newTask->context.uc_stack.ss_sp = malloc(FIBER_STACK);
    newTask->context.uc_stack.ss_size = FIBER_STACK;
    if (!newTask->context.uc_stack.ss_sp) {
        perror("Failed to allocate stack");
        free(newTask);
        exit(EXIT_FAILURE);
    }

    // Setup context
    getcontext(&newTask->context);
    newTask->context.uc_link = mainContext; // Return to main context after task ends
    makecontext(&newTask->context, func, 0);
    newTask->id = id;

    // Add task to queue
    addElement(queue, newTask);
}
