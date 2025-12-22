/* Zadanie 8: Zatrzymanie wykonywania ps po Ctrl-C */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

// Zmienna 'volatile' informuje kompilator, że wartość może zmienić się z zewnątrz (przez sygnał)
volatile int run_ps = 1;

void stop_ps(int sig) {
    run_ps = 0;
    printf("\n\n[Sygnał] Odebrano SIGINT. Kończę pętlę ps.\n");
}

int main() {
    // Rejestracja sygnału TYLKO w rodzicu (przed forkiem) lub obsługa w obu
    // Tutaj chcemy, żeby rodzic (ps) zareagował.
    signal(SIGINT, stop_ps);

    if (fork() == 0) {
        // --- Dziecko: Pętla ls (nie reaguje na zmienną run_ps) ---
        // Przywracamy domyślną obsługę w dziecku, żeby nie przechwytywało sygnału rodzica
        // (W praktyce terminal wyśle sygnał do obu, chyba że zmienimy grupy procesów)
        signal(SIGINT, SIG_IGN); 
        
        while(1) {
            if (fork() == 0) { execlp("ls", "ls", NULL); exit(1); }
            wait(NULL);
            sleep(1); 
        }
    } else {
        // --- Rodzic: Pętla ps ---
        while(run_ps) {
            if (fork() == 0) { execlp("ps", "ps", NULL); exit(1); }
            wait(NULL);
            sleep(1);
        }
        
        printf("Rodzic zakończył generowanie ps. (ls działa dalej w tle)\n");
        exit(0);
    }
    return 0;
}