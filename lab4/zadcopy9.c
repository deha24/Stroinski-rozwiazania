#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

volatile int active = 1;

void toggle(int sig) {
    active = !active;
    printf("\n[PS] Stan: %s\n", active ? "WZNOWIONY" : "WSTRZYMANY");
}

int main() {
    signal(SIGINT, toggle);

    if (fork() == 0) {
        signal(SIGINT, SIG_IGN); // Dziecko ls nie reaguje
        while(1) {
            if(fork() == 0) { execlp("ls", "ls", NULL); exit(1); }
            wait(NULL);
            sleep(2);
        }
    } else {
        while(1) {
            if(active) {
                if(fork() == 0) { execlp("ps", "ps", NULL); exit(1); }
                wait(NULL);
                sleep(2);
            } else {
                pause(); // Czekaj na sygnał (oszczędzanie CPU)
            }
        }
    }
    return 0;
}