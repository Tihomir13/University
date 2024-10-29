#include "./header.h"
#include <stdio.h>

void fiber() {
    printf("Fiber: started\n");
    printf("Fiber: Now swap context to main\n");
    swapcontext(&uctx_func, &uctx_main);
    printf("Fiber: returned\n");
    printf("Fiber: Now swap context again to main\n");
    swapcontext(&uctx_func, &uctx_main);
}
