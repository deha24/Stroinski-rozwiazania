/* Zadanie 6: Wyścig procesów */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

#define N 5 // Liczba potomków

int main() {
    pid_t pids[N];
    srand(time(NULL)); // Inicjalizacja losowości

    printf("Tworzę %d potomków. Start wyścigu!\n", N);

    for (int i = 0; i < N; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            // Kod potomka
            srand(getpid()); // Unikalne ziarno dla każdego procesu
            int wait_time = 1 + rand() % 8; // Losowy czas 1-8s
            sleep(wait_time);
            printf("--> Potomek %d (PID: %d) skończył po %ds.\n", i, getpid(), wait_time);
            exit(0);
        }
    }

    // Kod rodzica
    int status;
    pid_t winner = wait(&status); // Czeka na PIERWSZEGO zakończonego
    printf("\n*** Zwycięzca: PID %d ***\nZabijam pozostałe procesy...\n", winner);

    for (int i = 0; i < N; i++) {
        if (pids[i] != winner) {
            kill(pids[i], SIGTERM); // Wysyła sygnał zakończenia
        }
    }
    
    // Sprzątanie resztek (zapobieganie zombie z zabitych procesów)
    for (int i = 0; i < N - 1; i++) wait(NULL);

    printf("Wszystkie procesy posprzątane. Koniec.\n");
    return 0;
}