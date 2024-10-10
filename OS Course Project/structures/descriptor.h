#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

typedef struct TaskDescriptor {
    int id;
    struct TaskDescriptor* prev;
    struct TaskDescriptor* next;
} TaskDescriptor;

#endif
