/* Zadanie 9: Ctrl-C jako przełącznik (start/stop) dla ps */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

volatile int active = 1; // 1 = działa, 0 = pauza

void toggle_ps(int sig) {
    active = !active; // Przełącz stan
    if (active) printf("\n[Switch] WZNOWIONO wykonywanie ps.\n");
    else printf("\n[Switch] WSTRZYMANO wykonywanie ps.\n");
}

int main() {
    signal(SIGINT, toggle_ps);

    if (fork() == 0) {
        // --- Proces ls (ignoruje Ctrl-C, żeby nie przerywać pracy) ---
        signal(SIGINT, SIG_IGN);
        while(1) {
            // ls wykonuje się w tle co 2 sekundy
            if (fork() == 0) { execlp("ls", "ls", NULL); exit(1); }
            wait(NULL);
            sleep(2);
        }
    } else {
        // --- Proces ps (sterowany sygnałem) ---
        while(1) {
            if (active) {
                if (fork() == 0) { execlp("ps", "ps", NULL); exit(1); }
                wait(NULL);
                sleep(2);
            } else {
                // Jeśli pauza, czekaj na sygnał (nie zużywaj CPU w pustej pętli)
                pause(); 
            }
        }
    }
    return 0;
}