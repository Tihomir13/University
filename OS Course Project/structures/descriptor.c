typedef struct TaskDescriptor {
    int id;
    struct TaskDescriptor* prev;
    struct TaskDescriptor* next;
} TaskDescriptor;
