#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void child_handler(int sig) {
    printf("[Rodzic] Otrzymałem SIGCHLD. Jeśli nie zrobię wait(), powstanie zombie.\n");
}

int main() {
    // Wariant: Przechwytywanie (powoduje powstanie Zombie, jeśli brak wait)
    // Aby naprawić, należałoby użyć: signal(SIGCHLD, SIG_IGN);
    signal(SIGCHLD, child_handler);

    if (fork() == 0) {
        printf("[Dziecko] Kończę działanie.\n");
        exit(0);
    }

    printf("[Rodzic] Śpię 10s. Sprawdź procesy (ps -l) - szukaj <defunct>.\n");
    sleep(10);
    return 0;
}