#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

volatile int run = 1;

void stop(int sig) {
    run = 0;
}

int main() {
    signal(SIGINT, stop); // Tylko rodzic obsłuży to wyjściem z pętli

    if (fork() == 0) {
        signal(SIGINT, SIG_IGN); // Dziecko (ls) ignoruje Ctrl-C
        while(1) {
            if(fork() == 0) { execlp("ls", "ls", NULL); exit(1); }
            wait(NULL);
            sleep(2);
        }
    } else {
        while(run) {
            if(fork() == 0) { execlp("ps", "ps", NULL); exit(1); }
            wait(NULL);
            sleep(2);
        }
        printf("Koniec pętli ps.\n");
        exit(0); // Rodzic kończy, dziecko ls działa dalej w tle
    }
    return 0;
}