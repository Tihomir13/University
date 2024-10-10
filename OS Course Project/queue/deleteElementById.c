#include "../headers.h"

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
