#include "./includes.h"

void printMenu() {
    printf("1 - Add Task\n");
    printf("2 - Get first Task\n");
    printf("3 - Delete Task by ID\n");
    printf("4 - Exit\n");
    printf("Enter Option: ");
}

int main() {
    TaskQueue queue = { NULL, NULL };
    int choice, taskId;
    TaskDescriptor *task;

    do {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                task = (TaskDescriptor *)malloc(sizeof(TaskDescriptor));
                if (task == NULL) {
                    printf("Memory allocation error!\n");
                    break;
                }
                printf("Enter Task ID: ");
                scanf("%d", &task->id);
                addElement(&queue, task);
                printf("Task with ID %d has been added to the queue.\n", task->id);
                break;
            }
            case 2: {
                task = getFirstElement(&queue);
                if (task != NULL) {
                    printf("The first task with ID %d has been retrieved from the queue.\n", task->id);
                    free(task);
                } else {
                    printf("The queue is empty.\n");
                }
                break;
            }
            case 3: {
                printf("Enter the Task ID to delete: ");
                scanf("%d", &taskId);
                deleteElementById(&queue, taskId);
                printf("Task with ID %d has been deleted (if it existed).\n", taskId);
                break;
            }
            case 4: {
                printf("Exiting...\n");
                break;
            }
            default:
                printf("Invalid option! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}