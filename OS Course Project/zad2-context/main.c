// main.c
#include "fiber.h" // включване на fiber.h за достъп до fiber() функцията

ucontext_t mainContext, fiber1Context, fiber2Context, fiber3Context;

int main() {
    // Заделяне на стекове за всеки fiber
    char stack1[FIBER_STACK], stack2[FIBER_STACK], stack3[FIBER_STACK];

    // Първи цикъл на fiber1, fiber2 и fiber3
    getcontext(&fiber1Context);
    fiber1Context.uc_stack.ss_sp = stack1;
    fiber1Context.uc_stack.ss_size = sizeof(stack1);
    fiber1Context.uc_link = &fiber2Context;
    makecontext(&fiber1Context, (void (*)())changeContext, 4, &fiber1Context, &fiber2Context, "Fiber1", "Fiber2");

    getcontext(&fiber2Context);
    fiber2Context.uc_stack.ss_sp = stack2;
    fiber2Context.uc_stack.ss_size = sizeof(stack2);
    fiber2Context.uc_link = &fiber3Context;
    makecontext(&fiber2Context, (void (*)())changeContext, 4, &fiber2Context, &fiber3Context, "Fiber2", "Fiber3");

    getcontext(&fiber3Context);
    fiber3Context.uc_stack.ss_sp = stack3;
    fiber3Context.uc_stack.ss_size = sizeof(stack3);
    fiber3Context.uc_link = &fiber1Context; // Втори цикъл от fiber1
    makecontext(&fiber3Context, (void (*)())changeContext, 4, &fiber3Context, &fiber1Context, "Fiber3", "Fiber1");

    // Втори цикъл на fiber1, fiber2 и fiber3
    getcontext(&fiber1Context);
    fiber1Context.uc_stack.ss_sp = stack1;
    fiber1Context.uc_stack.ss_size = sizeof(stack1);
    fiber1Context.uc_link = &fiber2Context;
    makecontext(&fiber1Context, (void (*)())changeContext, 4, &fiber1Context, &fiber2Context, "Fiber1", "Fiber2");

    getcontext(&fiber2Context);
    fiber2Context.uc_stack.ss_sp = stack2;
    fiber2Context.uc_stack.ss_size = sizeof(stack2);
    fiber2Context.uc_link = &fiber3Context;
    makecontext(&fiber2Context, (void (*)())changeContext, 4, &fiber2Context, &fiber3Context, "Fiber2", "Fiber3");

    getcontext(&fiber3Context);
    fiber3Context.uc_stack.ss_sp = stack3;
    fiber3Context.uc_stack.ss_size = sizeof(stack3);
    fiber3Context.uc_link = &mainContext;
    makecontext(&fiber3Context, (void (*)())changeContext, 4, &fiber3Context, &mainContext, "Fiber3", "Main");

    // Стартиране на първия fiber
    printf("Main: swap context to Fiber1\n");
    swapcontext(&mainContext, &fiber1Context);
    printf("Main: returned after second Fiber3\n");

    printf("Main: exiting\n");
    return 0;
}
