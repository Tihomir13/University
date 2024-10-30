#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "fiber.h" // включване на декларацията за fiber()

#define FIBER_STACK 1024 * 64

ucontext_t mainContext, fiber1Context, fiber2Context, fiber3Context;

int main() {
    // Заделяне на стекове за всеки fiber
    char stack1[FIBER_STACK], stack2[FIBER_STACK], stack3[FIBER_STACK];

    // Инициализация на fiber1
    getcontext(&fiber1Context);
    fiber1Context.uc_stack.ss_sp = stack1;
    fiber1Context.uc_stack.ss_size = sizeof(stack1);
    fiber1Context.uc_link = &mainContext;  // Връща се в main след fiber3
    makecontext(&fiber1Context, (void (*)())fiber, 4, &fiber1Context, &fiber2Context, "Fiber1", "Fiber2");

    // Инициализация на fiber2
    getcontext(&fiber2Context);
    fiber2Context.uc_stack.ss_sp = stack2;
    fiber2Context.uc_stack.ss_size = sizeof(stack2);
    fiber2Context.uc_link = &mainContext;  // Връща се в main след fiber3
    makecontext(&fiber2Context, (void (*)())fiber, 4, &fiber2Context, &fiber3Context, "Fiber2", "Fiber3");

    // Инициализация на fiber3
    getcontext(&fiber3Context);
    fiber3Context.uc_stack.ss_sp = stack3;
    fiber3Context.uc_stack.ss_size = sizeof(stack3);
    fiber3Context.uc_link = &mainContext;  // Връща се в main след fiber3
    makecontext(&fiber3Context, (void (*)())fiber, 4, &fiber3Context, &mainContext, "Fiber3", "Main");

    // Превключване от main към fiber1
    printf("Main: swap context to Fiber1\n");
    swapcontext(&mainContext, &fiber1Context);
    printf("Main: returned from Fiber3\n");

    printf("Main: exiting\n");
    return 0;
}
