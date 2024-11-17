#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

int virtual_clock = 0;

void signal_handler(int signum) {
    if (signum == SIGALRM) {
        virtual_clock++;
        printf("Виртуален часовник: %d секунди\n", virtual_clock);
        fflush(stdout);
    }
}

int main() {
    signal(SIGALRM, signal_handler);

    struct itimerval timer;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL);

    while (1) {
        pause();
    }

    return 0;
}
