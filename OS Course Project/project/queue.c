#include <stdlib.h>
#include "queue.h"

void addElement(TaskQueue *queue, task_t *newTask) {
    newTask->next = NULL;
    if (!queue->tail) {
        queue->head = queue->tail = newTask;
        newTask->prev = NULL;
    } else {
        queue->tail->next = newTask;
        newTask->prev = queue->tail;
        queue->tail = newTask;
    }
}

task_t* getFirstElement(TaskQueue *queue) {
    if (!queue->head) {
        return NULL;
    }
    task_t *task = queue->head;
    queue->head = task->next;
    if (queue->head) {
        queue->head->prev = NULL;
    } else {
        queue->tail = NULL;
    }
    return task;
}

void deleteElementById(TaskQueue *queue, int id) {
    task_t *current = queue->head;
    while (current) {
        if (current->id == id) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                queue->head = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                queue->tail = current->prev;
            }
            free(current->context.uc_stack.ss_sp);
            free(current);
            return;
        }
        current = current->next;
    }
}
