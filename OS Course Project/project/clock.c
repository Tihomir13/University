#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

int virtual_clock = 0;

void signal_handler(int signum) {
    if (signum == SIGALRM) {
        ++virtual_clock;
    }
    printf("Виртуален часовник: %d секунди\n", virtual_clock);
    fflush(stdout);
}

void setup_clock() {
    struct itimerval timer;

    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;

    signal(SIGALRM, signal_handler);
    setitimer(ITIMER_REAL, &timer, NULL);
}
