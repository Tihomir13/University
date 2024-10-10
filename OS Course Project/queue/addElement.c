#include "../headers.h"

void addElement(TaskQueue *queue, TaskDescriptor *newTask)
{
    newTask->next = NULL;
    if (queue->tail == NULL)
    {
        newTask->prev = NULL;
        queue->head = newTask;
        queue->tail = newTask;
    }
    else
    {
        newTask->prev = queue->tail;
        queue->tail->next = newTask;
        queue->tail = newTask;
    }
}
