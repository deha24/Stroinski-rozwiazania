/* Zadanie 5: SIGCHLD i procesy Zombie */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void child_handler(int sig) {
    printf("[Rodzic] Otrzymałem SIGCHLD - potomek zakończył działanie.\n");
    // UWAGA: Brak wait() tutaj spowoduje powstanie Zombie!
}

int main() {
    printf("--- Test: Przechwytywanie SIGCHLD bez wait() ---\n");
    signal(SIGCHLD, child_handler);
    
    // Odkomentuj poniższą linię, aby naprawić problem zombie automatycznie:
    // signal(SIGCHLD, SIG_IGN); 

    pid_t pid = fork();
    if (pid == 0) {
        printf("[Dziecko] PID: %d. Kończę pracę.\n", getpid());
        exit(0);
    }

    // Rodzic śpi, żebyś mógł sprawdzić procesy w innej konsoli (polecenie: ps -l)
    printf("[Rodzic] Czekam 5 sekund. Sprawdź czy jest [defunct/zombie]...\n");
    sleep(5);
    
    printf("[Rodzic] Koniec.\n");
    return 0;
}