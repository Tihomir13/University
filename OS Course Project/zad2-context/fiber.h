#ifndef FIBER_H
#define FIBER_H

#include <ucontext.h>
#include <stdio.h>

void fiber(ucontext_t* currContext, ucontext_t* nextContext, const char* nameCurr, const char* nameNext);

#endif // FIBER_H
