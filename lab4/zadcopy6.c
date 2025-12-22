#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

#define N 5 // Liczba procesów

int main() {
    pid_t pids[N];
    srand(time(NULL));

    for(int i=0; i<N; i++) {
        if((pids[i] = fork()) == 0) {
            srand(getpid()); // Unikalne ziarno
            int t = 1 + rand() % 10;
            sleep(t);
            printf("Potomek PID %d skończył po %ds.\n", getpid(), t);
            exit(0);
        }
    }

    // Rodzic czeka na pierwszego
    int status;
    pid_t winner = wait(&status);
    printf("--- Zwycięzca: PID %d. Zabijam resztę. ---\n", winner);

    for(int i=0; i<N; i++) {
        if(pids[i] != winner) kill(pids[i], SIGTERM);
    }
    
    // Odbieramy statusy zabitych (sprzątanie zombie)
    for(int i=0; i<N-1; i++) wait(NULL);
    
    return 0;
}