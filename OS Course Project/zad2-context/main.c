#include "fiber.h" // включване на fiber.h за достъп до fiber() функцията

ucontext_t mainContext, fiber1Context, fiber2Context, fiber3Context;

int main() {
    // Динамично заделяне на стекове за всеки fiber с malloc
    char *stack1 = (char *)malloc(FIBER_STACK);
    char *stack2 = (char *)malloc(FIBER_STACK);
    char *stack3 = (char *)malloc(FIBER_STACK);

    if (stack1 == NULL || stack2 == NULL || stack3 == NULL) {
        perror("Неуспешно заделяне на памет за стековете");
        return 1;
    }

    // Създаване на контексти на fiber1, fiber2 и fiber3, свързани в цикъл
    getcontext(&fiber1Context);
    fiber1Context.uc_stack.ss_sp = stack1;
    fiber1Context.uc_stack.ss_size = FIBER_STACK;
    fiber1Context.uc_link = &fiber2Context; // fiber1 се свързва с fiber2
    makecontext(&fiber1Context, (void (*)())changeContext, 4, &fiber1Context, &fiber2Context, "Fiber1", "Fiber2");

    getcontext(&fiber2Context);
    fiber2Context.uc_stack.ss_sp = stack2;
    fiber2Context.uc_stack.ss_size = FIBER_STACK;
    fiber2Context.uc_link = &fiber3Context; // fiber2 се свързва с fiber3
    makecontext(&fiber2Context, (void (*)())changeContext, 4, &fiber2Context, &fiber3Context, "Fiber2", "Fiber3");

    getcontext(&fiber3Context);
    fiber3Context.uc_stack.ss_sp = stack3;
    fiber3Context.uc_stack.ss_size = FIBER_STACK;
    fiber3Context.uc_link = &mainContext; // fiber3 ще се свърже обратно с main след втория цикъл
    makecontext(&fiber3Context, (void (*)())changeContext, 4, &fiber3Context, &fiber1Context, "Fiber3", "Fiber1");

    // Стартиране на първия fiber
    printf("Main: swap context to Fiber1\n");
    swapcontext(&mainContext, &fiber1Context);
    printf("Main: returned after second Fiber3\n");

    // Освобождаване на паметта за стековете
    free(stack1);
    free(stack2);
    free(stack3);

    printf("Main: exiting\n");
    return 0;
}
