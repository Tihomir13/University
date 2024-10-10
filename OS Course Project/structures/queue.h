#ifndef QUEUE_H
#define QUEUE_H

#include "descriptor.h"

typedef struct TaskQueue {
    TaskDescriptor* head;
    TaskDescriptor* tail;
} TaskQueue;

#endif
