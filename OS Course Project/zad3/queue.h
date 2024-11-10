#ifndef QUEUE_H
#define QUEUE_H

#include "task.h" // Include task.h to use the task_t struct

typedef struct TaskQueue {
    task_t* head;
    task_t* tail;
} TaskQueue;

// Function declarations
void addElement(TaskQueue *queue, task_t *newTask);
task_t* getFirstElement(TaskQueue* queue);
void deleteElementById(TaskQueue* queue, int id);

#endif // QUEUE_H
