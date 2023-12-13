#include <stdio.h>
#include <signal.h>
#include <unistd.h>

typedef void (*sighandler_t)(int);

sighandler_t my_signal(int signum, sighandler_t handler) {
    return signal(signum, handler);
}

void alarmHandler(int signo);

int main()
{
    my_signal(SIGALRM, alarmHandler);
    alarm(5);    
    short i = 0;
    while (1) {
        sleep(1);
        i++;
        printf("%d second\n", i);
    }
}

void alarmHandler(int signo)
{
    printf("Wake up\n");
    exit(0);
}

