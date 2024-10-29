#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

#define FIBER_STACK 1024 * 64
ucontext_t mainContext, fiber1Context, fiber2Context, fiber3Context;

void fiber(ucontext_t& currContext, ucontext_t& nextContext, const char* nameCurr, const char* nameNext) {
    printf("%s: started\n", nameCurr);
    printf("%s: Now swap context to %s\n", nameCurr, nameNext);
    swapcontext(&currContext, &nextContext);
    printf("%s: finished\n", nameCurr);
}

int main() {
    char stack1[FIBER_STACK];

    // Инициализация на fiber1
    getcontext(&fiber1Context);
    fiber1Context.uc_stack.ss_sp = stack1;
    fiber1Context.uc_stack.ss_size = sizeof(stack1);
    fiber1Context.uc_link = &mainContext;  // Връща се към mainContext след приключване на fiber1
    makecontext(&fiber1Context, (void (*)())fiber, 4, fiber1Context, mainContext, "Fiber1", "Main");

    printf("Main: swap context to Fiber1\n");
    swapcontext(&mainContext, &fiber1Context); // Превключване към Fiber1
    printf("Main: returned from Fiber1\n");

    printf("Main: exiting\n");

    return 0;
}
