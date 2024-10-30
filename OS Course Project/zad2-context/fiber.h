// fiber.h
#ifndef FIBER_H
#define FIBER_H

#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

#define FIBER_STACK 1024 * 64

// Декларация на функцията fiber
void changeContext(ucontext_t* currContext, ucontext_t* nextContext, const char* nameCurr, const char* nameNext);

#endif // FIBER_H
