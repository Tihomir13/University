#include "fiber.h"

// Реализация на функцията fiber
void fiber(ucontext_t* currContext, ucontext_t* nextContext, const char* nameCurr, const char* nameNext) {
    printf("%s: started\n", nameCurr);
    printf("%s: Now swap context to %s\n", nameCurr, nameNext);
    swapcontext(currContext, nextContext);
    printf("%s: finished\n", nameCurr);
}
