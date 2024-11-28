#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h> // Този хедър файл е необходим
#include "clock.h"

// Глобални променливи
static int virtual_clock = 0;
static task_t *RunningTask = NULL;
static TaskQueue *globalQueue = NULL;

void signal_handler(int signum) {
    if (signum == SIGALRM) {
        virtual_clock++;
        printf("Clock tick: %d\n", virtual_clock);

        // Връщане на текущата задача в опашката
        if (RunningTask) {
            addElement(globalQueue, RunningTask);
        }

        // Вземане на нова задача от опашката
        RunningTask = getFirstElement(globalQueue);
        if (RunningTask) {
            setcontext(&(RunningTask->context));
        }
    }
}

void setup_clock(TaskQueue *taskQueue) {
    globalQueue = taskQueue;

    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGALRM, &sa, NULL);

    struct itimerval timer;
    timer.it_interval.tv_sec = 1;  // Честота на прекъсванията (1 секунда)
    timer.it_interval.tv_usec = 0;
    timer.it_value.tv_sec = 1;     // Първоначално забавяне (1 секунда)
    timer.it_value.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL);
}
