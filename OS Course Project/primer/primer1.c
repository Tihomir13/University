#include <malloc.h>
#include <ucontext.h>
#include <stdio.h>
#define FIBER_STACK 1024 * 64
ucontext_t uctx_func, uctx_main;
void fiber()
{
    printf("Fiber : started\n");
    printf("Fiber : Now swap context to main\n");
    swapcontext(&uctx_func, &uctx_main);
    printf("Fiber : returned\n");
    printf("Fiber : Now swap context again to main\n");
    swapcontext(&uctx_func, &uctx_main);
}
