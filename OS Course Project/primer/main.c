#define FIBER_STACK 1024 * 64
ucontext_t uctx_func, uctx_main;
void func1()
{
    printf("Hello I am func1\n");
}
int main()
{
    getcontext(&uctx_func);
    uctx_func.uc_link = NULL;
    uctx_func.uc_stack.ss_sp = malloc(FIBER_STACK);
    uctx_func.uc_stack.ss_size = FIBER_STACK;
    uctx_func.uc_stack.ss_flags = 0;
    makecontext(&uctx_func, func1, 0);
    swapcontext(&uctx_main, &uctx_func);
}