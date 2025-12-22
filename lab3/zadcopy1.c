/* Zadanie 1: Obsługa sygnałów z klawiatury */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig) {
    if (sig == SIGINT) {
        printf("\n[Sygnał %d] Otrzymano SIGINT (Ctrl-C)\n", sig);
    } else if (sig == SIGTSTP) {
        printf("\n[Sygnał %d] Otrzymano SIGTSTP (Ctrl-Z)\n", sig);
    } else if (sig == SIGQUIT) {
        printf("\n[Sygnał %d] Otrzymano SIGQUIT (Ctrl-\\)\n", sig);
    }
}

int main() {
    // Rejestracja funkcji obsługi
    signal(SIGINT, handler);   // Ctrl-C
    signal(SIGTSTP, handler);  // Ctrl-Z
    signal(SIGQUIT, handler);  // Ctrl-\ (Backslash)

    printf("Program uruchomiony (PID: %d).\n", getpid());
    printf("Testuj: Ctrl-C, Ctrl-Z, Ctrl-\\.\n");
    
    while(1) {
        pause(); // Oszczędza procesor czekając na sygnał
    }
    return 0;
}