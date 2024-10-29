#ifndef HEADER_H
#define HEADER_H

#include <ucontext.h>

extern ucontext_t uctx_func, uctx_main;

void fiber();

#endif // HEADER_H
