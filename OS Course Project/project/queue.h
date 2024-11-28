#ifndef QUEUE_H
#define QUEUE_H

#include "task.h"

// Дефиниция на структурата TaskQueue
typedef struct TaskQueue {
    task_t *head;
    task_t *tail;
} TaskQueue;

// Декларации на функции за управление на опашката
void addElement(TaskQueue *queue, task_t *newTask);
task_t* getFirstElement(TaskQueue *queue);
void deleteElementById(TaskQueue *queue, int id);

#endif // QUEUE_H
