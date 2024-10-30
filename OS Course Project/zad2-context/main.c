#include <stdlib.h>
#include <ucontext.h>
#include "fiber.h"

#define FIBER_STACK 1024 * 64

ucontext_t mainContext, fiber1Context;

int main() {
    char stack1[FIBER_STACK];

    // Инициализация на fiber1
    getcontext(&fiber1Context);
    fiber1Context.uc_stack.ss_sp = stack1;
    fiber1Context.uc_stack.ss_size = sizeof(stack1);
    fiber1Context.uc_link = &mainContext;

    // Променяме извикването на `makecontext` и параметрите, за да работи с `fiber`
    makecontext(&fiber1Context, (void (*)())fiber, 4, &fiber1Context, &mainContext, "Fiber1", "Main");

    printf("Main: swap context to Fiber1\n");
    swapcontext(&mainContext, &fiber1Context);
    printf("Main: returned from Fiber1\n");

    printf("Main: exiting\n");

    return 0;
}
