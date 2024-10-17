#include "../includes.h"

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

TaskDescriptor* getFirstElement(TaskQueue* queue) {
    if (queue->head == NULL) {
        return NULL;
    }
    
    TaskDescriptor* firstTask = queue->head;
    queue->head = firstTask->next;
    
    if (queue->head == NULL) {
        queue->tail = NULL;
    } else {
        queue->head->prev = NULL;
    }
    
    return firstTask;
}

void deleteElementById(TaskQueue* queue, int id) {
    TaskDescriptor* current = queue->head;
    
    while (current != NULL) {
        if (current->id == id) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                queue->head = current->next;
            }
            
            if (current->next != NULL) {
                current->next->prev = current->prev;
            } else {
                queue->tail = current->prev;
            }
            
            free(current);
            return;
        }
        current = current->next;
    }
}