#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    // Ustawiamy bieżący proces (rodzica) jako lidera nowej grupy procesów.
    // setpgid(pid, pgid) -> 0, 0 oznacza: ustaw procesowi o moim PID grupę równą mojemu PID.
    setpgid(0, 0); 
    
    printf("Lider grupy (Rodzic): PID %d, PGID (ID Grupy): %d\n", getpid(), getpgrp());

    // Tworzymy dwa procesy potomne
    for (int i = 0; i < 2; i++) {
        if (fork() == 0) {
            // --- Kod Potomka ---
            
            // Potomek dziedziczy grupę, ale zgodnie z poleceniem możemy wymusić/potwierdzić
            // ustawienie grupy. Pobieramy PGID rodzica.
            // Uwaga: w nowoczesnych systemach zazwyczaj nie trzeba tego robić ręcznie po forku, 
            // ale zadanie sugeruje użycie funkcji.
            
            printf("Potomek %d: PID %d, PGID: %d. Pracuję...\n", i+1, getpid(), getpgrp());
            sleep(2); // Symulacja pracy
            printf("Potomek %d: Kończę.\n", i+1);
            exit(0);
        }
    }

    // --- Kod Rodzica (Lidera) ---
    // Czekamy na zakończenie dwóch procesów
    for (int i = 0; i < 2; i++) {
        wait(NULL);
    }

    printf("Lider grupy: Wszystkie procesy z mojej grupy zakończyły zadania.\n");

    return 0;
}