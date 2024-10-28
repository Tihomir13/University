#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

#define FIBER_STACK 1024 * 64

ucontext_t uctx_func, uctx_main;

void fiber() {
    printf("Fiber: started\n");
    printf("Fiber: Now swap context to main\n");
    swapcontext(&uctx_func, &uctx_main);
    printf("Fiber: returned\n");
    printf("Fiber: Now swap context again to main\n");
    swapcontext(&uctx_func, &uctx_main);
}

int main() {
    getcontext(&uctx_func);
    uctx_func.uc_link = NULL;
    uctx_func.uc_stack.ss_sp = malloc(FIBER_STACK);
    if (uctx_func.uc_stack.ss_sp == NULL) {
        perror("Failed to allocate stack");
        return 1;
    }
    uctx_func.uc_stack.ss_size = FIBER_STACK;
    uctx_func.uc_stack.ss_flags = 0;

    makecontext(&uctx_func, fiber, 0);

    printf("Main: swap context to fiber\n");
    swapcontext(&uctx_main, &uctx_func);
    printf("Main: returned\n");
    
    printf("Main: swap context again to fiber\n");
    swapcontext(&uctx_main, &uctx_func);
    printf("Main: returned\n");
    printf("Main: exiting\n");

    free(uctx_func.uc_stack.ss_sp); // Освобождаване на паметта
    return 0;
}
