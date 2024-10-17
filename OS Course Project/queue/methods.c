#include <stdio.h>
#include <stdlib.h>

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

void printMenu() {
    printf("1 - Добави задача\n");
    printf("2 - Вземи първата задача\n");
    printf("3 - Изтрий задача по ID\n");
    printf("4 - Изход\n");
    printf("Изберете опция: ");
}

int main() {
    TaskQueue queue = { NULL, NULL };  // Инициализиране на празна опашка
    int choice, taskId;
    TaskDescriptor *task;
    
    do {
        printMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                task = (TaskDescriptor *)malloc(sizeof(TaskDescriptor));
                if (task == NULL) {
                    printf("Грешка при заделяне на памет!\n");
                    break;
                }
                printf("Въведете ID на задачата: ");
                scanf("%d", &task->id);
                addElement(&queue, task);
                printf("Задачата с ID %d е добавена в опашката.\n", task->id);
                break;
            }
            case 2: {
                task = getFirstElement(&queue);
                if (task != NULL) {
                    printf("Първата задача с ID %d е взета от опашката.\n", task->id);
                    free(task);
                } else {
                    printf("Опашката е празна.\n");
                }
                break;
            }
            case 3: {
                printf("Въведете ID на задачата за изтриване: ");
                scanf("%d", &taskId);
                deleteElementById(&queue, taskId);
                printf("Задачата с ID %d е изтрита (ако е съществувала).\n", taskId);
                break;
            }
            case 4: {
                printf("Изход...\n");
                break;
            }
            default:
                printf("Невалидна опция! Опитайте отново.\n");
        }
    } while (choice != 4);
    
    return 0;
}