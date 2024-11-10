#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "queue.h"
#include "task.h"

#define FIBER_STACK 1024 * 64

ucontext_t mainContext;
TaskQueue taskQueue;
task_t *RunningTask = NULL;

void createTask(void (*func)(), int id)
{
    task_t *newTask = (task_t *)malloc(sizeof(task_t));
    if (newTask == NULL)
    {
        perror("Failed to allocate memory for new task");
        exit(1);
    }

    // Allocate stack for the task
    newTask->context.uc_stack.ss_sp = malloc(FIBER_STACK);
    newTask->context.uc_stack.ss_size = FIBER_STACK;
    if (newTask->context.uc_stack.ss_sp == NULL)
    {
        perror("Failed to allocate stack for task");
        free(newTask);
        exit(1);
    }

    // Setup task context
    getcontext(&newTask->context);
    newTask->context.uc_link = &mainContext; // Return to main if the task completes
    makecontext(&newTask->context, func, 0);
    newTask->id = id;

    // Add task to the queue
    addElement(&taskQueue, newTask);
}

void taskFunc1()
{
    while (1)
    {
        printf("+\n");
        swapcontext(&RunningTask->context, &mainContext);
    }
}

void taskFunc2()
{
    while (1)
    {
        printf("-\n");
        swapcontext(&RunningTask->context, &mainContext);
    }
}

void taskFunc3()
{
    while (1)
    {
        printf("!\n");
        swapcontext(&RunningTask->context, &mainContext);
    }
}

int main()
{
    // Initialize the task queue
    taskQueue.head = NULL;
    taskQueue.tail = NULL;

    // Create tasks with different functions
    createTask(taskFunc1, 1);
    createTask(taskFunc2, 2);
    createTask(taskFunc3, 3);

    // Infinite loop to schedule tasks
    while (1)
    {
        // Add the current RunningTask to the end of the queue
        if (RunningTask != NULL)
        {
            addElement(&taskQueue, RunningTask);
        }

        // Get the next task from the front of the queue
        RunningTask = getFirstElement(&taskQueue);

        // Switch to the next task context
        if (RunningTask != NULL)
        {
            swapcontext(&mainContext, &RunningTask->context);
        }
    }

    // Free task resources (although unreachable in this loop)
    task_t *temp;
    while ((temp = getFirstElement(&taskQueue)) != NULL)
    {
        free(temp->context.uc_stack.ss_sp);
        free(temp);
    }

    return 0;
}
