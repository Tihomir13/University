#include "../headers.h"

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
