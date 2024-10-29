#include <iostream>
#include <ucontext.h>

constexpr int STACK_SIZE = 8192;
ucontext_t mainContext, fiber1Context, fiber2Context, fiber3Context;

void fiber1() {
    std::cout << "fiber1 start\n";
    swapcontext(&fiber1Context, &fiber2Context);
    std::cout << "fiber1 end\n";
    swapcontext(&fiber1Context, &fiber3Context);
}

void fiber2() {
    std::cout << "fiber2 start\n";
    swapcontext(&fiber2Context, &fiber3Context);
    std::cout << "fiber2 end\n";
    swapcontext(&fiber2Context, &fiber1Context);
}

void fiber3() {
    std::cout << "fiber3 start\n";
    swapcontext(&fiber3Context, &fiber1Context);
    std::cout << "fiber3 end\n";
    swapcontext(&fiber3Context, &mainContext);
}

int main() {
    char stack1[STACK_SIZE], stack2[STACK_SIZE], stack3[STACK_SIZE];

    // Инициализация на fiber1
    getcontext(&fiber1Context);
    fiber1Context.uc_stack.ss_sp = stack1;
    fiber1Context.uc_stack.ss_size = sizeof(stack1);
    fiber1Context.uc_link = &mainContext;
    makecontext(&fiber1Context, fiber1, 0);

    // Инициализация на fiber2
    getcontext(&fiber2Context);
    fiber2Context.uc_stack.ss_sp = stack2;
    fiber2Context.uc_stack.ss_size = sizeof(stack2);
    fiber2Context.uc_link = &mainContext;
    makecontext(&fiber2Context, fiber2, 0);

    // Инициализация на fiber3
    getcontext(&fiber3Context);
    fiber3Context.uc_stack.ss_sp = stack3;
    fiber3Context.uc_stack.ss_size = sizeof(stack3);
    fiber3Context.uc_link = &mainContext;
    makecontext(&fiber3Context, fiber3, 0);

    std::cout << "main start\n";
    swapcontext(&mainContext, &fiber1Context);
    std::cout << "main end\n";

    return 0;
}
