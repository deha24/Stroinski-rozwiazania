#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pid = fork();

    if (pid > 0) {
        // --- Proces Rodzica ---
        printf("[Rodzic] PID: %d. Kończę działanie natychmiast.\n", getpid());
        exit(0); 
        // Rodzic umiera, dziecko staje się sierotą
    } 
    else if (pid == 0) {
        // --- Proces Dziecka ---
        printf("[Dziecko] PID: %d, Mój rodzic (PPID): %d\n", getpid(), getppid());
        
        // Usypiamy dziecko, żeby dać czas rodzicowi na zakończenie działania
        sleep(2); 

        printf("\n[Dziecko] Po śmierci rodzica...\n");
        // Sprawdzamy kto jest teraz rodzicem. Powinien to być system (np. PID 1 lub ~1000 systemd)
        printf("[Dziecko] PID: %d, Mój NOWY rodzic (PPID): %d (Zostałem adoptowany)\n", getpid(), getppid());
    }

    return 0;
}