int main()
{
    getcontext(&uctx_func);
    uctx_func.uc_link = NULL;
    uctx_func.uc_stack.ss_sp = malloc(FIBER_STACK);
    uctx_func.uc_stack.ss_size = FIBER_STACK;
    uctx_func.uc_stack.ss_flags = 0;
    makecontext(&uctx_func, fiber, 0);
    printf(“Main : swap context to fiber\n”);
    swapcontext(&uctx_main, &uctx_func);
    printf(“Main : returned\n”);
    printf(“Main : swap context again to fiber\n”);
    swapcontext(&uctx_main, &uctx_func);
    printf(“Main : returned\n”);
    printf(“Main : exiting\n”);
    return 0;
}
Пример за превключване на контекст
